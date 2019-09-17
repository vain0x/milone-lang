let main _ =
  let case1 =
    let x = 1
    let x = 0
    assert (x = 0)

  let case2 =
    let x = 0
    (
      let x = 1
      assert (x = 1)
    )
    assert (x = 0)

  let case3 =
    let x = 'A'
    let x = 1
    in
      assert (x = 1)
    assert (x = 'A')

  0
