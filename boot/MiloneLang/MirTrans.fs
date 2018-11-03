module rec MiloneLang.MirTrans

[<RequireQualifiedAccess>]
type MirTransCtx =
  {
    VarSerial: int
    Vars: Map<int, string * MTy * Loc>
    LabelSerial: int

    /// Known identifiers and their dependencies.
    Caps: Map<int, (int * MTy * Loc) list>
    Known: Set<int>
    Refs: Set<int>
    Locals: Set<int>
  }

/// `List.map`, modifying context.
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] ->
      List.rev acc, ctx
    | x :: xs ->
      let y, ctx = f (x, ctx)
      go (y :: acc) (xs, ctx)
  go [] (xs, ctx)

/// `List.bind`, modifying context.
let stFlatMap f (xs, ctx) =
  let rec go acc xs ctx =
    match xs with
    | [] ->
      List.rev acc, ctx
    | x :: xs ->
      let acc, ctx = f (x, acc, ctx)
      go acc xs ctx
  go [] xs ctx

/// `Option.map`, modifying context.
let stOptionMap f (x, ctx) =
  match x with
  | Some x ->
    let x, ctx = f (x, ctx)
    Some x, ctx
  | None ->
    None, ctx

let ctxFromMirCtx (mirCtx: Mir.MirCtx): MirTransCtx =
  // Primitive functions are known.
  let known = Set.ofList Typing.knownSerials
  {
    VarSerial = mirCtx.VarSerial
    Vars = mirCtx.Vars
    LabelSerial = mirCtx.LabelSerial

    Caps = Map.empty
    Known = known
    Refs = Set.empty
    Locals = Set.empty
  }

let ctxFreshVar (ident: string) (ty: MTy) loc (ctx: MirTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ty, loc)
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
  refExpr, serial, ctx

let ctxPushScope locals (ctx: MirTransCtx) =
  { ctx with
      Refs = Set.empty
      Locals = locals |> Set.ofList
  }

let ctxPopScope (baseCtx: MirTransCtx) (derivedCtx: MirTransCtx) =
  { derivedCtx with
      Refs = baseCtx.Refs
      Locals = baseCtx.Locals
  }

let ctxAddRef serial (ctx: MirTransCtx) =
  { ctx with Refs = Set.add serial ctx.Refs }

let ctxAddLocal serial (ctx: MirTransCtx) =
  { ctx with Locals = Set.add serial ctx.Locals }

let ctxAddFun serial caps (ctx: MirTransCtx) =
  { ctx with
      Known = ctx.Known |> Set.add serial
      Caps = ctx.Caps |> Map.add serial caps
  }

let ctxCaps (ctx: MirTransCtx) =
  let refs = Set.difference ctx.Refs ctx.Locals
  let refs = Set.difference refs ctx.Known

  refs |> Set.toList |> List.map
    (fun serial ->
      let _, ty, loc = ctx.Vars |> Map.find serial
      serial, ty, loc
    )

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  expr, ctx

let declosureExprCall callee args resultTy loc (ctx: MirTransCtx) =
  let callee, ctx = (callee, ctx) |> declosureExpr
  let args, ctx = (args, ctx) |> stMap declosureExpr
  MExpr.Call (callee, args, resultTy, loc), ctx

let declosureExpr (expr, ctx) =
  match expr with
  | MExpr.Value _
  | MExpr.Default _ ->
    expr, ctx
  | MExpr.Ref (serial, _, _) ->
    declosureExprRef serial (expr, ctx)
  | MExpr.Call (callee, args, resultTy, loc) ->
    declosureExprCall callee args resultTy loc ctx
  | MExpr.UniOp (op, arg, ty, loc) ->
    let arg, ctx = (arg, ctx) |> declosureExpr
    MExpr.UniOp (op, arg, ty, loc), ctx
  | MExpr.Op (op, l, r, ty, loc) ->
    let l, ctx = (l, ctx) |> declosureExpr
    let r, ctx = (r, ctx) |> declosureExpr
    MExpr.Op (op, l, r, ty, loc), ctx

let declosureStmtLetVal serial init ty loc (acc, ctx: MirTransCtx) =
  let result =
    match init with
    | Some (MExpr.Call (MExpr.Ref (callee, _, _) as refExpr, args, callTy, callLoc)) ->
      match ctx.Caps |> Map.tryFind callee with
      | Some (_ :: _ as caps) ->
        let buildCapsTuple (caps: (int * MTy * Loc) list) callLoc ctx =
          let tupleTy = caps |> List.map (fun (_, ty, _) -> ty) |> MTy.Tuple
          let items = caps |> List.map MExpr.Ref
          let capsRef, capsSerial, ctx = ctx |> ctxFreshVar "caps" tupleTy callLoc
          let letCaps = MStmt.LetTuple (capsSerial, items, tupleTy, callLoc)
          capsRef, letCaps, ctx

        // Add caps arg.
        let capsRef, letCaps, ctx = buildCapsTuple caps callLoc ctx
        let args = capsRef :: args
        let acc = letCaps :: acc

        let init = Some (MExpr.Call (refExpr, args, callTy, loc))
        let ctx = ctx |> ctxAddLocal serial
        Some (MStmt.LetVal (serial, init, ty, loc) :: acc, ctx)
      | None
      | Some [] ->
        None
    | _ ->
      None

  match result with
  | Some result ->
    result
  | None ->
    let init, ctx = (init, ctx) |> stOptionMap declosureExpr
    let ctx = ctx |> ctxAddLocal serial
    MStmt.LetVal (serial, init, ty, loc) :: acc, ctx

