// -----------------------------------------------
// Syntax tree definition and generation
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private SyntaxKind =
  // Fragment
  | Path
  /// `<_, _>`
  | GenericArgList
  /// `ident = expr`
  | FieldInit
  /// `| pat when guard -> body`
  | Arm
  | ModuleHead

  // Ty
  | MissingTy
  | AppTy
  | NameTy
  | SuffixTy
  | TupleTy
  | FunTy

  // Expr
  | MissingExpr
  | LiteralExpr
  | PathExpr
  | ListExpr
  | RecordExpr
  | IfExpr
  | MatchExpr
  | FunExpr
  | NavExpr
  | IndexExpr
  | UnaryExpr
  | BinaryExpr
  | RangeExpr
  | TupleExpr
  | AscribeExpr
  | SemiExpr
  | LetValExpr
  | LetFunExpr

  // Decl
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

[<NoEquality; NoComparison>]
type private SyntaxElement =
  | SyntaxNode of SyntaxKind * SyntaxElement list * Pos option
  | SyntaxToken of Token * Pos

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private SyntaxTree =
  { DocId: DocId
    Root: SyntaxElement
    Tokens: TokenizeFullResult
    Ast: ARoot }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private SyntaxTreeGenCtx =
  { Tokens: (Token * Pos) array
    Consumed: bool array
    NewToken: Token * Pos -> SyntaxElement
    NewNode: SyntaxKind -> SyntaxElement list -> Pos option -> SyntaxElement }

let private sgSearchToken (ctx: SyntaxTreeGenCtx) pos : int =
  let len = ctx.Tokens.Length
  let at (i: int) = snd ctx.Tokens.[i]

  if len = 0 || at (len - 1) < pos then
    len
  else
    // Perform binary search to find a boundary `i`
    // such that `tokens.[0..i - 1]` are all strictly before pos
    // and `tokens.[i..len - 1]` are at pos or after pos.
    let mutable l = 0
    let mutable r = len

    while r - l > 1 do
      let m = (l + r) / 2
      let ok = m = 0 || at (m - 1) < pos
      if ok then l <- m else r <- m

    l

let private sgTokenAt (ctx: SyntaxTreeGenCtx) (pos: Pos) : SyntaxElement =
  let len = ctx.Tokens.Length
  let at (i: int) = snd ctx.Tokens.[i]

  let i = sgSearchToken ctx pos

  if i < len && at i = pos then
    ctx.NewToken ctx.Tokens.[i]
  else
    ctx.NewNode SyntaxKind.Todo [] (Some pos)

let private sgName (ctx: SyntaxTreeGenCtx) name : SyntaxElement =
  let (Name (ident, pos)) = name
  ctx.NewToken(IdentToken ident, pos)

let private sgPath (ctx: SyntaxTreeGenCtx) quals name : SyntaxElement =
  ctx.NewNode SyntaxKind.Path (List.append (quals |> List.map (sgName ctx)) [ sgName ctx name ]) None

// sg: syntax tree generation
let private sgTy (ctx: SyntaxTreeGenCtx) (ty: ATy) : SyntaxElement =
  let onTy ty = sgTy ctx ty
  let onTys tys = tys |> List.map (sgTy ctx)
  let onName name = sgName ctx name
  let newNode kind children pos = ctx.NewNode kind children (Some pos)
  let newNodeWithoutPos kind children = ctx.NewNode kind children None

  match ty with
  | AMissingTy pos -> newNode SyntaxKind.MissingTy [] pos

  | AAppTy (quals, name, tyArgs, pos) ->
    newNode
      SyntaxKind.AppTy
      [ sgPath ctx quals name
        newNodeWithoutPos SyntaxKind.GenericArgList (onTys tyArgs) ]
      pos

  | AVarTy name -> newNode SyntaxKind.NameTy [ onName name ] (nameToPos name)
  | ASuffixTy (bodyTy, suffix) -> newNodeWithoutPos SyntaxKind.SuffixTy [ onTy bodyTy; onName suffix ]
  | ATupleTy (itemTys, pos) -> newNode SyntaxKind.TupleTy (onTys itemTys) pos
  | AFunTy (lTy, rTy, pos) -> newNode SyntaxKind.FunTy [ onTy lTy; onTy rTy ] pos

