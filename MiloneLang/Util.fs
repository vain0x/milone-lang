/// Defines utility types and functions used in multiple modules.
module rec MiloneLang.Util

open MiloneLang.TreeMap

// -----------------------------------------------
// Collections
// -----------------------------------------------

type AssocMap<'K, 'V> = TreeMap.TreeMap<'K, 'V>

type AssocSet<'K> = TreeMap.TreeMap<'K, unit>

/// Tree to generate a string for debugging.
[<NoEquality; NoComparison>]
type DumpTree = DumpTree of heading: string * body: DumpTree list * next: DumpTree list

// -----------------------------------------------
// Pair
// -----------------------------------------------

let pairCmp cmp1 cmp2 (l1, l2) (r1, r2) =
  let c = cmp1 l1 r1
  if c <> 0 then c else cmp2 l2 r2

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

/// Tries to "zip" two lists by pairing every i'th item from both lists.
///
/// If two lists have different length, some elements have no pair.
/// These items are returns as third result.
/// The second result indicates which list is longer.
let listTryZip (xs: _ list) (ys: _ list): (_ * _) list * _ list * _ list =
  let rec listTryZipLoop acc xs ys =
    match xs, ys with
    | _, []
    | [], _ -> List.rev acc, xs, ys

    | x :: xs, y :: ys -> listTryZipLoop ((x, y) :: acc) xs ys

  listTryZipLoop [] xs ys

/// `List.map`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] -> List.rev acc, ctx
    | x :: xs ->
        let y, ctx = f (x, ctx)
        go (y :: acc) (xs, ctx)

  go [] (xs, ctx)

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

let listCmp cmp ls rs =
  let rec go ls rs =
    match ls, rs with
    | [], [] -> 0
    | [], _ -> -1
    | _, [] -> 1
    | l :: ls, r :: rs ->
        let c = cmp l r
        if c <> 0 then c else go ls rs

  go ls rs

let listSortCore unique cmp xs =
  let rec appendRev acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> appendRev (x :: acc) xs

  // `merge (xs, xn) (ys, yn) = (zs, zn), d` where
  // `zs.[0..zn - 1]` is the merge of `xs.[0..xn - 1]` and `ys.[0..yn - 1]`,
  // and `d` is the number of duplicated items.
  // NOTE: It seems not tail-call optimized by GCC?
  let rec merge (zs, zn) d (xs, xn) (ys, yn) =
    if xn = 0 then
      (appendRev ys zs, zn + yn), d
    else if yn = 0 then
      (appendRev xs zs, zn + xn), d
    else
      match xs, ys with
      | [], _
      | _, [] -> failwith "NEVER: wrong list length"

      | x :: xs1, y :: ys1 ->
          let c = cmp x y
          if c > 0
          then merge (y :: zs, zn + 1) d (xs, xn) (ys1, yn - 1)
          else if c = 0 && unique
          then merge (zs, zn) (d + 1) (xs, xn) (ys1, yn - 1)
          else merge (x :: zs, zn + 1) d (xs1, xn - 1) (ys, yn)

  // `go (xs, xn) = (zs, zn), xs1, d` where
  // `zs.[0..xn - 1]` is the sort of `xs.[0..xn - 1]`,
  // `xs1 = xs.[xn..]`,
  // and `d` is the number of duplicated items.
  let rec go (xs, n) =
    if n <= 1 then
      (xs, n), List.skip n xs, 0
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

let listSort cmp xs = listSortCore false cmp xs

let listUnique cmp xs = listSortCore true cmp xs

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

let assocTryFind cmp key assoc =
  let rec go assoc =
    match assoc with
    | [] -> None

    | (k, v) :: _ when cmp k key = 0 -> Some v

    | _ :: assoc -> go assoc

  go assoc

// -----------------------------------------------
// AssocMap
// -----------------------------------------------

let mapEmpty cmp: AssocMap<_, _> = TreeMap.empty cmp

let mapIsEmpty (map: AssocMap<_, _>) = TreeMap.isEmpty map

let mapAdd key value (map: AssocMap<_, _>): AssocMap<_, _> = TreeMap.add key value map

let mapRemove key (map: AssocMap<_, _>): _ option * AssocMap<_, _> = TreeMap.remove key map

let mapTryFind key (map: AssocMap<_, _>): _ option = TreeMap.tryFind key map

let mapFind key map =
  match mapTryFind key map with
  | Some value -> value

  | None -> failwithf "mapFind: missing key (%A)" key

let mapContainsKey key map =
  match mapTryFind key map with
  | Some _ -> true

  | None -> false

let mapFold folder state (map: AssocMap<_, _>) = TreeMap.fold folder state map

let mapMap f (map: AssocMap<_, _>): AssocMap<_, _> = TreeMap.map f map

let mapFilter pred (map: AssocMap<_, _>): AssocMap<_, _> = TreeMap.filter pred map

let mapToKeys (map: AssocMap<_, _>) = TreeMap.toList map |> List.map fst

let mapToList (map: AssocMap<_, _>) = TreeMap.toList map

let mapOfKeys cmp value keys: AssocMap<_, _> =
  keys
  |> List.map (fun key -> key, value)
  |> TreeMap.ofList cmp

