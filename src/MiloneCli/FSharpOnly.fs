module rec MiloneCli.FSharpOnly

open Std.StdError
open MiloneShared.UtilParallel
open MiloneShared.UtilProfiler
open MiloneCli.Cli

let private dirCreate (baseDir: string) (dir: string) =
  try
    let dir = System.IO.Path.Combine(baseDir, dir)
    System.IO.Directory.CreateDirectory(dir) |> ignore
    true
  with
  | _ -> false

let private readFile (filePath: string) : Future<string option> =
  try
    if System.IO.File.Exists(filePath) then
      System.IO.File.ReadAllTextAsync(filePath)
      |> Future.ofTask
      |> Future.map Some
    else
      Future.just None
  with
  | _ -> Future.just None

let private writeFile (filePath: string) (contents: string) : unit =
  let readFile filePath =
    if System.IO.File.Exists(filePath) then
      System.IO.File.ReadAllText(filePath) |> Some
    else
      None

  try
    match readFile filePath with
    | Some it when it = contents -> ()
    | _ -> System.IO.File.WriteAllText(filePath, contents)
  with
  | ex ->
    eprintfn "Couldn't write to file '%s'. '%s'" filePath ex.Message
    reraise ()

let private runCommand (command: string) (args: string list) : int =
  let p =
    System.Diagnostics.Process.Start(command, args)

  p.WaitForExit()
  p.ExitCode

let private executeInto (cmd: string) : never =
  try
    let p =
      System.Diagnostics.Process.Start("/bin/sh", [ "-c"; cmd ])

    p.WaitForExit()
  with
  | _ ->
    eprintfn "error: executeInto '%s'" cmd
    reraise ()

  exit 0

let private getPlatform () : Platform =
  match System.Environment.OSVersion.Platform with
  | System.PlatformID.Win32NT ->
    let w: WindowsApi =
      { NewGuid = fun () -> System.Guid.NewGuid().ToString()
        RunCommand = runCommand }

    Platform.Windows w

  | _ ->
    let l: LinuxApi = { ExecuteInto = executeInto }
    Platform.Linux l

let dotnetCliHost () : CliHost =
  let args =
    System.Environment.GetCommandLineArgs()
    |> Array.toList

  let home =
    System.Environment.GetFolderPath(System.Environment.SpecialFolder.UserProfile)

  let miloneHome =
    match System.Environment.GetEnvironmentVariable("MILONE_HOME") with
    | null
    | "" -> None
    | it -> Some it

  { Args = args
    WorkDir = System.Environment.CurrentDirectory
    Home = home
    MiloneHome = miloneHome
    Platform = getPlatform ()
    ProfileInit = profileInit
    ProfileLog = profileLog
    DirCreate = dirCreate
    FileExists = System.IO.File.Exists
    FileReadAllText = readFile
    FileWriteAllText = writeFile
    ReadStdinAll = stdin.ReadToEnd
    WriteStdout = printf "%s"
    WriteStderr = eprintf "%s" }
