module rec int_lit_range_err.Program

// Too large or too small int literal is error.

let invalidLitInPat (value: int) =
  match value with
  | 2147483648 -> ()
  | -2147483649 -> ()
  | _ -> assert false

let invalidLitInExpr (value: int) =
  assert (2147483648 <> value)
  assert (-2147483649 <> value)

let invalidHexLit (value: int) =
  assert (0x910001000 <> value)

let main _ =
  invalidLitInPat 0
  invalidLitInExpr 0
  invalidHexLit 0
  assert false
  1
