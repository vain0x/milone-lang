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
"""

let private makeDir (dir: string) =
  Directory.CreateDirectory(dir) |> ignore

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

let private run command args =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  let p = Process.Start(startInfo)
  p.WaitForExit()

  if p.ExitCode <> 0 then
    eprintfn "ERROR: '%s' %A exited with %d." command args p.ExitCode
    exit 1

let private runToOut command args =
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

let private commandGen2 () =
  eprintfn "milone-compiling gen2"
  makeDir "target/gen2"

  let stdOut =
    runToOut
      "dotnet"
      [ "run"
        "-p"
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

  w $"build target/milone: link_objs_to_exe runtime/milone.o {input}"

  writeTo (ninja.ToString()) "target/gen2/build.ninja"

  eprintfn "c-compiling gen2"

  run
    "bin/ninja"
    [ "-f"
      "target/gen2/build.ninja"
      "target/milone" ]

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

    w $"build {exe}: link_objs_to_exe runtime/milone.o {input}"

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

[<EntryPoint>]
let main argv =
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

  | _ ->
    eprintfn "unknown target: %A" argv
    exit 1

  0
