/// ## Parse
///
/// Analyze a list of tokens of a source file
/// to build an abstract syntax tree (AST)
/// and report syntax errors.
///
/// ### Disclaimer
///
/// The syntax and the layout rule are **NOT equivalent with F#**.
/// The parser assumes the source code is formatted
/// with the similar layout to the milone-lang code itself.
///
/// ### Layout rules
///
/// Words:
///
/// - Statements
///   - `let pat = body in next`
///     - `pat` and `body` are *inner* subterms
///     - `next` is a *dangling* subterm
///   - `if cond then body else alt`
///     - `cond` and `body` are inner subterms
///     - `alt` is a dangling subterm
///   - `match target with | pat when guard -> body`
///     - `target`, `pat` and `guard` are inner subterms
///     - `body` is a dangling subterm if it's in the last arm;
///         or an inner subterm otherwise
///   - `type`
///   - `module`
/// - Functional applications (`f x`)
///     - `f` is a callee
///     - `x` is an argument
///
/// Rules:
///
/// - STATEMENT_INNER_LAYOUT:
///
///   Statements require the inner subterms
///   to be strictly deeper than the first token.
///
///   ```fsharp
///     let f () =
///      0  // Minimally indented (1-space)
///   ```
///
/// - STATEMENT_DANGLING_LAYOUT:
///
///   Statements require the dangling subterm
///   to be deeper or equal to the first token.
///
///   ```fsharp
///     if guard then error else
///     success   // Minimally indented (on the same column as `if`)
///   ```
///
/// - ELSE_IF_LAYOUT:
///
///   In short: `else if` is OK.
///
/// - SEMI_LAYOUT:
///
///   In a sequence of statements, first token of each item
///   must be on the same column as the first item
///   except a semicolon precedes it.
///
/// - APP_LAYOUT:
///
///   Argument of functional applications must be strictly deeper than
///   the first token of the callee.
///
///   ```fsharp
///     f
///      x  // Minimally indented (1-space)
///   ```
///
/// Note that the implementation doesn't verify the rule completely.
module rec MiloneLang.Parsing

open MiloneLang.Types
open MiloneLang.Helpers

// -----------------------------------------------
// Tokens
// -----------------------------------------------

let leadsExpr tokens =
  match tokens with
  | (token, _) :: _ ->
    tokenIsExprFirst token

  | _ ->
    false

let leadsArg tokens =
  match tokens with
  | (token, _) :: _ ->
    tokenIsArgFirst token

  | _ ->
    false

let leadsPat tokens =
  match tokens with
  | (token, _) :: _ ->
    tokenIsPatFirst token

  | _ ->
    false

/// Location of next token.
let private nextLoc tokens: Loc =
  match tokens with
  | [] ->
    (-1, 0)

  | (_, loc) :: _ ->
    loc

/// Gets if next token exists and is inside the outer box.
let private nextInside baseLoc tokens: bool =
  match tokens with
  | [] ->
    false

  // Closed by something out of box.
  | (_, loc) :: _
    when locInside baseLoc loc ->
    true

  | _ ->
    false

// -----------------------------------------------
// Errors
// -----------------------------------------------

let parseErrorCore msg loc tokens errors =
  // let near = tokens |> listMap fst |> listTruncate 6
  // let msg = sprintf "Parse error %s near %A" msg near
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
// Parse types
// -----------------------------------------------

let parseTyAtom baseLoc (tokens, errors) =
  match tokens with
  | _ when nextInside baseLoc tokens |> not ->
    parseTyError "Expected a type atom" (tokens, errors)

  | (Token.Ident ident, loc) :: tokens ->
    ATy.Ident (ident, loc), tokens, errors

  | (Token.ParenL, _) :: tokens ->
    let ty, tokens, errors = parseTy baseLoc (tokens, errors)

    match tokens with
    | (Token.ParenR, _) :: tokens ->
      ty, tokens, errors

    | _ ->
      let errors = parseNewError "Expected ')'" (tokens, errors)
      ty, tokens, errors

  | _ ->
    parseTyError "Expected a type atom" (tokens, errors)

