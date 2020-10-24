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
/// Note that the implementation doesn't verify the rule completely.
module rec MiloneLang.Parsing

open MiloneLang.Types
open MiloneLang.Helpers

// -----------------------------------------------
// Tokens
// -----------------------------------------------

let leadsExpr tokens =
  match tokens with
  | (token, _) :: _ -> tokenIsExprFirst token

  | _ -> false

let leadsArg tokens =
  match tokens with
  | (token, _) :: _ -> tokenIsArgFirst token

  | _ -> false

let leadsPat tokens =
  match tokens with
  | (token, _) :: _ -> tokenIsPatFirst token

  | _ -> false

/// Position of next token.
let private nextPos tokens: Pos =
  match tokens with
  | [] -> (-1, 0)

  | (_, pos) :: _ -> pos

/// Gets if next token exists and is inside the outer box.
let private nextInside basePos tokens: bool =
  match tokens with
  | [] -> false

  // Closed by something out of box.
  | (_, pos) :: _ when posInside basePos pos -> true

  | _ -> false

// -----------------------------------------------
// Errors
// -----------------------------------------------

let parseErrorCore msg pos errors =
  let msg =
    "PARSE ERROR: "
    + msg
    + " ("
    + posToString pos
    + ")"

  (msg, pos) :: errors

let parseTyError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  ATy.Missing pos, tokens, errors

let parsePatError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  APat.Missing pos, tokens, errors

let parseExprError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AExpr.Missing pos, tokens, errors

let parseNewError msg (tokens, errors) =
  let pos = nextPos tokens
  parseErrorCore msg pos errors

// -----------------------------------------------
// Parse types
// -----------------------------------------------

/// `'<' ty '>'`
let parseTyArgs basePos (tokens, errors) =
  match tokens with
  | (LeftAngleToken, ltPos) :: tokens when posInside basePos ltPos ->
      let rec go acc (tokens, errors) =
        match tokens with
        | (CommaToken, _) :: tokens ->
            let argTy, tokens, errors = parseTy basePos (tokens, errors)
            go (argTy :: acc) (tokens, errors)

        | _ -> listRev acc, tokens, errors

      let argTy, tokens, errors = parseTy basePos (tokens, errors)
      let argTys, tokens, errors = go [ argTy ] (tokens, errors)

      let tokens, errors =
        match tokens with
        | (RightAngleToken, _) :: tokens -> tokens, errors

        | _ ->
            let errors =
              parseNewError "Expected '>'" (tokens, errors)

            tokens, errors

      argTys, tokens, errors

  | _ -> [], tokens, errors

let parseTyAtom basePos (tokens, errors) =
  match tokens with
  | _ when nextInside basePos tokens |> not -> parseTyError "Expected a type atom" (tokens, errors)

  | (IdentToken ident, pos) :: tokens ->
      let argTys, tokens, errors = parseTyArgs basePos (tokens, errors)
      ATy.App(ident, argTys, pos), tokens, errors

  | (LeftParenToken, _) :: tokens ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)

      match tokens with
      | (RightParenToken, _) :: tokens -> ty, tokens, errors

      | _ ->
          let errors =
            parseNewError "Expected ')'" (tokens, errors)

          ty, tokens, errors

  | _ -> parseTyError "Expected a type atom" (tokens, errors)

/// `ty-suffix = ty-atom ( ident )*`
let parseTySuffix basePos (tokens, errors) =
  let rec go (ty, tokens, errors) =
    let inside = nextInside basePos tokens
    match tokens with
    | (IdentToken ident, pos) :: tokens when inside -> go (ATy.Suffix(ty, ident, pos), tokens, errors)

    | _ -> ty, tokens, errors

  parseTyAtom basePos (tokens, errors) |> go

/// `ty-prefix = ( ident ':' )? ty-suffix`
/// FIXME: `foo:Foo` is only allowed in payload types.
let parseTyPrefix basePos (tokens, errors) =
  match tokens with
  | (IdentToken _, _) :: (ColonToken, _) :: tokens -> parseTySuffix basePos (tokens, errors)

  | _ -> parseTySuffix basePos (tokens, errors)

