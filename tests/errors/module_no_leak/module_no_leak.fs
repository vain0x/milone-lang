module rec module_no_leak.Program

// Depends on f2 and transitively depends on f1, but module f1 is not open here.
open module_no_leak.module_no_leak_f2

let main _ =
  // This should be error!
  f1 ()
  0
