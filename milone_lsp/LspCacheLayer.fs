module rec MiloneLsp.LspCacheLayer

open System
open System.Security.Cryptography
open System.Text
open System.Threading
open MiloneLsp.Util
open MiloneLang.Syntax

let private md5Hasher =
  new ThreadLocal<MD5>(fun () -> MD5.Create())

let private hashEquals (l: byte array) (r: byte array): bool =
  ReadOnlySpan(l).SequenceEqual(ReadOnlySpan(r))

// -----------------------------------------------
// DiagnosticsCache
// -----------------------------------------------

type Diagnostics = (string * (string * Pos) list) list

type DiagnosticsCache = { Map: MutMap<string, byte array> }

module DiagnosticsCache =
  let empty (): DiagnosticsCache = { Map = MutMap() }

  /// Filters to reduce diagnostics by using caches.
  let filter (diagnostics: Diagnostics) (map: DiagnosticsCache): Diagnostics =
    let publish = ResizeArray()
    let sb = StringBuilder()
    let encoding = Encoding.Default
    let hasher = md5Hasher.Value

    for docId, errors in diagnostics do
      // Compute hash of errors.
      let newHash =
        sb.Clear() |> ignore

        for msg, pos in errors do
          let y, x = pos
          sb.Append(y).Append(',').Append(x).Append(',').AppendLine(msg)
          |> ignore

        hasher.ComputeHash(encoding.GetBytes(sb.ToString()))

      // Remove if unchanged.
      let oldHashOpt = map.Map |> MutMap.remove docId
      if oldHashOpt
         |> Option.forall (fun oldHash -> hashEquals oldHash newHash |> not) then
        publish.Add((docId, errors))

      // Update cache.
      if errors |> List.isEmpty |> not
      then map.Map |> MutMap.insert docId newHash |> ignore

    List.ofSeq publish