let private sgPat (ctx: SyntaxTreeGenCtx) (pat: APat) : SyntaxElement = ctx.NewNode SyntaxKind.Todo [] None

let private sgExpr (ctx: SyntaxTreeGenCtx) (expr: AExpr) : SyntaxElement =
  let onPat pat = sgPat ctx pat
  let onPats pats = pats |> List.map (sgPat ctx)
  let onExpr expr = sgExpr ctx expr
  let onExprOpt exprOpt = exprOpt |> Option.map onExpr
  let onExprs exprs = exprs |> List.map onExpr
  let onName name = sgName ctx name
  let newNode kind children pos = ctx.NewNode kind children (Some pos)
  let newNodeWithoutPos kind children = ctx.NewNode kind children None

  match expr with
  | AMissingExpr pos -> newNode SyntaxKind.MissingExpr [] pos
  | ALitExpr (_, pos) -> newNode SyntaxKind.LiteralExpr [ sgTokenAt ctx pos ] pos

  | AIdentExpr name -> onName name
  | AListExpr (items, pos) -> newNode SyntaxKind.ListExpr (onExprs items) pos

  | ARecordExpr (baseOpt, fields, pos) ->
    newNode
      SyntaxKind.RecordExpr
      (List.append
        (onExprOpt baseOpt |> Option.toList)
        (fields
         |> List.map (fun (ident, init, pos) -> newNode SyntaxKind.FieldInit [ onName ident; onExpr init ] pos)))
      pos

  | AIfExpr (cond, body, alt, pos) ->
    newNode
      SyntaxKind.IfExpr
      (List.choose
        id
        [ Some(onExpr cond)
          Some(onExpr body)
          (onExprOpt alt) ])
      pos

  | AMatchExpr (cond, arms, pos) ->
    let onArm (AArm (pat, guard, body, pos)) =
      newNode
        SyntaxKind.Arm
        (List.choose
          id
          [ Some(onPat pat)
            onExprOpt guard
            Some(onExpr body) ])
        pos

    newNode SyntaxKind.MatchExpr (onExpr cond :: (arms |> List.map onArm)) pos

  | AFunExpr (argPats, body, pos) -> newNode SyntaxKind.FunExpr (List.append (onPats argPats) [ onExpr body ]) pos

  | ANavExpr (l, r, pos) -> newNode SyntaxKind.NavExpr [ onExpr l; onName r ] pos
  | AIndexExpr (l, r, pos) -> newNode SyntaxKind.IndexExpr (onExprs [ l; r ]) pos
  | AUnaryExpr (_, arg, pos) -> newNode SyntaxKind.UnaryExpr [ onExpr arg ] pos
  | ABinaryExpr (_, l, r, pos) -> newNode SyntaxKind.BinaryExpr (onExprs [ l; r ]) pos
  | ARangeExpr (l, r, pos) -> newNode SyntaxKind.RangeExpr (onExprs [ l; r ]) pos
  | ATupleExpr (items, pos) -> newNode SyntaxKind.TupleExpr (onExprs items) pos
  | AAscribeExpr (l, _, pos) -> newNode SyntaxKind.AscribeExpr [ onExpr l ] pos

  | ASemiExpr ([], last, _) -> onExpr last
  | ASemiExpr (stmts, last, pos) -> newNode SyntaxKind.SemiExpr (List.append (onExprs stmts) [ onExpr last ]) pos

  | ALetExpr (_, pat, init, next, pos) ->
    match pat with
    | AFunDeclPat (_, name, argPats) ->
      newNode
        SyntaxKind.LetFunExpr
        (onName name
         :: List.append (onPats argPats) [ onExpr init; onExpr next ])
        pos

    | _ -> newNode SyntaxKind.LetValExpr (onPat pat :: onExprs [ init; next ]) pos

