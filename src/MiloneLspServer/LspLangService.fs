module MiloneLspServer.LspLangService

open System
open System.Collections.Generic
open System.IO
open System.Text
open MiloneShared.SharedTypes
open MiloneStd.StdMap
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

module Syntax = MiloneSyntax.Syntax // FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi
module SyntaxParse = MiloneSyntax.SyntaxParse
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize

let private miloneHome =
  let opt (s: string) =
    match s with
    | null
    | "" -> None
    | _ -> Some s

  let getMiloneHomeEnv () =
    Environment.GetEnvironmentVariable("MILONE_HOME")
    |> opt

  let getHomeEnv () =
    Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)
    |> opt

  MiloneSyntax.SyntaxApi.getMiloneHomeFromEnv getMiloneHomeEnv getHomeEnv

let private stdLibProjects =
  MiloneSyntax.SyntaxApi.getStdLibProjects miloneHome
  |> Map.ofList

let private uriOfFilePath (filePath: string) =
  let canonicalize (filePath: string) =
    let filePath =
      filePath.Replace("\\", "/").Replace("//", "/")

    let filePath =
      if filePath.StartsWith("/") then
        filePath
      else
        "/" + filePath

    let rec go (components: string []) =
      let i = Array.IndexOf(components, "..")

      if i < 0 || i = 0 then
        components
      else
        let parent, rest =
          components.[..i - 2], components.[i + 1..]

        go (Array.append parent rest)

    String.concat "/" (go (filePath.Split("/")))

  StringBuilder()
    .Append(canonicalize filePath)
    .Replace(":", "%3A")
    .Insert(0, "file://")
    .ToString()
  |> Uri

let private uriToFilePath (uri: Uri) =
  try
    let (Uri uri) = uri
    let path = System.Uri(uri).LocalPath

    // HOTFIX: On linux, path starts with \\ and is separated by \ for some reason.
    let path =
      path.Replace("\\\\", "/").Replace("\\", "/")

    // HOTFIX: On Windows, path sometimes starts with an extra / and then it's invalid as file path; e.g. `/c:/Users/john/Foo/Foo.milone`.
    let path =
      if path.Contains(":") && path.StartsWith("/") then
        path.TrimStart('/')
      else
        path

    Some path
  with
  | _ -> None

/// Whether dir is excluded in traversal?
let private dirIsExcluded (dir: string) =
  let name = Path.GetFileName(dir)

  name.StartsWith(".")
  || name.Contains("~")
  || name = "node_modules"
  || name = "target"
  || name = "bin"
  || name = "obj"

// ---------------------------------------------
// Standard libs
// ---------------------------------------------

let private findModulesRecursively (maxDepth: int) (rootDir: string) : (string * string) list =
  let mutable files = ResizeArray()
  let mutable stack = Stack()
  stack.Push(0, rootDir)

  try
    while stack.Count <> 0 do
      let depth, dir = stack.Pop()
      debugFn "in %d:%s" depth dir
      assert (depth <= maxDepth)

      let projectName = Path.GetFileNameWithoutExtension(dir)

      for file in Directory.GetFiles(dir) do
        let ext = Path.GetExtension(file)

        if ext = ".milone" || ext = ".fs" then
          let moduleName = Path.GetFileNameWithoutExtension(file)
          debugFn "in %s" moduleName
          files.Add(projectName, moduleName)

      if depth < maxDepth then
        for subdir in Directory.GetDirectories(dir) do
          if subdir |> dirIsExcluded |> not then
            stack.Push(depth + 1, subdir)
  with
  | ex -> debugFn "find files in '%s': %A" rootDir ex

  files |> Seq.toList

let private findModulesInDir projectDir = findModulesRecursively 0 projectDir

// ---------------------------------------------
// Project
// ---------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectInfo =
  { ProjectDir: string
    ProjectName: string
    EntryFileExt: string }

let private projectsRef: Result<ProjectInfo list, exn> option ref = ref None

/// Finds all projects inside of the workspace.
let private doFindProjects (rootUri: string) : ProjectInfo list =
  let projects = ResizeArray()

  let rootDir =
    match Uri rootUri |> uriToFilePath with
    | Some it -> it
    | None -> failwithf "rootUri: %A" rootUri

  // Find projects recursively.
  let mutable stack = Stack()
  stack.Push((0, rootDir))

  while stack.Count <> 0 do
    let depth, dir = stack.Pop()

    let projectName = Path.GetFileNameWithoutExtension(dir)

    let tryAddProject ext =
      if File.Exists(Path.Combine(dir, projectName + ext)) then
        let project: ProjectInfo =
          { ProjectDir = dir
            ProjectName = projectName
            EntryFileExt = ext }

        projects.Add(project)

    tryAddProject ".milone"
    tryAddProject ".fs"

    if depth < 3 then
      let subdirs =
        try
          Directory.GetDirectories(dir)
        with
        | _ ->
          debugFn "couldn't get list of files: '%s'" dir
          [||]

      for subdir in subdirs do
        if subdir |> dirIsExcluded |> not then
          stack.Push((depth + 1, subdir))

  List.ofSeq projects

