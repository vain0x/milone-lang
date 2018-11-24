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
    Caps: Map<int, (int * int * MTy * Loc) list>
    Known: Set<int>
    Refs: Set<int>
    Locals: Set<int>

    Decls: MDecl<Loc> list
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

    Decls = []
  }

let ctxFreshVar (ident: string) (ty: MTy) loc (ctx: MirTransCtx) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
    }
  let refExpr = MExpr.Ref (serial, 1, ty, loc)
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
        Some (serial, 1, ty, loc)
      | _ ->
        None
    )

let ctxAddDecl decl (ctx: MirTransCtx) =
  { ctx with Decls = decl :: ctx.Decls }

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

let declosureExprRef serial (expr, ctx) =
  let ctx = ctx |> ctxAddRef serial
  expr, ctx

let declosureExpr (expr, ctx) =
  match expr with
  | MExpr.Lit _
  | MExpr.Default _
  | MExpr.Variant _ ->
    expr, ctx
  | MExpr.Ref (serial, _, _, _) ->
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
  | MInit.Fun (funSerial, envSerial) ->
    MInit.Fun (funSerial, envSerial), ctx
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
  | MInit.App _ ->
    failwith "Never: No app initializers are generated yet."

let declosureStmtLetVal serial init ty loc (acc, ctx: MirTransCtx) =
  let result =
    match init with
    | MInit.Call (MExpr.Ref (callee, arity, refTy, refLoc), args) ->
      match ctx.Caps |> Map.tryFind callee with
      | Some (_ :: _ as caps) ->
        let buildCapsTuple caps loc ctx =
          let tupleTy = caps |> List.map (fun (_, _, ty, _) -> ty) |> MTy.Tuple
          let items = caps |> List.map MExpr.Ref
          let capsRef, capsSerial, ctx = ctx |> ctxFreshVar "caps" tupleTy loc
          let letCaps = MStmt.LetVal (capsSerial, MInit.Tuple items, tupleTy, loc)
          capsRef, tupleTy, letCaps, ctx

        // Add caps arg.
        let capsRef, capsTy, letCaps, ctx = buildCapsTuple caps loc ctx
        let args = capsRef :: args
        let refExpr = MExpr.Ref (callee, arity + 1, MTy.Fun (capsTy, refTy), refLoc)
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
  | MStmt.Exit (arg, loc) ->
    let arg, ctx = (arg, ctx) |> declosureExpr
    MStmt.Exit (arg, loc) :: acc, ctx

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
    let argSerials = args |> List.map (fun (serial, _, _, _) -> serial)
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
    | (serial, _, ty, loc) :: caps ->
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
    let tys = caps |> List.map (fun (_, _, ty, _) -> ty)
    let capsTy = if tys |> List.isEmpty then MTy.Unit else MTy.Tuple tys

    let capsRef, capsSerial, ctx = ctx |> ctxFreshVar "caps" capsTy loc
    let body = deconstructCaps capsRef caps body

    let args = (capsSerial, 1, capsTy, loc) :: args
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

let declosure (decls, ctx: MirTransCtx) =
  (decls, ctx) |> stMap declosureDecl

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

let ctxIsFun serial (ctx: MirTransCtx) =
  match ctx.Vars |> Map.tryFind serial with
  | _ when serial < 0 ->
    // FIXME: too ugly
    true
  | Some (_, ValueIdent.Fun _, _, _) ->
    true
  | _ ->
    false

let splitAt i xs =
  List.truncate i xs, List.skip (min i (List.length xs)) xs

let appliedTy n ty =
  match ty with
  | MTy.Fun (_, ty) when n > 0 ->
    appliedTy (n - 1) ty
  | _ ->
    ty

let argTys n ty =
  let rec go acc n ty =
    match ty with
    | MTy.Fun (argTy, ty) when n > 0 ->
      go (argTy :: acc) (n - 1) ty
    | _ ->
      List.rev acc
  go [] n ty

