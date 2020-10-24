/// Defines the functions used in multiple modules.
module rec MiloneLang.Helpers

open MiloneLang.Types
open MiloneLang.Records

/// `List.map`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] -> listRev acc, ctx
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
    | [] -> listRev acc, ctx
    | x :: xs ->
        let acc, ctx = f (x, acc, ctx)
        go acc xs ctx

  go [] xs ctx

/// `Option.map`, modifying context.
let stOptionMap f (x, ctx) =
  match x with
  | Some x ->
      let x, ctx = f (x, ctx)
      Some x, ctx
  | None -> None, ctx

/// Maps over a list, collecting things, mutating context.
let exMap f (xs, acc, ctx) =
  let rec go ys xs acc ctx =
    match xs with
    | [] -> listRev ys, acc, ctx
    | x :: xs ->
        let y, acc, ctx = f (x, acc, ctx)
        go (y :: ys) xs acc ctx

  go [] xs acc ctx

// -----------------------------------------------
// Option
// -----------------------------------------------

let optionIsNone option =
  match option with
  | None -> true

  | Some _ -> false

let optionDefaultValue alt option =
  match option with
  | Some x -> x

  | None -> alt

// -----------------------------------------------
// List
// -----------------------------------------------

let cons head tail = head :: tail

let listIsEmpty xs =
  match xs with
  | [] -> true

  | _ -> false

let listLength xs =
  let rec go len xs =
    match xs with
    | [] -> len

    | _ :: xs -> go (len + 1) xs

  go 0 xs

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> go (x :: acc) xs

  go [] xs

let rec listIter f xs =
  match xs with
  | [] -> ()

  | x :: xs ->
      f x
      listIter f xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] -> listRev acc

    | x :: xs -> go (f x :: acc) xs

  go [] xs

let listMapWithIndex f xs =
  let rec go acc i xs =
    match xs with
    | [] -> listRev acc

    | x :: xs -> go (f i x :: acc) (i + 1) xs

  go [] 0 xs

let listFilter pred xs =
  let rec go acc xs =
    match xs with
    | [] -> listRev acc

    | x :: xs ->
        let acc = if pred x then x :: acc else acc
        go acc xs

  go [] xs

let listChoose f xs =
  let rec go acc xs =
    match xs with
    | [] -> listRev acc

    | x :: xs ->
        let acc =
          match f x with
          | Some y -> y :: acc

          | None -> acc

        go acc xs

  go [] xs

let listCollect f xs =
  let rec gogo acc ys =
    match ys with
    | [] -> acc

    | y :: ys -> gogo (y :: acc) ys

  let rec go acc xs =
    match xs with
    | [] -> listRev acc

    | x :: xs ->
        let acc = gogo acc (f x)
        go acc xs

  go [] xs

let listForAll pred xs =
  let rec go xs =
    match xs with
    | [] -> true

    | x :: xs -> pred x && go xs

  go xs

let listExists pred xs =
  let rec go xs =
    match xs with
    | [] -> false

    | x :: xs -> pred x || go xs

  go xs

/// USAGE: `items |> listFold (fun state item -> nextState) initialState`
let listFold folder state xs =
  let rec go state xs =
    match xs with
    | [] -> state

    | x :: xs -> go (folder state x) xs

  go state xs

let listReduce reducer xs =
  match xs with
  | [] -> failwith "listReduce: empty"

  | x :: xs -> listFold reducer x xs

let listLast xs =
  let rec go xs =
    match xs with
    | [] -> failwith "listLast: empty"

    | [ x ] -> x

    | _ :: xs -> go xs

  go xs

let listTryFind pred xs =
  let rec go xs =
    match xs with
    | [] -> None

    | x :: _ when pred x -> Some x

    | _ :: xs -> go xs

  go xs

let listTryPick f xs =
  let rec go xs =
    match xs with
    | [] -> None

    | x :: xs ->
        match f x with
        | Some x -> Some x
        | None -> go xs

  go xs

let listSkip count xs =
  let rec go count xs =
    match xs with
    | [] -> []

    | _ when count <= 0 -> xs

    | _ :: xs -> go (count - 1) xs

  go count xs

let listTruncate count xs =
  let rec go acc count xs =
    match xs with
    | [] -> listRev acc

    | _ when count <= 0 -> listRev acc

    | x :: xs -> go (x :: acc) (count - 1) xs

  go [] count xs

let listAppend xs ys =
  let rec go acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> go (x :: acc) xs

  go ys (listRev xs)

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
      (xs, n), listSkip n xs, 0
    else
      let m = n / 2
      let (xs, xn), xs1, d1 = go (xs, m)
      let (ys, yn), ys1, d2 = go (xs1, n - m)
      let (zs, zn), d3 = merge ([], 0) 0 (xs, xn) (ys, yn)
      (zs, zn), ys1, d1 + d2 + d3

  let xn = listLength xs
  let (zs, zn), ws, d = go (xs, xn)
  assert (zn + d = xn)
  assert (ws |> listIsEmpty)
  listTruncate zn zs

let listSort cmp xs = listSortCore false cmp xs

let listUnique cmp xs = listSortCore true cmp xs

// -----------------------------------------------
// Assoc
// -----------------------------------------------

let assocAdd key value assoc = (key, value) :: assoc

let assocRemove cmp key assoc =
  let rec go acc assoc =
    match assoc with
    | [] -> listRev acc

    | (k, _) :: assoc when cmp k key = 0 -> go acc assoc

    | kv :: assoc -> go (kv :: acc) assoc

  go [] assoc

let assocTryFind cmp key assoc =
  let rec go assoc =
    match assoc with
    | [] -> None

    | (k, v) :: _ when cmp k key = 0 -> Some v

    | _ :: assoc -> go assoc

  go assoc

let assocFold folder state assoc =
  let rec go state assoc =
    match assoc with
    | [] -> state

    | (k, v) :: assoc -> go (folder state k v) assoc

  go state assoc

