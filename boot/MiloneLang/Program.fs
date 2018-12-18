module MiloneLang.Program

  open System

  type Verbosity =
    | Verbose
    | Silent

  let private eol = """
"""

  let toCir verbosity (source: string): CDecl list * (string * Loc) list =
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

    match Typing.infer desugared with
    | typedAst, (_ :: _ as errors), _ ->
      log "typed" typedAst
      [], errors
    | typedAst, [], tyCtx ->

    log "typed" typedAst
    let funTransAst, tyCtx = FunTrans.trans (typedAst, tyCtx)
    log "funTrans" funTransAst
    let mir, mirCtx = Mir.mirify (funTransAst, tyCtx)
    log "mir" mir
    let cir = CIrGen.gen (mir, mirCtx)
    log "cir" cir
    cir, []

  let runCompile verbosity =
    let source = stdin.ReadToEnd()
    match source |> toCir verbosity with
    | _, (_ :: _ as errors) ->
      errors
      |> List.map (fun (message, (y, x)) -> sprintf "ERROR(%d:%d) %s" (y + 1) (x + 1) message)
      |> String.concat eol
      |> eprintfn "%s"
      1
    | decls, [] ->
      CPrinting.cprint decls
      |> printf "%s"
      0

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
