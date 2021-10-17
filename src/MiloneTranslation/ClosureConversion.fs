/// # ClosureConversion
///
/// Performs closure conversion (or so-called lambda lifting?)
/// so that all functions are closed i.e. not using outer local variables.
///
/// In milone-lang syntax, functions are allowed to use local variables
/// outside of their body. Such variables are *captured* by the function.
/// (They are also called *upvars*.)
///
/// This stage calculates the set of captured variables for each function
/// and transforms them to take captured variables as additional arguments.
///
/// This stage consists of the three steps:
///
/// - Reference collection
/// - Reference closure
/// - Transform
///
/// ## Reference collection
///
/// By traversing over the expression, calculates the following sets
/// (call it known context here) at every point.
///
/// - Locals: set of variables defined inside the current function.
/// - Refs: set of variables or functions that occurs in the current function.
///
/// At the end of function body, the function *remembers*
/// the current known context for the transformation later.
///
/// ## Reference closure
///
/// For the transformation, set of references must be *transitive*.
/// However, the Refs of `f` may be incomplete here. E.g.
///   there is a function `f`,
///   which calls a function `g`,
///   which uses a local `a`.
///
/// Perform a closure operation to the relation of references
/// to make the Refs be *transitive*.
///
/// See also `closureRefs` in implementation.
///
/// ## Transformation
///
/// Here the set of captured variables can easily compute
/// as `(Refs \ Locals)` using known context of functions,
/// where `s \ t` is set difference.
///
/// Three rules:
///
/// - Convert a reference of function to take captured variables
///   as additional arguments.
/// - Convert a declaration of function to take captured variables
///   as addition arguments.
/// - Update function declarations in the context
///   because the type of functions may change.
///
/// ## Example
///
/// From:
///
/// ```fsharp
///   let file = "file.fs"
///   let line = 2
///   let get () = file, line
///   //           ^^^^^^^^^^ captured vars
///   get ()
/// ```
///
/// to:
///
/// ```fsharp
///   let file = "file.fs"
///   let line = 2
///   let get file line () = file, line // the body is now closed
///   //      ^^^^^^^^^ added
///   get file line ()
///   //  ^^^^^^^^^ added
/// ```
///
/// See also `let_fun_closure.fs` in tests.
module rec MiloneTranslation.ClosureConversion

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

// -----------------------------------------------
// KnownCtx
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private KnownCtx =
  { Locals: AssocSet<VarSerial>
    UseVars: AssocSet<VarSerial>
    UseFuns: AssocSet<FunSerial> }

let private knownCtxEmpty () : KnownCtx =
  { Locals = TSet.empty varSerialCompare
    UseVars = TSet.empty varSerialCompare
    UseFuns = TSet.empty funSerialCompare }

let private knownCtxEnterFunDecl (ctx: KnownCtx) =
  { ctx with
      UseVars = TSet.empty varSerialCompare
      UseFuns = TSet.empty funSerialCompare
      Locals = TSet.empty varSerialCompare }

let private knownCtxLeaveFunDecl (baseCtx: KnownCtx) (ctx: KnownCtx) =
  { ctx with
      UseVars = baseCtx.UseVars
      UseFuns = baseCtx.UseFuns
      Locals = baseCtx.Locals }

let private knownCtxAddLocal serial (ctx: KnownCtx) =
  { ctx with
      Locals = ctx.Locals |> TSet.add serial }

let private knownCtxUseVar serial (ctx: KnownCtx) =
  { ctx with
      UseVars = ctx.UseVars |> TSet.add serial }

let private knownCtxUseFun funSerial (ctx: KnownCtx) =
  { ctx with
      UseFuns = ctx.UseFuns |> TSet.add funSerial }

let private knownCtxToNonlocalVars (ctx: KnownCtx) : AssocSet<VarSerial> =
  ctx.UseVars
  |> TSet.fold
       (fun acc varSerial ->
         if ctx.Locals |> TSet.contains varSerial |> not then
           acc |> TSet.add varSerial
         else
           acc)
       (TSet.empty varSerialCompare)

// -----------------------------------------------
// Caps
// -----------------------------------------------

/// List of captured variables.
/// Don't forget the case of empty.
type private Caps = (VarSerial * Ty * Loc) list

/// Updates the function type to take captured variables.
let private capsAddToFunTy tTy (caps: Caps) =
  caps
  |> List.fold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the callee to take captured variables as arguments.
let private capsMakeApp calleeSerial tyArgs calleeTy calleeLoc (caps: Caps) =
  let callee =
    let calleeTy = caps |> capsAddToFunTy calleeTy
    HFunExpr(calleeSerial, calleeTy, tyArgs, calleeLoc)

  let app, _ =
    caps
    |> List.rev
    |> List.fold
         (fun (callee, calleeTy) (serial, ty, loc) ->
           let arg = HVarExpr(serial, ty, loc)
           hxApp callee arg calleeTy loc, tyFun ty calleeTy)
         (callee, calleeTy)

  app

