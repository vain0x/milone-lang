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

let private greek (Name (ident, pos)) = Name("'" + ident, pos)

let private nameToIdent (Name (ident, _)) : string = ident

let private nameToPos (Name (_, pos)) : Pos = pos

/// Convert pos to loc.
let private toLoc (doc: DocId) (pos: Pos) : Loc =
  let row, column = pos
  Loc(doc, row, column)

let private opToPrim op =
  match op with
  | AddBinary -> HPrim.Add
  | SubBinary -> HPrim.Sub
  | MulBinary -> HPrim.Mul
  | DivBinary -> HPrim.Div
  | ModuloBinary -> HPrim.Modulo
  | BitAndBinary -> HPrim.BitAnd
  | BitOrBinary -> HPrim.BitOr
  | BitXorBinary -> HPrim.BitXor
  | LeftShiftBinary -> HPrim.LeftShift
  | RightShiftBinary -> HPrim.RightShift
  | EqualBinary -> HPrim.Equal
  | LessBinary -> HPrim.Less
  | ConsBinary -> HPrim.Cons

  | NotEqualBinary
  | LessEqualBinary
  | GreaterBinary
  | GreaterEqualBinary
  | LogicalAndBinary
  | LogicalOrBinary
  | AppBinary
  | PipeBinary -> unreachable ()

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

  let pat =
    AFunDeclPat(PrivateVis, Name(name, pos), pats)

  let next = AIdentExpr(Name(name, pos))
  ALetExpr(NotRec, pat, body, next, pos)

/// Desugar `-x`.
///
/// `-(-x)` ==> x.
/// `-n` (n: literal).
let private desugarMinusUnary arg =
  match arg with
  | AUnaryExpr (MinusUnary, arg, _) -> Some arg

  | ALitExpr (IntLit text, pos) -> ALitExpr(IntLit("-" + text), pos) |> Some

  | ALitExpr (FloatLit text, pos) -> ALitExpr(FloatLit("-" + text), pos) |> Some

  | _ -> None

/// `l <> r` ==> `not (l = r)`
let private desugarBinNe l r pos =
  let equalExpr = ABinaryExpr(EqualBinary, l, r, pos)
  axNot equalExpr pos

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
/// Ascription move just for simplification:
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
let private desugarLet isRec pat body next pos =
  match pat with
  | AAscribePat (pat, ascriptionTy, ascriptionLoc) ->
      let body =
        AAscribeExpr(body, ascriptionTy, ascriptionLoc)

      desugarLet isRec pat body next pos

  | AFunDeclPat (vis, name, args) -> ALetFun(isRec, vis, name, args, body, next, pos)

  | _ -> ALetVal(isRec, pat, body, next, pos)

let private desugarLetDecl isRec pat body pos =
  match pat with
  | AAscribePat (pat, ascriptionTy, ascriptionLoc) ->
      let body =
        AAscribeExpr(body, ascriptionTy, ascriptionLoc)

      desugarLetDecl isRec pat body pos

  | AFunDeclPat (vis, name, args) -> ALetFunDecl(isRec, vis, name, args, body, pos)

  | _ -> ALetValDecl(isRec, pat, body, pos)

let private tyUnresolved serial argTys = Ty(UnresolvedTk serial, argTys)

let private athTy (docId: DocId) (ty: ATy, nameCtx: NameCtx) : Ty * NameCtx =
  match ty with
  | AMissingTy pos ->
      let loc = toLoc docId pos
      tyError loc, nameCtx

  | AAppTy (quals, name, argTys, _) ->
      let quals, nameCtx =
        (quals, nameCtx)
        |> stMap (fun (name, ctx) -> ctx |> nameCtxAdd name)

      let serial, nameCtx = nameCtx |> nameCtxAdd name

      let argTys, nameCtx =
        (argTys, nameCtx) |> stMap (athTy docId)

      tyUnresolved (quals, serial) argTys, nameCtx

  | AVarTy name ->
      let tySerial, nameCtx = nameCtx |> nameCtxAdd (greek name)
      let loc = toLoc docId (nameToPos name)
      Ty(UnresolvedVarTk(tySerial, loc), []), nameCtx

  | ASuffixTy (lTy, suffix) ->
      let lTy, nameCtx = (lTy, nameCtx) |> athTy docId
      let serial, nameCtx = nameCtx |> nameCtxAdd suffix
      tyUnresolved ([], serial) [ lTy ], nameCtx

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

