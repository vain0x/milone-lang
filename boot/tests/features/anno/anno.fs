let main _ =
  let f x = x : int
  let g (x : int) = x
  let zero = f 1 - g 1

  let xs: _ list = [1]

  let ys: list<string> = ["a"]

  zero
