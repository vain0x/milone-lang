/// # TailRecOptimizing
///
/// Detects tail recursive calls and marks them
/// so that MIR emits efficient code.
///
/// A function call to the function itself at the end of it
/// is a *tail recursive* call.
///
/// ## Example
///
/// ```fsharp
///   let rec length xs =
///     match xs with
///     | [] -> 0
///     | _ :: xs -> length xs
///   //             ^^^^^^ tail recursive call
/// ```
module rec MiloneLang.TailRecOptimizing

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Typing

[<NoEquality; NoComparison>]
type private IsTail =
  | IsTail
  | NotTail

// -----------------------------------------------
// Helpers
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private TailRecCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>
    CurrentFun: FunSerial option }

let private ofTyCtx (tyCtx: TyCtx): TailRecCtx =
  { Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    CurrentFun = None }

let private isCurrentFun funSerial (ctx: TailRecCtx) =
  match ctx.CurrentFun with
  | Some it -> it = funSerial
  | None -> false

let private withCurrentFun funSerial (f: TailRecCtx -> HExpr * TailRecCtx) (ctx: TailRecCtx) =
  let parentFun = ctx.CurrentFun
  let ctx = { ctx with CurrentFun = Some funSerial }

  let result, ctx = f ctx

  let ctx = { ctx with CurrentFun = parentFun }
  result, ctx

let private troInfExpr isTail infOp items ty loc ctx =
  let items, ctx = (items, ctx) |> stMap (troExpr NotTail)

  match infOp, items, isTail with
  | InfOp.CallProc, HFunExpr (funSerial, _, _) :: _, IsTail when ctx |> isCurrentFun funSerial ->
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
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _
  | HOpenExpr _
  | HTyDeclExpr _
  | HErrorExpr _ -> expr, ctx

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

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or TyElaborating"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in TyElaboration"
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let tailRecOptimize (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let ctx = ofTyCtx tyCtx

  let expr, _ = troExpr IsTail (expr, ctx)

  expr, tyCtx
