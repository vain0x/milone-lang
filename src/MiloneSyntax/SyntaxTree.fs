module rec MiloneSyntax.SyntaxTree

open MiloneShared.SharedTypes
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError
open Std.StdPair
open Std.StdMap
open Std.StdSet

module C = Std.StdChar
module S = Std.StdString

// -----------------------------------------------
// Util
// -----------------------------------------------

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
// Types
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxKind =
  // Non-token anchor to occupy a position.
  | Anchor

  // Token:
  | Literal
  | Ident
  | LeftParen
  | RightParen
  | LeftBracket
  | RightBracket
  | LeftBrace
  | RightBrace
  | LeftAngle
  | RightAngle
  | Arrow
  | Colon
  | Dot
  | Equal
  | Pipe
  | Else
  | Fun
  | If
  | LetFun
  | LetVal
  | Match
  | Minus
  | Module
  | PtrOf
  | Then
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
  | UnaryExpr
  | BinaryExpr
  | AppExpr
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
  | Todo

type private Sk = SyntaxKind

[<NoEquality; NoComparison>]
type SyntaxElement =
  | SyntaxToken of SyntaxKind * Range
  | SyntaxNode of SyntaxKind * SyntaxElement list

[<NoEquality; NoComparison>]
type SyntaxTree = SyntaxTree of root: SyntaxElement

/// Mapping from start-position to (kind, end-position).
type private TokenRangeMap = TreeMap<Pos, Token * Pos>

/// Context of syntax-tree generation.
type private SgCtx = SgCtx of TokenRangeMap

// -----------------------------------------------
// Syntax Tree Generation
// -----------------------------------------------

// sg: syntax tree generation

let private sgToken (ctx: SgCtx) kind pos =
  let (SgCtx map) = ctx

  match resolveTokenRange map pos with
  | Some (_, range) -> SyntaxToken(kind, range)
  | None -> SyntaxToken(kind, (pos, pos))

let private newAnchor pos = SyntaxToken(Sk.Anchor, (pos, pos))

let private newNode kind children : SyntaxElement = SyntaxNode(kind, children)

let private buildNode kind childrenRev : SyntaxElement =
  SyntaxNode(kind, List.rev (List.collect id childrenRev))

let private sgName (ctx: SgCtx) name : SyntaxElement =
  let (Name (_, pos)) = name
  sgToken ctx Sk.Ident pos

let private sgPath (ctx: SgCtx) quals name : SyntaxElement =
  buildNode
    Sk.Path
    ([ quals
       |> List.collect (fun (name, pos) ->
         [ sgName ctx name
           sgToken ctx Sk.Dot pos ]) ]
     |> cons (sgName ctx name))

let private sgTyParamList ctx (tyParamListOpt: ATyParamList option) =
  match tyParamListOpt with
  | Some (l, tyParams, rOpt) ->
    buildNode
      Sk.GenericParamList
      ([ [ sgToken ctx Sk.LeftAngle l ] ]
       |> consListMap (sgName ctx) tyParams
       |> consOptionMap (sgToken ctx Sk.RightAngle) rOpt)
    |> Some

  | None -> None

let private sgTyArgList (ctx: SgCtx) (tyArgListOpt: ATyArgList option) =
  match tyArgListOpt with
  | Some (l, tyArgs, rOpt) ->
    buildNode
      Sk.GenericArgList
      ([ [ sgToken ctx Sk.LeftAngle l ] ]
       |> consListMap (sgTy ctx) tyArgs
       |> consOptionMap (sgToken ctx Sk.RightAngle) rOpt)
    |> Some

  | None -> None

