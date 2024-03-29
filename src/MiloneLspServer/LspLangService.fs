module MiloneLspServer.LspLangService

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneSyntax.SyntaxTypes
open Std.StdError
open Std.StdMap
open Std.StdSet
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi
module SyntaxTreeGen = MiloneSyntax.SyntaxTreeGen

module S = Std.StdString

type private LError = string * Location
type private FileExistsFun = FilePath -> bool
type private ReadTextFileFun = FilePath -> Future<string option>
type private DirEntriesFun = string -> string list * string list
type private ReadSourceFileFun = FilePath -> Future<(string * string) option>

let private MinVersion: DocVersion = 0
let private DocBaseVersion: DocVersion = 0x8000

// -----------------------------------------------
// Util
// -----------------------------------------------

// FIXME: avoid using generic compare
let private listUnique xs =
  xs |> TSet.ofList compare |> TSet.toList

// -----------------------------------------------
// File search
// -----------------------------------------------

/// Whether dir is excluded in traversal?
let private dirIsExcluded (dir: string) =
  let name = Path.basename dir

  name.StartsWith(".")
  || name.Contains("~")
  || name = "node_modules"
  || name = "target"
  || name = "bin"
  || name = "obj"

let private findModulesRecursively (getDirEntries: DirEntriesFun) (maxDepth: int) (rootDir: string) : FilePath list =
  let rec bfs acc stack =
    match stack with
    | [] -> acc

    | (depth, dir) :: stack ->
      assert (depth <= maxDepth)

      let files, subdirs = getDirEntries dir

      let acc =
        files
        |> Seq.fold
             (fun acc file ->
               match Path.ext file with
               | Some ".milone"
               | Some ".fs" -> file :: acc

               | _ -> acc)
             acc

      let stack =
        if depth < maxDepth then
          subdirs
          |> Seq.filter (fun subdir -> subdir |> dirIsExcluded |> not)
          |> Seq.fold (fun stack subdir -> (depth + 1, subdir) :: stack) stack
        else
          stack

      bfs acc stack

  bfs [] [ 0, rootDir ]

// ---------------------------------------------
// Project
// ---------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectInfo =
  { ProjectDir: string
    ProjectName: string }

/// Finds all projects inside of the workspace.
let private doFindProjects fileExists getDirEntries (rootUri: Uri) : ProjectInfo list =
  let rootDir = rootUri |> uriToFilePath

  // Find projects recursively.
  let rec bfs acc stack =
    match stack with
    | [] -> acc

    | (depth, dir) :: stack ->
      let acc =
        let projectName = Path.stem dir

        let tryToProjectInfo ext =
          if fileExists (dir + "/" + projectName + ext) then
            let project: ProjectInfo =
              { ProjectDir = dir
                ProjectName = projectName }

            Some project
          else
            None

        match tryToProjectInfo ".milone" with
        | Some it -> it :: acc
        | None ->
          match tryToProjectInfo ".fs" with
          | Some it -> it :: acc
          | None -> acc

      let stack =
        if depth < 3 then
          let _, subdirs = getDirEntries dir

          subdirs
          |> Seq.filter (fun subdir -> subdir |> dirIsExcluded |> not)
          |> Seq.fold (fun stack subdir -> (depth + 1, subdir) :: stack) stack
        else
          stack

      bfs acc stack

  bfs [] [ 0, rootDir ]

let private isSourceFile (path: string) =
  match Path.ext path with
  | Some ".milone"
  | Some ".fs" -> true
  | _ -> false

let private isManifest (path: string) = Path.basename path = "milone_manifest"

let private isEntrypoint (path: string) =
  match Path.dirname path with
  | Some parent -> Path.basename parent = Path.stem path
  | None -> false

let private filePathToModulePath path =
  match Path.dirname path with
  | Some parent -> Some(Path.basename parent, Path.stem path)
  | None -> None

let private filePathToDocId (filePath: string) : DocId = AstBundle.computeDocId filePath

let private uriToDocId (uri: Uri) : DocId = uri |> uriToFilePath |> filePathToDocId

let private uriToModulePath (uri: Uri) : (ProjectName * ModuleName) option =
  uri |> uriToFilePath |> filePathToModulePath

// ---------------------------------------------
// ProjectAnalysis
// ---------------------------------------------

