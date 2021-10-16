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
module Derive = MiloneTranslation.Derive
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

    /// Reads from standard input.
    ReadStdinAll: unit -> string

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

let private computeExePath targetDir platform isRelease name : Path =
  let triple =
    match platform with
    | Platform.Unix -> "x86_64-unknown-linux-gnu"
    | Platform.Windows -> "x86_64-pc-windows-msvc"

  let mode = if isRelease then "release" else "debug"

  let quad = triple + "-" + mode

  let ext =
    match platform with
    | Platform.Unix -> ""
    | Platform.Windows -> ".exe"

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
type CompileCtx =
  { EntryProjectDir: ProjectDir
    EntryProjectName: ProjectName

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

  writeLog host v "RecordRes"
  let modules, tyCtx = recordRes (modules, tyCtx)

  writeLog host v "Derive"
  let modules, tyCtx = Derive.deriveOps (modules, tyCtx)

  writeLog host v "ClosureConversion"
  let modules, tyCtx = closureConversion (modules, tyCtx)

  writeLog host v "EtaExpansion"
  let modules, tyCtx = etaExpansion (modules, tyCtx)

  writeLog host v "ComputeTyArgs"
  let modules, tyCtx = computeFunTyArgs (modules, tyCtx)

  writeLog host v "AutoBoxing"
  let modules, tyCtx = autoBox (modules, tyCtx)

  writeLog host v "Hoist"
  let modules, tyCtx = hoist (modules, tyCtx)

  writeLog host v "TailRecOptimizing"
  let modules, tyCtx = tailRecOptimize (modules, tyCtx)

  writeLog host v "Flatten"

  let modules, vars =
    modules
    |> List.mapFold
         (fun vars (m: Hir.HModule) ->
           let vars =
             // #map_merge
             m.Vars
             |> TMap.fold (fun vars k v -> TMap.add k v vars) vars

           { m with Vars = Hir.emptyVars }, vars)
         tyCtx.Vars

  let tyCtx = { tyCtx with Vars = vars }

  let decls =
    (modules
     |> List.collect (fun (m: Hir.HModule) -> m.Stmts))

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

let cliCheck (host: CliHost) verbosity projectDir =
  let ctx = compileCtxNew host verbosity projectDir

  let ok, output = check ctx
  let exitCode = if ok then 0 else 1

  if output <> "" then
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
    |> List.map (fun (name, _) -> targetDir + "/" + name + "\n")
    |> S.concat ""
    |> host.WriteStdout

    0

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildOptions =
  { ProjectDir: string
    TargetDir: string
    IsRelease: bool
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
      let isRelease = options.IsRelease
      let projectName = ctx.EntryProjectName
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let p: PU.BuildOnUnixParams =
        { TargetDir = Path targetDir
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)
          MiloneHome = miloneHome
          DirCreate = dirCreateOrFail host
          FileWrite = fileWrite host
          ExecuteInto = host.ExecuteInto }

      PU.buildOnUnix p
      unreachable ()

  | Platform.Windows ->
    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      let targetDir = options.TargetDir
      let isRelease = options.IsRelease
      let projectName = ctx.EntryProjectName
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let p: PW.BuildOnWindowsParams =
        { ProjectName = projectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)
          MiloneHome = miloneHome
          TargetDir = Path targetDir
          IsRelease = isRelease
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName

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
      let isRelease = options.IsRelease
      let projectName = ctx.EntryProjectName
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let p: PU.RunOnUnixParams =
        { TargetDir = Path targetDir
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)
          MiloneHome = miloneHome
          Args = restArgs
          DirCreate = dirCreateOrFail host
          FileWrite = fileWrite host
          ExecuteInto = host.ExecuteInto }

      PU.runOnUnix p
      unreachable ()

  | Platform.Windows ->
    let ctx =
      compileCtxNew host options.Verbosity options.ProjectDir

    match compile ctx with
    | CompileError output ->
      host.WriteStdout output
      1

    | CompileOk cFiles ->
      let targetDir = options.TargetDir
      let isRelease = options.IsRelease
      let projectName = ctx.EntryProjectName
      let miloneHome = Path(hostToMiloneHome host)

      writeCFiles host targetDir cFiles

      let p: PW.RunOnWindowsParams =
        { ProjectName = ctx.EntryProjectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)

          MiloneHome = miloneHome
          TargetDir = Path targetDir
          IsRelease = isRelease
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName

          NewGuid = fun () -> PW.Guid(host.NewGuid())
          DirCreate = dirCreateOrFail host
          FileExists = fun filePath -> host.FileExists(Path.toString filePath)
          FileWrite = fileWrite host
          RunCommand = runCommand host

          Args = restArgs }

      PW.runOnWindows p
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
  let projectName = "Eval"
  let targetDir = projectDir
  let isRelease = false
  let miloneHome = Path(hostToMiloneHome host)

  dirCreateOrFail host (Path targetDir)
  fileWrite host (Path(projectDir + "/Eval.milone")) sourceCode

  let ctx = compileCtxNew host Quiet projectDir

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output
    1

  | CompileOk cFiles ->
    writeCFiles host targetDir cFiles

    match host.Platform with
    | Platform.Unix ->
      let p: PU.RunOnUnixParams =
        { TargetDir = Path targetDir
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)
          MiloneHome = miloneHome
          Args = []
          DirCreate = dirCreateOrFail host
          FileWrite = fileWrite host
          ExecuteInto = host.ExecuteInto }

      PU.runOnUnix p
      unreachable ()

    | Platform.Windows ->
      let p: PW.RunOnWindowsParams =
        { ProjectName = ctx.EntryProjectName
          CFiles = cFiles |> List.map (fun (name, _) -> Path name)

          MiloneHome = miloneHome
          TargetDir = Path targetDir
          IsRelease = isRelease
          ExeFile = computeExePath (Path targetDir) host.Platform isRelease projectName

          NewGuid = fun () -> PW.Guid(host.NewGuid())
          DirCreate = dirCreateOrFail host
          FileExists = fun filePath -> host.FileExists(Path.toString filePath)
          FileWrite = fileWrite host
          RunCommand = runCommand host

          Args = [] }

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

/// Set of options, used commonly for build-like subcommands (check, compile, build, run).
type private BuildLikeOptions =
  { ProjectDir: ProjectDir
    TargetDir: string
    IsRelease: bool
    Verbosity: Verbosity }

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
      parseOption (fun x -> x = "-p" || x = "--project-dir") args

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
    { ProjectDir = projectDir
      TargetDir = targetDir
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

    let options: CompileOptions =
      { ProjectDir = b.ProjectDir
        TargetDir = b.TargetDir
        Verbosity = b.Verbosity }

    cliCompile host options

  | BuildCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args
    endArgs args

    let options: BuildOptions =
      { ProjectDir = b.ProjectDir
        TargetDir = b.TargetDir
        IsRelease = b.IsRelease
        Verbosity = b.Verbosity }

    cliBuild host options

  | RunCmd, args ->
    let args = eatParallelFlag args
    let b, args = parseBuildLikeOptions host args

    let runArgs, args =
      match args with
      | "--" :: it -> it, []
      | _ -> [], args

    endArgs args

    let options: BuildOptions =
      { ProjectDir = b.ProjectDir
        TargetDir = b.TargetDir
        IsRelease = b.IsRelease
        Verbosity = b.Verbosity }

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
