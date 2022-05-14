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
module rec MiloneSyntax.SyntaxParse

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError

module Int = Std.StdInt

let private newIntLit text flavorOpt =
  match flavorOpt with
  | None -> IntLit text
  | Some flavor -> IntLitWithFlavor(text, flavor)

// -----------------------------------------------
// Position
// -----------------------------------------------

/// No position information. Should be fixed.
let private noPos = -1, -1

let private posX ((_, x): Pos) = x

let private posY ((y, _): Pos) = y

let private posIsSameRow l r = posY l = posY r

let private posIsSameColumn l r = posX l = posX r

/// Gets if `r` is inside of the block of `l`.
let private posInside (l: Pos) (r: Pos) = posX l <= posX r

let private posAddX dx ((y, x): Pos) = y, x + dx

let private posMax ((lY, lX): Pos) ((rY, rX): Pos) = Int.max lY rY, Int.max lX rX

let private posPrev ((y, x): Pos) : Pos =
  if x <> 0 then y, x - 1
  else if y >= 1 then (y - 1), x
  else 0, 0

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

  /// `<`, `>`, `=`, `|>`, `|||`, `&&&`
  | SigilBp

  | AndBp
  | OrBp

let private bpNext bp =
  match bp with
  | OrBp -> AndBp
  | AndBp -> SigilBp
  | SigilBp -> XorBp
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
  | StringToken _
  | IdentToken _
  | LeftParenToken
  | LeftBracketToken
  | LeftBraceToken
  | FalseToken
  | MinusToken _
  | TrueToken -> true

  | _ -> false

/// Gets whether a token can be the first of a pattern.
let private inFirstOfPat (token: Token) =
  match token with
  | PublicToken
  | PrivateToken -> true

  | _ -> inFirstOfPatAndExpr token

/// Gets whether a token can be the first of an expression.
let private inFirstOfExpr (token: Token) =
  match token with
  | AmpAmpToken _
  | IfToken
  | MatchToken
  | FunToken
  | LetToken -> true

  | _ -> inFirstOfPatAndExpr token

/// In the FIRST set of arguments?
let private inFirstOfArg (token: Token) =
  match token with
  | MinusToken false
  | AmpAmpToken false -> false

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
let private nextPos tokens : Pos =
  match tokens with
  | [] -> (-1, 0)

  | (_, pos) :: _ -> pos

/// Gets whether next token exists and it is not shallower than `basePos`.
let private nextInside basePos tokens : bool =
  match tokens with
  | [] -> false

  // Closed by something out of box.
  | (_, pos) :: _ when posInside basePos pos -> true

  | _ -> false

// -----------------------------------------------
// Errors
// -----------------------------------------------

type private Tokens = (Token * Pos) list
type private Errors = (string * Pos) list

/// Parse result.
type private PR<'T> = 'T * Tokens * Errors

let private parseErrorCore msg pos errors : Errors =
  let msg =
    "PARSE ERROR: "
    + msg
    + " ("
    + Pos.toString pos
    + ")"

  (msg, pos) :: errors

let private parseTyError msg (tokens, errors) : ATy * Tokens * Errors =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingTy pos, tokens, errors

let private parsePatError msg (tokens, errors) : APat * Tokens * Errors =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingPat pos, tokens, errors

let private parseExprError msg (tokens, errors) : AExpr * Tokens * Errors =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  AMissingExpr pos, tokens, errors

let private parseDeclError msg (tokens, errors) : ADecl option * Tokens * Errors =
  let pos = nextPos tokens
  let errors = parseErrorCore msg pos errors
  None, tokens, errors

let private parseNewError msg (tokens, errors) : Errors =
  let pos = nextPos tokens
  parseErrorCore msg pos errors

// -----------------------------------------------
// Eating
// -----------------------------------------------

let private expectRightParen (tokens, errors) : Pos option * Tokens * Errors =
  match tokens with
  | (RightParenToken, pos) :: tokens -> Some pos, tokens, errors
  | _ -> None, tokens, parseNewError "Expected ')'" (tokens, errors)

let private expectRightBracket (tokens, errors) : Pos option * Tokens * Errors =
  match tokens with
  | (RightBracketToken, pos) :: tokens -> Some pos, tokens, errors
  | _ -> None, tokens, parseNewError "Expected ']'" (tokens, errors)

let private expectRightBrace (tokens, errors) : Pos option * Tokens * Errors =
  match tokens with
  | (RightBraceToken, pos) :: tokens -> Some pos, tokens, errors
  | _ -> None, tokens, parseNewError "Expected '}'" (tokens, errors)

let private expectRightAngle (tokens, errors) : Pos option * Tokens * Errors =
  match tokens with
  | (RightAngleToken, pos) :: tokens -> Some pos, tokens, errors
  | _ -> None, tokens, parseNewError "Expected '>'" (tokens, errors)

let private expectRightAttr (tokens, errors) : Pos option * Tokens * Errors =
  match tokens with
  | (RightAttrToken, pos) :: tokens -> Some pos, tokens, errors
  | _ -> None, tokens, parseNewError "Expected '>]'" (tokens, errors)

let private eatRec tokens : IsRec * Tokens =
  match tokens with
  | (RecToken, _) :: tokens -> IsRec, tokens
  | _ -> NotRec, tokens

let private eatVis tokens : Vis * Tokens =
  match tokens with
  | (PrivateToken, _) :: tokens -> PrivateVis, tokens
  | (PublicToken, _) :: tokens -> PublicVis, tokens
  | _ -> PublicVis, tokens

// -----------------------------------------------
// Name
// -----------------------------------------------

let private behindName name : Pos =
  let (Name (ident, (y, x))) = name
  y, x + ident.Length

// -----------------------------------------------
// Parse types
// -----------------------------------------------

/// `'<' ty '>'`
let private parseTyArgs basePos (tokens, errors) : PR<ATyArgList option> =
  match tokens with
  | (LeftAngleToken true, lPos) :: tokens when posInside basePos lPos ->
    let rec go acc (tokens, errors) =
      match tokens with
      | (CommaToken, _) :: tokens ->
        let argTy, tokens, errors = parseTy basePos (tokens, errors)
        go (argTy :: acc) (tokens, errors)

      | _ -> List.rev acc, tokens, errors

    let argTy, tokens, errors = parseTy basePos (tokens, errors)
    let argTys, tokens, errors = go [ argTy ] (tokens, errors)
    let rOpt, tokens, errors = (tokens, errors) |> expectRightAngle
    Some(lPos, argTys, rOpt), tokens, errors

  | _ -> None, tokens, errors

