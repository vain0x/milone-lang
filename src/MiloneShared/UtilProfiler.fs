module MiloneShared.UtilProfiler

[<NoEquality; NoComparison>]
type Profiler =
  private
    { Stopwatch: System.Diagnostics.Stopwatch

      /// Message specified at the time of the previous logging.
      mutable Msg: string

      /// Elapsed milliseconds at the time of the previous logging.
      mutable Epoch: int

      /// Heap size (bytes) at the time of the previous logging.
      mutable Mem: int64 }

let private getAllocatedBytes () =
  System.GC.GetAllocatedBytesForCurrentThread()

let profileInit () : Profiler =
  { Stopwatch = System.Diagnostics.Stopwatch.StartNew()
    Msg = "start"
    Epoch = 0
    Mem = getAllocatedBytes () }

let private profilePrint (msg: string) (millis: int) (mem: int64) =
  let thousandSep (n: int64) =
    if n < 0L then
      " -0,000,000"
    else
      let k, n = n / 1000L, n % 1000L // kilo
      let m, k = k / 1000L, k % 1000L // mega
      sprintf "%3d,%03d,%03d" m k n

  let sec = millis / 1000
  let millis = millis % 1000 / 10 // per 10 ms

  eprintfn "profile: %-17s time=%4d.%02d mem=%s" msg sec millis (thousandSep mem)

let profileLog (msg: string) (p: Profiler) : unit =
  let epoch = int p.Stopwatch.ElapsedMilliseconds
  let mem = getAllocatedBytes ()

  let epochDelta = epoch - p.Epoch
  let memDelta = mem - p.Mem
  profilePrint p.Msg epochDelta memDelta

  p.Msg <- msg
  p.Epoch <- epoch
  p.Mem <- mem

  if msg = "Finish" then
    eprintfn "profile: Finish"
    profilePrint "total" epoch mem
