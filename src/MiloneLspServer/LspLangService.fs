module MiloneLspServer.LspLangService

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneStd.StdError
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi

module C = MiloneStd.StdChar
module S = MiloneStd.StdString

type private DocVersion = int
type private FilePath = string
type private ProjectDir = string
type private MiloneHome = string
type private FileExistsFun = FilePath -> bool
type private ReadTextFileFun = FilePath -> Future<string option>
type private DocIdToFilePathFun = ProjectDir -> DocId -> string
type private DirEntriesFun = string -> string list * string list
type private ReadSourceFileFun = FilePath -> Future<string option>

let MinVersion: DocVersion = 0
let InitialVersion: DocVersion = 1
let DocBaseVersion: DocVersion = 0x8000

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

let private splitAt (i: int) (s: string) =
  if i <= 0 then "", s
  else if s.Length <= i then s, ""
  else s.[0..i - 1], s.[i..s.Length - 1]

let private upperFirst (s: string) =
  if s.Length >= 1 && C.isLower s.[0] then
    string (C.toUpper s.[0]) + s.[1..s.Length - 1]
  else
    s

let private lowerFirst (s: string) =
  if s.Length >= 1 && C.isUpper s.[0] then
    string (C.toLower s.[0]) + s.[1..s.Length - 1]
  else
    s

let private tryReplace (pattern: string) (target: string) (s: string) =
  if s |> S.contains pattern then
    s |> S.replace pattern target, true
  else
    s, false

let private trimEndSep (path: string) = S.trimEndIf (fun c -> c = '/') path

let private pathJoin l r = l + "/" + r

let dirname (path: string) =
  let rec go (s: string) =
    match S.findLastIndex "/" s with
    | None
    | Some 0 -> None

    | Some i when i = s.Length - 1 -> go (S.truncate (s.Length - 1) s)

    | Some i -> S.truncate i s |> Some

  path |> trimEndSep |> go

let basename (path: string) =
  match S.findLastIndex "/" path with
  | Some i when path <> "/" -> S.skip (i + 1) path
  | _ -> path

let private stem (path: string) =
  let path = basename path

  match S.findLastIndex "." path with
  | Some i when 0 < i && i + 1 < path.Length -> S.slice 0 i path
  | _ -> path

let private hasDriveLetter (path: string) =
  path.Length >= 2
  && C.isAlphabetic path.[0]
  && path.[1] = ':'

let private isRooted (path: string) =
  path |> S.startsWith "/" || hasDriveLetter path

let private stripRoot (path: string) =
  let path, rooted = path |> S.stripStart "/"

  if rooted then
    Some "/", path
  else if path.Length >= 3
          && hasDriveLetter path
          && path.[2] = '/' then
    let root, rest = splitAt 3 path
    Some root, rest
  else
    None, path

let private pathContract (path: string) =
  let rec go acc (xs: string list) =
    match acc, xs with
    | _, "." :: xs -> go acc xs
    | _ :: acc, ".." :: xs -> go acc xs

    | _, [] -> acc
    | _, x :: xs -> go (x :: acc) xs

  match stripRoot path with
  | _, "" -> path

  | rootOpt, path ->
    let path =
      path
      |> S.split "/"
      |> go []
      |> List.rev
      |> S.concat "/"

    (rootOpt |> Option.defaultValue "") + path

/// Normalizes path syntactically. Note some of Windows prefix is unsupported yet.
let normalize (path: string) =
  let path = path |> S.replace "\\" "/"

  let path =
    let rec removeDoubleSlashes (s: string) =
      let s, ok = s |> tryReplace "//" "/"
      if ok then removeDoubleSlashes s else s

    removeDoubleSlashes path

  let path = path |> trimEndSep

  // Upper drive letter.
  let path =
    if path |> hasDriveLetter then
      upperFirst path
    else
      path

  pathContract path

let private getExt (path: string) =
  let path = basename path

  match S.findLastIndex "." path with
  | Some i when 0 < i && i < path.Length -> Some(S.skip i path)
  | _ -> None

let uriOfFilePath (path: string) =
  let path = normalize path

  if path |> S.startsWith "/" then
    Uri("file://" + path)
  else if hasDriveLetter path then
    let path =
      path |> lowerFirst |> S.replace ":" "%3A"

    Uri("file:///" + path)
  else
    // unlikely used
    Uri("file://./" + path)

// Note: pathname contains backslashes even on Linux, provided by VSCode.
let private uriToFilePath (uri: Uri) =
  let path, fileScheme =
    uri |> Uri.toString |> S.stripStart "file://"

  if fileScheme then
    let path =
      // Windows path.
      if path |> S.skip 2 |> S.startsWith "%3A" then
        path |> S.skip 1 |> S.replace "%3A" ":"
      else
        path

    path |> normalize
  else
    // Not a file scheme.
    warnFn "Not file scheme: %s" path
    path

// -----------------------------------------------
// File search
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
               match getExt file with
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

let private isManifest (path: string) = basename path = "milone_manifest"

let private isEntrypoint (path: string) =
  match dirname path with
  | Some parent -> basename parent = stem path
  | None -> false

