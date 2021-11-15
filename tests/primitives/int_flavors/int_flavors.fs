module rec int_types.Program

// Integer types other than int.
// See also: <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/basic-types>

// Integer literal without suffix is of int.

let signedCases () =
  // int32 is same as int.
  assert (int32 1 = 1)

  // sbyte is same as int8.
  assert (sbyte 1 = int8 1)

  // Binary operations require both side of operands are exactly same type
  // except for shift operators. Right-hand side of shift operator is of int.

  // Arithmetic operations.
  assert (2y + 3y = 5y)
  assert (7s - 11s = -4s)
  assert (int (-4s) = -4)

  // Bit operations.
  assert ((1y + 2y + 4y) &&& (2y + 4y + 8y) = (2y + 4y))

  assert ((1s + 2s + 4s) ||| (2s + 4s + 8s) = (1s + 2s + 4s + 8s))

  assert ((1L + 2L + 4L) ^^^ (2L + 4L + 8L) = (1L + 8L))

  assert (((1y + 4y + 16y) <<< 1) = (2y + 8y + 32y))
  assert (((1s + 4s + 16s) >>> 1) = (0s + 2s + 8s))

  assert ((-1y >>> 1) = (-1y))

  // Comparison.
  assert (int32 13 = 13)
  assert (17L = 17L)
  assert (-23n < 19n)

  assert (compare 2y 2y = 0)
  assert (compare 2y 3y < 0)
  assert (compare 2y (-1y) > 0)

  assert (compare (1231231231L * 2L) (1231231231L * 3L) < 0)
  assert (compare (1231231231L * 3L) (1231231231L * 2L) > 0)

  // Conversion to string.
  assert (string (-1y) = "-1")
  assert (string (1231231231L * 3L) = "3693693693")

  // Conversion from string.
  assert (int (int64 "-3693693693" / 3L) = -1231231231)

let unsignedCases () =
  // byte is same as uint8.
  assert (byte 1 = uint8 1)

  // uint is same as uint32.
  assert (uint 1 = uint32 1)

  // Arithmetic operations.
  assert (2uy + 3uy = 5uy)
  assert (11us - 7us = 4us)

  // Bit operations.
  assert ((1uy + 2uy + 4uy) &&& (2uy + 4uy + 8uy) = (2uy + 4uy))

  assert ((1us + 2us + 4us) ||| (2us + 4us + 8us) = (1us + 2us + 4us + 8us))

  assert ((1UL + 2UL + 4UL) ^^^ (2UL + 4UL + 8UL) = (1UL + 8UL))

  assert (((1uy + 4uy + 16uy) <<< 1) = (2uy + 8uy + 32uy))
  assert (((1us + 4us + 16us) >>> 1) = (0us + 2us + 8us))

  // Comparison.
  assert (uint 13 = 13u)
  assert (17UL = 17UL)
  assert (19un < 23un)

  assert (compare 2UL 2UL = 0)
  assert (compare (1231231231UL * 2UL) (1231231231UL * 3UL) < 0)
  assert (compare (1231231231UL * 3UL) (1231231231UL * 2UL) > 0)

  // Conversion to string.
  assert (string 0uy = "0")
  assert (string (1231231231UL * 3UL) = "3693693693")

  // Conversion from string.
  assert (uint8 "255" = 255uy)
  assert (int (uint64 "3693693693" / 3UL) = 1231231231)

let private suffix () =
  assert (64L = int64 64)

  assert (8uy = uint8 8)
  assert (16us = uint16 16)
  assert (32u = uint32 32)
  assert (32ul = uint32 32)
  assert (64UL = uint64 64)
  assert (99un = unativeint 99)

  assert (string 180150120900600300L = "180150120900600300")

let main _ =
  signedCases ()
  unsignedCases ()
  suffix ()
  0
