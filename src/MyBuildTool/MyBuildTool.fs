module rec MyBuildTool.Program

open System
open System.Diagnostics
open System.IO
open System.Text

module FS = MyBuildTool.FileSearch

let private helpText () =
  """MyBuildTool: Build tool for milone-lang project.

SUBCOMMANDS:
    gen2    generates target/milone
    gen3    compiles the compiler with target/milone
            and verify the result.

    tests   tests projects in the `tests` directory

    self-install     install milone locally
    self-uninstall   uninstall it
    pack             make binary package

    package          make uncompressed binary package (for debugging)
    ... -n           dry run

    help, -h, --help
    version, -V, --version
"""

let private MiloneVersion = "0.6.0"
let private AssetsDir = __SOURCE_DIRECTORY__ + "/assets"
let private Trace = false

let private CRules =
  """
warning_flags = $
  -Wall $
  -Wextra $
  -Wpedantic $
  -Wno-parentheses-equality $
  -Wno-pointer-to-int-cast $
  -Wno-unknown-warning-option $
  -Wno-unused-but-set-parameter $
  -Wno-unused-but-set-variable $
  -Wno-unused-const-variable $
  -Wno-unused-function $
  -Wno-unused-label $
  -Wno-unused-parameter $
  -Wno-unused-variable

rule compile_c_to_obj
  description = compile_c_to_obj $in
  command = $${CC:-gcc} -std=c11 $warning_flags -O1 -g -c -I./src/libmilonert $in -o $out

rule link_objs_to_exe
  description = link_objs_to_exe $out
  command = $${CC:-gcc} $in -o $out

build src/libmilonert/milone.o: $
  compile_c_to_obj $
    src/libmilonert/milone.c $
    | src/libmilonert/milone.h

build src/libmilonert/milone_platform.o: $
  compile_c_to_obj $
    src/libmilonert/milone_platform.c $
    | src/libmilonert/milone.h
"""

module StringExt =
  let split (sep: string) (s: string) = s.Split(sep) |> Array.toList
  let trim (s: string) = s.Trim()

let private computeSha256 (bytes: byte []) : string =
  use h =
    System.Security.Cryptography.SHA256.Create()

  let hash = h.ComputeHash(bytes)

  BitConverter
    .ToString(hash)
    .Replace("-", "")
    .ToLower()

// -----------------------------------------------
// Operations
// -----------------------------------------------

/// Ensures a directory exists.
let private makeDir (dir: string) : unit =
  Directory.CreateDirectory(dir) |> ignore

/// Reads from a text file.
let private readFile file : string option =
  try
    File.ReadAllText(file) |> Some
  with
  | :? FileNotFoundException
  | :? DirectoryNotFoundException -> None

/// Reads from a text file to be compared to an expected result.
let private readToDiff (file: string) =
  try
    if File.Exists(file) then
      File.ReadAllText(file)
    else
      $"{file} doesn't exist"
  with
  | _ -> $"{file} couldn't be read."

let private writeFile file (contents: string) : unit = File.WriteAllText(file, contents)

/// Writes a text file if changed.
let private writeTo (contents: string) (output: string) =
  let same =
    try
      File.Exists(output)
      && File.ReadAllText(output) = contents
    with
    | _ -> false

  if not same then
    File.WriteAllText(output, contents)

let private copyFile src dest : unit = File.Copy(src, dest, true)

/// Copies multiple files to a directory.
let private copyFilesTo (srcFiles: string list) (destDir: string) : unit =
  for src in srcFiles do
    let destFile =
      Path.Combine(destDir, Path.GetFileName(src))

    File.Copy(src, destFile, true)

/// Gets whether the specified pathname is accepted by the filter.
let private applyFilter (filter: string list) (pathname: string) =
  filter
  |> List.exists (fun (p: string) ->
    if p.StartsWith("*.") then
      let ext = p.[1..]
      Path.GetExtension(pathname) = ext
    else
      Path.GetFileName(pathname) = p)

/// Gets a list of files in a directory, filtering.
let private getFilesWithFilter filter (dir: string) : string array =
  let files =
    try
      Directory.GetFiles(dir)
    with
    | :? DirectoryNotFoundException -> [||]

  files |> Array.filter (applyFilter filter)

