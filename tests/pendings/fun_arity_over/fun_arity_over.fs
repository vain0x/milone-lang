let main _ =
  let f : int -> int -> int =
    // `add` is 1-arity.
    let add (x: int) : int -> int =
      let inc () (y: int) : int = x + y
      // Return a function object with arity 1.
      inc ()

    // FIXME: `f`'s result should be a function object with arity 2,
    //        however, the actual result is 1-arity for now.
    add

  // We need convert `add` to something like this:
  // let f x y =
  //   let inc = add x
  //   inc y
  // f

  // exit 0

  assert (f 2 3 = 5)

  0
