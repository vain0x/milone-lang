// https://atcoder.jp/contests/abc140/tasks/abc140_a
module rec Competitive.ABC140A

open Competitive.Scan
open Std.IO
open Std.Vector

let private solve (n: int) = n * n * n

let abc140aTest () =
  assert (solve 2 = 8)
  assert (solve 1 = 1)

let abc140aMain (io: IO) =
  let n, io = scanInt io
  printfn "%d" (solve n)
  io
