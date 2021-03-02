/// # SyntaxTokenize
///
/// Performs tokenization, i.e. splits a source code to a list of tokens.
///
/// ## Motivation
///
/// This stage makes the parser simpler.
///
/// - The parser needs to know token position (row/column indexes)
///   for the indent-sensitive syntax. This stage takes over the task.
/// - The parser needs to look easily.
///   Plain string is much difficult to look ahead due to spaces and comments.
///   List of tokens is better structure for that.
///
/// ## Examples
///
/// ```fsharp
/// let main _ =
///   0
/// ```
///
/// This stage should break the the above code down to the following tokens:
///
/// | Y:X   | Token  | Text
/// |------:|:-------|:-----
/// |   0:0 | Let    | let
/// |   0:4 | Ident  | main
/// |   0:9 | Ident  | _
/// |  0:11 | Equal  | =
/// |   1:2 | IntLit | 0
///
/// ## Remarks
///
/// ### Reliability
///
/// This stage should *never fail*. Even if the input is completely broken,
/// tokenization must not cause fatal errors since tokenization is
/// constantly performed by LSP server while the programmer is editing
/// so that it can collect some information (such as list of symbols)
/// from incomplete codes.
///
/// This stage should also be fast as possible for the same reason.
///
/// ### About char
///
/// On .NET, `char` is a UTF-16 code unit, i.e. 2-byte.
/// However, in milone-lang, `char` is a UTF-8 code unit (1-byte).
/// Currently milone-lang keeps non-ASCII chars untouched,
/// so this difference doesn't matter.
///
/// ### Other notes
///
/// Sometimes row number is denoted by `y` and column number by `x`.
module rec MiloneLang.SyntaxTokenize

open MiloneLang.Util
open MiloneLang.Syntax

module C = MiloneStd.StdChar
module S = MiloneStd.StdString

// -----------------------------------------------
// Char
// -----------------------------------------------

let private charIsIdent (c: char): bool = c = '_' || C.isAlphanumeric c

let private charIsTyVar (c: char): bool = c = '_' || C.isAlphabetic c

let private charIsOp (c: char): bool =
  match c with
  | '+'
  | '-'
  | '*'
  | '/'
  | '%'
  | '='
  | '<'
  | '>'
  | '^'
  | '&'
  | '|'
  | ':'
  | '@'
  | ';'
  | '.' -> true

  | _ -> false

// -----------------------------------------------
// String
// -----------------------------------------------

/// Gets i'th byte of string. Returns \x00 if out of range.
let private at (text: string) (i: int) =
  if i < text.Length then
    text.[i]
  else
    '\x00'

/// Followed by `"""`?
let private isFollowedByRawQuotes (i: int) (s: string): bool =
  (i + 3 <= s.Length)
  && (match s.[i], s.[i + 1], s.[i + 2] with
      | '"', '"', '"' -> true
      | _ -> false)

/// Followed by \`\`?
let private isFollowedByBackticks (i: int) (s: string): bool =
  (i + 2 <= s.Length)
  && (match s.[i], s.[i + 1] with
      | '`', '`' -> true
      | _ -> false)

// -----------------------------------------------
// Pos
// -----------------------------------------------

/// Modifies the position that points to `text.[l]`
/// to one that points to `text.[r]`.
let private posShift (text: string) (l: int) (r: int) (pos: Pos) =
  assert (0 <= l && l <= r && r <= text.Length)

  let y, x = pos

  let rec go y x i =
    if i = r then
      y, x
    else if text.[i] = '\n' then
      go (y + 1) 0 (i + 1)
    else
      go y (x + 1) (i + 1)

  go y x l

// -----------------------------------------------
// Scan functions
// -----------------------------------------------

// Scan function skips some characters in a token
// and returns the end index.

let private scanBad (text: string) (i: int) =
  let stillBad c =
    match c with
    | ' '
    | '\r'
    | '\n'
    | '('
    | ')'
    | ',' -> false

    | _ -> true

  let rec go i =
    if i < text.Length && stillBad text.[i] then
      go (i + 1)
    else
      i

  go i

let private scanBlank (text: string) (i: int) =
  let rec go i =
    if i + 1 < text.Length then
      match text.[i], text.[i + 1] with
      | ' ', ' ' -> go (i + 2)

      | ' ', _
      | '\t', _ -> go (i + 1)

      | _ -> i
    else if i < text.Length && text.[i] |> C.isSpace then
      i + 1
    else
      i

  go i

let private scanNewlines (text: string) (i: int) =
  let rec go i =
    if i < text.Length then
      match text.[i] with
      | '\r'
      | '\n' -> go (i + 1)

      | _ -> i
    else
      i

  go i

/// Skips current line.
let private scanLine (text: string) (i: int) =
  let rec go i =
    if i < text.Length && text.[i] <> '\n' then
      go (i + 1)
    else
      i

  go i

