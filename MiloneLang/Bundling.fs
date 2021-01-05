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

type private ProjectName = string

type private ModuleName = string

// -----------------------------------------------
// BundleCtx
// -----------------------------------------------

type ModuleSyntaxData = DocId * ARoot * (string * Pos) list

[<NoEquality; NoComparison>]
type BundleHost =
  {
    /// External project references.
    ProjectRefs: ProjectName list

    /// Requests the host to load a module.
    ///
    /// The host should locate the module and retrieve its source code, tokenize and parse if exists.
    FetchModule: ProjectName -> ModuleName -> ModuleSyntaxData option }

[<NoEquality; NoComparison>]
type private BundleCtx =
  { NameCtx: NameCtx

    /// Modules to be opened.
    ModuleQueue: (ProjectName * ModuleName) list

    /// Processed module.
    ModuleAcc: HExpr list list

    /// Errors occurred while processing.
    ErrorAcc: (string * Loc) list

    /// Set of modules already fetched.
    FetchMemo: AssocSet<ProjectName * ModuleName>

    Host: BundleHost }

let private newCtx host: BundleCtx =
  { NameCtx = nameCtxEmpty ()
    ModuleQueue = []
    ModuleAcc = []
    ErrorAcc = []
    FetchMemo = setEmpty (pairCmp compare compare)
    Host = host }

let private addError msg loc (ctx: BundleCtx) =
  { ctx with
      ErrorAcc = (msg, loc) :: ctx.ErrorAcc }

// -----------------------------------------------
// Routines
// -----------------------------------------------

/// Returns (true, _, _) if already fetched.
let private fetchModuleWithMemo projectName moduleName (ctx: BundleCtx) =
  if ctx.FetchMemo
     |> setContains (projectName, moduleName) then
    true, None, ctx
  else
    let ctx =
      { ctx with
          FetchMemo = ctx.FetchMemo |> setAdd (projectName, moduleName) }

    let result =
      ctx.Host.FetchModule projectName moduleName

    false, result, ctx

let private doLoadModule docId ast errors (ctx: BundleCtx) =
  let expr, ctx =
    let expr, nameCtx = astToHir docId (ast, ctx.NameCtx)

    let errorAcc =
      List.append
        ctx.ErrorAcc
        (errors
         |> List.map (fun (msg, (y, x)) -> msg, (docId, y, x)))

    let ctx =
      { ctx with
          NameCtx = nameCtx
          ErrorAcc = errorAcc }

    expr, ctx

  // Open dependent modules if no error.
  let ctx =
    if errors |> List.isEmpty then
      ast
      |> findDependentModules
      |> List.fold (fun ctx (projectName, moduleName, _) -> ctx |> requireModule docId projectName moduleName) ctx
    else
      ctx

  // Append this module after dependent ones.
  { ctx with
      ModuleAcc = expr :: ctx.ModuleAcc }

/// Requires a module to load.
let private requireModule docId projectName moduleName (ctx: BundleCtx) =
  match ctx |> fetchModuleWithMemo projectName moduleName with
  | true, _, _ -> ctx

  | false, Some (docId, ast, errors), ctx -> ctx |> doLoadModule docId ast errors

  | false, None, ctx ->
      let msg =
        "Module not found: "
        + projectName
        + "."
        + moduleName

      ctx |> addError msg (docId, 0, 0)

/// Returns None if no module is load.
let bundleProgram (host: BundleHost) (projectName: string): (HExpr list * NameCtx * (string * Loc) list) option =
  let ctx = newCtx host

  // HACK: Load "MiloneOnly" module of projects if exists.
  let ctx =
    (List.append host.ProjectRefs [ projectName ])
    |> List.fold
         (fun ctx projectName ->
           match ctx
                 |> fetchModuleWithMemo projectName "MiloneOnly" with
           | false, Some (docId, ast, errors), ctx -> ctx |> doLoadModule docId ast errors

           | _ -> ctx)
         ctx

  // Load entrypoint module of the project.
  match ctx |> fetchModuleWithMemo projectName projectName with
  | false, Some (docId, ast, errors), ctx ->
      let ctx = ctx |> doLoadModule docId ast errors

      let expr =
        ctx.ModuleAcc |> List.rev |> List.collect id

      Some(expr, ctx.NameCtx, ctx.ErrorAcc)

  | _ ->
      // If failed to load entrypoint, we don't have any DocId or Loc, so we can't report any errors.
      None