let mapOfList cmp assoc: AssocMap<_, _> = TreeMap.ofList cmp assoc

// -----------------------------------------------
// AssocSet
// -----------------------------------------------

let setEmpty funs: AssocSet<_> = mapEmpty funs

let setIsEmpty (set: AssocSet<_>): bool = set |> mapIsEmpty

let setContains key (set: AssocSet<_>) = set |> mapContainsKey key

let setToList (set: AssocSet<_>) = set |> mapToKeys

let setOfList cmp xs: AssocSet<_> = mapOfKeys cmp () xs

let setAdd key set: AssocSet<_> = mapAdd key () set

let setRemove key set: bool * AssocSet<_> =
  let opt, set = set |> mapRemove key
  Option.isSome opt, set

let setFold folder state (set: AssocSet<_>) =
  set |> setToList |> List.fold folder state

// TODO: make it more efficient
let setExists pred (set: AssocSet<_>) = set |> setToList |> List.exists pred

// TODO: make it more efficient
let setUnion first second =
  first
  |> setFold (fun set item -> set |> setAdd item) second

// -----------------------------------------------
// Int
// -----------------------------------------------

let intMin (x: int) (y: int) = if x > y then y else x

let intMax (x: int) (y: int) = if x < y then y else x

let intEq (x: int) (y: int) = x = y

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
        let s = "0123456789abcdef" |> strSlice d (d + 1)
        go (s + acc) (len - 1) (n / 16)

    if value = 0 && len = 0 then "0" else go "" len value

let intFromHex (l: int) (r: int) (s: string) =
  assert (0 <= l && l < r && r <= s.Length)

  let hexDigitToInt (c: char) =
    if '0' <= c && c <= '9' then
      charSub c '0'
    else if 'A' <= c && c <= 'F' then
      charSub c 'A' + 10
    else if 'a' <= c && c <= 'f' then
      charSub c 'a' + 10
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

let charSub (x: char) (y: char) = int x - int y

let charIsControl (c: char) =
  let n = int c
  0 <= n && n < 32 || n = 127

let charIsSpace (c: char): bool =
  c = ' ' || c = '\t' || c = '\r' || c = '\n'

let charIsDigit (c: char): bool = '0' <= c && c <= '9'

let charIsAlpha (c: char): bool =
  ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')

let charNeedsEscaping (c: char) =
  charIsControl c || c = '\\' || c = '"' || c = '\''

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

  | '\"' -> "\\\""

  | '\\' -> "\\\\"

  | c ->
      let h = c |> int |> intToHexWithPadding 2
      "\\x" + h

// -----------------------------------------------
// String
// -----------------------------------------------

let strSlice (start: int) (endIndex: int) (s: string): string =
  assert (start <= endIndex && endIndex <= s.Length)
  if start >= endIndex then "" else s.[start..endIndex - 1]

let strConcat (xs: string list) = strJoin "" xs

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
      if i = str.Length || charNeedsEscaping str.[i]
      then i
      else raw (i + 1)

    // Skip the non-escape segment that starts at `i`.
    let i, acc =
      let r = raw i
      r, (str |> strSlice i r) :: acc

    if i = str.Length then
      acc
    else
      let t = str.[i] |> charEscape
      go (t :: acc) (i + 1)

  if str |> strNeedsEscaping |> not then str else go [] 0 |> List.rev |> strConcat

// -----------------------------------------------
// DumpTree (for debugging)
// -----------------------------------------------

let dumpTreeNew text children = DumpTree(text, children, [])

let dumpTreeNewLeaf text = DumpTree(text, [], [])

let dumpTreeAttachNext next tree =
  match tree with
  | DumpTree (text, children, oldNext) ->
      assert (children |> List.isEmpty |> not)
      assert (oldNext |> List.isEmpty)
      DumpTree(text, children, [ next ])

let dumpTreeFromError (msg: string) (y, x) =
  let y = string (y + 1)
  let x = string (x + 1)
  dumpTreeNew
    "ERROR"
    [ dumpTreeNewLeaf msg
      dumpTreeNewLeaf ("(" + y + ":" + x + ")") ]

let dumpTreeToString (node: DumpTree) =
  let rec go eol node acc =
    let rec goChildren eol children acc =
      match children with
      | [] -> acc

      | child :: children ->
          acc
          |> cons eol
          |> cons "- "
          |> go (eol + "  ") child
          |> goChildren eol children

    let goNext eol next acc =
      match next with
      | [] -> acc

      | [ next ] -> acc |> cons eol |> go eol next

      | _ -> failwith "NEVER: DumpTree.next never empty"

    match node with
    | DumpTree (text, [], []) -> acc |> cons (strEscape text)

    | DumpTree (text, [ DumpTree (childText, [], []) ], next) ->
        acc
        |> cons (strEscape text)
        |> cons ": "
        |> cons (strEscape childText)
        |> goNext eol next

    | DumpTree (text, children, next) ->
        acc
        |> cons (strEscape text)
        |> cons ":"
        |> goChildren eol children
        |> goNext eol next

  let eol = "\n"
  [] |> go eol node |> List.rev |> strConcat
