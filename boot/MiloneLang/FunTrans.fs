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
  }

let ctxFreshVar (ident: string) (ty: Ty) loc (ctx: FunTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
    }
  let refExpr = Expr.Ref (ident, serial, 1, ty, loc)
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
  let items = caps |> List.map Expr.Ref
  hxTuple items loc

let declosurePat (pat, ctx) =
  match pat with
  | Pat.Lit _
  | Pat.Nil _ ->
    pat, ctx
  | Pat.Ref (_, serial, _, _) ->
    let ctx = ctx |> ctxAddLocal serial
    pat, ctx
  | Pat.Cons (l, r, itemTy, loc) ->
    let l, ctx = (l, ctx) |> declosurePat
    let r, ctx = (r, ctx) |> declosurePat
    Pat.Cons (l, r, itemTy, loc), ctx
  | Pat.Tuple (items, ty, loc) ->
    let items, ctx = (items, ctx) |> stMap declosurePat
    Pat.Tuple (items, ty, loc), ctx
  | Pat.Call (callee, args, ty, loc) ->
    let callee, ctx = (callee, ctx) |> declosurePat
    let args, ctx = (args, ctx) |> stMap declosurePat
    Pat.Call (callee, args, ty, loc), ctx
  | Pat.Anno (pat, ty, loc) ->
    let pat, ctx = (pat, ctx) |> declosurePat
    Pat.Anno (pat, ty, loc), ctx

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  expr, ctx

let declosureCall callee args resultTy loc (ctx: FunTransCtx) =
  match callee with
  | Expr.Ref (ident, callee, arity, calleeTy, refLoc) ->
    match ctx.Caps |> Map.tryFind callee with
    | Some (_ :: _ as caps) ->
      let capsExpr = buildCapsTuple caps loc
      let capsTy = exprTy capsExpr

      // Add caps arg.
      let args = capsExpr :: args
      let arity = arity + 1
      let calleeTy = Ty.Fun (capsTy, calleeTy)

      let callee = Expr.Ref (ident, callee, arity, calleeTy, refLoc)
      hxCall callee args resultTy loc |> Some
    | _ ->
      None
  | _ ->
    None

let declosureExprCall callee args resultTy loc (ctx: FunTransCtx) =
  let callee, ctx = (callee, ctx) |> declosureExpr
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
    | Expr.Op (Op.App, callee, arg, _, _) ->
      roll (arg :: acc) callee
    | Expr.Op (Op.Pipe, arg, callee, _, _) ->
      roll (arg :: acc) callee
    | _ ->
      callee, acc
  let callee, args = roll [] expr
  declosureExprCall callee args resultTy loc ctx

let declosureExprLetVal pat init loc ctx =
  let pat, ctx = declosurePat (pat, ctx)
  let init, ctx = declosureExpr (init, ctx)
  Expr.Let (pat, init, loc), ctx

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
    let capsPats = caps |> List.map (fun (ident, serial, _, ty, loc) -> Pat.Ref (ident, serial, ty, loc))
    let capsPat = Pat.Tuple (capsPats, capsTy, loc)
    capsPat :: args, body, ctx

let declosureExprLetFun ident callee args body ty loc ctx =
  let caps, args, body, ctx =
    declosureFunBody callee args body ctx
  let args, body, ctx =
    addCapsArg caps args body loc ctx
  Expr.LetFun (ident, callee, args, body, ty, loc), ctx

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
  Expr.Op (op, l, r, ty, loc), ctx

let declosureExprInf ctx infOp items ty loc =
  let items, ctx = (items, ctx) |> stMap declosureExpr
  Expr.Inf (infOp, items, ty, loc), ctx

let declosureExprMatch target arms ty loc ctx =
  let target, ctx = declosureExpr (target, ctx)
  let go ((pat, body), ctx) =
    let pat, ctx = declosurePat (pat, ctx)
    let body, ctx = declosureExpr (body, ctx)
    (pat, body), ctx
  let arms, ctx = (arms, ctx) |> stMap go
  Expr.Match (target, arms, ty, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | Expr.Lit _ ->
    expr, ctx
  | Expr.Ref (_, serial, _, _, _) ->
    declosureExprRef serial (expr, ctx)
  | Expr.Match (target, arms, ty, loc) ->
    declosureExprMatch target arms ty loc ctx
  | Expr.Nav (subject, message, ty, loc) ->
    let subject, ctx = declosureExpr (subject, ctx)
    Expr.Nav (subject, message, ty, loc), ctx
  | Expr.Op (Op.App, _, _, ty, loc) ->
    declosureExprApp expr ty loc ctx
  | Expr.Op (op, l, r, ty, loc) ->
    declosureExprOp ctx op l r ty loc
  | Expr.Inf (infOp, items, ty, loc) ->
    declosureExprInf ctx infOp items ty loc
  | Expr.Let (pat, body, loc) ->
    declosureExprLetVal pat body loc ctx
  | Expr.LetFun (ident, callee, args, body, ty, loc) ->
    declosureExprLetFun ident callee args body ty loc ctx
  | Expr.TyDef (_, _, tyDef, _) ->
    declosureExprTyDef expr tyDef ctx
  | Expr.If _
  | Expr.Inf (InfOp.Anno, _, _, _)
  | Expr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | Expr.Error (error, loc) ->
    failwithf "Never: %s at %A" error loc

let declosure (exprs, ctx: FunTransCtx) =
  (exprs, ctx) |> stMap declosureExpr

let trans (decls, tyCtx) =
  let ctx = ctxFromTyCtx tyCtx
  let decls, ctx = (decls, ctx) |> declosure //|> uneta
  let tyCtx = ctx |> ctxFeedbackToTyCtx tyCtx
  decls, tyCtx
