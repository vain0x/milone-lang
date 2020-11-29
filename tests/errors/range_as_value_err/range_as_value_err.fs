module rec range_as_value_err.Program

// Range operators can't include step part for now.
// Range operators can't be used inside of lists for now.

let main _ =
  assert ("hello".[0 .. 2 .. 4] = "")

  let ok =
    match [0 .. 1] with
    | _ -> false
  assert ok
  0
