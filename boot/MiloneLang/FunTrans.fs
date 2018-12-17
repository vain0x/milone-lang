module rec MiloneLang.FunTrans

open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type FunTransCtx =
  {
    VarSerial: int
    Vars: Map<int, string * ValueIdent * Ty * Loc>
    Tys: Map<int, string * TyDef * Loc>

    /// Known identifiers and their dependencies.
    Caps: Map<int, (string * int * int * Ty * Loc) list>
    Known: Set<int>
    Refs: Set<int>
    Locals: Set<int>
  }

let ctxFromTyCtx (ftCtx: Typing.TyCtx): FunTransCtx =
  // Primitive functions are known.
  let known = Set.ofList knownSerials
  {
    VarSerial = ftCtx.VarSerial
    Vars = ftCtx.Vars
    Tys = ftCtx.Tys

    Caps = Map.empty
    Known = known
    Refs = Set.empty
    Locals = Set.empty
  }

let ctxFeedbackToTyCtx (tyCtx: Typing.TyCtx) (ctx: FunTransCtx) =
  { tyCtx with
      VarSerial = ctx.VarSerial
      Vars = ctx.Vars
      Tys = ctx.Tys
  }

let ctxFreshFun (ident: string) arity (ty: Ty) loc (ctx: FunTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Fun arity, ty, loc)
    }
  let refExpr = HExpr.Ref (ident, serial, arity, ty, loc)
  refExpr, serial, ctx

let ctxFreshVar (ident: string) (ty: Ty) loc (ctx: FunTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
    }
  let refExpr = HExpr.Ref (ident, serial, 1, ty, loc)
  refExpr, serial, ctx

let ctxPushScope locals (ctx: FunTransCtx) =
  { ctx with
      Refs = Set.empty
      Locals = locals |> Set.ofList
  }

let ctxPopScope (baseCtx: FunTransCtx) (derivedCtx: FunTransCtx) =
  { derivedCtx with
      Refs = baseCtx.Refs
      Locals = baseCtx.Locals
  }

let ctxAddKnown serial (ctx: FunTransCtx) =
  { ctx with Known = Set.add serial ctx.Known }

let ctxAddRef serial (ctx: FunTransCtx) =
  { ctx with Refs = Set.add serial ctx.Refs }

let ctxAddLocal serial (ctx: FunTransCtx) =
  { ctx with Locals = Set.add serial ctx.Locals }

let ctxAddFun serial caps (ctx: FunTransCtx) =
  { ctx with
      Known = ctx.Known |> Set.add serial
      Caps = ctx.Caps |> Map.add serial caps
  }

let ctxCaps (ctx: FunTransCtx) =
  let refs = Set.difference ctx.Refs ctx.Locals
  let refs = Set.difference refs ctx.Known

  refs |> Set.toList |> List.choose
    (fun serial ->
      match ctx.Vars |> Map.find serial with
      | ident, ValueIdent.Var, ty, loc ->
        Some (ident, serial, 1, ty, loc)
      | _ ->
        None
    )

// ## Declosure: Lambda conversion
// Performs closure conversion to make all functions be context-free.
//
// Function definitions may use out-side local variables.
// We call these variables *variables captured by the function* .
//
// In this stage, we calculate captured variables
// by listing all variable references occurred in function bodies
// and local variables defined in function bodies.
// See `ctxCaps`.
//
// Capturing function definitions are converted to have an additional arg
// to receive captured variables.
//
// Calls to functions are converted to pass an additional arg --
// a tuple that consists of the captured variables.
//
// NOTE: Not supporting partial application and function objects,
// i.e., functions must be used in call expression with full args for now.

let buildCapsTuple caps loc =
  let items = caps |> List.map HExpr.Ref
  hxTuple items loc

let declosurePat (pat, ctx) =
  match pat with
  | HPat.Lit _
  | HPat.Nil _ ->
    pat, ctx
  | HPat.Ref (_, serial, _, _) ->
    let ctx = ctx |> ctxAddLocal serial
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
  | HPat.Anno (pat, ty, loc) ->
    let pat, ctx = (pat, ctx) |> declosurePat
    HPat.Anno (pat, ty, loc), ctx

let declosureExprRefAsCallee serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  expr, ctx

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  match ctx.Caps |> Map.tryFind serial with
  | Some (_ :: _) ->
    let resultTy, loc = exprExtract expr
    match declosureCall expr [] resultTy loc ctx with
    | Some expr -> expr, ctx
    | None -> expr, ctx
  | _ ->
    expr, ctx