let assocMap f assoc =
  let rec go acc assoc =
    match assoc with
    | [] -> listRev acc

    | (k, v) :: assoc -> go ((k, f k v) :: acc) assoc

  go [] assoc

let assocFilter pred assoc =
  let rec go acc assoc =
    match assoc with
    | [] -> listRev acc

    | ((k, v) as kv) :: assoc ->
        let acc = if pred k v then (kv :: acc) else acc
        go acc assoc

  go [] assoc

let assocToKeyAcc acc assoc =
  let rec go acc assoc =
    match assoc with
    | [] -> acc

    | (k, _) :: assoc -> go (k :: acc) assoc

  go acc assoc

// -----------------------------------------------
// HashTrie
// -----------------------------------------------

let trieAdd (keyHash: int) key value trie =
  let rec go trie =
    match trie with
    | [] -> [ keyHash, [ key, value ] ]

    | (h, assoc) :: trie when h = keyHash -> (keyHash, assocAdd key value assoc) :: trie

    | kv :: trie -> kv :: go trie

  go trie

let trieRemove cmp (keyHash: int) key trie =
  let rec go trie =
    match trie with
    | [] -> []

    | (h, assoc) :: trie when h = keyHash -> (keyHash, assocRemove cmp key assoc) :: trie

    | kv :: trie -> kv :: go trie

  go trie

let trieTryFind cmp (keyHash: int) key trie =
  let rec go trie =
    match trie with
    | [] -> None

    | (h, assoc) :: _ when h = keyHash -> assocTryFind cmp key assoc

    | _ :: trie -> go trie

  go trie

let trieMap f trie =
  let rec go trie =
    match trie with
    | [] -> []

    | (h, assoc) :: trie -> (h, assocMap f assoc) :: go trie

  go trie

let tireFilter pred trie =
  let rec go trie =
    match trie with
    | [] -> []

    | (h, assoc) :: trie -> (h, assocFilter pred assoc) :: go trie

  go trie

let trieToKeys trie =
  let rec go acc trie =
    match trie with
    | [] -> acc

    | (_, assoc) :: trie -> go (assocToKeyAcc acc assoc) trie

  go [] trie

// -----------------------------------------------
// AssocMap
// -----------------------------------------------

let mapEmpty (hash, cmp): AssocMap<_, _> = [], hash, cmp

let mapAdd key value (trie, hash, cmp): AssocMap<_, _> =
  let trie = trie |> trieAdd (hash key) key value
  trie, hash, cmp

let mapRemove key (trie, hash, cmp): AssocMap<_, _> =
  let trie = trie |> trieRemove cmp (hash key) key
  trie, hash, cmp

let mapTryFind key ((trie, hash, cmp): AssocMap<_, _>) = trie |> trieTryFind cmp (hash key) key

let mapFind key map =
  match mapTryFind key map with
  | Some value -> value

  | None -> failwithf "mapFind: missing key (%A)" key

let mapContainsKey key map =
  match mapTryFind key map with
  | Some _ -> true

  | None -> false

let mapFold folder state (map: AssocMap<_, _>) =
  map |> mapToList |> assocFold folder state

let mapMap f (trie, hash, cmp): AssocMap<_, _> =
  let trie = trieMap f trie
  trie, hash, cmp

let mapFilter pred (trie, hash, cmp): AssocMap<_, _> =
  let trie = tireFilter pred trie
  trie, hash, cmp

let mapToKeys ((trie, _, cmp): AssocMap<_, _>) = trie |> trieToKeys |> listUnique cmp

let mapToList (map: AssocMap<_, _>) =
  let trie, _, cmp = map

  let rec go acc keys =
    match keys with
    | [] -> acc

    | key :: keys -> go ((key, mapFind key map) :: acc) keys

  // Sort in reversed order and re-reverse it with `go`.
  trie
  |> trieToKeys
  |> listUnique (fun l r -> cmp r l)
  |> go []

let mapOfKeys (hash, cmp) value keys: AssocMap<_, _> =
  /// Partition a key list by hash to acc/rest.
  let rec group keyHash acc others keys =
    match keys with
    | [] -> acc, others

    | key :: keys ->
        if hash key = keyHash
        then group keyHash ((key, value) :: acc) others keys
        else group keyHash acc (key :: others) keys

  let rec go trie keys =
    match keys with
    | [] -> trie

    | key :: keys ->
        let h = hash key
        let acc, keys = group h [ (key, value) ] [] keys
        go ((h, acc) :: trie) keys

  let trie = go [] keys
  trie, hash, cmp

let mapOfList (hash, cmp) assoc: AssocMap<_, _> =
  /// Partition an assoc by hash of key to acc/rest.
  let rec group keyHash acc others assoc =
    match assoc with
    | [] -> acc, others

    | ((key, _) as kv) :: assoc ->
        if hash key = keyHash then group keyHash (kv :: acc) others assoc else group keyHash acc (kv :: others) assoc

  let rec go trie assoc =
    match assoc with
    | [] -> trie

    | ((key, _) as kv) :: assoc ->
        let h = hash key
        let acc, assoc = group h [ kv ] [] assoc
        go ((h, acc) :: trie) assoc

  let trie = go [] assoc
  trie, hash, cmp

// -----------------------------------------------
// AssocSet
// -----------------------------------------------

let setEmpty funs: AssocSet<_> = mapEmpty funs

let setContains key (set: AssocSet<_>) = set |> mapContainsKey key

let setToList (set: AssocSet<_>) = set |> mapToKeys

let setOfList (hash, cmp) xs: AssocSet<_> = mapOfKeys (hash, cmp) () xs

let setAdd key set: AssocSet<_> = mapAdd key () set

let setDiff ((trie, hash, cmp): AssocSet<_>) (second: AssocSet<_>): AssocSet<_> =
  let rec filter acc assoc =
    match assoc with
    | [] -> listRev acc

    | (key, ()) :: assoc when setContains key second -> filter acc assoc

    | kv :: assoc -> filter (kv :: acc) assoc

  let rec go trie =
    match trie with
    | [] -> []

    | (h, assoc) :: trie ->
        let assoc = filter [] assoc
        (h, assoc) :: go trie

  let trie = go trie
  trie, hash, cmp

