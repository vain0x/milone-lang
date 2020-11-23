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
/// - Known: set of functions defined outside the current function.
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
/// as `(Refs \ Locals) \ Known` using known context of functions,
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
module rec MiloneLang.ClosureConversion

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Syntax
open MiloneLang.Typing
open MiloneLang.Hir

// -----------------------------------------------
// KnownCtx
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private KnownCtx =
  { Known: AssocSet<FunSerial>
    Locals: AssocSet<VarSerial>
    UseVars: AssocSet<VarSerial>
    UseFuns: AssocSet<FunSerial> }

let private knownCtxEmpty (): KnownCtx =
  { Known = setEmpty funSerialCmp
    Locals = setEmpty varSerialCmp
    UseVars = setEmpty varSerialCmp
    UseFuns = setEmpty funSerialCmp }

let private knownCtxEnterFunDecl (ctx: KnownCtx) =
  { ctx with
      UseVars = setEmpty varSerialCmp
      UseFuns = setEmpty funSerialCmp
      Locals = setEmpty varSerialCmp }

let private knownCtxLeaveFunDecl (baseCtx: KnownCtx) (ctx: KnownCtx) =
  { ctx with
      UseVars = baseCtx.UseVars
      UseFuns = baseCtx.UseFuns
      Locals = baseCtx.Locals }

let private knownCtxAddKnown serial (ctx: KnownCtx) =
  { ctx with
      Known = ctx.Known |> setAdd serial }

let private knownCtxAddLocal serial (ctx: KnownCtx) =
  { ctx with
      Locals = ctx.Locals |> setAdd serial }

let private knownCtxUseVar serial (ctx: KnownCtx) =
  { ctx with
      UseVars = ctx.UseVars |> setAdd serial }

let private knownCtxUseFun funSerial (ctx: KnownCtx) =
  { ctx with
      UseFuns = ctx.UseFuns |> setAdd funSerial }

/// Returns serials referenced in the current context but not known nor locals
/// including function serials.
let private knownCtxToNonlocalUses (ctx: KnownCtx): VarSerial list * FunSerial list =
  let vars =
    ctx.UseVars
    |> setFold (fun acc varSerial ->
         if ctx.Locals |> setContains varSerial |> not
         then varSerial :: acc
         else acc) []

  let funs =
    ctx.UseFuns
    |> setFold (fun acc funSerial ->
         if ctx.Known |> setContains funSerial |> not
         then funSerial :: acc
         else acc) []

  vars, funs

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
let private capsMakeApp calleeSerial calleeTy calleeLoc (caps: Caps) =
  let callee =
    let calleeTy = caps |> capsAddToFunTy calleeTy
    HFunExpr(calleeSerial, calleeTy, calleeLoc)

  let app, _ =
    caps
    |> List.rev
    |> List.fold (fun (callee, calleeTy) (serial, ty, loc) ->
         let arg = HRefExpr(serial, ty, loc)
         hxApp callee arg calleeTy loc, tyFun ty calleeTy) (callee, calleeTy)

  app

/// Updates the argument patterns to take captured variables.
let private capsAddToFunPats args (caps: Caps) =
  caps
  |> List.fold (fun args (serial, ty, loc) -> HRefPat(serial, ty, loc) :: args) args

let private capsUpdateFunDef funTy arity (caps: Caps) =
  let funTy = caps |> capsAddToFunTy funTy
  let arity = arity + List.length caps
  funTy, arity

// -----------------------------------------------
// Context
// -----------------------------------------------

/// Context of closure conversion.
[<NoEquality; NoComparison>]
type private CcCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Tys: AssocMap<TySerial, TyDef>
    Current: KnownCtx
    FunKnowns: AssocMap<FunSerial, KnownCtx> }

let private ofTyCtx (tyCtx: TyCtx): CcCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Tys = tyCtx.Tys

    Current = knownCtxEmpty ()
    FunKnowns = mapEmpty funSerialCmp }

let private toTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  { tyCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars
      Funs = ctx.Funs
      Tys = ctx.Tys }

let private addKnown funSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddKnown funSerial }

let private addLocal varSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddLocal varSerial }

let private useVar varSerial (ctx: CcCtx) =
  match ctx.Vars |> mapTryFind varSerial with
  | Some (VarDef (_, StaticSM, _, _)) ->
      // Don't count static vars as used.
      ctx

  | _ ->
      { ctx with
          Current = ctx.Current |> knownCtxUseVar varSerial }

