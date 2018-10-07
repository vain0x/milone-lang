module MiloneLang.Program

  open System

  let run (source: string): ProcessOutput =
    let tokens = Lexing.tokenize source
    eprintfn "tokens = %A" tokens
    let syns = Lexing.compose tokens
    eprintfn "syn = %A" syns
    let stmts = Parsing.parse syns
    eprintfn "parsed = %A" stmts
    Eval.eval stmts

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
