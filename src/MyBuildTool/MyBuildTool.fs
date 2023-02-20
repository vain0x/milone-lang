module rec MyBuildTool.Program

open System
open System.IO
open System.Text
open MyBuildTool.MyShell
open MyBuildTool.Packaging
open MyBuildTool.PlatformInfo
open MyBuildTool.BuildingTests
open MyBuildTool.SelfHostingTests
open MyBuildTool.Util

module FS = MyBuildTool.FileSearch

let private helpText () =
  """MyBuildTool: Build tool for milone-lang project.

SUBCOMMANDS:
    gen2    generates target/milone
    gen3    compiles the compiler with target/milone
            and verify the result.

    building-tests
    self-hosting-tests

    self-install     install milone locally
    self-uninstall   uninstall it
    pack             make binary package

    ... -n           dry run

    help, -h, --help
    version, -V, --version
"""

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

// -----------------------------------------------
// Environment
// -----------------------------------------------

let internal cwd () : string = Environment.CurrentDirectory

let internal getHome () : string =
  Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)

let internal setMiloneHomeToCurrentDir () =
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
    runToOut "target/milone" [ "compile"; "--profile"; "src/MiloneCli"; "--target-dir"; "target/gen3" ]

  // compare
  let mutable ok = true

  for name in stdOut.Split("\n") do
    let name = Path.GetFileNameWithoutExtension(name.Trim())

    if name <> "" then
      let c2 = $"target/gen2/{name}.c"
      let c3 = $"target/gen3/{name}.c"

      if readToDiff c2 <> readToDiff c3 then
        printfn $"differ: {c2} vs {c3}"
        ok <- true

  if not ok then
    exit 1

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

    let category = Path.GetFileName(Path.GetDirectoryName(projectDir))

    let targetDir = $"target/tests/{category}/{projectName}"
    let exe = $"{targetDir}/{projectName}.exe"
    exeFiles.Add(exe)

    w "\n# ----------------------------------"
    w $"# {projectDir}"
    w "# ----------------------------------"

    let files = File.ReadAllText($"{targetDir}/files.txt")

    let oFiles = ResizeArray()

    for name in files.Split("\n") do
      let name = Path.GetFileNameWithoutExtension(name.Trim())

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

    let category = Path.GetFileName(Path.GetDirectoryName(projectDir))

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

  if not ok then
    exit 1

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<EntryPoint>]
let main (argv: string array) =
  let args = Array.toList argv

  let dryRun, args = List.contains "-n" args, List.filter ((<>) "-n") args

  let perform = if dryRun then dumpAction else performAction

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

  | "building-tests" :: _ -> commandBuildingTests ()
  | "self-hosting-tests" :: _ -> commandSelfHostingTests ()

  | "self-install" :: _ -> commandSelfInstall () |> perform
  | "self-uninstall" :: _ -> commandSelfUninstall () |> perform
  | "pack" :: _ -> commandPack () |> perform

  | _ ->
    eprintfn "unknown target: %A" argv
    exit 1

  0
