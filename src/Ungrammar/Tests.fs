module rec UngrammarTests.Program

open Ungrammar.Tokenize

[<EntryPoint>]
let main _ =
  let text = stdin.ReadToEnd()
  printfn "%A" (tokenize text)
  0
