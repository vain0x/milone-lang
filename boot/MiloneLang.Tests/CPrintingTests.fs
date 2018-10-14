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
  let content =
    let cir = Program.toCir source
    CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
  let target =
    IO.File.WriteAllText(
      IO.Path.Combine(testsDir.Value, "c", fileName + ".c"),
      content
    )
  ()

[<Theory>]
[<InlineData("zero")>]
[<InlineData("add")>]
[<InlineData("arith")>]
[<InlineData("logic")>]
[<InlineData("hello")>]
[<InlineData("printfn")>]
[<InlineData("var_1")>]
[<InlineData("var_str")>]
[<InlineData("shadowing")>]
[<InlineData("if_else")>]
[<InlineData("if_else_complex")>]
[<InlineData("factorial")>]
let integrationTests (name: string) =
  testFile name
