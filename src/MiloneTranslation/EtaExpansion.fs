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
module rec MiloneTranslation.EtaExpansion

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module Int = MiloneStd.StdInt

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private CalleeKind =
  | Fun
  | Obj

let private listSplitAt i xs =
  List.truncate i xs, listSkip (Int.min i (List.length xs)) xs

let private tyToArity ty =
  match ty with
  | Ty (FunTk, [ _; ty ]) -> 1 + tyToArity ty
  | _ -> 0

// #tyAppliedBy
let private tyAppliedBy n ty =
  match ty with
  | Ty (FunTk, [ _; ty ]) when n > 0 -> tyAppliedBy (n - 1) ty
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

let private primToArity ty prim =
  match prim with
  | HPrim.Nil
  | HPrim.OptionNone -> 0

  | HPrim.OptionSome
  | HPrim.Not
  | HPrim.Exit
  | HPrim.Assert
  | HPrim.Box
  | HPrim.Unbox
  | HPrim.StrLength
  | HPrim.Char
  | HPrim.ToInt _
  | HPrim.ToFloat _
  | HPrim.String
  | HPrim.InRegion
  | HPrim.NativeCast -> 1

  | HPrim.Add
  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Modulo
  | HPrim.BitAnd
  | HPrim.BitOr
  | HPrim.BitXor
  | HPrim.LeftShift
  | HPrim.RightShift
  | HPrim.Equal
  | HPrim.Less
  | HPrim.Compare
  | HPrim.Cons
  | HPrim.PtrRead -> 2

  | HPrim.PtrWrite -> 3

  | HPrim.Printfn -> ty |> tyToArity

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private EtaCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx) : EtaCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: EtaCtx) =
  { tyCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars
      Funs = ctx.Funs
      Tys = ctx.Tys }

let private freshFun name arity (ty: Ty) loc (ctx: EtaCtx) =
  let funSerial = FunSerial(ctx.Serial + 1)

  let funDef: FunDef =
    let tyScheme =
      let isOwned (_: Serial) = true // FIXME: is it okay?
      tyGeneralize isOwned ty

    { Name = name
      Arity = arity
      Ty = tyScheme
      Abi = MiloneAbi
      Linkage = InternalLinkage
      ParentOpt = None
      Loc = loc }

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Funs = ctx.Funs |> TMap.add funSerial funDef }

  let funExpr = HFunExpr(funSerial, ty, [], loc) // FIXME: unimpl ty args
  funExpr, funSerial, ctx

let private freshVar name (ty: Ty) loc (ctx: EtaCtx) =
  let serial = VarSerial(ctx.Serial + 1)

  let varDef: VarDef =
    { Name = name
      IsStatic = NotStatic
      Ty = ty
      Linkage = InternalLinkage
      Loc = loc }

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> TMap.add serial varDef }

  HVarExpr(serial, ty, loc), serial, ctx

// -----------------------------------------------
// Conversion
// -----------------------------------------------

let private createRestArgsAndPats callee arity argLen callLoc ctx =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ -> [], [], ctx

    | n, Ty (FunTk, [ argTy; restTy ]) ->
      let argExpr, argSerial, ctx = freshVar "arg" argTy callLoc ctx
      let restArgPats, restArgs, ctx = go (n - 1) restTy ctx

      let restArgPat =
        HVarPat(PrivateVis, argSerial, argTy, callLoc)

      restArgPat :: restArgPats, argExpr :: restArgs, ctx

    | _ -> unreachable (callLoc, callee, n, restTy) // Type error?

  let restTy = callee |> exprToTy |> tyAppliedBy argLen
  go (arity - argLen) restTy ctx

/// args: given args to be packed as env and set to fun obj
let private createEnvPatAndTy args callLoc ctx =
  let rec go args ctx =
    match args with
    | [] -> [], [], [], ctx

    | arg :: args ->
      let argTy, argLoc = exprExtract arg
      let itemExpr, varSerial, ctx = freshVar "arg" argTy argLoc ctx

      let itemPat =
        HVarPat(PrivateVis, varSerial, argTy, argLoc)

      let itemPats, itemTys, itemExprs, ctx = go args ctx
      itemPat :: itemPats, argTy :: itemTys, itemExpr :: itemExprs, ctx

  // itemExprs: each is var expr bound to an item of unpacked env tuple.
  let itemPats, itemTys, itemExprs, ctx = go args ctx

  // envPat: pat to unpack env arg (given to underlying function).
  // envTy: type of env pat
  // envExpr: expr to be boxed and set to fun object
  let envPat, envTy, envExpr =
    match itemPats, itemTys, args with
    | [ itemPat ], [ itemTy ], [ arg ] -> itemPat, itemTy, arg

    | pats, tys, _ ->
      let envPat = hpTuple pats callLoc
      let envTy = tyTuple tys
      let envExpr = hxTuple args callLoc
      envPat, envTy, envExpr

  let boxedEnvExpr =
    let boxPrim =
      HPrimExpr(HPrim.Box, tyFun envTy tyObj, callLoc)

    hxCallProc boxPrim [ envExpr ] tyObj callLoc

  let unboxedEnvExpr envArgExpr = // envArgExpr: expr of env arg, given to underlying function
    let unboxPrim =
      HPrimExpr(HPrim.Unbox, tyFun tyObj envTy, callLoc)

    hxCallProc unboxPrim [ envArgExpr ] envTy callLoc

  envPat, envTy, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest parameters