/// `qual.ident <...>`
let private parseNavTy basePos (tokens, errors) : PR<ATy> =
  let rec go acc (tokens, errors) =
    match tokens with
    | (IdentToken qual, qualPos) :: (DotToken, dot) :: tokens -> go ((Name(qual, qualPos), dot) :: acc) (tokens, errors)

    | (IdentToken ident, pos) :: tokens ->
      let tyArgListOpt, tokens, errors = parseTyArgs basePos (tokens, errors)
      AAppTy(List.rev acc, Name(ident, pos), tyArgListOpt), tokens, errors

    | _ when not (List.isEmpty acc) ->
      // Include qualifiers for completion.
      let pos =
        match List.tryLast acc with
        | Some (_, pos) -> posAddX 1 pos
        | None -> unreachable ()

      let errors =
        parseErrorCore "Expected identifier" pos errors

      AAppTy(List.rev acc, Name("", pos), None), tokens, errors

    | _ -> parseTyError "Expected identifier" (tokens, errors)

  go [] (tokens, errors)

let private parseTyAtom basePos (tokens, errors) : PR<ATy> =
  match tokens with
  | _ when nextInside basePos tokens |> not -> parseTyError "Expected a type atom" (tokens, errors)

  | (IdentToken _, _) :: _ -> parseNavTy basePos (tokens, errors)

  | (TyVarToken name, pos) :: tokens -> AVarTy(Name(name, pos)), tokens, errors

  | (LeftParenToken, lPos) :: tokens ->
    let ty, tokens, errors = parseTy basePos (tokens, errors)
    let rPos, tokens, errors = (tokens, errors) |> expectRightParen
    AParenTy(lPos, ty, rPos), tokens, errors

  | _ -> parseTyError "Expected a type atom" (tokens, errors)

/// `ty-suffix = ty-atom ( ident )*`
let private parseTySuffix basePos (tokens, errors) : PR<ATy> =
  let rec go (ty, tokens, errors) =
    let inside = nextInside basePos tokens

    match tokens with
    | (IdentToken ident, pos) :: tokens when inside -> go (ASuffixTy(ty, Name(ident, pos)), tokens, errors)

    | _ -> ty, tokens, errors

  parseTyAtom basePos (tokens, errors) |> go

/// `ty-tuple = ty-suffix ( '*' ty-suffix )*`
let private parseTyTuple basePos (tokens, errors) : PR<ATy> =
  let rec go acc (tokens, errors) =
    match tokens with
    | (StarToken, _) :: tokens ->
      let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)
      go (itemTy :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)

  match tokens with
  | (StarToken, starPos) :: _ ->
    let itemTys, tokens, errors = go [] (tokens, errors)
    ATupleTy(itemTy :: itemTys, starPos), tokens, errors

  | _ -> itemTy, tokens, errors

/// `ty-fun = ty-tuple ( '->' ty-fun )?`
let private parseTyFun basePos (tokens, errors) : PR<ATy> =
  let sTy, tokens, errors = parseTyTuple basePos (tokens, errors)

  match tokens with
  | (ArrowToken, arrowPos) :: tokens ->
    let tTy, tokens, errors = parseTyFun basePos (tokens, errors)
    AFunTy(sTy, arrowPos, tTy), tokens, errors

  | _ -> sTy, tokens, errors

let private parseTy basePos (tokens, errors) = parseTyFun basePos (tokens, errors)

// -----------------------------------------------
// Parse patterns
// -----------------------------------------------

let private parseNavPatBody head headPos (tokens, errors) : PR<APat> =
  let rec go acc tokens =
    match tokens with
    | (DotToken, dotPos) :: (IdentToken ident, identPos) :: tokens ->
      go (ANavPat(acc, dotPos, Name(ident, identPos))) tokens
    | _ -> acc, tokens, errors

  go (AIdentPat(None, Name(head, headPos))) tokens

/// `pat ')'`
let private parsePatParenBody basePos lPos (tokens, errors) : PR<APat> =
  let pat, tokens, errors = parsePat basePos (tokens, errors)
  let rPos, tokens, errors = (tokens, errors) |> expectRightParen
  AParenPat(lPos, pat, rPos), tokens, errors

// same as doParseStmts
let private doParseListPatItems basePos (tokens, errors) : PR<APat list> =
  let rec go i last acc alignPos (tokens, errors) =
    assert (i < 100100100)

    match tokens with
    | (SemiToken, semiPos) :: tokens when posInside alignPos semiPos ->
      let pat, tokens, errors = parsePat alignPos (tokens, errors)
      go (i + 1) pat (last :: acc) alignPos (tokens, errors)

    | _ when
      posIsSameColumn alignPos (nextPos tokens)
      && leadsPat tokens
      ->
      let pat, tokens, errors = parsePat alignPos (tokens, errors)
      go (i + 1) pat (last :: acc) alignPos (tokens, errors)

    | _ -> List.rev (last :: acc), tokens, errors

  let alignPos = nextPos tokens

  if posInside basePos alignPos && leadsPat tokens then
    let first, tokens, errors = parsePat alignPos (tokens, errors)
    go 0 first [] alignPos (tokens, errors)
  else
    [], tokens, errors

/// `pat ( ';' pat )* ']'`
let private parsePatListBody basePos bracketPos (tokens, errors) : PR<APat> =
  let itemPats, tokens, errors =
    doParseListPatItems basePos (tokens, errors)

  let rOpt, tokens, errors = expectRightBracket (tokens, errors)
  AListPat(bracketPos, itemPats, rOpt), tokens, errors

let private parsePatAtom basePos (tokens, errors) : PR<APat> =
  let onVis vis visPos tokens =
    match tokens with
    | (IdentToken ident, pos) :: tokens -> AIdentPat(Some(vis, visPos), Name(ident, pos)), tokens, errors
    | _ -> parsePatError "Expected identifier" (tokens, errors)

  match tokens with
  | _ when not (nextInside basePos tokens && leadsPat tokens) ->
    parsePatError "Expected a pattern atom" (tokens, errors)

  | (IntToken (text, flavorOpt), pos) :: tokens -> ALitPat(newIntLit text flavorOpt, pos), tokens, errors
  | (FloatToken text, pos) :: tokens -> ALitPat(FloatLit text, pos), tokens, errors
  | (CharToken value, pos) :: tokens -> ALitPat(CharLit value, pos), tokens, errors
  | (StringToken value, pos) :: tokens -> ALitPat(StringLit value, pos), tokens, errors

  | (IdentToken ident, pos) :: tokens -> parseNavPatBody ident pos (tokens, errors)

  | (LeftParenToken, lPos) :: (RightParenToken, rPos) :: tokens -> ATuplePat(lPos, [], Some rPos), tokens, errors
  | (LeftParenToken, lPos) :: tokens -> parsePatParenBody basePos lPos (tokens, errors)
  | (LeftBracketToken, lPos) :: (RightBracketToken, rPos) :: tokens -> AListPat(lPos, [], Some rPos), tokens, errors
  | (LeftBracketToken, lPos) :: tokens -> parsePatListBody basePos lPos (tokens, errors)

  | (FalseToken, pos) :: tokens -> ALitPat(BoolLit false, pos), tokens, errors
  | (TrueToken, pos) :: tokens -> ALitPat(BoolLit true, pos), tokens, errors

  | (PublicToken, visPos) :: tokens -> onVis PublicVis visPos tokens
  | (PrivateToken, visPos) :: tokens -> onVis PrivateVis visPos tokens

  | (MinusToken _, pos) :: (IntToken (text, flavorOpt), _) :: tokens ->
    ALitPat(newIntLit ("-" + text) flavorOpt, pos), tokens, errors
  | (MinusToken _, _) :: tokens -> parsePatError "Expected negative literal pattern" (tokens, errors)

  | _ ->
    // Drop the next token to prevent infinite loop.
    parsePatError "Expected a pattern atom" (listSkip 1 tokens, errors)

