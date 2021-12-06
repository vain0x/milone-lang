module rec union_runtime.Program

type private Color =
  | R
  | G
  | B

let main _ =
  assert (__discriminant R = 0)
  assert (__discriminant G = 1)
  assert (__discriminant B = 2)
  0
