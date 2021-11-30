module MiloneLspServer.LspLangService

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi

module S = MiloneStd.StdString

type private DocVersion = int
type private FilePath = string
type private ProjectDir = string
type private MiloneHome = string
type private FileExistsFun = FilePath -> bool
type private DocIdToFilePathFun = ProjectDir -> DocId -> string
type private DirEntriesFun = string -> string list * string list
type private ReadSourceFileFun = FilePath -> Future<string option>

// -----------------------------------------------
// Util
// -----------------------------------------------

// FIXME: avoid using generic compare
let private listUnique xs =
  xs |> TSet.ofList compare |> TSet.toList

/// Reversed list.
type private RevList<'T> = 'T list

let rec private listAppend (acc: RevList<'T>) (xs: 'T list) : 'T list =
  match acc with
  | [] -> xs
  | x :: acc -> listAppend acc (x :: xs)

let private listPickWith (chooser: 'T -> 'U option) (xs: 'T list) : 'T RevList * ('U * 'T list) option =
  let rec go acc xs =
    match xs with
    | [] -> acc, None

    | x :: xs ->
      match chooser x with
      | None -> go (x :: acc) xs
      | Some u -> acc, Some(u, xs)

  go [] xs

let private listCutWith equals item xs : 'T RevList * 'T list * bool =
  let acc, restOpt =
    xs
    |> listPickWith (fun x -> if equals item x then Some() else None)

  match restOpt with
  | Some (_, rest) -> acc, rest, true
  | None -> acc, [], false

let private tryReplace (pattern: string) (target: string) (s: string) =
  if s |> S.contains pattern then
    s |> S.replace pattern target, true
  else
    s, false

let private trimEndSep (path: string) = S.trimEndIf (fun c -> c = '/') path

let private dirname (path: string) =
  let rec go (s: string) =
    match S.findLastIndex "/" s with
    | None
    | Some 0 -> None

    | Some i when i = s.Length - 1 -> go (S.truncate (s.Length - 1) s)

    | Some i -> S.truncate i s |> Some

  path |> trimEndSep |> go

let private basename (path: string) =
  match S.findLastIndex "/" path with
  | Some i -> S.skip (i + 1) path
  | None -> path

let private getExt (path: string) =
  let path = basename path

  match S.findLastIndex "." path with
  | Some i when 0 < i && i < path.Length -> Some(S.skip i path)
  | _ -> None

let private stem (path: string) =
  let path = basename path

  match S.findLastIndex "." path with
  | Some i when 0 < i && i < path.Length -> S.slice 0 i path
  | _ -> path

/// Normalizes path syntactically. Note Windows prefix is unsupported yet.
let private normalize (path: string) =
  let path = path |> S.replace "\\" "/"

  let path =
    let rec removeDoubleSlashes (s: string) =
      let s, ok = s |> tryReplace "//" "/"
      if ok then removeDoubleSlashes s else s

    removeDoubleSlashes path

  let path =
    if path |> S.startsWith "/" then
      path
    else
      "/" + path

  let rec collapseTwoDots (segments: string list) =
    match segments |> listCutWith (=) ".." with
    | _ :: acc, rest, true -> collapseTwoDots (listAppend acc rest)
    | _ -> segments

  path
  |> S.split "/"
  |> collapseTwoDots
  |> S.concat "/"

let uriOfFilePath (filePath: string) =
  let pathname =
    filePath |> normalize |> S.replace ":" "%3A"

  Uri("file://" + pathname)

let private uriToFilePath (uri: Uri) =
  let path, file =
    uri |> Uri.toString |> S.stripStart "file://"

  if file then
    // HOTFIX: On linux, path starts with \\ and is separated by \ for some reason.
    let path =
      path |> S.replace "\\\\" "/" |> S.replace "\\" "/"

    // HOTFIX: On Windows, path sometimes starts with an extra / and then it's invalid as file path; e.g. `/c:/Users/john/Foo/Foo.milone`.
    if path |> S.contains ":" then
      path |> S.stripStart "/" |> fst
    else
      path
  else
    path

// -----------------------------------------------
// Globals
// -----------------------------------------------

/// Whether dir is excluded in traversal?
let private dirIsExcluded (dir: string) =
  let name = basename dir

  name.StartsWith(".")
  || name.Contains("~")
  || name = "node_modules"
  || name = "target"
  || name = "bin"
  || name = "obj"

// ---------------------------------------------
// Standard libs
// ---------------------------------------------

let private findModulesRecursively getDirEntries (maxDepth: int) (rootDir: string) : (string * string) list =
  let rec bfs acc stack =
    match stack with
    | [] -> acc

    | (depth, dir) :: stack ->
      traceFn "in %d:%s" depth dir
      assert (depth <= maxDepth)

      let files, subdirs = getDirEntries dir

      let acc =
        let projectName = stem dir

        files
        |> Seq.fold
             (fun acc file ->
               match getExt file with
               | Some ".milone"
               | Some ".fs" ->
                 let moduleName = stem file
                 traceFn "in %s" moduleName
                 (projectName, moduleName) :: acc

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

let private findModulesInDir getDirEntries projectDir =
  findModulesRecursively getDirEntries 0 projectDir

// ---------------------------------------------
// Project
// ---------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectInfo =
  { ProjectDir: string
    ProjectName: string }

/// Finds all projects inside of the workspace.
let private doFindProjects fileExists getDirEntries (rootUri: string) : ProjectInfo list =
  let rootDir = Uri rootUri |> uriToFilePath

  // Find projects recursively.
  let rec bfs acc stack =
    match stack with
    | [] -> acc

    | (depth, dir) :: stack ->
      let acc =
        let projectName = stem dir

        let tryAddProject ext acc =
          if fileExists (dir + "/" + projectName + ext) then
            let project: ProjectInfo =
              { ProjectDir = dir
                ProjectName = projectName }

            project :: acc
          else
            acc

        acc
        |> tryAddProject ".milone"
        |> tryAddProject ".fs"

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

let private filePathToDocId (path: string) : DocId =
  let projectName =
    match dirname path with
    | Some path -> basename path
    | None -> "NoProject" // unlikely happen

  let moduleName = stem path

  projectName + "." + moduleName

let private uriToDocId (uri: Uri) : DocId = uri |> uriToFilePath |> filePathToDocId

let private docIdToModulePath (docId: DocId) =
  match docId.Split(".") with
  | [| p; m |] -> Some(p, m)

  | _ ->
    traceFn "Not a docId of module file: '%s'" docId
    None

let private convertDocIdToFilePath
  (fileExists: FileExistsFun)
  stdLibProjectMap
  (projectDir: ProjectDir)
  (docId: DocId)
  =
  let fixExt path =
    SyntaxApi.chooseSourceExt fileExists path

  let path =
    match docIdToModulePath docId with
    | Some (projectName, moduleName) ->
      let projectDir =
        match stdLibProjectMap |> Map.tryFind projectName with
        | Some it -> it
        | None -> projectDir + "/../" + projectName

      projectDir + "/" + moduleName + ".milone"

    | _ when fileExists docId -> docId
    | _ -> failwithf "Bad docId: '%s'" docId

  path |> normalize |> fixExt

let private docIdIsOptional docId =
  match docIdToModulePath docId with
  | Some (_, "MiloneOnly") -> true
  | _ -> false

// ---------------------------------------------
// ProjectAnalysis
// ---------------------------------------------

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
    stdLibModules
    getDirEntries
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

    let collectModuleNames pa =
      List.append stdLibModules (findModulesInDir getDirEntries projectDir)
      |> List.collect (fun (p, m) -> [ p; m ])
      |> listUnique,
      pa

    let beforeDot () =
      let y, x = targetPos

      let isTouched t =
        let _, x1 = t |> LToken.getPos
        x1 = x - 1 || x1 = x

      let rec go tokens =
        match tokens with
        | t1 :: t2 :: _ when t2 |> LToken.isDot && t2 |> isTouched -> t1 |> LToken.asIdent

        | [] -> None
        | _ :: ts -> go ts

      tokens |> LTokenList.filterByLine y |> go

    let collectNsSymbols qual pa =
      // FIXME: resolve `qual` as qualifier and collect symbols in its namespace
      [ qual + ".*" ], pa

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

            if d = docId
               && exclusion
                  |> List.exists (fun (y1, y2) -> y1 <= y && y < y2)
                  |> not then
              Some symbol
            else
              None)
          |> List.choose (fun symbol -> symbol |> Symbol.name bundleResult)

        result, pa

    if inModuleLine then
      collectModuleNames pa
    else
      // match beforeDot () with
      // | Some token -> collectNsSymbols token pa
      // | None -> collectLocalSymbols pa
      collectLocalSymbols pa

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

  let documentSymbol docId pa =
    let syntaxOpt, pa = ProjectAnalysis1.parse docId pa

    let symbols =
      let pathToName path =
        path
        |> List.tryLast
        |> Option.defaultValue "<module>"

      syntaxOpt
      |> Option.map (fun syntax -> ProjectAnalysis1.documentSymbols syntax pa)
      |> Option.defaultValue []
      |> List.map (fun (symbol, _, Loc (_, y, x)) ->
        let name, kind =
          match symbol with
          | DFunSymbol name -> name, 12 // 12
          | DTySymbol name -> name, 5 // class
          | DModuleSymbol path -> pathToName path, 2 // module

        (name, kind), (y, x))

    let symbols, pa =
      let kinds, posList = List.unzip symbols

      let ranges, pa =
        let tokens, pa = ProjectAnalysis1.tokenize docId pa
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
    DirEntries: DirEntriesFun }

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

    StdLibModules: (string * ProjectDir) list
    DocIdToFilePath: DocIdToFilePathFun
    ReadSourceFile: ReadSourceFileFun

    Host: WorkspaceAnalysisHost }

