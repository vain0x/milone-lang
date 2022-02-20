/// # TirGen
///
/// Conversion from AST to TIR.
///
/// ## Motivation
///
/// 1. AST should be decoupled with TIR.
///
/// AST is for syntactical analysis/transformations
/// but TIR is for semantic analysis/transformations.
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
module rec MiloneSyntax.TirGen

open MiloneShared.SharedTypes
open MiloneShared.Util
open Std.StdError
open MiloneSyntax.Tir
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.TirTypes

module S = Std.StdString

let private greek (Name (ident, pos)) = Name("'" + ident, pos)

let private nameToIdent (Name (ident, _)) : string = ident

let private nameToPos (Name (_, pos)) : Pos = pos

/// Convert pos to loc.
let private toLoc (doc: DocId) (pos: Pos) : Loc =
  let row, column = pos
  Loc(doc, row, column)

// -----------------------------------------------
// NameCtx
// -----------------------------------------------

// NameCtx is not suitable for parallel computation
// so here we use different type.

[<Struct; NoEquality; NoComparison>]
type TgNameCtx = TgNameCtx of lastSerial: Serial * identAcc: Ident list

type private NameCtx = TgNameCtx

let private nameCtxAdd (name: Name) (ctx: TgNameCtx) : Serial * NameCtx =
  let (TgNameCtx (serial, idents)) = ctx
  let (Name (ident, _)) = name
  serial + 1, TgNameCtx(serial + 1, ident :: idents)

let nameCtxFold folder state (nameCtx: TgNameCtx) =
  let (TgNameCtx (lastSerial, identAcc)) = nameCtx

  identAcc
  |> List.fold (fun (serial, state) ident -> serial - 1, folder state serial ident) (lastSerial, state)

let private addPath (path: Name list, ctx: TgNameCtx) : Serial list * NameCtx =
  path
  |> List.mapFold (fun ctx name -> nameCtxAdd name ctx) ctx

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
// TExpr
// -----------------------------------------------

let private txTrue loc = TLitExpr(BoolLit true, loc)

let private txNil itemTy loc =
  TPrimExpr(TPrim.Nil, tyList itemTy, loc)

let private txApp f x loc = TNodeExpr(TAppEN, [ f; x ], noTy, loc)

let private txAscribe expr ty loc =
  TNodeExpr(TAscribeEN, [ expr ], ty, loc)

// -----------------------------------------------
// TPrim
// -----------------------------------------------

let private opToPrim op =
  match op with
  | AddBinary -> TPrim.Add
  | SubBinary -> TPrim.Sub
  | MulBinary -> TPrim.Mul
  | DivBinary -> TPrim.Div
  | ModuloBinary -> TPrim.Modulo
  | BitAndBinary -> TPrim.BitAnd
  | BitOrBinary -> TPrim.BitOr
  | BitXorBinary -> TPrim.BitXor
  | LeftShiftBinary -> TPrim.LeftShift
  | RightShiftBinary -> TPrim.RightShift
  | EqualBinary -> TPrim.Equal
  | LessBinary -> TPrim.Less
  | ConsBinary -> TPrim.Cons

  | NotEqualBinary
  | LessEqualBinary
  | GreaterBinary
  | GreaterEqualBinary
  | LogicalAndBinary
  | LogicalOrBinary
  | AppBinary
  | PipeBinary -> unreachable ()

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

  | ALitExpr (IntLitWithFlavor (text, flavor), pos) ->
    ALitExpr(IntLitWithFlavor("-" + text, flavor), pos)
    |> Some

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

// -----------------------------------------------
// Control
// -----------------------------------------------

let private tgTy (docId: DocId) (ty: ATy, ctx: NameCtx) : Ty * NameCtx =
  let onTy x = tgTy docId x

  match ty with
  | AMissingTy pos ->
    let loc = toLoc docId pos
    tyError loc, ctx

  | AAppTy ([], Name ("_", pos), [], _) ->
    let loc = toLoc docId pos
    Ty(InferTk loc, []), ctx

  | AAppTy (quals, name, argTys, pos) ->
    let quals, ctx = (quals, ctx) |> addPath
    let serial, ctx = ctx |> nameCtxAdd name
    let argTys, ctx = (argTys, ctx) |> stMap onTy
    let loc = toLoc docId pos
    tyUnresolved (quals, serial, loc) argTys, ctx

  | AVarTy name ->
    let tySerial, ctx = ctx |> nameCtxAdd (greek name)
    let loc = toLoc docId (nameToPos name)
    Ty(UnresolvedVarTk(tySerial, loc), []), ctx

  | ASuffixTy (lTy, suffix) ->
    let lTy, ctx = (lTy, ctx) |> onTy
    let serial, ctx = ctx |> nameCtxAdd suffix
    let loc = toLoc docId (nameToPos suffix)
    tyUnresolved ([], serial, loc) [ lTy ], ctx

  | ATupleTy (itemTys, _) ->
    let itemTys, ctx = (itemTys, ctx) |> stMap onTy
    tyTuple itemTys, ctx

  | AFunTy (sTy, tTy, _) ->
    let sTy, ctx = (sTy, ctx) |> onTy
    let tTy, ctx = (tTy, ctx) |> onTy
    tyFun sTy tTy, ctx