let private athPat (docId: DocId) (pat: APat, nameCtx: NameCtx) : HPat * NameCtx =
  match pat with
  | AMissingPat pos ->
      let loc = toLoc docId pos
      hpAbort noTy loc, nameCtx

  | ALitPat (lit, pos) ->
      let loc = toLoc docId pos
      HLitPat(lit, loc), nameCtx

  | AIdentPat (vis, name) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd name
      let loc = toLoc docId (nameToPos name)
      HVarPat(vis, VarSerial serial, noTy, loc), nameCtx

  | AListPat ([], pos) ->
      let loc = toLoc docId pos
      HNodePat(HNilPN, [], noTy, loc), nameCtx

  | AListPat (pats, pos) ->
      let pat = desugarListLitPat pats pos
      (pat, nameCtx) |> athPat docId

  | ANavPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HNodePat(HNavPN(nameToIdent r), [ l ], noTy, loc), nameCtx

  | AAppPat (calleePat, argPat, pos) ->
      let calleePat, nameCtx = (calleePat, nameCtx) |> athPat docId
      let argPat, nameCtx = (argPat, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HNodePat(HAppPN, [ calleePat; argPat ], noTy, loc), nameCtx

  | AConsPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> athPat docId
      let r, nameCtx = (r, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HNodePat(HConsPN, [ l; r ], noTy, loc), nameCtx

  | ATuplePat (pats, pos) ->
      let pats, nameCtx = (pats, nameCtx) |> stMap (athPat docId)
      let loc = toLoc docId pos
      HNodePat(HTuplePN, pats, noTy, loc), nameCtx

  | AAsPat (pat, name, pos) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd name
      let pat, nameCtx = (pat, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HAsPat(pat, VarSerial serial, loc), nameCtx

  | AAscribePat (bodyPat, ty, pos) ->
      let bodyPat, nameCtx = (bodyPat, nameCtx) |> athPat docId
      let ty, nameCtx = (ty, nameCtx) |> athTy docId
      let loc = toLoc docId pos
      HNodePat(HAscribePN, [ bodyPat ], ty, loc), nameCtx

  | AOrPat (l, r, pos) ->
      let l, nameCtx = (l, nameCtx) |> athPat docId
      let r, nameCtx = (r, nameCtx) |> athPat docId
      let loc = toLoc docId pos
      HOrPat(l, r, loc), nameCtx

  | AFunDeclPat _ -> unreachable () // Invalid occurrence of fun pattern.

let private athExpr (docId: DocId) (expr: AExpr, nameCtx: NameCtx) : HExpr * NameCtx =
  match expr with
  | AMissingExpr pos ->
      // Error is already reported in parsing.
      let loc = toLoc docId pos
      HNodeExpr(HAbortEN, [], noTy, loc), nameCtx

  | ALitExpr (lit, pos) ->
      let loc = toLoc docId pos
      HLitExpr(lit, loc), nameCtx

  | AIdentExpr name ->
      let loc = toLoc docId (nameToPos name)

      // NOTE: Work in a local function to reduce the size of stack frames of `athExpr`.
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd name
        HVarExpr(VarSerial serial, noTy, loc), nameCtx

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

        (nameToIdent name, init, fieldLoc), nameCtx

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
        HNavExpr(l, nameToIdent r, noTy, loc), nameCtx

      doArm ()

  | AIndexExpr (l, r, pos) ->
      let doArm () =
        match expr with
        | AIndexExpr (x, ARangeExpr (l, r, _), _) ->
            let x, nameCtx = (x, nameCtx) |> athExpr docId
            let l, nameCtx = (l, nameCtx) |> athExpr docId
            let r, nameCtx = (r, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HNodeExpr(HSliceEN, [ l; r; x ], noTy, loc), nameCtx

        | _ ->
            let l, nameCtx = (l, nameCtx) |> athExpr docId
            let r, nameCtx = (r, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HNodeExpr(HIndexEN, [ l; r ], noTy, loc), nameCtx

      doArm ()

  | AUnaryExpr (MinusUnary, arg, pos) ->
      let doArm () =
        match desugarMinusUnary arg with
        | Some arg -> (arg, nameCtx) |> athExpr docId
        | None ->
            let arg, nameCtx = (arg, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HNodeExpr(HMinusEN, [ arg ], noTy, loc), nameCtx

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

  | ABinaryExpr (LogicalAndBinary, l, r, pos) ->
      let doArm () =
        let expr = desugarBinAnd l r pos
        (expr, nameCtx) |> athExpr docId

      doArm ()

  | ABinaryExpr (LogicalOrBinary, l, r, pos) ->
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
        HNodeExpr(HRangeEN, [ l; r ], noTy, loc), nameCtx

      doArm ()

  | ATupleExpr (items, pos) ->
      let doArm () =
        let loc = toLoc docId pos

        let items, nameCtx =
          (items, nameCtx) |> stMap (athExpr docId)

        hxTuple items loc, nameCtx

      doArm ()

  | AAscribeExpr (body, ty, pos) ->
      let doArm () =
        let body, nameCtx = (body, nameCtx) |> athExpr docId
        let ty, nameCtx = (ty, nameCtx) |> athTy docId
        let loc = toLoc docId pos
        hxAscribe body ty loc, nameCtx

      doArm ()

  | ASemiExpr (stmts, last, pos) ->
      let doArm () =
        let stmts, nameCtx =
          (stmts, nameCtx) |> stMap (athExpr docId)

        let last, nameCtx = (last, nameCtx) |> athExpr docId
        let loc = toLoc docId pos
        hxSemi (List.append stmts [ last ]) loc, nameCtx

      doArm ()

  | ALetExpr (isRec, pat, body, next, pos) ->
      let doArm () =
        match desugarLet isRec pat body next pos with
        | ALetFun (isRec, vis, name, args, body, next, pos) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd name
            let args, nameCtx = (args, nameCtx) |> stMap (athPat docId)
            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let next, nameCtx = (next, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            HLetFunExpr(FunSerial serial, isRec, vis, args, body, next, noTy, loc), nameCtx

        | ALetVal (_isRec, pat, body, next, pos) ->
            let pat, nameCtx = (pat, nameCtx) |> athPat docId
            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let next, nameCtx = (next, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            // FIXME: let rec for let-val is error. No way to report it for now...
            HLetValExpr(pat, body, next, noTy, loc), nameCtx

      doArm ()

let private prepend stmt stmts = stmt :: stmts

let private athDecl docId (decl, nameCtx) =
  match decl with
  | AExprDecl expr ->
      let expr, nameCtx = (expr, nameCtx) |> athExpr docId
      prepend expr, nameCtx

  | ALetDecl (isRec, pat, body, pos) ->
      let doArm () =
        match desugarLetDecl isRec pat body pos with
        | ALetFunDecl (isRec, vis, name, args, body, pos) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd name
            let args, nameCtx = (args, nameCtx) |> stMap (athPat docId)
            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            (fun next -> [ HLetFunExpr(FunSerial serial, isRec, vis, args, body, hxSemi next loc, noTy, loc) ]), nameCtx

        | ALetValDecl (_isRec, pat, body, pos) ->
            let pat, nameCtx = (pat, nameCtx) |> athPat docId
            let body, nameCtx = (body, nameCtx) |> athExpr docId
            let loc = toLoc docId pos
            // FIXME: let rec for let-val is error, no way to report.
            (fun next -> [ HLetValExpr(pat, body, hxSemi next loc, noTy, loc) ]), nameCtx

      doArm ()

  | ATySynonymDecl (vis, name, tyArgs, ty, pos) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd name
        let ty, nameCtx = (ty, nameCtx) |> athTy docId

        let tyArgs, nameCtx =
          (tyArgs, nameCtx)
          |> stMap (fun (name, nameCtx) -> nameCtx |> nameCtxAdd (greek name))

        let loc = toLoc docId pos
        prepend (HTyDeclExpr(serial, vis, tyArgs, TySynonymDecl(ty, loc), loc)), nameCtx

      doArm ()

  | AUnionTyDecl (vis, name, variants, pos) ->
      let doArm () =
        let athVariant (AVariant (name, payloadTy, _variantLoc), nameCtx) =
          let serial, nameCtx = nameCtx |> nameCtxAdd name

          let hasPayload, payloadTy, nameCtx =
            match payloadTy with
            | Some ty ->
                let ty, nameCtx = (ty, nameCtx) |> athTy docId
                true, ty, nameCtx
            | None -> false, tyUnit, nameCtx

          (nameToIdent name, VariantSerial serial, hasPayload, payloadTy), nameCtx

        let unionSerial, nameCtx = nameCtx |> nameCtxAdd name
        let variants, nameCtx = (variants, nameCtx) |> stMap athVariant
        let loc = toLoc docId pos
        prepend (HTyDeclExpr(unionSerial, vis, [], UnionTyDecl(nameToIdent name, variants, loc), loc)), nameCtx

      doArm ()

  | ARecordTyDecl (vis, recordName, fieldDecls, pos) ->
      let athFieldDecl ((name, ty, fieldPos), nameCtx) =
        let ty, nameCtx = (ty, nameCtx) |> athTy docId
        let fieldLoc = toLoc docId fieldPos

        (nameToIdent name, ty, fieldLoc), nameCtx

      let doArm () =
        let tySerial, nameCtx = nameCtx |> nameCtxAdd recordName

        let fields, nameCtx =
          (fieldDecls, nameCtx) |> stMap athFieldDecl

        let loc = toLoc docId pos
        prepend (HTyDeclExpr(tySerial, vis, [], RecordTyDecl(nameToIdent recordName, fields, loc), loc)), nameCtx

      doArm ()

  | AOpenDecl (path, pos) ->
      let doArm () =
        let loc = toLoc docId pos
        prepend (HOpenExpr(List.map nameToIdent path, loc)), nameCtx

      doArm ()

  | AModuleSynonymDecl (ident, path, pos) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        let loc = toLoc docId pos
        prepend (HModuleSynonymExpr(ModuleSynonymSerial serial, List.map nameToIdent path, loc)), nameCtx

      doArm ()

  | AModuleDecl (_isRec, _vis, name, decls, pos) ->
      // FIXME: use rec, vis
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd name
        let decls, nameCtx = (decls, nameCtx) |> athDecls docId
        let loc = toLoc docId pos
        prepend (HModuleExpr(ModuleTySerial serial, decls, loc)), nameCtx

      doArm ()

  | AAttrDecl (contents, next, pos) ->
      let doArm () =
        // printfn "/* attribute: %s %s */" (pos |> toLoc docId |> locToString) (objToString contents)
        athDecl docId (next, nameCtx)

      doArm ()

let private athDecls docId (decls, nameCtx) =
  let axUnit pos = ATupleExpr([], pos)

  let rec go (decls, nameCtx) =
    match decls with
    | [] -> [], nameCtx

    | decl :: decls ->
        let hole, nameCtx = athDecl docId (decl, nameCtx)
        let next, nameCtx = go (decls, nameCtx)
        hole next, nameCtx

  go (decls, nameCtx)

let astToHir (projectName: string) (docId: DocId) (root: ARoot, nameCtx: NameCtx) : HExpr list * NameCtx =
  let onModuleRoot moduleName body pos =
    let body, nameCtx = (body, nameCtx) |> athDecls docId
    let serial, nameCtx = nameCtx |> nameCtxAdd moduleName
    let loc = toLoc docId pos
    [ HModuleExpr(ModuleTySerial serial, body, loc) ], nameCtx

  let wrapWithProjectModule (body, nameCtx) =
    let serial, nameCtx =
      nameCtx |> nameCtxAdd (Name(projectName, (0, 0)))

    [ HModuleExpr(ModuleTySerial serial, body, noLoc) ], nameCtx

  match root with
  | AExprRoot exprs -> (exprs, nameCtx) |> athDecls docId

  | AModuleRoot (moduleName, body, pos) ->
      if nameToIdent moduleName = "MiloneOnly" then
        onModuleRoot moduleName body pos
      else
        onModuleRoot moduleName body pos
        |> wrapWithProjectModule
