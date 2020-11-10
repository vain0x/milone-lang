let main _ =
  match 1 :: [] with
  | x1 :: [] ->
    assert (x1 = 1)
  | _ ->
    assert false
  0
