/// # Hoist
///
/// Rearranges expression layout for following stages.
///
/// Moves declarations in functions to top-level
/// since monomorphization doesn't want to clone nested definitions.
///
/// ## Example
///
/// ```fsharp
///  // At top-level
///  let serialZero, serialNext =
///     // Local type definition
///     type Serial = | Serial of int
///     // Local function definition
///     let next (Serial value) = value + 1, Serial (value + 1)
///     Serial 0, next
/// ```
///
/// to
///
/// ```fsharp
///  // Local type definition hoisted to top-level
///  type Serial = | Serial of int
///  // Local function definition hoisted to top-level
///  let next (Serial value) = value + 1, Serial (value + 1)
///  let serialZero, serialNext = Serial 0, next
/// ```
module rec MiloneLang.Hoist

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLang.Typing

let private hxDummy = hxUnit noLoc

// -----------------------------------------------
// HExprAcc
// -----------------------------------------------

/// Accumulation of expression stack.
[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private HExprAcc =
  | Empty
  | Let of HExpr * HExprAcc
  | Semi of HExpr list * HExprAcc

let private hxAccAdd expr exprAcc =
  match expr, exprAcc with
  | HLetFunExpr _, _ -> HExprAcc.Let(expr, exprAcc)

  | _, HExprAcc.Semi (acc, parentAcc) -> HExprAcc.Semi(expr :: acc, parentAcc)

  | _ -> HExprAcc.Semi([ expr ], exprAcc)

let private hxAccToExpr next exprAcc =
  let withNext next letExpr =
    match letExpr with
    | HLetFunExpr (callee, vis, args, body, oldNext, ty, loc) ->
        assert (oldNext |> hxIsUnitLit)
        HLetFunExpr(callee, vis, args, body, next, ty, loc)

    | _ -> failwith "Never"

  let rec go exprAcc next =
    match exprAcc with
    | HExprAcc.Empty -> next

    | HExprAcc.Let (expr, exprAcc) -> expr |> withNext next |> go exprAcc

    | HExprAcc.Semi (exprs, exprAcc) ->
        hxSemi ((next :: exprs) |> List.rev) noLoc
        |> go exprAcc

  go exprAcc next

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private HoistMode =
  | TopLevel
  | Local

// (decls, exprs), where
// exprs are non-declaration top-level expressions.
type private HoistContext = HoistMode * HExprAcc * HExprAcc * FunSerial option

let private hoistCtxEmpty: HoistContext =
  HoistMode.TopLevel, HExprAcc.Empty, HExprAcc.Empty, None

let private currentIsEmpty ctx =
  match ctx with
  | HoistMode.TopLevel, HExprAcc.Empty, HExprAcc.Empty, _ -> true

  | _ -> false

let private currentIsTopLevel (mode, _, _, _) =
  match mode with
  | HoistMode.TopLevel -> true
  | HoistMode.Local -> false

let private isMainFun funSerial (_, _, _, mainFunOpt) =
  match mainFunOpt with
  | Some mainFun -> funSerialCmp mainFun funSerial = 0
  | _ -> false

let private withMainFun mainFunOpt (mode, decls, exprs, _) = mode, decls, exprs, mainFunOpt

let private addDecl expr (mode, decls, exprs, mainFunOpt) =
  let decls = decls |> hxAccAdd expr
  mode, decls, exprs, mainFunOpt

let private addExpr expr (mode, decls, exprs, mainFunOpt) =
  let exprs = exprs |> hxAccAdd expr
  mode, decls, exprs, mainFunOpt

let private takeDecls next (mode, decls, exprs, mainFunOpt) =
  let expr = decls |> hxAccToExpr next
  let ctx = mode, HExprAcc.Empty, exprs, mainFunOpt
  expr, ctx

let private takeExprs next (mode, decls, exprs, mainFunOpt) =
  let expr = exprs |> hxAccToExpr next
  let ctx = mode, decls, HExprAcc.Empty, mainFunOpt
  expr, ctx

// -----------------------------------------------
// Hoist routine
// -----------------------------------------------

let private hoistExprLocal (expr, ctx) =
  // Enter the local.
  let mode, decls, exprs, mainFunOpt = ctx

  let ctx =
    HoistMode.Local, decls, exprs, mainFunOpt

  let expr, ctx = (expr, ctx) |> hoistExpr

  // Leave the local.
  let _, decls, _, _ = ctx
  let ctx = mode, decls, exprs, mainFunOpt

  expr, ctx

let private hoistExprLetFunMain callee vis args body next ty loc ctx =
  let body, ctx = (body, ctx) |> hoistExprLocal

  // Go until the end to accumulate all expressions to the context.
  let next, ctx = (next, ctx) |> hoistExpr

  let mainFunExpr, ctx =
    // Add top-level non-declaration expressions
    // to the head of `main` function body
    // so that they evaluate at the beginning of the program.
    let body, ctx = ctx |> takeExprs body

    HLetFunExpr(callee, vis, args, body, next, ty, loc), ctx

  // Append the `main` to other declarations
  // to reconstruct the whole expressions.
  ctx |> takeDecls mainFunExpr

let private hoistExprLetFun callee vis args body next ty loc ctx =
  if ctx |> isMainFun callee then
    hoistExprLetFunMain callee vis args body next ty loc ctx
  else
    let body, ctx = (body, ctx) |> hoistExprLocal

    let expr =
      // Replace the `next` with a placeholder,
      // which is replaced with actual expressions again at the end.
      let next = hxDummy
      HLetFunExpr(callee, vis, args, body, next, ty, loc)

    let ctx = ctx |> addDecl expr

    (next, ctx) |> hoistExpr

let private hoistExprCore (expr, ctx) =
  match expr with
  | HLitExpr _
  | HRefExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _
  | HOpenExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let go ((pat, guard, body), ctx) =
          let guard, ctx = hoistExpr (guard, ctx)
          let body, ctx = hoistExpr (body, ctx)
          (pat, guard, body), ctx

        let cond, ctx = hoistExpr (cond, ctx)
        let arms, ctx = (arms, ctx) |> stMap go
        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap hoistExpr
        HInfExpr(infOp, items, ty, loc), ctx

      doArm ()

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts, ctx = (stmts, ctx) |> stMap hoistExpr
        let last, ctx = (last, ctx) |> hoistExpr
        HBlockExpr(stmts, last), ctx

      doArm ()

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let body, ctx = (body, ctx) |> hoistExprLocal
        let next, ctx = (next, ctx) |> hoistExpr
        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, args, body, next, ty, loc) -> hoistExprLetFun callee vis args body next ty loc ctx

  | HTyDeclExpr _ ->
      let doArm () =
        let ctx = ctx |> addDecl expr
        hxDummy, ctx

      doArm ()

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or RecordRes"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in RecordRes"
  | HModuleExpr _
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

let private hoistExpr (expr, ctx) =
  if ctx |> currentIsTopLevel |> not then
    (expr, ctx) |> hoistExprCore
  else
    // At the top-level. Check if inner expressions are also top-level or not.
    match expr with
    | HBlockExpr (stmts, last) ->
        let stmts, ctx = (stmts, ctx) |> stMap hoistExpr
        let last, ctx = (last, ctx) |> hoistExpr
        HBlockExpr(stmts, last), ctx

    | HLetValExpr _
    | HLetFunExpr _
    | HTyDeclExpr _ ->
        // Keep top-level except for let bodies.
        (expr, ctx) |> hoistExprCore

    | _ ->
        // It's a top-level non-declaration expression.
        let expr, ctx = (expr, ctx) |> hoistExprLocal
        let ctx = ctx |> addExpr expr
        hxDummy, ctx

let hoist (expr: HExpr, tyCtx: TyCtx) =
  let hoistCtx =
    hoistCtxEmpty |> withMainFun tyCtx.MainFunOpt

  let expr, hoistCtx = (expr, hoistCtx) |> hoistExpr

  assert (hoistCtx |> currentIsEmpty)

  expr, tyCtx
