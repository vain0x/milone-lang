/// Converts an abstract syntax tree (AST)
/// to high-level intermediate representation (HIR).
///
/// ## Motivation
///
/// 1. AST should be decoupled with HIR.
///
/// AST is for syntactical analysis/transformations
/// but HIR is for semantic analysis/transformations.
/// The two have different concerns and grow independently.
///
/// 2. AST is redundant and confusing
///
/// AST is optimal for humans but not for analysis.
/// For example, `[1; 2]` and `1 :: 2 :: []` have the same meaning
/// and no need to be distinct for the compiler, i.e. *syntax sugar*.
/// This stage is the best place to desugar them.
///
/// Another example, `let` expressions are confusing whether
/// they introduce either functions or variables. The two kind of
/// entities have different behavior in the following stages.
module rec MiloneLang.AstToHir

open MiloneLang.Types
open MiloneLang.Helpers

/// Convert pos to loc.
let toLoc (doc: DocId) (pos: Pos): Loc =
  let row, column = pos
  doc, row, column

let opToPrim op =
  match op with
  | AddBinary -> HPrim.Add

  | SubBinary -> HPrim.Sub

  | MulBinary -> HPrim.Mul

  | DivBinary -> HPrim.Div

  | ModBinary -> HPrim.Mod

  | EqualBinary -> HPrim.Eq

  | LessBinary -> HPrim.Lt

  | ConsBinary -> HPrim.Cons

  | NotEqualBinary
  | LessEqualBinary
  | GreaterBinary
  | GreaterEqualBinary
  | LogAndBinary
  | LogOrBinary
  | AppBinary
  | PipeBinary -> failwithf "NEVER: %A" op

/// `[x; y; ..]`. Desugar to a chain of (::).
let desugarListLitPat pats pos =
  assert (pats |> listIsEmpty |> not)

  let rec go pats =
    match pats with
    | [] -> APat.ListLit([], pos)

    | head :: tail ->
        let tail = go tail
        APat.Cons(head, tail, pos)

  go pats

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let desugarListLitExpr items pos =
  assert (items |> listIsEmpty |> not)

  let rec go items =
    match items with
    | [] -> AExpr.ListLit([], pos)

    | head :: tail ->
        let tail = go tail
        AExpr.Bin(ConsBinary, head, tail, pos)

  go items

/// Desugar `if` to `match`.
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let desugarIf cond body alt pos =
  let alt =
    match alt with
    | AExpr.Missing _ -> axUnit pos
    | _ -> alt

  let arms =
    [ AArm(apTrue pos, axTrue pos, body, pos)
      AArm(apFalse pos, axTrue pos, alt, pos) ]

  AExpr.Match(cond, arms, pos)

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let desugarFun pats body pos =
  let ident = "fun"
  let pat = APat.Fun(ident, pats, pos)
  let next = AExpr.Ident(ident, pos)
  AExpr.Let(PrivateVis, pat, body, next, pos)

/// Desugar `-x` to `0 - x`.
let desugarUniNeg arg pos =
  let zero = AExpr.Lit(IntLit 0, pos)
  AExpr.Bin(SubBinary, zero, arg, pos)

/// `l <> r` ==> `not (l = r)`
let desugarBinNe l r pos =
  let eqExpr = AExpr.Bin(EqualBinary, l, r, pos)
  axNot eqExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let desugarBinLe l r pos =
  let ltExpr = AExpr.Bin(LessBinary, r, l, pos)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let desugarBinGt l r pos = AExpr.Bin(LessBinary, r, l, pos)

/// `l >= r` ==> `not (l < r)`
let desugarBinGe l r pos =
  let ltExpr = AExpr.Bin(LessBinary, l, r, pos)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let desugarBinAnd l r pos = desugarIf l r (axFalse pos) pos

/// `l || r` ==> `if l then true else r`
let desugarBinOr l r pos = desugarIf l (axTrue pos) r pos

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let desugarBinPipe l r pos = AExpr.Bin(AppBinary, r, l, pos)

/// `s.[l .. r]` ==> `String.getSlice l r x`
/// NOTE: Evaluation order does change.
let tryDesugarIndexRange expr pos =
  match expr with
  | AExpr.Index (s, AExpr.Range ([ l; r ], _), _) ->
      let getSlice =
        AExpr.Nav(AExpr.Ident("String", pos), "getSlice", pos)

      true, axApp3 getSlice l r s pos

  | _ -> false, expr

/// Analyzes let syntax.
///
/// Annotation move just for simplification:
/// `let p : ty = body` ==>
///   `let p = body : ty`
///
/// Let to let-fun:
/// `let f x = body` ==>
///   `let-fun f(x) = body`
///
/// Let to let-val:
/// `let pat = body` ==>
///   `let-val pat = body`
let desugarLet vis pat body next pos =
  match pat with
  | APat.Anno (pat, annoTy, annoLoc) ->
      let body = AExpr.Anno(body, annoTy, annoLoc)
      desugarLet vis pat body next pos

  | APat.Fun (ident, args, _) -> ALet.LetFun(vis, ident, args, body, next, pos)

  | _ -> ALet.LetVal(vis, pat, body, next, pos)

