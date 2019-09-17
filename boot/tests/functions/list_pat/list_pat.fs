let main _ =
  match [1; 2] with
  | [] ->
    assert false
  | [x; y] ->
    assert (x = 1 && y = 2)
  | _ ->
    assert false

  0
