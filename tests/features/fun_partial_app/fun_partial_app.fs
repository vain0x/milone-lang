module rec fun_partial_app.Program

// Partial application is allowed.

let twice f (x: int): int = f (f x)

let dec (y: int) x = x - y

let add4 (x1: int) x2 x3 x4 = x1 + x2 + x3 + x4

let main _ =
  let dec3 = dec 3
  assert (twice dec3 8 = 2)

  let add2 = add4 2 3
  assert (add2 5 7 = 2 + 3 + 5 + 7)

  let f = add4
  assert (f 1 2 3 4 = 1 + 2 + 3 + 4)

  0
