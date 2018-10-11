module MiloneLang.Tests

open System
open MiloneLang.Assets
open Xunit

let testFile fileName =
  let source =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir.Value, "src", fileName + ".milone")
    )
  let target =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir.Value, "targets", fileName + ".out")
    ).TrimEnd()
  let output = Program.run source
  let expected =
    [
      for dest, line in output.Outs do
        let fd = match dest with StdOut -> 1 | StdErr -> 2
        yield sprintf ">%d %s" fd line
      yield sprintf "$? = %d" output.Code
    ]
    |> String.concat Environment.NewLine

  target |> is expected

[<Theory>]
[<InlineData("zero")>]
[<InlineData("add")>]
[<InlineData("emit_1")>]
[<InlineData("hello")>]
let integrationTests (name: string) =
  testFile name
