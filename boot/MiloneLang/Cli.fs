/// Front end of the compiler.
module rec MiloneLang.Cli

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers
open MiloneLang.Lexing
open MiloneLang.Parsing
open MiloneLang.AstToHir
open MiloneLang.Bundling
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.MainHoist
open MiloneLang.TyElaborating
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.Monomorphizing
open MiloneLang.Mir
open MiloneLang.KirGen
open MiloneLang.KirPropagate
open MiloneLang.KirToMir
open MiloneLang.KirDump
open MiloneLang.CIrGen
open MiloneLang.CPrinting

type Verbosity =
  | Verbose
  | Profile of Profiler
  | Quiet

let helpText = """USAGE: milone [OPTIONS] <project-dir>

EXAMPLE
    milone -q /path/to/foo

DESCRIPTION
    Compile the specified project
    and write compiled C-language code to standard output
    or compile error messages to standard error.

    Note that `Foo.fs` is the entry point of the project
    that is located at `/path/to/Foo`.

ARGS
    project-dir
        where the source files are located

OPTIONS
    -q              No debug logs
    -v              Verbose debug logs
       --profile    Print logs with time interval"""

let strTrimEnd (s: string) =
  let rec go i =
    if i = 0 || not (charIsSpace s.[i - 1]) then s |> strSlice 0 i else go (i - 1)

  go s.Length

let charIsPathSep (c: char) = c = '/' || c = '\\'

let pathStrTrimEndPathSep (s: string) =
  if s.Length >= 1 && charIsPathSep s.[s.Length - 1]
  then s |> strSlice 0 (s.Length - 1)
  else s

/// Gets the final component splitting by path separators.
let pathStrToFileName (s: string) =
  let rec go i =
    if i = 0 then s
    else if charIsPathSep s.[i - 1] then s |> strSlice i s.Length
    else go (i - 1)

  go s.Length

/// Gets the file name without extension.
let pathStrToStem (s: string) =
  match s |> pathStrToFileName with
  | "."
  | ".." -> s

  | s ->
      let rec go i =
        if i = 0 then s
        else if s.[i - 1] = '.' then s |> strSlice 0 (i - 1)
        else go (i - 1)

      go s.Length

let tyCtxHasError tyCtx =
  tyCtx |> tyCtxGetLogs |> listIsEmpty |> not

let printLogs logs =
  logs
  |> listIter (fun (log, loc) -> printfn "#error %s" (log |> logToString loc))
  "", false

let build host verbosity (projectDir: string): string * bool =
  let profileLog = host |> cliHostGetProfileLog
  let readFile = host |> cliHostGetFileReadAllText

  let log msg =
    match verbosity with
    | Verbose ->
        // FIXME: to stderr
        printfn "// %s" msg

    | Profile profiler -> profiler |> profileLog msg

    | Quiet -> ()

  let projectDir = projectDir |> pathStrTrimEndPathSep

  let projectName = projectDir |> pathStrToStem
  log ("Begin compiling project=" + projectName)

  let readModuleFile moduleName =
    // log ("Open module " + moduleName)
    readFile (projectDir + "/" + moduleName + ".fs")

  let expr, nameCtx, errorListList =
    let parseTokens (_moduleName: string) tokens =
      // log ("Parsing " + moduleName)
      parse tokens

    parseProjectModules readModuleFile parseTokens projectName (nameCtxEmpty ())

  log "Name resolution"
  let expr, scopeCtx = nameRes (expr, nameCtx)

  log "Type inference"
  let expr, tyCtx = infer (expr, scopeCtx, errorListList)
  if tyCtx |> tyCtxHasError then
    tyCtx |> tyCtxGetLogs |> printLogs
  else

    log "Hoist main"
    let expr, tyCtx = hoistMain (expr, tyCtx)

    log "TyElaboration"
    let expr, tyCtx = tyElaborate (expr, tyCtx)

    log "Closure conversion"
    let expr, tyCtx = declosure (expr, tyCtx)
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs |> printLogs
    else

      log "Eta expansion"
      let expr, tyCtx = uneta (expr, tyCtx)
      if tyCtx |> tyCtxHasError then
        tyCtx |> tyCtxGetLogs |> printLogs
      else

        log "Hoist"
        let expr, tyCtx = hoist (expr, tyCtx)

        log "Monomorphization"
        let expr, tyCtx = monify (expr, tyCtx)
        if tyCtx |> tyCtxHasError then
          tyCtx |> tyCtxGetLogs |> printLogs
        else

          log "Mir generation"
          let stmts, mirCtx = mirify (expr, tyCtx)

          if mirCtx |> mirCtxGetLogs |> listIsEmpty |> not then
            mirCtx |> mirCtxGetLogs |> printLogs
          else

            log "Cir generation"
            let cir, success = gen (stmts, mirCtx)

            let output = cprint cir

            log "Finished"
            output, success

let cliParse host (projectDir: string) =
  let readFile = host |> cliHostGetFileReadAllText

  // print errors
  let rec go1 code errors =
    match errors with
    | [] -> code

    | (msg, pos) :: errors ->
        printfn "ERROR: %s %s" (posToString pos) msg
        go1 1 errors

  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let readModuleFile moduleName =
    readFile (projectDir + "/" + moduleName + ".fs")

  let parseWithLogging moduleName tokens =
    printfn "\n-------------\nParsing %s...\n--------------" moduleName
    let ast, errors = parse tokens
    go1 0 errors |> ignore
    printfn "%s" (objToString ast)
    ast, errors

  parseProjectModules readModuleFile parseWithLogging projectName (nameCtxEmpty ())
  |> ignore
  0

