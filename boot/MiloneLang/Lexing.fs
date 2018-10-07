module MiloneLang.Lexing

type private Context =
  | Ty
  | Val
  | Pat

// Container of syntax layout.
type private Outer =
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
      | c when isDigit c ->
        (acc, y, x, i) |> readInt source |> go
      | c when not (isDigit c) && isIdentChar c ->
        (acc, y, x, i) |> readIdent source |> go
      | _ ->
        lexError "Unknown token" (source, i)
  go ([], 0, 0, 0)

let (|NonPunct|_|) token =
  match token with
  | Token.Punct _ -> None
  | _ -> Some ()

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
  let rec go context outer acc (tokens: (Token * Loc) list): Syn list * _ list =
    let next tokens t =
      match outer, tokens with
      | Box xb, WithX (x, (NonPunct, _) :: _) when xb = x && acc <> [] ->
        go context outer (Syn.Op ";" :: t :: acc) tokens
      | _ ->
        go context outer (t :: acc) tokens

    match context, outer, tokens with
    // Closing conditions.

    // Closing token found. We drop it from tokens.
    | _, _, ([] as tokens)
    | _, Tie ")", (Token.Punct ")", _) :: tokens
    | _, Tie "=", (Token.Punct "=", _) :: tokens ->
      acc, tokens
    // Closing token clearing other boxes. We don't drop it.
    | _, Box _, (Token.Punct ")", _) :: _
    | _, Box _, (Token.Punct "=", _) :: _ ->
      acc, tokens
    // Dedents clear boxes.
    | _, Box xb, (_, (_, x)) :: _ when x < xb ->
      acc, tokens

    // Bindings.
    | _, _, (Token.Ident "let", _) :: tokens ->
      let args, WithX (x, tokens) =
        go Context.Pat (Tie "=") [] tokens
      let body, tokens =
        go Context.Val (Box x) [] tokens
      Syn.Let (List.rev args, List.rev body) |> next tokens

    // Leaves.
    | _, _, (Token.Punct "(", _) :: tokens ->
      let syns, tokens = go context (Tie ")") [] tokens
      Syn.Paren (List.rev syns) |> next tokens
    | _, _, (Token.Unit, _) :: tokens ->
      Syn.Unit |> next tokens
    | _, _, (Token.Int value, _) :: tokens ->
      Syn.Int value |> next tokens
    | _, _, (Token.String value, _) :: tokens ->
      Syn.String value |> next tokens
    | (Context.Pat | Context.Val), _, (Token.Ident value, _) :: tokens ->
      Syn.Ident value |> next tokens
    | Context.Val, _, (Token.Punct op, _) :: tokens ->
      Syn.Op op |> next tokens

    // Out of context errors.
    | (Context.Pat | Context.Ty),
      _,
      ((Token.Punct _ | Token.Ident _), _) :: _ ->
      failwithf "Token out of context %A" tokens

  let syns, _ = go Context.Ty (Box -1) [] tokens
  List.rev syns

let lex (source: string): Syn list =
  source |> tokenize |> compose
