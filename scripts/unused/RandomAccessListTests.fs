module rec MiloneLang.RandomAccessListTests

open MiloneLang.Assets
open Xunit

module Ral = RandomAccessList

type Ral<'T> = RandomAccessList.RandomAccessList<'T>

[<Fact>]
let emptyTest () = Ral.empty () |> Ral.length |> is 0

[<Fact>]
let addTest () =
  let xs = Ral.empty () |> Ral.add 1
  xs |> Ral.item 0 |> is 1
  xs |> Ral.length |> is 1

  let xs = xs |> Ral.add 2 |> Ral.add 3
  xs |> Ral.item 0 |> is 1
  xs |> Ral.item 1 |> is 2
  xs |> Ral.item 2 |> is 3
  xs |> Ral.length |> is 3

[<Fact>]
let addManyTest () =
  let rec go i xs =
    if i = 100 then xs else xs |> Ral.add i |> go (i + 1)

  let xs = Ral.empty () |> go 0

  for i in 0 .. 100 - 1 do
    xs |> Ral.item i |> is i

  xs |> Ral.length |> is 100

[<Fact>]
let withItemTest () =
  let xs =
    Ral.empty ()
    |> Ral.add 1
    |> Ral.add 2
    |> Ral.add 3
    |> Ral.withItem 1 (-2)

  xs |> Ral.item 0 |> is 1
  xs |> Ral.item 1 |> is (-2)
  xs |> Ral.item 2 |> is 3

[<Fact>]
let foldTest () =
  Ral.ofList [ 1; 2; 3 ]
  |> Ral.fold (fun (i, s) x -> i + 1, s + (if i = 0 then "" else ", ") + string x) (0, "")
  |> is (3, "1, 2, 3")

[<Fact>]
let mapTest () =
  Ral.ofList [ 1; 2; 3 ]
  |> Ral.map string
  |> Ral.toList
  |> is [ "1"; "2"; "3" ]

[<Fact>]
let ofListTest () =
  let xs = Ral.ofList [ 1; 2; 3 ]

  xs |> Ral.item 0 |> is 1
  xs |> Ral.item 1 |> is 2
  xs |> Ral.item 2 |> is 3

[<Fact>]
let toListTest () =
  Ral.ofList [ 1; 2; 3 ]
  |> Ral.toList
  |> is [ 1; 2; 3 ]
