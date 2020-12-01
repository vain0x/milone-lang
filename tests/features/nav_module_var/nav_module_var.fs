module rec nav_module_var.Program

// Nav expressions to access variables defined in modules.

open nav_module_var.constants

let main _ =
  // static variable
  assert (constants.answer = 42)

  // function
  assert (constants.getAnswer () = 42)

  // variant
  let myAnswer = constants.Answer 42

  0
