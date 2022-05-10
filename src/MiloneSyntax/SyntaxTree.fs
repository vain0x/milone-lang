module rec MiloneSyntax.SyntaxTree

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError
open Std.StdJson
open Std.StdPair
open Std.StdMap

module C = Std.StdChar
module S = Std.StdString

// -----------------------------------------------
// Util
// -----------------------------------------------

let private noRange: Range = (0, 0), (0, 0)

module Pos =
  let zero: Pos = 0, 0
  let min l r = if Pos.compare r l < 0 then r else l
  let max l r = if Pos.compare l r < 0 then r else l

module Range =
  let join l r : Range =
    let lp, lq = l
    let rp, rq = r
    Pos.min lp rp, Pos.max lq rq

  let meet l r : Range =
    let lp, lq = l
    let rp, rq = r
    Pos.max lp rp, Pos.min lq rq

let private cons x xs = [ x ] :: xs

let private consOpt xOpt xs =
  match xOpt with
  | Some x -> [ x ] :: xs
  | None -> xs

let private consOptionMap f xOpt xs =
  match xOpt with
  | Some x -> [ f x ] :: xs
  | None -> xs

let private consList x xs = x :: xs
let private consListMap f x xs = List.map f x :: xs

// -----------------------------------------------
// Tokens
// -----------------------------------------------

/// Mapping from start-position to (kind, end-position).
type private TokenRangeMap = TreeMap<Pos, Token * Pos>

let private toTokenRangeMap (tokens: TokenizeFullResult) (eofPos: Pos) : TokenRangeMap =
  let lastOpt, map =
    tokens
    |> List.fold
         (fun (prevOpt, map) (token, pos) ->
           match prevOpt with
           | None -> Some(token, pos), map

           | Some (prevToken, prevPos) ->
             let map = map |> TMap.add prevPos (prevToken, pos)
             Some(token, pos), map)
         (None, TMap.empty (Pair.compare compare compare))

  match lastOpt with
  | Some (token, pos) -> map |> TMap.add pos (token, eofPos)
  | None -> map

let private resolveTokenRange (map: TokenRangeMap) (pos: Pos) : (Token * Range) option =
  match map |> TMap.tryFind pos with
  | Some (token, endPos) -> Some(token, (pos, endPos))
  | None -> None

// -----------------------------------------------
// Syntax Types
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxKind =
  // Non-token anchor to occupy a position.
  | Anchor

  // Token:
  | Bad
  | Blank
  | Newlines
  | Comment
  | Int
  | Float
  | Char
  | String
  | Ident
  | TyVar
  // Parentheses:
  | LeftParen
  | RightParen
  | LeftBracket
  | RightBracket
  | LeftBrace
  | RightBrace
  | LeftAngle
  | RightAngle
  | LeftAttr
  | RightAttr
  // Punctuations:
  | Amp
  | AmpAmp
  | AmpAmpAmp
  | Arrow
  | Colon
  | ColonColon
  | Comma
  | Dot
  | DotDot
  | Equal
  | Hat
  | HatHatHat
  | LeftEqual
  | LeftLeft
  | LeftLeftLeft
  | LeftRight
  | Let
  | Minus
  | Percent
  | Pipe
  | PipePipe
  | PipePipePipe
  | PipeRight
  | Plus
  | RightEqual
  | Semi
  | Slash
  | Star
  // Keywords:
  | As
  | Else
  | False
  | Fun
  | If
  | In
  | Match
  | Module
  | Of
  | Open
  | Private
  | Public
  | Rec
  | Then
  | True
  | Type
  | When
  | With

  // Fragment:
  | Path
  | ParamList
  | GenericParamList
  | GenericArgList
  | WithClause
  | FieldInit
  | ThenClause
  | ElseClause
  | Arm
  | GuardClause
  | VariantDecl
  | FieldDecl
  | ModuleHead

  // Ty:
  | MissingTy
  | PathTy
  | VarTy
  | ParenTy
  | SuffixTy
  | TupleTy
  | FunTy

  // Pat:
  | MissingPat
  | LitPat
  | IdentPat
  | ParenPat
  | ListPat
  | NavPat
  | AppPat
  | ConsPat
  | TuplePat
  | AsPat
  | AscribePat
  | OrPat

  // Expr:
  | MissingExpr
  | LiteralExpr
  | NameExpr
  | ParenExpr
  | ListExpr
  | RecordExpr
  | IfExpr
  | MatchExpr
  | FunExpr
  | NavExpr
  | IndexExpr
  | AppExpr
  | UnaryExpr
  | BinaryExpr
  | RangeExpr
  | TupleExpr
  | AscribeExpr
  | BlockExpr
  | LetValExpr
  | LetFunExpr

  // Decl:
  | ExprDecl
  | LetValDecl
  | LetFunDecl
  | TySynonymDecl
  | UnionTyDecl
  | RecordTyDecl
  | OpenDecl
  | ModuleDecl
  | ModuleSynonymDecl
  | AttrDecl

  | Root

