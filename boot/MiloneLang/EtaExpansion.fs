/// ## Un-eta
///
/// Resolve partial applications and function references.
/// Convert them to statements to create a function object with specified /arguments.
///
/// Thanks to declosure, in this stage, functions don't rely on local scope.
///
/// ### Example
///
/// Consider `let sum x y z = x + y + z` and partial application `sum 1 2`.
/// Here the given arguments is `1, 2`, the rest arguments is `z`.
/// We define a helper function called `sumObj` like this:
///
/// ```fsharp
///    let sumObj env z =
///      let x, y = unbox env
///      add x y z
/// ```
///
/// and convert partial application into the following.
///
/// ```fsharp
///    let env = box (x, y)
///    (sumObj, env) :> (int -> int)
/// ```
///
/// ### Function references
///
/// You can think of function reference as a kind of partial application
/// with given arguments is empty. In term of the above example,
///
/// ```fsharp
///    let sumObj env x y z =
///      let () = unbox env
///      add x y z
/// ```
///
/// is defined for function reference `sum` and the use site is converted to:
///
/// ```fsharp
///    let env = box ()
///    (sumObj, ()) :> (int -> int -> int -> int)
/// ```
module rec MiloneLang.EtaExpansion

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Typing
open MiloneLang.Records

[<RequireQualifiedAccess>]
type CalleeKind =
  | Fun
  | Obj

let etaCtxFromTyCtx (ftCtx: TyCtx): EtaCtx =
  EtaCtx(ftCtx |> tyCtxGetSerial, ftCtx |> tyCtxGetVars, ftCtx |> tyCtxGetTys)

let etaCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: EtaCtx) =
  tyCtx
  |> tyCtxWithSerial (ctx |> etaCtxGetSerial)
  |> tyCtxWithVars (ctx |> etaCtxGetVars)
  |> tyCtxWithTys (ctx |> etaCtxGetTys)

let etaCtxFreshFun (ident: Ident) arity (ty: Ty) loc (ctx: EtaCtx) =
  let serial = (ctx |> etaCtxGetSerial) + 1

  let tyScheme =
    let isOwned (_: Serial) = true // FIXME: is it okay?
    tyGeneralize isOwned ty

  let ctx =
    ctx
    |> etaCtxWithSerial ((ctx |> etaCtxGetSerial) + 1)
    |> etaCtxWithVars
         (ctx
          |> etaCtxGetVars
          |> mapAdd serial (FunDef(ident, arity, tyScheme, loc)))

  let refExpr = HRefExpr(serial, ty, loc)
  refExpr, serial, ctx

let etaCtxFreshVar (ident: Ident) (ty: Ty) loc (ctx: EtaCtx) =
  let serial = (ctx |> etaCtxGetSerial) + 1

  let ctx =
    ctx
    |> etaCtxWithSerial ((ctx |> etaCtxGetSerial) + 1)
    |> etaCtxWithVars
         (ctx
          |> etaCtxGetVars
          |> mapAdd serial (VarDef(ident, AutoSM, ty, loc)))

  let refExpr = HRefExpr(serial, ty, loc)
  refExpr, serial, ctx

let etaCtxIsFun serial (ctx: EtaCtx) =
  match ctx |> etaCtxGetVars |> mapTryFind serial with
  | Some (FunDef _) -> true
  | Some (VariantDef _) ->
      // FIXME: not a function
      true
  | _ -> false

let listSplitAt i xs =
  listTruncate i xs, listSkip (intMin i (listLength xs)) xs

let tyAppliedBy n ty =
  match ty with
  | AppTy (FunTyCtor, [ _; ty ]) when n > 0 -> tyAppliedBy (n - 1) ty
  | _ -> ty

/// E.g. given init = `id x` and args `x, y` then we should return `(id x) y`.
let restCall callee args resultTy loc =
  match args with
  | [] -> callee
  | args -> hxCallClosure callee args resultTy loc

let hxCallTo calleeKind callee args resultTy loc =
  match calleeKind, args with
  | _, [] -> callee
  | CalleeKind.Fun, args -> hxCallProc callee args resultTy loc
  | CalleeKind.Obj, args -> hxCallClosure callee args resultTy loc

let createRestArgsAndPats callee arity argLen callLoc ctx =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ -> [], [], ctx
    | n, AppTy (FunTyCtor, [ argTy; restTy ]) ->
        let argRef, argSerial, ctx = etaCtxFreshVar "arg" argTy callLoc ctx
        let restArgPats, restArgs, ctx = go (n - 1) restTy ctx
        let restArgPat = HRefPat(argSerial, argTy, callLoc)
        restArgPat :: restArgPats, argRef :: restArgs, ctx
    | _ -> failwithf "Never: Type error %A" (callLoc, callee, n, restTy)

  let restTy = callee |> exprToTy |> tyAppliedBy argLen
  go (arity - argLen) restTy ctx

