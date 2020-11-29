module rec module_used_as_ty_err.Program

// Module name cannot be used as type.

open module_used_as_ty_err.sub

let main _ =
  let x: sub = failwith "error"
  0
