module rec MiloneLang.AstToHir

open MiloneLang.Helpers

let onTy (ty: ATy): Ty =
  match ty with
  | ATy.Error _
  | ATy.Missing _ ->
    Ty.Error

  | ATy.Ident ("unit", _) ->
    Ty.Con (TyCon.Tuple, [])

  | ATy.Ident ("bool", _) ->
    Ty.Con (TyCon.Bool, [])

  | ATy.Ident ("int", _) ->
    Ty.Con (TyCon.Int, [])

  | ATy.Ident ("char", _) ->
    Ty.Con (TyCon.Char, [])

  | ATy.Ident ("string", _) ->
    Ty.Con (TyCon.Str, [])

  | ATy.Ident ("obj", _) ->
    Ty.Con (TyCon.Obj, [])

  | ATy.Ident (ident, _) ->
    Ty.Con (TyCon.RefIdent ident, [])

  | ATy.Suffix (lTy, "list", _) ->
    let lTy = lTy |> onTy
    Ty.Con (TyCon.List, [lTy])

  | ATy.Suffix _ ->
    Ty.Error

  | ATy.Tuple (itemTys, _) ->
    let itemTys = itemTys |> List.map onTy
    Ty.Con (TyCon.Tuple, itemTys)

  | ATy.Fun (sTy, tTy, _) ->
    let sTy = sTy |> onTy
    let tTy = tTy |> onTy
    Ty.Con (TyCon.Fun, [sTy; tTy])

let onPat (pat: APat): HPat =
  match pat with
  | APat.Error (msg, loc) ->
    failwithf "Pattern error %s %A" msg loc

  | APat.Missing (_, loc) ->
    failwithf "Missing pattern %A" loc

  | APat.Lit (lit, loc) ->
    HPat.Lit (lit, loc)

  | APat.Ident (ident, loc) ->
    HPat.Ref (ident, noSerial, noTy, loc)

  | APat.ListLit (pats, loc) ->
    // Desugar to (::).
    let pats = pats |> List.map onPat
    let nilPat = HPat.Nil (noTy, loc)
    let consPat tail head = HPat.Cons (head, tail, noTy, loc)
    pats |> List.rev |> List.fold consPat nilPat

  | APat.Nav (l, r, loc) ->
    let l = l |> onPat
    HPat.Nav (l, r, noTy, loc)

  | APat.Call (calleePat, argPats, loc) ->
    let calleePat = calleePat |> onPat
    let argPats = argPats |> List.map onPat
    HPat.Call (calleePat, argPats, noTy, loc)

  | APat.Cons (head, tail, loc) ->
    let head = head |> onPat
    let tail = tail |> onPat
    HPat.Cons (head, tail, noTy, loc)

  | APat.TupleLit (pats, loc) ->
    let pats = pats |> List.map onPat
    HPat.Tuple (pats, noTy, loc)

  | APat.As (pat, ident, loc) ->
    let pat = pat |> onPat
    HPat.As (pat, ident, noSerial, loc)

  | APat.Anno (pat, ty, loc) ->
    let pat = pat |> onPat
    let ty = ty |> onTy
    HPat.Anno (pat, ty, loc)

  | APat.Or (l, r, loc) ->
    let l = l |> onPat
    let r = r |> onPat
    HPat.Or (l, r, noTy, loc)

let onExpr (expr: AExpr): HExpr =
  match expr with
  | AExpr.Error (msg, loc) ->
    HExpr.Error (msg, loc)

  | AExpr.Missing loc ->
    HExpr.Error ("Missing expression", loc)

  | AExpr.Lit (lit, loc) ->
    HExpr.Lit (lit, loc)

  | AExpr.Ident (ident, loc) ->
    HExpr.Ref (ident, HValRef.Var noSerial, noTy, loc)

  | AExpr.ListLit (exprs, loc) ->
    let exprs = exprs |> List.map onExpr
    HExpr.Inf (InfOp.List noTy, exprs, noTy, loc)

  | AExpr.If (cond, body, alt, loc) ->
    let cond =
      cond |> onExpr
    let body =
      body |> onExpr
    let alt =
      match alt with
      | AExpr.Missing loc ->
        hxUnit loc
      | expr ->
        expr |> onExpr
    HExpr.If (cond, body, alt, noTy, loc)

  | AExpr.Match (target, arms, loc) ->
    let onArm (AArm.T (pat, guard, body, loc)) =
      let pat =
        pat |> onPat
      let guard =
        match guard with
        | AExpr.Missing _ ->
          hxTrue loc
        | _ ->
          guard |> onExpr
      let body =
        body |> onExpr
      pat, guard, body
    let target = target |> onExpr
    let arms = arms |> List.map onArm
    HExpr.Match (target, arms, noTy, loc)

  | AExpr.Fun (pats, body, loc) ->
    // Desugar to let expression.
    // `fun x y .. -> z` ==> `let f x y .. = z in f`
    let ident = "fun"
    let pat = APat.Call (APat.Ident (ident, loc), pats, loc)
    let next = AExpr.Ident (ident, loc)
    let expr = AExpr.Let (pat, body, next, loc)
    expr |> onExpr

  | AExpr.Nav (l, r, loc) ->
    let l = l |> onExpr
    HExpr.Nav (l, r, noTy, loc)

  | AExpr.Index (l, r, loc) ->
    let l = l |> onExpr
    let r = r |> onExpr
    HExpr.Op (Op.Index, l, r, noTy, loc)

  | AExpr.Bin (op, l, r, loc) ->
    let l = l |> onExpr
    let r = r |> onExpr
    HExpr.Op (op, l, r, noTy, loc)

  | AExpr.TupleLit (items, loc) ->
    let items = items |> List.map onExpr
    HExpr.Inf (InfOp.Tuple, items, noTy, loc)

  | AExpr.Anno (body, ty, loc) ->
    let body = body |> onExpr
    let ty = onTy ty
    HExpr.Inf (InfOp.Anno, [body], ty, loc)

  | AExpr.Semi (exprs, loc) ->
    let exprs = exprs |> List.map onExpr
    HExpr.Inf (InfOp.AndThen, exprs, noTy, loc)

  | AExpr.Let (pat, init, next, loc) ->
    let pat = pat |> onPat
    let init = init |> onExpr
    let next = next |> onExpr
    HExpr.Let (pat, init, next, noTy, loc)

  | AExpr.TySynonym (ident, ty, loc) ->
    let ty = ty |> onTy
    HExpr.TyDef (ident, noSerial, TyDecl.Synonym (ty, loc), loc)

  | AExpr.TyUnion (ident, variants, loc) ->
    let onVariant (AVariant.T (ident, argTy, loc)) =
      match argTy with
      | Some ty ->
        let ty = ty |> onTy
        ident, noSerial, true, ty
      | None ->
        ident, noSerial, false, tyUnit
    let variants = variants |> List.map onVariant
    HExpr.TyDef (ident, noSerial, TyDecl.Union (ident, variants, loc), loc)

  | AExpr.Open (path, loc) ->
    HExpr.Open (path, loc)

let astToHir (expr: AExpr): HExpr =
  expr |> onExpr
