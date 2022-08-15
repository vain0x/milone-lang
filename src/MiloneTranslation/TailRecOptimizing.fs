/// # TailRecOptimizing
///
/// Detects tail recursive calls and marks them
/// so that MIR emits efficient code.
///
/// A function call to the function itself at the end of it
/// is a *tail recursive* call.
//
// ## Example
//
// ```fsharp
//   let rec length xs =
//     match xs with
//     | [] -> 0
//     | _ :: xs -> length xs
//   //             ^^^^^^ tail recursive call
// ```
module rec MiloneTranslation.TailRecOptimizing

open Std.StdError
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes

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
  let items, ctx =
    items |> List.mapFold (troExpr NotTail) ctx

  match kind, items, isTail with
  | HCallProcEN, HFunExpr (funSerial, _, _, _) :: _, IsTail when ctx |> isCurrentFun funSerial ->
    HNodeExpr(HCallTailRecEN, items, ty, loc), ctx

  | _ -> HNodeExpr(kind, items, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private troExpr isTail (ctx: TailRecCtx) expr : HExpr * TailRecCtx =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = cond |> troExpr NotTail ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guard, body) ->
             let guard, ctx = guard |> troExpr NotTail ctx
             let body, ctx = body |> troExpr isTail ctx
             (pat, guard, body), ctx)
           ctx

    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, items, ty, loc) -> ctx |> troInfExpr isTail kind items ty loc

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = stmts |> List.mapFold troStmt ctx
    let last, ctx = last |> troExpr isTail ctx
    HBlockExpr(stmts, last), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private troStmt ctx stmt =
  match stmt with
  | HExprStmt expr ->
    let expr, ctx = expr |> troExpr NotTail ctx
    HExprStmt expr, ctx

  | HLetValStmt (pat, init, loc) ->
    let init, ctx = init |> troExpr NotTail ctx
    HLetValStmt(pat, init, loc), ctx

  | HLetFunStmt (callee, args, body, loc) ->
    let body, ctx =
      ctx
      |> withCurrentFun callee (fun ctx -> troExpr IsTail ctx body)

    HLetFunStmt(callee, args, body, loc), ctx

  | HNativeDeclStmt _ ->
    // Skip since it never happens in args.
    stmt, ctx

let private troModule (ctx: TailRecCtx) (m: HModule) : HModule * TailRecCtx =
  let stmts, ctx = m.Stmts |> List.mapFold troStmt ctx
  let m = { m with Stmts = stmts }
  m, ctx

let tailRecOptimize (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let decls, _ =
    let ctx: TailRecCtx = None
    modules |> List.mapFold troModule ctx

  decls, hirCtx
