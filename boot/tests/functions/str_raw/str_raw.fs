let testEol () =
  let eol = """
"""
  assert (eol = "\n" || eol = "\r\n")

let testNoEscape () =
  assert (""" \"" """ = " \\\"\" ")

let main _ =
  testEol ()
  testNoEscape ()
  0
