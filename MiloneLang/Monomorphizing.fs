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

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Hir

module TMap = MiloneStd.StdMap

let private funSerialTyPairCompare l r =
  pairCompare funSerialCompare tyCompare l r

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MonoCtx =
  { Serial: Serial
    Logs: (Log * Loc) list

    Funs: AssocMap<FunSerial, FunDef>
    Tys: AssocMap<TySerial, TyDef>

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

let private ofTyCtx (tyCtx: TyCtx) : MonoCtx =
  { Serial = tyCtx.Serial
    Logs = tyCtx.Logs

    Funs = tyCtx.Funs
    Tys = tyCtx.Tys

    GenericFunUseSiteTys = TMap.empty funSerialCompare
    GenericFunMonoSerials = TMap.empty funSerialTyPairCompare
    Mode = MonoMode.Monify
    SomethingHappened = true
    InfiniteLoopDetector = 0 }

let private unifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let ctx = monoCtx

  let expandMeta binding tySerial =
    match binding |> TMap.tryFind tySerial with
    | (Some _) as it -> it
    | _ ->
        match ctx.Tys |> TMap.tryFind tySerial with
        | Some (MetaTyDef ty) -> Some ty
        | _ -> None

  let substTy binding ty = tySubst (expandMeta binding) ty

  let rec go lTy rTy loc binding =
    match unifyNext lTy rTy loc with
    | UnifyOk
    | UnifyError _ ->
        // NOTE: Unification may fail due to auto boxing.
        //       This is not fatal problem since all type errors are already handled in typing phase.
        binding

    | UnifyOkWithStack stack -> List.fold (fun binding (l, r) -> go l r loc binding) binding stack

    | UnifyExpandMeta (tySerial, otherTy) ->
        match expandMeta binding tySerial with
        | Some ty -> go ty otherTy loc binding

        | None ->
            match unifyAfterExpandMeta lTy rTy tySerial (substTy binding otherTy) loc with
            | UnifyAfterExpandMetaResult.OkNoBind -> binding

            | UnifyAfterExpandMetaResult.OkBind -> binding |> TMap.add tySerial otherTy

            | UnifyAfterExpandMetaResult.Error _ -> binding

    | UnifyExpandSynonym _ -> unreachable () // Resolved in Typing.

  go lTy rTy loc emptyBinding

let private markAsSomethingHappened (ctx: MonoCtx) =
  if ctx.SomethingHappened then
    ctx
  else
    { ctx with SomethingHappened = true }

let private findFun (ctx: MonoCtx) funSerial = ctx.Funs |> mapFind funSerial

let private findGenericFun (ctx: MonoCtx) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial
  let (TyScheme (tyVars, funTy)) = funDef.Ty

  if List.isEmpty tyVars then
    None
  else
    Some(funDef.Name, funDef.Arity, funTy, funDef.Loc)

let private findFunName funSerial (ctx: MonoCtx) = (ctx.Funs |> mapFind funSerial).Name

/// Generalizes all functions that has type variables.
let private forceGeneralizeFuns (ctx: MonoCtx) =
  let funs =
    ctx.Funs
    |> TMap.map
         (fun funSerial (funDef: FunDef) ->
           let (TyScheme (_, ty)) = funDef.Ty
           let fvs = ty |> tyCollectFreeVars

           { funDef with Ty = TyScheme(fvs, ty) })

  { ctx with Funs = funs }

let private addMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity useSiteTy loc =
  assert (tryFindMonomorphizedFun ctx genericFunSerial useSiteTy
          |> Option.isNone)

  let funDef : FunDef =
    let name = ctx |> findFunName genericFunSerial

    { Name = name
      Arity = arity
      Ty = TyScheme([], useSiteTy)
      Abi = CAbi
      Loc = loc }

  let monoFunSerial = FunSerial(ctx.Serial + 1)

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Funs = ctx.Funs |> TMap.add monoFunSerial funDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> TMap.add (genericFunSerial, useSiteTy) monoFunSerial }

  let ctx = markAsSomethingHappened ctx
  monoFunSerial, ctx

