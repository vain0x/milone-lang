/// Splits a source file into a list of tokens.
///
/// ## Motivation
///
/// This stage is to make the parser simpler.
///
/// - The parser wants to know row/column indexes of tokens
///   because of the indentation-sensitive syntax.
/// - List of tokens is easier for the parser to look ahead
///   than that of characters.
/// - Spaces and comments unnecessary for the parser
///   (except for the row/column index of tokens).
///
/// ### Example
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
/// |  0:11 | Binary | =
/// |   1:2 | IntLit | 0
module rec MiloneLang.Lexing

open MiloneLang.Types
open MiloneLang.Helpers

/// (text, index, pos, tokenAcc)
type TokenizeCtx = string * int * Pos * (Token * Pos) list

/// Modifies the position that points to `text.[l]`
/// to one that points to `text.[r]`.
let posShift (text: string) (l: int) (r: int) ((y, x): Pos) =
  assert (0 <= l && l <= r && r <= text.Length)

  let rec go y x i =
    if i = r then y, x
    else if text.[i] = '\n' then go (y + 1) 0 (i + 1)
    else go y (x + 1) (i + 1)

  go y x l

// -----------------------------------------------
// Character helpers
// -----------------------------------------------

let charNull: char = char 0

let charIsIdent (c: char): bool =
  c = '_' || charIsDigit c || charIsAlpha c

let charIsOp (c: char): bool =
  c = '+'
  || c = '-'
  || c = '*'
  || c = '/'
  || c = '%'
  || c = '='
  || c = '<'
  || c = '>'
  || c = '^'
  || c = '&'
  || c = '|'
  || c = ':'
  || c = '@'
  || c = ';'
  || c = '.'

let charIsPun (c: char): bool =
  c = ','
  || c = '('
  || c = ')'
  || c = '['
  || c = ']'
  || c = '{'
  || c = '}'

// -----------------------------------------------
// String helpers
// -----------------------------------------------

/// `s.[i..].StartsWith(prefix)`
let strIsFollowedBy (i: int) (prefix: string) (s: string): bool =
  /// `s.[si..].StartsWith(prefix.[pi..])`
  let rec go pi si =
    pi = prefix.Length
    || (si < s.Length
        && prefix.[pi] = s.[si]
        && go (pi + 1) (si + 1))

  i + prefix.Length <= s.Length && go 0 i

/// Followed by `"""`?
let strIsFollowedByRawQuotes (i: int) (s: string): bool = strIsFollowedBy i "\"\"\"" s

// -----------------------------------------------
// Scan functions
// -----------------------------------------------

let scanError (_: string) (i: int) =
  // FIXME: Skip unrecognizable characters.
  i + 1

let lookEof (text: string) (i: int) = i >= text.Length

/// Gets if the text is followed by 1+ spaces at the position.
let lookSpace (text: string) (i: int) = text.[i] |> charIsSpace

/// Finds the end index of the following spaces.
let scanSpace (text: string) (i: int) =
  assert (lookSpace text i)

  let rec go i =
    if i < text.Length && text.[i] |> charIsSpace
    then go (i + 1)
    else i

  go i

let lookComment (text: string) (i: int) =
  // NOTE: Attributes are also skipped for now.
  text
  |> strIsFollowedBy i "//"
  || text |> strIsFollowedBy i "[<"

let scanLine (text: string) (i: int) =
  assert (lookComment text i)

  let rec go i =
    if i = text.Length then i
    else if text.[i] = '\n' then i + 1
    else go (i + 1)

  go i

let lookPun (text: string) (i: int) = text.[i] |> charIsPun

let scanPun (text: string) (i: int) =
  assert (lookPun text i)
  i + 1

let lookOp (text: string) (i: int) = text.[i] |> charIsOp

let scanOp (text: string) (i: int) =
  assert (lookOp text i)

  let rec go i =
    if i < text.Length && text.[i] |> charIsOp then go (i + 1) else i

  go i

let lookIdent (text: string) (i: int) =
  text.[i]
  |> charIsIdent
  && text.[i] |> charIsDigit |> not

let scanIdent (text: string) (i: int) =
  assert (lookIdent text i)

  let rec go i =
    if i < text.Length && text.[i] |> charIsIdent
    then go (i + 1)
    else i

  go i

let lookIntLit (text: string) (i: int) = text.[i] |> charIsDigit

let scanIntLit (text: string) (i: int) =
  assert (lookIntLit text i)

  let rec go i =
    if i < text.Length && text.[i] |> charIsDigit
    then go (i + 1)
    else i

  go i

let lookCharLit (text: string) (i: int) = text.[i] = '\''

