/// Parses a list of tokens to build an abstract syntax tree (AST).
///
/// This is a hand-written recursive descent parser.
///
/// Caution: Not compatible with F# syntax.
///   This parser assume the source code is formatted well
///   in the layout similar to this source code.
module rec MiloneLang.Parsing

open MiloneLang.Types
open MiloneLang.Helpers

let locX ((_, x): Loc) = x

let locY ((y, _): Loc) = y

let locIsSameColumn ((_, firstX): Loc) ((_, secondX): Loc) =
  firstX = secondX

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

let parseErrorCore msg loc tokens errors =
  let near = tokens |> listMap fst |> listTruncate 6
  let msg = sprintf "Parse error %s near %A" msg near
  (msg, loc) :: errors

let parseTyError msg (tokens, errors) =
  let loc = nextLoc tokens
  let errors = parseErrorCore msg loc tokens errors
  ATy.Missing loc, tokens, errors

let parsePatError msg (tokens, errors) =
  let loc = nextLoc tokens
  let errors = parseErrorCore msg loc tokens errors
  APat.Missing loc, tokens, errors

let parseExprError msg (tokens, errors) =
  let loc = nextLoc tokens
  let errors = parseErrorCore msg loc tokens errors
  AExpr.Missing loc, tokens, errors

let parseNewError msg (tokens, errors) =
  let loc = nextLoc tokens
  parseErrorCore msg loc tokens errors

// -----------------------------------------------
// Parse Ty
// -----------------------------------------------

let parseTyAtom boxX (tokens, errors) =
  match tokens with
  | _ when nextInside boxX tokens |> not ->
    parseTyError "Expected a type atom" (tokens, errors)

  | (Token.Ident ident, loc) :: tokens ->
    ATy.Ident (ident, loc), tokens, errors

  | (Token.ParenL, _) :: tokens ->
    let ty, tokens, errors = parseTy (nextX tokens) (tokens, errors)

    match tokens with
    | (Token.ParenR, _) :: tokens ->
      ty, tokens, errors

    | _ ->
      let errors = parseNewError "Expected ')'" (tokens, errors)
      ty, tokens, errors

  | _ ->
    parseTyError "Expected a type atom" (tokens, errors)

/// `ty-suffix = ty-atom ( ident )*`
let parseTySuffix boxX (tokens, errors) =
  let rec go (ty, tokens, errors) =
    let inside = nextInside boxX tokens
    match tokens with
    | (Token.Ident ident, loc) :: tokens when inside ->
      go (ATy.Suffix (ty, ident, loc), tokens, errors)

    | _ ->
      ty, tokens, errors

  parseTyAtom boxX (tokens, errors) |> go

/// `ty-prefix = ( ident ':' )? ty-suffix`
/// FIXME: `foo:Foo` is only allowed in payload types.
let parseTyPrefix boxX (tokens, errors) =
  match tokens with
  | (Token.Ident _, _) :: (Token.Colon, _) :: tokens ->
    parseTySuffix boxX (tokens, errors)

  | _ ->
    parseTySuffix boxX (tokens, errors)

