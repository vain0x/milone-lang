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

build {{ EXE_FILE }}: $
  testing_run_cc $
    {{ NINJA_FILE }} $
    | runtime/milone.h $
      runtime/milone.o
  expected_out_file = {{ EXPECTED_OUT_FILE }}
  out_file = {{ OUT_FILE }}
  project = tests/{{ CATEGORY }}/{{ PROJECT }}

build {{ OUT_FILE }}: $
  execute_test {{ EXE_FILE }}
  expected_out_file = {{ EXPECTED_OUT_FILE }}
  project = tests/{{ CATEGORY }}/{{ PROJECT }}

build {{ DIFF_FILE }}: $
  diff_test_output $
    {{ OUT_FILE }} $
    tests/{{ CATEGORY }}/{{ PROJECT }}/{{ PROJECT }}.out
  name = {{ PROJECT }}

build target/tests/{{ CATEGORY }}/{{ PROJECT }}/test.timestamp: $
  verify_test_output {{ DIFF_FILE }}
  pool = console

build {{ PROJECT }}: $
  phony target/tests/{{ CATEGORY }}/{{ PROJECT }}/test.timestamp
  pool = console
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

build {{ DIFF }}: $
  diff {{ GENERATED_OUT }} {{ EXPECTED_OUT }}

build {{ PROJECT }}: should_empty {{ DIFF }}
"""



let renderTestCaseBuildStatements category projectName =
  let file ext =
    sprintf "tests/%s/%s/%s%s" category projectName projectName ext

  buildTemplate
    .Replace("{{ CATEGORY }}", category)
    .Replace("{{ PROJECT }}", projectName)
    .Replace("{{ FS_FILE }}", file ".fs")
    .Replace("{{ EXPECTED_OUT_FILE }}", file ".out")
    .Replace("{{ DIFF_FILE }}", file ".generated.diff")
    .Replace("{{ EXE_FILE }}", file ".generated.exe")
    .Replace("{{ NINJA_FILE }}", file ".generated.ninja")
    .Replace("{{ OUT_FILE }}", file ".generated.out")

// -----------------------------------------------

let render () =
  let solutionDir = System.Environment.CurrentDirectory
  let fsProjects = FS.allFsProjects solutionDir
  let testProjects = FS.allTestProjects solutionDir

  let ninjaTemplate = File.ReadAllText("build-template.ninja")

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



  ninjaTemplate
    .Replace("{{ FSPROJ_FILES }}", fsProjects |> List.map fst |> String.concat " ")
    .Replace(
      "{{ MILONE_CLI_SRC }}",
      fsProjects
      |> List.collect (fun (x, xs) -> x :: xs)
      |> String.concat " "
    )
    .Replace("{{ TEST }}", test)
