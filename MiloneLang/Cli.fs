/// Front end of the compiler.
module rec MiloneLang.Cli

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.SyntaxTokenize
open MiloneLang.SyntaxParse
open MiloneLang.Hir
open MiloneLang.TySystem
open MiloneLang.AstToHir
open MiloneLang.AutoBoxing
open MiloneLang.Bundling
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.MainHoist
open MiloneLang.TyElaborating
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.TailRecOptimizing
open MiloneLang.Monomorphizing
open MiloneLang.Kir
open MiloneLang.KirGen
open MiloneLang.KirPropagate
// open MiloneLang.KirToMir
open MiloneLang.KirDump
open MiloneLang.MirGen
open MiloneLang.Cir
open MiloneLang.CirGen
open MiloneLang.CirDump

let private helpText = """milone-lang compiler

USAGE:
    milone [SUBCOMMAND] OPTIONS...

EXAMPLE
    milone compile ./MiloneLang

SUBCOMMANDS
    milone compile <PROJECT-DIR>
        Compiles a milone-lang project to C.

        If success, writes generated C codes to STDOUT
        and exits with zero.

        If error, exits with non-zero code.
        Errors are written to STDOUT. (FIXME: use STDERR)

OPTIONS
    -h, --help      Print this text.
    -V, --version   Print version of the compiler.

GLOBAL OPTIONS
    -v, --verbose   Enable verbose logging for debug
        --profile   Enable profile logging
    -q, --quiet     Disable logging

LINKS
    <https://github.com/vain0x/milone-lang>"""

// -----------------------------------------------
// Interface (1)
// -----------------------------------------------

[<NoEquality; NoComparison>]
type Verbosity =
  | Verbose
  | Profile of Profiler
  | Quiet

/// Abstraction layer of CLI program.
[<NoEquality; NoComparison>]
type CliHost =
  {
    /// Command line args.
    Args: string list

    /// Path to milone home (installation directory).
    MiloneHome: string

    /// Creates a profiler.
    ProfileInit: (unit -> Profiler)

    /// Prints a message to stderr for profiling.
    ProfileLog: (string -> Profiler -> unit)

    /// Reads all contents of a file as string.
    FileReadAllText: (string -> string option) }

// -----------------------------------------------
// Helpers
// -----------------------------------------------

let private strTrimEnd (s: string) =
  let rec go i =
    if i = 0 || not (charIsSpace s.[i - 1]) then s |> strSlice 0 i else go (i - 1)

  go s.Length

let private charIsPathSep (c: char) = c = '/' || c = '\\'

let private pathStrTrimEndPathSep (s: string) =
  if s.Length >= 1 && charIsPathSep s.[s.Length - 1]
  then s |> strSlice 0 (s.Length - 1)
  else s

/// Gets the final component splitting by path separators.
let private pathStrToFileName (s: string) =
  let rec go i =
    if i = 0 then s
    else if charIsPathSep s.[i - 1] then s |> strSlice i s.Length
    else go (i - 1)

  go s.Length

/// Gets the file name without extension.
let private pathStrToStem (s: string) =
  match s |> pathStrToFileName with
  | "."
  | ".." -> s

  | s ->
      let rec go i =
        if i = 0 then s
        else if s.[i - 1] = '.' then s |> strSlice 0 (i - 1)
        else go (i - 1)

      go s.Length

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileCtx =
  { ProjectDir: string
    ProjectName: string

    Verbosity: Verbosity
    Host: CliHost }

let compileCtxNew (host: CliHost) verbosity projectDir: CompileCtx =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  { ProjectDir = projectDir
    ProjectName = projectName
    Verbosity = verbosity
    Host = host }

