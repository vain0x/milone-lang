/// ## Declosure: Closure conversion
///
/// Performs closure conversion to make all functions be context-free.
///
/// Function definitions may use out-side local variables.
/// We call these variables *variables captured by the function* .
///
/// In this stage, we calculate captured variables
/// by listing all variable references occurred in function bodies
/// and local variables defined in function bodies.
/// See `ctxCaps`.
///
/// Capturing function definitions are converted to take additional args
/// to receive captured variables.
///
/// Calls to functions are also converted to pass corresponding args.
///
/// Note we refer to context-free functions as *procedures* (or proc).
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
  KnownCtx (
    setEmpty (intHash, intCmp),
    setEmpty (intHash, intCmp),
    setEmpty (intHash, intCmp)
  )

let knownCtxEnterScope (ctx: KnownCtx) =
  ctx
  |> knownCtxWithRefs (setEmpty (intHash, intCmp))
  |> knownCtxWithLocals (setEmpty (intHash, intCmp))

let knownCtxLeaveScope (baseCtx: KnownCtx) (ctx: KnownCtx) =
  ctx
  |> knownCtxWithRefs (baseCtx |> knownCtxGetRefs)
  |> knownCtxWithLocals (baseCtx |> knownCtxGetLocals)

let knownCtxAddKnown serial (ctx: KnownCtx) =
  ctx |> knownCtxWithKnown (ctx |> knownCtxGetKnown |> setAdd serial)

let knownCtxAddLocal serial (ctx: KnownCtx) =
  ctx |> knownCtxWithLocals (ctx |> knownCtxGetLocals |> setAdd serial)

let knownCtxAddRef serial (ctx: KnownCtx) =
  ctx |> knownCtxWithRefs (ctx |> knownCtxGetRefs |> setAdd serial)

/// Returns serials referenced in the current context but not known nor locals
/// including function serials.
let knownCtxToCapturedSerials (ctx: KnownCtx): AssocSet<VarSerial> =
  let refs = setDiff (ctx |> knownCtxGetRefs) (ctx |> knownCtxGetLocals)
  let refs = setDiff refs (ctx |> knownCtxGetKnown)
  refs

// -----------------------------------------------
// CcCtx (ClosureConversionContext)
// -----------------------------------------------

let ccCtxFromTyCtx (ftCtx: TyCtx): CcCtx =
  CcCtx (
    ftCtx |> tyCtxGetSerial,
    ftCtx |> tyCtxGetVars,
    ftCtx |> tyCtxGetTys,

    knownCtxEmpty (),
    mapEmpty (intHash, intCmp)
  )

let ccCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  tyCtx
  |> tyCtxWithSerial (ctx |> ccCtxGetSerial)
  |> tyCtxWithVars (ctx |> ccCtxGetVars)
  |> tyCtxWithTys (ctx |> ccCtxGetTys)

let ccCtxPushScope _locals (ctx: CcCtx) =
  ctx |> ccCtxWithCurrent (
    ctx
    |> ccCtxGetCurrent
    |> knownCtxEnterScope
  )

let ccCtxPopScope (baseCtx: CcCtx) (derivedCtx: CcCtx) =
  derivedCtx |> ccCtxWithCurrent (
    derivedCtx
    |> ccCtxGetCurrent
    |> knownCtxLeaveScope (baseCtx |> ccCtxGetCurrent)
  )

let ccCtxAddKnown funSerial (ctx: CcCtx) =
  ctx |> ccCtxWithCurrent (ctx |> ccCtxGetCurrent |> knownCtxAddKnown funSerial)

let ccCtxAddLocal varSerial (ctx: CcCtx) =
  ctx |> ccCtxWithCurrent (ctx |> ccCtxGetCurrent |> knownCtxAddLocal varSerial)

let ccCtxAddRef varSerial (ctx: CcCtx) =
  ctx |> ccCtxWithCurrent (ctx |> ccCtxGetCurrent |> knownCtxAddRef varSerial)

/// Called on leave function declaration to store the current known context.
let ccCtxLeaveFunDecl funSerial (ctx: CcCtx) =
  let ctx = ctx |> ccCtxAddKnown funSerial

  // Update only first traversal.
  let funs = ctx |> ccCtxGetFuns
  if funs |> mapContainsKey funSerial then
    ctx
  else
    ctx |> ccCtxWithFuns (funs |> mapAdd funSerial (ctx |> ccCtxGetCurrent))

/// Gets a list of captured variable serials for a function.
let ccCtxGetFunCapturedSerials funSerial (ctx: CcCtx) =
  match ctx |> ccCtxGetFuns |> mapTryFind funSerial with
  | Some knownCtx ->
    knownCtx |> knownCtxToCapturedSerials

  | None ->
    setEmpty (intHash, intCmp)

