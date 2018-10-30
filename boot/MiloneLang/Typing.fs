module rec MiloneLang.Typing

open System
open MiloneLang

type TyExpr = Expr<Ty * Loc>

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

let patTy (pat: Pat<Ty * Loc>): Ty =
  let ty, _ = Parsing.patExtract pat
  ty

let tyOf (expr: Expr<Ty * Loc>): Ty =
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

let freshVar ident (ctx: TyCtx): string * int * Ty * TyCtx =
  let ty, _, ctx = freshTyVar ident ctx
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarEnv = ctx.VarEnv |> Map.add ident (ty, serial)
        VarName = ctx.VarName |> Map.add serial ident
    }
  ident, serial, ty, ctx

/// Gets if the specified type var doesn't appear in the specified type.
let isFreshTyVar ty tyVar: bool =
  let rec go ty =
    match ty with
    | Ty.Unit
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str ->
      true
    | Ty.Fun (sTy, tTy) ->
      go sTy && go tTy
    | Ty.Tuple (lTy, rTy) ->
      go lTy && go rTy
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
  | Ty.Str ->
    true
  | Ty.Var _ ->
    false
  | Ty.Fun (sTy, tTy) ->
    isMonomorphic ctx sTy && isMonomorphic ctx tTy
  | Ty.List ty ->
    isMonomorphic ctx ty
  | Ty.Tuple (lTy, rTy) ->
    isMonomorphic ctx lTy && isMonomorphic ctx rTy

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
    | Ty.Unit
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str ->
      ty
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Tuple (lTy, rTy) ->
      Ty.Tuple (go lTy, go rTy)
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
    | Ty.Tuple (llTy, lrTy), Ty.Tuple (rlTy, rrTy) ->
      ctx |> go llTy rlTy |> go lrTy rrTy
    | Ty.Unit, Ty.Unit
    | Ty.Bool, Ty.Bool
    | Ty.Int, Ty.Int
    | Ty.Char, Ty.Char
    | Ty.Str, Ty.Str ->
      ctx
    | Ty.Var _, _ ->
      failwithf "Couldn't unify (due to self recursion) %A %A" lty rty
    | Ty.Unit, _
    | Ty.Bool, _
    | Ty.Int, _
    | Ty.Char, _
    | Ty.Str, _
    | Ty.Fun _, _
    | Ty.Tuple _, _
    | Ty.List _, _ ->
      let lty, rty = substTy ctx lty, substTy ctx rty
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let inferPatCons ctx l r loc =
  let itemTy, _, ctx = freshTyVar "cons" ctx
  let listTy = Ty.List itemTy
  let l, ctx = inferPat ctx l
  let ctx = unifyTy ctx (patTy l) itemTy
  let r, ctx = inferPat ctx r
  let ctx = unifyTy ctx (patTy r) listTy
  Pat.Cons (l, r, (listTy, loc)), ctx

let inferPat ctx pat =
  match pat with
  | Pat.Unit loc ->
    Pat.Unit (Ty.Unit, loc), ctx
  | Pat.Int (value, loc) ->
    Pat.Int (value, (Ty.Int, loc)), ctx
  | Pat.Nil loc ->
    let ty, _, ctx = freshTyVar "nil" ctx
    Pat.Nil (ty, loc), ctx
  | Pat.Ident (ident, _, loc) ->
    let ident, serial, ty, ctx = freshVar ident ctx
    Pat.Ident (ident, serial, (ty, loc)), ctx
  | Pat.Cons (l, r, loc) ->
    inferPatCons ctx l r loc
  | Pat.Tuple (l, r, loc) ->
    let l, ctx = inferPat ctx l
    let r, ctx = inferPat ctx r
    let tupleTy = Ty.Tuple (patTy l, patTy r)
    Pat.Tuple (l, r, (tupleTy, loc)), ctx
  | Pat.Anno (pat, ty, _) ->
    let pat, ctx = inferPat ctx pat
    let ctx = unifyTy ctx (patTy pat) ty
    pat, ctx

let inferRef (ctx: TyCtx) loc ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | Some (ty, serial) ->
    Expr.Ref (ident, serial, (ty, loc)), ctx
  | None ->
    failwithf "Couldn't resolve var %s" ident

