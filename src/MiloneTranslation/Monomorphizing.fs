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
open MiloneStd.StdError
open MiloneStd.StdMap
open MiloneStd.StdMultimap
open MiloneTranslation.Hir

// #tyAssign?
let private getTyAssignment tyVars tyArgs : TreeMap<TySerial, Ty> =
  match listTryZip tyVars tyArgs with
  | zipped, [], [] -> TMap.ofList compare zipped
  | _ -> unreachable () // Arity mismatch.

// #tyAssign
let private tyAssign tyScheme (tyArgs: Ty list) =
  let (TyScheme (tyVars, genericTy)) = tyScheme

  let assignment =
    match listTryZip tyVars tyArgs with
    | zipped, [], [] -> TMap.ofList compare zipped
    | _ -> unreachable () // Arity mismatch.

  tySubst (fun tySerial -> assignment |> TMap.tryFind tySerial) genericTy

type private ModuleId = int

[<NoEquality; NoComparison>]
type private FunBody = FunBody of argPats: HPat list * body: HExpr

/// Monomorphic use of generic function.
type private MonoUse = FunSerial * Ty list

let private monoUseCompare =
  pairCompare funSerialCompare (listCompare tyCompare)

// -----------------------------------------------
// Collect
// -----------------------------------------------

// Collect step folds expression to find all:
//
//  - monomorphic use-site of generic functions
//  - body of generic functions.

/// Read-only context of collect step.
type private CollectRx =
  { Funs: TreeMap<FunSerial, FunDef>
    CurrentModuleId: ModuleId }

/// Mutable context of collect step.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CollectWx =
  { GenericFunBody: TreeMap<FunSerial, ModuleId * FunBody>
    UseSiteTys: MonoUse list }

let private emptyCollectWx: CollectWx =
  { GenericFunBody = TMap.empty funSerialCompare
    UseSiteTys = [] }

let private collectOnExpr (rx: CollectRx) (wx: CollectWx) expr : CollectWx =
  let onExpr expr ctx = collectOnExpr rx ctx expr

  let onExprs exprs ctx =
    exprs |> List.fold (collectOnExpr rx) ctx

  let onStmts stmts wx =
    stmts |> List.fold (collectOnStmt rx) wx

  match expr with
  | HLitExpr _
  | HVarExpr _
  | HVariantExpr _
  | HPrimExpr _ -> wx

  | HFunExpr (funSerial, _, tyArgs, _) ->
    if tyArgs |> List.isEmpty |> not
       && tyArgs |> List.forall tyIsMonomorphic then
      { wx with UseSiteTys = (funSerial, tyArgs) :: wx.UseSiteTys }
    else
      wx

  | HMatchExpr (cond, arms, _, _) ->
    wx
    |> onExpr cond
    |> forList (fun (_, guard, body) ctx -> ctx |> onExpr guard |> onExpr body) arms

  | HNodeExpr (_, items, _, _) -> wx |> onExprs items
  | HBlockExpr (stmts, last) -> collectOnExpr rx (wx |> onStmts stmts) last

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private collectOnStmt (rx: CollectRx) (wx: CollectWx) stmt : CollectWx =
  let onExpr expr wx = collectOnExpr rx wx expr

  let getFunDef funSerial = rx.Funs |> mapFind funSerial

  match stmt with
  | HExprStmt expr -> wx |> onExpr expr

  | HLetValStmt (_, body, _) -> wx |> onExpr body

  | HLetFunStmt (funSerial, args, body, _) ->
    let funDef = getFunDef funSerial
    let (TyScheme (tyVars, _)) = funDef.Ty

    let wx =
      if tyVars |> List.isEmpty |> not then
        { wx with
            GenericFunBody =
              wx.GenericFunBody
              |> TMap.add funSerial (rx.CurrentModuleId, FunBody(args, body)) }
      else
        wx

    wx |> onExpr body

// -----------------------------------------------
// Rewrite
// -----------------------------------------------

// Rewrite step does:
//
// - replace all use of generic functions with monomorphized instance
// - remove all let-fun of generic functions.

/// Read-only context of rewrite step.
type private RewriteRx =
  { GetFunIdent: FunSerial -> Ident
    IsGenericFun: FunSerial -> bool
    InstanceMap: TreeMap<MonoUse, FunSerial> }

