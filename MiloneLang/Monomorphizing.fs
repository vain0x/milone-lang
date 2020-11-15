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
open MiloneLang.TySystem
open MiloneLang.Typing

let private intTyCmp (firstValue, firstTy) (secondValue, secondTy) =
  if firstValue <> secondValue then intCmp firstValue secondValue else tyCmp firstTy secondTy

type private MonoCtx =
  { Serial: Serial
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

    Mode: MonoMode
    SomethingHappened: bool
    InfiniteLoopDetector: int }

let private monoCtxFromTyCtx (tyCtx: TyCtx): MonoCtx =
  { Serial = tyCtx.Serial
    Logs = tyCtx.Logs

    Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    TyDepths = tyCtx.TyDepths

    GenericFunUseSiteTys = mapEmpty intCmp
    GenericFunMonoSerials = mapEmpty intTyCmp
    Mode = MonoMode.Monify
    SomethingHappened = true
    InfiniteLoopDetector = 0 }

let private monoCtxToTyCtx (monoCtx: MonoCtx): TyContext =
  { Serial = monoCtx.Serial
    Tys = monoCtx.Tys
    TyDepths = monoCtx.TyDepths

    // This doesn't matter here since we don't generalize.
    LetDepth = 0 }

let private monoCtxWithTyCtx (tyCtx: TyContext) logAcc (monoCtx: MonoCtx) =
  { monoCtx with
      Serial = tyCtx.Serial
      Logs = logAcc
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths }

let private monoCtxBindTy (monoCtx: MonoCtx) tySerial ty loc: MonoCtx =
  monoCtx
  |> monoCtxWithTyCtx (typingBind (monoCtxToTyCtx monoCtx) tySerial ty loc) monoCtx.Logs

let private monoCtxSubstTy (monoCtx: MonoCtx) ty: Ty = typingSubst (monoCtxToTyCtx monoCtx) ty

let private monoCtxUnifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let tyCtx = monoCtxToTyCtx monoCtx

  let logAcc, tyCtx =
    typingUnify monoCtx.Logs tyCtx lTy rTy loc

  monoCtx |> monoCtxWithTyCtx tyCtx logAcc

let private monoCtxSubstTyExpr ctx expr =
  let subst ty = monoCtxSubstTy ctx ty
  exprMap subst id expr

let private monoCtxSubstPatTy ctx pat =
  let subst ty = monoCtxSubstTy ctx ty
  patMap subst id pat

let private monoCtxSubstPatsTy ctx pats = List.map (monoCtxSubstPatTy ctx) pats

let private monoCtxMarkSomethingHappened (ctx: MonoCtx) = { ctx with SomethingHappened = true }

let private monoCtxFindVarDef (ctx: MonoCtx) serial = ctx.Vars |> mapFind serial

let private monoCtxFindGenericFunDef (ctx: MonoCtx) serial =
  match ctx.Vars |> mapFind serial with
  | FunDef (_, _, TyScheme ([], _), _) -> None
  | FunDef (ident, arity, TyScheme (_, funTy), loc) -> Some(ident, arity, funTy, loc)
  | _ -> None

let private monoCtxGetGenericFunIdent funSerial (ctx: MonoCtx) =
  match monoCtxFindGenericFunDef ctx funSerial with
  | Some (ident, _, _, _) -> ident

  | None -> failwith "NEVER"

/// Generalizes all functions that has type variables.
let private monoCtxForceGeneralizeFuns (ctx: MonoCtx) =
  let forceGeneralize (varSerial, varDef) =
    match varDef with
    | FunDef (ident, arity, TyScheme (_, ty), loc) ->
        let fvs = ty |> tyCollectFreeVars
        varSerial, FunDef(ident, arity, TyScheme(fvs, ty), loc)

    | _ -> varSerial, varDef

  let vars =
    ctx.Vars
    |> mapToList
    |> List.map forceGeneralize
    |> mapOfList intCmp

  { ctx with Vars = vars }

let private monoCtxAddMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity useSiteTy loc =
  assert (monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy
          |> Option.isNone)

  let varDef =
    let monoTyScheme = TyScheme([], useSiteTy)

    let ident =
      ctx |> monoCtxGetGenericFunIdent genericFunSerial

    FunDef(ident, arity, monoTyScheme, loc)

  let monoFunSerial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> mapAdd monoFunSerial varDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> mapAdd (genericFunSerial, useSiteTy) monoFunSerial }

  let ctx = monoCtxMarkSomethingHappened ctx
  monoFunSerial, ctx

let private monoCtxFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials
  |> mapTryFind (funSerial, useSiteTy)

