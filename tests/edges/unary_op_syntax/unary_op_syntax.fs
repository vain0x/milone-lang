module rec unary_op_syntax.Program

let f (n: int) (m: int) = n = m + 1

let main _ =
  assert (f -1 -2)
  0