let private doFindRefs hint docId targetPos pa =
  traceFn "doFindRefs %s" hint
  let tokens = ProjectAnalysis1.getTokens docId pa
  let tokenOpt = tokens |> LTokenList.findAt targetPos

  match tokenOpt with
  | None ->
    debugFn "%s: token not found on position: docId=%A pos=%s" hint docId (Pos.toString targetPos)
    None, pa

  | Some token ->
    let tokenLoc = Loc.ofDocPos docId (LToken.getPos token)
    traceFn "%s: tokenLoc=%A" hint tokenLoc

    let result, pa = pa |> ProjectAnalysis1.bundle

    match pa |> ProjectAnalysis1.collectSymbols result with
    | None ->
      let errorCount =
        result |> BundleResult.getErrors |> List.length

      debugFn "%s: no bundle result: errors %d" hint errorCount
      None, pa

    | Some symbols ->
      match symbols
            |> List.tryFind (fun (_, _, loc) -> Loc.equals loc tokenLoc)
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

             | _ ->
               let docId, pos = Loc.toDocPos loc
               map |> Multimap.add docId pos)
           (TMap.empty Symbol.compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, posList) ->
             let tokens = ProjectAnalysis1.getTokens docId pa

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
             let docId, pos = Loc.toDocPos loc
             map |> Multimap.add docId (msg, pos))
           (TMap.empty Symbol.compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, errorList) ->
             let tokens = ProjectAnalysis1.getTokens docId pa

             // parser reports error at EOF as y=-1. Fix up that here.
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

  let completion modules (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : (int * string) list * ProjectAnalysis =
    let tokens = ProjectAnalysis1.getTokens docId pa

    let inModuleLine =
      let y, _ = targetPos

      tokens
      |> LTokenList.filterByLine y
      |> List.exists LToken.isModuleOrOpenKeyword

    // #CompletionItemKind
    /// All project names and module names.
    let collectModuleNames () =
      modules
      |> List.collect (fun (p, m) -> [ p; m ])
      |> List.map (fun text -> 9, text)
      |> listUnique

    let collectLocalSymbols pa =
      let hint = "completion"

      let drop y2 x2 stack exclusion =
        let rec go stack exclusion =
          match stack with
          | [] -> stack, exclusion
          | t :: ts ->
            let y1, x1 = t |> LToken.getPos

            if x1 <= x2 then
              stack, exclusion
            else
              go ts ((y1, y2) :: exclusion)

        go stack exclusion

      let rec go stack exclusion tokens =
        match tokens with
        | [] -> drop 0x7fff -1 stack exclusion |> snd

        | token :: tokens ->
          let y2, x2 = token |> LToken.getPos

          if y2 > (fst targetPos) then
            exclusion
          else if token |> LToken.isBindingKeyword then
            let stack, exclusion = drop y2 x2 stack exclusion
            go (token :: stack) exclusion tokens
          else
            go stack exclusion tokens

      let exclusion = go [] [] (tokens |> LTokenList.toList)

      let bundleResult, pa = pa |> ProjectAnalysis1.bundle

      match pa |> ProjectAnalysis1.collectSymbols bundleResult with
      | None ->
        let errorCount =
          bundleResult
          |> BundleResult.getErrors
          |> List.length

        debugFn "%s: no bundle result: errors %d" hint errorCount
        [], pa

      | Some symbols ->
        let result =
          symbols
          |> List.choose (fun (symbol, _, loc) ->
            let (Loc (d, y, _)) = loc

            if Symbol.equals d docId
               && exclusion
                  |> List.exists (fun (y1, y2) -> y1 <= y && y < y2)
                  |> not then
              Some symbol
            else
              None)
          |> List.choose (fun symbol ->
            match symbol |> Symbol.name bundleResult with
            | Some name ->
              // #CompletionItemKind (1: text)
              Some(1, name)

            | None -> None)

        result, pa

    if inModuleLine then
      collectModuleNames (), pa
    else
      match ProjectAnalysisCompletion.tryNsCompletion docId targetPos pa with
      | Some items, pa -> items, pa
      | None, pa ->
        match ProjectAnalysisCompletion.tryRecordCompletion docId targetPos pa with
        | Some items, pa -> items, pa
        | None, pa -> collectLocalSymbols pa

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
               let d, pos = loc |> Loc.toDocPos

               if Symbol.equals d docId then
                 match defOrUse with
                 | Def -> readAcc, pos :: writeAcc
                 | Use -> pos :: readAcc, writeAcc
               else
                 readAcc, writeAcc)
             ([], [])

      let tokens = ProjectAnalysis1.getTokens docId pa

      let collect posList =
        tokens |> LTokenList.resolveRanges posList

      Some(collect reads, collect writes), pa

    | None, pa -> None, pa

  // experimental: show syntax structure
  let hover2 (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : string option * ProjectAnalysis =
    let syntaxOpt = ProjectAnalysis1.getSyntax docId pa

    match syntaxOpt with
    | Some syntax ->
      let (SyntaxTree root) = syntax.SyntaxTree

      let getRange node =
        match node with
        | SyntaxToken (_, range) -> range
        | SyntaxNode (_, range, _) -> range

      let between range pos =
        let p, q = range
        Pos.compare p pos <= 0 && Pos.compare pos q < 0

      let rec go node =
        if between (getRange node) targetPos then
          match node with
          | SyntaxToken (kind, range) -> [ kind, range ]

          | SyntaxNode (kind, range, children) ->
            let childOpt =
              children
              |> List.tryFind (fun child -> between (getRange child) targetPos)

            match childOpt with
            | Some child -> (kind, range) :: go child
            | None -> [ kind, range ]
        else
          []

      go root
      |> List.map string
      |> S.concat "\n"
      |> Some,
      pa

    | None -> None, pa

  // current: show symbol type
  let hover1 (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : string option * ProjectAnalysis =
    let tokens = ProjectAnalysis1.getTokens docId pa
    let tokenOpt = tokens |> LTokenList.findAt targetPos

    match tokenOpt with
    | None ->
      debugFn "hover: token not found on position: docId=%A pos=%s" docId (Pos.toString targetPos)
      None, pa

    | Some token ->
      let tokenLoc = Loc.ofDocPos docId (LToken.getPos token)
      // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

      let result, pa = pa |> ProjectAnalysis1.bundle
      let tyNameOpt, pa = ProjectAnalysis1.getTyName tokenLoc pa

      match tyNameOpt with
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

  let documentSymbol docId pa =
    let syntaxOpt = ProjectAnalysis1.getSyntax docId pa

    let symbols =
      let pathToName path =
        path
        |> List.tryLast
        |> Option.defaultValue "<module>"

      syntaxOpt
      |> Option.map (fun syntax -> ProjectAnalysis1.documentSymbols syntax pa)
      |> Option.defaultValue []
      |> List.choose (fun (symbol, _, Loc (_, y, x)) ->
        let ok name kind = Some((name, kind), (y, x))

        match symbol with
        | DFunSymbol name -> ok name 12 // 12
        | DTySymbol name -> ok name 5 // class
        | DModuleSymbol path -> ok (pathToName path) 2 // module
        | _ -> None)

    let symbols, pa =
      let kinds, posList = List.unzip symbols

      let ranges, pa =
        let tokens = ProjectAnalysis1.getTokens docId pa
        tokens |> LTokenList.resolveRanges posList, pa

      let symbols =
        if List.length kinds = List.length ranges then
          List.zip kinds ranges
          |> List.map (fun ((name, kind), range) -> name, kind, range)
        else
          []

      symbols, pa

    symbols, pa

  let rename (docId: DocId) (targetPos: Pos) (newName: string) (pa: ProjectAnalysis) =
    let includeDef = true
    let includeUse = true

    let resultOpt, pa =
      doFindDefsOrUses "rename" docId targetPos includeDef includeUse pa

    let changes =
      resultOpt
      |> Option.defaultValue []
      |> List.map (fun (docId, range) -> docId, (range, newName))

    changes, pa

// ---------------------------------------------
// WorkspaceAnalysis
// ---------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type WorkspaceAnalysisHost =
  { MiloneHome: MiloneHome
    FileExists: FileExistsFun
    ReadTextFile: ReadTextFileFun
    DirEntries: DirEntriesFun }

module WorkspaceAnalysisHost =
  let dummy: WorkspaceAnalysisHost =
    { MiloneHome = "/$/.milone"
      FileExists = fun _ -> false
      ReadTextFile = fun _ -> Future.just None
      DirEntries = fun _ -> [], [] }

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

    /// Map from docId to absolute path.
    ///
    /// Although `DocId` is a symbol of that path and the mapping is redundant
    /// but it seems robust to not depend on toString method.
    DocToPathMap: TreeMap<DocId, FilePath>

    // Per-file cache.
    ParseCache: TreeMap<Uri, DocVersion * Lazy<LSyntaxData option>>

    // Diagnostics.
    DiagnosticsKeys: Uri list
    DiagnosticsCache: DiagnosticsCache<byte array>

    RootUriOpt: Uri option
    StdLibFiles: FilePath list
    StdLibModules: (ProjectName * ModuleName) list
    ReadSourceFile: ReadSourceFileFun

    Host: WorkspaceAnalysisHost }

module private WorkspaceAnalysis1 =
  let docIdToFilePath (docId: DocId) (wa: WorkspaceAnalysis) = wa.DocToPathMap |> TMap.tryFind docId

  let docIdToUri (docId: DocId) (wa: WorkspaceAnalysis) =
    wa.DocToPathMap
    |> TMap.tryFind docId
    |> Option.map uriOfFilePath

  let addDoc (uri: Uri) version text (wa: WorkspaceAnalysis) =
    let docId = uriToDocId uri

    let syntaxOptLazy =
      lazy (
        match uriToModulePath uri with
        | Some(projectName, moduleName) ->
          traceFn "parse '%A' v:%d" docId version
          LSyntax.parse projectName moduleName docId text |> Some

        | None ->
          debugFn "parse: Invalid URI: '%s'" (uriToFilePath uri)
          None
      )

    { wa with
        Docs = wa.Docs |> TMap.add uri (version, text)
        DocToPathMap =
          wa.DocToPathMap
          |> TMap.add docId (uriToFilePath uri)
        ParseCache =
          wa.ParseCache |> TMap.add uri (version, syntaxOptLazy) }

  let removeDoc (uri: Uri) (wa: WorkspaceAnalysis) =
    { wa with
        Docs = wa.Docs |> TMap.remove uri |> snd
        DocToPathMap =
          wa.DocToPathMap
          |> TMap.remove (uriToDocId uri)
          |> snd
        ParseCache =
          wa.ParseCache |> TMap.remove uri |> snd }

let private createWorkspaceAnalysis (host: WorkspaceAnalysisHost) : WorkspaceAnalysis =
  { LastId = 0
    Docs = TMap.empty Uri.compare
    ProjectList = []
    Projects = TMap.empty compare

    DocToPathMap = TMap.empty Symbol.compare

    ParseCache = TMap.empty Uri.compare

    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals

    RootUriOpt = None
    StdLibFiles = []
    StdLibModules = []
    ReadSourceFile = fun _ -> Future.just None

    Host = host }

let private freshId (wa: WorkspaceAnalysis) =
  wa.LastId + 1, { wa with LastId = wa.LastId + 1 }

let private readTextFile path (wa: WorkspaceAnalysis) =
  wa.Host.ReadTextFile path |> Future.wait // #avoidBlocking

/// Can send edits to a file?
///
/// Files inside a project directory can be edited.
let private isSafeToEdit (uri: Uri) (wa: WorkspaceAnalysis) =
  let dir =
    match Path.dirname (uriToFilePath uri) with
    | Some dir -> Path.stem dir
    | None -> ""

  wa.ProjectList
  |> List.exists (fun (p: ProjectInfo) ->
    p.ProjectName |> S.startsWith "Milone" |> not
    && dir = p.ProjectName)

let private doDidOpenDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didOpenDoc %s v:%d" (Uri.toString uri) version

  let version = version + DocBaseVersion
  WorkspaceAnalysis1.addDoc uri version text wa

let private doDidOpenFile (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didOpenFile %s v:%d" (Uri.toString uri) version

  match wa.Docs |> TMap.tryFind uri with
  | Some (v, _) when v >= version -> wa
  | _ -> WorkspaceAnalysis1.addDoc uri version text wa

let doDidChangeDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didChangeDoc %s v:%d" (Uri.toString uri) version

  let version = version + DocBaseVersion
  WorkspaceAnalysis1.addDoc uri version text wa

let doDidChangeFile (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didChangeFile %s v:%d" (Uri.toString uri) version

  match wa.Docs |> TMap.tryFind uri with
  | Some (v, _) when v >= version -> wa
  | _ -> WorkspaceAnalysis1.addDoc uri version text wa

let private findProjects (wa: WorkspaceAnalysis) =
  let projects =
    match wa.RootUriOpt with
    | Some rootUri -> doFindProjects wa.Host.FileExists wa.Host.DirEntries rootUri
    | None -> []

  { wa with ProjectList = projects }

let private openAllModules version (wa: WorkspaceAnalysis) =
  let filesInRoot =
    wa.RootUriOpt
    |> Option.map (fun rootUri -> findModulesRecursively wa.Host.DirEntries 3 (uriToFilePath rootUri))
    |> Option.defaultValue []

  List.append wa.StdLibFiles filesInRoot
  |> listUnique
  |> List.map (fun path ->
    let uri = uriOfFilePath path
    let textFut = wa.ReadSourceFile path

    textFut
    |> Future.map (fun textOpt -> textOpt |> Option.map (fun text -> uri, text)))
  |> List.choose Future.wait // #avoidBlocking
  |> List.fold (fun (wa: WorkspaceAnalysis) (uri, (_, text)) -> doDidOpenFile uri version text wa) wa

let private getDocEntry uri (wa: WorkspaceAnalysis) =
  match wa.Docs |> TMap.tryFind uri with
  | Some (v, text) -> v, text

  | None ->
    traceFn "docs don't have '%s'" (uri |> Uri.toString)
    MinVersion, ""

let private getDocSyntax (uri: Uri) (wa: WorkspaceAnalysis) : (DocVersion * LSyntax) option =
  let version, text = getDocEntry uri wa

  match wa.ParseCache |> TMap.tryFind uri with
  | Some (v, syntaxOptLazy) when v = version ->
    match syntaxOptLazy.Value with
    | Some syntax -> Some(v, syntax)
    | None -> None

  | _ ->
    debugFn "getDocSyntax: Doc not parsed: '%s'" (Uri.toString uri)
    None

let doWithProjectAnalysis
  (p: ProjectInfo)
  (action: ProjectAnalysis -> 'A * ProjectAnalysis)
  (wa: WorkspaceAnalysis)
  : 'A * WorkspaceAnalysis =
  let computeDocIdIn projectDir moduleName =
    let miloneOne =
      (projectDir + "/") + (moduleName + ".milone")

    let fsOne =
      (projectDir + "/") + (moduleName + ".fs")

    let miloneOneExists = wa.Docs |> TMap.containsKey (uriOfFilePath miloneOne)
    let fsOneExists = wa.Docs |> TMap.containsKey (uriOfFilePath fsOne)

    (if fsOneExists && not miloneOneExists then
       fsOne
     else
       miloneOne)
    |> filePathToDocId

  let host: ProjectAnalysisHost =
    { ComputeDocId =
        fun (projectName, moduleName, originDocId) ->
          let projectDir =
            match wa.StdLibModules
                  |> List.tryFind (fun (p, _) -> p = projectName)
              with
            | Some _ -> wa.Host.MiloneHome + "/src/" + projectName

            | None ->
              let containingDir =
                WorkspaceAnalysis1.docIdToFilePath originDocId wa
                |> Option.bind Path.dirname
                |> Option.bind Path.dirname
                |> Option.defaultValue ".."

              containingDir + "/" + projectName

          computeDocIdIn projectDir moduleName

      GetCoreDocId = fun moduleName -> computeDocIdIn (wa.Host.MiloneHome + "/src/MiloneCore") moduleName

      GetDocEntry =
        fun docId ->
          match WorkspaceAnalysis1.docIdToUri docId wa with
          | Some uri -> getDocEntry uri wa
          | None -> MinVersion, ""

      GetDocSyntax =
        fun docId ->
          WorkspaceAnalysis1.docIdToUri docId wa
          |> Option.bind (fun uri -> getDocSyntax uri wa)

      MiloneHome = wa.Host.MiloneHome
      ReadTextFile = wa.Host.ReadTextFile }

  let pa =
    match wa.Projects |> TMap.tryFind p.ProjectName with
    | Some it -> it |> ProjectAnalysis1.withHost host

    | None ->
      let entryDoc =
        let docId =
          computeDocIdIn p.ProjectDir p.ProjectName

        docId, p.ProjectName, p.ProjectName

      ProjectAnalysis1.create entryDoc p.ProjectDir p.ProjectName host

  let result, pa = action pa

  let wa =
    { wa with Projects = wa.Projects |> TMap.add p.ProjectName pa }

  result, wa

module WorkspaceAnalysis =
  let dummy: WorkspaceAnalysis =
    createWorkspaceAnalysis WorkspaceAnalysisHost.dummy

  let withHost (host: WorkspaceAnalysisHost) (wa: WorkspaceAnalysis) : WorkspaceAnalysis =
    let miloneHome = host.MiloneHome

    let stdLibProjects = SyntaxApi.getStdLibProjects miloneHome

    let stdLibFiles =
      stdLibProjects
      |> List.collect (fun (_, projectDir) -> findModulesRecursively host.DirEntries 3 projectDir)

    let stdLibModules =
      stdLibFiles |> List.choose filePathToModulePath

    { wa with
        StdLibFiles = stdLibFiles
        StdLibModules = stdLibModules
        ReadSourceFile = SyntaxApi.readSourceFile host.ReadTextFile
        Host = host }

  let create (host: WorkspaceAnalysisHost) : WorkspaceAnalysis = dummy |> withHost host

  let getProjectDirs (wa: WorkspaceAnalysis) =
    wa.ProjectList
    |> List.map (fun (p: ProjectInfo) -> p.ProjectDir)

  let onInitialized rootUriOpt (wa: WorkspaceAnalysis) : WorkspaceAnalysis =
    let wa = { wa with RootUriOpt = rootUriOpt }
    let version, wa = freshId wa
    wa |> findProjects |> openAllModules version

  let didOpenDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) = doDidOpenDoc uri version text wa

  let didChangeDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) = doDidChangeDoc uri version text wa

  let didCloseDoc (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didCloseDoc %s" (Uri.toString uri)

    let path = uriToFilePath uri

    // #avoidBlocking
    match wa.Host.ReadTextFile path |> Future.wait with
    | Some text ->
      // Re-open as file if exists.
      let version, wa = freshId wa
      WorkspaceAnalysis1.addDoc uri version text wa

    | None -> WorkspaceAnalysis1.removeDoc uri wa

  let didOpenFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didOpenFile %s" (Uri.toString uri)

    let path = uriToFilePath uri

    let wa =
      if isEntrypoint path || isManifest path then
        findProjects wa
      else
        wa

    // delay reading file
    if isSourceFile path && not (isManifest path) then
      match readTextFile (uriToFilePath uri) wa with
      | Some text ->
        let version, wa = freshId wa
        doDidOpenFile uri version text wa

      | None -> wa
    else
      wa

  let didChangeFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didChangeFile %s" (Uri.toString uri)

    let path = uriToFilePath uri

    if isManifest path |> not then
      // delay reading file
      match readTextFile path wa with
      | Some text ->
        let version, wa = freshId wa
        doDidChangeFile uri version text wa

      | None -> wa
    else
      wa

  let didCloseFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didCloseFile %s" (Uri.toString uri)

    let path = uriToFilePath uri

    let wa =
      if isEntrypoint path || isManifest path then
        findProjects wa
      else
        wa

    if isManifest path |> not then
      WorkspaceAnalysis1.removeDoc uri wa
    else
      wa

  let diagnostics (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p ->
             let result, wa =
               doWithProjectAnalysis p ProjectAnalysis.validateProject wa

             (p, result), wa)
           wa

    let diagnostics =
      results
      |> Seq.collect (fun (_, errors) ->
        errors
        |> Seq.choose (fun (msg, (docId, start, endPos)) ->
          match WorkspaceAnalysis1.docIdToUri docId wa with
          | Some uri -> Some(msg, uri, start, endPos)
          | None -> None))
      |> Seq.toList

    let diagnostics, diagnosticsKeys, diagnosticsCache =
      aggregateDiagnostics wa.DiagnosticsKeys wa.DiagnosticsCache diagnostics

    let wa =
      { wa with
          DiagnosticsKeys = diagnosticsKeys
          DiagnosticsCache = diagnosticsCache }

    diagnostics, wa

  let codeAction (uri: Uri) (range: Range) (wa: WorkspaceAnalysis) =
    let generateModuleHeadAction () =
      let title = "Generate module head"
      let front: Range = Range.zero

      let isEmpty =
        match wa.Docs |> TMap.tryFind uri with
        | Some (_, text) -> text |> S.trimEnd |> S.isEmpty
        | None -> false

      let textOpt =
        if isEmpty then
          let path = uri |> uriToFilePath
          let parentOpt = Path.dirname path
          let projectNameOpt = parentOpt |> Option.map Path.basename
          let moduleName = path |> Path.stem

          match projectNameOpt with
          | Some projectName ->
            sprintf "module rec %s.%s\n" projectName moduleName
            |> Some
          | None -> None
        else
          None

      match textOpt with
      | Some text -> Some(title, [ uri, [ front, text ] ])
      | None -> None

    // FIXME: store parse result to cache
    let generateOpenAction () =
      let title = "Generate open"
      let pos, _ = range
      let row, _ = pos

      let dotPosOpt tokens =
        tokens
        |> LTokenList.findAdjacent pos
        |> List.tryFind LToken.isDot

      let identOpt tokens =
        tokens
        |> LTokenList.filterByLine row
        |> List.rev
        |> List.skipWhile (fun token -> LToken.getPos token > pos)
        |> List.tryPick LToken.asIdent

      let nextOpenRow tokens =
        tokens
        |> LTokenList.toList
        |> List.groupBy (fun token -> token |> LToken.getPos |> fst)
        |> List.rev
        |> List.tryFind (fun (_, tokens) -> tokens |> List.exists LToken.isOpen)
        |> Option.map (fun (row, _) -> row + 1)
        |> Option.defaultValue 0

      let asOpenedModule usedModule uri =
        match getDocSyntax uri wa, uriToModulePath uri with
        | Some (_, syntax), Some (projectName, moduleName) ->
          if syntax
             |> LSyntaxData.findModuleDefs
             |> List.exists (fun name -> name = usedModule) then
            Some(projectName, moduleName)
          else
            None

        | _ -> None

      let newEdit tokens (projectName, moduleName) =
        let text =
          "open " + projectName + "." + moduleName + "\n"

        let row = nextOpenRow tokens

        let range: Range = (row, 0), (row, 0)
        title, [ uri, [ range, text ] ]

      match getDocSyntax uri wa with
      | Some (_, syntax) ->
        let tokens = syntax |> LSyntaxData.getTokens

        match dotPosOpt tokens, identOpt tokens with
        | Some _, Some usedModule ->
          wa.Docs
          |> TMap.toList
          |> List.tryPick (fun (uri, _) -> asOpenedModule usedModule uri)
          |> Option.map (newEdit tokens)
        | _ -> None
      | _ -> None

    // FIXME: store parse cache
    let generateModuleSynonymAction () =
      let title = "Generate module synonym"

      let opt =
        match getDocSyntax uri wa with
        | Some (_, syntax) ->
          let pos, _ = range
          let row, _ = pos

          let tokens = syntax |> LSyntaxData.getTokens

          let dotPosOpt =
            tokens
            |> LTokenList.findAdjacent pos
            |> List.tryFind LToken.isDot

          let identOpt =
            tokens
            |> LTokenList.filterByLine row
            |> List.rev
            |> List.skipWhile (fun token -> LToken.getPos token > pos)
            |> List.tryPick LToken.asIdent

          let lastModuleRow () =
            tokens
            |> LTokenList.toList
            |> List.groupBy (fun token -> token |> LToken.getPos |> fst)
            |> List.rev
            |> List.tryFind (fun (_, tokens) ->
              tokens |> List.exists LToken.isModule
              && tokens |> List.exists LToken.isEqual)
            |> Option.map (fun (row, _) -> row + 1)
            |> Option.defaultValue 0

          match dotPosOpt, identOpt with
          | Some _, Some ident ->
            wa.Docs
            |> TMap.toList
            |> List.tryPick (fun (uri, _) ->
              match getDocSyntax uri wa with
              | Some (_, syntax) ->
                syntax
                |> LSyntaxData.findModuleSynonyms
                |> List.tryFind (fun (name, _, _) -> name = ident)
                |> Option.map (fun (_, path, _) ->
                  "module "
                  + ident
                  + " = "
                  + (path |> S.concat ".")
                  + "\n")
                |> Option.map (fun text ->
                  let row = lastModuleRow ()
                  row, text)

              | None -> None)
          | _ -> None

        | None -> None

      match opt with
      | Some (row, text) ->
        let range: Range = (row, 0), (row, 0)
        Some(title, [ uri, [ range, text ] ])

      | None -> None

    let actions =
      [ generateModuleHeadAction ()
        generateOpenAction ()
        generateModuleSynonymAction () ]
      |> List.choose id

    actions, wa

  /// (projectName, moduleName) list
  let getModules (p: ProjectInfo) (wa: WorkspaceAnalysis) =
    wa.Docs
    |> TMap.toKeys
    |> List.choose (fun uri -> uri |> uriToFilePath |> filePathToModulePath)
    |> List.filter (fun (name, _) -> name = p.ProjectName)
    |> List.append wa.StdLibModules

  let completion (uri: Uri) (pos: Pos) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.completion (getModules p wa) (uriToDocId uri) pos) wa)
           wa

    let items = results |> List.collect id |> listUnique

    items, wa

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
      |> List.mapFold (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.hover1 (uriToDocId uri) pos) wa) wa

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
      |> List.collect (fun (_, result) ->
        result
        |> List.choose (fun (docId, range) ->
          match WorkspaceAnalysis1.docIdToUri docId wa with
          | Some uri -> Some(uri, range)
          | None -> None))

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
      |> List.collect (fun (_, result) ->
        result
        |> List.choose (fun (docId, range) ->
          match WorkspaceAnalysis1.docIdToUri docId wa with
          | Some docId -> Some(docId, range)
          | None -> None))

    result, wa

  let documentSymbol (uri: Uri) (wa: WorkspaceAnalysis) =
    let symbolListList, wa =
      wa.ProjectList
      |> List.mapFold (fun wa p -> doWithProjectAnalysis p (ProjectAnalysis.documentSymbol (uriToDocId uri)) wa) wa

    List.collect id symbolListList, wa

  let rename (uri: Uri) (pos: Pos) (newName: string) (wa: WorkspaceAnalysis) =
    let results, wa =
      wa.ProjectList
      |> List.mapFold
           (fun wa p ->
             let edits, wa =
               doWithProjectAnalysis p (ProjectAnalysis.rename (uriToDocId uri) pos newName) wa

             edits
             |> List.choose (fun (docId, edit) ->
               match WorkspaceAnalysis1.docIdToUri docId wa with
               | Some docId -> Some(docId, edit)
               | None -> None),
             wa)
           wa

    let changes =
      results
      |> List.collect id
      |> List.groupBy fst
      |> List.map (fun (uri, edits) -> uri, List.map snd edits)

    let ok =
      changes
      |> List.forall (fun (uri, _) -> isSafeToEdit uri wa)

    (if ok then changes else []), wa

  let syntaxTree (uri: Uri) (wa: WorkspaceAnalysis) : string option =
    match getDocSyntax uri wa with
    | Some(_, syntax) -> SyntaxTreeGen.dumpSyntaxTree syntax.FullTokens syntax.SyntaxTree |> Some
    | _ -> None

