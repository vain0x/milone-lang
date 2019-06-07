let main _ =
  match 1 :: 2 :: [] with
  | x1 :: x2 :: [] ->
    assert (x1 = 1 && x2 = 2)
  | _ ->
    exit 1

  match [] *- 2 *- 1 with
  | 1 :: 2 :: _ ->
    ()
  | _ ->
    exit 1

  0
