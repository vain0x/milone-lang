module rec MiloneStd.Equal

let genericListEqual (equalFun: 'T -> 'T -> bool) (xs: 'T list) (ys: 'T list) : bool =
  match xs, ys with
  | [], [] -> true
  | x :: xs, y :: ys when equalFun x y -> genericListEqual equalFun xs ys
  | _ -> false
