module MiloneLang.CPrintingTests

open System
open System.IO
open MiloneLang.Assets
open Xunit

let testFile fileName =
  let source =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir.Value, "src", fileName + ".milone")
    )
  let target =
    IO.File.ReadAllText(
      IO.Path.Combine(testsDir.Value, "c", fileName + ".c")
    )
  let cir = Program.toCir source
  CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
  |> is target

[<Theory>]
[<InlineData("zero")>]
[<InlineData("add")>]
// [<InlineData("emit_1")>]
[<InlineData("hello")>]
[<InlineData("var_1")>]
[<InlineData("var_str")>]
let integrationTests (name: string) =
  testFile name