/// Updates the argument patterns to take captured variables.
let private capsAddToFunPats args (caps: Caps) =
  caps
  |> List.fold (fun args (serial, ty, loc) -> HVarPat(serial, ty, loc) :: args) args

let private capsUpdateFunDef funTy arity (caps: Caps) =
  let funTy = caps |> capsAddToFunTy funTy
  let arity = arity + List.length caps
  funTy, arity

// -----------------------------------------------
// Context
// -----------------------------------------------

/// Context of closure conversion.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CcCtx =
  { StaticVars: AssocMap<VarSerial, VarDef>
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Current: KnownCtx
    FunKnowns: AssocMap<FunSerial, KnownCtx>
    FunUpvars: AssocMap<FunSerial, AssocSet<VarSerial>> }

let private ofTyCtx (tyCtx: TyCtx) : CcCtx =
  { StaticVars = tyCtx.Vars
    Vars = emptyVars
    Funs = tyCtx.Funs

    Current = knownCtxEmpty ()
    FunKnowns = TMap.empty funSerialCompare
    FunUpvars = TMap.empty funSerialCompare }

let private toTyCtx (tyCtx: TyCtx) (ctx: CcCtx) = { tyCtx with Funs = ctx.Funs }

let private addLocal varSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddLocal varSerial }

let private isStaticVar varSerial (ctx: CcCtx) =
  ctx.StaticVars |> TMap.containsKey varSerial

let private useVar varSerial (ctx: CcCtx) =
  if isStaticVar varSerial ctx then
    // Don't count static vars as used.
    ctx
  else
    { ctx with
        Current = ctx.Current |> knownCtxUseVar varSerial }

let private useFun funSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxUseFun funSerial }

/// Called on leave function declaration to store the current known context.
let private saveKnownCtxToFun funSerial (ctx: CcCtx) =
  // Don't update in the second traversal for transformation.
  let funKnowns = ctx.FunKnowns

  if funKnowns |> TMap.containsKey funSerial then
    ctx
  else
    { ctx with
        FunKnowns = funKnowns |> TMap.add funSerial ctx.Current }

let private enterFunDecl (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxEnterFunDecl }

let private leaveFunDecl funSerial (baseCtx: CcCtx) (ctx: CcCtx) =
  let ctx = ctx |> saveKnownCtxToFun funSerial

  { ctx with
      Current =
        ctx.Current
        |> knownCtxLeaveFunDecl baseCtx.Current }

/// Gets a list of captured variables for a function.
let private genFunCaps funSerial (ctx: CcCtx) : Caps =
  let varSerials =
    match ctx.FunUpvars |> TMap.tryFind funSerial with
    | Some it -> it |> TSet.toList
    | None -> []

  varSerials
  |> List.choose
       (fun varSerial ->
         if isStaticVar varSerial ctx |> not then
           let varDef = ctx.Vars |> mapFind varSerial
           Some(varSerial, varDef.Ty, varDef.Loc)
         else
           None)

let private closureRefs (ctx: CcCtx) : CcCtx =
  let mergeUpvars localVars newUpvars (modified, upvars) : bool * AssocSet<VarSerial> =
    newUpvars
    |> TSet.fold
         (fun (modified, upvars) varSerial ->
           if upvars |> TSet.contains varSerial
              || localVars |> TSet.contains varSerial then
             modified, upvars
           else
             true, upvars |> TSet.add varSerial)
         (modified, upvars)

  let visitFun (totalModified, funUpvarsMap) funSerial (upvars, localVars, funs) =
    let modified, upvars =
      funs
      |> List.fold
           (fun (modified, upvars) funSerial ->
             match funUpvarsMap |> TMap.tryFind funSerial with
             | Some (newUpvars, _, _) ->
               (modified, upvars)
               |> mergeUpvars localVars newUpvars

             | None ->
               // `funSerial` is defined in earlier module. newUpvars is [].
               modified, upvars)
           (false, upvars)

    if modified then
      true,
      funUpvarsMap
      |> TMap.add funSerial (upvars, localVars, funs)
    else
      totalModified, funUpvarsMap

  let rec makeTransitive funUpvarsMap =
    let modified, funUpvarsMap =
      funUpvarsMap
      |> TMap.fold visitFun (false, funUpvarsMap)

    if modified then
      makeTransitive funUpvarsMap
    else
      funUpvarsMap

  let funUpvars =
    ctx.FunKnowns
    |> TMap.map
         (fun (_: FunSerial) (knownCtx: KnownCtx) ->
           knownCtxToNonlocalVars knownCtx, knownCtx.Locals, TSet.toList knownCtx.UseFuns)
    |> makeTransitive
    |> TMap.map (fun (_: FunSerial) (upvars: AssocSet<VarSerial>, _: AssocSet<VarSerial>, _: FunSerial list) -> upvars)

  { ctx with FunUpvars = funUpvars }

