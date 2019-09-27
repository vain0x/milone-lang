module MiloneLang.HelpersTests

open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

[<Fact>]
let listIsEmptyTest () =
  ([]: int list) |> listIsEmpty |> is true
  [1] |> listIsEmpty |> is false

[<Fact>]
let listLengthTest () =
  ([]: int list) |> listLength |> is 0
  [1; 2; 3] |> listLength |> is 3

[<Fact>]
let listRevTest () =
  ([]: int list) |> listRev |> is []
  [3; 1; 4; 1] |> listRev |> is [1; 4; 1; 3]

[<Fact>]
let listMapTest () =
  [3; 1; 4; 1] |> listMap ((+) 1) |> is [4; 2; 5; 2]

[<Fact>]
let listMapWithIndexTest () =
  [3; 1; 4; 1] |> listMapWithIndex (+) |> is [3; 2; 6; 4]

[<Fact>]
let listFilterTest () =
  [3; 1; 4; 1]
  |> listFilter (fun x -> x > 1)
  |> is [3; 4]

[<Fact>]
let listChooseTest () =
  [3; 1; 4; 1]
  |> listChoose (fun x -> if x > 1 then Some (x * x) else None)
  |> is [9; 16]

[<Fact>]
let listCollectTest () =
  [3; 1; 4; 1]
  |> listCollect (fun x -> if x > 1 then [x; x] else [x])
  |> is [3; 3; 1; 4; 4; 1]

[<Fact>]
let listForAllTest () =
  ([]: int list) |> listForAll (fun _ -> false) |> is true

  [3; 1; 4; 1]
  |> listForAll (fun x -> x >= 1)
  |> is true

  [3; 1; 4; 1]
  |> listForAll (fun x -> x > 1)
  |> is false

[<Fact>]
let listExistsTest () =
  ([]: int list) |> listExists (fun _ -> true) |> is false

  [3; 1; 4; 1]
  |> listExists (fun x -> x < 1)
  |> is false

  [3; 1; 4; 1]
  |> listExists (fun x -> x = 1)
  |> is true

[<Fact>]
let listFoldTest () =
  ([]: int list) |> listFold (+) 0 |> is 0

  [3; 1; 4; 1]
  |> listFold (fun s x -> s * 10 + x) 0
  |> is 3141

[<Fact>]
let listReduceTest () =
  [3; 1; 4; 1]
  |> listReduce (fun s x -> s * 10 + x)
  |> is 3141

[<Fact>]
let listLastTest () =
  [3; 1; 4; 1; 5; 9]
  |> listLast
  |> is 9

[<Fact>]
let listSkipTest () =
  [3; 1; 4; 1; 5; 9]
  |> listSkip 4
  |> is [5; 9]

[<Fact>]
let listTruncateTest () =
  [3; 1; 4; 1; 5; 9]
  |> listTruncate 4
  |> is [3; 1; 4; 1]

[<Fact>]
let listAppendTest () =
  listAppend [3; 1; 4; 1] [5; 9]
  |> is [3; 1; 4; 1; 5; 9]

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
let intFromHexTest () =
  let parse (s: string) = intFromHex 0 s.Length s

  "0" |> parse |> is 0
  "19aF" |> parse |> is 0x19af
  "(0xbeef)" |> intFromHex 3 7 |> is 0xbeef

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
