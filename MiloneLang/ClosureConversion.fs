/// ## Declosure: Closure conversion
///
/// Performs closure conversion to make all functions be context-free.
///
/// Functions can use local variables outside of their body.
/// Call these variables *captured by the function*.
///
/// This stage calculates the set of captured variables for functions
/// and transforms them to take captured variables as additional arguments.
///
/// Consists of three steps:
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
/// See also `ccCtxClosureRefs`.
///
/// ## Transformation
///
/// Here the set of captured variables can easily compute
/// as `(Refs - Locals) - Known` using known context of functions.
///
/// Three rules:
///
/// - Convert a reference of function to take captured variables
///   as additional arguments.
/// - Convert a declaration of function to take captured variables
///   as addition arguments.
/// - Update function definitions in the context
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
///   get ()
/// ```
///
/// to:
///
/// ```fsharp
///   let file = "file.fs"
///   let line = 2
///   let get file line () = file, line // the body is now closed
///   get file line
/// ```
///
/// See also `let_fun_closure.fs` in tests.
module rec MiloneLang.ClosureConversion

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Typing

/// List of captured variables.
/// Don't forget the case of empty.
type Caps = (VarSerial * Ty * Loc) list

// -----------------------------------------------
// KnownCtx
// -----------------------------------------------

[<RequireQualifiedAccess>]
type private KnownCtx =
  { Known: AssocSet<FunSerial>
    Locals: AssocSet<VarSerial>
    Refs: AssocSet<VarSerial> }

let private knownCtxEmpty (): KnownCtx =
  { Known = setEmpty intCmp
    Locals = setEmpty intCmp
    Refs = setEmpty intCmp }

let private knownCtxEnterFunDecl (ctx: KnownCtx) =
  { ctx with
      Refs = setEmpty intCmp
      Locals = setEmpty intCmp }

let private knownCtxLeaveFunDecl (baseCtx: KnownCtx) (ctx: KnownCtx) =
  { ctx with
      Refs = baseCtx.Refs
      Locals = baseCtx.Locals }

let private knownCtxAddKnown serial (ctx: KnownCtx) =
  { ctx with
      Known = ctx.Known |> setAdd serial }

let private knownCtxAddLocal serial (ctx: KnownCtx) =
  { ctx with
      Locals = ctx.Locals |> setAdd serial }

let private knownCtxAddRef serial (ctx: KnownCtx) =
  { ctx with
      Refs = ctx.Refs |> setAdd serial }

/// Returns serials referenced in the current context but not known nor locals
/// including function serials.
let private knownCtxToCapturedSerials (ctx: KnownCtx): AssocSet<VarSerial> =
  let refs = setDiff ctx.Refs ctx.Locals
  let refs = setDiff refs ctx.Known
  refs

// -----------------------------------------------
// CcCtx (ClosureConversionContext)
// -----------------------------------------------

type private CcCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>
    Current: KnownCtx
    Funs: AssocMap<FunSerial, KnownCtx> }

let private ccCtxFromTyCtx (tyCtx: TyCtx): CcCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys

    Current = knownCtxEmpty ()
    Funs = mapEmpty intCmp }

let private ccCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  { tyCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars
      Tys = ctx.Tys }

let private ccCtxAddKnown funSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddKnown funSerial }

let private ccCtxAddLocal varSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddLocal varSerial }

let private ccCtxAddRef varSerial (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxAddRef varSerial }

/// Called on leave function declaration to store the current known context.
let private ccCtxStoreFunKnownCtx funSerial (ctx: CcCtx) =
  let ctx = ctx |> ccCtxAddKnown funSerial

  // Don't update in the second traversal for transformation.
  let funs = ctx.Funs
  if funs |> mapContainsKey funSerial then
    ctx
  else
    { ctx with
        Funs = funs |> mapAdd funSerial ctx.Current }

let private ccCtxEnterFunDecl (ctx: CcCtx) =
  { ctx with
      Current = ctx.Current |> knownCtxEnterFunDecl }

let private ccCtxLeaveFunDecl funSerial (baseCtx: CcCtx) (ctx: CcCtx) =
  let ctx = ctx |> ccCtxStoreFunKnownCtx funSerial

  { ctx with
      Current =
        ctx.Current
        |> knownCtxLeaveFunDecl baseCtx.Current }

