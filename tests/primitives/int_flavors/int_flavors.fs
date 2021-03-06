module rec int_types.Program

// Integer types other than int.
// See also: <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/basic-types>

// FIXME: Support integer literal with suffix.
// Integer literal without suffix is of int.

let signedCases () =
  // int32 is same as int.
  assert (int32 1 = 1)

  // sbyte is same as int8.
  assert (sbyte 1 = int8 1)

  // Binary operations require both side of operands are exactly same type
  // except for shift operators. Right-hand side of shift operator is of int.

  // Arithmetic operations.
  assert (int8 2 + int8 3 = int8 5)
  assert (int16 7 - int16 11 = int16 (-4))
  assert (int (int16 (-4)) = -4)

  // Bit operations.
  assert (int8 (1 + 2 + 4) &&& int8 (2 + 4 + 8) = int8 (2 + 4))

  assert (int16 (1 + 2 + 4) ||| int16 (2 + 4 + 8) = int16 (1 + 2 + 4 + 8))

  assert (int64 (1 + 2 + 4) ^^^ int64 (2 + 4 + 8) = int64 (1 + 8))

  assert ((int8 (1 + 4 + 16) <<< 1) = int8 (2 + 8 + 32))
  assert ((int16 (1 + 4 + 16) >>> 1) = int16 (0 + 2 + 8))

  assert ((int8 (-1) >>> 1) = int8 (-1))

  // Comparison.
  assert (int32 13 = 13)
  assert (int64 17 = int64 17)
  assert (nativeint (-23) < nativeint 19)

  assert (compare (int8 2) (int8 2) = 0)
  assert (compare (int8 2) (int8 3) < 0)
  assert (compare (int8 2) (int8 (-1)) > 0)

  assert (compare (int64 1231231231 * int64 2) (int64 1231231231 * int64 3) < 0)
  assert (compare (int64 1231231231 * int64 3) (int64 1231231231 * int64 2) > 0)

  // Conversion to string.
  assert (string (int8 (-1)) = "-1")
  assert (string (int64 1231231231 * int64 3) = "3693693693")

  // Conversion from string.
  assert (int (int64 "-3693693693" / int64 3) = -1231231231)

let unsignedCases () =
  // byte is same as uint8.
  assert (byte 1 = uint8 1)

  // uint is same as uint32.
  assert (uint 1 = uint32 1)

  // Arithmetic operations.
  assert (uint8 2 + uint8 3 = uint8 5)
  assert (uint16 11 - uint16 7 = uint16 4)

  // Bit operations.
  assert (uint8 (1 + 2 + 4) &&& uint8 (2 + 4 + 8) = uint8 (2 + 4))

  assert (uint16 (1 + 2 + 4) ||| uint16 (2 + 4 + 8) = uint16 (1 + 2 + 4 + 8))

  assert (uint64 (1 + 2 + 4) ^^^ uint64 (2 + 4 + 8) = uint64 (1 + 8))

  assert ((uint8 (1 + 4 + 16) <<< 1) = uint8 (2 + 8 + 32))
  assert ((uint16 (1 + 4 + 16) >>> 1) = uint16 (0 + 2 + 8))

  // Comparison.
  assert (uint 13 = uint32 13)
  assert (uint64 17 = uint64 17)
  assert (unativeint 19 < unativeint 23)

  assert (compare (uint64 2) (uint64 2) = 0)
  assert (compare (uint64 1231231231 * uint64 2) (uint64 1231231231 * uint64 3) < 0)
  assert (compare (uint64 1231231231 * uint64 3) (uint64 1231231231 * uint64 2) > 0)

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
