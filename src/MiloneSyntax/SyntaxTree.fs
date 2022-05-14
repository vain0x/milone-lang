module rec MiloneSyntax.SyntaxTree

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError
open Std.StdPair
open Std.StdMap

module C = Std.StdChar
module S = Std.StdString

// -----------------------------------------------
// Util
// -----------------------------------------------

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
// SyntaxKind
// -----------------------------------------------

let private kindOfToken token =
  match token with
  | ErrorToken _ -> SyntaxKind.Bad
  | BlankToken -> SyntaxKind.Blank
  | NewlinesToken -> SyntaxKind.Newlines
  | CommentToken -> SyntaxKind.Comment
  | IntToken _ -> SyntaxKind.Int
  | FloatToken _ -> SyntaxKind.Float
  | CharToken _ -> SyntaxKind.Char
  | StringToken _ -> SyntaxKind.String
  | IdentToken _ -> SyntaxKind.Ident
  | TyVarToken _ -> SyntaxKind.TyVar
  | LeftParenToken -> SyntaxKind.LeftParen
  | RightParenToken -> SyntaxKind.RightParen
  | LeftBracketToken -> SyntaxKind.LeftBracket
  | RightBracketToken -> SyntaxKind.RightBracket
  | LeftBraceToken -> SyntaxKind.LeftBrace
  | RightBraceToken -> SyntaxKind.RightBrace
  | LeftAngleToken _ -> SyntaxKind.LeftAngle
  | RightAngleToken -> SyntaxKind.RightAngle
  | LeftAttrToken -> SyntaxKind.LeftAttr
  | RightAttrToken -> SyntaxKind.RightAttr
  | AmpToken -> SyntaxKind.Amp
  | AmpAmpToken _ -> SyntaxKind.AmpAmp
  | AmpAmpAmpToken -> SyntaxKind.AmpAmpAmp
  | ArrowToken -> SyntaxKind.Arrow
  | ColonToken -> SyntaxKind.Colon
  | ColonColonToken -> SyntaxKind.ColonColon
  | CommaToken -> SyntaxKind.Comma
  | DotToken -> SyntaxKind.Dot
  | DotDotToken -> SyntaxKind.DotDot
  | EqualToken -> SyntaxKind.Equal
  | HatToken -> SyntaxKind.Hat
  | HatHatHatToken -> SyntaxKind.HatHatHat
  | LeftEqualToken -> SyntaxKind.LeftEqual
  | LeftLeftToken -> SyntaxKind.LeftLeft
  | LeftLeftLeftToken -> SyntaxKind.LeftLeftLeft
  | LeftRightToken -> SyntaxKind.LeftRight
  | RightEqualToken -> SyntaxKind.RightEqual
  | MinusToken _ -> SyntaxKind.Minus
  | PercentToken -> SyntaxKind.Percent
  | PipeToken -> SyntaxKind.Pipe
  | PipeRightToken -> SyntaxKind.PipeRight
  | PipePipeToken -> SyntaxKind.PipePipe
  | PipePipePipeToken -> SyntaxKind.PipePipePipe
  | PlusToken -> SyntaxKind.Plus
  | SemiToken -> SyntaxKind.Semi
  | SlashToken -> SyntaxKind.Slash
  | StarToken -> SyntaxKind.Star
  | AsToken -> SyntaxKind.As
  | ElseToken -> SyntaxKind.Else
  | FalseToken -> SyntaxKind.False
  | FunToken -> SyntaxKind.Fun
  | IfToken -> SyntaxKind.If
  | InToken -> SyntaxKind.In
  | LetToken -> SyntaxKind.Let
  | MatchToken -> SyntaxKind.Match
  | ModuleToken -> SyntaxKind.Module
  | OfToken -> SyntaxKind.Of
  | OpenToken -> SyntaxKind.Open
  | PrivateToken -> SyntaxKind.Private
  | PublicToken -> SyntaxKind.Public
  | RecToken -> SyntaxKind.Rec
  | ThenToken -> SyntaxKind.Then
  | TrueToken -> SyntaxKind.True
  | TypeToken -> SyntaxKind.Type
  | WhenToken -> SyntaxKind.When
  | WithToken -> SyntaxKind.With

