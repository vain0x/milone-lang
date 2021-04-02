/// Entry point of the compiler.
module rec MiloneCli.Program

open MiloneCli.Cli

let private readFile (filePath: string) =
  try
    if System.IO.File.Exists(filePath) then
      System.IO.File.ReadAllText(filePath) |> Some
    else
      None
  with _ -> None

let private writeFile (filePath: string) (contents: string) : unit =
  try
    match readFile filePath with
    | Some it when it = contents -> ()
    | _ -> System.IO.File.WriteAllText(filePath, contents)
  with err -> eprintfn "Couldn't write to file '%s'. '%s'" filePath err.Message

let dotnetCliHost () : CliHost =
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
    Home = home
    MiloneHome = miloneHome
    ProfileInit = profileInit
    ProfileLog = profileLog
    FileReadAllText = readFile
    FileWriteAllText = writeFile
    WriteStdout = printf "%s" }

[<EntryPoint>]
let main _ = cli (dotnetCliHost ())
