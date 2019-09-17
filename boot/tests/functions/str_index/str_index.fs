let main _ =
  let hello = "hello"
  assert (hello.[0] = 'h' && hello.[4] = 'o')

  // Index type should be inferred as int.
  let at i (s: string) = s.[i]

  assert ((hello |> at 0) = 'h')

  0
