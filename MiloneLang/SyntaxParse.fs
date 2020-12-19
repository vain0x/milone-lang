/// ## SyntaxParse
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
///   - `match cond with | pat when guard -> body`
///     - `cond`, `pat` and `guard` are inner subterms
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
module rec MiloneLang.SyntaxParse

open MiloneLang.Util
open MiloneLang.Syntax

module Int = MiloneStd.StdInt

// -----------------------------------------------
// Position
// -----------------------------------------------

/// No position information. Should be fixed.
let private noPos = -1, -1

let private posX ((_, x): Pos) = x

let private posY ((y, _): Pos) = y

let private posIsSameRow first second = posY first = posY second

let private posIsSameColumn first second = posX first = posX second

/// Gets if `secondPos` is inside of the block of `firstPos`.
let private posInside (firstPos: Pos) (secondPos: Pos) = posX firstPos <= posX secondPos

let private posAddX dx ((y, x): Pos) = y, x + dx

let private posMax ((firstY, firstX): Pos) ((secondY, secondX): Pos) =
  Int.max firstY secondY, Int.max firstX secondX

/// Gets if three tokens can be merged. (Assuming each token is 1-letter.)
/// That is, no space or comments interleave these positions.
let private canMerge3 (pos1: Pos) pos2 pos3 =
  let y1, x1 = pos1
  let y2, x2 = pos2
  let y3, x3 = pos3
  y1 = y2 && y2 = y3 && x1 + 1 = x2 && x2 + 1 = x3

// -----------------------------------------------
// Bp
// -----------------------------------------------

/// Binding power.
///
/// See: <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/symbol-and-operator-reference/#operator-precedence>
[<NoEquality; NoComparison>]
type private Bp =
  | PrefixBp
  | MulBp
  | AddBp
  | ConsBp
  | XorBp
  | BitBp

  /// `|>`
  | PipeBp

  /// Comparison.
  | CmpBp

  | AndBp
  | OrBp

let private bpNext bp =
  match bp with
  | OrBp -> AndBp
  | AndBp -> CmpBp
  | CmpBp -> PipeBp
  | PipeBp -> BitBp
  | BitBp -> XorBp
  | XorBp -> ConsBp
  | ConsBp -> AddBp
  | AddBp -> MulBp

  | MulBp
  | PrefixBp -> PrefixBp

// -----------------------------------------------
// Tokens
// -----------------------------------------------

/// Gets whether a token can be the first of a pattern and an expression.
/// (Is it a member of the FIRST set of pat and expr?)
let private inFirstOfPatAndExpr (token: Token) =
  match token with
  | IntToken _
  | FloatToken _
  | CharToken _
  | StrToken _
  | IdentToken _
  | LeftParenToken
  | LeftBracketToken
  | LeftBraceToken
  | FalseToken
  | TrueToken -> true

  | _ -> false

/// Gets whether a token can be the first of a pattern.
let private inFirstOfPat (token: Token) = inFirstOfPatAndExpr token

/// Gets whether a token can be the first of an expression.
let private inFirstOfExpr (token: Token) =
  match token with
  | MinusToken
  | IfToken
  | MatchToken
  | FunToken
  | LetToken -> true

  | _ -> inFirstOfPatAndExpr token

/// In the FIRST set of arguments?
let private inFirstOfArg (token: Token) =
  match token with
  | MinusToken -> false

  | _ -> inFirstOfExpr token

let private inFirstOfDecl (token: Token) =
  match token with
  | TypeToken
  | OpenToken
  | ModuleToken
  | LeftAttrToken -> true

  | _ -> inFirstOfExpr token

let private leadsPat tokens =
  match tokens with
  | (token, _) :: _ -> inFirstOfPat token
  | _ -> false

let private leadsExpr tokens =
  match tokens with
  | (token, _) :: _ -> inFirstOfExpr token
  | _ -> false

let private leadsArg tokens =
  match tokens with
  | (token, _) :: _ -> inFirstOfArg token
  | _ -> false

let private leadsDecl tokens =
  match tokens with
  | (token, _) :: _ -> inFirstOfDecl token
  | _ -> false

/// Position of next token.
let private nextPos tokens: Pos =
  match tokens with
  | [] -> (-1, 0)

  | (_, pos) :: _ -> pos

/// Gets whether next token exists and it is not shallower than `basePos`.
let private nextInside basePos tokens: bool =
  match tokens with
  | [] -> false

  // Closed by something out of box.
  | (_, pos) :: _ when posInside basePos pos -> true

  | _ -> false

// -----------------------------------------------
// Errors
// -----------------------------------------------

let private parseErrorCore msg pos errors =
  let msg =
    "PARSE ERROR: "
    + msg
    + " ("
    + posToString pos
    + ")"

  (msg, pos) :: errors

let private parseTyError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingTy pos, tokens, errors

let private parsePatError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingPat pos, tokens, errors

let private parseExprError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingExpr pos, tokens, errors

let private parseDeclError msg (tokens, errors) =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  None, tokens, errors

let private parseNewError msg (tokens, errors) =
  let pos = nextPos tokens
  parseErrorCore msg pos errors

// -----------------------------------------------
// Eating
// -----------------------------------------------

let private expectRightParen (tokens, errors) =
  match tokens with
  | (RightParenToken, _) :: tokens -> tokens, errors
  | _ -> tokens, parseNewError "Expected ')'" (tokens, errors)

let private expectRightBracket (tokens, errors) =
  match tokens with
  | (RightBracketToken, _) :: tokens -> tokens, errors
  | _ -> tokens, parseNewError "Expected ']'" (tokens, errors)

