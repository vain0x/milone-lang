module MiloneTest.Program

open System
open System.IO
open MiloneLang.Cli
open MiloneLang.Program

let private writeAllText filename contents =
  let identical =
    try
      File.Exists filename
      && File.ReadAllText filename = contents
    with _ -> false

  if not identical then File.WriteAllText(filename, contents)

let private findSolutionDir () =
  let rec go (dir: string) =
    if File.Exists(Path.Combine(dir, "milone_lang.sln"))
    then dir
    else Path.GetDirectoryName(dir) |> go

  go Environment.CurrentDirectory

let private getProjectDir testsDir category project =
  Path.Combine(testsDir, category, project)

let private doTestCase solutionDir testsDir (errors: ResizeArray<_>) (category, project) =
  let projectDir = getProjectDir testsDir category project

  let outputFilename = Path.Combine(projectDir, project + ".c")

  let exeFilename =
    Path.Combine(testsDir, category, project, project + ".generated.exe")

  // Compile.
  let host = dotnetCliHost [] solutionDir

  let contents, success = build host Quiet projectDir
  if success then writeAllText outputFilename contents

let private buildProject solutionDir testsDir (category, project) =
  let projectDir = getProjectDir testsDir category project

  let ccArgs =
    [| "-std=c11"
       "-O2"
       "-Wall"
       "-Wno-unused-variable"
       "-Wno-unused-but-set-variable"
       "-Wno-unused-label"
       "-I"
       Path.Combine(solutionDir, "boot/runtime")
       Path.Combine(projectDir, project + ".c")
       "-o"
       exeFilename |]

  let p =
    let startInfo = Diagnostics.ProcessStartInfo()

    startInfo.FileName <- "gcc"
    startInfo.WorkingDirectory <- projectDir

    ccArgs |> Array.iter startInfo.ArgumentList.Add

    Diagnostics.Process.Start(startInfo)

  let ok = p.WaitForExit(5 * 1000)
  if not ok
  then errors.Add(sprintf "%s/%s: Compile with GCC time out." category project)

let collectTestCases testsDir (filter: string) =
  [| for category in Directory.GetDirectories(testsDir) do
       // features, examples, etc.
       let category = Path.GetFileName(category)
       let categoryDir = Path.Combine(testsDir, category)
       for project in IO.Directory.GetDirectories(categoryDir) do
         let project = Path.GetFileName(project)
         if project.Contains(filter) then category, project |]

let runCompileGen1 solutionDir testsDir testCases =
  System.Threading.Tasks.Parallel.ForEach(Seq.ofArray testCases, compileProject solutionDir testsDir)
  |> ignore

let runExecuteGen1 solutionDir testsDir testCases =
  let errors = ResizeArray()

  System.Threading.Tasks.Parallel.ForEach(Seq.ofArray testCases, buildProject solutionDir testsDir errors)
  |> ignore

  errors

[<EntryPoint>]
let main args =
  let filter =
    if args.Length >= 1 then args.[0] else ""

  let solutionDir = findSolutionDir ()
  let testsDir = Path.Combine(solutionDir, "boot/tests")
  let testCases = collectTestCases testsDir filter

  runCompileGen1 solutionDir testsDir testCases

  let errors =
    runExecuteGen1 solutionDir testsDir testCases

  if errors.Count <> 0 then
    for e in errors do
      eprintfn "%s" e
    exit 1

  printfn "OK: %d." testCases.Length
  0
