module rec int_bit_operators.Program

// Integer types support bit operators.

let main _ =
  assert ((1 + 2 + 4) &&& (2 + 4 + 8) = 2 + 4)
  assert ((1 + 2 + 4) ||| (2 + 4 + 8) = 1 + 2 + 4 + 8)
  assert ((1 + 2 + 4) ^^^ (2 + 4 + 8) = 1 + 8)

  assert ((1 <<< 0) = 1)
  assert ((1 <<< 1) = 2)
  assert (((1 + 2 + 8) <<< 1) = 2 + 4 + 16)

  assert ((4 >>> 0) = 4)
  assert ((4 >>> 1) = 2)
  assert ((4 >>> 2) = 1)
  assert ((4 >>> 3) = 0)
  assert (((1 + 2 + 8) >>> 1) = 0 + 1 + 4)
  0