let private filePathToModulePath path =
  match dirname path with
  | Some parent -> Some(basename parent, stem path)
  | None -> None

let filePathToDocId (path: string) : DocId =
  let projectName =
    match dirname path with
    | Some path -> basename path
    | None -> "NoProject" // unlikely happen

  let moduleName = stem path

  Symbol.intern (projectName + "." + moduleName)

let private uriToDocId (uri: Uri) : DocId = uri |> uriToFilePath |> filePathToDocId

let private docIdToModulePath (docId: DocId) =
  match Symbol.toString docId |> S.split "." with
  | [ p; m ] -> Some(p, m)

  | _ ->
    traceFn "Not a docId of module file: '%s'" (Symbol.toString docId)
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

    | _ when fileExists (Symbol.toString docId) -> Symbol.toString docId
    | _ -> failwithf "Bad docId: '%A'" docId

  path |> normalize |> fixExt

// ---------------------------------------------
// ProjectAnalysis
// ---------------------------------------------

let private doFindRefs hint docId targetPos pa =
  traceFn "doFindRefs %s" hint
  let tokens, pa = ProjectAnalysis1.tokenize docId pa
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
             let docId, pos = Loc.toDocPos loc
             map |> Multimap.add docId (msg, pos))
           (TMap.empty Symbol.compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, errorList) ->
             let tokens, pa = ProjectAnalysis1.tokenize docId pa

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

  let completion modules (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : string list * ProjectAnalysis =
    let tokens, pa = ProjectAnalysis1.tokenize docId pa

    let inModuleLine =
      let y, _ = targetPos

      tokens
      |> LTokenList.filterByLine y
      |> List.exists LToken.isModuleOrOpenKeyword

    /// All project names and module names.
    let collectModuleNames () =
      modules
      |> List.collect (fun (p, m) -> [ p; m ])
      |> listUnique

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

            if Symbol.equals d docId
               && exclusion
                  |> List.exists (fun (y1, y2) -> y1 <= y && y < y2)
                  |> not then
              Some symbol
            else
              None)
          |> List.choose (fun symbol -> symbol |> Symbol.name bundleResult)

        result, pa

    if inModuleLine then
      collectModuleNames (), pa
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
               let d, pos = loc |> Loc.toDocPos

               if Symbol.equals d docId then
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
      debugFn "hover: token not found on position: docId=%A pos=%s" docId (Pos.toString targetPos)
      None, pa

    | Some token ->
      let tokenLoc = Loc.ofDocPos docId (LToken.getPos token)
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

    // Per-file cache.
    TokenizeCache: TreeMap<Uri, DocVersion * LTokenList>
    ParseCache: TreeMap<Uri, DocVersion * LSyntaxData>

    // Diagnostics.
    DiagnosticsKeys: Uri list
    DiagnosticsCache: DiagnosticsCache<byte array>

    RootUriOpt: Uri option
    StdLibFiles: FilePath list
    StdLibModules: (string * ProjectDir) list
    DocIdToFilePath: DocIdToFilePathFun
    ReadSourceFile: ReadSourceFileFun

    Host: WorkspaceAnalysisHost }

let private createWorkspaceAnalysis (host: WorkspaceAnalysisHost) : WorkspaceAnalysis =
  { LastId = 0
    Docs = TMap.empty Uri.compare
    ProjectList = []
    Projects = TMap.empty compare

    TokenizeCache = TMap.empty Uri.compare
    ParseCache = TMap.empty Uri.compare

    DiagnosticsKeys = []
    DiagnosticsCache = DiagnosticsCache.empty Md5Helper.ofString Md5Helper.equals

    RootUriOpt = None
    StdLibFiles = []
    StdLibModules = []
    DocIdToFilePath = fun _ _ -> unreachable ()
    ReadSourceFile = fun _ -> Future.just None

    Host = host }

let private freshId (wa: WorkspaceAnalysis) =
  wa.LastId + 1, { wa with LastId = wa.LastId + 1 }

let private docIdToFilePath (p: ProjectInfo) docId (wa: WorkspaceAnalysis) = wa.DocIdToFilePath p.ProjectDir docId

let private docIdToUri p docId (wa: WorkspaceAnalysis) =
  docIdToFilePath p docId wa |> uriOfFilePath

let private readTextFile path (wa: WorkspaceAnalysis) =
  wa.Host.ReadTextFile path |> Future.wait // #avoidBlocking

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

