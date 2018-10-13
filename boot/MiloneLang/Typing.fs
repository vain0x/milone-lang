module rec MiloneLang.Typing

open System
open MiloneLang

type TyExpr = Expr<Ty * Loc>

type TyCtx =
  {
    VarSerial: int
    VarEnv: Map<string, Ty>
    TySerial: int
    TyEnv: Map<string, Ty>
  }

let tyFun s t =
  Ty.Fun (s, t)

let tyOf (expr: Expr<Ty * Loc>): Ty =
  let ty, _ = Parsing.exprExtract expr
  ty

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let rollback bctx dctx: TyCtx =
  assert (bctx.VarSerial <= dctx.VarSerial)
  assert (bctx.TySerial <= dctx.TySerial)
  { dctx with
      VarEnv = dctx.VarEnv
  }

let freshTyVar name (ctx: TyCtx): string * TyCtx =
  let serial = ctx.TySerial + 1
  let ctx = { ctx with TySerial = ctx.TySerial + 1 }
  let name = sprintf "'%s_%d" name serial
  name, ctx

let resolveTyVar name (ctx: TyCtx): Ty =
  match ctx.TyEnv |> Map.tryFind name with
  | Some ty ->
    ty
  | None ->
    Ty.Var name

let freshVar ident (ctx: TyCtx): string * Ty * TyCtx =
  let tyVar, ctx = freshTyVar ident ctx
  let ty = Ty.Var tyVar
  let ctx = { ctx with VarEnv = ctx.VarEnv |> Map.add ident ty }
  ident, ty, ctx

/// Gets if the specified type var doesn't appear in the specified type.
let isFreshTyVar ty tyVar: bool =
  let rec go ty =
    match ty with
    | Ty.Unit
    | Ty.Bool
    | Ty.Int
    | Ty.Str ->
      true
    | Ty.Fun (sty, tty) ->
      go sty && go tty
    | Ty.Var tv ->
      tv <> tyVar
  go ty

/// Adds type-var/type binding.
let bindTy (ctx: TyCtx) tyVar ty: TyCtx =
  // Don't bind itself.
  if substTy ctx ty = Ty.Var tyVar then
    ctx
  else
    { ctx with TyEnv = ctx.TyEnv |> Map.add tyVar ty }

/// Substitutes occurrances of already-infered type vars
/// with their results.
let substTy (ctx: TyCtx) ty: Ty =
  let rec go ty =
    match ty with
    | Ty.Unit
    | Ty.Bool
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
let unifyTy (ctx: TyCtx) (lty: Ty) (rty: Ty): TyCtx =
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
    | Ty.Bool, Ty.Bool
    | Ty.Int, Ty.Int
    | Ty.Str, Ty.Str ->
      ctx
    | Ty.Var _, _ ->
      failwithf "Couldn't unify (due to self recursion) %A %A" lty rty
    | Ty.Unit, _
    | Ty.Bool, _
    | Ty.Int _, _
    | Ty.Str _, _
    | Ty.Fun _, _ ->
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let inferRef (ctx: TyCtx) loc ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | Some ty ->
    Expr.Ref (ident, (ty, loc)), ctx
  | None ->
    failwithf "Couldn't resolve var %s" ident

/// if bool then 'a else 'a
let inferIf ctx pred thenCl elseCl loc =
  let pred, ctx = inferExpr ctx pred
  let thenCl, ctx = inferExpr ctx thenCl
  let elseCl, ctx = inferExpr ctx elseCl
  let ty = tyOf thenCl
  let ctx = unifyTy ctx (tyOf pred) Ty.Bool
  let ctx = unifyTy ctx ty (tyOf elseCl)
  Expr.If (pred, thenCl, elseCl, (ty, loc)), ctx

let inferApp (ctx: TyCtx) loc callee arg =
  let arg, ctx = inferExpr ctx arg
  let callee, ctx = inferExpr ctx callee
  let appTyVar, ctx = freshTyVar "a" ctx
  let appTy = Ty.Var appTyVar
  let ctx = unifyTy ctx (tyOf callee) (Ty.Fun(tyOf arg, appTy))
  Expr.Call (callee, [arg], (appTy, loc)), ctx

let inferOpInt (ctx: TyCtx) loc op lexpr rexpr =
  let lexpr, ctx = inferExpr ctx lexpr
  let rexpr, ctx = inferExpr ctx rexpr

  // Infer types so that left and right are of the same type.
  let addTyVar, ctx = freshTyVar "a" ctx
  let lty, rty, addTy = tyOf lexpr, tyOf rexpr, Ty.Var addTyVar
  let ctx = unifyTy ctx lty rty
  let ctx = unifyTy ctx lty addTy

  Expr.Op (op, lexpr, rexpr, (addTy, loc)), ctx

let inferLet ctx loc name init =
  let name, ty, ctx = freshVar name ctx
  let init, initCtx = inferExpr ctx init
  let ctx = rollback ctx initCtx
  let ctx = unifyTy ctx ty (tyOf init)
  Expr.Let (name, init, (Ty.Unit, loc)), ctx

let inferExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, Ty.Unit, ctx
    | [expr] ->
      let expr, ctx = inferExpr ctx expr
      List.rev (expr :: acc), tyOf expr, ctx
    | expr :: exprs ->
      let expr, ctx = inferExpr ctx expr
      let ctx = unifyTy ctx (tyOf expr) Ty.Unit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferBlock ctx loc exprs =
  let exprs, ty, ctx = inferExprs ctx exprs
  Expr.Begin (exprs, (ty, loc)), ctx

let inferExpr (ctx: TyCtx) (expr: Expr<Loc>): Expr<Ty * Loc> * TyCtx =
  match expr with
  | Expr.Unit loc ->
    Expr.Unit (Ty.Unit, loc), ctx
  | Expr.Int (value, loc) ->
    Expr.Int (value, (Ty.Int, loc)), ctx
  | Expr.String (value, loc) ->
    Expr.String (value, (Ty.Str, loc)), ctx
  | Expr.Prim (PrimFun.Printfn, loc) ->
    let ty = Ty.Fun (Ty.Str, Ty.Unit)
    Expr.Prim (PrimFun.Printfn, (ty, loc)), ctx
  | Expr.Ref (ident, loc) when ident = "true" || ident = "false" ->
    Expr.Ref (ident, (Ty.Bool, loc)), ctx
  | Expr.Ref (ident, loc) ->
    inferRef ctx loc ident
  | Expr.If (pred, thenCl, elseCl, loc) ->
    inferIf ctx pred thenCl elseCl loc
  | Expr.Call (callee, [arg], loc) ->
    inferApp ctx loc callee arg
  | Expr.Op (op, l, r, loc) ->
    inferOpInt ctx loc op l r
  | Expr.Let (name, init, loc) ->
    inferLet ctx loc name init
  | Expr.Begin (exprs, loc) ->
    inferBlock ctx loc exprs
  | Expr.Call _ ->
    failwith "unimpl"

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
      VarEnv = Map.empty
      TySerial = 0
      TyEnv = Map.empty
    }
  let exprs, _, ctx = inferExprs ctx exprs
  let exprs = List.map (substTyExpr ctx) exprs
  exprs, ctx
