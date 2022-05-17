module rec tuple_string.Program

let main _ =
  assert (string () = "()")
  assert (string (1, 2, 3) = "(1, 2, 3)")
  assert (string (1, 2, (3, 4)) = "(1, 2, (3, 4))")
  0