// Since F# supports custom operators, any combination of operator characters
// can be single token.
let private scanOp (text: string) (i: int) =
  let rec go i =
    if i < text.Length && text.[i] |> charIsOp then
      go (i + 1)
    else
      i

  go i

let private scanIdent (text: string) (i: int) =
  let rec go i =
    if i < text.Length && text.[i] |> charIsIdent then
      go (i + 1)
    else
      i

  go i

let private scanRawIdent (text: string) (i: int) =
  let rec go i =
    if text |> isFollowedByBackticks i then
      true, i
    else if i >= text.Length then
      false, i
    else
      go (i + 1)

  if text |> isFollowedByBackticks i then
    let ok, m = go (i + 1)
    if ok then Some m else None
  else
    None

let private scanNumberLit (text: string) (i: int) =
  let rec scanDigits (i: int) =
    if at text i |> C.isDigit then
      scanDigits (i + 1)
    else
      i

  let scanFraction i =
    // Check if point is following but not a range operator.
    if at text i = '.' && at text (i + 1) <> '.' then
      true, scanDigits (i + 1)
    else
      false, i

  let scanExponential i =
    match at text i with
    | 'e'
    | 'E'
    | 'p'
    | 'P' ->
        match at text (i + 1) with
        | '+'
        | '-' -> true, scanDigits (i + 2)

        | _ -> true, scanDigits (i + 1)
    | _ -> false, i

  let i = scanDigits i
  let hasFraction, i = scanFraction i
  let hasExponential, i = scanExponential i

  // Suffix.
  let r = scanIdent text i

  let isFloat = hasFraction || hasExponential
  isFloat, i, r

let private scanCharLit (text: string) (i: int) =
  let at (i: int) =
    if i < text.Length then
      text.[i]
    else
      '\x00'

  let rec go i =
    match at i with
    | '\'' -> i + 1

    | '\x00'
    | '\r'
    | '\n' -> i

    | '\\' ->
        if at (i + 1) <> '\x00' then
          go (i + 2)
        else
          i + 1

    | _ -> go (i + 1)

  assert (i >= 1 && at (i - 1) = '\'')
  go i

let private scanStrLit (text: string) (i: int) =
  let at (i: int) =
    if i < text.Length then
      text.[i]
    else
      '\x00'

  let rec go i =
    match at i with
    | '"' -> i + 1

    | '\x00'
    | '\r'
    | '\n' -> i

    | '\\' ->
        if at (i + 1) <> '\x00' then
          go (i + 2)
        else
          i + 1

    | _ -> go (i + 1)

  assert (i >= 1 && text.[i - 1] = '"')
  go i

let private scanStrLitRaw (text: string) (i: int) =
  let rec go i =
    if i + 3 <= text.Length then
      if text |> isFollowedByRawQuotes i then
        i + 3
      else
        go (i + 1)
    else
      text.Length

  assert (i >= 3 && isFollowedByRawQuotes (i - 3) text)
  go i

// -----------------------------------------------
// Evaluation
// -----------------------------------------------

let private tokenOfOp (text: string) l r: Token =
  let s = text |> S.slice l r

  let error () = ErrorToken UndefinedOpTokenError

  let expect expected token =
    if s = expected then token else error ()

  match s.[0] with
  | '&' ->
      match s with
      | "&" -> AmpToken
      | "&&" -> AmpAmpToken
      | "&&&" -> AmpAmpAmpToken
      | _ -> error ()

  | '-' ->
      match s with
      | "->" -> ArrowToken
      | "-" -> MinusToken
      | _ -> error ()

  | ':' ->
      match s with
      | ":" -> ColonToken
      | "::" -> ColonColonToken
      | _ -> error ()

  | '.' ->
      match s with
      | "." -> DotToken
      | ".." -> DotDotToken
      | _ -> error ()

  | '<' ->
      match s with
      | "<" -> LeftAngleToken
      | "<=" -> LeftEqualToken
      | "<>" -> LeftRightToken
      | "<<" -> LeftLeftToken
      | "<<<" -> LeftLeftLeftToken
      | _ -> error ()

  | '>' ->
      match s with
      | ">" -> RightAngleToken
      | ">=" -> RightEqualToken
      | _ -> error ()

  | '|' ->
      match s with
      | "|" -> PipeToken
      | "|>" -> PipeRightToken
      | "||" -> PipePipeToken
      | "|||" -> PipePipePipeToken
      | _ -> error ()

  | '^' ->
      match s with
      | "^" -> HatToken
      | "^^^" -> HatHatHatToken
      | _ -> error ()

  | '=' -> expect "=" EqualToken
  | '%' -> expect "%" PercentToken
  | '+' -> expect "+" PlusToken
  | ';' -> expect ";" SemiToken
  | '*' -> expect "*" StarToken
  | '/' -> expect "/" SlashToken

  | _ -> error ()

