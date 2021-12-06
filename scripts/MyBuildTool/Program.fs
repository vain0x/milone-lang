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

    help, -h, --help
    version, -V, --version
"""

let private cRules =
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
  command = $${CC:-gcc} -std=c11 $warning_flags -O1 -g -c -Iruntime $in -o $out

rule link_objs_to_exe
  description = link_objs_to_exe $out
  command = $${CC:-gcc} $in -o $out

build runtime/milone.o: $
  compile_c_to_obj $
    runtime/milone.c $
    | runtime/milone.h

build runtime/milone_platform.o: $
  compile_c_to_obj $
    runtime/milone_platform.c $
    | runtime/milone.h
"""

module StringExt =
  let split (sep: string) (s: string) = s.Split(sep) |> Array.toList
  let trim (s: string) = s.Trim()

let private tRng =
  new System.Threading.ThreadLocal<System.Random>(fun () -> System.Random())

// Sha256.
let private computeFileHash (file: string) : string =
  let contents = System.IO.File.ReadAllBytes(file)

  use h =
    System.Security.Cryptography.SHA256.Create()

  let hash = h.ComputeHash(contents)

  System
    .BitConverter
    .ToString(hash)
    .Replace("-", "")
    .ToLower()

let private makeDir (dir: string) : unit =
  Directory.CreateDirectory(dir) |> ignore

let private readFile file : string option =
  try
    System.IO.File.ReadAllText(file) |> Some
  with
  | _ -> None

let private writeFile file contents : unit =
  System.IO.File.WriteAllText(file, contents)

let private readToDiff (file: string) =
  try
    if File.Exists(file) then
      File.ReadAllText(file)
    else
      $"{file} doesn't exist"
  with
  | _ -> $"{file} couldn't be read."

let private writeTo (contents: string) (output: string) =
  let same =
    try
      File.Exists(output)
      && File.ReadAllText(output) = contents
    with
    | _ -> false

  if not same then
    File.WriteAllText(output, contents)

let private copyFile src dest : unit = System.IO.File.Copy(src, dest, true)

let private copyFilesTo (srcFiles: string list) (destDir: string) : unit =
  for src in srcFiles do
    let destFile =
      Path.Combine(destDir, System.IO.Path.GetFileName(src))

    System.IO.File.Copy(src, destFile, true)

let private copyDir src dest : unit =
  let rec go src dest =
    makeDir dest

    for subdir in System.IO.Directory.GetDirectories(src) do
      let destSubdir =
        Path.Combine(dest, System.IO.Path.GetFileName(subdir))

      go subdir destSubdir

    for file in System.IO.Directory.GetFiles(src) do
      let destFile =
        Path.Combine(dest, System.IO.Path.GetFileName(file))

      System.IO.File.Copy(file, destFile)

  go src dest

let private moveDir (src: string) (dest: string) : unit = System.IO.Directory.Move(src, dest)

let private removeFile file : unit = System.IO.File.Delete(file)

let private removeDir dir : unit =
  try
    System.IO.Directory.Delete(dir, true)
  with
  | :? System.IO.DirectoryNotFoundException -> ()

let private run command (args: string list) : unit =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  let p = Process.Start(startInfo)
  p.WaitForExit()

  if p.ExitCode <> 0 then
    eprintfn "ERROR: '%s' %A exited with %d." command args p.ExitCode
    exit 1

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
// gen2
// -----------------------------------------------

let private commandGen2 () =
  eprintfn "milone-compiling gen2"
  makeDir "target/gen2"

  let stdOut =
    runToOut
      "dotnet"
      [ "run"
        "--project"
        "src/MiloneCli"
        "--"
        "compile"
        "src/MiloneCli"
        "--target-dir"
        "target/gen2" ]

  let ninja = StringBuilder()
  let w (s: string) = ninja.AppendLine(s) |> ignore

  w "builddir = target/gen2"
  w cRules

  let oFiles = ResizeArray()

  for name in stdOut.Split("\n") do
    let name =
      Path.GetFileNameWithoutExtension(name.Trim())

    if String.IsNullOrEmpty(name) |> not then
      let c = $"target/gen2/{name}.c"
      let o = $"target/gen2/{name}.o"
      oFiles.Add(o)

      w $"build {o}: compile_c_to_obj {c} | runtime/milone.h"

  let input = oFiles |> String.concat " "

  w $"build target/milone: link_objs_to_exe runtime/milone.o runtime/milone_platform.o {input}"

  writeTo (ninja.ToString()) "target/gen2/build.ninja"

  eprintfn "c-compiling gen2"

  run
    "bin/ninja"
    [ "-f"
      "target/gen2/build.ninja"
      "target/milone" ]

// -----------------------------------------------
// gen3
// -----------------------------------------------

let private commandGen3 () =
  eprintfn "milone-compiling gen3"
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
  File.WriteAllText("target/tests-build.ninja", InstantiateBuildTemplateNinja.render ())

  run "bin/ninja" [ "-f"; "target/tests-build.ninja" ]

