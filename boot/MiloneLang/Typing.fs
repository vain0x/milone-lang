module rec MiloneLang.Typing

open MiloneLang
open MiloneLang.Helpers

type TyCtx =
  {
    /// Next serial number for variables.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    VarSerial: int
    /// Value level identifiers.
    /// From serial number to (source identifier, type, location).
    Vars: Map<int, string * ValueIdent * Ty * Loc>
    /// Identifier to type and serial.
    VarEnv: Map<string, ValueIdent * Ty * int>
    TySerial: int
    TyEnv: Map<string, Ty>
    Tys: Map<int, string * TyDef * Loc>
  }

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let ctxRollback bCtx dCtx: TyCtx =
  assert (bCtx.VarSerial <= dCtx.VarSerial)
  assert (bCtx.TySerial <= dCtx.TySerial)
  { dCtx with
      VarEnv = bCtx.VarEnv
  }

let ctxFreshTySerial (ctx: TyCtx) =
  let serial = ctx.TySerial + 1
  let ctx = { ctx with TySerial = ctx.TySerial + 1 }
  serial, ctx

let ctxFreshTyVar ident (ctx: TyCtx): Ty * string * TyCtx =
  let serial, ctx = ctxFreshTySerial ctx
  let ident = sprintf "'%s_%d" ident serial
  let ty = Ty.Var ident
  ty, ident, ctx

let ctxAddTy tyIdent tyDef loc ctx =
  match tyDef with
  | TyDef.Union variants ->
    let tySerial, ctx = ctxFreshTySerial ctx
    let refTy = Ty.Ref (tyIdent, tySerial)

    // Register variants as values.
    let variants, ctx =
      (variants, ctx) |> stMap (fun ((lIdent, _, hasArg, lArgTy), ctx) ->
        let valueIdent = ValueIdent.Variant tySerial
        let lTy = if hasArg then Ty.Fun (lArgTy, refTy) else refTy
        let lSerial, ctx = ctxFreshVar ctx lIdent valueIdent lTy loc
        (lIdent, lSerial, hasArg, lArgTy), ctx
      )

    let tyDef = TyDef.Union variants
    let ctx =
      { ctx with
          TyEnv = ctx.TyEnv |> Map.add tyIdent refTy
          Tys = ctx.Tys |> Map.add tySerial (tyIdent, tyDef, loc)
      }
    tySerial, tyDef, ctx

/// NOTE: currently used also for type reference resolution.
let ctxResolveTyVar name (ctx: TyCtx): Ty =
  match ctx.TyEnv |> Map.tryFind name with
  | Some ty ->
    ty
  | None ->
    Ty.Var name

let ctxFreshVar (ctx: TyCtx) ident valueIdent ty loc: int * TyCtx =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarEnv = ctx.VarEnv |> Map.add ident (valueIdent, ty, serial)
        Vars = ctx.Vars |> Map.add serial (ident, valueIdent, ty, loc)
    }
  serial, ctx

/// Resolves type references in type annotation.
let ctxResolveTy ctx ty =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj ->
      ty
    | Ty.Ref (ident, _) ->
      ctxResolveTyVar ident ctx
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Tuple itemTys ->
      Ty.Tuple (List.map go itemTys)
    | Ty.List ty ->
      Ty.List (go ty)
    | Ty.Var _ ->
      failwith "Never"
  go ty

/// Gets if the specified type var doesn't appear in the specified type.
let isFreshTyVar ty tyVar: bool =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj
    | Ty.Ref _
    | Ty.Tuple [] ->
      true
    | Ty.Fun (sTy, tTy) ->
      go sTy && go tTy
    | Ty.Tuple (itemTy :: itemTys) ->
      go itemTy && go (Ty.Tuple itemTys)
    | Ty.List ty ->
      go ty
    | Ty.Var tv ->
      tv <> tyVar
  go ty

