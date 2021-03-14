module rec fun_arity_app.Program

// See also fun_arity_over.

let add (x: int) (y: int) : int = x + y

let app f x = f x

let main _ =
  // app expects 1-arity function, but add is 2-arity.
  let increment = app add 1

  assert (increment 2 = 1 + 2)
  0
