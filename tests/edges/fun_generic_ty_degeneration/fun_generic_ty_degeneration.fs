module rec fun_generic_ty_degeneration.Program

// NOTE: after some change (introducing compute-ty-args and fixing generalization of nested function), the following comment might be incorrect.

// Function body can contain unbound type variables.
// These types are degenerated (converted) to unit.

// About issue:
// In previous implementation, type inference performed degeneration.
// However, closure conversion and hoisting nested functions
// made some type variables unbound, so instantiation of generic functions
// should have performed degeneration too.

let myFst (x, _) = x

let fstUnbox (boxedPair: obj) (phantom: ('S * 'T) option) : 'S =
  let f () = myFst (unbox boxedPair: 'S * 'T)
  f ()

let testCase (kv: int * string) =
  assert (fstUnbox (box kv) (None: (int * string) option) = 0)

let main _ =
  testCase (0, "right")
  0
