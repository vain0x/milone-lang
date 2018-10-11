module rec MiloneLang.Parsing

open System
open MiloneLang

/// Container of syntax layout.
type Outer =
  {
    /// Closing token for the current box.
    /// e.g. ')' for `( .. )` box; `=` for `let .. =` box.
    Tie: Token option
    /// Bottom of columns of the current box.
    Bottom: int
  }

/// Column position of the next token if exists or 0.
let private nextX tokens =
  match tokens with
  | [] ->
    0
  | (_, (_, x)) :: _ ->
    x

/// Gets if next token exists and is inside the outer box.
let private nextInside (outer: Outer) (tokens: (Token * Loc) list) =
  match outer, tokens with
  | _, [] ->
    false
  // Closed by delimiter.
  | { Tie = Some tie }, (t, _) :: _
    when t = tie ->
    false
  // Closed by something out of box.
  | { Bottom = boxX }, (_, (_, x)) :: _
    when x < boxX ->
    false
  | _ ->
    true

let parseError message (_, syns) =
  let near = syns |> List.truncate 6
  failwithf "Parse error %s near %A" message near

let parsePat outer tokens =
  if nextInside outer tokens |> not then None, tokens else
  match tokens with
  | (Token.Unit, _) :: tokens ->
    Some Pattern.Unit, tokens
  | (Token.Ident value, _) :: tokens ->
    Some (Pattern.Ident value), tokens
  | _ ->
    None, tokens

let parsePats (outer: Outer) (tokens: _ list) =
  let rec go acc (tokens: _ list) =
    match parsePat outer tokens with
    | Some pat, tokens ->
      go (pat :: acc) tokens
    | None, _ ->
      List.rev acc, tokens
  go [] tokens

/// Tries to read a token that consists of a group of delimited expression.
/// atom = unit / int / string / prim / ref / ( expr )
let parseAtom outer tokens =
  if nextInside outer tokens |> not then None, tokens else
  match tokens with
  | (Token.Unit, _) :: tokens ->
    Some Expr.Unit, tokens
  | (Token.Int value, _) :: tokens ->
    Some (Expr.Int value), tokens
  | (Token.String value, _) :: tokens ->
    Some (Expr.String value), tokens
  | (Token.Ident "printfn", _) :: tokens ->
    Some (Expr.Prim PrimFun.Printfn), tokens
  | (Token.Ident value, _) :: tokens ->
    Some (Expr.Ref value), tokens
  | (Token.ParenL, _) :: tokens ->
    let inside = { outer with Tie = Some Token.ParenR }
    match parseExpr inside tokens with
    | expr, (Token.ParenR, _) :: tokens ->
      Some expr, tokens
    | _ ->
      failwithf "Expected ')' %A" tokens
  | []
  | (Token.ParenR, _) :: _
  | (Token.Punct _, _) :: _ ->
    None, tokens

/// call = atom ( atom )*
let parseCall outer tokens =
  let calleeX = nextX tokens
  let first, tokens =
    match parseAtom outer tokens with
    | Some first, tokens ->
      first, tokens
    | _ ->
      failwithf "Expected an atom %A" tokens
  let inside =
    { outer with Bottom = max outer.Bottom (calleeX + 1) }
  let rec go acc tokens =
    match parseAtom inside tokens with
    | Some atom, tokens ->
      go (atom :: acc) tokens
    | None, _ ->
      acc, tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | args, tokens ->
    Expr.Call (first, List.rev args), tokens

/// add = call ( '+' call )*
let parseAdd outer tokens =
  let rec go expr tokens =
    match tokens with
    | (Token.Punct "+", _) :: tokens ->
      let second, syns = parseCall outer tokens
      let acc = Expr.Add (expr, second)
      go acc syns
    | _ ->
      expr, tokens
  let first, tokens = parseCall outer tokens
  go first tokens

/// let = 'let' ( pat )* '=' expr / call
let parseLet outer tokens =
  match tokens with
  | (Token.Ident "let", (_, letX)) :: (tokens as beforePatsTokens) ->
    let pats, tokens =
      let inside = { outer with Tie = Token.Punct "=" |> Some }
      match parsePats inside tokens with
      | pats, (Token.Punct "=", _) :: tokens ->
        pats, tokens
      | _ ->
        failwithf "Missing '=' %A" tokens
    let body, tokens =
      let bodyX = nextX tokens
      let inside = { outer with Bottom = max letX bodyX }
      parseExpr inside tokens
    let expr =
      match pats with
      | [Pattern.Ident name]
      | [Pattern.Ident name; Pattern.Unit] ->
        Expr.Let (name, body)
      | [] ->
        failwithf "Expected a pattern at %A" beforePatsTokens
      | _ ->
        failwithf "unimpl let %A" pats
    expr, tokens
  | _ ->
    parseAdd outer tokens

/// block = ( let )+
let rec parseBlock outer tokens =
  let rec go acc tokens =
    match tokens with
    | _ when nextInside outer tokens |> not ->
      List.rev acc, tokens
    | (Token.Punct ";", _) :: tokens
    | tokens ->
      let expr, tokens = parseLet outer tokens
      go (expr :: acc) tokens
  go [] tokens

let parseExpr outer tokens =
  match parseBlock outer tokens with
  | [], _ ->
    failwithf "Expected an expr but %A" tokens
  | [expr], tokens ->
    expr, tokens
  | exprs, tokens ->
    Expr.Begin exprs, tokens

/// Composes tokens into (a kind of) syntax tree.
///
/// - Composing with tie token `)` will continue
/// until hits on corresponding `)`, not depending on indent.
/// - Composing with box on column `x` will continue
/// until hits on next token on column (`<` x).
///   - Exceptionally, operators on column (`=` x) don't clear box.
///   - e.g. In pipeline `f x \n |> g`, you can align f and `|>` on the same column.
///     On the other hand, `f x \n g` is composed to two boxes: `f x` and `g`.
/// - Composition algorithm doesn't affect operator fixity.
///   - e.g. Whatever layout is, `f 1 2 \n * 3` is `(f 1 2) * 3` .
let parse (tokens: (Token * Loc) list): Expr list =
  let outer = { Tie = None; Bottom = -1 }
  let exprs, tokens = parseBlock outer tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  exprs
