module rec module_inner.Program

// Inner module statements.

module sub = module_inner.sub

module rec Inner =
  let f x = x + 1

let main _ =
  // Inner module in the same file.
  assert (Inner.f 2 = 3)

  // Inner module in another file.
  assert (sub.Inner.decrement 3 = 2)
  0
