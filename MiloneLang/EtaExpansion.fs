/// # EtaExpansion
///
/// Resolves partial applications and function references.
/// Converts them to statements to create a closure object
/// that holds specified arguments.
///
/// Thanks to ClosureConversion, functions are all closed in this stage.
/// That is, all local variables are defined in current functions.
///
/// ## Example
///
/// A function `sum` is defined to take 3 arguments `x, y, z`.
///
/// ```fsharp
///   let sum x y z = x + y + z
///
///   sum 1 2
/// //    ^^^ partial application
/// ```
///
/// The expression `sum 1 2` is a partial application
/// since `sum` is defined to take 3 parameters but given arguments are two,
/// i.e. `x = 1; y = 2`.
///
/// We call parameters whose values are not given in partial application
/// are *rest parameter(s)*. `z` is the rest parameter in current example.
///
/// To transform this, define a helper function, called `sumObj`, like this:
///
/// ```fsharp
///    let sumObj2 env z =
///       let x, y = unbox env
///       add x y z
/// ```
///
/// The function `sumObj2` takes an object `env` and rest parameters (`z`).
/// In its body, expand the `env` and call to the original function (`sum`)
/// with full arguments, which is not a partial application.
///
/// The partial application is finally converted like this (pseudo-code):
///
/// ```fsharp
///    let env = box (x, y)
///    (sumObj2, env) :> (int -> int)  // closure object creation
/// ```
///
/// Given arguments are packed into an object `env` so that `sumObj2` can use them
/// as described above.
///
/// A closure object is then created, where underlying function is `sumObj2`
/// and state is `env`.
///
/// ## Function references
///
/// Function references are partial application with no arguments.
/// For example:
///
/// ```fsharp
///    let f = sum
/// //         ^^^ function reference
/// ```
///
/// Given arguments is nothing and rest parameters are `x, y, z`.
/// Helper function is generated like this:
///
/// ```fsharp
///    let sumObj0 env x y z =
///      let () = unbox env
///      add x y z
/// ```
///
/// Call-site is transformed like this:
///
/// ```fsharp
///    let env = box ()
///    (sumObj0, ()) :> (int -> int -> int -> int)
/// ```
module rec MiloneLang.EtaExpansion

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.TySystem
open MiloneLang.Typing

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private CalleeKind =
  | Fun
  | Obj

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private EtaCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): EtaCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: EtaCtx) =
  { tyCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars
      Tys = ctx.Tys }

let private freshFun (ident: Ident) arity (ty: Ty) loc (ctx: EtaCtx) =
  let serial = ctx.Serial + 1

  let tyScheme =
    let isOwned (_: Serial) = true // FIXME: is it okay?
    tyGeneralize isOwned ty

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> mapAdd serial (FunDef(ident, arity, tyScheme, loc)) }

  let refExpr = HFunExpr(serial, ty, loc)
  refExpr, serial, ctx

let private freshVar (ident: Ident) (ty: Ty) loc (ctx: EtaCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> mapAdd serial (VarDef(ident, AutoSM, ty, loc)) }

  let refExpr = HRefExpr(serial, ty, loc)
  refExpr, serial, ctx

let private listSplitAt i xs =
  List.truncate i xs, List.skip (intMin i (List.length xs)) xs

let private tyAppliedBy n ty =
  match ty with
  | AppTy (FunTyCtor, [ _; ty ]) when n > 0 -> tyAppliedBy (n - 1) ty
  | _ -> ty

/// E.g. given init = `id x` and args `x, y` then we should return `(id x) y`.
let private restCall callee args resultTy loc =
  match args with
  | [] -> callee
  | args -> hxCallClosure callee args resultTy loc

let private hxCallTo calleeKind callee args resultTy loc =
  match calleeKind, args with
  | _, [] -> callee
  | CalleeKind.Fun, args -> hxCallProc callee args resultTy loc
  | CalleeKind.Obj, args -> hxCallClosure callee args resultTy loc

let private createRestArgsAndPats callee arity argLen callLoc ctx =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ -> [], [], ctx

    | n, AppTy (FunTyCtor, [ argTy; restTy ]) ->
        let argRef, argSerial, ctx = freshVar "arg" argTy callLoc ctx
        let restArgPats, restArgs, ctx = go (n - 1) restTy ctx
        let restArgPat = HRefPat(argSerial, argTy, callLoc)
        restArgPat :: restArgPats, argRef :: restArgs, ctx

    | _ -> failwithf "Never: Type error %A" (callLoc, callee, n, restTy)

  let restTy = callee |> exprToTy |> tyAppliedBy argLen
  go (arity - argLen) restTy ctx

