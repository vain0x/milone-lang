module rec pat_when.Program

// Match arm can have guard expressions.

let equal (t: int * int) =
  match t with
  | x, y when x = y -> true
  | _ -> false

let main _ =
  assert (equal (1, 1))
  assert (equal (1, 2) |> not)
  0
