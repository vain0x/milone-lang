/// Front end of the compiler.
module rec MiloneCli.Cli

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneStd.StdPath
open MiloneSyntax.Syntax
open MiloneTranslation.AutoBoxing
open MiloneTranslation.CirDump
open MiloneTranslation.CirGen
open MiloneTranslation.ClosureConversion
open MiloneTranslation.EtaExpansion
open MiloneTranslation.Hoist
open MiloneTranslation.MirGen
open MiloneTranslation.Monomorphizing
open MiloneTranslation.MonoTy
open MiloneTranslation.RecordRes
open MiloneTranslation.TailRecOptimizing

module C = MiloneStd.StdChar
module Hir = MiloneTranslation.Hir
module S = MiloneStd.StdString
module Tir = MiloneSyntax.Tir
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module Typing = MiloneSyntax.Typing
module SyntaxApi = MiloneSyntax.SyntaxApi
module Lower = MiloneCli.Lower
module PU = MiloneCli.PlatformUnix
module PW = MiloneCli.PlatformWindows

let private currentVersion () = "0.3.0"

let private helpText () =
  """milone-lang v"""
  + currentVersion ()
  + """ <https://github.com/vain0x/milone-lang>

USAGE:
    milone <SUBCOMMAND> OPTIONS...

EXAMPLE
    milone compile src/MiloneCli

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

EXPERIMENTAL features
    milone build <PROJECT-DIR>
        Builds a milone-lang project to C & build.ninja
        so that you can make an executable with ninja easily.

        --target-dir <DIR>  Output directory.
                            (Defaults to target/<PROJECT-NAME>)

    milone run <PROJECT-DIR> [-- ARGS...]
        Runs a milone-lang project.
        (Requirements: gcc and ninja.)

        --target-dir <DIR>  Output/build directory.
                            (Defaults to target/<PROJECT-NAME>)

OPTIONS
    -h, --help      Print help text.
    -V, --version   Print compiler version.

GLOBAL OPTIONS
    -v, --verbose   Enable verbose logging for debug
        --profile   Enable profile logging
    -q, --quiet     Disable logging
        --parallel  Enable parallel compilation (experimental)"""

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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Platform =
  | Unix
  | Windows

/// Abstraction layer of CLI program.
[<NoEquality; NoComparison>]
type CliHost =
  {
    /// Command line args.
    Args: string list

    WorkDir: string

    /// Path to $HOME.
    Home: string

    /// Path to milone home (installation directory).
    MiloneHome: string

    Platform: Platform

    /// Creates a profiler.
    ProfileInit: unit -> Profiler

    /// Prints a message to stderr for profiling.
    ProfileLog: string -> Profiler -> unit

    NewGuid: unit -> string

    /// Ensures directory exist.
    ///
    /// baseDir -> dir -> exist
    DirCreate: string -> string -> bool

    FileExists: string -> bool

    /// Reads all contents of a file as string.
    FileReadAllText: string -> Future<string option>

    /// Writes to text file.
    FileWriteAllText: string -> string -> unit

    /// Writes to standard output.
    WriteStdout: string -> unit

    /// Runs a subprocess and waits for exit. Returns exit code.
    ///
    /// (Pipes are inherited.)
    RunCommand: string -> string list -> int

    /// Turns this process into a shell that runs specified command.
    ExecuteInto: string -> unit }

// -----------------------------------------------
// Helpers
// -----------------------------------------------

let private pathStrTrimEndPathSep (s: string) : string =
  s
  |> Path.ofString
  |> Path.trimEndSep
  |> Path.toString

let private pathStrToStem (s: string) : string =
  s
  |> Path.ofString
  |> Path.fileStem
  |> Path.toString

let private pathStrToFileName (s: string) : string =
  s
  |> Path.ofString
  |> Path.basename
  |> Path.toString

let private hostToMiloneHome (host: CliHost) =
  let getEnv name =
    match name with
    | "MILONE_HOME" when host.MiloneHome <> "" -> Some host.MiloneHome
    | "HOME" when host.Home <> "" -> Some host.Home
    | _ -> None

  SyntaxApi.getMiloneHomeFromEnv getEnv

let private dirCreateOrFail (host: CliHost) (dirPath: Path) : unit =
  let ok =
    host.DirCreate host.WorkDir (Path.toString dirPath)

  if not ok then
    printfn "error: couldn't create directory at %s" (Path.toString dirPath)
    exit 1

let private fileWrite (host: CliHost) (filePath: Path) (contents: string) : unit =
  host.FileWriteAllText(Path.toString filePath) contents

let private runCommand (host: CliHost) (command: Path) (args: string list) : unit =
  let code =
    host.RunCommand(Path.toString command) args

  if code <> 0 then
    printfn "error: subprocess '%s' exited in code %d" (Path.toString command) code
    exit code