let private tgPat (docId: DocId) (pat: APat, ctx: NameCtx) : TPat * NameCtx =
  let onTy x = tgTy docId x
  let onPat x = tgPat docId x

  match pat with
  | AMissingPat pos ->
    let loc = toLoc docId pos
    tpAbort noTy loc, ctx

  | ALitPat (lit, pos) ->
    let loc = toLoc docId pos
    TLitPat(lit, loc), ctx

  | AIdentPat (_, Name ("_", pos)) ->
    let loc = toLoc docId pos
    TDiscardPat(noTy, loc), ctx

  | AIdentPat (vis, name) ->
    let serial, ctx = ctx |> nameCtxAdd name
    let loc = toLoc docId (nameToPos name)
    TVarPat(vis, VarSerial serial, noTy, loc), ctx

  | AListPat ([], pos) ->
    let loc = toLoc docId pos
    TNodePat(TNilPN, [], noTy, loc), ctx

  | AListPat (pats, pos) ->
    let pat = desugarListLitPat pats pos
    (pat, ctx) |> onPat

  | ANavPat (l, r, pos) ->
    let l, ctx = (l, ctx) |> onPat
    let loc = toLoc docId pos
    TNodePat(TNavPN(nameToIdent r), [ l ], noTy, loc), ctx

  | AAppPat (calleePat, argPat, pos) ->
    let calleePat, ctx = (calleePat, ctx) |> onPat
    let argPat, ctx = (argPat, ctx) |> onPat
    let loc = toLoc docId pos
    TNodePat(TAppPN, [ calleePat; argPat ], noTy, loc), ctx

  | AConsPat (l, r, pos) ->
    let l, ctx = (l, ctx) |> onPat
    let r, ctx = (r, ctx) |> onPat
    let loc = toLoc docId pos
    TNodePat(TConsPN, [ l; r ], noTy, loc), ctx

  | ATuplePat (pats, pos) ->
    let pats, ctx = (pats, ctx) |> stMap onPat
    let loc = toLoc docId pos
    TNodePat(TTuplePN, pats, noTy, loc), ctx

  | AAsPat (pat, name, pos) ->
    let serial, ctx = ctx |> nameCtxAdd name
    let pat, ctx = (pat, ctx) |> onPat
    let loc = toLoc docId pos
    TAsPat(pat, VarSerial serial, loc), ctx

  | AAscribePat (bodyPat, ty, pos) ->
    let bodyPat, ctx = (bodyPat, ctx) |> onPat
    let ty, ctx = (ty, ctx) |> onTy
    let loc = toLoc docId pos
    TNodePat(TAscribePN, [ bodyPat ], ty, loc), ctx

  | AOrPat (l, r, pos) ->
    let l, ctx = (l, ctx) |> onPat
    let r, ctx = (r, ctx) |> onPat
    let loc = toLoc docId pos
    TOrPat(l, r, loc), ctx

  | AFunDeclPat _ -> unreachable () // Invalid occurrence of fun pattern.