let private commandTestsBuild (testProjectDirs: string list) =
  let ninja = StringBuilder()
  let w (s: string) = ninja.AppendLine(s) |> ignore

  w "builddir = target/tests2"
  w cRules

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

        w $"build {o}: compile_c_to_obj {c} | runtime/milone.h"

    let input = oFiles |> String.concat " "

    w $"build {exe}: link_objs_to_exe runtime/milone.o runtime/milone_platform.o {input}"

  let exeFiles = String.concat " " exeFiles

  w $"default {exeFiles}"

  writeTo (ninja.ToString()) "target/tests2-build.ninja"

let private commandTestsSummarize (testProjectDirs: string list) =
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
// self-install
// -----------------------------------------------

let private getHome () : string =
  System.Environment.GetFolderPath(System.Environment.SpecialFolder.UserProfile)

[<RequireQualifiedAccess>]
type private Platform =
  | Unix
  | Windows

let private getPlatform () : Platform =
  match System.Environment.OSVersion.Platform with
  | System.PlatformID.Win32NT -> Platform.Windows
  | _ -> Platform.Unix

let private getExt platform : string =
  match platform with
  | Platform.Unix -> ""
  | Platform.Windows -> ".exe"

let private buildSelf () : unit =
  run
    "dotnet"
    ("run --project src/MiloneCli -- build --release src/MiloneCli"
     |> StringExt.split " ")

let private windowsBinaryPath =
  "target/MiloneCli/x86_64-pc-windows-msvc-release/MiloneCli.exe"

let private commandSelfInstall () : unit =
  let home = getHome ()
  let platform = getPlatform ()
  let ext = getExt platform

  let binDir = $"{home}/bin"
  let miloneHome = $"{home}/.milone"
  let destMiloneExe = $"{binDir}/milone{ext}"
  let destMiloneDotnetDir = $"{miloneHome}/bin/milone_dotnet"
  let destMiloneLspDir = $"{miloneHome}/bin/milone_lsp"
  let destRuntimeDir = $"{miloneHome}/runtime"
  let destMiloneLibsDir = $"{miloneHome}/milone_libs"
  let destVersionFile = $"{miloneHome}/version"

  doUninstall () |> ignore

  // Create directories.
  makeDir binDir
  makeDir miloneHome

  // Build binary.
  let generatedExeFile =
    match platform with
    | Platform.Unix -> "target/MiloneCli/x86_64-unknown-linux-gnu-release/MiloneCli"
    | Platform.Windows -> windowsBinaryPath

  buildSelf ()
  copyFile generatedExeFile destMiloneExe

  match platform with
  | Platform.Unix -> run "strip" [ "-s"; destMiloneExe ]
  | _ -> ()

  // Install .NET executable.
  let runtimeIdentifier =
    match platform with
    | Platform.Unix -> "linux-x64"
    | Platform.Windows -> "win10-x64"

  run
    "dotnet"
    [ "publish"
      "src/MiloneCli"
      "--runtime"
      runtimeIdentifier
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      destMiloneDotnetDir
      "-nologo" ]

  // Install LSP server.
  run
    "dotnet"
    [ "publish"
      "src/MiloneLspServer"
      "--runtime"
      runtimeIdentifier
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      destMiloneLspDir
      "-nologo" ]

  // Copy files.
  copyDir "runtime" destRuntimeDir
  copyDir "milone_libs" destMiloneLibsDir

  // FIXME: Exclude files
  removeFile $"{destRuntimeDir}/milone.o"
  removeFile $"{destRuntimeDir}/milone_platform.o"
  removeDir $"{destMiloneLibsDir}/MiloneStd/bin"
  removeDir $"{destMiloneLibsDir}/MiloneStd/obj"

  // Record version.
  let version =
    runToOut destMiloneExe [ "--version" ]
    |> StringExt.trim

  writeFile destVersionFile $"{version}\n"

  // Info about PATH.
  let underPath =
    try
      runToOut "milone" [ "--version" ] |> ignore
      true
    with
    | _ -> false

  if not underPath then
    printfn "It's recommended to add %s to $PATH." binDir

  printfn "milone-lang v%s is installed successfully!" version

let private doUninstall () : string option =
  let home = getHome ()
  let platform = getPlatform ()
  let ext = getExt platform

  let binDir = $"{home}/bin"
  let miloneHome = $"{home}/.milone"
  let destMiloneExe = $"{binDir}/milone{ext}"
  let destVersionFile = $"{miloneHome}/version"

  let versionOpt =
    readFile destVersionFile
    |> Option.map StringExt.trim

  match versionOpt with
  | Some version ->
    removeFile destMiloneExe
    removeDir miloneHome
    printfn "milone-lang v%s is uninstalled." version

  | None -> ()

  versionOpt

let private commandSelfUninstall () =
  match doUninstall () with
  | None -> printfn "milone-lang is not installed."
  | Some _ -> ()