let astToHirTy (docId: DocId) (ty: ATy, nameCtx: NameCtx): Ty * NameCtx =
  match ty with
  | AMissingTy pos ->
      let loc = toLoc docId pos
      Ty.Error loc, nameCtx

  | AAppTy (ident, argTys, _) ->
      let tySerial, nameCtx = nameCtx |> nameCtxAdd ident

      let argTys, nameCtx =
        (argTys, nameCtx) |> stMap (astToHirTy docId)

      tyRef tySerial argTys, nameCtx

  | ASuffixTy (lTy, ident, _) ->
      let lTy, nameCtx = (lTy, nameCtx) |> astToHirTy docId
      let tySerial, nameCtx = nameCtx |> nameCtxAdd ident
      tyRef tySerial [ lTy ], nameCtx

  | ATupleTy (itemTys, _) ->
      let itemTys, nameCtx =
        (itemTys, nameCtx) |> stMap (astToHirTy docId)

      tyTuple itemTys, nameCtx

  | AFunTy (sTy, tTy, _) ->
      let sTy, nameCtx = (sTy, nameCtx) |> astToHirTy docId
      let tTy, nameCtx = (tTy, nameCtx) |> astToHirTy docId
      tyFun sTy tTy, nameCtx

let astToHirPat (docId: DocId) (pat: APat, nameCtx: NameCtx): HPat * NameCtx =
  match pat with
  | APat.Missing pos -> failwithf "Missing pattern %s" (posToString pos)

  | APat.Lit (lit, pos) ->
      let loc = toLoc docId pos
      HPat.Lit(lit, loc), nameCtx

  | APat.Ident (ident, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let loc = toLoc docId pos
      HPat.Ref(serial, noTy, loc), nameCtx

  | APat.ListLit ([], pos) ->
      let loc = toLoc docId pos
      patNil noTy loc, nameCtx

  | APat.ListLit (pats, pos) ->
      let pat = desugarListLitPat pats pos
      (pat, nameCtx) |> astToHirPat docId

  | APat.Nav (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HPat.Nav(l, r, noTy, loc), nameCtx

  | APat.Call (calleePat, argPats, pos) ->
      let calleePat, nameCtx =
        (calleePat, nameCtx) |> astToHirPat docId

      let argPats, nameCtx =
        (argPats, nameCtx) |> stMap (astToHirPat docId)

      let loc = toLoc docId pos
      HPat.Call(calleePat, argPats, noTy, loc), nameCtx

  | APat.Cons (head, tail, pos) ->
      let head, nameCtx = (head, nameCtx) |> astToHirPat docId
      let tail, nameCtx = (tail, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HPat.Cons(head, tail, noTy, loc), nameCtx

  | APat.TupleLit (pats, pos) ->
      let pats, nameCtx =
        (pats, nameCtx) |> stMap (astToHirPat docId)

      let loc = toLoc docId pos
      HPat.Tuple(pats, noTy, loc), nameCtx

  | APat.As (pat, ident, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident

      let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId

      let loc = toLoc docId pos
      HPat.As(pat, serial, loc), nameCtx

  | APat.Anno (pat, ty, pos) ->
      let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId
      let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
      let loc = toLoc docId pos
      HPat.Anno(pat, ty, loc), nameCtx

  | APat.Or (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat docId
      let r, nameCtx = (r, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HPat.Or(l, r, noTy, loc), nameCtx

  | APat.Fun (_, _, pos) -> failwithf "Invalid occurrence of fun pattern: %s" (posToString pos)

let astToHirExpr (docId: DocId) (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  match expr with
  | AExpr.Missing pos ->
      let loc = toLoc docId pos
      HExpr.Error("Missing expression", loc), nameCtx

  | AExpr.Lit (lit, pos) ->
      let loc = toLoc docId pos
      HExpr.Lit(lit, loc), nameCtx

  | AExpr.Ident (ident, pos) ->
      let loc = toLoc docId pos

      // NOTE: Work in a local function to reduce the size of stack frames of `astToHirExpr`.
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        HExpr.Ref(serial, noTy, loc), nameCtx

      doArm ()

  | AExpr.ListLit ([], pos) ->
      let loc = toLoc docId pos
      hxNil noTy loc, nameCtx

  | AExpr.ListLit (items, pos) ->
      let doArm () =
        let expr = desugarListLitExpr items pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.If (cond, body, alt, pos) ->
      let doArm () =
        let expr = desugarIf cond body alt pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Match (target, arms, pos) ->
      let doArm () =
        // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
        let onArm (AArm (pat, guard, body, loc), nameCtx) =
          let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId

          let loc = toLoc docId pos

          let guard, nameCtx =
            match guard with
            | AExpr.Missing _ -> hxTrue loc, nameCtx
            | _ -> (guard, nameCtx) |> astToHirExpr docId

          let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
          (pat, guard, body), nameCtx

        let target, nameCtx = (target, nameCtx) |> astToHirExpr docId
        let arms, nameCtx = (arms, nameCtx) |> stMap onArm
        let loc = toLoc docId pos
        HExpr.Match(target, arms, noTy, loc), nameCtx

      doArm ()

  | AExpr.Fun (pats, body, pos) ->
      let doArm () =
        let expr = desugarFun pats body pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Nav (l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        HExpr.Nav(l, r, noTy, loc), nameCtx

      doArm ()

  | AExpr.Index (l, r, pos) ->
      let doArm () =
        match tryDesugarIndexRange expr pos with
        | true, expr -> (expr, nameCtx) |> astToHirExpr docId

        | false, _ ->
            let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
            let r, nameCtx = (r, nameCtx) |> astToHirExpr docId

            let loc = toLoc docId pos

            let hxIndex =
              hxApp (hxApp (HExpr.Prim(HPrim.Index, noTy, loc)) l noTy loc) r noTy loc

            hxIndex, nameCtx

      doArm ()

  | AExpr.Uni (NegUnary, arg, pos) ->
      let doArm () =
        let expr = desugarUniNeg arg pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (NotEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinNe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (LessEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinLe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (GreaterBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGt l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (GreaterEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (LogAndBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinAnd l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (LogOrBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinOr l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (PipeBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinPipe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AExpr.Bin (AppBinary, l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let r, nameCtx = (r, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        hxApp l r noTy loc, nameCtx

      doArm ()

  | AExpr.Bin (op, l, r, pos) ->
      let doArm () =
        let prim = op |> opToPrim
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let r, nameCtx = (r, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        let primExpr = HExpr.Prim(prim, noTy, loc)
        hxApp (hxApp primExpr l noTy loc) r noTy loc, nameCtx

      doArm ()

  | AExpr.Range (_, pos) ->
      let loc = toLoc docId pos
      HExpr.Error("Invalid use of range syntax.", loc), nameCtx

  | AExpr.TupleLit (items, pos) ->
      let doArm () =
        let loc = toLoc docId pos

        let items, nameCtx =
          (items, nameCtx) |> stMap (astToHirExpr docId)

        hxTuple items loc, nameCtx

      doArm ()

  | AExpr.Anno (body, ty, pos) ->
      let doArm () =
        let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
        let loc = toLoc docId pos
        hxAnno body ty loc, nameCtx

      doArm ()

  | AExpr.Semi (exprs, pos) ->
      let doArm () =
        assert (exprs |> listIsEmpty |> not)

        let exprs, nameCtx =
          (exprs, nameCtx) |> stMap (astToHirExpr docId)

        let loc = toLoc docId pos
        hxSemi exprs loc, nameCtx

      doArm ()

  | AExpr.Let (vis, pat, body, next, pos) ->
      let doArm () =
        match desugarLet vis pat body next pos with
        | ALet.LetFun (vis, ident, args, body, next, pos) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd ident
            let isMainFun = false // Name resolution should correct this.

            let args, nameCtx =
              (args, nameCtx) |> stMap (astToHirPat docId)

            let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
            let next, nameCtx = (next, nameCtx) |> astToHirExpr docId
            let loc = toLoc docId pos
            HExpr.LetFun(serial, vis, isMainFun, args, body, next, noTy, loc), nameCtx

        | ALet.LetVal (vis, pat, body, next, pos) ->
            let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId
            let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
            let next, nameCtx = (next, nameCtx) |> astToHirExpr docId
            let loc = toLoc docId pos
            HExpr.Let(vis, pat, body, next, noTy, loc), nameCtx

      doArm ()

  | AExpr.TySynonym (vis, ident, ty, pos) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
        let loc = toLoc docId pos
        HExpr.TyDecl(serial, vis, TyDecl.Synonym(ty, loc), loc), nameCtx

      doArm ()

  | AExpr.TyUnion (vis, ident, variants, pos) ->
      let doArm () =
        let onVariant (AVariant (ident, payloadTy, _variantLoc), nameCtx) =
          let serial, nameCtx = nameCtx |> nameCtxAdd ident

          let hasPayload, payloadTy, nameCtx =
            match payloadTy with
            | Some ty ->
                let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
                true, ty, nameCtx
            | None -> false, tyUnit, nameCtx

          (ident, serial, hasPayload, payloadTy), nameCtx

        let unionSerial, nameCtx = nameCtx |> nameCtxAdd ident
        let variants, nameCtx = (variants, nameCtx) |> stMap onVariant
        let loc = toLoc docId pos
        HExpr.TyDecl(unionSerial, vis, TyDecl.Union(ident, variants, loc), loc), nameCtx

      doArm ()

  | AExpr.Open (path, pos) ->
      let doArm () =
        let loc = toLoc docId pos
        HExpr.Open(path, loc), nameCtx

      doArm ()

let astToHir (docId: DocId) (root: ARoot, nameCtx: NameCtx): HExpr * NameCtx =
  match root with
  | ARoot.Expr expr -> astToHirExpr docId (expr, nameCtx)

  | ARoot.Module (ident, body, pos) ->
      let body, nameCtx = astToHirExpr docId (body, nameCtx)
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let loc = toLoc docId pos
      let next = hxUnit loc
      HExpr.Module(serial, body, next, loc), nameCtx