let private tgExpr (docId: DocId) (expr: AExpr, ctx: NameCtx) : TExpr * NameCtx =
  let onTy x = tgTy docId x
  let onPat x = tgPat docId x
  let onExpr x = tgExpr docId x

  let toName (Name (ident, pos)) : TName = ident, toLoc docId pos

  match expr with
  | AMissingExpr pos ->
    // Error is already reported in parsing.
    let loc = toLoc docId pos
    TNodeExpr(TAbortEN, [], noTy, loc), ctx

  | ALitExpr (lit, pos) ->
    let loc = toLoc docId pos
    TLitExpr(lit, loc), ctx

  | AIdentExpr name ->
    let loc = toLoc docId (nameToPos name)
    let serial, ctx = ctx |> nameCtxAdd name
    TVarExpr(VarSerial serial, noTy, loc), ctx

  | AListExpr ([], pos) ->
    let loc = toLoc docId pos
    txNil noTy loc, ctx

  | AListExpr (items, pos) ->
    let expr = desugarListLitExpr items pos
    (expr, ctx) |> onExpr

  | ARecordExpr (baseOpt, fields, pos) ->
    let onField ((name, init, fieldPos), ctx) =
      let init, ctx = (init, ctx) |> onExpr
      let fieldLoc = toLoc docId fieldPos
      (nameToIdent name, init, fieldLoc), ctx

    let baseOpt, ctx = (baseOpt, ctx) |> stOptionMap onExpr
    let fields, ctx = (fields, ctx) |> stMap onField
    let loc = toLoc docId pos
    TRecordExpr(baseOpt, fields, noTy, loc), ctx

  | AIfExpr (cond, body, altOpt, pos) ->
    let expr = desugarIf cond body altOpt pos
    (expr, ctx) |> onExpr

  | AMatchExpr (cond, arms, pos) ->
    // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
    let onArm (AArm (pat, guardOpt, body, pos), ctx) =
      let pat, ctx = (pat, ctx) |> onPat
      let loc = toLoc docId pos

      let guard, ctx =
        match guardOpt with
        | None -> txTrue loc, ctx
        | Some guard -> (guard, ctx) |> onExpr

      let body, ctx = (body, ctx) |> onExpr
      (pat, guard, body), ctx

    let cond, ctx = (cond, ctx) |> onExpr
    let arms, ctx = (arms, ctx) |> stMap onArm
    let loc = toLoc docId pos
    TMatchExpr(cond, arms, noTy, loc), ctx

  | AFunExpr (pats, body, pos) ->
    let expr = desugarFun pats body pos
    (expr, ctx) |> onExpr

  | ANavExpr (l, r, pos) ->
    let l, ctx = (l, ctx) |> onExpr
    let loc = toLoc docId pos
    TNavExpr(l, toName r, noTy, loc), ctx

  | AIndexExpr (l, r, pos) ->
    match expr with
    | AIndexExpr (x, ARangeExpr (l, r, _), _) ->
      let x, ctx = (x, ctx) |> onExpr
      let l, ctx = (l, ctx) |> onExpr
      let r, ctx = (r, ctx) |> onExpr
      let loc = toLoc docId pos
      TNodeExpr(TSliceEN, [ l; r; x ], noTy, loc), ctx

    | _ ->
      let l, ctx = (l, ctx) |> onExpr
      let r, ctx = (r, ctx) |> onExpr
      let loc = toLoc docId pos
      TNodeExpr(TIndexEN, [ l; r ], noTy, loc), ctx

  | AUnaryExpr (MinusUnary, arg, pos) ->
    match desugarMinusUnary arg with
    | Some arg -> (arg, ctx) |> onExpr
    | None ->
      let arg, ctx = (arg, ctx) |> onExpr
      let loc = toLoc docId pos
      TNodeExpr(TMinusEN, [ arg ], noTy, loc), ctx

  | ABinaryExpr (NotEqualBinary, l, r, pos) ->
    let expr = desugarBinNe l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (LessEqualBinary, l, r, pos) ->
    let expr = desugarBinLe l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (GreaterBinary, l, r, pos) ->
    let expr = desugarBinGt l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (GreaterEqualBinary, l, r, pos) ->
    let expr = desugarBinGe l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (LogicalAndBinary, l, r, pos) ->
    let expr = desugarBinAnd l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (LogicalOrBinary, l, r, pos) ->
    let expr = desugarBinOr l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (PipeBinary, l, r, pos) ->
    let expr = desugarBinPipe l r pos
    (expr, ctx) |> onExpr

  | ABinaryExpr (AppBinary, l, r, pos) ->
    let l, ctx = (l, ctx) |> onExpr
    let r, ctx = (r, ctx) |> onExpr
    let loc = toLoc docId pos
    txApp l r loc, ctx

  | ABinaryExpr (op, l, r, pos) ->
    let prim = op |> opToPrim
    let l, ctx = (l, ctx) |> onExpr
    let r, ctx = (r, ctx) |> onExpr
    let loc = toLoc docId pos
    let primExpr = TPrimExpr(prim, noTy, loc)
    txApp (txApp primExpr l loc) r loc, ctx

  | ATupleExpr (items, pos) ->
    let loc = toLoc docId pos
    let items, ctx = (items, ctx) |> stMap onExpr
    txTuple items loc, ctx

  // (_: 'T)
  | AAscribeExpr (AIdentExpr (Name ("_", _)), ty, pos) ->
    let ty, ctx = (ty, ctx) |> onTy
    let loc = toLoc docId pos
    TNodeExpr(TTyPlaceholderEN, [], ty, loc), ctx

  | AAscribeExpr (body, ty, pos) ->
    let body, ctx = (body, ctx) |> onExpr
    let ty, ctx = (ty, ctx) |> onTy
    let loc = toLoc docId pos
    txAscribe body ty loc, ctx

  | ASemiExpr (stmts, last, _) ->
    let stmts, ctx =
      (stmts, ctx)
      |> stMap (fun (expr, ctx) ->
        let expr, ctx = onExpr (expr, ctx)
        TExprStmt expr, ctx)

    let last, ctx = (last, ctx) |> onExpr
    TBlockExpr(stmts, last), ctx

  | ALetExpr (isRec, pat, body, next, pos) ->
    match desugarLet isRec pat body next pos with
    | ALetFun (isRec, vis, name, args, body, next, pos) ->
      let serial, ctx = ctx |> nameCtxAdd name
      let args, ctx = (args, ctx) |> stMap onPat
      let body, ctx = (body, ctx) |> onExpr
      let next, ctx = (next, ctx) |> onExpr

      let stmt =
        let loc = toLoc docId pos
        TLetFunStmt(FunSerial serial, isRec, vis, args, body, loc)

      txLetIn stmt next, ctx

    | ALetVal (_, pat, body, next, pos) ->
      let pat, ctx = (pat, ctx) |> onPat
      let body, ctx = (body, ctx) |> onExpr
      let next, ctx = (next, ctx) |> onExpr

      let stmt =
        let loc = toLoc docId pos
        // let rec for let-val should be error.
        TLetValStmt(pat, body, loc)

      txLetIn stmt next, ctx

  | ARangeExpr _ -> unreachable () // Generated only inside of AIndexExpr.