let setFold folder state (set: AssocSet<_>) =
  set |> setToList |> listFold folder state

// -----------------------------------------------
// Int
// -----------------------------------------------

let intMin (x: int) (y: int) = if x > y then y else x

let intMax (x: int) (y: int) = if x < y then y else x

let intEq (x: int) (y: int) = x = y

let intCmp (x: int) (y: int) =
  if y < x then 1
  else if y = x then 0
  else -1

let intHash (x: int) = x % 512

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

let hashCombine (first: int) (second: int) = first * 3 + second

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

let strCmp (x: string) (y: string) =
  if y < x then 1
  else if y = x then 0
  else -1

let strHash (x: string) =
  let step = 1 + x.Length / 128

  let rec go h (i: int) =
    if i >= x.Length then h else go (h * 31 + int x.[i]) (i + step)

  go 17 0

let strSlice (start: int) (endIndex: int) (s: string): string =
  assert (start <= endIndex && endIndex <= s.Length)
  if start >= endIndex then "" else s.[start..endIndex - 1]

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
    | x :: xs when xn = 1 -> x, xs
    | x :: y :: xs when xn = 2 -> x + y, xs
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

  if str |> strNeedsEscaping |> not then str else go [] 0 |> listRev |> strConcat

// -----------------------------------------------
// Position
// -----------------------------------------------

/// No position information. Should be fixed.
let noPos = -1, -1

let posX ((_, x): Pos) = x

let posY ((y, _): Pos) = y

let posIsSameRow first second = posY first = posY second

let posIsSameColumn first second = posX first = posX second

/// Gets if `secondPos` is inside of the block of `firstPos`.
let posInside (firstPos: Pos) (secondPos: Pos) = posX firstPos <= posX secondPos

let posAddX dx ((y, x): Pos) = y, x + dx

let posMax ((firstY, firstX): Pos) ((secondY, secondX): Pos) =
  intMax firstY secondY, intMax firstX secondX

let posToString ((y, x): Pos) = string (y + 1) + ":" + string (x + 1)

let posCmp (firstY, firstX) (secondY, secondX) =
  if firstY <> secondY then intCmp firstY secondY else intCmp firstX secondX

// -----------------------------------------------
// Location
// -----------------------------------------------

/// No location information. Should be fixed.
let noLoc = "<noLoc>", -1, -1

let locToString ((docId, y, x): Loc) =
  docId
  + ":"
  + string (y + 1)
  + ":"
  + string (x + 1)

let locCmp (firstDoc, firstY, firstX) (secondDoc, secondY, secondX) =
  let c = strCmp firstDoc secondDoc
  if c <> 0 then
    c
  else

  if firstY <> secondY then
    intCmp firstY secondY
  else
    intCmp firstX secondX

// -----------------------------------------------
// Token
// -----------------------------------------------

/// Gets if a token is in the first set of expressions/patterns,
/// i.e. whether it can be the first token of an expression or pattern.
let tokenIsExprOrPatFirst (token: Token) =
  match token with
  | IntToken _
  | CharToken _
  | StrToken _
  | IdentToken _
  | LeftParenToken
  | LeftBracketToken
  | FalseToken
  | TrueToken -> true

  | _ -> false

/// Gets if a token is in the first set of expressions.
let tokenIsExprFirst (token: Token) =
  match token with
  | _ when tokenIsExprOrPatFirst token -> true

  | MinusToken
  | IfToken
  | MatchToken
  | FunToken
  | DoToken
  | LetToken
  | TypeToken
  | OpenToken -> true

  | _ -> false

/// In the first set of arguments?
let tokenIsArgFirst (token: Token) =
  match token with
  | MinusToken -> false

  | _ -> tokenIsExprFirst token

let tokenIsPatFirst (token: Token) = tokenIsExprOrPatFirst token

let tokenAsVis token =
  match token with
  | PrivateToken -> Some PrivateVis
  | InternalToken
  | PublicToken -> Some PublicVis

  | _ -> None

// -----------------------------------------------
// Bp
// -----------------------------------------------

let bpNext bp =
  match bp with
  | OrBp -> AndBp

  | AndBp -> CmpBp

  | CmpBp -> PipeBp

  | PipeBp -> ConsBp

  | ConsBp -> AddBp

  | AddBp -> MulBp

  | MulBp
  | PrefixBp -> PrefixBp

// -----------------------------------------------
// APat
// -----------------------------------------------

let apFalse loc = ALitPat(litFalse, loc)

let apTrue loc = ALitPat(litTrue, loc)

// -----------------------------------------------
// AExpr
// -----------------------------------------------

let axUnit loc = ATupleExpr([], loc)

let axFalse loc = ALitExpr(litFalse, loc)

let axTrue loc = ALitExpr(litTrue, loc)

let axNil loc = AListExpr([], loc)

let axApp3 f x1 x2 x3 loc =
  let app x f = ABinaryExpr(AppBinary, f, x, loc)
  f |> app x1 |> app x2 |> app x3

/// `not x` ==> `x = false`
let axNot arg loc =
  let falseExpr = axFalse loc
  ABinaryExpr(EqualBinary, arg, falseExpr, loc)

// -----------------------------------------------
// DumpTree (for debugging)
// -----------------------------------------------

let dumpTreeNew text children = DumpTree(text, children, [])

let dumpTreeNewLeaf text = DumpTree(text, [], [])

let dumpTreeAttachNext next tree =
  match tree with
  | DumpTree (text, children, oldNext) ->
      assert (children |> listIsEmpty |> not)
      assert (oldNext |> listIsEmpty)
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
  [] |> go eol node |> listRev |> strConcat

// -----------------------------------------------
// Name context
// -----------------------------------------------

let nameCtxEmpty () = NameCtx(mapEmpty (intHash, intCmp), 0)

