/// Converts HIR to resolve some syntax sugars.
module rec MiloneLang.Desugaring

open MiloneLang
open MiloneLang.Types
open MiloneLang.Helpers

/// `x = false`
let hxNot expr loc =
  HExpr.Bin (Op.Eq, expr, hxFalse loc, noTy, loc)

let onPat pat =
  pat

let onPats pats =
  List.map onPat pats

/// `if p then t else e` ==> `match p with true -> t | false -> e`
let onIf pred thenCl elseCl ty loc =
  let trueLit = hxTrue noLoc
  let arms =
    [
      HPat.Lit (litTrue, loc), trueLit, onExpr thenCl
      HPat.Lit (litFalse, loc), trueLit, onExpr elseCl
    ]
  HExpr.Match (onExpr pred, arms, ty, loc)

let rec onArms arms =
  match arms with
  | [] ->
    []
  | (pat, guard, body) :: arms ->
    (onPat pat, onExpr guard, onExpr body) :: onArms arms

let rec onExprBin op l r ty loc =
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
    onExprBin Op.App r l ty loc
  | _ ->
    HExpr.Bin (op, onExpr l, onExpr r, ty, loc)

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let onExprList items loc =
  let rec go items =
    match items with
    | [] ->
      hxNil noTy loc
    | item :: items ->
      let item = onExpr item
      HExpr.Bin (Op.Cons, item, go items, noTy, loc)
  go items

/// `let f x : ty = body` ==>
///   `let-fun f(x) = body : ty`
/// `let f x = body` ==>
///   `let-fun f(x) = body`
/// `let pat = body` ==>
///   `let-val pat = body`
let onLet pat body next ty loc =
  match pat with
  | HPat.Anno (HPat.Call (HPat.Ref (ident, serial, _, _), args, _, _), annoTy, annoLoc) ->
    let body = hxAnno (onExpr body) annoTy annoLoc
    let args = onPats args
    let next = onExpr next
    HExpr.LetFun (ident, serial, args, body, next, ty, loc)
  | HPat.Call (HPat.Ref (ident, serial, _, _), args, _, _) ->
    let body = onExpr body
    let args = onPats args
    let next = onExpr next
    HExpr.LetFun (ident, serial, args, body, next, ty, loc)
  | HPat.Anno (HPat.Call _, _, _)
  | HPat.Call _ ->
    HExpr.Error ("Error: To define a function, the first pattern must be just an identifier.", loc)
  | _ ->
    HExpr.Let (onPat pat, onExpr body, onExpr next, ty, loc)

let rec onExprs exprs =
  List.map onExpr exprs

let onExpr (expr: HExpr): HExpr =
  match expr with
  | HExpr.Lit _
  | HExpr.Ref _
  | HExpr.TyDef _
  | HExpr.Open _ ->
    expr
  | HExpr.If (pred, thenCl, elseCl, ty, loc) ->
    onIf pred thenCl elseCl ty loc
  | HExpr.Match (target, arms, ty, loc) ->
    HExpr.Match (onExpr target, onArms arms, ty, loc)
  | HExpr.Nav (subject, message, ty, loc) ->
    HExpr.Nav (onExpr subject, message, ty, loc)
  | HExpr.Bin (op, l, r, ty, loc) ->
    onExprBin op l r ty loc
  | HExpr.Inf (InfOp.List _, items, _, loc) ->
    onExprList items loc
  | HExpr.Inf (infOp, args, ty, loc) ->
    HExpr.Inf (infOp, onExprs args, ty, loc)
  | HExpr.Let (pat, body, next, ty, loc) ->
    onLet pat body next ty loc
  | HExpr.LetFun _
  | HExpr.Error _ ->
    failwithf "Never %A" expr

let desugar (expr: HExpr): HExpr =
  onExpr expr
