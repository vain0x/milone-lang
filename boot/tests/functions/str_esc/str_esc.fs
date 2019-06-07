let f (_ : char) = ()
let g (_ : string) = ()

let main _ =
  f '\''
  f '\\'
  f '\u0000'
  g "\"HELLO\n WORLD\""
  0