// -----------------------------------------------
// Deployment
// -----------------------------------------------

let private commandPack () =
  let platform = getPlatform ()
  let ext = getExt platform

  let assetsDir = "scripts/MyBuildTool/assets"

  let workDir =
    let n = tRng.Value.Next()
    $"target/pack-{n}"

  let tempDir = $"{workDir}/milone-X.Y.Z"
  let destBinDir = $"{tempDir}/bin"
  let destMiloneHome = $"{tempDir}/.milone"
  let destMiloneExe = $"{destBinDir}/milone{ext}"
  let destMiloneDotnetDir = $"{destMiloneHome}/bin/milone_dotnet"
  let destMiloneLspDir = $"{destMiloneHome}/bin/milone_lsp"
  let destRuntimeDir = $"{destMiloneHome}/runtime"
  let destMiloneLibsDir = $"{destMiloneHome}/milone_libs"
  let destVersionFile = $"{destMiloneHome}/version"

  // Make structure.
  removeDir workDir
  makeDir destBinDir
  makeDir destMiloneHome

  // Build binary.
  let generatedExeFile =
    match platform with
    | Platform.Unix -> "target/MiloneCli/x86_64-unknown-linux-gnu-release/MiloneCli"
    | Platform.Windows -> windowsBinaryPath

  buildSelf ()
  copyFile generatedExeFile destMiloneExe

  match platform with
  | Platform.Unix -> run "strip" [ "-s"; destMiloneExe ]
  | _ -> ()

  // Record version.
  let version =
    runToOut destMiloneExe [ "--version" ]
    |> StringExt.trim

  writeFile destVersionFile $"{version}\n"

  // Build .NET executable.
  let runtimeIdentifier =
    match platform with
    | Platform.Unix -> "linux-x64"
    | Platform.Windows -> "win10-x64"

  run
    "dotnet"
    [ "publish"
      "src/MiloneCli"
      "--runtime"
      runtimeIdentifier
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      destMiloneDotnetDir
      "-nologo" ]

  // Build LSP server.
  run
    "dotnet"
    [ "publish"
      "src/MiloneLspServer"
      "--runtime"
      runtimeIdentifier
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      destMiloneLspDir
      "-nologo" ]

  // Copy runtime files.
  copyDir "runtime" destRuntimeDir
  copyDir "milone_libs" destMiloneLibsDir
  // FIXME: Exclude files
  removeFile $"{destRuntimeDir}/milone.o"
  removeFile $"{destRuntimeDir}/milone_platform.o"
  removeDir $"{destMiloneLibsDir}/MiloneStd/bin"
  removeDir $"{destMiloneLibsDir}/MiloneStd/obj"

  // Add documents.
  copyFilesTo
    [ "README.md"
      "LICENSE"
      $"{assetsDir}/INSTALL.md"
      $"{assetsDir}/install.ps1"
      $"{assetsDir}/install.sh"
      $"{assetsDir}/uninstall.ps1"
      $"{assetsDir}/uninstall.sh" ]
    tempDir

  // Rename and compress.
  let packDir = $"milone-{version}"

  moveDir tempDir packDir

  let outFile =
    match platform with
    | Platform.Unix ->
      let triple = "x86_64-linux-gnu"

      let outFile =
        $"{workDir}/milone-{version}-{triple}.tar.gz"

      removeFile outFile
      run "tar" [ "-czf"; outFile; packDir ]
      outFile

    | Platform.Windows ->
      let triple = "x86_64-pc-windows-msvc"

      let outFile =
        $"{workDir}/milone-{version}-{triple}.zip"

      removeFile outFile
      System.IO.Compression.ZipFile.CreateFromDirectory(packDir, outFile)
      outFile

  moveDir packDir tempDir

  printfn "%s  %s" (computeFileHash outFile) (Path.GetFileName(outFile))
  printfn "Generated %s" outFile
  printfn "milone-lang v%s is packed successfully!" version

[<EntryPoint>]
let main argv =
  if String.IsNullOrEmpty(Environment.GetEnvironmentVariable("MILONE_HOME")) then
    Environment.SetEnvironmentVariable("MILONE_HOME", Environment.CurrentDirectory)

  match Array.toList argv with
  | []
  | "help" :: _
  | "-h" :: _
  | "--help" :: _ -> printfn "%s" (helpText ())

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ -> printfn "0.1.0"

  | "gen2" :: _ -> commandGen2 ()
  | "gen3" :: _ -> commandGen3 ()

  | "tests" :: _ -> commandTests ()
  | "--build-run-tests" :: args -> commandTestsBuild args
  | "--summarize-tests" :: args -> commandTestsSummarize args

  | "self-install" :: _ -> commandSelfInstall ()
  | "self-uninstall" :: _ -> commandSelfUninstall ()
  | "pack" :: _ -> commandPack ()

  | _ ->
    eprintfn "unknown target: %A" argv
    exit 1

  0
