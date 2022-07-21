let main _ =
  assert (int 0 = 0)
  assert (int "42" - 42 = 0)
  assert (int "-1" + 1 = 0)

  assert (string 0 = "0")
  assert (string (0 - 97) = "-97")
  assert (string 'a' = "a")
  assert (string '\x00' = "")
  assert (string "fix" = "fix")

  0
