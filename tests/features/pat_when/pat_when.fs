let eq (t: int * int) =
  match t with
  | x, y when x = y ->
    true
  | _ ->
    false

let main _ =
  assert (eq (1, 1))
  assert (eq (1, 2) |> not)
  0
