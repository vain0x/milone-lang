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
module MiloneLang.Bundling

open MiloneLang.AstToHir
open MiloneLang.Types
open MiloneLang.Helpers

let findOpenPaths expr =
  let rec go expr =
    match expr with
    | HExpr.Open (path, _) ->
      [path]
    | HExpr.Inf (InfOp.Semi, exprs, _, _) ->
      exprs |> List.collect go
    | _ ->
      []
  go expr

let findOpenModules projectName expr =
  let extractor path =
    match path with
    | prefix :: moduleName :: _ when prefix = projectName ->
      Some moduleName
    | _ ->
      None
  findOpenPaths expr |> List.choose extractor

/// Insert the second expression to the bottom of the first expression.
/// This is bad way because of variable capturing issues.
let spliceExpr firstExpr secondExpr =
  let rec go expr =
    match expr with
    | HExpr.Let (pat, init, next, ty, loc) ->
      let next = go next
      HExpr.Let (pat, init, next, ty, loc)
    | HExpr.LetFun (ident, serial, isMainFun, args, body, next, ty, loc) ->
      let next = go next
      HExpr.LetFun (ident, serial, isMainFun, args, body, next, ty, loc)
    | HExpr.Inf (InfOp.Semi, exprs, ty, loc) ->
      let rec goLast exprs =
        match exprs with
        | [] ->
          [secondExpr]
        | [lastExpr] ->
          [go lastExpr]
        | x :: xs ->
          x :: goLast xs
      let exprs = goLast exprs
      HExpr.Inf (InfOp.Semi, exprs, ty, loc)
    | _ ->
      hxSemi [expr; secondExpr] noLoc
  go firstExpr

let parseProjectModules readModuleFile projectName nameCtx =
  let rec go (moduleAcc, moduleMap, nameCtx) moduleName =
    if moduleMap |> Map.containsKey moduleName then
      moduleAcc, moduleMap, nameCtx
    else
      let source = readModuleFile moduleName
      let tokens = Lexing.tokenize source
      let moduleAst = Parsing.parse tokens
      let moduleHir, nameCtx = AstToHir.astToHir (moduleAst, nameCtx)
      let dependencies = findOpenModules projectName moduleHir
      let moduleMap = moduleMap |> Map.add moduleName moduleHir
      let moduleAcc, moduleMap, nameCtx =
        List.fold go (moduleAcc, moduleMap, nameCtx) dependencies
      moduleHir :: moduleAcc, moduleMap, nameCtx

  let moduleAcc, _, nameCtx = go ([], Map.empty, nameCtx) projectName
  let modules = moduleAcc |> List.rev

  List.reduce spliceExpr modules, nameCtx
