/// Front end of the compiler.
module rec MiloneCli.Cli

open MiloneShared.Util
open MiloneShared.UtilParallel
open MiloneShared.UtilProfiler
open MiloneStd.StdError
open MiloneStd.StdPath
open MiloneSyntax.Syntax

module C = MiloneStd.StdChar
module S = MiloneStd.StdString
module Tir = MiloneSyntax.Tir
module Typing = MiloneSyntax.Typing
module SyntaxApi = MiloneSyntax.SyntaxApi
module Hir = MiloneTranslation.Hir
module TranslationApi = MiloneTranslation.TranslationApi
module Lower = MiloneCli.Lower
module PU = MiloneCli.PlatformUnix
module PW = MiloneCli.PlatformWindows

let private currentVersion () = "0.4.0"

let private helpText () =
  let s =
    """milone v${VERSION} <https://github.com/vain0x/milone-lang>

EXAMPLE

    # Run a project
    milone run path/to/MiloneProject

    # Build a project
    milone build path/to/MiloneProject

SUBCOMMANDS
    run       Run a project
    build     Build a project for executable
    check     Analyze a project
    compile   Compile a project to C
    eval      Compute an expression

See <https://github.com/vain0x/milone-lang/blob/v${VERSION}/docs/cli.md> for details."""

  s |> S.replace "${VERSION}" (currentVersion ())

// -----------------------------------------------
// Interface (1)
// -----------------------------------------------

[<NoEquality; NoComparison>]
type Verbosity =
  | Verbose
  | Profile of Profiler
  | Quiet

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type UnixApi =
  { /// Turns this process into a shell that runs specified command.
    ExecuteInto: string -> Never }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type WindowsApi =
  { NewGuid: unit -> string

    /// Runs a subprocess and waits for exit. Returns exit code.
    ///
    /// (Pipes are inherited.)
    RunCommand: string -> string list -> int }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Platform =
  | Unix of UnixApi
  | Windows of WindowsApi

/// Abstraction layer of CLI program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CliHost =
  {
    /// Command line args.
    Args: string list

    WorkDir: string

    /// Path to $HOME.
    Home: string

    /// Path to milone home (installation directory).
    MiloneHome: string option

    Platform: Platform

    /// Creates a profiler.
    ProfileInit: unit -> Profiler

    /// Prints a message to stderr for profiling.
    ProfileLog: string -> Profiler -> unit

    /// Ensures directory exist.
    ///
    /// baseDir -> dir -> exist
    DirCreate: string -> string -> bool

    FileExists: string -> bool

    /// Reads all contents of a file as string.
    FileReadAllText: string -> Future<string option>

    /// Writes to text file.
    FileWriteAllText: string -> string -> unit

    /// Reads from standard input.
    ReadStdinAll: unit -> string

    /// Writes to standard output.
    WriteStdout: string -> unit }

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

// #pathJoin
let private pathJoin (l: string) (r: string) =
  let slash (s: string) = s |> S.replace "\\" "/"

  let isRooted (s: string) =
    s |> S.startsWith "/"
    || s.Length >= 3 && s.[1] = ':' && s.[2] = '/'

  let l = slash l
  let r = slash r
  if isRooted r then r else l + "/" + r

let private hostToMiloneHome (host: CliHost) =
  SyntaxApi.getMiloneHomeFromEnv (fun () -> host.MiloneHome) (fun () -> Some host.Home)

let private dirCreateOrFail (host: CliHost) (dirPath: Path) : unit =
  let ok =
    host.DirCreate host.WorkDir (Path.toString dirPath)

  if not ok then
    printfn "error: couldn't create directory at %s" (Path.toString dirPath)
    exit 1

let private fileRead (host: CliHost) (filePath: Path) =
  host.FileReadAllText(Path.toString filePath)
  |> Future.wait // #avoidBlocking

let private fileWrite (host: CliHost) (filePath: Path) (contents: string) : unit =
  host.FileWriteAllText(Path.toString filePath) contents

let private runCommand (w: WindowsApi) (command: Path) (args: string list) : unit =
  let code = w.RunCommand(Path.toString command) args

  if code <> 0 then
    printfn "error: subprocess '%s' exited in code %d" (Path.toString command) code
    exit code

