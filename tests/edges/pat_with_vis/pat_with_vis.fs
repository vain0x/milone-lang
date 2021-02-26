module rec pat_with_vis.Program

type Wrap = Wrap of int

let (Wrap (public x), private y) = Wrap 2, 3

let main _ =
  assert (x = 2)
  assert (y = 3)
  0