/// `ty-tuple = ty-prefix ( '*' ty-prefix )*`
let parseTyTuple boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Star, _) :: tokens ->
      let itemTy, tokens, errors = parseTyPrefix boxX (tokens, errors)
      go (itemTy :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let itemTy, tokens, errors = parseTyPrefix boxX (tokens, errors)

  match tokens with
  | (Token.Star, opLoc) :: _ ->
    let itemTys, tokens, errors = go [] (tokens, errors)
    ATy.Tuple (itemTy :: itemTys, opLoc), tokens, errors

  | _ ->
    itemTy, tokens, errors

/// `ty-fun = ty-tuple ( '->' ty-fun )?`
/// FIXME: Support chain of arrows
let parseTyFun boxX (tokens, errors) =
  let sTy, tokens, errors = parseTyTuple boxX (tokens, errors)

  match tokens with
  | (Token.Arrow, opLoc) :: tokens ->
    let tTy, tokens, errors = parseTyFun boxX (tokens, errors)
    ATy.Fun (sTy, tTy, opLoc), tokens, errors

  | _ ->
    sTy, tokens, errors

let parseTy boxX (tokens, errors) =
  parseTyFun boxX (tokens, errors)

/// Parse the body of union `type` declaration.
let parseTyDeclUnion boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Pipe, _)
      :: (Token.Ident variantIdent, loc)
      :: (Token.Of, _) :: tokens ->
      let payloadTy, tokens, errors = parseTy boxX (tokens, errors)
      go (AVariant (variantIdent, Some payloadTy, loc) :: acc) (tokens, errors)

    | (Token.Pipe, _)
      :: (Token.Ident variantIdent, loc) :: tokens ->
      go (AVariant (variantIdent, None, loc) :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let variants, tokens, errors = go [] (tokens, errors)
  ATyDecl.Union variants, tokens, errors

/// Parse after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let parseTyDeclBody boxX (tokens, errors) =
  match tokens with
  | (Token.Pipe, _) :: _ ->
    parseTyDeclUnion boxX (tokens, errors)

  | (Token.Ident _, _) :: (Token.Of, _) :: _ ->
    parseTyDeclUnion boxX (tokens, errors)

  | _ ->
    let ty, tokens, errors = parseTy boxX (tokens, errors)
    ATyDecl.Synonym ty, tokens, errors

/// `pat ')'`
let parsePatParenBody (tokens, errors) =
  let pat, tokens, errors = parsePat (nextX tokens) (tokens, errors)

  match tokens with
  | (Token.ParenR, _) :: tokens ->
    pat, tokens, errors

  | tokens ->
    let errors = parseNewError "Expected ')'" (tokens, errors)
    pat, tokens, errors

/// `pat ( ';' pat )* ']'`
let parsePatListBody loc boxX (tokens, errors) =
  let rec go patAcc (tokens, errors) =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      listRev patAcc, tokens, errors

    // FIXME: Semicolon is required for now.
    | (Token.Semi, _) :: tokens ->
      let pat, tokens, errors = parsePat boxX (tokens, errors)
      go (pat :: patAcc) (tokens, errors)

    | _ ->
      let errors = parseNewError "Expected ';' or ']'" (tokens, errors)
      listRev patAcc, tokens, errors

  let itemPat, tokens, errors = parsePat boxX (tokens, errors)
  let itemPats, tokens, errors = go [itemPat] (tokens, errors)
  APat.ListLit (itemPats, loc), tokens, errors

let parsePatAtom boxX (tokens, errors) =
  match tokens with
  | _ when not (nextInside boxX tokens && leadsPat tokens) ->
    parsePatError "Expected a pattern atom" (tokens, errors)

  | (Token.Bool value, loc) :: tokens ->
    APat.Lit (Lit.Bool value, loc), tokens, errors

  | (Token.Int value, loc) :: tokens ->
    APat.Lit (Lit.Int value, loc), tokens, errors

  | (Token.Char value, loc) :: tokens ->
    APat.Lit (Lit.Char value, loc), tokens, errors

  | (Token.Str value, loc) :: tokens ->
    APat.Lit (Lit.Str value, loc), tokens, errors

  | (Token.Ident ident, loc) :: tokens ->
    APat.Ident (ident, loc), tokens, errors

  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    APat.TupleLit ([], loc), tokens, errors

  | (Token.ParenL, _) :: tokens ->
    parsePatParenBody (tokens, errors)

  | (Token.BracketL, loc) :: (Token.BracketR, _) :: tokens ->
    APat.ListLit ([], loc), tokens, errors

  | (Token.BracketL, loc) :: tokens ->
    parsePatListBody loc boxX (tokens, errors)

  | _ ->
    parsePatError "NEVER: The token must be a pat" (tokens, errors)

/// `pat-nav = pat-atom ( '.' ident )?`
let parsePatNav boxX (tokens, errors) =
  let pat, tokens, errors = parsePatAtom boxX (tokens, errors)

  match tokens with
  | (Token.Dot, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.Nav (pat, ident, loc), tokens, errors

  | (Token.Dot, _) :: tokens ->
    parsePatError "Expected identifier" (tokens, errors)

  | _ ->
    pat, tokens, errors

let parsePatCallArgs boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    if nextInside boxX tokens && leadsPat tokens then
      let expr, tokens, errors = parsePatNav boxX (tokens, errors)
      go (expr :: acc) (tokens, errors)
    else
      listRev acc, tokens, errors

  go [] (tokens, errors)

/// `pat-call = pat-nav ( pat-nav )*`
let parsePatCall boxX (tokens, errors) =
  let calleeLoc = nextLoc tokens
  let insideX = max boxX (locX calleeLoc + 1)

  let callee, tokens, errors = parsePatNav boxX (tokens, errors)
  let args, tokens, errors = parsePatCallArgs insideX (tokens, errors)

  match args with
  | [] ->
    callee, tokens, errors

  | _ ->
    APat.Call (callee, args, calleeLoc), tokens, errors

/// `pat-cons = pat-call ( '::' pat-cons )?`
let parsePatCons boxX (tokens, errors) =
  let head, tokens, errors = parsePatCall boxX (tokens, errors)

  match tokens with
  | (Token.ColonColon, loc) :: tokens ->
    let tail, tokens, errors = parsePatCons boxX (tokens, errors)
    APat.Cons (head, tail, loc), tokens, errors

  | _ ->
    head, tokens, errors

/// `pat-anno = pat-cons ( ':' ty )?`
let parsePatAnno boxX (tokens, errors) =
  let pat, tokens, errors = parsePatCons boxX (tokens, errors)

  match tokens with
  | (Token.Colon, loc) :: tokens ->
    let ty, tokens, errors = parseTy (nextX tokens) (tokens, errors)
    APat.Anno (pat, ty, loc), tokens, errors

  | _ ->
    pat, tokens, errors

/// `pat-tuple = pat-anno ( ',' pat-anno )*`
let parsePatTuple boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Comma, _) :: tokens ->
      let second, tokens, errors = parsePatAnno boxX (tokens, errors)
      go (second :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let itemPat, tokens, errors = parsePatAnno boxX (tokens, errors)

  match tokens with
  | (Token.Comma, loc) :: _ ->
    let itemPats, tokens, errors = go [] (tokens, errors)
    APat.TupleLit (itemPat :: itemPats, loc), tokens, errors

  | _ ->
    itemPat, tokens, errors

/// `pat-as = pat-tuple ( 'as' ident )?`
/// NOTE: The syntax of `as` patterns is more flexible in F#.
let parsePatAs boxX (tokens, errors) =
  let pat, tokens, errors = parsePatTuple boxX (tokens, errors)

  match tokens with
  | (Token.As, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.As (pat, ident, loc), tokens, errors

  | (Token.As, _) :: tokens ->
    let errors =  parseNewError "Expected an identifier" (tokens, errors)
    pat, tokens, errors

  | _ ->
    pat, tokens, errors

/// `pat-or = pat ( '|' pat-or )?`
let parsePatOr boxX (tokens, errors) =
  let lPat, tokens, errors = parsePatAs boxX (tokens, errors)

  match tokens with
  | (Token.Pipe, loc) :: tokens ->
    let rPat, tokens, errors = parsePatOr boxX (tokens, errors)
    APat.Or (lPat, rPat, loc), tokens, errors

  | _ ->
    lPat, tokens, errors

/// Parse a pattern of let expressions.
/// `pat-fun = ident pat-nav+ ( ':' ty )?`
/// `pat-let = pat-fun / pat`
let parsePatLet boxX (tokens, errors) =
  match tokens with
  | (Token.Ident callee, loc) :: nextTokens
    when nextInside boxX tokens
      && nextInside boxX nextTokens
      && leadsPat nextTokens ->
    let args, tokens, errors = parsePatCallArgs boxX (nextTokens, errors)
    let pat = APat.Fun (callee, args, loc)

    match tokens with
    | (Token.Colon, loc) :: tokens ->
      let ty, tokens, errors = parseTy boxX (tokens, errors)
      APat.Anno (pat, ty, loc), tokens, errors

    | _ ->
      pat, tokens, errors

  | _ ->
    parsePat boxX (tokens, errors)

/// `pat = pat-or`
let parsePat boxX (tokens, errors) =
  if not (nextInside boxX tokens && leadsPat tokens) then
    parsePatError "Expected a pattern" (tokens, errors)
  else
    parsePatOr boxX (tokens, errors)

let parsePats boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    if nextInside boxX tokens && leadsPat tokens then
      let pat, tokens, errors = parsePat boxX (tokens, errors)
      go (pat :: acc) (tokens, errors)
    else
      listRev acc, tokens, errors

  go [] (tokens, errors)

/// `range = term ( '..' term )?`
let parseRange boxX (tokens, errors) =
  let l, tokens, errors = parseTerm boxX (tokens, errors)

  match tokens with
  | (Token.DotDot, loc) :: tokens ->
    let r, tokens, errors = parseTerm boxX (tokens, errors)
    AExpr.Range ([l; r], loc), tokens, errors

  | _ ->
    l, tokens, errors

let parseList boxX bracketLoc (tokens, errors) =
  let items, tokens, errors = parseBindings boxX (tokens, errors)

  let tokens, errors =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      tokens, errors

    | _ ->
      let errors = parseNewError "Expected ']'" (tokens, errors)
      tokens, errors

  AExpr.ListLit (items, bracketLoc), tokens, errors

let parseThenCl boxX (tokens, errors) =
  let inside = nextInside boxX tokens
  match tokens with
  | (Token.Then, _) :: tokens when inside ->
    parseExpr boxX (tokens, errors)

  | _ ->
    parseExprError "Expected 'then'" (tokens, errors)

let parseElseCl boxX ifLoc (tokens, errors) =
  let inside = nextInside boxX tokens
  match tokens with
  | (Token.Else, elseLoc) :: (Token.If, ifLoc) :: tokens
    when inside && (locY elseLoc = locY ifLoc) ->
    // HACK: Parse next expr as if the `if` in `else if` is placed where `else` is.
    parseExpr1 boxX ((Token.If, elseLoc) :: tokens, errors)

  | (Token.Else, _) :: tokens when inside ->
    parseExpr (nextX tokens) (tokens, errors)

  | _ ->
    AExpr.Missing ifLoc, tokens, errors

/// You can align contents on the same column as if/then/else.
let parseIf boxX ifLoc (tokens, errors) =
  let cond, tokens, errors = parseExpr boxX (tokens, errors)
  let body, tokens, errors = parseThenCl boxX (tokens, errors)
  let alt, tokens, errors = parseElseCl boxX ifLoc (tokens, errors)
  AExpr.If (cond, body, alt, ifLoc), tokens, errors

/// `pat ( 'when' expr )? -> expr`
let parseMatchArm armLoc boxX (tokens, errors) =
  let pat, tokens, errors = parsePat boxX (tokens, errors)

  let guard, tokens, errors =
    match tokens with
    | (Token.When, _) :: tokens ->
      parseExpr1 boxX (tokens, errors)

    | _ ->
      let guard = AExpr.Missing (nextLoc tokens)
      guard, tokens, errors

  let body, tokens, errors =
    match tokens with
    | (Token.Arrow, _) :: tokens ->
      parseExpr boxX (tokens, errors)

    | _ ->
      parseExprError "Expected '->'" (tokens, errors)

  AArm (pat, guard, body, armLoc), tokens, errors

let parseMatch boxX matchLoc (tokens, errors) =
  let target, tokens, errors = parseExpr boxX (tokens, errors)

  let armLoc, tokens, errors =
    match tokens with
    | (Token.With, _) :: (Token.Pipe, pipeLoc) :: tokens ->
      pipeLoc, tokens, errors

    | (Token.With, withLoc) :: tokens ->
      withLoc, tokens, errors

    | _ ->
      let errors = parseNewError "Expected 'with'" (tokens, errors)
      matchLoc, tokens, errors

  let rec go acc armLoc (tokens, errors) =
    let arm, tokens, errors = parseMatchArm armLoc boxX (tokens, errors)

    let inside = nextInside (locX matchLoc) tokens

    match tokens with
    | (Token.Pipe, pipeLoc) :: tokens when inside ->
      go (arm :: acc) pipeLoc (tokens, errors)

    | _ ->
      listRev (arm :: acc), tokens, errors

  let arms, tokens, errors = go [] armLoc (tokens, errors)
  AExpr.Match (target, arms, matchLoc), tokens, errors

/// `fun-expr = 'fun' pat* '->' expr`
let parseFun _boxX funLoc (tokens, errors) =
  let patBoxX = locX funLoc + 1
  let pats, tokens, errors = parsePatCallArgs patBoxX (tokens, errors)

  let tokens, errors =
    match tokens with
    | (Token.Arrow, _) :: tokens ->
      tokens, errors

    | _ ->
      let errors = parseNewError "Missing '->'" (tokens, errors)
      tokens, errors

  let body, tokens, errors =
    let bodyX = nextX tokens
    parseExpr bodyX (tokens, errors)

  AExpr.Fun (pats, body, funLoc), tokens, errors

let parseParenBody boxX (tokens, errors) =
  let body, tokens, errors = parseExpr boxX (tokens, errors)

  match tokens with
  | (Token.ParenR, _) :: tokens ->
    body, tokens, errors

  | _ ->
    let errors = parseNewError "Expected ')'" (tokens, errors)
    body, tokens, errors

let tokenIsAccessModifier token =
  match token with
  | Token.Private
  | Token.Internal
  | Token.Public ->
    true

  | _ ->
    false

let parseAccessModifier tokens =
  match tokens with
  | (t, _) :: tokens when t |> tokenIsAccessModifier ->
    // FIXME: Support access modifiers.
    tokens

  | _ ->
    tokens

let parseLet boxX letLoc (tokens, errors) =
  let expectEq (tokens, errors) =
    match tokens with
    | (Token.Eq, _) :: tokens ->
      tokens, errors

    | _ ->
      let errors = parseNewError "Missing '='" (tokens, errors)
      tokens, errors

  let insideX = max boxX (locX letLoc + 1)

  let tokens = parseAccessModifier tokens

  let pat, tokens, errors = parsePatLet insideX (tokens, errors)
  let tokens, errors = expectEq (tokens, errors)

  let body, tokens, errors =
    let bodyX = max boxX (nextX tokens)
    parseExpr bodyX (tokens, errors)

  let next, tokens, errors =
    let inside = nextInside boxX tokens

    match tokens with
    | (Token.In, _) :: tokens when inside ->
      parseExpr insideX (tokens, errors)

    | _ :: _ when locIsSameColumn (nextLoc tokens) letLoc ->
      // To omit `in`, the in-clause must be on the same column as `let`.
      parseExpr boxX (tokens, errors)

    | tokens ->
      AExpr.TupleLit ([], letLoc), tokens, errors

  AExpr.Let (pat, body, next, letLoc), tokens, errors

let parseTyDecl boxX typeLoc (tokens, errors) =
  let bodyBoxX = max boxX (locX typeLoc + 1)

  let tokens = parseAccessModifier tokens

  match tokens with
  | (Token.Ident tyIdent, _) :: tokens ->
    let tokens, errors =
      match tokens with
      | (Token.Eq, _) :: tokens ->
        tokens, errors

      | _ ->
        let errors = parseNewError "Expected '='" (tokens, errors)
        tokens, errors

    let tyDecl, tokens, errors = parseTyDeclBody bodyBoxX (tokens, errors)

    let expr =
      match tyDecl with
      | ATyDecl.Synonym ty ->
        AExpr.TySynonym (tyIdent, ty, typeLoc)

      | ATyDecl.Union variants ->
        AExpr.TyUnion (tyIdent, variants, typeLoc)

    expr, tokens, errors

  | _ ->
    parseExprError "Expected identifier" (tokens, errors)

/// `open = 'open' ident ( '.' ident )*`
let parseBindingOpen _boxX openLoc (tokens, errors) =
  let parsePath (tokens, errors) =
    let rec go acc (tokens, errors) =
      match tokens with
      | (Token.Dot, _) :: (Token.Ident ident, _) :: tokens ->
        go (ident :: acc) (tokens, errors)

      | (Token.Dot, _) :: tokens ->
        let errors = parseNewError "Expected identifier" (tokens, errors)
        listRev acc, tokens, errors

      | _ ->
        listRev acc, tokens, errors

    match tokens with
    | (Token.Ident ident, _) :: tokens ->
      go [ident] (tokens, errors)

    | _ ->
      let errors = parseNewError "Expected identifier" (tokens, errors)
      [], tokens, errors

  let path, tokens, errors = parsePath (tokens, errors)
  AExpr.Open (path, openLoc), tokens, errors

let parseAtom boxX (tokens, errors) =
  match tokens with
  | _ when not (nextInside boxX tokens) ->
    parseExprError "Expected an expression" (tokens, errors)

  | (Token.ParenL, loc) :: (Token.ParenR, _) :: tokens ->
    AExpr.TupleLit ([], loc), tokens, errors

  | (Token.Bool value, loc) :: tokens ->
    AExpr.Lit (Lit.Bool value, loc), tokens, errors

  | (Token.Int value, loc) :: tokens ->
    AExpr.Lit (Lit.Int value, loc), tokens, errors

  | (Token.Char value, loc) :: tokens ->
    AExpr.Lit (Lit.Char value, loc), tokens, errors

  | (Token.Str value, loc) :: tokens ->
    AExpr.Lit (Lit.Str value, loc), tokens, errors

  | (Token.Ident ident, loc) :: tokens ->
    AExpr.Ident (ident, loc), tokens, errors

  | (Token.ParenL, _) :: tokens ->
    parseParenBody boxX (tokens, errors)

  | (Token.BracketL, bracketLoc) :: tokens ->
    parseList boxX bracketLoc (tokens, errors)

  | (Token.If, loc) :: tokens ->
    parseIf boxX loc (tokens, errors)

  | (Token.Match, loc) :: tokens ->
    parseMatch boxX loc (tokens, errors)

  | (Token.Fun, loc) :: tokens ->
    parseFun boxX loc (tokens, errors)

  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc (tokens, errors)

  | _ ->
    parseExprError "Expected an expression" (tokens, errors)

/// `suffix = atom ( '.' '[' range ']' | '.' ident )*`
let parseSuffix boxX (tokens, errors) =
  let l, tokens, errors = parseAtom boxX (tokens, errors)

  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Dot, loc) :: (Token.BracketL, _) :: tokens ->
      let r, tokens, errors = parseRange boxX (tokens, errors)

      let tokens, errors =
        match tokens with
        | (Token.BracketR, _) :: tokens ->
          tokens, errors

        | _ ->
          let errors = parseNewError "Expected closing ']'" (tokens, errors)
          tokens, errors

      go (AExpr.Index (acc, r, loc)) (tokens, errors)

    | (Token.Dot, loc) :: (Token.Ident r, _) :: tokens ->
      go (AExpr.Nav (acc, r, loc)) (tokens, errors)

    | (Token.Dot, _) :: tokens ->
      let errors = parseNewError "Expected .[] or .field" (tokens, errors)
      acc, tokens, errors

    | _ ->
      acc, tokens, errors

  go l (tokens, errors)

/// `app = suffix ( suffix )*`
let parseApp boxX (tokens, errors) =
  let calleeLoc = nextLoc tokens
  let insideX = max boxX (locX calleeLoc + 1)

  let callee, tokens, errors = parseSuffix boxX (tokens, errors)

  let rec go callee (tokens, errors) =
    if nextInside insideX tokens && leadsArg tokens then
      let arg, tokens, errors = parseSuffix insideX (tokens, errors)
      go (AExpr.Bin (Op.App, callee, arg, calleeLoc)) (tokens, errors)
    else
      callee, tokens, errors

  go callee (tokens, errors)

/// `prefix = '-'? app`
let parsePrefix boxX (tokens, errors) =
  match tokens with
  | (Token.Minus, loc) :: tokens ->
    let arg, tokens, errors = parseApp boxX (tokens, errors)
    AExpr.Uni (UniOp.Neg, arg, loc), tokens, errors

  | _ ->
    parseApp boxX (tokens, errors)

let parseNextLevelOp level boxX (tokens, errors) =
  match level with
  | OpLevel.Or ->
    parseOp OpLevel.And boxX (tokens, errors)

  | OpLevel.And ->
    parseOp OpLevel.Cmp boxX (tokens, errors)

  | OpLevel.Cmp ->
    parseOp OpLevel.Pipe boxX (tokens, errors)

  | OpLevel.Pipe ->
    parseOp OpLevel.Cons boxX (tokens, errors)

  | OpLevel.Cons ->
    parseOp OpLevel.Add boxX (tokens, errors)

  | OpLevel.Add ->
    parseOp OpLevel.Mul boxX (tokens, errors)

  | OpLevel.Mul ->
    parsePrefix boxX (tokens, errors)

let rec parseOps level boxX first (tokens, errors) =
  let nextL expr op opLoc (tokens, errors) =
    let second, tokens, errors = parseNextLevelOp level boxX (tokens, errors)
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level boxX expr (tokens, errors)

  let nextR expr op opLoc (tokens, errors) =
    let second, tokens, errors = parseOp level boxX (tokens, errors)
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level boxX expr (tokens, errors)

  match level, tokens with
  | OpLevel.Or, (Token.PipePipe, opLoc) :: tokens ->
    nextL first Op.Or opLoc (tokens, errors)

  | OpLevel.And, (Token.AmpAmp, opLoc) :: tokens ->
    nextL first Op.And opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.Eq, opLoc) :: tokens ->
    nextL first Op.Eq opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.LtGt, opLoc) :: tokens ->
    nextL first Op.Ne opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.Lt, opLoc) :: tokens ->
    nextL first Op.Lt opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.LtEq, opLoc) :: tokens ->
    nextL first Op.Le opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.Gt, opLoc) :: tokens ->
    nextL first Op.Gt opLoc (tokens, errors)

  | OpLevel.Cmp, (Token.GtEq, opLoc) :: tokens ->
    nextL first Op.Ge opLoc (tokens, errors)

  | OpLevel.Pipe, (Token.PipeGt, opLoc) :: tokens ->
    nextL first Op.Pipe opLoc (tokens, errors)

  | OpLevel.Cons, (Token.ColonColon, opLoc) :: tokens ->
    nextR first Op.Cons opLoc (tokens, errors)

  | OpLevel.Add, (Token.Plus, opLoc) :: tokens ->
    nextL first Op.Add opLoc (tokens, errors)

  | OpLevel.Add, (Token.Minus, opLoc) :: tokens ->
    nextL first Op.Sub opLoc (tokens, errors)

  | OpLevel.Mul, (Token.Star, opLoc) :: tokens ->
    nextL first Op.Mul opLoc (tokens, errors)

  | OpLevel.Mul, (Token.Slash, opLoc) :: tokens ->
    nextL first Op.Div opLoc (tokens, errors)

  | OpLevel.Mul, (Token.Percent, opLoc) :: tokens ->
    nextL first Op.Mod opLoc (tokens, errors)

  | _ ->
    first, tokens, errors

