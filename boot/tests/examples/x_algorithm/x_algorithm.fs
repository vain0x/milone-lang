let neg (x : int) =
  0 - x

let abs (x : int) =
  if x >= 0 then x else neg x

let gcd (x : int) (y : int) =
  if y = 0 then
    abs x
  else
    gcd y (x % y)

let isPrime (x : int) =
  let rec go k = k * k > x || x % k <> 0 && go (k + 1)
  x >= 2 && go 2

let main _ =
  assert (abs 0 = 0)
  assert (abs 1 = 1)
  assert (abs (neg 1) = 1)

  assert (gcd 1 1 = 1)
  assert (gcd 12 18 = 6)
  assert (gcd 4 (neg 6) = 2)

  assert (isPrime 2)
  assert (isPrime 3)
  assert (not (isPrime 4))
  assert (isPrime 1000000007)
  0