/// Tries to find a monomorphized instance of generic function with use-site type.
let private tryFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials
  |> TMap.tryFind (funSerial, useSiteTy)

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
        match ctx.GenericFunUseSiteTys |> TMap.tryFind funSerial with
        | None -> []
        | Some useSiteTys -> useSiteTys

      useSiteTy :: useSiteTys

    { ctx with
        GenericFunUseSiteTys =
          ctx.GenericFunUseSiteTys
          |> TMap.add funSerial useSiteTys }
    |> markAsSomethingHappened

let private takeMarkedTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> TMap.tryFind funSerial with
  | None
  | Some [] -> [], ctx

  | Some useSiteTys ->
      let ctx =
        { ctx with
            GenericFunUseSiteTys =
              ctx.GenericFunUseSiteTys
              |> TMap.remove funSerial
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

let private monifyLetFunExpr (ctx: MonoCtx) callee isRec vis args body next ty loc =
  let genericFunSerial = callee

  let letGenericFunExpr =
    HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] -> next, ctx
    | useSiteTy :: useSiteTys ->
        match tryFindMonomorphizedFun ctx genericFunSerial useSiteTy with
        | Some _ -> go next arity genericFunTy useSiteTys ctx
        | None ->
            // Unify genericFunTy and useSiteTy to build a mapping
            // from type variable to use-site type.
            let binding = unifyTy ctx genericFunTy useSiteTy loc

            let substOrDegenerateTy ty =
              let substMeta tySerial =
                match binding |> TMap.tryFind tySerial with
                | (Some _) as it -> it
                | None ->
                    match ctx.Tys |> TMap.tryFind tySerial with
                    | Some (MetaTyDef ty) -> Some ty
                    | _ -> Some tyUnit

              tySubst substMeta ty

            let monoArgs =
              args |> List.map (patMap substOrDegenerateTy id)

            let monoBody = body |> exprMap substOrDegenerateTy id

            let monoFunSerial, ctx =
              addMonomorphizedFun ctx genericFunSerial arity useSiteTy loc

            let next =
              HLetFunExpr(monoFunSerial, isRec, vis, monoArgs, monoBody, next, ty, loc)

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
  | HTyDeclExpr _
  | HOpenExpr _
  | HLitExpr _
  | HVarExpr _
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
          |> stMap
               (fun ((pat, guard, body), ctx) ->
                 let guard, ctx = (guard, ctx) |> monifyExpr
                 let body, ctx = (body, ctx) |> monifyExpr
                 (pat, guard, body), ctx)

        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HNodeExpr (kind, args, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyExpr
        HNodeExpr(kind, args, ty, loc), ctx

      doArm ()

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts, ctx = (stmts, ctx) |> stMap monifyExpr
        let last, ctx = (last, ctx) |> monifyExpr
        HBlockExpr(stmts, last), ctx

      doArm ()

  | HLetValExpr (pat, init, next, ty, loc) ->
      let doArm () =
        let init, ctx = (init, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        HLetValExpr(pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
      let doArm () =
        let body, ctx = (body, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        monifyLetFunExpr ctx callee isRec vis args body next ty loc

      doArm ()

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.
  | HModuleExpr _
  | HModuleSynonymExpr _ -> unreachable () // Resolved in NameRes.

let monify (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let monoCtx = ofTyCtx tyCtx |> forceGeneralizeFuns

  // Monomorphization.
  let rec go (decls, ctx: MonoCtx) =
    if not ctx.SomethingHappened then
      decls, ctx
    else if ctx.InfiniteLoopDetector > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx =
        { ctx with
            SomethingHappened = false
            InfiniteLoopDetector = ctx.InfiniteLoopDetector + 1 }

      (decls, ctx) |> stMap monifyExpr |> go

  let decls, monoCtx = go (decls, monoCtx)

  // Remove generic function definitions.
  // WARNING: Bad kind of code reuse.
  let decls, monoCtx =
    let monoCtx =
      { monoCtx with
          Mode = MonoMode.RemoveGenerics }

    (decls, monoCtx) |> stMap monifyExpr

  let tyCtx =
    { tyCtx with
        Serial = monoCtx.Serial
        Funs = monoCtx.Funs
        Tys = monoCtx.Tys }

  decls, tyCtx