let inferList ctx items loc =
  let itemTy, _, ctx = freshTyVar "item" ctx
  let rec go acc ctx items =
    match items with
    | [] -> List.rev acc, ctx
    | item :: items ->
      let item, ctx = inferExpr ctx item
      let ctx = unifyTy ctx (tyOf item) itemTy
      go (item :: acc) ctx items
  let items, ctx = go [] ctx items
  Expr.List (items, (Ty.List itemTy, loc)), ctx

/// if bool then 'a else 'a
let inferIf ctx pred thenCl elseCl loc =
  let pred, ctx = inferExpr ctx pred
  let thenCl, ctx = inferExpr ctx thenCl
  let elseCl, ctx = inferExpr ctx elseCl
  let ty = tyOf thenCl
  let ctx = unifyTy ctx (tyOf pred) Ty.Bool
  let ctx = unifyTy ctx ty (tyOf elseCl)
  Expr.If (pred, thenCl, elseCl, (ty, loc)), ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target (pat1, body1) (pat2, body2) loc =
  let target, ctx = inferExpr ctx target

  // arm1
  let pat1, ctx = inferPat ctx pat1
  let body1, ctx = inferExpr ctx body1
  let ctx = unifyTy ctx (tyOf target) (patTy pat1)

  // arm2
  let pat2, ctx = inferPat ctx pat2
  let body2, ctx = inferExpr ctx body2
  let ctx = unifyTy ctx (tyOf target) (patTy pat2)
  let ctx = unifyTy ctx (tyOf body1) (tyOf body2)

  Expr.Match (target, (pat1, body1), (pat2, body2), (tyOf body1, loc)), ctx

let inferNav ctx sub mes loc =
  let sub, ctx = inferExpr ctx sub
  match substTy ctx (tyOf sub), mes with
  | Ty.Str, "Length" ->
    Expr.Nav (sub, mes, (Ty.Int, loc)), ctx
  | _ ->
    failwithf "Unknown nav %A" (sub, mes, loc)

/// `x.[i] : 'y` <== x : 'x, i : int
/// NOTE: Currently only the `x : string` case can compile, however,
/// we don't infer that for compatibility.
let inferIndex ctx l r loc =
  let ty, _, ctx = freshTyVar "app" ctx
  let l, ctx = inferExpr ctx l
  let r, ctx = inferExpr ctx r
  let ctx = unifyTy ctx (tyOf r) Ty.Int
  Expr.Index (l, r, (ty, loc)), ctx

/// During inference of `f w x ..`,
/// assume we concluded `f w : 'f`.
/// We can also conclude `f w : 'x -> 'g`.
let rec inferAppArgs acc (ctx: TyCtx) calleeTy args =
  match args with
  | [] ->
    List.rev acc, calleeTy, ctx
  | arg :: args ->
    let appTy, _, ctx = freshTyVar "app" ctx
    let arg, ctx = inferExpr ctx arg
    let ctx = unifyTy ctx calleeTy (Ty.Fun (tyOf arg, appTy))
    inferAppArgs (arg :: acc) ctx appTy args

let inferApp (ctx: TyCtx) loc callee args =
  let callee, ctx = inferExpr ctx callee
  let args, appTy, ctx = inferAppArgs [] ctx (tyOf callee) args
  Expr.Call (callee, args, (appTy, loc)), ctx

let inferAppExit ctx calleeLoc arg callLoc =
  let arg, ctx = inferExpr ctx arg
  let ctx = unifyTy ctx (tyOf arg) (Ty.Int)
  let resultTy, _, ctx = freshTyVar "exit" ctx
  let funTy = Ty.Fun (Ty.Int, resultTy)
  let callee = Expr.Prim (PrimFun.Exit, (funTy, calleeLoc))
  Expr.Call (callee, [arg], (resultTy, callLoc)), ctx

let inferAppPrintfn ctx loc args =
  match args with
  | [] -> failwith "Never"
  | Expr.Str (format, _) :: _ ->
    let calleeTy =
      // FIXME: too rough
      if format.Contains("%s") then
        Ty.Fun (Ty.Str, Ty.Fun (Ty.Str, Ty.Unit))
      else if format.Contains("%d") then
        Ty.Fun (Ty.Str, Ty.Fun (Ty.Int, Ty.Unit))
      else Ty.Fun (Ty.Str, Ty.Unit)
    let args, appTy, ctx = inferAppArgs [] ctx calleeTy args
    let callee = Expr.Prim (PrimFun.Printfn, (calleeTy, loc))
    Expr.Call (callee, args, (appTy, loc)), ctx
  | _ ->
    failwith """First arg of printfn must be string literal, ".."."""

