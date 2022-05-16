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

let private axUnit pos = ATupleExpr(pos, [], None)
let private axFalse pos = ALitExpr(BoolLit false, pos)
let private axTrue pos = ALitExpr(BoolLit true, pos)

/// `not x` ==> `x = false`
let private axNot arg pos =
  let falseExpr = axFalse pos
  ABinaryExpr(EqualBinary, arg, pos, falseExpr)

// -----------------------------------------------
// Desugar
// -----------------------------------------------

/// `[ x; y; ... ]`. Desugars to a chain of `::`s.
let private desugarListPat pats pos : APat =
  assert (pats |> List.isEmpty |> not)

  let rec go pats =
    match pats with
    | [] -> AListPat(pos, [], None)

    | head :: tail ->
      let tail = go tail
      AConsPat(head, pos, tail)

  go pats

let private desugarListExpr items pos : AExpr =
  assert (items |> List.isEmpty |> not)

  let rec go items =
    match items with
    | [] -> AListExpr(pos, [], None)

    | head :: tail ->
      let tail = go tail
      ABinaryExpr(ConsBinary, head, pos, tail)

  go items

/// Desugars `if` to `match`.
///
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let private desugarIf ifPos cond body altOpt : AExpr =
  let pos = ifPos

  let alt =
    match altOpt with
    | Some alt -> alt
    | None -> axUnit pos

  let arms =
    [ None, apTrue pos, None, pos, body
      None, apFalse pos, None, pos, alt ]

  AMatchExpr(ifPos, cond, None, arms)

/// Desugars to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let private desugarFun funPos argPats equalPos body : AExpr =
  let name = "fun"

  ALetExpr(
    funPos,
    ALetContents.LetFun(NotRec, PrivateVis, Name(name, funPos), argPats, None, equalPos, body),
    Some(AIdentExpr(Name(name, funPos), None))
  )

/// Desugars `-x`.
///
/// `-(-x)` ==> x.
/// `-n` (n: literal).
let private desugarMinusUnary arg : AExpr option =
  match arg with
  | AUnaryExpr (MinusUnary, _, arg) -> Some arg

  | ALitExpr (IntLit text, pos) -> ALitExpr(IntLit("-" + text), pos) |> Some

  | ALitExpr (IntLitWithFlavor (text, flavor), pos) ->
    ALitExpr(IntLitWithFlavor("-" + text, flavor), pos)
    |> Some

  | ALitExpr (FloatLit text, pos) -> ALitExpr(FloatLit("-" + text), pos) |> Some

  | _ -> None

/// `l <> r` ==> `not (l = r)`
let private desugarBinNe l r pos : AExpr =
  let equalExpr = ABinaryExpr(EqualBinary, l, pos, r)
  axNot equalExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let private desugarBinLe l r pos : AExpr =
  let ltExpr = ABinaryExpr(LessBinary, r, pos, l)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let private desugarBinGt l r pos : AExpr = ABinaryExpr(LessBinary, r, pos, l)

/// `l >= r` ==> `not (l < r)`
let private desugarBinGe l r pos : AExpr =
  let ltExpr = ABinaryExpr(LessBinary, l, pos, r)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let private desugarBinAnd l r pos : AExpr = desugarIf pos l r (Some(axFalse pos))

/// `l || r` ==> `if l then true else r`
let private desugarBinOr l r pos : AExpr = desugarIf pos l (axTrue pos) (Some r)

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let private desugarBinPipe l r pos : AExpr = ABinaryExpr(AppBinary, r, pos, l)

