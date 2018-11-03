let test pred =
  if not pred then exit 1

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
  test (abs 0 = 0)
  test (abs 1 = 1)
  test (abs (neg 1) = 1)

  test (gcd 1 1 = 1)
  test (gcd 12 18 = 6)
  test (gcd 4 (neg 6) = 2)

  test (isPrime 2)
  test (isPrime 3)
  test (not (isPrime 4))
  test (isPrime 1000000007)
  0
