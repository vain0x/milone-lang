module MiloneShared.UtilParallel

/// Whether parallel primitives work actually in parallel.
let mutable AllowParallel = false

type Future<'T> = System.Threading.Tasks.ValueTask<'T>

module Future =
  open System
  open System.Threading.Tasks

  // .NET only
  let inline ofTask (task: Task<'T>) : Future<'T> = ValueTask<'T>(task)

  // .NET only
  let internal unwrap (future: Future<'T>) =
    assert (not AllowParallel)
    assert future.IsCompletedSuccessfully
    future.Result

  let inline just (value: 'T) : Future<'T> = ValueTask.FromResult(value)

  let map (f: 'T -> 'U) (task: Future<'T>) : Future<'U> =
    if not AllowParallel || task.IsCompletedSuccessfully then
      ValueTask.FromResult(f task.Result)
    else
      task
        .AsTask()
        .ContinueWith((fun (task: Task<_>) -> f task.Result), TaskContinuationOptions.OnlyOnRanToCompletion)
      |> ofTask

  let andThen (f: 'T -> Future<'U>) (task: Future<'T>) : Future<'U> =
    if not AllowParallel || task.IsCompletedSuccessfully then
      f task.Result
    else
      task
        .AsTask()
        .ContinueWith((fun (task: Task<_>) -> (f task.Result).AsTask()), TaskContinuationOptions.OnlyOnRanToCompletion)
        .Unwrap()
      |> ofTask

  let whenAll (futureList: Future<'T> list) : Future<'T list> =
    if not AllowParallel then
      futureList |> List.map (fun (f: Future<_>) -> f.Result) |> just
    else
      (futureList |> List.map (fun (f: Future<_>) -> f.AsTask()) |> Task.WhenAll)
        .ContinueWith((fun (task: Task<_>) -> List.ofArray task.Result), TaskContinuationOptions.OnlyOnRanToCompletion)
      |> ofTask

  /// Waits for a future to complete.
  let wait (future: Future<'T>) : 'T = future.AsTask().Result

  // .NET only
  let internal ofUnitValueTask (task: ValueTask) : ValueTask<unit> =
    if not AllowParallel || task.IsCompletedSuccessfully then
      ValueTask<unit>(())
    else
      ValueTask<unit>(
        task
          .AsTask()
          .ContinueWith(Func<_, unit>(fun _ -> ()), TaskContinuationOptions.OnlyOnRanToCompletion)
      )

  /// Spawns a task to run a complex computation. (.NET only)
  let internal spawn (f: unit -> Future<'T>) : Future<'T> =
    if not AllowParallel then
      f ()
    else
      Task.Run<'T>(fun () -> (f ()).AsTask()) |> ofTask

  // .NET only
  let internal catch (f: exn -> unit) (future: Future<'T>) : Future<unit> =
    if not AllowParallel then
      if future.IsFaulted then
        let ex = future.AsTask().Exception
        f ex

      just ()
    else
      future
        .AsTask()
        .ContinueWith((fun (task: Task<_>) -> f task.Exception), TaskContinuationOptions.OnlyOnFaulted)
      |> ofTask

// #mpscSync
let private mpscSync
  (consumer: 'S -> 'A -> 'S * 'T list)
  (producer: 'S -> 'T -> Future<'A>)
  (initialState: 'S)
  (initialCommands: 'T list)
  : 'S =
  let rec folder state commands =
    let state, commandListList =
      commands
      |> List.fold
           (fun (state, acc) command ->
             let action = producer state command |> Future.unwrap
             let state, newCommands = consumer state action
             state, newCommands :: acc)
           (state, [])

    List.fold folder state (List.rev commandListList)

  folder initialState initialCommands

let private mpscParallel
  (consumer: 'S -> 'A -> 'S * 'T list)
  (producer: 'S -> 'T -> Future<'A>)
  (initialState: 'S)
  (initialCommands: 'T list)
  : 'S =
  assert AllowParallel

  let chan = System.Threading.Channels.Channel.CreateBounded<'A>(256)

  let producerWork (state: 'S) (command: 'T) =
    Future.spawn (fun () ->
      producer state command
      |> Future.andThen (fun action -> chan.Writer.WriteAsync(action) |> Future.ofUnitValueTask))
    |> Future.catch (fun ex -> chan.Writer.Complete(ex))
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
          // Block.
          task.AsTask().Result

      update action

    state

  consumerWork ()

/// Performs a concurrent work.
/// (mpsc: multiple producers single consumer)
///
/// What happens:
///
/// - For each `command`, a worker is spawned to compute `producer` function.
/// - Once a worker end, state is updated by `consumer` function.
/// - Final state is returned. (Function continues while any worker is running.)
let mpscConcurrent
  (consumer: 'S -> 'A -> 'S * 'T list)
  (producer: 'S -> 'T -> Future<'A>)
  (initialState: 'S)
  (initialCommands: 'T list)
  : 'S =
  if AllowParallel then
    mpscParallel consumer producer initialState initialCommands
  else
    mpscSync consumer producer initialState initialCommands

/// `List.map` in parallel.
let __parallelMap (f: 'T -> 'U) (xs: 'T list) : 'U list =
  if AllowParallel then
    xs |> List.toArray |> Array.Parallel.map f |> Array.toList
  else
    List.map f xs

let __allowParallel () =
  AllowParallel <- true
  eprintf "info: Parallel compilation enabled. "