let private rewriteExpr (rx: RewriteRx) expr : HExpr =
  let onExpr expr = rewriteExpr rx expr
  let onExprs exprs = exprs |> List.map (rewriteExpr rx)
  let onStmts stmts = stmts |> List.choose (rewriteStmt rx)

  let getGenericInstance monoUse loc : FunSerial =
    match rx.InstanceMap |> TMap.tryFind monoUse with
    | Some it -> it

    | None ->
      let funSerial, _ = monoUse

      printfn
        "assertion violation: monomorphized instance should have been generated for %s #%d at %s"
        (rx.GetFunIdent funSerial)
        (funSerialToInt funSerial)
        (Loc.toString loc)

      assert false
      exit 1

  match expr with
  | HLitExpr _
  | HVarExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr

  | HFunExpr (_, _, [], _) -> expr

  | HFunExpr (funSerial, ty, tyArgs, loc) ->
    let monoFunSerial =
      getGenericInstance (funSerial, tyArgs) loc

    HFunExpr(monoFunSerial, ty, [], loc)

  | HMatchExpr (cond, arms, ty, loc) ->
    let arms = arms |> List.map (hArmMap id onExpr)
    HMatchExpr(onExpr cond, arms, ty, loc)

  | HNodeExpr (kind, items, ty, loc) -> HNodeExpr(kind, onExprs items, ty, loc)
  | HBlockExpr (stmts, last) -> HBlockExpr(onStmts stmts, onExpr last)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private rewriteStmt (rx: RewriteRx) stmt : HStmt option =
  let onExpr expr = rewriteExpr rx expr
  let onExprs exprs = exprs |> List.map (rewriteExpr rx)
  let onStmts stmts = stmts |> List.map (rewriteStmt rx)

  let isGenericFun funSerial = rx.IsGenericFun funSerial

  match stmt with
  | HExprStmt expr -> HExprStmt(rewriteExpr rx expr) |> Some

  | HLetValStmt (pat, body, loc) -> HLetValStmt(pat, onExpr body, loc) |> Some

  | HLetFunStmt (callee, args, body, loc) ->
    if isGenericFun callee then
      None
    else
      HLetFunStmt(callee, args, onExpr body, loc)
      |> Some

// -----------------------------------------------
// Generation
// -----------------------------------------------

/// State of monomorphization.
type private MonoCtx =
  { Serial: Serial
    NewFuns: (FunSerial * FunDef * FunBody * FunSerial * Loc) list
    InstanceMap: TreeMap<MonoUse, FunSerial>
    WorkList: MonoUse list }

let private generateMonomorphizedFun
  isMetaTy
  mangle
  (genericFunDef: FunDef)
  (genericFunBody: FunBody)
  (monoTyArgs: Ty list)
  =
  let assertNoMetaTy monoFunTy =
    if monoFunTy |> tyIsMonomorphic |> not then
      let (TyScheme (tyVars, genericFunTy)) = genericFunDef.Ty

      printfn
        "assertion violation\n  %s at %s\n  : %s => %s\n  tyArgs %s\n  monoTy = %s"
        genericFunDef.Name
        (Loc.toString genericFunDef.Loc)
        (__dump tyVars)
        (__dump genericFunTy)
        (__dump monoTyArgs)
        (__dump monoFunTy)

      assert (tyIsMonomorphic monoFunTy)

  let monoFunDef: FunDef =
    let monoFunTy = tyAssign genericFunDef.Ty monoTyArgs
    assertNoMetaTy monoFunTy

    { genericFunDef with
        Prefix = mangle monoFunTy :: genericFunDef.Prefix
        Ty = TyScheme([], monoFunTy)
        Linkage = InternalLinkage } // Generic function can't have stable linkage.

  let monoFunBody =
    let (FunBody (genericArgPats, genericBody)) = genericFunBody

    let assignment =
      let (TyScheme (tyVars, _)) = genericFunDef.Ty
      getTyAssignment tyVars monoTyArgs

    let substOrDegenerateTy ty =
      let substMeta tySerial =
        match assignment |> TMap.tryFind tySerial with
        | (Some _) as it -> it
        | None -> Some(if isMetaTy tySerial then ty else tyUnit)

      tySubst substMeta ty

    let monoArgPats =
      genericArgPats
      |> List.map (patMap substOrDegenerateTy)

    let monoBody =
      genericBody |> exprMap substOrDegenerateTy

    FunBody(monoArgPats, monoBody)

  monoFunDef, monoFunBody

let private generate isMetaTy mangle (rx: CollectRx) genericFunBodyMap (ctx: MonoCtx) (entry: MonoUse) : MonoCtx =
  let funSerial, monoTyArgs = entry

  match ctx.InstanceMap |> TMap.tryFind entry with
  | Some _ -> ctx

  | None ->
    let genericFunDef = rx.Funs |> mapFind funSerial

    let monoFunDef, monoFunBody =
      let _, genericFunBody = genericFunBodyMap |> mapFind funSerial
      generateMonomorphizedFun isMetaTy mangle genericFunDef genericFunBody monoTyArgs

    let workList =
      let (FunBody (_, body)) = monoFunBody

      let wx =
        { emptyCollectWx with UseSiteTys = ctx.WorkList }

      let wx = collectOnExpr rx wx body
      wx.UseSiteTys

    let monoFunSerial = FunSerial(ctx.Serial + 1)

    { ctx with
        Serial = ctx.Serial + 1
        NewFuns =
          (monoFunSerial, monoFunDef, monoFunBody, funSerial, genericFunDef.Loc)
          :: ctx.NewFuns
        InstanceMap = ctx.InstanceMap |> TMap.add entry monoFunSerial
        WorkList = workList }

