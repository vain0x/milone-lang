/// Front end of the compiler.
module rec MiloneLang.Cli

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.SyntaxTokenize
open MiloneLang.SyntaxParse
open MiloneLang.AstBundle
open MiloneLang.Hir
open MiloneLang.TySystem
open MiloneLang.AstToHir
open MiloneLang.AutoBoxing
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.MainHoist
open MiloneLang.RecordRes
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.TailRecOptimizing
open MiloneLang.Monomorphizing
open MiloneLang.MirGen
open MiloneLang.Cir
open MiloneLang.CirGen
open MiloneLang.CirDump

module C = MiloneStd.StdChar
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module S = MiloneStd.StdString

let private currentVersion () = "0.3.0"

let private helpText () =
  """milone-lang v"""
  + currentVersion ()
  + """ <https://github.com/vain0x/milone-lang>

USAGE:
    milone <SUBCOMMAND> OPTIONS...

EXAMPLE
    milone compile ./MiloneLang

SUBCOMMANDS
    milone check <PROJECT-DIR>
        Checks a milone-lang project.

        Performs syntax validation and type checking
        but skips code generation.

        If error, exits with non-zero code
        after writing errors to standard output.

    milone compile <PROJECT-DIR>
        Compiles a milone-lang project to C.

        If success, writes generated C codes to STDOUT
        and exits with zero.

        If error, exits with non-zero code.
        Errors are written to STDOUT. (FIXME: use STDERR)

    milone header <PROJECT-DIR>
        Compiles to C only declarations.

OPTIONS
    -h, --help      Print help text.
    -V, --version   Print compiler version.

GLOBAL OPTIONS
    -v, --verbose   Enable verbose logging for debug
        --profile   Enable profile logging
    -q, --quiet     Disable logging"""

// -----------------------------------------------
// Interface (1)
// -----------------------------------------------

type private ProjectName = string

type private ProjectDir = string

type private ModuleName = string

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

    /// Path to $HOME.
    Home: string

    /// Path to milone home (installation directory).
    MiloneHome: string

    /// Creates a profiler.
    ProfileInit: unit -> Profiler

    /// Prints a message to stderr for profiling.
    ProfileLog: string -> Profiler -> unit

    /// Reads all contents of a file as string.
    FileReadAllText: string -> string option

    /// Writes to text file.
    FileWriteAllText: string -> string -> unit

    /// Writes to standard output.
    WriteStdout: string -> unit }

// -----------------------------------------------
// Helpers
// -----------------------------------------------

let private charIsPathSep (c: char) = c = '/' || c = '\\'

let private pathStrTrimEndPathSep (s: string) = S.trimEndIf charIsPathSep s

// wants string.findLastIndex
/// Gets the final component splitting by path separators.
let private pathStrToFileName (s: string) =
  let rec go i =
    if i = 0 then
      s
    else if charIsPathSep s.[i - 1] then
      s |> S.slice i s.Length
    else
      go (i - 1)

  go s.Length

/// Gets the file name without extension.
let private pathStrToStem (s: string) =
  match s |> pathStrToFileName with
  | "."
  | ".." -> s

  | s ->
      match s |> S.findLastIndex "." with
      | Some i -> s |> S.slice 0 (i - 1)
      | None -> s

let private pathIsRelative (s: string) =
  (s |> S.startsWith "./")
  || (s |> S.startsWith "../")

