module rec pat_nav_unresolved_err.Program

// Unresolved nav pattern is error.

let main _ =
  match () with
  | A.x -> assert false
  0
