module rec match_nonexhaustive.Program

// Non-exhaustive pattern matching.

let main _ =
  match 2 * 2, 3 * 3 with
  | 4, 9 -> 0

  | 999, y ->
    assert (y <> 9)
    1
