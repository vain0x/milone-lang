let main _ =
  let str = "Hello, John!"
  assert (str.[0..4] = "Hello")
  assert (str.[7..10] = "John")
  assert (str.[11..11] = "!")
  0
