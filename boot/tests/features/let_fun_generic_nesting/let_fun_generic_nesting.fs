let main _ =
  // Case 1.
  let id x =
    // aux must not be generic.
    let aux () = x
    aux ()
  assert (id 1 = 1)

  // Case 2.
  let goo x =
    // gooAux must not be generic.
    let gooAux () = id x
    gooAux ()
  assert (goo 1 = 1)

  0
