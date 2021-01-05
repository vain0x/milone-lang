module rec str_literal_escape.Program

let f (_: char) = ()
let g (_: string) = ()

let main _ =
  f '\''
  f '\\'
  f '\x00'
  g "\"HELLO\n WORLD\""
  0