/// E.g. `add = mul ( ('+'|'-') mul )*`
let parseOp level boxX (tokens, errors) =
  let first, tokens, errors = parseNextLevelOp level boxX (tokens, errors)
  parseOps level boxX first (tokens, errors)

let parseTerm boxX (tokens, errors) =
  parseOp OpLevel.Or boxX (tokens, errors)

/// `tuple = term ( ',' term )*`
let parseTuple boxX (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Comma, _) :: tokens ->
      let second, tokens, errors = parseTerm boxX (tokens, errors)
      go (second :: acc) (tokens, errors)

    | tokens ->
      listRev acc, tokens, errors

  let item, tokens, errors = parseTerm boxX (tokens, errors)

  match tokens with
  | (Token.Comma, loc) :: _ ->
    let items, tokens, errors = go [] (tokens, errors)
    AExpr.TupleLit (item :: items, loc), tokens, errors

  | _ ->
    item, tokens, errors

/// `anno = tuple ( ':' ty )?`
let parseAnno boxX (tokens, errors) =
  let body, tokens, errors = parseTuple boxX (tokens, errors)

  match tokens with
  | (Token.Colon, loc) :: tokens ->
    let ty, tokens, errors = parseTy (nextX tokens) (tokens, errors)
    AExpr.Anno (body, ty, loc), tokens, errors

  | _ ->
    body, tokens, errors

