module rec union_newtype.Program

/// New-type union.
type NewTypeInt = NewTypeInt of int

let main _ =
  // New-type union can be unwrap with `let`.
  let (NewTypeInt inner) = NewTypeInt 1
  assert (inner = 1)

  0
