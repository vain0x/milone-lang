module rec tuple_arg.Program

// Tuples work as function argument.

let main _ =
  // FIXME: Without ascription, the result type is inferred too generic
  //        since trait bounds are processed after generalization
  //        (bounds should be processed *before* generalization ideally).
  let sub (x, y): int = x - y

  sub (8, 3) - 5