let private kindToString kind =
  match kind with
  | SyntaxKind.Bad -> "Bad"
  | SyntaxKind.Blank -> "Blank"
  | SyntaxKind.Newlines -> "Newlines"
  | SyntaxKind.Comment -> "Comment"
  | SyntaxKind.Int -> "Int"
  | SyntaxKind.Float -> "Float"
  | SyntaxKind.Char -> "Char"
  | SyntaxKind.String -> "String"
  | SyntaxKind.Ident -> "Ident"
  | SyntaxKind.TyVar -> "TyVar"
  | SyntaxKind.LeftParen -> "LeftParen"
  | SyntaxKind.RightParen -> "RightParen"
  | SyntaxKind.LeftBracket -> "LeftBracket"
  | SyntaxKind.RightBracket -> "RightBracket"
  | SyntaxKind.LeftBrace -> "LeftBrace"
  | SyntaxKind.RightBrace -> "RightBrace"
  | SyntaxKind.LeftAngle -> "LeftAngle"
  | SyntaxKind.RightAngle -> "RightAngle"
  | SyntaxKind.LeftAttr -> "LeftAttr"
  | SyntaxKind.RightAttr -> "RightAttr"
  | SyntaxKind.Amp -> "Amp"
  | SyntaxKind.AmpAmp -> "AmpAmp"
  | SyntaxKind.AmpAmpAmp -> "AmpAmpAmp"
  | SyntaxKind.Arrow -> "Arrow"
  | SyntaxKind.Colon -> "Colon"
  | SyntaxKind.ColonColon -> "ColonColon"
  | SyntaxKind.Comma -> "Comma"
  | SyntaxKind.Dot -> "Dot"
  | SyntaxKind.DotDot -> "DotDot"
  | SyntaxKind.Equal -> "Equal"
  | SyntaxKind.Hat -> "Hat"
  | SyntaxKind.HatHatHat -> "HatHatHat"
  | SyntaxKind.LeftEqual -> "LeftEqual"
  | SyntaxKind.LeftLeft -> "LeftLeft"
  | SyntaxKind.LeftLeftLeft -> "LeftLeftLeft"
  | SyntaxKind.LeftRight -> "LeftRight"
  | SyntaxKind.RightEqual -> "RightEqual"
  | SyntaxKind.Minus -> "Minus"
  | SyntaxKind.Percent -> "Percent"
  | SyntaxKind.Pipe -> "Pipe"
  | SyntaxKind.PipeRight -> "PipeRight"
  | SyntaxKind.PipePipe -> "PipePipe"
  | SyntaxKind.PipePipePipe -> "PipePipePipe"
  | SyntaxKind.Plus -> "Plus"
  | SyntaxKind.Semi -> "Semi"
  | SyntaxKind.Slash -> "Slash"
  | SyntaxKind.Star -> "Star"
  | SyntaxKind.As -> "As"
  | SyntaxKind.Else -> "Else"
  | SyntaxKind.False -> "False"
  | SyntaxKind.Fun -> "Fun"
  | SyntaxKind.If -> "If"
  | SyntaxKind.In -> "In"
  | SyntaxKind.Let -> "Let"
  | SyntaxKind.Match -> "Match"
  | SyntaxKind.Module -> "Module"
  | SyntaxKind.Of -> "Of"
  | SyntaxKind.Open -> "Open"
  | SyntaxKind.Private -> "Private"
  | SyntaxKind.Public -> "Public"
  | SyntaxKind.Rec -> "Rec"
  | SyntaxKind.Then -> "Then"
  | SyntaxKind.True -> "True"
  | SyntaxKind.Type -> "Type"
  | SyntaxKind.When -> "When"
  | SyntaxKind.With -> "With"

  | SyntaxKind.TyParamList -> "TyParamList"
  | SyntaxKind.TyArgList -> "TyArgList"
  | SyntaxKind.WithClause -> "WithClause"
  | SyntaxKind.FieldInit -> "FieldInit"
  | SyntaxKind.ElseClause -> "ElseClause"
  | SyntaxKind.GuardClause -> "GuardClause"
  | SyntaxKind.Arm -> "Arm"
  | SyntaxKind.LabeledTy -> "LabeledTy"
  | SyntaxKind.VariantDecl -> "VariantDecl"
  | SyntaxKind.FieldDecl -> "FieldDecl"
  | SyntaxKind.ModulePath -> "ModulePath"
  | SyntaxKind.ModuleHead -> "ModuleHead"

  // Ty:
  | SyntaxKind.MissingTy -> "MissingTy"
  | SyntaxKind.NameTy -> "NameTy"
  | SyntaxKind.VarTy -> "VarTy"
  | SyntaxKind.ParenTy -> "ParenTy"
  | SyntaxKind.SuffixTy -> "SuffixTy"
  | SyntaxKind.TupleTy -> "TupleTy"
  | SyntaxKind.FunTy -> "FunTy"

  // Pat:
  | SyntaxKind.MissingPat -> "MissingPat"
  | SyntaxKind.LiteralPat -> "LiteralPat"
  | SyntaxKind.WildcardPat -> "WildcardPat"
  | SyntaxKind.VarPat -> "VarPat"
  | SyntaxKind.PathPat -> "PathPat"
  | SyntaxKind.ParenPat -> "ParenPat"
  | SyntaxKind.ListPat -> "ListPat"
  | SyntaxKind.WrapPat -> "WrapPat"
  | SyntaxKind.ConsPat -> "ConsPat"
  | SyntaxKind.AscribePat -> "AscribePat"
  | SyntaxKind.TuplePat -> "TuplePat"
  | SyntaxKind.AsPat -> "AsPat"
  | SyntaxKind.OrPat -> "OrPat"

  // Expr:
  | SyntaxKind.MissingExpr -> "MissingExpr"
  | SyntaxKind.LiteralExpr -> "LiteralExpr"
  | SyntaxKind.NameExpr -> "NameExpr"
  | SyntaxKind.PathExpr -> "PathExpr"
  | SyntaxKind.ParenExpr -> "ParenExpr"
  | SyntaxKind.ListExpr -> "ListExpr"
  | SyntaxKind.RecordExpr -> "RecordExpr"
  | SyntaxKind.IfExpr -> "IfExpr"
  | SyntaxKind.MatchExpr -> "MatchExpr"
  | SyntaxKind.FunExpr -> "FunExpr"
  | SyntaxKind.IndexExpr -> "IndexExpr"
  | SyntaxKind.UnaryExpr -> "UnaryExpr"
  | SyntaxKind.AppExpr -> "AppExpr"
  | SyntaxKind.BinaryExpr -> "BinaryExpr"
  | SyntaxKind.RangeExpr -> "RangeExpr"
  | SyntaxKind.TupleExpr -> "TupleExpr"
  | SyntaxKind.AscribeExpr -> "AscribeExpr"
  | SyntaxKind.BlockExpr -> "BlockExpr"
  | SyntaxKind.LetValExpr -> "LetValExpr"
  | SyntaxKind.LetFunExpr -> "LetFunExpr"

  // Decl:
  | SyntaxKind.ExprDecl -> "ExprDecl"
  | SyntaxKind.LetValDecl -> "LetValDecl"
  | SyntaxKind.LetFunDecl -> "LetFunDecl"
  | SyntaxKind.TySynonymDecl -> "TySynonymDecl"
  | SyntaxKind.UnionTyDecl -> "UnionTyDecl"
  | SyntaxKind.RecordTyDecl -> "RecordTyDecl"
  | SyntaxKind.OpenDecl -> "OpenDecl"
  | SyntaxKind.ModuleDecl -> "ModuleDecl"
  | SyntaxKind.ModuleSynonymDecl -> "ModuleSynonymDecl"
  | SyntaxKind.AttrDecl -> "AttrDecl"

  | SyntaxKind.Root -> "Root"