let inferOpCore (ctx: TyCtx) loc op left right =
  let left, ctx = inferExpr ctx left
  let right, ctx = inferExpr ctx right

  // Infer types so that left and right are of the same type.
  let resultTy, _, ctx = freshTyVar "op" ctx
  let lTy, rTy = tyOf left, tyOf right
  let ctx = unifyTy ctx lTy rTy

  left, Expr.Op (op, left, right, (resultTy, loc)), ctx

let inferOpAdd (ctx: TyCtx) loc op left right =
  let left, expr, ctx = inferOpCore ctx loc op left right
  let ctx = unifyTy ctx (tyOf left) (tyOf expr)
  expr, ctx

let inferOpArith (ctx: TyCtx) loc op left right =
  let left, expr, ctx = inferOpCore ctx loc op left right
  let ctx = unifyTy ctx (tyOf left) Ty.Int
  let ctx = unifyTy ctx (tyOf expr) Ty.Int
  expr, ctx

let inferOpCmp (ctx: TyCtx) loc op left right =
  let _, expr, ctx = inferOpCore ctx loc op left right
  let ctx = unifyTy ctx (tyOf expr) Ty.Bool
  expr, ctx

let inferOpLogic (ctx: TyCtx) loc op left right =
  let left, expr, ctx = inferOpCore ctx loc op left right
  let ctx = unifyTy ctx (tyOf left) Ty.Bool
  let ctx = unifyTy ctx (tyOf expr) Ty.Bool
  expr, ctx

let inferOpCons ctx loc op left right =
  let itemTy, _, ctx = freshTyVar "list" ctx
  let listTy = Ty.List itemTy
  let left, ctx = inferExpr ctx left
  let ctx = unifyTy ctx (tyOf left) itemTy
  let right, ctx = inferExpr ctx right
  let ctx = unifyTy ctx (tyOf right) listTy
  Expr.Op (op, left, right, (listTy, loc)), ctx

let inferOpTie (ctx: TyCtx) loc op left right =
  let left, ctx = inferExpr ctx left
  let right, ctx = inferExpr ctx right
  let tupleTy = Ty.Tuple (tyOf left, tyOf right)
  Expr.Op (op, left, right, (tupleTy, loc)), ctx

let inferOp (ctx: TyCtx) loc op left right =
  match op with
  | Op.Add ->
    inferOpAdd ctx loc op left right
  | Op.Sub
  | Op.Mul
  | Op.Div
  | Op.Mod ->
    inferOpArith ctx loc op left right
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le
  | Op.Gt
  | Op.Ge ->
    inferOpCmp ctx loc op left right
  | Op.And
  | Op.Or ->
    inferOpLogic ctx loc op left right
  | Op.Cons ->
    inferOpCons ctx loc op left right
  | Op.Tie ->
    inferOpTie ctx loc op left right

let inferAnno ctx expr ty =
  let expr, ctx = inferExpr ctx expr
  let ctx = unifyTy ctx (tyOf expr) ty
  expr, ctx

let inferLetVal ctx pat init loc =
  // Define new variables defined by the pat to the context.
  let pat, ctx = inferPat ctx pat
  // Type init expression.
  let init, initCtx = inferExpr ctx init
  // Remove symbols defined inside `init`.
  let ctx = rollback ctx initCtx
  let ctx = unifyTy ctx (patTy pat) (tyOf init)
  Expr.Let ([pat], init, (Ty.Unit, loc)), ctx

