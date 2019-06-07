let main _ =
  if char 97 <> 'a' then exit 1
  if char 0 <> '\u0000' then exit 1

  if int 0 <> 0 then exit 1
  if int 'a' - 97 <> 0 then exit 1
  if int "42" - 42 <> 0 then exit 1
  if int "-1" + 1 <> 0 then exit 1

  if string 0 <> "0" then exit 1
  if string (0 - 97) <> "-97" then exit 1
  if string 'a' <> "a" then exit 1
  if string '\u0000' <> "" then exit 1
  if string "fix" <> "fix" then exit 1

  0