let ccCtxGetFunCaps funSerial (ctx: CcCtx): Caps =
  let chooseVars varSerials =
    varSerials |> listChoose (fun varSerial ->
      match ctx |> ccCtxGetVars |> mapTryFind varSerial with
      | Some (VarDef.Var (_, ty, loc)) ->
        Some (varSerial, ty, loc)

      | _ ->
        None
    )

  ctx
  |> ccCtxGetFunCapturedSerials funSerial
  |> setToList
  |> chooseVars

/// Extends the list of references to include transitive references.
/// E.g. a function `f` uses `g` and `g` uses `h` (and `h` uses etc.),
///      we think `f` also uses `h`.
let ccCtxClosureRefs (ctx: CcCtx): CcCtx =
  let emptySet = setEmpty (intHash, intCmp)

  let rec closureRefs refs ccCtx (modified, visited, acc) =
    match refs with
    | [] ->
      modified, visited, acc

    | varSerial :: refs
      when visited |> setContains varSerial ->
      (modified, visited, acc) |> closureRefs refs ccCtx

    | varSerial :: refs ->
      let visited = visited |> setAdd varSerial
      let modified = modified || (acc |> setContains varSerial |> not)
      let acc = acc |> setAdd varSerial
      let otherRefs = ccCtx |> ccCtxGetFunCapturedSerials varSerial |> setToList
      (modified, visited, acc)
      |> closureRefs otherRefs ccCtx
      |> closureRefs refs ccCtx

  let closureKnownCtx (modified, ccCtx) varSerial knownCtx =
    let refs = knownCtx |> knownCtxGetRefs
    match (false, emptySet, refs) |> closureRefs (refs |> setToList) ccCtx with
    | true, _, refs ->
      let knownCtx = knownCtx |> knownCtxWithRefs refs
      true, ccCtx |> ccCtxWithFuns (ccCtx |> ccCtxGetFuns |> mapAdd varSerial knownCtx)

    | false, _, _ ->
      modified, ccCtx

  let rec closureFuns (modified, ccCtx) =
    if not modified then
      ccCtx
    else
      ccCtx
      |> ccCtxGetFuns
      |> mapFold closureKnownCtx (false, ccCtx)
      |> closureFuns

  closureFuns (true, ctx)

// -----------------------------------------------
// Caps
// -----------------------------------------------

/// Updates the function type to take additional arguments
/// for each captured variable.
let capsAddToFunTy tTy (caps: Caps) =
  caps |> listFold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the callee to take captured variables.
let capsMakeApp calleeSerial calleeTy calleeLoc (caps: Caps) =
  let callee =
    let calleeTy = caps |> capsAddToFunTy calleeTy
    HExpr.Ref (calleeSerial, calleeTy, calleeLoc)
  let app, _ =
    // NOTE: Reverse to preserve the output.
    caps |> listRev |> listFold (fun (callee, calleeTy) (serial, ty, loc) ->
      let arg = HExpr.Ref (serial, ty, loc)
      hxApp callee arg calleeTy loc, tyFun ty calleeTy
    ) (callee, calleeTy)
  app

/// Updates the arguments of a function to take captured variables.
let capsAddToFunPats args (caps: Caps) =
  caps |> listFold (fun args (serial, ty, loc) ->
    HPat.Ref (serial, ty, loc) :: args
  ) args

let capsUpdateFunDef funTy arity (caps: Caps) =
  let funTy = caps |> capsAddToFunTy funTy
  let arity = arity + listLength caps
  funTy, arity

// -----------------------------------------------
// Closure conversion routines
// -----------------------------------------------

/// Converts a function reference.
/// If a function `f` captures `x` and `y`,
/// each reference of `f` are replaced with an application `f x y`.
let declosureFunRef refVarSerial refTy refLoc ctx =
  let refExpr =
    ctx
    |> ccCtxGetFunCaps refVarSerial
    |> capsMakeApp refVarSerial refTy refLoc
  refExpr, ctx

let declosureFunDecl callee isMainFun args body next ty loc ctx =
  let args, body, ctx =
    let baseCtx = ctx
    let ctx = ctx |> ccCtxPushScope []

    let args, ctx = (args, ctx) |> stMap declosurePat
    let body, ctx = (body, ctx) |> declosureExpr

    let ctx = ctx |> ccCtxLeaveFunDecl callee |> ccCtxPopScope baseCtx
    args, body, ctx

  let args = ctx |> ccCtxGetFunCaps callee |> capsAddToFunPats args
  let next, ctx = (next, ctx) |> declosureExpr
  HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc), ctx