let nameCtxAdd ident (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> mapAdd serial ident
  serial, NameCtx(map, serial)

// -----------------------------------------------
// NameTree
// -----------------------------------------------

// FIXME: this emits code that doesn't compile due to use of incomplete type
//   > error: invalid use of undefined type ‘struct UnitNameTree_Fun1’
//   >        struct NameTree_ app_193 = nameTreeEmpty_.fun(nameTreeEmpty_.env, 0);
// let nameTreeEmpty: unit -> NameTree =
//   let it = NameTree(mapEmpty (intHash, intCmp))
//   fun () -> it

let nameTreeEmpty (): NameTree = NameTree(mapEmpty (intHash, intCmp))

let nameTreeTryFind (key: Serial) (NameTree map): Serial list =
  match map |> mapTryFind key with
  | Some values -> values

  | None -> []

let nameTreeAdd (key: Serial) (value: Serial) (NameTree map): NameTree =
  let map =
    match map |> mapTryFind key with
    | Some values -> map |> mapAdd key (value :: values)

    | None -> map |> mapAdd key [ value ]

  NameTree map

// -----------------------------------------------
// TyCtor
// -----------------------------------------------

let tyCtorToInt tyCtor =
  match tyCtor with
  | BoolTyCtor -> 1

  | IntTyCtor -> 2

  | CharTyCtor -> 3

  | StrTyCtor -> 4

  | ObjTyCtor -> 5

  | FunTyCtor -> 6

  | TupleTyCtor -> 7

  | ListTyCtor -> 8

  | RefTyCtor tySerial ->
      assert (tySerial >= 0)
      9 + tySerial

let tyCtorHash tyCtor = tyCtor |> tyCtorToInt |> intHash

let tyCtorCmp first second =
  intCmp (tyCtorToInt first) (tyCtorToInt second)

let tyCtorEq first second = tyCtorCmp first second = 0

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | AddTrait ty -> AddTrait(f ty)

  | EqTrait ty -> EqTrait(f ty)

  | CmpTrait ty -> CmpTrait(f ty)

  | IndexTrait (lTy, rTy, outputTy) -> IndexTrait(f lTy, f rTy, f outputTy)

  | ToIntTrait ty -> ToIntTrait(f ty)

  | ToStringTrait ty -> ToStringTrait(f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

/// Placeholder. No type info in the parsing phase.
let noTy = ErrorTy noLoc

let tyBool = AppTy(BoolTyCtor, [])

let tyInt = AppTy(IntTyCtor, [])

let tyChar = AppTy(CharTyCtor, [])

let tyStr = AppTy(StrTyCtor, [])

let tyObj = AppTy(ObjTyCtor, [])

let tyTuple tys = AppTy(TupleTyCtor, tys)

let tyList ty = AppTy(ListTyCtor, [ ty ])

let tyFun sourceTy targetTy =
  AppTy(FunTyCtor, [ sourceTy; targetTy ])

let tyUnit = tyTuple []

let tyRef serial tys = AppTy(RefTyCtor serial, tys)

let tyAssocMap keyTy valueTy =
  let assocTy = tyList (tyTuple [ keyTy; valueTy ])
  let trieTy = tyList (tyTuple [ tyInt; assocTy ])
  let hashTy = tyFun keyTy tyInt
  let cmpTy = tyFun keyTy (tyFun keyTy tyInt)
  tyTuple [ trieTy; hashTy; cmpTy ]

let tyToHash ty =
  match ty with
  | ErrorTy (docId, y, x) ->
      1
      |> hashCombine (strHash docId)
      |> hashCombine y
      |> hashCombine x

  | MetaTy (tySerial, _) -> intHash (2 + tySerial)

  | AppTy (tyCtor, tys) ->
      let rec go h tys =
        match tys with
        | [] -> h

        | ty :: tys -> go (hashCombine h (tyToHash ty)) tys

      intHash (3 + go (tyCtorHash tyCtor) tys)

let tyCmp first second =
  match first, second with
  | ErrorTy first, ErrorTy second -> locCmp first second

  | ErrorTy _, _ -> -1

  | _, ErrorTy _ -> 1

  | MetaTy (firstSerial, firstLoc), MetaTy (secondSerial, secondLoc) ->
      if firstSerial <> secondSerial then intCmp firstSerial secondSerial else locCmp firstLoc secondLoc

  | MetaTy _, _ -> -1

  | _, MetaTy _ -> 1

  | AppTy (firstTyCtor, firstTys), AppTy (secondTyCtor, secondTys) ->
      let c = tyCtorCmp firstTyCtor secondTyCtor
      if c <> 0 then
        c
      else
        let rec go firstTys secondTys =
          match firstTys, secondTys with
          | [], [] -> 0

          | [], _ -> -1

          | _, [] -> 1

          | firstTy :: firstTys, secondTy :: secondTys ->
              let c = tyCmp firstTy secondTy
              if c <> 0 then c else go firstTys secondTys

        go firstTys secondTys

let tyEq first second = tyCmp first second = 0

let tyPrimFromIdent ident tys loc =
  match ident, tys with
  | "unit", [] -> tyUnit

  | "bool", [] -> tyBool

  | "int", [] -> tyInt

  | "char", [] -> tyChar

  | "string", [] -> tyStr

  | "obj", [] -> tyObj

  | "option", [ itemTy ] ->
      // FIXME: option is just an alias of list for now
      tyList itemTy

  | "list", [ itemTy ] -> tyList itemTy

  | "AssocMap", [ keyTy; valueTy ] -> tyAssocMap keyTy valueTy

  | "AssocSet", [ itemTy ] -> tyAssocMap itemTy tyUnit

  | _ -> ErrorTy loc

/// Gets if the specified type variable doesn't appear in a type.
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | ErrorTy _
    | AppTy (_, []) -> true

    | AppTy (tyCtor, ty :: tys) -> go ty && go (AppTy(tyCtor, tys))

    | MetaTy (s, _) -> s <> tySerial

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty: bool =
  let rec go tys =
    match tys with
    | [] -> true

    | MetaTy _ :: _ -> false

    | ErrorTy _ :: tys -> go tys

    | AppTy (_, tys1) :: tys2 -> go tys1 && go tys2

  go [ ty ]

/// Gets a list of type variables.
/// Assume all bound type variables are substituted.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] -> fvAcc

    | ErrorTy _ :: tys
    | AppTy (_, []) :: tys -> go fvAcc tys

    | AppTy (_, tys1) :: tys2 ->
        let acc = go fvAcc tys1
        let acc = go acc tys2
        acc

    | MetaTy (serial, _) :: tys ->
        let acc = serial :: fvAcc
        go acc tys

  go [] [ ty ] |> listUnique intCmp

let rec tyToArity ty =
  match ty with
  | AppTy (FunTyCtor, [ _; ty ]) -> 1 + tyToArity ty
  | _ -> 0

/// Converts nested function type to multi-arguments function type.
let rec tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | AppTy (FunTyCtor, [ sTy; tTy ]) -> go (n + 1) (sTy :: acc) tTy
    | tTy -> n, listRev acc, tTy

  go 0 [] ty

/// Substitutes meta types in a type as possible.
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec go ty =
    match ty with
    | ErrorTy _
    | AppTy (_, []) -> ty

    | AppTy (tyCtor, tys) -> AppTy(tyCtor, listMap go tys)

    | MetaTy (tySerial, _) ->
        match substMeta tySerial with
        | Some ty -> go ty

        | None -> ty

  go ty

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let tyDefToIdent tyDef =
  match tyDef with
  | MetaTyDef (ident, _, _) -> ident
  | UnionTyDef (ident, _, _) -> ident
  | ModuleTyDef (ident, _) -> ident

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varDefToIdent varDef =
  match varDef with
  | VarDef.Var (ident, _, _, _) -> ident
  | VarDef.Fun (ident, _, _, _) -> ident
  | VarDef.Variant (ident, _, _, _, _, _) -> ident

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litTrue = BoolLit true

let litFalse = BoolLit false

let litToTy (lit: Lit): Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | CharLit _ -> tyChar
  | StrLit _ -> tyStr

// -----------------------------------------------
// Primitives (HIR)
// -----------------------------------------------

let primFromIdent ident =
  match ident with
  | "not" -> HPrim.Not |> Some

  | "exit" -> HPrim.Exit |> Some

  | "assert" -> HPrim.Assert |> Some

  | "box" -> HPrim.Box |> Some

  | "unbox" -> HPrim.Unbox |> Some

  | "printfn" -> HPrim.Printfn |> Some

  | "char" -> HPrim.Char |> Some

  | "int" -> HPrim.Int |> Some

  | "string" -> HPrim.String |> Some

  | "None" -> HPrim.OptionNone |> Some

  | "Some" -> HPrim.OptionSome |> Some

  | "inRegion" -> HPrim.InRegion |> Some

  | "__nativeFun" -> HPrim.NativeFun("<native-fun>", -1) |> Some

  | _ -> None

let primToTySpec prim =
  let meta id = MetaTy(id, noLoc)
  let mono ty = TySpec(ty, [])
  let poly ty traits = TySpec(ty, traits)

  match prim with
  | HPrim.Add ->
      let addTy = meta 1
      poly (tyFun addTy (tyFun addTy addTy)) [ AddTrait addTy ]

  | HPrim.Sub -> mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Mul -> mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Div -> mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Mod -> mono (tyFun tyInt (tyFun tyInt tyInt))

  | HPrim.Eq ->
      let eqTy = meta 1
      poly (tyFun eqTy (tyFun eqTy tyBool)) [ EqTrait eqTy ]

  | HPrim.Lt ->
      let cmpTy = meta 1
      poly (tyFun cmpTy (tyFun cmpTy tyBool)) [ CmpTrait cmpTy ]

  | HPrim.Nil ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.Cons ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy (tyFun listTy listTy)) []

  | HPrim.OptionNone ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.OptionSome ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy listTy) []

  | HPrim.Index ->
      let lTy = meta 1
      let rTy = meta 2
      let resultTy = meta 3
      poly (tyFun lTy (tyFun rTy resultTy)) [ IndexTrait(lTy, rTy, resultTy) ]

  | HPrim.Not -> mono (tyFun tyBool tyBool)

  | HPrim.Exit ->
      let resultTy = meta 1
      poly (tyFun tyInt resultTy) []

  | HPrim.Assert -> mono (tyFun tyBool tyUnit)

  | HPrim.Box ->
      let itemTy = meta 1
      poly (tyFun itemTy tyObj) []

  | HPrim.Unbox ->
      let itemTy = meta 1
      poly (tyFun tyObj itemTy) []

  | HPrim.Char ->
      // FIXME: `char` can take non-int types.
      mono (tyFun tyInt tyChar)

  | HPrim.Int ->
      let toIntTy = meta 1
      poly (tyFun toIntTy tyInt) [ ToIntTrait toIntTy ]

  | HPrim.String ->
      let toStrTy = meta 1
      poly (tyFun toStrTy tyStr) [ ToStringTrait toStrTy ]

  | HPrim.StrLength -> mono (tyFun tyStr tyInt)

  | HPrim.StrGetSlice -> mono (tyFun tyInt (tyFun tyInt (tyFun tyStr tyStr)))

  | HPrim.InRegion -> mono (tyFun (tyFun tyUnit tyInt) tyInt)

  | HPrim.Printfn
  | HPrim.NativeFun _ -> poly (meta 1) []

