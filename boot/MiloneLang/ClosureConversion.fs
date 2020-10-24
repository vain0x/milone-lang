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
open MiloneLang.Records

/// List of captured variables.
/// Don't forget the case of empty.
type Caps = (VarSerial * Ty * Loc) list

// -----------------------------------------------
// KnownCtx
// -----------------------------------------------

let knownCtxEmpty (): KnownCtx =
  KnownCtx(setEmpty (intHash, intCmp), setEmpty (intHash, intCmp), setEmpty (intHash, intCmp))

let knownCtxEnterFunDecl (ctx: KnownCtx) =
  ctx
  |> knownCtxWithRefs (setEmpty (intHash, intCmp))
  |> knownCtxWithLocals (setEmpty (intHash, intCmp))

let knownCtxLeaveFunDecl (baseCtx: KnownCtx) (ctx: KnownCtx) =
  ctx
  |> knownCtxWithRefs (baseCtx |> knownCtxGetRefs)
  |> knownCtxWithLocals (baseCtx |> knownCtxGetLocals)

let knownCtxAddKnown serial (ctx: KnownCtx) =
  ctx
  |> knownCtxWithKnown (ctx |> knownCtxGetKnown |> setAdd serial)

let knownCtxAddLocal serial (ctx: KnownCtx) =
  ctx
  |> knownCtxWithLocals (ctx |> knownCtxGetLocals |> setAdd serial)

let knownCtxAddRef serial (ctx: KnownCtx) =
  ctx
  |> knownCtxWithRefs (ctx |> knownCtxGetRefs |> setAdd serial)

/// Returns serials referenced in the current context but not known nor locals
/// including function serials.
let knownCtxToCapturedSerials (ctx: KnownCtx): AssocSet<VarSerial> =
  let refs =
    setDiff (ctx |> knownCtxGetRefs) (ctx |> knownCtxGetLocals)

  let refs = setDiff refs (ctx |> knownCtxGetKnown)
  refs

// -----------------------------------------------
// CcCtx (ClosureConversionContext)
// -----------------------------------------------

let ccCtxFromTyCtx (ftCtx: TyCtx): CcCtx =
  CcCtx
    (ftCtx |> tyCtxGetSerial,
     ftCtx |> tyCtxGetVars,
     ftCtx |> tyCtxGetTys,

     knownCtxEmpty (),
     mapEmpty (intHash, intCmp))

let ccCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  tyCtx
  |> tyCtxWithSerial (ctx |> ccCtxGetSerial)
  |> tyCtxWithVars (ctx |> ccCtxGetVars)
  |> tyCtxWithTys (ctx |> ccCtxGetTys)

let ccCtxAddKnown funSerial (ctx: CcCtx) =
  ctx
  |> ccCtxWithCurrent
       (ctx
        |> ccCtxGetCurrent
        |> knownCtxAddKnown funSerial)

let ccCtxAddLocal varSerial (ctx: CcCtx) =
  ctx
  |> ccCtxWithCurrent
       (ctx
        |> ccCtxGetCurrent
        |> knownCtxAddLocal varSerial)

let ccCtxAddRef varSerial (ctx: CcCtx) =
  ctx
  |> ccCtxWithCurrent (ctx |> ccCtxGetCurrent |> knownCtxAddRef varSerial)

/// Called on leave function declaration to store the current known context.
let ccCtxStoreFunKnownCtx funSerial (ctx: CcCtx) =
  let ctx = ctx |> ccCtxAddKnown funSerial

  // Don't update in the second traversal for transformation.
  let funs = ctx |> ccCtxGetFuns
  if funs |> mapContainsKey funSerial then
    ctx
  else
    ctx
    |> ccCtxWithFuns (funs |> mapAdd funSerial (ctx |> ccCtxGetCurrent))

let ccCtxEnterFunDecl (ctx: CcCtx) =
  ctx
  |> ccCtxWithCurrent (ctx |> ccCtxGetCurrent |> knownCtxEnterFunDecl)

let ccCtxLeaveFunDecl funSerial (baseCtx: CcCtx) (ctx: CcCtx) =
  let ctx = ctx |> ccCtxStoreFunKnownCtx funSerial

  ctx
  |> ccCtxWithCurrent
       (ctx
        |> ccCtxGetCurrent
        |> knownCtxLeaveFunDecl (baseCtx |> ccCtxGetCurrent))

