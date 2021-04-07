// Instantiate `build-template.ninja`.

module rec MyBuildTool.InstantiateBuildTemplateNinja

open System.IO
open System.Text

module FS = MyBuildTool.FileSearch

type TestProject =
  { ProjectDir: string
    CategoryDir: string
    CategoryName: string
    ProjectName: string
    TargetDir: string
    Exe: string
    FilesTxt: string
    ErrorTxt: string
    ExpectedOut: string
    GeneratedOut: string
    Sources: string list }

let testProject (categoryDir: string, projectDir, projectName, sources) =
  let categoryName = Path.GetFileName(categoryDir)

  let targetDir =
    $"target/tests/{categoryName}/{projectName}"

  { CategoryDir = categoryDir
    ProjectDir = projectDir
    CategoryName = categoryName
    ProjectName = projectName
    TargetDir = targetDir
    FilesTxt = $"{targetDir}/files.txt"
    Exe = $"{targetDir}/{projectName}.exe"
    ExpectedOut = $"{projectDir}/{projectName}.out"
    ErrorTxt = $"{projectDir}/{projectName}_error.txt"
    GeneratedOut = $"{targetDir}/generated.txt"
    Sources = sources }

let render () =
  let solutionDir = System.Environment.CurrentDirectory
  let fsProjects = FS.allFsProjects solutionDir
  let testProjects = FS.allTestProjects solutionDir

  let myBuildToolInput =
    seq {
      for proj, src in fsProjects do
        if proj.StartsWith("scripts/MyBuildTool") then
          yield proj
          yield! src
    }
    |> String.concat " "

  let miloneCliInput =
    seq {
      for proj, src in fsProjects do
        if
          proj.StartsWith("src")
          || proj.StartsWith("milone_libs")
        then
          yield proj
          yield! src
    }
    |> String.concat " "

  let runTests, errorTests =
    let readExpectedOutput t =
      let _, projectDir, name, _ = t
      let path = sprintf "%s/%s.out" projectDir name

      try
        if File.Exists(path) then
          File.ReadAllText(path) |> Some
        else
          None
      with _ -> None

    testProjects
    |> List.choose
         (fun t ->
           match readExpectedOutput t with
           | None ->
               let _, projectDir, _, _ = t
               eprintfn "warn: '%s' skipped." projectDir
               None

           | Some output ->
               let shouldRun =
                 output.Contains("milone-lang compile error.")
                 |> not

               Some(shouldRun, t))
    |> List.partition fst
    |> (fun (x, y) -> List.map (snd >> testProject) x, List.map (snd >> testProject) y)

  let ninja = StringBuilder()
  let w (s: string) = ninja.AppendLine(s) |> ignore

  w
    """
builddir = target/tests
timestamp = target/.timestamp

my_build_tool = scripts/MyBuildTool/bin/Debug/net5.0/MyBuildTool
milone_dotnet = src/MiloneCli/bin/Debug/net5.0/MiloneCli

rule build_my_build_tool
  description = build_my_build_tool
  command = dotnet build -nologo scripts/MyBuildTool

rule build_milone_dotnet
  description = build_milone_dotnet
  command = dotnet build -nologo src/MiloneCli
"""

  w $"build $my_build_tool: build_my_build_tool {myBuildToolInput}"
  w $"build $milone_dotnet: build_milone_dotnet {miloneCliInput}"

  for t in runTests do
    let id =
      $"tests_{t.CategoryName}_{t.ProjectName}"

    let src = String.concat " " t.Sources

    w
      $"""
# ------------------------------------------------
# {t.ProjectDir} (run)
# ------------------------------------------------
rule {id}_build
  description = milone {t.ProjectDir}
  command = target/milone compile {t.ProjectDir} --target-dir {t.TargetDir} >$out
build {t.FilesTxt}: $
  {id}_build $
    | {src} $
      {t.ExpectedOut} $
      target/milone
rule {id}_run
  description = run {t.ProjectDir}
  command = {{ {t.Exe}; echo '$$? = '$$?; }} >$out
build {t.GeneratedOut}: $
  {id}_run $
    | {t.ExpectedOut} $
      {t.Exe}"""

  for t in errorTests do
    let id =
      $"tests_{t.CategoryName}_{t.ProjectName}"

    let src = String.concat " " t.Sources

    w
      $"""
# ------------------------------------------------
# {t.ProjectDir} (error)
# ------------------------------------------------
rule {id}_build
  description = ! milone {t.ProjectDir}
  command = $
    if target/milone compile {t.ProjectDir} --target-dir {t.TargetDir} >{t.ProjectDir}/{t.ProjectName}.c; then $
      echo 'Unexpectedly compilation succeeded.' >$out; $
    else $
      echo 'milone-lang compile error.' >$out; $
    fi

build {t.GeneratedOut}: $
  {id}_build $
    | {src} $
      {t.ExpectedOut} $
      target/milone"""

  let exeFiles =
    runTests
    |> List.map (fun (t: TestProject) -> t.Exe)
    |> String.concat " "

  let generatedOuts =
    runTests
    |> List.map (fun (t: TestProject) -> t.GeneratedOut)
    |> String.concat " "

  let runTestInputs =
    runTests
    |> List.collect (fun (t: TestProject) -> t.ExpectedOut :: t.FilesTxt :: t.Sources)
    |> String.concat " "

  let runTestProjectDirs =
    runTests
    |> Seq.map (fun (t: TestProject) -> t.ProjectDir)
    |> String.concat " "

  let testProjectDirs =
    (runTestProjectDirs
     :: List.map (fun (t: TestProject) -> t.ProjectDir) errorTests)
    |> String.concat " "

  w
    $"""
# ------------------------------------------------
# Tests
# ------------------------------------------------

rule build_run_tests
  description = build_run_tests
  command = $
    $my_build_tool --build-run-tests {runTestProjectDirs} && $
    ninja -f target/tests2-build.ninja
build {exeFiles}: $
  build_run_tests $
    | $my_build_tool runtime/milone.o runtime/milone.h $
      {runTestInputs}
  pool = console
rule summarize_tests
  description = summarize_tests
  command = $my_build_tool --summarize-tests {testProjectDirs} && touch $out
build target/.timestamp/summarize_tests: $
  summarize_tests $
    | {exeFiles} $my_build_tool {generatedOuts}
build tests: phony target/.timestamp/summarize_tests"""

  ninja.ToString()
