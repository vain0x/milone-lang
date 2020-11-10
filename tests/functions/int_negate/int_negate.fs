let main _ =
  let m = -2
  assert (m + 2 = 0)

  let u = 2
  let v = -u
  assert (v + 2 = 0)

  let f x = x - 2
  let y = -f 4
  assert (y + 2 = 0)
  0
