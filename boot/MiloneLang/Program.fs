/// Entry point of the compiler.
module rec MiloneLang.Program

open System
open MiloneLang.Cli
open MiloneLang.Records

let readFile (filePath: string) = System.IO.File.ReadAllText(filePath)

let dotnetCliHost args =
  CliHost(args, profileInit, profileLog, readFile)

[<EntryPoint>]
let main args =
  let args = List.ofArray args
  let host = dotnetCliHost args
  cli host
