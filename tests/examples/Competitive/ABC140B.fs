// https://atcoder.jp/contests/abc140/tasks/abc140_b
module rec Competitive.ABC140B

open Competitive.Scan
open Std.Block
open Std.IO
open Std.StdError
open Std.Vector

module private Block =
  let get index block =
    Block.tryItem index block
    |> Option.defaultWith unreachable

let private solve n a b c =
  let a = Block.ofList a
  let b = Block.ofList b
  let c = Block.ofList c

  let rec go (sum: int) i =
    if i < n then
      let ai = Block.get i a

      let add = Block.get (ai - 1) b
      let sum = sum + add

      let bonus =
        if i >= 1 && Block.get (i - 1) a = ai - 1 then
          Block.get (ai - 2) c
        else
          0

      go (sum + bonus) (i + 1)
    else
      sum

  go 0 0

let abc140bTest () =
  let f a b c =
    let n = List.length a
    assert (List.length b = n)
    assert (List.length c = n - 1)
    solve n a b c

  let case1 () =
    let a = [ 3; 1; 2 ]
    let b = [ 2; 5; 4 ]
    let c = [ 3; 6 ]
    f a b c = 14

  assert (case1 ())

  let case2 () =
    let a = [ 2; 3; 4; 1 ]
    let b = [ 13; 5; 8; 24 ]
    let c = [ 45; 9; 15 ]
    f a b c = 74

  assert (case2 ())

  let case3 () =
    let a = [ 1; 2 ]
    let b = [ 50; 50 ]
    let c = [ 50 ]
    f a b c = 150

  assert (case3 ())

let abc140bMain (io: IO) =
  let n, io = scanInt io
  let a, io = scanList scanInt n io
  let b, io = scanList scanInt n io
  let c, io = scanList scanInt (n - 1) io
  let m = solve n a b c
  printfn "%d" m
  io
