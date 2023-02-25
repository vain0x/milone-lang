module MiloneLspServer.LspUtil

open MiloneShared.SharedTypes
open MiloneShared.Util
open Std.StdMap
open Std.StdMultimap

module C = Std.StdChar
module S = Std.StdString
module SharedTypes = MiloneShared.SharedTypes

let private cons x y = x :: y

// Re-exports.
type RowIndex = SharedTypes.RowIndex
type Pos = SharedTypes.Pos

// -----------------------------------------------
// String
// -----------------------------------------------

module internal String =
  let tryReplace (pattern: string) (target: string) (s: string) =
    if s |> S.contains pattern then
      s |> S.replace pattern target, true
    else
      s, false

// Test tryReplace
do
  let s, ok =
    String.tryReplace "//" "/" "file:///foo"

  assert (s = "file://foo")
  assert ok

  let s, ok = String.tryReplace "//" "/" "./relative"
  assert (s = "./relative")
  assert (not ok)

// -----------------------------------------------
// Path
// -----------------------------------------------

module internal Path =
  let join l r = l + "/" + r

  let basename (path: string) =
    match S.findLastIndex "/" path with
    | Some i when path <> "/" -> S.skip (i + 1) path
    | _ -> path

  let dirname (path: string) =
    let trimEndSep (path: string) = S.trimEndIf (fun c -> c = '/') path

    let rec go (s: string) =
      match S.findLastIndex "/" s with
      | None
      | Some 0 -> None

      | Some i when i = s.Length - 1 -> go (S.truncate (s.Length - 1) s)

      | Some i -> S.truncate i s |> Some

    path |> trimEndSep |> go

  let stem (path: string) =
    let path = basename path

    match S.findLastIndex "." path with
    | Some i when 0 < i && i + 1 < path.Length -> S.slice 0 i path
    | _ -> path

  let ext (path: string) =
    let path = basename path

    match S.findLastIndex "." path with
    | Some i when 0 < i && i < path.Length -> Some(S.skip i path)
    | _ -> None

  let internal hasDriveLetter (path: string) =
    path.Length >= 2
    && C.isAlphabetic path.[0]
    && path.[1] = ':'

  let private isRooted (path: string) =
    path |> S.startsWith "/" || hasDriveLetter path

  let internal stripRoot (path: string) =
    let path, rooted = path |> S.stripStart "/"

    if rooted then
      Some "/", path
    else if path.Length >= 3
            && hasDriveLetter path
            && path.[2] = '/' then
      let root, rest = S.splitAt 3 path
      Some root, rest
    else
      None, path

  let internal pathContract (path: string) =
    let rec go acc (xs: string list) =
      match acc, xs with
      | _, "." :: xs -> go acc xs
      | x :: acc, ".." :: xs -> go acc xs

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
        let s, ok = s |> String.tryReplace "//" "/"
        if ok then removeDoubleSlashes s else s

      removeDoubleSlashes path

    // Upper drive letter.
    let path =
      if path |> hasDriveLetter then
        S.upperFirst path
      else
        path

    pathContract path

// testBasename
do
  assert (Path.basename "/root/rooted.milone" = "rooted.milone")
  assert (Path.basename "./parent/relative.milone" = "relative.milone")
  assert (Path.basename "../." = ".")
  assert (Path.basename "/" = "/")
  assert (Path.basename "" = "")
  assert (Path.basename "base" = "base")

// testStem
do
  assert (Path.stem "/root/rooted.milone" = "rooted")
  assert (Path.stem "../relative.milone" = "relative")
  assert (Path.stem ".git" = ".git")
  assert (Path.stem "." = ".")
  assert (Path.stem ".." = "..")
  assert (Path.stem "./no-ext" = "no-ext")
  assert (Path.stem "stem" = "stem")
  assert (Path.stem "ends-with-dot." = "ends-with-dot.")

// testStripRoot
do
  assert (Path.stripRoot "/" = (Some "/", ""))
  assert (Path.stripRoot "/rooted/path" = (Some "/", "rooted/path"))
  assert (Path.stripRoot "C:/drive/path" = (Some "C:/", "drive/path"))
  assert (Path.stripRoot "./relative/path" = (None, "./relative/path"))

// testContract
do
  assert (Path.pathContract "parent/./it" = "parent/it")
  assert (Path.pathContract "parent/sibling/../it" = "parent/it")
  assert (Path.pathContract "parent/s/t/../../it" = "parent/it")

  assert (Path.pathContract "./it" = "it")
  assert (Path.pathContract "../it" = "../it")

  assert (Path.pathContract "/./." = "/")
  assert (Path.pathContract "/.." = "/..")
  assert (Path.pathContract "/" = "/")
  assert (Path.pathContract "C:/.." = "C:/..")

