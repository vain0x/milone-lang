/// Generates CIR from AST.
module rec MiloneLang.CIrGen

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    VarSerial: int
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): Ctx =
  {
    VarSerial = tyCtx.VarSerial
  }

let tyOf expr =
  Typing.tyOf expr

let cty ty: CTy =
  match ty with
  | Ty.Unit ->
    CTy.Void
  | Ty.Bool
  | Ty.Int ->
    CTy.Int
  | Ty.Str ->
    CTy.Ptr CTy.Char
  | Ty.Fun _ ->
    CTy.Ptr CTy.Void
  | Ty.Var _ ->
    failwith "Type vars must be resolved in type inference phase."

let ctyOf expr =
  cty (tyOf expr)

let cop op =
  match op with
  | Op.Add -> COp.Add
  | Op.Sub -> COp.Sub
  | Op.Mul -> COp.Mul
  | Op.Div -> COp.Div
  | Op.Mod -> COp.Mod
  | Op.Eq -> COp.Eq
  | Op.Ne -> COp.Ne
  | Op.Lt -> COp.Lt
  | Op.Le -> COp.Le
  | Op.Gt -> COp.Gt
  | Op.Ge -> COp.Ge
  | Op.And
  | Op.Or -> failwith "We don't use && || in C language"

let callPrintf format args =
  let format = CExpr.Str (format + "\\n")
  CStmt.Expr (CExpr.Call (CExpr.Prim CPrim.Printf, format :: args))

let uniqueName name serial =
  sprintf "%s_%d" name serial

let freshName (ctx: Ctx) (name: string) =
  let serial = ctx.VarSerial + 1
  let name = uniqueName name serial
  let ctx = { ctx with VarSerial = ctx.VarSerial + 1 }
  name, ctx

let freshVar (ctx: Ctx) (name: string) (ty: CTy) =
  let name, ctx = freshName ctx name
  name, CExpr.Ref name, ctx

let genOpExpr acc ctx op first second ty loc =
  match op with
  | Op.And ->
    // l && r ---> if l then r else false
    let falseLit = Expr.Ref ("false", 0, (Ty.Bool, loc))
    let expr = Expr.If (first, second, falseLit, (ty, loc))
    genExpr acc ctx expr
  | Op.Or ->
    // l || r ---> if l then true else r
    let trueLit = Expr.Ref ("true", 0, (Ty.Bool, loc))
    let expr = Expr.If (first, trueLit, second, (ty, loc))
    genExpr acc ctx expr
  | _ ->
    // Currently no support of non-int add/cmp/etc.
    let ty = CTy.Int
    let first, acc, ctx = genExpr acc ctx first
    let second, acc, ctx = genExpr acc ctx second
    let name, ctx = freshName ctx "op"
    let acc = CStmt.Let (name, ty, Some (CExpr.Op (cop op, first, second))) :: acc
    CExpr.Ref name, acc, ctx

/// if pred then thenCl else elseCl ->
/// T result;
/// if (pred) { ..; result = thenCl; } else { ..; result = elseCl; }
/// ..(result)
let genIfExpr acc ctx pred thenCl elseCl ty =
  let resultName, result, ctx = freshVar ctx "if" (ctyOf thenCl)
  let pred, acc, ctx = genExpr acc ctx pred
  let thenCl, thenStmts, ctx = genExpr [] ctx thenCl
  let elseCl, elseStmts, ctx = genExpr [] ctx elseCl
  let thenStmts = CStmt.Expr (CExpr.Set (result, thenCl)) :: thenStmts
  let elseStmts = CStmt.Expr (CExpr.Set (result, elseCl)) :: elseStmts
  let acc = CStmt.Let (resultName, cty ty, None) :: acc
  let acc = CStmt.If (pred, List.rev thenStmts, List.rev elseStmts) :: acc
  result, acc, ctx

let genExprList acc ctx exprs =
  let rec go results acc ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, acc, ctx = genExpr acc ctx expr
      go (result :: results) acc ctx exprs
  go [] acc ctx exprs

let genExpr
  (acc: CStmt list) (ctx: Ctx) (arg: Expr<Ty * Loc>)
  : CExpr * CStmt list * Ctx =
  match arg with
  | Expr.Begin ([], _)
  | Expr.Unit _ ->
    CExpr.Unit, acc, ctx
  | Expr.Int (value, _) ->
    CExpr.Int value, acc, ctx
  | Expr.String (value, _) ->
    CExpr.Str value, acc, ctx
  | Expr.Ref ("true", _, _) ->
    CExpr.Int 1, acc, ctx
  | Expr.Ref ("false", _, _) ->
    CExpr.Int 0, acc, ctx
  | Expr.Ref (name, serial, _) ->
    CExpr.Ref (uniqueName name serial), acc, ctx
  | Expr.If (pred, thenCl, elseCl, (ty, _)) ->
    genIfExpr acc ctx pred thenCl elseCl ty
  | Expr.Op (op, first, second, (ty, loc)) ->
    genOpExpr acc ctx op first second ty loc
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _), (Expr.String (format, _)) :: args, _) ->
    let args, ctx = genExprList acc ctx args
    let acc = callPrintf format args :: acc
    CExpr.Unit, acc, ctx
  | Expr.Let (Pat.Ident (name, serial, (ty, _)), init, _) ->
    let name = uniqueName name serial
    let init, acc, ctx = genExpr acc ctx init
    let acc = CStmt.Let (name, cty ty, Some init) :: acc
    CExpr.Ref name, acc, ctx
  | Expr.Begin (expr :: exprs, _) ->
    let rec go acc ctx expr exprs =
      match genExpr acc ctx expr, exprs with
      | (result, acc, ctx), [] ->
        result, acc, ctx
      | (_, acc, ctx), expr :: exprs ->
        go acc ctx expr exprs
    go acc ctx expr exprs
  | Expr.Call (_, [], _) ->
    failwith "never"
  | Expr.Prim _
  | Expr.Call _
  | Expr.Let _ ->
    failwith "unimpl"

let gen (exprs: Expr<Ty * _> list, tyCtx: Typing.TyCtx): CDecl list =
  let ctx = ctxFromTyCtx tyCtx
  match exprs with
  | [Expr.Let (Pat.Ident (name, serial, _), body, _)] ->
    let name = if name = "main" then name else uniqueName name serial
    let result, acc, _ctx = genExpr [] ctx body
    let acc = CStmt.Return (Some result) :: acc
    let decl =
      CDecl.Fun {
        Name = name
        Body = List.rev acc
      }
    [decl]
  | _ -> failwith "unimpl"