let private sgDecl (ctx: SyntaxTreeGenCtx) decl : SyntaxElement =
  let onName name = sgName ctx name
  let onPat pat = sgPat ctx pat
  let onPats pats = pats |> List.map onPat
  let onExpr expr = sgExpr ctx expr
  let onExprOpt exprOpt = exprOpt |> Option.map onExpr
  let onExprs exprs = exprs |> List.map onExpr
  let onDecl decl = sgDecl ctx decl
  let onDecls decls = decls |> List.map onDecl
  let newNode kind children pos = ctx.NewNode kind children (Some pos)
  let newNodeWithoutPos kind children = ctx.NewNode kind children None
  let newTodo () = ctx.NewNode SyntaxKind.Todo [] None

  match decl with
  | AExprDecl expr -> newNodeWithoutPos SyntaxKind.ExprDecl [ onExpr expr ]

  | ALetDecl (_, pat, init, pos) ->
    match pat with
    | AFunDeclPat (_, name, argPats) ->
      newNode
        SyntaxKind.LetFunDecl
        (onName name
         :: List.append (onPats argPats) [ onExpr init ])
        pos

    | _ -> newNode SyntaxKind.LetValDecl [ onPat pat; onExpr init ] pos

  | ATySynonymDecl _
  | AUnionTyDecl _
  | ARecordTyDecl _
  | AOpenDecl _
  | AModuleSynonymDecl _ -> newTodo ()

  | AModuleDecl (_, _, name, decls, pos) -> newNode SyntaxKind.ModuleDecl (onName name :: onDecls decls) pos

  | AAttrDecl (_, next, _) -> sgDecl ctx next

let private sgRoot (ctx: SyntaxTreeGenCtx) root : SyntaxElement =
  let onName name = sgName ctx name
  let onDecl decl = sgDecl ctx decl
  let onDecls decls = decls |> List.map onDecl
  let newNode kind children pos = ctx.NewNode kind children (Some pos)
  let newNodeWithoutPos kind children = ctx.NewNode kind children None

  let (ARoot (headOpt, decls)) = root

  let headOpt =
    match headOpt with
    | Some (path, pos) ->
      let path =
        newNodeWithoutPos SyntaxKind.Path (path |> List.map onName)

      Some(newNode SyntaxKind.ModuleHead [ path ] pos)

    | _ -> None

  newNode SyntaxKind.Root (List.append (headOpt |> Option.toList) (onDecls decls)) (0, 0)

let private genSyntaxTree (docId: DocId) (tokens: TokenizeFullResult) (ast: ARoot) : SyntaxTree =
  let tokenArray = tokens |> List.toArray

  let ctx: SyntaxTreeGenCtx =
    { Tokens = tokenArray
      Consumed = Array.zeroCreate tokenArray.Length
      NewToken = fun (token, pos) -> SyntaxToken(token, pos)
      NewNode = fun kind children posOpt -> SyntaxNode(kind, children, posOpt) }

  { DocId = docId
    Root = sgRoot ctx ast
    Tokens = tokens
    Ast = ast }

// -----------------------------------------------
// Syntax tree use
// -----------------------------------------------

module private SyntaxTree =
  let dump (tree: SyntaxTree) : string =
    let mutable indent = 0
    let sb = System.Text.StringBuilder()

    let writeLine (text: string) =
      for _ in 0 .. indent - 1 do
        sb.Append("  ") |> ignore

      sb.Append(text).Append("\n") |> ignore

    let writeRightBraceLine () =
      let len = sb.Length

      if len >= 2
         && sb.[len - 2] = '}'
         && sb.[len - 1] = '\n' then
        sb.Remove(len - 1, 1).Append("}\n") |> ignore
      else
        writeLine "}"

    let onToken token =
      match token with
      | IntToken text -> sprintf "Int %s" text
      | FloatToken text -> sprintf "Float %s" text
      | CharToken c -> sprintf "Char %A" c
      | StrToken text -> sprintf "String %A" text
      | IdentToken text -> sprintf "Ident %A" text
      | _ -> sprintf "%A" token

    let rec onElement element =
      match element with
      | SyntaxToken (token, _) -> writeLine (onToken token)

      | SyntaxNode (kind, [], _) -> writeLine (sprintf "%A {}" kind)

      | SyntaxNode (kind, [ SyntaxToken (token, _) ], _) -> writeLine (sprintf "%A { %s }" kind (onToken token))

      | SyntaxNode (kind, children, _) ->
        writeLine (sprintf "%A {" kind)

        indent <- indent + 1

        for c in children do
          onElement c

        indent <- indent - 1
        writeRightBraceLine ()

    onElement tree.Root
    sb.ToString().TrimEnd()

// -----------------------------------------------
// Lower TIR
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LtCtx =
  { SymbolMap: MutMap<Loc, Symbol * DefOrUse>
    TyMap: MutMap<Loc, Ty>
    GetTokens: DocId -> TokenizeFullResult }

