module rec native_fun_call.Program

// Call statically linked native function.
// See also x_native_code.md in docs.

let intCompare (l: int) (r: int) : int = __nativeFun ("int_compare", l, r)

let main _ =
  assert (intCompare 5 3 = 1)
  0