let private expectRightBrace (tokens, errors) =
  match tokens with
  | (RightBraceToken, _) :: tokens -> tokens, errors
  | _ -> tokens, parseNewError "Expected '}'" (tokens, errors)

let private expectRightAngle (tokens, errors) =
  match tokens with
  | (RightAngleToken, _) :: tokens -> tokens, errors
  | _ -> tokens, parseNewError "Expected '>'" (tokens, errors)

let private expectRightAttr (tokens, errors) =
  match tokens with
  | (RightAttrToken, _) :: tokens -> tokens, errors
  | _ -> tokens, parseNewError "Expected '>]'" (tokens, errors)

let private eatRec tokens =
  match tokens with
  | (RecToken, _) :: tokens -> tokens
  | _ -> tokens

let private eatVis tokens =
  match tokens with
  | (PrivateToken, _) :: tokens -> PrivateVis, tokens
  | (PublicToken, _) :: tokens -> PublicVis, tokens
  | _ -> PublicVis, tokens

// -----------------------------------------------
// Parse types
// -----------------------------------------------

/// `'<' ty '>'`
let private parseTyArgs basePos (tokens, errors) =
  match tokens with
  | (LeftAngleToken, ltPos) :: tokens when posInside basePos ltPos ->
      let rec go acc (tokens, errors) =
        match tokens with
        | (CommaToken, _) :: tokens ->
            let argTy, tokens, errors = parseTy basePos (tokens, errors)
            go (argTy :: acc) (tokens, errors)

        | _ -> List.rev acc, tokens, errors

      let argTy, tokens, errors = parseTy basePos (tokens, errors)
      let argTys, tokens, errors = go [ argTy ] (tokens, errors)

      let tokens, errors = (tokens, errors) |> expectRightAngle

      argTys, tokens, errors

  | _ -> [], tokens, errors

/// `qual.ident <...>`
let private parseNavTy basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (IdentToken qual, _) :: (DotToken, _) :: tokens -> go (qual :: acc) (tokens, errors)

    | (IdentToken ident, pos) :: tokens ->
        let argTys, tokens, errors = parseTyArgs basePos (tokens, errors)
        AAppTy(List.rev acc, ident, argTys, pos), tokens, errors

    | _ ->
        let (_: ATy list), tokens, errors = parseTyArgs basePos (tokens, errors)
        parseTyError "Expected identifier" (tokens, errors)

  go [] (tokens, errors)

let private parseTyAtom basePos (tokens, errors) =
  match tokens with
  | _ when nextInside basePos tokens |> not -> parseTyError "Expected a type atom" (tokens, errors)

  | (IdentToken _, _) :: _ -> parseNavTy basePos (tokens, errors)

  | (TyVarToken name, pos) :: tokens -> AVarTy(name, pos), tokens, errors

  | (LeftParenToken, _) :: tokens ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)
      let tokens, errors = (tokens, errors) |> expectRightParen
      ty, tokens, errors

  | _ -> parseTyError "Expected a type atom" (tokens, errors)

/// `ty-suffix = ty-atom ( ident )*`
let private parseTySuffix basePos (tokens, errors) =
  let rec go (ty, tokens, errors) =
    let inside = nextInside basePos tokens
    match tokens with
    | (IdentToken ident, pos) :: tokens when inside -> go (ASuffixTy(ty, ident, pos), tokens, errors)

    | _ -> ty, tokens, errors

  parseTyAtom basePos (tokens, errors) |> go

/// `ty-tuple = ty-suffix ( '*' ty-suffix )*`
let private parseTyTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (StarToken, _) :: tokens ->
        let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)
        go (itemTy :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)

  match tokens with
  | (StarToken, opPos) :: _ ->
      let itemTys, tokens, errors = go [] (tokens, errors)
      ATupleTy(itemTy :: itemTys, opPos), tokens, errors

  | _ -> itemTy, tokens, errors

/// `ty-fun = ty-tuple ( '->' ty-fun )?`
let private parseTyFun basePos (tokens, errors) =
  let sTy, tokens, errors = parseTyTuple basePos (tokens, errors)

  match tokens with
  | (ArrowToken, opPos) :: tokens ->
      let tTy, tokens, errors = parseTyFun basePos (tokens, errors)
      AFunTy(sTy, tTy, opPos), tokens, errors

  | _ -> sTy, tokens, errors

let private parseTy basePos (tokens, errors) = parseTyFun basePos (tokens, errors)

// -----------------------------------------------
// Parse patterns
// -----------------------------------------------

let private parseNavPatBody head headPos (tokens, errors) =
  let rec go acc tokens =
    match tokens with
    | (DotToken, dotPos) :: (IdentToken ident, _) :: tokens -> go (ANavPat(acc, ident, dotPos)) tokens
    | _ -> acc, tokens, errors

  go (AIdentPat(head, headPos)) tokens

/// `pat ')'`
let private parsePatParenBody basePos (tokens, errors) =
  let pat, tokens, errors = parsePat basePos (tokens, errors)
  let tokens, errors = (tokens, errors) |> expectRightParen
  pat, tokens, errors

/// `pat ( ';' pat )* ']'`
let private parsePatListBody basePos bracketPos (tokens, errors) =
  let rec go patAcc (tokens, errors) =
    match tokens with
    | (RightBracketToken, _) :: tokens -> List.rev patAcc, tokens, errors

    // FIXME: Semicolon is required for now.
    | (SemiToken, _) :: tokens ->
        let pat, tokens, errors = parsePat basePos (tokens, errors)
        go (pat :: patAcc) (tokens, errors)

    | _ ->
        let errors =
          parseNewError "Expected ';' or ']'" (tokens, errors)

        List.rev patAcc, tokens, errors

  let itemPat, tokens, errors = parsePat basePos (tokens, errors)
  let itemPats, tokens, errors = go [ itemPat ] (tokens, errors)
  AListPat(itemPats, bracketPos), tokens, errors