let private evalCharLit (text: string) (l: int) (r: int): Token =
  match r - l with
  // '?'
  | 3 when text.[l] = '\'' && text.[l + 2] = '\'' -> CharToken(text.[l + 1])

  // '\?'
  | 4 when
    text.[l] = '\''
    && text.[l + 1] = '\\'
    && text.[l + 3] = '\'' ->
      let c = text.[l + 2]

      match c with
      | 't' -> CharToken '\t'
      | 'r' -> CharToken '\r'
      | 'n' -> CharToken '\n'

      | '\\'
      | '\''
      | '"' -> CharToken c

      | _ -> ErrorToken UnknownEscapeSequenceError

  // '\xHH'
  | 6 when
    text.[l] = '\''
    && text.[l + 1] = '\\'
    && text.[l + 2] = 'x'
    && text.[l + 5] = '\'' ->
      if text.[l + 3] = '0' && text.[l + 4] = '0' then
        CharToken '\x00'
      else
        ErrorToken UnimplHexEscapeError

  | _ -> ErrorToken InvalidCharLitError

let private evalStrLit (text: string) (l: int) (r: int): Token =
  let rec skipVerbatim i =
    if i + 1 < r && text.[i] <> '\\' then
      skipVerbatim (i + 1)
    else
      i

  /// Splits a string to alternating list of unescaped "verbatim" parts
  /// and escape sequences. E.g. "hello\nworld" -> "hello", "\n", "world".
  let rec go acc i =
    assert (i < r)

    // Take verbatim part.
    let endIndex = skipVerbatim i

    let acc =
      if i < endIndex then
        (text |> S.slice i endIndex) :: acc
      else
        acc

    let i = endIndex

    // Take an escape sequence or halt.
    if i = r - 1 then
      StrToken(acc |> List.rev |> strConcat)
    else
      assert (i < r - 1 && text.[i] = '\\')

      match text.[i + 1] with
      | 'x' when
        i + 4 < r
        && text.[i + 2] = '0'
        && text.[i + 3] = '0' -> go ("\x00" :: acc) (i + 4)
      | 't' when i + 2 < r -> go ("	" :: acc) (i + 2)
      | 'r' when i + 2 < r -> go ("\r" :: acc) (i + 2)
      | 'n' when i + 2 < r -> go ("\n" :: acc) (i + 2)

      | '\\'
      | '\''
      | '"' when i + 2 < r -> go ((text |> S.slice (i + 1) (i + 2)) :: acc) (i + 2)

      | _ -> ErrorToken UnknownEscapeSequenceError

  if l + 2 <= r && text.[l] = '"' && text.[r - 1] = '"' then
    go [] (l + 1)
  else
    ErrorToken InvalidStrLitError

let private evalStrLitRaw (text: string) l r =
  if (l + 6 <= r)
     && text |> isFollowedByRawQuotes l
     && text |> isFollowedByRawQuotes (r - 3) then
    StrToken(text |> S.slice (l + 3) (r - 3))
  else
    ErrorToken InvalidStrLitError

// -----------------------------------------------
// Tokenize routines
// -----------------------------------------------

[<Struct>]
[<NoEquality; NoComparison>]
type private Lookahead =
  | LEof
  | LBlank
  | LNewline
  | LComment
  | LNumber
  | LNonKeywordIdent
  | LIdent
  | LRawIdent
  | LTyVar
  | LChar
  | LStr
  | LRawStr
  | LOp
  | LBad
  | LToken of Token

