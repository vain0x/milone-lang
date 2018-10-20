module rec MiloneLang.Mir

type TyCtx = Typing.TyCtx

let mirifyPat (pat: Pat<Ty * Loc>): Pat<Ty * Loc> =
  pat

let mirifyExpr (expr: Expr<Ty * Loc>): Expr<Ty * Loc> =
  match expr with
  | Expr.Unit _
  | Expr.Int _
  | Expr.Str _
  | Expr.Prim _
  | Expr.Ref _ ->
    expr
  | Expr.If (pred, thenCl, elseCl, a) ->
    Expr.If (mirifyExpr pred, mirifyExpr thenCl, mirifyExpr elseCl, a)
  | Expr.Call (callee, args, a) ->
    Expr.Call (mirifyExpr callee, List.map mirifyExpr args, a)
  | Expr.Op (op, l, r, a) ->
    Expr.Op (op, mirifyExpr l, mirifyExpr r, a)
  | Expr.AndThen (exprs, a) ->
    Expr.AndThen (List.map mirifyExpr exprs, a)
  | Expr.Let ([pat], init, a) ->
    Expr.Let ([mirifyPat pat], mirifyExpr init, a)
  | Expr.Let (pat :: pats, body, a) ->
    Expr.Let (List.map mirifyPat (pat :: pats), mirifyExpr body, a)
  | Expr.Call (_, [], _)
  | Expr.Anno _
  | Expr.Let ([], _, _) ->
    failwith "Never"

let mirify (exprs: Expr<Ty * Loc> list, tyCtx: TyCtx): Expr<Ty * Loc> list * TyCtx =
  List.map mirifyExpr exprs, tyCtx
