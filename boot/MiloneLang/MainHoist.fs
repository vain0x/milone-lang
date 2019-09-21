/// ## Main hoisting
///
/// Converts the whole program to be wrapped in the main function.
///
/// ### Example
///
/// ```fsharp
/// let success = 0
/// let main _ =
///    success
/// ```
///
/// to
///
/// ```fsharp
/// let main _ =
///    let success = 0
///    success
/// ```
module rec MiloneLang.MainHoist

open MiloneLang.Helpers
open MiloneLang.Types

let hoistMainExpr expr =
  let rec go expr =
    match expr with
    | HExpr.LetFun ("main", serial, args, body, next, ty, loc) ->
      let makeMain rest =
        HExpr.LetFun ("main", serial, args, hxSemi [rest; body] loc, next, ty, loc)
      next, makeMain

    | HExpr.Let (pat, init, next, ty, loc) ->
      let next, f = go next
      HExpr.Let (pat, init, next, ty, loc), f

    | HExpr.LetFun (ident, serial, args, body, next, ty, loc) ->
      let next, f = go next
      HExpr.LetFun (ident, serial, args, body, next, ty, loc), f

    | HExpr.Inf (InfOp.Semi, exprs, ty, loc) ->
      let rec goLast exprs =
        match exprs with
        | [] ->
          [], id
        | [last] ->
          let last, f = go last
          [last], f
        | expr :: exprs ->
          let exprs, f = goLast exprs
          expr :: exprs, f
      let exprs, f = goLast exprs
      HExpr.Inf (InfOp.Semi, exprs, ty, loc), f
    | _ ->
      expr, id

  let expr, makeMain = go expr
  makeMain expr

let hoistMain (expr, tyCtx: Typing.TyCtx) =
  let expr = expr |> hoistMainExpr
  expr, tyCtx
