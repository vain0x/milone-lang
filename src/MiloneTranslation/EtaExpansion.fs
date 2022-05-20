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
open Std.StdError
open Std.StdMap
open MiloneTranslation.Hir
open MiloneTranslationTypes.HirTypes

module Int = Std.StdInt
module S = Std.StdString

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
  | HPrim.NullPtr -> 0

  | HPrim.Not
  | HPrim.Exit
  | HPrim.Assert
  | HPrim.Box
  | HPrim.Unbox
  | HPrim.StringLength
  | HPrim.Char
  | HPrim.ToInt _
  | HPrim.ToFloat _
  | HPrim.String
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
  | HPrim.PtrDistance -> 2

  | HPrim.Printfn -> ty |> tyToArity

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private EtaCtx =
  { Serial: Serial
    StaticVars: VarMap
    Vars: VarMap
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    ParentFun: string list }

let private ofHirCtx (hirCtx: HirCtx) : EtaCtx =
  { Serial = hirCtx.Serial
    StaticVars = hirCtx.StaticVars
    Vars = emptyVars
    Funs = hirCtx.Funs
    Variants = hirCtx.Variants
    ParentFun = [] }

let private toHirCtx (hirCtx: HirCtx) (ctx: EtaCtx) =
  { hirCtx with
      Serial = ctx.Serial
      Funs = ctx.Funs }

