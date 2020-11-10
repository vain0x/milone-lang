let main _ =
  if false then
    f () // ERROR! Use of undefined variable.

  let deepUnificationError =
    match ((1, 2), 3) with
    | (1, "type error"), 3 -> ()

  // ERROR! Index to int.
  // (0).[0]

  // ERROR! Recursive type.
  let rec f x = x f

  () // ERROR! This should be an int.