/// `ty-tuple = ty-prefix ( '*' ty-prefix )*`
let parseTyTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (StarToken, _) :: tokens ->
        let itemTy, tokens, errors = parseTyPrefix basePos (tokens, errors)
        go (itemTy :: acc) (tokens, errors)

    | _ -> listRev acc, tokens, errors

  let itemTy, tokens, errors = parseTyPrefix basePos (tokens, errors)

  match tokens with
  | (StarToken, opPos) :: _ ->
      let itemTys, tokens, errors = go [] (tokens, errors)
      ATy.Tuple(itemTy :: itemTys, opPos), tokens, errors

  | _ -> itemTy, tokens, errors

/// `ty-fun = ty-tuple ( '->' ty-fun )?`
/// FIXME: Support chain of arrows
let parseTyFun basePos (tokens, errors) =
  let sTy, tokens, errors = parseTyTuple basePos (tokens, errors)

  match tokens with
  | (ArrowToken, opPos) :: tokens ->
      let tTy, tokens, errors = parseTyFun basePos (tokens, errors)
      ATy.Fun(sTy, tTy, opPos), tokens, errors

  | _ -> sTy, tokens, errors

let parseTy basePos (tokens, errors) = parseTyFun basePos (tokens, errors)

/// Parses the body of union `type` declaration.
let parseTyDeclUnion basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (PipeToken, _) :: (IdentToken variantIdent, pos) :: (OfToken, _) :: tokens ->
        let payloadTy, tokens, errors = parseTy basePos (tokens, errors)
        go (AVariant(variantIdent, Some payloadTy, pos) :: acc) (tokens, errors)

    | (PipeToken, _) :: (IdentToken variantIdent, pos) :: tokens ->
        go (AVariant(variantIdent, None, pos) :: acc) (tokens, errors)

    | _ -> listRev acc, tokens, errors

  let variants, tokens, errors = go [] (tokens, errors)
  ATyDecl.Union variants, tokens, errors

/// Parses after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let parseTyDeclBody basePos (tokens, errors) =
  match tokens with
  | (PipeToken, _) :: _ -> parseTyDeclUnion basePos (tokens, errors)

  | (IdentToken _, _) :: (OfToken, _) :: _ ->
      let tokens = (PipeToken, noPos) :: tokens
      parseTyDeclUnion basePos (tokens, errors)

  | _ ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)
      ATyDecl.Synonym ty, tokens, errors

// -----------------------------------------------
// Parse patterns
// -----------------------------------------------

/// `pat ')'`
let parsePatParenBody basePos (tokens, errors) =
  let pat, tokens, errors = parsePat basePos (tokens, errors)

  match tokens with
  | (RightParenToken, _) :: tokens -> pat, tokens, errors

  | tokens ->
      let errors =
        parseNewError "Expected ')'" (tokens, errors)

      pat, tokens, errors

/// `pat ( ';' pat )* ']'`
let parsePatListBody basePos bracketPos (tokens, errors) =
  let rec go patAcc (tokens, errors) =
    match tokens with
    | (RightBracketToken, _) :: tokens -> listRev patAcc, tokens, errors

    // FIXME: Semicolon is required for now.
    | (SemiToken, _) :: tokens ->
        let pat, tokens, errors = parsePat basePos (tokens, errors)
        go (pat :: patAcc) (tokens, errors)

    | _ ->
        let errors =
          parseNewError "Expected ';' or ']'" (tokens, errors)

        listRev patAcc, tokens, errors

  let itemPat, tokens, errors = parsePat basePos (tokens, errors)
  let itemPats, tokens, errors = go [ itemPat ] (tokens, errors)
  APat.ListLit(itemPats, bracketPos), tokens, errors

