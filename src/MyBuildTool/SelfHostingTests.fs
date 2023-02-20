// Testing by running the self-hosted compiler to verify the generated code equality.
module internal MyBuildTool.SelfHostingTests

open System
open System.Diagnostics
open System.IO
open System.Threading
open System.Threading.Tasks
open MyBuildTool.MyShell
open MyBuildTool.PlatformInfo

let private Cwd = Environment.CurrentDirectory

// #miloneCmdForBuild
let private MiloneCmd =
  match Environment.GetEnvironmentVariable("MILONE") with
  | null -> $"{Cwd}/target/MiloneCli/milone{Platform.ExeExt}"
  | s -> s

// -----------------------------------------------
// Command
// -----------------------------------------------

let internal commandSelfHostingTests () =
  task {
    // Run compiler.
    let mutable stdOut = ""

    let command = MiloneCmd
    let args = [ "build"; "src/MiloneCli"; "--target-dir"; "target/gen3" ]

    use p =
      let startInfo =
        let si = ProcessStartInfo(command)
        si.RedirectStandardOutput <- true
        si.RedirectStandardError <- true
        si.UseShellExecute <- false

        for arg in args do
          si.ArgumentList.Add(arg)

        si.EnvironmentVariables.Add("MILONE_HOME", Cwd)
        si

      Process.Start(startInfo)

    do! p.WaitForExitAsync(CancellationToken())

    stdOut <- p.StandardOutput.ReadToEnd()

    // Compare code.
    let mutable ok = true

    for name in stdOut.Split("\n") do
      let name = Path.GetFileNameWithoutExtension(name.Trim())

      if name <> "" then
        let c2 = $"target/MiloneCli/{name}.c"
        let c3 = $"target/gen3/{name}.c"

        if not (File.Exists(c2)) && not (File.Exists(c3)) then
          // Pass. This happens for 'milone.c' etc.
          ok <- true
        else if readToDiff c2 <> readToDiff c3 then
          printfn $"differ: {c2} vs {c3}"
          ok <- true

    if ok then
      printfn "OK"
    else
      printfn "FAIL"
      exit 1
  }
  |> fun (t: Task<_>) -> t.GetAwaiter().GetResult()
