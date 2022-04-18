/// # NirGen
///
/// Conversion from AST to NIR.
///
/// ## Motivation
///
/// 1. AST should be decoupled from IRs to analyze.
///
/// AST is for syntactical analysis but other IRs don't.
/// They have different concerns and grow independently.
///
/// 2. AST is suboptimal for analysis.
///
/// AST is designed for humans but not for analysis.
/// For example, `[1; 2]` and `1 :: 2 :: []` are *same*
/// and no need to be distinct.
/// This stage is the best place to desugar them.
///
/// ## Project module generation
///
/// To ensure each file is enclosed by a module and inside namespace of project,
/// two modules are generated over the contents of AST like this:
///
/// ```fsharp
///   // file: P/M.milone
///   module rec P.M
///   <contents>
/// ```
///
/// ==>
///
/// ```fsharp
///   module rec P =
///     module rec M =
///       <contents>
/// ```
module rec MiloneSyntax.NirGen

open MiloneShared.SharedTypes
open MiloneSyntaxTypes.SyntaxTypes
open Std.StdError

let private optionMapFold (mapFolder: 'S -> 'T -> 'U * 'S) (state: 'S) (opt: 'T option) : 'U option * 'S =
  match opt with
  | Some item ->
    let item, state = mapFolder state item
    Some item, state

  | None -> None, state

/// Convert pos to loc.
let private toLoc (doc: DocId) (pos: Pos) : Loc =
  let row, column = pos
  Loc(doc, row, column)

// -----------------------------------------------
// APat
// -----------------------------------------------

let private apFalse pos = ALitPat(BoolLit false, pos)
let private apTrue pos = ALitPat(BoolLit true, pos)

// -----------------------------------------------
// AExpr
// -----------------------------------------------

let private axUnit loc = ATupleExpr([], loc)
let private axFalse loc = ALitExpr(BoolLit false, loc)
let private axTrue loc = ALitExpr(BoolLit true, loc)

/// `not x` ==> `x = false`
let private axNot arg loc =
  let falseExpr = axFalse loc
  ABinaryExpr(EqualBinary, arg, falseExpr, loc)

// -----------------------------------------------
// Desugar
// -----------------------------------------------

/// `[ x; y; ... ]`. Desugars to a chain of `::`s.
let private desugarListPat pats pos : APat =
  assert (pats |> List.isEmpty |> not)

  let rec go pats =
    match pats with
    | [] -> AListPat([], pos)

    | head :: tail ->
      let tail = go tail
      AConsPat(head, tail, pos)

  go pats

let private desugarListExpr items pos : AExpr =
  assert (items |> List.isEmpty |> not)

  let rec go items =
    match items with
    | [] -> AListExpr([], pos)

    | head :: tail ->
      let tail = go tail
      ABinaryExpr(ConsBinary, head, tail, pos)

  go items

/// Desugars `if` to `match`.
///
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let private desugarIf cond body altOpt pos : AExpr =
  let alt =
    match altOpt with
    | None -> axUnit pos
    | Some alt -> alt

  let arms =
    [ AArm(apTrue pos, None, body, pos)
      AArm(apFalse pos, None, alt, pos) ]

  AMatchExpr(cond, arms, pos)

/// Desugars to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let private desugarFun pats body pos : AExpr =
  let name = "fun"
  let next = AIdentExpr(Name(name, pos), [])
  ALetExpr(ALetContents.LetFun(NotRec, PrivateVis, Name(name, pos), pats, None, body), next, pos)

/// Desugars `-x`.
///
/// `-(-x)` ==> x.
/// `-n` (n: literal).
let private desugarMinusUnary arg : AExpr option =
  match arg with
  | AUnaryExpr (MinusUnary, arg, _) -> Some arg

  | ALitExpr (IntLit text, pos) -> ALitExpr(IntLit("-" + text), pos) |> Some

  | ALitExpr (IntLitWithFlavor (text, flavor), pos) ->
    ALitExpr(IntLitWithFlavor("-" + text, flavor), pos)
    |> Some

  | ALitExpr (FloatLit text, pos) -> ALitExpr(FloatLit("-" + text), pos) |> Some

  | _ -> None