let parsePatAtom basePos (tokens, errors) =
  match tokens with
  | _ when not (nextInside basePos tokens && leadsPat tokens) ->
      parsePatError "Expected a pattern atom" (tokens, errors)

  | (IntToken value, pos) :: tokens -> APat.Lit(IntLit value, pos), tokens, errors

  | (CharToken value, pos) :: tokens -> APat.Lit(CharLit value, pos), tokens, errors

  | (StrToken value, pos) :: tokens -> APat.Lit(StrLit value, pos), tokens, errors

  | (IdentToken ident, pos) :: tokens -> APat.Ident(ident, pos), tokens, errors

  | (LeftParenToken, pos) :: (RightParenToken, _) :: tokens -> APat.TupleLit([], pos), tokens, errors

  | (LeftParenToken, _) :: tokens -> parsePatParenBody basePos (tokens, errors)

  | (LeftBracketToken, pos) :: (RightBracketToken, _) :: tokens -> APat.ListLit([], pos), tokens, errors

  | (LeftBracketToken, pos) :: tokens -> parsePatListBody basePos pos (tokens, errors)

  | (FalseToken, pos) :: tokens -> APat.Lit(BoolLit false, pos), tokens, errors

  | (TrueToken, pos) :: tokens -> APat.Lit(BoolLit true, pos), tokens, errors

  | _ -> parsePatError "NEVER: The token must be a pat" (tokens, errors)

/// `pat-nav = pat-atom ( '.' ident )?`
let parsePatNav basePos (tokens, errors) =
  let pat, tokens, errors = parsePatAtom basePos (tokens, errors)

  match tokens with
  | (DotToken, pos) :: (IdentToken ident, _) :: tokens -> APat.Nav(pat, ident, pos), tokens, errors

  | (DotToken, _) :: tokens -> parsePatError "Expected identifier" (tokens, errors)

  | _ -> pat, tokens, errors

let parsePatCallArgs basePos (tokens, errors) =
  let innerBasePos = basePos |> posAddX 1

  let rec go acc (tokens, errors) =
    if nextInside innerBasePos tokens && leadsPat tokens then
      let expr, tokens, errors = parsePatNav basePos (tokens, errors)
      go (expr :: acc) (tokens, errors)
    else
      listRev acc, tokens, errors

  go [] (tokens, errors)

/// `pat-call = pat-nav ( pat-nav )*`
let parsePatCall basePos (tokens, errors) =
  let calleePos = nextPos tokens
  let callee, tokens, errors = parsePatNav basePos (tokens, errors)

  let args, tokens, errors =
    parsePatCallArgs basePos (tokens, errors)

  match args with
  | [] -> callee, tokens, errors

  | _ -> APat.Call(callee, args, calleePos), tokens, errors

/// `pat-cons = pat-call ( '::' pat-cons )?`
let parsePatCons basePos (tokens, errors) =
  let head, tokens, errors = parsePatCall basePos (tokens, errors)

  match tokens with
  | (ColonColonToken, pos) :: tokens ->
      let tail, tokens, errors = parsePatCons basePos (tokens, errors)
      APat.Cons(head, tail, pos), tokens, errors

  | _ -> head, tokens, errors

/// `pat-anno = pat-cons ( ':' ty )?`
let parsePatAnno basePos (tokens, errors) =
  let pat, tokens, errors = parsePatCons basePos (tokens, errors)

  match tokens with
  | (ColonToken, pos) :: tokens ->
      let ty, tokens, errors =
        parseTy (nextPos tokens) (tokens, errors)

      APat.Anno(pat, ty, pos), tokens, errors

  | _ -> pat, tokens, errors

/// `pat-tuple = pat-anno ( ',' pat-anno )*`
let parsePatTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (CommaToken, _) :: tokens ->
        let second, tokens, errors = parsePatAnno basePos (tokens, errors)
        go (second :: acc) (tokens, errors)

    | _ -> listRev acc, tokens, errors

  let itemPat, tokens, errors = parsePatAnno basePos (tokens, errors)

  match tokens with
  | (CommaToken, pos) :: _ ->
      let itemPats, tokens, errors = go [] (tokens, errors)
      APat.TupleLit(itemPat :: itemPats, pos), tokens, errors

  | _ -> itemPat, tokens, errors

/// `pat-as = pat-tuple ( 'as' ident )?`
/// NOTE: The syntax of `as` patterns is more flexible in F#.
let parsePatAs basePos (tokens, errors) =
  let pat, tokens, errors = parsePatTuple basePos (tokens, errors)

  match tokens with
  | (AsToken, pos) :: (IdentToken ident, _) :: tokens -> APat.As(pat, ident, pos), tokens, errors

  | (AsToken, _) :: tokens ->
      let errors =
        parseNewError "Expected an identifier" (tokens, errors)

      pat, tokens, errors

  | _ -> pat, tokens, errors

