let main _ =
  let hello = "hello"
  let world = "world"

  assert (hello.Length = 5)

  let message = hello + world
  assert (message.Length = 10)

  assert (hello.Length = 5)

  assert ("\x00\x01\x02\x03\x04".Length = 5)
  0
