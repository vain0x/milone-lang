/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module rec MiloneLang.Compatible

type AssocMap<'K, 'V> = (int * ('K * 'V) list) list * ('K -> int) * ('K -> 'K -> int)

type AssocSet<'K> = AssocMap<'K, unit>

let objToString (value: _) = string (value :> obj)

let inRegion (f: unit -> int): int = f ()

type Profiler = Profiler of System.Diagnostics.Stopwatch

let profileInit (): Profiler =
  Profiler(System.Diagnostics.Stopwatch.StartNew())

let profileLog (msg: string) (Profiler stopwatch): unit =
  let millis = int stopwatch.ElapsedMilliseconds
  eprintfn "profile: %4d.%03d %s" (millis / 1000) (millis % 1000) msg
  stopwatch.Restart()