/// Copies a directory shallowly. Only files passing the filter are copied.
let private copyDirWithFilter (filter: string list) (srcDir: string) (destDir: string) : unit =
  makeDir destDir

  for src in getFilesWithFilter filter srcDir do
    let destFile =
      Path.Combine(destDir, Path.GetFileName(src))

    File.Copy(src, destFile, true)

let private removeFile file : unit =
  try
    File.Delete(file)
  with
  | :? DirectoryNotFoundException -> ()

let private removeDir dir : unit =
  try
    Directory.Delete(dir, true)
  with
  | :? DirectoryNotFoundException -> ()

let private removeFilesWithFilter (filter: string list) (dir: string) : unit =
  for file in getFilesWithFilter filter dir do
    removeFile file

let private runWithEnv command (args: string list) env workDirOpt : unit =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  for key, value in env do
    startInfo.Environment.Add(key, value)

  match workDirOpt with
  | Some workDir -> startInfo.WorkingDirectory <- workDir
  | None -> ()

  let p = Process.Start(startInfo)
  p.WaitForExit()

  if p.ExitCode <> 0 then
    eprintfn "ERROR: '%s' %A exited with %d." command args p.ExitCode
    exit 1

let private run command (args: string list) : unit = runWithEnv command args [] None

let private runToOut command (args: string list) : string =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  startInfo.RedirectStandardOutput <- true
  startInfo.UseShellExecute <- false

  let p = Process.Start(startInfo)
  p.WaitForExit()

  let output = p.StandardOutput.ReadToEnd()

  if p.ExitCode <> 0 then
    printfn "%s\nERROR: '%s' %A exited with %d." output command args p.ExitCode
    exit 1

  output

// -----------------------------------------------
// Action
// -----------------------------------------------

type private Action =
  // Fundamental actions:
  | Do of label: string * k: (unit -> unit)
  | Block of label: string * Action list

  // Basic actions:
  | Echo of msg: string
  | Run of exe: string * args: string list * env: (string * string) list * workDir: string option
  | RunWith of exe: string * args: string list * k: (string -> unit)

  // File operations:
  | ReadBytesWith of binaryFile: string * k: (byte [] -> unit)
  | CopyFile of src: string * dest: string
  | CopyFiles of srcFiles: string list * dest: string
  | CopyDirWithFilter of src: string * dest: string * filter: string list
  | MakeDir of string
  | RemoveFile of file: string
  | RemoveFilesWithFilter of dir: string * filter: string list
  | RemoveDir of dir: string

[<Sealed; NoEquality; NoComparison>]
type private IOBuilder(label: string) =
  member _.Delay(f: unit -> Action list) = f

  member _.Run(f) = Block(label, f ())

  member _.Zero() : Action list = []
  member _.Yield(x: Action) : Action list = [ x ]
  member _.Bind(x: Action list, f: unit -> Action list) : Action list = List.append x (f ())
  member _.Combine(x: Action, y: unit -> Action list) : Action list = x :: (y ())
  member _.Combine(x: Action list, y: unit -> Action list) : Action list = List.append x (y ())

let private io label = IOBuilder(label)

// -----------------------------------------------
// Environment
// -----------------------------------------------

[<RequireQualifiedAccess>]
type private Platform =
  | Linux
  | Windows

let private getPlatform () : Platform =
  match Environment.OSVersion.Platform with
  | PlatformID.Win32NT -> Platform.Windows
  | _ -> Platform.Linux

let private getExeExt () : string =
  match getPlatform () with
  | Platform.Linux -> ""
  | Platform.Windows -> ".exe"

let private getTriplet () =
  match getPlatform () with
  | Platform.Linux -> "x86_64-unknown-linux-gnu"
  | Platform.Windows -> "x86_64-pc-windows-msvc"

let private generatedExeFile () =
  match getPlatform () with
  | Platform.Linux -> "target/MiloneCli/x86_64-unknown-linux-gnu-release/MiloneCli"
  | Platform.Windows -> "target/MiloneCli/x86_64-pc-windows-msvc-release/MiloneCli.exe"

let private getRuntimeIdentifier () =
  match getPlatform () with
  | Platform.Linux -> "linux-x64"
  | Platform.Windows -> "win10-x64"

let private cwd () : string = Environment.CurrentDirectory

let private getHome () : string =
  Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)

