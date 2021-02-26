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

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLang.Typing

[<NoEquality; NoComparison>]
type private IsTail =
  | IsTail
  | NotTail

// -----------------------------------------------
// Helpers
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
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
  | Some current -> funSerialCompare current funSerial = 0
  | _ -> false

let private withCurrentFun funSerial (f: TailRecCtx -> HExpr * TailRecCtx) (ctx: TailRecCtx) =
  let parentFun = ctx.CurrentFun
  let ctx = { ctx with CurrentFun = Some funSerial }

  let result, ctx = f ctx

  let ctx = { ctx with CurrentFun = parentFun }
  result, ctx

let private troInfExpr isTail kind items ty loc ctx =
  let items, ctx = (items, ctx) |> stMap (troExpr NotTail)

  match kind, items, isTail with
  | HCallProcEN, HFunExpr (funSerial, _, _) :: _, IsTail when ctx |> isCurrentFun funSerial ->
      HNodeExpr(HCallTailRecEN, items, ty, loc), ctx

  | _ -> HNodeExpr(kind, items, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private troExpr isTail (expr, ctx) =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
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

  | HNodeExpr (kind, items, ty, loc) -> ctx |> troInfExpr isTail kind items ty loc

  | HBlockExpr (stmts, last) ->
      let stmts, ctx = (stmts, ctx) |> stMap (troExpr NotTail)
      let last, ctx = (last, ctx) |> troExpr isTail
      HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
      let doArm () =
        let init, ctx = troExpr NotTail (init, ctx)
        let next, ctx = troExpr isTail (next, ctx)
        HLetValExpr(pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
      let doArm () =
        let body, ctx =
          ctx
          |> withCurrentFun callee (fun ctx -> troExpr IsTail (body, ctx))

        let next, ctx = troExpr isTail (next, ctx)
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc), ctx

      doArm ()

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or RecordRes"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in RecordRes"
  | HModuleExpr _
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

let tailRecOptimize (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let ctx = ofTyCtx tyCtx

  let expr, _ = troExpr IsTail (expr, ctx)

  expr, tyCtx
