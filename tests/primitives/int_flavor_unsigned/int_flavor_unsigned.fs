module rec int_flavor_unsigned.Program

// Unsigned integer types.

let main _ =
  // Conversion from/to int.
  assert (int 42u = 42)
  assert (uint 42 = 42u)

  // Conversion from/to char.
  assert (uint 'A' = 65u)
  assert (char 65u = 'A')

  // Conversion from/to string.
  assert (int (uint "42") = 42)
  assert (string 42u = "42")

  // Arithmetic operations.
  assert (int (40u + 2u) = 42)
  assert (int (49u - 7u) = 42)
  assert (int (6u * 7u) = 42)
  assert (int (294u / 7u) = 42)
  assert (int (2063u % 43u) = 42)

  // Wrapping.
  assert (int ((uint (-1) - 1u) / 2u) = 2147483647)

  // Comparison.
  assert (2u < 3u)
  assert (2u <= 3u)
  assert (2u <= 3u)
  assert (2u = 2u)
  assert (2u <> 3u)

  0
