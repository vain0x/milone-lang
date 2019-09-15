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

let apFalse loc =
  APat.Lit (litFalse, loc)

let apTrue loc =
  APat.Lit (litTrue, loc)

let axUnit loc =
  AExpr.TupleLit ([], loc)

let axFalse loc =
  AExpr.Lit (litFalse, loc)

let axTrue loc =
  AExpr.Lit (litTrue, loc)

let axNil loc =
  AExpr.ListLit ([], loc)

let axApp3 f x1 x2 x3 loc =
  let app x f = AExpr.Bin (Op.App, f, x, loc)
  f |> app x1 |> app x2 |> app x3

/// `[x; y; ..]`. Desugar to a chain of (::).
let desugarListLitPat pats loc =
  assert (pats |> listIsEmpty |> not)

  let rec go pats =
    match pats with
    | [] ->
      APat.ListLit ([], loc)

    | head :: tail ->
      let tail = go tail
      APat.Cons (head, tail, loc)

  go pats

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let desugarListLitExpr items loc =
  assert (items |> listIsEmpty |> not)

  let rec go items =
    match items with
    | [] ->
      AExpr.ListLit ([], loc)

    | head :: tail ->
      let tail = go tail
      AExpr.Bin (Op.Cons, head, tail, loc)

  go items

/// Desugar `if` to `match`.
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let desugarIf cond body alt loc =
  let alt =
    match alt with
    | AExpr.Missing _ ->
      axUnit loc
    | _ ->
      alt

  let arms =
    [
      AArm.T (apTrue loc, axTrue loc, body, loc)
      AArm.T (apFalse loc, axTrue loc, alt, loc)
    ]

  AExpr.Match (cond, arms, loc)

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let desugarFun pats body loc =
  let ident = "fun"
  let pat = APat.Fun (ident, pats, loc)
  let next = AExpr.Ident (ident, loc)
  AExpr.Let (pat, body, next, loc)

/// Desugar `-x` to `0 - x`.
let desugarUniNeg arg loc =
  let zero = AExpr.Lit (Lit.Int 0, loc)
  AExpr.Bin (Op.Sub, zero, arg, loc)

/// `l && r` ==> `if l then r else false`
let desugarBinAnd l r loc =
  desugarIf l r (axFalse loc) loc

/// `l || r` ==> `if l then true else r`
let desugarBinOr l r loc =
  desugarIf l (axTrue loc) r loc

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let desugarBinPipe l r loc =
  AExpr.Bin (Op.App, r, l, loc)

/// `s.[l .. r]` ==> `String.getSlice l r x`
/// NOTE: Evaluation order does change.
let tryDesugarIndexRange expr loc =
  match expr with
  | AExpr.Index (s, AExpr.Range ([l; r], _), _) ->
    let getSlice = AExpr.Nav (AExpr.Ident ("String", loc), "getSlice", loc)
    true, axApp3 getSlice l r s loc

  | _ ->
    false, expr

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
let desugarLet pat body next loc =
  match pat with
  | APat.Anno (pat, annoTy, annoLoc) ->
    let body = AExpr.Anno (body, annoTy, annoLoc)
    desugarLet pat body next loc

  | APat.Fun (ident, args, _) ->
    ALet.LetFun (ident, args, body, next, loc)

  | _ ->
    ALet.LetVal (pat, body, next, loc)

let onTy (ty: ATy, nameCtx: NameCtx): Ty * NameCtx =
  match ty with
  | ATy.Error (_, loc)
  | ATy.Missing loc ->
    Ty.Error loc, nameCtx

  | ATy.Ident (ident, _) ->
    let tySerial, nameCtx = nameCtx |> nameCtxAdd ident
    tyRef tySerial [], nameCtx

  | ATy.Suffix (lTy, ident, _) ->
    let lTy, nameCtx = (lTy, nameCtx) |> onTy
    let tySerial, nameCtx = nameCtx |> nameCtxAdd ident
    tyRef tySerial [lTy], nameCtx

  | ATy.Tuple (itemTys, _) ->
    let itemTys, nameCtx = (itemTys, nameCtx) |> stMap onTy
    tyTuple itemTys, nameCtx

  | ATy.Fun (sTy, tTy, _) ->
    let sTy, nameCtx = (sTy, nameCtx) |> onTy
    let tTy, nameCtx = (tTy, nameCtx) |> onTy
    tyFun sTy tTy, nameCtx