/// `let f ... : ty = body` ==> `let f ... = body : ty`
let private desugarResultTy expr resultTyOpt : AExpr =
  match resultTyOpt with
  | Some (colonPos, ascriptionTy) -> AAscribeExpr(expr, colonPos, ascriptionTy)
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

  | AAppTy ([], Some (Name ("_", pos)), None) -> NTy.Infer(toLoc pos), ctx

  | AAppTy (quals, None, _) ->
    match List.tryLast quals with
    | Some (_, (y, x)) -> NTy.Bad(toLoc (y, x + 1)), ctx
    | None -> unreachable ()

  | AAppTy (quals, Some name, tyArgs) ->
    let quals =
      quals |> List.map (fun (name, _) -> onName name)

    let name = onName name
    let _, loc = name

    let tyArgs, ctx =
      match tyArgs with
      | Some (_, tyArgs, _) -> onTys ctx tyArgs
      | None -> [], ctx

    NTy.App(quals, name, tyArgs, loc), ctx

  | AVarTy (Name (ident, pos)) -> NTy.Var("'" + ident, toLoc pos), ctx

  | AParenTy (_, ty, _) -> ngTy docId ctx ty

  // `ty suffix` ===> `suffix<ty>`
  | ASuffixTy (innerTy, Name (suffix, pos)) ->
    let innerTy, ctx = onTy ctx innerTy
    let loc = toLoc pos
    NTy.App([], (suffix, loc), [ innerTy ], loc), ctx

  | ATupleTy (itemTys, pos) ->
    let itemTys, ctx = onTys ctx itemTys
    NTy.Tuple(itemTys, toLoc pos), ctx

  | AFunTy (sTy, pos, tTy) ->
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
  | AIdentPat (visOpt, Name (ident, pos)) ->
    let vis =
      match visOpt with
      | Some (vis, _) -> vis
      | None -> PublicVis

    NPat.Ident(vis, (ident, toLoc pos)), ctx

  | AParenPat (_, pat, _) -> ngPat docId ctx pat

  | AListPat (pos, [], _) -> NPat.Nil(toLoc pos), ctx
  | AListPat (pos, pats, _) -> ngPat docId ctx (desugarListPat pats pos)

  | ANavPat (_, pos, None) -> NPat.Bad(toLoc pos), ctx

  | ANavPat (l, pos, Some r) ->
    let l, ctx = l |> onPat ctx
    let loc = toLoc pos
    NPat.Nav(l, onName r, loc), ctx

  | AAppPat (calleePat, pos, argPat) ->
    let calleePat, ctx = calleePat |> onPat ctx
    let argPat, ctx = argPat |> onPat ctx
    NPat.VariantApp(calleePat, argPat, toLoc pos), ctx

  | AConsPat (l, pos, r) ->
    let l, ctx = l |> onPat ctx
    let r, ctx = r |> onPat ctx
    NPat.Cons(l, r, toLoc pos), ctx

  | ATuplePat (lPos, pats, _) ->
    let pats, ctx = pats |> onPats ctx
    NPat.Tuple(pats, toLoc lPos), ctx

  | AAsPat (bodyPat, pos, name) ->
    let bodyPat, ctx = bodyPat |> onPat ctx
    NPat.As(bodyPat, onName name, toLoc pos), ctx

  | AAscribePat (bodyPat, pos, ty) ->
    let bodyPat, ctx = bodyPat |> onPat ctx
    let ty, ctx = ty |> onTy ctx
    NPat.Ascribe(bodyPat, ty, toLoc pos), ctx

  | AOrPat (l, pos, r) ->
    let l, ctx = l |> onPat ctx
    let r, ctx = r |> onPat ctx
    NPat.Or(l, r, toLoc pos), ctx

