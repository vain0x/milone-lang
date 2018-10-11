module rec MiloneLang.Typing

open System
open MiloneLang

type TyCtx =
  {
    VarSerial: int
    VarEnv: Map<string, Ty>
    TySerial: int
    TyEnv: Map<string, Ty>
  }

let tyFun s t =
  Ty.Fun (s, t)

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let rollback bctx dctx =
  assert (bctx.VarSerial <= dctx.VarSerial)
  assert (bctx.TySerial <= dctx.TySerial)
  { bctx with
      VarSerial = dctx.VarSerial
      TySerial = dctx.TySerial
  }

let freshTyVar name (ctx: TyCtx) =
  let serial = ctx.TySerial + 1
  let ctx = { ctx with TySerial = ctx.TySerial + 1 }
  let name = sprintf "'%s_%d" name serial
  name, ctx

let resolveTyVar name (ctx: TyCtx) =
  match ctx.TyEnv |> Map.tryFind name with
  | Some ty ->
    ty
  | None ->
    Ty.Var name

let freshVar ident (ctx: TyCtx) =
  let tyVar, ctx = freshTyVar ident ctx
  let ty = Ty.Var tyVar
  let ctx = { ctx with VarEnv = ctx.VarEnv |> Map.add ident ty }
  ident, ty, ctx

/// Gets if the specified type var doesn't appear in the specified type.
let isFreshTyVar ty tyVar =
  let rec go ty =
    match ty with
    | Ty.Unit
    | Ty.Int
    | Ty.Str ->
      true
    | Ty.Fun (sty, tty) ->
      go sty && go tty
    | Ty.Var tv ->
      tv <> tyVar
  go ty

/// Adds type-var/type binding.
let bindTy (ctx: TyCtx) tyVar ty =
  // Don't bind itself.
  if substTy ctx ty = Ty.Var tyVar then
    ctx
  else
    { ctx with TyEnv = ctx.TyEnv |> Map.add tyVar ty }

/// Substitutes occurrances of already-infered type vars
/// with their results.
let substTy (ctx: TyCtx) ty =
  let rec go ty =
    match ty with
    | Ty.Unit
    | Ty.Int
    | Ty.Str ->
      ty
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Var tyVar ->
      let ty2 = resolveTyVar tyVar ctx
      if ty = ty2 then ty else go ty2
  go ty

/// Resolves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let unifyTy (ctx: TyCtx) lty rty =
  let rec go lty rty ctx =
    match substTy ctx lty, substTy ctx rty with
    | Ty.Var ltv, Ty.Var rtv when ltv = rtv ->
      bindTy ctx ltv rty
    | Ty.Var ltv, _ when isFreshTyVar rty ltv ->
      bindTy ctx ltv rty
    | _, Ty.Var _ ->
      go rty lty ctx
    | Ty.Fun (lsty, ltty), Ty.Fun (rsty, rtty) ->
      ctx |> go lsty rsty |> go ltty rtty
    | Ty.Unit, Ty.Unit
    | Ty.Int, Ty.Int
    | Ty.Str, Ty.Str ->
      ctx
    | Ty.Var _, _ ->
      failwithf "Couldn't unify (due to self recursion) %A %A" lty rty
    | Ty.Unit, _
    | Ty.Int _, _
    | Ty.Str _, _
    | Ty.Fun _, _ ->
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let inferRef (ctx: TyCtx) ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | Some ty ->
    Expr.Ref ident, ty, ctx
  | None ->
    failwithf "Couldn't resolve var %s" ident

let inferApp (ctx: TyCtx) callee arg =
  let arg, argTy, ctx = inferExpr ctx arg
  let callee, calleeTy, ctx = inferExpr ctx callee
  let appTyVar, ctx = freshTyVar "a" ctx
  let appTy = Ty.Var appTyVar
  let ctx = unifyTy ctx calleeTy (Ty.Fun(argTy, appTy))
  Expr.Call (callee, [arg]), appTy, ctx

let inferAdd (ctx: TyCtx) lexpr rexpr =
  let lexpr, _lty, ctx = inferExpr ctx lexpr
  let rexpr, _rty, ctx = inferExpr ctx rexpr
  // FIXME: impl
  Expr.Add (lexpr, rexpr), Ty.Int, ctx

let inferLet ctx name init =
  let name, ty, ctx = freshVar name ctx
  let init, tyInit, initCtx = inferExpr ctx init
  let ctx = rollback ctx initCtx
  let ctx = unifyTy ctx tyInit ty
  Expr.Let (name, init), Ty.Unit, ctx

let inferExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, Ty.Unit, ctx
    | [expr] ->
      let expr, ty, ctx = inferExpr ctx expr
      List.rev (expr :: acc), ty, ctx
    | expr :: exprs ->
      let expr, ty, ctx = inferExpr ctx expr
      let ctx = unifyTy ctx ty Ty.Unit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferBlock ctx exprs =
  let exprs, ty, ctx = inferExprs ctx exprs
  Expr.Begin exprs, ty, ctx

let inferExpr ctx expr =
  match expr with
  | Expr.Unit ->
    expr, Ty.Unit, ctx
  | Expr.Int _ ->
    expr, Ty.Int, ctx
  | Expr.String _ ->
    expr, Ty.Str, ctx
  | Expr.Prim PrimFun.Printfn ->
    expr, tyFun Ty.Str Ty.Unit, ctx
  | Expr.Ref ident ->
    inferRef ctx ident
  | Expr.Call (callee, [arg]) ->
    inferApp ctx callee arg
  | Expr.Add (l, r) ->
    inferAdd ctx l r
  | Expr.Let (name, init) ->
    inferLet ctx name init
  | Expr.Begin exprs ->
    let exprs, ty, ctx = inferExprs ctx exprs
    Expr.Begin exprs, ty, ctx
  | Expr.Call _ ->
    failwith "unimpl"

let infer (exprs: Expr list): Expr list * TyCtx =
  let ctx =
    {
      VarSerial = 0
      VarEnv = Map.empty
      TySerial = 0
      TyEnv = Map.empty
    }
  let exprs, _, ctx = inferExprs ctx exprs
  exprs, ctx
