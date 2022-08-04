/// Front end of the compiler.
module rec MiloneCliCore.Cli

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneShared.UtilParallel
open MiloneShared.UtilProfiler
open MiloneShared.UtilSymbol
open Std.StdError
open Std.StdPath
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.SyntaxApiTypes
open MiloneTranslationTypes.TranslationApiTypes

module C = Std.StdChar
module S = Std.StdString
module Lower = MiloneCliCore.Lower
module PU = MiloneCliCore.PlatformUnix
module PW = MiloneCliCore.PlatformWindows

let private currentVersion () = "0.5.0"

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
  { /// Command line args.
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
    // baseDir -> dir -> exist
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

  if isRooted r then r
  else if r = "." then l
  else l + "/" + r

let private hostToMiloneHome (sApi: SyntaxApi) (host: CliHost) =
  sApi.GetMiloneHomeFromEnv(fun () -> host.MiloneHome) (fun () -> Some host.Home)

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

/// Computes the path where the output is generated.
let private computeExePath targetDir platform isRelease binaryType name : Path =
  let triple =
    match platform with
    | Platform.Unix _ -> "x86_64-unknown-linux-gnu"
    | Platform.Windows _ -> "x86_64-pc-windows-msvc"

  let mode = if isRelease then "release" else "debug"

  let quad = triple + "-" + mode

  let ext =
    match platform, binaryType with
    | Platform.Unix _, BinaryType.Exe -> ""
    | Platform.Unix _, BinaryType.SharedObj -> ".so"
    | Platform.Unix _, BinaryType.StaticLib -> ".a"
    | Platform.Windows _, BinaryType.Exe -> ".exe"
    | Platform.Windows _, BinaryType.SharedObj -> ".dll"
    | Platform.Windows _, BinaryType.StaticLib -> ".lib"

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
    SyntaxCtx: SyntaxCtx
    EntrypointName: string
    WriteLog: string -> unit }

let private compileCtxNew (sApi: SyntaxApi) (host: CliHost) verbosity projectDir : CompileCtx =
  let miloneHome = hostToMiloneHome sApi host
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let syntaxCtx: SyntaxCtx =
    let host: FetchModuleHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = host.FileReadAllText
        WriteLog = writeLog host verbosity }

    sApi.NewSyntaxCtx host

  { EntryProjectName = projectName
    SyntaxCtx = syntaxCtx

    EntrypointName =
      match (syntaxCtx |> sApi.GetManifest).BinaryType with
      | None
      | Some (BinaryType.Exe, _) -> "main"

      | _ -> projectName + "_initialize"

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

let private computeCFilename projectName (docId: DocId) : CFilename =
  if Symbol.toString docId = projectName + "." + projectName then
    projectName + ".c"
  else
    S.replace "." "_" (Symbol.toString docId) + ".c"

let private check (sApi: SyntaxApi) (ctx: CompileCtx) : bool * string =
  let _, result =
    sApi.PerformSyntaxAnalysis ctx.SyntaxCtx

  match result with
  | SyntaxAnalysisOk _ -> true, ""
  | SyntaxAnalysisError (errors, _) -> false, sApi.SyntaxErrorsToString errors

let private compile (sApi: SyntaxApi) (tApi: TranslationApi) (ctx: CompileCtx) : CompileResult =
  let projectName = ctx.EntryProjectName
  let writeLog = ctx.WriteLog

  let _, result =
    sApi.PerformSyntaxAnalysis ctx.SyntaxCtx

  match result with
  | SyntaxAnalysisError (errors, _) -> CompileError(sApi.SyntaxErrorsToString errors)

  | SyntaxAnalysisOk (modules, tirCtx) ->
    writeLog "Lower"
    let modules, hirCtx = Lower.lower (modules, tirCtx)

    let cFiles =
      tApi.CodeGenHir ctx.EntrypointName writeLog (modules, hirCtx)

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

let private cliCheck sApi (host: CliHost) verbosity projectDir =
  let ctx =
    compileCtxNew sApi host verbosity projectDir

  let ok, output = check sApi ctx
  let exitCode = if ok then 0 else 1

  if output <> "" then
    printfn "%s" (output |> S.replace "#error " "" |> S.trimEnd)

  exitCode

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CompileOptions =
  { ProjectDir: string
    TargetDir: string
    Verbosity: Verbosity }

let private cliCompile sApi tApi (host: CliHost) (options: CompileOptions) =
  let projectDir = options.ProjectDir
  let targetDir = options.TargetDir
  let verbosity = options.Verbosity

  let ctx =
    compileCtxNew sApi host verbosity projectDir

  match compile sApi tApi ctx with
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
    IsRelease: bool
    OutputOpt: string option }