let scanCharLit (text: string) (i: int) =
  assert (lookCharLit text i)

  let rec go i =
    if i + 1 < text.Length && text.[i] = '\\' then
      // Skip escape sequence.
      go (i + 2)
    else if i < text.Length && text.[i] = '\'' then
      // Complete.
      true, i + 1
    else if i < text.Length && text.[i] <> '\n' then
      // Go ahead.
      go (i + 1)
    else
      // Missed the closing quote.
      assert (i = text.Length || text.[i] = '\n')
      false, i

  go (i + 1)

let lookStrLit (text: string) (i: int) = text.[i] = '"'

let scanStrLit (text: string) (i: int) =
  assert (lookStrLit text i)

  let rec go i =
    if i + 1 < text.Length && text.[i] = '\\' then
      // Escape sequence.
      go (i + 2)
    else if i < text.Length && text.[i] = '"' then
      // Success.
      true, i + 1
    else if i < text.Length && text.[i] <> '\n' then
      // Go ahead.
      go (i + 1)
    else
      // Missed the closing quote.
      assert (i = text.Length || text.[i] = '\n')
      false, i

  go (i + 1)

let lookStrLitRaw (text: string) (i: int) = text |> strIsFollowedByRawQuotes i

let scanStrLitRaw (text: string) (i: int) =
  assert (lookStrLitRaw text i)

  let rec go i =
    if text |> strIsFollowedByRawQuotes i then
      true, i + 3
    else if i + 1 < text.Length then
      go (i + 1)
    else
      assert (i = text.Length)
      false, i

  go (i + 3)

// -----------------------------------------------
// Token helpers
// -----------------------------------------------

let tokenFromIdent (text: string) l r: Token =
  match text |> strSlice l r with
  | "true" -> TrueToken
  | "false" -> FalseToken
  | "do" -> DoToken
  | "let" -> LetToken
  | "if" -> IfToken
  | "then" -> ThenToken
  | "else" -> ElseToken
  | "match" -> MatchToken
  | "with" -> WithToken
  | "as" -> AsToken
  | "when" -> WhenToken
  | "rec" -> RecToken
  | "private" -> PrivateToken
  | "internal" -> InternalToken
  | "public" -> PublicToken
  | "module" -> ModuleToken
  | "namespace" -> NamespaceToken
  | "open" -> OpenToken
  | "type" -> TypeToken
  | "of" -> OfToken
  | "fun" -> FunToken
  | "in" -> InToken
  | s -> IdentToken s

let tokenFromOp (text: string) l r: Token =
  match text |> strSlice l r with
  | "&" -> AmpToken
  | "&&" -> AmpAmpToken
  | "->" -> ArrowToken
  | ":" -> ColonToken
  | "::" -> ColonColonToken
  | "." -> DotToken
  | ".." -> DotDotToken
  | "=" -> EqToken
  | ">" -> RightAngleToken
  | ">=" -> RightEqToken
  | "<" -> LeftAngleToken
  | "<=" -> LeftEqToken
  | "<>" -> LeftRightToken
  | "-" -> MinusToken
  | "%" -> PercentToken
  | "|" -> PipeToken
  | "|>" -> PipeRightToken
  | "||" -> PipePipeToken
  | "+" -> PlusToken
  | ";" -> SemiToken
  | "*" -> StarToken
  | "/" -> SlashToken
  | _ -> ErrorToken

let tokenFromPun (text: string) (l: int) r =
  assert (r - l = 1)
  match text.[l] with
  | ',' -> CommaToken
  | '(' -> LeftParenToken
  | ')' -> RightParenToken
  | '[' -> LeftBracketToken
  | ']' -> RightBracketToken
  | '{' -> LeftBraceToken
  | '}' -> RightBraceToken
  | _ -> failwith "NEVER! charIsPun is broken"

let tokenFromIntLit (text: string) l r: Token =
  let value = text |> strSlice l r |> int
  IntToken value

let tokenFromCharLit (text: string) l r: Token =
  assert (l
          + 2
          <= r
          && text.[l] = '\''
          && text.[r - 1] = '\'')

  // FIXME: redundant characters are just ignored.
  let i = l + 1

  let value =
    match text.[i] with
    | '\\' ->
        match text.[i + 1] with
        | 'x' -> charNull
        | 't' -> '\t'
        | 'r' -> '\r'
        | 'n' -> '\n'
        | c -> c
    | c -> c

  CharToken value