/// Gets if the specified type is resolved to a morphic type.
let isMonomorphic ctx ty: bool =
  match substTy ctx ty with
  | Ty.Bool
  | Ty.Int
  | Ty.Char
  | Ty.Str
  | Ty.Range
  | Ty.Obj
  | Ty.Tuple []
  | Ty.Ref _ ->
    true
  | Ty.Error
  | Ty.Var _ ->
    false
  | Ty.Fun (sTy, tTy) ->
    isMonomorphic ctx sTy && isMonomorphic ctx tTy
  | Ty.List ty ->
    isMonomorphic ctx ty
  | Ty.Tuple (itemTy :: itemTys) ->
    isMonomorphic ctx itemTy && isMonomorphic ctx (Ty.Tuple itemTys)

/// Adds type-var/type binding.
let bindTy (ctx: TyCtx) tyVar ty: TyCtx =
  // Don't bind itself.
  if substTy ctx ty = Ty.Var tyVar then
    ctx
  else
    { ctx with TyEnv = ctx.TyEnv |> Map.add tyVar ty }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let substTy (ctx: TyCtx) ty: Ty =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj
    | Ty.Ref _ ->
      ty
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Tuple itemTys ->
      Ty.Tuple (List.map go itemTys)
    | Ty.List ty ->
      Ty.List (go ty)
    | Ty.Var tyVar ->
      let ty2 = ctxResolveTyVar tyVar ctx
      if ty = ty2 then ty else go ty2
  go ty

/// Resolves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let unifyTy (ctx: TyCtx) (lty: Ty) (rty: Ty): TyCtx =
  let rec go lty rty ctx =
    match substTy ctx lty, substTy ctx rty with
    | Ty.Var ltv, Ty.Var rtv when ltv = rtv ->
      bindTy ctx ltv rty
    | Ty.Var ltv, _ when isFreshTyVar rty ltv ->
      bindTy ctx ltv rty
    | _, Ty.Var _ ->
      go rty lty ctx
    | Ty.Fun (lSTy, lTTy), Ty.Fun (rSTy, rTTy) ->
      ctx |> go lSTy rSTy |> go lTTy rTTy
    | Ty.List lTy, Ty.List rTy ->
      ctx |> go lTy rTy
    | Ty.Tuple (lTy :: lTys), Ty.Tuple (rTy :: rTys) ->
      ctx |> go lTy rTy |> go (Ty.Tuple lTys) (Ty.Tuple rTys)
    | Ty.Error, _
    | _, Ty.Error
    | Ty.Tuple [], Ty.Tuple []
    | Ty.Bool, Ty.Bool
    | Ty.Int, Ty.Int
    | Ty.Char, Ty.Char
    | Ty.Str, Ty.Str
    | Ty.Range, Ty.Range
    | Ty.Obj, Ty.Obj ->
      ctx
    | Ty.Ref (_, l), Ty.Ref (_, r) when l <> noSerial && l = r ->
      ctx
    | Ty.Var _, _ ->
      failwithf "Couldn't unify (due to self recursion) %A %A" lty rty
    | Ty.Bool, _
    | Ty.Int, _
    | Ty.Char, _
    | Ty.Str, _
    | Ty.Range, _
    | Ty.Obj, _
    | Ty.Fun _, _
    | Ty.Tuple _, _
    | Ty.List _, _
    | Ty.Ref _, _ ->
      let lty, rty = substTy ctx lty, substTy ctx rty
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let valueIdentArity v =
  match v with
  | ValueIdent.Fun arity -> arity
  | _ -> 1

let inferPatRef (ctx: TyCtx) ident loc ty =
  let serial, ty, ctx =
    match ctx.VarEnv |> Map.tryFind ident with
    | Some (ValueIdent.Variant _, variantTy, serial) ->
      let ctx = unifyTy ctx ty variantTy
      serial, ty, ctx
    | _ ->
      let serial, ctx = ctxFreshVar ctx ident ValueIdent.Var ty loc
      serial, ty, ctx
  HPat.Ref (ident, serial, ty, loc), ctx

