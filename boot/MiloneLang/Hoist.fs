/// Rearranges the expression layout for the following stages.
///
/// This stage eliminates local (in-function) type/function definitions
/// by moving them up to the top-level
/// because monomorphization doesn't want to clone nested definitions.
///
/// ### Example
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

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

/// Accumulation of expression stack.
[<RequireQualifiedAccess>]
type HExprAcc =
  | Empty
  | Let of HExpr * HExprAcc
  | Semi of HExpr list * HExprAcc

[<RequireQualifiedAccess>]
type HoistMode =
  | TopLevel
  | Local

// (decls, exprs), where
// exprs are non-declaration top-level expressions.
type HoistContext = HoistMode * HExprAcc * HExprAcc

let hxDummy = hxUnit noLoc

// -----------------------------------------------
// HExprAcc
// -----------------------------------------------

let hxAccAdd expr exprAcc =
  match expr, exprAcc with
  | HExpr.LetFun _, _ -> HExprAcc.Let(expr, exprAcc)

  | _, HExprAcc.Semi (acc, parentAcc) -> HExprAcc.Semi(expr :: acc, parentAcc)

  | _ -> HExprAcc.Semi([ expr ], exprAcc)

let hxAccToExpr next exprAcc =
  let withNext next letExpr =
    match letExpr with
    | HExpr.LetFun (callee, vis, isMainFun, args, body, oldNext, ty, loc) ->
        assert (oldNext |> hxIsUnitLit)
        HExpr.LetFun(callee, vis, isMainFun, args, body, next, ty, loc)

    | _ -> failwith "Never"

  let rec go exprAcc next =
    match exprAcc with
    | HExprAcc.Empty -> next

    | HExprAcc.Let (expr, exprAcc) -> expr |> withNext next |> go exprAcc

    | HExprAcc.Semi (exprs, exprAcc) ->
        hxSemi ((next :: exprs) |> listRev) noLoc
        |> go exprAcc

  go exprAcc next

let hoistCtxEmpty: HoistContext =
  HoistMode.TopLevel, HExprAcc.Empty, HExprAcc.Empty

let hoistCtxIsEmpty ctx =
  match ctx with
  | HoistMode.TopLevel, HExprAcc.Empty, HExprAcc.Empty -> true

  | _ -> false

let hoistCtxIsTopLevel (mode, _, _) =
  match mode with
  | HoistMode.TopLevel -> true

  | HoistMode.Local -> false

let hoistCtxAddDecl expr (mode, decls, exprs) =
  let decls = decls |> hxAccAdd expr
  mode, decls, exprs

let hoistCtxAddExpr expr (mode, decls, exprs) =
  let exprs = exprs |> hxAccAdd expr
  mode, decls, exprs

let hoistCtxTakeDecls next (mode, decls, exprs) =
  let expr = decls |> hxAccToExpr next
  let ctx = mode, HExprAcc.Empty, exprs
  expr, ctx

let hoistCtxTakeExprs next (mode, decls, exprs) =
  let expr = exprs |> hxAccToExpr next
  let ctx = mode, decls, HExprAcc.Empty
  expr, ctx

// -----------------------------------------------
// Hoist routine
// -----------------------------------------------

let hoistPat t = t

let hoistExprLocal (expr, ctx) =
  // Enter the local.
  let mode, decls, exprs = ctx
  let ctx = HoistMode.Local, decls, exprs

  let expr, ctx = (expr, ctx) |> hoistExpr

  // Leave the local.
  let _, decls, _ = ctx
  let ctx = mode, decls, exprs

  expr, ctx

let hoistExprLetFunMain callee vis isMainFun args body next ty loc ctx =
  assert isMainFun

  let body, ctx = (body, ctx) |> hoistExprLocal

  // Go until the end to accumulate all expressions to the context.
  let next, ctx = (next, ctx) |> hoistExpr

  let mainFunExpr, ctx =
    // Add top-level non-declaration expressions
    // to the head of `main` function body
    // so that they evaluate at the beginning of the program.
    let body, ctx = ctx |> hoistCtxTakeExprs body

    HExpr.LetFun(callee, vis, isMainFun, args, body, next, ty, loc), ctx

  // Append the `main` to other declarations
  // to reconstruct the whole expressions.
  ctx |> hoistCtxTakeDecls mainFunExpr

let hoistExprLetFun callee vis isMainFun args body next ty loc ctx =
  if isMainFun then
    hoistExprLetFunMain callee vis isMainFun args body next ty loc ctx
  else

    let body, ctx = (body, ctx) |> hoistExprLocal

    let expr =
      // Replace the `next` with a placeholder,
      // which is replaced with actual expressions again at the end.
      let next = hxDummy
      HExpr.LetFun(callee, vis, isMainFun, args, body, next, ty, loc)

    let ctx = ctx |> hoistCtxAddDecl expr

    (next, ctx) |> hoistExpr

let hoistExprCore (expr, ctx) =
  match expr with
  | HExpr.Error _
  | HExpr.Lit _
  | HExpr.Ref _
  | HExpr.Prim _
  | HExpr.Open _ -> expr, ctx

  | HExpr.Match (target, arms, ty, loc) ->
      let doArm () =
        let go ((pat, guard, body), ctx) =
          let pat, ctx = hoistPat (pat, ctx)
          let guard, ctx = hoistExpr (guard, ctx)
          let body, ctx = hoistExpr (body, ctx)
          (pat, guard, body), ctx

        let target, ctx = hoistExpr (target, ctx)
        let arms, ctx = (arms, ctx) |> stMap go
        HExpr.Match(target, arms, ty, loc), ctx

      doArm ()

  | HExpr.Nav (l, r, ty, loc) ->
      let doArm () =
        let l, ctx = hoistExpr (l, ctx)
        HExpr.Nav(l, r, ty, loc), ctx

      doArm ()

  | HExpr.Inf (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap hoistExpr
        HExpr.Inf(infOp, items, ty, loc), ctx

      doArm ()

  | HExpr.Let (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let pat, ctx = (pat, ctx) |> hoistPat
        let body, ctx = (body, ctx) |> hoistExprLocal
        let next, ctx = (next, ctx) |> hoistExpr
        HExpr.Let(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HExpr.LetFun (callee, vis, isMainFun, args, body, next, ty, loc) ->
      hoistExprLetFun callee vis isMainFun args body next ty loc ctx

  | HExpr.TyDecl _ ->
      let doArm () =
        let ctx = ctx |> hoistCtxAddDecl expr
        hxDummy, ctx

      doArm ()

let hoistExpr (expr, ctx) =
  if ctx |> hoistCtxIsTopLevel |> not then
    (expr, ctx) |> hoistExprCore
  else

    // At the top-level. Check if inner expressions are also top-level or not.
    match expr with
    | HExpr.Inf (InfOp.Semi, items, ty, loc) ->
        let items, ctx = (items, ctx) |> stMap hoistExpr
        HExpr.Inf(InfOp.Semi, items, ty, loc), ctx

    | HExpr.Let _
    | HExpr.LetFun _
    | HExpr.TyDecl _ ->
        // Keep top-level except for let bodies.
        (expr, ctx) |> hoistExprCore

    | _ ->
        // It's a top-level non-declaration expression.
        let expr, ctx = (expr, ctx) |> hoistExprLocal
        let ctx = ctx |> hoistCtxAddExpr expr
        hxDummy, ctx

let hoist (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let expr, hoistCtx = (expr, hoistCtxEmpty) |> hoistExpr
  assert (hoistCtx |> hoistCtxIsEmpty)

  expr, tyCtx
