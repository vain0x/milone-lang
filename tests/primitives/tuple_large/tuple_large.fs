module rec tuple_many.Program

// Tuple with large number of items.

let main _ =
  let x, y, (z, w) = 1, 2, (3, 4)
  assert (x = 1 && y = 2 && z = 3 && w = 4)

  let _t11 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
  0
