module rec module_no_leak.module_no_leak_f2

open module_no_leak.module_no_leak_f1

let f2 () =
  // f1 is visible thanks to open above.
  f1 ()