let private ngLetContents docId ctx pos (contents: ALetContents) : NStmt * NirGenCtx =
  let onPat ctx pat = ngPat docId ctx pat
  let onPats ctx pats = List.mapFold (ngPat docId) ctx pats
  let onExpr ctx expr = ngExpr docId ctx expr
  let toLoc (y, x) = Loc(docId, y, x)
  let onName (Name (ident, pos)) = ident, toLoc pos

  match contents with
  | ALetContents.LetFun (isRec, vis, name, argPats, resultTyOpt, _, body) ->
    let argPats, ctx = argPats |> onPats ctx

    let body, ctx =
      let body = desugarResultTy body resultTyOpt
      body |> onExpr ctx

    NStmt.LetFun(isRec, vis, onName name, argPats, body, toLoc pos), ctx

  | ALetContents.LetVal (_, pat, _, body) ->
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

  | AIdentExpr (name, tyArgList) ->
    let tyArgs, ctx =
      match tyArgList with
      | Some (_, tyArgs, _) -> tyArgs |> onTys ctx
      | None -> [], ctx

    NExpr.Ident(onName name, tyArgs), ctx

  | AParenExpr (_, expr, _) -> ngExpr docId ctx expr

  | AListExpr (pos, [], _) -> NExpr.Nil(toLoc pos), ctx
  | AListExpr (pos, items, _) -> ngExpr docId ctx (desugarListExpr items pos)

  | ARecordExpr (pos, baseOpt, fields, _) ->
    let baseOpt, ctx =
      match baseOpt with
      | Some (baseExpr, _) ->
        let expr, ctx = onExpr ctx baseExpr
        Some expr, ctx

      | None -> None, ctx

    let fields, ctx =
      fields
      |> List.mapFold
           (fun ctx (name, pos, init) ->
             let init, ctx = init |> onExpr ctx
             (onName name, init, toLoc pos), ctx)
           ctx

    NExpr.Record(baseOpt, fields, toLoc pos), ctx

  | AIfExpr (ifPos, cond, _, body, altOpt) ->
    let altOpt = altOpt |> Option.map snd
    ngExpr docId ctx (desugarIf ifPos cond body altOpt)

  | AMatchExpr (matchPos, cond, _, arms) ->
    let cond, ctx = cond |> onExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pos, pat, guardOpt, _, body) ->
             let pos = pos |> Option.defaultValue matchPos
             let pat, ctx = pat |> onPat ctx

             let guardOpt, ctx =
               match guardOpt with
               | Some (_, guard) -> onExprOpt ctx (Some guard)
               | None -> None, ctx

             let body, ctx = body |> onExpr ctx
             (pat, guardOpt, body, toLoc pos), ctx)
           ctx

    NExpr.Match(cond, arms, toLoc matchPos), ctx

  | AFunExpr (funPos, argPats, arrowPos, body) -> ngExpr docId ctx (desugarFun funPos argPats arrowPos body)

  | ANavExpr (_, pos, None) -> NExpr.Bad(toLoc pos), ctx

  | ANavExpr (l, pos, Some r) ->
    let l, ctx = l |> onExpr ctx
    NExpr.Nav(l, onName r, toLoc pos), ctx

  | AIndexExpr (l, pos, _, r, _) ->
    match expr with
    | AIndexExpr (x, _, _, ARangeExpr (l, _, r), _) ->
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

  | AUnaryExpr (MinusUnary, pos, arg) ->
    match desugarMinusUnary arg with
    | Some arg -> ngExpr docId ctx arg

    | None ->
      let arg, ctx = arg |> onExpr ctx
      NExpr.Unary(MinusUnary, arg, toLoc pos), ctx

  | AUnaryExpr (op, pos, arg) ->
    let arg, ctx = arg |> onExpr ctx
    NExpr.Unary(op, arg, toLoc pos), ctx

  | ABinaryExpr (NotEqualBinary, l, pos, r) -> ngExpr docId ctx (desugarBinNe l r pos)
  | ABinaryExpr (LessEqualBinary, l, pos, r) -> ngExpr docId ctx (desugarBinLe l r pos)
  | ABinaryExpr (GreaterBinary, l, pos, r) -> ngExpr docId ctx (desugarBinGt l r pos)
  | ABinaryExpr (GreaterEqualBinary, l, pos, r) -> ngExpr docId ctx (desugarBinGe l r pos)
  | ABinaryExpr (LogicalAndBinary, l, pos, r) -> ngExpr docId ctx (desugarBinAnd l r pos)
  | ABinaryExpr (LogicalOrBinary, l, pos, r) -> ngExpr docId ctx (desugarBinOr l r pos)
  | ABinaryExpr (PipeBinary, l, pos, r) -> ngExpr docId ctx (desugarBinPipe l r pos)

  | ABinaryExpr (op, l, pos, r) ->
    let l, ctx = l |> onExpr ctx
    let r, ctx = r |> onExpr ctx
    NExpr.Binary(op, l, r, toLoc pos), ctx

  | ATupleExpr (lPos, items, _) ->
    let items, ctx = items |> onExprs ctx
    NExpr.Tuple(items, toLoc lPos), ctx

  // (__type: 'T)
  | AAscribeExpr (AIdentExpr (Name ("__type", _), None), pos, ty) ->
    let ty, ctx = ty |> onTy ctx
    NExpr.TyPlaceholder(ty, toLoc pos), ctx

  | AAscribeExpr (body, pos, ty) ->
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

  | ALetExpr (letPos, contents, nextOpt) ->
    let stmt, ctx = ngLetContents docId ctx letPos contents
    let nextOpt, ctx = nextOpt |> onExprOpt ctx

    let next =
      match nextOpt with
      | Some it -> it
      | None -> NExpr.Tuple([], toLoc letPos)

    NExpr.Block([ stmt ], next), ctx

  | ARangeExpr _ -> unreachable () // Generated only inside of AIndexExpr.

