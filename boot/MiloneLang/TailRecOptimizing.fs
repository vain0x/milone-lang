// Tail recursion optimization.

module rec MiloneLang.TailRecOptimizing

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Records

type private IsTail =
  | IsTail
  | NotTail

// -----------------------------------------------
// Helpers
// -----------------------------------------------

let private ofTyCtx tyCtx =
  let (TyCtx (_, vars, tys, _, _, _, _)) = tyCtx
  TailRecCtx(vars, tys, None, setEmpty (intHash, intCmp))

let private isCurrentFun funSerial ctx =
  match ctx |> tailRecCtxGetCurrentFun with
  | Some it -> it = funSerial
  | None -> false

let private withCurrentFun funSerial (f: TailRecCtx -> HExpr * TailRecCtx) ctx =
  let parentFun = ctx |> tailRecCtxGetCurrentFun

  let ctx =
    ctx |> tailRecCtxWithCurrentFun (Some funSerial)

  let result, ctx = f ctx

  let ctx =
    ctx |> tailRecCtxWithCurrentFun parentFun

  result, ctx

let private troInfExpr isTail infOp items ty loc ctx =
  let items, ctx = (items, ctx) |> stMap (troExpr NotTail)

  match infOp, items, isTail with
  | InfOp.CallProc, HRefExpr (funSerial, _, _) :: _, IsTail when ctx |> isCurrentFun funSerial ->
      HInfExpr(InfOp.CallTailRec, items, ty, loc), ctx

  | InfOp.Semi, _, IsTail ->
      let items, ctx =
        let rec go items ctx =
          match items with
          | [] -> [], ctx

          | [ item ] ->
              let item, ctx = troExpr IsTail (item, ctx)
              [ item ], ctx

          | item :: items ->
              let items, ctx = go items ctx
              item :: items, ctx

        go items ctx

      HInfExpr(infOp, items, ty, loc), ctx

  | _ -> HInfExpr(infOp, items, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private troExpr isTail (expr, ctx) =
  match expr with
  | HLitExpr _
  | HRefExpr _
  | HPrimExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond, ctx = troExpr NotTail (cond, ctx)

        let go ((pat, guard, body), ctx) =
          let guard, ctx = troExpr NotTail (guard, ctx)
          let body, ctx = troExpr isTail (body, ctx)
          (pat, guard, body), ctx

        let arms, ctx = (arms, ctx) |> stMap go
        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let l, ctx = troExpr NotTail (l, ctx)
        HNavExpr(l, r, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) -> ctx |> troInfExpr isTail infOp items ty loc

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let init, ctx = troExpr NotTail (init, ctx)
        let next, ctx = troExpr isTail (next, ctx)
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let body, ctx =
          ctx
          |> withCurrentFun callee (fun ctx -> troExpr IsTail (body, ctx))

        let next, ctx = troExpr isTail (next, ctx)
        HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc), ctx

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "NEVER: %s at %A" error loc
  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let tailRecOptimize (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let ctx = ofTyCtx tyCtx

  let expr, ctx = troExpr IsTail (expr, ctx)

  expr, tyCtx