// testNormalize
do
  assert (Path.normalize "double//slash" = "double/slash")
  assert (Path.normalize "back\\slash" = "back/slash")
  assert (Path.normalize "parent/two/../dots" = "parent/dots")
  assert (Path.normalize "single/./dot" = "single/dot")
  assert (Path.normalize "" = "")
  assert (Path.normalize "/regular/rooted.ext" = "/regular/rooted.ext")
  assert (Path.normalize "a\\b/\\c\\..\\\\d" = "a/b/d")
  assert (Path.normalize "c:\\Program Files\\Git" = "C:/Program Files/Git")

// -----------------------------------------------
// Location
// -----------------------------------------------

/// Increasing version ID of text document.
type DocVersion = int

/// Range of text. (Pair of begin-position and end-position. End is exclusive.)
type Range = Pos * Pos

/// Location of text document.
type Location = DocId * Pos * Pos

/// Pathname of file or directory.
type FilePath = string

/// Pathname of project directory.
type ProjectDir = string

/// Pathname of the milone system directory. ($MILONE_HOME)
type MiloneHome = string

module Range =
  let zero: Range = (0, 0), (0, 0)

  let toString (range: Range) =
    let ((y1, x1), (y2, x2)) = range
    sprintf "%d:%d-%d:%d" (y1 + 1) (x1 + 1) (y2 + 1) (x2 + 1)

// -----------------------------------------------
// URI
// -----------------------------------------------

[<NoComparison>]
type Uri = Uri of string

let private compareUri (Uri l) (Uri r) : int = compare l r

module Uri =
  let toString (Uri s) = s

  let compare = compareUri

// -----------------------------------------------
// URI <-> Path
// -----------------------------------------------

let uriOfFilePath (path: string) : Uri =
  let path = Path.normalize path

  if path |> S.startsWith "/" then
    Uri("file://" + path)
  else if Path.hasDriveLetter path then
    let path =
      path |> S.lowerFirst |> S.replace ":" "%3A"

    Uri("file:///" + path)
  else
    // unlikely used
    Uri("file://./" + path)

// Note: pathname contains backslashes even on Linux, provided by VSCode.
let uriToFilePath (uri: Uri) : string =
  let path, fileScheme =
    uri |> Uri.toString |> S.stripStart "file://"

  if fileScheme then
    let path =
      // Windows path.
      if path |> S.skip 2 |> S.startsWith "%3A" then
        path |> S.skip 1 |> S.replace "%3A" ":"
      else
        path

    path |> Path.normalize
  else
    failwithf "Not a file scheme: %A." uri

// testUriOfFilePath
do
  let f a x = uriOfFilePath a |> Uri.toString = x

  assert (f "/rooted/path" "file:///rooted/path")
  assert (f "slashed/path" "file://./slashed/path")
  assert (f "C:\\windows\\path" "file:///c%3A/windows/path")

// testUriToFilePath
do
  let f s x = uriToFilePath (Uri s) = x

  assert (f "file:///rooted/path" "/rooted/path")
  assert (f "file://\\backslash\\path" "/backslash/path")
  assert (f "file:///c%3A\\windows\\path" "C:/windows/path")

// -----------------------------------------------
// DiagnosticsCache
// -----------------------------------------------

type private AError = string * Pos * Pos
type private Diagnostics = (Uri * AError list) list

[<NoEquality; NoComparison>]
type DiagnosticsCache<'H> =
  | DiagnosticsCache of files: TreeMap<Uri, 'H> * hasher: (string -> 'H) * hashEquals: ('H -> 'H -> bool)