// -----------------------------------------------
// Context
// -----------------------------------------------

type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileCtx =
  { EntryProjectDir: string
    EntryProjectName: string

    SyntaxCtx: SyntaxApi.SyntaxCtx

    Verbosity: Verbosity
    Host: CliHost }

let compileCtxNew (host: CliHost) verbosity projectDir : CompileCtx =
  let miloneHome = hostToMiloneHome host
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let syntaxCtx: SyntaxApi.SyntaxCtx =
    let host: SyntaxApi.SyntaxHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = host.FileReadAllText
        WriteLog = writeLog host verbosity }

    SyntaxApi.syntaxCtxNew host

  { EntryProjectDir = projectDir
    EntryProjectName = projectName
    SyntaxCtx = syntaxCtx
    Verbosity = verbosity
    Host = host }

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

// -----------------------------------------------
// Processes
// -----------------------------------------------

/// Transforms HIR. The result can be converted to MIR.
let transformHir (host: CliHost) v (modules: Tir.TProgram, tyCtx: Typing.TyCtx) =
  writeLog host v "Lower"
  let modules, tyCtx = Lower.lower (modules, tyCtx)

  let expr =
    let decls =
      (modules
       |> List.collect (fun (_, _, decls) -> decls))

    Hir.hxSemi decls noLoc

  writeLog host v "RecordRes"
  let expr, tyCtx = recordRes (expr, tyCtx)

  writeLog host v "ClosureConversion"
  let expr, tyCtx = closureConversion (expr, tyCtx)

  writeLog host v "EtaExpansion"
  let expr, tyCtx = etaExpansion (expr, tyCtx)

  writeLog host v "ComputeTyArgs"
  let expr, tyCtx = computeFunTyArgs (expr, tyCtx)

  writeLog host v "AutoBoxing"
  let expr, tyCtx = autoBox (expr, tyCtx)

  writeLog host v "Hoist"
  let decls, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let decls, tyCtx = tailRecOptimize (decls, tyCtx)

  writeLog host v "Monomorphizing"
  let decls, tyCtx = monify (decls, tyCtx)

  writeLog host v "MonoTy"
  let decls, tyCtx = monoTy (decls, tyCtx)

  decls, tyCtx

/// (file name, C code) list
type CodeGenResult = (string * string) list

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir (host: CliHost) v projectName (decls, tyCtx) : CodeGenResult =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (decls, tyCtx)

  writeLog host v "CirGen"
  let modules = genCir (stmts, mirCtx)

  writeLog host v "CirDump"

  let output =
    modules
    |> List.map
         (fun (docId, cir) ->
           let fileName =
             if docId = projectName + ".Program"
                || docId = projectName + ".EntryPoint"
                || docId = projectName + "." + projectName then
               projectName + ".c"
             else
               S.replace "." "_" docId + ".c"

           fileName, cirDump cir)

  writeLog host v "Finish"
  output

let check (ctx: CompileCtx) : bool * string =
  match SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx with
  | SyntaxApi.SyntaxAnalysisOk _ -> true, ""
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> false, SyntaxApi.syntaxErrorsToString errors

[<NoEquality; NoComparison>]
type CompileResult =
  | CompileOk of CodeGenResult
  | CompileError of string

let private compile (ctx: CompileCtx) : CompileResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  match SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx with
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> CompileError(SyntaxApi.syntaxErrorsToString errors)

  | SyntaxApi.SyntaxAnalysisOk (modules, tyCtx) ->
    let decls, tyCtx = transformHir host v (modules, tyCtx)

    CompileOk(codeGenHirViaMir host v ctx.EntryProjectName (decls, tyCtx))

// -----------------------------------------------
// Others
// -----------------------------------------------

let private writeCFiles (host: CliHost) (targetDir: string) (cFiles: (string * string) list) : unit =
  dirCreateOrFail host (Path targetDir)
  List.fold (fun () (name, contents) -> host.FileWriteAllText(targetDir + "/" + name) contents) () cFiles

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
    Verbosity: Verbosity }

let cliCompile (host: CliHost) (options: CompileOptions) =
  let ctx =
    compileCtxNew host options.Verbosity options.ProjectDir

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    let targetDir = options.TargetDir

    dirCreateOrFail host (Path targetDir)
    writeCFiles host targetDir cFiles

    cFiles
    |> List.map (fun (name, _) -> options.TargetDir + "/" + name + "\n")
    |> S.concat ""
    |> host.WriteStdout

    0

type BuildOptions =
  { ProjectDir: string
    TargetDir: string
    Verbosity: Verbosity }

