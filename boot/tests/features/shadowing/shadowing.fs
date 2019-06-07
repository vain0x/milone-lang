let main _ =
  let case1 =
    let x = 1
    let x = 0
    if x <> 0 then exit 1

  let case2 =
    let x = 0
    (
      let x = 1
      if x <> 1 then exit 1
    )
    if x <> 0 then exit 1

  let case3 =
    let x = 'A'
    let x = 1
    in
      if x <> 1 then exit 1
    if x <> 'A' then exit 1

  0