let private parsePatAtom basePos (tokens, errors) =
  match tokens with
  | _ when not (nextInside basePos tokens && leadsPat tokens) ->
      parsePatError "Expected a pattern atom" (tokens, errors)

  | (IntToken text, pos) :: tokens -> ALitPat(IntLit text, pos), tokens, errors
  | (FloatToken text, pos) :: tokens -> ALitPat(FloatLit text, pos), tokens, errors
  | (CharToken value, pos) :: tokens -> ALitPat(CharLit value, pos), tokens, errors
  | (StrToken value, pos) :: tokens -> ALitPat(StrLit value, pos), tokens, errors

  | (IdentToken ident, pos) :: tokens -> parseNavPatBody ident pos (tokens, errors)

  | (LeftParenToken, pos) :: (RightParenToken, _) :: tokens -> ATuplePat([], pos), tokens, errors
  | (LeftParenToken, _) :: tokens -> parsePatParenBody basePos (tokens, errors)
  | (LeftBracketToken, pos) :: (RightBracketToken, _) :: tokens -> AListPat([], pos), tokens, errors
  | (LeftBracketToken, pos) :: tokens -> parsePatListBody basePos pos (tokens, errors)

  | (FalseToken, pos) :: tokens -> ALitPat(BoolLit false, pos), tokens, errors
  | (TrueToken, pos) :: tokens -> ALitPat(BoolLit true, pos), tokens, errors

  | _ -> parsePatError "NEVER: The token must be a pat" (tokens, errors)

/// `pat-nav = pat-atom ( '.' ident )?`
let private parsePatNav basePos (tokens, errors) =
  let pat, tokens, errors = parsePatAtom basePos (tokens, errors)

  match tokens with
  | (DotToken, pos) :: (IdentToken ident, _) :: tokens -> ANavPat(pat, ident, pos), tokens, errors

  | (DotToken, _) :: tokens -> parsePatError "Expected identifier" (tokens, errors)

  | _ -> pat, tokens, errors

let private parsePatCallArgs basePos (tokens, errors) =
  let innerBasePos = basePos |> posAddX 1

  let rec go acc (tokens, errors) =
    if nextInside innerBasePos tokens && leadsPat tokens then
      let expr, tokens, errors = parsePatNav basePos (tokens, errors)
      go (expr :: acc) (tokens, errors)
    else
      List.rev acc, tokens, errors

  go [] (tokens, errors)

/// `pat-app = pat-nav ( pat-nav )?`
let private parsePatApp basePos (tokens, errors) =
  let calleePos = nextPos tokens
  let callee, tokens, errors = parsePatNav basePos (tokens, errors)

  // Parse argument if exists.
  if nextInside (basePos |> posAddX 1) tokens
     && leadsPat tokens then
    let arg, tokens, errors = parsePatNav basePos (tokens, errors)
    AAppPat(callee, arg, calleePos), tokens, errors
  else
    callee, tokens, errors

/// `pat-cons = pat-call ( '::' pat-cons )?`
let private parsePatCons basePos (tokens, errors) =
  let head, tokens, errors = parsePatApp basePos (tokens, errors)

  match tokens with
  | (ColonColonToken, pos) :: tokens ->
      let tail, tokens, errors = parsePatCons basePos (tokens, errors)
      AConsPat(head, tail, pos), tokens, errors

  | _ -> head, tokens, errors

/// `pat-anno = pat-cons ( ':' ty )?`
let private parsePatAnno basePos (tokens, errors) =
  let pat, tokens, errors = parsePatCons basePos (tokens, errors)

  match tokens with
  | (ColonToken, pos) :: tokens ->
      let ty, tokens, errors =
        parseTy (nextPos tokens) (tokens, errors)

      AAnnoPat(pat, ty, pos), tokens, errors

  | _ -> pat, tokens, errors