let inferPatCall (ctx: TyCtx) callee args loc ty =
  match callee, args with
  | HPat.Ref (ident, _, _, refLoc), [arg] ->
    match ctx.VarEnv |> Map.tryFind ident with
    | Some (ValueIdent.Variant _, (Ty.Fun (argTy, callTy) as variantTy), serial) ->
      let arg, ctx = inferPat ctx arg argTy
      let callee = HPat.Ref (ident, serial, variantTy, refLoc)
      let ctx = unifyTy ctx ty callTy
      HPat.Call (callee, [arg], ty, loc), ctx
    | _ ->
      failwith "Type Error: Not a function variant."
  | _ ->
    failwith "unimpl use of call pattern"

let inferPatTuple ctx itemPats loc tupleTy =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] ->
      List.rev accPats, List.rev accTys, ctx
    | itemPat :: itemPats ->
      let itemTy, _, ctx = ctxFreshTyVar "item" ctx
      let itemPat, ctx = inferPat ctx itemPat itemTy
      go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats
  let itemPats, itemTys, ctx = go [] [] ctx itemPats
  let ctx = unifyTy ctx tupleTy (Ty.Tuple itemTys)
  HPat.Tuple (itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  HPat.Cons (l, r, itemTy, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | HPat.Lit (lit, _) ->
    pat, unifyTy ctx ty (litTy lit)
  | HPat.Nil (_, loc) ->
    let itemTy, _, ctx = ctxFreshTyVar "item" ctx
    let ctx = unifyTy ctx ty (Ty.List itemTy)
    HPat.Nil (itemTy, loc), ctx
  | HPat.Ref (ident, _, _, loc) ->
    inferPatRef ctx ident loc ty
  | HPat.Call (callee, args, _, loc) ->
    inferPatCall ctx callee args loc ty
  | HPat.Cons (l, r, _, loc) ->
    inferPatCons ctx l r loc ty
  | HPat.Tuple (items, _, loc) ->
    inferPatTuple ctx items loc ty
  | HPat.Anno (pat, annoTy, _) ->
    let annoTy = ctxResolveTy ctx annoTy
    let ctx = unifyTy ctx ty annoTy
    let pat, ctx = inferPat ctx pat annoTy
    pat, ctx

let inferRef (ctx: TyCtx) ident loc ty =
  match ctx.VarEnv |> Map.tryFind ident, ident with
  | Some (valueIdent, refTy, serial), _ ->
    let ctx = unifyTy ctx refTy ty
    HExpr.Ref (ident, serial, valueIdentArity valueIdent, ty, loc), ctx
  | None, "not" ->
    let ctx = unifyTy ctx (Ty.Fun (Ty.Bool, Ty.Bool)) ty
    HExpr.Ref (ident, SerialNot, 1, ty, loc), ctx
  | None, "exit" ->
    let resultTy, _, ctx = ctxFreshTyVar "exit" ctx
    let ctx = unifyTy ctx (Ty.Fun (Ty.Int, resultTy)) ty
    HExpr.Ref (ident, SerialExit, 1, ty, loc), ctx
  | None, "box" ->
    let argTy, _, ctx = ctxFreshTyVar "box" ctx
    let ctx = unifyTy ctx (Ty.Fun (argTy, Ty.Obj)) ty
    HExpr.Ref (ident, SerialBox, 1, ty, loc), ctx
  | None, "unbox" ->
    let resultTy, _, ctx = ctxFreshTyVar "unbox" ctx
    let ctx = unifyTy ctx (Ty.Fun (Ty.Obj, resultTy)) ty
    HExpr.Ref (ident, SerialUnbox, 1, ty, loc), ctx
  | None, "printfn" ->
    // The function's type is unified in app expression inference.
    HExpr.Ref (ident, SerialPrintfn, 9999, ty, loc), ctx
  | None, _ ->
    failwithf "Couldn't resolve var %s" ident

let inferNil ctx loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  hxNil itemTy loc, ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target arms loc resultTy =
  let targetTy, _, ctx = ctxFreshTyVar "target" ctx
  let target, ctx = inferExpr ctx target targetTy

  let arms, ctx =
    (arms, ctx) |> stMap (fun ((pat, body), ctx) ->
      let baseCtx = ctx
      let pat, ctx = inferPat ctx pat targetTy
      let body, ctx = inferExpr ctx body resultTy
      let ctx = ctxRollback baseCtx ctx
      (pat, body), ctx
    )

  HExpr.Match (target, arms, resultTy, loc), ctx

let inferNav ctx sub mes loc resultTy =
  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let sub, ctx = inferExpr ctx sub subTy
  match substTy ctx subTy, mes with
  | Ty.Str, "Length" ->
    let ctx = unifyTy ctx resultTy Ty.Int
    let funExpr = HExpr.Ref (mes, SerialStrLength, 1, Ty.Fun (Ty.Str, Ty.Int), loc)
    HExpr.Op (Op.App, funExpr, sub, Ty.Int, loc), ctx
  | _ ->
    failwithf "Unknown nav %A" (sub, mes, loc)

/// `x.[i] : 'y` <== x : 'x, i : int or i : range
/// NOTE: Currently only the `x : string` case can compile, however,
/// we don't infer that for compatibility.
let inferIndex ctx l r loc resultTy =
  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let indexTy, _, ctx = ctxFreshTyVar "index" ctx
  let l, ctx = inferExpr ctx l subTy
  let r, ctx = inferExpr ctx r indexTy
  match substTy ctx subTy, substTy ctx indexTy with
  | Ty.Str, Ty.Range ->
    let ctx = unifyTy ctx resultTy Ty.Str
    hxIndex l r resultTy loc, ctx
  | Ty.Str, _ ->
    let ctx = unifyTy ctx indexTy Ty.Int
    let ctx = unifyTy ctx resultTy Ty.Char
    hxIndex l r resultTy loc, ctx
  | subTy, indexTy ->
    failwithf "Type: Index not supported %A" (subTy, indexTy, l, r)

let inferOpAppPrintfn ctx ident serial arg calleeTy loc =
  match arg with
  | HExpr.Lit (Lit.Str format, _) ->
    let funTy = analyzeFormat format
    let arity = arityTy funTy
    let ctx = unifyTy ctx calleeTy funTy
    HExpr.Ref (ident, serial, arity, calleeTy, loc), ctx
  | _ ->
    failwith """First arg of printfn must be string literal, ".."."""

let inferOpApp ctx callee arg loc appTy =
  let argTy, _, ctx = ctxFreshTyVar "arg" ctx
  let arg, ctx = inferExpr ctx arg argTy
  let callee, ctx = inferExpr ctx callee (Ty.Fun (argTy, appTy))
  let callee, ctx =
    match callee with
    | HExpr.Ref (ident, serial, _, calleeTy, loc) when serial = SerialPrintfn ->
      inferOpAppPrintfn ctx ident serial arg calleeTy loc
    | _ ->
      callee, ctx
  HExpr.Op (Op.App, callee, arg, appTy, loc), ctx

let inferOpCore (ctx: TyCtx) op left right loc operandTy resultTy =
  let left, ctx = inferExpr ctx left operandTy
  let right, ctx = inferExpr ctx right operandTy
  HExpr.Op (op, left, right, resultTy, loc), ctx

let inferOpAdd (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = ctxFreshTyVar "operand" ctx
  let ctx = unifyTy ctx operandTy resultTy
  let expr, ctx = inferOpCore ctx op left right loc operandTy resultTy
  match substTy ctx operandTy with
  | Ty.Int
  | Ty.Str ->
    expr, ctx
  | ty ->
    failwithf "Type: No support (+) for %A (%A + %A)" ty left right

let inferOpArith (ctx: TyCtx) op left right loc resultTy =
  let ctx = unifyTy ctx resultTy Ty.Int
  inferOpCore ctx op left right loc Ty.Int resultTy

let inferOpCmp (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = ctxFreshTyVar "operand" ctx
  let ctx = unifyTy ctx resultTy Ty.Bool
  inferOpCore ctx op left right loc operandTy resultTy

let inferOpCons ctx left right loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  let left, ctx = inferExpr ctx left itemTy
  let right, ctx = inferExpr ctx right listTy
  HExpr.Op (Op.Cons itemTy, left, right, listTy, loc), ctx

let inferOpRange ctx op left right loc ty =
  let ctx = unifyTy ctx ty Ty.Range
  inferOpCore ctx op left right loc Ty.Int ty

let inferOp (ctx: TyCtx) op left right loc ty =
  match op with
  | Op.Add ->
    inferOpAdd ctx op left right loc ty
  | Op.Sub
  | Op.Mul
  | Op.Div
  | Op.Mod ->
    inferOpArith ctx op left right loc ty
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le
  | Op.Gt
  | Op.Ge ->
    inferOpCmp ctx op left right loc ty
  | Op.App ->
    inferOpApp ctx left right loc ty
  | Op.Cons _ ->
    inferOpCons ctx left right loc ty
  | Op.Range ->
    inferOpRange ctx op left right loc ty
  | Op.Index ->
    inferIndex ctx left right loc ty
  | Op.And
  | Op.Or
  | Op.Pipe ->
    failwith "Never: Desugared operators"

let inferTuple (ctx: TyCtx) items loc tupleTy =
  let rec go acc itemTys ctx items =
    match items with
    | [] ->
      List.rev acc, List.rev itemTys, ctx
    | item :: items ->
      let itemTy, _, ctx = ctxFreshTyVar "item" ctx
      let item, ctx = inferExpr ctx item itemTy
      go (item :: acc) (itemTy :: itemTys) ctx items
  let items, itemTys, ctx = go [] [] ctx items
  let ctx = unifyTy ctx tupleTy (Ty.Tuple itemTys)
  hxTuple items loc, ctx

let inferAnno ctx expr annoTy ty =
  let annoTy = ctxResolveTy ctx annoTy
  let ctx = unifyTy ctx annoTy ty
  inferExpr ctx expr annoTy

let inferLetVal ctx pat init loc =
  let initTy, _, ctx = ctxFreshTyVar "init" ctx
  // Type init expression.
  let init, initCtx = inferExpr ctx init initTy
  // Remove symbols defined inside `init`.
  let ctx = ctxRollback ctx initCtx
  // Define new variables defined by the pat to the context.
  let pat, ctx = inferPat ctx pat initTy
  HExpr.Let (pat, init, loc), ctx

let inferLetFun ctx calleeName argPats body loc =
  let bodyTy, _, ctx = ctxFreshTyVar "body" ctx

  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx bodyTy argPats =
    match argPats with
    | [] ->
      [], bodyTy, ctx
    | argPat :: argPats ->
      let argTy, _, ctx = ctxFreshTyVar "arg" ctx
      let pat, ctx = inferPat ctx argPat argTy
      let pats, bodyTy, ctx = inferArgs ctx bodyTy argPats
      pat :: pats, Ty.Fun (argTy, bodyTy), ctx

  let arity = List.length argPats
  let funTy, _, ctx =
    if calleeName = "main"
    then Ty.Fun (tyUnit, Ty.Int), "", ctx // FIXME: argument type is string[]
    else ctxFreshTyVar "fun" ctx
  let serial, ctx = ctxFreshVar ctx calleeName (ValueIdent.Fun arity) funTy loc

  // FIXME: local functions are recursive by default
  let bodyCtx = ctx
  let argPats, actualFunTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
  let bodyCtx = unifyTy bodyCtx funTy actualFunTy
  let body, bodyCtx = inferExpr bodyCtx body bodyTy

  if isMonomorphic bodyCtx funTy |> not then
    failwithf "Reject polymorphic functions are not supported for now due to lack of let-polymorphism %A %A" (substTy bodyCtx funTy) argPats

  let ctx = ctxRollback ctx bodyCtx
  HExpr.LetFun (calleeName, serial, argPats, body, funTy, loc), ctx

/// Returns in reversed order.
let inferExprs ctx exprs lastTy: HExpr list * TyCtx =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      acc, ctx
    | [expr] ->
      let expr, ctx = inferExpr ctx expr lastTy
      expr :: acc, ctx
    | expr :: exprs ->
      let expr, ctx = inferExpr ctx expr tyUnit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferAndThen ctx loc exprs lastTy =
  let exprs, ctx = inferExprs ctx exprs lastTy
  hxAndThen (List.rev exprs) loc, ctx

let inferExprTyDef ctx ident tyDef loc =
  let serial, tyDef, ctx = ctx |> ctxAddTy ident tyDef loc
  HExpr.TyDef (ident, serial, tyDef, loc), ctx

let inferExpr (ctx: TyCtx) (expr: HExpr) ty: HExpr * TyCtx =
  match expr with
  | HExpr.Lit (lit, _) ->
    expr, unifyTy ctx (litTy lit) ty
  | HExpr.Ref (ident, _, _, _, loc) ->
    inferRef ctx ident loc ty
  | HExpr.Match (target, arms, _, loc) ->
    inferMatch ctx target arms loc ty
  | HExpr.Nav (receiver, field,  _,loc) ->
    inferNav ctx receiver field loc ty
  | HExpr.Op (op, l, r, _, loc) ->
    inferOp ctx op l r loc ty
  | HExpr.Inf (InfOp.List _, [], _, loc) ->
    inferNil ctx loc ty
  | HExpr.Inf (InfOp.Tuple, items, _, loc) ->
    inferTuple ctx items loc ty
  | HExpr.Inf (InfOp.Anno, [expr], annoTy, _) ->
    inferAnno ctx expr annoTy ty
  | HExpr.Inf (InfOp.AndThen, exprs, _, loc) ->
    inferAndThen ctx loc exprs ty
  | HExpr.Let (pat, body, loc) ->
    inferLetVal ctx pat body loc
  | HExpr.LetFun (calleeName, _, args, body, _, loc) ->
    inferLetFun ctx calleeName args body loc
  | HExpr.TyDef (ident, _, tyDef, loc) ->
    inferExprTyDef ctx ident tyDef loc
  | HExpr.If _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Fun _, _, _, _)
  | HExpr.Inf (InfOp.Exec, _, _, _)
  | HExpr.Inf (InfOp.Call, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

/// Replaces type vars embedded in exprs
/// with inference results.
let substTyExpr ctx expr =
  let subst ty =
    match substTy ctx ty with
    | Ty.Var _ ->
      failwithf "Couldn't determine type %A" ty
    | ty ->
      ty
  exprMap subst id expr

let infer (exprs: HExpr list): HExpr list * TyCtx =
  let ctx =
    {
      VarSerial = 0
      Vars = Map.empty
      VarEnv = Map.empty
      TySerial = 0
      TyEnv = Map.empty
      Tys = Map.empty
    }

  let exprs, ctx = inferExprs ctx exprs tyUnit

  // Substitute all types.
  let exprs = List.map (substTyExpr ctx) (List.rev exprs)

  let ctx =
    let vars =
      ctx.Vars |> Map.map (fun _ (ident, valueIdent, ty, loc) ->
        let ty = substTy ctx ty
        ident, valueIdent, ty, loc
      )
    { ctx with Vars = vars }

  exprs, ctx
