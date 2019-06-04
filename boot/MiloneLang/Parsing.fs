module rec MiloneLang.Parsing

open MiloneLang
open MiloneLang.Helpers

/// Body of type definition in AST.
[<RequireQualifiedAccess>]
type ATyDef =
  | Synonym
    of ATy
  | Union
    of AVariant list

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
  | (Token.If _, _) :: _
  | (Token.Match _, _) :: _
  | (Token.Fun, _) :: _
  | (Token.Do, _) :: _
  | (Token.Let, _) :: _
  | (Token.Type, _) :: _
  | (Token.Open, _) :: _ ->
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
  let near = tokens |> List.map fst |> List.truncate 6
  failwithf "Parse error %s near %A" message near

let parseTyAtom boxX tokens: ATy * _ list =
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
let parseTySuffix boxX tokens: ATy * _ list =
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
    | (Token.Punct "*", opLoc) :: tokens when nextInside boxX tokens ->
      let second, tokens = parseTyPrefix boxX tokens
      go (second :: acc) opLoc tokens
    | _ ->
      List.rev acc, opLoc, tokens
  let first, tokens = parseTyPrefix boxX tokens
  let noLoc = (0, 0)
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

let parseTy boxX tokens: ATy * _ list =
  parseTyFun boxX tokens

/// Parse after `type .. = |`.
let parseTyDefUnion boxX tokens =
  let rec go acc tokens =
    match tokens with
    | (Token.Pipe _, _) :: tokens ->
      go acc tokens
    | (Token.Ident variantIdent, loc) :: (Token.Of, _) :: tokens ->
      let argTy, tokens = parseTy boxX tokens
      go (AVariant.T (variantIdent, Some argTy, loc) :: acc) tokens
    | (Token.Ident variantIdent, loc) :: tokens ->
      go (AVariant.T (variantIdent, None, loc) :: acc) tokens
    | _ ->
      List.rev acc, tokens
  match go [] tokens with
  | variants, tokens ->
    ATyDef.Union variants, tokens

/// Parse after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let parseTyDefBody boxX tokens =
  match tokens with
  | (Token.Pipe, _) :: tokens when nextInside boxX tokens ->
    parseTyDefUnion boxX tokens
  | (Token.Ident _, _) :: (Token.Of _, _) :: _ when nextInside boxX tokens ->
    parseTyDefUnion boxX tokens
  | _ ->
    let ty, tokens = parseTy boxX tokens
    ATyDef.Synonym ty, tokens

let parsePatList boxX tokens =
  let rec go patAcc tokens =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      List.rev patAcc, tokens
    | (Token.Punct ";", _) :: tokens ->
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
    failwith "NEVER"

let parsePatAtom boxX tokens: APat * _ list =
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
    failwith "Never"

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
      List.rev acc, tokens
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
  | head, (Token.Punct "::", loc) :: tokens ->
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

/// pat = pat-or
let parsePat boxX tokens: APat * _ list =
  if not (nextInside boxX tokens && leadsPat tokens) then
    parseError "Expected a pattern" tokens
  else
    parsePatOr boxX tokens

let parsePats boxX (tokens: _ list): APat list * _ list =
  let rec go acc tokens =
    if nextInside boxX tokens && leadsPat tokens then
      let pat, tokens = parsePat boxX tokens
      go (pat :: acc) tokens
    else
      List.rev acc, tokens
  go [] tokens

let parseList boxX bracketLoc tokens =
  match parseBindings boxX tokens with
  | exprs, (Token.BracketR, _) :: tokens ->
    AExpr.ListLit (exprs, bracketLoc), tokens
  | _, tokens ->
    parseError "Expected ']'" tokens

let parseThenCl boxX tokens =
  match tokens with
  | (Token.Then, _) as t :: tokens when nextInside boxX [t] ->
    parseExpr boxX tokens
  | _ ->
    failwithf "Expected 'then' but %A" tokens

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

  let rec go acc tokens =
    match parseMatchArm boxX tokens with
    | arm, (Token.Pipe, _) :: tokens ->
      go (arm :: acc) tokens
    | arm, tokens ->
      List.rev (arm :: acc), tokens

  let arms, tokens = go [] tokens
  AExpr.Match (target, arms, matchLoc), tokens

/// fun-expr = 'fun' pats '->' expr
let parseFun boxX funLoc tokens =
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
  let tokens = parseAccessModifier tokens
  let patsX = max boxX (letX + 1)
  let pat, tokens =
    match parsePat patsX tokens with
    | pat, (Token.Punct "=", _) :: tokens ->
      pat, tokens
    | _ ->
      parseError "Missing '='" tokens
  let body, tokens =
    let bodyX = max boxX (nextX tokens)
    parseExpr bodyX tokens
  let next, tokens =
    match tokens with
    | (Token.In, _) as inToken :: tokens when nextInside boxX [inToken] ->
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
  | (Token.Ident tyIdent, _) :: (Token.Punct "=", _) :: tokens ->
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
      identAcc |> List.rev, tokens

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

/// call = suffix ( index )*
let parseCall boxX tokens =
  let calleeLoc = nextLoc tokens
  let _, calleeX = calleeLoc
  let insideX = max boxX (calleeX + 1)
  let callee, tokens = parseSuffix boxX tokens
  let rec go acc tokens =
    if nextInside insideX tokens && leadsExpr tokens then
      let expr, tokens = parseSuffix insideX tokens
      go (AExpr.Bin (Op.App, acc, expr, calleeLoc)) tokens
    else
      acc, tokens
  go callee tokens

let parseNextLevelOp level outer tokens =
  match level with
  | OpLevel.Range -> parseOp OpLevel.Or outer tokens
  | OpLevel.Or -> parseOp OpLevel.And outer tokens
  | OpLevel.And -> parseOp OpLevel.Cmp outer tokens
  | OpLevel.Cmp -> parseOp OpLevel.Pipe outer tokens
  | OpLevel.Pipe -> parseOp OpLevel.Cons outer tokens
  | OpLevel.Cons -> parseOp OpLevel.Add outer tokens
  | OpLevel.Add -> parseOp OpLevel.Mul outer tokens
  | OpLevel.Mul -> parseCall outer tokens

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
  | OpLevel.Pipe, (Token.Punct "|>", opLoc) :: tokens ->
    next expr Op.Pipe opLoc tokens
  | OpLevel.Cons, (Token.Punct "::", opLoc) :: tokens ->
    nextR expr (Op.Cons noTy) opLoc tokens
  | OpLevel.Cons, (Token.Punct "*-", opLoc) :: tokens ->
    next expr Op.ConsRev opLoc tokens
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

/// semi = binding ( ';' binding )*
let parseSemi boxX tokens =
  match parseBindings boxX tokens with
  | [], _ ->
    failwithf "Expected an expr but %A" tokens
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
    :: (Token.Punct "=", _) :: tokens ->
    parseExpr (moduleX + 1) tokens
  | _ ->
    parseExpr boxX tokens

let parseTopLevel tokens =
  match tokens with
  | [] ->
    AExpr.TupleLit ([], (0, 0)), []
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
  if tokens <> [] then
    failwithf "Expected eof but %A" tokens
  expr
