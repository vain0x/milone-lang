module rec ty_errors.Program

let main _ =
  let deepUnificationError =
    match ((1, 2), 3) with
    | (1, "type error"), 3 -> ()

  // ERROR! Index to int.
  // (0).[0]

  // ERROR! Recursive type.
  let rec f x = x f

  () // ERROR! This should be an int.