/// `pat-nav = pat-atom ( '.' ident )?`
let private parsePatNav basePos (tokens, errors) : PR<APat> =
  let pat, tokens, errors = parsePatAtom basePos (tokens, errors)

  match tokens with
  | (DotToken, pos) :: (IdentToken ident, identPos) :: tokens ->
    ANavPat(pat, pos, Name(ident, identPos)), tokens, errors

  | (DotToken, _) :: tokens -> parsePatError "Expected identifier" (tokens, errors)

  | _ -> pat, tokens, errors

let private parsePatCallArgs basePos (tokens, errors) : PR<APat list> =
  let innerBasePos = basePos |> posAddX 1

  let rec go acc (tokens, errors) =
    if nextInside innerBasePos tokens && leadsPat tokens then
      let pat, tokens, errors =
        parsePatNav innerBasePos (tokens, errors)

      go (pat :: acc) (tokens, errors)
    else
      List.rev acc, tokens, errors

  go [] (tokens, errors)

/// `pat-app = pat-nav ( pat-nav )?`
let private parsePatApp basePos (tokens, errors) : PR<APat> =
  let callee, tokens, errors = parsePatNav basePos (tokens, errors)

  // Parse argument if exists.
  if nextInside (basePos |> posAddX 1) tokens
     && leadsPat tokens then
    let argPos = posPrev (nextPos tokens)

    let arg, tokens, errors =
      parsePatNav (basePos |> posAddX 1) (tokens, errors)

    AAppPat(callee, argPos, arg), tokens, errors
  else
    callee, tokens, errors

/// `pat-cons = pat-call ( '::' pat-cons )?`
let private parsePatCons basePos (tokens, errors) : PR<APat> =
  let head, tokens, errors = parsePatApp basePos (tokens, errors)

  match tokens with
  | (ColonColonToken, opPos) :: tokens ->
    let tail, tokens, errors = parsePatCons basePos (tokens, errors)
    AConsPat(head, opPos, tail), tokens, errors

  | _ -> head, tokens, errors

/// `pat-ascribe = pat-cons ( ':' ty )?`
let private parsePatAscribe basePos (tokens, errors) : PR<APat> =
  let pat, tokens, errors = parsePatCons basePos (tokens, errors)

  match tokens with
  | (ColonToken, colonPos) :: tokens ->
    let ty, tokens, errors =
      parseTy (nextPos tokens) (tokens, errors)

    AAscribePat(pat, colonPos, ty), tokens, errors

  | _ -> pat, tokens, errors

/// `pat-tuple = pat-ascribe ( ',' pat-ascribe )*`
let private parsePatTuple basePos (tokens, errors) : PR<APat> =
  let rec go acc (tokens, errors) =
    match tokens with
    | (CommaToken, _) :: tokens ->
      let second, tokens, errors =
        parsePatAscribe basePos (tokens, errors)

      go (second :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let itemPat, tokens, errors =
    parsePatAscribe basePos (tokens, errors)

  match tokens with
  | (CommaToken, pos) :: _ ->
    let itemPats, tokens, errors = go [] (tokens, errors)
    ATuplePat(pos, itemPat :: itemPats, None), tokens, errors

  | _ -> itemPat, tokens, errors

/// `pat-as = pat-tuple ( 'as' ident )?`
/// NOTE: The syntax of `as` patterns is more flexible in F#.
let private parsePatAs basePos (tokens, errors) : PR<APat> =
  let pat, tokens, errors = parsePatTuple basePos (tokens, errors)

  match tokens with
  | (AsToken, pos) :: (IdentToken ident, identPos) :: tokens -> AAsPat(pat, pos, Name(ident, identPos)), tokens, errors

  | (AsToken, _) :: tokens ->
    let errors =
      parseNewError "Expected an identifier" (tokens, errors)

    pat, tokens, errors

  | _ -> pat, tokens, errors

/// `pat-or = pat ( '|' pat-or )?`
let private parsePatOr basePos (tokens, errors) : PR<APat> =
  let lPat, tokens, errors = parsePatAs basePos (tokens, errors)

  match tokens with
  | (PipeToken, pos) :: tokens ->
    let rPat, tokens, errors = parsePatOr basePos (tokens, errors)
    AOrPat(lPat, pos, rPat), tokens, errors

  | _ -> lPat, tokens, errors

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ALetHead =
  | LetVal of IsRec * APat
  | LetFun of IsRec * Vis * Name * argPats: APat list * resultTyOpt: (Pos * ATy) option

/// Parses head of let expressions.
///
/// `let-fun = vis? ident pat-av+ ( ':' ty )? = ...`
/// `let-val = pat ...`
let private parseLetHead basePos (tokens, errors) : PR<ALetHead> =
  let isRec, tokens = eatRec tokens

  let asLetFun () =
    let vis, tokens = eatVis tokens

    match tokens with
    | (IdentToken callee, calleePos) :: tokens when posInside basePos calleePos && leadsPat tokens ->
      Some(vis, callee, calleePos, tokens)
    | _ -> None

  match asLetFun () with
  | Some (vis, callee, calleePos, tokens) ->
    let args, tokens, errors =
      parsePatCallArgs basePos (tokens, errors)

    let resultTyOpt, tokens, errors =
      match tokens with
      | (ColonToken, pos) :: tokens ->
        let ty, tokens, errors = parseTy basePos (tokens, errors)
        Some(pos, ty), tokens, errors

      | _ -> None, tokens, errors

    ALetHead.LetFun(isRec, vis, Name(callee, calleePos), args, resultTyOpt), tokens, errors

  | _ ->
    let pat, tokens, errors = parsePat basePos (tokens, errors)
    ALetHead.LetVal(isRec, pat), tokens, errors

/// `pat = pat-or`
let private parsePat basePos (tokens, errors) : PR<APat> =
  if not (nextInside basePos tokens && leadsPat tokens) then
    parsePatError "Expected a pattern" (tokens, errors)
  else
    parsePatOr basePos (tokens, errors)

// -----------------------------------------------
// Parse operator expressions
// -----------------------------------------------

/// `range = term ( '..' term )?`
let private parseRange basePos (tokens, errors) : PR<AExpr> =
  let l, tokens, errors = parseExpr basePos (tokens, errors)

  match tokens with
  | (DotDotToken, pos) :: tokens ->
    let r, tokens, errors = parseExpr basePos (tokens, errors)
    ARangeExpr(l, pos, r), tokens, errors

  | _ -> l, tokens, errors

let private parseAtom basePos (tokens, errors) : PR<AExpr> =
  match tokens with
  | _ when not (nextInside basePos tokens) -> parseExprError "Expected an expression" (tokens, errors)

  | (IntToken (text, flavorOpt), pos) :: tokens -> ALitExpr(newIntLit text flavorOpt, pos), tokens, errors
  | (FloatToken text, pos) :: tokens -> ALitExpr(FloatLit text, pos), tokens, errors
  | (CharToken value, pos) :: tokens -> ALitExpr(CharLit value, pos), tokens, errors
  | (StringToken value, pos) :: tokens -> ALitExpr(StringLit value, pos), tokens, errors

  | (IdentToken ident, pos) :: tokens ->
    let tyArgs, tokens, errors = parseTyArgs pos (tokens, errors)
    AIdentExpr(Name(ident, pos), tyArgs), tokens, errors

  | (LeftParenToken, lPos) :: (RightParenToken, rPos) :: tokens -> ATupleExpr(lPos, [], Some rPos), tokens, errors
  | (LeftParenToken, lPos) :: tokens -> parseParenBody basePos lPos (tokens, errors)
  | (LeftBracketToken, bracketPos) :: tokens -> parseList basePos bracketPos (tokens, errors)
  | (LeftBraceToken, bracePos) :: tokens -> parseRecordExpr bracePos (tokens, errors)

  | (FalseToken, pos) :: tokens -> ALitExpr(BoolLit false, pos), tokens, errors
  | (TrueToken, pos) :: tokens -> ALitExpr(BoolLit true, pos), tokens, errors

  | (IfToken, pos) :: tokens -> parseIf pos (tokens, errors)
  | (MatchToken, pos) :: tokens -> parseMatch pos (tokens, errors)
  | (FunToken, pos) :: tokens -> parseFun basePos pos (tokens, errors)
  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)

  | _ ->
    // Drop the next token to prevent infinite loop.
    parseExprError "Expected an expression" (listSkip 1 tokens, errors)

