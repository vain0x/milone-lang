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
module S = MiloneStd.StdString

let private currentVersion () = "0.2.0"

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
    FileReadAllText: string -> string option }

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
// Project schema interpreter
// -----------------------------------------------

// type ProjectSchema =
//   { Name: string
//     Version: string
//     Options: ProjectOption list }

// type ProjectOption =
//   | Ref of projectDir: string
//   | AliasedRef of projectName: string * projectDir: string

let private doInterpretProjectSchema ast =
  let asStr expr =
    match expr with
    | ALitExpr (StrLit value, _) -> value
    | _ -> failwith "Expected a string literal."

  let asProjectRef expr =
    match expr with
    | ABinaryExpr (AppBinary, AIdentExpr (Name("Ref", _)), projectDir, _) ->
        let projectDir =
          projectDir |> asStr |> pathStrTrimEndPathSep

        let projectName = projectDir |> pathStrToStem
        Some(projectName, projectDir)

    | ABinaryExpr (AppBinary, AIdentExpr (Name("AliasedRef", _)), ATupleExpr ([ projectName; projectDir ], _), _) ->
        let projectName = projectName |> asStr

        let projectDir =
          projectDir |> asStr |> pathStrTrimEndPathSep

        Some(projectName, projectDir)

    | _ -> None

  let asProjectSchema decl =
    match decl with
    | AExprDecl (ARecordExpr (None, fields, _)) ->
        match fields
              |> List.tryFind (fun (Name(name, _), _, _) -> name = "Options") with
        | Some (_, AListExpr (items, _), _) -> items |> List.choose asProjectRef |> Some
        | _ -> None

    | _ -> None

  let decls =
    match ast with
    | AExprRoot decls -> decls
    | AModuleRoot (_, decls, _) -> decls

  decls |> List.tryPick asProjectSchema

let private parseProjectSchema tokenizeHost contents =
  let ast, errors =
    contents |> tokenize tokenizeHost |> parse

  if errors |> List.isEmpty |> not then
    errors
    |> listSort (fun (_, l) (_, r) -> posCompare l r)
    |> List.iter (fun (msg, loc) -> printfn "ERROR %s %s" (posToString loc) msg)

    failwith "Syntax error in project file."

  doInterpretProjectSchema ast

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
      if (acc |> mapContainsKey moduleName |> not)
         && isKnownName moduleName then
        acc |> mapAdd moduleName pos
      else
        acc

    moduleNames |> List.fold add (mapEmpty compare)

  let insertOpenDecls decls =
    moduleMap
    |> mapFold
         (fun decls moduleName pos ->
           AModuleSynonymDecl(Name(moduleName, pos), [ Name("MiloneCore", pos); Name(moduleName, pos) ], pos)
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

let compileCtxNew (host: CliHost) verbosity projectDir: CompileCtx =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let miloneHome =
    if host.MiloneHome <> "" then
      host.MiloneHome
    else
      host.Home + "/.milone"

  let projects =
    mapEmpty compare
    |> mapAdd "MiloneCore" (miloneHome + "/milone_libs/MiloneCore")
    |> mapAdd "MiloneStd" (miloneHome + "/milone_libs/MiloneStd")
    |> mapAdd projectName projectDir

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

let private compileCtxReadProjectFile (ctx: CompileCtx) =
  let host = ctx.Host

  let projectFilePath =
    ctx.ProjectDir
    + "/"
    + ctx.ProjectName
    + ".milone_project"

  match host.FileReadAllText projectFilePath with
  | Some contents ->
      match parseProjectSchema ctx.TokenizeHost contents with
      | Some refs ->
          let projects =
            refs
            |> List.fold
                 (fun projects (projectName, projectDir) ->
                   if projects |> mapContainsKey projectName then
                     failwithf "Project name is duplicated: '%s'" projectName

                   let projectDir =
                     if projectDir |> pathIsRelative then
                       ctx.ProjectDir + "/" + projectDir
                     else
                       projectDir

                   projects |> mapAdd projectName projectDir)
                 ctx.Projects

          { ctx with Projects = projects }

      | None -> failwith "Project is incomplete: couldn't find project schema."
  | None -> ctx

let private compileCtxAddProjectReferences references (ctx: CompileCtx) =
  let projects =
    references
    |> List.fold
         (fun projects projectDir ->
           let projectDir = projectDir |> pathStrTrimEndPathSep
           let projectName = projectDir |> pathStrToStem

           if projects |> mapContainsKey projectName then
             failwithf "Project name is duplicated: '%s'" projectName

           projects |> mapAdd projectName projectDir)
         ctx.Projects

  { ctx with Projects = projects }

let private toBundleHost parse (ctx: CompileCtx): BundleHost =
  let host = ctx.Host
  let readFile = host.FileReadAllText

  let parseModule (docId: DocId) (text: string) =
    let ast, errors = parse docId text
    Some(docId, ast, errors)

  { ProjectRefs = ctx.Projects |> mapToKeys

    FetchModule =
      fun projectName moduleName ->
        match ctx.Projects |> mapTryFind projectName with
        | None -> None
        | Some projectDir -> ctx.FetchModule projectName projectDir moduleName }

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
      |> mapTryFind tySerial
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
         | _ -> failwith "NEVER")