let primToArity ty prim =
  match prim with
  | HPrim.Nil
  | HPrim.OptionNone -> 0
  | HPrim.OptionSome
  | HPrim.Not
  | HPrim.Exit
  | HPrim.Assert
  | HPrim.Box
  | HPrim.Unbox
  | HPrim.StrLength
  | HPrim.Char
  | HPrim.Int
  | HPrim.String
  | HPrim.InRegion -> 1
  | HPrim.Add
  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Mod
  | HPrim.Eq
  | HPrim.Lt
  | HPrim.Cons
  | HPrim.Index -> 2
  | HPrim.StrGetSlice -> 3
  | HPrim.Printfn -> ty |> tyToArity
  | HPrim.NativeFun (_, arity) -> arity

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let patUnit loc = HPat.Tuple([], tyUnit, loc)

let patNil itemTy loc = HPat.Nil(itemTy, loc)

let rec patExtract (pat: HPat): Ty * Loc =
  match pat with
  | HPat.Lit (lit, a) -> litToTy lit, a
  | HPat.Nil (itemTy, a) -> tyList itemTy, a
  | HPat.OptionNone (itemTy, a) -> tyList itemTy, a
  | HPat.OptionSome (itemTy, a) -> tyList itemTy, a
  | HPat.Discard (ty, a) -> ty, a
  | HPat.Ref (_, ty, a) -> ty, a
  | HPat.Nav (_, _, ty, a) -> ty, a
  | HPat.Call (_, _, ty, a) -> ty, a
  | HPat.Cons (_, _, itemTy, a) -> tyList itemTy, a
  | HPat.Tuple (_, ty, a) -> ty, a
  | HPat.As (pat, _, a) ->
      let ty, _ = patExtract pat
      ty, a
  | HPat.Anno (_, ty, a) -> ty, a
  | HPat.Or (_, _, ty, a) -> ty, a

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat): HPat =
  let rec go pat =
    match pat with
    | HPat.Lit (lit, a) -> HPat.Lit(lit, g a)
    | HPat.Nil (itemTy, a) -> HPat.Nil(f itemTy, g a)
    | HPat.OptionNone (itemTy, a) -> HPat.OptionNone(f itemTy, g a)
    | HPat.OptionSome (itemTy, a) -> HPat.OptionSome(f itemTy, g a)
    | HPat.Discard (ty, a) -> HPat.Discard(f ty, g a)
    | HPat.Ref (serial, ty, a) -> HPat.Ref(serial, f ty, g a)
    | HPat.Nav (pat, ident, ty, a) -> HPat.Nav(go pat, ident, f ty, g a)
    | HPat.Call (callee, args, ty, a) -> HPat.Call(go callee, listMap go args, f ty, g a)
    | HPat.Cons (l, r, itemTy, a) -> HPat.Cons(go l, go r, f itemTy, g a)
    | HPat.Tuple (itemPats, ty, a) -> HPat.Tuple(listMap go itemPats, f ty, g a)
    | HPat.As (pat, serial, a) -> HPat.As(go pat, serial, g a)
    | HPat.Anno (pat, ty, a) -> HPat.Anno(go pat, f ty, g a)
    | HPat.Or (first, second, ty, a) -> HPat.Or(go first, go second, f ty, g a)

  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HPat.Lit _
    | HPat.Discard _
    | HPat.Ref _
    | HPat.Nil _
    | HPat.OptionNone _
    | HPat.OptionSome _ -> [ pat ]
    | HPat.Nav (pat, ident, ty, loc) ->
        go pat
        |> listMap (fun pat -> HPat.Nav(pat, ident, ty, loc))
    | HPat.Call (callee, [ arg ], ty, loc) ->
        go callee
        |> listCollect (fun callee ->
             go arg
             |> listMap (fun arg -> HPat.Call(callee, [ arg ], ty, loc)))
    | HPat.Cons (l, r, ty, loc) ->
        go l
        |> listCollect (fun l ->
             go r
             |> listMap (fun r -> HPat.Cons(l, r, ty, loc)))
    | HPat.Tuple (itemPats, ty, loc) ->
        let rec gogo itemPats =
          match itemPats with
          | [] -> [ [] ]
          | itemPat :: itemPats ->
              let itemPat = go itemPat
              gogo itemPats
              |> listCollect (fun itemPats ->
                   itemPat
                   |> listMap (fun itemPat -> itemPat :: itemPats))

        gogo itemPats
        |> listMap (fun itemPats -> HPat.Tuple(itemPats, ty, loc))
    | HPat.As (innerPat, _, _) ->
        match go innerPat with
        | [ _ ] -> [ pat ]
        | _ -> failwith "Unimpl: Can't use AS patterns conjunction with OR patterns"
    | HPat.Anno (pat, annoTy, loc) ->
        go pat
        |> listMap (fun pat -> HPat.Anno(pat, annoTy, loc))
    | HPat.Or (first, second, _, _) -> listAppend (go first) (go second)
    | HPat.Call _ -> failwith "Unimpl"

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc = HExpr.Lit(litTrue, loc)

