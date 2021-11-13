module MiloneLspServer.LspLangService

open System
open System.Collections.Generic
open System.IO
open System.Text
open MiloneShared.SharedTypes
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi

// FIXME: avoid using generic compare
let private listUnique xs =
  xs |> TSet.ofList compare |> TSet.toList

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

  SyntaxApi.getMiloneHomeFromEnv getMiloneHomeEnv getHomeEnv

let private stdLibProjects =
  SyntaxApi.getStdLibProjects miloneHome
  |> Map.ofList

let uriOfFilePath (filePath: string) =
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
  | _ ->
    traceFn "uriToFilePath failed: %s" (Uri.toString uri)
    None

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

  while stack.Count <> 0 do
    let depth, dir = stack.Pop()
    traceFn "in %d:%s" depth dir
    assert (depth <= maxDepth)

    let projectName = Path.GetFileNameWithoutExtension(dir)

    for file in Directory.GetFiles(dir) do
      let ext = Path.GetExtension(file)

      if ext = ".milone" || ext = ".fs" then
        let moduleName = Path.GetFileNameWithoutExtension(file)
        traceFn "in %s" moduleName
        files.Add(projectName, moduleName)

    if depth < maxDepth then
      for subdir in Directory.GetDirectories(dir) do
        if subdir |> dirIsExcluded |> not then
          stack.Push(depth + 1, subdir)

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
      let subdirs = Directory.GetDirectories(dir)

      for subdir in subdirs do
        if subdir |> dirIsExcluded |> not then
          stack.Push((depth + 1, subdir))

  List.ofSeq projects

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
    traceFn "Not a docId of module file: '%s'" docId
    None

let private docIdToFilePath (p: ProjectInfo) (docId: DocId) =
  match docIdToModulePath docId with
  | Some (projectName, moduleName) ->
    let projectDir =
      match stdLibProjects |> Map.tryFind projectName with
      | Some it -> it
      | None -> p.ProjectDir + "/../" + projectName

    Path.Combine(projectDir, moduleName + ".milone")

  | _ when File.Exists(docId) -> docId
  | _ -> failwithf "Bad docId: '%s'" docId

let private doDocIdToUri (p: ProjectInfo) (docId: string) =
  docId
  |> docIdToFilePath p
  |> fixExt
  |> uriOfFilePath

let private docIdIsOptional docId =
  match docIdToModulePath docId with
  | Some (_, "MiloneOnly") -> true
  | _ -> false

// ---------------------------------------------
// ProjectAnalysis
// ---------------------------------------------

type private ProjectDir = string

// FIXME: remove doc helpers
let private locOfDocPos (docId: DocId) (pos: Pos) : Loc =
  let y, x = pos
  Loc(docId, y, x)

let private locToDoc (loc: Loc) : DocId =
  let (Loc (docId, _, _)) = loc
  docId

let private locToPos (loc: Loc) : Pos =
  let (Loc (_, y, x)) = loc
  y, x

let private locToDocPos (loc: Loc) : DocId * Pos =
  let (Loc (docId, y, x)) = loc
  docId, (y, x)

let private doFindRefs hint docId targetPos pa =
  debugFn "doFindRefs %s" hint
  let tokens, pa = ProjectAnalysis1.tokenize docId pa
  let tokenOpt = tokens |> LTokenList.findAt targetPos

  match tokenOpt with
  | None ->
    debugFn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
    None, pa

  | Some token ->
    let tokenLoc = locOfDocPos docId (LToken.getPos token)
    debugFn "%s: tokenLoc=%A" hint tokenLoc

    let result, pa = pa |> ProjectAnalysis1.bundle

    match pa |> ProjectAnalysis1.collectSymbols result with
    | None ->
      let errorCount =
        result |> BundleResult.getErrors |> List.length

      debugFn "%s: no bundle result: errors %d" hint errorCount
      None, pa

    | Some symbols ->
      match symbols
            |> List.tryFind (fun (_, _, loc) -> loc = tokenLoc)
        with
      | None ->
        debugFn "%s: no symbol" hint
        None, pa

      | Some (targetSymbol, _, _) ->
        let result =
          symbols
          |> List.filter (fun (symbol, _, _) -> symbol = targetSymbol)

        Some result, pa

