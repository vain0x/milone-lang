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

let private readOp (source: string) (acc, y, x, i): Read =
  assert (isOpChar source.[i])
  let r = takeWhile isOpChar (source, i + 1)
  let t = Token.Punct (source.Substring(i, r - i)), (y, x)
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

let private readString (source: string) (acc, y, x, i): Read =
  assert (source.[i] = '"')
  let r = takeWhile ((<>) '"') (source, i + 1)
  if r = source.Length then
    lexError "Expected closing '\"' but eof" (source, r)
  let t = Token.String (source.Substring(i + 1, r - (i + 1))), (y, x)
  t :: acc, y, x + r - i + 1, r + 1

let private tokenIdent ident =
  match ident with
  | "let" -> Token.Let
  | "if" -> Token.If
  | "then" -> Token.Then
  | "else" -> Token.Else
  | _ -> Token.Ident ident

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
      // Don't split unit literal `()`.
      | '(' when at (i + 1) = ')' ->
        let t = Token.Unit, (y, x)
        (t :: acc, y, x + 2, i + 2) |> go
      | '('
      | ')' as c ->
        let t = (if c = '(' then Token.ParenL else Token.ParenR), (y, x)
        (t :: acc, y, x + 1, i + 1) |> go
      | c when isOpChar c ->
        (acc, y, x, i) |> readOp source |> go
      | '"' ->
        (acc, y, x, i) |> readString source |> go
      | c when isDigit c ->
        (acc, y, x, i) |> readInt source |> go
      | c when not (isDigit c) && isIdentChar c ->
        (acc, y, x, i) |> readIdent source |> go
      | _ ->
        lexError "Unknown token" (source, i)
  go ([], 0, 0, 0)
