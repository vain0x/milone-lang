/// # Bundling
///
/// Bundles modules. Resolves dependencies over modules
/// and merges modules into single HIR expression.
///
/// ## Statements as dependency specification
///
/// In F#, a project file (.fsproj) describes the member modules, their ordering
/// and external project/package references.
///
/// In milone-lang, `open`/`module` statements work as dependency for now.
///
/// When a module X has a statement `open P.M`,
/// where P is project name and M is module name,
/// such module `P.M` is also a member of the project,
/// and `P.M` should be earlier than X in the project.
///
/// `module Y = P.M` (module synonym) has same effect too.
///
/// Where the project `P` come from, is not specified here.
/// Instead, this module just uses a function `FetchModule`,
/// provided by the caller, to load a module.
/// See `Cli.fs` for its implementation.
///
/// ## Dependency Resolution Algorithm
///
/// Dependency resolution is just a topological sort.
///
/// Starting from a module that is specified by the user,
/// recursively loads modules based on statements described above.
///
/// ## Example
///
/// Assume we want to compile this module.
///
/// ```fsharp
/// open MiloneLang.SyntaxParse
///
/// let main _ = 0
/// ```
///
/// Since this opens `MiloneLang.SyntaxParse`,
/// the bundler finds `SyntaxParse.fs` (some where),
/// load, tokenize, and parse.
///
/// Assume `SyntaxParse` has another open statement.
///
/// ```fsharp
/// // SyntaxParse.fs
/// open MiloneLang.SyntaxTokenize
///
/// let parse () = 0
/// ```
///
/// Bundler finds `SyntaxTokenize.fs` and parse.
///
/// ```fsharp
/// // SyntaxTokenize.fs
/// let tokenize () = 0
/// ```
///
/// Finally these modules are merged in the order.
///
/// ```fsharp
/// let tokenize () = 0 // from Lexing.fs
/// let parse () = 0 // from SyntaxParse.fs
/// let main _ = 0 // from entrypoint module
/// ```
module rec MiloneLang.Bundling

open MiloneLang.AstToHir
open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir

module S = MiloneStd.StdString

type private ProjectName = string

type private ModuleName = string

/// Document location.
type private DocLoc = ProjectName * ModuleName

// -----------------------------------------------
// Public types
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectOption =
  | Ref of projectDir: string
  | AliasedRef of projectName: string * projectDir: string

// type ProjectSchema =
//   { Name: string
//     Options: (ProjectOption * Pos) list }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectSchemaResult =
  { Name: string
    Options: (ProjectOption * Pos) list }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectInput = { ProjectName: ProjectName }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectSchemaInput =
  { ProjectName: ProjectName

    /// DocId for schema file.
    DocId: DocId

    Refs: (ProjectName * Pos) list }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleInput =
  { ProjectName: ProjectName
    ModuleName: ModuleName
    DocId: DocId
    AstOpt: ARoot option }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleRequest =
  | ProjectSchema of ProjectName
  | Module of DocLoc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleError =
  | ProjectNotFound
  | ModuleNotFound
  | RecursiveDependency

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleResult =
  { Exprs: HExpr list
    NameCtx: NameCtx
    Errors: (BundleError * Loc) list }

let bundleErrorToString error =
  match error with
  | BundleError.ProjectNotFound -> "Project not found."
  | BundleError.ModuleNotFound -> "Module not found."
  | BundleError.RecursiveDependency -> "Module dependency forms a cycle."

// -----------------------------------------------
// Project schema evaluator
// -----------------------------------------------