let private doDidOpenDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didOpenDoc %s v:%d" (Uri.toString uri) version

  let version = version + DocBaseVersion
  { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

let private doDidOpenFile (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didOpenFile %s v:%d" (Uri.toString uri) version

  match wa.Docs |> TMap.tryFind uri with
  | Some (v, _) when v >= version -> wa
  | _ -> { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

let doDidChangeDoc (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didChangeDoc %s v:%d" (Uri.toString uri) version

  let version = version + DocBaseVersion
  { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

let doDidChangeFile (uri: Uri) (version: int) (text: string) (wa: WorkspaceAnalysis) =
  traceFn "didChangeFile %s v:%d" (Uri.toString uri) version

  match wa.Docs |> TMap.tryFind uri with
  | Some (v, _) when v >= version -> wa
  | _ -> { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

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
  |> List.fold (fun (wa: WorkspaceAnalysis) (uri, text) -> doDidOpenFile uri version text wa) wa

let private getDocVersion uri (wa: WorkspaceAnalysis) =
  match wa.Docs |> TMap.tryFind uri with
  | Some (v, _) -> v

  | None ->
    traceFn "docs don't have '%s'" (uri |> Uri.toString)
    MinVersion

let private tokenizeDoc uri (wa: WorkspaceAnalysis) =
  let version = getDocVersion uri wa

  match wa.ParseCache |> TMap.tryFind uri with
  | Some (v, syntaxData) when v = version ->
    let tokens = LSyntaxData.getTokens syntaxData
    Some(v, tokens)

  | _ ->
    match wa.TokenizeCache |> TMap.tryFind uri with
    | (Some (v, _)) as it when v = version -> it

    | _ ->
      let ok v text =
        traceFn "tokenize: '%s' v:%d" (Uri.toString uri) v
        let tokens = LTokenList.tokenizeAll text
        Some(v, tokens)

      match wa.Docs |> TMap.tryFind uri with
      | Some (v, text) -> ok v text

      | None ->
        debugFn "tokenize: '%s' not open" (Uri.toString uri)

        None

let private parseDoc (uri: Uri) (wa: WorkspaceAnalysis) =
  match tokenizeDoc uri wa with
  | Some (version, tokens) ->
    match wa.ParseCache |> TMap.tryFind uri with
    | (Some (v, _)) as it when v = version -> it

    | _ ->
      let v = version
      let docId = uri |> uriToFilePath |> filePathToDocId

      let projectName, moduleName =
        match docId |> docIdToModulePath with
        | Some it -> it
        | None -> unreachable () // docId is created in `p.m` format explicitly

      traceFn "parse '%A' v:%d" docId v

      let syntaxData =
        LSyntaxData.parse projectName moduleName docId tokens

      Some(v, syntaxData)

  | None -> None

let doWithProjectAnalysis
  (p: ProjectInfo)
  (action: ProjectAnalysis -> 'A * ProjectAnalysis)
  (wa: WorkspaceAnalysis)
  : 'A * WorkspaceAnalysis =
  let host: ProjectAnalysisHost =
    { GetDocVersion = fun docId -> getDocVersion (docIdToUri p docId wa) wa

      Tokenize =
        fun docId ->
          let uri = docIdToUri p docId wa

          tokenizeDoc uri wa
          |> Option.defaultValue (MinVersion, LTokenList.empty)

      Parse =
        fun docId ->
          let uri = docIdToUri p docId wa
          parseDoc uri wa

      MiloneHome = wa.Host.MiloneHome
      ReadTextFile = wa.Host.ReadTextFile }

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
           let uri = docIdToUri p docId wa

           { wa with
               TokenizeCache = wa.TokenizeCache |> TMap.add uri (v, tokens)
               ParseCache = wa.ParseCache |> TMap.add uri (v, syntaxData) })
         wa

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
      stdLibFiles
      |> List.choose (fun path -> path |> filePathToDocId |> docIdToModulePath)

    { wa with
        StdLibFiles = stdLibFiles
        StdLibModules = stdLibModules
        DocIdToFilePath = convertDocIdToFilePath host.FileExists (Map.ofList stdLibProjects)
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
      { wa with Docs = wa.Docs |> TMap.add uri (version, text) }

    | None ->
      // FIXME: drop tokenize/parse result
      let _, docs = wa.Docs |> TMap.remove uri
      { wa with Docs = docs }

  let didOpenFile (uri: Uri) (wa: WorkspaceAnalysis) =
    traceFn "didOpenFile %s" (Uri.toString uri)

    let path = uriToFilePath uri

    let wa =
      if isEntrypoint path || isManifest path then
        findProjects wa
      else
        wa

    // delay reading file
    if isManifest path |> not then
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
      // FIXME: remove tokenize/parse cache, same as closeDoc
      { wa with Docs = wa.Docs |> TMap.remove uri |> snd }
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

  let codeAction (uri: Uri) (range: Range) (wa: WorkspaceAnalysis) =
    let generateModuleHeadAction () =
      let title = "Generate module head"
      let front: Range = (0, 0), (0, 0)

      let isEmpty =
        match wa.Docs |> TMap.tryFind uri with
        | Some (_, text) -> text |> S.trimEnd |> S.isEmpty
        | None -> false

      let textOpt =
        if isEmpty then
          let path = uri |> uriToFilePath
          let parentOpt = dirname path
          let projectNameOpt = parentOpt |> Option.map basename
          let moduleName = path |> stem

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
        match parseDoc uri wa, uriToDocId uri |> docIdToModulePath with
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

      match parseDoc uri wa with
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
        match parseDoc uri wa with
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
              match parseDoc uri wa with
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

// -----------------------------------------------
// Formatting
// -----------------------------------------------

// spawns fantomas

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FormattingResult = { Edits: (Range * string) list }

// should compute diff
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
