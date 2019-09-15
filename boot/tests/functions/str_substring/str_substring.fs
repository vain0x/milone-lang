let main _ =
  let str = "Hello, John!"
  if str |> String.substring 0 5 <> "Hello" then exit 1
  if str |> String.substring 7 4 <> "John" then exit 2
  if str |> String.substring 11 1 <> "!" then exit 3
  0
