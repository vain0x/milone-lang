module MiloneLang.Program

  open System

  let toAst (source: string) =
    let tokens = Lexing.tokenize source
    eprintfn "tokens = %A" tokens
    let ast = Parsing.parse tokens
    eprintfn "ast = %A" ast
    ast

  let toCir (source: string) =
    source |> toAst |> CIrGen.gen

  let run (source: string): ProcessOutput =
    source |> toAst |> Eval.eval

  let transpile (source: string) =
    source |> toCir |> CPrinting.cprint

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