let private sgTy (ctx: SgCtx) (ty: ATy) : SyntaxElement =
  let onTy ty = sgTy ctx ty

  match ty with
  | AMissingTy pos -> newNode SyntaxKind.MissingTy [ newAnchor pos ]

  | AAppTy (quals, name, tyArgList) ->
    buildNode
      SyntaxKind.PathTy
      ([ [ sgPath ctx quals name ] ]
       |> consOpt (sgTyArgList ctx tyArgList))

  | AVarTy name -> newNode SyntaxKind.VarTy [ sgName ctx name ]

  | AParenTy (l, bodyTy, rOpt) ->
    buildNode
      Sk.ParenTy
      ([ [ sgToken ctx Sk.LeftParen l ] ]
       |> cons (onTy bodyTy)
       |> consOptionMap (sgToken ctx Sk.RightParen) rOpt)

  | ASuffixTy (bodyTy, suffix) -> newNode Sk.SuffixTy [ onTy bodyTy; sgName ctx suffix ]
  | ATupleTy (itemTys, _) -> newNode SyntaxKind.TupleTy (itemTys |> List.map onTy)
  | AFunTy (lTy, _, rTy) -> newNode Sk.FunTy [ onTy lTy; onTy rTy ]

let private sgPat (ctx: SgCtx) (pat: APat) : SyntaxElement =
  // FIXME: implement
  newNode SyntaxKind.Todo []

let private sgExpr (ctx: SgCtx) (expr: AExpr) : SyntaxElement =
  let onToken kind pos = sgToken ctx kind pos
  let onName name = sgName ctx name
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat
  let onPats pats = pats |> List.map (sgPat ctx)
  let onExpr expr = sgExpr ctx expr
  let onExprOpt exprOpt = exprOpt |> Option.map onExpr
  let onExprs exprs = exprs |> List.map onExpr

  match expr with
  | AMissingExpr pos -> newNode SyntaxKind.MissingExpr [ newAnchor pos ]
  | ALitExpr (_, pos) -> newNode SyntaxKind.LiteralExpr [ onToken Sk.Literal pos ]

  | AIdentExpr (name, tyArgList) ->
    buildNode
      Sk.NameExpr
      ([ [ onName name ] ]
       |> consOpt (sgTyArgList ctx tyArgList))

  | AParenExpr (l, body, rOpt) ->
    buildNode
      Sk.ParenExpr
      ([ [ onToken Sk.LeftParen l ] ]
       |> cons (onExpr body)
       |> consOptionMap (onToken Sk.RightParen) rOpt)

  | AListExpr (l, items, rOpt) ->
    buildNode
      SyntaxKind.ListExpr
      ([ [ onToken Sk.LeftBracket l ] ]
       |> consListMap onExpr items
       |> consOptionMap (onToken Sk.RightBracket) rOpt)

  | ARecordExpr (l, withClauseOpt, fields, rOpt) ->
    buildNode
      SyntaxKind.RecordExpr
      ([ [ onToken Sk.LeftBrace l ] ]
       |> consOpt (
         match withClauseOpt with
         | Some (baseExpr, withOpt) ->
           buildNode
             Sk.WithClause
             ([ [ onExpr baseExpr ] ]
              |> consOptionMap (onToken Sk.With) withOpt)
           |> Some

         | None -> None
       )
       |> consList (
         fields
         |> List.map (fun (ident, equalPos, init) ->
           newNode
             SyntaxKind.FieldInit
             [ onName ident
               onToken Sk.Equal equalPos
               onExpr init ])
       )
       |> consOptionMap (onToken Sk.RightBrace) rOpt)

  | AIfExpr (ifPos, cond, thenPos, body, altOpt) ->
    buildNode
      SyntaxKind.IfExpr
      ([ [ onToken Sk.If ifPos ] ]
       |> cons (onExpr cond)
       |> cons (newNode Sk.ThenClause [ onToken Sk.Then thenPos; onExpr body ])
       |> consOpt (
         match altOpt with
         | Some (elsePos, alt) ->
           newNode Sk.ElseClause [ onToken Sk.Else elsePos; onExpr alt ]
           |> Some
         | None -> None
       ))

  | AMatchExpr (matchPos, cond, withOpt, arms) ->
    buildNode
      SyntaxKind.MatchExpr
      ([ [ onToken Sk.Match matchPos ] ]
       |> cons (onExpr cond)
       |> consOptionMap (onToken Sk.With) withOpt
       |> consList (
         arms
         |> List.map (fun (pipeOpt, pat, guardOpt, arrowPos, body) ->
           buildNode
             Sk.Arm
             ([]
              |> consOptionMap (onToken Sk.Pipe) pipeOpt
              |> cons (onPat pat)
              |> consOpt (
                match guardOpt with
                | Some (whenPos, guard) ->
                  newNode
                    Sk.GuardClause
                    [ onToken Sk.When whenPos
                      onExpr guard ]
                  |> Some

                | None -> None
              )
              |> cons (onToken Sk.Arrow arrowPos)
              |> cons (onExpr body)))
       ))

  | AFunExpr (funPos, argPats, arrowPos, body) ->
    buildNode
      SyntaxKind.FunExpr
      ([ [ onToken Sk.Fun funPos ] ]
       |> cons (newNode Sk.ParamList (onPats argPats))
       |> cons (onToken Sk.Arrow arrowPos)
       |> cons (onExpr body))

  | ANavExpr (l, dotPos, r) ->
    newNode
      SyntaxKind.NavExpr
      [ onExpr l
        onToken Sk.Dot dotPos
        onName r ]

  | AIndexExpr (l, dotPos, lPos, r, rOpt) ->
    buildNode
      SyntaxKind.IndexExpr
      ([ [ onExpr l
           onToken Sk.Dot dotPos
           onToken Sk.LeftBracket lPos
           onExpr r ] ]
       |> consOptionMap (onToken Sk.RightBracket) rOpt)

  | AUnaryExpr (unary, opPos, arg) ->
    let opKind =
      match unary with
      | MinusUnary -> Sk.Minus
      | PtrOfUnary -> Sk.PtrOf

    newNode SyntaxKind.UnaryExpr [ onToken opKind opPos; onExpr arg ]

  | ABinaryExpr (AppBinary, l, _, r) -> newNode Sk.AppExpr (onExprs [ l; r ])
  | ABinaryExpr (_, l, _opPos, r) -> newNode SyntaxKind.BinaryExpr (onExprs [ l; r ])
  | ARangeExpr (l, _opPos, r) -> newNode SyntaxKind.RangeExpr (onExprs [ l; r ])
  | ATupleExpr (items, _) -> newNode SyntaxKind.TupleExpr (onExprs items)
  | AAscribeExpr (l, _colonPos, rTy) -> newNode SyntaxKind.AscribeExpr [ onExpr l; onTy rTy ]

  | ASemiExpr ([], last, _) -> onExpr last
  | ASemiExpr (stmts, last, _) -> buildNode SyntaxKind.BlockExpr ([ onExprs stmts ] |> cons (onExpr last))

  | ALetExpr (letPos, contents, next) ->
    match contents with
    | ALetContents.LetVal (_, pat, _equalPos, init) ->
      newNode
        SyntaxKind.LetValExpr
        [ onToken Sk.LetVal letPos
          onPat pat
          onExpr init
          onExpr next ]

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, _equalPos, body) ->
      buildNode
        SyntaxKind.LetFunExpr
        ([ [ onName name ] ]
         |> cons (newNode Sk.ParamList (onPats argPats))
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ onToken Sk.Colon colonPos; onTy ty ]
           | None -> []
         )
         |> consList (onExprs [ body; next ]))

