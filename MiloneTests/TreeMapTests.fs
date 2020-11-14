module MiloneLang.TreeMapTests

open MiloneLang.Assets
open Xunit

let intCmp = Helpers.intCmp
let strCmp = Helpers.strCmp

[<Fact>]
let basicTest () =
  let m =
    TreeMap.empty strCmp
    |> TreeMap.add "a" 1
    |> TreeMap.add "b" 2

  m |> TreeMap.tryFind "a" |> is (Some 1)
  m |> TreeMap.tryFind "b" |> is (Some 2)
  m |> TreeMap.tryFind "c" |> is None

[<Fact>]
let addTest () =
  let m = TreeMap.empty strCmp
  m |> TreeMap.tryFind "a" |> is None

  let m = m |> TreeMap.add "a" 1
  m |> TreeMap.tryFind "a" |> is (Some 1)

  let m = m |> TreeMap.add "a" 2
  m |> TreeMap.tryFind "a" |> is (Some 2)

[<Fact>]
let removeTest () =
  let m = TreeMap.empty strCmp
  let removed, _ = m |> TreeMap.remove "a"
  removed |> is None

  let m =
    m
    |> TreeMap.add "a" 1
    |> TreeMap.add "a" 2
    |> TreeMap.add "b" 3

  let removed, m = m |> TreeMap.remove "a"
  removed |> is (Some 2)

  m |> TreeMap.tryFind "a" |> is None
  m |> TreeMap.tryFind "b" |> is (Some 3)

  let removed, _ = m |> TreeMap.remove "c"
  removed |> is None

[<Fact>]
let mapTest () =
  TreeMap.empty strCmp
  |> TreeMap.add "a" 1
  |> TreeMap.add "c" 3
  |> TreeMap.add "a" 2
  |> TreeMap.map (fun k v -> k + ":" + string v)
  |> TreeMap.toList
  |> is [ "a", "a:2"; "c", "c:3" ]

[<Fact>]
let foldTest () =
  let folder s k v = s + "," + (k + ":" + string v)

  let m = TreeMap.empty strCmp
  m |> TreeMap.fold folder "" |> is ""

  let m = m |> TreeMap.add "a" 1
  m |> TreeMap.fold folder "" |> is ",a:1"

  let m = m |> TreeMap.add "c" 3
  m |> TreeMap.fold folder "" |> is ",a:1,c:3"

  let m = m |> TreeMap.add "a" 2
  m |> TreeMap.fold folder "" |> is ",a:2,c:3"

[<Fact>]
let ofListTest () =
  let m =
    TreeMap.ofList strCmp [ "a", 1; "c", 3; "a", 2; "b", 0 ]

  m
  |> TreeMap.toList
  |> is [ "a", 2; "b", 0; "c", 3 ]

[<Fact>]
let toListTest () =
  let m = TreeMap.empty strCmp
  m |> TreeMap.toList |> is []

  let m = m |> TreeMap.add "a" 1
  m |> TreeMap.toList |> is [ "a", 1 ]

  let m = m |> TreeMap.add "c" 3
  m |> TreeMap.toList |> is [ "a", 1; "c", 3 ]

  let m = m |> TreeMap.add "a" 2
  m |> TreeMap.toList |> is [ "a", 2; "c", 3 ]

  let m = m |> TreeMap.add "b" 0
  m
  |> TreeMap.toList
  |> is [ "a", 2; "b", 0; "c", 3 ]
