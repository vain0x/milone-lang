module MiloneLang.Program

  open System

  type Verbosity =
    | Verbose
    | Silent

  let toCir verbosity (source: string): CDecl list =
    let log label obj =
      match verbosity with
      | Verbosity.Verbose ->
        eprintfn "%s = %A" label obj
      | Verbosity.Silent ->
        ()

    let tokens = Lexing.tokenize source
    log "tokens" tokens
    let ast = Parsing.parse tokens
    log "ast" ast
    let desugared = Desugaring.desugar ast
    log "desugared" ast
    let typedAst, tyCtx = Typing.infer desugared
    log "typed" typedAst
    let funTransAst, tyCtx = FunTrans.trans (typedAst, tyCtx)
    log "funTrans" funTransAst
    let mir, mirCtx = Mir.mirify (funTransAst, tyCtx)
    log "mir" mir
    let mir, mirTransCtx = MirTrans.trans (mir, mirCtx)
    log "trans" mir
    let cir = CIrGen.gen (mir, mirTransCtx)
    log "cir" cir
    cir

  let compile verbosity (source: string): string =
    source |> toCir verbosity |> CPrinting.cprint

  [<EntryPoint>]
  let main args =
    match List.ofArray args with
    | ["-v"; "-"] ->
      stdout.Write(stdin.ReadToEnd() |> compile Verbosity.Verbose)
      0
    | ["-q"; "-"] ->
      stdout.Write(stdin.ReadToEnd() |> compile Verbosity.Silent)
      0
    | _ ->
      eprintfn "USAGE: `milone -v -` or `milone -`"
      1
