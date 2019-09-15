/// Parses a list of tokens to build an abstract syntax tree (AST).
///
/// This is a hand-written recursive descent parser.
///
/// Caution: Not compatible with F# syntax.
///   This parser assume the source code is formatted well
///   in the layout similar to this source code.
module rec MiloneLang.Parsing

open MiloneLang
open MiloneLang.Types
open MiloneLang.Helpers

let locY (y, _) = y

/// Gets if next token exists and should lead some construction (expr/pat/ty).
/// We use this for a kind of prediction.
/// E.g. if you are looking for an expr and the following token is an integer,
/// the following tokens should start with an expression,
/// even if we don't know how many tokens participate that expr.
let tokenRole tokens: bool * bool =
  match tokens with
  | (Token.Bool _, _) :: _
  | (Token.Int _, _) :: _
  | (Token.Char _, _) :: _
  | (Token.Str _, _) :: _
  | (Token.Ident _, _) :: _
  | (Token.ParenL, _) :: _
  | (Token.BracketL, _) :: _ ->
    // It can be an expr or pat.
    true, true
  | (Token.If, _) :: _
  | (Token.Match, _) :: _
  | (Token.Fun, _) :: _
  | (Token.Do, _) :: _
  | (Token.Let, _) :: _
  | (Token.Type, _) :: _
  | (Token.Open, _) :: _
  | (Token.Minus, _) :: _ ->
    // It is an expr, not pat.
    true, false
  | _ ->
    // Other tokens are read only in specific contexts.
    false, false

let leadsExpr tokens =
  let leadsExpr, _ = tokenRole tokens
  leadsExpr

let leadsArg tokens =
  match tokens with
  | (Token.Minus, _) :: _ ->
    false

  | _ ->
    leadsExpr tokens

let leadsPat tokens =
  let _, leadsPat = tokenRole tokens
  leadsPat

/// Location of next token.
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
  let y, x = nextLoc tokens
  let near = tokens |> listMap fst |> listTruncate 6
  failwithf "Parse error %s near %A (%d:%d)" message near (y + 1) (x + 1)

let parseTyAtom boxX tokens =
  match tokens with
  | _ when nextInside boxX tokens |> not ->
    parseError "Expected a type atom" tokens
  | (Token.Ident ident, loc) :: tokens ->
    ATy.Ident (ident, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    match parseTy (nextX tokens) tokens with
    | ty, (Token.ParenR, _) :: tokens ->
      ty, tokens
    | _, tokens ->
      parseError "Expected ')'" tokens
  | _ ->
    parseError "Expected a type atom" tokens

/// ty-suffix = ty-atom ( ident )*
let parseTySuffix boxX tokens =
  let rec go first tokens =
    match tokens with
    | (Token.Ident ident, loc) :: tokens ->
      go (ATy.Suffix (first, ident, loc)) tokens
    | tokens ->
      first, tokens
  let first, tokens = parseTyAtom boxX tokens
  go first tokens

/// ty-prefix = ( ident ':' )? ty-suffix
let parseTyPrefix boxX tokens =
  match tokens with
  // NOTE: Allow 'foo:Foo' in any kind of type expressions
  // except for payload types.
  | (Token.Ident _, _) :: (Token.Colon, _) :: tokens ->
    parseTySuffix boxX tokens
  | _ ->
    parseTySuffix boxX tokens

/// ty-tuple = ty-prefix ( '\*' ty-prefix )\*
let parseTyTuple boxX tokens =
  let rec go acc opLoc tokens =
    match tokens with
    | (Token.Star, opLoc) :: tokens when nextInside boxX tokens ->
      let second, tokens = parseTyPrefix boxX tokens
      go (second :: acc) opLoc tokens
    | _ ->
      listRev acc, opLoc, tokens
  let first, tokens = parseTyPrefix boxX tokens
  match go [] noLoc tokens with
  | [], _, tokens ->
    first, tokens
  | itemTys, opLoc, tokens ->
    ATy.Tuple (first :: itemTys, opLoc), tokens

/// ty-fun = ty-tuple ( '->' ty-fun )?
let parseTyFun boxX tokens =
  match parseTyTuple boxX tokens with
  | sTy, (Token.Arrow, arrowLoc) :: tokens ->
    let tTy, tokens = parseTyFun boxX tokens
    ATy.Fun (sTy, tTy, arrowLoc), tokens
  | ty, tokens ->
    ty, tokens

let parseTy boxX tokens =
  parseTyFun boxX tokens

/// Parse after `type .. = |`.
let parseTyDefUnion boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Pipe, _) :: tokens ->
      go acc tokens
    | (Token.Ident variantIdent, loc) :: (Token.Of, _) :: tokens ->
      let payloadTy, tokens = parseTy boxX tokens
      go (AVariant.T (variantIdent, Some payloadTy, loc) :: acc) tokens
    | (Token.Ident variantIdent, loc) :: tokens ->
      go (AVariant.T (variantIdent, None, loc) :: acc) tokens
    | _ ->
      listRev acc, tokens
  match go [] tokens with
  | variants, tokens ->
    ATyDef.Union variants, tokens