/// `pat-or = pat ( '|' pat-or )?`
let parsePatOr basePos (tokens, errors) =
  let lPat, tokens, errors = parsePatAs basePos (tokens, errors)

  match tokens with
  | (PipeToken, pos) :: tokens ->
      let rPat, tokens, errors = parsePatOr basePos (tokens, errors)
      APat.Or(lPat, rPat, pos), tokens, errors

  | _ -> lPat, tokens, errors

/// Parse a pattern of let expressions.
/// `pat-fun = ident pat-nav+ ( ':' ty )?`
/// `pat-let = pat-fun / pat`
let parsePatLet basePos (tokens, errors) =
  match tokens with
  | (IdentToken callee, calleePos) :: tokens when posInside basePos calleePos && leadsPat tokens ->
      let args, tokens, errors =
        parsePatCallArgs basePos (tokens, errors)

      let pat = APat.Fun(callee, args, calleePos)

      match tokens with
      | (ColonToken, pos) :: tokens ->
          let ty, tokens, errors = parseTy basePos (tokens, errors)
          APat.Anno(pat, ty, pos), tokens, errors

      | _ -> pat, tokens, errors

  | _ -> parsePat basePos (tokens, errors)

/// `pat = pat-or`
let parsePat basePos (tokens, errors) =
  if not (nextInside basePos tokens && leadsPat tokens)
  then parsePatError "Expected a pattern" (tokens, errors)
  else parsePatOr basePos (tokens, errors)

// -----------------------------------------------
// Parse expressions
// -----------------------------------------------

/// `range = term ( '..' term )?`
let parseRange basePos (tokens, errors) =
  let l, tokens, errors = parseExpr basePos (tokens, errors)

  match tokens with
  | (DotDotToken, pos) :: tokens ->
      let r, tokens, errors = parseExpr basePos (tokens, errors)
      AExpr.Range([ l; r ], pos), tokens, errors

  | _ -> l, tokens, errors

let parseList basePos bracketPos (tokens, errors) =
  let items, tokens, errors = parseStmts basePos (tokens, errors)

  let tokens, errors =
    match tokens with
    | (RightBracketToken, _) :: tokens -> tokens, errors

    | _ ->
        let errors =
          parseNewError "Expected ']'" (tokens, errors)

        tokens, errors

  AExpr.ListLit(items, bracketPos), tokens, errors

let parseThenClause basePos (tokens, errors) =
  let innerBasePos = basePos |> posAddX 1

  match tokens with
  | (ThenToken, thenPos) :: tokens when posInside basePos thenPos -> parseSemi innerBasePos thenPos (tokens, errors)

  | _ -> parseExprError "Expected 'then'" (tokens, errors)

let parseElseClause basePos (tokens, errors) =
  match tokens with
  | (ElseToken, elsePos) :: (IfToken, nextIfPos) :: tokens when posInside basePos elsePos
                                                                && posIsSameRow elsePos nextIfPos ->
      // ELSE_IF_LAYOUT rule. Parse the next as if `if` in `else if` is placed where `else` is.
      parseExpr basePos ((IfToken, elsePos) :: tokens, errors)

  | (ElseToken, elsePos) :: tokens when posInside basePos elsePos -> parseSemi basePos elsePos (tokens, errors)

  | _ -> AExpr.Missing basePos, tokens, errors

let parseIf ifPos (tokens, errors) =
  let innerBasePos = ifPos |> posAddX 1

  let cond, tokens, errors = parseExpr innerBasePos (tokens, errors)
  let body, tokens, errors = parseThenClause ifPos (tokens, errors)
  let alt, tokens, errors = parseElseClause ifPos (tokens, errors)
  AExpr.If(cond, body, alt, ifPos), tokens, errors

