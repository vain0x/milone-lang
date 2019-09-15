let main _ =
  let str = "Hello, John!"
  if str.[0..5] <> "Hello" then exit 1
  if str.[7..4] <> "John" then exit 2
  if str.[11..1] <> "!" then exit 3
  0