let inferLetFun ctx pat pats body loc =
  /// Infer argument patterns.
  /// Infer each pattern from last to the first, building function type.
  /// Like this: { f x y : 'z } -> { f x : (y : 'y) -> 'z }
  let inferArgs ctx ty pats =
    let rec go acc ty ctx pats =
      match pats with
      | [] ->
        acc, ty, ctx
      | pat :: pats ->
        let pat, ctx = inferPat ctx pat
        let ty = Ty.Fun (patTy pat, ty)
        go (pat :: acc) ty ctx pats
    go [] ty ctx (List.rev pats)

  match pat, pats with
  | Pat.Ident (callee, _, calleeLoc), argPats ->
    let callee, serial, calleeTy, ctx = freshVar callee ctx
    let bodyTy, _, ctx = freshTyVar "body" ctx
    let calleePat = Pat.Ident (callee, serial, (calleeTy, calleeLoc))

    let ctx =
      if callee <> "main" then ctx else
        unifyTy ctx calleeTy (Ty.Fun (Ty.Unit, Ty.Int))

    // FIXME: functions cannot capture local variables
    // FIXME: local functions are recursive by default
    let bodyCtx = ctx
    let argPats, funTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
    let body, bodyCtx = inferExpr bodyCtx body
    let bodyCtx = unifyTy bodyCtx (tyOf body) bodyTy
    let bodyCtx = unifyTy bodyCtx calleeTy funTy

    if argPats |> List.forall (fun pat -> isMonomorphic bodyCtx (patTy pat)) |> not then
      failwithf "Reject polymorphic functions are not supported for now due to lack of let-polymorphism %A" argPats

    let ctx = rollback ctx bodyCtx

    Expr.Let (calleePat :: argPats, body, (Ty.Unit, loc)), ctx
  | _ ->
    failwith "unimpl use of let"

/// Returns in reversed order.
let inferExprs ctx exprs: Expr<Ty * Loc> list * Ty * TyCtx =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      acc, Ty.Unit, ctx
    | [expr] ->
      let expr, ctx = inferExpr ctx expr
      expr :: acc, tyOf expr, ctx
    | expr :: exprs ->
      let expr, ctx = inferExpr ctx expr
      let ctx = unifyTy ctx (tyOf expr) Ty.Unit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferAndThen ctx loc exprs =
  let exprs, ty, ctx = inferExprs ctx exprs
  Expr.AndThen (List.rev exprs, (ty, loc)), ctx

let inferExpr (ctx: TyCtx) (expr: Expr<Loc>): Expr<Ty * Loc> * TyCtx =
  match expr with
  | Expr.Unit loc ->
    Expr.Unit (Ty.Unit, loc), ctx
  | Expr.Bool (value, loc) ->
    Expr.Bool (value, (Ty.Bool, loc)), ctx
  | Expr.Int (value, loc) ->
    Expr.Int (value, (Ty.Int, loc)), ctx
  | Expr.Char (value, loc) ->
    Expr.Char (value, (Ty.Char, loc)), ctx
  | Expr.Str (value, loc) ->
    Expr.Str (value, (Ty.Str, loc)), ctx
  | Expr.Ref (ident, _, loc) ->
    inferRef ctx loc ident
  | Expr.List (items, loc) ->
    inferList ctx items loc
  | Expr.If (pred, thenCl, elseCl, loc) ->
    inferIf ctx pred thenCl elseCl loc
  | Expr.Match (target, arm1, arm2, loc) ->
    inferMatch ctx target arm1 arm2 loc
  | Expr.Nav (receiver, field, loc) ->
    inferNav ctx receiver field loc
  | Expr.Index (l, r, loc) ->
    inferIndex ctx l r loc
  | Expr.Call (Expr.Prim (PrimFun.Exit, calleeLoc), [arg], loc) ->
    inferAppExit ctx calleeLoc arg loc
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _), args, loc) ->
    inferAppPrintfn ctx loc args
  | Expr.Call (callee, args, loc) ->
    inferApp ctx loc callee args
  | Expr.Op (op, l, r, loc) ->
    inferOp ctx loc op l r
  | Expr.Anno (expr, ty, _) ->
    inferAnno ctx expr ty
  | Expr.AndThen (exprs, loc) ->
    inferAndThen ctx loc exprs
  | Expr.Let ([pat], init, loc) ->
    inferLetVal ctx pat init loc
  | Expr.Let (pat :: pats, body, loc) ->
    inferLetFun ctx pat pats body loc
  | Expr.Prim _ ->
    failwith "printfn must appear in form of `printfn format args..`."
  | Expr.Let ([], _, _) ->
    failwith "Never let with no pats"

/// Replaces type vars embedded in exprs
/// with inference results.
let substTyExpr ctx expr =
  let subst (ty, loc) =
    match substTy ctx ty with
    | Ty.Var _ ->
      failwithf "Couldn't determine type %A" ty
    | ty ->
      ty, loc
  Parsing.exprMap subst expr

let infer (exprs: Expr<Loc> list): Expr<Ty * Loc> list * TyCtx =
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

  let exprs, _, ctx = inferExprs ctx exprs

  // Substitute all types.
  let exprs = List.map (substTyExpr ctx) (List.rev exprs)
  exprs, ctx
