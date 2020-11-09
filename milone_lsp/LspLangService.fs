module MiloneLsp.LspLangService

open MiloneLang.Types

let private uriOfFilePath (filePath: string) =
  System.Text.StringBuilder().Append(filePath).Replace(":", "%3A").Replace("\\", "/").Insert(0, "file:///").ToString()

/// Whether dir is excluded in traversal?
let private dirIsExcluded (dir: string) =
  let name = System.IO.Path.GetFileName(dir)

  name.StartsWith(".")
  || name.Contains("~")
  || name = "node_modules"
  || name = "target"
  || name = "bin"
  || name = "obj"

// -----------------------------------------------
// MutMultimap
// -----------------------------------------------

type MutMultimap<'K, 'T> = System.Collections.Generic.Dictionary<'K, ResizeArray<'T>>

module MutMultimap =
  let empty<'K, 'T when 'K: equality> () = MutMultimap()

  let insertKey key (multimap: MutMultimap<_, _>) =
    if multimap.ContainsKey(key) |> not then multimap.Add(key, ResizeArray())

  let insert key value (multimap: MutMultimap<_, _>) =
    match multimap.TryGetValue(key) with
    | true, values -> values.Add(value)

    | false, _ -> multimap.Add(key, ResizeArray([ value ]))

// ---------------------------------------------
// AnalysisCache
// ---------------------------------------------

type TokenizeResult = (Token * Pos) list

type ParseResult = ARoot * (string * Pos) list

[<NoEquality>]
[<NoComparison>]
type AnalysisCache =
  { mutable Ok: bool
    mutable TokenizeResultOpt: TokenizeResult option
    mutable ParseResultOpt: ParseResult option }

  static member Create(): AnalysisCache =
    { Ok = true
      TokenizeResultOpt = None
      ParseResultOpt = None }

  member this.Reset() =
    this.Ok <- true
    this.TokenizeResultOpt <- None
    this.ParseResultOpt <- None

  member this.IsReady =
    match this with
    | { Ok = true; TokenizeResultOpt = Some _; ParseResultOpt = Some _ } -> true
    | _ -> false

// ---------------------------------------------
// FileCache
// ---------------------------------------------

[<NoEquality>]
[<NoComparison>]
type FileCache =
  { FilePath: string
    mutable Text: string
    mutable Timestamp: System.DateTime
    AnalysisCache: AnalysisCache }

let private files =
  System.Collections.Generic.Dictionary<string, FileCache>()

let private fetchFile (filePath: string) lastWriteTime: FileCache option =
  let timestamp = System.DateTime() |> max lastWriteTime

  let textOpt =
    try
      System.IO.File.ReadAllText(filePath) |> Some
    with _ -> None

  match textOpt with
  | None -> None

  | Some text ->
      let fileCache: FileCache =
        { FilePath = filePath
          Text = text
          Timestamp = timestamp
          AnalysisCache = AnalysisCache.Create() }

      eprintfn "file cache added: '%s'" filePath
      files.Add(filePath, fileCache)

      Some fileCache

let private invalidateFileCache (fileCache: FileCache) lastWriteTime =
  let { FilePath = filePath } = fileCache

  let timestamp = System.DateTime() |> max lastWriteTime

  let textOpt =
    try
      System.IO.File.ReadAllText(filePath) |> Some
    with _ -> None

  match textOpt with
  | Some text ->
      eprintfn "file cache updated: '%s'" filePath
      fileCache.AnalysisCache.Reset()
      fileCache.Text <- text
      fileCache.Timestamp <- timestamp

      Some fileCache

  | None ->
      eprintfn "file cache removed: '%s'" filePath
      files.Remove(filePath) |> ignore
      None

