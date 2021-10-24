/// # Hoist
///
/// Rearranges expression layout for following stages.
///
/// - Move declarations to toplevel
///   for monomorphization to not clone nested definitions.
/// - Flatten let declarations into block
///   to reduce recursion level.
///
/// ## Example
///
/// ```fsharp
///  // At toplevel.
///
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
///  // Local type definition hoisted to toplevel
///  type Serial = | Serial of int
///  // Local function definition hoisted to toplevel
///  let next (Serial value) = value + 1, Serial (value + 1)
///  let serialZero, serialNext = Serial 0, next
/// ```
///
/// ## Let-in to block
///
/// Let expressions look like `let pat = init in next` in syntax.
/// This delimits the scope of pattern variables in `next`,
/// however, we don't care lexical scope after NameRes.
/// This stage changes that layout to `let pat = init in (); next`
/// so that chain of let expressions to be flat.
module rec MiloneTranslation.Hoist

// FIXME: Wording should be fixed.
//        "Declarations" above denotes to syntaxes that
//        introduce some symbols (and don't compute things)
//        such as let-val, let-fun and type-stmt.
//        Now I'm using "statements" for such syntax now.

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

let private hxDummy: HExpr = hxUnit noLoc

let private hxBlock stmts last : HExpr =
  match stmts with
  | [] -> last
  | _ -> HBlockExpr(stmts, last)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private HoistCtx =
  { Decls: HExpr list
    Stmts: HExpr list
    MainFunOpt: FunSerial option }

let private hoistCtxEmpty: HoistCtx =
  { Decls = []
    Stmts = []
    MainFunOpt = None }

let private addDecl decl (ctx: HoistCtx) : HoistCtx = { ctx with Decls = decl :: ctx.Decls }

let private addStmt stmt (ctx: HoistCtx) : HoistCtx =
  if hxIsUnitLit stmt then
    ctx
  else
    { ctx with Stmts = stmt :: ctx.Stmts }

let private takeStmts (ctx: HoistCtx) : HExpr list * HoistCtx =
  List.rev ctx.Stmts, { ctx with Stmts = [] }

let private takeDecls (ctx: HoistCtx) : HExpr list * HoistCtx =
  List.rev ctx.Decls, { ctx with Decls = [] }

// -----------------------------------------------
// Hoist routine
// -----------------------------------------------

/// Processes a let-fun of non-main function.
/// Returns `next`, which is not processed.
let private hoistExprLetFunForNonMainFun (expr, ctx) : HExpr * HoistCtx =
  let callee, args, body, next, loc =
    match expr with
    | HLetFunExpr (callee, args, body, next, _, loc) -> callee, args, body, next, loc
    | _ -> unreachable ()

  let body, ctx = (body, ctx) |> hoistBlock

  let ctx =
    ctx
    |> addDecl (HLetFunExpr(callee, args, body, hxDummy, tyUnit, loc))

  next, ctx

/// Checks if an expression is let-fun of main function.
let private isMainFun expr (ctx: HoistCtx) : bool =
  match expr with
  | HLetFunExpr (callee, _, _, _, _, _) ->
    match ctx.MainFunOpt with
    | Some mainFun -> funSerialCompare mainFun callee = 0
    | _ -> false

  | _ -> unreachable ()

/// Processes a let-fun of the main function.
let private hoistExprLetFunForMainFun (expr, ctx: HoistCtx) : HoistCtx =
  let callee, args, body, next, loc =
    match expr with
    | HLetFunExpr (callee, args, body, next, _, loc) -> callee, args, body, next, loc
    | _ -> unreachable ()

  let body, (ctx: HoistCtx) = (body, ctx) |> hoistBlock

  // Go to the end to process all toplevel expressions.
  let ctx: HoistCtx = (next, ctx) |> hoistExprToplevel

  // Body of the main function starts with a sequence of toplevel non-declaration expressions.
  let stmts, ctx = takeStmts ctx
  let body = hxBlock stmts body

  ctx
  |> addDecl (HLetFunExpr(callee, args, body, hxDummy, tyUnit, loc))

// -----------------------------------------------
// Control
// -----------------------------------------------

let private hoistExpr (expr, ctx) : HExpr * HoistCtx =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let go ((pat, guard, body), ctx) =
      let guard, ctx = hoistBlock (guard, ctx)
      let body, ctx = hoistBlock (body, ctx)
      (pat, guard, body), ctx

    let cond, ctx = hoistExpr (cond, ctx)
    let arms, ctx = (arms, ctx) |> stMap go
    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, items, ty, loc) ->
    let items, ctx = (items, ctx) |> stMap hoistExpr
    HNodeExpr(kind, items, ty, loc), ctx

  | HBlockExpr (stmts, last) ->
    let ctx = stmts |> List.fold hoistStmt ctx
    (last, ctx) |> hoistExpr

  | HLetValExpr (pat, init, next, _, loc) ->
    let init, ctx = (init, ctx) |> hoistExpr

    let ctx =
      ctx
      |> addStmt (HLetValExpr(pat, init, hxDummy, tyUnit, loc))

    hoistExpr (next, ctx)

  | HLetFunExpr _ ->
    (expr, ctx)
    |> hoistExprLetFunForNonMainFun
    |> hoistExpr

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private hoistExprToplevel (expr, ctx) : HoistCtx =
  match expr with
  | HBlockExpr (stmts, last) ->
    let ctx =
      stmts
      |> List.fold (fun ctx stmt -> hoistExprToplevel (stmt, ctx)) ctx

    hoistExprToplevel (last, ctx)

  | HLetValExpr (pat, init, next, _, loc) ->
    let init, ctx = (init, ctx) |> hoistBlock

    let ctx =
      ctx
      |> addStmt (HLetValExpr(pat, init, hxDummy, tyUnit, loc))

    hoistExprToplevel (next, ctx)

  | HLetFunExpr _ when isMainFun expr ctx -> hoistExprLetFunForMainFun (expr, ctx)

  | HLetFunExpr _ ->
    (expr, ctx)
    |> hoistExprLetFunForNonMainFun
    |> hoistExprToplevel

  | _ -> hoistStmt ctx expr

/// Processes an expression, whose value is discarded.
let private hoistStmt ctx expr : HoistCtx =
  let expr, ctx = (expr, ctx) |> hoistExpr
  ctx |> addStmt expr

/// Processes an expression into single block.
///
/// Stmts are unchanged.
let private hoistBlock (expr, ctx: HoistCtx) : HExpr * HoistCtx =
  let parent, ctx = ctx.Stmts, { ctx with Stmts = [] }

  let expr, ctx = (expr, ctx) |> hoistExpr

  let stmts, ctx =
    List.rev ctx.Stmts, { ctx with Stmts = parent }

  hxBlock stmts expr, ctx

let private hoistModule (ctx: HoistCtx) (m: HModule) : HModule * HoistCtx =
  let ctx =
    m.Stmts
    |> List.fold (fun ctx stmt -> hoistExprToplevel (stmt, ctx)) ctx

  let stmts, ctx = takeDecls ctx

  let m = { m with Stmts = stmts }
  m, ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let hoist (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let hoistCtx =
    { hoistCtxEmpty with MainFunOpt = hirCtx.MainFunOpt }

  let modules, hoistCtx =
    modules |> List.mapFold hoistModule hoistCtx

  // Toplevel statements should have been moved into the main function.
  if hoistCtx.Stmts |> List.isEmpty |> not then
    unreachable () // Main function not found?

  modules, hirCtx