let declosureStmt (stmt, acc, ctx) =
  match stmt with
  | MStmt.Expr (expr, loc) ->
    let expr, ctx = declosureExpr (expr, ctx)
    MStmt.Expr (expr, loc) :: acc, ctx
  | MStmt.LetVal (serial, init, ty, loc) ->
    declosureStmtLetVal serial init ty loc (acc, ctx)
  | MStmt.LetBox (serial, init, loc) ->
    let init, ctx = (init, ctx) |> declosureExpr
    let ctx = ctx |> ctxAddLocal serial
    MStmt.LetBox (serial, init, loc) :: acc, ctx
  | MStmt.LetCons (serial, head, tail, ty, loc) ->
    let head, ctx = (head, ctx) |> declosureExpr
    let tail, ctx = (tail, ctx) |> declosureExpr
    let ctx = ctx |> ctxAddLocal serial
    MStmt.LetCons (serial, head, tail, ty, loc) :: acc, ctx
  | MStmt.LetTuple (serial, items, ty, loc) ->
    let items, ctx = (items, ctx) |> stMap declosureExpr
    let ctx = ctx |> ctxAddLocal serial
    MStmt.LetTuple (serial, items, ty, loc) :: acc, ctx
  | MStmt.Set (serial, init, loc) ->
    let init, ctx = (init, ctx) |> declosureExpr
    MStmt.Set (serial, init, loc) :: acc, ctx
  | MStmt.Return (r, loc) ->
    let r, ctx = (r, ctx) |> declosureExpr
    MStmt.Return (r, loc) :: acc, ctx
  | MStmt.Label _
  | MStmt.Goto _ ->
    stmt :: acc, ctx
  | MStmt.GotoUnless (pred, label, loc) ->
    let pred, ctx = (pred, ctx) |> declosureExpr
    MStmt.GotoUnless (pred, label, loc) :: acc, ctx

let declosureFunBody callee args body ctx =
  /// Variables known to the function body.
  let localSerials =
    let argSerials = args |> List.map (fun (serial, _, _) -> serial)
    callee :: argSerials

  let ctx = ctx |> ctxPushScope localSerials
  let body, ctx = (body, ctx) |> stFlatMap declosureStmt
  let caps = ctx |> ctxCaps
  let ctx = ctx |> ctxPopScope ctx

  caps, body, ctx

let deconstructCaps capsRef caps body =
  let rec go i body caps =
    match caps with
    | [] ->
      body
    | (serial, ty, loc) :: caps ->
      let projExpr = MExpr.UniOp (MUniOp.Proj i, capsRef, ty, loc)
      let letStmt = MStmt.LetVal (serial, Some projExpr, ty, loc)
      go (i + 1) (letStmt :: body) caps
  go 0 body caps

let addCapsArg caps args body loc ctx =
  match caps with
  | [] ->
    // Static functions are intact.
    args, body, ctx
  | _ ->
    let tys = caps |> List.map (fun (_, ty, _) -> ty)
    let capsTy = if tys |> List.isEmpty then MTy.Unit else MTy.Tuple tys

    let capsRef, capsSerial, ctx = ctx |> ctxFreshVar "caps" capsTy loc
    let body = deconstructCaps capsRef caps body

    let args = (capsSerial, capsTy, loc) :: args
    args, body, ctx

let declosureDeclLetFun callee args ty body loc ctx =
  let caps, body, ctx = declosureFunBody callee args body ctx
  let args, body, ctx = addCapsArg caps args body loc ctx

  let ctx = ctx |> ctxAddFun callee caps
  MDecl.LetFun (callee, args, caps, ty, body, loc), ctx

let declosureDecl (decl, ctx) =
  match decl with
  | MDecl.LetFun (callee, args, _, ty, body, loc) ->
    declosureDeclLetFun callee args ty body loc ctx

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
/// Capturing function definitions are converted to have an additional arg
/// to receive captured variables.
///
/// Calls to functions are converted to pass an additional arg --
/// a tuple that consists of the captured variables.
///
/// NOTE: Not supporting partial application and function objects,
/// i.e., functions must be used in call expression with full args for now.
let declosure (decls, ctx: MirTransCtx) =
  (decls, ctx) |> stMap declosureDecl

let trans (decls, mirCtx) =
  let ctx = ctxFromMirCtx mirCtx
  declosure (decls, ctx)
