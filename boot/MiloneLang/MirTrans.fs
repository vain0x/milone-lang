module rec MiloneLang.MirTrans

open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type MirTransCtx =
  {
    VarSerial: int
    Vars: Map<int, string * ValueIdent * MTy * Loc>
    Tys: Map<int, string * MTyDef * Loc>
    LabelSerial: int

    /// Known identifiers and their dependencies.
    Caps: Map<int, (int * MTy * Loc) list>
    Known: Set<int>
    Refs: Set<int>
    Locals: Set<int>
  }

let ctxFromMirCtx (mirCtx: Mir.MirCtx): MirTransCtx =
  // Primitive functions are known.
  let known = Set.ofList knownSerials
  {
    VarSerial = mirCtx.VarSerial
    Vars = mirCtx.Vars
    LabelSerial = mirCtx.LabelSerial
    Tys = mirCtx.Tys

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
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
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

let ctxAddKnown serial (ctx: MirTransCtx) =
  { ctx with Known = Set.add serial ctx.Known }

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

  refs |> Set.toList |> List.choose
    (fun serial ->
      match ctx.Vars |> Map.find serial with
      | _, ValueIdent.Var, ty, loc ->
        Some (serial, ty, loc)
      | _ ->
        None
    )

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  expr, ctx

let declosureExpr (expr, ctx) =
  match expr with
  | MExpr.Lit _
  | MExpr.Default _
  | MExpr.Variant _ ->
    expr, ctx
  | MExpr.Ref (serial, _, _) ->
    declosureExprRef serial (expr, ctx)
  | MExpr.UniOp (op, arg, ty, loc) ->
    let arg, ctx = (arg, ctx) |> declosureExpr
    MExpr.UniOp (op, arg, ty, loc), ctx
  | MExpr.Op (op, l, r, ty, loc) ->
    let l, ctx = (l, ctx) |> declosureExpr
    let r, ctx = (r, ctx) |> declosureExpr
    MExpr.Op (op, l, r, ty, loc), ctx

let declosureInitCall callee args (ctx: MirTransCtx) =
  let callee, ctx = (callee, ctx) |> declosureExpr
  let args, ctx = (args, ctx) |> stMap declosureExpr
  MInit.Call (callee, args), ctx

let declosureInit (init, ctx) =
  match init with
  | MInit.UnInit _ ->
    init, ctx
  | MInit.Expr expr ->
    let expr, ctx = (expr, ctx) |> declosureExpr
    MInit.Expr expr, ctx
  | MInit.Call (callee, args) ->
    declosureInitCall callee args ctx
  | MInit.Box expr ->
    let expr, ctx = (expr, ctx) |> declosureExpr
    MInit.Box expr, ctx
  | MInit.Cons (head, tail, itemTy) ->
    let head, ctx = (head, ctx) |> declosureExpr
    let tail, ctx = (tail, ctx) |> declosureExpr
    MInit.Cons (head, tail, itemTy), ctx
  | MInit.Tuple items ->
    let items, ctx = (items, ctx) |> stMap declosureExpr
    MInit.Tuple items, ctx
  | MInit.Union (serial, arg, argTy) ->
    let arg, ctx = (arg, ctx) |> declosureExpr
    MInit.Union (serial, arg, argTy), ctx

let declosureStmtLetVal serial init ty loc (acc, ctx: MirTransCtx) =
  let result =
    match init with
    | MInit.Call (MExpr.Ref (callee, _, _) as refExpr, args) ->
      match ctx.Caps |> Map.tryFind callee with
      | Some (_ :: _ as caps) ->
        let buildCapsTuple caps loc ctx =
          let tupleTy = caps |> List.map (fun (_, ty, _) -> ty) |> MTy.Tuple
          let items = caps |> List.map MExpr.Ref
          let capsRef, capsSerial, ctx = ctx |> ctxFreshVar "caps" tupleTy loc
          let letCaps = MStmt.LetVal (capsSerial, MInit.Tuple items, tupleTy, loc)
          capsRef, letCaps, ctx

        // Add caps arg.
        let capsRef, letCaps, ctx = buildCapsTuple caps loc ctx
        let args = capsRef :: args
        let acc = letCaps :: acc

        let ctx = ctx |> ctxAddLocal serial
        Some (MStmt.LetVal (serial, MInit.Call (refExpr, args), ty, loc) :: acc, ctx)
      | None
      | Some [] ->
        None
    | _ ->
      None

  match result with
  | Some result ->
    result
  | None ->
    let init, ctx = (init, ctx) |> declosureInit
    let ctx = ctx |> ctxAddLocal serial
    MStmt.LetVal (serial, init, ty, loc) :: acc, ctx

let declosureStmt (stmt, acc, ctx) =
  match stmt with
  | MStmt.Do (expr, loc) ->
    let expr, ctx = declosureExpr (expr, ctx)
    MStmt.Do (expr, loc) :: acc, ctx
  | MStmt.LetVal (serial, init, ty, loc) ->
    declosureStmtLetVal serial init ty loc (acc, ctx)
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

let declosureDeclTyDef decl tyDef ctx =
  match tyDef with
  | TyDef.Union variants ->
    let ctx =
      variants |> List.fold (fun ctx (_, variantSerial, _, _) ->
        ctx |> ctxAddKnown variantSerial
      ) ctx
    decl, ctx

let declosureFunBody callee args body ctx =
  /// Variables known to the function body.
  let localSerials =
    let argSerials = args |> List.map (fun (serial, _, _) -> serial)
    callee :: argSerials

  let baseCtx = ctx
  let ctx = ctx |> ctxPushScope localSerials

  // Traverse for dependency collection.
  let _, ctx = (body, ctx) |> stFlatMap declosureStmt
  let caps = ctx |> ctxCaps
  let ctx = ctx |> ctxAddFun callee caps

  // Traverse again. We can now convert recursive calls correctly.
  let body, ctx = (body, ctx) |> stFlatMap declosureStmt

  let ctx = ctx |> ctxPopScope baseCtx
  caps, body, ctx

let deconstructCaps capsRef caps body =
  let rec go i body caps =
    match caps with
    | [] ->
      body
    | (serial, ty, loc) :: caps ->
      let projExpr = MExpr.UniOp (MUniOp.Proj i, capsRef, ty, loc)
      let letStmt = MStmt.LetVal (serial, MInit.Expr projExpr, ty, loc)
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
  MDecl.LetFun (callee, args, caps, ty, body, loc), ctx

let declosureDecl (decl, ctx) =
  match decl with
  | MDecl.TyDef (_, tyDef, _) ->
    declosureDeclTyDef decl tyDef ctx
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
