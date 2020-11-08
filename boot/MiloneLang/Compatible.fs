/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module rec MiloneLang.Compatible

type AssocMap<'K, 'V> = (uint * ('K * 'V) list) list * ('K -> uint) * ('K -> 'K -> int)

type AssocSet<'K> = AssocMap<'K, unit>

let objToString (value: _) = string (value :> obj)

let inRegion (f: unit -> int): int = f ()

type Profiler = Profiler of System.Diagnostics.Stopwatch * int64 ref

let private getAllocatedBytes (): int64 =
  System.GC.GetAllocatedBytesForCurrentThread()

let profileInit (): Profiler =
  let bytesRef = getAllocatedBytes () |> ref
  Profiler(System.Diagnostics.Stopwatch.StartNew(), bytesRef)

let profileLog (msg: string) (Profiler (stopwatch, bytesRef)): unit =
  let millis = int stopwatch.ElapsedMilliseconds
  let sec = millis / 1000
  let millis = millis % 1000

  let totalBytes = getAllocatedBytes ()

  let bytes =
    (totalBytes - (!bytesRef)) |> int |> max 0

  let kilo = bytes / 1000
  let bytes = bytes % 1000
  let mega = kilo / 1000
  let kilo = kilo % 1000

  eprintfn "profile: time=%4d.%03d mem=%5d,%03d,%03d\n%s" sec millis mega kilo bytes msg

  stopwatch.Restart()
  bytesRef := totalBytes
