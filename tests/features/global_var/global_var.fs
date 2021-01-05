module rec global_var.Program

// Let expression can define global variables.

let success = 0

let f () = success

let g () = f ()

let main _ = g ()