let private createEnvPatAndTy items callLoc ctx =
  let rec go items ctx =
    match items with
    | [] -> [], [], [], ctx

    | item :: items ->
        let itemTy, itemLoc = exprExtract item
        let itemRef, itemSerial, ctx = freshVar "arg" itemTy itemLoc ctx
        let itemPat = HRefPat(itemSerial, itemTy, itemLoc)
        let itemPats, argTys, argRefs, ctx = go items ctx
        itemPat :: itemPats, itemTy :: argTys, itemRef :: argRefs, ctx

  let itemPats, itemTys, itemRefs, ctx = go items ctx
  let envTy = tyTuple itemTys
  let envPat = HTuplePat(itemPats, envTy, callLoc)
  envPat, envTy, itemRefs, ctx

let private createEnvDeconstructLetExpr envPat envTy envArgRef next callLoc =
  let unboxRef =
    HPrimExpr(HPrim.Unbox, tyFun tyObj envTy, callLoc)

  let unboxExpr =
    hxCallProc unboxRef [ envArgRef ] envTy callLoc

  HLetValExpr(PrivateVis, envPat, unboxExpr, next, exprToTy next, callLoc)

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest parameters
/// and calls the partial-applied callee with full arguments.
let private createUnderlyingFunDef funTy arity envPat envTy forwardCall restArgPats callLoc ctx =
  let envArgRef, envArgSerial, ctx = freshVar "env" tyObj callLoc ctx
  let envArgPat = HRefPat(envArgSerial, tyObj, callLoc)

  let underlyingFunTy = tyFun envTy funTy

  let _, funSerial, ctx =
    freshFun "fun" arity underlyingFunTy callLoc ctx

  let argPats = envArgPat :: restArgPats

  let body =
    createEnvDeconstructLetExpr envPat envTy envArgRef forwardCall callLoc

  let funLet next =
    HLetFunExpr(funSerial, PrivateVis, false, argPats, body, next, exprToTy next, callLoc)

  let funRef =
    HFunExpr(funSerial, underlyingFunTy, callLoc)

  funLet, funRef, ctx

let private createEnvBoxExpr args envTy callLoc =
  let tuple = hxTuple args callLoc

  let boxRef =
    HPrimExpr(HPrim.Box, tyFun envTy tyObj, callLoc)

  hxCallProc boxRef [ tuple ] tyObj callLoc

/// In the case the callee is a function.
let private resolvePartialAppFun callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy
  let envItems = args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, envRefs, ctx = createEnvPatAndTy envItems callLoc ctx
  let forwardArgs = List.append envRefs restArgs

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
let private resolvePartialAppObj callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  // Introduce a variable for memoization.
  let calleeRef, calleeLet, ctx =
    let calleeRef, calleeSerial, ctx = freshVar "callee" funTy callLoc ctx

    let calleePat = HRefPat(calleeSerial, funTy, callLoc)

    let calleeLet next =
      HLetValExpr(PrivateVis, calleePat, callee, next, exprToTy next, callLoc)

    calleeRef, calleeLet, ctx

  let envItems = calleeRef :: args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, envRefs, ctx = createEnvPatAndTy envItems callLoc ctx

  let calleeRef, forwardArgs =
    match List.append envRefs restArgs with
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

let private resolvePartialApp calleeKind callee arity args argLen callLoc ctx =
  assert (argLen < arity)
  match calleeKind with
  | CalleeKind.Fun -> resolvePartialAppFun callee arity args argLen callLoc ctx
  | CalleeKind.Obj -> resolvePartialAppObj callee arity args argLen callLoc ctx

// -----------------------------------------------
// Featured transformations
// -----------------------------------------------

let private doExpandCall calleeKind callee arity calleeLoc args resultTy callLoc ctx =
  let argLen = List.length args
  if argLen < arity then
    resolvePartialApp calleeKind callee arity args argLen callLoc ctx
  else
    let callArgs, restArgs = listSplitAt arity args
    let callResultTy = tyAppliedBy arity (exprToTy callee)

    let callExpr =
      hxCallTo calleeKind callee callArgs callResultTy calleeLoc

    hxCallTo CalleeKind.Obj callExpr restArgs resultTy callLoc, ctx

