module rec MiloneLang.Parsing

open MiloneLang
open MiloneLang.Helpers

/// Gets if next token exists and should lead some construction (expr/pat/ty).
/// We use this for a kind of prediction.
/// E.g. if you are looking for an expr and the following token is an integer,
/// the following tokens should start with an expression,
/// even if we don't know how many tokens participate that expr.
let tokenRole tokens: bool * bool =
  match tokens with
  | (Token.Int _, _) :: _
  | (Token.Char _, _) :: _
  | (Token.Str _, _) :: _
  | (Token.Ident _, _) :: _
  | (Token.ParenL, _) :: _
  | (Token.BracketL, _) :: _ ->
    // It can be an expr or pat.
    true, true
  | (Token.If _, _) :: _
  | (Token.Match _, _) :: _
  | (Token.Do, _) :: _
  | (Token.Let, _) :: _ ->
    // It is an expr, not pat.
    true, false
  | _ ->
    // Other tokens are read only in specific contexts.
    false, false

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
  | (Token.Ident "char", _) :: tokens ->
    Ty.Char, tokens
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

/// ty-list = ty-atom ( 'list' )*
let parseTyList boxX tokens =
  let rec go first tokens =
    match tokens with
    | (Token.Ident "list", _) :: tokens ->
      go (Ty.List first) tokens
    | tokens ->
      first, tokens
  let first, tokens = parseTyAtom boxX tokens
  go first tokens

/// ty-tuple = ty-list ( '\*' ty-list )\*
let parseTyTuple boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Punct "*", _) :: tokens when nextInside boxX tokens ->
      let second, tokens = parseTyList boxX tokens
      go (second :: acc) tokens
    | _ ->
      List.rev acc, tokens
  let first, tokens = parseTyList boxX tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | itemTys, tokens ->
    Ty.Tuple (first :: itemTys), tokens

/// ty-fun = ty-tuple ( '->' ty-fun )?
let parseTyFun boxX tokens =
  match parseTyTuple boxX tokens with
  | sTy, (Token.Arrow, _) :: tokens ->
    let tTy, tokens = parseTyFun boxX tokens
    Ty.Fun (sTy, tTy), tokens
  | ty, tokens ->
    ty, tokens

let parseTy boxX tokens: Ty * _ list =
  parseTyFun boxX tokens

let parsePatAtom boxX tokens: Pat<_> * _ list =
  match tokens with
  | _ when not (nextInside boxX tokens && leadsPat tokens) ->
    parseError "Expected a pattern atom" tokens
  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    Pat.Unit loc, tokens
  | (Token.Int value, loc) :: tokens ->
    Pat.Value (Value.Int value, loc), tokens
  | (Token.Ident ident, loc) :: tokens ->
    Pat.Ref (ident, noSerial, noTy, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    match parsePat (nextX tokens) tokens with
    | pat, (Token.ParenR, _) :: tokens ->
      pat, tokens
    | _, tokens ->
      parseError "Expected ')'" tokens
  | (Token.BracketL, loc) :: (Token.BracketR, _) :: tokens ->
    Pat.Nil (noTy, loc), tokens
  | _ ->
    failwith "never"

/// pat-cons = pat-atom ( '::' pat-cons )?
let parsePatCons boxX tokens =
  match parsePatAtom boxX tokens with
  | l, (Token.Punct "::", loc) :: tokens ->
    let r, tokens = parsePatCons boxX tokens
    Pat.Cons (l, r, noTy, loc), tokens
  | l, tokens ->
    l, tokens

/// pat-anno = pat-cons ( ':' ty )?
let parsePatAnno boxX tokens =
  match parsePatCons boxX tokens with
  | pat, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    Pat.Anno (pat, ty, loc), tokens
  | pat, tokens ->
    pat, tokens

/// pat-tuple = pat-anno ( ',' pat-anno )*
let parsePatTuple boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Punct ",", _) :: tokens when nextInside boxX tokens ->
      let second, tokens = parsePatAnno boxX tokens
      go (second :: acc) tokens
    | _ ->
      List.rev acc, tokens
  let loc = nextLoc tokens
  let first, tokens = parsePatAnno boxX tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | itemPats, tokens ->
    Pat.Tuple (first :: itemPats, noTy, loc), tokens

/// pat = pat-tuple
let parsePat boxX tokens: Pat<_> * _ list =
  if not (nextInside boxX tokens && leadsPat tokens) then
    parseError "Expected a pattern" tokens
  else
    parsePatTuple boxX tokens

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
    Expr.List (exprs, noTy, bracketLoc), tokens
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
  Expr.If (pred, thenCl, elseCl, noTy, ifLoc), tokens

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
  Expr.Match (target, arm1, arm2, noTy, matchLoc), tokens

let parseParen boxX tokens =
  match parseExpr boxX tokens with
  | expr, (Token.ParenR, _) :: tokens ->
    expr, tokens
  | _ ->
    failwithf "Expected ')' %A" tokens

let parseAccessModifier tokens =
  match tokens with
  | ((Token.Private | Token.Internal | Token.Public), _) :: tokens ->
    // FIXME: support access modifiers
    tokens
  | _ ->
    tokens

let parseLet boxX letLoc tokens =
  let _, letX = letLoc
  let pats, tokens =
    let patsX = max boxX (letX + 1)
    let tokens = parseAccessModifier tokens
    match parsePats patsX tokens with
    | pats, (Token.Punct "=", _) :: tokens ->
      pats, tokens
    | _ ->
      failwithf "Missing '=' %A" tokens
  let body, tokens =
    let bodyX = max boxX (nextX tokens)
    parseExpr bodyX tokens
  Expr.Let (pats, body, letLoc), tokens