let private setMiloneHomeToCurrentDir () =
  if String.IsNullOrEmpty(Environment.GetEnvironmentVariable("MILONE_HOME")) then
    Environment.SetEnvironmentVariable("MILONE_HOME", cwd ())

// -----------------------------------------------
// gen2
// -----------------------------------------------

let private commandGen2 () =
  eprintfn "milone-compiling gen2"

  setMiloneHomeToCurrentDir ()

  run
    "dotnet"
    [ "run"
      "--no-restore"
      "--project"
      "src/MiloneCli"
      "--"
      "build"
      "src/MiloneCli"
      "--target-dir"
      "target/gen2"
      "--output"
      "target/milone" ]

// -----------------------------------------------
// gen3
// -----------------------------------------------

let private commandGen3 () =
  eprintfn "milone-compiling gen3"

  setMiloneHomeToCurrentDir ()

  makeDir "target/gen3"

  let stdOut =
    runToOut
      "target/milone"
      [ "compile"
        "--profile"
        "src/MiloneCli"
        "--target-dir"
        "target/gen3" ]

  // compare
  let mutable ok = true

  for name in stdOut.Split("\n") do
    let name =
      Path.GetFileNameWithoutExtension(name.Trim())

    if name <> "" then
      let c2 = $"target/gen2/{name}.c"
      let c3 = $"target/gen3/{name}.c"

      if readToDiff c2 <> readToDiff c3 then
        printfn $"differ: {c2} vs {c3}"
        ok <- true

  if not ok then exit 1

// -----------------------------------------------
// tests
// -----------------------------------------------

let private commandTests () =
  setMiloneHomeToCurrentDir ()

  File.WriteAllText("target/tests-build.ninja", InstantiateBuildTemplateNinja.render ())

  run "bin/ninja" [ "-f"; "target/tests-build.ninja" ]

let private commandTestsBuild (testProjectDirs: string list) =
  setMiloneHomeToCurrentDir ()

  let ninja = StringBuilder()
  let w (s: string) = ninja.AppendLine(s) |> ignore

  w "builddir = target/tests2"
  w CRules

  let exeFiles = ResizeArray()

  for projectDir in testProjectDirs do
    let projectName = Path.GetFileName(projectDir)

    let category =
      Path.GetFileName(Path.GetDirectoryName(projectDir))

    let targetDir = $"target/tests/{category}/{projectName}"
    let exe = $"{targetDir}/{projectName}.exe"
    exeFiles.Add(exe)

    w "\n# ----------------------------------"
    w $"# {projectDir}"
    w "# ----------------------------------"

    let files =
      File.ReadAllText($"{targetDir}/files.txt")

    let oFiles = ResizeArray()

    for name in files.Split("\n") do
      let name =
        Path.GetFileNameWithoutExtension(name.Trim())

      if String.IsNullOrEmpty(name) |> not then
        let c = $"{projectDir}/{name}.c"
        let o = $"{targetDir}/{name}.o"
        oFiles.Add(o)

        w $"build {o}: compile_c_to_obj {c} | src/libmilonert/milone.h"

    let input = oFiles |> String.concat " "

    w $"build {exe}: link_objs_to_exe src/libmilonert/milone.o src/libmilonert/milone_platform.o {input}"

  let exeFiles = String.concat " " exeFiles

  w $"default {exeFiles}"

  writeTo (ninja.ToString()) "target/tests2-build.ninja"

let private commandTestsSummarize (testProjectDirs: string list) =
  setMiloneHomeToCurrentDir ()

  let mutable pass = 0
  let mutable fail = 0

  for projectDir in testProjectDirs do
    let projectName = Path.GetFileName(projectDir)

    let category =
      Path.GetFileName(Path.GetDirectoryName(projectDir))

    let targetDir = $"target/tests/{category}/{projectName}"
    let expectedOut = $"{projectDir}/{projectName}.output"
    let generatedTxt = $"{targetDir}/generated.txt"

    if readToDiff expectedOut <> readToDiff generatedTxt then
      printfn $"differ {generatedTxt} vs {expectedOut}"
      fail <- fail + 1
    else
      pass <- pass + 1

  let ok = pass <> 0 && fail = 0
  printfn "pass %d / fail %d / total %d" pass fail (pass + fail)
  printfn "%s" (if ok then "OK" else "FAILED")
  if not ok then exit 1

// -----------------------------------------------
// Helper of Package
// -----------------------------------------------

