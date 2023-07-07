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

// Wording should be fixed.
// "Declarations" above denotes to syntaxes that
// introduce some symbols (and don't compute things)
// such as let-val, let-fun and type-stmt.
// Now I'm using "statements" for such syntax now.

open MiloneShared.SharedTypes
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes

let private hpUnit loc = HNodePat(HTuplePN, [], tyUnit, loc)

let private hxBlock stmts last : HExpr =
  match stmts, last with
  | [], _ -> last
  | _, HBlockExpr (other, last) -> HBlockExpr(List.append stmts other, last)
  | _ -> HBlockExpr(stmts, last)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private HoistCtx =
  { Decls: HStmt list
    Stmts: HStmt list }

let private hoistCtxEmpty: HoistCtx = { Decls = []; Stmts = [] }

let private addDecl (decl: HStmt) (ctx: HoistCtx) : HoistCtx = { ctx with Decls = decl :: ctx.Decls }

let private addStmt stmt (ctx: HoistCtx) : HoistCtx =
  match stmt with
  | HExprStmt expr when hxIsUnitLit expr -> ctx
  | _ -> { ctx with Stmts = stmt :: ctx.Stmts }

let private takeStmts (ctx: HoistCtx) : HStmt list * HoistCtx =
  List.rev ctx.Stmts, { ctx with Stmts = [] }

let private takeDecls (ctx: HoistCtx) : HStmt list * HoistCtx =
  List.rev ctx.Decls, { ctx with Decls = [] }

// -----------------------------------------------
// Control
// -----------------------------------------------

let private hoistExpr ctx expr : HExpr * HoistCtx =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = cond |> hoistExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guard, body) ->
             let guard, ctx = guard |> hoistExprAsBlock ctx
             let body, ctx = body |> hoistExprAsBlock ctx
             (pat, guard, body), ctx)
           ctx

    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (HNativeDeclEN cCode, args, _, loc) ->
    let args, ctx = args |> List.mapFold hoistExpr ctx
    hxUnit loc, addDecl (HNativeDeclStmt(cCode, args, loc)) ctx

  | HNodeExpr (kind, items, ty, loc) ->
    let items, ctx = items |> List.mapFold hoistExpr ctx
    HNodeExpr(kind, items, ty, loc), ctx

  | HBlockExpr (stmts, last) ->
    let ctx = stmts |> List.fold hoistStmt ctx
    last |> hoistExpr ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private hoistExprAsStmt (ctx: HoistCtx) expr : HoistCtx =
  let expr, ctx = expr |> hoistExpr ctx
  ctx |> addStmt (HExprStmt expr)

/// Processes an expression into single block.
///
/// Stmts are unchanged.
let private hoistExprAsBlock (ctx: HoistCtx) expr : HExpr * HoistCtx =
  let parent, ctx = ctx.Stmts, { ctx with Stmts = [] }
  let expr, ctx = expr |> hoistExpr ctx

  let stmts, ctx =
    List.rev ctx.Stmts, { ctx with Stmts = parent }

  hxBlock stmts expr, ctx

let private hoistStmt ctx stmt : HoistCtx =
  match stmt with
  | HExprStmt expr -> expr |> hoistExprAsStmt ctx

  | HLetValStmt (pat, init, loc) ->
    let init, ctx = init |> hoistExprAsBlock ctx
    ctx |> addStmt (HLetValStmt(pat, init, loc))

  | HLetFunStmt (callee, args, body, loc) ->
    let body, ctx = body |> hoistExprAsBlock ctx

    ctx
    |> addDecl (HLetFunStmt(callee, args, body, loc))

  | HNativeDeclStmt _ -> unreachable () // Generated in Hoist.

let private hoistModule (hirCtx: HirCtx) (m: HModule) : (HModule * HStmt option) * HirCtx =
  let ctx =
    m.Stmts |> List.fold hoistStmt hoistCtxEmpty

  let toplevelStmts, ctx = takeStmts ctx
  let funStmts, _ = takeDecls ctx

  let funStmts, startOpt, hirCtx =
    if List.isEmpty toplevelStmts then
      funStmts, None, hirCtx
    else
      let funSerial = FunSerial(hirCtx.Serial + 1)
      let funTy = tyFun tyUnit tyUnit
      let loc = Loc(m.DocId, 0, 0)

      // Move toplevel statements to a function that is called on start.
      let funDef: FunDef =
        { Name = "start"
          Arity = 1
          Ty = TyScheme([], funTy)
          Abi = MiloneAbi
          Linkage = InternalLinkage
          Prefix = []
          Loc = loc }

      let hirCtx =
        { hirCtx with
            Serial = hirCtx.Serial + 1
            Funs = hirCtx.Funs |> TMap.add funSerial funDef }

      let funStmts =
        let body = HBlockExpr(toplevelStmts, hxUnit loc)

        let stmt =
          HLetFunStmt(funSerial, [ hpUnit loc ], body, loc)

        List.append funStmts [ stmt ]

      let callStmt =
        let startFun = HFunExpr(funSerial, funTy, [], loc)
        HExprStmt(hxCallProc startFun [ hxUnit loc ] tyUnit loc)

      funStmts, Some callStmt, hirCtx

  let m = { m with Stmts = funStmts }
  (m, startOpt), hirCtx

// -----------------------------------------------
// Main function
// -----------------------------------------------

let private genMainFun (hirCtx: HirCtx) (m: HModule) =
  match m.MainFunOpt with
  | None when m.IsExecutable ->
    let funSerial = FunSerial(hirCtx.Serial + 1)
    let loc = Loc(m.DocId, 0, 0)

    let funDef: FunDef =
      { Name = "main"
        Arity = 1
        Ty = TyScheme([], tyFun tyUnit tyInt)
        Abi = CAbi
        Linkage = ExternalLinkage "main"
        Prefix = []
        Loc = loc }

    let hirCtx =
      { hirCtx with
          Serial = hirCtx.Serial + 1
          Funs = hirCtx.Funs |> TMap.add funSerial funDef }

    let m =
      let stmt =
        HLetFunStmt(funSerial, [ hpUnit loc ], HLitExpr(IntLit "0", loc), loc)

      { m with
          MainFunOpt = Some funSerial
          Stmts = List.append m.Stmts [ stmt ] }

    m, hirCtx

  | _ -> m, hirCtx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let hoist (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let modules, startStmts, hirCtx =
    let pairs, hirCtx =
      modules |> List.mapFold hoistModule hirCtx

    let modules, startStmtOpts = pairs |> List.unzip
    let startStmts = startStmtOpts |> List.choose id
    modules, startStmts, hirCtx

  // Mutate main function to call all start functions.
  let modules, hirCtx =
    if List.isEmpty startStmts then
      modules, hirCtx
    else
      modules
      |> List.mapFold (fun hirCtx (m: HModule) ->
        // Generate main function.
        let m, hirCtx = genMainFun hirCtx m

        let isMain stmt =
          match stmt, m.MainFunOpt with
          | HLetFunStmt (s, _, _, _), Some funSerial -> funSerialCompare s funSerial = 0
          | _ -> false

        if m.Stmts |> List.exists isMain then
          let stmts =
            m.Stmts
            |> List.map (fun stmt ->
              if isMain stmt then
                match stmt with
                | HLetFunStmt (funSerial, argPats, body, loc) ->
                  let body = hxBlock startStmts body
                  HLetFunStmt(funSerial, argPats, body, loc)
                | _ -> stmt
              else
                stmt)

          { m with Stmts = stmts }, hirCtx
        else
          m, hirCtx) hirCtx

  modules, hirCtx