// -----------------------------------------------
// SyntaxElement
// -----------------------------------------------

/// Converts a token with range to syntax element.
let private wrapToken (token, range) = SyntaxToken(kindOfToken token, range)

let private getRange element =
  match element with
  | SyntaxToken (_, range) -> range
  | SyntaxNode (_, range, _) -> range

// -----------------------------------------------
// Builder
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private BuilderElement =
  | Anchor of Pos
  | Node of SyntaxKind * children: BuilderElement list

let private newAnchor pos = BuilderElement.Anchor pos

let private newNode kind children = BuilderElement.Node(kind, children)

let private buildNode kind childrenRev =
  BuilderElement.Node(kind, childrenRev |> List.rev |> List.collect id)

// -----------------------------------------------
// Syntax Tree Generation
// -----------------------------------------------

// sg: syntax tree generation

/// Context of syntax tree generation.
type private SgCtx = SgCtx of TokenRangeMap

// Parser might produce incorrect position.
/// Anchor of a token of the specified kind. #incorrectPos
let private sgTokenChecked (rx: SgCtx) token pos =
  let (SgCtx rangeMap) = rx

  match token, rangeMap |> TMap.tryFind pos with
  | ThenToken, Some (ThenToken, _) -> Some(newAnchor pos)
  | ArrowToken, Some (ArrowToken, _) -> Some(newAnchor pos)
  | EqualToken, Some (EqualToken, _) -> Some(newAnchor pos)
  | PipeToken, Some (PipeToken, _) -> Some(newAnchor pos)

  | ThenToken, _
  | ArrowToken, _
  | EqualToken, _
  | PipeToken, _ -> None
  | _ -> unreachable ()

