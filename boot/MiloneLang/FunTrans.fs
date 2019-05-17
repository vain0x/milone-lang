module rec MiloneLang.FunTrans

open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type FunTransCtx =
  {
    VarSerial: int
    Vars: Map<int, VarDef>
    Tys: Map<int, TyDef>

    /// Known identifiers and their dependencies.
    Caps: Map<int, (string * int * int * Ty * Loc) list>
    Known: Set<int>
    Refs: Set<int>
    Locals: Set<int>
  }

let ctxFromTyCtx (ftCtx: Typing.TyCtx): FunTransCtx =
  {
    VarSerial = ftCtx.VarSerial
    Vars = ftCtx.Vars
    Tys = ftCtx.Tys

    Caps = Map.empty
    Known = Set.empty
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
        Vars = ctx.Vars |> Map.add serial (VarDef.Fun (ident, arity, ty, loc))
    }
  let refExpr = HExpr.Ref (ident, HValRef.Var serial, arity, ty, loc)
  refExpr, serial, ctx

let ctxFreshVar (ident: string) (ty: Ty) loc (ctx: FunTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (VarDef.Var (ident, ty, loc))
    }
  let refExpr = HExpr.Ref (ident, HValRef.Var serial, 1, ty, loc)
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
      | VarDef.Var (ident, ty, loc) ->
        let arity = 1
        Some (ident, serial, arity, ty, loc)
      | _ ->
        None
    )

// ## Declosure: Closure conversion
//
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
// Note we refer to context-free functions as *procedures* (or proc).

let buildCapsTuple caps loc =
  let items = caps |> List.map (fun (ident, serial, arity, ty, loc) ->
    HExpr.Ref (ident, HValRef.Var serial, arity, ty, loc))
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
  | HPat.As (pat, ident, serial, loc) ->
    let ctx = ctx |> ctxAddLocal serial
    let pat, ctx = (pat, ctx) |> declosurePat
    HPat.As (pat, ident, serial, loc), ctx
  | HPat.Anno (pat, ty, loc) ->
    let pat, ctx = (pat, ctx) |> declosurePat
    HPat.Anno (pat, ty, loc), ctx
  | HPat.Or (first, second, ty, loc) ->
    let first, ctx = (first, ctx) |> declosurePat
    let second, ctx = (second, ctx) |> declosurePat
    HPat.Or (first, second, ty, loc), ctx

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
  | HExpr.Ref (ident, HValRef.Var callee, arity, calleeTy, refLoc) ->
    match ctx.Caps |> Map.tryFind callee with
    | Some (_ :: _ as caps) ->
      let capsExpr = buildCapsTuple caps loc
      let capsTy = exprTy capsExpr

      // Add caps arg.
      let args = capsExpr :: args
      let arity = arity + 1
      let calleeTy = tyFun capsTy calleeTy

      let callee = HExpr.Ref (ident, HValRef.Var callee, arity, calleeTy, refLoc)
      hxCallProc callee args resultTy loc |> Some
    | _ ->
      None
  | _ ->
    None

let declosureExprCall callee args resultTy loc (ctx: FunTransCtx) =
  let callee, ctx =
    match callee with
    | HExpr.Ref (_, HValRef.Var serial, _, _, _) ->
      (callee, ctx) |> declosureExprRefAsCallee serial
    | _ ->
      (callee, ctx) |> declosureExpr
  let args, ctx = (args, ctx) |> stMap declosureExpr
  match declosureCall callee args resultTy loc ctx with
  | Some expr ->
    expr, ctx
  | None ->
    hxCallProc callee args resultTy loc, ctx

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

let declosureExprLetVal pat init next ty loc ctx =
  let pat, ctx = declosurePat (pat, ctx)
  let init, ctx = declosureExpr (init, ctx)
  let next, ctx = declosureExpr (next, ctx)
  HExpr.Let (pat, init, next, ty, loc), ctx

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
    let capsTy = caps |> List.map (fun (_, _, _, ty, _) -> ty) |> tyTuple
    let capsPats = caps |> List.map (fun (ident, serial, _, ty, loc) -> HPat.Ref (ident, serial, ty, loc))
    let capsPat = HPat.Tuple (capsPats, capsTy, loc)
    capsPat :: args, body, ctx

