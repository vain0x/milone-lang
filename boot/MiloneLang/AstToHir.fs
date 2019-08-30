/// Converts AST to HIR.
/// Just a data conversion to keep the parser decoupled.
module rec MiloneLang.AstToHir

open MiloneLang.Types
open MiloneLang.Helpers

/// Desugar to a chain of (::).
let desugarListLitPat pats loc =
  assert (pats |> listIsEmpty |> not)

  let rec go pats =
    match pats with
    | [] ->
      APat.ListLit ([], loc)

    | head :: pats ->
      let tail = go pats
      APat.Cons (head, tail, loc)

  go pats

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let desugarFun pats body loc =
  let ident = "fun"
  let pat = APat.Call (APat.Ident (ident, loc), pats, loc)
  let next = AExpr.Ident (ident, loc)
  AExpr.Let (pat, body, next, loc)

/// Desugar `-x` to `0 - x`.
let desugarUniNeg arg loc =
  let zero = AExpr.Lit (Lit.Int 0, loc)
  AExpr.Bin (Op.Sub, zero, arg, loc)

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

  | AExpr.ListLit (exprs, loc) ->
    let exprs, nameCtx = (exprs, nameCtx) |> stMap onExpr
    HExpr.Inf (InfOp.List noTy, exprs, noTy, loc), nameCtx

  | AExpr.If (cond, body, alt, loc) ->
    let cond, nameCtx =
      (cond, nameCtx) |> onExpr
    let body, nameCtx =
      (body, nameCtx) |> onExpr
    let alt, nameCtx =
      match alt with
      | AExpr.Missing loc ->
        hxUnit loc, nameCtx
      | expr ->
        (expr, nameCtx) |> onExpr
    HExpr.If (cond, body, alt, noTy, loc), nameCtx

  | AExpr.Match (target, arms, loc) ->
    // Desugar `| pat -> body` to `|pat when true -> body` so that all arms have guard expressions.
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
    let l, nameCtx = (l, nameCtx) |> onExpr
    let r, nameCtx = (r, nameCtx) |> onExpr
    HExpr.Bin (Op.Index, l, r, noTy, loc), nameCtx

  | AExpr.Uni (UniOp.Neg, arg, loc) ->
    let expr = desugarUniNeg arg loc
    (expr, nameCtx) |> onExpr

  | AExpr.Bin (op, l, r, loc) ->
    let l, nameCtx = (l, nameCtx) |> onExpr
    let r, nameCtx = (r, nameCtx) |> onExpr
    HExpr.Bin (op, l, r, noTy, loc), nameCtx

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

  | AExpr.Let (pat, init, next, loc) ->
    let pat, nameCtx = (pat, nameCtx) |> onPat
    let init, nameCtx = (init, nameCtx) |> onExpr
    let next, nameCtx = (next, nameCtx) |> onExpr
    HExpr.Let (pat, init, next, noTy, loc), nameCtx

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
