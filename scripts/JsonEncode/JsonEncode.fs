// Encodes an input as JSON string.
// Reads from standard input, writes to standard output.
//
// USAGE:
//    ... | dotnet fsi scripts/JsonEncode.fsx
//
// EXAMPLES:
//    $ printf 'Hello,\nworld!\n' | dotnet fsi scripts/JsonEncode.fsx
//    "Hello,\nworld\n"

module JsonEncode.Program

open System

[<EntryPoint>]
let main _ =
  let text = stdin.ReadToEnd()

  let json = Utf8Json.JsonSerializer.Serialize(text)

  use stdOut = Console.OpenStandardOutput()
  stdOut.Write(json, 0, json.Length)
  0
