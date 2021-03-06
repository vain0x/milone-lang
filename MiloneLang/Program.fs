/// Entry point of the compiler.
module rec MiloneLang.Program

open MiloneLang.Cli

let private readFile (filePath: string) =
  try
    if System.IO.File.Exists(filePath) then
      System.IO.File.ReadAllText(filePath) |> Some
    else
      None
  with _ -> None

let dotnetCliHost () : CliHost =
  let args =
    System.Environment.GetCommandLineArgs()
    |> Array.toList

  let home =
    System.Environment.GetFolderPath(System.Environment.SpecialFolder.UserProfile)

  let miloneHome =
    System.Environment.GetEnvironmentVariable("MILONE_HOME")

  { Args = args
    Home = home
    MiloneHome = miloneHome
    ProfileInit = profileInit
    ProfileLog = profileLog
    FileReadAllText = readFile }

[<EntryPoint>]
let main _ = cli (dotnetCliHost ())
