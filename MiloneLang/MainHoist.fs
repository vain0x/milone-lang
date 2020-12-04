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

open MiloneLang.Hir
open MiloneLang.Typing

let private isMainFun serial mainFunOpt =
  match mainFunOpt with
  | Some mainFun -> funSerialCmp serial mainFun = 0
  | _ -> false

let private hoistMainExpr mainFunOpt expr =
  let rec go expr =
    match expr with
    | HLetFunExpr (serial, vis, args, body, next, ty, loc) when isMainFun serial mainFunOpt ->
        let makeMain rest =
          HLetFunExpr(serial, vis, args, hxSemi [ rest; body ] loc, next, ty, loc)

        next, makeMain

    | HBlockExpr (stmts, last) ->
        let last, f = go last
        HBlockExpr(stmts, last), f

    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let next, f = go next
        HLetValExpr(vis, pat, init, next, ty, loc), f

    | HLetFunExpr (serial, vis, args, body, next, ty, loc) ->
        let next, f = go next
        HLetFunExpr(serial, vis, args, body, next, ty, loc), f

    | _ -> expr, id

  let expr, makeMain = go expr
  makeMain expr

let hoistMain (expr, tyCtx: TyCtx) =
  let expr = expr |> hoistMainExpr tyCtx.MainFunOpt
  expr, tyCtx
