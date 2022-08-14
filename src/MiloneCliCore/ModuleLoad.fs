// Successor to AstBundle. See also docs/internals/ast_bundle.md

// This pass does an asynchronous recursive process:
//
//    - start from an entrypoint module that is specified by CLI args
//    - load source files and parse them
//    - find dependent modules by loaded ones and enqueue them
//    - do recursively until queue becomes empty.

// This pass is a business of MiloneCli rather than Syntax library
// because details vary on the client.
//
// Consider how the other client, LSP server (say, S), does work in this pass.
//
// - (How to load files)
//    The server has loaded all source files before starting analysis
//    and some of them are modified in the editor.
//    On the other hand, MiloneCli loads files on-demand.
//
// - (Which files to load)
//    The server also loads files that don't have any dependents
//    to check them and report errors to the editor.
//    On the other hand, MiloneCli doesn't want to open unused source files.

module rec MiloneCliCore.ModuleLoad

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError
open Std.StdSet
open Std.StdMap

module S = Std.StdString

type private FetchModuleFun2 =
  ProjectName
    -> ModuleName
    -> Future<(ModuleSyntaxData2 * (ProjectName * ModuleName * Pos) list * ModuleSyntaxError list) option>

// -----------------------------------------------
// ComputeLayer
// -----------------------------------------------

