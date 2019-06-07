let main _ =
  let hello = "hello"
  let world = "world"

  if hello.Length <> 5 then exit 1

  let message = hello + world
  if message.Length <> 10 then exit 1

  if String.length hello <> 5 then exit 1
  0
