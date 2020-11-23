/// # Monomorphization
///
/// Resolves use of polymorphic functions.
///
/// **Monomorphization** refers to a kind of code conversion
/// to eliminate use of generic types and functions from program.
///
/// ## Glossary
///
/// Types and functions are *monomorphic* if and only if
/// they have no type parameters.
///
/// ## Example
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
/// ## Algorithm
///
/// Repeat the following while something happens:
///
/// 1. For each use of generic function `f`,
///    if the use-site type `t` is monomorphic,
///    replace with the monomorphized instance of (`f`, `t`) if exists;
///    or mark the pair (`f`, `t`) for later otherwise.
/// 2. For each definition of generic function `f`,
///    and for each marked pair (`f`, `t`),
///    clone the definition and then unify the function type with `t`.
///    The cloned function is referred as monomorphized instance of (`f`, `t`).
///
/// NOTE: The algorithm seems inefficient and the finiteness is unproven.
module rec MiloneLang.Monomorphizing

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Hir

let private funSerialTyPairCmp l r = pairCmp funSerialCmp tyCmp l r

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private MonoCtx =
  { Serial: Serial
    Logs: (Log * Loc) list

    Funs: AssocMap<FunSerial, FunDef>
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

let private ofTyCtx (tyCtx: TyCtx): MonoCtx =
  { Serial = tyCtx.Serial
    Logs = tyCtx.Logs

    Funs = tyCtx.Funs
    Tys = tyCtx.Tys
    TyDepths = tyCtx.TyDepths

    GenericFunUseSiteTys = mapEmpty funSerialCmp
    GenericFunMonoSerials = mapEmpty funSerialTyPairCmp
    Mode = MonoMode.Monify
    SomethingHappened = true
    InfiniteLoopDetector = 0 }

let private toTyContext (monoCtx: MonoCtx): TyContext =
  { Serial = monoCtx.Serial
    Tys = monoCtx.Tys
    TyDepths = monoCtx.TyDepths

    // This doesn't matter here since we don't generalize.
    LetDepth = 0 }

let private withTyContext (tyCtx: TyContext) logAcc (monoCtx: MonoCtx) =
  { monoCtx with
      Serial = tyCtx.Serial
      Logs = logAcc
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths }

let private substTy (monoCtx: MonoCtx) ty: Ty = typingSubst (toTyContext monoCtx) ty

let private unifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let tyCtx = toTyContext monoCtx

  let logAcc, tyCtx =
    typingUnify monoCtx.Logs tyCtx lTy rTy loc

  monoCtx |> withTyContext tyCtx logAcc

let private markAsSomethingHappened (ctx: MonoCtx) = { ctx with SomethingHappened = true }

let private findFun (ctx: MonoCtx) funSerial = ctx.Funs |> mapFind funSerial

let private findGenericFun (ctx: MonoCtx) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial
  let (TyScheme (tyVars, funTy)) = funDef.Ty

  if List.isEmpty tyVars
  then None
  else Some(funDef.Name, funDef.Arity, funTy, funDef.Loc)

let private findFunName funSerial (ctx: MonoCtx) = (ctx.Funs |> mapFind funSerial).Name

/// Generalizes all functions that has type variables.
let private forceGeneralizeFuns (ctx: MonoCtx) =
  let funs =
    ctx.Funs
    |> mapFold (fun funs funSerial (funDef: FunDef) ->
         let (TyScheme (_, ty)) = funDef.Ty
         let fvs = ty |> tyCollectFreeVars

         funs
         |> mapAdd funSerial { funDef with Ty = TyScheme(fvs, ty) }) ctx.Funs

  { ctx with Funs = funs }

let private addMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity useSiteTy loc =
  assert (tryFindMonomorphizedFun ctx genericFunSerial useSiteTy
          |> Option.isNone)

  let funDef: FunDef =
    let name = ctx |> findFunName genericFunSerial
    { Name = name
      Arity = arity
      Ty = TyScheme([], useSiteTy)
      Loc = loc }

  let monoFunSerial = FunSerial(ctx.Serial + 1)

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Funs = ctx.Funs |> mapAdd monoFunSerial funDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> mapAdd (genericFunSerial, useSiteTy) monoFunSerial }

  let ctx = markAsSomethingHappened ctx
  monoFunSerial, ctx

