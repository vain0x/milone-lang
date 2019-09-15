let main _ =
  let str = "Hello, John!"
  if str |> String.substring 0 4 <> "Hello" then exit 1
  if str |> String.substring 7 10 <> "John" then exit 2
  if str |> String.substring 11 11 <> "!" then exit 3
  0
