module rec fun_underlying_fun_forward_decl_issue.Program

// Repro.
// There was an issue that forward declaration of a function
// which is generated as an underlying function of partial application
// did have incorrect signature.

// In sub.fs, static variable `f2` is defined
// and initializer includes an partial application of function `f`.
// Initialization code is generated in this module.
// Hence forward declaration of `f` is generated.
// The signature was incorrect.
//
// Expected: `struct FunObj f(void const *env, string y);`
// Actual: `struct FunObj f(void const *env, int x, string y);`
//
// Obviously type of underlying function includes
// partially applied parameters unnecessarily.

open fun_underlying_fun_forward_decl_issue.sub

let main _ =
  assert (f2 "hi" = "x = 2, y = hi")
  0
