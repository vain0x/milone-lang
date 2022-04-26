module rec linear.Program

open Std.Linear

type private Counter = Counter of Linear<int>

let private create (init: int) : Counter = Counter(Linear.acquire init)

let private increment (counter: Counter) : int * Counter =
  let (Counter n) = counter
  let n = Linear.dispose n + 1
  n, Counter(Linear.acquire n)

let private drop (counter: Counter) : unit =
  let (Counter n) = counter
  let _ = Linear.dispose n
  ()

let private acquireAndThenDispose () =
  let counter = create 0
  let _ = drop counter
  ()

let private acquireAndUse () =
  let counter = create 0
  let n, counter = increment counter
  assert (n = 1)
  let n, counter = increment counter
  drop counter

let private transfer () =
  let counter = create 0
  let other = counter
  drop other

let private branchCase () =
  let counter = create 0
  let n, counter = increment counter

  let counter =
    match n with
    | 0 -> counter

    | _ ->
      let _, counter = increment counter
      counter

  drop counter

let private multipleMatches () =
  let first = create 1
  let second = create 2

  match 1 with
  | _ -> drop first

  match 2 with
  | _ -> drop second

let private nestedMatches () =
  let root = create 1

  match 1 with
  | _ ->
    let inner = create 2

    match 2 with
    | _ ->
      drop inner
      drop root

let private loopCase () =
  let rec acquireMany (n: int) =
    let rec go acc i = if i < n then create i :: acc else acc
    go [] 0

  let rec disposeMany counters =
    match counters with
    | [] -> []

    | c :: counters ->
      drop c
      disposeMany counters

  let counters: Counter list = acquireMany 0
  disposeMany counters

/// Generic union with type variable bound to linear type.
type private Wrapper<'T> = Wrapper of 'T

let private genericWrapperCase () =
  let w = Wrapper(Linear.acquire "contents")
  let (Wrapper value) = w
  assert (Linear.dispose value = "contents")

/// Generic union that is always linear.
type private LinearWrapper<'T> = LinearWrapper of Linear<'T>

let private genericLinearCase () =
  let linear = LinearWrapper(Linear.acquire (2, 3))
  let (LinearWrapper l) = linear
  let x, y = Linear.dispose l
  assert (x = 2 && y = 3)

let private linearMap (mapping: 'T -> 'U) (l: LinearWrapper<'T>) : LinearWrapper<'U> =
  let (LinearWrapper l) = l
  LinearWrapper(Linear.acquire (mapping (Linear.dispose l)))

let private genericLinearFunCase () =
  let l =
    LinearWrapper(Linear.acquire 2)
    |> linearMap (fun (x: int) -> x + 1)

  let (LinearWrapper l) = l
  let n = Linear.dispose l
  assert (n = 3)

let private optionOfLinearCase () =
  let linearOpt =
    LinearWrapper(Linear.acquire (5, 7)) |> Some

  match linearOpt with
  | Some (LinearWrapper l) ->
    let x, y = Linear.dispose l
    assert (x = 5 && y = 3)

  | None -> ()

let private nestedLinearCase () =
  let nested = Linear.acquire (Linear.acquire 2)
  let unwrapped = Linear.dispose nested
  let _ = Linear.dispose unwrapped
  ()

/// Union can be linear with subtle restriction.
/// (Basically a union cannot forwardly reference to own another unions.)
type private CounterWrapper = CounterWrapper of Counter

let private counterWrapperCase () =
  let w = CounterWrapper(create 0)
  let (CounterWrapper c) = w
  drop c

let main _ =
  acquireAndThenDispose ()
  acquireAndUse ()
  transfer ()
  branchCase ()
  multipleMatches ()
  nestedMatches ()
  genericWrapperCase ()
  genericLinearCase ()
  genericLinearFunCase ()
  nestedLinearCase ()
  counterWrapperCase ()
  0
