module rec MiloneLspServer.LspUtil

open MiloneShared.SharedTypes
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

[<NoEquality; NoComparison>]
type DiagnosticsCache<'H> =
  | DiagnosticsCache of files: TreeMap<Uri, 'H> * hasher: (string -> 'H) * hashEquals: ('H -> 'H -> bool)

module DiagnosticsCache =
  type private Diagnostics = (Uri * (string * Pos) list) list

  let empty (hasher: string -> 'H) (hashEquals: 'H -> 'H -> bool) : DiagnosticsCache<'H> =
    DiagnosticsCache(TMap.empty Uri.compare, hasher, hashEquals)

  /// Filters to reduce diagnostics by using caches.
  let filter (diagnostics: Diagnostics) (cache: DiagnosticsCache<'H>) : Diagnostics * DiagnosticsCache<'H> =
    let (DiagnosticsCache (fileMap, hasher, hashEquals)) = cache

    let hashErrors errors =
      errors
      |> List.fold
           (fun acc (msg, (y, x)) ->
             acc
             |> cons (string y)
             |> cons ":"
             |> cons (string x)
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

  let find (uri: Uri) (docs: Docs) : DocData option =
    traceFn "Doc find uri:'%A'" (string uri)
    docs |> TMap.tryFind uri

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
