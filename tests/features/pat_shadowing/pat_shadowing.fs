module rec pat_shadowing.Program

// Let expressions can define variables with the same name, i.e. shadowing is allowed.

let main _ =
  let case1 =
    let x = 1
    let x = 0
    assert (x = 0)

  let case2 =
    let x = 0
    (let x = 1
     assert (x = 1))
    assert (x = 0)

  0
