/// Merges modules into single expression.
///
/// ## Algorithm
///
/// At first a module that is an entry point is given.
///
/// Whenever a module is given, open and parse the file
/// and collect `open` declarations. For each `open`,
/// we find the corresponding source file and load it first.
///
/// Sort the loaded modules in the topological order
/// (i.e. opened modules first, opening modules last)
/// and merge them.
///
/// FIXME: Currently, this stage breaks the privacy of modules.
///   Some definitions in upstream modules may become visible
///   to down stream modules without explicit `open`s.
///
/// ## Example
///
/// If the following module file is given:
///
/// ```fsharp
/// open MiloneLang.Parsing
///
/// let main _ = 0
/// ```
///
/// and then find the `Parsing.fs`.
///
/// ```fsharp
/// // Parsing.fs
/// open MiloneLang.Lexing
///
/// let parse () = 0
/// ```
///
/// Similarly, find the `Lexing.fs` because of the `open` declaration.
///
/// ```fsharp
/// // Lexing.fs
/// let tokenize () = 0
/// ```
///
/// Finally merge them in the order.
///
/// ```fsharp
/// let tokenize () = 0 in
/// let parse () = 0 in
/// let main _ = 0
/// ```
module rec MiloneLang.Bundling

open MiloneLang.AstToHir
open MiloneLang.Helpers
open MiloneLang.Lexing
open MiloneLang.Parsing
open MiloneLang.Types

let private openKindToInt openKind =
  match openKind with
  | CoreModule -> 1
  | ProjectModule -> 2

let private openKindHash openKind = intHash (openKindToInt openKind)

let private openKindCmp l r = (openKindToInt l) - (openKindToInt r)

let private keyHash (openKind, moduleName) =
  intHash (openKindToInt openKind)
  |> hashCombine (strHash moduleName)

let private keyCmp (l1, l2) (r1, r2) =
  let c = openKindCmp l1 r1
  if c <> 0 then c else strCmp l2 r2

let findOpenPaths expr =
  let rec go expr =
    match expr with
    | HOpenExpr (path, _) -> [ path ]
    | HInfExpr (InfOp.Semi, exprs, _, _) -> exprs |> listCollect go
    | HModuleExpr (_, body, _, _) -> go body
    | _ -> []

  go expr

let findOpenModules projectName expr =
  let extractor path =
    match path with
    | prefix :: moduleName :: _ when prefix = projectName -> Some(ProjectModule, moduleName)
    | [ "MiloneCore"; moduleName ] -> Some(CoreModule, moduleName)
    | _ -> None

  findOpenPaths expr |> listChoose extractor

/// Insert the second expression to the bottom of the first expression.
/// This is bad way because of variable capturing issues.
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

let parseProjectModules readCoreFile readModuleFile parse projectName nameCtx =
  let addModule go (moduleAcc, moduleMap, nameCtx, errorAcc) (openKind, moduleName) source =
    // FIXME: provide unique ID?
    let docId: DocId = moduleName
    let tokens = tokenize source
    let moduleAst, errors = parse moduleName tokens
    let moduleHir, nameCtx = astToHir docId (moduleAst, nameCtx)
    let dependencies = findOpenModules projectName moduleHir

    let moduleMap =
      moduleMap
      |> mapAdd (openKind, moduleName) moduleHir

    let errors: (string * Loc) list =
      errors
      |> listMap (fun (msg: string, pos: Pos) ->
           let row, column = pos
           let loc = docId, row, column
           msg, loc)

    let moduleAcc, moduleMap, nameCtx, errorAcc =
      listFold go (moduleAcc, moduleMap, nameCtx, errorAcc) dependencies

    moduleHir :: moduleAcc, moduleMap, nameCtx, errors :: errorAcc

  let rec go (moduleAcc, moduleMap, nameCtx, errorAcc) (openKind, moduleName) =
    if moduleMap |> mapContainsKey (openKind, moduleName) then
      moduleAcc, moduleMap, nameCtx, errorAcc
    else
      let source =
        match openKind with
        | CoreModule -> readCoreFile moduleName

        | ProjectModule ->
            match readModuleFile moduleName with
            | Some it -> it
            | None -> failwithf "File missing for module '%s'" moduleName

      addModule go (moduleAcc, moduleMap, nameCtx, errorAcc) (openKind, moduleName) source

  // Initial state.
  let ctx =
    ([], mapEmpty (keyHash, keyCmp), nameCtx, [])

  // Add polyfills module to the project if exists.
  let ctx =
    match readModuleFile "Polyfills" with
    | Some source ->
        addModule (fun _ _ -> failwith "Polyfills don't have open.") ctx (ProjectModule, "Polyfills") source

    | None -> ctx

  // Start dependency resolution from entry-point module.
  let ctx = go ctx (ProjectModule, projectName)

  // Finish.
  let moduleAcc, _, nameCtx, errorAcc = ctx
  let modules = moduleAcc |> List.rev
  listReduce spliceExpr modules, nameCtx, errorAcc
