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

/// Closure conversion context.
[<RequireQualifiedAccess>]
type CcCtx =
  {
    Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>

    /// Known identifiers and their dependencies.
    Caps: AssocMap<FunSerial, (VarSerial * Ty * Loc) list>
    Known: Set<FunSerial>
    Refs: Set<VarSerial>
    Locals: Set<VarSerial>
  }

let ccCtxFromTyCtx (ftCtx: TyCtx): CcCtx =
  {
    Serial = ftCtx |> tyCtxGetSerial
    Vars = ftCtx |> tyCtxGetVars
    Tys = ftCtx |> tyCtxGetTys

    Caps = mapEmpty intCmp
    Known = Set.empty
    Refs = Set.empty
    Locals = Set.empty
  }

let ccCtxFeedbackToTyCtx (tyCtx: TyCtx) (ctx: CcCtx) =
  tyCtx
  |> tyCtxWithSerial ctx.Serial
  |> tyCtxWithVars ctx.Vars
  |> tyCtxWithTys ctx.Tys

let ccCtxPushScope locals (ctx: CcCtx) =
  { ctx with
      Refs = Set.empty
      Locals = locals |> Set.ofList
  }

let ccCtxPopScope (baseCtx: CcCtx) (derivedCtx: CcCtx) =
  { derivedCtx with
      Refs = baseCtx.Refs
      Locals = baseCtx.Locals
  }

let ccCtxAddKnown serial (ctx: CcCtx) =
  { ctx with Known = Set.add serial ctx.Known }

let ccCtxAddRef serial (ctx: CcCtx) =
  { ctx with Refs = Set.add serial ctx.Refs }

let ccCtxAddLocal serial (ctx: CcCtx) =
  { ctx with Locals = Set.add serial ctx.Locals }

let ccCtxAddFun serial caps (ctx: CcCtx) =
  { ctx with
      Known = ctx.Known |> Set.add serial
      Caps = ctx.Caps |> mapAdd serial caps
  }

/// Gets the captured variables of the current function.
let ccCtxGetCaps (ctx: CcCtx) =
  let refs = Set.difference ctx.Refs ctx.Locals
  let refs = Set.difference refs ctx.Known

  refs |> Set.toList |> listChoose
    (fun serial ->
      match ctx.Vars |> mapFind serial with
      | VarDef.Var (_, ty, loc) ->
        Some (serial, ty, loc)
      | _ ->
        None
    )

/// Updates the function type to take additional arguments
/// for each captured variable.
let capsAddToFunTy tTy caps =
  caps |> listFold (fun tTy (_, sTy, _) -> tyFun sTy tTy) tTy

/// Updates the arguments of a call to pass captured variables.
let capsAddToCallArgs args caps =
  caps |> listFold (fun args (serial, ty, loc) ->
    HExpr.Ref (serial, ty, loc) :: args
  ) args

/// Updates the arguments of a function to take captured variables.
let capsAddToFunPats args caps =
  caps |> listFold (fun args (serial, ty, loc) ->
    HPat.Ref (serial, ty, loc) :: args
  ) args

let capsUpdateFunDef funTy arity caps =
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

let declosureExprRefAsCallee serial (expr, ctx) =
  let ctx = ctx |> ccCtxAddRef serial
  expr, ctx

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ccCtxAddRef serial
  match ctx.Caps |> mapTryFind serial with
  | Some (_ :: _) ->
    let resultTy, loc = exprExtract expr
    match declosureCall expr [] resultTy loc ctx with
    | Some (expr, ctx) -> expr, ctx
    | None -> expr, ctx
  | _ ->
    expr, ctx

let declosureCall callee args resultTy loc (ctx: CcCtx) =
  match callee with
  | HExpr.Ref (callee, calleeTy, refLoc) ->
    match ctx.Caps |> mapTryFind callee with
    | Some (_ :: _ as caps) ->
      // Add caps arg.
      let args = caps |> capsAddToCallArgs args
      let calleeTy = caps |> capsAddToFunTy calleeTy

      // Count captured variables as occurrences too.
      let ctx = caps |> listFold (fun ctx (serial, _, _) -> ctx |> ccCtxAddRef serial) ctx

      let callee = HExpr.Ref (callee, calleeTy, refLoc)
      (hxCallProc callee args resultTy loc, ctx) |> Some
    | _ ->
      None
  | _ ->
    None

let declosureExprCall callee args resultTy loc (ctx: CcCtx) =
  let callee, ctx =
    match callee with
    | HExpr.Ref (serial, _, _) ->
      (callee, ctx) |> declosureExprRefAsCallee serial
    | _ ->
      (callee, ctx) |> declosureExpr
  let args, ctx = (args, ctx) |> stMap declosureExpr
  match declosureCall callee args resultTy loc ctx with
  | Some (expr, ctx) ->
    expr, ctx
  | None ->
    hxCallProc callee args resultTy loc, ctx

let declosureExprApp expr resultTy loc ctx =
  /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
  let rec roll acc callee =
    match callee with
    | HExpr.Inf (InfOp.App, [callee; arg], _, _) ->
      roll (arg :: acc) callee
    | _ ->
      callee, acc
  let callee, args = roll [] expr
  declosureExprCall callee args resultTy loc ctx

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
  let caps = ctx |> ccCtxGetCaps
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

let declosureExprInf ctx expr infOp items ty loc =
  match infOp with
  | InfOp.App ->
    declosureExprApp expr ty loc ctx
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
  | HExpr.Ref (serial, _, _) ->
    declosureExprRef serial (expr, ctx)
  | HExpr.Match (target, arms, ty, loc) ->
    declosureExprMatch target arms ty loc ctx
  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = declosureExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx
  | HExpr.Inf (infOp, items, ty, loc) ->
    declosureExprInf ctx expr infOp items ty loc
  | HExpr.Let (pat, body, next, ty, loc) ->
    declosureExprLetVal pat body next ty loc ctx
  | HExpr.LetFun (callee, isMainFun, args, body, next, ty, loc) ->
    declosureExprLetFun callee isMainFun args body next ty loc ctx
  | HExpr.TyDecl (_, tyDecl, _) ->
    declosureExprTyDecl expr tyDecl ctx
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosureUpdateFuns (ctx: CcCtx) =
  let update vars varSerial caps =
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

  let vars = ctx.Caps |> mapFold update ctx.Vars
  { ctx with Vars = vars }

let declosureUpdateCtx (expr, ctx) =
  let ctx = ctx |> declosureUpdateFuns
  expr, ctx

let declosure (expr, tyCtx: TyCtx) =
  let ccCtx = ccCtxFromTyCtx tyCtx
  let expr, ccCtx = (expr, ccCtx) |> declosureExpr |> declosureUpdateCtx
  let tyCtx = ccCtx |> ccCtxFeedbackToTyCtx tyCtx
  expr, tyCtx
