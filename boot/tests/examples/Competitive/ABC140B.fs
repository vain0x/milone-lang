// https://atcoder.jp/contests/abc140/tasks/abc140_b
module rec Competitive.ABC140B

open Competitive.Helpers

let abc140bSolve n a b c =
  let rec go (sum: int) i =
    if i = n then
      sum
    else
      let ai = a |> vectorGet i
      let eat = b |> vectorGet (ai - 1) // 0-indexed

      let bonus =
        if i + 1 < n && a |> vectorGet (i + 1) = ai + 1 then
          c |> vectorGet (ai - 1)
        else
          0

      go (sum + eat + bonus) (i + 1)
  go 0 0

let abc140bTest () =
  let f a b c =
    let n = a |> listLength
    assert (b |> listLength = n)
    assert (c |> listLength = n - 1)
    let a = vectorOfList typeInt a
    let b = vectorOfList typeInt b
    let c = vectorOfList typeInt c
    abc140bSolve n a b c

  let case1 () =
    let a = [3; 1; 2]
    let b = [2; 5; 4]
    let c = [3; 6]
    f a b c = 14
  assert (case1 ())

  let case2 () =
    let a = [2; 3; 4; 1]
    let b = [13; 5; 8; 24]
    let c = [45; 9; 15]
    f a b c = 74
  assert (case2 ())

  let case3 () =
    let a = [1; 2]
    let b = [50; 50]
    let c = [50]
    f a b c = 150
  assert (case3 ())

let abc140bMain () =
  let n = scanInt ()
  let a = scanIntVector n
  let b = scanIntVector n
  let c = scanIntVector (n - 1)
  let m = abc140bSolve n a b c
  printfn "%d" m
