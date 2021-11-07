module MiloneLspServer.LspLangService

open System
open System.Collections.Generic
open System.IO
open System.Text
open MiloneShared.SharedTypes
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

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
  MiloneSyntax.SyntaxApi.chooseSourceExt File.Exists filePath

let private docIdToUri (project: ProjectInfo) (docId: string) =
  let projectName, moduleName =
    match docId.Split(".") with
    | [| p; m |] -> p, m
    | _ -> failwithf "unexpected docId: '%s'" docId

  let projectDir =
    match stdLibProjects |> Map.tryFind projectName with
    | Some it -> it
    | None -> project.ProjectDir + "/../" + projectName

  Path.Combine(projectDir, moduleName + ".milone")
  |> fixExt
  |> uriOfFilePath

// ---------------------------------------------
// Analysis
// ---------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceState2 =
  { Docs: Docs

    DiagnosticsKeys: Uri list
    DiagnosticsCache: DiagnosticsCache<byte array> }

let mutable current: LangServiceState2 =
  { Docs = Docs.empty
    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals }

/// (msg, loc) list
type ProjectValidateResult = (string * Loc) list

let newLangService (project: ProjectInfo) : LangServiceState =
  let projectDir = project.ProjectDir

  let toFilePath moduleName ext =
    Path.Combine(projectDir, moduleName + ext)

  let toUri moduleName ext =
    toFilePath moduleName ext |> uriOfFilePath

  let findDocId projectName moduleName =
    sprintf "%s.%s" projectName moduleName |> Some

  let docIdToUri = docIdToUri project

  let getVersion docId =
    match current.Docs |> Docs.find (docIdToUri docId) with
    | Some d -> d.Version
    | None -> 0

  let getText (docId: string) =
    let uri = docIdToUri docId

    match current.Docs |> Docs.find uri with
    | Some d -> d.Version, d.Text

    | None ->
      match uri |> uriToFilePath with
      | None ->
        debugFn "getText: docId not found: %s" docId
        0, ""

      | Some filePath ->
        match File.tryReadFile filePath with
        | Some it -> 0, it
        | None ->
          if
            Path.GetFileNameWithoutExtension(filePath)
            <> "MiloneOnly"
          then
            debugFn "getText: docId file could not read: %s" filePath

          0, ""

  let getProjectName docId =
    match docId |> docIdToUri |> uriToFilePath with
    | None -> None
    | Some filePath ->
      try
        Path.GetDirectoryName(filePath) |> Some
      with
      | _ -> None

  let docs: LangServiceDocs =
    { FindDocId = findDocId
      GetVersion = getVersion
      GetText = getText
      GetProjectName = getProjectName }

  let langServiceHost: LangServiceHost =
    { MiloneHome = miloneHome
      Docs = docs
      MiloneHomeModules = fun () -> stdLibProjects |> Map.toList
      FindModulesInDir = findModulesInDir }

  LangService.create langServiceHost

let private langServiceCache = MutMap<string, LangServiceState>()

let newLangServiceWithCache (project: ProjectInfo) =
  match langServiceCache
        |> MutMap.tryFind project.ProjectName
    with
  | Some it -> it

  | None ->
    let ls = newLangService project

    langServiceCache
    |> MutMap.insert project.ProjectName ls
    |> ignore

    ls

let mutable lastId = 0

let nextId () =
  System.Threading.Interlocked.Increment(&lastId)

let didOpenDoc (uri: Uri) (version: int) (text: string) : unit =
  current <- { current with Docs = current.Docs |> Docs.add uri version text }

let didChangeDoc (uri: Uri) (version: int) (text: string) : unit =
  current <- { current with Docs = current.Docs |> Docs.update uri version text }

let didCloseDoc (uri: Uri) : unit =
  current <- { current with Docs = current.Docs |> Docs.remove uri }

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

let validateProject (project: ProjectInfo) : ProjectValidateResult =
  project
  |> newLangServiceWithCache
  |> LangService.validateProject project.ProjectDir

// (uri, (msg, pos) list) list
type WorkspaceValidateResult = (Uri * (string * Pos) list) list

let private doValidateWorkspace projects =
  let state = current

  // Collect list of errors per file.
  // Note we need to report absence of errors for docs opened in editor
  // so that the editor clears outdated diagnostics.
  let map = MutMultimap<Uri, string * Pos>()

  for docId in state.DiagnosticsKeys do
    map |> MutMultimap.insertKey docId

  for project in projects do
    for msg, loc in validateProject project do
      let (Loc (docId, y, x)) = loc

      map
      |> MutMultimap.insert (docIdToUri project docId) (msg, (y, x))

  let diagnostics =
    [ for KeyValue (uri, errors) in map do
        let errors =
          errors.ToArray()
          |> Array.sortBy (fun (_, pos) -> pos)
          |> Array.toList

        yield uri, errors ]

  // Remember docId for each document that some error is published to.
  // We need publish empty error list to it to remove these errors next time.
  let diagnosticsKeys =
    diagnostics
    |> List.choose (fun (uri, errors) ->
      if errors |> List.isEmpty |> not then
        Some uri
      else
        None)

  let diagnostics, diagnosticsCache =
    state.DiagnosticsCache
    |> DiagnosticsCache.filter diagnostics

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
  let doCompletion (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.completion project.ProjectDir (uriToDocId uri) pos

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
  let doHighlight (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.documentHighlight project.ProjectDir (uriToDocId uri) pos

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
  let doHover (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.hover project.ProjectDir (uriToDocId uri) pos

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
  let doDefinition (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.definition project.ProjectDir (uriToDocId uri) pos
    |> List.map (fun (docId, range) -> docIdToUri project docId, range)

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
  let doReferences (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.references project.ProjectDir (uriToDocId uri) pos includeDecl
    |> List.map (fun (docId, range) -> docIdToUri project docId, range)

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
      state.Docs
      |> Docs.find uri
      |> Option.map (fun data -> data.Text)

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
