/// Entry point of the compiler.
module rec MiloneLang.Program

open System
open MiloneLang.Cli

let readFile (filePath: string) = System.IO.File.ReadAllText(filePath)

[<EntryPoint>]
let main args =
  let args = List.ofArray args
  cli readFile args