let private ltAddSymbol (ctx: LtCtx) symbol defOrUse loc =
  ctx.SymbolMap
  |> MutMap.insert loc (symbol, defOrUse)
  |> ignore

let private ltAddTy (ctx: LtCtx) ty loc =
  ctx.TyMap |> MutMap.insert loc ty |> ignore

let private lastIdentBefore (ctx: LtCtx) loc =
  let (Loc (docId, py, px)) = loc

  ctx.GetTokens docId
  |> List.skipWhile (fun (_, (y, x)) -> (y, x) < (py, 0))
  |> List.takeWhile (fun (_, (y, x)) -> (y, x) <= (py, px))
  |> List.rev
  |> List.tryPick (fun (token, (y, x)) ->
    match token with
    | IdentToken _ -> Some(Loc(docId, y, x))
    | _ -> None)

let private firstIdentAfter (ctx: LtCtx) loc =
  let (Loc (docId, py, px)) = loc

  ctx.GetTokens docId
  |> List.tryPick (fun (token, (y, x)) ->
    match token with
    | IdentToken _ when (py, px) < (y, x) -> Some(Loc(docId, y, x))
    | _ -> None)

let private ltTy (ctx: LtCtx) ty : unit =
  let (Ty (tk, tyArgs)) = ty

  match tk with
  | UnionTk (tySerial, Some loc) -> ltAddSymbol ctx (TySymbol(UnionTySymbol tySerial)) Use loc
  | RecordTk (tySerial, Some loc) -> ltAddSymbol ctx (TySymbol(RecordTySymbol tySerial)) Use loc
  | _ -> ()

  for ty in tyArgs do
    ltTy ctx ty

let private ltPat (ctx: LtCtx) pat =
  let onPat pat = ltPat ctx pat

  match pat with
  | TLitPat _
  | TDiscardPat _ -> ()

  | TVarPat (_, varSerial, ty, loc) ->
    ltAddSymbol ctx (ValueSymbol(VarSymbol varSerial)) Def loc
    ltAddTy ctx ty loc

  | TVariantPat (variantSerial, ty, loc) ->
    ltAddSymbol ctx (ValueSymbol(VariantSymbol variantSerial)) Use loc
    ltAddTy ctx ty loc

  | TNodePat (kind, pats, ty, loc) ->
    match kind with
    | TVariantAppPN variantSerial -> ltAddSymbol ctx (ValueSymbol(VariantSymbol variantSerial)) Use loc
    | TNavPN _ -> ()
    | TAscribePN -> ltTy ctx ty
    | _ -> ()

    ltAddTy ctx ty loc

    for pat in pats do
      onPat pat

  | TAsPat (bodyPat, varSerial, loc) ->
    ltAddSymbol ctx (ValueSymbol(VarSymbol varSerial)) Def loc
    ltAddTy ctx (patToTy bodyPat) loc
    onPat bodyPat

  | TOrPat (l, r, _) ->
    onPat l
    onPat r

let private ltExpr (ctx: LtCtx) expr : unit =
  let onPat pat = ltPat ctx pat
  let onExpr expr = ltExpr ctx expr

  match expr with
  | TLitExpr _ -> ()

  | TVarExpr (varSerial, ty, loc) ->
    ltAddSymbol ctx (ValueSymbol(VarSymbol varSerial)) Use loc
    ltAddTy ctx ty loc

  | TFunExpr (funSerial, ty, loc) ->
    ltAddSymbol ctx (ValueSymbol(FunSymbol funSerial)) Use loc
    ltAddTy ctx ty loc

  | TVariantExpr (variantSerial, ty, loc) ->
    ltAddSymbol ctx (ValueSymbol(VariantSymbol variantSerial)) Use loc
    ltAddTy ctx ty loc

  | TPrimExpr (prim, ty, loc) ->
    ltAddSymbol ctx (PrimSymbol prim) Use loc
    ltAddTy ctx ty loc

  | TMatchExpr (cond, arms, _, _) ->
    onExpr cond

    for pat, guard, expr in arms do
      onPat pat
      onExpr guard
      onExpr expr

  | TRecordExpr (baseOpt, fields, ty, _) ->
    baseOpt |> Option.iter onExpr

    for ident, init, loc in fields do
      match ty with
      | Ty (RecordTk (tySerial, _), _) ->
        // before '='
        match lastIdentBefore ctx loc with
        | Some loc ->
          ltAddSymbol ctx (FieldSymbol(tySerial, ident)) Use loc
          ltAddTy ctx ty loc

        | _ -> ()
      | _ -> ()

      ltExpr ctx init

  | TNavExpr (l, (r, loc), ty, _) ->
    onExpr l

    match exprToTy l with
    | Ty (RecordTk (tySerial, _), _) ->
      ltAddSymbol ctx (FieldSymbol(tySerial, r)) Use loc
      ltAddTy ctx ty loc
    | _ -> ()

  | TNodeExpr (_, exprs, _, _) ->
    for expr in exprs do
      onExpr expr

  | TBlockExpr (_, stmts, expr) ->
    for stmt in stmts do
      ltStmt ctx stmt

    ltExpr ctx expr

