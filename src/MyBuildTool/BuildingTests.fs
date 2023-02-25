// Testing by building projects in the tests directory.
module internal MyBuildTool.BuildingTests

open System
open System.Diagnostics
open System.IO
open System.Threading
open System.Threading.Tasks
open MyBuildTool.MyShell
open MyBuildTool.Util.IO

let private Cwd = Environment.CurrentDirectory

// #miloneCmdForBuild
let private MiloneCmdLazy: Lazy<string> =
  lazy
    (match Environment.GetEnvironmentVariable("MILONE") with
     | null -> failwith "Expected 'MILONE' environment variable."
     | s -> eprintfn "trace: MILONE='%s'" s; s)

let private Categories =
  [ "edges"; "errors"; "examples"; "features"; "pendings"; "primitives" ]

let private ConcurrencyLevel = 4

// -----------------------------------------------
// Helpers
// -----------------------------------------------

/// Runs asynchronous functions in parallel and waits for all synchronously.
let private runParallel (actions: (unit -> Task<unit>) array) : unit =
  use cts = new CancellationTokenSource()
  let mutable count = 0

  let _ =
    task {
      while not cts.Token.IsCancellationRequested do
        do! Task.Delay(TimeSpan.FromSeconds(3.0), cts.Token)
        eprintf "\r[%d/%d] Running..." count actions.Length
    }

  Parallel.ForEachAsync(
    actions,
    ParallelOptions(MaxDegreeOfParallelism = ConcurrencyLevel),
    Func<_, _, _>(fun action _ ->
      task {
        do! action ()
        Interlocked.Increment(&count) |> ignore
      }
      |> ValueTask)
  )
  |> fun (t: Task) -> t.GetAwaiter().GetResult()

  cts.Cancel()

// -----------------------------------------------
// TestProject
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TestProject =
  {
    ProjectDir: string
    ProjectName: string
    /// (true: positive test to run. false: negative test for compile errors.)
    mutable IsPositive: bool
    mutable ExpectedOutput: string
    mutable ActualOutput: string
  }

  member this.ExpectedOutputPath =
    let projectDir, projectName = this.ProjectDir, this.ProjectName
    $"{projectDir}/{projectName}.output"

  member this.ActualOutputPath =
    let projectDir, projectName = this.ProjectDir, this.ProjectName
    $"{projectDir}/{projectName}.generated.txt"

  member this.ExePath =
    let projectDir, projectName = this.ProjectDir, this.ProjectName
    $"{projectDir}/{projectName}.exe"

// -----------------------------------------------
// Command
// -----------------------------------------------

let internal commandBuildingTests () =
  // Find all test project directories.
  let testProjectDirs =
    [| for category in Categories do
         let categoryDir = $"tests/{category}"

         for projectDir in Directory.GetDirectories(categoryDir) do
           yield projectDir |]

  // Read output files.
  let testProjects: TestProject array =
    [| for projectDir in testProjectDirs do
         let t: TestProject =
           { ProjectDir = projectDir
             ProjectName = basename projectDir
             IsPositive = false
             ExpectedOutput = ""
             ActualOutput = "" }

         match readFile t.ExpectedOutputPath with
         | Some output ->
           t.IsPositive <- output.Contains("milone-lang compile error") |> not
           t.ExpectedOutput <- output.ReplaceLineEndings()
           yield t

         | None -> () |]

  // Split projects into positive ones and negative ones.
  let positiveTests = ResizeArray()
  let negativeTests = ResizeArray()

  for t in testProjects do
    if t.IsPositive then
      positiveTests.Add(t)
    else
      negativeTests.Add(t)

  // Perform tests:
  //
  // - Run all positive tests.
  // - Compile all negative tests.
  [| for t in positiveTests do
       fun () ->
         task {
           let command = MiloneCmdLazy.Value
           let args = [ "run"; t.ProjectDir; "--target-dir"; t.ProjectDir; "-o"; t.ExePath ]

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

           use cts = new CancellationTokenSource()
           let ct = cts.Token
           cts.CancelAfter(TimeSpan.FromSeconds(10.0))

           let mutable cancelled = false

           try
             do! p.WaitForExitAsync(ct)
           with :? OperationCanceledException ->
             eprintfn "error: Project '%s' has been timed out." t.ProjectDir
             eprintfn "stderr:\n%s" (p.StandardError.ReadToEnd())
             p.Kill(entireProcessTree = true)
             cancelled <- true

           let output =
             if cancelled then
               "FATAL: Timeout.\n"
             else
               let s = p.StandardOutput.ReadToEnd()
               let s = if s <> "" && not (s.EndsWith('\n')) then s + "\n" else s
               let line = $"$? = {p.ExitCode}\n"
               $"{s}{line}"

           if p.ExitCode <> 0 then
             eprintfn "error: Project '%s' exited with code %d." t.ProjectDir p.ExitCode
             eprintfn "stderr:\n%s" (p.StandardError.ReadToEnd())

           t.ActualOutput <- output.ReplaceLineEndings()
           do! File.WriteAllTextAsync(t.ActualOutputPath, output)
         }

     for t in negativeTests do
       fun () ->
         task {
           let command = MiloneCmdLazy.Value
           let args = [ "build"; t.ProjectDir; "--target-dir"; t.ProjectDir; "-o"; t.ExePath ]

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

           use cts = new CancellationTokenSource()
           let ct = cts.Token
           cts.CancelAfter(TimeSpan.FromSeconds(10.0))

           let mutable cancelled = false

           try
             do! p.WaitForExitAsync(ct)
           with :? OperationCanceledException ->
             eprintfn "error: Project '%s' has been timed out." t.ProjectDir
             eprintfn "stderr:\n%s" (p.StandardError.ReadToEnd())
             p.Kill(entireProcessTree = true)
             cancelled <- true

           let mutable output = ""

           if cancelled then
             output <- "Error: Timeout.\n"
           else if p.ExitCode = 0 then
             output <- "Error: Unexpectedly successful.\n"
             eprintfn "error: Project '%s' unexpectedly passed checking.\n" t.ProjectDir
           else
             output <- "milone-lang compile error.\n"
             let code = p.StandardOutput.ReadToEnd()
             do! File.WriteAllTextAsync($"{t.ProjectDir}/{t.ProjectName}.c", code)

           t.ActualOutput <- output.ReplaceLineEndings()
           do! File.WriteAllTextAsync(t.ActualOutputPath, output)
         } |]
  |> runParallel

  // Diff results.
  let mutable pass = 0
  let mutable fail = 0

  for t in testProjects do
    if t.ActualOutput = t.ExpectedOutput then
      pass <- pass + 1
    else
      eprintfn "error: Test '%s' output differs" t.ProjectDir
      fail <- fail + 1

  // Show summary.
  let successful = pass <> 0 && fail = 0
  printfn "pass %d / fail %d / total %d" pass fail (pass + fail)
  printfn "%s" (if successful then "OK" else "FAILED")

  exit (if successful then 0 else 1)