let private sgDecl (ctx: SgCtx) decl : SyntaxElement =
  let onToken kind pos = sgToken ctx kind pos
  let onName name = sgName ctx name
  let onTy ty = sgTy ctx ty
  let onPat pat = sgPat ctx pat
  let onExpr expr = sgExpr ctx expr
  let onDecls decls = decls |> List.map (sgDecl ctx)

  match decl with
  | AExprDecl expr -> newNode SyntaxKind.ExprDecl [ onExpr expr ]

  | ALetDecl (letPos, contents) ->
    match contents with
    | ALetContents.LetVal (_, pat, _equalPos, init) ->
      newNode
        SyntaxKind.LetValDecl
        [ onToken Sk.LetVal letPos
          onPat pat
          onExpr init ]

    | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, _equalPos, body) ->
      buildNode
        SyntaxKind.LetFunDecl
        ([ [ onToken Sk.LetFun letPos
             onName name ] ]
         |> cons (newNode Sk.ParamList (argPats |> List.map onPat))
         |> consList (
           match resultTyOpt with
           | Some (colonPos, ty) -> [ onToken Sk.Colon colonPos; onTy ty ]
           | None -> []
         )
         |> cons (onExpr body))

  | ATySynonymDecl _
  | AUnionTyDecl _
  | ARecordTyDecl _
  | AOpenDecl _
  | AModuleSynonymDecl _ -> newNode Sk.Todo []

  | AModuleDecl (modulePos, _, _, name, _, decls) ->
    newNode
      SyntaxKind.ModuleDecl
      (onToken Sk.Module modulePos
       :: onName name :: onDecls decls)

  | AAttrDecl (l, attr, rOpt, next) ->
    // FIXME: add attribute node
    sgDecl ctx next

