module rec str_literal_escape.Program

let f (_: char) = ()
let g (_: string) = ()

let main _ =
  f '\''
  f '\\'
  f '\x00'
  f '\x7f'
  f '\xFF'
  g "\"HELLO\n WORLD\""
  g "\x7f"

  // FIXME: escape invalid UTF-8 sequence
  g "\x80 \xc1"
  0