let hxFalse loc = HExpr.Lit(litFalse, loc)

let hxApp f x ty loc = HExpr.Inf(InfOp.App, [ f; x ], ty, loc)

let hxAnno expr ty loc = HExpr.Inf(InfOp.Anno, [ expr ], ty, loc)

let hxSemi items loc =
  HExpr.Inf(InfOp.Semi, items, exprToTy (listLast items), loc)

let hxCallProc callee args resultTy loc =
  HExpr.Inf(InfOp.CallProc, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HExpr.Inf(InfOp.CallClosure, callee :: args, resultTy, loc)

let hxTuple items loc =
  HExpr.Inf(InfOp.Tuple, items, tyTuple (listMap exprToTy items), loc)

let hxUnit loc = hxTuple [] loc

let hxNil itemTy loc =
  HExpr.Prim(HPrim.Nil, tyList itemTy, loc)

let hxIsUnitLit expr =
  match expr with
  | HExpr.Inf (InfOp.Tuple, [], _, _) -> true
  | _ -> false

let hxIsAlwaysTrue expr =
  match expr with
  | HExpr.Lit (BoolLit true, _) -> true
  | _ -> false

let exprExtract (expr: HExpr): Ty * Loc =
  match expr with
  | HExpr.Lit (lit, a) -> litToTy lit, a
  | HExpr.Ref (_, ty, a) -> ty, a
  | HExpr.Prim (_, ty, a) -> ty, a
  | HExpr.Match (_, _, ty, a) -> ty, a
  | HExpr.Nav (_, _, ty, a) -> ty, a
  | HExpr.Inf (_, _, ty, a) -> ty, a
  | HExpr.Let (_, _, _, _, ty, a) -> ty, a
  | HExpr.LetFun (_, _, _, _, _, _, ty, a) -> ty, a
  | HExpr.TyDecl (_, _, _, a) -> tyUnit, a
  | HExpr.Open (_, a) -> tyUnit, a
  | HExpr.Module (_, _, _, a) -> tyUnit, a
  | HExpr.Error (_, a) -> ErrorTy a, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr): HExpr =
  let goPat pat = patMap f g pat

  let rec go expr =
    match expr with
    | HExpr.Lit (lit, a) -> HExpr.Lit(lit, g a)
    | HExpr.Ref (serial, ty, a) -> HExpr.Ref(serial, f ty, g a)
    | HExpr.Prim (prim, ty, a) -> HExpr.Prim(prim, f ty, g a)
    | HExpr.Match (target, arms, ty, a) ->
        let arms =
          arms
          |> listMap (fun (pat, guard, body) -> goPat pat, go guard, go body)

        HExpr.Match(go target, arms, f ty, g a)
    | HExpr.Nav (sub, mes, ty, a) -> HExpr.Nav(go sub, mes, f ty, g a)
    | HExpr.Inf (infOp, args, resultTy, a) -> HExpr.Inf(infOp, listMap go args, f resultTy, g a)
    | HExpr.Let (vis, pat, init, next, ty, a) -> HExpr.Let(vis, goPat pat, go init, go next, f ty, g a)
    | HExpr.LetFun (serial, vis, isMainFun, args, body, next, ty, a) ->
        HExpr.LetFun(serial, vis, isMainFun, listMap goPat args, go body, go next, f ty, g a)
    | HExpr.TyDecl (serial, vis, tyDef, a) -> HExpr.TyDecl(serial, vis, tyDef, g a)
    | HExpr.Open (path, a) -> HExpr.Open(path, g a)
    | HExpr.Module (ident, body, next, a) -> HExpr.Module(ident, go body, go next, g a)
    | HExpr.Error (error, a) -> HExpr.Error(error, g a)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