let private emptyWorkspaceAnalysis (host: WorkspaceAnalysisHost) : WorkspaceAnalysis =
  let miloneHome = host.MiloneHome
  let stdLibProjects = SyntaxApi.getStdLibProjects miloneHome

  let stdLibModules =
    stdLibProjects
    |> List.collect (fun (_, projectDir) -> findModulesInDir host.DirEntries projectDir)

  { LastId = 0
    Docs = TMap.empty Uri.compare
    ProjectList = []
    Projects = TMap.empty compare

    TokenizeCache = TMap.empty compare
    ParseCache = TMap.empty compare

    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals

    StdLibModules = stdLibModules
    DocIdToFilePath = convertDocIdToFilePath host.FileExists (Map.ofList stdLibProjects)
    ReadSourceFile = SyntaxApi.readSourceFile File.readTextFile

    Host = host }

let private freshId (wa: WorkspaceAnalysis) =
  wa.LastId + 1, { wa with LastId = wa.LastId + 1 }

let private docIdToFilePath (p: ProjectInfo) docId (wa: WorkspaceAnalysis) = wa.DocIdToFilePath p.ProjectDir docId

let private docIdToUri p docId (wa: WorkspaceAnalysis) =
  docIdToFilePath p docId wa |> uriOfFilePath