let cliCompile host verbosity projectDir =
  let output, success = build host verbosity projectDir
  let exitCode = if success then 0 else 1

  printfn "%s" (output |> strTrimEnd)
  exitCode

// experimental: use kir
let buildWithKir host verbosity mode (projectDir: string): string * bool =
  let profileLog = host |> cliHostGetProfileLog
  let readFile = host |> cliHostGetFileReadAllText

  let readModuleFile moduleName =
    readFile (projectDir + "/" + moduleName + ".fs")

  let parseTokens (_moduleName: string) tokens = parse tokens

  let log msg =
    match verbosity with
    | Profile profiler -> profiler |> profileLog msg

    | Verbose
    | Quiet -> ()

  let projectDir = projectDir |> pathStrTrimEndPathSep

  let projectName = projectDir |> pathStrToStem
  log ("Begin compiling project=" + projectName)

  let expr, nameCtx, errorListList =
    parseProjectModules readModuleFile parseTokens projectName (nameCtxEmpty ())

  log "Name resolution"
  let expr, scopeCtx = nameRes (expr, nameCtx)

  log "Type inference"
  let expr, tyCtx = infer (expr, scopeCtx, errorListList)
  if tyCtx |> tyCtxHasError then
    tyCtx |> tyCtxGetLogs |> printLogs
  else
    log "Hoist main"
    let expr, tyCtx = hoistMain (expr, tyCtx)

    log "TyElaboration"
    let expr, tyCtx = tyElaborate (expr, tyCtx)

    log "Closure conversion"
    let expr, tyCtx = declosure (expr, tyCtx)
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs |> printLogs
    else
      log "Eta expansion"
      let expr, tyCtx = uneta (expr, tyCtx)
      if tyCtx |> tyCtxHasError then
        tyCtx |> tyCtxGetLogs |> printLogs
      else
        log "Hoist"
        let expr, tyCtx = hoist (expr, tyCtx)

        log "Monomorphization"
        let expr, tyCtx = monify (expr, tyCtx)
        if tyCtx |> tyCtxHasError then
          tyCtx |> tyCtxGetLogs |> printLogs
        else
          log "KirGen"
          let kRoot, kirGenCtx = kirGen (expr, tyCtx)

          let kRoot, kirGenCtx = kirPropagate (kRoot, kirGenCtx)

          if mode then
            log "KirDump"

            let output =
              kirDump projectName "" (kRoot, kirGenCtx)

            output, true
          else
            log "KirToMir"
            let stmts, mirCtx = kirToMir (kRoot, kirGenCtx)

            log "Cir generation"
            let cir, success = gen (stmts, mirCtx)
            let cOutput = cprint cir
            cOutput, success

// log "KirToMir"
// let stmts, mirCtx = kirToMir (kRoot, kirGenCtx)

// if mirCtx |> mirCtxGetLogs |> listIsEmpty |> not then
//   mirCtx |> mirCtxGetLogs |> printLogs
// else
//   log "Cir generation"
//   let cir, success = gen (stmts, mirCtx)

//   let output = cprint cir

//   log "Finished"
//   output, success

let cliCompileWithKirToDump host verbosity projectDir =
  printfn "/*"

  let output, success =
    buildWithKir host verbosity true projectDir

  if success then
    printfn "*/"
    printfn "%s" (output |> strTrimEnd)
    0
  else
    printfn "\n%s\n*/" output
    1

let cliCompileWithKirToClang host verbosity projectDir =
  printfn "/*"

  let output, success =
    buildWithKir host verbosity false projectDir

  if success then
    printfn "*/"
    printfn "%s" (output |> strTrimEnd)
    0
  else
    printfn "\n%s\n*/" output
    1

let cli (host: CliHost) =
  match host |> cliHostGetArgs with
  | [ "parse"; projectDir ] -> cliParse host projectDir

  | [ "-v"; projectDir ] -> cliCompile host Verbose projectDir

  | [ "--profile"; projectDir ] ->
      let profile = Profile(cliHostGetProfileInit host ())

      cliCompile host profile projectDir

  | [ "-q"; projectDir ] -> cliCompile host Quiet projectDir

  // experimental feature
  | "--kir-dump" :: projectDirs ->
      printfn "// Common code.\n%s\n" (kirHeader ())

      projectDirs
      |> listFold (fun success projectDir ->
           printfn "// -------------------------------\n// %s\n{\n" projectDir

           let code =
             cliCompileWithKirToDump host Quiet projectDir

           printfn "\n// exit = %d\n}\n" code

           code + success) 0

  | "--kir-c" :: projectDirs ->
      printfn "// Generated using KIR.\n"

      projectDirs
      |> listFold (fun success projectDir ->
           printfn "// -------------------------------\n// %s\n" projectDir

           let code =
             cliCompileWithKirToClang host Quiet projectDir

           printfn "\n// exit = %d\n" code

           code + success) 0

  | _ ->
      // FIXME: to stderr
      printfn "%s" helpText
      1