/// Gets a list of captured variable serials for a function
/// including referenced functions.
let ccCtxGetFunCapturedSerials funSerial (ctx: CcCtx) =
  match ctx |> ccCtxGetFuns |> mapTryFind funSerial with
  | Some knownCtx -> knownCtx |> knownCtxToCapturedSerials

  | None -> setEmpty (intHash, intCmp)

/// Gets a list of captured variables for a function.
/// Doesn't include referenced functions.
let ccCtxGetFunCaps funSerial (ctx: CcCtx): Caps =
  let chooseVars varSerials =
    varSerials
    |> listChoose (fun varSerial ->
         match ctx |> ccCtxGetVars |> mapTryFind varSerial with
         | Some (VarDef.Var (_, AutoSM, ty, loc)) -> Some(varSerial, ty, loc)

         | _ -> None)

  ctx
  |> ccCtxGetFunCapturedSerials funSerial
  |> setToList
  |> chooseVars

/// Extends the set of references to be transitive.
/// E.g. a function `f` uses `g` and `g` uses `h` (and `h` uses etc.),
///      we think `f` also uses `h`.
let ccCtxClosureRefs (ctx: CcCtx): CcCtx =
  let emptySet = setEmpty (intHash, intCmp)

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

  let closureKnownCtx (modified, ccCtx) varSerial knownCtx =
    let refs = knownCtx |> knownCtxGetRefs
    match (false, emptySet, refs)
          |> closureRefs (refs |> setToList) ccCtx with
    | true, _, refs ->
        let knownCtx = knownCtx |> knownCtxWithRefs refs
        true,
        ccCtx
        |> ccCtxWithFuns (ccCtx |> ccCtxGetFuns |> mapAdd varSerial knownCtx)

    | false, _, _ -> modified, ccCtx

  let rec closureFuns (modified, ccCtx) =
    if not modified then
      ccCtx
    else
      ccCtx
      |> ccCtxGetFuns
      |> mapFold closureKnownCtx (false, ccCtx)
      |> closureFuns

  closureFuns (true, ctx)

/// Applies the changes of function types.
let ccCtxUpdateFunDefs (ctx: CcCtx) =
  let update vars varSerial (_: KnownCtx) =
    match ctx |> ccCtxGetFunCaps varSerial with
    | [] -> vars

    | caps ->
        match vars |> mapFind varSerial with
        | VarDef.Fun (ident, arity, TyScheme.ForAll (fvs, funTy), loc) ->
            let funTy, arity = caps |> capsUpdateFunDef funTy arity
            let tyScheme = TyScheme.ForAll(fvs, funTy)
            let varDef = VarDef.Fun(ident, arity, tyScheme, loc)
            vars |> mapAdd varSerial varDef

        | _ -> vars

  let vars =
    ctx
    |> ccCtxGetFuns
    |> mapFold update (ctx |> ccCtxGetVars)

  ctx |> ccCtxWithVars vars

// -----------------------------------------------
// Caps
// -----------------------------------------------

/// Updates the function type to take captured variables.
let capsAddToFunTy tTy (caps: Caps) =
  caps
  |> listFold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the callee to take captured variables as arguments.
let capsMakeApp calleeSerial calleeTy calleeLoc (caps: Caps) =
  let callee =
    let calleeTy = caps |> capsAddToFunTy calleeTy
    HExpr.Ref(calleeSerial, calleeTy, calleeLoc)

  let app, _ =
    caps
    |> listRev
    |> listFold (fun (callee, calleeTy) (serial, ty, loc) ->
         let arg = HExpr.Ref(serial, ty, loc)
         hxApp callee arg calleeTy loc, tyFun ty calleeTy) (callee, calleeTy)

  app

/// Updates the argument patterns to take captured variables.
let capsAddToFunPats args (caps: Caps) =
  caps
  |> listFold (fun args (serial, ty, loc) -> HPat.Ref(serial, ty, loc) :: args) args

let capsUpdateFunDef funTy arity (caps: Caps) =
  let funTy = caps |> capsAddToFunTy funTy
  let arity = arity + listLength caps
  funTy, arity

// -----------------------------------------------
// Closure conversion routines
// -----------------------------------------------

