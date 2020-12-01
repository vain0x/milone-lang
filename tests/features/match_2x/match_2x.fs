let main _ =
  let f (x : int) = x * x
  match f 3 with
  | 1 ->
    1
  | y ->
    y - 9