let private ngTyParamList docId tyParamList =
  let tyArgs =
    match tyParamList with
    | Some (_, tyArgs, _) -> tyArgs
    | None -> []

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

  | ATySynonymDecl (pos, vis, name, tyParamList, _, bodyTy) ->
    let bodyTy, ctx = bodyTy |> onTy ctx
    let tyParamList = tyParamList |> ngTyParamList docId
    NDecl.TySynonym(vis, onName name, tyParamList, bodyTy, toLoc pos), ctx

  | AUnionTyDecl (pos, vis, name, tyParamList, _, variants) ->
    let tyParamList = tyParamList |> ngTyParamList docId

    let variants, ctx =
      variants
      |> List.mapFold
           (fun ctx (pos, name, payloadTyOpt) ->
             let payloadTyOpt, ctx =
               match payloadTyOpt with
               | Some (_, itemTys) ->
                 let itemTys, ctx =
                   itemTys |> List.map snd |> List.mapFold onTy ctx

                 let payloadTy =
                   match itemTys with
                   | [ ty ] -> ty
                   | _ -> NTy.Tuple(itemTys, toLoc pos)

                 Some payloadTy, ctx

               | None -> None, ctx

             (onName name, payloadTyOpt, toLoc pos), ctx)
           ctx

    NDecl.Union(vis, onName name, tyParamList, variants, toLoc pos), ctx

  | ARecordTyDecl (pos, vis, name, tyParamList, _, _, fields, _) ->
    let repr =
      attrs
      |> List.exists (fun a ->
        // Unwrap paren of arg.
        let a =
          match a with
          | ABinaryExpr (binary, l, pos, AParenExpr (_, r, _)) -> ABinaryExpr(binary, l, pos, r)
          | _ -> a

        match a with
        | ABinaryExpr (AppBinary, AIdentExpr (Name ("Repr", _), None), _, ALitExpr (StringLit "C", _)) -> true
        | _ -> false)
      |> IsCRepr

    let tyParamList = tyParamList |> ngTyParamList docId

    let fields, ctx =
      fields
      |> List.mapFold
           (fun ctx (name, ty, pos) ->
             let ty, ctx = ty |> onTy ctx
             (onName name, ty, toLoc pos), ctx)
           ctx

    NDecl.Record(vis, onName name, tyParamList, fields, repr, toLoc pos), ctx

  | AOpenDecl (pos, path) ->
    let path = path |> List.map onName
    NDecl.Open(path, toLoc pos), ctx

  | AModuleSynonymDecl (pos, name, _, path) ->
    let path = path |> List.map onName
    NDecl.ModuleSynonym(onName name, path, toLoc pos), ctx

  | AModuleDecl (pos, isRec, vis, name, _, decls) ->
    let decls, ctx = decls |> ngDecls docId attrs ctx
    NDecl.Module(NModuleDecl(isRec, vis, onName name, decls, toLoc pos)), ctx

  | AAttrDecl (_, attr, _, next) ->
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
      | Some (headPos, [ _; Name (_, namePos) ]) -> namePos, headPos
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
