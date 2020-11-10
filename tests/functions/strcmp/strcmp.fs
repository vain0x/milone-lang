let testBinarySafe () =
  assert ("\x00x" < "\x00y")

let main _ =
  let le = "a" < "b"
  let eq = "o" = "o"
  assert (le && eq)

  testBinarySafe ()
  0