let declosureCall callee args resultTy loc (ctx: FunTransCtx) =
  match callee with
  | HExpr.Ref (ident, callee, arity, calleeTy, refLoc) ->
    match ctx.Caps |> Map.tryFind callee with
    | Some (_ :: _ as caps) ->
      let capsExpr = buildCapsTuple caps loc
      let capsTy = exprTy capsExpr

      // Add caps arg.
      let args = capsExpr :: args
      let arity = arity + 1
      let calleeTy = Ty.Fun (capsTy, calleeTy)

      let callee = HExpr.Ref (ident, callee, arity, calleeTy, refLoc)
      hxCall callee args resultTy loc |> Some
    | _ ->
      None
  | _ ->
    None

let declosureExprCall callee args resultTy loc (ctx: FunTransCtx) =
  let callee, ctx =
    match callee with
    | HExpr.Ref (_, serial, _, _, _) ->
      (callee, ctx) |> declosureExprRefAsCallee serial
    | _ ->
      (callee, ctx) |> declosureExpr
  let args, ctx = (args, ctx) |> stMap declosureExpr
  match declosureCall callee args resultTy loc ctx with
  | Some expr ->
    expr, ctx
  | None ->
    hxCall callee args resultTy loc, ctx

let declosureExprApp expr resultTy loc ctx =
  /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
  let rec roll acc callee =
    match callee with
    | HExpr.Op (Op.App, callee, arg, _, _) ->
      roll (arg :: acc) callee
    | HExpr.Op (Op.Pipe, arg, callee, _, _) ->
      roll (arg :: acc) callee
    | _ ->
      callee, acc
  let callee, args = roll [] expr
  declosureExprCall callee args resultTy loc ctx

let declosureExprLetVal pat init loc ctx =
  let pat, ctx = declosurePat (pat, ctx)
  let init, ctx = declosureExpr (init, ctx)
  HExpr.Let (pat, init, loc), ctx

let declosureFunBody callee args body ctx =
  let baseCtx = ctx
  let ctx = ctx |> ctxPushScope []

  // Traverse for dependency collection.
  let args, ctx = (args, ctx) |> stMap declosurePat
  let _, ctx = (body, ctx) |> declosureExpr
  let caps = ctx |> ctxCaps
  let ctx = ctx |> ctxAddFun callee caps

  // Traverse again. We can now convert recursive calls correctly.
  let args, ctx = (args, ctx) |> stMap declosurePat
  let body, ctx = (body, ctx) |> declosureExpr

  let ctx = ctx |> ctxPopScope baseCtx
  caps, args, body, ctx

let addCapsArg caps args body loc ctx =
  match caps with
  | [] ->
    // Static functions are intact.
    args, body, ctx
  | _ ->
    let capsTy = caps |> List.map (fun (_, _, _, ty, _) -> ty) |> Ty.Tuple
    let capsPats = caps |> List.map (fun (ident, serial, _, ty, loc) -> HPat.Ref (ident, serial, ty, loc))
    let capsPat = HPat.Tuple (capsPats, capsTy, loc)
    capsPat :: args, body, ctx

let declosureExprLetFun ident callee args body ty loc ctx =
  let caps, args, body, ctx =
    declosureFunBody callee args body ctx
  let args, body, ctx =
    addCapsArg caps args body loc ctx
  HExpr.LetFun (ident, callee, args, body, ty, loc), ctx

let declosureExprTyDef expr tyDef ctx =
  match tyDef with
  | TyDef.Union variants ->
    let ctx =
      variants |> List.fold (fun ctx (_, variantSerial, _, _) ->
        ctx |> ctxAddKnown variantSerial
      ) ctx
    expr, ctx

let declosureExprOp ctx op l r ty loc =
  let l, ctx = declosureExpr (l, ctx)
  let r, ctx = declosureExpr (r, ctx)
  HExpr.Op (op, l, r, ty, loc), ctx

let declosureExprInf ctx infOp items ty loc =
  let items, ctx = (items, ctx) |> stMap declosureExpr
  HExpr.Inf (infOp, items, ty, loc), ctx

