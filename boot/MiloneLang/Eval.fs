module rec MiloneLang.Eval

open MiloneLang

let initialCtx: EvalContext =
  {
    Outs = []
  }

let emitOut line (ctx: EvalContext) =
  { ctx with Outs = (StdOut, line) :: ctx.Outs }

let emitErr line (ctx: EvalContext) =
  { ctx with Outs = (StdErr, line) :: ctx.Outs }

let valueToString =
  function
  | Value.Unit ->
    "()"
  | Value.Int value ->
    string value
  | Value.String value ->
    value
  | Value.PrimFun _ as it ->
    string it

let primPrintfn ctx format =
  let format, ctx = evalExpr format ctx
  match format with
  | Value.String format ->
    let ctx = emitOut format ctx
    Value.Unit, ctx
  | _ -> failwithf "Expected a string but %A" format

let rec evalExpr (expr: Expr) ctx =
  match expr with
  | Expr.Unit
  | Expr.Begin [] ->
    Value.Unit, ctx
  | Expr.Int value ->
    Value.Int value, ctx
  | Expr.String value ->
    Value.String value, ctx
  | Expr.Prim primFun ->
    Value.PrimFun primFun, ctx
  | Expr.Ref value ->
    failwithf "Undefined var %s" value
  | Expr.Call (Expr.Prim PrimFun.EmitOut, [arg]) ->
    let arg, ctx = evalExpr arg ctx
    let ctx = emitOut (arg |> valueToString) ctx
    Value.Int 0, ctx
  | Expr.Call (Expr.Prim PrimFun.Printfn, [format]) ->
    let value, ctx = primPrintfn ctx format
    value, ctx
  | Expr.Call _ ->
    failwithf "Unknown call: %A" expr
  | Expr.Add (left, right) ->
    match evalExpr left ctx, evalExpr right ctx with
    | (Value.Int left, _), (Value.Int right, _) ->
      left + right |> Value.Int, ctx
    | (Value.String left, _), (Value.String right, _) ->
      left + right |> Value.String, ctx
    | _ -> failwithf "type error: %A" expr
  | Expr.Let _ ->
    failwith "unimpl let"
  | Expr.Begin [expr] ->
    evalExpr expr ctx
  | Expr.Begin (expr :: exprs) ->
    match evalExpr expr ctx with
    | Value.Unit, ctx ->
      evalExpr (Expr.Begin exprs) ctx
    | _ ->
      failwithf "Expected unit but not"

let evalExprList ctx (exprs: Expr list): Value list * EvalContext =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, ctx
    | expr :: exprs ->
      let value, ctx = evalExpr expr ctx
      go (value :: acc) ctx exprs
  go [] ctx exprs

let evalStmt ctx (stmt: Stmt): Value * EvalContext =
  match stmt with
  | Stmt.FunDecl (_, expr) ->
    evalExpr expr ctx

let evalStmts ctx (stmts: Stmt list): Value * EvalContext =
  match stmts with
  | [] ->
    failwith "no main fun"
  | Stmt.FunDecl ("main", _) as stmt :: _ ->
    evalStmt ctx stmt
  | _ :: stmts ->
    evalStmts ctx stmts

let eval (stmts: Stmt list): ProcessOutput =
  match evalStmts initialCtx stmts with
  | Value.Int code, out ->
    {
      Outs = out.Outs |> List.rev
      Code = code
    }
  | v ->
    failwithf "Exit code must be an integer: %A" v
