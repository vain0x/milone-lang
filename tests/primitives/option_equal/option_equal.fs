module rec option_equal.Program

// Option type supports structural equality (=).

let private testIntOption () =
  let some = Some 2
  assert (some = Some 2)
  assert (some <> Some 3)
  assert (some <> None)

  let none: int option = None
  assert (none = None)
  assert (none <> some)

let private testPair () =
  assert (Some(2, "a") = Some(2, "a"))
  assert (Some(2, "a") <> Some(2, "A"))

let main _ =
  testIntOption ()
  testPair ()
  0