/// `pat ( 'when' expr )? -> expr`
let parseMatchArm matchPos armPos (tokens, errors) =
  let innerBasePos = matchPos |> posAddX 1

  let pat, tokens, errors = parsePat innerBasePos (tokens, errors)

  let guard, tokens, errors =
    match tokens with
    | (WhenToken, _) :: tokens -> parseExpr innerBasePos (tokens, errors)

    | _ ->
        let guard = AExpr.Missing(nextPos tokens)
        guard, tokens, errors

  let body, tokens, errors =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> parseSemi matchPos arrowPos (tokens, errors)

    | _ -> parseExprError "Expected '->'" (tokens, errors)

  AArm(pat, guard, body, armPos), tokens, errors

let parseMatch matchPos (tokens, errors) =
  let target, tokens, errors = parseExpr matchPos (tokens, errors)

  let armPos, tokens, errors =
    match tokens with
    | (WithToken, _) :: (PipeToken, pipePos) :: tokens -> pipePos, tokens, errors

    | (WithToken, withPos) :: tokens -> withPos, tokens, errors

    | _ ->
        let errors =
          parseNewError "Expected 'with'" (tokens, errors)

        matchPos, tokens, errors

  let rec go acc armPos (tokens, errors) =
    let arm, tokens, errors =
      parseMatchArm matchPos armPos (tokens, errors)

    match tokens with
    | (PipeToken, pipePos) :: tokens when posInside matchPos pipePos -> go (arm :: acc) pipePos (tokens, errors)

    | _ -> listRev (arm :: acc), tokens, errors

  let arms, tokens, errors = go [] armPos (tokens, errors)
  AExpr.Match(target, arms, matchPos), tokens, errors

/// `fun-expr = 'fun' pat* '->' expr`
let parseFun basePos funPos (tokens, errors) =
  let pats, tokens, errors =
    parsePatCallArgs basePos (tokens, errors)

  let body, tokens, errors =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> parseSemi basePos arrowPos (tokens, errors)

    | _ -> parseExprError "Missing '->'" (tokens, errors)

  AExpr.Fun(pats, body, funPos), tokens, errors

let parseParenBody basePos _parenPos (tokens, errors) =
  // NOTE: Parens should form a layout bposk but not for now.
  //  If does, `(` in `xs |> List.map (fun x -> body)` unexpectedly requires
  //  `body` to be deeper than it. This is one of flaws of the simplified layout rule.
  let body, tokens, errors = parseExpr basePos (tokens, errors)

  match tokens with
  | (RightParenToken, _) :: tokens -> body, tokens, errors

  | _ ->
      let errors =
        parseNewError "Expected ')'" (tokens, errors)

      body, tokens, errors

let parseVis tokens =
  let outerTokens = tokens

  match tokens with
  | (t, _) :: tokens ->
      match tokenAsVis t with
      | Some vis -> vis, tokens

      | None -> PublicVis, outerTokens

  | [] -> PublicVis, tokens

let parseLet letPos (tokens, errors) =
  let innerBasePos = letPos |> posAddX 1

  let vis, tokens = parseVis tokens

  let pat, tokens, errors =
    parsePatLet innerBasePos (tokens, errors)

  let body, tokens, errors =
    match tokens with
    | (EqToken, eqPos) :: tokens -> parseSemi innerBasePos eqPos (tokens, errors)

    | _ -> parseExprError "Missing '='" (tokens, errors)

  let next, tokens, errors =
    match tokens with
    | (InToken, inPos) :: tokens when posInside letPos inPos -> parseSemi letPos inPos (tokens, errors)

    | _ :: _ when posIsSameColumn (nextPos tokens) letPos ->
        // Implicit `in` clause must be on the same column as `let`.
        parseSemi letPos (nextPos tokens) (tokens, errors)

    | tokens -> AExpr.TupleLit([], letPos), tokens, errors

  AExpr.Let(vis, pat, body, next, letPos), tokens, errors

let parseTyDecl typePos (tokens, errors) =
  let basePos = typePos |> posAddX 1

  let vis, tokens = parseVis tokens

  match tokens with
  | (IdentToken tyIdent, _) :: tokens ->
      match tokens with
      | (EqToken, _) :: tokens ->
          let tyDecl, tokens, errors = parseTyDeclBody basePos (tokens, errors)

          let expr =
            match tyDecl with
            | ATyDecl.Synonym ty -> AExpr.TySynonym(vis, tyIdent, ty, typePos)

            | ATyDecl.Union variants -> AExpr.TyUnion(vis, tyIdent, variants, typePos)

          expr, tokens, errors

      | _ ->
          let ty, tokens, errors =
            parseTyError "Expected '='" (tokens, errors)

          AExpr.TySynonym(vis, tyIdent, ty, typePos), tokens, errors

  | _ -> parseExprError "Expected identifier" (tokens, errors)

