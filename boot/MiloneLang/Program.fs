module MiloneLang.Program

  open System

  type Verbosity =
    | Verbose
    | Silent

  let private eol = """
"""

  let toCir verbosity (source: string): CDecl list * bool =
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
    let cir, success = CIrGen.gen (mir, mirCtx)
    log "cir" cir
    cir, success

  let runCompile verbosity =
    let source = stdin.ReadToEnd()
    let cir, success = source |> toCir verbosity
    let exitCode = if success then 0 else 1
    printf "%s" (CPrinting.cprint cir)
    exitCode

  [<EntryPoint>]
  let main args =
    match List.ofArray args with
    | ["-v"; "-"] ->
      runCompile Verbosity.Verbose
    | ["-q"; "-"] ->
      runCompile Verbosity.Silent
    | _ ->
      eprintfn "USAGE: `milone -v -` or `milone -`"
      1