let evalProjectSchema projectName ast : ProjectSchemaResult option =
  let asProjectRef expr : (ProjectOption * Pos) option =
    match expr with
    | ABinaryExpr (AppBinary, AIdentExpr ("Ref", pos), ALitExpr (StrLit projectDir, _), _) ->
      Some(ProjectOption.Ref projectDir, pos)

    | ABinaryExpr (AppBinary,
                   AIdentExpr ("AliasedRef", pos),
                   ATupleExpr ([ ALitExpr (StrLit projectName, _); ALitExpr (StrLit projectDir, _) ], _),
                   _) -> Some(ProjectOption.AliasedRef(projectName, projectDir), pos)

    | _ -> None

  let asProjectSchema decl =
    match decl with
    | AExprDecl (ARecordExpr (None, fields, _)) ->
      match fields
            |> List.tryFind (fun (name, _, _) -> name = "Options")
        with
      | Some (_, AListExpr (items, _), _) -> items |> List.choose asProjectRef |> Some
      | _ -> None

    | _ -> None

  let decls =
    match ast with
    | AExprRoot decls -> decls
    | AModuleRoot (_, decls, _) -> decls

  match decls |> List.tryPick asProjectSchema with
  | None -> None
  | Some options ->
    let schema: ProjectSchemaResult =
      { Name = projectName
        Options = options }

    Some schema

// -----------------------------------------------
// Bundle API
// -----------------------------------------------

// private
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleData =
  { DocId: DocId
    AstOpt: ARoot option
    Dependencies: (ProjectName * ModuleName * Pos) list }

// private
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectData =
  { Modules: AssocMap<ModuleName, ModuleData>
    SchemaDocIdOpt: DocId option
    Refs: (ProjectName * Pos) list }

// wants make fields private
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Bundle =
  { Projects: AssocMap<ProjectName, ProjectData>
    Modules: AssocMap<DocLoc, ModuleData>
    RequestAcc: BundleRequest list }

let bundleNew () : Bundle =
  { Projects = mapEmpty compare
    Modules = mapEmpty (pairCmp compare compare)
    RequestAcc = [] }

/// Adds a project to be bundled, if not exists.
let bundleAddProject (input: ProjectInput) (bundle: Bundle) : Bundle =
  match bundle.Projects |> mapTryFind input.ProjectName with
  | Some _ -> bundle

  | None ->
    let projectData: ProjectData =
      { Modules = mapEmpty compare
        SchemaDocIdOpt = None
        Refs = [] }

    // HACK: Automatically request a module, named "MiloneOnly", to be bundled.
    let miloneOnlyRequest =
      BundleRequest.Module(input.ProjectName, "MiloneOnly")

    let entryModuleRequest =
      BundleRequest.Module(input.ProjectName, input.ProjectName)

    { bundle with
        Projects =
          bundle.Projects
          |> mapAdd input.ProjectName projectData
        RequestAcc =
          miloneOnlyRequest
          :: entryModuleRequest
             :: BundleRequest.ProjectSchema input.ProjectName
                :: bundle.RequestAcc }

let bundleAddSchema (input: ProjectSchemaInput) (bundle: Bundle) =
  match bundle.Projects |> mapTryFind input.ProjectName with
  | None -> bundle

  | Some projectData when projectData.SchemaDocIdOpt |> Option.isSome -> bundle

  | Some projectData ->
    { bundle with
        Projects =
          bundle.Projects
          |> mapAdd
               input.ProjectName
               { projectData with
                   Refs = input.Refs
                   SchemaDocIdOpt = Some input.DocId } }

let bundleAddModule (input: ModuleInput) (bundle: Bundle) =
  if
    bundle.Modules
    |> mapContainsKey (input.ProjectName, input.ModuleName)
  then
    bundle
  else
    let dependencies =
      match input.AstOpt with
      | Some ast -> findDependentModules ast
      | None -> []

    let moduleData: ModuleData =
      { DocId = input.DocId
        AstOpt = input.AstOpt
        Dependencies = dependencies }

    let requests =
      dependencies
      |> List.fold
           (fun acc (projectName, moduleName, _) ->
             BundleRequest.Module(projectName, moduleName)
             :: acc)
           bundle.RequestAcc

    { bundle with
        Modules =
          bundle.Modules
          |> mapAdd (input.ProjectName, input.ModuleName) moduleData
        RequestAcc = requests }