let private toBuildOnUnixParams
  sApi
  (host: CliHost)
  (u: UnixApi)
  (options: BuildOptions)
  (ctx: CompileCtx)
  (cFiles: (CFilename * CCode) list)
  : PU.BuildOnUnixParams =
  let miloneHome = Path(hostToMiloneHome sApi host)

  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let isRelease = options.IsRelease
  let outputOpt = options.OutputOpt
  let projectName = ctx.EntryProjectName

  let manifest = ctx.SyntaxCtx |> sApi.GetManifest

  let binaryType =
    match manifest.BinaryType with
    | Some (it, _) -> it
    | None -> BinaryType.Exe

  { TargetDir = Path targetDir
    IsRelease = isRelease
    ExeFile = computeExePath (Path targetDir) host.Platform isRelease binaryType projectName
    OutputOpt = outputOpt |> Option.map Path
    CFiles = cFiles |> List.map (fun (name, _) -> Path name)
    MiloneHome = miloneHome
    BinaryType = binaryType
    CSanitize = manifest.CSanitize
    CStd = manifest.CStd
    CcList =
      manifest.CcList
      |> List.map (fun (Path name, _) -> Path(projectDir + "/" + name))
    ObjList =
      manifest.ObjList
      |> List.map (fun (Path name, _) -> Path(projectDir + "/" + name))
    Libs = manifest.Libs |> List.map fst
    LinuxCFlags = manifest.LinuxCFlags |> Option.defaultValue ""
    LinuxLinkFlags = manifest.LinuxLinkFlags |> Option.defaultValue ""
    DirCreate = dirCreateOrFail host
    FileWrite = fileWrite host
    ExecuteInto = u.ExecuteInto }

