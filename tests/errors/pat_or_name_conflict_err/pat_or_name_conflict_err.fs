module rec pat_or_name_conflict_err.Program

let main _ =
  match [ 2; 2 ] with
  | [ x; x ] -> assert (x = x)
  | _ -> ()

  let y, y = 2, 3

  let (z as z) = 2, 3

  assert false
  0
