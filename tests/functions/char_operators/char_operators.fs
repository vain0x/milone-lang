module rec char_operators.Program

// char type supports some of operators.

let arithmeticOperatorsTest () =
  // (+) works (why?)
  assert ('\r' + '\n' = char (13 + 10))

  // (-), (*), (&&&) etc. are type error.
  // assert ('8' - '0' = char 8)
  ()

let comparisonOperatorsTest () =
  assert ('A' = 'A')
  assert ('A' <> 'B')

  assert ('A' < 'B')
  assert ('A' <= 'A')
  assert ('A' <= 'B')

  assert ('B' > 'A')
  assert ('A' >= 'A')
  assert ('B' >= 'A')

  assert (compare 'A' 'A' = 0)
  assert (compare 'A' 'B' < 0)
  assert (compare 'B' 'A' > 0)

let main _ =
  arithmeticOperatorsTest ()
  comparisonOperatorsTest ()
  0