/// `ty-suffix = ty-atom ( ident )*`
let parseTySuffix baseLoc (tokens, errors) =
  let rec go (ty, tokens, errors) =
    let inside = nextInside baseLoc tokens
    match tokens with
    | (Token.Ident ident, loc) :: tokens when inside ->
      go (ATy.Suffix (ty, ident, loc), tokens, errors)

    | _ ->
      ty, tokens, errors

  parseTyAtom baseLoc (tokens, errors) |> go

/// `ty-prefix = ( ident ':' )? ty-suffix`
/// FIXME: `foo:Foo` is only allowed in payload types.
let parseTyPrefix baseLoc (tokens, errors) =
  match tokens with
  | (Token.Ident _, _) :: (Token.Colon, _) :: tokens ->
    parseTySuffix baseLoc (tokens, errors)

  | _ ->
    parseTySuffix baseLoc (tokens, errors)

/// `ty-tuple = ty-prefix ( '*' ty-prefix )*`
let parseTyTuple baseLoc (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Star, _) :: tokens ->
      let itemTy, tokens, errors = parseTyPrefix baseLoc (tokens, errors)
      go (itemTy :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let itemTy, tokens, errors = parseTyPrefix baseLoc (tokens, errors)

  match tokens with
  | (Token.Star, opLoc) :: _ ->
    let itemTys, tokens, errors = go [] (tokens, errors)
    ATy.Tuple (itemTy :: itemTys, opLoc), tokens, errors

  | _ ->
    itemTy, tokens, errors

/// `ty-fun = ty-tuple ( '->' ty-fun )?`
/// FIXME: Support chain of arrows
let parseTyFun baseLoc (tokens, errors) =
  let sTy, tokens, errors = parseTyTuple baseLoc (tokens, errors)

  match tokens with
  | (Token.Arrow, opLoc) :: tokens ->
    let tTy, tokens, errors = parseTyFun baseLoc (tokens, errors)
    ATy.Fun (sTy, tTy, opLoc), tokens, errors

  | _ ->
    sTy, tokens, errors

let parseTy baseLoc (tokens, errors) =
  parseTyFun baseLoc (tokens, errors)

/// Parses the body of union `type` declaration.
let parseTyDeclUnion baseLoc (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Pipe, _)
      :: (Token.Ident variantIdent, loc)
      :: (Token.Of, _) :: tokens ->
      let payloadTy, tokens, errors = parseTy baseLoc (tokens, errors)
      go (AVariant (variantIdent, [payloadTy], loc) :: acc) (tokens, errors)

    | (Token.Pipe, _)
      :: (Token.Ident variantIdent, loc) :: tokens ->
      go (AVariant (variantIdent, [], loc) :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let variants, tokens, errors = go [] (tokens, errors)
  ATyDecl.Union variants, tokens, errors

/// Parses after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let parseTyDeclBody baseLoc (tokens, errors) =
  match tokens with
  | (Token.Pipe, _) :: _ ->
    parseTyDeclUnion baseLoc (tokens, errors)

  | (Token.Ident _, _) :: (Token.Of, _) :: _ ->
    parseTyDeclUnion baseLoc (tokens, errors)

  | _ ->
    let ty, tokens, errors = parseTy baseLoc (tokens, errors)
    ATyDecl.Synonym ty, tokens, errors

// -----------------------------------------------
// Parse patterns
// -----------------------------------------------

/// `pat ')'`
let parsePatParenBody baseLoc (tokens, errors) =
  let pat, tokens, errors = parsePat baseLoc (tokens, errors)

  match tokens with
  | (Token.ParenR, _) :: tokens ->
    pat, tokens, errors

  | tokens ->
    let errors = parseNewError "Expected ')'" (tokens, errors)
    pat, tokens, errors

/// `pat ( ';' pat )* ']'`
let parsePatListBody baseLoc bracketLoc (tokens, errors) =
  let rec go patAcc (tokens, errors) =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      listRev patAcc, tokens, errors

    // FIXME: Semicolon is required for now.
    | (Token.Semi, _) :: tokens ->
      let pat, tokens, errors = parsePat baseLoc (tokens, errors)
      go (pat :: patAcc) (tokens, errors)

    | _ ->
      let errors = parseNewError "Expected ';' or ']'" (tokens, errors)
      listRev patAcc, tokens, errors

  let itemPat, tokens, errors = parsePat baseLoc (tokens, errors)
  let itemPats, tokens, errors = go [itemPat] (tokens, errors)
  APat.ListLit (itemPats, bracketLoc), tokens, errors

let parsePatAtom baseLoc (tokens, errors) =
  match tokens with
  | _ when not (nextInside baseLoc tokens && leadsPat tokens) ->
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
    parsePatParenBody baseLoc (tokens, errors)

  | (Token.BracketL, loc) :: (Token.BracketR, _) :: tokens ->
    APat.ListLit ([], loc), tokens, errors

  | (Token.BracketL, loc) :: tokens ->
    parsePatListBody baseLoc loc (tokens, errors)

  | _ ->
    parsePatError "NEVER: The token must be a pat" (tokens, errors)

/// `pat-nav = pat-atom ( '.' ident )?`
let parsePatNav baseLoc (tokens, errors) =
  let pat, tokens, errors = parsePatAtom baseLoc (tokens, errors)

  match tokens with
  | (Token.Dot, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.Nav (pat, ident, loc), tokens, errors

  | (Token.Dot, _) :: tokens ->
    parsePatError "Expected identifier" (tokens, errors)

  | _ ->
    pat, tokens, errors

let parsePatCallArgs baseLoc calleeLoc (tokens, errors) =
  // APP_LAYOUT rule
  let argBaseLoc = locMax baseLoc calleeLoc |> locAddX 1

  let rec go acc (tokens, errors) =
    if nextInside argBaseLoc tokens && leadsPat tokens then
      let expr, tokens, errors = parsePatNav baseLoc (tokens, errors)
      go (expr :: acc) (tokens, errors)
    else
      listRev acc, tokens, errors

  go [] (tokens, errors)

/// `pat-call = pat-nav ( pat-nav )*`
let parsePatCall baseLoc (tokens, errors) =
  let calleeLoc = nextLoc tokens
  let callee, tokens, errors = parsePatNav baseLoc (tokens, errors)
  let args, tokens, errors = parsePatCallArgs baseLoc calleeLoc (tokens, errors)

  match args with
  | [] ->
    callee, tokens, errors

  | _ ->
    APat.Call (callee, args, calleeLoc), tokens, errors

/// `pat-cons = pat-call ( '::' pat-cons )?`
let parsePatCons baseLoc (tokens, errors) =
  let head, tokens, errors = parsePatCall baseLoc (tokens, errors)

  match tokens with
  | (Token.ColonColon, loc) :: tokens ->
    let tail, tokens, errors = parsePatCons baseLoc (tokens, errors)
    APat.Cons (head, tail, loc), tokens, errors

  | _ ->
    head, tokens, errors

/// `pat-anno = pat-cons ( ':' ty )?`
let parsePatAnno baseLoc (tokens, errors) =
  let pat, tokens, errors = parsePatCons baseLoc (tokens, errors)

  match tokens with
  | (Token.Colon, loc) :: tokens ->
    let ty, tokens, errors = parseTy (nextLoc tokens) (tokens, errors)
    APat.Anno (pat, ty, loc), tokens, errors

  | _ ->
    pat, tokens, errors

/// `pat-tuple = pat-anno ( ',' pat-anno )*`
let parsePatTuple baseLoc (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Comma, _) :: tokens ->
      let second, tokens, errors = parsePatAnno baseLoc (tokens, errors)
      go (second :: acc) (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let itemPat, tokens, errors = parsePatAnno baseLoc (tokens, errors)

  match tokens with
  | (Token.Comma, loc) :: _ ->
    let itemPats, tokens, errors = go [] (tokens, errors)
    APat.TupleLit (itemPat :: itemPats, loc), tokens, errors

  | _ ->
    itemPat, tokens, errors

/// `pat-as = pat-tuple ( 'as' ident )?`
/// NOTE: The syntax of `as` patterns is more flexible in F#.
let parsePatAs baseLoc (tokens, errors) =
  let pat, tokens, errors = parsePatTuple baseLoc (tokens, errors)

  match tokens with
  | (Token.As, loc) :: (Token.Ident ident, _) :: tokens ->
    APat.As (pat, ident, loc), tokens, errors

  | (Token.As, _) :: tokens ->
    let errors =  parseNewError "Expected an identifier" (tokens, errors)
    pat, tokens, errors

  | _ ->
    pat, tokens, errors

/// `pat-or = pat ( '|' pat-or )?`
let parsePatOr baseLoc (tokens, errors) =
  let lPat, tokens, errors = parsePatAs baseLoc (tokens, errors)

  match tokens with
  | (Token.Pipe, loc) :: tokens ->
    let rPat, tokens, errors = parsePatOr baseLoc (tokens, errors)
    APat.Or (lPat, rPat, loc), tokens, errors

  | _ ->
    lPat, tokens, errors

/// Parse a pattern of let expressions.
/// `pat-fun = ident pat-nav+ ( ':' ty )?`
/// `pat-let = pat-fun / pat`
let parsePatLet baseLoc (tokens, errors) =
  match tokens with
  | (Token.Ident callee, calleeLoc) :: tokens
    when locInside baseLoc calleeLoc && leadsPat tokens ->
    let args, tokens, errors = parsePatCallArgs baseLoc calleeLoc (tokens, errors)
    let pat = APat.Fun (callee, args, calleeLoc)

    match tokens with
    | (Token.Colon, loc) :: tokens ->
      let ty, tokens, errors = parseTy baseLoc (tokens, errors)
      APat.Anno (pat, ty, loc), tokens, errors

    | _ ->
      pat, tokens, errors

  | _ ->
    parsePat baseLoc (tokens, errors)

/// `pat = pat-or`
let parsePat baseLoc (tokens, errors) =
  if not (nextInside baseLoc tokens && leadsPat tokens) then
    parsePatError "Expected a pattern" (tokens, errors)
  else
    parsePatOr baseLoc (tokens, errors)

// -----------------------------------------------
// Parse expressions
// -----------------------------------------------

/// `range = term ( '..' term )?`
let parseRange baseLoc (tokens, errors) =
  let l, tokens, errors = parseExpr baseLoc (tokens, errors)

  match tokens with
  | (Token.DotDot, loc) :: tokens ->
    let r, tokens, errors = parseExpr baseLoc (tokens, errors)
    AExpr.Range ([l; r], loc), tokens, errors

  | _ ->
    l, tokens, errors

let parseList baseLoc bracketLoc (tokens, errors) =
  let items, tokens, errors = parseStmts baseLoc (tokens, errors)

  let tokens, errors =
    match tokens with
    | (Token.BracketR, _) :: tokens ->
      tokens, errors

    | _ ->
      let errors = parseNewError "Expected ']'" (tokens, errors)
      tokens, errors

  AExpr.ListLit (items, bracketLoc), tokens, errors

let parseThenClause baseLoc (tokens, errors) =
  let innerBaseLoc = baseLoc |> locAddX 1

  match tokens with
  | (Token.Then, thenLoc) :: tokens when locInside baseLoc thenLoc ->
    parseSemi innerBaseLoc thenLoc (tokens, errors)

  | _ ->
    parseExprError "Expected 'then'" (tokens, errors)

let parseElseClause baseLoc (tokens, errors) =
  match tokens with
  | (Token.Else, elseLoc) :: (Token.If, nextIfLoc) :: tokens
    when locInside baseLoc elseLoc && locIsSameRow elseLoc nextIfLoc ->
    // ELSE_IF_LAYOUT rule. Parse the next as if `if` in `else if` is placed where `else` is.
    parseExpr baseLoc ((Token.If, elseLoc) :: tokens, errors)

  | (Token.Else, elseLoc) :: tokens
    when locInside baseLoc elseLoc ->
    parseSemi baseLoc elseLoc (tokens, errors)

  | _ ->
    AExpr.Missing baseLoc, tokens, errors

let parseIf ifLoc (tokens, errors) =
  let innerBaseLoc = ifLoc |> locAddX 1

  let cond, tokens, errors = parseExpr innerBaseLoc (tokens, errors)
  let body, tokens, errors = parseThenClause ifLoc (tokens, errors)
  let alt, tokens, errors = parseElseClause ifLoc (tokens, errors)
  AExpr.If (cond, body, alt, ifLoc), tokens, errors

/// `pat ( 'when' expr )? -> expr`
let parseMatchArm matchLoc armLoc (tokens, errors) =
  let innerBaseLoc = matchLoc |> locAddX 1

  let pat, tokens, errors = parsePat innerBaseLoc (tokens, errors)

  let guard, tokens, errors =
    match tokens with
    | (Token.When, _) :: tokens ->
      parseExpr innerBaseLoc (tokens, errors)

    | _ ->
      let guard = AExpr.Missing (nextLoc tokens)
      guard, tokens, errors

  let body, tokens, errors =
    match tokens with
    | (Token.Arrow, arrowLoc) :: tokens ->
      parseSemi matchLoc arrowLoc (tokens, errors)

    | _ ->
      parseExprError "Expected '->'" (tokens, errors)

  AArm (pat, guard, body, armLoc), tokens, errors

let parseMatch matchLoc (tokens, errors) =
  let target, tokens, errors = parseExpr matchLoc (tokens, errors)

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
    let arm, tokens, errors = parseMatchArm matchLoc armLoc (tokens, errors)

    match tokens with
    | (Token.Pipe, pipeLoc) :: tokens when locInside matchLoc pipeLoc ->
      go (arm :: acc) pipeLoc (tokens, errors)

    | _ ->
      listRev (arm :: acc), tokens, errors

  let arms, tokens, errors = go [] armLoc (tokens, errors)
  AExpr.Match (target, arms, matchLoc), tokens, errors

/// `fun-expr = 'fun' pat* '->' expr`
let parseFun baseLoc funLoc (tokens, errors) =
  let pats, tokens, errors = parsePatCallArgs baseLoc funLoc (tokens, errors)

  let body, tokens, errors =
    match tokens with
    | (Token.Arrow, arrowLoc) :: tokens ->
      parseSemi baseLoc arrowLoc (tokens, errors)

    | _ ->
      parseExprError "Missing '->'" (tokens, errors)

  AExpr.Fun (pats, body, funLoc), tokens, errors

let parseParenBody baseLoc parenLoc (tokens, errors) =
  let body, tokens, errors = parseSemi baseLoc parenLoc (tokens, errors)

  match tokens with
  | (Token.ParenR, _) :: tokens ->
    body, tokens, errors

  | _ ->
    let errors = parseNewError "Expected ')'" (tokens, errors)
    body, tokens, errors

let parseAccessModifier tokens =
  match tokens with
  | (t, _) :: tokens when t |> tokenIsAccessModifier ->
    // FIXME: Support access modifiers.
    tokens

  | _ ->
    tokens

let parseLet letLoc (tokens, errors) =
  let innerBaseLoc = letLoc |> locAddX 1

  let tokens = parseAccessModifier tokens

  let pat, tokens, errors = parsePatLet innerBaseLoc (tokens, errors)

  let body, tokens, errors =
    match tokens with
    | (Token.Eq, eqLoc) :: tokens ->
      parseSemi innerBaseLoc eqLoc (tokens, errors)

    | _ ->
      parseExprError "Missing '='" (tokens, errors)

  let next, tokens, errors =
    match tokens with
    | (Token.In, inLoc) :: tokens when locInside letLoc inLoc ->
      parseSemi letLoc inLoc (tokens, errors)

    | _ :: _ when locIsSameColumn (nextLoc tokens) letLoc ->
      // Implicit `in` clause must be on the same column as `let`.
      parseSemi letLoc (nextLoc tokens) (tokens, errors)

    | tokens ->
      AExpr.TupleLit ([], letLoc), tokens, errors

  AExpr.Let (pat, body, next, letLoc), tokens, errors

let parseTyDecl typeLoc (tokens, errors) =
  let baseLoc = typeLoc |> locAddX 1

  let tokens = parseAccessModifier tokens

  match tokens with
  | (Token.Ident tyIdent, _) :: tokens ->
    match tokens with
    | (Token.Eq, _) :: tokens ->
      let tyDecl, tokens, errors = parseTyDeclBody baseLoc (tokens, errors)

      let expr =
        match tyDecl with
        | ATyDecl.Synonym ty ->
          AExpr.TySynonym (tyIdent, ty, typeLoc)

        | ATyDecl.Union variants ->
          AExpr.TyUnion (tyIdent, variants, typeLoc)

      expr, tokens, errors

    | _ ->
      let ty, tokens, errors = parseTyError "Expected '='" (tokens, errors)
      AExpr.TySynonym (tyIdent, ty, typeLoc), tokens, errors

  | _ ->
    parseExprError "Expected identifier" (tokens, errors)

/// `open = 'open' ident ( '.' ident )*`
let parseOpen openLoc (tokens, errors) =
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

let parseAtom baseLoc (tokens, errors) =
  match tokens with
  | _ when not (nextInside baseLoc tokens) ->
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

  | (Token.ParenL, parenLoc) :: tokens ->
    parseParenBody baseLoc parenLoc (tokens, errors)

  | (Token.BracketL, bracketLoc) :: tokens ->
    parseList baseLoc bracketLoc (tokens, errors)

  | (Token.If, loc) :: tokens ->
    parseIf loc (tokens, errors)

  | (Token.Match, loc) :: tokens ->
    parseMatch loc (tokens, errors)

  | (Token.Fun, loc) :: tokens ->
    parseFun baseLoc loc (tokens, errors)

  | (Token.Let, letLoc) :: tokens ->
    parseLet letLoc (tokens, errors)

  | _ ->
    parseExprError "Expected an expression" (tokens, errors)

/// `suffix = atom ( '.' '[' range ']' | '.' ident )*`
let parseSuffix baseLoc (tokens, errors) =
  let l, tokens, errors = parseAtom baseLoc (tokens, errors)

  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Dot, loc) :: (Token.BracketL, _) :: tokens ->
      let r, tokens, errors = parseRange baseLoc (tokens, errors)

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
let parseApp baseLoc (tokens, errors) =
  let calleeLoc = nextLoc tokens
  let argBaseLoc = calleeLoc |> locAddX 1

  let callee, tokens, errors = parseSuffix baseLoc (tokens, errors)

  let rec go callee (tokens, errors) =
    if nextInside argBaseLoc tokens && leadsArg tokens then
      let arg, tokens, errors = parseSuffix baseLoc (tokens, errors)
      go (AExpr.Bin (Op.App, callee, arg, calleeLoc)) (tokens, errors)
    else
      callee, tokens, errors

  go callee (tokens, errors)

/// `prefix = '-'? app`
let parsePrefix baseLoc (tokens, errors) =
  match tokens with
  | (Token.Minus, loc) :: tokens ->
    let arg, tokens, errors = parseApp baseLoc (tokens, errors)
    AExpr.Uni (UniOp.Neg, arg, loc), tokens, errors

  | _ ->
    parseApp baseLoc (tokens, errors)

let parseNextLevelOp level baseLoc (tokens, errors) =
  match opLevelToNext level with
  | OpLevel.Prefix ->
    parsePrefix baseLoc (tokens, errors)

  | nextLevel ->
    parseOp nextLevel baseLoc (tokens, errors)

let rec parseOps level baseLoc first (tokens, errors) =
  let nextL expr op opLoc (tokens, errors) =
    let second, tokens, errors = parseNextLevelOp level baseLoc (tokens, errors)
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level baseLoc expr (tokens, errors)

  let nextR expr op opLoc (tokens, errors) =
    let second, tokens, errors = parseOp level baseLoc (tokens, errors)
    let expr = AExpr.Bin (op, expr, second, opLoc)
    parseOps level baseLoc expr (tokens, errors)

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
let parseOp level baseLoc (tokens, errors) =
  let first, tokens, errors = parseNextLevelOp level baseLoc (tokens, errors)
  parseOps level baseLoc first (tokens, errors)

let parseTupleItem baseLoc (tokens, errors) =
  parseOp OpLevel.Or baseLoc (tokens, errors)

/// `tuple = item ( ',' item )*`
let parseTuple baseLoc (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (Token.Comma, _) :: tokens ->
      let second, tokens, errors = parseTupleItem baseLoc (tokens, errors)
      go (second :: acc) (tokens, errors)

    | tokens ->
      listRev acc, tokens, errors

  let item, tokens, errors = parseTupleItem baseLoc (tokens, errors)

  match tokens with
  | (Token.Comma, loc) :: _ ->
    let items, tokens, errors = go [] (tokens, errors)
    AExpr.TupleLit (item :: items, loc), tokens, errors

  | _ ->
    item, tokens, errors

/// `anno = tuple ( ':' ty )?`
let parseAnno baseLoc (tokens, errors) =
  let body, tokens, errors = parseTuple baseLoc (tokens, errors)

  match tokens with
  | (Token.Colon, loc) :: tokens ->
    let ty, tokens, errors = parseTy baseLoc (tokens, errors)
    AExpr.Anno (body, ty, loc), tokens, errors

  | _ ->
    body, tokens, errors

let parseExpr baseLoc (tokens, errors) =
  parseAnno baseLoc (tokens, errors)

let parseStmt baseLoc (tokens, errors) =
  match tokens with
  | (Token.Let, letLoc) :: (Token.Rec, _) :: tokens ->
    // FIXME: use `rec`
    parseLet letLoc (tokens, errors)

  | (Token.Let, letLoc) :: tokens ->
    parseLet letLoc (tokens, errors)

  | (Token.Type, typeLoc) :: tokens ->
    parseTyDecl typeLoc (tokens, errors)

  | (Token.Open, typeLoc) :: tokens ->
    parseOpen typeLoc (tokens, errors)

  | _ ->
    parseExpr baseLoc (tokens, errors)

/// Parses a sequence of statements.
/// These statements must be aligned on the same column
/// except ones preceded by semicolon.
let rec parseStmts baseLoc (tokens, errors) =
  let rec go acc alignLoc (tokens, errors) =
    match tokens with
    | (Token.Semi, semiLoc) :: tokens
      when locInside alignLoc semiLoc ->
      let expr, tokens, errors = parseStmt baseLoc (tokens, errors)
      go (expr :: acc) alignLoc (tokens, errors)

    | _ when locIsSameColumn alignLoc (nextLoc tokens) && leadsExpr tokens ->
      let expr, tokens, errors = parseStmt baseLoc (tokens, errors)
      go (expr :: acc) alignLoc (tokens, errors)

    | _ ->
      listRev acc, tokens, errors

  let alignLoc = nextLoc tokens
  if locInside baseLoc alignLoc then
    go [] alignLoc (tokens, errors)
  else
    [], tokens, errors

/// Parses a sequence of expressions separated by `;`s
/// or aligned on the same column.
/// Contents must be deeper than or equal to `baseLoc`,
/// which is typically the location of `let`/`type`/`module`/etc.
/// The `mainLoc` is a hint of the semi expression's location.
/// `stmts = stmt ( ';' stmt )*`
let parseSemi baseLoc mainLoc (tokens, errors) =
  let items, tokens, errors = parseStmts baseLoc (tokens, errors)

  match items with
  | [] ->
    parseExprError "Expected statements" (tokens, errors)

  | [item] ->
    item, tokens, errors

  | _ ->
    AExpr.Semi (items, mainLoc), tokens, errors

/// `top-level = ( 'module' 'rec'? path module-body / module-body )?`
let parseTopLevel (tokens, errors) =
  let topLoc = 0, 0

  match tokens with
  | [] ->
    AExpr.TupleLit ([], topLoc), tokens, errors

  | (Token.Module, moduleLoc)
    :: (Token.Rec, _)
    :: (Token.Ident _, _)
    :: (Token.Dot, _)
    :: (Token.Ident _, _) :: tokens ->
    parseSemi moduleLoc moduleLoc (tokens, errors)

  | (Token.Module, moduleLoc)
    :: (Token.Rec, _)
    :: (Token.Ident _, _) :: tokens ->
    parseSemi moduleLoc moduleLoc (tokens, errors)

  | (Token.Module, moduleLoc)
    :: (Token.Ident _, _) :: tokens ->
    parseSemi moduleLoc moduleLoc (tokens, errors)

  | _ ->
    parseSemi topLoc topLoc (tokens, errors)

let parse (tokens: (Token * Loc) list): AExpr * (string * Loc) list =
  let expr, tokens, errors = parseTopLevel (tokens, [])

  let errors =
    match tokens with
    | [] ->
      errors

    | _ ->
      parseNewError "Expected eof" (tokens, errors)

  expr, errors