/// `suffix = atom ( '.' '[' range ']' | '.' ident )*`
let private parseSuffix basePos (tokens, errors) : PR<AExpr> =
  let l, tokens, errors = parseAtom basePos (tokens, errors)

  let rec go acc (tokens, errors) =
    match tokens with
    | (DotToken, dotPos) :: (LeftBracketToken, lPos) :: tokens ->
      let r, tokens, errors = parseRange basePos (tokens, errors)
      let rPos, tokens, errors = (tokens, errors) |> expectRightBracket

      go (AIndexExpr(acc, dotPos, lPos, r, rPos)) (tokens, errors)

    | (DotToken, dotPos) :: (IdentToken ident, identPos) :: tokens ->
      go (ANavExpr(acc, dotPos, Name(ident, identPos))) (tokens, errors)

    | (DotToken, _) :: tokens ->
      let errors =
        parseNewError "Expected .[] or .field" (tokens, errors)

      acc, tokens, errors

    | _ -> acc, tokens, errors

  go l (tokens, errors)

/// `app = suffix ( suffix )*`
let private parseApp basePos (tokens, errors) : PR<AExpr> =
  let innerBasePos = basePos |> posAddX 1

  let callee, tokens, errors = parsePrefix basePos (tokens, errors)

  let rec go callee (tokens, errors) =
    if nextInside innerBasePos tokens && leadsArg tokens then
      let pos = posPrev (nextPos tokens)

      let arg, tokens, errors =
        parsePrefix innerBasePos (tokens, errors)

      go (ABinaryExpr(AppBinary, callee, pos, arg)) (tokens, errors)
    else
      callee, tokens, errors

  go callee (tokens, errors)

/// `prefix = ('-' | '&&')? app`
let private parsePrefix basePos (tokens, errors) : PR<AExpr> =
  match tokens with
  | (MinusToken _, pos) :: tokens ->
    let arg, tokens, errors = parseSuffix basePos (tokens, errors)
    AUnaryExpr(MinusUnary, pos, arg), tokens, errors

  | (AmpAmpToken _, pos) :: tokens ->
    let arg, tokens, errors = parseSuffix basePos (tokens, errors)
    AUnaryExpr(PtrOfUnary, pos, arg), tokens, errors

  | _ -> parseSuffix basePos (tokens, errors)

let private parseNextBp bp basePos (tokens, errors) : PR<AExpr> =
  match bpNext bp with
  | PrefixBp -> parseApp basePos (tokens, errors)
  | nextBp -> parseOp nextBp basePos (tokens, errors)

let private parseOps bp basePos l (tokens, errors) : PR<AExpr> =
  let nextL expr op opPos (tokens, errors) =
    let second, tokens, errors = parseNextBp bp basePos (tokens, errors)
    let expr = ABinaryExpr(op, expr, opPos, second)
    parseOps bp basePos expr (tokens, errors)

  let nextR expr op opPos (tokens, errors) =
    let second, tokens, errors = parseOp bp basePos (tokens, errors)
    let expr = ABinaryExpr(op, expr, opPos, second)
    parseOps bp basePos expr (tokens, errors)

  match bp, tokens with
  | OrBp, (PipePipeToken, opPos) :: tokens -> nextL l LogicalOrBinary opPos (tokens, errors)

  | AndBp, (AmpAmpToken false, opPos) :: tokens -> nextL l LogicalAndBinary opPos (tokens, errors)

  | SigilBp, (RightAngleToken, opPos) :: (RightAngleToken, pos2) :: (RightAngleToken, pos3) :: tokens when
    canMerge3 opPos pos2 pos3
    ->
    nextL l RightShiftBinary opPos (tokens, errors)

  | SigilBp, (EqualToken, opPos) :: tokens -> nextL l EqualBinary opPos (tokens, errors)
  | SigilBp, (LeftRightToken, opPos) :: tokens -> nextL l NotEqualBinary opPos (tokens, errors)
  | SigilBp, (LeftAngleToken false, opPos) :: tokens -> nextL l LessBinary opPos (tokens, errors)
  | SigilBp, (LeftEqualToken, opPos) :: tokens -> nextL l LessEqualBinary opPos (tokens, errors)
  | SigilBp, (RightAngleToken, opPos) :: tokens -> nextL l GreaterBinary opPos (tokens, errors)
  | SigilBp, (RightEqualToken, opPos) :: tokens -> nextL l GreaterEqualBinary opPos (tokens, errors)

  | SigilBp, (PipeRightToken, opPos) :: tokens -> nextL l PipeBinary opPos (tokens, errors)

  | SigilBp, (AmpAmpAmpToken, opPos) :: tokens -> nextL l BitAndBinary opPos (tokens, errors)
  | SigilBp, (PipePipePipeToken, opPos) :: tokens -> nextL l BitOrBinary opPos (tokens, errors)
  | SigilBp, (LeftLeftLeftToken, opPos) :: tokens -> nextL l LeftShiftBinary opPos (tokens, errors)

  | XorBp, (HatHatHatToken, opPos) :: tokens -> nextR l BitXorBinary opPos (tokens, errors)

  | ConsBp, (ColonColonToken, opPos) :: tokens -> nextR l ConsBinary opPos (tokens, errors)

  | AddBp, (PlusToken, opPos) :: tokens -> nextL l AddBinary opPos (tokens, errors)
  | AddBp, (MinusToken false, opPos) :: tokens -> nextL l SubBinary opPos (tokens, errors)

  | MulBp, (StarToken, opPos) :: tokens -> nextL l MulBinary opPos (tokens, errors)
  | MulBp, (SlashToken, opPos) :: tokens -> nextL l DivBinary opPos (tokens, errors)
  | MulBp, (PercentToken, opPos) :: tokens -> nextL l ModuloBinary opPos (tokens, errors)

  | _ -> l, tokens, errors