let funArgTy ty =
  match ty with
  | MTy.Fun (ty, _) ->
    ty
  | _ ->
    failwith "Never: Type error."

/// `f(x, y)` -> `(f x) y`
let unroll initTy loc init args acc ctx =
  match args, initTy with
  | [], _ ->
    init, acc, ctx
  | arg :: args, MTy.Fun (_, appTy) ->
    let temp, tempSerial, ctx  = ctxFreshVar "app" initTy loc ctx
    let acc = MStmt.LetVal (tempSerial, init, initTy, loc) :: acc
    let init, initTy = MInit.App (temp, arg), appTy
    unroll initTy loc init args acc ctx
  | _ ->
    failwith "type error"

/// Builds an argument list to call an underlying function of partial application.
/// E.g. When it's partial application like `let f x y = x + y + a in g 1`,
/// we are generating function like `let g t y = f t.0 t.1 y` where `t = (a, 1)`,
/// this function builds `f t.0 t.1 y` part.
let buildForwardingArgs capsArg lastArg capsArgTy argTys loc =
  let rec go acc argTys i =
    match argTys with
    | [] ->
      List.rev (lastArg :: acc)
    | argTy :: argTys ->
      let caps = MExpr.UniOp (MUniOp.Unbox, capsArg, capsArgTy, loc)
      let arg = MExpr.UniOp (MUniOp.Proj i, caps, argTy, loc)
      go (arg :: acc) argTys (i + 1)
  go [] argTys 0

/// Packs items into a boxed tuple, called environment.
let buildEnvTuple args loc acc ctx =
  let envTy = args |> List.map mexprTy |> MTy.Tuple
  let envRef, envSerial, ctx = ctx |> ctxFreshVar "env" envTy loc
  let _, boxSerial, ctx = ctx |> ctxFreshVar "box" MTy.Obj loc
  let acc = MStmt.LetVal (envSerial, MInit.Tuple args, envTy, loc) :: acc
  let acc = MStmt.LetVal (boxSerial, MInit.Box envRef, MTy.Obj, loc) :: acc
  boxSerial, acc, ctx

/// Resolves partial application.
/// 1. Define an underlying function, accepting environment and rest arguments,
///   to call the callee with full arguments.
/// 2. Create a boxed tuple called environment from given arguments.
/// 3. Create a function object, pair of the underlying function and environment.
let resolvePartialApp arity funTy loc argLen callee args acc ctx =
  // FIXME: support `arity > argLen + 1` cases
  assert (arity = argLen + 1)
  let resultTy = appliedTy arity funTy
  let appArgTy = appliedTy (arity - 1) funTy |> funArgTy
  let envTys = argTys (arity - 1) funTy
  let envTy = MTy.Tuple envTys
  let _, subFunSerial, ctx = ctxFreshVar "fun" funTy loc ctx
  let envArg, envArgSerial, ctx = ctxFreshVar "env" MTy.Obj loc ctx
  let appArg, appArgSerial, ctx = ctxFreshVar "arg" appArgTy loc ctx

  // let g env x = callee ..(unbox env) x
  let body, ctx =
    let temp, tempSerial, ctx = ctxFreshVar "call" resultTy loc ctx
    let callArgs = buildForwardingArgs envArg appArg envTy envTys loc
    let init = MInit.Call (callee, callArgs)
    let body = [
      MStmt.LetVal (tempSerial, init, resultTy, loc)
      MStmt.Return (temp, loc)
    ]
    body, ctx
  // (g, env=(..args)) as int -> int
  let funArgs =
    [
      envArgSerial, 1, MTy.Obj, loc
      appArgSerial, 1, appArgTy, loc
    ]
  let decl = MDecl.LetFun (subFunSerial, funArgs, [], resultTy, body, loc)

  let envSerial, acc, ctx = buildEnvTuple args loc acc ctx
  let ctx = ctx |> ctxAddDecl decl

  MInit.Fun (subFunSerial, envSerial), acc, ctx