/// `l <> r` ==> `not (l = r)`
let private desugarBinNe l r pos : AExpr =
  let equalExpr = ABinaryExpr(EqualBinary, l, r, pos)
  axNot equalExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let private desugarBinLe l r pos : AExpr =
  let ltExpr = ABinaryExpr(LessBinary, r, l, pos)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let private desugarBinGt l r pos : AExpr = ABinaryExpr(LessBinary, r, l, pos)

/// `l >= r` ==> `not (l < r)`
let private desugarBinGe l r pos : AExpr =
  let ltExpr = ABinaryExpr(LessBinary, l, r, pos)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let private desugarBinAnd l r pos : AExpr = desugarIf l r (Some(axFalse pos)) pos

/// `l || r` ==> `if l then true else r`
let private desugarBinOr l r pos : AExpr = desugarIf l (axTrue pos) (Some r) pos

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let private desugarBinPipe l r pos : AExpr = ABinaryExpr(AppBinary, r, l, pos)

/// `let f ... : ty = body` ==> `let f ... = body : ty`
let private desugarResultTy expr resultTyOpt : AExpr =
  match resultTyOpt with
  | Some (ascriptionTy, ascriptionPos) -> AAscribeExpr(expr, ascriptionTy, ascriptionPos)
  | None -> expr

// -----------------------------------------------
// Context
// -----------------------------------------------

type private NirGenCtx = (NirGenLog * Loc) list

let private emptyCtx: NirGenCtx = []

// -----------------------------------------------
// Control
// -----------------------------------------------

let private ngName docId name : NName =
  let (Name (ident, pos)) = name
  ident, toLoc docId pos

let private ngTy (docId: DocId) (ctx: NirGenCtx) (ty: ATy) : NTy * NirGenCtx =
  let onTy ctx ty = ngTy docId ctx ty
  let onTys ctx tys = tys |> List.mapFold (ngTy docId) ctx
  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match ty with
  | AMissingTy pos -> NTy.Bad(toLoc pos), ctx

  | AAppTy ([], Name ("_", pos), [], _) -> NTy.Infer(toLoc pos), ctx

  | AAppTy (quals, name, argTys, pos) ->
    let quals = quals |> List.map onName
    let name = name |> onName
    let argTys, ctx = onTys ctx argTys
    NTy.App(quals, name, argTys, toLoc pos), ctx

  | AVarTy (Name (ident, pos)) -> NTy.Var("'" + ident, toLoc pos), ctx

  // `ty suffix` ===> `suffix<ty>`
  | ASuffixTy (innerTy, Name (suffix, pos)) ->
    let innerTy, ctx = onTy ctx innerTy
    let loc = toLoc pos
    NTy.App([], (suffix, loc), [ innerTy ], loc), ctx

  | ATupleTy (itemTys, pos) ->
    let itemTys, ctx = onTys ctx itemTys
    NTy.Tuple(itemTys, toLoc pos), ctx

  | AFunTy (sTy, tTy, pos) ->
    let sTy, ctx = onTy ctx sTy
    let tTy, ctx = onTy ctx tTy
    NTy.Fun(sTy, tTy, toLoc pos), ctx

let private ngPat (docId: DocId) (ctx: NirGenCtx) (pat: APat) : NPat * NirGenCtx =
  let onTy ctx ty = ngTy docId ctx ty
  let onPat ctx pat = ngPat docId ctx pat
  let onPats ctx pats = pats |> List.mapFold (ngPat docId) ctx
  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match pat with
  | AMissingPat pos -> NPat.Bad(toLoc pos), ctx

  | ALitPat (lit, pos) -> NPat.Lit(lit, toLoc pos), ctx
  | AIdentPat (_, Name ("_", pos)) -> NPat.Discard(toLoc pos), ctx
  | AIdentPat (vis, Name (ident, pos)) -> NPat.Ident(vis, (ident, toLoc pos)), ctx

  | AListPat ([], pos) -> NPat.Nil(toLoc pos), ctx

  | AListPat (pats, pos) ->
    let pat = desugarListPat pats pos
    ngPat docId ctx pat

  | ANavPat (l, r, pos) ->
    let l, ctx = l |> onPat ctx
    let loc = toLoc pos
    NPat.Nav(l, onName r, loc), ctx

  | AAppPat (calleePat, argPat, pos) ->
    let calleePat, ctx = calleePat |> onPat ctx
    let argPat, ctx = argPat |> onPat ctx
    let loc = toLoc pos
    NPat.VariantApp(calleePat, argPat, loc), ctx

  | AConsPat (l, r, pos) ->
    let l, ctx = l |> onPat ctx
    let r, ctx = r |> onPat ctx
    let loc = toLoc pos
    NPat.Cons(l, r, loc), ctx

  | ATuplePat (pats, pos) ->
    let pats, ctx = pats |> onPats ctx
    let loc = toLoc pos
    NPat.Tuple(pats, loc), ctx

  | AAsPat (bodyPat, name, pos) ->
    let bodyPat, ctx = bodyPat |> onPat ctx
    let loc = toLoc pos
    NPat.As(bodyPat, onName name, loc), ctx

  | AAscribePat (bodyPat, ty, pos) ->
    let bodyPat, ctx = bodyPat |> onPat ctx
    let ty, ctx = ty |> onTy ctx
    let loc = toLoc pos
    NPat.Ascribe(bodyPat, ty, loc), ctx

  | AOrPat (l, r, pos) ->
    let l, ctx = l |> onPat ctx
    let r, ctx = r |> onPat ctx
    let loc = toLoc pos
    NPat.Or(l, r, loc), ctx