let declosureExprMatch target arms ty loc ctx =
  let target, ctx = declosureExpr (target, ctx)
  let go ((pat, body), ctx) =
    let pat, ctx = declosurePat (pat, ctx)
    let body, ctx = declosureExpr (body, ctx)
    (pat, body), ctx
  let arms, ctx = (arms, ctx) |> stMap go
  HExpr.Match (target, arms, ty, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | HExpr.Lit _ ->
    expr, ctx
  | HExpr.Ref (_, serial, _, _, _) ->
    declosureExprRef serial (expr, ctx)
  | HExpr.Match (target, arms, ty, loc) ->
    declosureExprMatch target arms ty loc ctx
  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = declosureExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx
  | HExpr.Op (Op.App, _, _, ty, loc) ->
    declosureExprApp expr ty loc ctx
  | HExpr.Op (op, l, r, ty, loc) ->
    declosureExprOp ctx op l r ty loc
  | HExpr.Inf (infOp, items, ty, loc) ->
    declosureExprInf ctx infOp items ty loc
  | HExpr.Let (pat, body, loc) ->
    declosureExprLetVal pat body loc ctx
  | HExpr.LetFun (ident, callee, args, body, ty, loc) ->
    declosureExprLetFun ident callee args body ty loc ctx
  | HExpr.TyDef (_, _, tyDef, _) ->
    declosureExprTyDef expr tyDef ctx
  | HExpr.If _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosure (exprs, ctx: FunTransCtx) =
  (exprs, ctx) |> stMap declosureExpr

// ## Un-eta
//
// Resolve partial applications and function references.
// Convert them to statements to create a function object with specified arguments.
//
// Thanks to declosure, in this stage, functions don't rely on local scope.
//
// ### Example
//
// Consider `let sum x y z = x + y + z` and partial application `sum 1 2`.
// Here the given arguments is `1, 2`, the rest arguments is `z`.
// We define a helper function called `sumObj` like this:
//    let sumObj env z =
//      let x, y = unbox env
//      add x y z
// and convert partial application into the following.
//    let env = box (x, y)
//    (sumObj, env) :> (int -> int)
//
// ### Function references
//
// You can think of function reference as a kind of partial application
// with given arguments is empty. In term of the above example,
//    let sumObj env x y z =
//      let () = unbox env
//      add x y z
// is defined for function reference `sum` and the use site is converted to:
//    let env = box ()
//    (sumObj, ()) :> (int -> int -> int -> int)

let ctxIsFun serial (ctx: FunTransCtx) =
  match ctx.Vars |> Map.tryFind serial with
  | _ when serial < 0 ->
    // FIXME: too ugly
    true
  | Some (_, ValueIdent.Fun _, _, _) ->
    true
  | Some (_, ValueIdent.Variant _, _, _) ->
    // FIXME: not a function
    true
  | _ ->
    false

let splitAt i xs =
  List.truncate i xs, List.skip (min i (List.length xs)) xs

let appliedTy n ty =
  match ty with
  | Ty.Fun (_, ty) when n > 0 ->
    appliedTy (n - 1) ty
  | _ ->
    ty

/// E.g. given init = `id x` and args `x, y` then we should return `(id x) y`.
let restCall callee args resultTy loc =
  match args with
  | [] ->
    callee
  | args ->
    hxExec callee args resultTy loc

type CalleeKind =
  | Fun
  | Obj

let hxCallTo calleeKind callee args resultTy loc =
  match calleeKind, args with
  | _, [] ->
    callee
  | CalleeKind.Fun, args ->
    hxCall callee args resultTy loc
  | CalleeKind.Obj, args ->
    hxExec callee args resultTy loc

let createRestArgsAndPats callee arity argLen callLoc ctx =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ ->
      [], [], ctx
    | n, Ty.Fun (argTy, restTy) ->
      let argRef, argSerial, ctx = ctxFreshVar "arg" argTy callLoc ctx
      let restArgPats, restArgs, ctx = go (n - 1) restTy ctx
      let restArgPat = HPat.Ref ("arg", argSerial, argTy, callLoc)
      restArgPat :: restArgPats, argRef :: restArgs, ctx
    | _ ->
      failwith "Never: Type error"
  let restTy = callee |> exprTy |> appliedTy argLen
  go (arity - argLen) restTy ctx

let createEnvPatAndTy items callLoc ctx =
  let rec go items ctx =
    match items with
    | [] ->
      [], [], [], ctx
    | item :: items ->
      let itemTy, itemLoc = exprExtract item
      let itemRef, itemSerial, ctx = ctxFreshVar "arg" itemTy itemLoc ctx
      let itemPat = HPat.Ref ("arg", itemSerial, itemTy, itemLoc)
      let itemPats, argTys, argRefs, ctx = go items ctx
      itemPat :: itemPats, itemTy :: argTys, itemRef :: argRefs, ctx
  let itemPats, itemTys, itemRefs, ctx = go items ctx
  let envTy = Ty.Tuple itemTys
  let envPat = HPat.Tuple (itemPats, envTy, callLoc)
  envPat, envTy, itemRefs, ctx

let createEnvDeconstructLetExpr envPat envTy envArgRef next callLoc =
  let unboxRef = HExpr.Ref ("unbox", SerialUnbox, 1, Ty.Fun (Ty.Obj, envTy), callLoc)
  let unboxExpr = hxCall unboxRef [envArgRef] envTy callLoc
  hxAndThen [
    HExpr.Let (envPat, unboxExpr, callLoc)
    next
  ] callLoc

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest arguments
/// and calls the partial-applied callee with full arguments.
let createUnderlyingFunDef funTy arity envPat envTy forwardCall restArgPats resultTy callLoc ctx =
  let envArgRef, envArgSerial, ctx = ctxFreshVar "env" Ty.Obj callLoc ctx
  let envArgPat = HPat.Ref ("env", envArgSerial, Ty.Obj, callLoc)
  let _, funSerial, ctx = ctxFreshFun "fun" arity funTy callLoc ctx
  let argPats = envArgPat :: restArgPats
  let body = createEnvDeconstructLetExpr envPat envTy envArgRef forwardCall callLoc
  let letFun = HExpr.LetFun ("fun", funSerial, argPats, body, resultTy, callLoc)
  letFun, funSerial, ctx

let createEnvBoxExpr args envTy callLoc =
  let tuple = hxTuple args callLoc
  let boxRef = HExpr.Ref ("box", SerialBox, 1, Ty.Fun (envTy, Ty.Obj), callLoc)
  hxCall boxRef [tuple] Ty.Obj callLoc

/// In the case the callee is a function.
let resolvePartialAppFun callee arity args argLen callLoc ctx =
  let funTy = exprTy callee
  let resultTy = appliedTy arity funTy
  let envItems = args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx
  let envPat, envTy, envRefs, ctx =
    createEnvPatAndTy envItems callLoc ctx
  let forwardArgs =
    envRefs @ restArgs
  let forwardExpr =
    hxCall callee forwardArgs resultTy callLoc
  let funLet, funSerial, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats resultTy callLoc ctx
  let envBoxExpr =
    createEnvBoxExpr envItems envTy callLoc
  let funObjExpr =
    HExpr.Inf (InfOp.Fun funSerial, [envBoxExpr], appliedTy argLen funTy, callLoc)
  let expr =
    hxAndThen [
      funLet
      funObjExpr
    ] callLoc
  expr, ctx

/// In the case that the callee is a function object.
/// We need to include it to the environment.
let resolvePartialAppObj callee arity args argLen callLoc ctx =
  let funTy = exprTy callee
  let resultTy = appliedTy arity funTy

  // Introduce a variable for memoization.
  let calleeRef, calleeLet, ctx =
    let calleeRef, calleeSerial, ctx = ctxFreshVar "callee" funTy callLoc ctx
    let calleePat = HPat.Ref ("callee", calleeSerial, funTy, callLoc)
    let calleeLet = HExpr.Let (calleePat, callee, callLoc)
    calleeRef, calleeLet, ctx
  let envItems = calleeRef :: args

  let restArgPats, restArgs, ctx =
    createRestArgsAndPats callee arity argLen callLoc ctx

  let envPat, envTy, envRefs, ctx =
    createEnvPatAndTy envItems callLoc ctx
  let calleeRef, forwardArgs =
    match envRefs @ restArgs with
    | calleeRef :: forwardArgs ->
      calleeRef, forwardArgs
    | _ ->
      failwith "Never"

  let forwardExpr =
    hxExec calleeRef forwardArgs resultTy callLoc
  let funLet, funSerial, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats resultTy callLoc ctx
  let envBoxExpr =
    createEnvBoxExpr envItems envTy callLoc
  let funObjExpr =
    HExpr.Inf (InfOp.Fun funSerial, [envBoxExpr], appliedTy argLen funTy, callLoc)
  let expr =
    hxAndThen [
      calleeLet
      funLet
      funObjExpr
    ] callLoc
  expr, ctx

let resolvePartialApp calleeKind callee arity args argLen callLoc ctx =
  assert (argLen < arity)
  match calleeKind with
  | CalleeKind.Fun ->
    resolvePartialAppFun callee arity args argLen callLoc ctx
  | CalleeKind.Obj ->
    resolvePartialAppObj callee arity args argLen callLoc ctx

let unetaCallCore calleeKind callee arity calleeLoc args resultTy callLoc ctx =
  let argLen = List.length args
  if argLen < arity then
    resolvePartialApp calleeKind callee arity args argLen callLoc ctx
  else
    let callArgs, restArgs = splitAt arity args
    let callResultTy = appliedTy arity (exprTy callee)
    let callExpr = hxCallTo calleeKind callee callArgs callResultTy calleeLoc
    hxCallTo CalleeKind.Obj callExpr restArgs resultTy callLoc, ctx

let unetaCall callee args resultTy loc ctx =
  match callee, args with
  | HExpr.Ref (_, serial, arity, _, calleeLoc), _ when ctx |> ctxIsFun serial ->
    let args, ctx = (args, ctx) |> stMap unetaExpr
    unetaCallCore CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx
  | _, args ->
    let calleeTy, calleeLoc = exprExtract callee
    let callee, ctx = (callee, ctx) |> unetaExpr
    let args, ctx = (args, ctx) |> stMap unetaExpr
    let arity = arityTy calleeTy // FIXME: maybe wrong
    unetaCallCore CalleeKind.Obj callee arity calleeLoc args resultTy loc ctx
  | _ ->
    failwith "Never"

let unetaRef expr serial calleeLoc (ctx: FunTransCtx) =
  match ctx.Vars |> Map.tryFind serial with
  | Some (_, ValueIdent.Fun arity, _, _) ->
    resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx
  | _ ->
    expr, ctx

let unetaExprInf infOp args ty loc ctx =
  match infOp, args with
  | InfOp.Call, callee :: args ->
    unetaCall callee args ty loc ctx
  | _ ->
    let args, ctx = (args, ctx) |> stMap unetaExpr
    HExpr.Inf (infOp, args, ty, loc), ctx

let unetaExprLetFun ident callee argPats body ty loc ctx =
  let argPats, ctx = (argPats, ctx) |> stMap unetaPat
  let body, ctx = (body, ctx) |> unetaExpr
  HExpr.LetFun (ident, callee, argPats, body, ty, loc), ctx

let unetaPat (pat, ctx) =
  pat, ctx

let unetaExpr (expr, ctx) =
  match expr with
  | HExpr.Lit _
  | HExpr.TyDef _
  | HExpr.Error _ ->
    expr, ctx
  | HExpr.Ref (_, serial, _, _, calleeLoc) ->
    unetaRef expr serial calleeLoc ctx
  | HExpr.Match (target, arms, ty, loc) ->
    let target, ctx = (target, ctx) |> unetaExpr
    let arms, ctx = (arms, ctx) |> stMap (fun ((pat, body), ctx) ->
      let pat, ctx = (pat, ctx) |> unetaPat
      let body, ctx = (body, ctx) |> unetaExpr
      (pat, body), ctx)
    HExpr.Match (target, arms, ty, loc), ctx
  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = unetaExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx
  | HExpr.Op (op, l, r, ty, loc) ->
    let l, ctx = (l, ctx) |> unetaExpr
    let r, ctx = (r, ctx) |> unetaExpr
    HExpr.Op (op, l, r, ty, loc), ctx
  | HExpr.Inf (infOp, args, ty, loc) ->
    unetaExprInf infOp args ty loc ctx
  | HExpr.Let (pat, init, loc) ->
    let pat, ctx = (pat, ctx) |> unetaPat
    let init, ctx = (init, ctx) |> unetaExpr
    HExpr.Let (pat, init, loc), ctx
  | HExpr.LetFun (ident, callee, args, body, ty, loc) ->
    unetaExprLetFun ident callee args body ty loc ctx
  | HExpr.If _ ->
    failwith "Never: If expressions are desugared"

let uneta (exprs, ctx: FunTransCtx) =
  let exprs, ctx = (exprs, ctx) |> stMap unetaExpr
  exprs, ctx

/// Performs transformation about functions.
let trans (exprs, tyCtx) =
  let ctx = ctxFromTyCtx tyCtx
  let exprs, ctx = (exprs, ctx) |> declosure |> uneta
  let tyCtx = ctx |> ctxFeedbackToTyCtx tyCtx
  exprs, tyCtx