/// `pat-tuple = pat-anno ( ',' pat-anno )*`
let private parsePatTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (CommaToken, _) :: tokens ->
        let second, tokens, errors = parsePatAnno basePos (tokens, errors)
        go (second :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let itemPat, tokens, errors = parsePatAnno basePos (tokens, errors)

  match tokens with
  | (CommaToken, pos) :: _ ->
      let itemPats, tokens, errors = go [] (tokens, errors)
      ATuplePat(itemPat :: itemPats, pos), tokens, errors

  | _ -> itemPat, tokens, errors

/// `pat-as = pat-tuple ( 'as' ident )?`
/// NOTE: The syntax of `as` patterns is more flexible in F#.
let private parsePatAs basePos (tokens, errors) =
  let pat, tokens, errors = parsePatTuple basePos (tokens, errors)

  match tokens with
  | (AsToken, pos) :: (IdentToken ident, _) :: tokens -> AAsPat(pat, ident, pos), tokens, errors

  | (AsToken, _) :: tokens ->
      let errors =
        parseNewError "Expected an identifier" (tokens, errors)

      pat, tokens, errors

  | _ -> pat, tokens, errors

/// `pat-or = pat ( '|' pat-or )?`
let private parsePatOr basePos (tokens, errors) =
  let lPat, tokens, errors = parsePatAs basePos (tokens, errors)

  match tokens with
  | (PipeToken, pos) :: tokens ->
      let rPat, tokens, errors = parsePatOr basePos (tokens, errors)
      AOrPat(lPat, rPat, pos), tokens, errors

  | _ -> lPat, tokens, errors

/// Parse a pattern of let expressions.
/// `pat-fun = ident pat-nav+ ( ':' ty )?`
/// `pat-let = pat-fun / pat`
let private parsePatLet basePos (tokens, errors) =
  match tokens with
  | (IdentToken callee, calleePos) :: tokens when posInside basePos calleePos && leadsPat tokens ->
      let args, tokens, errors =
        parsePatCallArgs basePos (tokens, errors)

      let pat = AFunDeclPat(callee, args, calleePos)

      match tokens with
      | (ColonToken, pos) :: tokens ->
          let ty, tokens, errors = parseTy basePos (tokens, errors)
          AAnnoPat(pat, ty, pos), tokens, errors

      | _ -> pat, tokens, errors

  | _ -> parsePat basePos (tokens, errors)

/// `pat = pat-or`
let private parsePat basePos (tokens, errors) =
  if not (nextInside basePos tokens && leadsPat tokens)
  then parsePatError "Expected a pattern" (tokens, errors)
  else parsePatOr basePos (tokens, errors)

// -----------------------------------------------
// Parse operator expressions
// -----------------------------------------------

/// `range = term ( '..' term )?`
let private parseRange basePos (tokens, errors) =
  let l, tokens, errors = parseExpr basePos (tokens, errors)

  match tokens with
  | (DotDotToken, pos) :: tokens ->
      let r, tokens, errors = parseExpr basePos (tokens, errors)
      ARangeExpr(l, r, pos), tokens, errors

  | _ -> l, tokens, errors

let private parseAtom basePos (tokens, errors) =
  match tokens with
  | _ when not (nextInside basePos tokens) -> parseExprError "Expected an expression" (tokens, errors)

  | (IntToken text, pos) :: tokens -> ALitExpr(IntLit text, pos), tokens, errors
  | (FloatToken text, pos) :: tokens -> ALitExpr(FloatLit text, pos), tokens, errors
  | (CharToken value, pos) :: tokens -> ALitExpr(CharLit value, pos), tokens, errors
  | (StrToken value, pos) :: tokens -> ALitExpr(StrLit value, pos), tokens, errors
  | (IdentToken ident, pos) :: tokens -> AIdentExpr(ident, pos), tokens, errors

  | (LeftParenToken, pos) :: (RightParenToken, _) :: tokens -> ATupleExpr([], pos), tokens, errors
  | (LeftParenToken, parenPos) :: tokens -> parseParenBody basePos parenPos (tokens, errors)
  | (LeftBracketToken, bracketPos) :: tokens -> parseList basePos bracketPos (tokens, errors)
  | (LeftBraceToken, bracePos) :: tokens -> parseRecordExpr bracePos (tokens, errors)

  | (FalseToken, pos) :: tokens -> ALitExpr(BoolLit false, pos), tokens, errors
  | (TrueToken, pos) :: tokens -> ALitExpr(BoolLit true, pos), tokens, errors

  | (IfToken, pos) :: tokens -> parseIf pos (tokens, errors)
  | (MatchToken, pos) :: tokens -> parseMatch pos (tokens, errors)
  | (FunToken, pos) :: tokens -> parseFun basePos pos (tokens, errors)
  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)

  | _ -> parseExprError "Expected an expression" (tokens, errors)

/// `suffix = atom ( '.' '[' range ']' | '.' ident )*`
let private parseSuffix basePos (tokens, errors) =
  let l, tokens, errors = parseAtom basePos (tokens, errors)

  let rec go acc (tokens, errors) =
    match tokens with
    | (DotToken, pos) :: (LeftBracketToken, _) :: tokens ->
        let r, tokens, errors = parseRange basePos (tokens, errors)
        let tokens, errors = (tokens, errors) |> expectRightBracket

        go (AIndexExpr(acc, r, pos)) (tokens, errors)

    | (DotToken, pos) :: (IdentToken r, _) :: tokens -> go (ANavExpr(acc, r, pos)) (tokens, errors)

    | (DotToken, _) :: tokens ->
        let errors =
          parseNewError "Expected .[] or .field" (tokens, errors)

        acc, tokens, errors

    | _ -> acc, tokens, errors

  go l (tokens, errors)

/// `app = suffix ( suffix )*`
let private parseApp basePos (tokens, errors) =
  let calleePos = nextPos tokens
  let innerBasePos = basePos |> posAddX 1

  let callee, tokens, errors = parseSuffix basePos (tokens, errors)

  let rec go callee (tokens, errors) =
    if nextInside innerBasePos tokens && leadsArg tokens then
      let arg, tokens, errors = parseSuffix basePos (tokens, errors)
      go (ABinaryExpr(AppBinary, callee, arg, calleePos)) (tokens, errors)
    else
      callee, tokens, errors

  go callee (tokens, errors)

/// `prefix = '-'? app`
let private parsePrefix basePos (tokens, errors) =
  match tokens with
  | (MinusToken, pos) :: tokens ->
      let arg, tokens, errors = parseApp basePos (tokens, errors)
      AUnaryExpr(NegUnary, arg, pos), tokens, errors

  | _ -> parseApp basePos (tokens, errors)

let private parseNextBp bp basePos (tokens, errors) =
  match bpNext bp with
  | PrefixBp -> parsePrefix basePos (tokens, errors)

  | nextBp -> parseOp nextBp basePos (tokens, errors)

