// https://atcoder.jp/contests/abc140/tasks/abc140_b
module rec Competitive.ABC140B

open Competitive.Scan
open Std.IO
open Std.Vector

let private solve n a b c =
  let a = Vector.ofList a
  let b = Vector.ofList b
  let c = Vector.ofList c

  let rec go (sum: int) a b c i =
    if i < n then
      let ai, a = Vector.forceGet i a

      let add, b = Vector.forceGet (ai - 1) b
      let sum = sum + add

      let bonus, a, c =
        if i >= 1 then
          let prev, a = Vector.forceGet (i - 1) a
          if prev = ai - 1 then
            let x, c = Vector.forceGet (ai - 2) c
            x, a, c
          else
            0, a, c
        else
          0, a, c

      go (sum + bonus) a b c (i + 1)
    else
      sum, a, b, c

  let total, a, b, c = go 0 a b c 0
  Vector.dispose a
  Vector.dispose b
  Vector.dispose c
  total

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
