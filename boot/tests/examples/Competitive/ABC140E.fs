/// https://atcoder.jp/contests/abc140/tasks/abc140_e
///
/// Reference solution (Rust):
///   https://atcoder.jp/contests/abc140/submissions/7438073
///
/// This don't get AC because too inefficient.
module rec Competitive.ABC140E

open Competitive.Helpers
open Competitive.SegTree

let abc140eSolve n perm =
  let segItemTypeInt = segItemTypeNew 0 (fun _ _ -> 0)

  let perm = perm |> segTreeOfList segItemTypeInt

  // add sentinels
  let perm =
    perm
    |> segTreeInsert 0 (n + 1)
    |> segTreePush (n + 2)
  assert (segTreeToLength perm = n + 2)

  // segment trees for processed items
  let prev =
    listReplicate 0 (n + 2)
    |> segTreeOfList (segItemTypeNew 0 intMax)
  let next =
    listReplicate (n + 1) (n + 2)
    |> segTreeOfList (segItemTypeNew (n + 1) intMin)

  // inverse of perm
  let pos =
    let rec go pos i =
      if i = n + 2 then
        pos
      else
        let pos = pos |> segTreeSet (perm |> segTreeGet i) i
        go pos (i + 1)

    let pos =
      listReplicate 0 (n + 3)
      |> segTreeOfList segItemTypeInt
    go pos 0

  let rec go sum prev next p =
    if p < 1 then
      sum
    else
      let i = pos |> segTreeGet p

      let x = prev |> segTreeSum 0 i
      let w = prev |> segTreeSum 0 x
      assert (w <= x && x < i)

      let y = next |> segTreeSum (i + 1) (n + 2)
      let z = next |> segTreeSum (y + 1) (n + 2)
      assert (i < y && y <= z)

      let count = (x - w) * (y - i) + (i - x) * (z - y)
      let sum = sum + count * p

      // printfn "p=%d (i=%d) w=%d x=%d y=%d z=%d" p i w x y z

      // mark i'th element as processed
      let prev = prev |> segTreeSet i i
      let next = next |> segTreeSet i i

      go sum prev next (p - 1)

  go 0 prev next n

let abc140eTest () =
  let solve p expected  =
    let n = p |> listLength
    let actual = abc140eSolve n p

    if actual = expected then
      true
    else
      printfn "actual=%d expected=%d" actual expected
      false

  assert (solve [2; 3; 1] 5)
  assert (solve [1; 2; 3; 4; 5] 30)
  assert (solve [8; 2; 7; 3; 4; 5; 6; 1] 136)

let abc140eMain () =
  let n = scanInt ()
  let p = scanIntList n
  let m = abc140eSolve n p
  printfn "%d" m
