module rec int_types.Program

// Integer types other than int.

// FIXME: Support integer literal with suffix.

let signedCases () =
  // int32 is the same type as int.
  // Integer literal without suffix is of int.
  // Binary operations require both side of operands are exactly same type.

  // Arithmetic operations.
  assert (int8 2 + int8 3 = int8 5)
  assert (int16 7 - int16 11 = int16 (-4))
  assert (int (int16 (-4)) = -4)

  // Comparison.
  assert (int32 13 = 13)
  assert (int64 17 = int64 17)
  assert (nativeint (-23) < nativeint 19)

  // Conversion to string.
  assert (string (int8 (-1)) = "-1")
  assert (string (int64 1231231231 * int64 3) = "3693693693")

  // Conversion from string.
  assert (int (int64 "-3693693693" / int64 3) = -1231231231)

let unsignedCases () =
  // uint and uint32 are same.

  // Arithmetic operations.
  assert (uint8 2 + uint8 3 = uint8 5)
  assert (uint16 11 - uint16 7 = uint16 4)

  // Comparison.
  assert (uint 13 = uint32 13)
  assert (uint64 17 = uint64 17)
  assert (unativeint 19 < unativeint 23)

  // Conversion to string.
  assert (string (uint8 0) = "0")
  assert (string (uint64 1231231231 * uint64 3) = "3693693693")

  // Conversion from string.
  assert (uint8 "255" = uint8 255)
  assert (int (uint64 "3693693693" / uint64 3) = 1231231231)

let main _ =
  signedCases ()
  unsignedCases ()
  0
