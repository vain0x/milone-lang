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
    | [] -> AListPat([], pos)

    | head :: tail ->
        let tail = go tail
        AConsPat(head, tail, pos)

  go pats

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let desugarListLitExpr items pos =
  assert (items |> listIsEmpty |> not)

  let rec go items =
    match items with
    | [] -> AListExpr([], pos)

    | head :: tail ->
        let tail = go tail
        ABinaryExpr(ConsBinary, head, tail, pos)

  go items

/// Desugar `if` to `match`.
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let desugarIf cond body alt pos =
  let alt =
    match alt with
    | AMissingExpr _ -> axUnit pos
    | _ -> alt

  let arms =
    [ AArm(apTrue pos, axTrue pos, body, pos)
      AArm(apFalse pos, axTrue pos, alt, pos) ]

  AMatchExpr(cond, arms, pos)

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let desugarFun pats body pos =
  let ident = "fun"
  let pat = AFunDeclPat(ident, pats, pos)
  let next = AIdentExpr(ident, pos)
  ALetExpr(PrivateVis, pat, body, next, pos)

/// Desugar `-x` to `0 - x`.
let desugarUniNeg arg pos =
  let zero = ALitExpr(IntLit 0, pos)
  ABinaryExpr(SubBinary, zero, arg, pos)

/// `l <> r` ==> `not (l = r)`
let desugarBinNe l r pos =
  let eqExpr = ABinaryExpr(EqualBinary, l, r, pos)
  axNot eqExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let desugarBinLe l r pos =
  let ltExpr = ABinaryExpr(LessBinary, r, l, pos)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let desugarBinGt l r pos = ABinaryExpr(LessBinary, r, l, pos)

/// `l >= r` ==> `not (l < r)`
let desugarBinGe l r pos =
  let ltExpr = ABinaryExpr(LessBinary, l, r, pos)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let desugarBinAnd l r pos = desugarIf l r (axFalse pos) pos

/// `l || r` ==> `if l then true else r`
let desugarBinOr l r pos = desugarIf l (axTrue pos) r pos

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let desugarBinPipe l r pos = ABinaryExpr(AppBinary, r, l, pos)

/// `s.[l .. r]` ==> `String.getSlice l r x`
/// NOTE: Evaluation order does change.
let tryDesugarIndexRange expr pos =
  match expr with
  | AIndexExpr (s, ARangeExpr ([ l; r ], _), _) ->
      let getSlice =
        ANavExpr(AIdentExpr("String", pos), "getSlice", pos)

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
  | AAnnoPat (pat, annoTy, annoLoc) ->
      let body = AAnnoExpr(body, annoTy, annoLoc)
      desugarLet vis pat body next pos

  | AFunDeclPat (ident, args, _) -> ALetFun(vis, ident, args, body, next, pos)

  | _ -> ALetVal(vis, pat, body, next, pos)

