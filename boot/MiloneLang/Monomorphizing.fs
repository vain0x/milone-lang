/// Resolves polymorphic functions.
///
/// ## Monomorphization
///
/// **Monomorphization** refers to a kind of code conversion
/// to eliminate use of generic types and functions from program.
///
/// We need this stage because the target language (C language)
/// doesn't support generics.
///
/// ## Glossary
///
/// Types and functions are *monomorphic* if and only if
/// they have no type parameters.
///
/// ### Example
///
/// The code below contains use of generic type `'a * 'b`
/// and two use of generic function `flip`.
///
/// ```fsharp
///   let flip (x, y) = (y, x)
///   (1, "one") |> flip |> flip
/// ```
///
/// The monomorphization converts it to the code below:
///
/// ```fsharp
///   let flipIntStringPair ((x, y): int * string): string * int = (y, x)
///   let flipStringIntPair ((x, y): string * int): int * string = (y, x)
///   (1, "one") |> flipIntStringPair |> flipStringIntPair
/// ```
///
/// In short, this conversion *clones* generic definitions
/// for each combination of type parameters in use-site
/// with type parameters replaced with such monomorphic types.
///
/// ### Algorithm
///
/// Repeat the following while something happens:
///
/// 1. For each reference expression to generic function `f`,
///    if the use-site type `t` is monomorphic,
///    replace with the monomorphized instance of (`f`, `t`) if exists;
///    or mark the pair (`f`, `t`) for later otherwise.
/// 2. For each definition expression of generic function `f`,
///    for each marked pair (`f`, `t`),
///    clone the definition and unify the function type with `t`.
///    The cloned function is referred to as monomorphized instance of (`f`, `t`).
///
/// NOTE: The algorithm seems inefficient and the finiteness is unproven.
module rec MiloneLang.Monomorphizing

open MiloneLang
open MiloneLang.Types
open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type Mode =
  | Monify
  | RemoveGenerics

type MonoCtx =
  {
    Serial: Serial
    Logs: (Log * Loc) list

    Vars: Map<VarSerial, VarDef>
    Tys: Map<TySerial, TyDef>
    TyDepths: Map<TySerial, LetDepth>

    /// Map from
    /// - generic function serial
    ///
    /// to:
    /// - found use-site types
    GenericFunUseSiteTys: Map<FunSerial, Ty list>

    /// Map from pairs:
    /// - generic function's serial
    /// - monomorphic type
    ///
    /// to:
    /// - monomorphized function's serial
    GenericFunMonoSerials: Map<FunSerial * Ty, FunSerial>

    Mode: Mode
    SomethingHappened: bool
    InfiniteLoopDetector: int
  }

let ctxToTyCtx (monoCtx: MonoCtx): TyContext =
  {
    Serial = monoCtx.Serial
    Tys = monoCtx.Tys
    TyDepths = monoCtx.TyDepths
  }

let ctxWithTyCtx (tyCtx: TyContext) logAcc (monoCtx: MonoCtx) =
  { monoCtx with
      Serial = tyCtx.Serial
      Logs = logAcc
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths
  }

let bindTy (monoCtx: MonoCtx) tySerial ty loc: MonoCtx =
  monoCtx |> ctxWithTyCtx (typingBind (ctxToTyCtx monoCtx) tySerial ty loc) monoCtx.Logs

let substTy (monoCtx: MonoCtx) ty: Ty =
  typingSubst (ctxToTyCtx monoCtx) ty

let unifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let tyCtx = ctxToTyCtx monoCtx
  let logAcc, tyCtx = typingUnify monoCtx.Logs tyCtx lTy rTy loc
  monoCtx |> ctxWithTyCtx tyCtx logAcc

let substTyExpr ctx expr =
  let subst ty = substTy ctx ty
  exprMap subst id expr

let substTyPat ctx pat =
  let subst ty = substTy ctx ty
  patMap subst id pat

let substTyPats ctx pats =
  List.map (substTyPat ctx) pats