type private Sk = SyntaxKind

[<NoEquality; NoComparison>]
type SyntaxElement =
  | SyntaxToken of SyntaxKind * Range
  | SyntaxNode of SyntaxKind * Range * SyntaxElement list

[<NoEquality; NoComparison>]
type SyntaxTree = SyntaxTree of root: SyntaxElement

/// Context of syntax-tree generation.
type private SgCtx = SgCtx of TokenRangeMap

// -----------------------------------------------
// SyntaxKind
// -----------------------------------------------

let private kindOfToken token =
  match token with
  | ErrorToken _ -> Sk.Bad
  | BlankToken -> Sk.Blank
  | NewlinesToken -> Sk.Newlines
  | CommentToken -> Sk.Comment
  | IntToken _ -> Sk.Int
  | FloatToken _ -> Sk.Float
  | CharToken _ -> Sk.Char
  | StringToken _ -> Sk.String
  | IdentToken _ -> Sk.Ident
  | TyVarToken _ -> Sk.TyVar
  | LeftParenToken -> Sk.LeftParen
  | RightParenToken -> Sk.RightParen
  | LeftBracketToken -> Sk.LeftBracket
  | RightBracketToken -> Sk.RightBracket
  | LeftBraceToken -> Sk.LeftBrace
  | RightBraceToken -> Sk.RightBrace
  | LeftAngleToken _ -> Sk.LeftAngle
  | RightAngleToken -> Sk.RightAngle
  | LeftAttrToken -> Sk.LeftAttr
  | RightAttrToken -> Sk.RightAttr
  | AmpToken -> Sk.Amp
  | AmpAmpToken _ -> Sk.AmpAmp
  | AmpAmpAmpToken -> Sk.AmpAmpAmp
  | ArrowToken -> Sk.Arrow
  | ColonToken -> Sk.Colon
  | ColonColonToken -> Sk.ColonColon
  | CommaToken -> Sk.Comma
  | DotToken -> Sk.Dot
  | DotDotToken -> Sk.DotDot
  | EqualToken -> Sk.Equal
  | HatToken -> Sk.Hat
  | HatHatHatToken -> Sk.HatHatHat
  | LeftEqualToken -> Sk.LeftEqual
  | LeftLeftToken -> Sk.LeftLeft
  | LeftLeftLeftToken -> Sk.LeftLeftLeft
  | LeftRightToken -> Sk.LeftRight
  | RightEqualToken -> Sk.RightEqual
  | MinusToken _ -> Sk.Minus
  | PercentToken -> Sk.Percent
  | PipeToken -> Sk.Pipe
  | PipeRightToken -> Sk.PipeRight
  | PipePipeToken -> Sk.PipePipe
  | PipePipePipeToken -> Sk.PipePipePipe
  | PlusToken -> Sk.Plus
  | SemiToken -> Sk.Semi
  | SlashToken -> Sk.Slash
  | StarToken -> Sk.Star
  | AsToken -> Sk.As
  | ElseToken -> Sk.Else
  | FalseToken -> Sk.False
  | FunToken -> Sk.Fun
  | IfToken -> Sk.If
  | InToken -> Sk.In
  | LetToken -> Sk.Let
  | MatchToken -> Sk.Match
  | ModuleToken -> Sk.Module
  | OfToken -> Sk.Of
  | OpenToken -> Sk.Open
  | PrivateToken -> Sk.Private
  | PublicToken -> Sk.Public
  | RecToken -> Sk.Rec
  | ThenToken -> Sk.Then
  | TrueToken -> Sk.True
  | TypeToken -> Sk.Type
  | WhenToken -> Sk.When
  | WithToken -> Sk.With

// -----------------------------------------------
// SyntaxElement
// -----------------------------------------------

let private newAnchor pos = SyntaxToken(Sk.Anchor, (pos, pos))

/// Converts a token with range to syntax element.
let private wrapToken (token, range) = SyntaxToken(kindOfToken token, range)