/// Gets a list of captured variable serials for a function
/// including referenced functions.
let private ccCtxGetFunCapturedSerials funSerial (ctx: CcCtx) =
  match ctx.Funs |> mapTryFind funSerial with
  | Some knownCtx -> knownCtx |> knownCtxToCapturedSerials

  | None -> setEmpty intCmp

/// Gets a list of captured variables for a function.
/// Doesn't include referenced functions.
let private ccCtxGetFunCaps funSerial (ctx: CcCtx): Caps =
  let chooseVars varSerials =
    varSerials
    |> List.choose (fun varSerial ->
         match ctx.Vars |> mapTryFind varSerial with
         | Some (VarDef (_, AutoSM, ty, loc)) -> Some(varSerial, ty, loc)

         | _ -> None)

  ctx
  |> ccCtxGetFunCapturedSerials funSerial
  |> setToList
  |> chooseVars

/// Extends the set of references to be transitive.
/// E.g. a function `f` uses `g` and `g` uses `h` (and `h` uses etc.),
///      we think `f` also uses `h`.
let private ccCtxClosureRefs (ctx: CcCtx): CcCtx =
  let emptySet = setEmpty intCmp

  let rec closureRefs refs ccCtx (modified, visited, acc) =
    match refs with
    | [] -> modified, visited, acc

    | varSerial :: refs when visited |> setContains varSerial -> (modified, visited, acc) |> closureRefs refs ccCtx

    | varSerial :: refs ->
        let visited = visited |> setAdd varSerial

        let modified =
          modified || (acc |> setContains varSerial |> not)

        let acc = acc |> setAdd varSerial

        let otherRefs =
          ccCtx
          |> ccCtxGetFunCapturedSerials varSerial
          |> setToList

        (modified, visited, acc)
        |> closureRefs otherRefs ccCtx
        |> closureRefs refs ccCtx

  let closureKnownCtx (modified, ccCtx) varSerial (knownCtx: KnownCtx) =
    let refs = knownCtx.Refs
    match (false, emptySet, refs)
          |> closureRefs (refs |> setToList) ccCtx with
    | true, _, refs ->
        let knownCtx = { knownCtx with Refs = refs }
        true,
        { ccCtx with
            Funs = ccCtx.Funs |> mapAdd varSerial knownCtx }

    | false, _, _ -> modified, ccCtx

  let rec closureFuns (modified, ccCtx: CcCtx) =
    if not modified then
      ccCtx
    else
      ccCtx.Funs
      |> mapFold closureKnownCtx (false, ccCtx)
      |> closureFuns

  closureFuns (true, ctx)

/// Applies the changes of function types.
let private ccCtxUpdateFunDefs (ctx: CcCtx) =
  let update vars varSerial (_: KnownCtx) =
    match ctx |> ccCtxGetFunCaps varSerial with
    | [] -> vars

    | caps ->
        match vars |> mapFind varSerial with
        | FunDef (ident, arity, TyScheme (fvs, funTy), loc) ->
            let funTy, arity = caps |> capsUpdateFunDef funTy arity
            let tyScheme = TyScheme(fvs, funTy)
            let varDef = FunDef(ident, arity, tyScheme, loc)
            vars |> mapAdd varSerial varDef

        | _ -> vars

  let vars = ctx.Funs |> mapFold update ctx.Vars

  { ctx with Vars = vars }

// -----------------------------------------------
// Caps
// -----------------------------------------------

/// Updates the function type to take captured variables.
let private capsAddToFunTy tTy (caps: Caps) =
  caps
  |> List.fold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the callee to take captured variables as arguments.
let private capsMakeApp calleeSerial calleeTy calleeLoc (caps: Caps) =
  let callee =
    let calleeTy = caps |> capsAddToFunTy calleeTy
    HRefExpr(calleeSerial, calleeTy, calleeLoc)

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
// Closure conversion routines
// -----------------------------------------------

let private declosureFunRef refVarSerial refTy refLoc ctx =
  // NOTE: No need to check whether it's a function
  //       because non-function caps are empty.
  let refExpr =
    ctx
    |> ccCtxGetFunCaps refVarSerial
    |> capsMakeApp refVarSerial refTy refLoc

  refExpr, ctx

let private declosureFunDecl callee vis isMainFun args body next ty loc ctx =
  let args, body, ctx =
    let baseCtx = ctx
    let ctx = ctx |> ccCtxEnterFunDecl

    let args, ctx = (args, ctx) |> stMap declosurePat
    let body, ctx = (body, ctx) |> declosureExpr

    let ctx = ctx |> ccCtxLeaveFunDecl callee baseCtx
    args, body, ctx

  let args =
    ctx
    |> ccCtxGetFunCaps callee
    |> capsAddToFunPats args

  let next, ctx = (next, ctx) |> declosureExpr
  HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc), ctx

