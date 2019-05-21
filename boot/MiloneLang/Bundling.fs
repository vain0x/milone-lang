module MiloneLang.Bundling

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

let parseProjectModules readModuleFile projectName =
  let rec go moduleAcc moduleMap moduleName =
    if moduleMap |> Map.containsKey moduleName then
      moduleAcc, moduleMap
    else
      let source = readModuleFile moduleName
      let tokens = Lexing.tokenize source
      let moduleAst = Parsing.parse tokens
      let dependencies = findOpenModules projectName moduleAst
      let moduleMap = moduleMap |> Map.add moduleName moduleAst
      let moduleAcc, moduleMap =
        List.fold (fun (moduleAcc, moduleMap) dep ->
          let moduleAcc, moduleMap = go moduleAcc moduleMap dep
          moduleAcc, moduleMap
        ) ([], moduleMap) dependencies
      moduleAst :: moduleAcc, moduleMap

  let moduleAcc, _ = go [] Map.empty projectName
  let modules = moduleAcc |> List.rev

  MiloneLang.Helpers.hxAndThen modules (0, 0)