let private RunDotnetPublish (projectDir, outputDir) : Action =
  Run(
    "dotnet",
    [ "publish"
      projectDir
      "--runtime"
      getRuntimeIdentifier ()
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      outputDir
      "-nologo"
      "-v:quiet"
      "-consoleLoggerParameters:NoSummary" ],
    [],
    None
  )

let private RunPwsh command : Action =
  Run(
    "C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe",
    [ "-NoLogo"
      "-NoProfile"
      "-NonInteractive"
      "-c"
      command ],
    [],
    Path.GetDirectoryName(command) |> Some
  )

let private dumpAction a =
  let mutable indent = ""

  let rec go a =
    match a with
    | Block (label, actions) ->
      let parentIndent = indent
      indent <- indent + "  "

      eprintfn "%s%s {" parentIndent label

      for a in actions do
        go a

      eprintfn "%s}" parentIndent

      indent <- parentIndent

    | Do (label, _) -> eprintfn "%sDo(%s)" indent label

    | CopyDirWithFilter (src, dest, filter) ->
      eprintfn "%sCopyDirWithFilter(%A, %s)" indent (getFilesWithFilter filter src) dest

    | RemoveFilesWithFilter (dir, filter) ->
      eprintfn "%sRemoveFilesWithFilter(%A)" indent (getFilesWithFilter filter dir)

    | _ -> eprintfn "%s%A" indent a

  go a

let private performAction a =
  let rec go a =
    if Trace then
      match a with
      | Block _
      | Echo _ -> ()
      | _ -> dumpAction a

    match a with
    | Block (label, actions) ->
      try
        for a in actions do
          go a
      with
      | _ ->
        eprintfn "Failed in %s" label
        reraise ()

    | CopyFile (src, dest) -> copyFile src dest
    | CopyFiles (srcFiles, dest) -> copyFilesTo srcFiles dest
    | CopyDirWithFilter (src, dest, filter) -> copyDirWithFilter filter src dest
    | MakeDir dir -> makeDir dir
    | Run (exe, args, env, workDir) -> runWithEnv exe args env workDir
    | RunWith (exe, args, k) -> k (runToOut exe args)
    | RemoveFile file -> removeFile file
    | RemoveFilesWithFilter (dir, filter) -> removeFilesWithFilter filter dir
    | RemoveDir dir -> removeDir dir
    | Echo msg -> printfn "%s" msg
    | Do (_, k) -> k ()

    | ReadBytesWith (file, k) ->
      let contents =
        try
          File.ReadAllBytes(file)
        with
        | :? FileNotFoundException
        | :? DirectoryNotFoundException -> [||]

      k contents

  go a

let private destFiles (destDir: string) =
  let exeExt = getExeExt ()
  let destMiloneHome = $"{destDir}/share/milone"

  {| BinDir = $"{destDir}/bin"
     MiloneExe = $"{destDir}/bin/milone{exeExt}"
     MiloneHome = destMiloneHome
     MiloneLspDir = $"{destMiloneHome}/bin/milone_lsp"
     SrcDir = $"{destMiloneHome}/src"
     VersionFile = $"{destMiloneHome}/version" |}

// -----------------------------------------------
// Package
// -----------------------------------------------

// IMPORTANT!
//    This script must be sync with
//    binary_package.md, INSTALL.md, and install/uninstall scripts.

