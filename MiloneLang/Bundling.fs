/// ## Module Bundling
///
/// Resolves dependencies and merges modules into single HIR expression.
///
/// ### `open` statement
///
/// In F#, a project file (.fsproj) describes the member modules, their ordering
/// and external project/package references.
///
/// In milone-lang, `open` statements work as dependency for now.
/// When a module X has a statement `open P.M`,
/// where P is project name and M is module name,
/// such module `P.M` is also a member of the project,
/// and `P.M` should be earlier than X in the project.
///
/// `open` doesn't specify where the project `P` come from.
/// Instead, this module just uses a function `FetchModule`,
/// provided by the caller, to load a module.
/// See `Cli.fs` for its implementation.
///
/// ### Dependency Resolution Algorithm
///
/// Dependency resolution is just a topological sort.
///
/// Starting from a module that is specified by the user,
/// recursively loads modules based on `open` statements
/// as described above.
///
/// ## Example
///
/// Assume we want to compile this module.
///
/// ```fsharp
/// open MiloneLang.Parsing
///
/// let main _ = 0
/// ```
///
/// Since this opens `MiloneLang.Parsing`,
/// the bundler finds `Parsing.fs` (some where),
/// load, tokenize, and parse.
///
/// Assume `Parsing` has another open statement.
///
/// ```fsharp
/// // Parsing.fs
/// open MiloneLang.Lexing
///
/// let parse () = 0
/// ```
///
/// Bundler finds `Lexing.fs` and parse.
///
/// ```fsharp
/// // Lexing.fs
/// let tokenize () = 0
/// ```
///
/// Finally these modules are merged in the order.
///
/// ```fsharp
/// let tokenize () = 0 // from Lexing.fs
/// let parse () = 0 // from Parsing.fs
/// let main _ = 0 // from entrypoint module
/// ```
module rec MiloneLang.Bundling

open MiloneLang.AstToHir
open MiloneLang.Helpers
open MiloneLang.Types

let private findOpenPaths expr =
  let rec go expr =
    match expr with
    | HOpenExpr (path, loc) -> [ path, loc ]
    | HInfExpr (InfOp.Semi, exprs, _, _) -> exprs |> List.collect go
    | HModuleExpr (_, body, _, _) -> go body
    | _ -> []

  go expr

let private findOpenModules expr =
  findOpenPaths expr
  |> List.choose (fun (path, loc) ->
       match path with
       | projectName :: moduleName :: _ -> Some(projectName, moduleName, loc)
       | _ -> None)

/// Insert the second expression to the bottom of the first expression.
/// This is bad way because of variable capturing issues and program size/depth issue.
let spliceExpr firstExpr secondExpr =
  let rec go expr =
    match expr with
    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let next = go next
        HLetValExpr(vis, pat, init, next, ty, loc)
    | HLetFunExpr (serial, vis, isMainFun, args, body, next, ty, loc) ->
        let next = go next
        HLetFunExpr(serial, vis, isMainFun, args, body, next, ty, loc)
    | HInfExpr (InfOp.Semi, exprs, ty, loc) ->
        let rec goLast exprs =
          match exprs with
          | [] -> [ secondExpr ]
          | [ lastExpr ] -> [ go lastExpr ]
          | x :: xs -> x :: goLast xs

        let exprs = goLast exprs
        HInfExpr(InfOp.Semi, exprs, ty, loc)
    | HModuleExpr (ident, body, next, loc) ->
        let next = go next
        HModuleExpr(ident, body, next, loc)
    | _ -> hxSemi [ expr; secondExpr ] noLoc

  go firstExpr

// -----------------------------------------------
// BundleCtx
// -----------------------------------------------

type BundleHost =
  {
    /// Requests the host to load a module.
    ///
    /// The host should locate the module and retrieve its source code, tokenize and parse if exists.
    FetchModule: string -> string -> (DocId * ARoot * (string * Pos) list) option }

type private BundleCtx =
  { NameCtx: NameCtx

    /// Modules to be opened.
    ModuleQueue: (string * string) list

    /// Processed module.
    ModuleAcc: HExpr list

    /// Errors occurred while processing.
    ErrorAcc: (string * Loc) list

    /// Set of modules already fetched.
    FetchMemo: AssocSet<string * string>

    Host: BundleHost }

let private newCtx host: BundleCtx =
  { NameCtx = nameCtxEmpty ()
    ModuleQueue = []
    ModuleAcc = []
    ErrorAcc = []
    FetchMemo = setEmpty (pairHash strHash strHash, pairCmp strCmp strCmp)
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
      let host = ctx.Host // FIXME: A.B.C is unimplemented
      host.FetchModule projectName moduleName

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
      expr
      |> findOpenModules
      |> List.fold (fun ctx (projectName, moduleName, loc) ->
           let docId, _, _ = loc
           ctx |> requireModule docId projectName moduleName) ctx
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
let bundleProgram (host: BundleHost) (projectName: string): (HExpr * NameCtx * (string * Loc) list) option =
  let ctx = newCtx host

  // HACK: Load "./Polyfills" module in the project if exists.
  let ctx =
    match ctx |> fetchModuleWithMemo projectName "Polyfills" with
    | false, Some (docId, ast, errors), ctx -> ctx |> doLoadModule docId ast errors

    | _ -> ctx

  // Load entrypoint module of the project.
  match ctx |> fetchModuleWithMemo projectName projectName with
  | false, Some (docId, ast, errors), ctx ->
      let ctx = ctx |> doLoadModule docId ast errors

      let expr =
        ctx.ModuleAcc
        |> List.rev
        |> List.reduce spliceExpr

      Some(expr, ctx.NameCtx, ctx.ErrorAcc)

  | _ ->
      // If failed to load entrypoint, we don't have any DocId or Loc, so we can't report any errors.
      None