// -----------------------------------------------
// Interface
// -----------------------------------------------

let monify (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let getFunIdent funSerial =
    let funDef = hirCtx.Funs |> mapFind funSerial
    let serial = string (funSerialToInt funSerial)
    let loc = Loc.toString funDef.Loc

    funDef.Name + " #" + serial + " " + loc

  // #tyNames
  let tyNames =
    hirCtx.Tys
    |> TMap.fold
         (fun tyNames tySerial tyDef ->
           let tk, name =
             match tyDef with
             | UnionTyDef (ident, _, _, _) -> UnionTk tySerial, ident
             | RecordTyDef (ident, _, _, _) -> RecordTk tySerial, ident
             | MetaTyDef _ -> unreachable () // Resolved in Typing.

           tyNames |> TMap.add (Ty(tk, [])) name)
         (TMap.empty tyCompare)

  // Analyze initially.
  let initialWorkList, genericFunBodyMap =
    let collectWx =
      modules
      |> List.mapi (fun moduleId (m: HModule) -> moduleId, m)
      |> List.fold
           (fun wx (moduleId, m: HModule) ->
             let collectRx: CollectRx =
               { CurrentModuleId = moduleId
                 Funs = hirCtx.Funs }

             m.Stmts |> List.fold (collectOnStmt collectRx) wx)
           emptyCollectWx

    collectWx.UseSiteTys, collectWx.GenericFunBody

  let isGenericFun funSerial =
    genericFunBodyMap |> TMap.containsKey funSerial

  // Repeat to generate.
  let isMetaTy tySerial =
    match hirCtx.Tys |> TMap.tryFind tySerial with
    | Some (MetaTyDef ty) ->
      // remove this!
      printfn "meta #%d %s" tySerial (__dump ty)
      assert false
      true

    | _ -> false

  let rec go workList (ctx: MonoCtx) : MonoCtx =
    match workList with
    | [] ->
      if ctx.WorkList |> List.isEmpty then
        ctx
      else
        let workList, ctx =
          ctx.WorkList, { ctx with WorkList = [] }

        go workList ctx

    | item :: workList ->
      // Module id is unused.
      let collectRx: CollectRx =
        { CurrentModuleId = -1
          Funs = hirCtx.Funs }

      let mangle ty =
        // don't drop memoization state
        tyMangle (ty, tyNames) |> fst

      go workList (generate isMetaTy mangle collectRx genericFunBodyMap ctx item)

  let ctx =
    let ctx: MonoCtx =
      { Serial = hirCtx.Serial
        NewFuns = []
        InstanceMap = TMap.empty monoUseCompare
        WorkList = [] }

    go initialWorkList ctx

  // Split monomorphized instances into modules.
  let newFunsPerModule =
    ctx.NewFuns
    |> List.map (fun (funSerial, _, body, genericFunSerial, loc) ->
      let moduleId, _ =
        genericFunBodyMap |> mapFind genericFunSerial

      moduleId, (funSerial, body, loc))
    |> Multimap.ofList compare

  // Rewrite.
  let modules =
    modules
    |> List.mapi (fun moduleId (m: HModule) ->
      let funBodies =
        newFunsPerModule
        |> Multimap.find moduleId
        |> List.map (fun (funSerial, body, loc) ->
          let (FunBody (args, body)) = body
          HLetFunStmt(funSerial, args, body, loc))

      let stmts = List.append funBodies m.Stmts

      let stmts =
        let rx: RewriteRx =
          { GetFunIdent = getFunIdent
            IsGenericFun = isGenericFun
            InstanceMap = ctx.InstanceMap }

        stmts |> List.choose (rewriteStmt rx)

      { m with Stmts = stmts })

  // Merge.
  let hirCtx: HirCtx =
    let funs =
      hirCtx.Funs
      |> TMap.filter (fun funSerial _ -> funSerial |> isGenericFun |> not)

    // #map_merge
    let funs =
      ctx.NewFuns
      |> List.fold (fun funs (funSerial, funDef, _, _, _) -> funs |> TMap.add funSerial funDef) funs

    { hirCtx with
        Serial = ctx.Serial
        Funs = funs }

  modules, hirCtx