let private cliBuild (host: CliHost) (options: BuildOptions) =
  match host.Platform with
  | Platform.Unix ->
    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      let targetDir = options.TargetDir
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let exeFile =
        Path(targetDir + "/" + ctx.EntryProjectName + ".exe")

      let p: PU.BuildOnUnixParams =
        { TargetDir = Path options.TargetDir
          ExeFile = exeFile
          CFiles = List.map (fun (name, _) -> Path name) cFiles
          MiloneHome = miloneHome
          DirCreate = dirCreateOrFail host
          FileWrite = fileWrite host
          ExecuteInto = host.ExecuteInto }

      PU.buildOnUnix p
      unreachable ()

  | Platform.Windows ->
    let miloneHome = hostToMiloneHome host

    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      writeCFiles host options.TargetDir cFiles

      let p: PW.BuildOnWindowsParams =
        { ProjectName = ctx.EntryProjectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)
          OutputName = ctx.EntryProjectName
          MiloneHome = Path miloneHome
          TargetDir = Path options.TargetDir

          NewGuid = fun () -> PW.Guid(host.NewGuid())
          DirCreate = dirCreateOrFail host
          FileExists = fun filePath -> host.FileExists(Path.toString filePath)
          FileWrite = fileWrite host
          RunCommand = runCommand host }

      PW.buildOnWindows p
      0

let private cliRun (host: CliHost) (options: BuildOptions) (restArgs: string list) =
  match host.Platform with
  | Platform.Unix ->
    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      let targetDir = options.TargetDir
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let exeFile =
        Path(targetDir + "/" + ctx.EntryProjectName + ".exe")

      let p: PU.RunOnUnixParams =
        { TargetDir = Path options.TargetDir
          ExeFile = exeFile
          CFiles = List.map (fun (name, _) -> Path name) cFiles
          MiloneHome = miloneHome
          Args = restArgs
          DirCreate = dirCreateOrFail host
          FileWrite = fileWrite host
          ExecuteInto = host.ExecuteInto }

      PU.runOnUnix p
      unreachable ()

  | Platform.Windows ->
    let miloneHome = hostToMiloneHome host

    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      writeCFiles host options.TargetDir cFiles

      let p: PW.RunOnWindowsParams =
        { ProjectName = ctx.EntryProjectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)

          OutputName = ctx.EntryProjectName
          MiloneHome = Path miloneHome
          TargetDir = Path options.TargetDir

          NewGuid = fun () -> PW.Guid(host.NewGuid())
          DirCreate = dirCreateOrFail host
          FileExists = fun filePath -> host.FileExists(Path.toString filePath)
          FileWrite = fileWrite host
          RunCommand = runCommand host

          Args = restArgs }

      PW.runOnWindows p
      0

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

let private parseParallel args =
  parseFlag
    (fun (_: bool) arg ->
      match arg with
      | "--parallel" -> Some true
      | _ -> None)
    false
    args

let private eatParallelFlag args =
  let ok, args = parseParallel args
  if ok then __allowParallel () // FIXME: avoid global state
  args

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

let private defaultTargetDir projectDir =
  let projectName =
    projectDir
    |> pathStrTrimEndPathSep
    |> pathStrToFileName

  "target/" + projectName

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CheckCmd
  | CompileCmd
  | BuildCmd
  | ParseCmd
  | RunCmd
  | BadCmd of string

let private parseArgs args =
  let args = args |> listSkip 1

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
    | "build" -> BuildCmd, args
    | "check" -> CheckCmd, args
    | "compile" -> CompileCmd, args
    | "run" -> RunCmd, args

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

  | CompileCmd, args ->
    let args = eatParallelFlag args
    let verbosity, args = parseVerbosity host args

    let targetDir, args =
      parseOption (fun x -> x = "--target-dir") args

    match args with
    | projectDir :: _ ->
      let options: CompileOptions =
        { ProjectDir = projectDir
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
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

  | BuildCmd, args ->
    let args = eatParallelFlag args
    let verbosity, args = parseVerbosity host args

    let targetDir, args =
      parseOption (fun x -> x = "--target-dir") args

    match args with
    | projectDir :: _ ->
      let options: BuildOptions =
        { ProjectDir = projectDir
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
          Verbosity = verbosity }

      cliBuild host options

    | [] ->
      printfn "ERROR: Expected project dir."
      1

  | RunCmd, args ->
    let args = eatParallelFlag args
    let verbosity, args = parseVerbosity host args

    let targetDir, args =
      parseOption (fun x -> x = "--target-dir") args

    let restArgs =
      args
      |> List.skipWhile (fun x -> x <> "--")
      |> listSkip 1

    match args with
    | projectDir :: _ ->
      let options: BuildOptions =
        { ProjectDir = projectDir
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
          Verbosity = verbosity }

      cliRun host options restArgs

    | [] ->
      printfn "ERROR: Expected project dir."
      1

  | BadCmd subcommand, _ ->
    printfn "ERROR: Unknown subcommand '%s'." subcommand
    1