/// Loads source codes from files, performs tokenization and SyntaxParse,
/// and transforms them into high-level intermediate representation (HIR).
let syntacticallyAnalyze (ctx: CompileCtx) =
  let host = ctx.Host
  let v = ctx.Verbosity

  writeLog host v ("Bundling project=" + ctx.ProjectName)

  let doParse (_: DocId) (s: string) =
    let tokens = s |> tokenize ctx.TokenizeHost
    let errorTokens, tokens = tokens |> List.partition isErrorToken
    let ast, parseErrors = tokens |> parse

    let errors =
      List.append (tokenizeErrors errorTokens) parseErrors

    ast, errors

  match bundleProgram (ctx |> toBundleHost doParse) ctx.ProjectName with
  | Some syntax -> syntax
  | None -> failwithf "Entry module file not found: %s" ctx.ProjectName

[<NoEquality; NoComparison>]
type SemaAnalysisResult =
  | SemaAnalysisOk of HExpr * TyCtx
  | SemaAnalysisNameResError of (NameResLog * Loc) list
  | SemaAnalysisTypingError of TyCtx

/// Analyzes HIR to validate program and collect information.
let semanticallyAnalyze (host: CliHost) v (exprs, nameCtx, syntaxErrors): SemaAnalysisResult =
  assert (syntaxErrors |> List.isEmpty)

  writeLog host v "NameRes"

  let expr, scopeCtx = nameRes (exprs, nameCtx)

  if scopeCtx.Logs |> List.isEmpty |> not then
    SemaAnalysisNameResError scopeCtx.Logs
  else
    writeLog host v "Typing"

    let expr, tyCtx = infer (expr, scopeCtx, [])

    if tyCtx.Logs |> List.isEmpty |> not then
      SemaAnalysisTypingError tyCtx
    else
      writeLog host v "ArityCheck"
      let tyCtx = arityCheck (expr, tyCtx)

      if tyCtx.Logs |> List.isEmpty |> not then
        SemaAnalysisTypingError tyCtx
      else
        SemaAnalysisOk(expr, tyCtx)

/// Transforms HIR. The result can be converted to MIR.
let transformHir (host: CliHost) v (expr, tyCtx) =
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
  let expr, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let expr, tyCtx = tailRecOptimize (expr, tyCtx)

  writeLog host v "Monomorphizing"
  monify (expr, tyCtx)

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir (host: CliHost) v headerOnly (expr, tyCtx) =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (expr, tyCtx)

  if mirCtx.Logs |> List.isEmpty |> not then
    false, mirCtx.Logs |> semanticErrorToString tyCtx
  else
    writeLog host v "CirGen"
    let ok, cir = genCir (stmts, mirCtx)

    writeLog host v "CirDump"
    let output = if headerOnly then cirDumpHeader cir else cirDump cir

    writeLog host v "Finish"
    ok, output

let check (ctx: CompileCtx): bool * string =
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

let compile (ctx: CompileCtx): bool * string =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx

  if syntax |> syntaxHasError then
    false, syntaxErrorToString syntax
  else
    match semanticallyAnalyze host v syntax with
    | SemaAnalysisNameResError logs -> false, nameResLogsToString logs
    | SemaAnalysisTypingError tyCtx -> false, semanticErrorToString tyCtx tyCtx.Logs

    | SemaAnalysisOk (expr, tyCtx) ->
        let expr, tyCtx = transformHir host v (expr, tyCtx)
        codeGenHirViaMir host v ctx.HeaderOnly (expr, tyCtx)

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

    let ast, errors =
      contents |> tokenize ctx.TokenizeHost |> parse

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

let cliCheck (host: CliHost) verbosity projectDir =
  let ctx =
    compileCtxNew host verbosity projectDir
    |> compileCtxReadProjectFile

  let ok, output = check ctx
  let exitCode = if ok then 0 else 1

  printfn "%s" (output |> S.replace "#error " "" |> S.trimEnd)
  exitCode

let cliCompile (host: CliHost) verbosity headerOnly projectDir =
  let ctx =
    compileCtxNew host verbosity projectDir
    |> compileCtxReadProjectFile

  let ctx = { ctx with HeaderOnly = headerOnly }

  let ok, output = compile ctx
  let exitCode = if ok then 0 else 1

  printfn "%s" (output |> S.trimEnd)
  exitCode

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
      | projectDir :: _ -> cliCompile host verbosity true projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | CompileCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ -> cliCompile host verbosity false projectDir

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