let declosureFunRef refVarSerial refTy refLoc ctx =
  // NOTE: No need to check whether it's a function
  //       because non-function caps are empty.
  let refExpr =
    ctx
    |> ccCtxGetFunCaps refVarSerial
    |> capsMakeApp refVarSerial refTy refLoc

  refExpr, ctx

let declosureFunDecl callee vis isMainFun args body next ty loc ctx =
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
  HExpr.LetFun(callee, vis, isMainFun, args, body, next, ty, loc), ctx

let declosureVariantDecl ctx variant =
  let (_, variantSerial, _, _) = variant
  ctx |> ccCtxAddKnown variantSerial

let declosurePat (pat, ctx) =
  match pat with
  | HPat.Lit _
  | HPat.Nil _
  | HPat.OptionNone _
  | HPat.OptionSome _
  | HPat.Discard _
  | HPat.Nav _ -> pat, ctx

  | HPat.Ref (serial, _, _) ->
      let ctx = ctx |> ccCtxAddLocal serial
      pat, ctx

  | HPat.Cons (l, r, itemTy, loc) ->
      let l, ctx = (l, ctx) |> declosurePat
      let r, ctx = (r, ctx) |> declosurePat
      HPat.Cons(l, r, itemTy, loc), ctx

  | HPat.Tuple (items, ty, loc) ->
      let items, ctx = (items, ctx) |> stMap declosurePat
      HPat.Tuple(items, ty, loc), ctx

  | HPat.Call (callee, args, ty, loc) ->
      let callee, ctx = (callee, ctx) |> declosurePat
      let args, ctx = (args, ctx) |> stMap declosurePat
      HPat.Call(callee, args, ty, loc), ctx

  | HPat.As (pat, serial, loc) ->
      let ctx = ctx |> ccCtxAddLocal serial
      let pat, ctx = (pat, ctx) |> declosurePat
      HPat.As(pat, serial, loc), ctx

  | HPat.Anno (pat, ty, loc) ->
      let pat, ctx = (pat, ctx) |> declosurePat
      HPat.Anno(pat, ty, loc), ctx

  | HPat.Or (first, second, ty, loc) ->
      let first, ctx = (first, ctx) |> declosurePat
      let second, ctx = (second, ctx) |> declosurePat
      HPat.Or(first, second, ty, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | HExpr.Lit _
  | HExpr.Prim _
  | HExpr.Open _ -> expr, ctx

  | HExpr.Ref (serial, refTy, refLoc) ->
      let doArm () =
        let ctx = ctx |> ccCtxAddRef serial
        declosureFunRef serial refTy refLoc ctx

      doArm ()

  | HExpr.Match (target, arms, ty, loc) ->
      let doArm () =
        let target, ctx = declosureExpr (target, ctx)

        let go ((pat, guard, body), ctx) =
          let pat, ctx = declosurePat (pat, ctx)
          let guard, ctx = declosureExpr (guard, ctx)
          let body, ctx = declosureExpr (body, ctx)
          (pat, guard, body), ctx

        let arms, ctx = (arms, ctx) |> stMap go
        HExpr.Match(target, arms, ty, loc), ctx

      doArm ()

  | HExpr.Nav (l, r, ty, loc) ->
      let doArm () =
        let l, ctx = declosureExpr (l, ctx)
        HExpr.Nav(l, r, ty, loc), ctx

      doArm ()

  | HExpr.Inf (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap declosureExpr
        HExpr.Inf(infOp, items, ty, loc), ctx

      doArm ()

  | HExpr.Let (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let pat, ctx = declosurePat (pat, ctx)
        let body, ctx = declosureExpr (body, ctx)
        let next, ctx = declosureExpr (next, ctx)
        HExpr.Let(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HExpr.LetFun (callee, vis, isMainFun, args, body, next, ty, loc) ->
      declosureFunDecl callee vis isMainFun args body next ty loc ctx

  | HExpr.TyDecl (_, _, tyDecl, _) ->
      let doArm () =
        match tyDecl with
        | TyDecl.Synonym _ -> expr, ctx

        | TyDecl.Union (_, variants, _) ->
            let ctx =
              variants |> listFold declosureVariantDecl ctx

            expr, ctx

      doArm ()

  | HExpr.Error (error, loc) -> failwithf "Never: %s at %A" error loc
  | HExpr.Module _ -> failwith "NEVER: module is resolved in name res"

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
