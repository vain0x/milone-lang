let twice f (x : int) = f (f x) : int

let dec (y : int) x = x - y

let add4 (x1 : int) x2 x3 x4 = x1 + x2 + x3 + x4

let main _ =
  let dec3 = dec 3
  if twice dec3 8 <> 2 then exit 1

  let add2 = add4 2 3
  if add2 5 7 <> (2 + 3 + 5 + 7) then exit 1

  let f = add4
  if f 1 2 3 4 <> (1 + 2 + 3 + 4) then exit 1

  0