let private sgThen ctx pos = sgTokenChecked ctx ThenToken pos
let private sgArrow ctx pos = sgTokenChecked ctx ArrowToken pos
let private sgEqual ctx pos = sgTokenChecked ctx EqualToken pos
let private sgPipe ctx pos = sgTokenChecked ctx PipeToken pos

let private sgName name =
  let (Name (_, pos)) = name
  newAnchor pos

let private sgTyParamList (tyParamListOpt: ATyParamList option) =
  match tyParamListOpt with
  | Some (lPos, tyParams, rOpt) ->
    buildNode
      SyntaxKind.TyParamList
      ([ [ newAnchor lPos ] ]
       |> consListMap sgName tyParams
       |> consOptionMap newAnchor rOpt)
    |> Some

  | None -> None

let private sgTyArgList (ctx: SgCtx) (tyArgListOpt: ATyArgList option) =
  match tyArgListOpt with
  | Some (lPos, tyArgs, rOpt) ->
    buildNode
      SyntaxKind.TyArgList
      ([ [ newAnchor lPos ] ]
       |> consListMap (sgTy ctx) tyArgs
       |> consOptionMap newAnchor rOpt)
    |> Some

  | None -> None

let private sgTy (ctx: SgCtx) (ty: ATy) : BuilderElement =
  let onTy ty = sgTy ctx ty

  match ty with
  | AMissingTy pos -> newNode SyntaxKind.MissingTy [ newAnchor pos ]

  | AAppTy (quals, name, tyArgList) ->
    buildNode
      SyntaxKind.NameTy
      (quals
       |> List.map (fun (name, pos) -> [ sgName name; newAnchor pos ])
       |> cons (sgName name)
       |> consOpt (sgTyArgList ctx tyArgList))

  | AVarTy name -> newNode SyntaxKind.VarTy [ sgName name ]

  | AParenTy (lPos, bodyTy, rOpt) ->
    buildNode
      SyntaxKind.ParenTy
      ([ [ newAnchor lPos ] ]
       |> cons (onTy bodyTy)
       |> consOptionMap newAnchor rOpt)

  | ASuffixTy (bodyTy, suffix) -> newNode SyntaxKind.SuffixTy [ onTy bodyTy; sgName suffix ]
  | ATupleTy (itemTys, _) -> newNode SyntaxKind.TupleTy (itemTys |> List.map onTy)
  | AFunTy (lTy, _, rTy) -> newNode SyntaxKind.FunTy [ onTy lTy; onTy rTy ]

let private sgPat (ctx: SgCtx) (pat: APat) : BuilderElement =
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat

  match pat with
  | AMissingPat pos -> newNode SyntaxKind.MissingPat [ newAnchor pos ]
  | ALitPat (_, pos) -> newNode SyntaxKind.LiteralPat [ newAnchor pos ]
  | AIdentPat (_, Name ("_", pos)) -> newNode SyntaxKind.WildcardPat [ newAnchor pos ]
  | AIdentPat (visOpt, name) ->
    match visOpt with
    | Some (_, pos) -> newNode SyntaxKind.VarPat [ newAnchor pos; sgName name ]
    | None -> newNode SyntaxKind.VarPat [ sgName name ]

  | AParenPat (lPos, bodyPat, rPos) ->
    buildNode
      SyntaxKind.ParenPat
      ([ [ newAnchor lPos ] ]
       |> cons (onPat bodyPat)
       |> consOptionMap newAnchor rPos)

  | AListPat (lPos, itemPats, rPos) ->
    buildNode
      SyntaxKind.ListPat
      ([ [ newAnchor lPos ] ]
       |> consListMap onPat itemPats
       |> consOptionMap newAnchor rPos)

  | ANavPat (lPat, dotPos, r) ->
    newNode
      SyntaxKind.PathPat
      [ onPat lPat
        newAnchor dotPos
        sgName r ]

  | AAppPat (lPat, _, rPat) -> newNode SyntaxKind.WrapPat [ onPat lPat; onPat rPat ]

  | AConsPat (lPat, opPos, rPat) ->
    newNode
      SyntaxKind.ConsPat
      [ onPat lPat
        newAnchor opPos
        onPat rPat ]

  | ATuplePat (lPos, [], rOpt) ->
    buildNode
      SyntaxKind.TuplePat
      ([ [ newAnchor lPos ] ]
       |> consOptionMap newAnchor rOpt)

  | ATuplePat (_, itemPats, _) -> newNode SyntaxKind.TuplePat (itemPats |> List.map onPat)

  | AAsPat (bodyPat, asPos, name) ->
    newNode
      SyntaxKind.AsPat
      [ onPat bodyPat
        newAnchor asPos
        newNode SyntaxKind.VarPat [ sgName name ] ]

  | AAscribePat (bodyPat, colonPos, ty) ->
    newNode
      SyntaxKind.AscribePat
      [ onPat bodyPat
        newAnchor colonPos
        onTy ty ]

  | AOrPat (lPat, pipePos, rPat) ->
    newNode
      SyntaxKind.OrPat
      [ onPat lPat
        newAnchor pipePos
        onPat rPat ]

