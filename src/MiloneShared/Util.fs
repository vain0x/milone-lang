/// Defines utility types and functions used in multiple modules.
module rec MiloneShared.Util

open MiloneStd.StdMap

module C = MiloneStd.StdChar
module S = MiloneStd.StdString
module Int = MiloneStd.StdInt

// -----------------------------------------------
// Error
// -----------------------------------------------

/// Never executed.
let unreachable context = failwithf "NEVER: %A" context

/// Not implemented.
let todo context = failwithf "Not implemented: %A" context

// -----------------------------------------------
// Pair
// -----------------------------------------------

let pairCompare compare1 compare2 (l1, l2) (r1, r2) =
  let c = compare1 l1 r1
  if c <> 0 then c else compare2 l2 r2

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

/// Skips initial `count` items.
///
/// Unlike `List.skip`, just returns `[]` when `count` is negative or too large.
let listSkip (count: int) (xs: _ list) : _ list =
  let rec listSkipLoop count xs =
    match xs with
    | [] -> []
    | _ when count <= 0 -> xs
    | _ :: xs -> listSkipLoop (count - 1) xs

  listSkipLoop count xs

/// Tries to "zip" two lists by pairing every i'th item from both lists.
///
/// If two lists have different length, some elements have no pair.
/// These items are returns as third result.
/// The second result indicates which list is longer.
let listTryZip (xs: _ list) (ys: _ list) : (_ * _) list * _ list * _ list =
  let rec listTryZipLoop acc xs ys =
    match xs, ys with
    | _, []
    | [], _ -> List.rev acc, xs, ys

    | x :: xs, y :: ys -> listTryZipLoop ((x, y) :: acc) xs ys

  listTryZipLoop [] xs ys

/// `List.map`, modifying context.
///
/// USAGE:
/// ```fs
/// let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
/// ```
let stMap f (xs, ctx) =
  xs |> List.mapFold (fun ctx x -> f (x, ctx)) ctx

/// `List.bind`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stFlatMap (fun (x, ctx) -> ys, ctx)
let stFlatMap f (xs, ctx) =
  let rec go acc xs ctx =
    match xs with
    | [] -> List.rev acc, ctx
    | x :: xs ->
      let acc, ctx = f (x, acc, ctx)
      go acc xs ctx

  go [] xs ctx

let listCompare compare ls rs =
  let rec go ls rs =
    match ls, rs with
    | [], [] -> 0
    | [], _ -> -1
    | _, [] -> 1
    | l :: ls, r :: rs ->
      let c = compare l r
      if c <> 0 then c else go ls rs

  go ls rs

let listSortCore unique compare xs =
  let rec appendRev acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> appendRev (x :: acc) xs

  // `merge (xs, xn) (ys, yn) = (zs, zn), d` where
  // `zs.[0..zn - 1]` is the merge of `xs.[0..xn - 1]` and `ys.[0..yn - 1]`,
  // and `d` is the number of duplicated items.
  let rec merge (zs, zn) d (xs, xn) (ys, yn) =
    if xn = 0 then
      (appendRev ys zs, zn + yn), d
    else

    if yn = 0 then
      (appendRev xs zs, zn + xn), d
    else
      match xs, ys with
      | [], _
      | _, [] -> unreachable () // wrong list length.

      | x :: xs1, y :: ys1 ->
        let c = compare x y

        if c > 0 then
          merge (y :: zs, zn + 1) d (xs, xn) (ys1, yn - 1)
        else if c = 0 && unique then
          merge (zs, zn) (d + 1) (xs, xn) (ys1, yn - 1)
        else
          merge (x :: zs, zn + 1) d (xs1, xn - 1) (ys, yn)

  // `go (xs, xn) = (zs, zn), xs1, d` where
  // `zs.[0..xn - 1]` is the sort of `xs.[0..xn - 1]`,
  // `xs1 = xs.[xn..]`,
  // and `d` is the number of duplicated items.
  let rec go (xs, n) =
    if n <= 1 then
      (xs, n), listSkip n xs, 0
    else
      let m = n / 2
      let (xs, xn), xs1, d1 = go (xs, m)
      let (ys, yn), ys1, d2 = go (xs1, n - m)
      let (zs, zn), d3 = merge ([], 0) 0 (xs, xn) (ys, yn)
      (zs, zn), ys1, d1 + d2 + d3

  let xn = List.length xs
  let (zs, zn), ws, d = go (xs, xn)
  assert (zn + d = xn)
  assert (ws |> List.isEmpty)
  List.truncate zn zs

