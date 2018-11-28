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

/// Creates an initializer to call the result of call expression.
/// E.g. `let lift f = List.map f in lift id xs`,
/// the `init` is to call `lift id` and here we make an initializer to call it.
let restCall initTy loc init args acc ctx =
  match args with
  | [] ->
    init, acc, ctx
  | args ->
    let temp, tempSerial, ctx  = ctxFreshVar "app" initTy loc ctx
    let acc = MStmt.LetVal (tempSerial, init, initTy, loc) :: acc
    let init = MInit.Call (temp, args, initTy)
    init, acc, ctx

/// Builds an argument list to call an underlying function of partial application.
/// E.g. When it's partial application like `let f x y = x + y + a in g 1`,
/// we are generating function like `let g t y = f t.0 t.1 y` where `t = (a, 1)`,
/// this function builds `f t.0 t.1 y` part.
let buildForwardingArgs capsArg restArgs capsArgTy argTys loc =
  let rec go acc argTys i =
    match argTys with
    | [] ->
      List.rev acc @ restArgs
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

/// Calculates rest argument types for the function with the specified arity
/// after partially applied the specified number of arguments.
/// E.g. if arity=2, argLen=1, funTy=`int->string->(char->unit)` then `[string]`
let rec restArgTys arity argLen funTy =
  if arity <= 0 then
    []
  else if argLen <= 0 then
    match funTy with
    | MTy.Fun (sTy, tTy) ->
      sTy :: restArgTys (arity - 1) 0 tTy
    | _ ->
      failwith "Never: Type error."
  else
    match funTy with
    | MTy.Fun (_, ty) ->
      restArgTys (arity - 1) (argLen - 1) ty
    | _ ->
      failwith "Never: Type error."

/// Resolves partial application.
/// 1. Define an underlying function, accepting environment and rest arguments,
///   to call the callee with full arguments.
/// 2. Create a boxed tuple called environment from given arguments.
/// 3. Create a function object, pair of the underlying function and environment.
let resolvePartialApp arity funTy loc argLen callee args calleeTy acc ctx =
  // FIXME: support `arity > argLen + 1` cases
  assert (argLen < arity)
  let resultTy = appliedTy arity funTy
  let restArgTys = restArgTys arity argLen funTy
  let envTys = argTys argLen funTy
  let envTy = MTy.Tuple envTys
  let _, subFunSerial, ctx = ctxFreshVar "fun" funTy loc ctx
  let envArg, envArgSerial, ctx = ctxFreshVar "env" MTy.Obj loc ctx

  let restArgs, funArgs, ctx =
    let rec go restArgs funArgs argTys ctx =
      match argTys with
      | [] ->
        List.rev restArgs, List.rev funArgs, ctx
      | argTy :: argTys ->
        let arg, serial, ctx = ctxFreshVar "arg" argTy loc ctx
        let funArg = serial, arityMTy argTy, argTy, loc
        go (arg :: restArgs) (funArg :: funArgs) argTys ctx
    go [] [] restArgTys ctx

  // let g env x = callee ..(unbox env) x
  let body, ctx =
    let temp, tempSerial, ctx = ctxFreshVar "call" resultTy loc ctx
    let callArgs = buildForwardingArgs envArg restArgs envTy envTys loc
    let init = MInit.Call (callee, callArgs, calleeTy)
    let body = [
      MStmt.LetVal (tempSerial, init, resultTy, loc)
      MStmt.Return (temp, loc)
    ]
    body, ctx
  // (g, env=(..args)) as int -> int
  let funArgs = (envArgSerial, 0, MTy.Obj, loc) :: funArgs
  let decl = MDecl.LetFun (subFunSerial, funArgs, [], resultTy, body, loc)

  let envSerial, acc, ctx = buildEnvTuple args loc acc ctx
  let ctx = ctx |> ctxAddDecl decl

  MInit.Fun (subFunSerial, envSerial), acc, ctx

let unetaInitCallFun arity funTy loc callee args calleeTy acc (ctx: MirTransCtx) =
  let argLen = List.length args
  if argLen < arity then
    resolvePartialApp arity funTy loc argLen callee args calleeTy acc ctx
  else
    let callArgs, restArgs = splitAt arity args
    let init = MInit.Call (callee, callArgs, calleeTy)
    let initTy = appliedTy arity funTy
    restCall initTy loc init restArgs acc ctx

let unetaInitCall callee args calleeTy acc (ctx: MirTransCtx) =
  match callee, args with
  | MExpr.Ref (serial, arity, funTy, loc), _ when ctx |> ctxIsFun serial ->
    unetaInitCallFun arity funTy loc callee args calleeTy acc ctx
  | _, args ->
    MInit.App (callee, args), acc, ctx
  | _ ->
    failwith "Never"

let unetaInit loc (init, acc, ctx) =
  match init with
  | MInit.UnInit _ ->
    init, acc, ctx
  | MInit.Expr expr ->
    MInit.Expr expr, acc, ctx
  | MInit.Call (callee, args, calleeTy ) ->
    unetaInitCall callee args calleeTy acc ctx
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
  (decls, ctx) |> uneta
