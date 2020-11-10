let testBinarySafe () =
  assert (("a" + "\x00b").[2] = 'b')

let main _ =
  let hello = "Hello"
  let world = ", world!"
  printfn "%s" (hello + world)

  testBinarySafe ()
  0
