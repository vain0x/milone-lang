module rec pat_resolved_as_fun_err.Program

// Function name can't be used as pattern.

open pat_resolved_as_fun_err.sub

let main _ =
  match fun () -> () with
  | sub.f -> assert true
  0