let private newNode kind children = SyntaxNode(kind, noRange, children)

let private getRange element =
  match element with
  | SyntaxToken (_, range) -> range
  | SyntaxNode (_, range, _) -> range

// -----------------------------------------------
// Syntax Tree Generation
// -----------------------------------------------

// sg: syntax tree generation

let private sgToken (ctx: SgCtx) kind pos =
  let (SgCtx map) = ctx

  match resolveTokenRange map pos with
  | Some (_, range) -> SyntaxToken(kind, range)
  | None -> SyntaxToken(kind, (pos, pos))

let private buildNode kind childrenRev : SyntaxElement =
  SyntaxNode(kind, noRange, childrenRev |> List.rev |> List.collect id)

// Parser might produce incorrect position.
/// Anchor of `then` keyword. #incorrectPos
let private sgThen ctx pos =
  let (SgCtx rangeMap) = ctx

  match rangeMap |> TMap.tryFind pos with
  | Some (ThenToken, _) -> Some(newAnchor pos)
  | _ -> None

/// Anchor of `->`. #incorrectPos
let private sgArrow ctx pos =
  let (SgCtx rangeMap) = ctx

  match rangeMap |> TMap.tryFind pos with
  | Some (ArrowToken, _) -> Some(newAnchor pos)
  | _ -> None

/// Anchor of `=`. #incorrectPos
let private sgEqual ctx pos =
  let (SgCtx rangeMap) = ctx

  match rangeMap |> TMap.tryFind pos with
  | Some (EqualToken, _) -> Some(newAnchor pos)
  | _ -> None

/// Anchor of `|`. #incorrectPos
let private sgPipe ctx pos =
  let (SgCtx rangeMap) = ctx

  match rangeMap |> TMap.tryFind pos with
  | Some (PipeToken, _) -> Some(newAnchor pos)
  | _ -> None

let private sgName name : SyntaxElement =
  let (Name (_, pos)) = name
  newAnchor pos

let private sgPath quals name : SyntaxElement =
  buildNode
    Sk.Path
    ([ quals
       |> List.collect (fun (name, pos) -> [ sgName name; newAnchor pos ]) ]
     |> cons (sgName name))

let private sgTyParamList ctx (tyParamListOpt: ATyParamList option) =
  match tyParamListOpt with
  | Some (lPos, tyParams, rOpt) ->
    buildNode
      Sk.GenericParamList
      ([ [ newAnchor lPos ] ]
       |> consListMap sgName tyParams
       |> consOptionMap newAnchor rOpt)
    |> Some

  | None -> None

let private sgTyArgList (ctx: SgCtx) (tyArgListOpt: ATyArgList option) =
  match tyArgListOpt with
  | Some (lPos, tyArgs, rOpt) ->
    buildNode
      Sk.GenericArgList
      ([ [ newAnchor lPos ] ]
       |> consListMap (sgTy ctx) tyArgs
       |> consOptionMap newAnchor rOpt)
    |> Some

  | None -> None

let private sgTy (ctx: SgCtx) (ty: ATy) : SyntaxElement =
  let onTy ty = sgTy ctx ty

  match ty with
  | AMissingTy pos -> newNode SyntaxKind.MissingTy [ newAnchor pos ]

  | AAppTy (quals, name, tyArgList) ->
    buildNode
      SyntaxKind.PathTy
      ([ [ sgPath quals name ] ]
       |> consOpt (sgTyArgList ctx tyArgList))

  | AVarTy name -> newNode SyntaxKind.VarTy [ sgName name ]

  | AParenTy (lPos, bodyTy, rOpt) ->
    buildNode
      Sk.ParenTy
      ([ [ newAnchor lPos ] ]
       |> cons (onTy bodyTy)
       |> consOptionMap newAnchor rOpt)

  | ASuffixTy (bodyTy, suffix) -> newNode Sk.SuffixTy [ onTy bodyTy; sgName suffix ]
  | ATupleTy (itemTys, _) -> newNode SyntaxKind.TupleTy (itemTys |> List.map onTy)
  | AFunTy (lTy, _, rTy) -> newNode Sk.FunTy [ onTy lTy; onTy rTy ]

