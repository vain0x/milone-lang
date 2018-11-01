module rec MiloneLang.Typing

open System
open MiloneLang

type TyCtx =
  {
    VarSerial: int
    /// Identifier serial number to human readable name.
    VarName: Map<int, string>
    /// Identifier to type and serial.
    VarEnv: Map<string, Ty * int>
    TySerial: int
    TyEnv: Map<string, Ty>
  }

let patTy (pat: Pat<Loc>): Ty =
  let ty, _ = Parsing.patExtract pat
  ty

let tyOf (expr: Expr< Loc>): Ty =
  let ty, _ = Parsing.exprExtract expr
  ty

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let rollback bCtx dCtx: TyCtx =
  assert (bCtx.VarSerial <= dCtx.VarSerial)
  assert (bCtx.TySerial <= dCtx.TySerial)
  { dCtx with
      VarEnv = bCtx.VarEnv
  }

let freshTyVar ident (ctx: TyCtx): Ty * string * TyCtx =
  let serial = ctx.TySerial + 1
  let ctx = { ctx with TySerial = ctx.TySerial + 1 }
  let ident = sprintf "'%s_%d" ident serial
  let ty = Ty.Var ident
  ty, ident, ctx

let resolveTyVar name (ctx: TyCtx): Ty =
  match ctx.TyEnv |> Map.tryFind name with
  | Some ty ->
    ty
  | None ->
    Ty.Var name

let freshVar (ctx: TyCtx) ident ty: int * TyCtx =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarEnv = ctx.VarEnv |> Map.add ident (ty, serial)
        VarName = ctx.VarName |> Map.add serial ident
    }
  serial, ctx