let private doFindDefsOrUses hint docId targetPos includeDef includeUse pa =
  match doFindRefs hint docId targetPos pa with
  | None, pa -> None, pa

  | Some symbols, pa ->
    let result, pa =
      symbols
      |> Seq.toList
      |> List.fold
           (fun map (_, defOrUse, loc) ->
             match defOrUse with
             | Def when not includeDef -> map
             | Use when not includeUse -> map

             | _ -> map |> Multimap.add (locToDoc loc) (locToPos loc))
           (TMap.empty compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, posList) ->
             let tokens, pa = ProjectAnalysis1.tokenize docId pa

             let ranges =
               tokens |> LTokenList.resolveRanges posList

             (docId, ranges), pa)
           pa

    let result =
      result
      |> List.collect (fun (docId, ranges) -> ranges |> List.map (fun range -> docId, range))

    Some result, pa

module ProjectAnalysis =
  let validateProject (pa: ProjectAnalysis) : LError list * ProjectAnalysis =
    let result, pa = pa |> ProjectAnalysis1.bundle

    let errorListList, pa =
      result
      |> BundleResult.getErrors
      |> List.fold
           (fun map (msg, loc) ->
             let docId, pos = locToDocPos loc
             map |> Multimap.add docId (msg, pos))
           (TMap.empty compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, errorList) ->
             let tokens, pa = ProjectAnalysis1.tokenize docId pa

             // FIXME: parser reports error at EOF as y=-1. Fix up that here.
             let errorList =
               errorList
               |> List.map (fun (msg, pos) ->
                 let y, _ = pos

                 if y >= 0 then
                   msg, pos
                 else
                   match tokens |> LTokenList.tryLast with
                   | Some token ->
                     let y, _ = token |> LToken.getPos
                     msg, (y + 1, 0)

                   | _ -> msg, (0, 0))

             let posList = errorList |> List.map snd

             let rangeMap =
               tokens
               |> LTokenList.resolveRanges posList
               |> Seq.map (fun (l, r) -> l, r)
               |> Seq.toList
               |> TMap.ofList compare

             let locList =
               errorList
               |> List.map (fun (msg, pos) ->
                 match rangeMap |> TMap.tryFind pos with
                 | Some r -> msg, (docId, pos, r)
                 | None -> msg, (docId, pos, pos))

             locList, pa)
           pa

    List.collect id errorListList, pa

  let completion
    (projectDir: ProjectDir)
    (docId: DocId)
    (targetPos: Pos)
    (pa: ProjectAnalysis)
    : string list * ProjectAnalysis =
    let tokens, pa = ProjectAnalysis1.tokenize docId pa

    let inModuleLine =
      let y, _ = targetPos

      tokens
      |> LTokenList.filterByLine y
      |> List.exists LToken.isModuleOrOpenKeyword

    let result =
      if inModuleLine then
        List.append (Map.toList stdLibProjects) (findModulesInDir projectDir)
        |> List.collect (fun (p, m) -> [ p; m ])
        |> listUnique
      else
        []

    result, pa

  /// `(defs, uses) option`
  let findRefs
    docId
    targetPos
    (pa: ProjectAnalysis)
    : ((DocId * Pos) list * (DocId * Pos) list) option * ProjectAnalysis =
    match doFindRefs "findRefs" docId targetPos pa with
    | Some symbols, pa ->
      let defs, uses =
        symbols
        |> List.fold
             (fun (defAcc, useAcc) (_, defOrUse, Loc (docId, y, x)) ->
               match defOrUse with
               | Def -> (docId, (y, x)) :: defAcc, useAcc
               | Use -> defAcc, (docId, (y, x)) :: useAcc)
             ([], [])

      Some(defs, uses), pa

    | None, pa -> None, pa

  /// `(reads, writes) option`
  let documentHighlight docId targetPos (pa: ProjectAnalysis) : (Range list * Range list) option * ProjectAnalysis =
    match doFindRefs "highlight" docId targetPos pa with
    | Some symbols, pa ->
      let reads, writes =
        symbols
        |> List.fold
             (fun (readAcc, writeAcc) (_, defOrUse, loc) ->
               if locToDoc loc = docId then
                 let pos = loc |> locToPos

                 match defOrUse with
                 | Def -> readAcc, pos :: writeAcc
                 | Use -> pos :: readAcc, writeAcc
               else
                 readAcc, writeAcc)
             ([], [])

      let tokens, pa = ProjectAnalysis1.tokenize docId pa

      let collect posList =
        tokens |> LTokenList.resolveRanges posList

      Some(collect reads, collect writes), pa

    | None, pa -> None, pa

  let hover (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : string option * ProjectAnalysis =
    let tokens, pa = ProjectAnalysis1.tokenize docId pa
    let tokenOpt = tokens |> LTokenList.findAt targetPos

    match tokenOpt with
    | None ->
      debugFn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
      None, pa

    | Some token ->
      let tokenLoc = locOfDocPos docId (LToken.getPos token)
      // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

      let result, pa = pa |> ProjectAnalysis1.bundle

      match ProjectAnalysis1.getTyName result tokenLoc pa with
      | None ->
        let errorCount =
          result |> BundleResult.getErrors |> List.length

        debugFn "hover: no bundle result: errors %d" errorCount
        None, pa

      | Some tyNameOpt -> tyNameOpt, pa

  let definition docId targetPos (pa: ProjectAnalysis) : (DocId * Range) list * ProjectAnalysis =
    let includeDef = true
    let includeUse = false

    let resultOpt, pa =
      doFindDefsOrUses "definition" docId targetPos includeDef includeUse pa

    Option.defaultValue [] resultOpt, pa

  let references docId targetPos (includeDef: bool) (pa: ProjectAnalysis) : (DocId * Range) list * ProjectAnalysis =
    let includeUse = true

    let resultOpt, pa =
      doFindDefsOrUses "references" docId targetPos includeDef includeUse pa

    Option.defaultValue [] resultOpt, pa

// ---------------------------------------------
// WorkspaceAnalysis
// ---------------------------------------------

type private FilePath = string
type private DocVersion = int

type private MiloneHome = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type WorkspaceAnalysisHost =
  { MiloneHome: MiloneHome
    DocIdToUri: ProjectInfo -> DocId -> Uri
    ReadSourceFile: string -> Future<string option> }

/// State of workspace-wide analysis.
/// That is, this is basically the root of state of LSP server.
///
/// Also has project-independent data such as parse result.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type WorkspaceAnalysis =
  { LastId: int
    Docs: TreeMap<Uri, DocVersion * string>
    ProjectList: ProjectInfo list
    Projects: TreeMap<string, ProjectAnalysis>

    // Per-file cache.
    TokenizeCache: TreeMap<DocId, DocVersion * LTokenList>
    ParseCache: TreeMap<DocId, DocVersion * LSyntaxData>

    // Diagnostics.
    DiagnosticsKeys: Uri list
    DiagnosticsCache: DiagnosticsCache<byte array>

    Host: WorkspaceAnalysisHost }

let private emptyWorkspaceAnalysis: WorkspaceAnalysis =
  { LastId = 0
    Docs = TMap.empty Uri.compare
    ProjectList = []
    Projects = TMap.empty compare

    TokenizeCache = TMap.empty compare
    ParseCache = TMap.empty compare

    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals

    Host =
      { MiloneHome = miloneHome
        DocIdToUri = doDocIdToUri
        ReadSourceFile = SyntaxApi.readSourceFile File.readTextFile } }

let private freshId (wa: WorkspaceAnalysis) =
  wa.LastId + 1, { wa with LastId = wa.LastId + 1 }

let private docIdToUri p docId (wa: WorkspaceAnalysis) = wa.Host.DocIdToUri p docId

let doWithProjectAnalysis
  (p: ProjectInfo)
  (action: ProjectAnalysis -> 'A * ProjectAnalysis)
  (wa: WorkspaceAnalysis)
  : 'A * WorkspaceAnalysis =
  let getVersion docId =
    match wa.Docs |> TMap.tryFind (docIdToUri p docId wa) with
    | Some (v, _) -> Some v

    | None ->
      traceFn "docs don't have '%s'" (docIdToUri p docId wa |> Uri.toString)
      None

  let tokenize1 docId =
    let version =
      getVersion docId |> Option.defaultValue 0

    match wa.ParseCache |> TMap.tryFind docId with
    | Some (v, syntaxData) when v >= version -> v, LSyntaxData.getTokens syntaxData

    | _ ->
      match wa.TokenizeCache |> TMap.tryFind docId with
      | Some ((v, _) as it) when v >= version -> it

      | _ ->
        let ok v text =
          traceFn "tokenize '%s' v:%d" docId v

          let tokens = LTokenList.tokenizeAll text

          v, tokens

        match wa.Docs |> TMap.tryFind (docIdToUri p docId wa) with
        | None ->
          traceFn
            "tokenize: docId:'%s' uri:'%s' not found -- fallback to file"
            docId
            (docIdToUri p docId wa |> Uri.toString)

          // FIXME: LSP server should add all files to docs before processing queries.
          let textOpt =
            SyntaxApi.readSourceFile File.readTextFile (docIdToFilePath p docId)
            |> Future.wait

          match textOpt with
          | None ->
            if docIdIsOptional docId |> not then
              warnFn "missing docId '%s' to be tokenized" docId

            -1, LTokenList.empty

          | Some text -> ok 0 text

        | Some (v, text) -> ok v text

  let parse1 docId =
    let version, tokens = tokenize1 docId

    match wa.ParseCache |> TMap.tryFind docId with
    | Some ((v, _) as it) when v >= version -> Some it

    | _ ->
      let v = version

      match docIdToModulePath docId with
      | None ->
        warnFn "illegal docId '%s'" docId
        None

      | Some (projectName, moduleName) ->
        traceFn "parse '%s' v:%d" docId v

        let syntaxData =
          LSyntaxData.parse projectName moduleName docId tokens

        Some(v, syntaxData)

  let host: ProjectAnalysisHost =
    { GetDocVersion = getVersion
      Tokenize = tokenize1
      Parse = parse1

      MiloneHome = wa.Host.MiloneHome
      ReadTextFile = File.readTextFile }

  let pa =
    match wa.Projects |> TMap.tryFind p.ProjectName with
    | Some it -> it |> ProjectAnalysis1.withHost host
    | None -> ProjectAnalysis1.create p.ProjectDir p.ProjectName host

  let result, pa = action pa

  // FIXME: store tokenize cache
  let _, newParseResults, pa = pa |> ProjectAnalysis1.drain

  let wa =
    newParseResults
    |> List.fold
         (fun (wa: WorkspaceAnalysis) (v, syntaxData) ->
           let docId = LSyntaxData.getDocId syntaxData
           let tokens = LSyntaxData.getTokens syntaxData

           { wa with
               TokenizeCache = wa.TokenizeCache |> TMap.add docId (v, tokens)
               ParseCache = wa.ParseCache |> TMap.add docId (v, syntaxData) })
         wa

  let wa =
    newParseResults
    |> List.map (fun (_, syntaxData) ->
      let docId = LSyntaxData.getDocId syntaxData
      docIdToUri p docId wa)
    |> List.filter (fun uri -> wa.Docs |> TMap.containsKey uri |> not)
    |> List.fold
         (fun (wa: WorkspaceAnalysis) uri ->
           // FIXME: don't read file
           // same as didOpenFile
           match uriToFilePath uri |> Option.bind File.tryReadFile with
           | Some text ->
             traceFn "file '%s' opened after bundle" (Uri.toString uri)
             { wa with Docs = wa.Docs |> TMap.add uri (0, text) }

           | None -> wa)
         wa

  let wa =
    { wa with Projects = wa.Projects |> TMap.add p.ProjectName pa }

  result, wa

module WorkspaceAnalysis =
  let empty: WorkspaceAnalysis = emptyWorkspaceAnalysis

  let didOpenDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
    { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

  let didChangeDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
    { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

  let didCloseDoc (uri: Uri) (wa: WorkspaceAnalysis) =
    // FIXME: drop tokenize/parse result
    let _, docs = wa.Docs |> TMap.remove uri
    { wa with Docs = docs }

  let didOpenFile (uri: Uri) (wa: WorkspaceAnalysis) =
    // FIXME: don't read file
    match uriToFilePath uri |> Option.bind File.tryReadFile with
    | Some text ->
      let version, wa = freshId wa
      didOpenDoc uri version text wa

    | None -> wa

  let didChangeFile (uri: Uri) (wa: WorkspaceAnalysis) =
    // FIXME: don't read file
    match uriToFilePath uri |> Option.bind File.tryReadFile with
    | Some text ->
      let version, wa = freshId wa
      didChangeDoc uri version text wa

    | None -> wa

  let didCloseFile (uri: Uri) (wa: WorkspaceAnalysis) = didCloseDoc uri wa

  let validateProject (p: ProjectInfo) (wa: WorkspaceAnalysis) =
    doWithProjectAnalysis p ProjectAnalysis.validateProject wa

  let validateAllProjects (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p ->
             let result, wa = validateProject p wa
             (p, result), wa)
           wa

    let diagnostics =
      results
      |> Seq.collect (fun (p, errors) ->
        errors
        |> Seq.map (fun (msg, (docId, start, endPos)) ->
          let uri = docIdToUri p docId wa
          msg, uri, start, endPos))
      |> Seq.toList

    let diagnostics, diagnosticsKeys, diagnosticsCache =
      aggregateDiagnostics wa.DiagnosticsKeys wa.DiagnosticsCache diagnostics

    let wa =
      { wa with
          DiagnosticsKeys = diagnosticsKeys
          DiagnosticsCache = diagnosticsCache }

    diagnostics, wa

  let completion (uri: Uri) (pos: Pos) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.completion p.ProjectDir (uriToDocId uri) pos) wa)
           wa

    List.collect id results, wa

  let documentHighlight (uri: Uri) (pos: Pos) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.documentHighlight (uriToDocId uri) pos) wa)
           wa

    let reads, writes = List.choose id results |> List.unzip

    List.collect id reads, List.collect id writes, wa

  let hover (uri: Uri) (pos: Pos) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.hover (uriToDocId uri) pos) wa) wa

    List.choose id results, wa

  let definition (uri: Uri) (pos: Pos) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p ->
             let result, wa =
               wa
               |> doWithProjectAnalysis p (ProjectAnalysis.definition (uriToDocId uri) pos)

             (p, result), wa)
           wa

    let result =
      results
      |> List.collect (fun (p, result) ->
        result
        |> List.map (fun (docId, range) -> docIdToUri p docId wa, range))

    result, wa

  let references (uri: Uri) (pos: Pos) (includeDecl: bool) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p ->
             let result, wa =
               wa
               |> doWithProjectAnalysis p (ProjectAnalysis.references (uriToDocId uri) pos includeDecl)

             (p, result), wa)
           wa

    let result =
      results
      |> List.collect (fun (p, result) ->
        result
        |> List.map (fun (docId, range) -> docIdToUri p docId wa, range))

    result, wa