let private writeLog (host: CliHost) verbosity msg : unit =
  match verbosity with
  | Verbose -> __trace ("// " + msg)

  | Profile profiler ->
    let profileLog = host.ProfileLog
    profiler |> profileLog msg

  | Quiet -> ()

let private computeExePath targetDir platform isRelease name : Path =
  let triple =
    match platform with
    | Platform.Unix _ -> "x86_64-unknown-linux-gnu"
    | Platform.Windows _ -> "x86_64-pc-windows-msvc"

  let mode = if isRelease then "release" else "debug"

  let quad = triple + "-" + mode

  let ext =
    match platform with
    | Platform.Unix _ -> ""
    | Platform.Windows _ -> ".exe"

  Path(
    Path.toString targetDir
    + "/"
    + quad
    + "/"
    + name
    + ext
  )

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CompileCtx =
  { EntryProjectName: ProjectName
    SyntaxCtx: SyntaxApi.SyntaxCtx
    WriteLog: string -> unit }

let private compileCtxNew (host: CliHost) verbosity projectDir : CompileCtx =
  let miloneHome = hostToMiloneHome host
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let syntaxCtx: SyntaxApi.SyntaxCtx =
    let host: SyntaxApi.FetchModuleHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = host.FileReadAllText
        WriteLog = writeLog host verbosity }

    SyntaxApi.newSyntaxCtx host

  { EntryProjectName = projectName
    SyntaxCtx = syntaxCtx
    WriteLog = writeLog host verbosity }

// -----------------------------------------------
// Processes
// -----------------------------------------------

/// Filename of C code. `ProjectName_ModuleName.c` or `ProjectName.c`.
type private CFilename = string

type private CCode = string

type private CodeGenResult = (CFilename * CCode) list

[<NoEquality; NoComparison>]
type private CompileResult =
  | CompileOk of CodeGenResult
  | CompileError of string

let private computeCFilename projectName docId : CFilename =
  if docId = projectName + "." + projectName then
    projectName + ".c"
  else
    S.replace "." "_" docId + ".c"

let private check (ctx: CompileCtx) : bool * string =
  let _, result =
    SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx

  match result with
  | SyntaxApi.SyntaxAnalysisOk _ -> true, ""
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> false, SyntaxApi.syntaxErrorsToString errors

let private compile (ctx: CompileCtx) : CompileResult =
  let projectName = ctx.EntryProjectName
  let writeLog = ctx.WriteLog

  let _, result =
    SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx

  match result with
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> CompileError(SyntaxApi.syntaxErrorsToString errors)

  | SyntaxApi.SyntaxAnalysisOk (modules, tirCtx) ->
    writeLog "Lower"
    let modules, hirCtx = Lower.lower (modules, tirCtx)

    let cFiles =
      TranslationApi.codeGenHir writeLog (modules, hirCtx)

    let cFiles =
      cFiles
      |> List.map (fun (docId, cCode) -> computeCFilename projectName docId, cCode)

    writeLog "Finish"
    CompileOk cFiles

// -----------------------------------------------
// Others
// -----------------------------------------------

let private writeCFiles (host: CliHost) (targetDir: string) (cFiles: (CFilename * CCode) list) : unit =
  dirCreateOrFail host (Path targetDir)
  List.fold (fun () (name, contents) -> host.FileWriteAllText(targetDir + "/" + name) contents) () cFiles

// -----------------------------------------------
// Actions
// -----------------------------------------------

let private cliCheck (host: CliHost) verbosity projectDir =
  let ctx = compileCtxNew host verbosity projectDir

  let ok, output = check ctx
  let exitCode = if ok then 0 else 1

  if output <> "" then
    printfn "%s" (output |> S.replace "#error " "" |> S.trimEnd)

  exitCode

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CompileOptions =
  { ProjectDir: string
    TargetDir: string
    Verbosity: Verbosity }