let private tgTyArgs (tyArgs, ctx) =
  (tyArgs, ctx)
  |> stMap (fun (name, ctx) -> ctx |> nameCtxAdd (greek name))

let private tgDecl docId attrs (decl, ctx) : TStmt * NameCtx =
  let onTy x = tgTy docId x
  let onPat x = tgPat docId x
  let onExpr x = tgExpr docId x

  match decl with
  | AExprDecl expr ->
    let expr, ctx = (expr, ctx) |> onExpr
    TExprStmt expr, ctx

  | ALetDecl (isRec, pat, body, pos) ->
    match desugarLetDecl isRec pat body pos with
    | ALetFunDecl (isRec, vis, name, args, body, pos) ->
      let serial, ctx = ctx |> nameCtxAdd name
      let args, ctx = (args, ctx) |> stMap onPat
      let body, ctx = (body, ctx) |> onExpr
      let loc = toLoc docId pos

      TLetFunStmt(FunSerial serial, isRec, vis, args, body, loc), ctx

    | ALetValDecl (_, pat, body, pos) ->
      let pat, ctx = (pat, ctx) |> onPat
      let body, ctx = (body, ctx) |> onExpr
      let loc = toLoc docId pos
      // let rec for let-val should be error.
      TLetValStmt(pat, body, loc), ctx

  | ATySynonymDecl (vis, name, tyArgs, ty, pos) ->
    let serial, ctx = ctx |> nameCtxAdd name
    let ty, ctx = (ty, ctx) |> onTy
    let tyArgs, ctx = (tyArgs, ctx) |> tgTyArgs

    let loc = toLoc docId pos
    TTyDeclStmt(serial, vis, tyArgs, TySynonymDecl(ty, loc), loc), ctx

  | AUnionTyDecl (vis, name, tyArgs, variants, pos) ->
    let tgVariant (AVariant (name, payloadTy, pos), ctx) =
      let serial, ctx = ctx |> nameCtxAdd name
      let loc = toLoc docId pos

      let hasPayload, payloadTy, ctx =
        match payloadTy with
        | Some ty ->
          let ty, ctx = (ty, ctx) |> onTy
          true, ty, ctx
        | None -> false, tyUnit, ctx

      (nameToIdent name, VariantSerial serial, hasPayload, payloadTy, loc), ctx

    let unionSerial, ctx = ctx |> nameCtxAdd name
    let tyArgs, ctx = (tyArgs, ctx) |> tgTyArgs
    let variants, ctx = (variants, ctx) |> stMap tgVariant
    let loc = toLoc docId pos

    TTyDeclStmt(unionSerial, vis, tyArgs, UnionTyDecl(nameToIdent name, variants, loc), loc), ctx

  | ARecordTyDecl (vis, recordName, tyArgs, fieldDecls, pos) ->
    let repr =
      attrs
      |> List.exists (fun a ->
        match a with
        | ABinaryExpr (AppBinary, AIdentExpr (Name ("Repr", _)), ALitExpr (StrLit "C", _), _) -> true
        | _ -> false)
      |> IsCRepr

    let tgFieldDecl ((name, ty, fieldPos), ctx) =
      let ty, ctx = (ty, ctx) |> onTy
      let fieldLoc = toLoc docId fieldPos
      (nameToIdent name, ty, fieldLoc), ctx

    let tySerial, ctx = ctx |> nameCtxAdd recordName
    let tyArgs, ctx = (tyArgs, ctx) |> tgTyArgs
    let fields, ctx = (fieldDecls, ctx) |> stMap tgFieldDecl
    let loc = toLoc docId pos
    TTyDeclStmt(tySerial, vis, tyArgs, RecordTyDecl(nameToIdent recordName, fields, repr, loc), loc), ctx

  | AOpenDecl (path, pos) ->
    let loc = toLoc docId pos
    TOpenStmt(List.map nameToIdent path, loc), ctx

  | AModuleSynonymDecl (ident, path, pos) ->
    let serial, ctx = ctx |> nameCtxAdd ident
    let loc = toLoc docId pos

    TModuleSynonymStmt(ModuleSynonymSerial serial, List.map nameToIdent path, loc), ctx

  | AModuleDecl (_, _, name, decls, pos) ->
    // should use rec, vis
    let serial, ctx = ctx |> nameCtxAdd name
    let body, ctx = (decls, ctx) |> tgDecls docId
    let loc = toLoc docId pos

    TModuleStmt(ModuleTySerial serial, body, loc), ctx

  | AAttrDecl (attr, next, _pos) ->
    let rec prepend attr acc =
      match attr with
      | ASemiExpr (stmts, last, _) -> List.append stmts (last :: acc)
      | _ -> attr :: acc

    // printfn "/* attribute: %s %s */" (pos |> toLoc docId |> Loc.toString) (objToString contents)
    tgDecl docId (prepend attr attrs) (next, ctx)