let tokenFromStrLit (text: string) l r: Token =
  assert (l + 2 <= r && text.[l] = '"' && text.[r - 1] = '"')

  // Process a string as alternation of unescaped parts and escape sequences.
  // E.g. "hello\nworld" -> "hello" + "\n" + "world"
  let rec go acc i =
    // Take an unescaped part.
    let rec next i =
      if i = r - 1 || text.[i] = '\\' then i else next (i + 1)

    let endIndex = next i
    let acc = (text |> strSlice i endIndex) :: acc
    let i = endIndex

    // Take an escape sequence or halt.
    if i = r - 1 then
      acc |> List.rev |> strConcat
    else
      assert (text.[i] = '\\')
      match text.[i + 1] with
      | 'x' -> go ("\x00" :: acc) (i + 4)
      | 't' -> go ("\t" :: acc) (i + 2)
      | 'r' -> go ("\r" :: acc) (i + 2)
      | 'n' -> go ("\n" :: acc) (i + 2)
      | _ -> go ((text |> strSlice (i + 1) (i + 2)) :: acc) (i + 2)

  let value = go [] (l + 1)

  StrToken value

let tokenFromStrLitRaw (text: string) l r =
  assert (l
          + 6
          <= r
          && text |> strIsFollowedByRawQuotes l
          && text |> strIsFollowedByRawQuotes (r - 3))
  StrToken(text |> strSlice (l + 3) (r - 3))

// -----------------------------------------------
// Tokenize functions
// -----------------------------------------------

let tokCtxToTextIndex ((text, i, _, _): TokenizeCtx) = text, i

/// Moves the cursor to the end index (`r`)
/// without emitting a token.
let tokCtxSkip r ((text, i, pos, acc): TokenizeCtx): TokenizeCtx =
  assert (0 <= i && i <= r && r <= text.Length)
  let newPos = pos |> posShift text i r
  text, r, newPos, acc

/// Moves the cursor to the next index (`r`)
/// and emits a token that spans over the moved range.
let tokCtxPush kind r ((text, i, pos, acc): TokenizeCtx): TokenizeCtx =
  assert (0 <= i && i <= r && r <= text.Length)
  let newAcc = (kind, pos) :: acc
  let newPos = pos |> posShift text i r
  text, r, newPos, newAcc

let tokEof ((text, i, _, acc): TokenizeCtx) =
  assert (lookEof text i)
  acc |> List.rev

let tokError t =
  let text, i = t |> tokCtxToTextIndex
  let r = scanError text i
  t |> tokCtxSkip r

let tokComment (t: TokenizeCtx) =
  let text, i = t |> tokCtxToTextIndex
  let r = scanLine text i
  t |> tokCtxSkip r

let tokSpace (t: TokenizeCtx) =
  let text, i = t |> tokCtxToTextIndex
  let r = scanSpace text i
  t |> tokCtxSkip r

let tokPun t =
  let text, i = t |> tokCtxToTextIndex
  let r = scanPun text i
  let token = tokenFromPun text i r
  t |> tokCtxPush token r

let tokOp t =
  let text, i = t |> tokCtxToTextIndex
  let r = scanOp text i
  let token = tokenFromOp text i r
  t |> tokCtxPush token r

let tokIdent t =
  let text, i = t |> tokCtxToTextIndex
  let r = scanIdent text i
  let token = tokenFromIdent text i r
  t |> tokCtxPush token r

let tokIntLit t =
  let text, i = t |> tokCtxToTextIndex
  let r = scanIntLit text i
  let token = tokenFromIntLit text i r
  t |> tokCtxPush token r

let tokCharLit t =
  let text, i = t |> tokCtxToTextIndex
  let ok, r = scanCharLit text i

  let token =
    if ok then tokenFromCharLit text i r else ErrorToken

  t |> tokCtxPush token r

let tokStrLit t =
  let text, i = t |> tokCtxToTextIndex
  let ok, r = scanStrLit text i

  let token =
    if ok then tokenFromStrLit text i r else ErrorToken

  t |> tokCtxPush token r

let tokStrLitRaw t =
  let text, i = t |> tokCtxToTextIndex
  let ok, r = scanStrLitRaw text i

  let token =
    if ok then tokenFromStrLitRaw text i r else ErrorToken

  t |> tokCtxPush token r

let tokenize (text: string): (Token * Pos) list =
  let rec go t =
    let text, i = t |> tokCtxToTextIndex

    if lookEof text i then
      t |> tokEof

    else

    if lookComment text i then
      t |> tokComment |> go
    else

    if lookSpace text i then
      t |> tokSpace |> go
    else

    if lookOp text i then
      t |> tokOp |> go
    else

    if lookIntLit text i then
      t |> tokIntLit |> go
    else

    if lookIdent text i then
      t |> tokIdent |> go
    else

    if lookCharLit text i then
      t |> tokCharLit |> go
    else

    if lookStrLitRaw text i then
      t |> tokStrLitRaw |> go
    else

    if lookStrLit text i then
      t |> tokStrLit |> go
    else if lookPun text i then
      t |> tokPun |> go

    else
      t |> tokError |> go

  go (text, 0, (0, 0), [])