let private sgExpr (ctx: SgCtx) (expr: AExpr) : BuilderElement =
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
      SyntaxKind.NameExpr
      ([ [ sgName name ] ]
       |> consOpt (sgTyArgList ctx tyArgList))

  | AParenExpr (lPos, body, rOpt) ->
    buildNode
      SyntaxKind.ParenExpr
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
             SyntaxKind.WithClause
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
       |> consOpt (sgThen ctx thenPos)
       |> cons (onExpr body)
       |> consOpt (
         match altOpt with
         | Some (elsePos, alt) ->
           newNode SyntaxKind.ElseClause [ newAnchor elsePos; onExpr alt ]
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
             SyntaxKind.Arm
             ([]
              |> consOptionMap newAnchor pipeOpt
              |> cons (onPat pat)
              |> consOpt (
                match guardOpt with
                | Some (whenPos, guard) ->
                  newNode SyntaxKind.GuardClause [ newAnchor whenPos; onExpr guard ]
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
       |> consListMap onPat argPats
       |> consOpt (sgArrow ctx arrowPos)
       |> cons (onExpr body))

  | ANavExpr (l, dotPos, r) -> newNode SyntaxKind.PathExpr [ onExpr l; newAnchor dotPos; sgName r ]

  | AIndexExpr (l, dotPos, lPos, r, rOpt) ->
    buildNode
      SyntaxKind.IndexExpr
      ([ [ onExpr l
           newAnchor dotPos
           newAnchor lPos
           onExpr r ] ]
       |> consOptionMap newAnchor rOpt)

  | AUnaryExpr (_, opPos, arg) -> newNode SyntaxKind.UnaryExpr [ newAnchor opPos; onExpr arg ]

  | ABinaryExpr (AppBinary, l, _, r) -> newNode SyntaxKind.AppExpr (onExprs [ l; r ])
  | ABinaryExpr (_, l, opPos, r) -> newNode SyntaxKind.BinaryExpr ([ onExpr l; newAnchor opPos; onExpr r ])
  | ARangeExpr (l, opPos, r) -> newNode SyntaxKind.RangeExpr ([ onExpr l; newAnchor opPos; onExpr r ])
  | ATupleExpr (lPos, [], rOpt) ->
    buildNode
      SyntaxKind.TupleExpr
      ([ [ newAnchor lPos ] ]
       |> consOptionMap newAnchor rOpt)
  | ATupleExpr (_, items, _) -> newNode SyntaxKind.TupleExpr (onExprs items)
  | AAscribeExpr (l, colonPos, rTy) ->
    newNode
      SyntaxKind.AscribeExpr
      [ onExpr l
        newAnchor colonPos
        onTy rTy ]

  | ASemiExpr ([], last, _) -> onExpr last
  | ASemiExpr (stmts, last, _) -> buildNode SyntaxKind.BlockExpr ([ onExprs stmts ] |> cons (onExpr last))

  | ALetExpr (letPos, contents, nextOpt) ->
    match contents with
    | ALetContents.LetVal (_, pat, equalPos, init) ->
      buildNode
        SyntaxKind.LetValExpr
        ([ [ newAnchor letPos; onPat pat ] ]
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr init)
         |> consOptionMap onExpr nextOpt)

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, equalPos, body) ->
      buildNode
        SyntaxKind.LetFunExpr
        ([ [ sgName name ] ]
         |> consListMap onPat argPats
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ newAnchor colonPos; onTy ty ]
           | None -> []
         )
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr body)
         |> consOptionMap onExpr nextOpt)