let private monoCtxMarkUseOfGenericFun (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic = useSiteTy |> tyIsMonomorphic

  let notMonomorphizedYet =
    monoCtxFindMonomorphizedFun ctx funSerial useSiteTy
    |> Option.isNone

  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
      | None -> []
      | Some useSiteTys -> useSiteTys

    let useSiteTys = useSiteTy :: useSiteTys

    let ctx =
      { ctx with
          GenericFunUseSiteTys =
            ctx.GenericFunUseSiteTys
            |> mapAdd funSerial useSiteTys }

    let ctx = monoCtxMarkSomethingHappened ctx
    ctx

let private monoCtxTakeMarkedGenericFunUseSiteTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
  | None
  | Some [] -> [], ctx
  | Some useSiteTys ->
      let _, map =
        ctx.GenericFunUseSiteTys |> mapRemove funSerial

      let ctx = { ctx with GenericFunUseSiteTys = map }

      let ctx = monoCtxMarkSomethingHappened ctx
      useSiteTys, ctx

/// Replaces the variable serial to monomorphized function serial if possible.
/// Or marks an use of generic function if possible.
/// Does nothing if the serial is NOT a generic function.
let private monoCtxProcessVarRef ctx varSerial useSiteTy =
  match monoCtxFindVarDef ctx varSerial with
  | VarDef _
  | VariantDef _
  | FunDef (_, _, TyScheme ([], _), _) -> varSerial, ctx

  | FunDef _ ->
      match monoCtxFindMonomorphizedFun ctx varSerial useSiteTy with
      | Some monoFunSerial -> monoFunSerial, ctx

      | None ->
          let ctx =
            monoCtxMarkUseOfGenericFun ctx varSerial useSiteTy

          varSerial, ctx

let private monifyPat (pat, ctx) = pat, ctx

let private monifyExprLetFun (ctx: MonoCtx) callee vis isMainFun args body next ty loc =
  let genericFunSerial = callee

  let letGenericFunExpr =
    HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] -> next, ctx
    | useSiteTy :: useSiteTys ->
        match monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
        | Some _ -> go next arity genericFunTy useSiteTys ctx
        | None ->

            // Within the context where genericFunTy and useSiteTy are unified
            // resolve all types in args and body.
            let extendedCtx =
              monoCtxUnifyTy ctx genericFunTy useSiteTy loc

            let monoArgs = monoCtxSubstPatsTy extendedCtx args
            let monoBody = monoCtxSubstTyExpr extendedCtx body

            let monoFunSerial, ctx =
              monoCtxAddMonomorphizedFun ctx genericFunSerial arity useSiteTy loc

            let next =
              HLetFunExpr(monoFunSerial, vis, isMainFun, monoArgs, monoBody, next, ty, loc)

            go next arity genericFunTy useSiteTys ctx

  match monoCtxFindGenericFunDef ctx genericFunSerial, ctx.Mode with
  | None, _ -> letGenericFunExpr, ctx
  | Some _, MonoMode.RemoveGenerics -> next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
      let useSiteTys, ctx =
        monoCtxTakeMarkedGenericFunUseSiteTys ctx genericFunSerial

      go letGenericFunExpr arity genericFunTy useSiteTys ctx

let private monifyExpr (expr, ctx) =
  match expr with
  | HErrorExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HLitExpr _
  | HPrimExpr _ -> expr, ctx

  | HRefExpr (varSerial, useSiteTy, loc) ->
      let doArm () =
        let varSerial, ctx =
          monoCtxProcessVarRef ctx varSerial useSiteTy

        HRefExpr(varSerial, useSiteTy, loc), ctx

      doArm ()

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target, ctx = (target, ctx) |> monifyExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap (fun ((pat, guard, body), ctx) ->
               let pat, ctx = (pat, ctx) |> monifyPat
               let guard, ctx = (guard, ctx) |> monifyExpr
               let body, ctx = (body, ctx) |> monifyExpr
               (pat, guard, body), ctx)

        HMatchExpr(target, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (subject, message, ty, loc) ->
      let doArm () =
        let subject, ctx = monifyExpr (subject, ctx)
        HNavExpr(subject, message, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, args, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyExpr
        HInfExpr(infOp, args, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat, ctx = (pat, ctx) |> monifyPat
        let init, ctx = (init, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyPat
        let body, ctx = (body, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        monifyExprLetFun ctx callee vis isMainFun args body next ty loc

      doArm ()

  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let monify (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let monoCtx =
    monoCtxFromTyCtx tyCtx
    |> monoCtxForceGeneralizeFuns

  // Monomorphization.
  let rec go (expr, ctx: MonoCtx) =
    if not ctx.SomethingHappened then
      expr, ctx
    else if ctx.InfiniteLoopDetector > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx =
        { ctx with
            SomethingHappened = false
            InfiniteLoopDetector = ctx.InfiniteLoopDetector + 1 }

      (expr, ctx) |> monifyExpr |> go

  let expr, monoCtx = go (expr, monoCtx)

  // Remove generic function definitions.
  // WARNING: Bad kind of code reuse.
  let expr, monoCtx =
    let monoCtx =
      { monoCtx with
          Mode = MonoMode.RemoveGenerics }

    monifyExpr (expr, monoCtx)

  let tyCtx =
    { tyCtx with
        Serial = monoCtx.Serial
        Vars = monoCtx.Vars
        Tys = monoCtx.Tys }

  expr, tyCtx