let private sgPat (ctx: SgCtx) (pat: APat) : SyntaxElement =
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat

  match pat with
  | AMissingPat pos -> newNode Sk.MissingPat [ newAnchor pos ]
  | ALitPat (_, pos) -> newNode Sk.LitPat [ newAnchor pos ]
  | AIdentPat (_, name) -> newNode Sk.IdentPat [ sgName name ]

  | AParenPat (lPos, bodyPat, rPos) ->
    buildNode
      Sk.ParenPat
      ([ [ newAnchor lPos ] ]
       |> cons (onPat bodyPat)
       |> consOptionMap newAnchor rPos)

  | AListPat (lPos, itemPats, rPos) ->
    buildNode
      Sk.ListPat
      ([ [ newAnchor lPos ] ]
       |> consListMap onPat itemPats
       |> consOptionMap newAnchor rPos)

  | ANavPat (lPat, dotPos, r) ->
    newNode
      Sk.NavPat
      [ onPat lPat
        newAnchor dotPos
        sgName r ]

  | AAppPat (lPat, _, rPat) -> newNode Sk.AppPat [ onPat lPat; onPat rPat ]

  | AConsPat (lPat, opPos, rPat) ->
    newNode
      Sk.ConsPat
      [ onPat lPat
        newAnchor opPos
        onPat rPat ]

  | ATuplePat (itemPats, _) -> newNode Sk.TuplePat (itemPats |> List.map onPat)

  | AAsPat (bodyPat, asPos, name) ->
    newNode
      Sk.AsPat
      [ onPat bodyPat
        newAnchor asPos
        sgName name ]

  | AAscribePat (bodyPat, colonPos, ty) ->
    newNode
      Sk.AscribePat
      [ onPat bodyPat
        newAnchor colonPos
        onTy ty ]

  | AOrPat (lPat, pipePos, rPat) ->
    newNode
      Sk.OrPat
      [ onPat lPat
        newAnchor pipePos
        onPat rPat ]