let private sgDecl (ctx: SgCtx) attrAcc decl : BuilderElement =
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat
  let onExpr expr = sgExpr ctx expr
  let onDecls decls = decls |> List.map (sgDecl ctx [])

  let genAttrList () =
    attrAcc
    |> List.rev
    |> List.map (fun (lPos, attr, rOpt) ->
      buildNode
        SyntaxKind.AttrDecl
        ([ [ newAnchor lPos; onExpr attr ] ]
         |> consOptionMap newAnchor rOpt))

  let onTyHead typePos name tyParamList equalPos =
    [ genAttrList () ]
    |> cons (newAnchor typePos)
    |> cons (sgName name)
    |> consOpt (sgTyParamList tyParamList)
    |> consOpt (sgEqual ctx equalPos)

  match decl with
  | AExprDecl expr -> buildNode SyntaxKind.ExprDecl ([ genAttrList () ] |> cons (onExpr expr))

  | ALetDecl (letPos, contents) ->
    match contents with
    | ALetContents.LetVal (_, pat, equalPos, init) ->
      buildNode
        SyntaxKind.LetValDecl
        ([ genAttrList () ]
         |> consList [ newAnchor letPos; onPat pat ]
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr init))

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, equalPos, body) ->
      buildNode
        SyntaxKind.LetFunDecl
        ([ genAttrList () ]
         |> consList [ newAnchor letPos
                       sgName name ]
         |> consListMap onPat argPats
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ newAnchor colonPos; onTy ty ]
           | None -> []
         )
         |> consOpt (sgEqual ctx equalPos)
         |> cons (onExpr body))

  | ATySynonymDecl (typePos, _, name, tyParamList, equalPos, ty) ->
    buildNode
      SyntaxKind.TySynonymDecl
      (onTyHead typePos name tyParamList equalPos
       |> cons (onTy ty))

  | AUnionTyDecl (typePos, _, name, tyParamList, equalPos, variants) ->
    buildNode
      SyntaxKind.UnionTyDecl
      (onTyHead typePos name tyParamList equalPos
       |> consList (
         variants
         |> List.map (fun (pipePos, name, payloadOpt) ->
           buildNode
             SyntaxKind.VariantDecl
             ([]
              |> consOpt (sgPipe ctx pipePos)
              |> cons (sgName name)
              |> consList (
                match payloadOpt with
                | Some (ofPos, labeledTys) ->
                  newAnchor ofPos
                  :: (labeledTys
                      |> List.map (fun (labelOpt, itemTy) ->
                        match labelOpt with
                        | Some label -> newNode SyntaxKind.LabeledTy [ newAnchor label; onTy itemTy ]
                        | None -> onTy itemTy))
                | None -> []
              )))
       ))

  | ARecordTyDecl (typePos, _, name, tyParamList, equalPos, lPos, fields, rPos) ->
    buildNode
      SyntaxKind.RecordTyDecl
      (onTyHead typePos name tyParamList equalPos
       |> cons (newAnchor lPos)
       |> consList (
         fields
         |> List.map (fun (name, ty, _) -> newNode SyntaxKind.FieldDecl [ sgName name; onTy ty ])
       )
       |> consOptionMap newAnchor rPos)

  | AOpenDecl (openPos, path) ->
    buildNode
      SyntaxKind.OpenDecl
      ([ genAttrList () ]
       |> cons (newAnchor openPos)
       |> cons (newNode SyntaxKind.ModulePath (path |> List.map sgName)))

  | AModuleSynonymDecl (modulePos, name, equalPos, path) ->
    buildNode
      SyntaxKind.ModuleSynonymDecl
      ([ genAttrList () ]
       |> consList [ newAnchor modulePos
                     sgName name ]
       |> consOpt (sgEqual ctx equalPos)
       |> cons (newNode SyntaxKind.ModulePath (path |> List.map sgName)))

  | AModuleDecl (modulePos, _, _, name, equalPos, decls) ->
    buildNode
      SyntaxKind.ModuleDecl
      ([ genAttrList () ]
       |> consList [ newAnchor modulePos
                     sgName name ]
       |> consOpt (sgEqual ctx equalPos)
       |> consList (onDecls decls))

  | AAttrDecl (lPos, attr, rOpt, next) -> sgDecl ctx ((lPos, attr, rOpt) :: attrAcc) next