let private cliCompile (host: CliHost) (options: CompileOptions) =
  let projectDir = options.ProjectDir
  let targetDir = options.TargetDir
  let verbosity = options.Verbosity

  let ctx = compileCtxNew host verbosity projectDir

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    dirCreateOrFail host (Path targetDir)
    writeCFiles host targetDir cFiles

    cFiles
    |> List.map (fun (name, _) -> targetDir + "/" + name + "\n")
    |> S.concat ""
    |> host.WriteStdout

    0

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private BuildOptions =
  { CompileOptions: CompileOptions
    IsRelease: bool }

let private toBuildOnUnixParams
  (host: CliHost)
  (u: UnixApi)
  (options: BuildOptions)
  (ctx: CompileCtx)
  (cFiles: (CFilename * CCode) list)
  : PU.BuildOnUnixParams =
  let miloneHome = Path(hostToMiloneHome host)

  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let isRelease = options.IsRelease
  let projectName = ctx.EntryProjectName

  let manifest =
    ctx.SyntaxCtx |> SyntaxApi.SyntaxCtx.getManifest

  { TargetDir = Path targetDir
    IsRelease = isRelease
    ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName
    CFiles = cFiles |> List.map (fun (name, _) -> Path name)
    MiloneHome = miloneHome
    CSanitize = manifest.CSanitize
    CStd = manifest.CStd
    CcList =
      manifest.CcList
      |> List.map (fun (Path name, _) -> Path(projectDir + "/" + name))
    ObjList =
      manifest.ObjList
      |> List.map (fun (Path name, _) -> Path(projectDir + "/" + name))
    Libs = manifest.Libs |> List.map fst
    DirCreate = dirCreateOrFail host
    FileWrite = fileWrite host
    ExecuteInto = u.ExecuteInto }

let private toBuildOnWindowsParams
  (host: CliHost)
  (w: WindowsApi)
  (options: BuildOptions)
  (ctx: CompileCtx)
  (cFiles: (CFilename * CCode) list)
  : PW.BuildOnWindowsParams =
  let miloneHome = Path(hostToMiloneHome host)

  let compileOptions = options.CompileOptions
  let targetDir = compileOptions.TargetDir
  let isRelease = options.IsRelease
  let projectName = ctx.EntryProjectName
  let projectDir = compileOptions.ProjectDir

  let manifest =
    ctx.SyntaxCtx |> SyntaxApi.SyntaxCtx.getManifest

  { ProjectName = projectName
    CFiles =
      cFiles
      |> List.map (fun (name, _) -> Path(pathJoin targetDir name))
    MiloneHome = miloneHome
    TargetDir = Path targetDir
    IsRelease = isRelease
    ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName

    CcList =
      manifest.CcList
      |> List.map (fun (Path name, _) -> Path(pathJoin projectDir name))
    Libs = manifest.Libs |> List.map fst

    NewGuid = fun () -> PW.Guid(w.NewGuid())
    DirCreate = dirCreateOrFail host
    FileExists = fun filePath -> host.FileExists(Path.toString filePath)
    FileRead = fileRead host
    FileWrite = fileWrite host
    RunCommand = runCommand w }

let private cliBuild (host: CliHost) (options: BuildOptions) =
  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let verbosity = compileOptions.Verbosity

  let ctx = compileCtxNew host verbosity projectDir

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      PU.buildOnUnix (toBuildOnUnixParams host u options ctx cFiles)
      |> never

    | Platform.Windows w ->
      PW.buildOnWindows (toBuildOnWindowsParams host w options ctx cFiles)
      0

let private cliRun (host: CliHost) (options: BuildOptions) (restArgs: string list) =
  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let verbosity = compileOptions.Verbosity

  let ctx = compileCtxNew host verbosity projectDir

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      let p =
        toBuildOnUnixParams host u options ctx cFiles

      PU.runOnUnix p restArgs |> never

    | Platform.Windows w ->
      let p =
        toBuildOnWindowsParams host w options ctx cFiles

      PW.runOnWindows p restArgs
      0

