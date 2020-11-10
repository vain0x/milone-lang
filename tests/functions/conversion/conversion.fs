let main _ =
  assert (char 97 = 'a')
  assert (char 0 = '\x00')

  assert (int 0 = 0)
  assert (int 'a' - 97 = 0)
  assert (int "42" - 42 = 0)
  assert (int "-1" + 1 = 0)

  assert (string 0 = "0")
  assert (string (0 - 97) = "-97")
  assert (string 'a' = "a")
  assert (string '\x00' = "")
  assert (string "fix" = "fix")

  0