let mutable private current = emptyWorkspaceAnalysis

let onInitialized rootUriOpt : unit =
  let projects =
    match rootUriOpt with
    | Some rootUri -> doFindProjects rootUri
    | None -> []

  infoFn "findProjects: %A" (List.map (fun (p: ProjectInfo) -> p.ProjectDir) projects)
  current <- { current with ProjectList = projects }

let didOpenDoc uri version text : unit =
  traceFn "didOpenDoc %s v:%d" (Uri.toString uri) version
  current <- WorkspaceAnalysis.didOpenDoc uri version text current

let didChangeDoc uri version text : unit =
  traceFn "didChangeDoc %s v:%d" (Uri.toString uri) version
  current <- WorkspaceAnalysis.didChangeDoc uri version text current

let didCloseDoc uri : unit =
  traceFn "didCloseDoc %s" (Uri.toString uri)
  current <- WorkspaceAnalysis.didCloseDoc uri current

let didOpenFile uri : unit =
  traceFn "didOpenFile %s" (Uri.toString uri)
  current <- WorkspaceAnalysis.didOpenFile uri current

let didChangeFile uri : unit =
  traceFn "didChangeFile %s" (Uri.toString uri)
  current <- WorkspaceAnalysis.didChangeFile uri current

let didCloseFile uri : unit =
  traceFn "didCloseFile %s" (Uri.toString uri)
  current <- WorkspaceAnalysis.didCloseDoc uri current

