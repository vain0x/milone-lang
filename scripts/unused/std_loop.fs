module rec std_loop.Program

// Tests MiloneStd/StdLoop.fs

module Loop = MiloneStd.StdLoop
module S = MiloneStd.StdString

/// `0..n-1`
let private gen (n: int) = Loop.range 0 n

let private eq (expected: int list) (actual: _ -> bool * 'S) : bool =
  (fun actual ->
    let debug (xs: int list) = xs |> List.map string |> S.concat ", "

    let expected = debug expected
    let actual = debug actual

    if expected = actual then
      true
    else
      printfn "expected: %s\nactual: %s\n" expected actual
      false) (actual |> Loop.toList)

// ===============================================

let testEmpty () =
  let xs = Loop.empty ()

  assert (xs |> eq [])
  assert (xs |> Loop.isEmpty)

  let n: int = Loop.length xs = eq
  assert (n = 0)

let testRange (len: int) =
  assert (Loop.range 0 0 |> eq [])
  assert (Loop.range 0 1 |> eq [ 0 ])
  assert (Loop.range 1 3 |> eq [ 1; 2 ])
  assert (Loop.range 0 len |> eq [ 0; 1; 2; 3; 4 ])

let testReplicate (len: int) =
  assert (Loop.replicate len 1 |> eq [ 1; 1; 1 ])
  assert (Loop.replicate len 2 |> eq [ 2; 2; 2 ])

let testMap (len: int) =
  assert (gen len
          |> Loop.map (fun i -> i * i)
          |> eq [ 0; 1; 4; 9 ])

  assert (gen len
          |> Loop.map (fun i -> i + 1) // 1; 2; 3; 4
          |> Loop.map (fun i -> i * 2)
          |> eq [ 2; 4; 6; 8 ])

let testForall (len: int) =
  assert (gen len |> Loop.forall (fun i -> i >= 0))

  assert (gen len
          |> Loop.forall
               (fun i ->
                 assert (i <= 2) // It breaks at i = 2.
                 i < 2)
          |> not)

// ===============================================

let main _ =
  testRange 5
  testReplicate 3
  testMap 4
  testForall 4
  0
