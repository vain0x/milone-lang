module rec GenNinjaFile.Program

open System
open System.IO

// let private stripPrefix (prefix: string) (s: string) =
//   if s.StartsWith(prefix) then s.[prefix.Length..s.Length - 1] else s

let private pathIsOk (filePath: string) =
  let fileName = Path.GetFileName(filePath)

  match fileName with
  | "bin"
  | "obj"
  | "node_modules"
  | "target" -> false
  | _ ->
      not (fileName.StartsWith("."))
      && not (fileName.Contains("~"))

let private extIs ext (s: string) = Path.GetExtension(s) = ext

let private extIsSrc (s: string) =
  match Path.GetExtension(s) with
  | ".fs"
  | ".fsproj"
  | ".milone" -> true
  | _ -> false

let private findFiles pred (rootDir: string) =
  let rec go dir =
    seq {
      if pathIsOk dir then
        for entry in IO.Directory.GetDirectories(dir) do
          yield! go entry

        for entry in Directory.GetFiles(dir) do
          if pred entry then entry
    }

  go rootDir

let private findTestProjects testsDir =
  [| for category in IO.Directory.GetDirectories(testsDir) do
       // features, examples, etc.
       let category = Path.GetFileName(category)
       let categoryDir = Path.Combine(testsDir, category)

       for projectName in IO.Directory.GetDirectories(categoryDir) do
         let projectName = Path.GetFileName(projectName)

         if pathIsOk projectName then
           yield category, projectName |]

let private generate (solutionDir: string) (ninjaTemplate: string) =
  let testsDir = solutionDir + "/tests"

  let miloneCoreSrc =
    findFiles extIsSrc (solutionDir + "/milone_libs/MiloneCore")
    |> Seq.toList

  let miloneStdSrc =
    findFiles extIsSrc (solutionDir + "/milone_libs/MiloneStd")
    |> Seq.toList

  let miloneLangSrc =
    findFiles extIsSrc (solutionDir + "/MiloneLang")
    |> Seq.toList

  let ninjaTemplate =
    TemplateSelfCompilation.templateSelfCompilation
      { MiloneCoreSrc = miloneCoreSrc
        MiloneStdSrc = miloneStdSrc
        MiloneLangSrc = miloneLangSrc
        NinjaTemplate = ninjaTemplate }

  let testProjects = findTestProjects testsDir

  let testCFiles =
    testProjects
    |> Array.map (fun (category, project) -> sprintf "tests/%s/%s/%s.c" category project project)
    |> String.concat " "

  let testDiffFiles =
    testProjects
    |> Array.map (fun (category, project) -> sprintf "tests/%s/%s/%s.generated.diff" category project project)
    |> String.concat " "

  let testBuilds =
    seq {
      for category, projectName in testProjects do
        TemplateTestCase.renderTestCaseBuildStatements category projectName
    }
    |> String.concat "\n"

  ninjaTemplate
    .Replace("{{ FS_PROJ_FILES }}",
             findFiles (extIs ".fsproj") solutionDir
             |> String.concat " ")
    .Replace("{{ MILONE_CORE_SRC }}", miloneCoreSrc |> String.concat " ")
    .Replace("{{ MILONE_STD_SRC }}", miloneStdSrc |> String.concat " ")
    .Replace("{{ MILONE_LANG_SRC }}", miloneLangSrc |> String.concat " ")
    .Replace("{{ TEST_C_FILES }}", testCFiles)
    .Replace("{{ TEST_DIFF_FILES }}", testDiffFiles)
    .Replace("{{ TEST_BUILDS }}", testBuilds)

[<EntryPoint>]
let main argv =
  match argv with
  | [| solutionDir |] ->
      let ninjaTemplate = stdin.ReadToEnd()
      let output = generate solutionDir ninjaTemplate
      printf "%s" output
      0

  | _ ->
      eprintfn "USAGE: <command> path/to/tests"
      1
