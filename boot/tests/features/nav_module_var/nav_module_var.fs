module rec nav_module_var.Program

// Nav expressions to access variables defined in modules.

open nav_module_var.constants

let main _ =
  assert (constants.answer = 42)
  assert (constants.getAnswer () = 42)
  0
