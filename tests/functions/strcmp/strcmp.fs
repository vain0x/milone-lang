let testBasicCase () =
  assert("a" < "b")
  assert("alpha" < "beta")

  assert ("" = "")
  assert ("o" = "o")

  assert ("z" > "a")

let testBinarySafe () =
  assert ("\x00x" < "\x00y")

let testCompareFun () =
  assert (compare "a" "b" < 0)
  assert (compare "a" "a" = 0)
  assert (compare "b" "a" > 0)

let main _ =
  testBasicCase ()
  testBinarySafe ()
  testCompareFun ()
  0
