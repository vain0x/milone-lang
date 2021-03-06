module rec bool_operators.Program

// Bool support some operators.
// Note: bool to int is not supported.

let test (t: bool) (f: bool) =
  assert t

  // Not.
  assert (not f)
  assert (not (not t))

  // And.
  assert (t && t)
  assert (not (t && f))
  assert (not (f && t))
  assert (not (f && f))

  // Or.
  assert (t || t)
  assert (t || f)
  assert (f || t)
  assert (not (f || f))

  // Comparison.
  assert (true = true)
  assert (true <> false)

  assert (false < true)
  assert (false <= true)
  assert (true <= true)

  assert (true > false)

  // Conversion.
  // bool to int is type error in F#.
  // assert (int t = 1)

  // FIXME: implement bool to string conversion
  // assert (string t = "True")
  // assert (string f = "False")
  ()

let testShortCircuit (t: bool) (f: bool) =
  assert (not (
    f
    && (exit 1
        f)
  ))

  assert (t
          || (exit 1
              f))

let main _ =
  test true false
  testShortCircuit true false
  0