let private sgRoot (ctx: SgCtx) root : BuilderElement =
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
             newNode SyntaxKind.ModulePath (path |> List.map sgName) ]
         |> Some

       | _ -> None
     )
     |> consListMap (sgDecl ctx []) decls)

// -----------------------------------------------
// Postprocess
// -----------------------------------------------

let private isLeading token =
  match token with
  | ErrorToken _
  | NewlinesToken _
  | BlankToken _
  | CommentToken _ -> true
  | _ -> false

/// Takes (leading) trivias.
let private takeLeadingTrivias (rangeMap: TokenRangeMap) tokens =
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

/// Takes tokens before `untilPos` excluding leading trivias of the next token.
let private takeTokensBefore (rangeMap: TokenRangeMap) untilPos tokens =
  // Position of the last non-trivia token before `untilPos`.
  let lastOpt =
    let rec measure lastOpt tokens =
      match tokens with
      | (token, pos) :: tokens when Pos.compare pos untilPos < 0 ->
        if not (isLeading token) then
          measure (Some pos) tokens
        else
          measure lastOpt tokens

      | [] -> Some untilPos
      | _ -> lastOpt

    measure None tokens

  match lastOpt with
  | Some lastPos ->
    let rec go acc tokens =
      match tokens with
      | (token, pos) :: tokens when Pos.compare pos lastPos <= 0 ->
        let _, endPos = rangeMap |> mapFind pos
        go (wrapToken (token, (pos, endPos)) :: acc) tokens

      | _ -> List.rev acc, tokens

    go [] tokens

  | None -> [], tokens

/// Takes tokens until a position (inclusive).
let private takeTokensUntil (rangeMap: TokenRangeMap) untilPos tokens =
  let rec go acc tokens =
    match tokens with
    | (token, pos) :: tokens when Pos.compare pos untilPos <= 0 ->
      let _, endPos = rangeMap |> mapFind pos
      go (wrapToken (token, (pos, endPos)) :: acc) tokens

    | _ -> List.rev acc, tokens

  go [] tokens

/// Merges tokens into tree to create a full-fidelity syntax tree.
let private postprocess
  (tokens: TokenizeFullResult)
  (rangeMap: TokenRangeMap)
  (eofPos: Pos)
  (root: BuilderElement)
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
    | BuilderElement.Anchor pos ->
      // Take all tokens before and at the position.
      let middle, tokens = takeTokensUntil rangeMap pos tokens

      let trailing, tokens = takeTrailingTrivias rangeMap tokens
      List.append middle trailing, tokens

    | BuilderElement.Node (kind, children) ->
      let children, (availableRange, tokens) =
        children
        |> listCollectFold
             (fun (availableRange, tokens) child ->
               // Take tokens not covered by this child.
               let rec leftmost element =
                 match element with
                 | BuilderElement.Anchor pos -> Some pos
                 | BuilderElement.Node (_, children) -> List.tryPick leftmost children

               let middle, tokens =
                 match leftmost child with
                 | Some pos -> takeTokensBefore rangeMap pos tokens
                 | None -> [], tokens

               let availableRange = shrinkRange middle availableRange

               let trailingOfMiddle, tokens =
                 if not (List.isEmpty middle) then
                   takeTrailingTrivias rangeMap tokens
                 else
                   [], tokens

               let availableRange =
                 shrinkRange trailingOfMiddle availableRange

               let child, tokens = go availableRange tokens child
               let availableRange = shrinkRange child availableRange

               let elements =
                 List.collect id [ middle; trailingOfMiddle; child ]

               elements, (availableRange, tokens))
             (availableRange, tokens)

      let range =
        match children with
        | [] ->
          let pos, _ = shrinkRange children availableRange
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

