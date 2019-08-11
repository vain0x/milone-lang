//! Lexical analysis.
//! Creates a list of tokens from a text of single file.
//! Consists of two transformations: scan and recognize.

module rec MiloneLang.Lexing

open MiloneLang

// ## Scan
//
// Read the source code from start to end
// to make a mapping from spans to token kinds.
//
// ### Motivation
//
// There are two reasons why I separated the most simplest phase
// in the compiler to two paths:
// 1. Scanning must be written carefully not to access out of range,
//    which makes things complicated unnecessarily
//    such as looking ahead for escape sequence analysis.
// 2. Line number tracking is verbose when it's mixed with
//    scanning multi-line tokens/spaces.
//
// ### Example
//
// Given the source code "let main _ = 0", the scanner should
// build a list of tokens like this:
//
//  0.. 3   Ident   (let)
//  4.. 8   Ident   (main)
//  9..10   Ident   (_)
// 11..12   Op      (=)
// 13..14   IntLit  (0)

/// Kind of token in the scanning phase.
[<RequireQualifiedAccess>]
type TokenKind =
  | Error
  | Ident
  | IntLit
  | CharLit
  | StrLit
  | Op
  | Pun

/// (kind, start, end)
/// where indexes are in bytes.
type ScanAcc = (TokenKind * int * int) list

let charNull: char = char 0

let charIsSpace (c: char): bool =
  c = ' ' || c = '\t' || c = '\r' || c = '\n'

let charIsDigit (c: char): bool =
  '0' <= c && c <= '9'

let charIsAlpha (c: char): bool =
  ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')

let charIsIdent (c: char): bool =
  c = '_' || charIsDigit c || charIsAlpha c

let charIsOp (c: char): bool =
  "+-*/%=<>^&|:@;.," |> strContainsChar c

let charIsPun (c: char): bool =
  "()[]" |> strContainsChar c

/// `s.[i..].StartsWith(prefix)`
let strNthStartsWith (i: int) (prefix: string) (s: string): bool =
  /// `s.[si..].StartsWith(prefix.[pi..])`
  let rec go pi si =
    pi = prefix.Length || (
      si < s.Length
      && prefix.[pi] = s.[si]
      && go (pi + 1) (si + 1)
    )
  i + prefix.Length <= s.Length && go 0 i

let scanError (acc: ScanAcc, text: string, i: int) =
  (TokenKind.Error, i, i + 1) :: acc, text, i + 1

let scanSpace (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] |> charIsSpace)
  let rec go i =
    if i < text.Length && text.[i] |> charIsSpace then
      go (i + 1)
    else
      i
  acc, text, go i

let scanLine (acc: ScanAcc, text: string, i: int) =
  let rec go i =
    if i = text.Length then
      i
    else if text.[i] = '\n' then
      i + 1
    else
      go (i + 1)
  acc, text, go i

let scanPun (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] |> charIsPun)
  let endIndex = i + 1
  (TokenKind.Pun, i, endIndex) :: acc, text, endIndex

let scanOp (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] |> charIsOp)
  let rec go i =
    if i < text.Length && text.[i] |> charIsOp then
      go (i + 1)
    else
      i
  let endIndex = go i
  (TokenKind.Op, i, endIndex) :: acc, text, endIndex

let scanIdent (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] |> charIsIdent && text.[i] |> charIsDigit |> not)
  let rec go i =
    if i < text.Length && text.[i] |> charIsIdent then
      go (i + 1)
    else
      i
  let endIndex = go i
  (TokenKind.Ident, i, endIndex) :: acc, text, endIndex

let scanIntLit (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] |> charIsDigit)
  let rec go i =
    if i < text.Length && text.[i] |> charIsDigit then
      go (i + 1)
    else
      i
  let endIndex = go i
  (TokenKind.IntLit, i, endIndex) :: acc, text, endIndex

let scanCharLit (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] = '\'')
  let rec go i =
    if i + 1 < text.Length && text.[i] = '\\' then
      // Skip escape sequence.
      go (i + 2)
    else if i < text.Length && text.[i] = '\'' then
      // Complete.
      TokenKind.CharLit, i + 1
    else if i < text.Length && text.[i] <> '\n' then
      // Go ahead.
      go (i + 1)
    else
      // Missed the closing quote.
      assert (i = text.Length || text.[i] = '\n')
      TokenKind.Error, i
  let kind, endIndex = go (i + 1)
  (kind, i, endIndex) :: acc, text, endIndex

let scanStrLit (acc: ScanAcc, text: string, i: int) =
  assert (text.[i] = '"')
  let rec go i =
    if i + 1 < text.Length && text.[i] = '\\' then
      // Escape sequence.
      go (i + 2)
    else if i < text.Length && text.[i] = '"' then
      // Success.
      TokenKind.StrLit, i + 1
    else if i < text.Length && text.[i] <> '\n' then
      // Go ahead.
      go (i + 1)
    else
      // Missed the closing quote.
      assert (i = text.Length || text.[i] = '\n')
      TokenKind.Error, i
  let kind, endIndex = go (i + 1)
  (kind, i, endIndex) :: acc, text, endIndex

let scanRoot (text: string) =
  let rec go (acc, text, i) =
    let t = acc, text, i
    let follow prefix = text |> strNthStartsWith i prefix

    if i >= text.Length then
      text, acc |> listRev
    else if follow "//" || follow "[<" then
      // Skip comments. Attributes are also skipped for now.
      t |> scanLine |> go
    else if text.[i] |> charIsSpace then
      t |> scanSpace |> go
    else if text.[i] |> charIsOp then
      t |> scanOp |> go
    else if text.[i] |> charIsDigit then
      t |> scanIntLit |> go
    else if text.[i] |> charIsIdent then
      t |> scanIdent |> go
    else if text.[i] = '\'' then
      t |> scanCharLit |> go
    else if text.[i] = '"' then
      t |> scanStrLit |> go
    else if text.[i] |> charIsPun then
      t |> scanPun |> go
    else
      t |> scanError |> go
  go ([], text, 0)