let private toBundleHost parse (ctx: CompileCtx): BundleHost =
  let host = ctx.Host
  let miloneHome = host.MiloneHome
  let readFile = host.FileReadAllText

  let readCoreFile (moduleName: string) =
    match readFile (miloneHome + "/libcore/" + moduleName + ".fs") with
    | Some it -> it
    | None ->
        printfn "Missing file: MILONE_HOME='%s' module='%s'" miloneHome moduleName
        failwithf "File not found"

  let readModuleFile (projectDir: string) (moduleName: string) =
    readFile (projectDir + "/" + moduleName + ".fs")

  let parseModule (moduleName: string) (contents: string) =
    // unique name?
    let docId: DocId = moduleName

    let ast, errors = parse docId contents
    Some(docId, ast, errors)

  { FetchModule =
      fun projectName moduleName ->
        if projectName = "MiloneCore" then
          parseModule moduleName (readCoreFile moduleName)
        else if projectName = ctx.ProjectName then
          match readModuleFile ctx.ProjectDir moduleName with
          | Some contents -> parseModule moduleName contents
          | None -> None
        else
          None }

// -----------------------------------------------
// Write output and logs
// -----------------------------------------------

let private writeLog (host: CliHost) verbosity msg =
  let profileLog = host.ProfileLog

  match verbosity with
  | Verbose ->
      // FIXME: to stderr
      printfn "// %s" msg

  | Profile profiler -> profiler |> profileLog msg

  | Quiet -> ()

let private syntaxHasError syntax =
  let _, _, errors = syntax
  errors |> List.isEmpty |> not

let private printSyntaxErrors syntax =
  let _, _, errors = syntax

  errors
  |> listSort (fun (_, l) (_, r) -> locCmp l r)
  |> List.iter (fun (msg, loc) -> printfn "#error %s %s" (locToString loc) msg)

let private tyCtxHasError (tyCtx: TyCtx) = tyCtx.Logs |> List.isEmpty |> not

let private printLogs (tyCtx: TyCtx) logs =
  let tyDisplayFn ty =
    let getTyName tySerial =
      tyCtx.Tys
      |> mapTryFind tySerial
      |> Option.map tyDefToName

    tyDisplay getTyName ty

  logs
  |> listSort (fun (_, l) (_, r) -> locCmp l r)
  |> List.iter (fun (log, loc) -> printfn "#error %s" (log |> logToString tyDisplayFn loc))

// -----------------------------------------------
// Processes
// -----------------------------------------------

/// Loads source codes from files, performs tokenization and SyntaxParse,
/// and transforms them into high-level intermediate representation (HIR).
let syntacticallyAnalyze (ctx: CompileCtx) =
  let host = ctx.Host
  let v = ctx.Verbosity

  writeLog host v ("Bundling project=" + ctx.ProjectName)

  let doParse (_: DocId) (s: string) = s |> tokenize |> parse
  match bundleProgram (ctx |> toBundleHost doParse) ctx.ProjectName with
  | Some syntax -> syntax
  | None -> failwithf "Entry module file not found: %s" ctx.ProjectName

/// Analyzes HIR to validate program and collect information.
let semanticallyAnalyze (host: CliHost) v (expr, nameCtx, errors) =
  writeLog host v "NameRes"
  let expr, scopeCtx = nameRes (expr, nameCtx)

  writeLog host v "Typing"
  infer (expr, scopeCtx, errors)

/// Transforms HIR. The result can be converted to KIR or MIR.
let transformHir (host: CliHost) v (expr, tyCtx) =
  writeLog host v "MainHoist"
  let expr, tyCtx = hoistMain (expr, tyCtx)

  writeLog host v "AutoBoxing"
  let expr, tyCtx = autoBox (expr, tyCtx)

  writeLog host v "TyElaborating"
  let expr, tyCtx = tyElaborate (expr, tyCtx)

  writeLog host v "ClosureConversion"
  let expr, tyCtx = closureConversion (expr, tyCtx)

  writeLog host v "EtaExpansion"
  let expr, tyCtx = etaExpansion (expr, tyCtx)

  writeLog host v "Hoist"
  let expr, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let expr, tyCtx = tailRecOptimize (expr, tyCtx)

  writeLog host v "Monomorphizing"
  monify (expr, tyCtx)

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir (host: CliHost) v (expr, tyCtx) =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (expr, tyCtx)

  if mirCtx.Logs |> List.isEmpty |> not then
    mirCtx.Logs |> printLogs tyCtx
    "", false
  else
    writeLog host v "CirGen"
    let cir, success = genCir (stmts, mirCtx)
    let output = cirDump cir

    writeLog host v "Finish"
    output, success

