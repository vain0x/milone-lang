module rec module_open_not_found_err.Program

// Trying to open non-existing module is an error.

open module_used_as_ty_err.NotExistingModule

let main _ =
  assert false
  0