/// Applies the changes of function types.
let private updateFunDefs (ctx: CcCtx) =
  let funs =
    ctx.FunKnowns
    |> TMap.fold
         (fun funs funSerial (_: KnownCtx) ->
           match ctx |> genFunCaps funSerial with
           | [] -> funs

           | caps ->
             let funDef: FunDef = funs |> mapFind funSerial
             let (TyScheme (tyVars, funTy)) = funDef.Ty

             let funTy, arity =
               caps |> capsUpdateFunDef funTy funDef.Arity

             let ty = TyScheme(tyVars, funTy)

             funs
             |> TMap.add funSerial { funDef with Arity = arity; Ty = ty })
         ctx.Funs

  { ctx with Funs = funs }

// -----------------------------------------------
// Featured transformations
// -----------------------------------------------

let private ccFunExpr funSerial tyArgs funTy funLoc ctx =
  ctx
  |> genFunCaps funSerial
  |> capsMakeApp funSerial tyArgs funTy funLoc

let private ccLetFunExpr callee args body next ty loc ctx =
  let args, body, ctx =
    let baseCtx = ctx
    let ctx = ctx |> enterFunDecl

    let ctx = args |> List.fold ccPat ctx
    let body, ctx = (body, ctx) |> ccExpr

    let ctx = ctx |> leaveFunDecl callee baseCtx
    args, body, ctx

  let args =
    ctx |> genFunCaps callee |> capsAddToFunPats args

  let next, ctx = (next, ctx) |> ccExpr
  HLetFunExpr(callee, args, body, next, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private ccPat ctx pat : CcCtx =
  let onPat pat ctx = ccPat ctx pat
  let onPats pats ctx = pats |> List.fold ccPat ctx

  match pat with
  | HLitPat _
  | HDiscardPat _
  | HVariantPat _ -> ctx

  | HVarPat (serial, _, _) -> ctx |> addLocal serial
  | HNodePat (_, argPats, _, _) -> ctx |> onPats argPats
  | HAsPat (bodyPat, serial, _) -> ctx |> addLocal serial |> onPat bodyPat
  | HOrPat (l, r, _) -> ctx |> onPat l |> onPat r

let private ccExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr, ctx

  | HVarExpr (serial, ty, loc) ->
    let ctx = ctx |> useVar serial
    HVarExpr(serial, ty, loc), ctx

  | HFunExpr (serial, funTy, tyArgs, funLoc) ->
    let ctx = ctx |> useFun serial
    ccFunExpr serial tyArgs funTy funLoc ctx, ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = ccExpr (cond, ctx)

    let go ((pat, guard, body), ctx) =
      let ctx = ccPat ctx pat
      let guard, ctx = ccExpr (guard, ctx)
      let body, ctx = ccExpr (body, ctx)
      (pat, guard, body), ctx

    let arms, ctx = (arms, ctx) |> stMap go
    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, items, ty, loc) ->
    let items, ctx = (items, ctx) |> stMap ccExpr
    HNodeExpr(kind, items, ty, loc), ctx

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap ccExpr
    let last, ctx = (last, ctx) |> ccExpr
    HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, body, next, ty, loc) ->
    let ctx = ccPat ctx pat
    let body, ctx = ccExpr (body, ctx)
    let next, ctx = ccExpr (next, ctx)
    HLetValExpr(pat, body, next, ty, loc), ctx

  | HLetFunExpr (callee, args, body, next, ty, loc) -> ccLetFunExpr callee args body next ty loc ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private ccModule1 (m: HModule, ctx: CcCtx) =
  let stmts, ctx = (m.Stmts, ctx) |> stMap ccExpr
  let m = { m with Stmts = stmts }
  m, ctx

let private ccModule (m: HModule, tyCtx: TyCtx) =
  let ccCtx = ofTyCtx tyCtx

  let ccCtx = { ccCtx with Vars = m.Vars }

  // Traverse for reference collection.
  // NOTE: Converted expression is possibly incorrect
  //       because the set of captured variables is incomplete
  //       when to process a function reference before definition.
  let _, ccCtx = (m, ccCtx) |> ccModule1

  // Resolve transitive references.
  let ccCtx = ccCtx |> closureRefs

  // Traverse again to transform function references.
  let m, ccCtx = (m, ccCtx) |> ccModule1

  let tyCtx = ccCtx |> updateFunDefs |> toTyCtx tyCtx
  m, tyCtx

let closureConversion (modules: HProgram, tyCtx: TyCtx) : HProgram * TyCtx = (modules, tyCtx) |> stMap ccModule