// ## Recognize
//
// Parse text ranges as tokens.
// Calculate line numbers and column numbers for token ranges.

/// Assume that the l-th byte is at the y-th line and x-th column.
/// Calculate line/column numbers for the r-th byte
/// by counting number of line breaks in the range.
let advanceTextPos (y, x) (text: string) (l: int) (r: int) =
  let rec go y x i =
    if i = r then
      y, x
    else if text.[i] = '\n' then
      go (y + 1) 0 (i + 1)
    else
      go y (x + 1) (i + 1)
  go y x l

let tokenFromIdent (text: string) l r: Token =
  match text |> strSlice l r with
  | "true" ->
    Token.Bool true
  | "false" ->
    Token.Bool false
  | "do" ->
    Token.Do
  | "let" ->
    Token.Let
  | "if" ->
    Token.If
  | "then" ->
    Token.Then
  | "else" ->
    Token.Else
  | "match" ->
    Token.Match
  | "with" ->
    Token.With
  | "as" ->
    Token.As
  | "when" ->
    Token.When
  | "rec" ->
    Token.Rec
  | "private" ->
    Token.Private
  | "internal" ->
    Token.Internal
  | "public" ->
    Token.Public
  | "module" ->
    Token.Module
  | "namespace" ->
    Token.Namespace
  | "open" ->
    Token.Open
  | "type" ->
    Token.Type
  | "of" ->
    Token.Of
  | "fun" ->
    Token.Fun
  | "in" ->
    Token.In
  | s ->
    Token.Ident s

let tokenFromOp (text: string) l r: Token =
  match text |> strSlice l r with
  | ":" ->
    Token.Colon
  | "." ->
    Token.Dot
  | "|" ->
    Token.Pipe
  | "->" ->
    Token.Arrow
  | s ->
    Token.Punct s

let tokenFromPun (text: string) (l: int) r =
  assert (r - l = 1)
  match text.[l] with
  | '(' ->
    Token.ParenL
  | ')' ->
    Token.ParenR
  | '[' ->
    Token.BracketL
  | ']' ->
    Token.BracketR
  | _ ->
    failwith "NEVER! charIsPun is broken"

let tokenFromIntLit (text: string) l r: Token =
  let value = text |> strSlice l r |> int
  Token.Int value

let tokenFromCharLit (text: string) l r: Token =
  assert (l + 2 <= r && text.[l] = '\'' && text.[r - 1] = '\'')

  // FIXME: redundant characters are just ignored.
  let i = l + 1
  let value =
    match text.[i] with
    | '\\' ->
      match text.[i + 1] with
      | 'u' ->
        charNull
      | 't' ->
        '\t'
      | 'r' ->
        '\r'
      | 'n' ->
        '\n'
      | c ->
        c
    | c ->
      c

  Token.Char value

let tokenFromStrLit (text: string) l r: Token =
  assert (l + 2 <= r && text.[l] = '"' && text.[r - 1] = '"')

  // Process a string as alternation of unescaped parts and escape sequences.
  // E.g. "hello\nworld" -> "hello" + "\n" + "world"
  let rec go acc i =
    // Take an unescaped part.
    let rec next i =
      if i = r - 1 || text.[i] = '\\' then
        i
      else
        next (i + 1)
    let endIndex = next i
    let acc = (text |> strSlice i endIndex) :: acc
    let i = endIndex

    // Take an escape sequence or halt.
    if i = r - 1 then
      acc |> listRev |> strConcat
    else
      assert (text.[i] = '\\')
      match text.[i + 1] with
      | 'u' ->
        go ("\u0000" :: acc) (i + 6)
      | 't' ->
        go ("\t" :: acc) (i + 2)
      | 'r' ->
        go ("\r" :: acc) (i + 2)
      | 'n' ->
        go ("\n" :: acc) (i + 2)
      | _ ->
        go ((text |> strSlice (i + 1) (i + 2)) :: acc) (i + 2)
  let value = go [] (l + 1)

  Token.Str value

let recognizeToken kind (text: string) l r =
  match kind with
  | TokenKind.Error ->
    failwith "Invalid char"

  | TokenKind.Op ->
    tokenFromOp text l r

  | TokenKind.Pun ->
    tokenFromPun text l r

  | TokenKind.IntLit ->
    tokenFromIntLit text l r

  | TokenKind.CharLit ->
    tokenFromCharLit text l r

  | TokenKind.StrLit ->
    tokenFromStrLit text l r

  | TokenKind.Ident ->
    tokenFromIdent text l r

let recognizeTokens (text, tokens) =
  /// Assume the previous token ends with last-th byte at (line, column) = (y, x) position.
  let rec go acc y x last tokens =
    match tokens with
    | [] ->
      acc |> listRev
    | (kind, l, r) :: tokens ->
      // Locate l-th byte.
      let y, x = advanceTextPos (y, x) text last l

      // Recognize the token.
      let token = recognizeToken kind text l r
      let acc = (token, (y, x)) :: acc

      // Locate r-th byte.
      let y, x = advanceTextPos (y, x) text l r
      go acc y x r tokens
  go [] 0 0 0 tokens

let tokenize (text: string): (Token * Loc) list =
  text |> scanRoot |> recognizeTokens