/// E.g. `add = mul ( ('+'|'-') mul )*`
let private parseOp bp basePos (tokens, errors) : PR<AExpr> =
  let l, tokens, errors = parseNextBp bp basePos (tokens, errors)

  parseOps bp basePos l (tokens, errors)

let private parseTupleItem basePos (tokens, errors) : PR<AExpr> = parseOp OrBp basePos (tokens, errors)

/// `tuple = item ( ',' item )*`
let private parseTuple basePos (tokens, errors) : PR<AExpr> =
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
    ATupleExpr(pos, item :: items, None), tokens, errors

  | _ -> item, tokens, errors

/// `ascribe = tuple ( ':' ty )?`
let private parseAscribe basePos (tokens, errors) : PR<AExpr> =
  let body, tokens, errors = parseTuple basePos (tokens, errors)

  match tokens with
  | (ColonToken, colonPos) :: tokens ->
    let ty, tokens, errors = parseTy basePos (tokens, errors)
    AAscribeExpr(body, colonPos, ty), tokens, errors

  | _ -> body, tokens, errors

let private parseExpr basePos (tokens, errors) : PR<AExpr> = parseAscribe basePos (tokens, errors)

// -----------------------------------------------
// Parse block expressions
// -----------------------------------------------

let private parseParenBody basePos lPos (tokens, errors) : PR<AExpr> =
  match tokens with
  | (FunToken, funPos) :: tokens ->
    // HACK: Specialize for `(fun ... -> ...)` so that `(` doesn't form a block.
    let body, tokens, errors =
      parseFun basePos funPos (tokens, errors)

    let rPos, tokens, errors = (tokens, errors) |> expectRightParen
    AParenExpr(lPos, body, rPos), tokens, errors

  | _ ->
    let stmts, tokens, errors = parseItems (tokens, errors)
    let rPos, tokens, errors = (tokens, errors) |> expectRightParen

    let wrap expr = AParenExpr(lPos, expr, rPos)

    let body, tokens, errors =
      match splitLast stmts with
      | Some ([], expr) -> wrap expr, tokens, errors
      | Some (stmts, last) -> wrap (ASemiExpr(stmts, last, lPos)), tokens, errors
      | None -> parseExprError "Expected an expression" (tokens, errors)

    body, tokens, errors

let private parseList _basePos lPos (tokens, errors) : PR<AExpr> =
  let items, tokens, errors = parseItems (tokens, errors)
  let rOpt, tokens, errors = (tokens, errors) |> expectRightBracket
  AListExpr(lPos, items, rOpt), tokens, errors

