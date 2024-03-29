/// Defines utility types and functions used in multiple modules.
module rec MiloneShared.Util

open Std.StdAssoc
open Std.StdError
open Std.StdList
open Std.StdPair
open Std.StdMap

module C = Std.StdChar
module S = Std.StdString
module Int = Std.StdInt

// -----------------------------------------------
// Pair
// -----------------------------------------------

let pairCompare compare1 compare2 l r = Pair.compare compare1 compare2 l r

// -----------------------------------------------
// Option
// -----------------------------------------------

let optionMapFold (mapFolder: 'S -> 'T -> 'U * 'S) (state: 'S) (opt: 'T option) : 'U option * 'S =
  match opt with
  | Some item ->
    let item, state = mapFolder state item
    Some item, state

  | None -> None, state

// -----------------------------------------------
// List
// -----------------------------------------------

let cons head tail = head :: tail

let forList folder xs state =
  List.fold (fun state x -> folder x state) state xs

let listSkip count xs = List.drop count xs
let listTryZip xs ys = List.zipEx xs ys
let listSort itemCompare xs = List.sortWith itemCompare xs
let listUnique itemCompare xs = List.sortUniqueWith itemCompare xs
let listCompare itemCompare ls rs = List.compare itemCompare ls rs

let listChooseFold (mapFolder: 'S -> 'T -> 'U option * 'S) (state: 'S) (xs: 'T list) : 'U list * 'S =
  let yss, state = List.mapFold mapFolder state xs
  yss |> List.choose id, state

let listCollectFold (mapFolder: 'S -> 'T -> 'U list * 'S) (state: 'S) (xs: 'T list) : 'U list * 'S =
  let yss, state = List.mapFold mapFolder state xs
  yss |> List.collect id, state

/// Tries to split a list to pair of non-last items and the last item.
let splitLast xs =
  let rec go acc last xs =
    match xs with
    | [] -> List.rev acc, last
    | x :: xs -> go (last :: acc) x xs

  match xs with
  | [] -> None
  | x :: xs -> Some(go [] x xs)

let assocTryFind compare key assoc = Assoc.tryFind compare key assoc

// -----------------------------------------------
// TreeMap
// -----------------------------------------------

let mapFind key map =
  match TMap.tryFind key map with
  | Some value -> value
  | None -> failwith ("mapFind: Missing key: " + __dump key)

// -----------------------------------------------
// Char
// -----------------------------------------------

let charNeedsEscaping (c: char) =
  C.isControl c || c = '\\' || c = '"' || c = '\''

let charEscape (c: char) =
  assert (c |> charNeedsEscaping)

  match c with
  // C-style.
  | '\x00' -> "\\0"

  | '\t' -> "\\t"
  | '\n' -> "\\n"
  | '\r' -> "\\r"
  | '\'' -> "\\\'"
  | '"' -> "\\\""
  | '\\' -> "\\\\"

  | c ->
    let hh = S.uint64ToHex 2 (uint64 (byte c))
    "\\x" + hh

// -----------------------------------------------
// String
// -----------------------------------------------

let stringNeedsEscaping (s: string) =
  let rec go i =
    i < s.Length && (charNeedsEscaping s.[i] || go (i + 1))

  go 0

let stringEscape (s: string) =
  let rec go acc i =
    /// Finds the end index of the maximum non-escaping segment
    /// that starts at `l`.
    let rec raw i =
      if i = s.Length || charNeedsEscaping s.[i] then
        i
      else
        raw (i + 1)

    // Skip the non-escape segment that starts at `i`.
    let i, acc =
      let r = raw i
      r, (s |> S.slice i r) :: acc

    if i = s.Length then
      acc
    else
      let t = s.[i] |> charEscape
      go (t :: acc) (i + 1)

  if s |> stringNeedsEscaping |> not then
    s
  else
    go [] 0 |> List.rev |> S.concat ""
