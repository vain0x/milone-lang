/// Entry point of the compiler.
module rec MiloneCli.Program

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
  | err -> eprintfn "Couldn't write to file '%s'. '%s'" filePath err.Message

let private executeInto (cmd: string) : unit =
  try
    let p =
      System.Diagnostics.Process.Start("/bin/sh", [ "-c"; cmd ])

    p.WaitForExit()
  with
  | err -> eprintfn "Couldn't execute into: '%s'. '%s'" cmd err.Message

// HACK: Force to load DLLs and perhaps do JIT-ing functions.
//       (With this, AstBundle becomes much faster.)
let private preLoad () =
  let rng = System.Random()
  let next () = lock rng (fun () -> rng.Next())

  mpscConcurrent
    (fun () a ->
      eprintf "%d\n" (a % 10) // Prevent dead code elimination.
      (), [])
    (fun () () -> Future.just (next ()))
    ()
    [ (); () ]

let dotnetCliHost () : CliHost =
  preLoad ()

  let args =
    System.Environment.GetCommandLineArgs()
    |> Array.toList

  let home =
    System.Environment.GetFolderPath(System.Environment.SpecialFolder.UserProfile)

  let miloneHome =
    match System.Environment.GetEnvironmentVariable("MILONE_HOME") with
    | null -> ""
    | it -> it

  { Args = args
    WorkDir = System.Environment.CurrentDirectory
    Home = home
    MiloneHome = miloneHome
    ProfileInit = profileInit
    ProfileLog = profileLog
    DirCreate = dirCreate
    FileReadAllText = readFile
    FileWriteAllText = writeFile
    WriteStdout = printf "%s"
    ExecuteInto = executeInto }

[<EntryPoint>]
let main _ = cli (dotnetCliHost ())
