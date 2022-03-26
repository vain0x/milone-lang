module rec linear.Program

type private Counter = Counter of __linear<int>

let private create (init: int) : Counter = Counter(__acquire init)

let private increment (counter: Counter) : int * Counter =
  let (Counter n) = counter
  let n = __dispose n + 1
  n, Counter n

let private drop (counter: Counter) : unit =
  let (Counter n) = counter
  let _ = __dispose n
  ()

let private acquireAndThenDispose () =
  let counter = create 0
  let _ = counter
  ()

let private acquireAndUse () =
  let counter = Counter 0
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

let main _ =
  acquireAndThenDispose ()
  acquireAndUse ()
  transfer ()
  branchCase ()
  0