module private SyntaxTreeDump =
  // #json_escape
  let private needsEscape c = c = '"' || c = '\\' || C.isControl c

  let private escapeChar c =
    match c with
    | '"' -> "\\\""
    | '\\' -> "\\\\"
    | '\r' -> "\\r"
    | '\n' -> "\\n"
    | '\t' -> "\\t"
    | '\x08' -> "\\b" // backspace
    | '\x0c' -> "\\f" // formfeed

    | _ ->
      assert (needsEscape c)
      "\\u" + S.uint64ToHex 4 (uint64 (byte c))

  let private writeString (text: string) acc =
    let rec scanVerbatim i =
      if i < text.Length && not (needsEscape text.[i]) then
        scanVerbatim (i + 1)
      else
        i

    let rec go acc i =
      if i < text.Length then
        if needsEscape text.[i] then
          go (escapeChar text.[i] :: acc) (i + 1)
        else
          let r = scanVerbatim i
          assert (i < r)
          go (text.[i..r - 1] :: acc) r
      else
        acc

    "\"" :: go ("\"" :: acc) 0

  let private cons h t : string list = h :: t

  let private writeReplicate count s acc =
    if count >= 1 then
      writeReplicate (count - 1) s (s :: acc)
    else
      acc

  let private flavorToString flavor =
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

  let private sdRange range acc =
    let pos, endPos = range

    acc
    |> cons "\""
    |> cons (Pos.toString pos)
    |> cons ".."
    |> cons (Pos.toString endPos)
    |> cons "\""

  let private sdElement rx newline acc (element: SyntaxElement) =
    match element with
    | SyntaxToken (kind, tokenRange) ->
      let pos, _ = tokenRange
      let range acc = sdRange tokenRange acc

      let map: TokenRangeMap = rx

      match resolveTokenRange map pos with
      | Some (token, _) ->
        match token with
        | IntToken (text, flavorOpt) ->
          acc
          |> cons "[\"Int\", "
          |> range
          |> cons ", "
          |> cons text
          |> (fun acc ->
            match flavorOpt with
            | Some flavor ->
              acc
              |> cons ", \""
              |> cons (flavorToString flavor)
              |> cons "\""

            | None -> acc)
          |> cons "]"

        | FloatToken text ->
          acc
          |> cons "[\"Float\", "
          |> range
          |> cons ", "
          |> cons text
          |> cons "]"

        | CharToken c ->
          acc
          |> cons "[\"Char\", "
          |> range
          |> cons ", \""
          |> cons (
            if needsEscape c then
              escapeChar c
            else
              string c
          )
          |> cons "\"]"

        | StringToken s ->
          acc
          |> cons "[\"String\", "
          |> range
          |> cons ", "
          |> writeString s
          |> cons "]"

        | IdentToken text ->
          acc
          |> cons "[\"Ident\", "
          |> range
          |> cons ", "
          |> writeString text
          |> cons "]"

        | TyVarToken text ->
          acc
          |> cons "[\"TyVar\", "
          |> range
          |> cons "\"'"
          |> cons text
          |> cons "\"]"

        | NewlinesToken ->
          let (y1, x1), (y2, x2) = tokenRange
          let blank = if y1 < y2 then x2 else x1 + x2

          acc
          |> cons "[\"Newlines\", "
          |> range
          |> cons ", \""
          |> writeReplicate (y2 - y1) "\\n"
          |> writeReplicate blank " "
          |> cons "\"]"

        | CommentToken -> acc |> cons "[\"Comment\", " |> range |> cons "]"

        | _ ->
          acc
          |> cons "[\""
          |> cons (kindToString kind)
          |> cons "\", "
          |> range
          |> cons "]"

      | None ->
        acc
        |> cons "[\""
        |> cons (kindToString kind)
        |> cons "\", "
        |> range
        |> cons "]"

    | SyntaxNode (kind, range, []) ->
      acc
      |> cons "[\""
      |> cons (kindToString kind)
      |> cons "\", "
      |> sdRange range
      |> cons ", []]"

    | SyntaxNode (kind, range, children) ->
      let acc =
        acc
        |> cons "[\""
        |> cons (kindToString kind)
        |> cons "\", "
        |> sdRange range
        |> cons ", ["

      let acc =
        let deep = newline + "  "

        let onChild child acc =
          let acc = acc |> cons deep
          sdElement rx deep acc child

        match children with
        | [] -> acc

        | child :: children ->
          let acc = onChild child acc

          children
          |> List.fold (fun acc child -> acc |> cons "," |> onChild child) acc

      acc |> cons newline |> cons "]]"

  let sdRoot (rangeMap: TokenRangeMap) (root: SyntaxElement) : string =
    sdElement rangeMap "\n" [] root
    |> List.rev
    |> S.concat ""

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

  // assert (stValidate rangeMap tokens root)
  SyntaxTreeDump.sdRoot rangeMap root