/// Finds project directories recursively. Memoized.
let findProjects (rootUriOpt: string option) : Result<ProjectInfo list, exn> =
  match !projectsRef, rootUriOpt with
  | Some it, _ -> it

  | None, None -> Ok []

  | None, Some rootUri ->
    let projects =
      try
        let projects = doFindProjects rootUri
        infoFn "findProjects: %A" (List.map (fun (p: ProjectInfo) -> p.ProjectDir) projects)
        Ok projects
      with
      | ex ->
        errorFn "findProjects failed: %A" ex
        Error ex

    projectsRef := Some projects
    projects

let private uriToDocId (uri: Uri) : DocId =
  let filePath =
    match uriToFilePath uri with
    | Some it -> it
    | None -> failwithf "unexpected URI: %A" uri

  let projectName =
    Path.GetFileName(Path.GetDirectoryName(filePath))

  let moduleName =
    Path.GetFileNameWithoutExtension(filePath)

  sprintf "%s.%s" projectName moduleName

let private fixExt filePath =
  SyntaxApi.chooseSourceExt File.Exists filePath

let private docIdToModulePath (docId: DocId) =
  match docId.Split(".") with
  | [| p; m |] -> Some(p, m)

  | _ ->
    debugFn "Not a docId of module file: '%s'" docId
    None

let private docIdToUri (project: ProjectInfo) (docId: string) =
  let filePath =
    match docIdToModulePath docId with
    | Some (projectName, moduleName) ->
      let projectDir =
        match stdLibProjects |> Map.tryFind projectName with
        | Some it -> it
        | None -> project.ProjectDir + "/../" + projectName

      Path.Combine(projectDir, moduleName + ".milone")

    | _ when File.Exists(docId) -> docId
    | _ -> failwithf "Bad docId: '%s'" docId

  filePath |> fixExt |> uriOfFilePath

let private docIdIsOptional docId =
  match docIdToModulePath docId with
  | Some (_, "MiloneOnly") -> true
  | _ -> false

// ---------------------------------------------
// Analysis
// ---------------------------------------------

type private DocVersion = int

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceState2 =
  { Docs: TreeMap<Uri, DocVersion * string>
    Projects: TreeMap<string, LangServiceState>

    // Workspace-wide cache.
    TokenizeCache: TreeMap<DocId, DocVersion * Syntax.TokenizeFullResult>
    ParseCache: TreeMap<DocId, DocVersion * Syntax.ModuleSyntaxData>

    // Diagnostics.
    DiagnosticsKeys: Uri list
    DiagnosticsCache: DiagnosticsCache<byte array> }

let empty2: LangServiceState2 =
  { Docs = TMap.empty Uri.compare
    Projects = TMap.empty compare

    TokenizeCache = TMap.empty compare
    ParseCache = TMap.empty compare

    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals }

let mutable private current = empty2

/// (msg, loc) list
type private ProjectValidateResult = (string * Loc) list

let private emptyProjectLangService : LangServiceState =
  let langServiceHost: LangServiceHost =
    { GetDocVersion = fun _ -> failwith "illegal use"
      Tokenize = fun _ -> failwith "illegal use"
      Parse = fun _ -> failwith "illegal use"

      MiloneHome = miloneHome
      MiloneHomeModules = fun () -> stdLibProjects |> Map.toList
      FindModulesInDir = findModulesInDir }

  LangService.create langServiceHost

let private tokenizeHost = Syntax.tokenizeHostNew ()