let parseExpr1 boxX (tokens, errors) =
  parseAnno boxX (tokens, errors)

let parseBinding boxX (tokens, errors) =
  match tokens with
  | (Token.Let, letLoc) :: (Token.Rec, _) :: tokens ->
    // FIXME: use `rec`
    parseLet boxX letLoc (tokens, errors)

  | (Token.Let, letLoc) :: tokens ->
    parseLet boxX letLoc (tokens, errors)

  | (Token.Type, typeLoc) :: tokens ->
    parseTyDecl boxX typeLoc (tokens, errors)

  | (Token.Open, typeLoc) :: tokens ->
    parseBindingOpen boxX typeLoc (tokens, errors)

  | _ ->
    parseExpr1 boxX (tokens, errors)

/// All expressions must be aligned on the same column,
/// except it is preceded by semicolon.
let rec parseBindings boxX (tokens, errors) =
  let rec go acc alignX (tokens, errors) =
    match tokens with
    | (Token.Semi, _) :: tokens
      when nextX tokens >= alignX ->
      let expr, tokens, errors = parseBinding boxX (tokens, errors)
      go (expr :: acc) alignX (tokens, errors)

    | _
      when nextX tokens = alignX && leadsExpr tokens ->
      let expr, tokens, errors = parseBinding boxX (tokens, errors)
      go (expr :: acc) alignX (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  go [] (nextX tokens) (tokens, errors)

/// semi = binding ( ';' binding )*
let parseSemi loc boxX (tokens, errors) =
  let items, tokens, errors = parseBindings boxX (tokens, errors)

  match items with
  | [] ->
    parseExprError "Expected an expr" (tokens, errors)

  | [item] ->
    item, tokens, errors

  | _ ->
    AExpr.Semi (items, loc), tokens, errors

let parseExpr boxX (tokens, errors) =
  let loc = nextLoc tokens
  parseSemi loc boxX (tokens, errors)

/// module = 'module' identifier = ..
/// FIXME: stub
let parseModule boxX (tokens, errors) =
  match tokens with
  | (Token.Module, (_, moduleX))
    :: (Token.Ident _, _)
    :: (Token.Eq, _) :: tokens ->
    parseExpr (moduleX + 1) (tokens, errors)

  | _ ->
    parseExpr boxX (tokens, errors)

let parseTopLevel loc (tokens, errors) =
  match tokens with
  | [] ->
    AExpr.TupleLit ([], loc), tokens, errors

  | (Token.Module, moduleLoc)
    :: (Token.Rec, _)
    :: (Token.Ident _, _)
    :: (Token.Dot, _)
    :: (Token.Ident _, _) :: tokens ->
    parseModule (locX moduleLoc) (tokens, errors)

  | (Token.Module, moduleLoc)
    :: (Token.Rec, _)
    :: (Token.Ident _, _) :: tokens ->
    parseModule (locX moduleLoc) (tokens, errors)

  | (Token.Module, moduleLoc)
    :: (Token.Ident _, _) :: tokens ->
    parseModule (locX moduleLoc) (tokens, errors)

  | _ ->
    parseModule (locX loc) (tokens, errors)

/// module = ( 'module' 'rec'? ident bindings / bindings )?
let parse (tokens: (Token * Loc) list): AExpr * (string * Loc) list =
  let topLoc = 0, 0
  let expr, tokens, errors = parseTopLevel topLoc (tokens, [])

  let errors =
    match tokens with
    | [] ->
      errors

    | _ ->
      parseNewError "Expected eof" (tokens, errors)

  expr, errors