/// `open = 'open' ident ( '.' ident )*`
let parseOpen openPos (tokens, errors) =
  let parsePath (tokens, errors) =
    let rec go acc (tokens, errors) =
      match tokens with
      | (DotToken, _) :: (IdentToken ident, _) :: tokens -> go (ident :: acc) (tokens, errors)

      | (DotToken, _) :: tokens ->
          let errors =
            parseNewError "Expected identifier" (tokens, errors)

          listRev acc, tokens, errors

      | _ -> listRev acc, tokens, errors

    match tokens with
    | (IdentToken ident, _) :: tokens -> go [ ident ] (tokens, errors)

    | _ ->
        let errors =
          parseNewError "Expected identifier" (tokens, errors)

        [], tokens, errors

  let path, tokens, errors = parsePath (tokens, errors)
  AExpr.Open(path, openPos), tokens, errors

let parseAtom basePos (tokens, errors) =
  match tokens with
  | _ when not (nextInside basePos tokens) -> parseExprError "Expected an expression" (tokens, errors)

  | (LeftParenToken, pos) :: (RightParenToken, _) :: tokens -> AExpr.TupleLit([], pos), tokens, errors

  | (FalseToken, pos) :: tokens -> AExpr.Lit(BoolLit false, pos), tokens, errors

  | (TrueToken, pos) :: tokens -> AExpr.Lit(BoolLit true, pos), tokens, errors

  | (IntToken value, pos) :: tokens -> AExpr.Lit(IntLit value, pos), tokens, errors

  | (CharToken value, pos) :: tokens -> AExpr.Lit(CharLit value, pos), tokens, errors

  | (StrToken value, pos) :: tokens -> AExpr.Lit(StrLit value, pos), tokens, errors

  | (IdentToken ident, pos) :: tokens -> AExpr.Ident(ident, pos), tokens, errors

  | (LeftParenToken, parenPos) :: tokens -> parseParenBody basePos parenPos (tokens, errors)

  | (LeftBracketToken, bracketPos) :: tokens -> parseList basePos bracketPos (tokens, errors)

  | (IfToken, pos) :: tokens -> parseIf pos (tokens, errors)

  | (MatchToken, pos) :: tokens -> parseMatch pos (tokens, errors)

  | (FunToken, pos) :: tokens -> parseFun basePos pos (tokens, errors)

  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)

  | _ -> parseExprError "Expected an expression" (tokens, errors)

/// `suffix = atom ( '.' '[' range ']' | '.' ident )*`
let parseSuffix basePos (tokens, errors) =
  let l, tokens, errors = parseAtom basePos (tokens, errors)

  let rec go acc (tokens, errors) =
    match tokens with
    | (DotToken, pos) :: (LeftBracketToken, _) :: tokens ->
        let r, tokens, errors = parseRange basePos (tokens, errors)

        let tokens, errors =
          match tokens with
          | (RightBracketToken, _) :: tokens -> tokens, errors

          | _ ->
              let errors =
                parseNewError "Expected closing ']'" (tokens, errors)

              tokens, errors

        go (AExpr.Index(acc, r, pos)) (tokens, errors)

    | (DotToken, pos) :: (IdentToken r, _) :: tokens -> go (AExpr.Nav(acc, r, pos)) (tokens, errors)

    | (DotToken, _) :: tokens ->
        let errors =
          parseNewError "Expected .[] or .field" (tokens, errors)

        acc, tokens, errors

    | _ -> acc, tokens, errors

  go l (tokens, errors)