let private expandCallExpr callee args resultTy loc (ctx: EtaCtx) =
  match callee, args with
  | HFunExpr (serial, _, calleeLoc), _ ->
      let arity =
        match ctx.Vars |> mapFind serial with
        | FunDef (_, arity, _, _) -> arity
        | _ -> failwith "NEVER"

      let args, ctx = (args, ctx) |> stMap exExpr
      doExpandCall CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx

  | HVariantExpr (_, variantTy, calleeLoc), _ ->
      assert (tyIsFun variantTy)
      let arity = 1
      let args, ctx = (args, ctx) |> stMap exExpr
      doExpandCall CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx

  | HPrimExpr (prim, primTy, calleeLoc), _ ->
      let arity = prim |> primToArity primTy
      let args, ctx = (args, ctx) |> stMap exExpr
      doExpandCall CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx

  | _, args ->
      let calleeTy, calleeLoc = exprExtract callee
      let callee, ctx = (callee, ctx) |> exExpr
      let args, ctx = (args, ctx) |> stMap exExpr
      let arity = tyToArity calleeTy // FIXME: maybe wrong
      doExpandCall CalleeKind.Obj callee arity calleeLoc args resultTy loc ctx

let private exFunName expr serial _refTy calleeLoc (ctx: EtaCtx) =
  match ctx.Vars |> mapTryFind serial with
  | Some (FunDef (_, arity, _, _)) -> resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx
  | def -> failwithf "NEVER: %A" (expr, def)

// This is used only when variant is not applied syntactically.
// Value-carrying variant is transformed as partial app.
let private exVariantName expr variantTy loc (ctx: EtaCtx) =
  if tyIsFun variantTy then
    let arity = 1
    resolvePartialApp CalleeKind.Fun expr arity [] 0 loc ctx
  else
    expr, ctx

let private exPrimExpr expr prim primTy calleeLoc (ctx: EtaCtx) =
  let arity = prim |> primToArity primTy
  if arity = 0
  then expr, ctx
  else resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx

let private exInfExpr expr infOp args ty loc ctx =
  match infOp with
  | InfOp.App ->
      /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
      let rec roll acc callee =
        match callee with
        | HInfExpr (InfOp.App, [ callee; arg ], _, _) -> roll (arg :: acc) callee
        | _ -> callee, acc

      let callee, args = roll [] expr
      expandCallExpr callee args ty loc ctx

  | _ ->
      let args, ctx = (args, ctx) |> stMap exExpr
      HInfExpr(infOp, args, ty, loc), ctx

let private exLetFunExpr callee vis isMainFun argPats body next ty loc ctx =
  let body, ctx = (body, ctx) |> exExpr
  let next, ctx = (next, ctx) |> exExpr
  HLetFunExpr(callee, vis, isMainFun, argPats, body, next, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private exExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HRefExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HErrorExpr _ -> expr, ctx

  | HFunExpr (serial, refTy, calleeLoc) -> exFunName expr serial refTy calleeLoc ctx
  | HVariantExpr (_, ty, loc) -> exVariantName expr ty loc ctx
  | HPrimExpr (prim, primTy, calleeLoc) -> exPrimExpr expr prim primTy calleeLoc ctx

  | HMatchExpr (target, arms, ty, loc) ->
      let target, ctx = (target, ctx) |> exExpr

      let arms, ctx =
        (arms, ctx)
        |> stMap (fun ((pat, guard, body), ctx) ->
             let guard, ctx = (guard, ctx) |> exExpr
             let body, ctx = (body, ctx) |> exExpr
             (pat, guard, body), ctx)

      HMatchExpr(target, arms, ty, loc), ctx

  | HInfExpr (infOp, args, ty, loc) -> exInfExpr expr infOp args ty loc ctx

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let init, ctx = (init, ctx) |> exExpr
      let next, ctx = (next, ctx) |> exExpr
      HLetValExpr(vis, pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      exLetFunExpr callee vis isMainFun args body next ty loc ctx

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or TyElaborating"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in TyElaboration"
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let etaExpansion (expr, tyCtx: TyCtx) =
  let etaCtx = ofTyCtx tyCtx
  let expr, etaCtx = (expr, etaCtx) |> exExpr
  let tyCtx = etaCtx |> toTyCtx tyCtx
  expr, tyCtx
