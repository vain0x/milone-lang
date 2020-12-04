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

open MiloneLang.Util
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

    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let next, f = go next
        HLetValExpr(vis, pat, init, next, ty, loc), f

    | HLetFunExpr (serial, vis, args, body, next, ty, loc) ->
        let next, f = go next
        HLetFunExpr(serial, vis, args, body, next, ty, loc), f

    | HInfExpr (InfOp.Semi, exprs, ty, loc) ->
        let rec goLast exprs =
          match exprs with
          | [] -> [], id
          | [ last ] ->
              let last, f = go last
              [ last ], f
          | expr :: exprs ->
              let exprs, f = goLast exprs
              expr :: exprs, f

        let exprs, f = goLast exprs
        HInfExpr(InfOp.Semi, exprs, ty, loc), f
    | _ -> expr, id

  let expr, makeMain = go expr
  makeMain expr

let hoistMain (expr, tyCtx: TyCtx) =
  let expr = expr |> hoistMainExpr tyCtx.MainFunOpt
  expr, tyCtx
