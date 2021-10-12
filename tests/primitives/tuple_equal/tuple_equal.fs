module rec tuple_equal.Program

// Tuple provides structural equality (=).

let private testPair () =
  assert ((0, "zero") = (0, "zero"))

  assert ((0, "zero") <> (1, "zero"))
  assert ((0, "zero") <> (0, "one"))

let private testUnit () = assert (() = ())

let private testNested () =
  assert ((1, (2, 3)) = (1, (2, 3)))

  assert ((1, (2, 3)) <> (0, (2, 3)))
  assert ((1, (2, 3)) <> (1, (2, 0)))

let private testUnitCompare () =
  // When tuple comparison is implemented, move this there.
  assert (() <= ())
  assert (not (() < ()))
  assert (() >= ())
  assert (not (() > ()))

let main _ =
  testUnit ()
  testPair ()
  testNested ()
  testUnitCompare ()
  0
