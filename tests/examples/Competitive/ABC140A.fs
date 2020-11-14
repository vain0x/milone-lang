// https://atcoder.jp/contests/abc140/tasks/abc140_a
module rec Competitive.ABC140A

open Competitive.Helpers

let abc140aSolve n = n * n * n

let abc140aTest () =
  assert (abc140aSolve 2 = 8)
  assert (abc140aSolve 1 = 1)

let abc140aMain () =
  let n = scanInt ()
  let m = abc140aSolve n
  printfn "%d" m