// -----------------------------------------------
// Binary Operators (MIR)
// -----------------------------------------------

let mOpIsAdd op =
  match op with
  | MAddBinary -> true

  | _ -> false

let opIsComparison op =
  match op with
  | MEqualBinary
  | MLessBinary -> true
  | _ -> false

// -----------------------------------------------
// Expressions (MIR)
// -----------------------------------------------

let mxNot expr loc = MUnaryExpr(MNotUnary, expr, tyBool, loc)

let mexprExtract expr =
  match expr with
  | MDefaultExpr (ty, loc) -> ty, loc
  | MLitExpr (lit, loc) -> litToTy lit, loc
  | MRefExpr (_, ty, loc) -> ty, loc
  | MProcExpr (_, ty, loc) -> ty, loc
  | MVariantExpr (_, _, ty, loc) -> ty, loc
  | MUnaryExpr (_, _, ty, loc) -> ty, loc
  | MBinaryExpr (_, _, _, ty, loc) -> ty, loc

let mexprToTy expr =
  let ty, _ = mexprExtract expr
  ty

// -----------------------------------------------
// Statements (MIR)
// -----------------------------------------------

let msGotoUnless pred label loc =
  let notPred = mxNot pred loc
  MGotoIfStmt(notPred, label, loc)

// -----------------------------------------------
// Expression sugaring (MIR)
// -----------------------------------------------

