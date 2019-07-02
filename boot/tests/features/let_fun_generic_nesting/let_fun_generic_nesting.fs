let main _ =
  let id x =
    let aux () = x
    aux ()
  assert (id 1 = 1)
  0
