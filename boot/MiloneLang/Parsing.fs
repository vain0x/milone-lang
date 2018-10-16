module rec MiloneLang.Parsing

open System
open MiloneLang

[<RequireQualifiedAccess>]
type TokenRole =
  | Open
  | Close

let patMap (f: 'x -> 'y) (pat: Pat<'x>): Pat<'y> =
  match pat with
  | Pat.Unit a ->
    Pat.Unit (f a)
  | Pat.Ident (name, serial, a) ->
    Pat.Ident (name, serial, f a)

let exprExtract (expr: Expr<'a>): 'a =
  match expr with
  | Expr.Unit a -> a
  | Expr.Int (_, a) -> a
  | Expr.String (_, a) -> a
  | Expr.Prim (_, a) -> a
  | Expr.Ref (_, _, a) -> a
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
  | Expr.Ref (ident, serial, a) ->
    Expr.Ref (ident, serial, f a)
  | Expr.If (pred, thenCl, elseCl, a) ->
    Expr.If (exprMap f pred, exprMap f thenCl, exprMap f elseCl, f a)
  | Expr.Call (callee, args, a) ->
    Expr.Call (exprMap f callee, List.map (exprMap f) args, f a)
  | Expr.Op (op, l, r, a) ->
    Expr.Op (op, exprMap f l, exprMap f r, f a)
  | Expr.Let (pats, init, a) ->
    Expr.Let (List.map (patMap f) pats, exprMap f init, f a)
  | Expr.Begin (exprs, a) ->
    Expr.Begin (List.map (exprMap f) exprs, f a)

let tokenRole tokens: TokenRole =
  match tokens with
  | []
  | (Token.Then, _) :: _
  | (Token.Else, _) :: _
  | (Token.ParenR, _) :: _
  | (Token.Punct _, _) :: _
    -> TokenRole.Close
  | (Token.Unit, _) :: _
  | (Token.Int _, _) :: _
  | (Token.String _, _) :: _
  | (Token.Ident _, _) :: _
  | (Token.ParenL, _) :: _
  | (Token.If _, _) :: _
  | (Token.Let, _) :: _
    -> TokenRole.Open

let leadsExpr tokens =
  tokenRole tokens = TokenRole.Open

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
let private nextInside boxX tokens: bool =
  match tokens with
  | [] ->
    false
  // Closed by something out of box.
  | (_, (_, x)) :: _
    when x < boxX ->
    false
  | _ ->
    true

let parseError message (_, tokens) =
  let near = tokens |> List.map fst |> List.truncate 6
  failwithf "Parse error %s near %A" message near

let parsePat boxX tokens: Pat<_> option * _ list =
  if nextInside boxX tokens |> not then
    None, tokens
  else
    match tokens with
    | (Token.Unit, loc) :: tokens ->
      Some (Pat.Unit loc), tokens
    | (Token.Ident value, loc) :: tokens ->
      Some (Pat.Ident (value, 0, loc)), tokens
    | _ ->
      None, tokens

let parsePats boxX (tokens: _ list): Pat<_> list * _ list =
  let rec go acc (tokens: _ list) =
    match parsePat boxX tokens with
    | Some pat, tokens ->
      go (pat :: acc) tokens
    | None, _ ->
      List.rev acc, tokens
  go [] tokens

let parseThenCl boxX tokens =
  match tokens with
  | (Token.Then, _) as t :: tokens when nextInside boxX [t] ->
    parseExpr boxX tokens
  | _ ->
    failwithf "Expected 'then' but %A" tokens

let parseElseCl boxX ifLoc tokens =
  match tokens with
  | (Token.Else, _) as t :: tokens when nextInside boxX [t] ->
    let insideX =
      match tokens with
      | (Token.If, _) :: _ ->
        boxX
      | _ ->
        max boxX (nextX tokens)
    parseExpr insideX tokens
  | _ ->
    // Append `else ()` if missing.
    Expr.Unit ifLoc, tokens

/// You can align contents on the same column as if/then/else.
let parseIf boxX ifLoc tokens =
  let pred, tokens = parseExpr boxX tokens
  let thenCl, tokens = parseThenCl boxX tokens
  let elseCl, tokens = parseElseCl boxX ifLoc tokens
  Expr.If (pred, thenCl, elseCl, ifLoc), tokens

let parseParen boxX tokens =
  match parseExpr boxX tokens with
  | expr, (Token.ParenR, _) :: tokens ->
    expr, tokens
  | _ ->
    failwithf "Expected ')' %A" tokens

let parseLet boxX letLoc tokens =
  let _, letX = letLoc
  let pats, tokens =
    let patsX = max boxX (letX + 1)
    match parsePats patsX tokens with
    | pats, (Token.Punct "=", _) :: tokens ->
      pats, tokens
    | _ ->
      failwithf "Missing '=' %A" tokens
  let body, tokens =
    let bodyX = max boxX (nextX tokens)
    parseExpr bodyX tokens
  Expr.Let (pats, body, letLoc), tokens

/// Tries to read a token that consists of a group of delimited expression.
/// atom = unit / int / string / prim / ref / ( expr )
let parseAtom boxX tokens: Expr<Loc> option * (Token * Loc) list =
  if nextInside boxX tokens |> not then
    None, tokens
  else
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
      Some (Expr.Ref (value, 0, loc)), tokens
    | (Token.ParenL, _) :: tokens ->
      let expr, tokens = parseParen boxX tokens
      Some expr, tokens
    | (Token.If, loc) :: tokens ->
      let expr, tokens = parseIf boxX loc tokens
      Some expr, tokens
    | (Token.Let, letLoc) :: tokens ->
      let expr, tokens = parseLet boxX letLoc tokens
      Some expr, tokens
    | []
    | (Token.Else, _) :: _
    | (Token.Then, _) :: _
    | (Token.ParenR, _) :: _
    | (Token.Punct _, _) :: _ ->
      None, tokens

/// call = atom ( atom )*
let parseCall boxX tokens =
  let calleeLoc = nextLoc tokens
  let _, calleeX = calleeLoc
  let insideX = max boxX (calleeX + 1)
  let first, tokens =
    match parseAtom boxX tokens with
    | Some first, tokens ->
      first, tokens
    | _ ->
      failwithf "Expected an atom %A" tokens
  let rec go acc tokens =
    match parseAtom insideX tokens with
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
  | OpLevel.Or -> parseOp OpLevel.And outer tokens
  | OpLevel.And -> parseOp OpLevel.Cmp outer tokens
  | OpLevel.Cmp -> parseOp OpLevel.Add outer tokens
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parseCall outer tokens

let rec parseOps level boxX expr tokens =
  let next expr op opLoc tokens =
    let second, tokens = parseNextLevelOp level boxX tokens
    let expr = Expr.Op (op, expr, second, opLoc)
    parseOps level boxX expr tokens
  match level, tokens with
  | OpLevel.Or, (Token.Punct "||", opLoc) :: tokens ->
    next expr Op.Or opLoc tokens
  | OpLevel.And, (Token.Punct "&&", opLoc) :: tokens ->
    next expr Op.And opLoc tokens
  | OpLevel.Cmp, (Token.Punct "=", opLoc) :: tokens ->
    next expr Op.Eq opLoc tokens
  | OpLevel.Cmp, (Token.Punct "<>", opLoc) :: tokens ->
    next expr Op.Ne opLoc tokens
  | OpLevel.Cmp, (Token.Punct "<", opLoc) :: tokens ->
    next expr Op.Lt opLoc tokens
  | OpLevel.Cmp, (Token.Punct "<=", opLoc) :: tokens ->
    next expr Op.Le opLoc tokens
  | OpLevel.Cmp, (Token.Punct ">", opLoc) :: tokens ->
    next expr Op.Gt opLoc tokens
  | OpLevel.Cmp, (Token.Punct ">=", opLoc) :: tokens ->
    next expr Op.Ge opLoc tokens
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

/// mul = call ( ('*'|'/'|'%') call )*
/// add = mul ( ('+'|'-') mul )*
let parseOp level boxX tokens =
  let first, tokens = parseNextLevelOp level boxX tokens
  parseOps level boxX first tokens

let parseOr boxX tokens =
  parseOp OpLevel.Or boxX tokens

/// let = 'let' ( pat )* '=' expr / call
let parseBinding boxX tokens =
  match tokens with
  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc tokens
  | _ ->
    parseOr boxX tokens

/// block = let ( ';' let )*
/// All expressions are aligned on the same column,
/// except it is preceded by 1+ semicolons.
let rec parseBlock boxX tokens =
  let rec go acc alignX tokens =
    match tokens with
    | (Token.Punct ";", _) :: (Token.Punct ";", _) :: tokens
      when nextX tokens >= alignX ->
      go acc alignX tokens
    | (Token.Punct ";", _) :: tokens
      when nextX tokens >= alignX ->
      let expr, tokens = parseBinding boxX tokens
      go (expr :: acc) alignX tokens
    | tokens
      when nextX tokens = alignX && leadsExpr tokens ->
      let expr, tokens = parseBinding boxX tokens
      go (expr :: acc) alignX tokens
    | _ ->
      List.rev acc, tokens

  if nextInside boxX tokens then
    go [] (nextX tokens) tokens
  else
    failwithf "Expected a list of expressions."

let parseExpr (boxX: int) (tokens: (Token * Loc) list): Expr<Loc> * (Token * Loc) list =
  match parseBlock boxX tokens with
  | [], _ ->
    failwithf "Expected an expr but %A" tokens
  | [expr], tokens ->
    expr, tokens
  | exprs, tokens ->
    Expr.Begin (exprs, nextLoc tokens), tokens

/// Composes tokens into (a kind of) syntax tree.
let parse (tokens: (Token * Loc) list): Expr<Loc> list =
  let exprs, tokens = parseBlock -1 tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  exprs
