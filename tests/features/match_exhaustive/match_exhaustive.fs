module rec match_exhaustive.Program

// Match expression, which is exhaustive.

let main _ =
  let f (x: int) = x * x

  match f 3 with
  | 1 ->
    assert false
    1

  | y ->
    assert (y = 9)
    0