// -----------------------------------------------
// MiloneCore resolution
// -----------------------------------------------

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let resolveMiloneCoreDeps tokens ast =
  let knownNames = [ "List"; "Option"; "String" ]

  let isKnownName moduleName =
    knownNames
    |> List.exists (fun name -> name = moduleName)

  let moduleMap =
    let rec go acc tokens =
      match tokens with
      | [] -> acc
      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens -> go ((moduleName, pos) :: acc) tokens
      | _ :: tokens -> go acc tokens

    let moduleNames = go [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownName moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    moduleNames |> List.fold add (TMap.empty compare)

  let insertOpenDecls decls =
    moduleMap
    |> TMap.fold
         (fun decls moduleName pos ->
           AModuleSynonymDecl(
             Name(moduleName, pos),
             [ Name("MiloneCore", pos)
               Name(moduleName, pos) ],
             pos
           )
           :: decls)
         decls

  match ast with
  | AExprRoot decls -> AExprRoot(insertOpenDecls decls)
  | AModuleRoot (name, decls, pos) -> AModuleRoot(name, insertOpenDecls decls, pos)

// -----------------------------------------------
// Context
// -----------------------------------------------

type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileCtx =
  { ProjectDir: string
    ProjectName: string

    /// project name -> project directory
    Projects: AssocMap<string, string>

    TokenizeHost: TokenizeHost
    FetchModule: ProjectName -> ProjectDir -> ModuleName -> ModuleSyntaxData option

    HeaderOnly: bool

    Verbosity: Verbosity
    Host: CliHost }

let compileCtxNew (host: CliHost) verbosity projectDir : CompileCtx =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let miloneHome =
    if host.MiloneHome <> "" then
      host.MiloneHome
    else
      host.Home + "/.milone"

  let projects =
    TMap.empty compare
    |> TMap.add "MiloneCore" (miloneHome + "/milone_libs/MiloneCore")
    |> TMap.add "MiloneStd" (miloneHome + "/milone_libs/MiloneStd")
    |> TMap.add projectName projectDir

  let readModuleFile (_: string) (projectDir: string) (moduleName: string) =
    let read (ext: string) =
      match host.FileReadAllText(projectDir + "/" + moduleName + ext) with
      | Some text -> Some(moduleName, text)
      | None -> None

    match read ".milone" with
    | (Some _) as it -> it
    | None -> read ".fs"

  let tokenizeHost = tokenizeHostNew ()

  let doParse (text: string) =
    let tokens = text |> tokenize tokenizeHost
    let errorTokens, tokens = tokens |> List.partition isErrorToken
    let ast, parseErrors = tokens |> parse

    let errors =
      List.append (tokenizeErrors errorTokens) parseErrors

    let ast =
      if errors |> List.isEmpty then
        resolveMiloneCoreDeps tokens ast
      else
        ast

    ast, errors

  let fetchModule (projectName: string) (projectDir: string) (moduleName: string) =
    match readModuleFile projectName projectDir moduleName with
    | None -> None
    | Some (docId, text) ->
        let ast, errors = doParse text
        Some(docId, ast, errors)

  { ProjectDir = projectDir
    ProjectName = projectName
    Projects = projects
    TokenizeHost = tokenizeHost
    FetchModule = fetchModule
    HeaderOnly = false
    Verbosity = verbosity
    Host = host }

let private compileCtxAddProjectReferences references (ctx: CompileCtx) =
  let projects =
    references
    |> List.fold
         (fun projects projectDir ->
           let projectDir = projectDir |> pathStrTrimEndPathSep
           let projectName = projectDir |> pathStrToStem

           if projects |> TMap.containsKey projectName then
             failwithf "Project name is duplicated: '%s'" projectName

           projects |> TMap.add projectName projectDir)
         ctx.Projects

  { ctx with Projects = projects }

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

let private syntaxHasError (syntax: SyntaxAnalysisResult) =
  let _, _, errors = syntax
  errors |> List.isEmpty |> not

let private syntaxErrorToString syntax =
  let _, _, errors = syntax

  errors
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map (fun (msg, loc) -> "#error " + locToString loc + " " + msg + "\n")
  |> strConcat

let private tyCtxHasError (tyCtx: TyCtx) = tyCtx.Logs |> List.isEmpty |> not

let private nameResLogsToString logs =
  logs
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map
       (fun (log, loc) ->
         "#error "
         + locToString loc
         + " "
         + nameResLogToString log
         + "\n")
  |> strConcat

let private semanticErrorToString (tyCtx: TyCtx) logs =
  let tyDisplayFn ty =
    let getTyName tySerial =
      tyCtx.Tys
      |> TMap.tryFind tySerial
      |> Option.map tyDefToName

    tyDisplay getTyName ty

  logs
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map
       (fun (log, loc) ->
         "#error "
         + locToString loc
         + " "
         + logToString tyDisplayFn log
         + "\n")
  |> strConcat

// -----------------------------------------------
// Processes
// -----------------------------------------------

type private SyntaxAnalysisResult = HProgram * NameCtx * (string * Loc) list

let private isErrorToken token =
  match token with
  | ErrorToken _, _ -> true
  | _ -> false

let private tokenizeErrors errorTokens =
  errorTokens
  |> List.map
       (fun token ->
         match token with
         | ErrorToken error, pos -> tokenizeErrorToString error, pos
         | _ -> unreachable ())

/// Loads source codes from files, performs tokenization and SyntaxParse,
/// and transforms them into high-level intermediate representation (HIR).
let syntacticallyAnalyze (ctx: CompileCtx) : SyntaxAnalysisResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  writeLog host v ("AstBundle project=" + ctx.ProjectName)

  let fetchModule (projectName: ProjectName) (moduleName: ModuleName) : ModuleSyntaxData option =
    let projectDir =
      match ctx.Projects |> TMap.tryFind projectName with
      | Some it -> it
      | None -> ctx.ProjectDir + "/../" + projectName

    ctx.FetchModule projectName projectDir moduleName

  bundleCompatible fetchModule ctx.ProjectName

[<NoEquality; NoComparison>]
type SemaAnalysisResult =
  | SemaAnalysisOk of HProgram * TyCtx
  | SemaAnalysisNameResError of (NameResLog * Loc) list
  | SemaAnalysisTypingError of TyCtx

/// Analyzes HIR to validate program and collect information.
let semanticallyAnalyze (host: CliHost) v (syntax: SyntaxAnalysisResult) : SemaAnalysisResult =
  let modules, nameCtx, syntaxErrors = syntax
  assert (syntaxErrors |> List.isEmpty)

  writeLog host v "NameRes"

  let modules, scopeCtx = nameRes (modules, nameCtx)

  if scopeCtx.Logs |> List.isEmpty |> not then
    SemaAnalysisNameResError scopeCtx.Logs
  else
    writeLog host v "Typing"

    let modules, tyCtx = infer (modules, scopeCtx, [])

    if tyCtx.Logs |> List.isEmpty |> not then
      SemaAnalysisTypingError tyCtx
    else
      writeLog host v "ArityCheck"
      let tyCtx = arityCheck (modules, tyCtx)

      if tyCtx.Logs |> List.isEmpty |> not then
        SemaAnalysisTypingError tyCtx
      else
        SemaAnalysisOk(modules, tyCtx)

/// Transforms HIR. The result can be converted to MIR.
let transformHir (host: CliHost) v (modules: HProgram, tyCtx) =
  let expr =
    let decls =
      (modules
       |> List.collect (fun (_, _, decls) -> decls))

    hxSemi decls noLoc

  writeLog host v "MainHoist"
  let expr, tyCtx = hoistMain (expr, tyCtx)

  writeLog host v "AutoBoxing"
  let expr, tyCtx = autoBox (expr, tyCtx)

  writeLog host v "RecordRes"
  let expr, tyCtx = recordRes (expr, tyCtx)

  writeLog host v "ClosureConversion"
  let expr, tyCtx = closureConversion (expr, tyCtx)

  writeLog host v "EtaExpansion"
  let expr, tyCtx = etaExpansion (expr, tyCtx)

  writeLog host v "Hoist"
  let decls, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let decls, tyCtx = tailRecOptimize (decls, tyCtx)

  writeLog host v "Monomorphizing"
  monify (decls, tyCtx)

/// (module name, C code) list
type CodeGenResult = (string * string) list

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir (host: CliHost) v projectName headerOnly (decls, tyCtx) : CodeGenResult =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (decls, tyCtx)

  writeLog host v "CirGen"
  let cir = genCir (stmts, mirCtx)

  writeLog host v "CirDump"

  let output =
    if headerOnly then
      cirDumpHeader cir
    else
      cirDump cir

  writeLog host v "Finish"
  [ projectName + ".c", output ]

let check (ctx: CompileCtx) : bool * string =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx

  if syntax |> syntaxHasError then
    false, syntaxErrorToString syntax
  else
    match semanticallyAnalyze host v syntax with
    | SemaAnalysisNameResError logs -> false, nameResLogsToString logs
    | SemaAnalysisTypingError tyCtx -> false, semanticErrorToString tyCtx tyCtx.Logs
    | SemaAnalysisOk _ -> true, ""

[<NoEquality; NoComparison>]
type CompileResult =
  | CompileOk of CodeGenResult
  | CompileError of string

let private compile (ctx: CompileCtx) : CompileResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx

  if syntax |> syntaxHasError then
    CompileError(syntaxErrorToString syntax)
  else
    match semanticallyAnalyze host v syntax with
    | SemaAnalysisNameResError logs -> CompileError(nameResLogsToString logs)
    | SemaAnalysisTypingError tyCtx -> CompileError(semanticErrorToString tyCtx tyCtx.Logs)

    | SemaAnalysisOk (modules, tyCtx) ->
        let decls, tyCtx = transformHir host v (modules, tyCtx)
        CompileOk(codeGenHirViaMir host v ctx.ProjectName ctx.HeaderOnly (decls, tyCtx))

// -----------------------------------------------
// Actions
// -----------------------------------------------

let cliParse (host: CliHost) v (projectDir: string) = todo ()
// let ctx = compileCtxNew host v projectDir

// let parseWithLogging moduleName contents =
//   writeLog
//     host
//     v
//     ("\n-------------\nSyntaxParse %s...\n--------------"
//      + moduleName)

//   let ast, errors =
//     contents |> tokenize ctx.TokenizeHost |> parse

//   if errors |> List.isEmpty |> not then
//     printfn "In %s" moduleName

//     errors
//     |> List.iter (fun (msg, pos) -> printfn "ERROR: %s %s" (posToString pos) msg)

//   match v with
//   | Verbose -> printfn "%s" (objToString ast)
//   | _ -> ()

//   ast, errors

// bundleProgram (ctx |> toBundleHost parseWithLogging) ctx.ProjectName
// |> ignore

// 0

let cliCheck (host: CliHost) verbosity projectDir =
  let ctx = compileCtxNew host verbosity projectDir

  let ok, output = check ctx
  let exitCode = if ok then 0 else 1

  printfn "%s" (output |> S.replace "#error " "" |> S.trimEnd)
  exitCode

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileOptions =
  { ProjectDir: string
    TargetDir: string
    HeaderOnly: bool
    Verbosity: Verbosity }

let cliCompile (host: CliHost) (options: CompileOptions) =
  let ctx =
    compileCtxNew host options.Verbosity options.ProjectDir

  let ctx =
    { ctx with
        HeaderOnly = options.HeaderOnly }

  let result = compile ctx

  match result with
  | CompileOk files ->
      List.fold (fun () (name, contents) -> host.FileWriteAllText(options.TargetDir + "/" + name) contents) () files
      0

  | CompileError output ->
      host.WriteStdout output
      1

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

/// Parses CLI args for an option with value.
let private parseOption isFlag args =
  // acc: args not consumed in reversed order
  let rec go acc args =
    match args with
    | []
    | [ _ ] -> None, List.append (List.rev acc) args

    | flag :: value :: args when isFlag flag -> Some value, List.append (List.rev acc) args

    | arg :: args -> go (arg :: acc) args

  go [] args

let private containsHelpFlag args =
  let ok, _ =
    parseFlag
      (fun _ arg ->
        match arg with
        | "-h"
        | "--help" -> Some true
        | _ -> None)
      false
      args

  ok

let private parseVerbosity (host: CliHost) args =
  parseFlag
    (fun (_: Verbosity) arg ->
      match arg with
      | "-v"
      | "--verbose" -> Some Verbose
      | "-q"
      | "--quiet" -> Some Quiet
      | "--profile" -> Some(Profile(host.ProfileInit()))
      | _ -> None)
    Quiet
    args

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CheckCmd
  | CompileCmd
  | HeaderCmd
  | ParseCmd
  | BadCmd of string

let private parseArgs args =
  let args = args |> List.skip 1

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
      | "check" -> CheckCmd, args

      | "build"
      | "compile" -> CompileCmd, args

      | "header" -> HeaderCmd, args

      // for debug
      | "parse" -> ParseCmd, args

      | _ -> BadCmd arg, []

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

let cli (host: CliHost) =
  match host.Args |> parseArgs with
  | HelpCmd, _ ->
      printfn "%s" (helpText ())
      0

  | VersionCmd, _ ->
      printfn "%s" (currentVersion ())
      0

  | CheckCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | [ projectDir ] -> cliCheck host verbosity projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

      | arg :: _ ->
          printfn "ERROR: Unknown argument: '%s'." arg
          1

  | HeaderCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ ->
          let options : CompileOptions =
            { ProjectDir = projectDir
              TargetDir = "."
              HeaderOnly = true
              Verbosity = verbosity }

          cliCompile host options

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | CompileCmd, args ->
      let verbosity, args = parseVerbosity host args

      let targetDir, args =
        parseOption (fun x -> x = "--target-dir") args

      match args with
      | projectDir :: _ ->
          let options : CompileOptions =
            { ProjectDir = projectDir
              TargetDir = Option.defaultValue "." targetDir
              HeaderOnly = false
              Verbosity = verbosity }

          cliCompile host options

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | ParseCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ -> cliParse host verbosity projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | BadCmd subcommand, _ ->
      printfn "ERROR: Unknown subcommand '%s'." subcommand
      1