let declosureExprLetFun ident callee args body next ty loc ctx =
  let caps, args, body, ctx =
    declosureFunBody callee args body ctx
  let args, body, ctx =
    addCapsArg caps args body loc ctx
  let next, ctx =
    declosureExpr (next, ctx)
  HExpr.LetFun (ident, callee, args, body, next, ty, loc), ctx

let declosureExprTyDecl expr tyDecl ctx =
  match tyDecl with
  | TyDecl.Union (_, variants, _) ->
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
  let go ((pat, guard, body), ctx) =
    let pat, ctx = declosurePat (pat, ctx)
    let guard, ctx = declosureExpr (guard, ctx)
    let body, ctx = declosureExpr (body, ctx)
    (pat, guard, body), ctx
  let arms, ctx = (arms, ctx) |> stMap go
  HExpr.Match (target, arms, ty, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | HExpr.Lit _
  | HExpr.Ref (_, HValRef.Prim _, _, _, _) ->
    expr, ctx
  | HExpr.Ref (_, HValRef.Var serial, _, _, _) ->
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
  | HExpr.Let (pat, body, next, ty, loc) ->
    declosureExprLetVal pat body next ty loc ctx
  | HExpr.LetFun (ident, callee, args, body, next, ty, loc) ->
    declosureExprLetFun ident callee args body next ty loc ctx
  | HExpr.TyDef (_, _, tyDecl, _) ->
    declosureExprTyDecl expr tyDecl ctx
  | HExpr.If _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosure (expr, ctx: FunTransCtx) =
  (expr, ctx) |> declosureExpr

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
  | Some (VarDef.Fun _) ->
    true
  | Some (VarDef.Variant _) ->
    // FIXME: not a function
    true
  | _ ->
    false

let splitAt i xs =
  List.truncate i xs, List.skip (min i (List.length xs)) xs

let appliedTy n ty =
  match ty with
  | Ty.Con (TyCon.Fun, [_; ty]) when n > 0 ->
    appliedTy (n - 1) ty
  | _ ->
    ty

/// E.g. given init = `id x` and args `x, y` then we should return `(id x) y`.
let restCall callee args resultTy loc =
  match args with
  | [] ->
    callee
  | args ->
    hxCallClosure callee args resultTy loc

type CalleeKind =
  | Fun
  | Obj

let hxCallTo calleeKind callee args resultTy loc =
  match calleeKind, args with
  | _, [] ->
    callee
  | CalleeKind.Fun, args ->
    hxCallProc callee args resultTy loc
  | CalleeKind.Obj, args ->
    hxCallClosure callee args resultTy loc

let createRestArgsAndPats callee arity argLen callLoc ctx =
  let rec go n restTy ctx =
    match n, restTy with
    | 0, _ ->
      [], [], ctx
    | n, Ty.Con (TyCon.Fun, [argTy; restTy]) ->
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
  let envTy = tyTuple itemTys
  let envPat = HPat.Tuple (itemPats, envTy, callLoc)
  envPat, envTy, itemRefs, ctx

let createEnvDeconstructLetExpr envPat envTy envArgRef next callLoc =
  let unboxRef = HExpr.Ref ("unbox", HValRef.Prim HPrim.Unbox, 1, tyFun tyObj envTy, callLoc)
  let unboxExpr = hxCallProc unboxRef [envArgRef] envTy callLoc
  HExpr.Let (envPat, unboxExpr, next, exprTy next, callLoc)

/// Creates a let expression to define an underlying function.
/// It takes an environment and rest arguments
/// and calls the partial-applied callee with full arguments.
let createUnderlyingFunDef funTy arity envPat envTy forwardCall restArgPats callLoc ctx =
  let envArgRef, envArgSerial, ctx = ctxFreshVar "env" tyObj callLoc ctx
  let envArgPat = HPat.Ref ("env", envArgSerial, tyObj, callLoc)
  let _, funSerial, ctx = ctxFreshFun "fun" arity funTy callLoc ctx
  let argPats = envArgPat :: restArgPats
  let body = createEnvDeconstructLetExpr envPat envTy envArgRef forwardCall callLoc
  let funLet next = HExpr.LetFun ("fun", funSerial, argPats, body, next, exprTy next, callLoc)
  funLet, funSerial, ctx

let createEnvBoxExpr args envTy callLoc =
  let tuple = hxTuple args callLoc
  let boxRef = HExpr.Ref ("box", HValRef.Prim HPrim.Box, 1, tyFun envTy tyObj, callLoc)
  hxCallProc boxRef [tuple] tyObj callLoc

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
    hxCallProc callee forwardArgs resultTy callLoc
  let funLet, funSerial, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats callLoc ctx
  let envBoxExpr =
    createEnvBoxExpr envItems envTy callLoc
  let funObjExpr =
    HExpr.Inf (InfOp.Closure funSerial, [envBoxExpr], appliedTy argLen funTy, callLoc)
  let expr =
    funLet funObjExpr
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
    let calleeLet next = HExpr.Let (calleePat, callee, next, exprTy next, callLoc)
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
    hxCallClosure calleeRef forwardArgs resultTy callLoc
  let funLet, funSerial, ctx =
    createUnderlyingFunDef funTy arity envPat envTy forwardExpr restArgPats callLoc ctx
  let envBoxExpr =
    createEnvBoxExpr envItems envTy callLoc
  let closureExpr =
    HExpr.Inf (InfOp.Closure funSerial, [envBoxExpr], appliedTy argLen funTy, callLoc)
  let expr =
    calleeLet (funLet closureExpr)
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
  | HExpr.Ref (_, HValRef.Var serial, arity, _, calleeLoc), _ when ctx |> ctxIsFun serial ->
    let args, ctx = (args, ctx) |> stMap unetaExpr
    unetaCallCore CalleeKind.Fun callee arity calleeLoc args resultTy loc ctx
  | HExpr.Ref (_, HValRef.Prim _, arity, _, calleeLoc), _ ->
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

let unetaRef expr valRef calleeLoc (ctx: FunTransCtx) =
  match valRef with
  | HValRef.Var serial ->
    match ctx.Vars |> Map.tryFind serial with
    | Some (VarDef.Fun (_, arity, _, _)) ->
      resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx
    | _ ->
      expr, ctx
  | HValRef.Prim prim ->
    let arity = primToArity prim
    resolvePartialApp CalleeKind.Fun expr arity [] 0 calleeLoc ctx

let unetaExprInf infOp args ty loc ctx =
  match infOp, args with
  | InfOp.CallProc, callee :: args ->
    unetaCall callee args ty loc ctx
  | _ ->
    let args, ctx = (args, ctx) |> stMap unetaExpr
    HExpr.Inf (infOp, args, ty, loc), ctx

let unetaExprLetFun ident callee argPats body next ty loc ctx =
  let argPats, ctx = (argPats, ctx) |> stMap unetaPat
  let body, ctx = (body, ctx) |> unetaExpr
  let next, ctx = (next, ctx) |> unetaExpr
  HExpr.LetFun (ident, callee, argPats, body, next, ty, loc), ctx

let unetaPat (pat, ctx) =
  pat, ctx

let unetaExpr (expr, ctx) =
  match expr with
  | HExpr.Lit _
  | HExpr.TyDef _
  | HExpr.Error _ ->
    expr, ctx
  | HExpr.Ref (_, valRef, _, _, calleeLoc) ->
    unetaRef expr valRef calleeLoc ctx
  | HExpr.Match (target, arms, ty, loc) ->
    let target, ctx = (target, ctx) |> unetaExpr
    let arms, ctx = (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
      let pat, ctx = (pat, ctx) |> unetaPat
      let guard, ctx = (guard, ctx) |> unetaExpr
      let body, ctx = (body, ctx) |> unetaExpr
      (pat, guard, body), ctx)
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
  | HExpr.Let (pat, init, next, ty, loc) ->
    let pat, ctx = (pat, ctx) |> unetaPat
    let init, ctx = (init, ctx) |> unetaExpr
    let next, ctx = (next, ctx) |> unetaExpr
    HExpr.Let (pat, init, next, ty, loc), ctx
  | HExpr.LetFun (ident, callee, args, body, next, ty, loc) ->
    unetaExprLetFun ident callee args body next ty loc ctx
  | HExpr.If _ ->
    failwith "Never: If expressions are desugared"

let uneta (expr, ctx: FunTransCtx) =
  (expr, ctx) |> unetaExpr

/// Performs transformation about functions.
let trans (expr, tyCtx) =
  let ctx = ctxFromTyCtx tyCtx
  let expr, ctx = (expr, ctx) |> declosure |> uneta
  let tyCtx = ctx |> ctxFeedbackToTyCtx tyCtx
  expr, tyCtx