let private toBuildOnWindowsParams
  sApi
  (host: CliHost)
  (w: WindowsApi)
  (options: BuildOptions)
  (ctx: CompileCtx)
  (cFiles: (CFilename * CCode) list)
  : PW.BuildOnWindowsParams =
  let miloneHome = Path(hostToMiloneHome sApi host)

  let compileOptions = options.CompileOptions
  let targetDir = compileOptions.TargetDir
  let isRelease = options.IsRelease
  let outputOpt = options.OutputOpt
  let projectName = ctx.EntryProjectName
  let projectDir = compileOptions.ProjectDir

  let manifest = ctx.SyntaxCtx |> sApi.GetManifest

  let binaryType =
    match manifest.BinaryType with
    | Some (it, _) -> it
    | None -> BinaryType.Exe

  let subSystem =
    match manifest.SubSystem with
    | Some it -> it
    | None -> SubSystem.Windows

  { ProjectName = projectName
    CFiles =
      cFiles
      |> List.map (fun (name, _) -> Path(pathJoin targetDir name))
    MiloneHome = miloneHome
    TargetDir = Path targetDir
    IsRelease = isRelease
    ExeFile = computeExePath (Path targetDir) host.Platform isRelease binaryType projectName
    OutputOpt = outputOpt |> Option.map Path

    BinaryType = binaryType
    SubSystem = subSystem

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

let private cliBuild sApi tApi (host: CliHost) (options: BuildOptions) =
  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let verbosity = compileOptions.Verbosity

  let ctx =
    compileCtxNew sApi host verbosity projectDir

  match compile sApi tApi ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      PU.buildOnUnix (toBuildOnUnixParams sApi host u options ctx cFiles)
      |> never

    | Platform.Windows w ->
      PW.buildOnWindows (toBuildOnWindowsParams sApi host w options ctx cFiles)
      0

let private cliRun sApi tApi (host: CliHost) (options: BuildOptions) (restArgs: string list) =
  let compileOptions = options.CompileOptions
  let projectDir = compileOptions.ProjectDir
  let targetDir = compileOptions.TargetDir
  let verbosity = compileOptions.Verbosity

  let ctx =
    compileCtxNew sApi host verbosity projectDir

  match compile sApi tApi ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      let p =
        toBuildOnUnixParams sApi host u options ctx cFiles

      PU.runOnUnix p restArgs |> never

    | Platform.Windows w ->
      let p =
        toBuildOnWindowsParams sApi host w options ctx cFiles

      PW.runOnWindows p restArgs
      0

let private cliEval sApi tApi (host: CliHost) (sourceCode: string) =
  let sourceCode =
    """module rec Eval.Program

module S = Std.StdString

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
      IsRelease = false
      OutputOpt = None }

  let ctx =
    compileCtxNew sApi host verbosity projectDir

  dirCreateOrFail host (Path targetDir)
  fileWrite host (Path(projectDir + "/Eval.milone")) sourceCode

  match compile sApi tApi ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix u ->
      let p =
        toBuildOnUnixParams sApi host u options ctx cFiles

      PU.runOnUnix p [] |> never

    | Platform.Windows w ->
      let p =
        toBuildOnWindowsParams sApi host w options ctx cFiles

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
    OutputOpt: string option
    Verbosity: Verbosity }

module private BuildLikeOptions =
  let toCompileOptions (b: BuildLikeOptions) : CompileOptions =
    { ProjectDir = b.ProjectDir
      TargetDir = b.TargetDir
      Verbosity = b.Verbosity }

  let toBuildOptions (b: BuildLikeOptions) : BuildOptions =
    { CompileOptions = toCompileOptions b
      IsRelease = b.IsRelease
      OutputOpt = b.OutputOpt }

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

  let outputFileOpt, args =
    parseOption (fun x -> x = "-o" || x = "--output") args

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

  let outputFileOpt =
    match outputFileOpt with
    | Some it -> pathJoin host.WorkDir it |> Some
    | None -> None

  let options: BuildLikeOptions =
    { ProjectDir = pathJoin host.WorkDir projectDir
      TargetDir = pathJoin host.WorkDir targetDir
      IsRelease = Option.defaultValue false isReleaseOpt
      OutputOpt = outputFileOpt
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

let cli (sApi: SyntaxApi) (tApi: TranslationApi) (host: CliHost) =
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
    cliCheck sApi host verbosity projectDir

  | CompileCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args
    endArgs args

    cliCompile sApi tApi host (BuildLikeOptions.toCompileOptions b)

  | BuildCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args
    endArgs args

    cliBuild sApi tApi host (BuildLikeOptions.toBuildOptions b)

  | RunCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args

    let runArgs, args =
      match args with
      | "--" :: it -> it, []
      | _ -> [], args

    endArgs args

    let options = BuildLikeOptions.toBuildOptions b
    cliRun sApi tApi host options runArgs

  | EvalCmd, args ->
    let sourceCode =
      match args with
      | [ "-" ] -> host.ReadStdinAll()
      | [ it ] -> it

      | _ ->
        printfn "ERROR: Invalid args: `milone eval 'expression'`"
        exit 1

    cliEval sApi tApi host sourceCode

  | BadCmd subcommand, _ ->
    printfn "ERROR: Unknown subcommand '%s'." subcommand
    1