let private freshFun name arity (ty: Ty) loc (ctx: EtaCtx) =
  let funSerial = FunSerial(ctx.Serial + 1)

  let funDef: FunDef =
    let tyScheme =
      let isOwned (_: Serial) = true // unsure it's okay or not
      tyGeneralize isOwned ty

    { Name = name
      Arity = arity
      Ty = tyScheme
      Abi = MiloneAbi
      Linkage = InternalLinkage
      Prefix = [ "eta" + string arity ]
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

let private createRestArgsAndPats ctx callee arity argLen callLoc =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ -> [], [], ctx

    | n, Ty (FunTk, [ argTy; restTy ]) ->
      let argExpr, argSerial, ctx = freshVar "arg" argTy callLoc ctx
      let restArgPats, restArgs, ctx = go (n - 1) restTy ctx

      let restArgPat = HVarPat(argSerial, argTy, callLoc)

      restArgPat :: restArgPats, argExpr :: restArgs, ctx

    | _ -> unreachable (callLoc, callee, n, restTy) // Type error?

  let restTy = callee |> exprToTy |> tyAppliedBy argLen
  go (arity - argLen) restTy ctx

/// args: given args to be packed as env and set to fun obj
let private createEnvPatAndTy ctx args callLoc =
  let rec go args ctx =
    match args with
    | [] -> [], [], [], ctx

    | arg :: args ->
      let argTy, argLoc = exprExtract arg
      let itemExpr, varSerial, ctx = freshVar "arg" argTy argLoc ctx

      let itemPat = HVarPat(varSerial, argTy, argLoc)

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

  envPat, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest parameters
/// and calls the partial-applied callee with full arguments.
let private createUnderlyingFunDef ctx name funTy arity envPat forwardCall restArgPats unboxedEnvExpr callLoc =
  let envArgExpr, envArgSerial, ctx = freshVar "env" tyObj callLoc ctx

  let envArgPat = HVarPat(envArgSerial, tyObj, callLoc)

  let underlyingFunTy = tyFun tyObj funTy

  let _, funSerial, ctx =
    freshFun name (arity + 1) underlyingFunTy callLoc ctx

  let argPats = envArgPat :: restArgPats

  let body =
    hxLetIn (HLetValStmt(envPat, unboxedEnvExpr envArgExpr, callLoc)) forwardCall

  let funLet next =
    hxLetIn (HLetFunStmt(funSerial, argPats, body, callLoc)) next

  let funExpr =
    HFunExpr(funSerial, underlyingFunTy, [], callLoc)

  funLet, funExpr, ctx

/// In the case the callee is a function.
let private resolvePartialAppFun ctx name callee arity args argLen callLoc =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats ctx callee arity argLen callLoc

  let envPat, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx = createEnvPatAndTy ctx args callLoc

  let forwardExpr =
    let forwardArgs = List.append itemExprs restArgs
    hxCallProc callee forwardArgs resultTy callLoc

  let funLet, funExpr, ctx =
    let appliedTy = tyAppliedBy argLen funTy

    createUnderlyingFunDef ctx name appliedTy (arity - argLen) envPat forwardExpr restArgPats unboxedEnvExpr callLoc

  let funObjExpr =
    HNodeExpr(HClosureEN, [ funExpr; boxedEnvExpr ], tyAppliedBy argLen funTy, callLoc)

  let expr = funLet funObjExpr
  expr, ctx

/// In the case that the callee is a function object.
/// We need to include it to the environment.
let private resolvePartialAppObj ctx name callee arity args argLen callLoc =
  let funTy = exprToTy callee
  let resultTy = tyAppliedBy arity funTy

  // Introduce a variable for memoization.
  let calleeExpr, calleeLet, ctx =
    let calleeExpr, calleeSerial, ctx = freshVar "callee" funTy callLoc ctx

    let calleePat = HVarPat(calleeSerial, funTy, callLoc)

    let calleeLet next =
      hxLetIn (HLetValStmt(calleePat, callee, callLoc)) next

    calleeExpr, calleeLet, ctx

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats ctx callee arity argLen callLoc

  // callee itself is also a kind of hidden arg to be packed into env obj.
  let envPat, itemExprs, boxedEnvExpr, unboxedEnvExpr, ctx =
    createEnvPatAndTy ctx (calleeExpr :: args) callLoc

  let calleeExpr, forwardArgs =
    match List.append itemExprs restArgs with
    | calleeExpr :: forwardArgs -> calleeExpr, forwardArgs
    | _ -> unreachable ()

  let forwardExpr =
    hxCallClosure calleeExpr forwardArgs resultTy callLoc

  let funLet, funExpr, ctx =
    let appliedTy = tyAppliedBy argLen funTy

    createUnderlyingFunDef ctx name appliedTy (arity - argLen) envPat forwardExpr restArgPats unboxedEnvExpr callLoc

  let closureExpr =
    HNodeExpr(HClosureEN, [ funExpr; boxedEnvExpr ], tyAppliedBy argLen funTy, callLoc)

  let expr = calleeLet (funLet closureExpr)
  expr, ctx

let private resolvePartialApp ctx name calleeKind callee arity args argLen callLoc =
  assert (argLen < arity)

  match calleeKind with
  | CalleeKind.Fun -> resolvePartialAppFun ctx name callee arity args argLen callLoc
  | CalleeKind.Obj -> resolvePartialAppObj ctx name callee arity args argLen callLoc

// -----------------------------------------------
// Featured transformations
// -----------------------------------------------

let private doExpandCall ctx name calleeKind callee arity calleeLoc args resultTy callLoc =
  let argLen = List.length args

  if argLen < arity then
    resolvePartialApp ctx name calleeKind callee arity args argLen callLoc
  else
    let callArgs, restArgs = listSplitAt arity args
    let callResultTy = tyAppliedBy arity (exprToTy callee)

    let callExpr =
      hxCallTo calleeKind callee callArgs callResultTy calleeLoc

    hxCallTo CalleeKind.Obj callExpr restArgs resultTy callLoc, ctx

let private expandCallExpr (ctx: EtaCtx) callee args resultTy loc =
  match callee, args with
  | HFunExpr (funSerial, _, _, calleeLoc), _ ->
    let funDef = ctx.Funs |> mapFind funSerial
    let arity = funDef.Arity

    let name =
      (ctx.ParentFun |> List.rev |> S.concat "_")
      + "_"
      + funDef.Name

    let args, ctx = args |> List.mapFold exExpr ctx
    doExpandCall ctx name CalleeKind.Fun callee arity calleeLoc args resultTy loc

  | HVariantExpr (variantSerial, variantTy, calleeLoc), _ ->
    assert (tyIsFun variantTy)

    let name =
      (ctx.Variants |> mapFind variantSerial).Name

    let arity = 1
    let args, ctx = args |> List.mapFold exExpr ctx
    doExpandCall ctx name CalleeKind.Fun callee arity calleeLoc args resultTy loc

  | HPrimExpr (prim, primTy, calleeLoc), _ ->
    // FIXME: prim to name
    let arity = prim |> primToArity primTy
    let args, ctx = args |> List.mapFold exExpr ctx
    doExpandCall ctx "prim" CalleeKind.Fun callee arity calleeLoc args resultTy loc

  | _, args ->
    let calleeTy, calleeLoc = exprExtract callee
    let callee, ctx = callee |> exExpr ctx
    let args, ctx = args |> List.mapFold exExpr ctx
    let arity = tyToArity calleeTy // unsure it's okay or not
    doExpandCall ctx "obj" CalleeKind.Obj callee arity calleeLoc args resultTy loc

let private exFunName (ctx: EtaCtx) expr funSerial calleeLoc =
  let funDef = ctx.Funs |> mapFind funSerial

  let name =
    (ctx.ParentFun |> List.rev |> S.concat "_")
    + "_"
    + funDef.Name

  let arity = funDef.Arity
  resolvePartialApp ctx name CalleeKind.Fun expr arity [] 0 calleeLoc

// This is used only when variant is not applied syntactically.
// Value-carrying variant is transformed as partial app.
let private exVariantName (ctx: EtaCtx) expr variantSerial variantTy loc =
  if tyIsFun variantTy then
    let name =
      (ctx.Variants |> mapFind variantSerial).Name

    let arity = 1
    resolvePartialApp ctx name CalleeKind.Fun expr arity [] 0 loc
  else
    expr, ctx

let private exPrimExpr (ctx: EtaCtx) expr prim primTy calleeLoc =
  let arity = prim |> primToArity primTy

  if arity = 0 then
    expr, ctx
  else
    resolvePartialApp ctx "prim" CalleeKind.Fun expr arity [] 0 calleeLoc

let private exInfExpr ctx expr kind args ty loc =
  match kind with
  | HAppEN ->
    /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
    let rec roll acc callee =
      match callee with
      | HNodeExpr (HAppEN, [ callee; arg ], _, _) -> roll (arg :: acc) callee
      | _ -> callee, acc

    let callee, args = roll [] expr
    expandCallExpr ctx callee args ty loc

  | _ ->
    let args, ctx = args |> List.mapFold exExpr ctx
    HNodeExpr(kind, args, ty, loc), ctx

let private exLetFunStmt (ctx: EtaCtx) stmt =
  let callee, argPats, body, loc =
    match stmt with
    | HLetFunStmt (callee, argPats, body, loc) -> callee, argPats, body, loc
    | _ -> unreachable ()

  let body, ctx =
    let name = (ctx.Funs |> mapFind callee).Name

    let parent, ctx =
      ctx.ParentFun, { ctx with ParentFun = name :: ctx.ParentFun }

    let body, ctx = body |> exExpr ctx
    let ctx = { ctx with ParentFun = parent }
    body, ctx

  HLetFunStmt(callee, argPats, body, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private exExpr ctx expr : HExpr * EtaCtx =
  match expr with
  | HLitExpr _
  | HVarExpr _ -> expr, ctx

  | HFunExpr (funSerial, _, _, calleeLoc) -> exFunName ctx expr funSerial calleeLoc
  | HVariantExpr (variantSerial, ty, loc) -> exVariantName ctx expr variantSerial ty loc
  | HPrimExpr (prim, primTy, calleeLoc) -> exPrimExpr ctx expr prim primTy calleeLoc

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = cond |> exExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guard, body) ->
             let guard, ctx = guard |> exExpr ctx
             let body, ctx = body |> exExpr ctx
             (pat, guard, body), ctx)
           ctx

    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) -> exInfExpr ctx expr kind args ty loc

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = stmts |> List.mapFold exStmt ctx
    let last, ctx = last |> exExpr ctx
    HBlockExpr(stmts, last), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private exStmt ctx stmt : HStmt * EtaCtx =
  match stmt with
  | HExprStmt expr ->
    let expr, ctx = expr |> exExpr ctx
    HExprStmt expr, ctx

  | HLetValStmt (pat, init, loc) ->
    let init, ctx = init |> exExpr ctx
    HLetValStmt(pat, init, loc), ctx

  | HLetFunStmt _ -> exLetFunStmt ctx stmt

  | HNativeDeclStmt _ -> unreachable () // Generated in Hoist.

let private exModule (ctx: EtaCtx) (m: HModule) =
  let ctx = { ctx with Vars = m.Vars }
  let stmts, ctx = m.Stmts |> List.mapFold exStmt ctx

  let m =
    { m with
        Vars = ctx.Vars
        Stmts = stmts }

  m, ctx

let etaExpansion (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let etaCtx = ofHirCtx hirCtx
  let modules, etaCtx = modules |> List.mapFold exModule etaCtx
  let hirCtx = etaCtx |> toHirCtx hirCtx
  modules, hirCtx
