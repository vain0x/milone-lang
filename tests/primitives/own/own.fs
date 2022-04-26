module rec own.Program

open Std.Own

type private Counter = Counter of Own<int>

let private create (init: int) : Counter = Counter(Own.acquire init)

let private increment (counter: Counter) : int * Counter =
  let (Counter n) = counter
  let n = Own.release n + 1
  n, Counter(Own.acquire n)

let private drop (counter: Counter) : unit =
  let (Counter n) = counter
  let _ = Own.release n
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

/// Generic union with type variable bound to an owned type.
type private Wrapper<'T> = Wrapper of 'T

let private genericWrapperCase () =
  let w = Wrapper(Own.acquire "contents")
  let (Wrapper value) = w
  assert (Own.release value = "contents")

/// Generic union that is always owned.
type private OwnWrapper<'T> = OwnWrapper of Own<'T>

let private genericOwnCase () =
  let Own = OwnWrapper(Own.acquire (2, 3))
  let (OwnWrapper l) = Own
  let x, y = Own.release l
  assert (x = 2 && y = 3)

let private ownMap (mapping: 'T -> 'U) (l: OwnWrapper<'T>) : OwnWrapper<'U> =
  let (OwnWrapper l) = l
  OwnWrapper(Own.acquire (mapping (Own.release l)))

let private genericOwnFunCase () =
  let l =
    OwnWrapper(Own.acquire 2)
    |> ownMap (fun (x: int) -> x + 1)

  let (OwnWrapper l) = l
  let n = Own.release l
  assert (n = 3)

let private optionOfOwnCase () =
  let ownOpt = OwnWrapper(Own.acquire (5, 7)) |> Some

  match ownOpt with
  | Some (OwnWrapper l) ->
    let x, y = Own.release l
    assert (x = 5 && y = 3)

  | None -> ()

let private nestedOwnCase () =
  let nested = Own.acquire (Own.acquire 2)
  let unwrapped = Own.release nested
  let _ = Own.release unwrapped
  ()

/// Union can be an owned type with subtle restriction.
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
  genericOwnCase ()
  genericOwnFunCase ()
  nestedOwnCase ()
  counterWrapperCase ()
  0
