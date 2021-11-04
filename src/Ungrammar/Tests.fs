module rec UngrammarTests.Program

module Parse = Ungrammar.Parse
module Tokenize = Ungrammar.Tokenize

let locate (text: string) (pos: int) : int * int =
  let s =
    text.Substring(0, pos).Replace("\r\n", "\n")

  let n = s.LastIndexOf("\n")

  if n >= 0 then
    s.Split("\n").Length - 1, pos - n - 1
  else
    0, pos

let fail text pos msg =
  let y, x = locate text pos
  printfn "%d:%d %s" (y + 1) (x + 1) msg

[<EntryPoint>]
let main _ =
  let text = stdin.ReadToEnd()

  let tokens =
    match Tokenize.tokenize text with
    | Ok it -> it
    | Error (msg, pos) ->
      fail text pos (sprintf "%A" msg)
      exit 1

  let grammar, errors = Parse.parse text tokens
  printfn "%A" (grammar.Rules |> Map.toList)

  for msg, pos in errors do
    fail text pos msg

  0
