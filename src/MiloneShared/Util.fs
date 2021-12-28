/// Defines utility types and functions used in multiple modules.
module rec MiloneShared.Util

open MiloneStd.StdAssoc
open MiloneStd.StdError
open MiloneStd.StdList
open MiloneStd.StdPair
open MiloneStd.StdMap

module C = MiloneStd.StdChar
module S = MiloneStd.StdString
module Int = MiloneStd.StdInt

// -----------------------------------------------
// Pair
// -----------------------------------------------

let pairCompare compare1 compare2 l r = Pair.compare compare1 compare2 l r

// -----------------------------------------------
// Option
// -----------------------------------------------

/// `Option.map`, modifying context.
let stOptionMap f (x, ctx) =
  match x with
  | Some x ->
    let x, ctx = f (x, ctx)
    Some x, ctx
  | None -> None, ctx

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

/// `List.map`, modifying context.
///
/// USAGE:
/// ```fs
/// let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
/// ```
let stMap f (xs, ctx) =
  xs |> List.mapFold (fun ctx x -> f (x, ctx)) ctx

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

let strNeedsEscaping (str: string) =
  let rec go i =
    i < str.Length
    && (charNeedsEscaping str.[i] || go (i + 1))

  go 0

let strEscape (str: string) =
  let rec go acc i =
    /// Finds the end index of the maximum non-escaping segment
    /// that starts at `l`.
    let rec raw i =
      if i = str.Length || charNeedsEscaping str.[i] then
        i
      else
        raw (i + 1)

    // Skip the non-escape segment that starts at `i`.
    let i, acc =
      let r = raw i
      r, (str |> S.slice i r) :: acc

    if i = str.Length then
      acc
    else
      let t = str.[i] |> charEscape
      go (t :: acc) (i + 1)

  if str |> strNeedsEscaping |> not then
    str
  else
    go [] 0 |> List.rev |> S.concat ""