let declosurePat (pat, ctx) =
  match pat with
  | HPat.Lit _
  | HPat.Nil _
  | HPat.OptionNone _
  | HPat.OptionSome _
  | HPat.Discard _
  | HPat.Nav _ ->
    pat, ctx
  | HPat.Ref (serial, _, _) ->
    let ctx = ctx |> ccCtxAddLocal serial
    pat, ctx
  | HPat.Cons (l, r, itemTy, loc) ->
    let l, ctx = (l, ctx) |> declosurePat
    let r, ctx = (r, ctx) |> declosurePat
    HPat.Cons (l, r, itemTy, loc), ctx
  | HPat.Tuple (items, ty, loc) ->
    let items, ctx = (items, ctx) |> stMap declosurePat
    HPat.Tuple (items, ty, loc), ctx
  | HPat.Call (callee, args, ty, loc) ->
    let callee, ctx = (callee, ctx) |> declosurePat
    let args, ctx = (args, ctx) |> stMap declosurePat
    HPat.Call (callee, args, ty, loc), ctx
  | HPat.As (pat, serial, loc) ->
    let ctx = ctx |> ccCtxAddLocal serial
    let pat, ctx = (pat, ctx) |> declosurePat
    HPat.As (pat, serial, loc), ctx
  | HPat.Anno (pat, ty, loc) ->
    let pat, ctx = (pat, ctx) |> declosurePat
    HPat.Anno (pat, ty, loc), ctx
  | HPat.Or (first, second, ty, loc) ->
    let first, ctx = (first, ctx) |> declosurePat
    let second, ctx = (second, ctx) |> declosurePat
    HPat.Or (first, second, ty, loc), ctx

let declosureExprLetVal pat init next ty loc ctx =
  let pat, ctx = declosurePat (pat, ctx)
  let init, ctx = declosureExpr (init, ctx)
  let next, ctx = declosureExpr (next, ctx)
  HExpr.Let (pat, init, next, ty, loc), ctx

let declosureExprTyDecl expr tyDecl ctx =
  match tyDecl with
  | TyDecl.Synonym _ ->
    expr, ctx
  | TyDecl.Union (_, variants, _) ->
    let ctx =
      variants |> listFold (fun ctx (_, variantSerial, _, _) ->
        ctx |> ccCtxAddKnown variantSerial
      ) ctx
    expr, ctx

let declosureExprInf ctx infOp items ty loc =
  let items, ctx = (items, ctx) |> stMap declosureExpr
  HExpr.Inf (infOp, items, ty, loc), ctx

let declosureExprMatch target arms ty loc ctx =
  let target, ctx = declosureExpr (target, ctx)
  let go ((pat, guard, body), ctx) =
    let pat, ctx = declosurePat (pat, ctx)
    let guard, ctx = declosureExpr (guard, ctx)
    let body, ctx = declosureExpr (body, ctx)
    (pat, guard, body), ctx
  let arms, ctx = (arms, ctx) |> stMap go
  HExpr.Match (target, arms, ty, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | HExpr.Open _
  | HExpr.Lit _
  | HExpr.Prim _ ->
    expr, ctx
  | HExpr.Ref (serial, refTy, refLoc) ->
    let ctx = ctx |> ccCtxAddRef serial
    declosureFunRef serial refTy refLoc ctx
  | HExpr.Match (target, arms, ty, loc) ->
    declosureExprMatch target arms ty loc ctx
  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = declosureExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx
  | HExpr.Inf (infOp, items, ty, loc) ->
    declosureExprInf ctx infOp items ty loc
  | HExpr.Let (pat, body, next, ty, loc) ->
    declosureExprLetVal pat body next ty loc ctx
  | HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc) ->
    declosureFunDecl callee isMainFun args body next ty loc ctx
  | HExpr.TyDecl (_, tyDecl, _) ->
    declosureExprTyDecl expr tyDecl ctx
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosureUpdateFuns (ctx: CcCtx) =
  let update vars varSerial _ =
    match ctx |> ccCtxGetFunCaps varSerial with
    | [] ->
      vars

    | caps ->
      match vars |> mapFind varSerial with
      | VarDef.Fun (ident, arity, TyScheme.ForAll (fvs, funTy), loc) ->
        let funTy, arity = caps |> capsUpdateFunDef funTy arity
        let tyScheme = TyScheme.ForAll (fvs, funTy)
        let varDef = VarDef.Fun (ident, arity, tyScheme, loc)
        vars |> mapAdd varSerial varDef

      | _ ->
        vars

  let vars = ctx |> ccCtxGetFuns |> mapFold update (ctx |> ccCtxGetVars)
  ctx |> ccCtxWithVars vars

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

  let tyCtx = ccCtx |> declosureUpdateFuns |> ccCtxFeedbackToTyCtx tyCtx
  expr, tyCtx
