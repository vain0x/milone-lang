module rec MiloneLang.Desugaring

open MiloneLang
open MiloneLang.Helpers

let hxRef name loc =
  Expr.Ref (name, noSerial, 0, noTy, loc)

/// `x = false`
let hxNot expr loc =
  Expr.Op (Op.Eq, expr, hxFalse loc, noTy, loc)

let onPat pat =
  pat

let onPats pats =
  List.map onPat pats

/// `if p then t else e` ==> `match p with true -> t | false -> e`
let onIf pred thenCl elseCl ty loc =
  let arms =
    [
      Pat.Lit (Lit.Bool true, loc), onExpr thenCl
      Pat.Lit (Lit.Bool false, loc), onExpr elseCl
    ]
  Expr.Match (onExpr pred, arms, ty, loc)

let rec onArms arms =
  match arms with
  | [] ->
    []
  | (pat, body) :: arms ->
    (onPat pat, onExpr body) :: onArms arms

let rec onExprOp op l r ty loc =
  match op with
  | Op.And ->
    // `l && r` ==> `if l then r else false`
    onIf l r (hxFalse loc) ty loc
  | Op.Or ->
    // `l || r` ==> `if l then true else r`
    onIf l (hxTrue loc) r ty loc
  | Op.Pipe ->
    // `x |> f` ==> `f x`
    // NOTE: Evaluation order does change.
    onExprOp Op.App r l ty loc
  | _ ->
    Expr.Op (op, onExpr l, onExpr r, ty, loc)

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let onExprList items loc =
  let rec go items =
    match items with
    | [] ->
      hxNil noTy loc
    | item :: items ->
      let item = onExpr item
      Expr.Op (Op.Cons noTy, item, go items, noTy, loc)
  go items

/// `let f x : ty = body` ==>
///   `let-fun f(x) = body : ty`
/// `let f x = body` ==>
///   `let-fun f(x) = body`
/// `let pat = body` ==>
///   `let-val pat = body`
let onLet pat body loc =
  match pat with
  | Pat.Anno (Pat.Call (Pat.Ref (ident, serial, _, _), args, _, _), annoTy, annoLoc) ->
    let body = hxAnno (onExpr body) annoTy annoLoc
    let args = onPats args
    Expr.LetFun (ident, serial, args, body, noTy, loc)
  | Pat.Call (Pat.Ref (ident, serial, _, _), args, _, _) ->
    let body = onExpr body
    let args = onPats args
    Expr.LetFun (ident, serial, args, body, noTy, loc)
  | Pat.Anno (Pat.Call _, _, _)
  | Pat.Call _ ->
    Expr.Error ("Error: To define a function, the first pattern must be just an identifier.", loc)
  | _ ->
    Expr.Let (onPat pat, onExpr body, loc)

let rec onExprs exprs =
  List.map onExpr exprs

let onExpr (expr: Expr<_>): Expr<_> =
  match expr with
  | Expr.Lit _
  | Expr.Ref _
  | Expr.TyDef _ ->
    expr
  | Expr.If (pred, thenCl, elseCl, ty, loc) ->
    onIf pred thenCl elseCl ty loc
  | Expr.Match (target, arms, ty, loc) ->
    Expr.Match (onExpr target, onArms arms, ty, loc)
  | Expr.Nav (subject, message, ty, loc) ->
    Expr.Nav (onExpr subject, message, ty, loc)
  | Expr.Op (op, l, r, ty, loc) ->
    onExprOp op l r ty loc
  | Expr.Inf (InfOp.List _, items, _, loc) ->
    onExprList items loc
  | Expr.Inf (infOp, args, ty, loc) ->
    Expr.Inf (infOp, onExprs args, ty, loc)
  | Expr.Let (pat, body, loc) ->
    onLet pat body loc
  | Expr.LetFun _
  | Expr.Error _ ->
    failwith "Never"

let desugar (exprs: Expr<'a> list): Expr<'a> list =
  onExprs exprs