let doWithLangService
  (p: ProjectInfo)
  (action: LangServiceState -> 'A * LangServiceState)
  (state: LangServiceState2)
  : 'A * LangServiceState2 =
  let getVersion docId =
    match state.Docs |> TMap.tryFind (docIdToUri p docId) with
    | Some (v, _) -> Some v
    | None -> None

  let ls =
    match state.Projects |> TMap.tryFind p.ProjectName with
    | Some it -> it
    | None -> emptyProjectLangService

  let tokenize1 docId =
    let version =
      getVersion docId |> Option.defaultValue 0

    match state.ParseCache |> TMap.tryFind docId with
    | Some (v, (_, tokens, _, _)) when v >= version -> v, tokens

    | _ ->
      match state.TokenizeCache |> TMap.tryFind docId with
      | Some ((v, _) as it) when v >= version -> it

      | _ ->
        match state.Docs |> TMap.tryFind (docIdToUri p docId) with
        | None ->
          if docIdIsOptional docId |> not then
            warnFn "missing docId '%s' to be tokenized" docId

          -1, []

        | Some (v, text) ->
          debugFn "tokenize '%s' v:%d" docId v

          let tokens =
            SyntaxTokenize.tokenizeAll tokenizeHost text

          v, tokens

  let parse1 docId =
    let version =
      getVersion docId |> Option.defaultValue 0

    let _, tokens = tokenize1 docId

    match state.ParseCache |> TMap.tryFind docId with
    | Some ((v, _) as it) when v >= version -> Some it

    | _ ->
      match getVersion docId with
      | None ->
        if docIdIsOptional docId |> not then
          warnFn "missing docId '%s' to be parsed" docId

        None

      | Some v ->
        match docIdToModulePath docId with
        | None ->
          warnFn "illegal docId '%s'" docId
          None

        | Some (projectName, moduleName) ->
          debugFn "parse '%s' v:%d" docId v

          let syntaxData =
            parseFullTokens projectName moduleName docId tokens

          Some(v, syntaxData)

  let ls =
    let host =
      { ls.Host with
          GetDocVersion = getVersion
          Tokenize = tokenize1
          Parse = parse1 }

    { ls with Host = host }

  let result, ls = action ls

  let state =
    ls.NewParseResults
    |> List.fold
         (fun (state: LangServiceState2) (v, syntaxData) ->
           let docId, tokens, _, _ = syntaxData

           { state with
               TokenizeCache = state.TokenizeCache |> TMap.add docId (v, tokens)
               ParseCache = state.ParseCache |> TMap.add docId (v, syntaxData) })
         state

  let state =
    { state with Projects = state.Projects |> TMap.add p.ProjectName ls }

  result, state

let private withLangService p action =
  let result, state = doWithLangService p action current
  current <- state
  result

let mutable private lastId = 0

let nextId () =
  System.Threading.Interlocked.Increment(&lastId)

let openDoc (uri: Uri) (version: int) (text: string) (state: LangServiceState2) =
  { state with Docs = state.Docs |> TMap.add uri (version, text) }

let didOpenDoc (uri: Uri) (version: int) (text: string) : unit =
  current <- openDoc uri version text current

let didChangeDoc (uri: Uri) (version: int) (text: string) : unit =
  current <- { current with Docs = current.Docs |> TMap.add uri (version, text) }

let didCloseDoc (uri: Uri) : unit =
  let _, docs = current.Docs |> TMap.remove uri
  current <- { current with Docs = docs }

let didOpenFile (uri: Uri) : unit =
  match uriToFilePath uri |> Option.bind File.tryReadFile with
  | Some text ->
    let version = nextId ()
    didOpenDoc uri version text

  | None -> ()

let didChangeFile (uri: Uri) : unit =
  match uriToFilePath uri |> Option.bind File.tryReadFile with
  | Some text ->
    let version = nextId ()
    didChangeDoc uri version text

  | None -> ()

let didCloseFile (uri: Uri) : unit = didCloseDoc uri

let validateProject (p: ProjectInfo) : ProjectValidateResult =
  withLangService p (LangService.validateProject p.ProjectDir)

// (uri, (msg, pos) list) list
type private WorkspaceValidateResult = (Uri * (string * Pos) list) list

let private doValidateWorkspace projects =
  let state = current

  let diagnostics =
    projects
    |> Seq.collect (fun p ->
      validateProject p
      |> Seq.map (fun (msg, loc) ->
        let (Loc (docId, y, x)) = loc
        msg, docIdToUri p docId, (y, x)))
    |> Seq.toList

  let diagnostics, diagnosticsKeys, diagnosticsCache =
    aggregateDiagnostics state.DiagnosticsKeys state.DiagnosticsCache diagnostics

  current <-
    { current with
        DiagnosticsKeys = diagnosticsKeys
        DiagnosticsCache = diagnosticsCache }

  diagnostics

/// Validate all projects in workspace to report errors.
let validateWorkspace (rootUriOpt: string option) : WorkspaceValidateResult =
  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
    try
      doValidateWorkspace projects
    with
    | ex ->
      errorFn "validateWorkspace failed: %A" ex
      []

let completion rootUriOpt uri pos =
  let doCompletion (p: ProjectInfo) uri pos =
    withLangService p (LangService.completion p.ProjectDir (uriToDocId uri) pos)

  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
    try
      projects
      |> List.collect (fun project -> doCompletion project uri pos)
    with
    | ex ->
      errorFn "completion failed: %A" ex
      []

let documentHighlight rootUriOpt uri pos =
  let doHighlight (p: ProjectInfo) uri pos =
    withLangService p (LangService.documentHighlight p.ProjectDir (uriToDocId uri) pos)

  // let texts = ResizeArray()
  let reads = ResizeArray()
  let writes = ResizeArray()

  match findProjects rootUriOpt with
  | Error _ -> ()
  | Ok projects ->
    try
      for project in projects do
        match doHighlight project uri pos with
        | None -> ()
        | Some (r, w) ->
          reads.AddRange(r)
          writes.AddRange(w)
    with
    | ex -> errorFn "documentHighlight failed: %A" ex

  reads, writes

let hover rootUriOpt uri pos =
  let doHover (p: ProjectInfo) uri pos =
    withLangService p (LangService.hover p.ProjectDir (uriToDocId uri) pos)

  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
    try
      projects
      |> List.choose (fun project -> doHover project uri pos)
    with
    | ex ->
      errorFn "hover failed: %A" ex
      []

let definition rootUriOpt uri pos =
  let doDefinition (p: ProjectInfo) uri pos =
    withLangService p (LangService.definition p.ProjectDir (uriToDocId uri) pos)
    |> List.map (fun (docId, range) -> docIdToUri p docId, range)

  match findProjects rootUriOpt with
  | Error _ -> []
  | Ok projects ->
    try
      projects
      |> List.collect (fun project -> doDefinition project uri pos)
    with
    | ex ->
      errorFn "definition failed: %A" ex
      []

let references rootUriOpt uri pos (includeDecl: bool) =
  let doReferences (p: ProjectInfo) uri pos =
    withLangService p (LangService.references p.ProjectDir (uriToDocId uri) pos includeDecl)
    |> List.map (fun (docId, range) -> docIdToUri p docId, range)

  match findProjects rootUriOpt with
  | Error _ -> []
  | Ok projects ->
    try
      projects
      |> List.collect (fun project -> doReferences project uri pos)
    with
    | ex ->
      errorFn "references failed: %A" ex
      []

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FormattingResult = { Edits: (Range * string) list }

// FIXME: compute diff
let private formattingResultOfDiff _prev next : FormattingResult =
  { Edits = [ ((0, 0), (1100100100, 0)), next ] }

let formatting (uri: Uri) : FormattingResult option =
  let state = current

  match uriToFilePath uri with
  | Some filePath ->
    let dir = Path.GetDirectoryName(filePath)

    let temp =
      let basename =
        Path.GetFileNameWithoutExtension(filePath)

      let suffix = Guid.NewGuid().ToString()

      // Create temporary file alongside the file for .editorconfig.
      Path.Combine(dir, sprintf "%s_%s.ignored.fs" basename suffix)

    let textOpt =
      match state.Docs |> TMap.tryFind uri with
      | Some (_, text) -> Some text
      | _ -> None

    try
      try
        let text =
          match textOpt with
          | Some text ->
            File.WriteAllText(temp, text)
            text

          | None ->
            File.Copy(filePath, temp)
            File.ReadAllText(filePath)

        use proc =
          // When the server is executed as VSCode extension,
          // some environment variables are not inherited.

          let homeDir =
            Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)

          let startInfo = Diagnostics.ProcessStartInfo()
          startInfo.FileName <- "/usr/bin/dotnet"
          startInfo.ArgumentList.Add("fantomas")
          startInfo.ArgumentList.Add(temp)
          startInfo.WorkingDirectory <- dir
          startInfo.EnvironmentVariables.Add("DOTNET_CLI_HOME", homeDir)
          startInfo.EnvironmentVariables.Add("PATH", "/usr/bin")
          startInfo.RedirectStandardOutput <- true
          Diagnostics.Process.Start(startInfo)

        let exited = proc.WaitForExit(30 * 1000)

        if not exited then
          proc.Kill(entireProcessTree = true)
          None
        else
          let newText = File.ReadAllText(temp)
          formattingResultOfDiff text newText |> Some
      with
      | err ->
        warnFn "failed fantomas: %O" err
        None
    finally
      try
        File.Delete(temp)
      with
      | err -> warnFn "failed deleting temporary file '%s': %O" temp err

  | None -> None
