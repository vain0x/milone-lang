module rec pat_or_bindings.Program

// OR patterns including some bindings is not implemented correctly yet.

let main _ =
  match [ 2; 3 ] with
  | x :: _
  | _ :: x :: _ -> assert (x = 2 || x = 3)
  | _ -> ()

  assert false
  0
