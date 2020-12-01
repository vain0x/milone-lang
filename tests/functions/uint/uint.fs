module rec uint.Program

// uint type support. (32-bit unsigned integer.)

let main _ =
  // Conversion from/to other scalars.
  assert (int (uint 42) = 42)
  assert (int (uint 'A') = int 'A')

  // Conversion from/to strings.
  assert (int (uint "42") = 42)
  assert (string (uint 42) = "42")

  // Arithmetic operations.
  assert (int (uint 40 + uint 2) = 42)
  assert (int (uint 49 - uint 7) = 42)
  assert (int (uint 6 * uint 7) = 42)
  assert (int (uint 294 / uint 7) = 42)
  assert (int (uint 2063 % uint 43) = 42)

  // Wrapping.
  assert (int ((uint (-1) - uint 1) / uint 2) = 2147483647)

  // Comparison.
  assert (uint 2 < uint 3)
  assert (uint 2 <= uint 3)
  assert (uint 2 <= uint 3)
  assert (uint 2 = uint 2)
  assert (uint 2 <> uint 3)

  0