let onPat (pat: APat, nameCtx: NameCtx): HPat * NameCtx =
  match pat with
  | APat.Error (msg, loc) ->
    failwithf "Pattern error %s %A" msg loc

  | APat.Missing (_, loc) ->
    failwithf "Missing pattern %A" loc

  | APat.Lit (lit, loc) ->
    HPat.Lit (lit, loc), nameCtx

  | APat.Ident (ident, loc) ->
    let serial, nameCtx = nameCtx |> nameCtxAdd ident
    HPat.Ref (ident, serial, noTy, loc), nameCtx

  | APat.ListLit ([], loc) ->
    patNil noTy loc, nameCtx

  | APat.ListLit (pats, loc) ->
    let pat = desugarListLitPat pats loc
    (pat, nameCtx) |> onPat

  | APat.Nav (l, r, loc) ->
    let l, nameCtx = (l, nameCtx) |> onPat
    HPat.Nav (l, r, noTy, loc), nameCtx

  | APat.Call (calleePat, argPats, loc) ->
    let calleePat, nameCtx = (calleePat, nameCtx) |> onPat
    let argPats, nameCtx = (argPats, nameCtx) |> stMap onPat
    HPat.Call (calleePat, argPats, noTy, loc), nameCtx

  | APat.Cons (head, tail, loc) ->
    let head, nameCtx = (head, nameCtx) |> onPat
    let tail, nameCtx = (tail, nameCtx) |> onPat
    HPat.Cons (head, tail, noTy, loc), nameCtx

  | APat.TupleLit (pats, loc) ->
    let pats, nameCtx = (pats, nameCtx) |> stMap onPat
    HPat.Tuple (pats, noTy, loc), nameCtx

  | APat.As (pat, ident, loc) ->
    let serial, nameCtx = nameCtx |> nameCtxAdd ident
    let pat, nameCtx = (pat, nameCtx) |> onPat
    HPat.As (pat, ident, serial, loc), nameCtx

  | APat.Anno (pat, ty, loc) ->
    let pat, nameCtx = (pat, nameCtx) |> onPat
    let ty, nameCtx = (ty, nameCtx) |> onTy
    HPat.Anno (pat, ty, loc), nameCtx

  | APat.Or (l, r, loc) ->
    let l, nameCtx = (l, nameCtx) |> onPat
    let r, nameCtx = (r, nameCtx) |> onPat
    HPat.Or (l, r, noTy, loc), nameCtx

  | APat.Fun (_, _, loc) ->
    failwithf "Invalid occurrence of fun pattern: %A" loc