/// Parse after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let parseTyDefBody boxX tokens =
  match tokens with
  | (Token.Pipe, _) :: tokens when nextInside boxX tokens ->
    parseTyDefUnion boxX tokens
  | (Token.Ident _, _) :: (Token.Of, _) :: _ when nextInside boxX tokens ->
    parseTyDefUnion boxX tokens
  | _ ->
    let ty, tokens = parseTy boxX tokens
    ATyDef.Synonym ty, tokens

let parsePatList boxX tokens =
  let rec go patAcc tokens =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      listRev patAcc, tokens
    | (Token.Semi, _) :: tokens ->
      let pat, tokens = parsePat boxX tokens
      go (pat :: patAcc) tokens
    | _ ->
      parseError "Expected ';' or ']'" tokens

  match tokens with
  | (Token.BracketL, loc) :: (Token.BracketR, _) :: tokens ->
    APat.ListLit ([], loc), tokens
  | (Token.BracketL, loc) :: tokens ->
    let pat, tokens = parsePat boxX tokens
    let pats, tokens = go [pat] tokens
    APat.ListLit (pats, loc), tokens
  | _ ->
    parseError "NEVER" tokens

let parsePatAtom boxX tokens =
  match tokens with
  | _ when not (nextInside boxX tokens && leadsPat tokens) ->
    parseError "Expected a pattern atom" tokens
  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    APat.TupleLit ([], loc), tokens
  | (Token.Bool value, loc) :: tokens ->
    APat.Lit (Lit.Bool value, loc), tokens
  | (Token.Int value, loc) :: tokens ->
    APat.Lit (Lit.Int value, loc), tokens
  | (Token.Char value, loc) :: tokens ->
    APat.Lit (Lit.Char value, loc), tokens
  | (Token.Str value, loc) :: tokens ->
    APat.Lit (Lit.Str value, loc), tokens
  | (Token.Ident ident, loc) :: tokens ->
    APat.Ident (ident, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    match parsePat (nextX tokens) tokens with
    | pat, (Token.ParenR, _) :: tokens ->
      pat, tokens
    | _, tokens ->
      parseError "Expected ')'" tokens
  | (Token.BracketL, _) :: _ ->
    parsePatList boxX tokens
  | _ ->
    parseError "NEVER" tokens

/// pat-nav = pat-atom ( '.' ident )?
let parsePatNav boxX tokens =
  let pat, tokens = parsePatAtom boxX tokens

  match tokens with
  | (Token.Dot, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.Nav (pat, ident, loc), tokens
  | (Token.Dot, _) :: tokens ->
    parseError "Expected identifier" tokens
  | _ ->
    pat, tokens

let parsePatCallArgs insideX tokens =
  let rec go acc tokens =
    if nextInside insideX tokens && leadsPat tokens then
      let expr, tokens = parsePatNav insideX tokens
      go (expr :: acc) tokens
    else
      listRev acc, tokens
  go [] tokens

/// pat-call = pat-nav ( pat-nav )*
let parsePatCall boxX tokens =
  let calleeLoc = nextLoc tokens
  let _, calleeX = calleeLoc
  let insideX = max boxX (calleeX + 1)
  let callee, tokens = parsePatNav boxX tokens
  let args, tokens = parsePatCallArgs insideX tokens
  match args with
  | [] ->
    callee, tokens
  | _ ->
    APat.Call (callee, args, calleeLoc), tokens

/// pat-cons = pat-call ( '::' pat-cons )?
let parsePatCons boxX tokens =
  match parsePatCall boxX tokens with
  | head, (Token.ColonColon, loc) :: tokens ->
    let tail, tokens = parsePatCons boxX tokens
    APat.Cons (head, tail, loc), tokens
  | pat, tokens ->
    pat, tokens

/// pat-anno = pat-cons ( ':' ty )?
let parsePatAnno boxX tokens =
  match parsePatCons boxX tokens with
  | pat, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    APat.Anno (pat, ty, loc), tokens
  | pat, tokens ->
    pat, tokens

/// pat-tuple = pat-anno ( ',' pat-anno )*
let parsePatTuple boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Comma, _) :: tokens when nextInside boxX tokens ->
      let second, tokens = parsePatAnno boxX tokens
      go (second :: acc) tokens
    | _ ->
      listRev acc, tokens
  let loc = nextLoc tokens
  let first, tokens = parsePatAnno boxX tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | itemPats, tokens ->
    APat.TupleLit (first :: itemPats, loc), tokens

/// pat-as = pat-tuple ( 'as' ident )?
let parsePatAs boxX tokens =
  match parsePatTuple boxX tokens with
  | pat, (Token.As, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.As (pat, ident, loc), tokens
  | pat, tokens ->
    pat, tokens

/// pat-or = pat ( '|' pat )*
let parsePatOr boxX tokens =
  match parsePatAs boxX tokens with
  | first, (Token.Pipe, loc) :: tokens ->
    let second, tokens = parsePatOr boxX tokens
    APat.Or (first, second, loc), tokens
  | first, tokens ->
    first, tokens

/// pat-let = pat-fun / pat
/// pat-fun = ident pat-nav+ ( ':' ty )?
let parsePatLet boxX tokens =
  match tokens with
  | (Token.Ident callee, loc) :: nextTokens
    when nextInside boxX tokens && nextInside boxX nextTokens && leadsPat nextTokens ->
    let args, tokens = parsePatCallArgs boxX nextTokens
    let pat = APat.Fun (callee, args, loc)

    match tokens with
    | (Token.Colon, loc) :: tokens ->
      let ty, tokens = parseTy boxX tokens
      APat.Anno (pat, ty, loc), tokens

    | _ ->
      pat, tokens

  | _ ->
    parsePat boxX tokens

/// pat = pat-or
let parsePat boxX tokens =
  if not (nextInside boxX tokens && leadsPat tokens) then
    parseError "Expected a pattern" tokens
  else
    parsePatOr boxX tokens

let parsePats boxX tokens =
  let rec go acc tokens =
    if nextInside boxX tokens && leadsPat tokens then
      let pat, tokens = parsePat boxX tokens
      go (pat :: acc) tokens
    else
      listRev acc, tokens
  go [] tokens

let parseList boxX bracketLoc tokens =
  match parseBindings boxX tokens with
  | exprs, (Token.BracketR, _) :: tokens ->
    AExpr.ListLit (exprs, bracketLoc), tokens
  | _, tokens ->
    parseError "Expected ']'" tokens

let parseThenCl boxX tokens =
  match tokens with
  | ((Token.Then, _) as t) :: tokens when nextInside boxX [t] ->
    parseExpr boxX tokens
  | _ ->
    parseError "Expected 'then'" tokens

let parseElseCl boxX ifLoc tokens =
  let nextInside = nextInside boxX tokens
  match tokens with
  | (Token.Else, elseLoc) :: (Token.If, ifLoc) :: tokens
    when nextInside && (locY elseLoc = locY ifLoc) ->
    // HACK: Parse next expr as if the `if` in `else if` is placed where `else` is.
    parseExpr1 boxX ((Token.If, elseLoc) :: tokens)
  | (Token.Else, _) :: tokens when nextInside ->
    parseExpr (nextX tokens) tokens
  | _ ->
    // Append `else ()` if missing.
    AExpr.Missing ifLoc, tokens

/// You can align contents on the same column as if/then/else.
let parseIf boxX ifLoc tokens =
  let cond, tokens = parseExpr boxX tokens
  let body, tokens = parseThenCl boxX tokens
  let alt, tokens = parseElseCl boxX ifLoc tokens
  AExpr.If (cond, body, alt, ifLoc), tokens

let parseMatchArm boxX tokens =
  let loc = nextLoc tokens
  let tokens =
    match tokens with
    | (Token.Pipe, _) :: tokens -> tokens
    | _ -> tokens
  let pat, guard, tokens =
    match parsePat boxX tokens with
    | pat, (Token.When, _) :: tokens ->
      let guard, tokens = parseExpr1 boxX tokens
      pat, guard, tokens
    | pat, tokens ->
      let guard = AExpr.Missing (nextLoc tokens)
      pat, guard, tokens
  let body, tokens =
    match tokens with
    | (Token.Arrow, _) :: tokens ->
      parseExpr boxX tokens
    | _ ->
      parseError "Expected '->'" tokens
  AArm.T (pat, guard, body, loc), tokens

let parseMatch boxX matchLoc tokens =
  let target, tokens =
    match parseExpr boxX tokens with
    | expr, (Token.With, _) :: tokens ->
      expr, tokens
    | _, tokens ->
      parseError "Expected 'with'" tokens

  let pipeX = nextX tokens

  let rec go acc tokens =
    match parseMatchArm boxX tokens with
    | arm, (Token.Pipe, (_, x)) :: tokens when x = pipeX ->
      go (arm :: acc) tokens
    | arm, tokens ->
      listRev (arm :: acc), tokens

  let arms, tokens = go [] tokens
  AExpr.Match (target, arms, matchLoc), tokens

/// fun-expr = 'fun' pats '->' expr
let parseFun _boxX funLoc tokens =
  let _, funX = funLoc
  let patBoxX = funX + 1
  let pats, tokens =
    match parsePatCallArgs patBoxX tokens with
    | pats, (Token.Arrow, _) :: tokens ->
      pats, tokens
    | _ ->
      parseError "Missing '->'" tokens
  let body, tokens =
    let bodyX = nextX tokens
    parseExpr bodyX tokens
  AExpr.Fun (pats, body, funLoc), tokens

let parseParen boxX tokens =
  match parseExpr boxX tokens with
  | expr, (Token.ParenR, _) :: tokens ->
    expr, tokens
  | _ ->
    parseError "Expected ')'" tokens

let parseAccessModifier tokens =
  match tokens with
  | ((Token.Private | Token.Internal | Token.Public), _) :: tokens ->
    // FIXME: support access modifiers
    tokens
  | _ ->
    tokens

let parseLet boxX letLoc tokens =
  let _, letX = letLoc
  let tokens = parseAccessModifier tokens
  let patsX = max boxX (letX + 1)
  let pat, tokens =
    match parsePatLet patsX tokens with
    | pat, (Token.Eq, _) :: tokens ->
      pat, tokens
    | _ ->
      parseError "Missing '='" tokens
  let body, tokens =
    let bodyX = max boxX (nextX tokens)
    parseExpr bodyX tokens
  let next, tokens =
    match tokens with
    | ((Token.In, _) as inToken) :: tokens when nextInside boxX [inToken] ->
      parseExpr (letX + 1) tokens
    | _ :: _ when nextX tokens = letX ->
      // To omit `in`, the clause must be on the same column as `let`.
      parseExpr boxX tokens
    | tokens ->
      AExpr.TupleLit ([], letLoc), tokens
  AExpr.Let (pat, body, next, letLoc), tokens

let parseTyDef boxX keywordLoc tokens =
  let _, keywordX = keywordLoc
  let tokens = parseAccessModifier tokens
  match tokens with
  | _ when not (nextInside boxX tokens) ->
    parseError "Expected type name" tokens
  | (Token.Ident tyIdent, _) :: (Token.Eq, _) :: tokens ->
    match parseTyDefBody (keywordX + 1) tokens with
    | ATyDef.Synonym ty, tokens ->
      AExpr.TySynonym (tyIdent, ty, keywordLoc), tokens
    | ATyDef.Union variants, tokens ->
      AExpr.TyUnion (tyIdent, variants, keywordLoc), tokens
  | tokens ->
    parseError "Expected '='" tokens

/// open = 'open' ident ( '.' ident )*
let parseBindingOpen _boxX keywordLoc tokens =
  let rec go identAcc tokens =
    match tokens with
    | (Token.Dot, _) :: (Token.Ident secondIdent, _) :: tokens ->
      go (secondIdent :: identAcc) tokens
    | (Token.Dot, _) :: tokens ->
      parseError "Expected identifier" tokens
    | _ ->
      identAcc |> listRev, tokens

  match tokens with
  | (Token.Ident ident, _) :: tokens ->
    let path, tokens = go [ident] tokens
    AExpr.Open (path, keywordLoc), tokens
  | _ ->
    parseError "Expected identifier" tokens

/// atom  = unit / int / char /string / bool / prim / ref
///       / ( expr ) / if-then-else / match-with / let
let parseAtom boxX tokens: AExpr * (Token * Loc) list =
  match tokens with
  | _ when not (nextInside boxX tokens) ->
    parseError "Expected an atomic expression" tokens
  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    AExpr.TupleLit ([], loc), tokens
  | (Token.Bool value, loc) :: tokens ->
    AExpr.Lit (Lit.Bool value, loc), tokens
  | (Token.Int value, loc) :: tokens ->
    AExpr.Lit (Lit.Int value, loc), tokens
  | (Token.Char value, loc) :: tokens ->
    AExpr.Lit (Lit.Char value, loc), tokens
  | (Token.Str value, loc) :: tokens ->
    AExpr.Lit (Lit.Str value, loc), tokens
  | (Token.Ident ident, loc) :: tokens ->
    AExpr.Ident (ident, loc), tokens
  | (Token.ParenL, _) :: tokens ->
    parseParen boxX tokens
  | (Token.BracketL, bracketLoc) :: tokens ->
    parseList boxX bracketLoc tokens
  | (Token.If, loc) :: tokens ->
    parseIf boxX loc tokens
  | (Token.Match, loc) :: tokens ->
    parseMatch boxX loc tokens
  | (Token.Fun, loc) :: tokens ->
    parseFun boxX loc tokens
  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc tokens
  | _ ->
    parseError "Expected an atomic expression" tokens

/// suffix = atom ( '.' '[' expr ']' | '.' ident )*
let parseSuffix boxX tokens =
  let callee, tokens = parseAtom boxX tokens
  let rec go acc tokens =
    match tokens with
    | (Token.Dot, loc) :: (Token.BracketL, _) :: tokens ->
      match parseExpr boxX tokens with
      | expr, (Token.BracketR, _) :: tokens ->
        go (AExpr.Index (acc, expr, loc)) tokens
      | _, tokens ->
        parseError "Expected closing ']'" tokens
    | (Token.Dot, loc) :: (Token.Ident mem, _) :: tokens ->
      go (AExpr.Nav (acc, mem, loc)) tokens
    | (Token.Dot, _) :: tokens ->
      parseError "Expected .[] or .member" tokens
    | _ ->
      acc, tokens
  go callee tokens

/// call = suffix ( suffix )*
let parseCall boxX tokens =
  let calleeLoc = nextLoc tokens
  let _, calleeX = calleeLoc
  let insideX = max boxX (calleeX + 1)
  let callee, tokens = parseSuffix boxX tokens
  let rec go acc tokens =
    if nextInside insideX tokens && leadsArg tokens then
      let expr, tokens = parseSuffix insideX tokens
      go (AExpr.Bin (Op.App, acc, expr, calleeLoc)) tokens
    else
      acc, tokens
  go callee tokens

/// prefix = '-'? call
let parsePrefix boxX tokens =
  match tokens with
  | (Token.Minus, loc) :: tokens ->
    let arg, tokens = parseCall boxX tokens
    AExpr.Uni (UniOp.Neg, arg, loc), tokens

  | _ ->
    parseCall boxX tokens

let parseNextLevelOp level outer tokens =
  match level with
  | OpLevel.Or -> parseOp OpLevel.And outer tokens
  | OpLevel.And -> parseOp OpLevel.Cmp outer tokens
  | OpLevel.Cmp -> parseOp OpLevel.Pipe outer tokens
  | OpLevel.Pipe -> parseOp OpLevel.Cons outer tokens
  | OpLevel.Cons -> parseOp OpLevel.Add outer tokens
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parsePrefix outer tokens

let rec parseOps level boxX expr tokens =
  let next expr op opLoc tokens =
    let second, tokens = parseNextLevelOp level boxX tokens
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level boxX expr tokens
  let nextR expr op opLoc tokens =
    let second, tokens = parseOp level boxX tokens
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level boxX expr tokens
  match level, tokens with
  | OpLevel.Or, (Token.PipePipe, opLoc) :: tokens ->
    next expr Op.Or opLoc tokens
  | OpLevel.And, (Token.AmpAmp, opLoc) :: tokens ->
    next expr Op.And opLoc tokens
  | OpLevel.Cmp, (Token.Eq, opLoc) :: tokens ->
    next expr Op.Eq opLoc tokens
  | OpLevel.Cmp, (Token.LtGt, opLoc) :: tokens ->
    next expr Op.Ne opLoc tokens
  | OpLevel.Cmp, (Token.Lt, opLoc) :: tokens ->
    next expr Op.Lt opLoc tokens
  | OpLevel.Cmp, (Token.LtEq, opLoc) :: tokens ->
    next expr Op.Le opLoc tokens
  | OpLevel.Cmp, (Token.Gt, opLoc) :: tokens ->
    next expr Op.Gt opLoc tokens
  | OpLevel.Cmp, (Token.GtEq, opLoc) :: tokens ->
    next expr Op.Ge opLoc tokens
  | OpLevel.Pipe, (Token.PipeGt, opLoc) :: tokens ->
    next expr Op.Pipe opLoc tokens
  | OpLevel.Cons, (Token.ColonColon, opLoc) :: tokens ->
    nextR expr Op.Cons opLoc tokens
  | OpLevel.Add, (Token.Plus, opLoc) :: tokens ->
    next expr Op.Add opLoc tokens
  | OpLevel.Add, (Token.Minus, opLoc) :: tokens ->
    next expr Op.Sub opLoc tokens
  | OpLevel.Mul, (Token.Star, opLoc) :: tokens ->
    next expr Op.Mul opLoc tokens
  | OpLevel.Mul, (Token.Slash, opLoc) :: tokens ->
    next expr Op.Div opLoc tokens
  | OpLevel.Mul, (Token.Percent, opLoc) :: tokens ->
    next expr Op.Mod opLoc tokens
  | _ ->
    expr, tokens

/// E.g. add = mul ( ('+'|'-') mul )*
let parseOp level boxX tokens =
  let first, tokens = parseNextLevelOp level boxX tokens
  parseOps level boxX first tokens

let parseTerm boxX tokens =
  parseOp OpLevel.Or boxX tokens

/// tuple = term ( ',' term )*
let parseTuple boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Comma, _) :: tokens when nextInside boxX tokens ->
      let second, tokens = parseTerm boxX tokens
      go (second :: acc) tokens
    | tokens ->
      listRev acc, tokens
  let loc = nextLoc tokens
  let first, tokens = parseTerm boxX tokens
  match go [] tokens with
  | [], tokens ->
    first, tokens
  | acc, tokens ->
    AExpr.TupleLit (first :: acc, loc), tokens

/// anno = tuple ( ':' ty )?
let parseAnno boxX tokens =
  match parseTuple boxX tokens with
  | expr, (Token.Colon, loc) :: tokens ->
    let ty, tokens = parseTy (nextX tokens) tokens
    AExpr.Anno (expr, ty, loc), tokens
  | expr, tokens ->
    expr, tokens

let parseExpr1 boxX tokens =
  parseAnno boxX tokens

let parseBinding boxX tokens =
  match tokens with
  | (Token.Let, letLoc) :: (Token.Rec, _) :: tokens ->
    // FIXME: use `rec`
    parseLet boxX letLoc tokens
  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc tokens
  | (Token.Type, keywordLoc) :: tokens ->
    parseTyDef boxX keywordLoc tokens
  | (Token.Open, keywordLoc) :: tokens ->
    parseBindingOpen boxX keywordLoc tokens
  | _ ->
    parseExpr1 boxX tokens

/// All expressions must be aligned on the same column,
/// except it is preceded by semicolon.
let rec parseBindings boxX tokens =
  let rec go acc alignX tokens =
    match tokens with
    | (Token.Semi, _) :: tokens
      when nextX tokens >= alignX ->
      let expr, tokens = parseBinding boxX tokens
      go (expr :: acc) alignX tokens
    | tokens
      when nextX tokens = alignX && leadsExpr tokens ->
      let expr, tokens = parseBinding boxX tokens
      go (expr :: acc) alignX tokens
    | _ ->
      listRev acc, tokens
  go [] (nextX tokens) tokens

/// semi = binding ( ';' binding )*
let parseSemi boxX tokens =
  match parseBindings boxX tokens with
  | [], _ ->
    parseError "Expected an expr" tokens
  | [expr], tokens ->
    expr, tokens
  | exprs, tokens ->
    AExpr.Semi (exprs, nextLoc tokens), tokens

let parseExpr (boxX: int) (tokens: (Token * Loc) list): AExpr * (Token * Loc) list =
  parseSemi boxX tokens

/// module = 'module' identifier = ..
/// FIXME: stub
let parseModule (boxX: int) tokens =
  match tokens with
  | (Token.Module, (_, moduleX))
    :: (Token.Ident _, _)
    :: (Token.Eq, _) :: tokens ->
    parseExpr (moduleX + 1) tokens
  | _ ->
    parseExpr boxX tokens

let parseTopLevel tokens =
  match tokens with
  | [] ->
    AExpr.TupleLit ([], noLoc), []
  | (Token.Module, (_, moduleX))
    :: (Token.Rec, _)
    :: (Token.Ident _, _)
    :: (Token.Dot, _)
    :: (Token.Ident _, _) :: tokens ->
    parseModule moduleX tokens
  | (Token.Module, (_, moduleX))
    :: (Token.Rec, _)
    :: (Token.Ident _, _) :: tokens ->
    parseModule moduleX tokens
  | (Token.Module, (_, moduleX))
    :: (Token.Ident _, _) :: tokens ->
    parseModule moduleX tokens
  | _ ->
    parseModule 0 tokens

/// module = ( 'module' 'rec'? ident bindings / bindings )?
let parse (tokens: (Token * Loc) list): AExpr =
  let expr, tokens = parseTopLevel tokens
  if tokens |> listIsEmpty |> not then
    parseError "Expected eof" tokens
  expr
