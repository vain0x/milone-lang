let main _ =
  match [1; 2] with
  | [] ->
    exit 1
  | [x; y] ->
    assert (x = 1 && y = 2)
  | _ ->
    exit 1

  0