/// and calls the partial-applied callee with full arguments.
let private createUnderlyingFunDef funTy arity envPat envTy forwardCall restArgPats unboxedEnvExpr callLoc ctx =
  let envArgExpr, envArgSerial, ctx = freshVar "env" tyObj callLoc ctx

  let envArgPat =
    HVarPat(PrivateVis, envArgSerial, tyObj, callLoc)

  let underlyingFunTy = tyFun tyObj funTy

  let _, funSerial, ctx =
    freshFun "fun" (arity + 1) underlyingFunTy callLoc ctx

  let argPats = envArgPat :: restArgPats

  let body =
    let next = forwardCall
    HLetValExpr(envPat, unboxedEnvExpr envArgExpr, next, exprToTy next, callLoc)

  let funLet next =
    HLetFunExpr(funSerial, NotRec, PrivateVis, argPats, body, next, exprToTy next, callLoc)

  let funExpr =
    HFunExpr(funSerial, underlyingFunTy, [], callLoc)

  funLet, funExpr, ctx

/// In the case the callee is a function.
let private resolvePartialAppFun callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx = createEnvPatAndTy args callLoc ctx

  let forwardExpr =
    let forwardArgs = List.append itemExprs restArgs
    hxCallProc callee forwardArgs resultTy callLoc

  let funLet, funExpr, ctx =
    let appliedTy = tyAppliedBy argLen funTy
    createUnderlyingFunDef appliedTy (arity - argLen) envPat envTy forwardExpr restArgPats unboxedEnvExpr callLoc ctx

  let funObjExpr =
    HNodeExpr(HClosureEN, [ funExpr; boxedEnvExpr ], tyAppliedBy argLen funTy, callLoc)

  let expr = funLet funObjExpr
  expr, ctx

/// In the case that the callee is a function object.
/// We need to include it to the environment.
let private resolvePartialAppObj callee arity args argLen callLoc ctx =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  // Introduce a variable for memoization.
  let calleeExpr, calleeLet, ctx =
    let calleeExpr, calleeSerial, ctx = freshVar "callee" funTy callLoc ctx

    let calleePat =
      HVarPat(PrivateVis, calleeSerial, funTy, callLoc)

    let calleeLet next =
      HLetValExpr(calleePat, callee, next, exprToTy next, callLoc)

    calleeExpr, calleeLet, ctx

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  // callee itself is also a kind of hidden arg to be packed into env obj.
  let envPat, envTy, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx =
    createEnvPatAndTy (calleeExpr :: args) callLoc ctx

  let calleeExpr, forwardArgs =
    match List.append itemExprs restArgs with
    | calleeExpr :: forwardArgs -> calleeExpr, forwardArgs
    | _ -> unreachable ()

  let forwardExpr =
    hxCallClosure calleeExpr forwardArgs resultTy callLoc

  let funLet, funExpr, ctx =
    let appliedTy = tyAppliedBy argLen funTy

    createUnderlyingFunDef appliedTy (arity - argLen) envPat envTy forwardExpr restArgPats unboxedEnvExpr callLoc ctx

  let closureExpr =
    HNodeExpr(HClosureEN, [ funExpr; boxedEnvExpr ], tyAppliedBy argLen funTy, callLoc)

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
  | HFunExpr (funSerial, _, _, calleeLoc), _ ->
    let arity = (ctx.Funs |> mapFind funSerial).Arity
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

let private exFunName expr funSerial calleeLoc (ctx: EtaCtx) =
  let arity = (ctx.Funs |> mapFind funSerial).Arity
  resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx

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

  if arity = 0 then
    expr, ctx
  else
    resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx

let private exInfExpr expr kind args ty loc ctx =
  match kind with
  | HAppEN ->
    /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
    let rec roll acc callee =
      match callee with
      | HNodeExpr (HAppEN, [ callee; arg ], _, _) -> roll (arg :: acc) callee
      | _ -> callee, acc

    let callee, args = roll [] expr
    expandCallExpr callee args ty loc ctx

  | _ ->
    let args, ctx = (args, ctx) |> stMap exExpr
    HNodeExpr(kind, args, ty, loc), ctx

let private exLetFunExpr callee isRec vis argPats body next ty loc ctx =
  let body, ctx = (body, ctx) |> exExpr
  let next, ctx = (next, ctx) |> exExpr
  HLetFunExpr(callee, isRec, vis, argPats, body, next, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private exExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HVarExpr _ -> expr, ctx

  | HFunExpr (serial, _, _, calleeLoc) -> exFunName expr serial calleeLoc ctx
  | HVariantExpr (_, ty, loc) -> exVariantName expr ty loc ctx
  | HPrimExpr (prim, primTy, calleeLoc) -> exPrimExpr expr prim primTy calleeLoc ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = (cond, ctx) |> exExpr

    let arms, ctx =
      (arms, ctx)
      |> stMap
           (fun ((pat, guard, body), ctx) ->
             let guard, ctx = (guard, ctx) |> exExpr
             let body, ctx = (body, ctx) |> exExpr
             (pat, guard, body), ctx)

    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) -> exInfExpr expr kind args ty loc ctx

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap exExpr
    let last, ctx = (last, ctx) |> exExpr
    HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
    let init, ctx = (init, ctx) |> exExpr
    let next, ctx = (next, ctx) |> exExpr
    HLetValExpr(pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    exLetFunExpr callee isRec vis args body next ty loc ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let etaExpansion (expr, tyCtx: TyCtx) =
  let etaCtx = ofTyCtx tyCtx
  let expr, etaCtx = (expr, etaCtx) |> exExpr
  let tyCtx = etaCtx |> toTyCtx tyCtx
  expr, tyCtx