let private ngLetContents docId ctx (contents: ALetContents) pos : NStmt * NirGenCtx =
  let onPat ctx pat = ngPat docId ctx pat
  let onPats ctx pats = List.mapFold (ngPat docId) ctx pats
  let onExpr ctx expr = ngExpr docId ctx expr
  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match contents with
  | ALetContents.LetFun (isRec, vis, name, argPats, resultTyOpt, body) ->
    let argPats, ctx = argPats |> onPats ctx

    let body, ctx =
      let body = desugarResultTy body resultTyOpt
      body |> onExpr ctx

    NStmt.LetFun(isRec, vis, onName name, argPats, body, toLoc pos), ctx

  | ALetContents.LetVal (_, pat, body) ->
    // let rec for let-val should be error.
    let pat, ctx = pat |> onPat ctx
    let body, ctx = body |> onExpr ctx
    NStmt.LetVal(pat, body, toLoc pos), ctx

let private ngExpr (docId: DocId) (ctx: NirGenCtx) (expr: AExpr) : NExpr * NirGenCtx =
  let onTy ctx ty = ngTy docId ctx ty
  let onTys ctx tys = List.mapFold (ngTy docId) ctx tys
  let onPat ctx pat = ngPat docId ctx pat
  let onExpr ctx expr = ngExpr docId ctx expr
  let onExprs ctx exprs = List.mapFold (ngExpr docId) ctx exprs

  let onExprOpt ctx exprOpt =
    optionMapFold (ngExpr docId) ctx exprOpt

  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match expr with
  | AMissingExpr pos ->
    // Error is already reported in parsing.
    NExpr.Bad(toLoc pos), ctx

  | ALitExpr (lit, pos) -> NExpr.Lit(lit, toLoc pos), ctx

  | AIdentExpr (name, tyArgs) ->
    let tyArgs, ctx = onTys ctx tyArgs
    NExpr.Ident(onName name, tyArgs), ctx

  | AListExpr ([], pos) -> NExpr.Nil(toLoc pos), ctx
  | AListExpr (items, pos) -> ngExpr docId ctx (desugarListExpr items pos)

  | ARecordExpr (baseOpt, fields, pos) ->
    let baseOpt, ctx = baseOpt |> onExprOpt ctx

    let fields, ctx =
      fields
      |> List.mapFold
           (fun ctx (name, init, pos) ->
             let init, ctx = init |> onExpr ctx
             (onName name, init, toLoc pos), ctx)
           ctx

    NExpr.Record(baseOpt, fields, toLoc pos), ctx

  | AIfExpr (cond, body, altOpt, pos) -> ngExpr docId ctx (desugarIf cond body altOpt pos)

  | AMatchExpr (cond, arms, pos) ->
    let cond, ctx = cond |> onExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (AArm (pat, guardOpt, body, pos)) ->
             let pat, ctx = pat |> onPat ctx
             let guardOpt, ctx = guardOpt |> onExprOpt ctx
             let body, ctx = body |> onExpr ctx
             (pat, guardOpt, body, toLoc pos), ctx)
           ctx

    NExpr.Match(cond, arms, toLoc pos), ctx

  | AFunExpr (pats, body, pos) -> ngExpr docId ctx (desugarFun pats body pos)

  | ANavExpr (l, r, pos) ->
    let l, ctx = l |> onExpr ctx
    NExpr.Nav(l, onName r, toLoc pos), ctx

  | AIndexExpr (l, r, pos) ->
    match expr with
    | AIndexExpr (x, ARangeExpr (l, r, _), _) ->
      let x, ctx = x |> onExpr ctx
      let l, ctx = l |> onExpr ctx
      let r, ctx = r |> onExpr ctx
      let loc = toLoc pos
      NExpr.Slice(x, l, r, loc), ctx

    | _ ->
      let l, ctx = l |> onExpr ctx
      let r, ctx = r |> onExpr ctx
      let loc = toLoc pos
      NExpr.Index(l, r, loc), ctx

  | AUnaryExpr (MinusUnary, arg, pos) ->
    match desugarMinusUnary arg with
    | Some arg -> ngExpr docId ctx arg

    | None ->
      let arg, ctx = arg |> onExpr ctx
      NExpr.Unary(MinusUnary, arg, toLoc pos), ctx

  | AUnaryExpr (op, arg, pos) ->
    let arg, ctx = arg |> onExpr ctx
    NExpr.Unary(op, arg, toLoc pos), ctx

  | ABinaryExpr (NotEqualBinary, l, r, pos) -> ngExpr docId ctx (desugarBinNe l r pos)
  | ABinaryExpr (LessEqualBinary, l, r, pos) -> ngExpr docId ctx (desugarBinLe l r pos)
  | ABinaryExpr (GreaterBinary, l, r, pos) -> ngExpr docId ctx (desugarBinGt l r pos)
  | ABinaryExpr (GreaterEqualBinary, l, r, pos) -> ngExpr docId ctx (desugarBinGe l r pos)
  | ABinaryExpr (LogicalAndBinary, l, r, pos) -> ngExpr docId ctx (desugarBinAnd l r pos)
  | ABinaryExpr (LogicalOrBinary, l, r, pos) -> ngExpr docId ctx (desugarBinOr l r pos)
  | ABinaryExpr (PipeBinary, l, r, pos) -> ngExpr docId ctx (desugarBinPipe l r pos)

  | ABinaryExpr (op, l, r, pos) ->
    let l, ctx = l |> onExpr ctx
    let r, ctx = r |> onExpr ctx
    NExpr.Binary(op, l, r, toLoc pos), ctx

  | ATupleExpr (items, pos) ->
    let items, ctx = items |> onExprs ctx
    NExpr.Tuple(items, toLoc pos), ctx

  // (__type: 'T)
  | AAscribeExpr (AIdentExpr (Name ("__type", _), []), ty, pos) ->
    let ty, ctx = ty |> onTy ctx
    NExpr.TyPlaceholder(ty, toLoc pos), ctx

  | AAscribeExpr (body, ty, pos) ->
    let body, ctx = body |> onExpr ctx
    let ty, ctx = ty |> onTy ctx
    NExpr.Ascribe(body, ty, toLoc pos), ctx

  | ASemiExpr (stmts, last, _) ->
    let stmts, ctx =
      stmts
      |> List.mapFold
           (fun ctx expr ->
             let expr, ctx = expr |> onExpr ctx
             NStmt.Expr expr, ctx)
           ctx

    let last, ctx = last |> onExpr ctx
    NExpr.Block(stmts, last), ctx

  | ALetExpr (contents, next, pos) ->
    let stmt, ctx = ngLetContents docId ctx contents pos
    let next, ctx = next |> onExpr ctx
    NExpr.Block([ stmt ], next), ctx

  | ARangeExpr _ -> unreachable () // Generated only inside of AIndexExpr.

