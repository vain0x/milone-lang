/// # AST Bundle
///
/// Resolves dependencies between modules.
/// This stage determines the set of modules in the project and the ordering of them.
///
/// These modules are combined into single HIR expression.
module rec MiloneLang.AstBundle

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.AstToHir
open MiloneLang.Hir

module TSet = MiloneStd.StdSet
module TMap = MiloneStd.StdMap
module S = MiloneStd.StdString

type private ProjectName = string
type private ModuleName = string
type private ModuleRef = int * ModuleName

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleRequest =
  { ProjectName: string
    ModuleName: string
    OriginOpt: (ModuleRef * Pos) option
    Optional: bool }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleInfo =
  { Ref: ModuleRef
    Project: ProjectName
    DocId: DocId
    AstOpt: ARoot option }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleCtx =
  { Projects: TSet.TreeSet<ProjectName>
    Modules: TMap.TreeMap<ModuleRef, ModuleInfo>
    ModuleMap: TMap.TreeMap<ProjectName * ModuleName, ModuleInfo>

    ModuleStack: ModuleRequest list
    ModuleDeps: TMap.TreeMap<ModuleRef, (ProjectName * ModuleName) list> }

[<NoEquality; NoComparison>]
type BundleStatus =
  | NoRequest
  | ModuleInfoRequested of ModuleRequest
  | ModuleBundled of ModuleRef

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleResult = { Modules: ModuleInfo list }

let private compareRef (l: int * string) (r: int * string) : int =
  let c = compare (fst l) (fst r)

  if c <> 0 then
    c
  else
    assert (snd l = snd r)
    0

// -----------------------------------------------
// ModuleRequest
// -----------------------------------------------

let private newRootRequest (projectName: ProjectName) (moduleName: string) : ModuleRequest =
  { ProjectName = projectName
    ModuleName = moduleName
    OriginOpt = None
    Optional = false }

let private newMiloneOnlyRequest (projectName: ProjectName) : ModuleRequest =
  { ProjectName = projectName
    ModuleName = "MiloneOnly"
    OriginOpt = None
    Optional = true }

let private newDepRequest
  (projectName: ProjectName)
  (moduleName: ModuleName)
  (originRef: ModuleRef)
  (pos: Pos)
  : ModuleRequest =
  { ProjectName = projectName
    ModuleName = moduleName
    OriginOpt = Some(originRef, pos)
    Optional = false }

// -----------------------------------------------
// Context
// -----------------------------------------------

let private requestDeps (moduleInfo: ModuleInfo) (ctx: BundleCtx) : BundleCtx =
  match moduleInfo.AstOpt with
  | None -> ctx

  | Some root ->
      // All modules depend on MiloneOnly implicitly.
      let deps, stack =
        let r = newMiloneOnlyRequest moduleInfo.Project
        [ r.ProjectName, r.ModuleName ], r :: ctx.ModuleStack

      let deps, stack =
        findDependentModules root
        |> List.fold
             (fun (deps, stack) (projectName, moduleName, pos) ->
               let deps = (projectName, moduleName) :: deps

               let stack =
                 newDepRequest projectName moduleName moduleInfo.Ref pos
                 :: stack

               deps, stack)
             (deps, stack)

      { ctx with
          ModuleDeps = ctx.ModuleDeps |> TMap.add moduleInfo.Ref deps
          ModuleStack = stack }

// -----------------------------------------------
// Interface
// -----------------------------------------------

/// Starts bundle process.
///
/// You should call `bundleNext` to process requests.
/// Once it returned `NoRequest`, call `bundleFinish`.
let bundleStart () : BundleCtx =
  { Projects = TSet.empty compare
    Modules = TMap.empty compareRef
    ModuleMap = TMap.empty (pairCompare compare compare)

    ModuleStack = []
    ModuleDeps = TMap.empty compareRef }

let bundleFinish (ctx: BundleCtx) : BundleResult =
  assert (ctx.ModuleStack |> List.isEmpty)

  let rec folder (doneSet, acc) (moduleRef, deps) =
    if doneSet |> TSet.contains moduleRef then
      doneSet, acc
    else
      let doneSet = doneSet |> TSet.add moduleRef
      let moduleInfo = ctx.Modules |> mapFind moduleRef

      let doneSet, acc =
        deps
        |> List.choose
             (fun dep ->
               match ctx.ModuleMap |> TMap.tryFind dep with
               | None -> None
               | Some depInfo ->
                   ctx.ModuleDeps
                   |> TMap.tryFind depInfo.Ref
                   |> Option.map (fun deps -> depInfo.Ref, deps))
        |> List.fold folder (doneSet, acc)

      doneSet, moduleInfo :: acc

  let _, acc =
    ctx.ModuleDeps
    |> TMap.fold
         (fun (doneSet, acc) moduleRef deps -> folder (doneSet, acc) (moduleRef, deps))
         (TSet.empty compareRef, [])

  { Modules = List.rev acc }

