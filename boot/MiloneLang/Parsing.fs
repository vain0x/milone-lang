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

let exprExtract (expr: Expr<'a>): 'a =
  match expr with
  | Expr.Unit a -> a
  | Expr.Int (_, a) -> a
  | Expr.String (_, a) -> a
  | Expr.Prim (_, a) -> a
  | Expr.Ref (_, a) -> a
  | Expr.If (_, _, _, a) -> a
  | Expr.Call (_, _, a) -> a
  | Expr.Op (_, _, _, a) -> a
  | Expr.Let (_, _, a) -> a
  | Expr.Begin (_, a) -> a

let exprMap (f: 'x -> 'y) (expr: Expr<'x>): Expr<'y> =
  match expr with
  | Expr.Unit a ->
    Expr.Unit (f a)
  | Expr.Int (value, a) ->
    Expr.Int (value, f a)
  | Expr.String (value, a) ->
    Expr.String (value, f a)
  | Expr.Prim (value, a) ->
    Expr.Prim (value, f a)
  | Expr.Ref (ident, a) ->
    Expr.Ref (ident, f a)
  | Expr.If (pred, thenCl, elseCl, a) ->
    Expr.If (exprMap f pred, exprMap f thenCl, exprMap f elseCl, f a)
  | Expr.Call (callee, args, a) ->
    Expr.Call (exprMap f callee, List.map (exprMap f) args, f a)
  | Expr.Op (op, l, r, a) ->
    Expr.Op (op, exprMap f l, exprMap f r, f a)
  | Expr.Let (ident, init, a) ->
    Expr.Let (ident, exprMap f init, f a)
  | Expr.Begin (exprs, a) ->
    Expr.Begin (List.map (exprMap f) exprs, f a)

let private nextLoc tokens: Loc =
  match tokens with
  | [] ->
    (-1, 0)
  | (_, loc) :: _ ->
    loc

/// Column position of the next token if exists or 0.
let private nextX tokens: int =
  match tokens with
  | [] ->
    0
  | (_, (_, x)) :: _ ->
    x

/// Gets if next token exists and is inside the outer box.
let private nextInside (outer: Outer) tokens: bool =
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

let parsePat outer tokens: Pattern option * _ list =
  if nextInside outer tokens |> not then None, tokens else
  match tokens with
  | (Token.Unit, _) :: tokens ->
    Some Pattern.Unit, tokens
  | (Token.Ident value, _) :: tokens ->
    Some (Pattern.Ident value), tokens
  | _ ->
    None, tokens

let parsePats (outer: Outer) (tokens: _ list): Pattern list * _ list =
  let rec go acc (tokens: _ list) =
    match parsePat outer tokens with
    | Some pat, tokens ->
      go (pat :: acc) tokens
    | None, _ ->
      List.rev acc, tokens
  go [] tokens

let parseIf (outer: Outer) loc tokens =
  let _, ifX = loc
  let ifBox: Outer =
    {
      Bottom = max outer.Bottom ifX
      Tie = None
    }
  let predInside: Outer =
    {
      Bottom = ifX + 1
      Tie = Some Token.Then
    }
  let pred, tokens =
    parseExpr predInside tokens

  match tokens with
  | (Token.Then, _) as t :: tokens when nextInside ifBox [t] ->
    let thenOuter: Outer =
      {
        Bottom = max (ifX + 1) (nextX tokens)
        Tie = Some Token.Else
      }
    let thenCl, tokens =
      parseExpr thenOuter tokens
    match tokens with
    | (Token.Else, _) as t :: tokens when nextInside ifBox [t] ->
      let elseOuter: Outer =
        {
          Bottom = max (ifX + 1) (nextX tokens)
          Tie = None
        }
      let elseCl, tokens =
        parseExpr elseOuter tokens
      Expr.If (pred, thenCl, elseCl, loc), tokens
    | _ ->
      // Assume `else ()` if missing.
      let elseCl = Expr.Unit loc
      Expr.If (pred, thenCl, elseCl, loc), tokens
  | _ ->
    failwithf "Expected 'then' but %A" tokens

/// Tries to read a token that consists of a group of delimited expression.
/// atom = unit / int / string / prim / ref / ( expr )
let parseAtom outer tokens: Expr<Loc> option * (Token * Loc) list =
  if nextInside outer tokens |> not then None, tokens else
  match tokens with
  | (Token.Unit, loc) :: tokens ->
    Some (Expr.Unit loc), tokens
  | (Token.Int value, loc) :: tokens ->
    Some (Expr.Int (value, loc)), tokens
  | (Token.String value, loc) :: tokens ->
    Some (Expr.String (value, loc)), tokens
  | (Token.Ident "printfn", loc) :: tokens ->
    Some (Expr.Prim (PrimFun.Printfn, loc)), tokens
  | (Token.Ident value, loc) :: tokens ->
    Some (Expr.Ref (value, loc)), tokens
  | (Token.ParenL, _) :: tokens ->
    let inside = { outer with Tie = Some Token.ParenR }
    match parseExpr inside tokens with
    | expr, (Token.ParenR, _) :: tokens ->
      Some expr, tokens
    | _ ->
      failwithf "Expected ')' %A" tokens
  | (Token.If, loc) :: tokens ->
    let expr, tokens = parseIf outer loc tokens
    Some expr, tokens
  | []
  | (Token.Else, _) :: _
  | (Token.Then, _) :: _
  | (Token.ParenR, _) :: _
  | (Token.Punct _, _) :: _ ->
    None, tokens

/// call = atom ( atom )*
let parseCall outer tokens =
  let (_, calleeX) as calleeLoc = nextLoc tokens
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
    Expr.Call (first, List.rev args, calleeLoc), tokens

let parseNextLevelOp level outer tokens =
  match level with
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parseCall outer tokens

/// mul = call ( ('*'|'/'|'%') call )*
/// add = mul ( ('+'|'-') mul )*
let parseOp level outer tokens =
  let rec loop expr tokens =
    let next expr op opLoc tokens =
      let second, tokens = parseNextLevelOp level outer tokens
      let acc = Expr.Op (op, expr, second, opLoc)
      loop acc tokens
    match level, tokens with
    | OpLevel.Add, (Token.Punct "+", opLoc) :: tokens ->
      next expr Op.Add opLoc tokens
    | OpLevel.Add, (Token.Punct "-", opLoc) :: tokens ->
      next expr Op.Sub opLoc tokens
    | OpLevel.Mul, (Token.Punct "*", opLoc) :: tokens ->
      next expr Op.Mul opLoc tokens
    | OpLevel.Mul, (Token.Punct "/", opLoc) :: tokens ->
      next expr Op.Div opLoc tokens
    | OpLevel.Mul, (Token.Punct "%", opLoc) :: tokens ->
      next expr Op.Mod opLoc tokens
    | _ ->
      expr, tokens

  let first, tokens = parseNextLevelOp level outer tokens
  loop first tokens

let parseMul outer tokens =
  parseOp OpLevel.Mul outer tokens

let parseAdd outer tokens =
  parseOp OpLevel.Add outer tokens

/// let = 'let' ( pat )* '=' expr / call
let parseLet outer tokens =
  match tokens with
  | (Token.Ident "let", letLoc) :: (tokens as beforePatsTokens) ->
    let pats, tokens =
      let inside = { outer with Tie = Token.Punct "=" |> Some }
      match parsePats inside tokens with
      | pats, (Token.Punct "=", _) :: tokens ->
        pats, tokens
      | _ ->
        failwithf "Missing '=' %A" tokens
    let body, tokens =
      let (_, letX), bodyX = letLoc, nextX tokens
      let inside = { outer with Bottom = max letX bodyX }
      parseExpr inside tokens
    let expr =
      match pats with
      | [Pattern.Ident name]
      | [Pattern.Ident name; Pattern.Unit] ->
        Expr.Let (name, body, letLoc)
      | [] ->
        failwithf "Expected a pattern at %A" beforePatsTokens
      | _ ->
        failwithf "unimpl let %A" pats
    expr, tokens
  | _ ->
    parseAdd outer tokens

let leadsExpr tokens =
  match tokens with
  | [] -> false
  | (Token.Unit, _) :: _
  | (Token.Int _, _) :: _
  | (Token.String _, _) :: _
  | (Token.Ident _, _) :: _
  | (Token.ParenL, _) :: _
  | (Token.If _, _) :: _
    -> true
  | (Token.Then, _) :: _
  | (Token.Else, _) :: _
  | (Token.ParenR, _) :: _
  | (Token.Punct _, _) :: _
    -> false

/// block = ( let )+
let rec parseBlock outer tokens =
  let rec go acc tokens =
    let nextInside = nextInside outer tokens
    match tokens with
    | (Token.Punct ";", _) :: tokens
    | tokens
      when nextInside && leadsExpr tokens ->
      let expr, tokens = parseLet outer tokens
      go (expr :: acc) tokens
    | _ ->
      List.rev acc, tokens
  go [] tokens

let parseExpr (outer: Outer) (tokens: (Token * Loc) list): Expr<Loc> * (Token * Loc) list =
  match parseBlock outer tokens with
  | [], _ ->
    failwithf "Expected an expr but %A" tokens
  | [expr], tokens ->
    expr, tokens
  | exprs, tokens ->
    Expr.Begin (exprs, nextLoc tokens), tokens

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
let parse (tokens: (Token * Loc) list): Expr<Loc> list =
  let outer = { Tie = None; Bottom = -1 }
  let exprs, tokens = parseBlock outer tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  exprs
