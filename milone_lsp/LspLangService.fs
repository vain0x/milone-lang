module MiloneLsp.LspLangService

open System
open System.Collections.Generic
open System.IO
open System.Text
open MiloneLsp.Lsp
open MiloneLsp.Util
open MiloneLsp.LspCacheLayer

let private miloneHome =
  let miloneHome =
    Environment.GetEnvironmentVariable("MILONE_HOME")

  if miloneHome <> "" then
    miloneHome
  else
    Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)
    + "/.milone"

let private uriOfFilePath (filePath: string) =
  StringBuilder()
    .Append(filePath)
    .Replace(":", "%3A")
    .Replace("\\", "/")
    .Insert(0, "file://")
    .ToString()

let private uriToFilePath (uri: string) =
  try
    let path = Uri(uri).LocalPath

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
  with _ -> None

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
// Project
// ---------------------------------------------

[<NoEquality; NoComparison>]
type ProjectInfo =
  { ProjectDir: string
    ProjectName: string
    EntryFileExt: string }

let private projectsRef: Result<ProjectInfo list, exn> option ref = ref None

/// Finds all projects inside of the workspace.
let private doFindProjects (rootUri: string): ProjectInfo list =
  // eprintfn "findProjects: rootUri = %s" rootUri
  let projects = ResizeArray()

  let rootDir =
    match rootUri |> uriToFilePath with
    | Some it -> it
    | None -> failwithf "rootUri: %A" rootUri

  eprintfn "rootDir = '%s'" rootDir

  // Find projects recursively.
  let mutable stack = Stack()
  stack.Push((0, rootDir))

  while stack.Count <> 0 do
    let depth, dir = stack.Pop()
    // eprintfn "dir: '%s'" dir

    let projectName = Path.GetFileNameWithoutExtension(dir)

    let tryAddProject ext =
      if File.Exists(Path.Combine(dir, projectName + ext)) then
        let project: ProjectInfo =
          { ProjectDir = dir
            ProjectName = projectName
            EntryFileExt = ext }

        eprintfn "project: '%s'" projectName
        projects.Add(project)

    tryAddProject ".milone"
    tryAddProject ".fs"

    if depth < 3 then
      let subdirs =
        try
          Directory.GetDirectories(dir)
        with _ ->
          eprintfn "couldn't get list of files: '%s'" dir
          [||]

      for subdir in subdirs do
        if subdir |> dirIsExcluded |> not then
          stack.Push((depth + 1, subdir))

  List.ofSeq projects

/// Finds project directories recursively. Memoized.
let findProjects (rootUriOpt: string option): Result<ProjectInfo list, exn> =
  match !projectsRef, rootUriOpt with
  | Some it, _ -> it

  | None, None -> Ok []

  | None, Some rootUri ->
      let projects =
        try
          Ok(doFindProjects rootUri)
        with ex ->
          eprintfn "findProjects failed: %A" ex
          Error ex

      projectsRef := Some projects
      projects

// ---------------------------------------------
// Analysis
// ---------------------------------------------

/// (msg, loc) list
type ProjectValidateResult = (string * Loc) list

let newLangService (project: ProjectInfo): LangServiceState =
  let { ProjectDir = projectDir
        ProjectName = projectName } =
    project

  let toFilePath moduleName ext =
    Path.Combine(projectDir, moduleName + ext)

  let toUri moduleName ext =
    toFilePath moduleName ext |> uriOfFilePath

  let fixExt filePath =
    let fs = Path.ChangeExtension(filePath, ".fs")

    if File.Exists(filePath) || not (File.Exists(fs)) then
      filePath
    else
      fs

  let findDocId projectName moduleName =
    match projectName with
    | "MiloneCore"
    | "MiloneStd" ->
        sprintf "%s/milone_libs/%s/%s.milone" miloneHome projectName moduleName
        |> fixExt
        |> uriOfFilePath
        |> Some

    | _ when projectName = project.ProjectName ->
        toFilePath moduleName ".milone"
        |> fixExt
        |> uriOfFilePath
        |> Some

    | _ ->
        eprintfn "findDocId: not found %s/%s" projectName moduleName
        None

  let getVersion docId =
    match LspDocCache.findDoc docId with
    | Some docCache -> docCache.Version
    | None -> 0

  let getText docId =
    match LspDocCache.findDoc docId with
    | Some docCache -> docCache.Version, docCache.Text

    | None ->
        match docId |> uriToFilePath with
        | None ->
            eprintfn "getText: docId not found: %s" docId
            0, ""

        | Some filePath ->
            match File.tryReadFile filePath with
            | Some it -> 0, it
            | None ->
                if Path.GetFileNameWithoutExtension(filePath)
                   <> "MiloneOnly" then
                  eprintfn "getText: docId file could not read: %s" filePath

                0, ""

  let getProjectName docId =
    match docId |> uriToFilePath with
    | None -> None
    | Some filePath ->
        try
          Path.GetDirectoryName(filePath) |> Some
        with _ -> None

  let docs: LangServiceDocs =
    { FindDocId = findDocId
      GetVersion = getVersion
      GetText = getText
      GetProjectName = getProjectName }

  let langServiceHost: LangServiceHost = { MiloneHome = miloneHome; Docs = docs }

  LangService.create langServiceHost