let onExpr (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  match expr with
  | AExpr.Error (msg, loc) ->
    HExpr.Error (msg, loc), nameCtx

  | AExpr.Missing loc ->
    HExpr.Error ("Missing expression", loc), nameCtx

  | AExpr.Lit (lit, loc) ->
    HExpr.Lit (lit, loc), nameCtx

  | AExpr.Ident (ident, loc) ->
    let serial, nameCtx = nameCtx |> nameCtxAdd ident
    HExpr.Ref (ident, HValRef.Var serial, noTy, loc), nameCtx

  | AExpr.ListLit ([], loc) ->
    hxNil noTy loc, nameCtx

  | AExpr.ListLit (items, loc) ->
    let expr = desugarListLitExpr items loc
    (expr, nameCtx) |> onExpr

  | AExpr.If (cond, body, alt, loc) ->
    let expr = desugarIf cond body alt loc
    (expr, nameCtx) |> onExpr

  | AExpr.Match (target, arms, loc) ->
    // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
    let onArm (AArm.T (pat, guard, body, loc), nameCtx) =
      let pat, nameCtx =
        (pat, nameCtx) |> onPat
      let guard, nameCtx =
        match guard with
        | AExpr.Missing _ ->
          hxTrue loc, nameCtx
        | _ ->
          (guard, nameCtx) |> onExpr
      let body, nameCtx =
        (body, nameCtx) |> onExpr
      (pat, guard, body), nameCtx
    let target, nameCtx = (target, nameCtx) |> onExpr
    let arms, nameCtx = (arms, nameCtx) |> stMap onArm
    HExpr.Match (target, arms, noTy, loc), nameCtx

  | AExpr.Fun (pats, body, loc) ->
    let expr = desugarFun pats body loc
    (expr, nameCtx) |> onExpr

  | AExpr.Nav (l, r, loc) ->
    let l, nameCtx = (l, nameCtx) |> onExpr
    HExpr.Nav (l, r, noTy, loc), nameCtx

  | AExpr.Index (l, r, loc) ->
    match tryDesugarIndexRange expr loc with
    | true, expr ->
      (expr, nameCtx) |> onExpr

    | false, _ ->
      let l, nameCtx = (l, nameCtx) |> onExpr
      let r, nameCtx = (r, nameCtx) |> onExpr
      HExpr.Bin (Op.Index, l, r, noTy, loc), nameCtx

  | AExpr.Uni (UniOp.Neg, arg, loc) ->
    let expr = desugarUniNeg arg loc
    (expr, nameCtx) |> onExpr

  | AExpr.Bin (Op.And, l, r, loc) ->
    let expr = desugarBinAnd l r loc
    (expr, nameCtx) |> onExpr

  | AExpr.Bin (Op.Or, l, r, loc) ->
    let expr = desugarBinOr l r loc
    (expr, nameCtx) |> onExpr

  | AExpr.Bin (Op.Pipe, l, r, loc) ->
    let expr = desugarBinPipe l r loc
    (expr, nameCtx) |> onExpr

  | AExpr.Bin (op, l, r, loc) ->
    let l, nameCtx = (l, nameCtx) |> onExpr
    let r, nameCtx = (r, nameCtx) |> onExpr
    HExpr.Bin (op, l, r, noTy, loc), nameCtx

  | AExpr.Range (_, loc) ->
    HExpr.Error ("Invalid use of range syntax.", loc), nameCtx

  | AExpr.TupleLit (items, loc) ->
    let items, nameCtx = (items, nameCtx) |> stMap onExpr
    HExpr.Inf (InfOp.Tuple, items, noTy, loc), nameCtx

  | AExpr.Anno (body, ty, loc) ->
    let body, nameCtx = (body, nameCtx) |> onExpr
    let ty, nameCtx = (ty, nameCtx) |> onTy
    HExpr.Inf (InfOp.Anno, [body], ty, loc), nameCtx

  | AExpr.Semi (exprs, loc) ->
    let exprs, nameCtx = (exprs, nameCtx) |> stMap onExpr
    HExpr.Inf (InfOp.Semi, exprs, noTy, loc), nameCtx

  | AExpr.Let (pat, body, next, loc) ->
    match desugarLet pat body next loc with
    | ALet.LetFun (ident, args, body, next, loc) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let args, nameCtx = (args, nameCtx) |> stMap onPat
      let body, nameCtx = (body, nameCtx) |> onExpr
      let next, nameCtx = (next, nameCtx) |> onExpr
      HExpr.LetFun (ident, serial, args, body, next, noTy, loc), nameCtx

    | ALet.LetVal (pat, body, next, loc) ->
      let pat, nameCtx = (pat, nameCtx) |> onPat
      let body, nameCtx = (body, nameCtx) |> onExpr
      let next, nameCtx = (next, nameCtx) |> onExpr
      HExpr.Let (pat, body, next, noTy, loc), nameCtx

  | AExpr.TySynonym (ident, ty, loc) ->
    let serial, nameCtx = nameCtx |> nameCtxAdd ident
    let ty, nameCtx = (ty, nameCtx) |> onTy
    HExpr.TyDef (ident, serial, TyDecl.Synonym (ty, loc), loc), nameCtx

  | AExpr.TyUnion (ident, variants, loc) ->
    let onVariant (AVariant.T (ident, payloadTy, _variantLoc), nameCtx) =
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let hasPayload, payloadTy, nameCtx =
        match payloadTy with
        | Some ty ->
          let ty, nameCtx = (ty, nameCtx) |> onTy
          true, ty, nameCtx
        | None ->
          false, tyUnit, nameCtx
      (ident, serial, hasPayload, payloadTy), nameCtx
    let unionSerial, nameCtx =
      nameCtx |> nameCtxAdd ident
    let variants, nameCtx =
      (variants, nameCtx) |> stMap onVariant
    HExpr.TyDef (ident, unionSerial, TyDecl.Union (ident, variants, loc), loc), nameCtx

  | AExpr.Open (path, loc) ->
    HExpr.Open (path, loc), nameCtx

let astToHir (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  (expr, nameCtx) |> onExpr
