module rec ty_var_unified_unexpectedly.Program

// Explicitly named type variables such as `'T` shouldn't unify.
// In F# it's allowed with warning. I hope milone-lang to reject this as error.

let f () : 'T =
  // this unify 'T = int but shouldn't.
  1

let main _ =
  assert (f () = 1)
  0