let useFile (filePath: string): FileCache option =
  let lastWriteTimeOpt =
    try
      if System.IO.File.Exists(filePath)
      then System.IO.File.GetLastWriteTime(filePath) |> Some
      else None
    with _ -> None

  match files.TryGetValue(filePath), lastWriteTimeOpt with
  | (true, fileCache), Some lastWriteTime ->
      if fileCache.Timestamp < lastWriteTime
      then invalidateFileCache fileCache lastWriteTime
      else Some fileCache

  | (true, _), None ->
      eprintfn "file cache removed: '%s'" filePath
      files.Remove(filePath) |> ignore
      None

  | (false, _), Some lastWriteTime -> fetchFile filePath lastWriteTime

  | (false, _), None -> None

// ---------------------------------------------
// DocData
// ---------------------------------------------

/// Text doc that is opened in editor.
type DocData =
  {
    /// String to identify a file. E.g. `file:///home/owner/.../foo.milone`.
    Uri: string

    /// Number to identify an edition of this file.
    Version: int

    Text: string

    AnalysisCache: AnalysisCache }

/// List of docs open in editor, keyed by URI.
let private docs =
  System.Collections.Generic.Dictionary<string, DocData>()

let findDoc (uri: string): DocData option =
  match docs.TryGetValue(uri) with
  | true, docData -> Some docData
  | false, _ -> None

let openDoc (uri: string) (version: int) (text: string) =
  let docData: DocData =
    { Uri = uri
      Version = version
      Text = text
      AnalysisCache = AnalysisCache.Create() }

  eprintfn "INFO: Doc opened uri:'%s' v:%d len:%d" uri version text.Length
  docs.Add(uri, docData)

let changeDoc (uri: string) (version: int) (text: string): unit =
  match findDoc uri with
  | Some _ ->
      let docData =
        { Uri = uri
          Version = version
          Text = text
          AnalysisCache = AnalysisCache.Create() }

      eprintfn "INFO: Doc changed uri:'%s' v:%d len:%d" uri version text.Length
      docs.[uri] <- docData

  | None -> openDoc uri version text

let closeDoc (uri: string): unit =
  eprintfn "INFO: Doc closed uri:'%s'" uri
  docs.Remove(uri) |> ignore

// ---------------------------------------------
// Project
// ---------------------------------------------

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
    let path = System.Uri(rootUri).LocalPath

    // HOTFIX: On Windows, Uri.LocalPath can starts with an extra / and then it's invalid as file path; e.g. `/c:/Users/john/Foo/Foo.milone`.
    if path.Contains(":") && path.StartsWith("/")
    then path.TrimStart([| '/' |])
    else path

  eprintfn "rootDir = '%s'" rootDir

  // Find projects recursively.
  let mutable stack = System.Collections.Generic.Stack()
  stack.Push(rootDir)

  while stack.Count <> 0 do
    let dir = stack.Pop()
    eprintfn "dir: '%s'" dir

    let projectName =
      System.IO.Path.GetFileNameWithoutExtension(dir)

    let tryAddProject ext =
      if System.IO.File.Exists(System.IO.Path.Combine(dir, projectName + ext)) then
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
        System.IO.Directory.GetDirectories(dir)
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

let tokenizeWithCaching (text: string) (analysisCache: AnalysisCache): TokenizeResult =
  match analysisCache.TokenizeResultOpt with
  | Some it -> it

  | None ->
      let result = MiloneLang.Lexing.tokenize text
      analysisCache.TokenizeResultOpt <- Some result
      result

let parseWithCaching (text: string) (analysisCache: AnalysisCache): ParseResult =
  match analysisCache.ParseResultOpt with
  | Some it -> it

  | None ->
      let tokens = tokenizeWithCaching text analysisCache
      let result = MiloneLang.Parsing.parse tokens

      let ok =
        let _, errors = result
        List.isEmpty errors

      analysisCache.ParseResultOpt <- Some result
      analysisCache.Ok <- analysisCache.Ok && ok
      result

let validateDoc (uri: string): (string * Pos) list =
  match findDoc uri with
  | Some docData ->
      let _, errors =
        parseWithCaching docData.Text docData.AnalysisCache

      errors

  | None -> []

type ProjectValidateResult =
  { ModuleUris: string list

    /// (uri, msg, pos) list
    Errors: (string * string * Pos) list }

