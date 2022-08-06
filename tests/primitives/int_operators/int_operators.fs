module rec int_operators.Program

let literalTest () =
  // Int minimum/maximum values can be written as literal.
  assert (-((-2147483648) + 1) = 2147483647)

let hexLiteralTest () =
  assert (0x00000000 = 0)
  assert (0x10 = 16)
  assert (0x7fffffff = 2147483647)
  assert (0xffffffff = -1)

let arithmeticOperatorsTest (two: int) (three: int) (thirtyNine: int) =
  assert (two + three = 5)
  assert (three - two = 1)
  assert (two * three = 6)
  assert (thirtyNine / two = 19)
  assert (thirtyNine / three = 13)
  assert (thirtyNine % two = 1)
  assert (thirtyNine % three = 0)

  assert (-two = -2)

let bitOperatorsTest (n1: int) =
  let n2 = n1 * 2
  let n4 = n2 * 2
  let n8 = n4 * 2
  let n16 = n8 * 2

  assert (((n1 + n2 + n4) &&& (n2 + n4 + n8)) = n2 + n4)
  assert (((n1 + n2 + n4) ||| (n2 + n4 + n8)) = n1 + n2 + n4 + n8)
  assert (((n1 + n2 + n4) ^^^ (n2 + n4 + n8)) = n1 + n8)

  assert ((n1 <<< 0) = n1)
  assert ((n1 <<< 1) = n2)
  assert (((n1 + n2 + n8) <<< 1) = n2 + n4 + n16)

  assert ((n4 >>> 0) = n4)
  assert ((n4 >>> 1) = n2)
  assert ((n4 >>> 2) = n1)
  assert ((n4 >>> 3) = 0)
  assert (((n1 + n2 + n8) >>> 1) = 0 + n1 + n4)

  assert (~~~0 = 0xffffffff)
  assert (~~~0xffffffff = 0)
  assert (~~~0xca10cafe = 0x35ef3501)

let compareTest (n2: int) (n3: int) =
  assert (n2 = 2)
  assert (n3 <> 2)

  assert (n2 <= 2)
  assert (n2 <= n3)
  assert (n2 < n3)

  assert (n3 > n2)

  assert (compare n2 3 < 0)
  assert (compare n2 2 = 0)
  assert (compare n3 2 > 0)

let toIntTest () =
  assert (int 0 = 0)
  assert (int "42" = 42)
  assert (int "-1" + 1 = 0)

let main _ =
  literalTest ()
  hexLiteralTest ()
  arithmeticOperatorsTest 2 3 39
  bitOperatorsTest 1
  compareTest 2 3
  toIntTest ()
  0