let ctxGetMode (ctx: MonoCtx) =
  ctx.Mode

let ctxMarkSomethingHappened (ctx: MonoCtx) =
  { ctx with SomethingHappened = true }

let ctxFindVarDef (ctx: MonoCtx) serial =
  ctx.Vars |> Map.find serial

let ctxFindGenericFunDef (ctx: MonoCtx) serial =
  match ctx.Vars |> Map.find serial with
  | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
    None
  | VarDef.Fun (ident, arity, TyScheme.ForAll (_, funTy), loc) ->
    Some (ident, arity, funTy, loc)
  | _ ->
    None

/// Generalizes all functions that has type variables.
let ctxForceGeneralizeFuns (ctx: MonoCtx) =
  let forceGeneralize (varSerial, varDef) =
    match varDef with
    | VarDef.Fun (ident, arity, TyScheme.ForAll (_, ty), loc) ->
      let fvs = ty |> tyCollectFreeVars
      varSerial, VarDef.Fun (ident, arity, TyScheme.ForAll (fvs, ty), loc)

    | _ ->
      varSerial, varDef

  let vars = ctx.Vars |> Map.toList |> List.map forceGeneralize |> Map.ofList
  { ctx with Vars = vars }

let ctxAddMonomorphizedFun (ctx: MonoCtx) genericFunSerial ident arity useSiteTy loc =
  assert (ctxFindMonomorphizedFun ctx genericFunSerial useSiteTy |> Option.isNone)

  let monoTyScheme = TyScheme.ForAll ([], useSiteTy)
  let varDef = VarDef.Fun (ident, arity, monoTyScheme, loc)
  let monoFunSerial = ctx.Serial + 1
  let ctx =
    { ctx with
        Serial =
          ctx.Serial + 1
        Vars =
          ctx.Vars |> Map.add monoFunSerial varDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> Map.add (genericFunSerial, useSiteTy) monoFunSerial
    }
  let ctx = ctxMarkSomethingHappened ctx
  monoFunSerial, ctx

let ctxFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials |> Map.tryFind (funSerial, useSiteTy)

