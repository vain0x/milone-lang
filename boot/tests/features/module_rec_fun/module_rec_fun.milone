let rec even n =
  n = 0 || odd (n - 1)

let rec odd n =
  n <> 0 && even (n - 1)

let main _ =
  if odd 1 |> not then exit 1
  if even 2 |> not then exit 1
  if even 3 then exit 1

  0
