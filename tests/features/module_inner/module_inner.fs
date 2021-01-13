module rec module_inner.Program

// Inner module statements.

module rec Inner =
  let f x = x + 1

let main _ =
  assert (Inner.f 2 = 3)
  0
