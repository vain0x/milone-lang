module rec char_operators.Program

let private testAddition () =
  assert ('\r' + '\n' = char (13uy + 10uy))

let private testEquality () =
  assert ('A' = 'A')
  assert ('A' <> 'a')

let private testConversion () =
  assert (char 'A' = 'A')
  assert (char "A" = 'A')

  // Char can convert from/to byte-sized integers.
  assert (char 65uy = 'A')
  assert (char 65y = 'A')

  assert (char 0uy = '\x00')
  assert (char 127uy = '\x7f')
  assert (char 255uy = '\xff')

let private testByteLit () =
  assert ('A'B = 65uy)
  assert ('\x7E'B = 0x7Euy)

let main _ =
  testAddition ()
  testEquality ()
  testConversion ()
  testByteLit ()
  0
