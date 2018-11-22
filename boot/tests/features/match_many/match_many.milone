let main _ =
  match () with
  | () -> ()

  match 0 :: [] with
  | _ :: _ :: [] -> exit 1
  | _ :: [] -> ()
  | [] -> exit 1

  // Check if match arms make a scope.
  let x = 2
  match x, 1 with
  | 1, x ->
    exit 1
  | 2, _ ->
    if x <> 2 then exit 1
  | _ ->
    exit 1

  0
