module MiloneLsp.LspLangService

open System
open System.Collections.Generic
open System.IO
open System.Text
open MiloneLsp.Lsp
open MiloneLsp.Util

let private miloneHome =
  Environment.GetEnvironmentVariable("MILONE_HOME")

let private uriOfFilePath (filePath: string) =
  StringBuilder().Append(filePath).Replace(":", "%3A").Replace("\\", "/").Insert(0, "file://").ToString()

let private uriToFilePath (uri: string) =
  try
    Uri(uri).LocalPath |> Some
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
  eprintfn "findProjects: rootUri = %s" rootUri
  let projects = ResizeArray()

  let rootDir =
    let path = Uri(rootUri).LocalPath

    // HOTFIX: On Windows, Uri.LocalPath can starts with an extra / and then it's invalid as file path; e.g. `/c:/Users/john/Foo/Foo.milone`.
    if path.Contains(":") && path.StartsWith("/")
    then path.TrimStart('/')
    else path

  eprintfn "rootDir = '%s'" rootDir

  // Find projects recursively.
  let mutable stack = Stack()
  stack.Push(rootDir)

  while stack.Count <> 0 do
    let dir = stack.Pop()
    eprintfn "dir: '%s'" dir

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

    let subdirs =
      try
        Directory.GetDirectories(dir)
      with _ ->
        eprintfn "couldn't get list of files: '%s'" dir
        [||]

    for subdir in subdirs do
      if subdir |> dirIsExcluded |> not then stack.Push(subdir)

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

let validateProject (project: ProjectInfo): ProjectValidateResult =
  let { ProjectDir = projectDir; ProjectName = projectName } = project

  let toFilePath moduleName ext =
    Path.Combine(projectDir, moduleName + ext)

  let toUri moduleName ext =
    toFilePath moduleName ext |> uriOfFilePath

  let findExt moduleName =
    if File.Exists(toFilePath moduleName ".milone")
       || not (File.Exists(toFilePath moduleName ".fs")) then
      ".milone"
    else
      ".fs"

  let findDocId projectName moduleName =
    match projectName with
    | "MiloneCore"
    | "MiloneStd" ->
        sprintf "%s/milone_libs/%s/%s.fs" miloneHome projectName moduleName
        |> uriOfFilePath
        |> Some

    | _ when projectName = project.ProjectName ->
        let ext = findExt moduleName
        toUri moduleName ext |> Some

    | _ ->
        eprintfn "findDocId: not found %s/%s" projectName moduleName
        None

  let getText docId =
    match LspDocCache.findDoc docId with
    | Some docCache -> docCache.Text

    | None ->
        match docId |> uriToFilePath with
        | None -> ""
        | Some filePath ->
            File.tryReadFile filePath
            |> Option.defaultValue ""

  let getProjectName docId =
    match docId |> uriToFilePath with
    | None -> None
    | Some filePath ->
        try
          Path.GetDirectoryName(filePath) |> Some
        with _ -> None

  let docs: LangServiceDocs =
    { FindDocId = findDocId
      GetText = getText
      GetProjectName = getProjectName }

  let langServiceHost: LangServiceHost = { MiloneHome = miloneHome; Docs = docs }

  let langService = LangService.create langServiceHost

  LangService.validateProject projectDir langService

// (docId, (msg, pos) list) list
type WorkspaceValidateResult = (string * (string * Pos) list) list

let private diagnosticKeys = ResizeArray<string>()

let private doValidateWorkspace projects =
  // Collect list of errors per file.
  // Note we need to report absence of errors for docs opened in editor
  // so that the editor clears outdated diagnostics.
  let map = MutMultimap<string, string * Pos>()

  for docId in diagnosticKeys do
    map |> MutMultimap.insertKey docId

  for project in projects do
    for msg, loc in validateProject project do
      let docId, y, x = loc
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
  |> ResizeArray.assign
       (diagnostics
        |> List.choose (fun (docId, errors) -> if errors |> List.isEmpty |> not then Some docId else None))

  diagnostics

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
