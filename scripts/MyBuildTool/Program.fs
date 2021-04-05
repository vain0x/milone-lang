module rec MyBuildTool.Program

open System
open System.Diagnostics
open System.IO
open System.Text

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

  | "gen2" :: _ ->

    let startInfo = ProcessStartInfo("dotnet")
    startInfo.ArgumentList.Add("run")
    startInfo.ArgumentList.Add("-p")
    startInfo.ArgumentList.Add("src/MiloneCli")
    startInfo.ArgumentList.Add("--")
    startInfo.ArgumentList.Add("compile")
    startInfo.ArgumentList.Add("src/MiloneCli")
    startInfo.ArgumentList.Add("--target-dir")
    startInfo.ArgumentList.Add("target/gen2")
    startInfo.RedirectStandardOutput <- true
    startInfo.UseShellExecute <- false
    let p = Process.Start(startInfo)
    p.WaitForExit()
    let stdOut = p.StandardOutput.ReadToEnd()

    eprintfn "out = %A, %d" (stdOut) p.ExitCode
    0

  | "milone" :: projectDir :: envs ->
      let _, map =
        envs
        |> List.fold
             (fun (parity, map) (e: string) ->
               if parity = 0 then
                 if e = "-e" then
                   1, map
                 else
                   failwithf "Expected -e, %A" e
               else
                 match e.Split("=")
                       |> Array.map (fun (s: string) -> s.Trim()) with
                 | [| name; value |] -> 0, Map.add name value map
                 | _ -> failwithf "invalid env %A" e)
             (0, Map.empty)

      let env (name: string) =
        match Map.tryFind name map with
        | Some it -> it
        | None ->
            match Environment.GetEnvironmentVariable(name) with
            | null
            | "" ->
                match name with
                | "MILONE_HOME" ->
                    Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)
                    + "/.milone"
                | "MILONE" -> "milone"
                | "EXE" -> "a.out"
                | "VERBOSITY" -> "--quiet"
                | "TARGET_DIR" -> "target"
                | _ -> failwithf "env missing %A" name
            | it -> it

      eprintfn "projectDir=%s map=%A" projectDir map



      // $my_build_tool milone src/MiloneCli $
      //   -e MILONE_HOME=$$PWD $
      //   -e MILONE=$milone_dotnet_debug $
      //   -e EXE=$out $
      //   -e TARGET_DIR=target/gen2 $
      //   -e VERBOSITY=$verbosity $
      //   >$target_dir/build.ninja && $
      0

  | "milone-delete-c-files" :: targetDir -> 0

  | "--build-run-tests" :: _ ->
      printfn "summarize-tests"
      0

  | "--summarize-tests" :: _ ->
      printfn "summarize-tests"
      0

  | targets ->
      // Stage 1: Install 'bin/ninja'.
      // FIXME: impl

      // Stage 2: Generate the default 'build.ninja'.
      // let workspaceDir = Environment.CurrentDirectory
      // let fsProjects = FS.allFsProjects workspaceDir
      // let testProjects = FS.allTestProjects workspaceDir

      // let stage2 () =
      //   let input =
      //     [ yield "build-template.ninja"

      //       for projectFile, sourceFiles in fsProjects do
      //         yield projectFile
      //         yield! sourceFiles

      //       for _, projectDir, _, _ in testProjects do
      //         yield projectDir ]

      //   let output = "target/build-meta.ninja"

      //   let ninjaTemplate = File.ReadAllText("build-template.ninja")

      //   output |> writeTo (InstantiateBuildTemplateNinja.render ())

      // Stage 3: Run ninja-1.

      // Stage 4: Re-run ninja-2.

      printfn "%s" (InstantiateBuildTemplateNinja.render ())
      0
