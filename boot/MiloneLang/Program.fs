module MiloneLang.Program
  open System

  type Verbosity =
    | Verbose
    | Silent

  let parseProjectModules (projectDir: string) =
    let modulePath moduleName = IO.Path.Combine(projectDir, sprintf "%s.milone" moduleName)
    let readModuleFile moduleName = IO.File.ReadAllText(modulePath moduleName)
    let projectName = IO.Path.GetFileName(projectDir)
    Bundling.parseProjectModules readModuleFile projectName

  let toCir verbosity (projectDir: string): CDecl list * bool =
    let log label obj =
      match verbosity with
      | Verbosity.Verbose ->
        eprintfn "%s = %A" label obj
      | Verbosity.Silent ->
        ()

    let ast = parseProjectModules projectDir
    // let tokens = Lexing.tokenize source
    // log "tokens" tokens
    // let ast = Parsing.parse tokens
    // log "ast" ast
    let desugared = Desugaring.desugar ast
    log "desugared" ast
    let typedAst, tyCtx = Typing.infer desugared
    log "typed" typedAst
    let funTransAst, tyCtx = FunTrans.trans (typedAst, tyCtx)
    log "funTrans" funTransAst
    let monoAst, tyCtx = Monomorphizing.monify (funTransAst, tyCtx)
    log "monoAst" monoAst
    let mir, mirCtx = Mir.mirify (monoAst, tyCtx)
    log "mir" mir
    let cir, success = CIrGen.gen (mir, mirCtx)
    log "cir" cir
    cir, success

  let runCompile verbosity projectDir =
    let cir, success = toCir verbosity projectDir
    let exitCode = if success then 0 else 1
    printf "%s" (CPrinting.cprint cir)
    exitCode

  [<EntryPoint>]
  let main args =
    match List.ofArray args with
    | ["-v"; projectDir] ->
      runCompile Verbosity.Verbose projectDir
    | ["-q"; projectDir] ->
      runCompile Verbosity.Silent projectDir
    | _ ->
      eprintfn """USAGE: milone [OPTIONS] <project-dir>

EXAMPLE
    milone -q /path/to/foo

DESCRIPTION
    Compile the specified project
    and write compiled C-language code to standard output
    or compile error messages to standard error.

    Note that `foo.milone` is the entry point of the project
    that is located at `/path/to/foo`.

ARGS
    project-dir
        where the source files are located

OPTIONS
    -q  No debug logs
    -v  Verbose debug logs
"""
      1