let private sgExpr (ctx: SgCtx) (expr: AExpr) : SyntaxElement =
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat
  let onPats pats = pats |> List.map (sgPat ctx)
  let onExpr expr = sgExpr ctx expr
  let onExprs exprs = exprs |> List.map onExpr

  match expr with
  | AMissingExpr pos -> newNode SyntaxKind.MissingExpr [ newAnchor pos ]
  | ALitExpr (_, pos) -> newNode SyntaxKind.LiteralExpr [ newAnchor pos ]

  | AIdentExpr (name, tyArgList) ->
    buildNode
      Sk.NameExpr
      ([ [ sgName name ] ]
       |> consOpt (sgTyArgList ctx tyArgList))

  | AParenExpr (lPos, body, rOpt) ->
    buildNode
      Sk.ParenExpr
      ([ [ newAnchor lPos ] ]
       |> cons (onExpr body)
       |> consOptionMap newAnchor rOpt)

  | AListExpr (lPos, items, rOpt) ->
    buildNode
      SyntaxKind.ListExpr
      ([ [ newAnchor lPos ] ]
       |> consListMap onExpr items
       |> consOptionMap newAnchor rOpt)

  | ARecordExpr (lPos, withClauseOpt, fields, rOpt) ->
    buildNode
      SyntaxKind.RecordExpr
      ([ [ newAnchor lPos ] ]
       |> consOpt (
         match withClauseOpt with
         | Some (baseExpr, withOpt) ->
           buildNode
             Sk.WithClause
             ([ [ onExpr baseExpr ] ]
              |> consOptionMap newAnchor withOpt)
           |> Some

         | None -> None
       )
       |> consList (
         fields
         |> List.map (fun (ident, equalPos, init) ->
           newNode
             SyntaxKind.FieldInit
             [ sgName ident
               newAnchor equalPos
               onExpr init ])
       )
       |> consOptionMap newAnchor rOpt)

  | AIfExpr (ifPos, cond, thenPos, body, altOpt) ->
    buildNode
      SyntaxKind.IfExpr
      ([ [ newAnchor ifPos ] ]
       |> cons (onExpr cond)
       |> cons (
         buildNode
           Sk.ThenClause
           ([]
            |> consOpt (sgThen ctx thenPos)
            |> cons (onExpr body))
       )
       |> consOpt (
         match altOpt with
         | Some (elsePos, alt) ->
           newNode Sk.ElseClause [ newAnchor elsePos; onExpr alt ]
           |> Some
         | None -> None
       ))

  | AMatchExpr (matchPos, cond, withOpt, arms) ->
    buildNode
      SyntaxKind.MatchExpr
      ([ [ newAnchor matchPos ] ]
       |> cons (onExpr cond)
       |> consOptionMap newAnchor withOpt
       |> consList (
         arms
         |> List.map (fun (pipeOpt, pat, guardOpt, arrowPos, body) ->
           buildNode
             Sk.Arm
             ([]
              |> consOptionMap newAnchor pipeOpt
              |> cons (onPat pat)
              |> consOpt (
                match guardOpt with
                | Some (whenPos, guard) ->
                  newNode Sk.GuardClause [ newAnchor whenPos; onExpr guard ]
                  |> Some

                | None -> None
              )
              |> consOpt (sgArrow ctx arrowPos)
              |> cons (onExpr body)))
       ))

  | AFunExpr (funPos, argPats, arrowPos, body) ->
    buildNode
      SyntaxKind.FunExpr
      ([ [ newAnchor funPos ] ]
       |> cons (newNode Sk.ParamList (onPats argPats))
       |> consOpt (sgArrow ctx arrowPos)
       |> cons (onExpr body))

  | ANavExpr (l, dotPos, r) -> newNode SyntaxKind.NavExpr [ onExpr l; newAnchor dotPos; sgName r ]

  | AIndexExpr (l, dotPos, lPos, r, rOpt) ->
    buildNode
      SyntaxKind.IndexExpr
      ([ [ onExpr l
           newAnchor dotPos
           newAnchor lPos
           onExpr r ] ]
       |> consOptionMap newAnchor rOpt)

  | AUnaryExpr (_, opPos, arg) -> newNode SyntaxKind.UnaryExpr [ newAnchor opPos; onExpr arg ]

  | ABinaryExpr (AppBinary, l, _, r) -> newNode Sk.AppExpr (onExprs [ l; r ])
  | ABinaryExpr (_, l, opPos, r) -> newNode SyntaxKind.BinaryExpr ([ onExpr l; newAnchor opPos; onExpr r ])
  | ARangeExpr (l, opPos, r) -> newNode SyntaxKind.RangeExpr ([ onExpr l; newAnchor opPos; onExpr r ])
  | ATupleExpr (items, _) -> newNode SyntaxKind.TupleExpr (onExprs items)
  | AAscribeExpr (l, colonPos, rTy) ->
    newNode
      SyntaxKind.AscribeExpr
      [ onExpr l
        newAnchor colonPos
        onTy rTy ]

  | ASemiExpr ([], last, _) -> onExpr last
  | ASemiExpr (stmts, last, _) -> buildNode SyntaxKind.BlockExpr ([ onExprs stmts ] |> cons (onExpr last))

  | ALetExpr (letPos, contents, next) ->
    match contents with
    | ALetContents.LetVal (_, pat, equalPos, init) ->
      buildNode
        SyntaxKind.LetValExpr
        ([ [ newAnchor letPos; onPat pat ] ]
         |> consOpt (sgEqual ctx equalPos)
         |> consList (onExprs [ init; next ]))

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, equalPos, body) ->
      buildNode
        SyntaxKind.LetFunExpr
        ([ [ sgName name ] ]
         |> cons (newNode Sk.ParamList (onPats argPats))
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ newAnchor colonPos; onTy ty ]
           | None -> []
         )
         |> consOpt (sgEqual ctx equalPos)
         |> consList (onExprs [ body; next ]))