let private parseOps bp basePos first (tokens, errors) =
  let nextL expr op opPos (tokens, errors) =
    let second, tokens, errors = parseNextBp bp basePos (tokens, errors)

    let expr = ABinaryExpr(op, expr, second, opPos)
    parseOps bp basePos expr (tokens, errors)

  let nextR expr op opPos (tokens, errors) =
    let second, tokens, errors = parseOp bp basePos (tokens, errors)
    let expr = ABinaryExpr(op, expr, second, opPos)
    parseOps bp basePos expr (tokens, errors)

  match bp, tokens with
  | OrBp, (PipePipeToken, opPos) :: tokens -> nextL first LogOrBinary opPos (tokens, errors)

  | AndBp, (AmpAmpToken, opPos) :: tokens -> nextL first LogAndBinary opPos (tokens, errors)

  | CmpBp, (EqToken, opPos) :: tokens -> nextL first EqualBinary opPos (tokens, errors)
  | CmpBp, (LeftRightToken, opPos) :: tokens -> nextL first NotEqualBinary opPos (tokens, errors)
  | CmpBp, (LeftAngleToken, opPos) :: tokens -> nextL first LessBinary opPos (tokens, errors)
  | CmpBp, (LeftEqToken, opPos) :: tokens -> nextL first LessEqualBinary opPos (tokens, errors)
  | CmpBp, (RightAngleToken, opPos) :: tokens -> nextL first GreaterBinary opPos (tokens, errors)
  | CmpBp, (RightEqToken, opPos) :: tokens -> nextL first GreaterEqualBinary opPos (tokens, errors)

  | PipeBp, (PipeRightToken, opPos) :: tokens -> nextL first PipeBinary opPos (tokens, errors)

  | XorBp, (HatHatHatToken, opPos) :: tokens -> nextR first BitXorBinary opPos (tokens, errors)

  | BitBp, (AmpAmpAmpToken, opPos) :: tokens -> nextL first BitAndBinary opPos (tokens, errors)
  | BitBp, (PipePipePipeToken, opPos) :: tokens -> nextL first BitOrBinary opPos (tokens, errors)
  | BitBp, (LeftLeftLeftToken, opPos) :: tokens -> nextL first LeftShiftBinary opPos (tokens, errors)
  | BitBp, (RightAngleToken, opPos) :: (RightAngleToken, pos2) :: (RightAngleToken, pos3) :: tokens when canMerge3
                                                                                                           opPos
                                                                                                           pos2
                                                                                                           pos3 ->
      nextL first RightShiftBinary opPos (tokens, errors)

  | ConsBp, (ColonColonToken, opPos) :: tokens -> nextR first ConsBinary opPos (tokens, errors)

  | AddBp, (PlusToken, opPos) :: tokens -> nextL first AddBinary opPos (tokens, errors)
  | AddBp, (MinusToken, opPos) :: tokens -> nextL first SubBinary opPos (tokens, errors)

  | MulBp, (StarToken, opPos) :: tokens -> nextL first MulBinary opPos (tokens, errors)
  | MulBp, (SlashToken, opPos) :: tokens -> nextL first DivBinary opPos (tokens, errors)
  | MulBp, (PercentToken, opPos) :: tokens -> nextL first ModBinary opPos (tokens, errors)

  | _ -> first, tokens, errors

/// E.g. `add = mul ( ('+'|'-') mul )*`
let private parseOp bp basePos (tokens, errors) =
  let first, tokens, errors = parseNextBp bp basePos (tokens, errors)

  parseOps bp basePos first (tokens, errors)

let private parseTupleItem basePos (tokens, errors) = parseOp OrBp basePos (tokens, errors)

/// `tuple = item ( ',' item )*`
let private parseTuple basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (CommaToken, _) :: tokens ->
        let second, tokens, errors = parseTupleItem basePos (tokens, errors)
        go (second :: acc) (tokens, errors)

    | tokens -> List.rev acc, tokens, errors

  let item, tokens, errors = parseTupleItem basePos (tokens, errors)

  match tokens with
  | (CommaToken, pos) :: _ ->
      let items, tokens, errors = go [] (tokens, errors)
      ATupleExpr(item :: items, pos), tokens, errors

  | _ -> item, tokens, errors

/// `anno = tuple ( ':' ty )?`
let private parseAnno basePos (tokens, errors) =
  let body, tokens, errors = parseTuple basePos (tokens, errors)

  match tokens with
  | (ColonToken, pos) :: tokens ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)
      AAnnoExpr(body, ty, pos), tokens, errors

  | _ -> body, tokens, errors

let private parseExpr basePos (tokens, errors) = parseAnno basePos (tokens, errors)

// -----------------------------------------------
// Parse block expressions
// -----------------------------------------------

let private parseParenBody basePos _parenPos (tokens, errors) =
  // NOTE: Parens should form a layout block but not for now.
  //  If does, `(` in `xs |> List.map (fun x -> body)` unexpectedly requires
  //  `body` to be deeper than it. This is one of flaws of the simplified layout rule.
  let body, tokens, errors = parseExpr basePos (tokens, errors)
  let tokens, errors = (tokens, errors) |> expectRightParen
  body, tokens, errors

let private parseList basePos bracketPos (tokens, errors) =
  let items, tokens, errors = parseItems basePos (tokens, errors)
  let tokens, errors = (tokens, errors) |> expectRightBracket
  AListExpr(items, bracketPos), tokens, errors