// -----------------------------------------------
// Formatting
// -----------------------------------------------

// To format, just spawns fantomas.
// Remarks:
//    When the server is executed as VSCode extension,
//    some environment variables are not inherited.

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FormattingResult = { Edits: (Range * string) list }

// should compute diff
let private formattingResultOfDiff _prev next : FormattingResult =
  { Edits = [ ((0, 0), (1100100100, 0)), next ] }

module Formatting =
  open System.Collections.Generic
  open System.Diagnostics
  open System.IO

  type private E = System.Environment

  let private dotnetCommand () =
    let c =
      E.GetEnvironmentVariable("MILONE_LSP_SERVER_DOTNET_COMMAND")

    if not (isNull c) then
      c
    else
      match E.OSVersion.Platform with
      | System.PlatformID.Win32NT -> "C:/Program Files/dotnet/dotnet.exe"
      | _ -> "/usr/share/dotnet/dotnet"

  let private homeDir () =
    E.GetFolderPath(E.SpecialFolder.UserProfile)

  let private toolDir () =
    Path.Combine(homeDir (), ".dotnet/tools")

  /// Don't invoke locally-installed fantomas-tool
  /// when working directory is in this set.
  let private denySet = HashSet<string>()

  let private runLocalFantomas (workDir: string) (temp: string) : bool =
    if denySet.Contains(workDir) |> not then
      try
        use proc =
          let startInfo = ProcessStartInfo()
          startInfo.FileName <- dotnetCommand ()
          startInfo.ArgumentList.Add("fantomas")
          startInfo.ArgumentList.Add(temp)
          startInfo.WorkingDirectory <- workDir
          startInfo.EnvironmentVariables.["DOTNET_CLI_HOME"] <- homeDir ()
          startInfo.EnvironmentVariables.["PATH"] <- ""
          startInfo.RedirectStandardOutput <- true
          Process.Start(startInfo)

        let exited = proc.WaitForExit(10 * 1000)
        let ok = exited && proc.ExitCode = 0

        if not exited then
          warnFn "Killing locally-installed fantomas as timeout."
          proc.Kill(entireProcessTree = true)

        if not ok then
          warnFn "Locally-installed fantomas failed."

        ok
      with
      | ex ->
        warnFn
          "fantomas-tool isn't locally installed. (%s)\nTo install: `dotnet new tool-manifest` and `dotnet tool install fantomas-tool`."
          ex.Message

        denySet.Add(workDir) |> ignore
        false
    else
      false

  let private runGlobalFantomas (workDir: string) (temp: string) : bool =
    try
      use proc =
        let startInfo = ProcessStartInfo()
        startInfo.FileName <- Path.Combine(toolDir (), "fantomas")
        startInfo.ArgumentList.Add(temp)
        startInfo.WorkingDirectory <- workDir
        startInfo.EnvironmentVariables.["DOTNET_CLI_HOME"] <- homeDir ()
        startInfo.EnvironmentVariables.["PATH"] <- ""
        startInfo.RedirectStandardOutput <- true
        Process.Start(startInfo)

      let exited = proc.WaitForExit(10 * 1000)
      let ok = exited && proc.ExitCode = 0

      if not exited then
        warnFn "Killing globally-installed fantomas as timeout."
        proc.Kill(entireProcessTree = true)

      if not ok then
        warnFn "Globally-installed fantomas failed."

      ok
    with
    | ex ->
      warnFn
        "fantomas-tool isn't globally installed. (%s)\nTo install globally, `dotnet tool -g install fantomas-tool`."
        ex.Message

      reraise ()

  let formatting (uri: Uri) (wa: WorkspaceAnalysis) : FormattingResult option =
    let filePath = uriToFilePath uri
    let dir = Path.GetDirectoryName(filePath)

    let temp =
      let basename =
        Path.GetFileNameWithoutExtension(filePath)

      let suffix = System.Guid.NewGuid().ToString()

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

      let ok =
        runLocalFantomas dir temp
        || runGlobalFantomas dir temp

      if ok then
        let newText = File.ReadAllText(temp)
        formattingResultOfDiff text newText |> Some
      else
        None
    finally
      try
        File.Delete(temp)
      with
      | ex -> warnFn "failed deleting temporary file '%s': %O" temp ex
