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
  | Value.Int value ->
    string value
  | Value.PrimFun _ as it ->
    string it

let rec evalExpr (expr: Expr) ctx =
  match expr with
  | Expr.Int value ->
    Value.Int value, ctx
  | Expr.Prim primFun ->
    Value.PrimFun primFun, ctx
  | Expr.Call (Expr.Prim PrimFun.EmitOut, [arg]) ->
    let arg, ctx = evalExpr arg ctx
    let ctx = emitOut (arg |> valueToString) ctx
    Value.Int 0, ctx
  | Expr.Call _ ->
    failwithf "Unknown call: %A" expr
  | Expr.Add (left, right) ->
    match evalExpr left ctx, evalExpr right ctx with
    | (Value.Int left, _), (Value.Int right, _) ->
      left + right |> Value.Int, ctx
    | _ -> failwithf "add is not int: %A" expr

let evalStmt ctx (stmt: Stmt): Value * EvalContext =
  match stmt with
  | Stmt.FunDecl (_, expr) ->
    evalExpr expr ctx

let eval (stmt: Stmt): ProcessOutput =
  match evalStmt initialCtx stmt with
  | Value.Int code, out ->
    {
      Outs = out.Outs |> List.rev
      Code = code
    }
  | v ->
    failwithf "Exit code must be an integer: %A" v
