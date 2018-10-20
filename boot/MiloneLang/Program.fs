module MiloneLang.Program

  open System

  let toAst (source: string): Expr<Loc> list =
    let tokens = Lexing.tokenize source
    eprintfn "tokens = %A" tokens
    let ast = Parsing.parse tokens
    eprintfn "ast = %A" ast
    ast

  let toCir (source: string): CDecl list =
    source |> toAst |> Typing.infer |> Mir.mirify |> CIrGen.gen

  let transpile (source: string): string =
    source |> toCir |> CPrinting.cprint

  [<EntryPoint>]
  let main args =
    match List.ofArray args with
    | ["-t"; "c"] ->
      stdout.Write(stdin.ReadToEnd() |> transpile)
      0
    | ["--infer"] ->
      stdout.Write(stdin.ReadToEnd() |> toAst |> Typing.infer |> sprintf "%A")
      0
    | _ ->
      1
