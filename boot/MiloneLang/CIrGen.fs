/// Generates CIR from AST.
module rec MiloneLang.CIrGen

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    Serial: int
  }

let tyOf expr =
  Typing.tyOf expr

let cty ty: CTy =
  match ty with
  | Ty.Unit ->
    CTy.Void
  | Ty.Int ->
    CTy.Int
  | Ty.Str ->
    CTy.Ptr CTy.Char
  | Ty.Fun _ ->
    CTy.Ptr CTy.Void
  | Ty.Var _ ->
    failwith "Type vars must be resolved in type inference phase."

let callPrintf format args =
  CStmt.Expr (CExpr.Call (CExpr.Prim CPrim.Printf, format :: args))

let freshName (ctx: Ctx) =
  let name = "l" + string ctx.Serial
  let ctx = { ctx with Serial = ctx.Serial + 1 }
  name, ctx

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
  | Expr.Ref (name, _) ->
    CExpr.Ref name, acc, ctx
  | Expr.Add (first, second, (Ty.Int, _)) ->
    let first, acc, ctx = genExpr acc ctx first
    let second, acc, ctx = genExpr acc ctx second
    let name, ctx = freshName ctx
    let acc = CStmt.Let (name, CTy.Int, CExpr.Add(first, second)) :: acc
    CExpr.Ref name, acc, ctx
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _), format :: args, _) ->
    let format, acc, ctx = genExpr acc ctx format
    let args, ctx = genExprList acc ctx args
    let acc = callPrintf format args :: acc
    let acc = callPrintf (CExpr.Str "\\n") [] :: acc
    CExpr.Unit, acc, ctx
  | Expr.Let (name, init, _) ->
    let cty = cty (tyOf init)
    let init, acc, ctx = genExpr acc ctx init
    let acc = CStmt.Let (name, cty, init) :: acc
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
  | Expr.Add _ ->
    failwith "unimpl"

let gen (exprs: Expr<Ty * _> list, tyCtx: Typing.TyCtx): CDecl list =
  let ctx: Ctx =
    {
      Serial = 0
    }
  match exprs with
  | [Expr.Let (name, body, _)] ->
    let result, acc, _ctx = genExpr [] ctx body
    let acc = CStmt.Return (Some result) :: acc
    let decl =
      CDecl.Fun {
        Name = name
        Body = List.rev acc
      }
    [decl]
  | _ -> failwith "unimpl"