let createEnvPatAndTy items callLoc ctx =
  let rec go items ctx =
    match items with
    | [] -> [], [], [], ctx
    | item :: items ->
        let itemTy, itemLoc = exprExtract item
        let itemRef, itemSerial, ctx = etaCtxFreshVar "arg" itemTy itemLoc ctx
        let itemPat = HRefPat(itemSerial, itemTy, itemLoc)
        let itemPats, argTys, argRefs, ctx = go items ctx
        itemPat :: itemPats, itemTy :: argTys, itemRef :: argRefs, ctx

  let itemPats, itemTys, itemRefs, ctx = go items ctx
  let envTy = tyTuple itemTys
  let envPat = HTuplePat(itemPats, envTy, callLoc)
  envPat, envTy, itemRefs, ctx

let createEnvDeconstructLetExpr envPat envTy envArgRef next callLoc =
  let unboxRef =
    HPrimExpr(HPrim.Unbox, tyFun tyObj envTy, callLoc)

  let unboxExpr =
    hxCallProc unboxRef [ envArgRef ] envTy callLoc

  HLetValExpr(PrivateVis, envPat, unboxExpr, next, exprToTy next, callLoc)

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest arguments
/// and calls the partial-applied callee with full arguments.
let createUnderlyingFunDef funTy arity envPat envTy forwardCall restArgPats callLoc ctx =
  let envArgRef, envArgSerial, ctx = etaCtxFreshVar "env" tyObj callLoc ctx
  let envArgPat = HRefPat(envArgSerial, tyObj, callLoc)

  let underlyingFunTy = tyFun envTy funTy

  let _, funSerial, ctx =
    etaCtxFreshFun "fun" arity underlyingFunTy callLoc ctx

  let argPats = envArgPat :: restArgPats

  let body =
    createEnvDeconstructLetExpr envPat envTy envArgRef forwardCall callLoc

  let funLet next =
    HLetFunExpr(funSerial, PrivateVis, false, argPats, body, next, exprToTy next, callLoc)

  let funRef = HRefExpr(funSerial, underlyingFunTy, callLoc)
  funLet, funRef, ctx

let createEnvBoxExpr args envTy callLoc =
  let tuple = hxTuple args callLoc

  let boxRef =
    HPrimExpr(HPrim.Box, tyFun envTy tyObj, callLoc)

  hxCallProc boxRef [ tuple ] tyObj callLoc

/// In the case the callee is a function.
let resolvePartialAppFun callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy
  let envItems = args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, envRefs, ctx = createEnvPatAndTy envItems callLoc ctx
  let forwardArgs = listAppend envRefs restArgs

  let forwardExpr =
    hxCallProc callee forwardArgs resultTy callLoc

  let funLet, funRef, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats callLoc ctx

  let envBoxExpr = createEnvBoxExpr envItems envTy callLoc

  let funObjExpr =
    HInfExpr(InfOp.Closure, [ funRef; envBoxExpr ], tyAppliedBy argLen funTy, callLoc)

  let expr = funLet funObjExpr
  expr, ctx

/// In the case that the callee is a function object.
/// We need to include it to the environment.
let resolvePartialAppObj callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  // Introduce a variable for memoization.
  let calleeRef, calleeLet, ctx =
    let calleeRef, calleeSerial, ctx =
      etaCtxFreshVar "callee" funTy callLoc ctx

    let calleePat = HRefPat(calleeSerial, funTy, callLoc)

    let calleeLet next =
      HLetValExpr(PrivateVis, calleePat, callee, next, exprToTy next, callLoc)

    calleeRef, calleeLet, ctx

  let envItems = calleeRef :: args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, envRefs, ctx = createEnvPatAndTy envItems callLoc ctx

  let calleeRef, forwardArgs =
    match listAppend envRefs restArgs with
    | calleeRef :: forwardArgs -> calleeRef, forwardArgs
    | _ -> failwith "Never"

  let forwardExpr =
    hxCallClosure calleeRef forwardArgs resultTy callLoc

  let funLet, funRef, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats callLoc ctx

  let envBoxExpr = createEnvBoxExpr envItems envTy callLoc

  let closureExpr =
    HInfExpr(InfOp.Closure, [ funRef; envBoxExpr ], tyAppliedBy argLen funTy, callLoc)

  let expr = calleeLet (funLet closureExpr)
  expr, ctx

let resolvePartialApp calleeKind callee arity args argLen callLoc ctx =
  assert (argLen < arity)
  match calleeKind with
  | CalleeKind.Fun -> resolvePartialAppFun callee arity args argLen callLoc ctx
  | CalleeKind.Obj -> resolvePartialAppObj callee arity args argLen callLoc ctx