module DiagnosticsCache =
  let empty (hasher: string -> 'H) (hashEquals: 'H -> 'H -> bool) : DiagnosticsCache<'H> =
    DiagnosticsCache(TMap.empty Uri.compare, hasher, hashEquals)

  /// Filters to reduce diagnostics by using caches.
  let filter (diagnostics: Diagnostics) (cache: DiagnosticsCache<'H>) : Diagnostics * DiagnosticsCache<'H> =
    let (DiagnosticsCache (fileMap, hasher, hashEquals)) = cache

    let hashErrors errors =
      errors
      |> List.fold
           (fun acc (msg, l, r) ->
             let ly, lx = l
             let ry, rx = r
             let n1 = (ly <<< 16) ||| lx
             let n2 = (ry <<< 16) ||| rx
             let n = (uint64 n1 <<< 32) ||| uint64 n2

             acc
             |> cons (string n)
             |> cons "{"
             |> cons msg
             |> cons "}")
           []
      |> S.concat ""
      |> hasher

    let publishList, fileMap =
      diagnostics
      |> List.mapFold
           (fun fileMap (uri, errors) ->
             let newHash = hashErrors errors
             let oldHashOpt, fileMap = fileMap |> TMap.remove uri

             let changed =
               match oldHashOpt with
               | Some oldHash -> hashEquals oldHash newHash |> not
               | None -> true

             // Publish if changed.
             let publishOpt =
               if changed then
                 Some(uri, errors)
               else
                 None

             // Update cache.
             let fileMap =
               if errors |> List.isEmpty |> not then
                 fileMap |> TMap.add uri newHash
               else
                 fileMap

             publishOpt, fileMap)
           fileMap

    let publishList = publishList |> List.choose id

    let cache =
      DiagnosticsCache(fileMap, hasher, hashEquals)

    publishList, cache

let private compareError (l: AError) (r: AError) : int =
  let _, l1, r1 = l
  let _, l2, r2 = r

  let ly1, lx1 = l1
  let ly2, lx2 = l2

  if ly1 <> ly2 then
    compare ly1 ly2
  else if lx1 <> lx2 then
    compare lx1 lx2
  else
    let ry1, rx1 = r1
    let ry2, rx2 = r2

    if ry1 <> ry2 then
      compare ry1 ry2
    else
      compare rx1 rx2

/// Collect list of errors per file.
///
/// Note we need to report absence of errors for docs opened in editor
/// so that the editor clears outdated diagnostics.
/// `diagnosticsKeys` remember text doc URIs that
/// we reported some diagnostics previously (and yet cleared).
let aggregateDiagnostics diagnosticsKeys diagnosticsCache diagnostics =
  let diagnostics =
    let initMap: TreeMap<Uri, (string * Pos * Pos) list> =
      diagnosticsKeys
      |> List.map (fun uri -> uri, [])
      |> TMap.ofList Uri.compare

    diagnostics
    |> List.fold (fun map (msg, uri, l, r) -> map |> Multimap.add uri (msg, l, r)) initMap
    |> TMap.toList
    |> List.map (fun (uri, entries) -> uri, entries |> listSort compareError)

  let diagnosticsKeys =
    diagnostics
    |> List.choose (fun (uri, errors) ->
      if errors |> List.isEmpty |> not then
        Some uri
      else
        None)

  let diagnostics, diagnosticsCache =
    diagnosticsCache
    |> DiagnosticsCache.filter diagnostics

  diagnostics, diagnosticsKeys, diagnosticsCache

// -----------------------------------------------
// LineBuffer
// -----------------------------------------------

/// Text with line-oriented indexes.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LineBuffer =
  private
    { Text: string
      LineCount: int
      /// Line index → byte range.
      OffsetMap: TreeMap<int, int * int> }

module internal LineBuffer =
  let compute (text: string) : LineBuffer =
    let rec computeLoop acc y (i: int) =
      if i < text.Length then
        let j = text.IndexOf('\n', i)

        if j >= i then
          let r = if i < j && text.[j - 1] = '\r' then j - 1 else j
          computeLoop ((y, (i, r)) :: acc) (y + 1) (j + 1)
        else
          let acc = (y, (i, text.Length)) :: acc
          y + 1, acc
      else
        y, acc

    let lineCount, acc = computeLoop [] 0 0

    { Text = text
      LineCount = lineCount
      OffsetMap = TMap.ofList compare acc }

  let lineRangeAt index (buf: LineBuffer) =
    buf.OffsetMap |> TMap.tryFind index

  let lineStringAt index (buf: LineBuffer) =
    match buf.OffsetMap |> TMap.tryFind index with
    | Some (l, r) ->
      let r = if l < r && buf.Text.[r - 1] = '\r' then r - 1 else r
      buf.Text.[l..r - 1]

    | None -> ""

  let posToIndex (pos: Pos) (buf: LineBuffer) =
    let y, x = pos

    match lineRangeAt y buf with
    | Some (l, r) -> Some(l + min x r)
    | _ -> None

  let stringBetween (range: Range) (buf: LineBuffer) =
    let startPos, endPos = range

    match posToIndex startPos buf, posToIndex endPos buf with
    | Some l, Some r when l <= r -> buf.Text[l..r - 1]
    | _ -> ""
