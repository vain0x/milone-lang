module rec linear.Program

type private Counter = Counter of __linear<int>

let private create (init: int) : Counter = Counter(__acquire init)

let private increment (counter: Counter) : int * Counter =
  let (Counter n) = counter
  let n = __dispose n + 1
  n, Counter(__acquire n)

let private drop (counter: Counter) : unit =
  let (Counter n) = counter
  let _ = __dispose n
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
  let w = Wrapper(__acquire "contents")
  let (Wrapper value) = w
  assert (__dispose value = "contents")

/// Generic union that is always linear.
type private Linear<'T> = Linear of __linear<'T>

let private genericLinearCase () =
  let linear = Linear(__acquire (2, 3))
  let (Linear l) = linear
  let x, y = __dispose l
  assert (x = 2 && y = 3)

let private optionOfLinearCase () =
  let linearOpt = Linear(__acquire (5, 7)) |> Some

  match linearOpt with
  | Some (Linear l) ->
    let x, y = __dispose l
    assert (x = 5 && y = 3)

  | None -> ()

let main _ =
  acquireAndThenDispose ()
  acquireAndUse ()
  transfer ()
  branchCase ()
  multipleMatches ()
  nestedMatches ()
  genericWrapperCase ()
  genericLinearCase ()
  0
