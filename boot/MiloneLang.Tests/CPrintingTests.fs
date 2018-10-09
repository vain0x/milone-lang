module MiloneLang.CPrintingTests

open System
open System.IO
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let testsDir = Tests.testsDir

let testFile fileName =
  let source =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir, "src", fileName + ".milone")
    )
  let target =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir, "c", fileName + ".c")
    )
  let cir = Program.toCir source
  CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
  |> is target

[<Theory>]
[<InlineData("zero")>]
[<InlineData("add")>]
// [<InlineData("emit_1")>]
[<InlineData("hello")>]
let integrationTests (name: string) =
  testFile name