let private sgDecl (ctx: SgCtx) decl : SyntaxElement =
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat
  let onExpr expr = sgExpr ctx expr
  let onDecls decls = decls |> List.map (sgDecl ctx)

  let onTyHead typePos name tyParamList equalPos =
    [ [ newAnchor typePos; sgName name ] ]
    |> consOpt (sgTyParamList ctx tyParamList)
    |> consOpt (sgEqual ctx equalPos)

  match decl with
  | AExprDecl expr -> newNode SyntaxKind.ExprDecl [ onExpr expr ]

  | ALetDecl (letPos, contents) ->
    match contents with
    | ALetContents.LetVal (_, pat, equalPos, init) ->
      buildNode
        SyntaxKind.LetValDecl
        ([ [ newAnchor letPos; onPat pat ] ]
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr init))

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, equalPos, body) ->
      buildNode
        SyntaxKind.LetFunDecl
        ([ [ newAnchor letPos; sgName name ] ]
         |> cons (newNode Sk.ParamList (argPats |> List.map onPat))
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ newAnchor colonPos; onTy ty ]
           | None -> []
         )
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr body))

  | ATySynonymDecl (typePos, _, name, tyParamList, equalPos, ty) ->
    buildNode
      Sk.TySynonymDecl
      (onTyHead typePos name tyParamList equalPos
       |> cons (onTy ty))

  | AUnionTyDecl (typePos, _, name, tyParamList, equalPos, variants) ->
    buildNode
      Sk.UnionTyDecl
      (onTyHead typePos name tyParamList equalPos
       |> consList (
         variants
         |> List.map (fun (pipePos, name, payloadOpt) ->
           buildNode
             Sk.VariantDecl
             ([]
              |> consOpt (sgPipe ctx pipePos)
              |> cons (sgName name)
              |> consList (
                match payloadOpt with
                | Some (ofPos, ty) -> [ newAnchor ofPos; onTy ty ]
                | None -> []
              )))
       ))

  | ARecordTyDecl (typePos, _, name, tyParamList, equalPos, lPos, fields, rPos) ->
    buildNode
      Sk.RecordTyDecl
      (onTyHead typePos name tyParamList equalPos
       |> cons (newAnchor lPos)
       |> consList (
         fields
         |> List.map (fun (name, ty, _) -> newNode Sk.FieldDecl [ sgName name; onTy ty ])
       )
       |> consOptionMap (newAnchor) rPos)

  | AOpenDecl (openPos, path) ->
    newNode
      Sk.OpenDecl
      [ newAnchor openPos
        newNode Sk.Path (path |> List.map sgName) ]

  | AModuleSynonymDecl (modulePos, name, equalPos, path) ->
    buildNode
      Sk.ModuleSynonymDecl
      ([ [ newAnchor modulePos; sgName name ] ]
       |> consOpt (sgEqual ctx equalPos)
       |> cons (newNode Sk.Path (path |> List.map sgName)))

  | AModuleDecl (modulePos, _, _, name, equalPos, decls) ->
    buildNode
      SyntaxKind.ModuleDecl
      ([ [ newAnchor modulePos; sgName name ] ]
       |> consOpt (sgEqual ctx equalPos)
       |> consList (onDecls decls))

  | AAttrDecl (lPos, attr, rOpt, next) ->
    buildNode
      SyntaxKind.AttrDecl
      ([ [ newAnchor lPos; onExpr attr ] ]
       |> consOptionMap (newAnchor) rOpt
       |> cons (sgDecl ctx next))

let private sgRoot (ctx: SgCtx) root : SyntaxElement =
  let (ARoot (headOpt, decls)) = root

  buildNode
    SyntaxKind.Root
    ([]
     |> consOpt (
       match headOpt with
       | Some (modulePos, path) ->
         newNode
           SyntaxKind.ModuleHead
           [ newAnchor modulePos
             newNode Sk.Path (path |> List.map sgName) ]
         |> Some

       | _ -> None
     )
     |> consListMap (sgDecl ctx) decls)

// -----------------------------------------------
// Postprocess
// -----------------------------------------------

/// Takes (leading) trivias.
let private takeLeadingTrivias (rangeMap: TokenRangeMap) tokens =
  let isLeading token =
    match token with
    | ErrorToken _
    | NewlinesToken _
    | BlankToken _
    | CommentToken _ -> true
    | _ -> false

  let rec go acc tokens =
    match tokens with
    | (token, pos) :: tokens when isLeading token ->
      let _, endPos = rangeMap |> mapFind pos
      go (wrapToken (token, (pos, endPos)) :: acc) tokens

    | _ -> List.rev acc, tokens

  go [] tokens

/// Takes trailing (non-newline) trivias.
let private takeTrailingTrivias (rangeMap: TokenRangeMap) tokens =
  let isTrailing token =
    match token with
    | ErrorToken _
    | BlankToken _
    | CommentToken _ -> true
    | _ -> false

  let rec go acc tokens =
    match tokens with
    | (token, pos) :: tokens when isTrailing token ->
      let _, endPos = rangeMap |> mapFind pos
      go (wrapToken (token, (pos, endPos)) :: acc) tokens

    | _ -> List.rev acc, tokens

  go [] tokens

let private takeTokensBefore (rangeMap: TokenRangeMap) untilPos tokens =
  let rec go acc tokens =
    let tokensOrig = tokens

    match tokens with
    | (token, pos) :: tokens ->
      let _, endPos = rangeMap |> mapFind pos

      if Pos.compare pos untilPos < 0 then
        go (wrapToken (token, (pos, endPos)) :: acc) tokens
      else
        List.rev acc, tokensOrig

    | _ -> List.rev acc, tokens

  go [] tokens

