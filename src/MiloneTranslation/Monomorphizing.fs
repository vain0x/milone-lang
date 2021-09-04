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
///
/// ## Remarks
///
/// - Currently monomorphized instances don't duplicate local variable definitions.
module rec MiloneTranslation.Monomorphizing

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

let private funSerialTyListPairCompare l r =
  pairCompare funSerialCompare (listCompare tyCompare) l r

// #tyAssign
let private tyAssign tyScheme (tyArgs: Ty list) =
  let (TyScheme (tyVars, genericTy)) = tyScheme

  let assignment =
    match listTryZip tyVars tyArgs with
    | zipped, [], [] -> TMap.ofList compare zipped
    | _ -> unreachable () // Arity mismatch.

  tySubst (fun tySerial -> assignment |> TMap.tryFind tySerial) genericTy

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MonoCtx =
  { Serial: Serial

    Funs: AssocMap<FunSerial, FunDef>
    Tys: AssocMap<TySerial, TyDef>

    /// Map from
    /// - generic function serial
    ///
    /// to:
    /// - list of found use-site ty args
    GenericFunUseSiteTys: AssocMap<FunSerial, Ty list list>

    /// Map from pairs:
    /// - generic function's serial
    /// - monomorphic use-site ty args
    ///
    /// to:
    /// - monomorphized function's serial
    GenericFunMonoSerials: AssocMap<FunSerial * Ty list, FunSerial>

    Mode: MonoMode
    SomethingHappened: bool }

let private ofTyCtx (tyCtx: TyCtx) : MonoCtx =
  { Serial = tyCtx.Serial

    Funs = tyCtx.Funs
    Tys = tyCtx.Tys

    GenericFunUseSiteTys = TMap.empty funSerialCompare
    GenericFunMonoSerials = TMap.empty funSerialTyListPairCompare
    Mode = MonoMode.Monify
    SomethingHappened = true }

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

let private addMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity tyArgs loc =
  assert (tryFindMonomorphizedFun ctx genericFunSerial tyArgs
          |> Option.isNone)

  let funDef: FunDef =
    let def: FunDef = ctx.Funs |> mapFind genericFunSerial

    let monomorphicFunTy = tyAssign def.Ty tyArgs

    // if not (tyIsMonomorphic monomorphicFunTy) then
    //   let (TyScheme (tyVars, genericTy)) = def.Ty

    //   printfn
    //     "\n\nassertion violation\n %s defined at %s\n  tyVars = %s\ngenericTy = %s\ntyArgs = %s\n monoTy = %s"
    //     def.Name
    //     (locToString def.Loc)
    //     (objToString tyVars)
    //     (objToString genericTy)
    //     (objToString tyArgs)
    //     (objToString monomorphicFunTy)

    assert (tyIsMonomorphic monomorphicFunTy)

    { def with
        Arity = arity
        Ty = TyScheme([], monomorphicFunTy)
        Linkage = InternalLinkage // Generic function can't have stable linkage.
        Loc = loc }

  let monoFunSerial = FunSerial(ctx.Serial + 1)

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Funs = ctx.Funs |> TMap.add monoFunSerial funDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> TMap.add (genericFunSerial, tyArgs) monoFunSerial }

  let ctx = markAsSomethingHappened ctx
  monoFunSerial, ctx

/// Tries to find a monomorphized instance of generic function with use-site type.
let private tryFindMonomorphizedFun (ctx: MonoCtx) funSerial tyArgs =
  ctx.GenericFunMonoSerials
  |> TMap.tryFind (funSerial, tyArgs)