/// `app = suffix ( suffix )*`
let parseApp basePos (tokens, errors) =
  let calleePos = nextPos tokens
  let innerBasePos = basePos |> posAddX 1

  let callee, tokens, errors = parseSuffix basePos (tokens, errors)

  let rec go callee (tokens, errors) =
    if nextInside innerBasePos tokens && leadsArg tokens then
      let arg, tokens, errors = parseSuffix basePos (tokens, errors)
      go (AExpr.Bin(Op.App, callee, arg, calleePos)) (tokens, errors)
    else
      callee, tokens, errors

  go callee (tokens, errors)

/// `prefix = '-'? app`
let parsePrefix basePos (tokens, errors) =
  match tokens with
  | (MinusToken, pos) :: tokens ->
      let arg, tokens, errors = parseApp basePos (tokens, errors)
      AExpr.Uni(NegUnary, arg, pos), tokens, errors

  | _ -> parseApp basePos (tokens, errors)

let parseNextBp bp basePos (tokens, errors) =
  match bpNext bp with
  | PrefixBp -> parsePrefix basePos (tokens, errors)

  | nextBp -> parseOp nextBp basePos (tokens, errors)

let rec parseOps bp basePos first (tokens, errors) =
  let nextL expr op opPos (tokens, errors) =
    let second, tokens, errors =
      parseNextBp bp basePos (tokens, errors)

    let expr = AExpr.Bin(op, expr, second, opPos)
    parseOps bp basePos expr (tokens, errors)

  let nextR expr op opPos (tokens, errors) =
    let second, tokens, errors = parseOp bp basePos (tokens, errors)
    let expr = AExpr.Bin(op, expr, second, opPos)
    parseOps bp basePos expr (tokens, errors)

  match bp, tokens with
  | OrBp, (PipePipeToken, opPos) :: tokens -> nextL first Op.Or opPos (tokens, errors)

  | AndBp, (AmpAmpToken, opPos) :: tokens -> nextL first Op.And opPos (tokens, errors)

  | CmpBp, (EqToken, opPos) :: tokens -> nextL first Op.Eq opPos (tokens, errors)

  | CmpBp, (LeftRightToken, opPos) :: tokens -> nextL first Op.Ne opPos (tokens, errors)

  | CmpBp, (LeftAngleToken, opPos) :: tokens -> nextL first Op.Lt opPos (tokens, errors)

  | CmpBp, (LeftEqToken, opPos) :: tokens -> nextL first Op.Le opPos (tokens, errors)

  | CmpBp, (RightAngleToken, opPos) :: tokens -> nextL first Op.Gt opPos (tokens, errors)

  | CmpBp, (RightEqToken, opPos) :: tokens -> nextL first Op.Ge opPos (tokens, errors)

  | PipeBp, (PipeRightToken, opPos) :: tokens -> nextL first Op.Pipe opPos (tokens, errors)

  | ConsBp, (ColonColonToken, opPos) :: tokens -> nextR first Op.Cons opPos (tokens, errors)

  | AddBp, (PlusToken, opPos) :: tokens -> nextL first Op.Add opPos (tokens, errors)

  | AddBp, (MinusToken, opPos) :: tokens -> nextL first Op.Sub opPos (tokens, errors)

  | MulBp, (StarToken, opPos) :: tokens -> nextL first Op.Mul opPos (tokens, errors)

  | MulBp, (SlashToken, opPos) :: tokens -> nextL first Op.Div opPos (tokens, errors)

  | MulBp, (PercentToken, opPos) :: tokens -> nextL first Op.Mod opPos (tokens, errors)

  | _ -> first, tokens, errors

/// E.g. `add = mul ( ('+'|'-') mul )*`
let parseOp bp basePos (tokens, errors) =
  let first, tokens, errors =
    parseNextBp bp basePos (tokens, errors)

  parseOps bp basePos first (tokens, errors)

let parseTupleItem basePos (tokens, errors) =
  parseOp OrBp basePos (tokens, errors)

/// `tuple = item ( ',' item )*`
let parseTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (CommaToken, _) :: tokens ->
        let second, tokens, errors = parseTupleItem basePos (tokens, errors)
        go (second :: acc) (tokens, errors)

    | tokens -> listRev acc, tokens, errors

  let item, tokens, errors = parseTupleItem basePos (tokens, errors)

  match tokens with
  | (CommaToken, pos) :: _ ->
      let items, tokens, errors = go [] (tokens, errors)
      AExpr.TupleLit(item :: items, pos), tokens, errors

  | _ -> item, tokens, errors

