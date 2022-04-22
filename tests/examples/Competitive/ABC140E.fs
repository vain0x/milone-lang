/// https://atcoder.jp/contests/abc140/tasks/abc140_e
///
/// Reference solution (Rust):
///   https://atcoder.jp/contests/abc140/submissions/7438073
module rec Competitive.ABC140E

// not verified to get AC

open Std.IO
open Std.Vector
open Competitive.Scan
open Competitive.SegTree

let private intMin (l: int) r = if r < l then r else l
let private intMax (l: int) r = if l < r then r else l

let private solve n perm =
  // Add sentinels.
  let perm = (n + 1) :: List.append perm [ n + 1 ]
  assert (List.length perm = n + 2)

  // Segment trees for processed items.
  let prev = SegTree.replicate (n + 2) 0 0 intMax

  let next =
    let inf = n + 1
    SegTree.replicate (n + 2) (n + 1) inf intMin

  // Inverse of perm.
  let pos =
    let rec go pos perm i =
      if i = n + 2 then
        pos, perm
      else
        let p, perm = Vector.forceGet i perm
        let pos = Vector.forceSet p i pos
        go pos perm (i + 1)

    let pos = Vector.ofList (List.replicate (n + 3) 0)
    let perm = Vector.ofList perm
    let pos, perm = go pos perm 0
    Vector.dispose perm
    pos


  let rec go pos sum prev next p =
    if p < 1 then
      sum, pos, prev, next
    else
      let i, pos = Vector.forceGet p pos

      let x, prev = SegTree.sum 0 i prev
      let w, prev = SegTree.sum 0 x prev
      assert (w <= x && x < i)

      let y, next = SegTree.sum (i + 1) (n + 2) next
      let z, next = SegTree.sum (y + 1) (n + 2) next
      assert (i < y && y <= z)

      let count = (x - w) * (y - i) + (i - x) * (z - y)
      let sum = sum + count * p

      // printfn "p=%d (i=%d) w=%d x=%d y=%d z=%d" p i w x y z

      // mark i'th element as processed
      let prev = SegTree.set i i prev
      let next = SegTree.set i i next

      go pos sum prev next (p - 1)

  let sum, pos, prev, next = go pos 0 prev next n
  Vector.dispose pos
  SegTree.dispose prev
  SegTree.dispose next
  sum

let abc140eTest () =
  let solve p expected =
    let n = List.length p
    let actual = solve n p

    if actual = expected then
      true
    else
      printfn "actual=%d expected=%d" actual expected
      false

  assert (solve [ 2; 3; 1 ] 5)
  assert (solve [ 1; 2; 3; 4; 5 ] 30)
  assert (solve [ 8; 2; 7; 3; 4; 5; 6; 1 ] 136)

let abc140eMain (io: IO) =
  let n, io = scanInt io
  let p, io = scanList scanInt n io
  let m = solve n p
  printfn "%d" m
  io
