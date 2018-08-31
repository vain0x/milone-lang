module MiloneLang.Tests

open System
open System.IO
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let testsDir =
  let rec go (dir: string) =
    if IO.Path.GetFileName(dir) = "boot" then
      IO.Path.Combine(dir, "tests")
    else
      IO.Path.GetDirectoryName(dir) |> go
  go Environment.CurrentDirectory

let testFile fileName =
  let source =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir, "src", fileName + ".milone")
    )
  let target =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir, "targets", fileName + ".out")
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

[<Fact>]
let testZero () =
  testFile "zero"

[<Fact>]
let testAdd () =
  testFile "add"

[<Fact>]
let testEmit1 () =
  testFile "emit_1"
