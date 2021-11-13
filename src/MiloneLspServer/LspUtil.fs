module rec MiloneLspServer.LspUtil

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneLspServer.Util
open MiloneStd.StdMap

module S = MiloneStd.StdString

let private cons x y = x :: y

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
// DiagnosticsCache
// -----------------------------------------------

type private Pos = int * int
type private Error = string * Pos * Pos

[<NoEquality; NoComparison>]
type DiagnosticsCache<'H> =
  | DiagnosticsCache of files: TreeMap<Uri, 'H> * hasher: (string -> 'H) * hashEquals: ('H -> 'H -> bool)

module DiagnosticsCache =
  type private Diagnostics = (Uri * Error list) list

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
             let n1 = ly <<< 16 ||| lx
             let n2 = ry <<< 16 ||| rx
             let n = uint64 n1 <<< 32 ||| uint64 n2

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

let private compareError (_: string, l1, r1) (_: string, l2, r2) : int =
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
    |> List.fold (fun map (msg, uri, l, r) -> map |> multimapAdd uri (msg, l, r)) initMap
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
// Docs
// -----------------------------------------------

/// Text doc that is opened in editor.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type DocData =
  { /// Number to identify an edition of the document.
    Version: int
    Text: string }

type Docs = TreeMap<Uri, DocData>

module Docs =
  let empty: Docs = TMap.empty Uri.compare

  let private find (uri: Uri) (docs: Docs) : DocData option =
    traceFn "Doc find uri:'%A'" (string uri)
    docs |> TMap.tryFind uri

  let getVersion (uri: Uri) docs : int =
    match docs |> find uri with
    | Some d -> d.Version
    | None -> 0

  let getText (uri: Uri) docs : string option =
    match docs |> find uri with
    | Some d -> Some d.Text
    | None -> None

  let add (uri: Uri) (version: int) (text: string) (docs: Docs) =
    let docData: DocData = { Version = version; Text = text }

    debugFn "Doc opened uri:'%A' v:%d len:%d" uri version text.Length
    docs |> TMap.add uri docData

  let update (uri: Uri) (version: int) (text: string) (docs: Docs) : Docs =
    let docData: DocData = { Version = version; Text = text }

    debugFn "Doc changed uri:'%A' v:%d len:%d" uri version text.Length
    docs |> TMap.add uri docData

  let remove (uri: Uri) (docs: Docs) : Docs =
    debugFn "Doc closed uri:'%A'" uri
    docs |> TMap.remove uri |> snd
