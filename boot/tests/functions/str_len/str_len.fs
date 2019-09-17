let main _ =
  let hello = "hello"
  let world = "world"

  assert (hello.Length = 5)

  let message = hello + world
  assert (message.Length = 10)

  assert (String.length hello = 5)
  0
