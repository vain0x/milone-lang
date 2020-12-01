/// # AstToHir
///
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

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir

/// Convert pos to loc.
let private toLoc (doc: DocId) (pos: Pos): Loc =
  let row, column = pos
  doc, row, column

let private opToPrim op =
  match op with
  | AddBinary -> HPrim.Add
  | SubBinary -> HPrim.Sub
  | MulBinary -> HPrim.Mul
  | DivBinary -> HPrim.Div
  | ModBinary -> HPrim.Mod
  | BitAndBinary -> HPrim.BitAnd
  | BitOrBinary -> HPrim.BitOr
  | BitXorBinary -> HPrim.BitXor
  | LeftShiftBinary -> HPrim.LeftShift
  | RightShiftBinary -> HPrim.RightShift
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

// -----------------------------------------------
// APat
// -----------------------------------------------

let private apFalse pos = ALitPat(litFalse, pos)

let private apTrue pos = ALitPat(litTrue, pos)

// -----------------------------------------------
// AExpr
// -----------------------------------------------

let private axUnit loc = ATupleExpr([], loc)

let private axFalse loc = ALitExpr(litFalse, loc)

let private axTrue loc = ALitExpr(litTrue, loc)

let private axApp3 f x1 x2 x3 loc =
  let app x f = ABinaryExpr(AppBinary, f, x, loc)
  f |> app x1 |> app x2 |> app x3

/// `not x` ==> `x = false`
let private axNot arg loc =
  let falseExpr = axFalse loc
  ABinaryExpr(EqualBinary, arg, falseExpr, loc)

// -----------------------------------------------
// Desugar
// -----------------------------------------------

/// `[x; y; ..]`. Desugar to a chain of (::).
let private desugarListLitPat pats pos =
  assert (pats |> List.isEmpty |> not)

  let rec go pats =
    match pats with
    | [] -> AListPat([], pos)

    | head :: tail ->
        let tail = go tail
        AConsPat(head, tail, pos)

  go pats

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let private desugarListLitExpr items pos =
  assert (items |> List.isEmpty |> not)

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
let private desugarIf cond body altOpt pos =
  let alt =
    match altOpt with
    | None -> axUnit pos
    | Some alt -> alt

  let arms =
    [ AArm(apTrue pos, None, body, pos)
      AArm(apFalse pos, None, alt, pos) ]

  AMatchExpr(cond, arms, pos)

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let private desugarFun pats body pos =
  let name = "fun"
  let pat = AFunDeclPat(name, pats, pos)
  let next = AIdentExpr(name, pos)
  ALetExpr(PrivateVis, pat, body, next, pos)

/// Desugar `-x` to `0 - x`.
let private desugarUniNeg arg pos =
  match arg with
  | ALitExpr (IntLit value, pos) ->
      // FIXME: this trick fails for int min value
      ALitExpr(IntLit(-value), pos)

  | ALitExpr (FloatLit text, pos) -> ALitExpr(FloatLit("-" + text), pos)

  | _ ->
      // FIXME: this fails when arg is not of int
      let zero = ALitExpr(IntLit 0, pos)
      ABinaryExpr(SubBinary, zero, arg, pos)

/// `l <> r` ==> `not (l = r)`
let private desugarBinNe l r pos =
  let eqExpr = ABinaryExpr(EqualBinary, l, r, pos)
  axNot eqExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let private desugarBinLe l r pos =
  let ltExpr = ABinaryExpr(LessBinary, r, l, pos)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let private desugarBinGt l r pos = ABinaryExpr(LessBinary, r, l, pos)

/// `l >= r` ==> `not (l < r)`
let private desugarBinGe l r pos =
  let ltExpr = ABinaryExpr(LessBinary, l, r, pos)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let private desugarBinAnd l r pos = desugarIf l r (Some(axFalse pos)) pos

/// `l || r` ==> `if l then true else r`
let private desugarBinOr l r pos = desugarIf l (axTrue pos) (Some r) pos

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let private desugarBinPipe l r pos = ABinaryExpr(AppBinary, r, l, pos)

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
let private desugarLet vis pat body next pos =
  match pat with
  | AAnnoPat (pat, annoTy, annoLoc) ->
      let body = AAnnoExpr(body, annoTy, annoLoc)
      desugarLet vis pat body next pos

  | AFunDeclPat (name, args, _) -> ALetFun(vis, name, args, body, next, pos)

  | _ -> ALetVal(vis, pat, body, next, pos)

