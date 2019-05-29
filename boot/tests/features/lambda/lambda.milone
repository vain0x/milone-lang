let main _ =
  let twice f x = x |> f |> f
  let x =
    40 |> twice (fun x ->
      let y = x + 1
      y
    )
  if x <> 42 then
    exit 1

  if (fun x y -> x / y) 84 2 <> 42 then
    exit 1

  0
