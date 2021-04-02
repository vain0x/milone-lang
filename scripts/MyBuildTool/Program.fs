module rec MyBuildTool.Program

open System
open System.IO

module FS = MyBuildTool.FileSearch

let private helpText () =
  """MyBuildTool: Build tool for milone-lang project."""

let binNinja = "bin/ninja"

let entities = "fsproj"

let private gen1Bin =
  "src/MiloneCli/bin/Debug/net5.0/MiloneCli"

let private gen2Bin = "target/milone"

let private writeTo (contents: string) (output: string) =
  let same =
    try
      File.Exists(output)
      && File.ReadAllText(output) = contents
    with _ -> false

  if not same then
    File.WriteAllText(output, contents)

[<EntryPoint>]
let main argv =
  match Array.toList argv with
  | []
  | "help" :: _
  | "-h" :: _
  | "--help" :: _ ->
      printfn "%s" (helpText ())
      0

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ ->
      printfn "0.1.0"
      0

  | "subtask" :: targets -> exit 0

  | targets ->
      // Stage 1: Install 'bin/ninja'.
      // FIXME: impl

      // Stage 2: Generate the default 'build.ninja'.
      let workspaceDir = Environment.CurrentDirectory
      let fsProjects = FS.allFsProjects workspaceDir
      let testDirs = FS.allTestDirs workspaceDir

      let stage2 () =
        let input =
          [ yield "build-template.ninja"

            for projectFile, sourceFiles in fsProjects do
              yield projectFile
              yield! sourceFiles

            yield! testDirs ]

        let output = "target/build-meta.ninja"

        let ninjaTemplate = File.ReadAllText("build-template.ninja")

        output |> writeTo InstantiateBuildTemplateNinja.render
          output
          """
            builddir = target/build-meta

            rule generate
                dotnet run -p scripts/MyBuildTool -- subtask build.ninja

            default build.ninja
        """

      // Stage 3: Run ninja-1.

      // Stage 4: Re-run ninja-2.


      0
