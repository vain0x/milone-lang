let main _ =
  let x, y, (z, w) = 1, 2, (3, 4)
  if not (x = 1 && y = 2 && z = 3 && w = 4) then exit 1

  let t11 = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
  0