let private readSourceFile p docId (wa: WorkspaceAnalysis) =
  wa.ReadSourceFile(docIdToFilePath p docId wa)

/// Can send edits to a file?
///
/// Files inside a project directory can be edited.
let private isSafeToEdit (uri: Uri) (wa: WorkspaceAnalysis) =
  let dir =
    uriToFilePath uri
    |> dirname
    |> Option.map stem
    |> Option.defaultValue ""

  wa.ProjectList
  |> List.exists (fun (p: ProjectInfo) ->
    p.ProjectName |> S.startsWith "Milone" |> not
    && dir = p.ProjectName)

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
          let textOpt = readSourceFile p docId wa |> Future.wait

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
           match uriToFilePath uri |> File.tryReadFile with
           | Some text ->
             traceFn "file '%s' opened after bundle" (Uri.toString uri)
             { wa with Docs = wa.Docs |> TMap.add uri (0, text) }

           | None -> wa)
         wa

  let wa =
    { wa with Projects = wa.Projects |> TMap.add p.ProjectName pa }

  result, wa

module WorkspaceAnalysis =
  let empty (host: WorkspaceAnalysisHost) : WorkspaceAnalysis = emptyWorkspaceAnalysis host

  let didOpenDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
    traceFn "didOpenDoc %s v:%d" (Uri.toString uri) version
    { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

  let didChangeDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
    traceFn "didChangeDoc %s v:%d" (Uri.toString uri) version
    { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

  let didCloseDoc (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didCloseDoc %s" (Uri.toString uri)
    // FIXME: drop tokenize/parse result
    let _, docs = wa.Docs |> TMap.remove uri
    { wa with Docs = docs }

  let didOpenFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didOpenFile %s" (Uri.toString uri)
    // FIXME: don't read file
    match uriToFilePath uri |> File.tryReadFile with
    | Some text ->
      let version, wa = freshId wa
      didOpenDoc uri version text wa

    | None -> wa

  let didChangeFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didChangeFile %s" (Uri.toString uri)
    // FIXME: don't read file
    match uriToFilePath uri |> File.tryReadFile with
    | Some text ->
      let version, wa = freshId wa
      didChangeDoc uri version text wa

    | None -> wa

  let didCloseFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didCloseFile %s" (Uri.toString uri)
    didCloseDoc uri wa

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
           (fun wa p ->
             doWithProjectAnalysis
               p
               (ProjectAnalysis.completion wa.StdLibModules wa.Host.DirEntries p.ProjectDir (uriToDocId uri) pos)
               wa)
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
             |> List.map (fun (docId, edit) -> docIdToUri p docId wa, edit),
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

let onInitialized rootUriOpt (wa: WorkspaceAnalysis) : WorkspaceAnalysis =
  let projects =
    match rootUriOpt with
    | Some rootUri -> doFindProjects wa.Host.FileExists wa.Host.DirEntries rootUri
    | None -> []

  infoFn "findProjects: %A" (List.map (fun (p: ProjectInfo) -> p.ProjectDir) projects)
  { wa with ProjectList = projects }

// -----------------------------------------------
// Formatting
// -----------------------------------------------

// spawns fantomas

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FormattingResult = { Edits: (Range * string) list }

// FIXME: compute diff
let private formattingResultOfDiff _prev next : FormattingResult =
  { Edits = [ ((0, 0), (1100100100, 0)), next ] }

module Formatting =
  open System.Diagnostics
  open System.IO

  type E = System.Environment

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

      use proc =
        // When the server is executed as VSCode extension,
        // some environment variables are not inherited.

        let homeDir =
          E.GetFolderPath(E.SpecialFolder.UserProfile)

        let startInfo = ProcessStartInfo()
        startInfo.FileName <- "/usr/bin/dotnet"
        startInfo.ArgumentList.Add("fantomas")
        startInfo.ArgumentList.Add(temp)
        startInfo.WorkingDirectory <- dir
        startInfo.EnvironmentVariables.Add("DOTNET_CLI_HOME", homeDir)
        startInfo.EnvironmentVariables.Add("PATH", "/usr/bin")
        startInfo.RedirectStandardOutput <- true
        Process.Start(startInfo)

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
