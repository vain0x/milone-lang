/// Entry point of the compiler.
module rec MiloneLang.Program

open MiloneLang.Cli
open MiloneLang.Records

let readFile (filePath: string) =
  try
    if System.IO.File.Exists(filePath)
    then System.IO.File.ReadAllText(filePath) |> Some
    else None
  with _ -> None

let dotnetCliHost args miloneHome =
  CliHost(args, miloneHome, profileInit, profileLog, readFile)

[<EntryPoint>]
let main args =
  let args = List.ofArray args

  let miloneHome =
    System.Environment.GetEnvironmentVariable("MILONE_HOME")

  cli (dotnetCliHost args miloneHome)
