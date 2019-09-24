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