/// Validate all projects in workspace to report errors.
let validateWorkspace () =
  let diagnostics, wa =
    WorkspaceAnalysis.validateAllProjects current

  current <- wa
  diagnostics

let completion uri pos =
  let result, wa =
    WorkspaceAnalysis.completion uri pos current

  current <- wa
  result

let documentHighlight uri pos =
  let reads, writes, wa =
    current
    |> WorkspaceAnalysis.documentHighlight uri pos

  current <- wa
  reads, writes

let hover uri pos =
  let result, wa =
    current |> WorkspaceAnalysis.hover uri pos

  current <- wa
  result

let definition uri pos =
  let result, wa =
    current |> WorkspaceAnalysis.definition uri pos

  current <- wa
  result

let references uri pos (includeDecl: bool) =
  let result, wa =
    current
    |> WorkspaceAnalysis.references uri pos includeDecl

  current <- wa
  result

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FormattingResult = { Edits: (Range * string) list }

// FIXME: compute diff
let private formattingResultOfDiff _prev next : FormattingResult =
  { Edits = [ ((0, 0), (1100100100, 0)), next ] }

let formatting (uri: Uri) : FormattingResult option =
  let wa = current

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
      match wa.Docs |> TMap.tryFind uri with
      | Some (_, text) -> Some text
      | _ -> None

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
    finally
      try
        File.Delete(temp)
      with
      | ex -> warnFn "failed deleting temporary file '%s': %O" temp ex

  | None -> None
