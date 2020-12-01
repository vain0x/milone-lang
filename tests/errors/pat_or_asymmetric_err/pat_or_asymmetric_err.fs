module rec pat_or_asymmetric_err.Program

let main _ =
  match [ 2; 3 ] with
  | x :: _
  | [] -> assert (x = 2)

  match [ 2; 3 ] with
  | []
  | x :: _ -> assert (x = 2)

  match [ 2; 3 ] with
  | [] -> ()
  | x :: _
  | _ :: ((x :: _)
  | (_ :: _ :: _)) -> assert (x = 2)

  assert false
  0
