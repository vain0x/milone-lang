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
module rec MiloneTranslation.TailRecOptimizing

open MiloneShared.Util
open MiloneTranslation.Hir

[<NoEquality; NoComparison>]
type private IsTail =
  | IsTail
  | NotTail

// -----------------------------------------------
// Helpers
// -----------------------------------------------

/// Current function.
type private TailRecCtx = FunSerial option

let private isCurrentFun funSerial (currentFunOpt: TailRecCtx) =
  match currentFunOpt with
  | Some current -> funSerialCompare current funSerial = 0
  | _ -> false

let private withCurrentFun funSerial (f: TailRecCtx -> HExpr * TailRecCtx) (ctx: TailRecCtx) =
  let parentCtx = ctx

  let result, _ =
    let newCtx: TailRecCtx = Some funSerial
    f newCtx

  result, parentCtx

let private troInfExpr isTail kind items ty loc ctx =
  let items, ctx = (items, ctx) |> stMap (troExpr NotTail)

  match kind, items, isTail with
  | HCallProcEN, HFunExpr (funSerial, _, _, _) :: _, IsTail when ctx |> isCurrentFun funSerial ->
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
  | HPrimExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = troExpr NotTail (cond, ctx)

    let go ((pat, guard, body), ctx) =
      let guard, ctx = troExpr NotTail (guard, ctx)
      let body, ctx = troExpr isTail (body, ctx)
      (pat, guard, body), ctx

    let arms, ctx = (arms, ctx) |> stMap go
    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, items, ty, loc) -> ctx |> troInfExpr isTail kind items ty loc

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap (troExpr NotTail)
    let last, ctx = (last, ctx) |> troExpr isTail
    HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
    let init, ctx = troExpr NotTail (init, ctx)
    let next, ctx = troExpr isTail (next, ctx)
    HLetValExpr(pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, args, body, next, ty, loc) ->
    let body, ctx =
      ctx
      |> withCurrentFun callee (fun ctx -> troExpr IsTail (body, ctx))

    let next, ctx = troExpr isTail (next, ctx)
    HLetFunExpr(callee, args, body, next, ty, loc), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let tailRecOptimize (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let decls, _ =
    let ctx: TailRecCtx = None
    (decls, ctx) |> stMap (troExpr IsTail)

  decls, tyCtx