let ctxMarkUseOfGenericFun (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic =
    useSiteTy |> tyIsMonomorphic
  let notMonomorphizedYet =
    ctxFindMonomorphizedFun ctx funSerial useSiteTy |> Option.isNone
  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      match ctx.GenericFunUseSiteTys |> Map.tryFind funSerial with
      | None -> []
      | Some useSiteTys -> useSiteTys
    let useSiteTys =
      useSiteTy :: useSiteTys
    let map =
      ctx.GenericFunUseSiteTys
      |> Map.add funSerial useSiteTys
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = ctxMarkSomethingHappened ctx
    ctx

let ctxTakeMarkedGenericFunUseSiteTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> Map.tryFind funSerial with
  | None
  | Some [] ->
    [], ctx
  | Some useSiteTys ->
    let map = ctx.GenericFunUseSiteTys |> Map.remove funSerial
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = ctxMarkSomethingHappened ctx
    useSiteTys, ctx

/// Replaces the variable serial to monomorphized function serial if possible.
/// Or marks an use of generic function if possible.
/// Does nothing if the serial is NOT a generic function.
let ctxProcessVarRef ctx varSerial useSiteTy =
  match ctxFindVarDef ctx varSerial with
  | VarDef.Var _
  | VarDef.Variant _
  | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
    varSerial, ctx

  | VarDef.Fun _ ->
    match ctxFindMonomorphizedFun ctx varSerial useSiteTy with
    | Some monoFunSerial ->
      monoFunSerial, ctx

    | None ->
      let ctx = ctxMarkUseOfGenericFun ctx varSerial useSiteTy
      varSerial, ctx

let monifyPat (pat, ctx) =
  pat, ctx

let monifyExprLetFun ctx ident callee args body next ty loc =
  let genericFunSerial = callee
  let letGenericFunExpr = HExpr.LetFun (ident, callee, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] ->
      next, ctx
    | useSiteTy :: useSiteTys ->
      match ctxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
      | Some _ ->
        go next arity genericFunTy useSiteTys ctx
      | None ->

      // Within the context where genericFunTy and useSiteTy are unified
      // resolve all types in args and body.
      let extendedCtx = unifyTy ctx genericFunTy useSiteTy loc
      let monoArgs = substTyPats extendedCtx args
      let monoBody = substTyExpr extendedCtx body
      let monoFunSerial, ctx = ctxAddMonomorphizedFun ctx genericFunSerial ident arity useSiteTy loc
      let next = HExpr.LetFun (ident, monoFunSerial, monoArgs, monoBody, next, ty, loc)
      go next arity genericFunTy useSiteTys ctx

  match ctxFindGenericFunDef ctx genericFunSerial, ctxGetMode ctx with
  | None, _ ->
    letGenericFunExpr, ctx
  | Some _, Mode.RemoveGenerics ->
    next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
    let useSiteTys, ctx =
      ctxTakeMarkedGenericFunUseSiteTys ctx genericFunSerial
    go letGenericFunExpr arity genericFunTy useSiteTys ctx

let rec monifyExpr (expr, ctx) =
  match expr with
  | HExpr.Error _
  | HExpr.TyDef _
  | HExpr.Open _
  | HExpr.Lit _
  | HExpr.Prim _ ->
    expr, ctx

  | HExpr.Ref (ident, varSerial, useSiteTy, loc) ->
    let varSerial, ctx = ctxProcessVarRef ctx varSerial useSiteTy
    HExpr.Ref (ident, varSerial, useSiteTy, loc), ctx

  | HExpr.Match (target, arms, ty, loc) ->
    let target, ctx = (target, ctx) |> monifyExpr
    let arms, ctx = (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
      let pat, ctx = (pat, ctx) |> monifyPat
      let guard, ctx = (guard, ctx) |> monifyExpr
      let body, ctx = (body, ctx) |> monifyExpr
      (pat, guard, body), ctx)
    HExpr.Match (target, arms, ty, loc), ctx

  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = monifyExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx

  | HExpr.Inf (infOp, args, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyExpr
    HExpr.Inf (infOp, args, ty, loc), ctx

  | HExpr.Let (pat, init, next, ty, loc) ->
    let pat, ctx = (pat, ctx) |> monifyPat
    let init, ctx = (init, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    HExpr.Let (pat, init, next, ty, loc), ctx

  | HExpr.LetFun (ident, callee, args, body, next, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyPat
    let body, ctx = (body, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    monifyExprLetFun ctx ident callee args body next ty loc

let monify (expr: HExpr, tyCtx: Typing.TyCtx): HExpr * Typing.TyCtx =
  let monoCtx: MonoCtx =
    {
      Serial = tyCtx.Serial
      Logs = tyCtx.Logs

      Vars = tyCtx.Vars
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths

      GenericFunUseSiteTys = Map.empty
      GenericFunMonoSerials = Map.empty

      Mode = Mode.Monify
      SomethingHappened = true
      InfiniteLoopDetector = 0
    }

  let monoCtx = monoCtx |> ctxForceGeneralizeFuns

  // Monomorphization.
  let rec go (expr, ctx) =
    if ctx.SomethingHappened |> not then
      expr, ctx
    else if ctx.InfiniteLoopDetector > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx =
        { ctx with
            SomethingHappened = false
            InfiniteLoopDetector = ctx.InfiniteLoopDetector + 1
        }
      (expr, ctx) |> monifyExpr |> go

  let expr, monoCtx =
    go (expr, monoCtx)

  // Remove generic function definitions.
  // WARNING: Bad kind of code reuse.
  let expr, monoCtx =
    let monoCtx = { monoCtx with Mode = Mode.RemoveGenerics }
    monifyExpr (expr, monoCtx)

  let tyCtx =
    {
      tyCtx with
        Serial = monoCtx.Serial
        Vars = monoCtx.Vars
        Tys = monoCtx.Tys
    }

  expr, tyCtx
