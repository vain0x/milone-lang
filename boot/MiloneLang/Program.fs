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

  let toCir (source: string) =
    let tokens = Lexing.tokenize source
    let syn = Lexing.compose tokens
    let ast = Parsing.parse syn
    CIrGen.gen ast

  let transpile (source: string) =
    let cir = toCir source
    CPrinting.cprint cir

  [<EntryPoint>]
  let main args =
    match List.ofArray args with
    | ["-t"; "c"] ->
      stdout.Write(stdin.ReadToEnd() |> transpile)
      0
    | _ ->
      let output = stdin.ReadToEnd() |> run
      for line in output.Outs do
        match line with
        | StdOut, line ->
          stdout.WriteLine(line)
        | StdErr, line ->
          stderr.WriteLine(line)
      output.Code