let private tgDecls docId (decls, ctx) : TStmt list * NameCtx = (decls, ctx) |> stMap (tgDecl docId [])

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genTir
  (projectName: ProjectName)
  (moduleName: ModuleName)
  (docId: DocId)
  (root: ARoot, ctx: NameCtx)
  : TStmt list * NameCtx =
  let zeroPos = 0, 0

  let onModuleRoot moduleName body pos =
    let body, ctx = (body, ctx) |> tgDecls docId
    let serial, ctx = ctx |> nameCtxAdd moduleName
    let loc = toLoc docId pos
    [ TModuleStmt(ModuleTySerial serial, body, loc) ], ctx

  let wrapWithProjectModule (body, ctx) =
    let serial, ctx =
      ctx |> nameCtxAdd (Name(projectName, zeroPos))

    [ TModuleStmt(ModuleTySerial serial, body, noLoc) ], ctx

  let (ARoot (headOpt, decls)) = root

  let moduleName, pos =
    match headOpt with
    | Some ([ _; moduleName ], pos) -> moduleName, pos
    | _ -> Name(moduleName, zeroPos), zeroPos

  onModuleRoot moduleName decls pos
  |> wrapWithProjectModule

// ===============================================
// Experimental

// Count number of symbols.

let private plus (x: int) (y: int) : int = x + y

let private sumBy count xs =
  xs |> List.fold (fun (n: int) x -> n + count x) 0

let private ocTy (ty: ATy) : int =
  match ty with
  | AMissingTy _ -> 0
  | AVarTy _ -> 1

  | AAppTy ([], Name ("_", _), [], _) -> 0
  | AAppTy (quals, _name, argTys, _) -> List.length quals + 1 + ocTys argTys
  | ASuffixTy (lTy, _suffix) -> ocTy lTy + 1
  | ATupleTy (itemTys, _) -> ocTys itemTys
  | AFunTy (sTy, tTy, _) -> ocTy sTy + ocTy tTy