let unetaCallCore calleeKind callee arity calleeLoc args resultTy callLoc ctx =
  let argLen = listLength args
  if argLen < arity then
    resolvePartialApp calleeKind callee arity args argLen callLoc ctx
  else
    let callArgs, restArgs = listSplitAt arity args
    let callResultTy = tyAppliedBy arity (exprToTy callee)

    let callExpr =
      hxCallTo calleeKind callee callArgs callResultTy calleeLoc

    hxCallTo CalleeKind.Obj callExpr restArgs resultTy callLoc, ctx

let unetaCall callee args resultTy loc ctx =
  match callee, args with
  | HRefExpr (serial, _, calleeLoc), _ when ctx |> etaCtxIsFun serial ->
      let arity =
        match ctx |> etaCtxGetVars |> mapFind serial with
        | FunDef (_, arity, _, _) -> arity
        | VariantDef (_, _, hasPayload, _, _, _) -> if hasPayload then 1 else 0
        | _ -> 1

      let args, ctx = (args, ctx) |> stMap unetaExpr
      unetaCallCore CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx
  | HPrimExpr (prim, primTy, calleeLoc), _ ->
      let arity = prim |> primToArity primTy
      let args, ctx = (args, ctx) |> stMap unetaExpr
      unetaCallCore CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx
  | _, args ->
      let calleeTy, calleeLoc = exprExtract callee
      let callee, ctx = (callee, ctx) |> unetaExpr
      let args, ctx = (args, ctx) |> stMap unetaExpr
      let arity = tyToArity calleeTy // FIXME: maybe wrong
      unetaCallCore CalleeKind.Obj callee arity calleeLoc args resultTy loc ctx
  | _ -> failwith "Never"

let unetaRef expr serial _refTy calleeLoc (ctx: EtaCtx) =
  match ctx |> etaCtxGetVars |> mapTryFind serial with
  | Some (FunDef (_, arity, _, _)) -> resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx
  | _ -> expr, ctx

let unetaPrim expr prim primTy calleeLoc (ctx: EtaCtx) =
  let arity = prim |> primToArity primTy
  if arity = 0
  then expr, ctx
  else resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx

let unetaExprInf expr infOp args ty loc ctx =
  match infOp with
  | InfOp.App ->
      /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
      let rec roll acc callee =
        match callee with
        | HInfExpr (InfOp.App, [ callee; arg ], _, _) -> roll (arg :: acc) callee
        | _ -> callee, acc

      let callee, args = roll [] expr
      unetaCall callee args ty loc ctx
  | _ ->
      let args, ctx = (args, ctx) |> stMap unetaExpr
      HInfExpr(infOp, args, ty, loc), ctx

let unetaExprLetFun callee vis isMainFun argPats body next ty loc ctx =
  let argPats, ctx = (argPats, ctx) |> stMap unetaPat
  let body, ctx = (body, ctx) |> unetaExpr
  let next, ctx = (next, ctx) |> unetaExpr
  HLetFunExpr(callee, vis, isMainFun, argPats, body, next, ty, loc), ctx

let unetaPat (pat, ctx) = pat, ctx

let unetaExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HErrorExpr _ -> expr, ctx
  | HRefExpr (serial, refTy, calleeLoc) -> unetaRef expr serial refTy calleeLoc ctx
  | HPrimExpr (prim, primTy, calleeLoc) -> unetaPrim expr prim primTy calleeLoc ctx
  | HMatchExpr (target, arms, ty, loc) ->
      let target, ctx = (target, ctx) |> unetaExpr

      let arms, ctx =
        (arms, ctx)
        |> stMap (fun ((pat, guard, body), ctx) ->
             let pat, ctx = (pat, ctx) |> unetaPat
             let guard, ctx = (guard, ctx) |> unetaExpr
             let body, ctx = (body, ctx) |> unetaExpr
             (pat, guard, body), ctx)

      HMatchExpr(target, arms, ty, loc), ctx
  | HNavExpr (subject, message, ty, loc) ->
      let subject, ctx = unetaExpr (subject, ctx)
      HNavExpr(subject, message, ty, loc), ctx
  | HInfExpr (infOp, args, ty, loc) -> unetaExprInf expr infOp args ty loc ctx
  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let pat, ctx = (pat, ctx) |> unetaPat
      let init, ctx = (init, ctx) |> unetaExpr
      let next, ctx = (next, ctx) |> unetaExpr
      HLetValExpr(vis, pat, init, next, ty, loc), ctx
  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      unetaExprLetFun callee vis isMainFun args body next ty loc ctx
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let uneta (expr, tyCtx: TyCtx) =
  let etaCtx = etaCtxFromTyCtx tyCtx
  let expr, etaCtx = (expr, etaCtx) |> unetaExpr
  let tyCtx = etaCtx |> etaCtxFeedbackToTyCtx tyCtx
  expr, tyCtx