/// Gets if the specified type var doesn't appear in the specified type.
let isFreshTyVar ty tyVar: bool =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Unit
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Box
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
  | Ty.Unit
  | Ty.Bool
  | Ty.Int
  | Ty.Char
  | Ty.Str
  | Ty.Box
  | Ty.Tuple [] ->
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
    | Ty.Unit
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Box
    | Ty.Str ->
      ty
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Tuple itemTys ->
      Ty.Tuple (List.map go itemTys)
    | Ty.List ty ->
      Ty.List (go ty)
    | Ty.Var tyVar ->
      let ty2 = resolveTyVar tyVar ctx
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
    | Ty.Unit, Ty.Unit
    | Ty.Bool, Ty.Bool
    | Ty.Int, Ty.Int
    | Ty.Char, Ty.Char
    | Ty.Str, Ty.Str
    | Ty.Box, Ty.Box ->
      ctx
    | Ty.Var _, _ ->
      failwithf "Couldn't unify (due to self recursion) %A %A" lty rty
    | Ty.Unit, _
    | Ty.Bool, _
    | Ty.Int, _
    | Ty.Char, _
    | Ty.Str, _
    | Ty.Box, _
    | Ty.Fun _, _
    | Ty.Tuple _, _
    | Ty.List _, _ ->
      let lty, rty = substTy ctx lty, substTy ctx rty
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let inferPatTuple ctx itemPats loc tupleTy =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] ->
      List.rev accPats, List.rev accTys, ctx
    | itemPat :: itemPats ->
      let itemTy, _, ctx = freshTyVar "item" ctx
      let itemPat, ctx = inferPat ctx itemPat itemTy
      go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats
  let itemPats, itemTys, ctx = go [] [] ctx itemPats
  let ctx = unifyTy ctx tupleTy (Ty.Tuple itemTys)
  Pat.Tuple (itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, _, ctx = freshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  Pat.Cons (l, r, itemTy, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | Pat.Unit _ ->
    pat, unifyTy ctx ty Ty.Unit
  | Pat.Value (value, _) ->
    pat, unifyTy ctx ty (Parsing.valueTy value)
  | Pat.Nil (_, loc) ->
    let itemTy, _, ctx = freshTyVar "item" ctx
    let ctx = unifyTy ctx ty (Ty.List itemTy)
    Pat.Nil (itemTy, loc), ctx
  | Pat.Ident (ident, _, _, loc) ->
    let serial, ctx = freshVar ctx ident ty
    Pat.Ident (ident, serial, ty, loc), ctx
  | Pat.Cons (l, r, _, loc) ->
    inferPatCons ctx l r loc ty
  | Pat.Tuple (items, _, loc) ->
    inferPatTuple ctx items loc ty
  | Pat.Anno (pat, annoTy, _) ->
    let ctx = unifyTy ctx ty annoTy
    let pat, ctx = inferPat ctx pat annoTy
    pat, ctx

let inferPrimBox ctx loc ty =
  let argTy, _, ctx = freshTyVar "box" ctx
  let ctx = unifyTy ctx (Ty.Fun (argTy, Ty.Box)) ty
  Expr.Prim (PrimFun.Box, ty, loc), ctx

let inferPrimUnbox ctx loc ty =
  let resultTy, _, ctx = freshTyVar "unbox" ctx
  let ctx = unifyTy ctx (Ty.Fun (Ty.Box, resultTy)) ty
  Expr.Prim (PrimFun.Unbox, ty, loc), ctx

let inferRef (ctx: TyCtx) ident loc ty =
  match ctx.VarEnv |> Map.tryFind ident with
  | Some (refTy, serial) ->
    let ctx = unifyTy ctx refTy ty
    Expr.Ref (ident, serial, ty, loc), ctx
  | None ->
    failwithf "Couldn't resolve var %s" ident

let inferList ctx items loc listTy =
  let itemTy, _, ctx = freshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  let rec go acc ctx items =
    match items with
    | [] -> List.rev acc, ctx
    | item :: items ->
      let item, ctx = inferExpr ctx item itemTy
      go (item :: acc) ctx items
  let items, ctx = go [] ctx items
  Expr.List (items, itemTy, loc), ctx

/// if bool then 'a else 'a
let inferIf ctx pred thenCl elseCl loc resultTy =
  let pred, ctx = inferExpr ctx pred Ty.Bool
  let thenCl, ctx = inferExpr ctx thenCl resultTy
  let elseCl, ctx = inferExpr ctx elseCl resultTy
  Expr.If (pred, thenCl, elseCl, resultTy, loc), ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target (pat1, body1) (pat2, body2) loc resultTy =
  let targetTy, _, ctx = freshTyVar "target" ctx
  let target, ctx = inferExpr ctx target targetTy

  // arm1
  let pat1, ctx = inferPat ctx pat1 targetTy
  let body1, ctx = inferExpr ctx body1 resultTy

  // arm2
  let pat2, ctx = inferPat ctx pat2 targetTy
  let body2, ctx = inferExpr ctx body2 resultTy

  Expr.Match (target, (pat1, body1), (pat2, body2), resultTy, loc), ctx

let inferNav ctx sub mes loc resultTy =
  let subTy, _, ctx = freshTyVar "sub" ctx
  let sub, ctx = inferExpr ctx sub subTy
  match substTy ctx subTy, mes with
  | Ty.Str, "Length" ->
    let ctx = unifyTy ctx resultTy Ty.Int
    Expr.Nav (sub, mes, Ty.Int, loc), ctx
  | _ ->
    failwithf "Unknown nav %A" (sub, mes, loc)

/// `x.[i] : 'y` <== x : 'x, i : int
/// NOTE: Currently only the `x : string` case can compile, however,
/// we don't infer that for compatibility.
let inferIndex ctx l r loc resultTy =
  let subTy, _, ctx = freshTyVar "sub" ctx
  let l, ctx = inferExpr ctx l subTy
  let r, ctx = inferExpr ctx r Ty.Int
  match substTy ctx subTy with
  | Ty.Str ->
    let ctx = unifyTy ctx resultTy Ty.Char
    Expr.Index (l, r, resultTy, loc), ctx
  | subTy ->
    failwithf "Type: Index not supported %A" (subTy, l, r)

/// During inference of `f w x ..`,
/// assume we concluded `f w : 'f`.
/// We can also conclude `f w : 'x -> 'g`.
let rec inferAppArgs acc (ctx: TyCtx) args callTy =
  match args with
  | [] ->
    acc, callTy, ctx
  | arg :: args ->
    let argTy, _, ctx = freshTyVar "arg" ctx
    let arg, ctx = inferExpr ctx arg argTy
    inferAppArgs (arg :: acc) ctx args (Ty.Fun (argTy, callTy))

let inferApp (ctx: TyCtx) callee args loc callTy =
  let args, calleeTy, ctx = inferAppArgs [] ctx (List.rev args) callTy
  let callee, ctx = inferExpr ctx callee calleeTy
  Expr.Call (callee, args, callTy, loc), ctx

let inferAppExit ctx calleeLoc arg callLoc callTy =
  let arg, ctx = inferExpr ctx arg Ty.Int
  let funTy = Ty.Fun (Ty.Int, callTy)
  let callee = Expr.Prim (PrimFun.Exit, funTy, calleeLoc)
  Expr.Call (callee, [arg], callTy, callLoc), ctx

let inferAppPrintfn ctx args loc callTy =
  match args with
  | Expr.Value (Value.Str format, _) :: _ ->
    let ctx = unifyTy ctx callTy Ty.Unit
    let funTy =
      // FIXME: too rough
      if format.Contains("%s") then
        Ty.Fun (Ty.Str, Ty.Fun (Ty.Str, Ty.Unit))
      else if format.Contains("%d") then
        Ty.Fun (Ty.Str, Ty.Fun (Ty.Int, Ty.Unit))
      else
        Ty.Fun (Ty.Str, Ty.Unit)
    let args, calleeTy, ctx = inferAppArgs [] ctx (List.rev args) callTy
    let ctx = unifyTy ctx calleeTy funTy
    let callee = Expr.Prim (PrimFun.Printfn, calleeTy, loc)
    Expr.Call (callee, args, callTy, loc), ctx
  | _ ->
    failwith """First arg of printfn must be string literal, ".."."""

let inferOpCore (ctx: TyCtx) op left right loc operandTy resultTy =
  let left, ctx = inferExpr ctx left operandTy
  let right, ctx = inferExpr ctx right operandTy
  Expr.Op (op, left, right, resultTy, loc), ctx

let inferOpAdd (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = freshTyVar "operand" ctx
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
  let operandTy, _, ctx = freshTyVar "operand" ctx
  let ctx = unifyTy ctx resultTy Ty.Bool
  inferOpCore ctx op left right loc operandTy resultTy

let inferOpLogic (ctx: TyCtx) op left right loc resultTy =
  let ctx = unifyTy ctx resultTy Ty.Bool
  inferOpCore ctx op left right loc Ty.Bool Ty.Bool

let inferOpCons ctx op left right loc listTy =
  let itemTy, _, ctx = freshTyVar "item" ctx
  let ctx = unifyTy ctx listTy (Ty.List itemTy)
  let left, ctx = inferExpr ctx left itemTy
  let right, ctx = inferExpr ctx right listTy
  Expr.Op (op, left, right, listTy, loc), ctx

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
  | Op.And
  | Op.Or ->
    inferOpLogic ctx op left right loc ty
  | Op.Cons ->
    inferOpCons ctx op left right loc ty

let inferTuple (ctx: TyCtx) items loc tupleTy =
  let rec go acc itemTys ctx items =
    match items with
    | [] ->
      List.rev acc, List.rev itemTys, ctx
    | item :: items ->
      let itemTy, _, ctx = freshTyVar "item" ctx
      let item, ctx = inferExpr ctx item itemTy
      go (item :: acc) (itemTy :: itemTys) ctx items
  let items, itemTys, ctx = go [] [] ctx items
  let ctx = unifyTy ctx tupleTy (Ty.Tuple itemTys)
  Expr.Tuple (items, tupleTy, loc), ctx

let inferAnno ctx expr annoTy ty =
  let ctx = unifyTy ctx annoTy ty
  inferExpr ctx expr annoTy

let inferLetVal ctx pat init loc unitTy =
  let ctx = unifyTy ctx unitTy Ty.Unit
  let initTy, _, ctx = freshTyVar "init" ctx
  // Type init expression.
  let init, initCtx = inferExpr ctx init initTy
  // Remove symbols defined inside `init`.
  let ctx = rollback ctx initCtx
  // Define new variables defined by the pat to the context.
  let pat, ctx = inferPat ctx pat initTy
  Expr.Let ([pat], init, loc), ctx

let inferLetFun ctx calleePat argPats body loc unitTy =
  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx bodyTy argPats =
    match argPats with
    | [] ->
      [], bodyTy, ctx
    | argPat :: argPats ->
      let argTy, _, ctx = freshTyVar "arg" ctx
      let pat, ctx = inferPat ctx argPat argTy
      let pats, bodyTy, ctx = inferArgs ctx bodyTy argPats
      pat :: pats, Ty.Fun (argTy, bodyTy), ctx

  match calleePat with
  | Pat.Ident (callee, _, _, calleeLoc) ->
    let ctx = unifyTy ctx unitTy Ty.Unit
    let funTy, _, ctx =
      if callee = "main"
      then Ty.Fun (Ty.Unit, Ty.Int), "", ctx
      else freshTyVar "fun" ctx
    let bodyTy, _, ctx = freshTyVar "body" ctx
    let serial, ctx = freshVar ctx callee funTy

    // FIXME: functions cannot capture local variables
    // FIXME: local functions are recursive by default
    let bodyCtx = ctx
    let argPats, actualFunTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
    let bodyCtx = unifyTy bodyCtx funTy actualFunTy
    let body, bodyCtx = inferExpr bodyCtx body bodyTy

    if isMonomorphic bodyCtx funTy |> not then
      failwithf "Reject polymorphic functions are not supported for now due to lack of let-polymorphism %A %A" (substTy bodyCtx funTy) argPats

    let ctx = rollback ctx bodyCtx

    let calleePat = Pat.Ident (callee, serial, funTy, calleeLoc)
    Expr.Let (calleePat :: argPats, body, loc), ctx
  | _ ->
    failwith "First pattern of let with parameters must be an identifier."

/// Returns in reversed order.
let inferExprs ctx exprs lastTy: Expr<Loc> list * TyCtx =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      acc, ctx
    | [expr] ->
      let expr, ctx = inferExpr ctx expr lastTy
      expr :: acc, ctx
    | expr :: exprs ->
      let expr, ctx = inferExpr ctx expr Ty.Unit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferAndThen ctx loc exprs lastTy =
  let exprs, ctx = inferExprs ctx exprs lastTy
  Expr.AndThen (List.rev exprs, lastTy, loc), ctx

let inferExpr (ctx: TyCtx) (expr: Expr<Loc>) ty: Expr<Loc> * TyCtx =
  match expr with
  | Expr.Value (value, _) ->
    expr, unifyTy ctx (Parsing.valueTy value) ty
  | Expr.Unit _ ->
    expr, unifyTy ctx ty Ty.Unit
  | Expr.Prim (PrimFun.Box, _, loc) ->
    inferPrimBox ctx loc ty
  | Expr.Prim (PrimFun.Unbox, _, loc) ->
    inferPrimUnbox ctx loc ty
  | Expr.Ref (ident, _, _, loc) ->
    inferRef ctx ident loc ty
  | Expr.List (items, _, loc) ->
    inferList ctx items loc ty
  | Expr.If (pred, thenCl, elseCl, _, loc) ->
    inferIf ctx pred thenCl elseCl loc ty
  | Expr.Match (target, arm1, arm2, _, loc) ->
    inferMatch ctx target arm1 arm2 loc ty
  | Expr.Nav (receiver, field,  _,loc) ->
    inferNav ctx receiver field loc ty
  | Expr.Index (l, r, _, loc) ->
    inferIndex ctx l r loc ty
  | Expr.Call (Expr.Prim (PrimFun.Exit, _, calleeLoc), [arg], _, loc) ->
    inferAppExit ctx calleeLoc arg loc ty
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _, _), args, _, loc) ->
    inferAppPrintfn ctx args loc ty
  | Expr.Call (callee, args, _, loc) ->
    inferApp ctx callee args loc ty
  | Expr.Op (op, l, r, _, loc) ->
    inferOp ctx op l r loc ty
  | Expr.Tuple (items, _, loc) ->
    inferTuple ctx items loc ty
  | Expr.Anno (expr, annoTy, _) ->
    inferAnno ctx expr annoTy ty
  | Expr.AndThen (exprs, _, loc) ->
    inferAndThen ctx loc exprs ty
  | Expr.Let ([pat], init, loc) ->
    inferLetVal ctx pat init loc ty
  | Expr.Let (calleePat :: argPats, body, loc) ->
    inferLetFun ctx calleePat argPats body loc ty
  | Expr.Prim _ ->
    failwith "printfn must appear in form of `printfn format args..`."
  | Expr.Let ([], _, _) ->
    failwith "Never let with no pats"

/// Replaces type vars embedded in exprs
/// with inference results.
let substTyExpr ctx expr =
  let subst ty =
    match substTy ctx ty with
    | Ty.Var _ ->
      failwithf "Couldn't determine type %A" ty
    | ty ->
      ty
  Parsing.exprMap subst id expr

let infer (exprs: Expr<Loc> list): Expr<Loc> list * TyCtx =
  let ctx =
    {
      VarSerial = 0
      VarName = Map.empty
      VarEnv = Map.empty
      TySerial = 0
      TyEnv = Map.empty
    }

  let prims =
    [
      "not", Ty.Fun (Ty.Bool, Ty.Bool), -1
    ]
  let rec go ctx prims =
    match prims with
    | [] -> ctx
    | (ident, ty, serial) :: prims ->
      let ctx = { ctx with VarEnv = ctx.VarEnv |> Map.add ident (ty, serial) }
      go ctx prims
  let ctx = go ctx prims

  let exprs, ctx = inferExprs ctx exprs Ty.Unit

  // Substitute all types.
  let exprs = List.map (substTyExpr ctx) (List.rev exprs)
  exprs, ctx
