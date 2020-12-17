module rec global_var_initializer.Program

// Let expression can define global variable with non-static initializer.
// The initializer is executed at the start of main function.

let f () = box 1

let boxedValue = box 1

let main _ =
  assert (f () |> unbox = 1)
  0
