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

// -----------------------------------------------
// DumpTree (for debugging)
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
      let s = "0123456789abcdef" |> strSlice d (d + 1)
      go (s + acc) (len - 1) (n / 16)

  if value = 0 && len = 0 then
    "0"
  else
    go "" len value

let dumpTreeNew text children =
  DumpTree (text, children, [])

let dumpTreeNewLeaf text =
  DumpTree (text, [], [])

let dumpTreeAttachNext next tree =
  match tree with
  | DumpTree (text, children, oldNext) ->
    assert (children |> listIsEmpty |> not)
    assert (oldNext |> listIsEmpty)
    DumpTree (text, children, [next])

let dumpTreeFromError (msg: string) (y, x) =
  let y = string (y + 1)
  let x = string (x + 1)
  dumpTreeNew "ERROR" [
    dumpTreeNewLeaf msg
    dumpTreeNewLeaf ("(" + y + ":" + x + ")")
  ]

let dumpTreeToString (node: DumpTree) =
  let charIsControl (c: char) =
    let n = int c
    0 <= n && n < 32 || n = 127

  let charNeedsEscaping (c: char) =
    charIsControl c || c = '\\' || c = '"' || c = '\''

  let strNeedsEscaping (str: string) =
    let rec go i = i < str.Length && (charNeedsEscaping str.[i] || go (i + 1))
    go 0

  let strEscapeCore (i: int) (str: string) =
    assert (str.[i] |> charNeedsEscaping)

    match str.[i] with
    | '\u0000' ->
      i + 1, "\\0"

    | '\t' ->
      i + 1, "\\t"

    | '\n' ->
      i + 1, "\\n"

    | '\r' ->
      i + 1, "\\r"

    | '\'' ->
      i + 1, "\\\'"

    | '\"' ->
      i + 1, "\\\""

    | '\\' ->
      i + 1, "\\\\"

    | c ->
      let h = c |> int |> intToHexWithPadding 2
      i + 1, "\\x" + h

  let strEscape (str: string) =
    if str |> strNeedsEscaping |> not then
      str
    else

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
        r, (str |> strSlice i r) :: acc

      if i = str.Length then
        acc
      else

      let i, s = strEscapeCore i str
      go (s :: acc) i

    go [] 0 |> listRev |> strConcat

  let rec go eol node acc =
    let rec goChildren eol children acc =
      match children with
      | [] ->
        acc

      | child :: children ->
        acc
        |> cons eol |> cons "- " |> go (eol + "  ") child
        |> goChildren eol children

    let goNext eol next acc =
      match next with
      | [] ->
        acc

      | [next] ->
        acc |> cons eol |> go eol next

      | _ ->
        failwith "NEVER: DumpTree.next never empty"

    match node with
    | DumpTree (text, [], []) ->
      acc |> cons (strEscape text)

    | DumpTree (text, [DumpTree (childText, [], [])], next) ->
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
// Location
// -----------------------------------------------

/// No location information. Should be fixed.
let noLoc = -1, -1

let locX ((_, x): Loc) = x

let locY ((y, _): Loc) = y

let locIsSameRow first second =
  locY first = locY second

let locIsSameColumn first second =
  locX first = locX second

/// Gets if `secondLoc` is inside of the block of `firstLoc`.
let locInside (firstLoc: Loc) (secondLoc: Loc) =
  locX firstLoc <= locX secondLoc

let locAddX dx ((y, x): Loc) =
  y, x + dx

let locMax ((firstY, firstX): Loc) ((secondY, secondX): Loc) =
  intMax firstY secondY, intMax firstX secondX

// -----------------------------------------------
// Token
// -----------------------------------------------

/// Gets if a token is in the first set of expressions/patterns,
/// i.e. whether it can be the first token of an expression or pattern.
let tokenIsExprOrPatFirst (token: Token) =
  match token with
  | Token.Bool _
  | Token.Int _
  | Token.Char _
  | Token.Str _
  | Token.Ident _
  | Token.ParenL
  | Token.BracketL ->
    true

  | _ ->
    false

/// Gets if a token is in the first set of expressions.
let tokenIsExprFirst (token: Token) =
  match token with
  | _ when tokenIsExprOrPatFirst token ->
    true

  | Token.Minus
  | Token.If
  | Token.Match
  | Token.Fun
  | Token.Do
  | Token.Let
  | Token.Type
  | Token.Open ->
    true

  | _ ->
    false

/// In the first set of arguments?
let tokenIsArgFirst (token: Token) =
  match token with
  | Token.Minus ->
    false

  | _ ->
    tokenIsExprFirst token

let tokenIsPatFirst (token: Token) =
  tokenIsExprOrPatFirst token

let tokenIsAccessModifier token =
  match token with
  | Token.Private
  | Token.Internal
  | Token.Public ->
    true

  | _ ->
    false

// -----------------------------------------------
// OpLevel
// -----------------------------------------------

let opLevelToNext level =
  match level with
  | OpLevel.Or ->
    OpLevel.And

  | OpLevel.And ->
    OpLevel.Cmp

  | OpLevel.Cmp ->
    OpLevel.Pipe

  | OpLevel.Pipe ->
    OpLevel.Cons

  | OpLevel.Cons ->
    OpLevel.Add

  | OpLevel.Add ->
    OpLevel.Mul

  | OpLevel.Mul
  | OpLevel.Prefix ->
    OpLevel.Prefix
