module rec MiloneLang.Lexing

open MiloneLang

type Acc = (Token * Loc) list

type RowIndex = int
type ColumnIndex = int
type Read = Acc * RowIndex * ColumnIndex * int

let private lexError message (source: string, i) =
  let near = source.Substring(i, min (source.Length - i) 6)
  failwithf "Lex error '%s' near %s" message near

let private isDigit c =
  '0' <= c && c <= '9'

let private isAlpha c =
  ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')

let private isIdentChar c =
  c = '_' || isDigit c || isAlpha c

let private isOpChar (c: char) =
  "+-*/%=<>^&|:@;.,".Contains(c)

/// Finds the first position that doesn't satisfy the specified predicate starting from `i`.
let private takeWhile pred (source: string, i) =
  let rec go r =
    if r < source.Length && pred source.[r] then
      go (r + 1)
    else
      r
  go i

let private readSpace (source: string) (acc, y, x, i): Read =
  assert (source.[i] = ' ')
  let r = takeWhile ((=) ' ') (source, i + 1)
  acc, y, x + r - i, r

let private readEol (source: string) (acc, y, _x, i): Read =
  assert (source.[i] = '\r' || source.[i] = '\n')
  let r =
    if i + 1 < source.Length && source.StartsWith("\r\n")
    then i + 2
    else i + 1
  acc, y + 1, 0, r

let private readLineComment (source: string) (acc, y, x, i): Read =
  // assert (source.[i] = '/' && source.[i + 1] = '/')
  let rec go r =
    if r < source.Length && source.[r] <> '\r' && source.[r] <> '\n' then
      go (r + 1)
    else
      r
  let r = go (i + 2)
  // No need to read EOL here.
  acc, y, x + r - i, r

let private readOp (source: string) (acc, y, x, i): Read =
  assert (isOpChar source.[i])
  let r = takeWhile isOpChar (source, i + 1)
  let t = tokenPunct (source.Substring(i, r - i)), (y, x)
  t :: acc, y, x + r - i, r

let private readIdent (source: string) (acc, y, x, i): Read =
  assert (isIdentChar source.[i])
  let r = takeWhile isIdentChar (source, i + 1)
  let t = tokenIdent (source.Substring(i, r - i)), (y, x)
  t :: acc, y, x + r - i, r

let private readInt (source: string) (acc, y, x, i): Read =
  assert (isDigit source.[i])
  let r = takeWhile isDigit (source, i + 1)
  let t = Token.Int (source.Substring(i, r - i) |> int), (y, x)
  t :: acc, y, x + r - i, r

let private readStr (source: string) (acc, y, x, i): Read =
  assert (source.[i] = '"')
  let rec chunk i =
    if i >= source.Length || source.[i] = '"' || source.[i] = '\\'
    then i
    else chunk (i + 1)
  let unescape i =
    match source.[i] with
    | 'r' -> "\r"
    | 'n' -> "\n"
    | 't' -> "\t"
    | '"' -> "\""
    | '\\' -> "\\"
    | 'u' -> failwith "unimpl unicode esc"
    | c -> failwithf "unimpl escape %c" c
  let rec go acc i =
    if i >= source.Length then
      lexError "Expected closing '\"'" (source, i)
    else if source.[i] = '"' then
      acc, i + 1
    else if source.[i] = '\\' then
      go (unescape (i + 1) :: acc) (i + 2)
    else
      let r = chunk i
      go (source.Substring(i, r - i) :: acc) r
  let chunks, r = go [] (i + 1)
  let str = chunks |> List.rev |> String.concat ""
  let t = Token.Str str, (y, x)
  t :: acc, y, x + r - i, r

let private readChar (source: string) (acc, y, x, i): Read =
  assert (source.[i] = '\'')
  let c, len =
    // FIXME: range check
    if source.[i + 1] = '\\' then
      match source.[i + 2] with
      | '\'' -> '\'', 2
      | '\\' -> '\\', 2
      | 't' -> '\t', 2
      | 'r' -> '\r', 2
      | 'n' -> '\n', 2
      | 'u' -> '\u0000', 6
      | c -> c, 2
    else
      source.[i + 1], 1
  let r = i + 1 + len + 1
  if source.[r - 1] <> '\'' then
    lexError "Expected closing '\''" (source, r - 1)
  let t = Token.Char c, (y, x)
  t :: acc, y, x + r - i, r

let private tokenIdent ident =
  match ident with
  | "true" -> Token.Bool true
  | "false" -> Token.Bool false
  | "do" -> Token.Do
  | "let" -> Token.Let
  | "if" -> Token.If
  | "then" -> Token.Then
  | "else" -> Token.Else
  | "match" -> Token.Match
  | "with" -> Token.With
  | "when" -> Token.When
  | "rec" -> Token.Rec
  | "private" -> Token.Private
  | "internal" -> Token.Internal
  | "public" -> Token.Public
  | "module" -> Token.Module
  | "namespace" -> Token.Namespace
  | "open" -> Token.Open
  | "type" -> Token.Type
  | "of" -> Token.Of
  | "in" -> Token.In
  | _ -> Token.Ident ident

let private tokenPunct str =
  match str with
  | ":" -> Token.Colon
  | "." -> Token.Dot
  | "|" -> Token.Pipe
  | "->" -> Token.Arrow
  | _ -> Token.Punct str

let tokenize (source: string): (Token * Loc) list =
  let at i =
    if i < source.Length then source.[i] else '\u0000'
  let rec go (acc, y, x, i) =
    if i >= source.Length then
      acc |> List.rev
    else
      match source.[i] with
      | ' ' ->
        (acc, y, x, i) |> readSpace source |> go
      | '\r'
      | '\n' ->
        (acc, y, x, i) |> readEol source |> go
      // FIXME: attributes are comments for now
      | '[' when at (i + 1) = '<' ->
        (acc, y, x, i) |> readLineComment source |> go
      | '/' when at (i + 1) = '/' ->
        (acc, y, x, i) |> readLineComment source |> go
      | '('
      | ')' as c ->
        let t = (if c = '(' then Token.ParenL else Token.ParenR), (y, x)
        (t :: acc, y, x + 1, i + 1) |> go
      | '[' ->
        ((Token.BracketL, (y, x)) :: acc, y, x + 1, i + 1) |> go
      | ']' ->
        ((Token.BracketR, (y, x)) :: acc, y, x + 1, i + 1) |> go
      | c when isOpChar c ->
        (acc, y, x, i) |> readOp source |> go
      | '"' ->
        (acc, y, x, i) |> readStr source |> go
      | '\'' ->
        (acc, y, x, i) |> readChar source |> go
      | c when isDigit c ->
        (acc, y, x, i) |> readInt source |> go
      | c when not (isDigit c) && isIdentChar c ->
        (acc, y, x, i) |> readIdent source |> go
      | _ ->
        lexError "Unknown token" (source, i)
  go ([], 0, 0, 0)