let private useFun funSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxUseFun funSerial }

/// Called on leave function declaration to store the current known context.
let private saveKnownCtxToFun funSerial (ctx: CcCtx) =
  let ctx = ctx |> addKnown funSerial

  // Don't update in the second traversal for transformation.
  let funKnowns = ctx.FunKnowns
  if funKnowns |> mapContainsKey funSerial then
    ctx
  else
    { ctx with
        FunKnowns = funKnowns |> mapAdd funSerial ctx.Current }

let private enterFunDecl (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxEnterFunDecl }

let private leaveFunDecl funSerial (baseCtx: CcCtx) (ctx: CcCtx) =
  let ctx = ctx |> saveKnownCtxToFun funSerial

  { ctx with
      Current =
        ctx.Current
        |> knownCtxLeaveFunDecl baseCtx.Current }

/// Gets a list of captured variable serials for a function
/// including referenced functions.
let private getCapturedSerials funSerial (ctx: CcCtx) =
  match ctx.FunKnowns |> mapTryFind funSerial with
  | Some knownCtx -> knownCtx |> knownCtxToNonlocalUses
  | None -> [], []

/// Gets a list of captured variables for a function.
/// Doesn't include referenced functions.
let private genFunCaps funSerial (ctx: CcCtx): Caps =
  let varSerials, _ = ctx |> getCapturedSerials funSerial

  varSerials
  |> List.choose (fun varSerial ->
       match ctx.Vars |> mapTryFind varSerial with
       | Some (VarDef (_, AutoSM, ty, loc)) -> Some(varSerial, ty, loc)

       | _ -> None)

/// Extends the set of references to be transitive.
/// E.g. a function `f` uses `g` and `g` uses `h` (and `h` uses etc.),
///      we think `f` also uses `h`.
let private closureRefs (ctx: CcCtx): CcCtx =
  let rec doClosureRefs vars funs ccCtx (modified, visited, acc) =
    match vars, funs with
    | [], [] -> modified, visited, acc

    | varSerial :: vars, _ ->
        let revisit = acc |> setContains varSerial
        let modified = modified || not revisit

        let acc =
          if revisit then acc else acc |> setAdd varSerial

        doClosureRefs vars funs ccCtx (modified, visited, acc)

    | _, funSerial :: funs ->
        let revisit = visited |> setContains funSerial
        let modified = modified || not revisit

        let visited =
          if revisit then visited else visited |> setAdd funSerial

        let otherVars, otherFuns = ccCtx |> getCapturedSerials funSerial

        (modified, visited, acc)
        |> doClosureRefs otherVars otherFuns ccCtx
        |> doClosureRefs vars funs ccCtx

  let closureKnownCtx (modified, ccCtx) funSerial (knownCtx: KnownCtx) =
    let vars = knownCtx.UseVars
    let funs = knownCtx.UseFuns
    match (false, funs, vars)
          |> doClosureRefs (vars |> setToList) (funs |> setToList) ccCtx with
    | true, visited, vars ->
        true,
        { ccCtx with
            FunKnowns =
              ccCtx.FunKnowns
              |> mapAdd
                   funSerial
                   { knownCtx with
                       UseVars = vars
                       UseFuns = visited } }

    | false, _, _ -> modified, ccCtx

  let rec closureFuns (modified, ccCtx: CcCtx) =
    if not modified then
      ccCtx
    else
      ccCtx.FunKnowns
      |> mapFold closureKnownCtx (false, ccCtx)
      |> closureFuns

  closureFuns (true, ctx)

/// Applies the changes of function types.
let private updateFunDefs (ctx: CcCtx) =
  let funs =
    ctx.FunKnowns
    |> mapFold (fun funs funSerial (_: KnownCtx) ->
         match ctx |> genFunCaps funSerial with
         | [] -> funs

         | caps ->
             let funDef: FunDef = funs |> mapFind funSerial
             let (TyScheme (tyVars, funTy)) = funDef.Ty

             let funTy, arity =
               caps |> capsUpdateFunDef funTy funDef.Arity

             let ty = TyScheme(tyVars, funTy)

             funs
             |> mapAdd funSerial { funDef with Arity = arity; Ty = ty }) ctx.Funs

  { ctx with Funs = funs }

// -----------------------------------------------
// Featured transformations
// -----------------------------------------------

