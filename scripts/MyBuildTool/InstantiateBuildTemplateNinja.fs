// Instantiate `build-template.ninja`.

module rec MyBuildTool.InstantiateBuildTemplateNinja

open System.IO

module FS = MyBuildTool.FileSearch

// -----------------------------------------------
// tests
// -----------------------------------------------

let runTestTemplate = """
# ------------------------------------------------
# {{ PATH }} (run)
# ------------------------------------------------

rule {{ MILONE_RULE }}
  description = milone {{ PATH }}
  command = target/milone compile {{ PATH }} --target-dir {{ TARGET_DIR }} >$out

build {{ FILES_TXT }}: $
  {{ MILONE_RULE }} $
    | {{ SRC }} $
      {{ EXPECTED_OUT }} $
      target/milone

rule {{ MILONE_RULE }}_run
  description = run_tests run {{ PROJECT }}
  command = { {{ EXE }}; echo '$$? = '$$?; } >$out

build {{ GENERATED_OUT }}: $
  {{ MILONE_RULE }}_run $
    | {{ EXPECTED_OUT }} $
      {{ EXE }}
"""

let errorTestTemplate = """
# ------------------------------------------------
# {{ PATH }} (error)
# ------------------------------------------------

rule {{ MILONE_RULE }}
  description = milone {{ PATH }}
  command = ! target/milone compile {{ PATH }} --target-dir {{ TARGET_DIR }} >$out

build {{ GENERATED_OUT }}: $
  {{ MILONE_RULE }} $
    | {{ SRC }} $
      {{ EXPECTED_OUT }} $
      target/milone
"""

let testCollectionTemplate = """
# ------------------------------------------------
# Tests
# ------------------------------------------------

rule build_run_tests
  description = build_run_tests
  command = $my_build_tool --build-run-tests

build {{ EXE_FILES }}: $
  build_run_tests | {{ RUN_TEST_INPUTS }}

build run_tests: $
  phony {{ EXE_FILES }}

build error_tests: $
  phony {{ ERROR_TEST_INPUTS }}



rule summarize_tests
  description = summarize_tests
  command = $my_build_tool --summarize-tests

build target/summarize_tests.timestamp: $
  summarize_tests $
    | run_tests error_tests

build tests: phony target/summarize_tests.timestamp
"""

// -----------------------------------------------

type TestProject =
  { ProjectDir: string
    CategoryDir: string
    CategoryName: string
    ProjectName: string
    TargetDir: string
    Exe: string
    FilesTxt: string
    ExpectedOut: string
    GeneratedOut: string
    Sources: string list }

let testProject (categoryDir: string, projectDir, projectName, sources) =
  let categoryName = Path.GetFileName(categoryDir)
  let targetDir = $"target/{categoryName}/{projectName}"

  { CategoryDir = categoryDir
    ProjectDir = projectDir
    CategoryName = categoryName
    ProjectName = projectName
    TargetDir = targetDir
    FilesTxt = $"{targetDir}/files.txt"
    Exe = $"{targetDir}/{projectName}.exe"
    ExpectedOut = $"{projectDir}/{projectName}.out"
    GeneratedOut = $"{targetDir}/generated.txt"
    Sources = sources }

let render () =
  let solutionDir = System.Environment.CurrentDirectory
  let fsProjects = FS.allFsProjects solutionDir
  let testProjects = FS.allTestProjects solutionDir

  let ninjaTemplate = File.ReadAllText("build-template.ninja")

  let ninjaTemplate =
    ninjaTemplate
      .Replace("{{ FS_PROJ_FILES }}", List.map fst fsProjects |> String.concat " ")
      .Replace(
        "{{ MILONE_CLI_SRC }}",
        fsProjects
        |> List.collect snd
        |> String.concat " "
      )

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

  let test =
    runTests
    |> List.map
         (fun (t: TestProject) ->
           runTestTemplate
             .Replace("{{ PATH }}", t.ProjectDir)
             .Replace("{{ PROJECT }}", t.ProjectName)
             .Replace("{{ MILONE_RULE }}", t.ProjectName + "_build")
             .Replace("{{ SRC }}", String.concat " " t.Sources)
             .Replace("{{ TARGET_DIR }}", t.TargetDir)
             .Replace("{{ EXE }}", t.Exe)
             .Replace("{{ EXPECTED_OUT }}", t.ExpectedOut)
             .Replace("{{ FILES_TXT }}", t.FilesTxt)
             .Replace("{{ GENERATED_OUT }}", t.GeneratedOut))
    |> fun items ->
         List.append
           items
           (errorTests
            |> List.map
                 (fun (t: TestProject) ->
                   errorTestTemplate
                     .Replace("{{ PATH }}", t.ProjectDir)
                     .Replace("{{ PROJECT }}", t.ProjectName)
                     .Replace("{{ MILONE_RULE }}", t.ProjectName + "_build")
                     .Replace("{{ SRC }}", String.concat " " t.Sources)
                     .Replace("{{ TARGET_DIR }}", t.TargetDir)
                     .Replace("{{ GENERATED_OUT }}", t.GeneratedOut)
                     .Replace("{{ EXPECTED_OUT }}", t.ExpectedOut)))
    |> String.concat "\n"

  let collect =
    let exeFiles =
      runTests
      |> List.map (fun (t: TestProject) -> t.Exe)
      |> String.concat " "

    let runTestInputs =
      runTests
      |> List.collect (fun (t: TestProject) -> t.ExpectedOut :: t.Sources)
      |> String.concat " "

    let errorTestInputs =
      errorTests
      |> List.collect (fun (t: TestProject) -> t.ExpectedOut :: t.Sources)
      |> String.concat " "

    testCollectionTemplate
      .Replace("{{ EXE_FILES }}", exeFiles)
      .Replace("{{ RUN_TEST_INPUTS }}", runTestInputs)
      .Replace("{{ ERROR_TEST_INPUTS }}", errorTestInputs)

  ninjaTemplate
    .Replace("{{ FSPROJ_FILES }}", fsProjects |> List.map fst |> String.concat " ")
    .Replace(
      "{{ MILONE_CLI_SRC }}",
      fsProjects
      |> List.collect (fun (x, xs) -> x :: xs)
      |> String.concat " "
    )
    .Replace("{{ TEST }}", test + "\n" + collect)
