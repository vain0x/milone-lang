let rec even n =
  n = 0 || odd (n - 1)

let rec odd n =
  n <> 0 && even (n - 1)

let main _ =
  assert (odd 1)
  assert (even 2)
  assert (even 3 |> not)
  0