let listSort compare xs = listSortCore false compare xs

let listUnique compare xs = listSortCore true compare xs

/// Tries to split a list to pair of non-last items and the last item.
let splitLast xs =
  let rec go acc last xs =
    match xs with
    | [] -> List.rev acc, last
    | x :: xs -> go (last :: acc) x xs

  match xs with
  | [] -> None
  | x :: xs -> Some(go [] x xs)

// -----------------------------------------------
// Assoc
// -----------------------------------------------

let assocTryFind compare key assoc =
  let rec go assoc =
    match assoc with
    | [] -> None

    | (k, v) :: _ when compare k key = 0 -> Some v

    | _ :: assoc -> go assoc

  go assoc

// -----------------------------------------------
// AssocMap
// -----------------------------------------------

let mapFind key map =
  match TMap.tryFind key map with
  | Some value -> value

  | None -> failwithf "mapFind: Missing key: %A." key

// -----------------------------------------------
// Multimap
// -----------------------------------------------

type Multimap<'K, 'T> = TreeMap<'K, 'T list>

let multimapFind (key: 'K) (multimap: Multimap<'K, 'T>) : 'T list =
  multimap
  |> TMap.tryFind key
  |> Option.defaultValue []

let multimapAdd (key: 'K) (item: 'T) (multimap: Multimap<'K, 'T>) : Multimap<'K, 'T> =
  let items = multimap |> multimapFind key
  TMap.add key (item :: items) multimap

let multimapOfList compareFun (entries: ('K * 'T) list) : Multimap<'K, 'T> =
  entries
  |> List.fold (fun map (key, value) -> multimapAdd key value map) (TMap.empty compareFun)

// -----------------------------------------------
// Int
// -----------------------------------------------

let intToHexWithPadding (len: int) (value: int) =
  if value < 0 then
    failwith "intToHexWithPadding: unimplemented negative"
  else

    assert (len >= 0)

    let rec go acc len (n: int) =
      if n = 0 && len <= 0 then
        acc
      else
        let d = n % 16
        let s = "0123456789abcdef" |> S.slice d (d + 1)
        go (s + acc) (len - 1) (n / 16)

    if value = 0 && len = 0 then
      "0"
    else
      go "" len value

let intFromHex (l: int) (r: int) (s: string) =
  assert (0 <= l && l < r && r <= s.Length)

  let hexDigitToInt (c: char) =
    if '0' <= c && c <= '9' then
      int c - int '0'
    else if 'A' <= c && c <= 'F' then
      int c - int 'A' + 10
    else if 'a' <= c && c <= 'f' then
      int c - int 'a' + 10
    else
      assert false
      0

  let rec go (acc: int) (i: int) =
    if i = r then
      acc
    else
      let d = hexDigitToInt s.[i]
      go (acc * 16 + d) (i + 1)

  go 0 l

// -----------------------------------------------
// Char
// -----------------------------------------------

let charNeedsEscaping (c: char) =
  C.isControl c || c = '\\' || c = '"' || c = '\''

let charEscape (c: char) =
  assert (c |> charNeedsEscaping)

  match c with
  | '\x00' ->
    // C-style.
    "\\0"

  | '\t' -> "\\t"

  | '\n' -> "\\n"

  | '\r' -> "\\r"

  | '\'' -> "\\\'"

  | '"' -> "\\\""

  | '\\' -> "\\\\"

  | c ->
    let h = c |> int |> intToHexWithPadding 2
    "\\x" + h

// -----------------------------------------------
// String
// -----------------------------------------------

let strConcat (xs: string list) = S.concat "" xs

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
    go [] 0 |> List.rev |> strConcat
