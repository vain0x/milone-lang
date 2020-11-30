module rec native_fun_illegal_use_err.Program

// __nativeFun must be used in correct syntax.

let main _ =
  let name = "__someFun"
  __nativeFun name 1 2 3
  assert false
  0
