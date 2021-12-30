module rec ty_var_unified_unexpectedly.Program

// Explicitly named type variables such as `'T` can't unify to another type.
// In F# it's allowed with warning.

let f () : 'T =
  // this unify 'T = int but shouldn't.
  1

let main _ =
  assert (f () = 1)
  0
