module rec Lib.Gcd

let gcd (x: int) (y: int) =
  assert (x >= 0)
  assert (y >= 0)

  let rec go (x: int) (y: int) = if y = 0 then x else go y (x % y)

  go x y