let private tyUnresolved serial argTys = AppTy(UnresolvedTyCtor serial, argTys)

let private athTy (docId: DocId) (ty: ATy, nameCtx: NameCtx): Ty * NameCtx =
  match ty with
  | AMissingTy pos ->
      let loc = toLoc docId pos
      ErrorTy loc, nameCtx

  | AAppTy (name, argTys, _) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd name
      let argTys, nameCtx = (argTys, nameCtx) |> stMap (athTy docId)
      tyUnresolved serial argTys, nameCtx

  | AVarTy (name, _) ->
      let tySerial, nameCtx = nameCtx |> nameCtxAdd ("'" + name)
      tyUnresolved tySerial [], nameCtx

  | ASuffixTy (lTy, suffix, _) ->
      let lTy, nameCtx = (lTy, nameCtx) |> athTy docId
      let serial, nameCtx = nameCtx |> nameCtxAdd suffix
      tyUnresolved serial [ lTy ], nameCtx

  | ATupleTy (itemTys, _) ->
      let itemTys, nameCtx =
        (itemTys, nameCtx) |> stMap (athTy docId)

      tyTuple itemTys, nameCtx

  | AFunTy (sTy, tTy, _) ->
      let sTy, nameCtx = (sTy, nameCtx) |> athTy docId
      let tTy, nameCtx = (tTy, nameCtx) |> athTy docId
      tyFun sTy tTy, nameCtx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private athPat (docId: DocId) (pat: APat, nameCtx: NameCtx): HPat * NameCtx =
  match pat with
  | AMissingPat pos -> failwithf "Missing pattern %s" (posToString pos)

  | ALitPat (lit, pos) ->
      let loc = toLoc docId pos
      HLitPat(lit, loc), nameCtx

  | AIdentPat (name, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd name
      let loc = toLoc docId pos
      HRefPat(VarSerial serial, noTy, loc), nameCtx

  | AListPat ([], pos) ->
      let loc = toLoc docId pos
      HNilPat(noTy, loc), nameCtx

  | AListPat (pats, pos) ->
      let pat = desugarListLitPat pats pos
      (pat, nameCtx) |> athPat docId

  | ANavPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HNavPat(l, r, noTy, loc), nameCtx

  | AAppPat (calleePat, argPats, pos) ->
      let calleePat, nameCtx = (calleePat, nameCtx) |> athPat docId

      let argPats, nameCtx =
        (argPats, nameCtx) |> stMap (athPat docId)

      let loc = toLoc docId pos
      HCallPat(calleePat, argPats, noTy, loc), nameCtx

  | AConsPat (head, tail, pos) ->
      let head, nameCtx = (head, nameCtx) |> athPat docId
      let tail, nameCtx = (tail, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HConsPat(head, tail, noTy, loc), nameCtx

  | ATuplePat (pats, pos) ->
      let pats, nameCtx = (pats, nameCtx) |> stMap (athPat docId)

      let loc = toLoc docId pos
      HTuplePat(pats, noTy, loc), nameCtx

  | AAsPat (pat, name, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd name

      let pat, nameCtx = (pat, nameCtx) |> athPat docId

      let loc = toLoc docId pos
      HAsPat(pat, VarSerial serial, loc), nameCtx

  | AAnnoPat (pat, ty, pos) ->
      let pat, nameCtx = (pat, nameCtx) |> athPat docId
      let ty, nameCtx = (ty, nameCtx) |> athTy docId
      let loc = toLoc docId pos
      HAnnoPat(pat, ty, loc), nameCtx

  | AOrPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> athPat docId
      let r, nameCtx = (r, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HOrPat(l, r, noTy, loc), nameCtx

  | AFunDeclPat (_, _, pos) -> failwithf "Invalid occurrence of fun pattern: %s" (posToString pos)

let private athExpr (docId: DocId) (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  match expr with
  | AMissingExpr pos ->
      // Error is already reported in parsing.
      let loc = toLoc docId pos
      HInfExpr(InfOp.Abort, [], noTy, loc), nameCtx

  | ALitExpr (lit, pos) ->
      let loc = toLoc docId pos
      HLitExpr(lit, loc), nameCtx

  | AIdentExpr (name, pos) ->
      let loc = toLoc docId pos

      // NOTE: Work in a local function to reduce the size of stack frames of `athExpr`.
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd name
        HRefExpr(VarSerial serial, noTy, loc), nameCtx

      doArm ()

  | AListExpr ([], pos) ->
      let loc = toLoc docId pos
      hxNil noTy loc, nameCtx

  | AListExpr (items, pos) ->
      let doArm () =
        let expr = desugarListLitExpr items pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ARecordExpr (baseOpt, fields, pos) ->
      let onField ((name, init, fieldPos), nameCtx) =
        let init, nameCtx = (init, nameCtx) |> athExpr docId
        let fieldLoc = toLoc docId fieldPos

        (name, init, fieldLoc), nameCtx

      let doArm () =
        let baseOpt, nameCtx =
          (baseOpt, nameCtx) |> stOptionMap (athExpr docId)

        let fields, nameCtx = (fields, nameCtx) |> stMap onField
        let loc = toLoc docId pos
        HRecordExpr(baseOpt, fields, noTy, loc), nameCtx

      doArm ()

  | AIfExpr (cond, body, altOpt, pos) ->
      let doArm () =
        let expr = desugarIf cond body altOpt pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | AMatchExpr (cond, arms, pos) ->
      let doArm () =
        // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
        let onArm (AArm (pat, guardOpt, body, pos), nameCtx) =
          let pat, nameCtx = (pat, nameCtx) |> athPat docId

          let loc = toLoc docId pos

          let guard, nameCtx =
            match guardOpt with
            | None -> hxTrue loc, nameCtx
            | Some guard -> (guard, nameCtx) |> athExpr docId

          let body, nameCtx = (body, nameCtx) |> athExpr docId
          (pat, guard, body), nameCtx

        let cond, nameCtx = (cond, nameCtx) |> athExpr docId
        let arms, nameCtx = (arms, nameCtx) |> stMap onArm
        let loc = toLoc docId pos
        HMatchExpr(cond, arms, noTy, loc), nameCtx

      doArm ()

  | AFunExpr (pats, body, pos) ->
      let doArm () =
        let expr = desugarFun pats body pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ANavExpr (l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> athExpr docId
        let loc = toLoc docId pos
        HNavExpr(l, r, noTy, loc), nameCtx

      doArm ()

  | AIndexExpr (l, r, pos) ->
      let doArm () =
        match expr with
        | AIndexExpr (x, ARangeExpr (l, r, _), _) ->
            let x, nameCtx = (x, nameCtx) |> athExpr docId
            let l, nameCtx = (l, nameCtx) |> athExpr docId
            let r, nameCtx = (r, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HInfExpr(InfOp.Slice, [ l; r; x ], noTy, loc), nameCtx

        | _ ->
            let l, nameCtx = (l, nameCtx) |> athExpr docId
            let r, nameCtx = (r, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HInfExpr(InfOp.Index, [ l; r ], noTy, loc), nameCtx

      doArm ()

  | AUnaryExpr (NegUnary, arg, pos) ->
      let doArm () =
        let expr = desugarUniNeg arg pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (NotEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinNe l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (LessEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinLe l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (GreaterBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGt l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (GreaterEqualBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinGe l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (LogAndBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinAnd l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (LogOrBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinOr l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (PipeBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinPipe l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (AppBinary, l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> athExpr docId
        let r, nameCtx = (r, nameCtx) |> athExpr docId
        let loc = toLoc docId pos
        hxApp l r noTy loc, nameCtx

      doArm ()

  | ABinaryExpr (op, l, r, pos) ->
      let doArm () =
        let prim = op |> opToPrim
        let l, nameCtx = (l, nameCtx) |> athExpr docId
        let r, nameCtx = (r, nameCtx) |> athExpr docId
        let loc = toLoc docId pos
        let primExpr = HPrimExpr(prim, noTy, loc)
        hxApp (hxApp primExpr l noTy loc) r noTy loc, nameCtx

      doArm ()

  | ARangeExpr (l, r, pos) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> athExpr docId
        let r, nameCtx = (r, nameCtx) |> athExpr docId
        let loc = toLoc docId pos
        HInfExpr(InfOp.Range, [ l; r ], noTy, loc), nameCtx

      doArm ()

  | ATupleExpr (items, pos) ->
      let doArm () =
        let loc = toLoc docId pos

        let items, nameCtx =
          (items, nameCtx) |> stMap (athExpr docId)

        hxTuple items loc, nameCtx

      doArm ()

  | AAnnoExpr (body, ty, pos) ->
      let doArm () =
        let body, nameCtx = (body, nameCtx) |> athExpr docId
        let ty, nameCtx = (ty, nameCtx) |> athTy docId
        let loc = toLoc docId pos
        hxAnno body ty loc, nameCtx

      doArm ()

  | ASemiExpr (exprs, pos) ->
      let doArm () =
        assert (exprs |> List.isEmpty |> not)

        let exprs, nameCtx =
          (exprs, nameCtx) |> stMap (athExpr docId)

        let loc = toLoc docId pos
        hxSemi exprs loc, nameCtx

      doArm ()

  | ALetExpr (vis, pat, body, next, pos) ->
      let doArm () =
        match desugarLet vis pat body next pos with
        | ALetFun (vis, name, args, body, next, pos) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd name
            let isMainFun = false // Name resolution should correct this.

            let args, nameCtx = (args, nameCtx) |> stMap (athPat docId)

            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let next, nameCtx = (next, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HLetFunExpr(FunSerial serial, vis, isMainFun, args, body, next, noTy, loc), nameCtx

        | ALetVal (vis, pat, body, next, pos) ->
            let pat, nameCtx = (pat, nameCtx) |> athPat docId
            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let next, nameCtx = (next, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HLetValExpr(vis, pat, body, next, noTy, loc), nameCtx

      doArm ()

  | ATySynonymExpr (vis, name, tyArgs, ty, pos) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd name
        let ty, nameCtx = (ty, nameCtx) |> athTy docId

        let tyArgs, nameCtx =
          (tyArgs, nameCtx)
          |> stMap (fun (name, nameCtx) -> nameCtx |> nameCtxAdd ("'" + name))

        let loc = toLoc docId pos
        HTyDeclExpr(serial, vis, tyArgs, TySynonymDecl(ty, loc), loc), nameCtx

      doArm ()

  | AUnionTyExpr (vis, name, variants, pos) ->
      let doArm () =
        let athVariant (AVariant (name, payloadTy, _variantLoc), nameCtx) =
          let serial, nameCtx = nameCtx |> nameCtxAdd name

          let hasPayload, payloadTy, nameCtx =
            match payloadTy with
            | Some ty ->
                let ty, nameCtx = (ty, nameCtx) |> athTy docId
                true, ty, nameCtx
            | None -> false, tyUnit, nameCtx

          (name, VariantSerial serial, hasPayload, payloadTy), nameCtx

        let unionSerial, nameCtx = nameCtx |> nameCtxAdd name
        let variants, nameCtx = (variants, nameCtx) |> stMap athVariant
        let loc = toLoc docId pos
        HTyDeclExpr(unionSerial, vis, [], UnionTyDecl(name, variants, loc), loc), nameCtx

      doArm ()

  | ARecordTyExpr (vis, recordName, fieldDecls, pos) ->
      let athFieldDecl ((name, ty, fieldPos), nameCtx) =
        let ty, nameCtx = (ty, nameCtx) |> athTy docId
        let fieldLoc = toLoc docId fieldPos

        (name, ty, fieldLoc), nameCtx

      let doArm () =
        let tySerial, nameCtx = nameCtx |> nameCtxAdd recordName

        let fields, nameCtx =
          (fieldDecls, nameCtx) |> stMap athFieldDecl

        let loc = toLoc docId pos
        HTyDeclExpr(tySerial, vis, [], RecordTyDecl(recordName, fields, loc), loc), nameCtx

      doArm ()

  | AOpenExpr (path, pos) ->
      let doArm () =
        let loc = toLoc docId pos
        HOpenExpr(path, loc), nameCtx

      doArm ()

  | AAttrExpr (contents, next, pos) ->
      let doArm () =
        // printfn "/* attribute: %s %s */" (pos |> toLoc docId |> locToString) (objToString contents)
        athExpr docId (next, nameCtx)

      doArm ()

let astToHir (docId: DocId) (root: ARoot, nameCtx: NameCtx): HExpr * NameCtx =
  match root with
  | AExprRoot expr -> athExpr docId (expr, nameCtx)

  | AModuleRoot (moduleName, body, pos) ->
      let body, nameCtx = athExpr docId (body, nameCtx)
      let serial, nameCtx = nameCtx |> nameCtxAdd moduleName
      let loc = toLoc docId pos
      let next = hxUnit loc
      HModuleExpr(ModuleTySerial serial, body, next, loc), nameCtx