let private lookahead (text: string) (i: int) =
  let at (i: int) =
    if i < text.Length then
      text.[i]
    else
      '\x00'

  assert (i < text.Length)
  let c = text.[i]

  match c with
  | '\x00' -> LEof, 0

  | ' '
  | '\t' -> LBlank, 1

  | '\r'
  | '\n' -> LNewline, 1

  | '0'
  | '1'
  | '2'
  | '3'
  | '4'
  | '5'
  | '6'
  | '7'
  | '8'
  | '9' -> LNumber, 1

  | '_'
  | 'A'
  | 'B'
  | 'C'
  | 'D'
  | 'E'
  | 'F'
  | 'G'
  | 'H'
  | 'I'
  | 'J'
  | 'K'
  | 'L'
  | 'M'
  | 'N'
  | 'O'
  | 'P'
  | 'Q'
  | 'R'
  | 'S'
  | 'T'
  | 'U'
  | 'V'
  | 'W'
  | 'X'
  | 'Y'
  | 'Z' -> LNonKeywordIdent, 1

  | 'a'
  | 'b'
  | 'c'
  | 'd'
  | 'e'
  | 'f'
  | 'g'
  | 'h'
  | 'i'
  | 'j'
  | 'k'
  | 'l'
  | 'm'
  | 'n'
  | 'o'
  | 'p'
  | 'q'
  | 'r'
  | 's'
  | 't'
  | 'u'
  | 'v'
  | 'w'
  | 'x'
  | 'y'
  | 'z' -> LIdent, 1

  | '\'' ->
      if charIsTyVar (at (i + 1)) && at (i + 2) <> '\'' then
        LTyVar, 2
      else
        LChar, 1

  | '"' ->
      if isFollowedByRawQuotes i text then
        LRawStr, 3
      else
        LStr, 1

  | '`' -> LRawIdent, 1

  | ',' -> LToken CommaToken, 1
  | '(' -> LToken LeftParenToken, 1
  | ')' -> LToken RightParenToken, 1

  | '[' ->
      match at (i + 1) with
      | '<' -> LToken LeftAttrToken, 2
      | _ -> LToken LeftBracketToken, 1

  | ']' -> LToken RightBracketToken, 1
  | '{' -> LToken LeftBraceToken, 1
  | '}' -> LToken RightBraceToken, 1

  | '/' ->
      match at (i + 1) with
      | '/' -> LComment, 2
      | _ -> LOp, 1

  | '>' ->
      match at (i + 1) with
      | ']' -> LToken RightAttrToken, 2

      | c when c <> '>' && charIsOp c -> LOp, 2

      | _ ->
          // Consecutive right angles (such as `>>>`) are merged while parsing.
          LToken RightAngleToken, 1

  | '-'
  | ';'
  | ':'
  | '.'
  | '@'
  | '*'
  | '&'
  | '%'
  | '^'
  | '+'
  | '<'
  | '='
  | '|' -> LOp, 1

  | _ -> LBad, 1

let private doNext (host: TokenizeHost) (text: string) (index: int): Token * int =
  let look, len = lookahead text index

  match look with
  | LEof -> BlankToken, text.Length - index

  | LBlank ->
      let r = scanBlank text (index + len)
      BlankToken, r

  | LNewline ->
      let r = scanNewlines text (index + len)
      NewlinesToken, r

  | LComment ->
      let r = scanLine text (index + len)
      CommentToken, r

  | LNumber ->
      let isFloat, m, r = scanNumberLit text (index + len)

      // Value can be too large or too small; range should be checked in Typing.
      // m: before suffix
      if m < r then
        ErrorToken UnimplNumberSuffixError, r
      else if isFloat then
        FloatToken text.[index..r - 1], r
      else
        IntToken(S.slice index r text), r

  | LNonKeywordIdent ->
      let r = scanIdent text (index + len)
      IdentToken text.[index..r - 1], r

  | LIdent ->
      let r = scanIdent text (index + len)
      let ident = text |> S.slice index r

      let token =
        match host.FindKeyword ident with
        | Some it -> it
        | None -> IdentToken ident

      token, r

  | LRawIdent ->
      match scanRawIdent text index with
      | Some m ->
          assert (text |> isFollowedByBackticks m)
          let ident = text.[index + 2..m - 1]
          IdentToken ident, m + 2

      | None -> ErrorToken InvalidRawIdentError, index + len

  | LTyVar ->
      let r = index + len
      TyVarToken text.[index + 1..r - 1], r

  | LChar ->
      let r = scanCharLit text (index + len)
      evalCharLit text index r, r

  | LStr ->
      let r = scanStrLit text (index + len)
      evalStrLit text index r, r

  | LRawStr ->
      let r = scanStrLitRaw text (index + len)
      evalStrLitRaw text index r, r

  | LOp ->
      let r = scanOp text (index + len)
      tokenOfOp text index r, r

  | LToken _ ->
      match look with
      | LToken token -> token, index + len
      | _ -> unreachable ()

  | LBad ->
      let r = scanBad text (index + len)
      ErrorToken BadTokenError, r

/// Tokenizes a string. Trivias are removed.
let tokenize (host: TokenizeHost) (text: string): (Token * Pos) list =
  let rec go acc (i: int) (pos: Pos) =
    if i < text.Length then
      let token, r = doNext host text i

      assert (i < r)

      let acc =
        match token with
        | BlankToken
        | NewlinesToken
        | CommentToken -> acc

        | _ -> (token, pos) :: acc

      let pos = posShift text i r pos
      go acc r pos
    else
      acc

  go [] 0 (0, 0) |> List.rev

/// Tokenizes a string. Trivias are preserved.
let tokenizeAll (host: TokenizeHost) (text: string): (Token * Pos) list =
  let rec go acc (i: int) (pos: Pos) =
    if i < text.Length then
      let token, r = doNext host text i
      assert (i < r)

      let acc = (token, pos) :: acc

      let pos = posShift text i r pos
      go acc r pos
    else
      acc

  go [] 0 (0, 0) |> List.rev