/// EXPERIMENTAL.
let dumpHirAsKir (host: CliHost) v (expr, tyCtx) =
  writeLog host v "KirGen"
  let kRoot, kirGenCtx = kirGen (expr, tyCtx)

  writeLog host v "KirPropagate"
  let kRoot, kirGenCtx = kirPropagate (kRoot, kirGenCtx)

  writeLog host v "KirDump"
  let result = kirDump "" "" (kRoot, kirGenCtx)

  writeLog host v "Finish"
  result, true

/// EXPERIMENTAL.
let codeGenHirViaKir (host: CliHost) v (expr, tyCtx) =
  writeLog host v "KirGen"
  let kRoot, kirGenCtx = kirGen (expr, tyCtx)

  writeLog host v "KirPropagate"
  let kRoot, kirGenCtx = kirPropagate (kRoot, kirGenCtx)

  failwith "compile with KIR is suspended"

// writeLog host v "KirToMir"
// let stmts, mirCtx = kirToMir (kRoot, kirGenCtx)

// writeLog host v "Cir generation"
// let cir, success = gen (stmts, mirCtx)
// let cOutput = cirDump cir

// writeLog host v "Finish"
// cOutput, success

let compile (ctx: CompileCtx): string * bool =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx
  if syntax |> syntaxHasError then
    printSyntaxErrors syntax
    "", false
  else
    let expr, tyCtx = semanticallyAnalyze host v syntax
    if tyCtx |> tyCtxHasError then
      tyCtx.Logs |> printLogs tyCtx
      "", false
    else
      let expr, tyCtx = transformHir host v (expr, tyCtx)
      codeGenHirViaMir host v (expr, tyCtx)

// -----------------------------------------------
// Actions
// -----------------------------------------------

let cliParse (host: CliHost) v (projectDir: string) =
  let ctx = compileCtxNew host v projectDir

  let parseWithLogging moduleName contents =
    writeLog
      host
      v
      ("\n-------------\nSyntaxParse %s...\n--------------"
       + moduleName)
    let ast, errors = contents |> tokenize |> parse

    if errors |> List.isEmpty |> not then
      printfn "In %s" moduleName

      errors
      |> List.iter (fun (msg, pos) -> printfn "ERROR: %s %s" (posToString pos) msg)

    match v with
    | Verbose -> printfn "%s" (objToString ast)
    | _ -> ()

    ast, errors

  bundleProgram (ctx |> toBundleHost parseWithLogging) ctx.ProjectName
  |> ignore
  0

let cliCompile (host: CliHost) verbosity projectDir =
  let ctx = compileCtxNew host verbosity projectDir

  let output, success = compile ctx
  let exitCode = if success then 0 else 1

  printfn "%s" (output |> strTrimEnd)
  exitCode

let cliKirDump (host: CliHost) projectDirs =
  let v = Quiet
  printfn "// Common code.\n%s\n" (kirHeader ())

  projectDirs
  |> List.fold (fun code projectDir ->
       printfn "// -------------------------------\n// %s\n{\n" projectDir
       printfn "/*"

       let ctx = compileCtxNew host v projectDir

       let output, success =
         let syntax = syntacticallyAnalyze ctx

         let expr, tyCtx = semanticallyAnalyze host v syntax

         if tyCtx |> tyCtxHasError then
           tyCtx.Logs |> printLogs tyCtx
           "", false
         else
           let expr, tyCtx = transformHir host v (expr, tyCtx)
           dumpHirAsKir host v (expr, tyCtx)

       let code =
         if success then
           printfn "*/"
           printfn "%s" (output |> strTrimEnd)
           code
         else
           printfn "\n%s\n*/" output
           1

       printfn "\n// exit = %d\n}\n" code
       code) 0

