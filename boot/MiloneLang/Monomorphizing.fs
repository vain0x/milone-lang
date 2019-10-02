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

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

[<RequireQualifiedAccess>]
type Mode =
  | Monify
  | RemoveGenerics

type MonoCtx =
  {
    Serial: Serial
    Logs: (Log * Loc) list

    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>
    TyDepths: AssocMap<TySerial, LetDepth>

    /// Map from
    /// - generic function serial
    ///
    /// to:
    /// - found use-site types
    GenericFunUseSiteTys: AssocMap<FunSerial, Ty list>

    /// Map from pairs:
    /// - generic function's serial
    /// - monomorphic type
    ///
    /// to:
    /// - monomorphized function's serial
    GenericFunMonoSerials: AssocMap<FunSerial * Ty, FunSerial>

    Mode: Mode
    SomethingHappened: bool
    InfiniteLoopDetector: int
  }

let monoCtxToTyCtx (monoCtx: MonoCtx): TyContext =
  TyContext (
    monoCtx.Serial,
    monoCtx.Tys,
    monoCtx.TyDepths
  )

let monoCtxWithTyCtx (tyCtx: TyContext) logAcc (monoCtx: MonoCtx) =
  { monoCtx with
      Serial = tyCtx |> tyContextGetSerial
      Logs = logAcc
      Tys = tyCtx |> tyContextGetTys
      TyDepths = tyCtx |> tyContextGetTyDepths
  }

let monoCtxBindTy (monoCtx: MonoCtx) tySerial ty loc: MonoCtx =
  monoCtx |> monoCtxWithTyCtx (typingBind (monoCtxToTyCtx monoCtx) tySerial ty loc) monoCtx.Logs

let monoCtxSubstTy (monoCtx: MonoCtx) ty: Ty =
  typingSubst (monoCtxToTyCtx monoCtx) ty

let monoCtxUnifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let tyCtx = monoCtxToTyCtx monoCtx
  let logAcc, tyCtx = typingUnify monoCtx.Logs tyCtx lTy rTy loc
  monoCtx |> monoCtxWithTyCtx tyCtx logAcc

let monoCtxSubstTyExpr ctx expr =
  let subst ty = monoCtxSubstTy ctx ty
  exprMap subst id expr

let monoCtxSubstPatTy ctx pat =
  let subst ty = monoCtxSubstTy ctx ty
  patMap subst id pat

let monoCtxSubstPatsTy ctx pats =
  listMap (monoCtxSubstPatTy ctx) pats

let monoCtxGetMode (ctx: MonoCtx) =
  ctx.Mode

let monoCtxMarkSomethingHappened (ctx: MonoCtx) =
  { ctx with SomethingHappened = true }

let monoCtxFindVarDef (ctx: MonoCtx) serial =
  ctx.Vars |> mapFind serial

let monoCtxFindGenericFunDef (ctx: MonoCtx) serial =
  match ctx.Vars |> mapFind serial with
  | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
    None
  | VarDef.Fun (ident, arity, TyScheme.ForAll (_, funTy), loc) ->
    Some (ident, arity, funTy, loc)
  | _ ->
    None

let monoCtxGetGenericFunIdent funSerial (ctx: MonoCtx) =
  match monoCtxFindGenericFunDef ctx funSerial with
  | Some (ident, _, _, _) ->
    ident

  | None ->
    failwith "NEVER"

/// Generalizes all functions that has type variables.
let monoCtxForceGeneralizeFuns (ctx: MonoCtx) =
  let forceGeneralize (varSerial, varDef) =
    match varDef with
    | VarDef.Fun (ident, arity, TyScheme.ForAll (_, ty), loc) ->
      let fvs = ty |> tyCollectFreeVars
      varSerial, VarDef.Fun (ident, arity, TyScheme.ForAll (fvs, ty), loc)

    | _ ->
      varSerial, varDef

  let vars = ctx.Vars |> mapToList |> listMap forceGeneralize |> mapOfList (intHash, intCmp)
  { ctx with Vars = vars }

let monoCtxAddMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity useSiteTy loc =
  assert (monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy |> Option.isNone)

  let varDef =
    let monoTyScheme = TyScheme.ForAll ([], useSiteTy)
    let ident = ctx |> monoCtxGetGenericFunIdent genericFunSerial
    VarDef.Fun (ident, arity, monoTyScheme, loc)
  let monoFunSerial = ctx.Serial + 1
  let ctx =
    { ctx with
        Serial =
          ctx.Serial + 1
        Vars =
          ctx.Vars |> mapAdd monoFunSerial varDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> mapAdd (genericFunSerial, useSiteTy) monoFunSerial
    }
  let ctx = monoCtxMarkSomethingHappened ctx
  monoFunSerial, ctx

let monoCtxFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials |> mapTryFind (funSerial, useSiteTy)

let monoCtxMarkUseOfGenericFun (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic =
    useSiteTy |> tyIsMonomorphic
  let notMonomorphizedYet =
    monoCtxFindMonomorphizedFun ctx funSerial useSiteTy |> Option.isNone
  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
      | None -> []
      | Some useSiteTys -> useSiteTys
    let useSiteTys =
      useSiteTy :: useSiteTys
    let map =
      ctx.GenericFunUseSiteTys
      |> mapAdd funSerial useSiteTys
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = monoCtxMarkSomethingHappened ctx
    ctx

let monoCtxTakeMarkedGenericFunUseSiteTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
  | None
  | Some [] ->
    [], ctx
  | Some useSiteTys ->
    let map = ctx.GenericFunUseSiteTys |> mapRemove funSerial
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = monoCtxMarkSomethingHappened ctx
    useSiteTys, ctx

/// Replaces the variable serial to monomorphized function serial if possible.
/// Or marks an use of generic function if possible.
/// Does nothing if the serial is NOT a generic function.
let monoCtxProcessVarRef ctx varSerial useSiteTy =
  match monoCtxFindVarDef ctx varSerial with
  | VarDef.Var _
  | VarDef.Variant _
  | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
    varSerial, ctx

  | VarDef.Fun _ ->
    match monoCtxFindMonomorphizedFun ctx varSerial useSiteTy with
    | Some monoFunSerial ->
      monoFunSerial, ctx

    | None ->
      let ctx = monoCtxMarkUseOfGenericFun ctx varSerial useSiteTy
      varSerial, ctx

let monifyPat (pat, ctx) =
  pat, ctx

let monifyExprLetFun ctx callee isMainFun args body next ty loc =
  let genericFunSerial = callee
  let letGenericFunExpr = HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] ->
      next, ctx
    | useSiteTy :: useSiteTys ->
      match monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
      | Some _ ->
        go next arity genericFunTy useSiteTys ctx
      | None ->

      // Within the context where genericFunTy and useSiteTy are unified
      // resolve all types in args and body.
      let extendedCtx = monoCtxUnifyTy ctx genericFunTy useSiteTy loc
      let monoArgs = monoCtxSubstPatsTy extendedCtx args
      let monoBody = monoCtxSubstTyExpr extendedCtx body
      let monoFunSerial, ctx = monoCtxAddMonomorphizedFun ctx genericFunSerial arity useSiteTy loc
      let next = HExpr.LetFun (monoFunSerial, isMainFun, monoArgs, monoBody, next, ty, loc)
      go next arity genericFunTy useSiteTys ctx

  match monoCtxFindGenericFunDef ctx genericFunSerial, monoCtxGetMode ctx with
  | None, _ ->
    letGenericFunExpr, ctx
  | Some _, Mode.RemoveGenerics ->
    next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
    let useSiteTys, ctx =
      monoCtxTakeMarkedGenericFunUseSiteTys ctx genericFunSerial
    go letGenericFunExpr arity genericFunTy useSiteTys ctx

let rec monifyExpr (expr, ctx) =
  match expr with
  | HExpr.Error _
  | HExpr.TyDecl _
  | HExpr.Open _
  | HExpr.Lit _
  | HExpr.Prim _ ->
    expr, ctx

  | HExpr.Ref (varSerial, useSiteTy, loc) ->
    let varSerial, ctx = monoCtxProcessVarRef ctx varSerial useSiteTy
    HExpr.Ref (varSerial, useSiteTy, loc), ctx

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

  | HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyPat
    let body, ctx = (body, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    monifyExprLetFun ctx callee isMainFun args body next ty loc

let monify (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let monoCtx: MonoCtx =
    {
      Serial = tyCtx |> tyCtxGetSerial
      Logs = tyCtx |> tyCtxGetLogs

      Vars = tyCtx |> tyCtxGetVars
      Tys = tyCtx |> tyCtxGetTys
      TyDepths = tyCtx |> tyCtxGetTyDepths

      GenericFunUseSiteTys = mapEmpty (intHash, intCmp)
      GenericFunMonoSerials = mapEmpty (hash, compare) // FIXME: Write intTyCmp

      Mode = Mode.Monify
      SomethingHappened = true
      InfiniteLoopDetector = 0
    }

  let monoCtx = monoCtx |> monoCtxForceGeneralizeFuns

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
    tyCtx
    |> tyCtxWithSerial monoCtx.Serial
    |> tyCtxWithVars monoCtx.Vars
    |> tyCtxWithTys monoCtx.Tys

  expr, tyCtx