let private parseRecordExpr lPos (tokens, errors) : PR<AExpr> =
  let rec go acc alignPos (tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> List.rev acc, tokens, errors

    | (SemiToken, _) :: tokens -> go acc (nextPos tokens) (tokens, errors)

    | (IdentToken ident, identPos) :: (EqualToken, equalPos) :: tokens when identPos |> posIsSameColumn alignPos ->
      let init, tokens, errors =
        parseExpr (identPos |> posAddX 1) (tokens, errors)

      go ((Name(ident, identPos), equalPos, init) :: acc) alignPos (tokens, errors)

    | (_, pos) :: tokens when pos |> posInside alignPos ->
      let errors =
        parseErrorCore "Expected 'field = expr'." pos errors

      go acc alignPos (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let baseOpt, (fields, tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> None, ([], tokens, errors)

    | (IdentToken _, _) :: (EqualToken, _) :: _ -> None, go [] (nextPos tokens) (tokens, errors)

    | _ ->
      let baseExpr, tokens, errors =
        parseExpr (nextPos tokens) (tokens, errors)

      let withPosOpt, tokens, errors =
        match tokens with
        | (WithToken, withPos) :: tokens -> Some withPos, tokens, errors

        | _ ->
          let errors =
            parseErrorCore "Expected 'with' keyword." (nextPos tokens) errors

          None, tokens, errors

      Some(baseExpr, withPosOpt), go [] (nextPos tokens) (tokens, errors)

  let rPos, tokens, errors = (tokens, errors) |> expectRightBrace

  ARecordExpr(lPos, baseOpt, fields, rPos), tokens, errors

let private parseThenClause basePos (tokens, errors) : PR<Pos * AExpr> =
  let innerBasePos = basePos |> posAddX 1

  // #incorrectPos
  let thenPos, (body, tokens, errors) =
    match tokens with
    | (ThenToken, thenPos) :: tokens when posInside basePos thenPos ->
      let body, tokens, errors =
        parseSemi innerBasePos thenPos (tokens, errors)

      thenPos, (body, tokens, errors)

    | _ ->
      let pos = posPrev (nextPos tokens)
      pos, parseExprError "Expected 'then'" (tokens, errors)

  (thenPos, body), tokens, errors

let private parseElseClause basePos (tokens, errors) : PR<(Pos * AExpr) option> =
  match tokens with
  | (ElseToken, elsePos) :: (IfToken, nextIfPos) :: tokens when
    posInside basePos elsePos
    && posIsSameRow elsePos nextIfPos
    ->
    // ELSE_IF_LAYOUT rule. Parse the next as if `if` in `else if` is placed where `else` is.
    let alt, tokens, errors =
      parseExpr basePos ((IfToken, elsePos) :: tokens, errors)

    Some(elsePos, alt), tokens, errors

  | (ElseToken, elsePos) :: tokens when posInside basePos elsePos ->
    let alt, tokens, errors =
      parseSemi basePos elsePos (tokens, errors)

    Some(elsePos, alt), tokens, errors

  | _ -> None, tokens, errors

let private parseIf ifPos (tokens, errors) : PR<AExpr> =
  let innerBasePos = ifPos |> posAddX 1

  let cond, tokens, errors = parseExpr innerBasePos (tokens, errors)
  let (thenPos, body), tokens, errors = parseThenClause ifPos (tokens, errors)
  let altOpt, tokens, errors = parseElseClause ifPos (tokens, errors)
  AIfExpr(ifPos, cond, thenPos, body, altOpt), tokens, errors

/// `'|'? pat ( 'when' expr )? -> expr`
let private parseMatchArm matchPos (pipePos: Pos option) (tokens, errors) =
  let innerBasePos = matchPos |> posAddX 1

  let pat, tokens, errors = parsePat innerBasePos (tokens, errors)

  let guardOpt, tokens, errors =
    match tokens with
    | (WhenToken, whenPos) :: tokens ->
      let guard, tokens, errors = parseExpr innerBasePos (tokens, errors)
      Some(whenPos, guard), tokens, errors

    | _ -> None, tokens, errors

  // #incorrectPos
  let arrowPos, (body, tokens, errors) =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> arrowPos, parseSemi matchPos arrowPos (tokens, errors)

    | _ -> posPrev (nextPos tokens), parseExprError "Expected '->'" (tokens, errors)

  (pipePos, pat, guardOpt, arrowPos, body), tokens, errors

let private parseMatch matchPos (tokens, errors) : PR<AExpr> =
  let cond, tokens, errors = parseExpr matchPos (tokens, errors)

  let withPos, pipePos, tokens, errors =
    match tokens with
    | (WithToken, withPos) :: (PipeToken, pipePos) :: tokens -> Some withPos, Some pipePos, tokens, errors

    | (WithToken, withPos) :: tokens -> Some withPos, None, tokens, errors

    | _ ->
      let errors =
        parseNewError "Expected 'with'" (tokens, errors)

      None, None, tokens, errors

  let rec go acc pipePos (tokens, errors) =
    let arm, tokens, errors =
      parseMatchArm matchPos pipePos (tokens, errors)

    match tokens with
    | (PipeToken, pipePos) :: tokens when posInside matchPos pipePos -> go (arm :: acc) (Some pipePos) (tokens, errors)

    | _ -> List.rev (arm :: acc), tokens, errors

  let arms, tokens, errors =
    if Option.isNone withPos then
      [], tokens, errors
    else if
      Option.isNone pipePos
      && not (nextInside matchPos tokens && leadsPat tokens)
    then
      // Avoid parsing body if apparently no arms.
      [], tokens, ("Expected at least one arm.", matchPos) :: errors
    else
      go [] pipePos (tokens, errors)

  AMatchExpr(matchPos, cond, withPos, arms), tokens, errors

/// `fun-expr = 'fun' pat* '->' expr`
let private parseFun basePos funPos (tokens, errors) : PR<AExpr> =
  let argPats, tokens, errors =
    parsePatCallArgs basePos (tokens, errors)

  // #incorrectPos
  let arrowPos, (body, tokens, errors) =
    match tokens with
    | (ArrowToken, arrowPos) :: tokens -> arrowPos, parseSemi basePos arrowPos (tokens, errors)

    | _ -> posPrev (nextPos tokens), parseExprError "Missing '->'" (tokens, errors)

  AFunExpr(funPos, argPats, arrowPos, body), tokens, errors

// -----------------------------------------------
// Parse binding statements
// -----------------------------------------------

let private parseLet letPos (tokens, errors) : PR<AExpr> =
  let innerBasePos = letPos |> posAddX 1

  let head, tokens, errors =
    parseLetHead innerBasePos (tokens, errors)

  // #incorrectPos
  let equalPos, (body, tokens, errors) =
    match tokens with
    | (EqualToken, equalPos) :: tokens -> equalPos, parseSemi innerBasePos equalPos (tokens, errors)

    | _ -> posPrev (nextPos tokens), parseExprError "Missing '='" (tokens, errors)

  let nextOpt, tokens, errors =
    match tokens with
    | (InToken, inPos) :: tokens when posInside letPos inPos ->
      let next, tokens, errors = parseSemi letPos inPos (tokens, errors)
      Some next, tokens, errors

    | _ :: _ when posIsSameColumn (nextPos tokens) letPos ->
      // Implicit `in` clause must be on the same column as `let`.
      let next, tokens, errors =
        parseSemi letPos (nextPos tokens) (tokens, errors)

      Some next, tokens, errors

    | _ -> None, tokens, errors

  match head with
  | ALetHead.LetVal (isRec, pat) ->
    ALetExpr(letPos, ALetContents.LetVal(isRec, pat, equalPos, body), nextOpt), tokens, errors

  | ALetHead.LetFun (isRec, vis, callee, argPats, resultTyOpt) ->
    ALetExpr(letPos, ALetContents.LetFun(isRec, vis, callee, argPats, resultTyOpt, equalPos, body), nextOpt),
    tokens,
    errors

/// `payload-ty = labeled-ty ( '*' labeled-ty )*`
/// `labeled-ty = ( ident ':' )? ty-suffix`
let private parsePayloadTy basePos (tokens, errors) : PR<(Pos option * ATy) list> =
  let eatLabel tokens =
    match tokens with
    | (IdentToken _, pos) :: (ColonToken, _) :: tokens -> Some pos, tokens
    | _ -> None, tokens

  // parse first
  let labelOpt, tokens = eatLabel tokens
  let firstTy, tokens, errors = parseTySuffix basePos (tokens, errors)

  // parse second or more
  let rec go acc (tokens, errors) =
    match tokens with
    | (StarToken, _) :: tokens ->
      let labelOpt, tokens = eatLabel tokens
      let itemTy, tokens, errors = parseTySuffix basePos (tokens, errors)
      go ((labelOpt, itemTy) :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  go [ labelOpt, firstTy ] (tokens, errors)

/// Parses the body of union `type` declaration.
let private parseTyDeclUnion basePos (tokens, errors) : PR<ATyDeclBody> =
  let rec go acc (tokens, errors) =
    match tokens with
    | (PipeToken, pipePos) :: (IdentToken ident, identPos) :: (OfToken, ofPos) :: tokens ->
      let payloadTy, tokens, errors = parsePayloadTy basePos (tokens, errors)

      go
        ((pipePos, Name(ident, identPos), Some(ofPos, payloadTy))
         :: acc)
        (tokens, errors)

    | (PipeToken, pipePos) :: (IdentToken ident, identPos) :: tokens ->
      go ((pipePos, Name(ident, identPos), None) :: acc) (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let variants, tokens, errors = go [] (tokens, errors)
  AUnionTyDeclBody variants, tokens, errors

/// Parses the body of record type declaration.
let private parseTyDeclRecord basePos lPos (tokens, errors) : PR<ATyDeclBody> =
  let rec go acc alignPos (tokens, errors) =
    match tokens with
    | (RightBraceToken, _) :: _ -> List.rev acc, tokens, errors

    | (SemiToken, _) :: tokens -> go acc (nextPos tokens) (tokens, errors)

    | (IdentToken ident, identPos) :: (ColonToken, colonPos) :: tokens when identPos |> posIsSameColumn alignPos ->
      let ty, tokens, errors =
        parseTy (identPos |> posAddX 1) (tokens, errors)

      go ((Name(ident, identPos), ty, colonPos) :: acc) alignPos (tokens, errors)

    | (_, pos) :: tokens when pos |> posInside basePos ->
      let errors =
        parseErrorCore "Expected a field declaration." pos errors

      go acc alignPos (tokens, errors)

    | _ -> List.rev acc, tokens, errors

  let fields, tokens, errors =
    let alignPos = nextPos tokens
    go [] alignPos (tokens, errors)

  let rPos, tokens, errors = (tokens, errors) |> expectRightBrace

  ARecordTyDeclBody(lPos, fields, rPos), tokens, errors

/// Parses after `type .. =`.
/// NOTE: Unlike F#, it can't parse `type A = A` as definition of discriminated union.
let private parseTyDeclBody basePos (tokens, errors) : PR<ATyDeclBody> =
  let _, tokens = eatVis tokens

  match tokens with
  | (PipeToken, _) :: _ -> parseTyDeclUnion basePos (tokens, errors)

  | (IdentToken _, pos) :: (OfToken, _) :: _ ->
    // #incorrectPos
    let tokens = (PipeToken, posPrev pos) :: tokens
    parseTyDeclUnion basePos (tokens, errors)

  | (LeftBraceToken, lPos) :: tokens -> parseTyDeclRecord basePos lPos (tokens, errors)

  | _ ->
    let ty, tokens, errors = parseTy basePos (tokens, errors)
    ATySynonymDeclBody ty, tokens, errors

let private parseStmt basePos (tokens, errors) : PR<AExpr> =
  match tokens with
  | (LetToken, letPos) :: tokens -> parseLet letPos (tokens, errors)
  | _ -> parseExpr basePos (tokens, errors)

/// Parses a sequence of statements.
/// These statements must be aligned on the same column
/// except ones preceded by semicolon.
///
/// Returns last and non-last statements in reversed order.
let private doParseStmts last alignPos (tokens, errors) : PR<AExpr * AExpr list> =
  let rec go i last acc alignPos (tokens, errors) =
    assert (i < 100100100)

    match tokens with
    | (SemiToken, semiPos) :: tokens when posInside alignPos semiPos ->
      let expr, tokens, errors = parseStmt alignPos (tokens, errors)
      go (i + 1) expr (last :: acc) alignPos (tokens, errors)

    | _ when
      posIsSameColumn alignPos (nextPos tokens)
      && leadsExpr tokens
      ->
      let expr, tokens, errors = parseStmt alignPos (tokens, errors)
      go (i + 1) expr (last :: acc) alignPos (tokens, errors)

    | _ -> (last, acc), tokens, errors

  go 0 last [] alignPos (tokens, errors)

/// Parses a sequence of expressions separated by `;`s
/// or aligned on the same column.
/// Contents must be deeper than or equal to `basePos`,
/// which is typically the pos of `let`/`type`/`module`/etc.
/// The `mainPos` is a hint of the semi expression's pos.
/// `stmts = stmt ( ';' stmt )*`
let private parseSemi basePos mainPos (tokens, errors) : PR<AExpr> =
  let basePos = nextPos tokens |> posMax basePos
  let alignPos = nextPos tokens

  if posInside basePos alignPos && leadsExpr tokens then
    let first, tokens, errors = parseStmt alignPos (tokens, errors)

    let (last, acc), tokens, errors =
      doParseStmts first alignPos (tokens, errors)

    ASemiExpr(List.rev acc, last, mainPos), tokens, errors
  else
    parseExprError "Expected statements" (tokens, errors)

let private parseItems (tokens, errors) : PR<AExpr list> =
  let alignPos = nextPos tokens

  if leadsExpr tokens then
    let first, tokens, errors = parseStmt alignPos (tokens, errors)

    let (last, acc), tokens, errors =
      doParseStmts first alignPos (tokens, errors)

    List.rev (last :: acc), tokens, errors
  else
    [], tokens, errors

// -----------------------------------------------
// Parse declarations
// -----------------------------------------------

let private parseTyParamList identPos (tokens, errors) : PR<ATyParamList option> =
  match tokens with
  | (LeftAngleToken true, lPos) :: tokens when posIsSameRow identPos lPos ->
    let rec go acc tokens =
      match tokens with
      | (TyVarToken ident, identPos) :: tokens ->
        let acc = Name(ident, identPos) :: acc

        match tokens with
        | (CommaToken, _) :: tokens -> go acc tokens

        | (RightAngleToken, rPos) :: tokens -> List.rev acc, Some rPos, None, tokens

        | _ -> List.rev acc, None, Some "Expected '>'.", tokens

      | _ -> List.rev acc, None, Some "Expected type variable.", tokens

    let tyArgs, rPos, msgOpt, tokens = go [] tokens

    let errors =
      match msgOpt with
      | Some msg -> parseNewError msg (tokens, errors)
      | None -> errors

    Some(lPos, tyArgs, rPos), tokens, errors

  | _ -> None, tokens, errors

let private parseLetDecl letPos (tokens, errors) : PR<ADecl option> =
  let innerBasePos = letPos |> posAddX 1

  let head, tokens, errors =
    parseLetHead innerBasePos (tokens, errors)

  // #incorrectPos
  let equalPos, (init, tokens, errors) =
    match tokens with
    | (EqualToken, equalPos) :: tokens -> equalPos, parseSemi innerBasePos equalPos (tokens, errors)
    | _ -> posPrev (nextPos tokens), parseExprError "Missing '='" (tokens, errors)

  let decl, tokens, errors =
    match head with
    | ALetHead.LetVal (isRec, pat) -> ALetDecl(letPos, ALetContents.LetVal(isRec, pat, equalPos, init)), tokens, errors

    | ALetHead.LetFun (isRec, vis, callee, argPats, resultTyOpt) ->
      ALetDecl(letPos, ALetContents.LetFun(isRec, vis, callee, argPats, resultTyOpt, equalPos, init)), tokens, errors

  Some decl, tokens, errors

let private parseTyDecl typePos (tokens, errors) : PR<ADecl option> =
  let basePos = typePos |> posAddX 1

  let vis, tokens = eatVis tokens

  let tyIdentOpt, (tokens, errors) =
    match tokens with
    | (IdentToken tyIdent, tyIdentPos) :: tokens -> Some(tyIdent, tyIdentPos), (tokens, errors)
    | _ ->
      let errors =
        parseNewError "Expected identifier" (tokens, errors)

      None, (tokens, errors)

  let opt, tokens, errors =
    match tyIdentOpt with
    | Some (tyIdent, tyIdentPos) ->
      let tyName = Name(tyIdent, tyIdentPos)

      let tyArgs, tokens, errors =
        parseTyParamList tyIdentPos (tokens, errors)

      Some(tyName, tyArgs), tokens, errors

    | None -> None, tokens, errors

  match opt, tokens with
  | Some (tyName, tyParamList), (EqualToken, equalPos) :: tokens ->
    let tyDecl, tokens, errors =
      parseTyDeclBody basePos (tokens, errors)

    let decl =
      match tyDecl with
      | ATySynonymDeclBody ty -> ATySynonymDecl(typePos, vis, tyName, tyParamList, equalPos, ty)
      | AUnionTyDeclBody variants -> AUnionTyDecl(typePos, vis, tyName, tyParamList, equalPos, variants)
      | ARecordTyDeclBody (lPos, fields, rPos) ->
        ARecordTyDecl(typePos, vis, tyName, tyParamList, equalPos, lPos, fields, rPos)

    Some decl, tokens, errors

  | Some (tyName, tyParamList), tokens ->
    // #incorrectPos
    let equalPos = posPrev (nextPos tokens)

    let ty, tokens, errors =
      parseTyError "Expected '='" (tokens, errors)

    Some(ATySynonymDecl(typePos, vis, tyName, tyParamList, equalPos, ty)), tokens, errors

  | _ -> None, tokens, errors

let private parsePath (tokens, errors) : PR<Name list> =
  let rec go acc (tokens, errors) =
    match tokens with
    | (DotToken, _) :: (IdentToken ident, identPos) :: tokens -> go (Name(ident, identPos) :: acc) (tokens, errors)

    | (DotToken, _) :: tokens ->
      let errors =
        parseNewError "Expected identifier" (tokens, errors)

      List.rev acc, tokens, errors

    | _ -> List.rev acc, tokens, errors

  match tokens with
  | (IdentToken ident, identPos) :: tokens -> go [ Name(ident, identPos) ] (tokens, errors)

  | _ ->
    let errors =
      parseNewError "Expected identifier" (tokens, errors)

    [], tokens, errors

/// `open = 'open' ident ( '.' ident )*`
let private parseOpenDecl openPos (tokens, errors) : PR<ADecl option> =
  let path, tokens, errors = parsePath (tokens, errors)
  Some(AOpenDecl(openPos, path)), tokens, errors

let private parseModuleDecl modulePos (tokens, errors) : PR<ADecl option> =
  let isRec, tokens = eatRec tokens
  let vis, tokens = eatVis tokens

  let name, tokens, errors =
    match tokens with
    | (IdentToken moduleName, pos) :: tokens -> Name(moduleName, pos), tokens, errors

    | _ ->
      let errors =
        parseNewError "Expected identifier" (tokens, errors)

      Name("_", modulePos), tokens, errors

  match tokens with
  | (EqualToken, equalPos) :: (((IdentToken _, _) :: _) as tokens) ->
    let path, tokens, errors = parsePath (tokens, errors)
    Some(AModuleSynonymDecl(modulePos, name, equalPos, path)), tokens, errors

  | (EqualToken, equalPos) :: tokens ->
    let decls, tokens, errors =
      parseModuleBody (nextPos tokens) (tokens, errors)

    Some(AModuleDecl(modulePos, isRec, vis, name, equalPos, decls)), tokens, errors

  | _ ->
    // #incorrectPos
    let equalPos = behindName name

    let errors =
      parseNewError "Expected '='" (tokens, errors)

    Some(AModuleSynonymDecl(modulePos, name, equalPos, [])), tokens, errors

let private parseAttrDecl basePos lPos (tokens, errors) : PR<ADecl option> =
  let contents, tokens, errors =
    parseSemi basePos basePos (tokens, errors)

  let rPos, tokens, errors = (tokens, errors) |> expectRightAttr

  if tokens
     |> nextPos
     |> posIsSameColumn basePos
     |> not then
    parseDeclError "Expected a declaration after attribute." (tokens, errors)
  else
    let declOpt, tokens, errors = parseDecl basePos (tokens, errors)

    match declOpt with
    | Some decl -> Some(AAttrDecl(lPos, contents, rPos, decl)), tokens, errors
    | None -> None, tokens, errors

let private parseDecl basePos (tokens, errors) : PR<ADecl option> =
  match tokens with
  | (LeftAttrToken, lPos) :: tokens -> parseAttrDecl lPos lPos (tokens, errors)
  | (LetToken, letPos) :: tokens -> parseLetDecl letPos (tokens, errors)
  | (TypeToken, typePos) :: tokens -> parseTyDecl typePos (tokens, errors)
  | (OpenToken, typePos) :: tokens -> parseOpenDecl typePos (tokens, errors)
  | (ModuleToken, modulePos) :: tokens -> parseModuleDecl modulePos (tokens, errors)

  | _ ->
    let exprOpt, tokens, errors = parseExpr basePos (tokens, errors)

    match exprOpt with
    | AMissingExpr _ -> None, tokens, errors
    | expr -> Some(AExprDecl expr), tokens, errors

let private parseModuleBody basePos (tokens, errors) : PR<ADecl list> =
  let rec go i acc (tokens, errors) =
    assert (i < 1100100)

    match tokens with
    | _ when nextInside basePos tokens |> not -> List.rev acc, tokens, errors

    | _ ->
      // error if unaligned
      let declOpt, tokens, errors = parseDecl basePos (tokens, errors)

      match declOpt with
      | Some decl -> go (i + 1) (decl :: acc) (tokens, errors)
      | None -> List.rev acc, tokens, errors

  go 0 [] (tokens, errors)

// -----------------------------------------------
// Parse toplevel
// -----------------------------------------------

let private parseModuleHead (tokens, errors) : PR<AModuleHead option> =
  let backtrack () = None, tokens, errors

  match tokens with
  | (ModuleToken, modulePos) :: tokens ->
    let isRec, tokens = eatRec tokens
    let path, tokens, errors = parsePath (tokens, errors)

    match tokens with
    | (EqualToken, _) :: _ ->
      // It was inner module.
      backtrack ()

    | _ ->
      let hint () =
        "Hint: `module rec ProjectName.ModuleName`."

      let errors =
        match isRec with
        | IsRec -> errors
        | NotRec -> parseErrorCore ("Module header requires 'rec'. " + hint ()) modulePos errors

      let errors =
        match path with
        | []
        | [ _; _ ] -> errors
        | Name (_, pos) :: _ ->
          parseErrorCore
            ("Module header must contain exactly two names. "
             + hint ())
            pos
            errors

      Some(modulePos, path), tokens, errors

  | _ -> backtrack ()

let private parseRoot (tokens, errors) : PR<ARoot> =
  let headOpt, tokens, errors = parseModuleHead (tokens, errors)

  let basePos: Pos =
    match headOpt with
    | Some (pos, _) -> pos
    | None -> 0, 0

  let decls, tokens, errors =
    if not (List.isEmpty tokens) then
      parseModuleBody basePos (tokens, errors)
    else
      [], tokens, errors

  ARoot(headOpt, decls), tokens, errors

let parse (tokens: TokenizeResult) : ARoot * Errors =
  let root, tokens, errors = parseRoot (tokens, [])

  let errors =
    if not (List.isEmpty tokens) then
      parseNewError "Expected eof" (tokens, errors)
    else
      errors

  root, errors
