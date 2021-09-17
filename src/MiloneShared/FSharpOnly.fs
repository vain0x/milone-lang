/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module FSharpOnly

let objToString (value: _) = string (value :> obj)

let inRegion (f: unit -> int) : int = f ()

let __stringLengthInUtf8Bytes (s: string) : int =
  System.Text.Encoding.UTF8.GetByteCount(s)

// -----------------------------------------------
// Concurrency
// -----------------------------------------------

type Future<'T> = System.Threading.Tasks.ValueTask<'T>

module Future =
  open System.Threading.Tasks

  // .NET only
  let ofTask (task: Task<'T>) : Future<'T> = ValueTask<'T>(task)

  let just (value: 'T) : Future<'T> = ValueTask.FromResult(value)

  let map (f: 'T -> 'U) (task: Future<'T>) : Future<'U> =
    if task.IsCompletedSuccessfully then
      ValueTask.FromResult(f task.Result)
    else
      task
        .AsTask()
        .ContinueWith(fun (task: Task<_>) -> f task.Result)
      |> ofTask

  let andThen (f: 'T -> Future<'U>) (task: Future<'T>) : Future<'U> =
    if task.IsCompletedSuccessfully then
      f task.Result
    else
      task
        .AsTask()
        .ContinueWith(fun (task: Task<_>) -> (f task.Result).AsTask())
        .Unwrap()
      |> ofTask

  /// Spawns a task to run a complex computation. (.NET only)
  let spawn (f: unit -> Future<'T>) : Future<'T> =
    Task.Run<'T>(fun () -> (f ()).AsTask()) |> ofTask

/// Performs a concurrent work.
/// (mpsc: multiple producers single consumer)
///
/// What happens:
///
/// - For each `command`, a worker is spawned to compute `producer` function.
/// - Once a worker ends with an `action`, state is updated by `consumer` function.
/// - Final state is returned. (Function continues while any worker is running.)
let mpscConcurrent
  (consumer: 'S -> 'A -> 'S * 'T list)
  (producer: 'S -> 'T -> Future<'A option>)
  (initialState: 'S)
  (initialCommands: 'T list)
  : 'S =
  let chan =
    System.Threading.Channels.Channel.CreateUnbounded<'A>()

  let producerWork (state: 'S) (command: 'T) =
    Future.spawn
      (fun () ->
        producer state command
        |> Future.map
             (fun actionOpt ->
               match actionOpt with
               | Some action -> chan.Writer.TryWrite(action) |> ignore
               | None -> ()))
    |> ignore

  let consumerWork () =
    let mutable state = initialState
    let mutable commandCount = 0

    let spawn commands =
      for command in commands do
        commandCount <- commandCount + 1
        producerWork state command

    let update action =
      let newState, newCommands = consumer state action
      state <- newState
      spawn newCommands
      commandCount <- commandCount - 1

    spawn initialCommands

    while commandCount <> 0 do
      let action =
        let task = chan.Reader.ReadAsync()

        if task.IsCompletedSuccessfully then
          task.Result
        else
          task.AsTask().Result

      update action

    state

  consumerWork ()

// -----------------------------------------------
// C FFI
// -----------------------------------------------

/// `T const *` in C.
[<AbstractClass; Sealed>]
type __constptr<'T> =
  override _.ToString() = "__constptr is not available in F#"

  static member op_Implicit(_: __constptr<'T>) : int = 0
  static member op_Implicit(_: __constptr<'T>) : unativeint = unativeint 0

/// C-ABI function pointer type: `T (*)(params...)` in C.
///
/// P is `()` or `P1 * P2 * ...`.
[<AbstractClass; Sealed>]
type __nativeFun<'P, 'T> =
  override _.ToString() =
    failwith "__nativeFun type is not available in F#"

// Calls a C function, which should be linked statically.
let __nativeFun _ =
  failwith "__nativeFun is not available in F#"

// Casts a pointer, unchecked.
let __nativeCast _ =
  failwith "__nativeCast is not available in F#"

/// Accesses to `ptr[i]` to read a value.
let __ptrRead (_ptr: __constptr<'a>) (_index: int) : 'a =
  failwith "__ptrRead is not available in F#"

/// Writes a value to `ptr[i]`.
let __ptrWrite (_ptr: nativeptr<'a>) (_index: int) (_value: 'a) : unit =
  failwith "__ptrWrite is not available in F#"

// -----------------------------------------------
// Profiler
// -----------------------------------------------

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
