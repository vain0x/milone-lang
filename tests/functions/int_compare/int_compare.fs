module rec int_compare.Program

// Comparison of int.

let basicTest () =
  assert (2 < 3)
  assert ((2 < 2) |> not)

  assert (2 = 2)
  assert ((2 = 3) |> not)

  assert (3 > 2)
  assert ((2 > 3) |> not)

let compareFunTest () =
  assert (compare 2 2 = 0)
  assert (compare 2 3 < 0)
  assert (compare 3 2 > 0)

let main _ =
  basicTest ()
  compareFunTest ()
  0