let private markUseSite (ctx: MonoCtx) funSerial tyArgs =
  let isMonomorphic = List.forall tyIsMonomorphic tyArgs

  let notMonomorphizedYet =
    tryFindMonomorphizedFun ctx funSerial tyArgs
    |> Option.isNone

  let canMark = isMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    { ctx with
        GenericFunUseSiteTys = multimapAdd funSerial tyArgs ctx.GenericFunUseSiteTys }
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
let private monifyFunExpr ctx funSerial tyArgs =
  let funDef = findFun ctx funSerial
  let (TyScheme (tyVars, _)) = funDef.Ty

  if List.isEmpty tyVars then
    funSerial, [], ctx
  else
    match tryFindMonomorphizedFun ctx funSerial tyArgs with
    | Some monoFunSerial -> monoFunSerial, [], ctx

    | None ->
      let ctx = markUseSite ctx funSerial tyArgs

      funSerial, tyArgs, ctx

let private monifyLetFunExpr (ctx: MonoCtx) callee isRec vis args body next ty loc =
  let genericFunSerial = callee

  let letGenericFunExpr =
    HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc)

  let rec go next arity genericFunTy workList ctx =
    match workList with
    | [] -> next, ctx
    | tyArgs :: workList ->
      match tryFindMonomorphizedFun ctx genericFunSerial tyArgs with
      | Some _ -> go next arity genericFunTy workList ctx
      | None ->
        let genericFunDef = ctx.Funs |> mapFind genericFunSerial
        let (TyScheme (tyVars, _)) = genericFunDef.Ty

        let binding =
          // #tyAssign?
          match listTryZip tyVars tyArgs with
          | zipped, [], [] -> TMap.ofList compare zipped
          | _ -> unreachable () // Arity mismatch.

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
          addMonomorphizedFun ctx genericFunSerial arity tyArgs loc

        let next =
          HLetFunExpr(monoFunSerial, isRec, vis, monoArgs, monoBody, next, ty, loc)

        go next arity genericFunTy workList ctx

  match findGenericFun ctx genericFunSerial, ctx.Mode with
  | None, _ -> letGenericFunExpr, ctx
  | Some _, MonoMode.RemoveGenerics -> next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
    let workList, ctx = takeMarkedTys ctx genericFunSerial

    go letGenericFunExpr arity genericFunTy workList ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private monifyExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HFunExpr (funSerial, ty, tyArgs, loc) ->
    let funSerial, tyArgs, ctx = monifyFunExpr ctx funSerial tyArgs
    HFunExpr(funSerial, ty, tyArgs, loc), ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = (cond, ctx) |> monifyExpr

    let arms, ctx =
      (arms, ctx)
      |> stMap
           (fun ((pat, guard, body), ctx) ->
             let guard, ctx = (guard, ctx) |> monifyExpr
             let body, ctx = (body, ctx) |> monifyExpr
             (pat, guard, body), ctx)

    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyExpr
    HNodeExpr(kind, args, ty, loc), ctx

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap monifyExpr
    let last, ctx = (last, ctx) |> monifyExpr
    HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
    let init, ctx = (init, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    HLetValExpr(pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    let body, ctx = (body, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    monifyLetFunExpr ctx callee isRec vis args body next ty loc

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let monify (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let monoCtx = ofTyCtx tyCtx

  // Monomorphization.
  let rec go (round: int) (decls, ctx: MonoCtx) =
    if not ctx.SomethingHappened then
      decls, ctx
    else if round > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx = { ctx with SomethingHappened = false }

      (decls, ctx) |> stMap monifyExpr |> go (round + 1)

  let decls, monoCtx = go 0 (decls, monoCtx)

  // Remove generic function definitions.
  // WARNING: Bad kind of code reuse.
  let decls, monoCtx =
    let monoCtx =
      { monoCtx with
          Mode = MonoMode.RemoveGenerics }

    (decls, monoCtx) |> stMap monifyExpr

  // Currently monomorphized instances don't duplicate local variable definitions.
  // VarDef.Ty is no longer reliable.
  let vars =
    tyCtx.Vars
    |> TMap.map (fun _ (varDef: VarDef) -> { varDef with Ty = noTy })

  let tyCtx =
    { tyCtx with
        Serial = monoCtx.Serial
        Vars = vars
        Funs = monoCtx.Funs
        Tys = monoCtx.Tys }

  decls, tyCtx
