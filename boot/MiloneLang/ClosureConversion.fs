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

type Caps = (VarSerial * Ty * Loc) list

let ccCtxFromTyCtx (ftCtx: TyCtx): CcCtx =
  CcCtx (
    ftCtx |> tyCtxGetSerial,
    ftCtx |> tyCtxGetVars,
    ftCtx |> tyCtxGetTys,

    mapEmpty (intHash, intCmp),
    setEmpty (intHash, intCmp),
    setEmpty (intHash, intCmp),
    setEmpty (intHash, intCmp)
  )

let ccCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  tyCtx
  |> tyCtxWithSerial (ctx |> ccCtxGetSerial)
  |> tyCtxWithVars (ctx |> ccCtxGetVars)
  |> tyCtxWithTys (ctx |> ccCtxGetTys)

let ccCtxPushScope locals (ctx: CcCtx) =
  ctx
  |> ccCtxWithRefs (setEmpty (intHash, intCmp))
  |> ccCtxWithLocals (locals |> setOfList (intHash, intCmp))

let ccCtxPopScope (baseCtx: CcCtx) (derivedCtx: CcCtx) =
  derivedCtx
  |> ccCtxWithRefs (baseCtx |> ccCtxGetRefs)
  |> ccCtxWithLocals (baseCtx |> ccCtxGetLocals)

let ccCtxAddKnown serial (ctx: CcCtx) =
  ctx |> ccCtxWithKnown (ctx |> ccCtxGetKnown |> setAdd serial)

let ccCtxAddRef serial (ctx: CcCtx) =
  ctx |> ccCtxWithRefs (ctx |> ccCtxGetRefs |> setAdd serial)

let ccCtxAddLocal serial (ctx: CcCtx) =
  ctx |> ccCtxWithLocals (ctx |> ccCtxGetLocals |> setAdd serial)

let ccCtxAddFun serial (caps: Caps) (ctx: CcCtx) =
  ctx
  |> ccCtxWithKnown (ctx |> ccCtxGetKnown |> setAdd serial)
  |> ccCtxWithCaps (ctx |> ccCtxGetCaps |> mapAdd serial caps)

/// Gets the captured variables of the current function.
let ccCtxGetCurrentCaps (ctx: CcCtx): _ list =
  let refs = setDiff (ctx |> ccCtxGetRefs) (ctx |> ccCtxGetLocals)
  let refs = setDiff refs (ctx |> ccCtxGetKnown)

  refs |> setToList |> listChoose (fun serial ->
      match ctx |> ccCtxGetVars |> mapFind serial with
      | VarDef.Var (_, ty, loc) ->
        Some (serial, ty, loc)
      | _ ->
        None
    )

/// Updates the function type to take additional arguments
/// for each captured variable.
let capsAddToFunTy tTy (caps: Caps) =
  caps |> listFold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the callee to take captured variables.
let capsAddToApp calleeSerial calleeTy calleeLoc (caps: Caps) =
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

let declosureExprRef serial refTy refLoc (expr, ctx) =
  let ctx = ctx |> ccCtxAddRef serial
  declosureCall expr serial refTy refLoc ctx

/// Converts a called ref to an app expression that takes the captured variables.
let declosureCall callee calleeSerial calleeTy calleeLoc ctx =
  match ctx |> ccCtxGetCaps |> mapTryFind calleeSerial with
  | Some (_ :: _ as caps) ->
    // Build a callee partially applied.
    let callee = caps |> capsAddToApp calleeSerial calleeTy calleeLoc

    // Count captured variables as occurrences too.
    let ctx = caps |> listFold (fun ctx (serial, _, _) -> ctx |> ccCtxAddRef serial) ctx
    callee, ctx
  | _ ->
    callee, ctx

let declosureExprApp callee arg resultTy loc ctx =
  let callee, arg, ctx =
    match callee with
    | HExpr.Ref (calleeSerial, calleeTy, calleeLoc) ->
      let ctx = ctx |> ccCtxAddRef calleeSerial
      let arg, ctx = (arg, ctx) |> declosureExpr
      let callee, ctx = declosureCall callee calleeSerial calleeTy calleeLoc ctx
      callee, arg, ctx

    | _ ->
      let callee, ctx = (callee, ctx) |> declosureExpr
      let arg, ctx = (arg, ctx) |> declosureExpr
      callee, arg, ctx

  hxApp callee arg resultTy loc, ctx

let declosureExprLetVal pat init next ty loc ctx =
  let pat, ctx = declosurePat (pat, ctx)
  let init, ctx = declosureExpr (init, ctx)
  let next, ctx = declosureExpr (next, ctx)
  HExpr.Let (pat, init, next, ty, loc), ctx

let declosureFunBody callee args body ctx =
  let baseCtx = ctx
  let ctx = ctx |> ccCtxPushScope []

  // Traverse for dependency collection.
  let args, ctx = (args, ctx) |> stMap declosurePat
  let _, ctx = (body, ctx) |> declosureExpr
  let caps = ctx |> ccCtxGetCurrentCaps
  let ctx = ctx |> ccCtxAddFun callee caps

  // Traverse again. We can now convert recursive calls correctly.
  let args, ctx = (args, ctx) |> stMap declosurePat
  let body, ctx = (body, ctx) |> declosureExpr

  let ctx = ctx |> ccCtxPopScope baseCtx
  caps, args, body, ctx

let declosureExprLetFun callee isMainFun args body next ty loc ctx =
  let caps, args, body, ctx =
    declosureFunBody callee args body ctx
  let args=
    caps |> capsAddToFunPats args
  let next, ctx =
    declosureExpr (next, ctx)
  HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc), ctx

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
  match infOp, items with
  | InfOp.App, [callee; arg] ->
    declosureExprApp callee arg ty loc ctx
  | _ ->
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
    declosureExprRef serial refTy refLoc (expr, ctx)
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
    declosureExprLetFun callee isMainFun args body next ty loc ctx
  | HExpr.TyDecl (_, tyDecl, _) ->
    declosureExprTyDecl expr tyDecl ctx
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosureUpdateFuns (ctx: CcCtx) =
  let update vars varSerial (caps: Caps) =
    match caps with
    | [] ->
      vars

    | _ ->
      match vars |> mapFind varSerial with
      | VarDef.Fun (ident, arity, TyScheme.ForAll (fvs, funTy), loc) ->
        let funTy, arity = caps |> capsUpdateFunDef funTy arity
        let tyScheme = TyScheme.ForAll (fvs, funTy)
        let varDef = VarDef.Fun (ident, arity, tyScheme, loc)
        vars |> mapAdd varSerial varDef

      | _ ->
        vars

  let vars = ctx |> ccCtxGetCaps |> mapFold update (ctx |> ccCtxGetVars)
  ctx |> ccCtxWithVars vars

let declosureUpdateCtx (expr, ctx) =
  let ctx = ctx |> declosureUpdateFuns
  expr, ctx

let declosure (expr, tyCtx: TyCtx) =
  let ccCtx = ccCtxFromTyCtx tyCtx
  let expr, ccCtx = (expr, ccCtx) |> declosureExpr |> declosureUpdateCtx
  let tyCtx = ccCtx |> ccCtxFeedbackToTyCtx tyCtx
  expr, tyCtx
