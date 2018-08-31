module MiloneLang.Program

  open System

  let run (source: string): ProcessOutput =
    let tokens = Parsing.lex source
    eprintfn "tokens = %A" tokens
    let stmt = Parsing.parse tokens
    eprintfn "parsed = %A" stmt
    Eval.eval stmt

  [<EntryPoint>]
  let main _ =
    let output = stdin.ReadToEnd() |> run
    for line in output.Outs do
      match line with
      | StdOut, line ->
        stdout.WriteLine(line)
      | StdErr, line ->
        stderr.WriteLine(line)
    output.Code
