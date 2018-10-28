module rec MiloneLang.Parsing

open System
open MiloneLang

let patExtract (pat: Pat<'a>): 'a =
  match pat with
  | Pat.Unit a -> a
  | Pat.Int (_, a) -> a
  | Pat.Ident (_, _, a) -> a
  | Pat.Tuple (_, _, a) -> a
  | Pat.Anno (_, _, a) -> a

let patMap (f: 'x -> 'y) (pat: Pat<'x>): Pat<'y> =
  match pat with
  | Pat.Unit a ->
    Pat.Unit (f a)
  | Pat.Int (value, a) ->
    Pat.Int (value, f a)
  | Pat.Ident (name, serial, a) ->
    Pat.Ident (name, serial, f a)
  | Pat.Tuple (l, r, a) ->
    Pat.Tuple (patMap f l, patMap f r, f a)
  | Pat.Anno (pat, ty, a) ->
    Pat.Anno (patMap f pat, ty, f a)

let exprExtract (expr: Expr<'a>): 'a =
  match expr with
  | Expr.Unit a -> a
  | Expr.Bool (_, a) -> a
  | Expr.Int (_, a) -> a
  | Expr.Str (_, a) -> a
  | Expr.Prim (_, a) -> a
  | Expr.Ref (_, _, a) -> a
  | Expr.List (_, a) -> a
  | Expr.If (_, _, _, a) -> a
  | Expr.Match (_, _, _, a) -> a
  | Expr.Index (_, _, a) -> a
  | Expr.Call (_, _, a) -> a
  | Expr.Op (_, _, _, a) -> a
  | Expr.Anno (_, _, a) -> a
  | Expr.AndThen (_, a) -> a
  | Expr.Let (_, _, a) -> a

let exprMap (f: 'x -> 'y) (expr: Expr<'x>): Expr<'y> =
  match expr with
  | Expr.Unit a ->
    Expr.Unit (f a)
  | Expr.Bool (value, a) ->
    Expr.Bool (value, f a)
  | Expr.Int (value, a) ->
    Expr.Int (value, f a)
  | Expr.Str (value, a) ->
    Expr.Str (value, f a)
  | Expr.Prim (value, a) ->
    Expr.Prim (value, f a)
  | Expr.Ref (ident, serial, a) ->
    Expr.Ref (ident, serial, f a)
  | Expr.List (items, a) ->
    Expr.List (List.map (exprMap f) items, f a)
  | Expr.If (pred, thenCl, elseCl, a) ->
    Expr.If (exprMap f pred, exprMap f thenCl, exprMap f elseCl, f a)
  | Expr.Match (target, (pat1, body1), (pat2, body2), a) ->
    let arm1 = (patMap f pat1, exprMap f body1)
    let arm2 = (patMap f pat2, exprMap f body2)
    Expr.Match (exprMap f target, arm1, arm2, f a)
  | Expr.Index (l, r, a) ->
    Expr.Index (exprMap f l, exprMap f r, f a)
  | Expr.Call (callee, args, a) ->
    Expr.Call (exprMap f callee, List.map (exprMap f) args, f a)
  | Expr.Op (op, l, r, a) ->
    Expr.Op (op, exprMap f l, exprMap f r, f a)
  | Expr.Anno (expr, ty, a) ->
    Expr.Anno (exprMap f expr, ty, f a)
  | Expr.AndThen (exprs, a) ->
    Expr.AndThen (List.map (exprMap f) exprs, f a)
  | Expr.Let (pats, init, a) ->
    Expr.Let (List.map (patMap f) pats, exprMap f init, f a)

/// Gets if next token exists and should lead some construction (expr/pat/ty).
/// We use this for a kind of prediction.
/// E.g. if you are looking for an expr and the following token is an integer,
/// the following tokens should start with an expression,
/// even if we don't know how many tokens participate that expr.
let tokenRole tokens: bool * bool =
  match tokens with
  | []
  | (Token.Then, _) :: _
  | (Token.Else, _) :: _
  | (Token.With, _) :: _
  | (Token.ParenR, _) :: _
  | (Token.BracketR, _) :: _
  | (Token.Colon, _) :: _
  | (Token.Dot, _) :: _
  | (Token.Pipe, _) :: _
  | (Token.Arrow, _) :: _
  | (Token.Punct _, _) :: _ ->
    // These tokens are read only in specific contexts.
    false, false
  | (Token.Unit, _) :: _
  | (Token.Int _, _) :: _
  | (Token.Str _, _) :: _
  | (Token.Ident _, _) :: _
  | (Token.ParenL, _) :: _
  | (Token.BracketL, _) :: _ ->
    // It can be an expr or pat.
    true, true
  | (Token.If _, _) :: _
  | (Token.Match _, _) :: _
  | (Token.Let, _) :: _ ->
    // It is an expr, not pat.
    true, false

let leadsExpr tokens =
  let leadsExpr, _ = tokenRole tokens
  leadsExpr

let leadsPat tokens =
  let _, leadsPat = tokenRole tokens
  leadsPat

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

let parseError message tokens =
  let near = tokens |> List.map fst |> List.truncate 6
  failwithf "Parse error %s near %A" message near

let parseTyAtom boxX tokens: Ty * _ list =
  match tokens with
  | _ when nextInside boxX tokens |> not ->
    parseError "Expected a type atom" tokens
  | (Token.Ident "unit", _) :: tokens ->
    Ty.Unit, tokens
  | (Token.Ident "bool", _) :: tokens ->
    Ty.Bool, tokens
  | (Token.Ident "int", _) :: tokens ->
    Ty.Int, tokens
  | (Token.Ident "string", _) :: tokens ->
    Ty.Str, tokens
  | (Token.ParenL, _) :: tokens ->
    match parseTy (nextX tokens) tokens with
    | ty, (Token.ParenR, _) :: tokens ->
      ty, tokens
    | _, tokens ->
      parseError "Expected ')'" tokens
  | _ ->
    parseError "Expected a type atom" tokens

/// ty-fun = ty-atom ( '->' ty-fun )?
let parseTyFun boxX tokens =
  match parseTyAtom boxX tokens with
  | sTy, (Token.Arrow, _) :: tokens ->
    let tTy, tokens = parseTyFun boxX tokens
    Ty.Fun(sTy, tTy), tokens
  | ty, tokens ->
    ty, tokens

let parseTy boxX tokens: Ty * _ list =
  parseTyFun boxX tokens

let parsePatAtom boxX tokens: Pat<_> * _ list =
  match tokens with
  | _ when not (nextInside boxX tokens && leadsPat tokens) ->
    parseError "Expected a pattern atom" tokens
  | (Token.Unit, loc) :: tokens ->
    Pat.Unit loc, tokens
  | (Token.Int value, loc) :: tokens ->
    Pat.Int (value, loc), tokens
  | (Token.Ident value, loc) :: tokens ->
    Pat.Ident (value, 0, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    match parsePat (nextX tokens) tokens with
    | pat, (Token.ParenR, _) :: tokens ->
      pat, tokens
    | _, tokens ->
      parseError "Expected ')'" tokens
  | _ ->
    failwith "never"

/// pat-tuple = pat-atom ( ',' pat-atom )?
let parsePatTuple boxX tokens =
  match parsePatAtom boxX tokens with
  | l, (Token.Punct ",", loc) :: tokens ->
    let r, tokens = parsePatAtom boxX tokens
    Pat.Tuple (l, r, loc), tokens
  | l, tokens ->
    l, tokens

/// pat-anno = pat-tuple ( ':' ty )?
let parsePatAnno boxX tokens =
  match parsePatTuple boxX tokens with
  | pat, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    Pat.Anno (pat, ty, loc), tokens
  | pat, tokens ->
    pat, tokens

let parsePat boxX tokens: Pat<_> * _ list =
  if not (nextInside boxX tokens && leadsPat tokens) then
    parseError "Expected a pattern" tokens
  else
    parsePatAnno boxX tokens

let parsePats boxX (tokens: _ list): Pat<_> list * _ list =
  let rec go acc (tokens: _ list) =
    if nextInside boxX tokens && leadsPat tokens then
      let pat, tokens = parsePat boxX tokens
      go (pat :: acc) tokens
    else
      List.rev acc, tokens
  go [] tokens

let parseList boxX bracketLoc tokens =
  match parseBindings boxX tokens with
  | exprs, (Token.BracketR, _) :: tokens ->
    Expr.List (exprs, bracketLoc), tokens
  | _, tokens ->
    parseError "Expected ']'" tokens

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

let parseMatchArm boxX tokens =
  let tokens =
    match tokens with
    | (Token.Pipe, _) :: tokens -> tokens
    | _ -> tokens
  let pat, tokens =
    match parsePat boxX tokens with
    | pat, (Token.Arrow, _) :: tokens ->
      pat, tokens
    | _, tokens ->
      parseError "Expected '->'" tokens
  let body, tokens =
    parseExpr boxX tokens
  (pat, body), tokens

let parseMatch boxX matchLoc tokens =
  let target, tokens =
    match parseExpr boxX tokens with
    | expr, (Token.With, _) :: tokens ->
      expr, tokens
    | _, tokens ->
      parseError "Expected 'with'" tokens
  let arm1, tokens = parseMatchArm boxX tokens
  let arm2, tokens = parseMatchArm boxX tokens
  Expr.Match (target, arm1, arm2, matchLoc), tokens

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

/// atom  = unit / int / string / bool / prim / ref
///       / ( expr ) / if-then-else / match-with / let
let parseAtom boxX tokens: Expr<Loc> * (Token * Loc) list =
  match tokens with
  | _ when not (nextInside boxX tokens) ->
    parseError "Expected an atomic expression" tokens
  | (Token.Unit, loc) :: tokens ->
    Expr.Unit loc, tokens
  | (Token.Int value, loc) :: tokens ->
    Expr.Int (value, loc), tokens
  | (Token.Str value, loc) :: tokens ->
    Expr.Str (value, loc), tokens
  | (Token.Ident "false", loc) :: tokens ->
    Expr.Bool (false, loc), tokens
  | (Token.Ident "true", loc) :: tokens ->
    Expr.Bool (true, loc), tokens
  | (Token.Ident "exit", loc) :: tokens ->
    Expr.Prim (PrimFun.Exit, loc), tokens
  | (Token.Ident "printfn", loc) :: tokens ->
    Expr.Prim (PrimFun.Printfn, loc), tokens
  | (Token.Ident value, loc) :: tokens ->
    Expr.Ref (value, 0, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    parseParen boxX tokens
  | (Token.BracketL, bracketLoc) :: tokens ->
    parseList boxX bracketLoc tokens
  | (Token.If, loc) :: tokens ->
    parseIf boxX loc tokens
  | (Token.Match, loc) :: tokens ->
    parseMatch boxX loc tokens
  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc tokens
  | []
  | (Token.Else, _) :: _
  | (Token.Then, _) :: _
  | (Token.With, _) :: _
  | (Token.ParenR, _) :: _
  | (Token.BracketR, _) :: _
  | (Token.Colon, _) :: _
  | (Token.Dot, _) :: _
  | (Token.Pipe, _) :: _
  | (Token.Arrow, _) :: _
  | (Token.Punct _, _) :: _ ->
    parseError "Expected an atomic expression" tokens

/// index = atom ( '.' '[' expr ']' )*
let parseIndex boxX tokens =
  let callee, tokens = parseAtom boxX tokens
  let rec go acc tokens =
    match tokens with
    | (Token.Dot, loc) :: (Token.BracketL, _) :: tokens ->
      match parseExpr boxX tokens with
      | expr, (Token.BracketR, _) :: tokens ->
        go (Expr.Index (acc, expr, loc)) tokens
      | _, tokens ->
        parseError "Expected closing ']'" tokens
    | _ ->
      acc, tokens
  go callee tokens

/// call = index ( index )*
let parseCall boxX tokens =
  let calleeLoc = nextLoc tokens
  let _, calleeX = calleeLoc
  let insideX = max boxX (calleeX + 1)
  let callee, tokens = parseIndex boxX tokens
  let rec go acc tokens =
    if nextInside insideX tokens && leadsExpr tokens then
      let expr, tokens = parseIndex insideX tokens
      go (expr :: acc) tokens
    else
      List.rev acc, tokens
  match go [] tokens with
  | [], tokens ->
    callee, tokens
  | args, tokens ->
    Expr.Call (callee, args, calleeLoc), tokens

let parseNextLevelOp level outer tokens =
  match level with
  | OpLevel.Tie -> parseOp OpLevel.Or outer tokens
  | OpLevel.Or -> parseOp OpLevel.And outer tokens
  | OpLevel.And -> parseOp OpLevel.Cmp outer tokens
  | OpLevel.Cmp -> parseOp OpLevel.Cons outer tokens
  | OpLevel.Cons -> parseOp OpLevel.Add outer tokens
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parseCall outer tokens

let rec parseOps level boxX expr tokens =
  let next expr op opLoc tokens =
    let second, tokens = parseNextLevelOp level boxX tokens
    let expr = Expr.Op (op, expr, second, opLoc)
    parseOps level boxX expr tokens
  match level, tokens with
  | OpLevel.Tie, (Token.Punct ",", opLoc) :: tokens ->
    next expr Op.Tie opLoc tokens
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
  | OpLevel.Cons, (Token.Punct "::", opLoc) :: tokens ->
    next expr Op.Cons opLoc tokens
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

/// E.g. add = mul ( ('+'|'-') mul )*
let parseOp level boxX tokens =
  let first, tokens = parseNextLevelOp level boxX tokens
  parseOps level boxX first tokens

let parseTerm boxX tokens =
  parseOp OpLevel.Tie boxX tokens

/// anno = term ( ':' ty )?
let parseAnno boxX tokens =
  match parseTerm boxX tokens with
  | expr, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    Expr.Anno (expr, ty, loc), tokens
  | expr, tokens ->
    expr, tokens

/// let = 'let' ( pat )* '=' expr / anno
let parseBinding boxX tokens =
  match tokens with
  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc tokens
  | _ ->
    parseAnno boxX tokens

/// All expressions must be aligned on the same column,
/// except it is preceded by 1+ semicolons.
let rec parseBindings boxX tokens =
  let rec go acc alignX tokens =
    match tokens with
    | (Token.Punct ";", _) :: ((Token.Punct ";", _) :: _ as tokens) ->
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
  go [] (nextX tokens) tokens

/// and-then = binding ( ';' binding )*
let parseAndThen boxX tokens =
  match parseBindings boxX tokens with
  | [], _ ->
    failwithf "Expected an expr but %A" tokens
  | [expr], tokens ->
    expr, tokens
  | exprs, tokens ->
    Expr.AndThen (exprs, nextLoc tokens), tokens

let parseExpr (boxX: int) (tokens: (Token * Loc) list): Expr<Loc> * (Token * Loc) list =
  parseAndThen boxX tokens

/// module = ( binding ( ';' binding )* )?
/// Composes tokens into (a kind of) syntax tree.
let parse (tokens: (Token * Loc) list): Expr<Loc> list =
  let exprs, tokens =
    match tokens with
    | [] -> [], []
    | _ -> parseBindings -1 tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  exprs
