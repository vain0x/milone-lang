let eq (t: int * int) =
  match t with
  | x, y when x = y ->
    true
  | _ ->
    false

let main _ =
  if eq (1, 1) |> not then exit 1
  if eq (1, 2) then exit 1
  0