let validateProject (project: ProjectInfo): ProjectValidateResult =
  let { ProjectDir = projectDir; ProjectName = projectName } = project

  let toFilePath moduleName ext =
    System.IO.Path.Combine(projectDir, moduleName + ext)

  let toUri moduleName ext =
    toFilePath moduleName ext |> uriOfFilePath

  let moduleUris = System.Collections.Generic.Dictionary()
  moduleUris.Add(projectName, toUri projectName project.EntryFileExt)

  // Get contents of module from doc in editor or file, if any.
  let tryReadModule moduleName ext =
    match docs.TryGetValue(toUri moduleName ext) with
    | true, docData -> Some docData.Text

    | false, _ ->
        match useFile (toFilePath moduleName ext) with
        | Some fileCache -> Some fileCache.Text
        | None -> None

  // Bundle.
  let expr, nameCtx, errorListList =
    let readCoreFile moduleName =
      eprintfn "readCoreFile: unimplemented"
      ""

    let readModuleFile moduleName =
      eprintfn "readModuleFile '%s'" moduleName

      let source =
        match tryReadModule moduleName ".milone" with
        | Some it -> Some(it, ".milone")
        | None ->
            match tryReadModule moduleName ".fs" with
            | Some it -> Some(it, ".fs")
            | None -> None

      match source with
      | Some (source, ext) ->
          // Remember URI to create error location later.
          if moduleUris.ContainsKey(moduleName) |> not
          then moduleUris.Add(moduleName, toUri moduleName ext)

          Some source

      | None -> None

    let parseModule (moduleName: string) tokens =
      eprintfn "parse: '%s'" moduleName
      MiloneLang.Parsing.parse tokens

    let nameCtx = MiloneLang.Helpers.nameCtxEmpty ()

    MiloneLang.Bundling.parseProjectModules readCoreFile readModuleFile parseModule projectName nameCtx

  // Name resolution.
  let expr, scopeCtx =
    MiloneLang.NameRes.nameRes (expr, nameCtx)

  // Type inference.
  let _expr, tyCtx =
    MiloneLang.Typing.infer (expr, scopeCtx, errorListList)

  // Collect errors.
  let errors =
    let tyDisplayFn ty =
      let getTyIdent tySerial =
        tyCtx
        |> MiloneLang.Records.tyCtxGetTys
        |> MiloneLang.Helpers.mapTryFind tySerial
        |> Option.map MiloneLang.Helpers.tyDefToIdent

      ty |> MiloneLang.Helpers.tyDisplay getTyIdent

    [ for log, loc in tyCtx |> MiloneLang.Records.tyCtxGetLogs do
        let moduleName, row, column = loc

        let uri =
          match moduleUris.TryGetValue(moduleName) with
          | true, it -> it
          | false, _ -> toUri moduleName ".milone"

        let pos = row, column

        let msg =
          MiloneLang.Helpers.logToString tyDisplayFn loc log

        yield uri, msg, pos ]

  let moduleUris = List.ofSeq moduleUris.Values

  { ModuleUris = moduleUris
    Errors = errors }

// (uri, (msg, pos) list) list
type WorkspaceValidateResult = (string * (string * Pos) list) list

/// Validate all projects in workspace to collect semantic errors.
let validateWorkspace (rootUriOpt: string option): WorkspaceValidateResult =
  match findProjects rootUriOpt with
  | Error _ -> []

  | Ok projects ->
      try
        // Collect list of errors per file.
        // Note we need to report absence of errors for docs opened in editor
        // so that the editor clears outdated diagnostics.
        let mutable map = MutMultimap.empty ()

        for project in projects do
          let { ModuleUris = moduleUris; Errors = errors } = validateProject project

          for uri in moduleUris do
            map |> MutMultimap.insertKey uri

          for uri, msg, pos in errors do
            map |> MutMultimap.insert uri (msg, pos)

        [ for KeyValue (uri, errors) in map do
            yield uri, List.ofSeq errors ]
      with ex ->
        eprintfn "validateWorkspace failed: %A" ex
        []
