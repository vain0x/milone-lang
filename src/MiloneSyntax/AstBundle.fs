/// # AST Bundle
///
/// Resolves dependencies between modules.
/// This stage determines the set of modules in the project and the ordering of them.
///
/// These modules are combined into single HIR expression.
module rec MiloneSyntax.AstBundle

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.AstToHir
open MiloneSyntax.Syntax
open MiloneSyntax.Tir

module TSet = MiloneStd.StdSet
module TMap = MiloneStd.StdMap
module S = MiloneStd.StdString

// -----------------------------------------------
// Utils
// -----------------------------------------------

let private topologicalSort
  (compareVertices: 'T -> 'T -> int)
  (getChildren: 'T -> 'T list)
  (vertices: 'T list)
  : 'T list =
  let rec folder (doneSet, acc: 'T list) (v: 'T) =
    if TSet.contains v doneSet then
      doneSet, acc
    else
      let doneSet = TSet.add v doneSet

      let doneSet, acc =
        List.fold folder (doneSet, acc) (getChildren v)

      doneSet, v :: acc

  let _, acc =
    let doneSet = TSet.empty compareVertices
    vertices |> List.fold folder (doneSet, [])

  List.rev acc

// -----------------------------------------------
// Types
// -----------------------------------------------

type private ProjectName = string
type private ModuleName = string
type private Error = string * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ModuleRequest =
  { ProjectName: ProjectName
    ModuleName: ModuleName
    Origin: Loc
    Optional: bool }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ModuleData =
  { Name: ModuleName
    Project: ProjectName
    DocId: DocId
    Ast: ARoot
    Deps: ModuleRequest list
    SymbolCount: SymbolCount
    Errors: Error list }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RequestResult =
  | Requested
  | Resolved of ModuleData
  | Failed

type private RequestMap = TMap.TreeMap<ProjectName * ModuleName, RequestResult>

// note: avoid using this function so that DocId can be computed by clients.
let computeDocId (p: ProjectName) (m: ModuleName) : DocId = p + "." + m

// -----------------------------------------------
// ModuleRequest
// -----------------------------------------------

let private newRootRequest (docId: DocId) (p: ProjectName) (m: ModuleName) : ModuleRequest =
  { ProjectName = p
    ModuleName = m
    Origin = Loc(docId, 0, 0)
    Optional = false }

let private newMiloneOnlyRequest (p: ProjectName) (originDocId: DocId) : ModuleRequest =
  { ProjectName = p
    ModuleName = "MiloneOnly"
    Origin = Loc(originDocId, 0, 0)
    Optional = true }

let private newDepRequest (p: ProjectName) (m: ModuleName) (originLoc: Loc) : ModuleRequest =
  { ProjectName = p
    ModuleName = m
    Origin = originLoc
    Optional = false }

let private requestToNotFoundError (r: ModuleRequest) : Error option =
  if not r.Optional then
    Some("Module not found.", r.Origin)
  else
    None

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private State =
  { RequestMap: RequestMap
    Errors: Error list }

let private initialState: State =
  { RequestMap = TMap.empty (pairCompare compare compare)
    Errors = [] }

let private addRequest (state: State) (request: ModuleRequest) : ModuleRequest option * State =
  let requestMap = state.RequestMap
  let key = request.ProjectName, request.ModuleName

  if not (TMap.containsKey key requestMap) then
    let state =
      { state with
          RequestMap = TMap.add key RequestResult.Requested requestMap }

    Some request, state
  else
    None, state

let private toModules (state: State) : ModuleData list =
  state.RequestMap
  |> TMap.toList
  |> List.choose
       (fun (_, r: RequestResult) ->
         match r with
         | RequestResult.Resolved moduleData -> Some moduleData
         | RequestResult.Failed -> None
         | RequestResult.Requested -> unreachable ())

let private toErrors (state: State) : Error list =
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
        { state with
            RequestMap = TMap.add key (RequestResult.Resolved m) requestMap }

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
        match requestToNotFoundError request with
        | Some error -> error :: state.Errors
        | None -> state.Errors

      let state =
        { state with
            RequestMap = requestMap
            Errors = errors }

      state, []

    | _ -> unreachable ()

let private producer (fetchModule: FetchModuleFun) (_: State) (r: ModuleRequest) : Future<Action> =
  fetchModule r.ProjectName r.ModuleName
  |> Future.map
       (fun result ->
         match result with
         | Some (docId, ast, errors) ->
           let deps =
             let dep1 =
               if r.ModuleName <> "MiloneOnly" then
                 [ newMiloneOnlyRequest r.ProjectName docId ]
               else
                 []

             let otherDeps =
               findDependentModules ast
               |> List.map
                    (fun (projectName, moduleName, pos) ->
                      let originLoc =
                        let y, x = pos
                        Loc(docId, y, x)

                      newDepRequest projectName moduleName originLoc)

             List.append dep1 otherDeps

           let errors =
             errors
             |> List.map (fun (msg, (y, x)) -> (msg, Loc(docId, y, x)))

           let m: ModuleData =
             { Name = r.ModuleName
               Project = r.ProjectName
               DocId = docId
               Ast = ast
               Deps = deps
               SymbolCount = countSymbols ast
               Errors = errors }

           Action.DidFetchOk m

         | None -> Action.DidFetchFail r)

// -----------------------------------------------
// Interface
// -----------------------------------------------

type private SymbolCount = int
type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list
type private FetchModuleFun = ProjectName -> ModuleName -> Future<ModuleSyntaxData option>
type private BundleResult = TProgram * NameCtx * Error list

let bundle (fetchModule: FetchModuleFun) (entryProjectName: string) : BundleResult =
  let entryRequest =
    let p = entryProjectName
    let docId = computeDocId p p
    newRootRequest docId p p

  let state = initialState
  let _, state = addRequest state entryRequest

  let state =
    mpscConcurrent consumer (producer fetchModule) state [ entryRequest ]

  let modules =
    let comparer (l: ModuleData) (r: ModuleData) = compare l.DocId r.DocId

    let getDeps (m: ModuleData) =
      m.Deps
      |> List.choose
           (fun (r: ModuleRequest) ->
             match TMap.tryFind (r.ProjectName, r.ModuleName) state.RequestMap with
             | Some (RequestResult.Resolved m) -> Some m
             | _ -> None)

    state
    |> toModules
    |> topologicalSort comparer getDeps

  let errors = state |> toErrors

  // Allocate serials for all modules.
  let modules, lastSerial =
    modules
    |> List.mapFold
         (fun (serial: int) (moduleData: ModuleData) ->
           let endSerial = serial + moduleData.SymbolCount
           (serial, moduleData), endSerial)
         0

  // Convert to TIR.
  let modules =
    modules
    |> __parallelMap
         (fun (serial: Serial, moduleData: ModuleData) ->
           let moduleName = moduleData.Name
           let projectName = moduleData.Project
           let docId = moduleData.DocId
           let ast = moduleData.Ast
           let symbolCount = moduleData.SymbolCount

           let exprs, nameCtx =
             let nameCtx = AhNameCtx(serial, [])
             astToHir projectName docId (ast, nameCtx)

           let (AhNameCtx (lastSerial, _)) = nameCtx

           //  printfn
           //    "%s expect: %d..%d (%d) actual: %d..%d (%d)"
           //    docId
           //    serial
           //    (serial + symbolCount)
           //    symbolCount
           //    serial
           //    lastSerial
           //    (lastSerial - serial)

           assert (lastSerial - serial = symbolCount)

           (projectName, moduleName, exprs), nameCtx)

  let modules, identMap =
    modules
    |> List.mapFold
         (fun identMap (m, nameCtx) ->
           let _, identMap =
             nameCtx
             |> nameCtxFold (fun map serial ident -> TMap.add serial ident map) identMap

           m, identMap)
         (TMap.empty compare)

  let nameCtx = NameCtx(identMap, lastSerial)

  modules, nameCtx, errors