let astToHirTy (docId: DocId) (ty: ATy, nameCtx: NameCtx): Ty * NameCtx =
  match ty with
  | AMissingTy pos ->
      let loc = toLoc docId pos
      ErrorTy loc, nameCtx

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
  | AMissingPat pos -> failwithf "Missing pattern %s" (posToString pos)

  | ALitPat (lit, pos) ->
      let loc = toLoc docId pos
      HLitPat(lit, loc), nameCtx

  | AIdentPat (ident, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let loc = toLoc docId pos
      HRefPat(serial, noTy, loc), nameCtx

  | AListPat ([], pos) ->
      let loc = toLoc docId pos
      patNil noTy loc, nameCtx

  | AListPat (pats, pos) ->
      let pat = desugarListLitPat pats pos
      (pat, nameCtx) |> astToHirPat docId

  | ANavPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HNavPat(l, r, noTy, loc), nameCtx

  | AAppPat (calleePat, argPats, pos) ->
      let calleePat, nameCtx =
        (calleePat, nameCtx) |> astToHirPat docId

      let argPats, nameCtx =
        (argPats, nameCtx) |> stMap (astToHirPat docId)

      let loc = toLoc docId pos
      HCallPat(calleePat, argPats, noTy, loc), nameCtx

  | AConsPat (head, tail, pos) ->
      let head, nameCtx = (head, nameCtx) |> astToHirPat docId
      let tail, nameCtx = (tail, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HConsPat(head, tail, noTy, loc), nameCtx

  | ATuplePat (pats, pos) ->
      let pats, nameCtx =
        (pats, nameCtx) |> stMap (astToHirPat docId)

      let loc = toLoc docId pos
      HTuplePat(pats, noTy, loc), nameCtx

  | AAsPat (pat, ident, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident

      let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId

      let loc = toLoc docId pos
      HAsPat(pat, serial, loc), nameCtx

  | AAnnoPat (pat, ty, pos) ->
      let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId
      let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
      let loc = toLoc docId pos
      HAnnoPat(pat, ty, loc), nameCtx

  | AOrPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat docId
      let r, nameCtx = (r, nameCtx) |> astToHirPat docId
      let loc = toLoc docId pos
      HOrPat(l, r, noTy, loc), nameCtx

  | AFunDeclPat (_, _, pos) -> failwithf "Invalid occurrence of fun pattern: %s" (posToString pos)

let astToHirExpr (docId: DocId) (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  match expr with
  | AMissingExpr pos ->
      let loc = toLoc docId pos
      HErrorExpr("Missing expression", loc), nameCtx

  | ALitExpr (lit, pos) ->
      let loc = toLoc docId pos
      HLitExpr(lit, loc), nameCtx

  | AIdentExpr (ident, pos) ->
      let loc = toLoc docId pos

      // NOTE: Work in a local function to reduce the size of stack frames of `astToHirExpr`.
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        HRefExpr(serial, noTy, loc), nameCtx

      doArm ()

  | AListExpr ([], pos) ->
      let loc = toLoc docId pos
      hxNil noTy loc, nameCtx

  | AListExpr (items, pos) ->
      let doArm () =
        let expr = desugarListLitExpr items pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AIfExpr (cond, body, alt, pos) ->
      let doArm () =
        let expr = desugarIf cond body alt pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | AMatchExpr (target, arms, pos) ->
      let doArm () =
        // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
        let onArm (AArm (pat, guard, body, loc), nameCtx) =
          let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId

          let loc = toLoc docId pos

          let guard, nameCtx =
            match guard with
            | AMissingExpr _ -> hxTrue loc, nameCtx
            | _ -> (guard, nameCtx) |> astToHirExpr docId

          let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
          (pat, guard, body), nameCtx

        let target, nameCtx = (target, nameCtx) |> astToHirExpr docId
        let arms, nameCtx = (arms, nameCtx) |> stMap onArm
        let loc = toLoc docId pos
        HMatchExpr(target, arms, noTy, loc), nameCtx

      doArm ()

  | AFunExpr (pats, body, pos) ->
      let doArm () =
        let expr = desugarFun pats body pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ANavExpr (l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        HNavExpr(l, r, noTy, loc), nameCtx

      doArm ()

  | AIndexExpr (l, r, pos) ->
      let doArm () =
        match tryDesugarIndexRange expr pos with
        | true, expr -> (expr, nameCtx) |> astToHirExpr docId

        | false, _ ->
            let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
            let r, nameCtx = (r, nameCtx) |> astToHirExpr docId

            let loc = toLoc docId pos

            let hxIndex =
              hxApp (hxApp (HPrimExpr(HPrim.Index, noTy, loc)) l noTy loc) r noTy loc

            hxIndex, nameCtx

      doArm ()

  | AUnaryExpr (NegUnary, arg, pos) ->
      let doArm () =
        let expr = desugarUniNeg arg pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (NotEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinNe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (LessEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinLe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (GreaterBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGt l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (GreaterEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (LogAndBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinAnd l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (LogOrBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinOr l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (PipeBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinPipe l r pos
        (expr, nameCtx) |> astToHirExpr docId

      doArm ()

  | ABinaryExpr (AppBinary, l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let r, nameCtx = (r, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        hxApp l r noTy loc, nameCtx

      doArm ()

  | ABinaryExpr (op, l, r, pos) ->
      let doArm () =
        let prim = op |> opToPrim
        let l, nameCtx = (l, nameCtx) |> astToHirExpr docId
        let r, nameCtx = (r, nameCtx) |> astToHirExpr docId
        let loc = toLoc docId pos
        let primExpr = HPrimExpr(prim, noTy, loc)
        hxApp (hxApp primExpr l noTy loc) r noTy loc, nameCtx

      doArm ()

  | ARangeExpr (_, pos) ->
      let loc = toLoc docId pos
      HErrorExpr("Invalid use of range syntax.", loc), nameCtx

  | ATupleExpr (items, pos) ->
      let doArm () =
        let loc = toLoc docId pos

        let items, nameCtx =
          (items, nameCtx) |> stMap (astToHirExpr docId)

        hxTuple items loc, nameCtx

      doArm ()

  | AAnnoExpr (body, ty, pos) ->
      let doArm () =
        let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
        let loc = toLoc docId pos
        hxAnno body ty loc, nameCtx

      doArm ()

  | ASemiExpr (exprs, pos) ->
      let doArm () =
        assert (exprs |> listIsEmpty |> not)

        let exprs, nameCtx =
          (exprs, nameCtx) |> stMap (astToHirExpr docId)

        let loc = toLoc docId pos
        hxSemi exprs loc, nameCtx

      doArm ()

  | ALetExpr (vis, pat, body, next, pos) ->
      let doArm () =
        match desugarLet vis pat body next pos with
        | ALetFun (vis, ident, args, body, next, pos) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd ident
            let isMainFun = false // Name resolution should correct this.

            let args, nameCtx =
              (args, nameCtx) |> stMap (astToHirPat docId)

            let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
            let next, nameCtx = (next, nameCtx) |> astToHirExpr docId
            let loc = toLoc docId pos
            HLetFunExpr(serial, vis, isMainFun, args, body, next, noTy, loc), nameCtx

        | ALetVal (vis, pat, body, next, pos) ->
            let pat, nameCtx = (pat, nameCtx) |> astToHirPat docId
            let body, nameCtx = (body, nameCtx) |> astToHirExpr docId
            let next, nameCtx = (next, nameCtx) |> astToHirExpr docId
            let loc = toLoc docId pos
            HLetValExpr(vis, pat, body, next, noTy, loc), nameCtx

      doArm ()

  | ATySynonymExpr (vis, ident, ty, pos) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy docId
        let loc = toLoc docId pos
        HTyDeclExpr(serial, vis, TySynonymDecl(ty, loc), loc), nameCtx

      doArm ()

  | AUnionTyExpr (vis, ident, variants, pos) ->
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
        HTyDeclExpr(unionSerial, vis, UnionTyDecl(ident, variants, loc), loc), nameCtx

      doArm ()

  | AOpenExpr (path, pos) ->
      let doArm () =
        let loc = toLoc docId pos
        HOpenExpr(path, loc), nameCtx

      doArm ()

let astToHir (docId: DocId) (root: ARoot, nameCtx: NameCtx): HExpr * NameCtx =
  match root with
  | AExprRoot expr -> astToHirExpr docId (expr, nameCtx)

  | AModuleRoot (ident, body, pos) ->
      let body, nameCtx = astToHirExpr docId (body, nameCtx)
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let loc = toLoc docId pos
      let next = hxUnit loc
      HModuleExpr(serial, body, next, loc), nameCtx