/// Takes tokens until a position (inclusive).
let private takeTokensUntil (rangeMap: TokenRangeMap) untilPos tokens =
  let rec go acc tokens =
    let tokensOrig = tokens

    match tokens with
    | (token, pos) :: tokens ->
      let _, endPos = rangeMap |> mapFind pos

      if Pos.compare pos untilPos <= 0 then
        go (wrapToken (token, (pos, endPos)) :: acc) tokens
      else
        List.rev acc, tokensOrig

    | _ -> List.rev acc, tokens

  go [] tokens

let private postprocess
  (tokens: TokenizeFullResult)
  (rangeMap: TokenRangeMap)
  (eofPos: Pos)
  (root: SyntaxElement)
  : SyntaxElement =
  let shrinkRange elements range =
    match List.tryLast elements with
    | Some t ->
      let _, m = getRange t
      let p, q = range
      Pos.max p m, q

    | None -> range

  let rec go (availableRange: Range) tokens element =
    match element with
    | SyntaxToken (_, (pos, _)) ->
      // Don't relay on the kind and trust token stream.

      // Take all tokens before and at the position.
      let middle, tokens = takeTokensUntil rangeMap pos tokens

      let trailing, tokens = takeTrailingTrivias rangeMap tokens
      List.collect id [ middle; trailing ], tokens

    | SyntaxNode (kind, _, children) ->
      let leading, tokens = takeLeadingTrivias rangeMap tokens
      let availableRange = shrinkRange leading availableRange

      let children, (availableRange, tokens) =
        children
        |> listCollectFold
             (fun (availableRange, tokens) child ->
               // Take tokens not covered by this child.
               let rec leftmost element =
                 match element with
                 | SyntaxToken (_, pos) -> Some pos
                 | SyntaxNode (_, _, children) -> List.tryPick leftmost children

               let middle, tokens =
                 match leftmost child with
                 | Some (pos, _) -> takeTokensBefore rangeMap pos tokens
                 | None -> [], tokens

               let availableRange = shrinkRange middle availableRange

               let leading, tokens = takeLeadingTrivias rangeMap tokens
               let availableRange = shrinkRange leading availableRange

               let child, tokens = go availableRange tokens child
               let availableRange = shrinkRange child availableRange

               let trailing, tokens = takeTrailingTrivias rangeMap tokens
               let availableRange = shrinkRange trailing availableRange

               let elements =
                 List.collect id [ middle; leading; child; trailing ]

               elements, (availableRange, tokens))
             (availableRange, tokens)

      let trailing, tokens = takeTrailingTrivias rangeMap tokens

      let elements =
        List.collect id [ leading; children; trailing ]

      let range =
        match elements with
        | [] ->
          let pos, _ = shrinkRange elements availableRange
          pos, pos

        | first :: nonFirst ->
          match List.tryLast nonFirst with
          | Some last -> Range.join (getRange first) (getRange last)
          | None -> getRange first

      [ SyntaxNode(kind, range, children) ], tokens

  let wholeRange: Range = Pos.zero, eofPos

  let rootLeadingTokens, tokens = takeLeadingTrivias rangeMap tokens

  match go wholeRange tokens root with
  | [ SyntaxNode (kind, _, children) ], tokens ->
    let trailing =
      tokens
      |> List.map (fun (token, pos) ->
        let _, endPos = rangeMap |> mapFind pos
        wrapToken (token, (pos, endPos)))

    let children =
      List.collect
        id
        [ rootLeadingTokens
          children
          trailing ]

    SyntaxNode(kind, wholeRange, children)

  | _ -> unreachable ()

// -----------------------------------------------
// Validate
// -----------------------------------------------

let private stValidate rangeMap (tokens: TokenizeFullResult) (root: SyntaxElement) =
  let rec go tokens element =
    match element, tokens with
    | SyntaxToken (kind, range), (k, pos) :: tokens ->
      let _, endPos = rangeMap |> mapFind pos

      let p1, q1 = range

      if Pos.compare p1 pos = 0
         && Pos.compare q1 endPos = 0 then
        // check kind
        true, tokens
      else
        __trace (
          "token/tree mismatch. Next token: "
          + __dump (k, pos)
          + " but was SyntaxToken: "
          + __dump (kind, range)
        )

        false, tokens

    | SyntaxToken _, _ ->
      __trace (
        "token/tree mismatch. Expected no token but was: "
        + __dump element
      )

      false, tokens

    | SyntaxNode (_, _, children), _ ->
      children
      |> List.fold
           (fun (ok, tokens) child ->
             if ok then
               go tokens child
             else
               false, tokens)
           (true, tokens)

  match go tokens root with
  | true, (token :: _) ->
    __trace (
      "token/tree mismatch. Syntax tree didn't contain: "
      + __dump token
    )

    false

  | ok, _ -> ok

