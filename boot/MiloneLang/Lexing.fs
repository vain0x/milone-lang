module rec MiloneLang.Lexing

open MiloneLang

// Container of syntax layout.
type Outer =
  internal
  | Tie
    of close:string
  | Box
    of column:int

let private (|WithX|) tokens =
  match tokens with
  | [] ->
    0, tokens
  | (_, (_, x)) :: _ ->
    x, tokens

let private (|NonPunct|_|) token =
  match token with
  | Token.Punct _ -> None
  | _ -> Some ()

let private lexError message (source: string, i) =
  let near = source.Substring(i, min (source.Length - i) 6)
  failwithf "Lex error near '%s': %s" message near

let private isDigit c =
  '0' <= c && c <= '9'

let private isAlpha c =
  ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')

let private isIdentChar c =
  c = '_' || isDigit c || isAlpha c

/// Finds the first position that doesn't satisfy the specified predicate starting from `i`.
let private readUntil pred (source: string, i) =
  let rec go r =
    if r < source.Length && pred source.[r] then
      go (r + 1)
    else
      r
  go i

let private readSpace (source: string) (acc, y, x, i) =
  assert (source.[i] = ' ')
  let r = readUntil ((=) ' ') (source, i + 1)
  acc, y, x + r - i, r

let private readLinebreak (source: string) (acc, y, x, i) =
  assert (source.[i] = '\r' || source.[i] = '\n')
  let r =
    if i + 1 < source.Length && source.StartsWith("\r\n")
    then i + 2
    else i + 1
  acc, y + 1, 0, r

let private readIdent (source: string) (acc, y, x, i) =
  assert (isIdentChar source.[i])
  let r = readUntil isIdentChar (source, i + 1)
  let t = Token.Ident (source.Substring(i, r - i)), (y, x)
  t :: acc, y, x + r - i, r

let private readInt (source: string) (acc, y, x, i) =
  assert (isDigit source.[i])
  let r = readUntil isDigit (source, i + 1)
  let t = Token.Int (source.Substring(i, r - i) |> int), (y, x)
  t :: acc, y, x + r - i, r

let private readString (source: string) (acc, y, x, i) =
  assert (source.[i] = '"')
  let r = readUntil ((<>) '"') (source, i + 1)
  if r = source.Length then
    lexError "Expected closing '\"' but eof" (source, r)
  let t = Token.String (source.Substring(i + 1, r - (i + 1))), (y, x)
  t :: acc, y, x + r - i + 1, r + 1

let tokenize (source: string): list<Token * Loc> =
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
        (acc, y, x, i) |> readLinebreak source |> go
      | '(' when at (i + 1) = ')' ->
        let t = Token.Unit, (y, x)
        (t :: acc, y, x + 2, i + 2) |> go
      | '('
      | ')'
      | '+'
      | '=' as c ->
        let t = Token.Punct (string c), (y, x)
        go (t :: acc, y, x + 1, i + 1)
      | '"' ->
        (acc, y, x, i) |> readString source |> go
      | c when isDigit c ->
        (acc, y, x, i) |> readInt source |> go
      | c when not (isDigit c) && isIdentChar c ->
        (acc, y, x, i) |> readIdent source |> go
      | _ ->
        lexError "Unknown token" (source, i)
  go ([], 0, 0, 0)

/// Reads an arg list of `let` or `fun`.
let rec composeArgs outer tokens =
  composeFactors [] outer tokens

/// Reads a let construction.
let composeLet letX tokens =
  let args, WithX (bodyX, tokens) =
    composeArgs (Tie "=") tokens
  let body, tokens =
    composeExpr (Box (max letX bodyX)) tokens
  let syn = Syn.Let (List.rev args, body)
  syn, tokens

/// Reads a token that consists of a group of delimited tokens.
let composeFactor outer tokens =
  match outer, tokens with
  | _, (Token.Punct "(", _) :: tokens ->
    let expr, tokens = composeExpr (Tie ")") tokens
    Some expr, tokens
  | _, (Token.Unit, _) :: tokens ->
    Some Syn.Unit, tokens
  | _, (Token.Int value, _) :: tokens ->
    Some (Syn.Int value), tokens
  | _, (Token.String value, _) :: tokens ->
    Some (Syn.String value), tokens
  | _, (Token.Ident value, _) :: tokens ->
    Some (Syn.Ident value), tokens
  | _, (Token.Punct op, _) :: tokens ->
    Some (Syn.Op op), tokens
  | _, [] ->
    None, tokens

let rec composeFactors acc outer tokens =
  match composeFactor outer tokens with
  | None, tokens ->
    acc, tokens
  | Some syn, tokens ->
    let acc = syn :: acc

    match outer, tokens with
    | _, [] ->
      acc, tokens
    // Closed by delimiter.
    | Tie tie, (Token.Punct op, _) :: tokens
      when op = tie ->
      acc, tokens
    // Closed by next term or something.
    | Box boxX, (NonPunct, (_, x)) :: _
      when x <= boxX ->
      acc, tokens
    // Closed by other elements out of box.
    | Box boxX, (_, (_, x)) :: _
      when x < boxX ->
      acc, tokens

    | _, _ :: _ ->
      composeFactors acc outer tokens

/// Reads an item of semicolon-separated list.
let composeTerm outer tokens =
  match tokens with
  | (Token.Ident "let", (_, letX)) :: tokens ->
    let syn, tokens = composeLet letX tokens
    syn, tokens
  | tokens ->
    let syns, tokens = composeFactors [] outer tokens
    let syn = Syn.Term (List.rev syns)
    syn, tokens

let composeTerms acc outer tokens =
  let term, tokens = composeTerm outer tokens
  let acc = term :: acc

  match outer, tokens with
  | _, [] ->
    acc, tokens
  // Closed by other elements out of box.
  | Box boxX, (_, (_, x)) :: _
    when x < boxX ->
    acc, tokens

  | _, _ :: _ ->
    composeTerms acc outer tokens

let composeExpr outer tokens =
  let terms, tokens = composeTerms [] outer tokens
  let expr = Syn.Expr (List.rev terms)
  expr, tokens

let rec composeDefs acc outer tokens =
  match tokens with
  | [] ->
    acc, tokens
  | (Token.Ident "let", (_, letX)) :: tokens ->
    let syn, tokens = composeLet letX tokens
    composeDefs (syn :: acc) outer tokens
  | _ ->
    failwithf "Expected 'let' but %A" tokens

/// Composes tokens into (a kind of) syntax tree.
///
/// - Composing with tie token ')' will continue
/// until hits on corresponding ')'.
/// - Composing with box with column x will continue
/// until next occurrence of token with column (`<=` x).
///   - But punct tokens with column (`=` x) don't clear box.
///   - e.g. In pipeline `f x \n |> g`, you can align f and g on the same column. On the other hand, `f x \n g` (f and g are on the same column) is composed to two boxes: `f x`, `g`.
/// - Composition algorithm doesn't affect operator fixity.
///   - e.g. However you layout, `f 1 2 \n * 3` is `(f 1 2) * 3` .
let compose (tokens: (Token * Loc) list): Syn list =
  let syns, tokens = composeDefs [] (Box -1) tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  List.rev syns

/// Performs lexical analysis on string.
let lex (source: string): Syn list =
  source |> tokenize |> compose
