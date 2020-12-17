module rec str_operators.Program

let addTest () =
  let hello = "Hello"
  let world = ", world!"
  assert (hello + world = "Hello, world!")

  // Binary safe.
  assert (("a" + "\x00b").[2] = 'b')

let compareTest () =
  assert ("" = "")
  assert ("o" = "o")
  assert ("alpha" = "alpha")

  assert ("a" < "b")
  assert ("alpha" < "beta")

  assert ("z" > "a")

  assert (compare "alpha" "beta" < 0)
  assert (compare "alpha" "alpha" = 0)
  assert (compare "beta" "alpha" > 0)

  // Binary safe.
  assert ("\x00x" < "\x00y")

  // String comparison should stop at null byte? (currently non-stop on .NET, stop on native)
  // assert ("" <> "\x00")
  ()

let indexOperatorTest () =
  let hello = "hello"
  assert (hello.[0] = 'h' && hello.[4] = 'o')

  // Index type should be inferred as int.
  let at i (s: string) = s.[i]

  assert (at 0 hello = 'h')

let subscriptOperatorTest () =
  let str = "Hello, John!"
  assert (str.[0..4] = "Hello")
  assert (str.[7..10] = "John")
  assert (str.[11..11] = "!")

let main _ =
  addTest ()
  compareTest ()
  indexOperatorTest ()
  subscriptOperatorTest ()
  0