let cliCompileViaKir (host: CliHost) projectDirs =
  let v = Quiet
  printfn "// Generated using KIR.\n"

  projectDirs
  |> List.fold (fun code projectDir ->
       printfn "// -------------------------------\n// %s\n" projectDir
       printfn "/*"

       let ctx = compileCtxNew host v projectDir

       let output, success =
         let syntax = syntacticallyAnalyze ctx

         let expr, tyCtx = semanticallyAnalyze host v syntax

         if tyCtx |> tyCtxHasError then
           tyCtx.Logs |> printLogs tyCtx
           "", false
         else
           let expr, tyCtx = transformHir host v (expr, tyCtx)
           codeGenHirViaKir host v (expr, tyCtx)

       let code =
         if success then
           printfn "*/"
           printfn "%s" (output |> strTrimEnd)
           code
         else
           printfn "\n%s\n*/" output
           1

       printfn "\n// exit = %d\n" code
       code) 0

// -----------------------------------------------
// Arg parsing
// -----------------------------------------------

/// Parses CLI args for a flag.
///
/// `picker state arg` should return `Some state` if arg is consumed. None otherwise.
///
/// Returns final state and args not consumed.
let private parseFlag picker state args =
  // acc: args not consumed in reversed order
  let rec go acc state args =
    match args with
    | []
    | "--" :: _ -> state, List.append (List.rev acc) args

    | arg :: args ->
        match picker state arg with
        | Some state -> go acc state args

        | None -> go (arg :: acc) state args

  go [] state args

let private containsHelpFlag args =
  let ok, _ =
    parseFlag (fun _ arg ->
      match arg with
      | "-h"
      | "--help" -> Some true
      | _ -> None) false args

  ok

let private parseVerbosity (host: CliHost) args =
  parseFlag (fun (_: Verbosity) arg ->
    match arg with
    | "-v" -> Some Verbose
    | "-q" -> Some Quiet
    | "--profile" -> Some(Profile(host.ProfileInit()))
    | _ -> None) Quiet args

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CompileCmd
  | ParseCmd
  | KirDumpCmd
  | BadCmd of string

let private parseArgs args =
  match args with
  | []
  | "help" :: _ -> HelpCmd, []
  | _ when args |> containsHelpFlag -> HelpCmd, []

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ -> VersionCmd, []

  // for backward
  | "-v" :: _
  | "-q" :: _
  | "--profile" :: _ -> CompileCmd, args

  | arg :: args ->
      match arg with
      | "build"
      | "compile" -> CompileCmd, args

      // for debug
      | "parse" -> ParseCmd, args
      | "kir-dump" -> KirDumpCmd, args
      | "kir-c" -> CompileCmd, "--kir" :: args

      | _ -> BadCmd arg, []

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

let cli (host: CliHost) =
  match host.Args |> parseArgs with
  | HelpCmd, _ ->
      printfn "%s" helpText
      0

  | VersionCmd, _ ->
      printfn "0.1.0"
      0

  | CompileCmd, args ->
      let verbosity, args = parseVerbosity host args

      let useKir, args =
        parseFlag (fun _ arg -> if arg = "--kir" then Some true else None) false args

      match useKir, args with
      | true, _ -> cliCompileViaKir host args

      | false, projectDir :: _ -> cliCompile host verbosity projectDir

      | false, [] ->
          printfn "ERROR: Expected project dir."
          1

  | ParseCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ -> cliParse host verbosity projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | KirDumpCmd, projectDirs -> cliKirDump host projectDirs

  | BadCmd subcommand, _ ->
      printfn "ERROR: Unknown subcommand '%s'." subcommand
      1