/// atom  = unit / int / char /string / bool / prim / ref
///       / ( expr ) / if-then-else / match-with / let
let parseAtom boxX tokens: Expr<Loc> * (Token * Loc) list =
  match tokens with
  | _ when not (nextInside boxX tokens) ->
    parseError "Expected an atomic expression" tokens
  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    Expr.Unit loc, tokens
  | (Token.Int value, loc) :: tokens ->
    Expr.Value (Value.Int value, loc), tokens
  | (Token.Char value, loc) :: tokens ->
    Expr.Value (Value.Char value, loc), tokens
  | (Token.Str value, loc) :: tokens ->
    Expr.Value (Value.Str value, loc), tokens
  | (Token.Ident "false", loc) :: tokens ->
    Expr.Value (Value.Bool false, loc), tokens
  | (Token.Ident "true", loc) :: tokens ->
    Expr.Value (Value.Bool true, loc), tokens
  | (Token.Ident value, loc) :: tokens ->
    Expr.Ref (value, noSerial, noTy, loc), tokens
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
  | _ ->
    parseError "Expected an atomic expression" tokens

/// index = atom ( '.' '[' expr ']' | '.' field )*
let parseIndex boxX tokens =
  let callee, tokens = parseAtom boxX tokens
  let rec go acc tokens =
    match tokens with
    | (Token.Dot, loc) :: (Token.BracketL, _) :: tokens ->
      match parseExpr boxX tokens with
      | expr, (Token.BracketR, _) :: tokens ->
        go (Expr.Index (acc, expr, noTy, loc)) tokens
      | _, tokens ->
        parseError "Expected closing ']'" tokens
    | (Token.Dot, loc) :: (Token.Ident field, _) :: tokens ->
      go (Expr.Nav (acc, field, noTy, loc)) tokens
    | (Token.Dot, _) :: tokens ->
      parseError "Expected .[] or .field" tokens
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
    Expr.Call (callee, args, noTy, calleeLoc), tokens

let parseNextLevelOp level outer tokens =
  match level with
  | OpLevel.Range -> parseOp OpLevel.Or outer tokens
  | OpLevel.Or -> parseOp OpLevel.And outer tokens
  | OpLevel.And -> parseOp OpLevel.Cmp outer tokens
  | OpLevel.Cmp -> parseOp OpLevel.Cons outer tokens
  | OpLevel.Cons -> parseOp OpLevel.Add outer tokens
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parseCall outer tokens

let rec parseOps level boxX expr tokens =
  let next expr op opLoc tokens =
    let second, tokens = parseNextLevelOp level boxX tokens
    let expr = Expr.Op (op, expr, second, noTy, opLoc)
    parseOps level boxX expr tokens
  let nextR expr op opLoc tokens =
    let second, tokens = parseOp level boxX tokens
    let expr = Expr.Op (op, expr, second, noTy, opLoc)
    parseOps level boxX expr tokens
  match level, tokens with
  | OpLevel.Range, (Token.Punct "..", opLoc) :: tokens ->
    next expr Op.Range opLoc tokens
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
    nextR expr Op.Cons opLoc tokens
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
  parseOp OpLevel.Range boxX tokens

/// tuple = term ( ',' term )*
let parseTuple boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Punct ",", _) :: tokens when nextInside boxX tokens ->
      let second, tokens = parseTerm boxX tokens
      go (second :: acc) tokens
    | tokens ->
      List.rev acc, tokens
  let loc = nextLoc tokens
  let first, tokens = parseTerm boxX tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | acc, tokens ->
    Expr.Tuple (first :: acc, noTy, loc), tokens

/// anno = tuple ( ':' ty )?
let parseAnno boxX tokens =
  match parseTuple boxX tokens with
  | expr, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    Expr.Anno (expr, ty, loc), tokens
  | expr, tokens ->
    expr, tokens

/// let = 'let' ( pat )* '=' expr / anno
let parseBinding boxX tokens =
  match tokens with
  | (Token.Let, letLoc) :: (Token.Rec, _) :: tokens ->
    // FIXME: use `rec`
    parseLet boxX letLoc tokens
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
    Expr.AndThen (exprs, noTy, nextLoc tokens), tokens

let parseExpr (boxX: int) (tokens: (Token * Loc) list): Expr<Loc> * (Token * Loc) list =
  parseAndThen boxX tokens

/// stub
let parseModule (boxX: int) tokens =
  match tokens with
  | (Token.Module, (_, moduleX))
    :: (Token.Ident _, _)
    :: (Token.Punct "=", _) :: tokens ->
    parseBindings (moduleX + 1) tokens
  | _ ->
    parseBindings boxX tokens

/// module = ( binding ( ';' binding )* )?
/// Composes tokens into (a kind of) syntax tree.
let parse (tokens: (Token * Loc) list): Expr<Loc> list =
  let exprs, tokens =
    match tokens with
    | [] ->
      [], []
    | (Token.Module, (_, moduleX))
      :: (Token.Ident _, _)
      :: (Token.Rec, _) :: tokens ->
      parseModule moduleX tokens
    | (Token.Module, (_, moduleX))
      :: (Token.Ident _, _) :: tokens ->
      parseModule moduleX tokens
    | _ ->
      parseModule -1 tokens
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  exprs