let bundleTakeRequests (bundle: Bundle) : BundleRequest list * Bundle =
  // remove duplicated requests?
  let requests, bundle =
    bundle.RequestAcc, { bundle with RequestAcc = [] }

  // if schema request exists, module requests should not be taken

  // remove unnecessary requests
  let requests =
    requests
    |> List.filter (fun request ->
      match request with
      | BundleRequest.ProjectSchema projectName ->
        match bundle.Projects |> mapTryFind projectName with
        | Some projectData -> projectData.SchemaDocIdOpt |> Option.isNone
        | None -> false

      | BundleRequest.Module (projectName, moduleName) ->
        bundle.Modules
        |> mapContainsKey (projectName, moduleName)
        |> not)

  requests, bundle

let bundleProcess (bundle: Bundle) : BundleResult = newCtx bundle |> doBundle |> toResult

// -----------------------------------------------
// BundleCtx
// -----------------------------------------------

// Bundle DFS routine.

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Status =
  | Processing
  | Done

[<NoEquality; NoComparison>]
type private BundleCtx =
  { NameCtx: NameCtx
    ModuleQueue: (ProjectName * ModuleName * Pos) list
    ModuleAcc: HExpr list list
    ErrorAcc: (BundleError * Loc) list
    ProcessMap: AssocMap<DocLoc, Status>
    Bundle: Bundle }

let private newCtx bundle : BundleCtx =
  { NameCtx = nameCtxEmpty ()
    ModuleQueue = []
    ModuleAcc = []
    ErrorAcc = []
    ProcessMap = mapEmpty (pairCmp compare compare)
    Bundle = bundle }

let private toResult (ctx: BundleCtx) : BundleResult =
  { Exprs = ctx.ModuleAcc |> List.rev |> List.collect id
    NameCtx = ctx.NameCtx
    Errors = ctx.ErrorAcc }

let private addError msg loc (ctx: BundleCtx) =
  { ctx with ErrorAcc = (msg, loc) :: ctx.ErrorAcc }

let private doMarkingAsProcessing docId (f: BundleCtx -> BundleCtx) (ctx: BundleCtx) =
  let ctx =
    { ctx with ProcessMap = ctx.ProcessMap |> mapAdd docId Status.Processing }

  let ctx = f ctx
  { ctx with ProcessMap = ctx.ProcessMap |> mapAdd docId Status.Done }

let private requireModule projectName moduleName (ctx: BundleCtx) : BundleCtx =
  match
    ctx.ProcessMap
    |> mapTryFind (projectName, moduleName)
    with
  | Some Status.Done -> ctx

  | Some Status.Processing ->
    printfn "/* cyclic dependencies involved in %s.%s */" projectName moduleName
    // recursive dependency
    ctx

  | None ->
    match
      ctx.Bundle.Modules
      |> mapTryFind (projectName, moduleName)
      with
    | None ->
      // not found?
      printfn "/* module not found: %s.%s */" projectName moduleName
      ctx

    | Some moduleData ->
      let ctx =
        ctx
        |> doMarkingAsProcessing (projectName, moduleName) (fun ctx ->
          moduleData.Dependencies
          |> List.fold
               (fun (ctx: BundleCtx) (projectName, moduleName, pos) ->
                 // duplicated?
                 match
                   ctx.Bundle.Modules
                   |> mapTryFind (projectName, moduleName)
                   with
                 | Some _ -> ctx |> requireModule projectName moduleName

                 | None ->
                   let y, x = pos
                   let loc: Loc = moduleData.DocId, y, x
                   ctx |> addError BundleError.ModuleNotFound loc)
               ctx)

      // Add to bundled program.
      match moduleData.AstOpt with
      | None -> ctx
      | Some ast ->
        let exprs, nameCtx =
          astToHir moduleData.DocId (ast, ctx.NameCtx)

        { ctx with
            ModuleAcc = exprs :: ctx.ModuleAcc
            NameCtx = nameCtx }

let private doBundle (ctx: BundleCtx) : BundleCtx =
  // HACK: "MiloneOnly" must be first.
  let ctx =
    ctx.Bundle.Projects
    |> mapFold (fun ctx projectName (_: ProjectData) -> ctx |> requireModule projectName "MiloneOnly") ctx

  ctx.Bundle.Modules
  |> mapFold (fun ctx (projectName, moduleName) (_: ModuleData) -> ctx |> requireModule projectName moduleName) ctx