let private ccFunExpr refVarSerial refTy refLoc ctx =
  // NOTE: No need to check whether it's a function
  //       because non-function caps are empty.
  let refExpr =
    ctx
    |> genFunCaps refVarSerial
    |> capsMakeApp refVarSerial refTy refLoc

  refExpr, ctx

let private ccLetFunExpr callee vis isMainFun args body next ty loc ctx =
  let args, body, ctx =
    let baseCtx = ctx
    let ctx = ctx |> enterFunDecl

    let args, ctx = (args, ctx) |> stMap ccPat
    let body, ctx = (body, ctx) |> ccExpr

    let ctx = ctx |> leaveFunDecl callee baseCtx
    args, body, ctx

  let args =
    ctx |> genFunCaps callee |> capsAddToFunPats args

  let next, ctx = (next, ctx) |> ccExpr
  HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc), ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private ccPat (pat, ctx) =
  match pat with
  | HLitPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _
  | HDiscardPat _
  | HVariantPat _ -> pat, ctx

  | HRefPat (serial, _, _) ->
      let ctx = ctx |> addLocal serial
      pat, ctx

  | HConsPat (l, r, itemTy, loc) ->
      let l, ctx = (l, ctx) |> ccPat
      let r, ctx = (r, ctx) |> ccPat
      HConsPat(l, r, itemTy, loc), ctx

  | HTuplePat (items, ty, loc) ->
      let items, ctx = (items, ctx) |> stMap ccPat
      HTuplePat(items, ty, loc), ctx

  | HCallPat (callee, args, ty, loc) ->
      let callee, ctx = (callee, ctx) |> ccPat
      let args, ctx = (args, ctx) |> stMap ccPat
      HCallPat(callee, args, ty, loc), ctx

  | HBoxPat (itemPat, loc) ->
      let itemPat, ctx = (itemPat, ctx) |> ccPat
      HBoxPat(itemPat, loc), ctx

  | HAsPat (pat, serial, loc) ->
      let ctx = ctx |> addLocal serial
      let pat, ctx = (pat, ctx) |> ccPat
      HAsPat(pat, serial, loc), ctx

  | HOrPat (first, second, ty, loc) ->
      let first, ctx = (first, ctx) |> ccPat
      let second, ctx = (second, ctx) |> ccPat
      HOrPat(first, second, ty, loc), ctx

  | HNavPat _ -> failwith "NEVER: HNavPat is resolved in NameRes."
  | HAnnoPat _ -> failwith "NEVER: HAnnoPat is resolved in Typing."

let private ccExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HVariantExpr _
  | HPrimExpr _
  | HTyDeclExpr _
  | HOpenExpr _ -> expr, ctx

  | HRefExpr (serial, ty, loc) ->
      let doArm () =
        let ctx = ctx |> useVar serial
        HRefExpr(serial, ty, loc), ctx

      doArm ()

  | HFunExpr (serial, refTy, refLoc) ->
      let doArm () =
        let ctx = ctx |> useFun serial
        ccFunExpr serial refTy refLoc ctx

      doArm ()

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond, ctx = ccExpr (cond, ctx)

        let go ((pat, guard, body), ctx) =
          let pat, ctx = ccPat (pat, ctx)
          let guard, ctx = ccExpr (guard, ctx)
          let body, ctx = ccExpr (body, ctx)
          (pat, guard, body), ctx

        let arms, ctx = (arms, ctx) |> stMap go
        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap ccExpr
        HInfExpr(infOp, items, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let pat, ctx = ccPat (pat, ctx)
        let body, ctx = ccExpr (body, ctx)
        let next, ctx = ccExpr (next, ctx)
        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      ccLetFunExpr callee vis isMainFun args body next ty loc ctx

  | HErrorExpr (error, loc) -> failwithf "Never: %s at %A" error loc
  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or TyElaborating"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in TyElaboration"
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let closureConversion (expr, tyCtx: TyCtx) =
  let ccCtx = ofTyCtx tyCtx

  // Traverse for reference collection.
  // NOTE: Converted expression is possibly incorrect
  //       because the set of captured variables is incomplete
  //       when to process a function reference before definition.
  let _, ccCtx = (expr, ccCtx) |> ccExpr

  // Resolve transitive references.
  let ccCtx = ccCtx |> closureRefs

  // Traverse again to transform function references.
  let expr, ccCtx = (expr, ccCtx) |> ccExpr

  let tyCtx = ccCtx |> updateFunDefs |> toTyCtx tyCtx

  expr, tyCtx