// #computeLayer
/// Splits vertices in a tree into a list of layers.
///
/// Result (list of layers) satisfies a condition:
///   vertices in a layer depend only vertices in strictly lower layers.
let private computeLayer
  (compareVertices: 'T -> 'T -> int)
  (getChildren: 'T -> 'T list)
  (vertices: 'T list)
  : 'T list list =
  let rec collect prevSet (okAcc: 'T list, ngAcc: 'T list) (v: 'T) =
    assert (TSet.contains v prevSet |> not)

    let ok =
      getChildren v
      |> List.forall (fun u -> TSet.contains u prevSet)

    if ok then
      v :: okAcc, ngAcc
    else
      okAcc, v :: ngAcc

  let rec go prevSet (rest: 'T list) (acc: 'T list list) =
    if List.isEmpty rest then
      List.rev acc
    else
      let okAcc, ngAcc =
        rest |> List.fold (collect prevSet) ([], [])

      assert (List.isEmpty okAcc |> not) // Cyclic dependencies might exist.

      let prevSet =
        List.fold (fun prevSet v -> TSet.add v prevSet) prevSet okAcc

      go prevSet ngAcc (okAcc :: acc)

  go (TSet.empty compareVertices) vertices []

// -----------------------------------------------
// Types
// -----------------------------------------------

type private SyntaxError = string * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ModuleRequest =
  { ProjectName: ProjectName
    ModuleName: ModuleName
    Origin: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ModuleData =
  { Name: ModuleName
    Project: ProjectName
    SyntaxData: ModuleSyntaxData2
    Deps: ModuleRequest list
    Errors: SyntaxError list }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RequestResult =
  | Requested
  | Resolved of ModuleData
  | Failed

type private RequestMap = TreeMap<ProjectName * ModuleName, RequestResult>

// note: avoid using this function so that DocId can be computed by clients.
let computeDocId (p: ProjectName) (m: ModuleName) : DocId = Symbol.intern (p + "." + m)

// -----------------------------------------------
// ModuleRequest
// -----------------------------------------------

let private newRootRequest (docId: DocId) (p: ProjectName) (m: ModuleName) : ModuleRequest =
  { ProjectName = p
    ModuleName = m
    Origin = Loc(docId, 0, 0) }

let private newDepRequest (p: ProjectName) (m: ModuleName) (originLoc: Loc) : ModuleRequest =
  { ProjectName = p
    ModuleName = m
    Origin = originLoc }

let private requestToNotFoundError (r: ModuleRequest) : SyntaxError = "Module not found.", r.Origin

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private State =
  { RequestMap: RequestMap
    Errors: SyntaxError list }

let private initialState: State =
  { RequestMap = TMap.empty (pairCompare compare compare)
    Errors = [] }

let private addRequest (state: State) (request: ModuleRequest) : ModuleRequest option * State =
  let requestMap = state.RequestMap
  let key = request.ProjectName, request.ModuleName

  if not (TMap.containsKey key requestMap) then
    let state =
      { state with RequestMap = TMap.add key RequestResult.Requested requestMap }

    Some request, state
  else
    None, state

let private toModules (state: State) : ModuleData list =
  state.RequestMap
  |> TMap.toList
  |> List.choose (fun (_, r: RequestResult) ->
    match r with
    | RequestResult.Resolved moduleData -> Some moduleData
    | RequestResult.Failed -> None
    | RequestResult.Requested -> unreachable ())

let private toErrors (state: State) : SyntaxError list =
  state
  |> toModules
  |> List.collect (fun (m: ModuleData) -> m.Errors)
  |> List.append state.Errors

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Action =
  | DidFetchOk of ModuleData
  | DidFetchFail of ModuleRequest

let private consumer (state: State) action : State * ModuleRequest list =
  let requestMap = state.RequestMap

  match action with
  | Action.DidFetchOk m ->
    let key = m.Project, m.Name

    match TMap.tryFind key requestMap with
    | Some RequestResult.Requested ->
      let state =
        { state with RequestMap = TMap.add key (RequestResult.Resolved m) requestMap }

      let requests, state = m.Deps |> List.mapFold addRequest state

      state, List.choose id requests

    | _ -> unreachable ()

  | Action.DidFetchFail request ->
    let key = request.ProjectName, request.ModuleName

    match TMap.tryFind key requestMap with
    | Some RequestResult.Requested ->
      let requestMap =
        TMap.add key RequestResult.Failed requestMap

      let errors =
        requestToNotFoundError request :: state.Errors

      let state =
        { state with
            RequestMap = requestMap
            Errors = errors }

      state, []

    | _ -> unreachable ()

let private producer (fetchModule: FetchModuleFun2) (_: State) (r: ModuleRequest) : Future<Action> =
  fetchModule r.ProjectName r.ModuleName
  |> Future.map (fun result ->
    match result with
    | Some ((syntaxData: ModuleSyntaxData2), dependentModules, errors) ->
      let docId = syntaxData.DocId

      let deps =
        dependentModules
        |> List.map (fun (projectName, moduleName, pos) ->
          let originLoc =
            let y, x = pos
            Loc(docId, y, x)

          newDepRequest projectName moduleName originLoc)

      let errors =
        errors
        |> List.map (fun (msg, (y, x)) -> (msg, Loc(docId, y, x)))

      let m: ModuleData =
        { Name = r.ModuleName
          Project = r.ProjectName
          SyntaxData = syntaxData
          Deps = deps
          Errors = errors }

      Action.DidFetchOk m

    | None -> Action.DidFetchFail r)

// -----------------------------------------------
// Interface
// -----------------------------------------------

type LoadResult = ModuleSyntaxData2 list list * SyntaxError list

let load (fetchModule: FetchModuleFun2) (entryProjectName: ProjectName) : LoadResult =
  let entryRequest =
    let p = entryProjectName
    let docId = computeDocId p p
    newRootRequest docId p p

  let state = initialState
  let _, state = addRequest state entryRequest

  let state =
    mpscConcurrent consumer (producer fetchModule) state [ entryRequest ]

  let layers =
    let comparer (l: ModuleData) (r: ModuleData) =
      Symbol.compare l.SyntaxData.DocId r.SyntaxData.DocId

    let getDeps (m: ModuleData) =
      m.Deps
      |> List.choose (fun (r: ModuleRequest) ->
        match TMap.tryFind (r.ProjectName, r.ModuleName) state.RequestMap with
        | Some (RequestResult.Resolved m) -> Some m
        | _ -> None)

    state
    |> toModules
    |> computeLayer comparer getDeps
    |> List.map (fun layer ->
      layer
      |> List.map (fun (m: ModuleData) ->
        ({ ProjectName = m.Project
           ModuleName = m.Name
           DocId = m.SyntaxData.DocId
           Ast = m.SyntaxData.Ast }: ModuleSyntaxData2)))

  let errors = state |> toErrors

  layers, errors
