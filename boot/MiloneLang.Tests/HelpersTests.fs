module MiloneLang.HelpersTests

open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

[<Fact>]
let intToHexWithPaddingTest () =
  let hex len n = intToHexWithPadding len n

  0 |> hex 0 |> is "0"
  0 |> hex 2 |> is "00"
  1 |> hex 1 |> is "1"
  1 |> hex 2 |> is "01"
  0xbeef |> hex 0 |> is "beef"
  0x01234567 |> hex 8 |> is "01234567"
  0x7fffffff |> hex 8 |> is "7fffffff"

[<Fact>]
let dumpTreeTestEscape () =
  let toString text = dumpTreeNewLeaf text |> dumpTreeToString
  " hello \x00 \x08 \x1f \x7f \t \n \r \\ \" ' "
  |> toString
  |> is """ hello \0 \x08 \x1f \x7f \t \n \r \\ \" \' """

[<Fact>]
let dumpTreeTestLayout () =
  let tree =
    dumpTreeNew "module" [
      dumpTreeNewLeaf "Program"
    ]
    |> dumpTreeAttachNext (
      dumpTreeNew "let" [
        dumpTreeNewLeaf "main"
        dumpTreeNew "body" [
          dumpTreeNew "printfn" [
            dumpTreeNewLeaf "\"Hello, world!\""
          ]
          dumpTreeNewLeaf "0"
        ]
      ]
    )
  let expected = """module: Program
let:
- main
- body:
  - printfn: \"Hello, world!\"
  - 0"""
  tree |> dumpTreeToString |> is expected

[<Fact>]
let analyzeFormatTests () =
  analyzeFormat "Brave 100%%"
  |> is (tyFun tyStr tyUnit)

  analyzeFormat "Hello, %s!"
  |> is (tyFun tyStr (tyFun tyStr tyUnit))

  analyzeFormat "Welcome to %s. Entry price is %c%d!"
  |> is (tyFun tyStr (tyFun tyStr (tyFun tyChar (tyFun tyInt tyUnit))))
