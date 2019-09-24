module rec MiloneLang.Helpers

open MiloneLang.Types

// -----------------------------------------------
// List
// -----------------------------------------------

let cons head tail = head :: tail

let listIsEmpty xs =
  match xs with
  | [] ->
    true
  | _ ->
    false

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] ->
      acc
    | x :: xs ->
      go (x :: acc) xs
  go [] xs

let listLength xs =
  let rec go len xs =
    match xs with
    | [] ->
      len
    | _ :: xs ->
      go (len + 1) xs
  go 0 xs

let rec listIter f xs =
  match xs with
  | [] ->
    ()

  | x :: xs ->
    f x
    listIter f xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc
    | x :: xs ->
      go (f x :: acc) xs
  go [] xs

let listTruncate count xs =
  let rec go count xs =
    match xs with
    | [] ->
      []

    | _ when count <= 0 ->
      []

    | x :: xs ->
      x :: go (count - 1) xs

  go count xs

// -----------------------------------------------
// Int
// -----------------------------------------------

let intMin (x: int) (y: int) =
  if x > y then y else x

let intMax (x: int) (y: int) =
  if x < y then y else x

let intEq (x: int) (y: int) =
  x = y

// -----------------------------------------------
// String
// -----------------------------------------------

let strSlice (start: int) (endIndex: int) (s: string): string =
  assert (start <= endIndex && endIndex <= s.Length)
  if start >= endIndex then
    ""
  else
    s.[start..endIndex - 1]

let strConcat (xs: string list) =
  /// Get (str, ys) where
  /// `str` is the concatenation of first `xn` items in `xs`
  /// `ys` is a list of the other items
  let rec go xs xn =
    // assert (xn <= listLength xs)
    match xs with
    | [] ->
      assert (xn = 0)
      "", []
    | x :: xs when xn = 1 ->
      x, xs
    | x :: y :: xs when xn = 2 ->
      x + y, xs
    | xs ->
      let m = xn / 2
      let l, xs = go xs m
      let r, xs = go xs (xn - m)
      l + r, xs
  let n = xs |> listLength
  let s, xs = go xs n
  assert (xs |> listIsEmpty)
  s

  // let rec go (xs: string list) =
  //   match xs with
  //   | [] ->
  //     ""
  //   | x :: xs ->
  //     x + go xs
  // go xs