/// Tries to resolve next request from stack.
let bundleNext (ctx: BundleCtx) : BundleStatus * BundleCtx =
  match ctx.ModuleStack with
  | [] -> NoRequest, ctx

  | r :: stack ->
      match ctx.ModuleMap
            |> TMap.tryFind (r.ProjectName, r.ModuleName) with
      | None -> ModuleInfoRequested r, ctx

      | Some moduleInfo ->
          // Request is resolved.
          let ctx = { ctx with ModuleStack = stack }

          if ctx.ModuleDeps |> TMap.containsKey moduleInfo.Ref then
            // Already bundled.
            bundleNext ctx
          else
            let ctx = ctx |> requestDeps moduleInfo
            ModuleBundled moduleInfo.Ref, ctx

let bundleSkip (ctx: BundleCtx) : BundleCtx =
  match ctx.ModuleStack with
  | [] -> ctx
  | _ :: stack -> { ctx with ModuleStack = stack }

let bundleAddRequest (projectName: ProjectName) (moduleName: ModuleName) (ctx: BundleCtx) : BundleCtx =
  let stack =
    newRootRequest projectName moduleName
    :: ctx.ModuleStack

  { ctx with ModuleStack = stack }

/// Tells module info to the bundler.
let bundleAddModuleInfo (moduleInfo: ModuleInfo) (ctx: BundleCtx) : BundleCtx =
  assert (ctx.Modules
          |> TMap.containsKey moduleInfo.Ref
          |> not)

  { ctx with
      Modules = ctx.Modules |> TMap.add moduleInfo.Ref moduleInfo
      ModuleMap =
        ctx.ModuleMap
        |> TMap.add (moduleInfo.Project, snd moduleInfo.Ref) moduleInfo }

// -----------------------------------------------
// Compatibility
// -----------------------------------------------

// Compatible with old bundler.

let bundleCompatible
  (fetchModule: ProjectName -> ModuleName -> (DocId * ARoot * (string * Pos) list) option)
  (entryProjectName: string)
  =
  let rec go (serial: int) errorAcc bundleCtx =
    let status, bundleCtx = bundleNext bundleCtx

    match status with
    | NoRequest -> bundleFinish bundleCtx, errorAcc

    | ModuleInfoRequested r ->
        let projectName = r.ProjectName
        let moduleName = r.ModuleName

        // Fetch module.
        let moduleInfoOpt, serial, errorAcc =
          match fetchModule projectName moduleName with
          | None -> None, serial, errorAcc

          | Some (docId, ast, errors) ->
              let serial = serial + 1

              let moduleInfo : ModuleInfo =
                { Ref = (serial, moduleName)
                  Project = projectName
                  DocId = docId
                  AstOpt = Some ast }

              let errorAcc =
                errors
                |> List.fold (fun errorAcc (msg, (y, x)) -> (msg, Loc(docId, y, x)) :: errorAcc) errorAcc

              Some moduleInfo, serial, errorAcc

        // Tell or discard.
        match moduleInfoOpt with
        | None ->
            let errorAcc =
              if r.Optional then
                errorAcc
              else
                let originLoc =
                  match r.OriginOpt with
                  | None -> Loc(entryProjectName, 0, 0)
                  | Some (moduleRef, (y, x)) -> Loc(snd moduleRef, y, x)

                ("Module not found.", originLoc) :: errorAcc

            go serial errorAcc (bundleSkip bundleCtx)

        | Some moduleInfo -> go serial errorAcc (bundleAddModuleInfo moduleInfo bundleCtx)

    | ModuleBundled _ -> go serial errorAcc bundleCtx

  let bundleResult, errors =
    bundleStart ()
    |> bundleAddRequest entryProjectName entryProjectName
    |> go 0 []

  let moduleAcc, nameCtx =
    bundleResult.Modules
    |> List.fold
         (fun (moduleAcc, nameCtx) (moduleInfo: ModuleInfo) ->
           match moduleInfo.AstOpt with
           | None -> moduleAcc, nameCtx

           | Some ast ->
               let docId : DocId = snd moduleInfo.Ref
               let exprs, nameCtx = astToHir moduleInfo.Project docId (ast, nameCtx)
               exprs :: moduleAcc, nameCtx)
         ([], nameCtxEmpty ())

  let exprs = moduleAcc |> List.rev |> List.collect id

  exprs, nameCtx, errors