let private cliEval (host: CliHost) (sourceCode: string) =
  let sourceCode =
    """module rec Eval.Program

module S = MiloneStd.StdString

let main _ =
  (
"""
    + sourceCode
    + """
  ) |> string |> printfn "%s"
  0
"""

  let projectDir = "target/Eval"
  let targetDir = projectDir
  let verbosity = Quiet

  let options: BuildOptions =
    { CompileOptions =
        { ProjectDir = projectDir
          TargetDir = targetDir
          Verbosity = verbosity }
      IsRelease = false }

  let ctx = compileCtxNew host verbosity projectDir

  dirCreateOrFail host (Path targetDir)
  fileWrite host (Path(projectDir + "/Eval.milone")) sourceCode

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      let p =
        toBuildOnUnixParams host u options ctx cFiles

      PU.runOnUnix p [] |> never

    | Platform.Windows w ->
      let p =
        toBuildOnWindowsParams host w options ctx cFiles

      PW.runOnWindows p []
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

/// Set of options, used commonly for build-like subcommands (check, compile, build, run).
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private BuildLikeOptions =
  { ProjectDir: ProjectDir
    TargetDir: string
    IsRelease: bool
    Verbosity: Verbosity }

module private BuildLikeOptions =
  let toCompileOptions (b: BuildLikeOptions) : CompileOptions =
    { ProjectDir = b.ProjectDir
      TargetDir = b.TargetDir
      Verbosity = b.Verbosity }

  let toBuildOptions (b: BuildLikeOptions) : BuildOptions =
    { CompileOptions = toCompileOptions b
      IsRelease = b.IsRelease }

let private parseBuildLikeOptions host args : BuildLikeOptions * string list =
  let verbosity, args = parseVerbosity host args

  let targetDirOpt, args =
    parseOption (fun x -> x = "--target-dir") args

  let isReleaseOpt, args =
    parseFlag
      (fun (_: bool option) x ->
        match x with
        | "--release" -> Some(Some true)
        | "--debug" -> Some(Some false)
        | _ -> None)
      None
      args

  let projectDirOpt, args =
    let projectDirOpt, args =
      parseOption (fun x -> x = "--project") args

    match projectDirOpt, args with
    | Some it, _ -> Some it, args
    | _, arg :: args when not (S.startsWith "-" arg) -> Some arg, args
    | _ -> None, args

  let projectDir =
    match projectDirOpt with
    | Some it -> it
    | None ->
      printfn "ERROR: Expected project dir."
      exit 1

  let targetDir =
    match targetDirOpt with
    | Some it -> it
    | None -> defaultTargetDir projectDir

  let options: BuildLikeOptions =
    { ProjectDir = pathJoin host.WorkDir projectDir
      TargetDir = pathJoin host.WorkDir targetDir
      IsRelease = Option.defaultValue false isReleaseOpt
      Verbosity = verbosity }

  options, args

/// Ensures that no redundant arguments are specified.
let private endArgs args : unit =
  match args with
  | arg :: _ ->
    printfn "ERROR: Unknown argument '%s'." arg
    exit 1

  | _ -> ()

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CheckCmd
  | CompileCmd
  | BuildCmd
  | RunCmd
  | EvalCmd
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

  | arg :: args ->
    match arg with
    | "build" -> BuildCmd, args
    | "check" -> CheckCmd, args
    | "compile" -> CompileCmd, args
    | "run" -> RunCmd, args
    | "eval" -> EvalCmd, args
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
    let b, args = parseBuildLikeOptions host args
    endArgs args

    let projectDir = b.ProjectDir
    let verbosity = b.Verbosity
    cliCheck host verbosity projectDir

  | CompileCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args
    endArgs args

    cliCompile host (BuildLikeOptions.toCompileOptions b)

  | BuildCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args
    endArgs args

    cliBuild host (BuildLikeOptions.toBuildOptions b)

  | RunCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args

    let runArgs, args =
      match args with
      | "--" :: it -> it, []
      | _ -> [], args

    endArgs args

    let options = BuildLikeOptions.toBuildOptions b
    cliRun host options runArgs

  | EvalCmd, args ->
    let sourceCode =
      match args with
      | [ "-" ] -> host.ReadStdinAll()
      | [ it ] -> it

      | _ ->
        printfn "ERROR: Invalid args: `milone eval 'expression'`"
        exit 1

    cliEval host sourceCode

  | BadCmd subcommand, _ ->
    printfn "ERROR: Unknown subcommand '%s'." subcommand
    1
