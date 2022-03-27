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

let main _ =
  acquireAndThenDispose ()
  acquireAndUse ()
  transfer ()
  branchCase ()
  multipleMatches ()
  nestedMatches ()
  0
