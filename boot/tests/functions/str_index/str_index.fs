let main _ =
  let hello = "hello"
  if not (hello.[0] = 'h' && hello.[4] = 'o') then exit 1

  // Index type should be inferred as int.
  let at i (s: string) = s.[i]

  if (hello |> at 0) <> 'h' then exit 1

  0