let rec mxSugar expr =
  let mxSugarUni op l ty loc =
    match l with
    // SUGAR: `not true` ==> `false`
    // SUGAR: `not false` ==> `true`
    | MLitExpr (BoolLit value, loc) -> MLitExpr(BoolLit(not value), loc)

    // SUGAR: `not (not x)` ==> `x`
    | MUnaryExpr (MNotUnary, l, _, _) -> l

    // SUGAR: `not (x = y)` ==> `x <> y`
    | MBinaryExpr (MEqualBinary, l, r, ty, loc) -> MBinaryExpr(MNotEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x <> y)` ==> `x = y`
    | MBinaryExpr (MNotEqualBinary, l, r, ty, loc) -> MBinaryExpr(MEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x < y)` ==> `x >= y`
    | MBinaryExpr (MLessBinary, l, r, ty, loc) -> MBinaryExpr(MGreaterEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x >= y)` ==> `x < y`
    | MBinaryExpr (MGreaterEqualBinary, l, r, ty, loc) -> MBinaryExpr(MLessBinary, l, r, ty, loc)

    | _ -> MUnaryExpr(op, l, ty, loc)

  let mxSugarBin op l r ty loc =
    match op, l, r with
    // SUGAR: `x = false` ==> `not x`
    | MEqualBinary, MLitExpr (BoolLit false, _), _ -> mxSugarUni MNotUnary r ty loc

    | MEqualBinary, _, MLitExpr (BoolLit false, _) -> mxSugarUni MNotUnary l ty loc

    // SUGAR: `x = true` ==> `x`
    | MEqualBinary, MLitExpr (BoolLit true, _), _ -> r

    | MEqualBinary, _, MLitExpr (BoolLit true, _) -> l

    | _ -> MBinaryExpr(op, l, r, ty, loc)

  match expr with
  // SUGAR: `x: unit` ==> `()`
  | MRefExpr (_, AppTy (TupleTyCtor, []), loc) -> MDefaultExpr(tyUnit, loc)

  | MUnaryExpr (op, l, ty, loc) ->
      let l = mxSugar l
      mxSugarUni op l ty loc

  | MBinaryExpr (op, l, r, ty, loc) ->
      let l = mxSugar l
      let r = mxSugar r
      mxSugarBin op l r ty loc

  | _ -> expr

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else if i + 1 < format.Length && format.[i] = '%' then
      match format.[i + 1] with
      | 's' -> tyFun tyStr (go (i + 2))
      | 'd' -> tyFun tyInt (go (i + 2))
      | 'c' -> tyFun tyChar (go (i + 2))
      | _ -> go (i + 2)
    else
      go (i + 1)

  tyFun tyStr (go 0)

// -----------------------------------------------
// Type inference algorithm (HIR)
// -----------------------------------------------

/// Adds type-var/type binding.
let typingBind (ctx: TyContext) tySerial ty loc =
  let intInf = 2147483647

  // FIXME: track identifier
  let noIdent = "unknown"

  // Don't bind itself.
  match typingSubst ctx ty with
  | MetaTy (s, _) when s = tySerial -> ctx
  | ty ->

      // Update depth of all related meta types to the minimum.
      let tyDepths =
        let tySerials = tySerial :: tyCollectFreeVars ty

        let depth =
          tySerials
          |> listMap (fun tySerial -> ctx |> tyContextGetTyDepths |> mapFind tySerial)
          |> listFold intMin intInf

        tySerials
        |> listFold (fun tyDepths tySerial -> tyDepths |> mapAdd tySerial depth) (ctx |> tyContextGetTyDepths)

      ctx
      |> tyContextWithTys
           (ctx
            |> tyContextGetTys
            |> mapAdd tySerial (MetaTyDef(noIdent, ty, loc)))
      |> tyContextWithTyDepths tyDepths

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let typingSubst (ctx: TyContext) ty: Ty =
  let substMeta tySerial =
    match ctx |> tyContextGetTys |> mapTryFind tySerial with
    | Some (MetaTyDef (_, ty, _)) -> Some ty
    | _ -> None

  tySubst substMeta ty

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let typingUnify logAcc (ctx: TyContext) (lty: Ty) (rty: Ty) (loc: Loc) =
  let lRootTy, rRootTy = lty, rty

  let addLog kind lTy rTy logAcc ctx =
    let lRootTy = typingSubst ctx lRootTy
    let rRootTy = typingSubst ctx rRootTy
    (Log.TyUnify(kind, lRootTy, rRootTy, lTy, rTy), loc)
    :: logAcc,
    ctx

  let rec go lty rty (logAcc, ctx) =
    let lSubstTy = typingSubst ctx lty
    let rSubstTy = typingSubst ctx rty
    match lSubstTy, rSubstTy with
    | MetaTy (l, _), MetaTy (r, _) when l = r -> logAcc, ctx
    | MetaTy (lSerial, loc), _ when tyIsFreeIn rSubstTy lSerial ->
        let ctx = typingBind ctx lSerial rty loc
        logAcc, ctx
    | _, MetaTy _ -> go rty lty (logAcc, ctx)
    | AppTy (lTyCtor, []), AppTy (rTyCtor, []) when tyCtorEq lTyCtor rTyCtor -> logAcc, ctx
    | AppTy (lTyCtor, lTy :: lTys), AppTy (rTyCtor, rTy :: rTys) ->
        (logAcc, ctx)
        |> go lTy rTy
        |> go (AppTy(lTyCtor, lTys)) (AppTy(rTyCtor, rTys))
    | ErrorTy _, _
    | _, ErrorTy _ -> logAcc, ctx
    | MetaTy _, _ -> addLog TyUnifyLog.SelfRec lSubstTy rSubstTy logAcc ctx
    | AppTy _, _ -> addLog TyUnifyLog.Mismatch lSubstTy rSubstTy logAcc ctx

  go lty rty (logAcc, ctx)

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait =
    theTrait |> traitMapTys (typingSubst ctx)

  let expectScalar ty (logAcc, ctx) =
    match ty with
    | ErrorTy _
    | AppTy (BoolTyCtor, [])
    | AppTy (IntTyCtor, [])
    | AppTy (CharTyCtor, [])
    | AppTy (StrTyCtor, []) -> logAcc, ctx

    | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  match theTrait with
  | AddTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (StrTyCtor, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | EqTrait ty -> (logAcc, ctx) |> expectScalar ty

  | CmpTrait ty -> (logAcc, ctx) |> expectScalar ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | ErrorTy _ -> [], ctx

      | AppTy (StrTyCtor, []) ->
          let logAcc, ctx = typingUnify logAcc ctx rTy tyInt loc

          let logAcc, ctx =
            typingUnify logAcc ctx resultTy tyChar loc

          logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToIntTrait ty -> (logAcc, ctx) |> expectScalar ty

  | ToStringTrait ty -> (logAcc, ctx) |> expectScalar ty

// -----------------------------------------------
// Logs
// -----------------------------------------------

let logToString loc log =
  let loc = loc |> locToString

  match log with
  | Log.TyUnify (TyUnifyLog.SelfRec, _, _, lTy, rTy) ->
      sprintf "%s Couldn't unify '%A' and '%A' due to self recursion." loc lTy rTy

  | Log.TyUnify (TyUnifyLog.Mismatch, lRootTy, rRootTy, lTy, rTy) ->
      sprintf "%s While unifying '%A' and '%A', failed to unify '%A' and '%A'." loc lRootTy rRootTy lTy rTy

  | Log.TyBoundError (AddTrait ty) -> sprintf "%s No support (+) for '%A' yet" loc ty

  | Log.TyBoundError (EqTrait ty) -> sprintf "%s No support equality for '%A' yet" loc ty

  | Log.TyBoundError (CmpTrait ty) -> sprintf "%s No support comparison for '%A' yet" loc ty

  | Log.TyBoundError (IndexTrait (lTy, rTy, _)) ->
      sprintf "%s No support indexing operation (l = '%A', r = '%A')" loc lTy rTy

  | Log.TyBoundError (ToIntTrait ty) -> sprintf "%s Can't convert to int from '%A'" loc ty

  | Log.TyBoundError (ToStringTrait ty) -> sprintf "%s Can't convert to string from '%A'" loc ty

  | Log.Error msg -> sprintf "%s %s" loc msg