let unetaInitCallFun arity funTy loc callee args acc (ctx: MirTransCtx) =
  let argLen = List.length args
  if argLen < arity then
    resolvePartialApp arity funTy loc argLen callee args acc ctx
  else
    let callArgs, restArgs = splitAt arity args
    let init = MInit.Call (callee, callArgs)
    let initTy = appliedTy arity funTy
    unroll initTy loc init restArgs acc ctx

let unetaInitCall loc callee args acc (ctx: MirTransCtx) =
  match callee, args with
  | MExpr.Ref (serial, arity, funTy, loc), _ when ctx |> ctxIsFun serial ->
    unetaInitCallFun arity funTy loc callee args acc ctx
  | _, arg :: args ->
    let initTy = appliedTy 1 (mexprTy callee)
    unroll initTy loc (MInit.App (callee, arg)) args acc ctx
  | _ ->
    failwith "Never"

let unetaInit loc (init, acc, ctx) =
  match init with
  | MInit.UnInit _ ->
    init, acc, ctx
  | MInit.Expr expr ->
    MInit.Expr expr, acc, ctx
  | MInit.Call (callee, args) ->
    unetaInitCall loc callee args acc ctx
  | MInit.Box expr ->
    MInit.Box expr, acc, ctx
  | MInit.Cons (head, tail, itemTy) ->
    MInit.Cons (head, tail, itemTy), acc, ctx
  | MInit.Tuple items ->
    MInit.Tuple items, acc, ctx
  | MInit.Union (serial, arg, argTy) ->
    MInit.Union (serial, arg, argTy), acc, ctx
  | MInit.App _
  | MInit.Fun _ ->
    failwith "Never: Not generated yet."

let unetaStmtLetVal serial init ty loc acc (ctx: MirTransCtx) =
  let init, acc, ctx = (init, acc, ctx) |> unetaInit loc
  MStmt.LetVal (serial, init, ty, loc) :: acc, ctx

let unetaStmt (stmt, acc, ctx) =
  match stmt with
  | MStmt.Do (expr, loc) ->
    MStmt.Do (expr, loc) :: acc, ctx
  | MStmt.LetVal (serial, init, ty, loc) ->
    unetaStmtLetVal serial init ty loc acc ctx
  | MStmt.Set (serial, init, loc) ->
    MStmt.Set (serial, init, loc) :: acc, ctx
  | MStmt.Return (r, loc) ->
    MStmt.Return (r, loc) :: acc, ctx
  | MStmt.Label _
  | MStmt.Goto _ ->
    stmt :: acc, ctx
  | MStmt.GotoUnless (pred, label, loc) ->
    MStmt.GotoUnless (pred, label, loc) :: acc, ctx
  | MStmt.Exit (arg, loc) ->
    MStmt.Exit (arg, loc) :: acc, ctx

let unetaDeclTyDef decl tyDef ctx =
  match tyDef with
  | TyDef.Union _ ->
    ctx |> ctxAddDecl decl

let unetaDeclLetFun callee args caps ty body loc ctx =
  let body, ctx = (body, ctx) |> stFlatMap unetaStmt
  ctx |> ctxAddDecl (MDecl.LetFun (callee, args, caps, ty, body, loc))

let unetaDecl ctx decl =
  match decl with
  | MDecl.TyDef (_, tyDef, _) ->
    unetaDeclTyDef decl tyDef ctx
  | MDecl.LetFun (callee, args, caps, ty, body, loc) ->
    unetaDeclLetFun callee args caps ty body loc ctx

let uneta (decls, ctx: MirTransCtx) =
  let ctx = List.fold unetaDecl ctx decls
  List.rev ctx.Decls, ctx

let trans (decls, mirCtx) =
  let ctx = ctxFromMirCtx mirCtx
  (decls, ctx) |> declosure |> uneta
