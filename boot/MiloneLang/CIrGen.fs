/// Generates CIR from AST.
module rec MiloneLang.CIrGen

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    Serial: int
  }

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

let genExpr acc ctx arg =
  match arg with
  | Expr.Begin []
  | Expr.Unit ->
    CExpr.Unit, acc, ctx
  | Expr.Int value ->
    CExpr.Int value, acc, ctx
  | Expr.String value ->
    CExpr.Str value, acc, ctx
  | Expr.Ref _ ->
    failwith "unimpl"
  | Expr.Add (first, second) ->
    // FIXME: in case of string
    let first, acc, ctx = genExpr acc ctx first
    let second, acc, ctx = genExpr acc ctx second
    let name, ctx = freshName ctx
    let acc = CStmt.Let (name, CTy.Int, CExpr.Add(first, second)) :: acc
    CExpr.Ref name, acc, ctx
  | Expr.Call (Expr.Prim PrimFun.Printfn, format :: args) ->
    let format, acc, ctx = genExpr acc ctx format
    let args, ctx = genExprList acc ctx args
    let acc = callPrintf format args :: acc
    let acc = callPrintf (CExpr.Str "\\n") [] :: acc
    CExpr.Unit, acc, ctx
  | Expr.Begin (expr :: exprs) ->
    let rec go acc ctx expr exprs =
      match genExpr acc ctx expr, exprs with
      | (result, acc, ctx), [] ->
        result, acc, ctx
      | (_, acc, ctx), expr :: exprs ->
        go acc ctx expr exprs
    go acc ctx expr exprs
  | Expr.Call (_, []) ->
    failwith "never"
  | Expr.Prim _
  | Expr.Call _ ->
    failwith "unimpl"

let genDecl ctx (stmt: Stmt) =
  match stmt with
  | Stmt.FunDecl (name, expr) ->
    let result, acc, ctx = genExpr [] ctx expr
    let acc = CStmt.Return (Some result) :: acc
    let decl =
      CDecl.Fun {
        Name = name
        Body = List.rev acc
      }
    decl, ctx

let gen (stmts: Stmt list): CDecl list =
  let ctx: Ctx =
    {
      Serial = 0
    }
  match stmts with
  | [stmt] ->
    let decl, _ = genDecl ctx stmt
    [decl]
  | _ -> failwith "unimpl"