let private parseRecordExpr bracePos (tokens, errors) =
  let rec go acc alignPos (tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> List.rev acc, tokens, errors

    | (SemiToken, _) :: tokens -> go acc (nextPos tokens) (tokens, errors)

    | (IdentToken ident, fieldPos) :: (EqToken, _) :: tokens when fieldPos |> posIsSameColumn alignPos ->
        let init, tokens, errors =
          parseExpr (fieldPos |> posAddX 1) (tokens, errors)

        go ((ident, init, fieldPos) :: acc) alignPos (tokens, errors)

    | (_, pos) :: tokens when pos |> posInside alignPos ->
        let errors =
          parseErrorCore "Expected 'field = expr'." pos errors

        go acc alignPos (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let baseOpt, (fields, tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> None, ([], tokens, errors)

    | (IdentToken _, _) :: (EqToken, _) :: _ -> None, go [] (nextPos tokens) (tokens, errors)

    | _ ->
        let baseExpr, tokens, errors =
          parseExpr (nextPos tokens) (tokens, errors)

        let tokens, errors =
          match tokens with
          | (WithToken, _) :: tokens -> tokens, errors

          | _ ->
              let errors =
                parseErrorCore "Expected 'with' keyword." (nextPos tokens) errors

              tokens, errors

        Some baseExpr, go [] (nextPos tokens) (tokens, errors)

  let tokens, errors = (tokens, errors) |> expectRightBrace

  ARecordExpr(baseOpt, fields, bracePos), tokens, errors

let private parseThenClause basePos (tokens, errors) =
  let innerBasePos = basePos |> posAddX 1

  match tokens with
  | (ThenToken, thenPos) :: tokens when posInside basePos thenPos -> parseSemi innerBasePos thenPos (tokens, errors)

  | _ -> parseExprError "Expected 'then'" (tokens, errors)

let private parseElseClause basePos (tokens, errors) =
  match tokens with
  | (ElseToken, elsePos) :: (IfToken, nextIfPos) :: tokens when posInside basePos elsePos
                                                                && posIsSameRow elsePos nextIfPos ->
      // ELSE_IF_LAYOUT rule. Parse the next as if `if` in `else if` is placed where `else` is.
      let alt, tokens, errors =
        parseExpr basePos ((IfToken, elsePos) :: tokens, errors)

      Some alt, tokens, errors

  | (ElseToken, elsePos) :: tokens when posInside basePos elsePos ->
      let alt, tokens, errors =
        parseSemi basePos elsePos (tokens, errors)

      Some alt, tokens, errors

  | _ -> None, tokens, errors

let private parseIf ifPos (tokens, errors) =
  let innerBasePos = ifPos |> posAddX 1

  let cond, tokens, errors = parseExpr innerBasePos (tokens, errors)
  let body, tokens, errors = parseThenClause ifPos (tokens, errors)
  let altOpt, tokens, errors = parseElseClause ifPos (tokens, errors)
  AIfExpr(cond, body, altOpt, ifPos), tokens, errors

/// `pat ( 'when' expr )? -> expr`
let private parseMatchArm matchPos armPos (tokens, errors) =
  let innerBasePos = matchPos |> posAddX 1

  let pat, tokens, errors = parsePat innerBasePos (tokens, errors)

  let guardOpt, tokens, errors =
    match tokens with
    | (WhenToken, _) :: tokens ->
        let guard, tokens, errors = parseExpr innerBasePos (tokens, errors)
        Some guard, tokens, errors

    | _ -> None, tokens, errors

  let body, tokens, errors =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> parseSemi matchPos arrowPos (tokens, errors)

    | _ -> parseExprError "Expected '->'" (tokens, errors)

  AArm(pat, guardOpt, body, armPos), tokens, errors

let private parseMatch matchPos (tokens, errors) =
  let cond, tokens, errors = parseExpr matchPos (tokens, errors)

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

    | _ -> List.rev (arm :: acc), tokens, errors

  let arms, tokens, errors = go [] armPos (tokens, errors)
  AMatchExpr(cond, arms, matchPos), tokens, errors

/// `fun-expr = 'fun' pat* '->' expr`
let private parseFun basePos funPos (tokens, errors) =
  let pats, tokens, errors =
    parsePatCallArgs basePos (tokens, errors)

  let body, tokens, errors =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> parseSemi basePos arrowPos (tokens, errors)

    | _ -> parseExprError "Missing '->'" (tokens, errors)

  AFunExpr(pats, body, funPos), tokens, errors

// -----------------------------------------------
// Parse binding statements
// -----------------------------------------------

let private parseLet letPos (tokens, errors) =
  let innerBasePos = letPos |> posAddX 1

  let vis, tokens = eatVis tokens

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

    | tokens -> ATupleExpr([], letPos), tokens, errors

  ALetExpr(vis, pat, body, next, letPos), tokens, errors


/// `payload-ty = labeled-ty ( '*' labeled-ty )*`
/// `labeled-ty = ( ident ':' )? ty-suffix`
let private parsePayloadTy basePos (tokens, errors) =
  let eatLabel tokens =
    match tokens with
    | (IdentToken _, _) :: (ColonToken, _) :: tokens -> tokens
    | _ -> tokens

  let pos = nextPos tokens

  // parse first
  let tokens = eatLabel tokens
  let firstTy, tokens, errors = parseTySuffix basePos (tokens, errors)

  // parse second or more
  let rec go acc (tokens, errors) =
    match tokens with
    | (StarToken, _) :: tokens ->
        let tokens = eatLabel tokens
        let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)
        go (itemTy :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let itemTys, tokens, errors = go [ firstTy ] (tokens, errors)

  match itemTys with
  | [ itemTy ] -> itemTy, tokens, errors
  | _ -> ATupleTy(itemTys, pos), tokens, errors

/// Parses the body of union `type` declaration.
let private parseTyDeclUnion basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (PipeToken, _) :: (IdentToken variantIdent, pos) :: (OfToken, _) :: tokens ->
        let payloadTy, tokens, errors = parsePayloadTy basePos (tokens, errors)
        go (AVariant(variantIdent, Some payloadTy, pos) :: acc) (tokens, errors)

    | (PipeToken, _) :: (IdentToken variantIdent, pos) :: tokens ->
        go (AVariant(variantIdent, None, pos) :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let variants, tokens, errors = go [] (tokens, errors)
  AUnionTyDeclBody variants, tokens, errors

/// Parses the body of record type declaration.
let private parseTyDeclRecord basePos (tokens, errors) =
  let rec go acc alignPos (tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> List.rev acc, tokens, errors

    | (SemiToken, _) :: tokens -> go acc (nextPos tokens) (tokens, errors)

    | (IdentToken ident, fieldPos) :: (ColonToken, _) :: tokens when fieldPos |> posIsSameColumn alignPos ->
        let ty, tokens, errors =
          parseTy (fieldPos |> posAddX 1) (tokens, errors)

        go ((ident, ty, fieldPos) :: acc) alignPos (tokens, errors)

    | (_, pos) :: tokens when pos |> posInside basePos ->
        let errors =
          parseErrorCore "Expected a field declaration." pos errors

        go acc alignPos (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let fields, tokens, errors =
    let alignPos = nextPos tokens
    go [] alignPos (tokens, errors)

  let tokens, errors = (tokens, errors) |> expectRightBrace

  ARecordTyDeclBody fields, tokens, errors

/// Parses after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let private parseTyDeclBody basePos (tokens, errors) =
  match tokens with
  | (PipeToken, _) :: _ -> parseTyDeclUnion basePos (tokens, errors)

  | (IdentToken _, _) :: (OfToken, _) :: _ ->
      let tokens = (PipeToken, noPos) :: tokens
      parseTyDeclUnion basePos (tokens, errors)

  | (LeftBraceToken, _) :: tokens -> parseTyDeclRecord basePos (tokens, errors)

  | _ ->
      let ty, tokens, errors = parseTy basePos (tokens, errors)
      ATySynonymDeclBody ty, tokens, errors

let private parseStmt basePos (tokens, errors) =
  match tokens with
  | (LetToken, letPos) :: (RecToken, _) :: tokens ->
      // FIXME: use `rec`
      parseLet letPos (tokens, errors)

  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)

  | _ -> parseExpr basePos (tokens, errors)

/// Parses a sequence of statements.
/// These statements must be aligned on the same column
/// except ones preceded by semicolon.
///
/// Returns last and non-last statements in reversed order.
let private doParseStmts basePos (tokens, errors) =
  let rec go last acc alignPos (tokens, errors) =
    match tokens with
    | (SemiToken, semiPos) :: tokens when posInside alignPos semiPos ->
        let expr, tokens, errors = parseStmt alignPos (tokens, errors)
        go expr (last :: acc) alignPos (tokens, errors)

    | _ when posIsSameColumn alignPos (nextPos tokens)
             && leadsExpr tokens ->
        let expr, tokens, errors = parseStmt alignPos (tokens, errors)
        go expr (last :: acc) alignPos (tokens, errors)

    | _ -> Some(last, acc), tokens, errors

  let alignPos = nextPos tokens
  if posInside basePos alignPos && leadsExpr tokens then
    let first, tokens, errors = parseStmt alignPos (tokens, errors)
    go first [] alignPos (tokens, errors)
  else
    None, tokens, errors

/// Parses a sequence of expressions separated by `;`s
/// or aligned on the same column.
/// Contents must be deeper than or equal to `basePos`,
/// which is typically the pos of `let`/`type`/`module`/etc.
/// The `mainPos` is a hint of the semi expression's pos.
/// `stmts = stmt ( ';' stmt )*`
let private parseSemi basePos mainPos (tokens, errors) =
  let basePos = nextPos tokens |> posMax basePos
  let contents, tokens, errors = doParseStmts basePos (tokens, errors)
  match contents with
  | None -> parseExprError "Expected statements" (tokens, errors)
  | Some (last, acc) -> ASemiExpr(List.rev acc, last, mainPos), tokens, errors

let private parseItems basePos (tokens, errors) =
  let contents, tokens, errors = doParseStmts basePos (tokens, errors)
  match contents with
  | Some (last, acc) -> List.rev (last :: acc), tokens, errors
  | None -> [], tokens, errors

// -----------------------------------------------
// Parse declarations
// -----------------------------------------------

let private parseLetDecl letPos (tokens, errors) =
  let innerBasePos = letPos |> posAddX 1

  let tokens = eatRec tokens
  let vis, tokens = eatVis tokens

  let pat, tokens, errors =
    parsePatLet innerBasePos (tokens, errors)

  let init, tokens, errors =
    match tokens with
    | (EqToken, equalPos) :: tokens -> parseSemi innerBasePos equalPos (tokens, errors)
    | _ -> parseExprError "Missing '='" (tokens, errors)

  Some(ALetDecl(vis, pat, init, letPos)), tokens, errors

let private parseTyDecl typePos (tokens, errors) =
  let basePos = typePos |> posAddX 1

  let vis, tokens = eatVis tokens

  match tokens with
  | (IdentToken tyIdent, _) :: (LeftAngleToken, _) :: tokens ->
      let rec go acc tokens =
        match tokens with
        | (TyVarToken ident, _) :: tokens ->
            let acc = ident :: acc

            match tokens with
            | (CommaToken, _) :: tokens -> go acc tokens

            | (RightAngleToken, _) :: tokens -> List.rev acc, None, tokens

            | _ -> List.rev acc, Some "Expected '>'.", tokens

        | _ -> List.rev acc, Some "Expected type variable.", tokens

      match go [] tokens with
      | _, Some msg, tokens -> parseDeclError msg (tokens, errors)

      | tyArgs, None, tokens ->
          let ty, tokens, errors =
            match tokens with
            | (EqToken, _) :: tokens -> parseTy basePos (tokens, errors)
            | _ -> parseTyError "Expected '='." (tokens, errors)

          Some(ATySynonymDecl(vis, tyIdent, tyArgs, ty, typePos)), tokens, errors

  | (IdentToken tyIdent, _) :: tokens ->
      match tokens with
      | (EqToken, _) :: tokens ->
          let tyDecl, tokens, errors = parseTyDeclBody basePos (tokens, errors)

          let decl =
            match tyDecl with
            | ATySynonymDeclBody ty -> ATySynonymDecl(vis, tyIdent, [], ty, typePos)
            | AUnionTyDeclBody variants -> AUnionTyDecl(vis, tyIdent, variants, typePos)
            | ARecordTyDeclBody fields -> ARecordTyDecl(vis, tyIdent, fields, typePos)

          Some decl, tokens, errors

      | _ ->
          let ty, tokens, errors =
            parseTyError "Expected '='" (tokens, errors)

          Some(ATySynonymDecl(vis, tyIdent, [], ty, typePos)), tokens, errors

  | _ -> parseDeclError "Expected identifier" (tokens, errors)

let private parsePath (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | (DotToken, _) :: (IdentToken ident, _) :: tokens -> go (ident :: acc) (tokens, errors)

    | (DotToken, _) :: tokens ->
        let errors =
          parseNewError "Expected identifier" (tokens, errors)

        List.rev acc, tokens, errors

    | _ -> List.rev acc, tokens, errors

  match tokens with
  | (IdentToken ident, _) :: tokens -> go [ ident ] (tokens, errors)

  | _ ->
      let errors =
        parseNewError "Expected identifier" (tokens, errors)

      [], tokens, errors

/// `open = 'open' ident ( '.' ident )*`
let private parseOpenDecl openPos (tokens, errors) =
  let path, tokens, errors = parsePath (tokens, errors)
  Some(AOpenDecl(path, openPos)), tokens, errors

let private parseModuleDecl modulePos (tokens, errors) =
  let moduleName, tokens, errors =
    match tokens with
    | (IdentToken moduleName, _) :: tokens -> moduleName, tokens, errors
    | _ ->
        let errors =
          parseNewError "Expected identifier" (tokens, errors)

        "_", tokens, errors

  let path, tokens, errors =
    match tokens with
    | (EqToken, _) :: tokens -> parsePath (tokens, errors)
    | _ ->
        let errors =
          parseNewError "Expected '='" (tokens, errors)

        [], tokens, errors

  Some(AModuleSynonymDecl(moduleName, path, modulePos)), tokens, errors

let private parseAttrDecl basePos (tokens, errors) =
  let contents, tokens, errors =
    parseSemi basePos basePos (tokens, errors)

  let tokens, errors = (tokens, errors) |> expectRightAttr

  if tokens
     |> nextPos
     |> posIsSameColumn basePos
     |> not then
    parseDeclError "Expected a declaration after attribute." (tokens, errors)
  else
    let declOpt, tokens, errors = parseDecl basePos (tokens, errors)
    match declOpt with
    | Some decl -> Some(AAttrDecl(contents, decl, basePos)), tokens, errors
    | None -> None, tokens, errors

let private parseDecl basePos (tokens, errors) =
  match tokens with
  | (LeftAttrToken, pos) :: tokens -> parseAttrDecl pos (tokens, errors)
  | (LetToken, letPos) :: tokens -> parseLetDecl letPos (tokens, errors)
  | (TypeToken, typePos) :: tokens -> parseTyDecl typePos (tokens, errors)
  | (OpenToken, typePos) :: tokens -> parseOpenDecl typePos (tokens, errors)
  | (ModuleToken, modulePos) :: tokens -> parseModuleDecl modulePos (tokens, errors)

  | _ ->
      let exprOpt, tokens, errors = parseExpr basePos (tokens, errors)
      match exprOpt with
      | AMissingExpr _ -> None, tokens, errors
      | expr -> Some(AExprDecl expr), tokens, errors

let private parseModuleBody basePos (tokens, errors) =
  let rec go acc (tokens, errors) =
    match tokens with
    | _ when nextInside basePos tokens |> not -> List.rev acc, tokens, errors

    | _ ->
        // error if unaligned
        let declOpt, tokens, errors = parseDecl basePos (tokens, errors)
        match declOpt with
        | Some decl -> go (decl :: acc) (tokens, errors)
        | None -> List.rev acc, tokens, errors

  go [] (tokens, errors)

// -----------------------------------------------
// Parse toplevel
// -----------------------------------------------

/// `top-level = ( 'module' 'rec'? path module-body / module-body )?`
let private parseTopLevel (tokens, errors) =
  match tokens with
  | [] -> AExprRoot [], tokens, errors

  | (ModuleToken, modulePos) :: (RecToken, _) :: (IdentToken _, _) :: (DotToken, _) :: (IdentToken ident, _) :: tokens ->
      let decls, tokens, errors =
        parseModuleBody modulePos (tokens, errors)

      AModuleRoot(ident, decls, modulePos), tokens, errors

  | (ModuleToken, modulePos) :: (RecToken, _) :: (IdentToken ident, _) :: tokens ->
      let decls, tokens, errors =
        parseModuleBody modulePos (tokens, errors)

      AModuleRoot(ident, decls, modulePos), tokens, errors

  | (ModuleToken, _) :: tokens ->
      let errors =
        parseNewError
          "module syntax error. Hint: `module rec ProjectName.ModuleName`. (rec keyword is mandatory for now.)"
          (tokens, errors)

      AExprRoot [], [], errors

  | _ ->
      let pos = 0, 0
      let exprs, tokens, errors = parseModuleBody pos (tokens, errors)
      AExprRoot exprs, tokens, errors

let parse (tokens: (Token * Pos) list): ARoot * (string * Pos) list =
  let expr, tokens, errors = parseTopLevel (tokens, [])

  let errors =
    match tokens with
    | [] -> errors

    | _ -> parseNewError "Expected eof" (tokens, errors)

  expr, errors
