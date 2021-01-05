module rec ty_var_err.Program

let pair (x: 'x) (y: 'x) = x, y

let main _ =
  // Type error.
  let _ = pair 2 "a"
  0
