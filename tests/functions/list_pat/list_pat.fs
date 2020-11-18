let basicCase xs =
  match xs with
  | [] -> assert false
  | _ -> ()

let complicatedCase xs =
  match xs with
  | [] -> assert false
  | [x; y] -> assert (x = 1 && y = 2)
  | _ -> assert false

let main _ =
  basicCase [ 1 ]
  complicatedCase [ 1; 2 ]
  0
