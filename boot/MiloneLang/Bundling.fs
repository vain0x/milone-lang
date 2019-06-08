module MiloneLang.Bundling

open MiloneLang.AstToHir
open MiloneLang.Helpers

let findOpenPaths expr =
  let rec go expr =
    match expr with
    | HExpr.Open (path, _) ->
      [path]
    | HExpr.Inf (InfOp.AndThen, exprs, _, _) ->
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
    | HExpr.LetFun (ident, serial, args, body, next, ty, loc) ->
      let next = go next
      HExpr.LetFun (ident, serial, args, body, next, ty, loc)
    | HExpr.Inf (InfOp.AndThen, exprs, ty, loc) ->
      let rec goLast exprs =
        match exprs with
        | [] ->
          [secondExpr]
        | [lastExpr] ->
          [go lastExpr]
        | x :: xs ->
          x :: goLast xs
      let exprs = goLast exprs
      HExpr.Inf (InfOp.AndThen, exprs, ty, loc)
    | _ ->
      hxAndThen [expr; secondExpr] (0, 0)
  go firstExpr

let parseProjectModules readModuleFile projectName =
  let rec go moduleAcc moduleMap moduleName =
    if moduleMap |> Map.containsKey moduleName then
      moduleAcc, moduleMap
    else
      let source = readModuleFile moduleName
      let tokens = Lexing.tokenize source
      let moduleAst = Parsing.parse tokens
      let moduleHir = AstToHir.astToHir moduleAst
      let dependencies = findOpenModules projectName moduleHir
      let moduleMap = moduleMap |> Map.add moduleName moduleHir
      let moduleAcc, moduleMap =
        List.fold (fun (moduleAcc, moduleMap) dep ->
          let moduleAcc, moduleMap = go moduleAcc moduleMap dep
          moduleAcc, moduleMap
        ) (moduleAcc, moduleMap) dependencies
      moduleHir :: moduleAcc, moduleMap

  let moduleAcc, _ = go [] Map.empty projectName
  let modules = moduleAcc |> List.rev

  List.reduce spliceExpr modules