// -----------------------------------------------
// Dump
// -----------------------------------------------

let private sdRange range =
  let pos, endPos = range

  "\""
  + Pos.toString pos
  + ".."
  + Pos.toString endPos
  + "\""

let private sdElement rx indent (element: SyntaxElement) =
  match element with
  | SyntaxToken (kind, tokenRange) ->
    let pos, _ = tokenRange
    let range = sdRange tokenRange

    let map: TokenRangeMap = rx

    match resolveTokenRange map pos with
    | Some (token, _) ->
      match token with
      | IntToken (text, flavorOpt) ->
        let flavor =
          match flavorOpt with
          | Some flavor ->
            let item =
              match flavor with
              | I8 -> "int8"
              | I16 -> "int16"
              | I32 -> "int"
              | I64 -> "int64"
              | IPtr -> "nativeint"
              | U8 -> "byte"
              | U16 -> "uint16"
              | U32 -> "uint"
              | U64 -> "uint64"
              | UPtr -> "unativeint"

            ", \"" + item + "\""

          | None -> ""

        "[\"Int\", " + range + ", " + text + flavor + "]"

      | FloatToken text -> "[\"Float\", " + range + ", " + text + "]"

      | CharToken c ->
        let value =
          if c <> '\x00' then
            Json.dump (JString(string c))
          else
            "\"\\u0000\""

        "[\"Char\", " + range + ", " + value + "]"

      | StringToken s ->
        "[\"String\", "
        + range
        + ", "
        + Json.dump (JString s)
        + "]"

      | IdentToken text ->
        "[\"Ident\", "
        + range
        + ", "
        + Json.dump (JString text)
        + "]"

      | TyVarToken text -> "[\"TyVar\", " + range + "\"'" + text + "\"]"

      | NewlinesToken ->
        let (y1, x1), (y2, x2) = tokenRange
        let blank = if y1 < y2 then x2 else x1 + x2

        "[\"Newlines\", "
        + range
        + ", \""
        + String.replicate (y2 - y1) "\\n"
        + String.replicate blank " "
        + "\"]"

      | CommentToken -> "[\"Comment\", " + range + "]"

      | _ -> "[\"" + __dump kind + "\", " + range + "]"

    | None -> "[\"" + __dump kind + "\", " + range + "]"

  | SyntaxNode (kind, range, []) ->
    "[\""
    + __dump kind
    + "\", "
    + sdRange range
    + ", []]"

  | SyntaxNode (kind, range, children) ->
    let range = sdRange range

    let s =
      "[\"" + __dump kind + "\", " + range + ", ["

    let t =
      let deepIndent = indent + "  "

      children
      |> List.map (fun child -> "\n" + deepIndent + sdElement rx deepIndent child)
      |> S.concat ","

    s + t + "\n" + indent + "]]"

let private sdRoot (rangeMap: TokenRangeMap) (root: SyntaxElement) : string = sdElement rangeMap "" root

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genSyntaxTree (tokens: TokenizeFullResult) (ast: ARoot) : SyntaxTree =
  let eofPos: Pos =
    match List.tryLast tokens with
    | Some (_, (y, _)) -> y + 1, 0
    | None -> 0, 0

  let rangeMap = toTokenRangeMap tokens eofPos
  let ctx: SgCtx = SgCtx rangeMap

  sgRoot ctx ast
  |> postprocess tokens rangeMap eofPos
  |> SyntaxTree

let dumpTree (tokens: TokenizeFullResult) (ast: ARoot) : string =
  let eofPos: Pos =
    match List.tryLast tokens with
    | Some (_, (y, _)) -> y + 1, 0
    | None -> 0, 0

  let rangeMap = toTokenRangeMap tokens eofPos
  let ctx: SgCtx = SgCtx rangeMap

  let root =
    sgRoot ctx ast
    |> postprocess tokens rangeMap eofPos

  if not (stValidate rangeMap tokens root) then
    __trace "violated!"

  // assert (stValidate rangeMap tokens root)
  sdRoot rangeMap root
