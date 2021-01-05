module JsonEncode.Program

open System
open System.IO
open Utf8Json

[<EntryPoint>]
let main _ =
  let text = stdin.ReadToEnd()

  let json = Utf8Json.JsonSerializer.Serialize(text)

  use stdOut = Console.OpenStandardOutput()
  stdOut.Write(json, 0, json.Length)
  0