let private langServiceCache = MutMap<string, LangServiceState>()

let newLangServiceWithCache (project: ProjectInfo) =
  match langServiceCache
        |> MutMap.tryFind project.ProjectName with
  | Some it -> it

  | None ->
      let ls = newLangService project

      langServiceCache
      |> MutMap.insert project.ProjectName ls
      |> ignore

      ls

let validateProject (project: ProjectInfo): ProjectValidateResult =
  project
  |> newLangServiceWithCache
  |> LangService.validateProject project.ProjectDir

// (docId, (msg, pos) list) list
type WorkspaceValidateResult = (string * (string * Pos) list) list

let private diagnosticKeys = ResizeArray<string>()

// URI -> MD5 hash of diagnostics
let private diagnosticsCache = DiagnosticsCache.empty ()

let private doValidateWorkspace projects =
  // Collect list of errors per file.
  // Note we need to report absence of errors for docs opened in editor
  // so that the editor clears outdated diagnostics.
  let map = MutMultimap<string, string * Pos>()

  for docId in diagnosticKeys do
    map |> MutMultimap.insertKey docId

  for project in projects do
    for msg, loc in validateProject project do
      let (Loc.Loc (docId, y, x)) = loc
      map |> MutMultimap.insert docId (msg, (y, x))

  let diagnostics =
    [ for KeyValue (docId, errors) in map do
        let errors =
          errors.ToArray()
          |> Array.sortBy (fun (_, pos) -> pos)
          |> Array.toList

        yield docId, errors ]

  // Remember docId for each document that some error is published to.
  // We need publish empty error list to it to remove these errors next time.
  diagnosticKeys
  |> ResizeArray.assign (
    diagnostics
    |> List.choose
         (fun (docId, errors) ->
           if errors |> List.isEmpty |> not then
             Some docId
           else
             None)
  )

  diagnosticsCache
  |> DiagnosticsCache.filter diagnostics

/// Validate all projects in workspace to report errors.
let validateWorkspace (rootUriOpt: string option): WorkspaceValidateResult =
  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
      try
        doValidateWorkspace projects
      with ex ->
        eprintfn "validateWorkspace failed: %A" ex
        []

let documentHighlight rootUriOpt uri pos =
  let doHighlight (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.documentHighlight project.ProjectDir uri pos

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
      with ex -> eprintfn "documentHighlight failed: %A" ex

  reads, writes

let hover rootUriOpt uri pos =
  let doHover (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.hover project.ProjectDir uri pos

  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
      try
        projects
        |> List.choose (fun project -> doHover project uri pos)
      with ex ->
        eprintfn "hover failed: %A" ex
        []

let definition rootUriOpt uri pos =
  let doDefinition (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.definition project.ProjectDir uri pos

  match findProjects rootUriOpt with
  | Error _ -> []
  | Ok projects ->
      try
        projects
        |> List.collect (fun project -> doDefinition project uri pos)
      with ex ->
        eprintfn "definition failed: %A" ex
        []

let references rootUriOpt uri pos (includeDecl: bool) =
  let doReferences (project: ProjectInfo) uri pos =
    project
    |> newLangServiceWithCache
    |> LangService.references project.ProjectDir uri pos includeDecl

  match findProjects rootUriOpt with
  | Error _ -> []
  | Ok projects ->
      try
        projects
        |> List.collect (fun project -> doReferences project uri pos)
      with ex ->
        eprintfn "references failed: %A" ex
        []