let private sgRoot (ctx: SgCtx) root : SyntaxElement =
  let onToken kind pos = sgToken ctx kind pos
  let onName name = sgName ctx name
  let onDecl decl = sgDecl ctx decl

  let (ARoot (headOpt, decls)) = root

  buildNode
    SyntaxKind.Root
    ([]
     |> consOpt (
       match headOpt with
       | Some (modulePos, path) ->
         newNode
           SyntaxKind.ModuleHead
           [ onToken Sk.Module modulePos
             newNode Sk.Path (path |> List.map onName) ]
         |> Some

       | _ -> None
     )
     |> consListMap onDecl decls)

// -----------------------------------------------
// Dump
// -----------------------------------------------

let private sdElement rx indent (element: SyntaxElement) =
  match element with
  | SyntaxToken (kind, (pos, endPos)) ->
    let range =
      Pos.toString pos + ".." + Pos.toString endPos

    let value =
      let map: TokenRangeMap = rx

      match resolveTokenRange map pos with
      | Some (token, _) ->
        match token with
        | IntToken (text, _) -> text // TODO: flavor
        | FloatToken text -> text

        | CharToken c ->
          match c with
          | '\n' -> "'\\n'"
          | '\\' -> "'\\\\'"
          | '\'' -> "'\\''"
          | _ when C.isAscii c && not (C.isControl c) -> "'" + string c + "'"
          | _ -> "'\\x" + S.uint64ToHex 2 (uint64 (byte c)) + "'"

        | StringToken s -> __dump s // TODO: escape
        | IdentToken text -> text // TODO: quote
        | TyVarToken text -> "'" + text

        | NewlinesToken ->
          let y1, x1 = pos
          let y2, x2 = endPos
          let blank = if y1 < y2 then x2 else x1 + x2

          "`"
          + String.replicate (y2 - y1) "\\n"
          + String.replicate blank " "
          + "`"

        | CommentToken ->
          // TODO: extract comment from text
          "Comment"

        | _ -> __dump kind

      | None -> __dump kind

    "token " + range + " " + value

  | SyntaxNode (kind, []) -> __dump kind + " {}"

  | SyntaxNode (kind, [ (SyntaxToken _) as child ]) ->
    let deepIndent = indent + "  "

    __dump kind
    + " {"
    + sdElement rx deepIndent child
    + "}"

  | SyntaxNode (kind, children) ->
    let s = __dump kind + " {"

    let t =
      let deepIndent = indent + "  "

      children
      |> List.map (fun child -> "\n" + deepIndent + sdElement rx deepIndent child)
      |> S.concat ""

    s + t + "\n" + indent + "}"

let private stDump (tokens: TokenizeFullResult) (tree: SyntaxTree) : string =
  let (SyntaxTree root) = tree
  let map = toTokenRangeMap tokens
  sdElement map "" root

// -----------------------------------------------
// Tokens
// -----------------------------------------------

let private toTokenRangeMap (tokens: TokenizeFullResult) : TokenRangeMap =
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
  | Some (token, pos) ->
    let y, _ = pos
    let endPos: Pos = y + 1, 0
    map |> TMap.add pos (token, endPos)

  | None -> map

let private resolveTokenRange (map: TokenRangeMap) (pos: Pos) : (Token * Range) option =
  match map |> TMap.tryFind pos with
  | Some (token, endPos) -> Some(token, (pos, endPos))
  | None -> None

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genSyntaxTree (tokens: TokenizeFullResult) (ast: ARoot) : SyntaxTree =
  let ctx: SgCtx = SgCtx(toTokenRangeMap tokens)
  SyntaxTree(sgRoot ctx ast)

let dumpTree (tokens: TokenizeFullResult) (ast: ARoot) : string =
  genSyntaxTree tokens ast |> stDump tokens
