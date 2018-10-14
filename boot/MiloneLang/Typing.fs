module rec MiloneLang.Typing

open System
open MiloneLang

type TyExpr = Expr<Ty * Loc>

type TyCtx =
  {
    VarSerial: int
    /// Identifier to type and serial.
    VarEnv: Map<string, Ty * int>
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
let rollback bCtx dCtx: TyCtx =
  assert (bCtx.VarSerial <= dCtx.VarSerial)
  assert (bCtx.TySerial <= dCtx.TySerial)
  { dCtx with
      VarEnv = bCtx.VarEnv
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

let freshVar ident (ctx: TyCtx): string * int * Ty * TyCtx =
  let tyVar, ctx = freshTyVar ident ctx
  let ty = Ty.Var tyVar
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarEnv = ctx.VarEnv |> Map.add ident (ty, serial)
    }
  ident, serial, ty, ctx

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

/// Substitutes occurrences of already-inferred type vars
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
    | Ty.Fun (lSTy, lTTy), Ty.Fun (rSTy, rTTy) ->
      ctx |> go lSTy rSTy |> go lTTy rTTy
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
      let lty, rty = substTy ctx lty, substTy ctx rty
      failwithf "Couldn't unify %A %A" lty rty
  go lty rty ctx

let inferRef (ctx: TyCtx) loc ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | Some (ty, serial) ->
    Expr.Ref (ident, serial, (ty, loc)), ctx
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

/// During inference of `f w x ..`,
/// assume we concluded `f w : 'f`.
/// We can also conclude `f w : 'x -> 'g`.
let rec inferAppArgs acc (ctx: TyCtx) calleeTy args =
  match args with
  | [] ->
    List.rev acc, calleeTy, ctx
  | arg :: args ->
    let appTyVar, ctx = freshTyVar "app" ctx
    let appTy = Ty.Var appTyVar
    let arg, ctx = inferExpr ctx arg
    let ctx = unifyTy ctx calleeTy (Ty.Fun (tyOf arg, appTy))
    inferAppArgs (arg :: acc) ctx appTy args

let inferApp (ctx: TyCtx) loc callee args =
  let callee, ctx = inferExpr ctx callee
  let args, appTy, ctx = inferAppArgs [] ctx (tyOf callee) args
  Expr.Call (callee, args, (appTy, loc)), ctx

let inferAppPrintfn ctx loc args =
  match args with
  | [] -> failwith "Never"
  | Expr.String (format, _) :: _ ->
    let calleeTy =
      // FIXME: too rough
      if format.Contains("%s")
      then Ty.Fun (Ty.Str, Ty.Fun (Ty.Str, Ty.Unit))
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
  let resultTyVar, ctx = freshTyVar "op" ctx
  let lTy, rTy, resultTy = tyOf left, tyOf right, Ty.Var resultTyVar
  let ctx = unifyTy ctx lTy rTy

  left, Expr.Op (op, left, right, (resultTy, loc)), ctx

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

let inferOp (ctx: TyCtx) loc op left right =
  match op with
  | Op.Add
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

let inferLet ctx pats init loc =
  match pats with
  | [Pat.Ident (name, _, patLoc)] ->
    // let x = init
    // Define new variable defined by this let to the context. This won't roll back there.
    let name, serial, ty, ctx = freshVar name ctx
    // Type init expression.
    let init, initCtx = inferExpr ctx init
    // Roll back context to remove out-of-scope symbols,
    // defined inside `init`.
    let ctx = rollback ctx initCtx
    let ctx = unifyTy ctx ty (tyOf init)
    let pats = [Pat.Ident (name, serial, (ty, patLoc))]
    Expr.Let (pats, init, (Ty.Unit, loc)), ctx
  | [Pat.Ident (name, _, patLoc); Pat.Unit unitLoc] ->
    // let f () = body
    let name, serial, ty, ctx = freshVar name ctx
    // FIXME: currently functions cannot capture local variables
    let bodyCtx = { ctx with VarEnv = Map.empty }
    let body, bodyCtx = inferExpr bodyCtx init
    let ctx = rollback ctx bodyCtx
    let ctx = unifyTy ctx ty (Ty.Fun (Ty.Unit, tyOf body))
    let pats = [Pat.Ident (name, serial, (ty, patLoc)); Pat.Unit (Ty.Unit, unitLoc)]
    Expr.Let (pats, body, (Ty.Unit, loc)), ctx
  | _ ->
    failwith "unimpl use of let"

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
  | Expr.Ref (ident, serial, loc) when ident = "true" || ident = "false" ->
    Expr.Ref (ident, serial, (Ty.Bool, loc)), ctx
  | Expr.Ref (ident, _, loc) ->
    inferRef ctx loc ident
  | Expr.If (pred, thenCl, elseCl, loc) ->
    inferIf ctx pred thenCl elseCl loc
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _), args, loc) ->
    inferAppPrintfn ctx loc args
  | Expr.Call (callee, args, loc) ->
    inferApp ctx loc callee args
  | Expr.Op (op, l, r, loc) ->
    inferOp ctx loc op l r
  | Expr.Let (pat, init, loc) ->
    inferLet ctx pat init loc
  | Expr.Begin (exprs, loc) ->
    inferBlock ctx loc exprs
  | Expr.Call _ ->
    failwith "unimpl"
  | Expr.Prim _ ->
    failwith "printfn must appear in form of `printfn format args..`."

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
