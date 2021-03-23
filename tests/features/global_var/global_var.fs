module rec global_var.Program

// Let expression can define global variables.

let success = 0

let private failure = 1

let f () = success

let g () = f ()

let main _ =
  assert (g () = 0)
  assert (failure = 1)
  0