let private ocTyOpt tyOpt =
  match tyOpt with
  | Some ty -> ocTy ty
  | None -> 0

let private ocTys = sumBy ocTy

let private ocPat (pat: APat) : int =
  match pat with
  | AMissingPat _
  | ALitPat _ -> 0

  | AIdentPat (_, Name ("_", _)) -> 0
  | AIdentPat _ -> 1
  | AListPat (pats, _) -> ocPats pats
  | ANavPat (l, _, _) -> ocPat l
  | AAppPat (calleePat, argPat, _) -> ocPat calleePat + ocPat argPat
  | AConsPat (l, r, _) -> ocPat l + ocPat r
  | ATuplePat (pats, _) -> ocPats pats
  | AAsPat (bodyPat, _name, _) -> ocPat bodyPat + 1
  | AAscribePat (bodyPat, ty, _) -> ocPat bodyPat + ocTy ty
  | AOrPat (l, r, _) -> ocPat l + ocPat r
  | AFunDeclPat (_, _name, argPats) -> 1 + ocPats argPats

let private ocPats = sumBy ocPat

let private ocExpr (expr: AExpr) : int =
  match expr with
  | AMissingExpr _
  | ALitExpr _ -> 0

  | AIdentExpr _ -> 1
  | AListExpr (items, _) -> ocExprs items

  | ARecordExpr (baseOpt, fields, _) ->
    ocExprOpt baseOpt
    + sumBy (fun (_, init, _) -> ocExpr init) fields

  | AIfExpr (cond, body, altOpt, _) -> ocExpr cond + ocExpr body + ocExprOpt altOpt

  | AMatchExpr (cond, arms, _) ->
    ocExpr cond
    + sumBy (fun (AArm (pat, guardOpt, body, _)) -> ocPat pat + ocExprOpt guardOpt + ocExpr body) arms

  | AFunExpr (pats, body, _) -> ocPats pats + ocExpr body + 2 // "fun" occurs twice

  | ANavExpr (l, _, _) -> ocExpr l

  | AIndexExpr (l, r, _) ->
    match expr with
    | AIndexExpr (x, ARangeExpr (l, r, _), _) -> ocExpr x + ocExpr l + ocExpr r
    | _ -> ocExpr l + ocExpr r

  | AUnaryExpr (_, arg, _) -> ocExpr arg
  | ABinaryExpr (_, l, r, _) -> ocExpr l + ocExpr r
  | ATupleExpr (items, _) -> ocExprs items
  | AAscribeExpr (AIdentExpr (Name ("_", _)), ty, _) -> ocTy ty
  | AAscribeExpr (body, ty, _) -> ocExpr body + ocTy ty
  | ASemiExpr (stmts, last, _) -> ocExprs stmts + ocExpr last
  | ALetExpr (_, pat, body, next, _) -> ocPat pat + ocExpr body + ocExpr next

  | ARangeExpr _ -> unreachable () // Generated only inside of AIndexExpr.

let private ocExprOpt exprOpt : int =
  match exprOpt with
  | Some expr -> ocExpr expr
  | None -> 0

let private ocExprs = sumBy ocExpr

let private ocDecl (decl: ADecl) : int =
  match decl with
  | AExprDecl expr -> ocExpr expr
  | ALetDecl (_, pat, body, _) -> ocPat pat + ocExpr body

  | ATySynonymDecl (_, _name, tyArgs, ty, _) -> 1 + List.length tyArgs + ocTy ty

  | AUnionTyDecl (_, _name, tyArgs, variants, _) ->
    1
    + List.length tyArgs
    + sumBy (fun (AVariant (_name, payloadTy, _)) -> 1 + ocTyOpt payloadTy) variants

  | ARecordTyDecl (_, _name, tyArgs, fieldDecls, _) ->
    1
    + List.length tyArgs
    + sumBy (fun (_, ty, _) -> ocTy ty) fieldDecls

  | AOpenDecl _ -> 0
  | AModuleSynonymDecl (_name, _, _) -> 1
  | AModuleDecl (_, _, _name, decls, _) -> 1 + ocDecls decls
  | AAttrDecl (_contents, next, _) -> ocDecl next

let private ocDecls = sumBy ocDecl

let countSymbols (root: ARoot) : int =
  let (ARoot (_, decls)) = root

  // +2 for project and module
  ocDecls decls + 2
