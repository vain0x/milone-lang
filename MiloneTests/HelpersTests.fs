module MiloneLang.HelpersTests

open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

[<Fact>]
let listIsEmptyTest () =
  ([]: int list) |> List.isEmpty |> is true
  [ 1 ] |> List.isEmpty |> is false

[<Fact>]
let listLengthTest () =
  ([]: int list) |> List.length |> is 0
  [ 1; 2; 3 ] |> List.length |> is 3

[<Fact>]
let listRevTest () =
  ([]: int list) |> List.rev |> is []
  [ 3; 1; 4; 1 ] |> List.rev |> is [ 1; 4; 1; 3 ]

[<Fact>]
let listMapTest () =
  [ 3; 1; 4; 1 ]
  |> List.map ((+) 1)
  |> is [ 4; 2; 5; 2 ]

[<Fact>]
let listMapWithIndexTest () =
  [ 3; 1; 4; 1 ]
  |> List.mapi (+)
  |> is [ 3; 2; 6; 4 ]

[<Fact>]
let listFilterTest () =
  [ 3; 1; 4; 1 ]
  |> List.filter (fun x -> x > 1)
  |> is [ 3; 4 ]

[<Fact>]
let listChooseTest () =
  [ 3; 1; 4; 1 ]
  |> List.choose (fun x -> if x > 1 then Some(x * x) else None)
  |> is [ 9; 16 ]

[<Fact>]
let listCollectTest () =
  [ 3; 1; 4; 1 ]
  |> List.collect (fun x -> if x > 1 then [ x; x ] else [ x ])
  |> is [ 3; 3; 1; 4; 4; 1 ]

[<Fact>]
let listForAllTest () =
  ([]: int list)
  |> listForAll (fun _ -> false)
  |> is true

  [ 3; 1; 4; 1 ]
  |> listForAll (fun x -> x >= 1)
  |> is true

  [ 3; 1; 4; 1 ]
  |> listForAll (fun x -> x > 1)
  |> is false

[<Fact>]
let listExistsTest () =
  ([]: int list)
  |> listExists (fun _ -> true)
  |> is false

  [ 3; 1; 4; 1 ]
  |> listExists (fun x -> x < 1)
  |> is false

  [ 3; 1; 4; 1 ]
  |> listExists (fun x -> x = 1)
  |> is true

[<Fact>]
let listFoldTest () =
  ([]: int list) |> listFold (+) 0 |> is 0

  [ 3; 1; 4; 1 ]
  |> listFold (fun s x -> s * 10 + x) 0
  |> is 3141

[<Fact>]
let listReduceTest () =
  [ 3; 1; 4; 1 ]
  |> listReduce (fun s x -> s * 10 + x)
  |> is 3141

[<Fact>]
let listLastTest () = [ 3; 1; 4; 1; 5; 9 ] |> listLast |> is 9

[<Fact>]
let listSkipTest () =
  [ 3; 1; 4; 1; 5; 9 ] |> listSkip 4 |> is [ 5; 9 ]

[<Fact>]
let listTruncateTest () =
  [ 3; 1; 4; 1; 5; 9 ]
  |> listTruncate 4
  |> is [ 3; 1; 4; 1 ]

[<Fact>]
let listAppendTest () =
  listAppend [ 3; 1; 4; 1 ] [ 5; 9 ]
  |> is [ 3; 1; 4; 1; 5; 9 ]

[<Fact>]
let listSortTest () =
  [ 3; 2; 1; 3; 2; 3 ]
  |> listSort intCmp
  |> is [ 1; 2; 2; 3; 3; 3 ]
  [ 3; 1; 4; 1; 5; 9 ]
  |> listSort intCmp
  |> is [ 1; 1; 3; 4; 5; 9 ]

[<Fact>]
let listUniqueTest () =
  [ 1; 2; 2; 3; 3; 3 ]
  |> listUnique intCmp
  |> is [ 1; 2; 3 ]
  [ 3; 1; 4; 1; 5; 9 ]
  |> listUnique intCmp
  |> is [ 1; 3; 4; 5; 9 ]

[<Fact>]
let mapBasicTest () =
  let m =
    mapEmpty (strHash, strCmp)
    |> mapAdd "a" 1
    |> mapAdd "b" 2

  m |> mapTryFind "a" |> is (Some 1)
  m |> mapTryFind "b" |> is (Some 2)
  m |> mapTryFind "c" |> is None

[<Fact>]
let mapAddTest () =
  let m =
    mapEmpty (strHash, strCmp)
    |> mapAdd "a" 1
    |> mapAdd "a" 2

  m |> mapTryFind "a" |> is (Some 2)

[<Fact>]
let mapRemoveTest () =
  let removed, m =
    mapEmpty (strHash, strCmp)
    |> mapAdd "a" 1
    |> mapAdd "a" 2
    |> mapAdd "b" 3
    |> mapRemove "a"

  removed |> is (Some 2)
  m |> mapTryFind "a" |> is None
  m |> mapTryFind "b" |> is (Some 3)

  let removed, _ = m |> mapRemove "c"
  removed |> is None

[<Fact>]
let mapFoldTest () =
  let m =
    mapEmpty (strHash, strCmp)
    |> mapAdd "a" 1
    |> mapAdd "c" 3
    |> mapAdd "a" 2

  m
  |> mapFold (fun s k v -> s + "," + (k + ":" + string v)) ""
  |> is ",a:2,c:3"

[<Fact>]
let mapMapTest () =
  mapEmpty (strHash, strCmp)
  |> mapAdd "a" 1
  |> mapAdd "c" 3
  |> mapAdd "a" 2
  |> mapMap (fun k v -> k + ":" + string v)
  |> mapToList
  |> is [ "a", "a:2"; "c", "c:3" ]

[<Fact>]
let mapToListTest () =
  mapEmpty (strHash, strCmp)
  |> mapAdd "a" 1
  |> mapAdd "c" 3
  |> mapAdd "a" 2
  |> mapAdd "b" 0
  |> mapToList
  |> is [ "a", 2; "b", 0; "c", 3 ]

[<Fact>]
let mapOfListTest () =
  mapOfList (strHash, strCmp) [ "a", 1; "c", 3; "a", 2; "b", 0 ]
  |> mapToList
  |> is [ "a", 2; "b", 0; "c", 3 ]

[<Fact>]
let setOfListTest () =
  let s =
    setOfList (strHash, strCmp) [ "a"; "b"; "c" ]

  s |> setContains "a" |> is true
  s |> setContains "d" |> is false

[<Fact>]
let setToListTest () =
  setOfList (strHash, strCmp) [ "a"; "b"; "c" ]
  |> setAdd "a"
  |> setAdd "d"
  |> setToList
  |> is [ "a"; "b"; "c"; "d" ]

[<Fact>]
let setDiffTest () =
  let first =
    setOfList (strHash, strCmp) [ "a"; "b"; "c"; "d" ]

  let second =
    setOfList (strHash, strCmp) [ "a"; "c"; "e"; "f" ]

  setDiff first second
  |> setToList
  |> is [ "b"; "d" ]

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
    dumpTreeNew "module" [ dumpTreeNewLeaf "Program" ]
    |> dumpTreeAttachNext
         (dumpTreeNew
           "let"
            [ dumpTreeNewLeaf "main"
              dumpTreeNew
                "body"
                [ dumpTreeNew "printfn" [ dumpTreeNewLeaf "\"Hello, world!\"" ]
                  dumpTreeNewLeaf "0" ] ])

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
