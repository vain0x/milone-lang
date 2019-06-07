let main _ =
  match 1 :: [] with
  | x1 :: [] ->
    x1 - 1
  | _ ->
    exit 1