let private ngTyArgs docId tyArgs =
  tyArgs
  |> List.map (fun (Name (ident, pos)) -> "'" + ident, toLoc docId pos)

let private ngDecl docId attrs ctx decl : NDecl * NirGenCtx =
  let onTy ctx ty = ngTy docId ctx ty
  let onTyOpt ctx tyOpt = optionMapFold (ngTy docId) ctx tyOpt
  let onPat ctx pat = ngPat docId ctx pat
  let onPats ctx pats = List.mapFold (ngPat docId) ctx pats
  let onExpr ctx expr = ngExpr docId ctx expr
  let onExprs ctx exprs = List.mapFold (ngExpr docId) ctx exprs

  let onExprOpt ctx exprOpt =
    optionMapFold (ngExpr docId) ctx exprOpt

  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match decl with
  | AExprDecl expr ->
    let expr, ctx = expr |> onExpr ctx
    NDecl.Stmt(NStmt.Expr expr), ctx

  | ALetDecl (contents, pos) ->
    let stmt, ctx = ngLetContents docId ctx contents pos
    NDecl.Stmt stmt, ctx

  | ATySynonymDecl (vis, name, tyArgs, bodyTy, pos) ->
    let bodyTy, ctx = bodyTy |> onTy ctx
    let tyArgs = tyArgs |> ngTyArgs docId
    NDecl.TySynonym(vis, onName name, tyArgs, bodyTy, toLoc pos), ctx

  | AUnionTyDecl (vis, name, tyArgs, variants, pos) ->
    let tyArgs = tyArgs |> ngTyArgs docId

    let variants, ctx =
      variants
      |> List.mapFold
           (fun ctx (AVariant (name, payloadTyOpt, pos)) ->
             let payloadTyOpt, ctx = payloadTyOpt |> onTyOpt ctx
             (onName name, payloadTyOpt, toLoc pos), ctx)
           ctx

    NDecl.Union(vis, onName name, tyArgs, variants, toLoc pos), ctx

  | ARecordTyDecl (vis, name, tyArgs, fields, pos) ->
    let repr =
      attrs
      |> List.exists (fun a ->
        match a with
        | ABinaryExpr (AppBinary, AIdentExpr (Name ("Repr", _), []), ALitExpr (StrLit "C", _), _) -> true
        | _ -> false)
      |> IsCRepr

    let tyArgs = tyArgs |> ngTyArgs docId

    let fields, ctx =
      fields
      |> List.mapFold
           (fun ctx (name, ty, pos) ->
             let ty, ctx = ty |> onTy ctx
             (onName name, ty, toLoc pos), ctx)
           ctx

    NDecl.Record(vis, onName name, tyArgs, fields, repr, toLoc pos), ctx

  | AOpenDecl (path, pos) ->
    let path = path |> List.map onName
    NDecl.Open(path, toLoc pos), ctx

  | AModuleSynonymDecl (name, path, pos) ->
    let path = path |> List.map onName
    NDecl.ModuleSynonym(onName name, path, toLoc pos), ctx

  | AModuleDecl (isRec, vis, name, decls, pos) ->
    let decls, ctx = decls |> ngDecls docId attrs ctx
    NDecl.Module(NModuleDecl(isRec, vis, onName name, decls, toLoc pos)), ctx

  | AAttrDecl (attr, next, _) ->
    let rec prepend attr acc =
      match attr with
      | ASemiExpr (stmts, last, _) -> List.append stmts (last :: acc)
      | _ -> attr :: acc

    ngDecl docId (prepend attr attrs) ctx next

