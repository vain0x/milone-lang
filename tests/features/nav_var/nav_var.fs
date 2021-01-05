module rec nav_var.Program

// Nav expressions to access variables defined in modules.

open nav_var.sub

let main _ =
  // static variable
  assert (sub.answer = 42)

  // function
  assert (sub.getAnswer () = 42)

  // variant
  let myAnswer = sub.Answer 42

  0
