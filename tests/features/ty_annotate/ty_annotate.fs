module rec ty_annotate.Program

// Type annotation (`xxx : type`).

let main _ =
  let f x: int = x
  let g (x: int) = x
  let zero = f 1 - g 1

  let xs: _ list = [ 1 ]

  let ys: list<string> = [ "a" ]

  zero