/// Generates a binary package.
let private generateBinaryPackage (destDir: string) =
  let onLinux = getPlatform () = Platform.Linux
  let dest = destFiles destDir

  io "package" {
    // Make structure.
    RemoveDir destDir
    MakeDir dest.BinDir
    MakeDir dest.MiloneHome

    // Build.
    Run(
      "dotnet",
      ("run --project src/MiloneCli -- build --release src/MiloneCli"
       |> StringExt.split " "),
      [ "MILONE_HOME", cwd () ],
      None
    )

    CopyFile(generatedExeFile (), dest.MiloneExe)

    if onLinux then
      Run("strip", [ "-s"; dest.MiloneExe ], [], None)

    // Record version.
    RunWith(
      dest.MiloneExe,
      [ "--version" ],
      fun version ->
        let version = StringExt.trim version
        assert (version = MiloneVersion)
        writeFile dest.VersionFile $"{version}\n"
    )

    // Build LSP server.
    RunDotnetPublish("src/MiloneLspServer", dest.MiloneLspDir)
    RemoveFilesWithFilter(dest.MiloneLspDir, [ "*.pdb" ])

    // Copy runtime files.
    CopyDirWithFilter("src/libmilonert", $"{dest.SrcDir}/libmilonert", [ "*.c"; "*.h"; "LICENSE" ])
    CopyDirWithFilter("src/MiloneCore", $"{dest.SrcDir}/MiloneCore", [ "*.fs"; "*.milone"; "LICENSE" ])
    CopyDirWithFilter("src/Std", $"{dest.SrcDir}/Std", [ "*.fs"; "*.milone"; "LICENSE" ])

    if onLinux then
      CopyFile("bin/ninja", $"{dest.MiloneHome}/bin/ninja")

    // Add assets.
    let installScript, uninstallScript =
      match getPlatform () with
      | Platform.Linux -> $"{AssetsDir}/install.sh", $"{AssetsDir}/uninstall.sh"
      | Platform.Windows -> $"{AssetsDir}/install.ps1", $"{AssetsDir}/uninstall.ps1"

    CopyFiles(
      [ "README.md"
        "LICENSE"
        $"{AssetsDir}/INSTALL.md"
        installScript
        uninstallScript ],
      destDir
    )
  }

// -----------------------------------------------
// Pack
// -----------------------------------------------

/// Makes a compressed binary package to upload.
let private commandPack () =
  let triplet = getTriplet ()

  let version = MiloneVersion
  let destDir = $"{cwd ()}/target/milone-{version}"

  io "pack" {
    generateBinaryPackage destDir

    // Compress.
    let outFile =
      match getPlatform () with
      | Platform.Linux -> $"target/milone-{version}-{triplet}.tar.gz"
      | Platform.Windows -> $"target/milone-{version}-{triplet}.zip"

    RemoveFile outFile

    match getPlatform () with
    | Platform.Linux -> Run("tar", [ "-czf"; outFile; destDir ], [], None)
    | Platform.Windows -> Do("compress", (fun () -> Compression.ZipFile.CreateFromDirectory(destDir, outFile)))

    ReadBytesWith(
      outFile,
      fun contents ->
        let hash = computeSha256 contents
        printfn "%s  %s" hash (Path.GetFileName(outFile))
    )

    Echo $"Generated {outFile}"
    Echo $"milone-lang v{version} is packed successfully!"
  }

// -----------------------------------------------
// self-install
// -----------------------------------------------

let private commandSelfInstall () : Action =
  let destDir =
    $"{cwd ()}/target/milone-{MiloneVersion}"

  io "self-install" {
    generateBinaryPackage destDir

    match getPlatform () with
    | Platform.Linux -> Run("/bin/sh", [ $"{destDir}/install.sh" ], [], Some destDir)
    | Platform.Windows -> RunPwsh $"{destDir}/install.ps1"
  }

// -----------------------------------------------
// self-uninstall
// -----------------------------------------------

let private commandSelfUninstall () =
  io "uninstall" {
    match getPlatform () with
    | Platform.Linux -> Run("/bin/sh", [ $"{AssetsDir}/uninstall.sh" ], [], None)
    | Platform.Windows -> RunPwsh $"{AssetsDir}/uninstall.ps1"
  }

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<EntryPoint>]
let main (argv: string array) =
  let args = Array.toList argv

  let dryRun, args =
    List.contains "-n" args, List.filter ((<>) "-n") args

  let perform =
    if dryRun then
      dumpAction
    else
      performAction

  match args with
  | []
  | "help" :: _
  | "-h" :: _
  | "--help" :: _ -> printf "%s" (helpText ())

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ -> printfn "0.1.0"

  | "gen2" :: _ -> commandGen2 ()
  | "gen3" :: _ -> commandGen3 ()

  | "tests" :: _ -> commandTests ()
  | "--build-run-tests" :: args -> commandTestsBuild args
  | "--summarize-tests" :: args -> commandTestsSummarize args

  | "self-install" :: _ -> commandSelfInstall () |> perform
  | "self-uninstall" :: _ -> commandSelfUninstall () |> perform
  | "pack" :: _ -> commandPack () |> perform
  | "package" :: _ -> generateBinaryPackage "target/package" |> perform

  | _ ->
    eprintfn "unknown target: %A" argv
    exit 1

  0