/// `anno = tuple ( ':' ty )?`
let parseAnno basePos (tokens, errors) =
  let body, tokens, errors = parseTuple basePos (tokens, errors)

  match tokens with
  | (ColonToken, pos) :: tokens ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)
      AExpr.Anno(body, ty, pos), tokens, errors

  | _ -> body, tokens, errors

let parseExpr basePos (tokens, errors) = parseAnno basePos (tokens, errors)

let parseStmt basePos (tokens, errors) =
  match tokens with
  | (LetToken, letPos) :: (RecToken, _) :: tokens ->
      // FIXME: use `rec`
      parseLet letPos (tokens, errors)

  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)

  | (TypeToken, typePos) :: tokens -> parseTyDecl typePos (tokens, errors)

  | (OpenToken, typePos) :: tokens -> parseOpen typePos (tokens, errors)

  | _ -> parseExpr basePos (tokens, errors)

/// Parses a sequence of statements.
/// These statements must be aligned on the same column
/// except ones preceded by semicolon.
let rec parseStmts basePos (tokens, errors) =
  let rec go acc alignPos (tokens, errors) =
    match tokens with
    | (SemiToken, semiPos) :: tokens when posInside alignPos semiPos ->
        let expr, tokens, errors = parseStmt alignPos (tokens, errors)
        go (expr :: acc) alignPos (tokens, errors)

    | _ when posIsSameColumn alignPos (nextPos tokens)
             && leadsExpr tokens ->
        let expr, tokens, errors = parseStmt alignPos (tokens, errors)
        go (expr :: acc) alignPos (tokens, errors)

    | _ -> listRev acc, tokens, errors

  let alignPos = nextPos tokens
  if posInside basePos alignPos then go [] alignPos (tokens, errors) else [], tokens, errors

/// Parses a sequence of expressions separated by `;`s
/// or aligned on the same column.
/// Contents must be deeper than or equal to `basePos`,
/// which is typically the posation of `let`/`type`/`module`/etc.
/// The `mainPos` is a hint of the semi expression's posation.
/// `stmts = stmt ( ';' stmt )*`
let parseSemi basePos mainPos (tokens, errors) =
  let basePos = nextPos tokens |> posMax basePos
  let items, tokens, errors = parseStmts basePos (tokens, errors)

  match items with
  | [] -> parseExprError "Expected statements" (tokens, errors)

  | [ item ] -> item, tokens, errors

  | _ -> AExpr.Semi(items, mainPos), tokens, errors

/// `top-bp = ( 'module' 'rec'? path module-body / module-body )?`
let parseTopLevel (tokens, errors) =

  match tokens with
  | [] ->
      let pos = 0, 0
      ARoot.Expr(AExpr.TupleLit([], pos)), tokens, errors

  | (ModuleToken, modulePos) :: (RecToken, _) :: (IdentToken _, _) :: (DotToken, _) :: (IdentToken ident, _) :: tokens ->
      let expr, tokens, errors =
        parseSemi modulePos modulePos (tokens, errors)

      ARoot.Module(ident, expr, modulePos), tokens, errors

  | (ModuleToken, modulePos) :: (RecToken, _) :: (IdentToken ident, _) :: tokens ->
      let expr, tokens, errors =
        parseSemi modulePos modulePos (tokens, errors)

      ARoot.Module(ident, expr, modulePos), tokens, errors

  | (ModuleToken, modulePos) :: (IdentToken ident, _) :: tokens ->
      let expr, tokens, errors =
        parseSemi modulePos modulePos (tokens, errors)

      ARoot.Module(ident, expr, modulePos), tokens, errors

  | _ ->
      let pos = 0, 0
      let expr, tokens, errors = parseSemi pos pos (tokens, errors)
      ARoot.Expr expr, tokens, errors

let parse (tokens: (Token * Pos) list): ARoot * (string * Pos) list =
  let expr, tokens, errors = parseTopLevel (tokens, [])

  let errors =
    match tokens with
    | [] -> errors

    | _ -> parseNewError "Expected eof" (tokens, errors)

  expr, errors
