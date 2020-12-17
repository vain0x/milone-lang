module rec tuple_arg.Program

// Tuples work as function argument.

let main _ =
  let sub (x, y) = x - y
  sub (8, 3) - 5