/// Tries to find a monomorphized instance of generic function with use-site type.
let private tryFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials
  |> mapTryFind (funSerial, useSiteTy)

let private markUseSite (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic = useSiteTy |> tyIsMonomorphic

  let notMonomorphizedYet =
    tryFindMonomorphizedFun ctx funSerial useSiteTy
    |> Option.isNone

  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      let useSiteTys =
        match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
        | None -> []
        | Some useSiteTys -> useSiteTys

      useSiteTy :: useSiteTys

    { ctx with
        GenericFunUseSiteTys =
          ctx.GenericFunUseSiteTys
          |> mapAdd funSerial useSiteTys }
    |> markAsSomethingHappened

let private takeMarkedTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> mapTryFind funSerial with
  | None
  | Some [] -> [], ctx

  | Some useSiteTys ->
      let ctx =
        { ctx with
            GenericFunUseSiteTys =
              ctx.GenericFunUseSiteTys
              |> mapRemove funSerial
              |> snd }
        |> markAsSomethingHappened

      useSiteTys, ctx

// -----------------------------------------------
// Featured transformations
// -----------------------------------------------

/// Replaces the variable serial to monomorphized function serial if possible.
/// Or marks an use of generic function if possible.
/// Does nothing if the serial is NOT a generic function.
let private monifyFunExpr ctx funSerial useSiteTy =
  let funDef = findFun ctx funSerial
  let (TyScheme (tyVars, _)) = funDef.Ty
  if List.isEmpty tyVars then
    funSerial, ctx
  else
    match tryFindMonomorphizedFun ctx funSerial useSiteTy with
    | Some monoFunSerial -> monoFunSerial, ctx

    | None ->
        let ctx = markUseSite ctx funSerial useSiteTy

        funSerial, ctx

let private monifyLetFunExpr (ctx: MonoCtx) callee vis isMainFun args body next ty loc =
  let genericFunSerial = callee

  let letGenericFunExpr =
    HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] -> next, ctx
    | useSiteTy :: useSiteTys ->
        match tryFindMonomorphizedFun ctx genericFunSerial useSiteTy with
        | Some _ -> go next arity genericFunTy useSiteTys ctx
        | None ->
            // Within the context where genericFunTy and useSiteTy are unified
            // resolve all types in args and body.
            let extendedCtx = unifyTy ctx genericFunTy useSiteTy loc

            let monoArgs =
              args |> List.map (patMap (substTy extendedCtx) id)

            let monoBody = body |> exprMap (substTy extendedCtx) id

            let monoFunSerial, ctx =
              addMonomorphizedFun ctx genericFunSerial arity useSiteTy loc

            let next =
              HLetFunExpr(monoFunSerial, vis, isMainFun, monoArgs, monoBody, next, ty, loc)

            go next arity genericFunTy useSiteTys ctx

  match findGenericFun ctx genericFunSerial, ctx.Mode with
  | None, _ -> letGenericFunExpr, ctx
  | Some _, MonoMode.RemoveGenerics -> next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
      let useSiteTys, ctx = takeMarkedTys ctx genericFunSerial

      go letGenericFunExpr arity genericFunTy useSiteTys ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private monifyExpr (expr, ctx) =
  match expr with
  | HErrorExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HLitExpr _
  | HRefExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HFunExpr (funSerial, useSiteTy, loc) ->
      let doArm () =
        let funSerial, ctx = monifyFunExpr ctx funSerial useSiteTy

        HFunExpr(funSerial, useSiteTy, loc), ctx

      doArm ()

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond, ctx = (cond, ctx) |> monifyExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap (fun ((pat, guard, body), ctx) ->
               let guard, ctx = (guard, ctx) |> monifyExpr
               let body, ctx = (body, ctx) |> monifyExpr
               (pat, guard, body), ctx)

        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, args, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyExpr
        HInfExpr(infOp, args, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let init, ctx = (init, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let body, ctx = (body, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        monifyLetFunExpr ctx callee vis isMainFun args body next ty loc

      doArm ()

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or TyElaborating"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in TyElaboration"
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let monify (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let monoCtx = ofTyCtx tyCtx |> forceGeneralizeFuns

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
        Funs = monoCtx.Funs
        Tys = monoCtx.Tys }

  expr, tyCtx