let private ngDecls docId attrs ctx decls =
  decls |> List.mapFold (ngDecl docId attrs) ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

/// Converts an AST of single file to an NIR module.
let genNir
  (projectName: ProjectName)
  (moduleName: ModuleName)
  (docId: DocId)
  (root: ARoot)
  : NRoot * (NirGenLog * Loc) list =
  let (ARoot (headOpt, decls)) = root

  let zeroPos = 0, 0
  let zeroLoc = toLoc docId zeroPos
  let ctx = emptyCtx

  let fileModuleDecl, ctx =
    let namePos, headPos =
      match headOpt with
      | Some ([ _; Name (_, namePos) ], headPos) -> namePos, headPos
      | _ -> zeroPos, zeroPos

    let decls, ctx = decls |> ngDecls docId [] ctx
    let name = moduleName, toLoc docId namePos
    let loc = toLoc docId headPos
    NDecl.Module(NModuleDecl(IsRec, PublicVis, name, decls, loc)), ctx

  let projectModuleDecl, ctx =
    let name = projectName, zeroLoc
    let decls = [ fileModuleDecl ]
    NModuleDecl(IsRec, PublicVis, name, decls, zeroLoc), ctx

  projectModuleDecl, ctx

let nirGenLogToString log =
  match log with
  | InvalidVisError -> "Invisible"
  | NirGenError message -> message