let private ltStmt (ctx: LtCtx) stmt : unit =
  let onTy ty = ltTy ctx ty
  let onPat pat = ltPat ctx pat
  let onExpr expr = ltExpr ctx expr
  let onStmt stmt = ltStmt ctx stmt

  match stmt with
  | TExprStmt expr -> onExpr expr

  | TLetValStmt (pat, init, _) ->
    onPat pat
    onExpr init

  | TLetFunStmt (callee, _, _, args, body, loc) ->
    let tyFunN argTys resultTy : Ty =
      argTys
      |> List.fold (fun funTy argTy -> tyFun argTy funTy) resultTy

    // after 'let'
    match firstIdentAfter ctx loc with
    | Some loc ->
      let funTy =
        let argTys = args |> List.map patToTy
        let resultTy = body |> exprToTy
        tyFunN argTys resultTy

      ltAddSymbol ctx (ValueSymbol(FunSymbol callee)) Def loc
      ltAddTy ctx funTy loc

    | None -> ()

    // HACK: Visit type as if let-fun has result-type ascription. Typing removes result type ascription.
    onTy (exprToTy body)

    for arg in args do
      onPat arg

    onExpr body

  | TTyDeclStmt (tySerial, _, tyArgs, tyDecl, tyDeclLoc) ->
    match tyDecl with
    | TySynonymDecl _ -> ()

    | UnionTyDecl (_, variants, _) ->
      // after 'type'
      match firstIdentAfter ctx tyDeclLoc with
      | Some loc -> ltAddSymbol ctx (TySymbol(UnionTySymbol tySerial)) Def loc
      | _ -> ()

      for _, variantSerial, hasPayload, payloadTy, identLoc in variants do
        let ty =
          let tyArgs =
            tyArgs
            |> List.map (fun tySerial -> tyMeta tySerial tyDeclLoc)

          if hasPayload then
            tyFun payloadTy (tyUnion tySerial tyArgs identLoc)
          else
            tyUnit

        ltAddSymbol ctx (ValueSymbol(VariantSymbol variantSerial)) Def identLoc
        ltAddTy ctx ty identLoc

    | RecordTyDecl (_, fields, _, _) ->
      // after 'type'
      match firstIdentAfter ctx tyDeclLoc with
      | Some loc -> ltAddSymbol ctx (TySymbol(RecordTySymbol tySerial)) Def loc
      | _ -> ()

      for ident, ty, loc in fields do
        // before ':'
        match lastIdentBefore ctx loc with
        | Some loc ->
          ltAddSymbol ctx (FieldSymbol(tySerial, ident)) Def loc
          ltAddTy ctx ty loc
        | _ -> ()

  | TModuleStmt (_, body, _) ->
    for stmt in body do
      onStmt stmt

  | TTyDeclStmt _
  | TOpenStmt _
  | TModuleSynonymStmt _ -> ()

let private lowerTir (modules: TProgram) : LtCtx =
  let ctx: LtCtx =
    { SymbolMap = MutMap.empty ()
      TyMap = MutMap.empty ()
      GetTokens = fun _ -> todo () }

  for m in modules do
    for stmt in m.Stmts do
      ltStmt ctx stmt

  ctx

module LangService =
  /// Prints syntax tree.
  let parse (ls: LangServiceState) docId : string =
    let tokens = tokenizeWithCache ls docId

    let _, ast, _ =
      parseWithCache ls docId SyntaxApi.ModuleKind.Regular

    genSyntaxTree docId tokens ast |> SyntaxTree.dump
