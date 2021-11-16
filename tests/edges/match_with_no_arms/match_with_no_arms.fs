module rec match_with_no_arms.Program

// Parser should report an error if match-with has no arms.
// It should also recover from that error to parse following code correctly,
// which improves the experiment of intellisense.

let main _ =
  match exit 0 with

let other () = ()