let private declosureVariantDecl ctx variant =
  let (_, variantSerial, _, _) = variant
  ctx |> ccCtxAddKnown variantSerial

let private declosurePat (pat, ctx) =
  match pat with
  | HLitPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _
  | HDiscardPat _
  | HNavPat _ -> pat, ctx

  | HRefPat (serial, _, _) ->
      let ctx = ctx |> ccCtxAddLocal serial
      pat, ctx

  | HConsPat (l, r, itemTy, loc) ->
      let l, ctx = (l, ctx) |> declosurePat
      let r, ctx = (r, ctx) |> declosurePat
      HConsPat(l, r, itemTy, loc), ctx

  | HTuplePat (items, ty, loc) ->
      let items, ctx = (items, ctx) |> stMap declosurePat
      HTuplePat(items, ty, loc), ctx

  | HCallPat (callee, args, ty, loc) ->
      let callee, ctx = (callee, ctx) |> declosurePat
      let args, ctx = (args, ctx) |> stMap declosurePat
      HCallPat(callee, args, ty, loc), ctx

  | HBoxPat (itemPat, loc) ->
      let itemPat, ctx = (itemPat, ctx) |> declosurePat
      HBoxPat(itemPat, loc), ctx

  | HAsPat (pat, serial, loc) ->
      let ctx = ctx |> ccCtxAddLocal serial
      let pat, ctx = (pat, ctx) |> declosurePat
      HAsPat(pat, serial, loc), ctx

  | HAnnoPat (pat, ty, loc) ->
      let pat, ctx = (pat, ctx) |> declosurePat
      HAnnoPat(pat, ty, loc), ctx

  | HOrPat (first, second, ty, loc) ->
      let first, ctx = (first, ctx) |> declosurePat
      let second, ctx = (second, ctx) |> declosurePat
      HOrPat(first, second, ty, loc), ctx

let private declosureExpr (expr, ctx) =
  match expr with
  | HLitExpr _
  | HPrimExpr _
  | HOpenExpr _ -> expr, ctx

  | HRefExpr (serial, refTy, refLoc) ->
      let doArm () =
        let ctx = ctx |> ccCtxAddRef serial
        declosureFunRef serial refTy refLoc ctx

      doArm ()

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target, ctx = declosureExpr (target, ctx)

        let go ((pat, guard, body), ctx) =
          let pat, ctx = declosurePat (pat, ctx)
          let guard, ctx = declosureExpr (guard, ctx)
          let body, ctx = declosureExpr (body, ctx)
          (pat, guard, body), ctx

        let arms, ctx = (arms, ctx) |> stMap go
        HMatchExpr(target, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let l, ctx = declosureExpr (l, ctx)
        HNavExpr(l, r, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap declosureExpr
        HInfExpr(infOp, items, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let pat, ctx = declosurePat (pat, ctx)
        let body, ctx = declosureExpr (body, ctx)
        let next, ctx = declosureExpr (next, ctx)
        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      declosureFunDecl callee vis isMainFun args body next ty loc ctx

  | HTyDeclExpr (_, _, _, tyDecl, _) ->
      let doArm () =
        match tyDecl with
        | TySynonymDecl _
        | RecordTyDecl _ -> expr, ctx

        | UnionTyDecl (_, variants, _) ->
            let ctx =
              variants |> List.fold declosureVariantDecl ctx

            expr, ctx

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "Never: %s at %A" error loc
  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let declosure (expr, tyCtx: TyCtx) =
  let ccCtx = ccCtxFromTyCtx tyCtx

  // Traverse for reference collection.
  // NOTE: Converted expression is possibly incorrect
  //       because the set of captured variables is incomplete
  //       when to process a function reference before definition.
  let _, ccCtx = (expr, ccCtx) |> declosureExpr

  // Resolve transitive references.
  let ccCtx = ccCtx |> ccCtxClosureRefs

  // Traverse again to transform function references.
  let expr, ccCtx = (expr, ccCtx) |> declosureExpr

  let tyCtx =
    ccCtx
    |> ccCtxUpdateFunDefs
    |> ccCtxFeedbackToTyCtx tyCtx

  expr, tyCtx
