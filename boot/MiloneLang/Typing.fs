module rec MiloneLang.Typing

open MiloneLang
open MiloneLang.Helpers

/// Reference of namespace.
[<RequireQualifiedAccess>]
type NsRef =
  /// Type as namespace to host static members, e.g. `String.Join`.
  | TyStatic
    of int
  /// Type as namespace to host instance members, e.g. `(_: string).Length`.
  | TyDynamic
    of int

/// Identifier to denote some symbol in namespace.
[<RequireQualifiedAccess>]
type IdentRef =
  | Var
    of string
  | Ty
    of string

[<RequireQualifiedAccess>]
type SymbolRef =
  | Var
    of int
  | Ty
    of int

type TyCtx =
  {
    /// Next serial number for variables.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    VarSerial: int
    /// Variable serial to variable definition.
    Vars: Map<int, VarDef>
    /// Identifier to variable serial.
    VarEnv: Map<string, int>
    TySerial: int
    /// Identifier to type serial.
    TyEnv: Map<string, int>
    /// Type serial to type definition.
    Tys: Map<int, TyDef>
    TyDepths: Map<int, int>
    /// Namespaces.
    Ns: (NsRef * IdentRef * SymbolRef) list
    LetDepth: int
    UnifyQueue: (Ty * Ty * Loc) list
    Diags: Diag list
  }

let ctxAddErr (ctx: TyCtx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let ctxRollback bCtx dCtx: TyCtx =
  assert (bCtx.VarSerial <= dCtx.VarSerial)
  assert (bCtx.TySerial <= dCtx.TySerial)
  { dCtx with
      TyEnv = bCtx.TyEnv
      VarEnv = bCtx.VarEnv
      LetDepth = bCtx.LetDepth
  }

let ctxToTyCtx (ctx: TyCtx): TyContext =
  {
    TySerial = ctx.TySerial
    Tys = ctx.Tys
    TyDepths = ctx.TyDepths
  }

let ctxWithTyCtx (ctx: TyCtx) (tyCtx: TyContext): TyCtx =
  { ctx with
      TySerial = tyCtx.TySerial
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths
  }

let ctxIncLetDepth (ctx: TyCtx) =
  { ctx with LetDepth = ctx.LetDepth + 1 }

let ctxFreshTySerial (ctx: TyCtx) =
  let serial = ctx.TySerial + 1
  let ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyDepths = ctx.TyDepths |> Map.add serial ctx.LetDepth
    }
  serial, ctx

let ctxFreshTyVar ident (ctx: TyCtx): Ty * string * TyCtx =
  let serial, ctx = ctxFreshTySerial ctx
  let ident = sprintf "'%s_%d" ident serial
  let ty = Ty.Meta serial
  let ctx =
    { ctx with
        TyEnv = ctx.TyEnv |> Map.add ident serial
    }
  ty, ident, ctx

let ctxUnifyLater (ctx: TyCtx) unresolvedTy metaTy loc =
  { ctx with UnifyQueue = (unresolvedTy, metaTy, loc) :: ctx.UnifyQueue }

let ctxResolveUnifyQueue (ctx: TyCtx) =
  let rec go ctx queue =
    match queue with
    | [] ->
      ctx
    | (unresolvedTy, metaTy, loc) :: queue ->
      let resolvedTy, ctx = ctxResolveTy ctx unresolvedTy
      let ctx = unifyTy ctx loc resolvedTy metaTy
      go ctx queue
  let queue = ctx.UnifyQueue
  let ctx = { ctx with UnifyQueue = [] }
  go ctx queue

let ctxAddVariant unionTyIdent unionTySerial unionTy variant loc ctx =
  let variantIdent, _, hasArg, unresolvedArgTy =
    variant
  let argTy, ctx =
    if hasArg then
      let argTy, _, ctx = ctxFreshTyVar "arg" ctx
      let ctx = ctxUnifyLater ctx unresolvedArgTy argTy loc
      argTy, ctx
    else
      tyUnit, ctx
  let variantTy =
    if hasArg then
      tyFun argTy unionTy
    else
      unionTy
  let variantVarDef =
    VarDef.Variant (variantIdent, unionTySerial, hasArg, argTy, variantTy, loc)
  let variantSerial, ctx =
    ctxFreshVarCore ctx variantIdent variantVarDef

  // The variant is the static member of the namespace.
  let ctx =
    let nsRef = NsRef.TyStatic unionTySerial
    let memRef = IdentRef.Var variantIdent
    let symbol = SymbolRef.Var variantSerial
    ctxAddNsMember ctx nsRef memRef symbol

  let variant = variantIdent, variantSerial, hasArg, argTy
  variant, variantSerial, ctx

let ctxAddVariants unionTyIdent unionTySerial unionTy variants loc ctx =
  let rec go variantAcc variantSerialAcc variants ctx =
    match variants with
    | [] ->
      List.rev variantAcc, List.rev variantSerialAcc, ctx
    | variant :: variants ->
      let variant, lSerial, ctx = ctxAddVariant unionTyIdent unionTySerial unionTy variant loc ctx
      go (variant :: variantAcc) (lSerial :: variantSerialAcc) variants ctx
  go [] [] variants ctx

/// Add a type declaration to the context.
/// At the moment we can't resolve types correctly
/// because some type definitions are still unseen.
let ctxAddTy tyIdent tyDecl loc ctx =
  match tyDecl with
  | TyDecl.Synonym (bodyTy, synonymLoc) ->
    let synonymTySerial, ctx = ctxFreshTySerial ctx
    let synonymTy, _, ctx = ctxFreshTyVar "synonym" ctx
    let ctx =
      { ctx with
          TyEnv = ctx.TyEnv |> Map.add tyIdent synonymTySerial
          Tys = ctx.Tys |> Map.add synonymTySerial (TyDef.Meta (tyIdent, synonymTy, loc))
      }
    let ctx = ctxUnifyLater ctx bodyTy synonymTy synonymLoc
    synonymTySerial, tyDecl, ctx

  | TyDecl.Union (_, variants, _) ->
    let unionTySerial, ctx = ctxFreshTySerial ctx
    let unionTy = tyRef unionTySerial []
    let unionTyIdent = tyIdent

    // Register variants as variables.
    let variants, variantSerials, ctx =
      ctxAddVariants unionTyIdent unionTySerial unionTy variants loc ctx

    let unionTyDef = TyDef.Union (unionTyIdent, variantSerials, loc)
    let ctx =
      { ctx with
          TyEnv = ctx.TyEnv |> Map.add unionTyIdent unionTySerial
          Tys = ctx.Tys |> Map.add unionTySerial unionTyDef
      }

    let unionTyDecl = TyDecl.Union (unionTyIdent, variants, loc)
    unionTySerial, unionTyDecl, ctx

let ctxFreshVarCore (ctx: TyCtx) ident varDef: int * TyCtx =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarEnv = ctx.VarEnv |> Map.add ident serial
        Vars = ctx.Vars |> Map.add serial varDef
    }
  serial, ctx

let ctxFreshVar ctx ident ty loc =
  ctxFreshVarCore ctx ident (VarDef.Var (ident, ty, loc))

let ctxFreshFun ctx ident arity ty loc =
  ctxFreshVarCore ctx ident (VarDef.Fun (ident, arity, ty, loc))

let ctxAddVarAlias (ctx: TyCtx) serial aliasIdent =
  { ctx with
      VarEnv = ctx.VarEnv |> Map.add aliasIdent serial
  }

let ctxAddNsMember (ctx: TyCtx) ns mem symbol =
  { ctx with Ns = (ns, mem, symbol) :: ctx.Ns }

let ctxFindNs (ctx: TyCtx) ns mem =
  let rec go nss =
    match nss with
    | [] ->
      None
    | (xNs, xMem, symbol) :: _ when xNs = ns && xMem = mem ->
      Some symbol
    | _ :: nss ->
      go nss
  go ctx.Ns

let ctxResolveQualifiedVariant ctx tyIdent variantIdent =
  match ctxFindTyDef tyIdent ctx with
  | Some (tySerial, _) ->
    match ctxFindNs ctx (NsRef.TyStatic tySerial) (IdentRef.Var variantIdent) with
    | Some (SymbolRef.Var serial) ->
      match ctxFindVar ctx serial with
      | VarDef.Variant (ident, tySerial, hasArg, argTy, ty, loc) ->
        Some (serial, (ident, tySerial, hasArg, argTy, ty, loc))
      | _ -> None
    | _ -> None
  | None -> None

let ctxFindTyDef name (ctx: TyCtx) =
  match ctx.TyEnv |> Map.tryFind name with
  | Some tySerial ->
    match ctx.Tys |> Map.tryFind tySerial with
    | Some tyDef ->
      Some (tySerial, tyDef)
    | None ->
      None
  | None ->
    None

let ctxResolveTyRefIdent ident (ctx: TyCtx) =
  match ctx |> ctxFindTyDef ident with
  | None ->
    Ty.Error
  | Some (_, TyDef.Meta (_, ty, _)) ->
    ty
  | Some (tySerial, _) ->
    tyRef tySerial []

/// Resolves type references in type annotation.
let ctxResolveTy ctx ty =
  let rec go (ty, ctx) =
    match ty with
    | Ty.Error
    | Ty.Con (TyCon.Ref _, _) ->
      ty, ctx
    | Ty.Con (TyCon.RefIdent "_", _) ->
      let tySerial, ctx = ctxFreshTySerial ctx
      Ty.Meta tySerial, ctx
    | Ty.Con (TyCon.RefIdent ident, _) ->
      ctxResolveTyRefIdent ident ctx, ctx
    | Ty.Con (tyCon, tys) ->
      let tys, ctx = (tys, ctx) |> stMap go
      Ty.Con (tyCon, tys), ctx
    | Ty.Meta _ ->
      failwith "Never"
  go (ty, ctx)

/// Gets if the specified type var doesn't appear in the specified type.
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Con (_, []) ->
      true
    | Ty.Con (tyCon, ty :: tys) ->
      go ty && go (Ty.Con (tyCon, tys))
    | Ty.Meta s ->
      s <> tySerial
  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are resolved by `substTy`.
let tyIsMonomorphic ty: bool =
  let rec go tys =
    match tys with
    | [] ->
      true
    | Ty.Meta _ :: _ ->
      false
    | Ty.Error :: tys ->
      go tys
    | Ty.Con (_, tys1) :: tys2 ->
      go tys1 && go tys2
  go [ty]

/// Adds type-var/type binding.
let bindTyCore (ctx: TyContext) tySerial ty =
  // FIXME: track location info
  let noLoc = 0, 0
  // FIXME: track identifier
  let noIdent = "unknown"

  // Don't bind itself.
  match substTyCore ctx ty with
  | Ty.Meta s when s = tySerial -> ctx
  | _ ->

  // Update depth of all related meta types to the minimum.
  let tyDepths =
    let tySerials = tySerial :: tyCollectFreeVars ty
    let depth =
      tySerials
      |> List.map (fun tySerial -> ctx.TyDepths |> Map.find tySerial)
      |> List.min
    tySerials |> List.fold (fun tyDepths tySerial -> tyDepths |> Map.add tySerial depth) ctx.TyDepths

  { ctx with
      Tys = ctx.Tys |> Map.add tySerial (TyDef.Meta (noIdent, ty, noLoc))
      TyDepths = tyDepths
  }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let substTyCore (ctx: TyContext) ty: Ty =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Con (_, []) ->
      ty
    | Ty.Con (tyCon, tys) ->
      Ty.Con (tyCon, List.map go tys)
    | Ty.Meta tySerial ->
      match ctx.Tys |> Map.tryFind tySerial with
      | Some (TyDef.Meta (_, ty, _)) ->
        go ty
      | _ ->
        ty
  go ty

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let unifyTyCore (ctx: TyContext) (lty: Ty) (rty: Ty): string list * TyContext =
  let lRootTy, rRootTy = lty, rty
  let rec go lty rty (msgAcc, ctx) =
    let lSubstTy = substTyCore ctx lty
    let rSubstTy = substTyCore ctx rty
    match lSubstTy, rSubstTy with
    | Ty.Meta l, Ty.Meta r when l = r ->
      msgAcc, ctx
    | Ty.Meta lSerial, _ when tyIsFreeIn rSubstTy lSerial ->
      let ctx = bindTyCore ctx lSerial rty
      msgAcc, ctx
    | _, Ty.Meta _ ->
      go rty lty (msgAcc, ctx)
    | Ty.Con (lTyCon, []), Ty.Con (rTyCon, []) when lTyCon = rTyCon ->
      msgAcc, ctx
    | Ty.Con (lTyCon, lTy :: lTys), Ty.Con (rTyCon, rTy :: rTys) ->
      (msgAcc, ctx) |> go lTy rTy |> go (Ty.Con (lTyCon, lTys)) (Ty.Con (rTyCon, rTys))
    | Ty.Error, _
    | _, Ty.Error ->
      msgAcc, ctx
    | Ty.Meta _, _ ->
      let msg = sprintf "Couldn't unify '%A' and '%A' due to self recursion." lSubstTy rSubstTy
      msg :: msgAcc, ctx
    | Ty.Con _, _ ->
      let lRootTy = substTyCore ctx lRootTy
      let rRootTy = substTyCore ctx rRootTy
      let msg = sprintf "While unifying '%A' and '%A', failed to unify '%A' and '%A'." lRootTy rRootTy lSubstTy rSubstTy
      msg :: msgAcc, ctx
  let msgAcc, ctx =
    go lty rty ([], ctx)
  List.rev msgAcc, ctx

let bindTy (ctx: TyCtx) tySerial ty =
  bindTyCore (ctxToTyCtx ctx) tySerial ty |> ctxWithTyCtx ctx

let substTy (ctx: TyCtx) ty: Ty =
  substTyCore (ctxToTyCtx ctx) ty

let unifyTy (ctx: TyCtx) loc (lty: Ty) (rty: Ty): TyCtx =
  let msgs, tyCtx = unifyTyCore (ctxToTyCtx ctx) lty rty
  let ctx = ctxWithTyCtx ctx tyCtx
  let ctx = List.fold (fun ctx msg -> ctxAddErr ctx msg loc) ctx msgs
  ctx

/// Assume all bound type variables are resolved by `substTy`.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] ->
      fvAcc
    | Ty.Error :: tys
    | Ty.Con (_, []) :: tys ->
      go fvAcc tys
    | Ty.Con (_, tys1) :: tys2 ->
      let acc = go fvAcc tys1
      let acc = go acc tys2
      acc
    | Ty.Meta serial :: tys ->
      let acc = serial :: fvAcc
      go acc tys
  go [] [ty] |> listUnique

/// Assume all bound type variables are resolved by `substTy`.
///
/// `isOwned` checks if the type variable is introduced by the most recent `let`.
/// For example, `let f x = (let g = f in g x)` will have too generic type
/// without this checking (according to TaPL).
let tyGeneralize isOwned (ty: Ty) =
  let fvs = tyCollectFreeVars ty |> List.filter isOwned
  TyScheme.ForAll (fvs, ty)

let tySchemeInstantiate ctx (tyScheme: TyScheme) =
  match tyScheme with
  | TyScheme.ForAll ([], ty) ->
    ty, ctx
  | TyScheme.ForAll (fvs, ty) ->
    // Generate fresh type variable for each bound type variable.
    let mapping, ctx =
      (fvs, ctx) |> stMap (fun (fv, ctx) ->
        let newSerial, ctx = ctxFreshTySerial ctx
        (fv, newSerial), ctx
      )

    // Replace bound variables in the type with fresh ones.
    let ty =
      let extendedCtx =
        mapping |> List.fold
          (fun ctx (src, target) -> bindTy ctx src (Ty.Meta target)) ctx
      substTy extendedCtx ty

    ty, ctx

let ctxFindVar (ctx: TyCtx) serial =
  ctx.Vars |> Map.find serial

let ctxResolveVar (ctx: TyCtx) ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | None -> None
  | Some serial ->
    match ctx.Vars |> Map.tryFind serial with
    | None -> None
    | Some varDef -> Some (serial, varDef)

let ctxGeneralizeFun (ctx: TyCtx) (outerCtx: TyCtx) (bodyCtx: TyCtx) funSerial =
  match ctx.Vars |> Map.find funSerial with
  | VarDef.Fun (ident, arity, TyScheme.ForAll ([], funTy), loc) ->
    let isOwned tySerial =
      let depth = bodyCtx.TyDepths |> Map.find tySerial
      depth > outerCtx.LetDepth
    let funTy = substTy bodyCtx funTy
    let funTyScheme = tyGeneralize isOwned funTy
    let varDef = VarDef.Fun (ident, arity, funTyScheme, loc)
    let ctx = { ctx with Vars = ctx.Vars |> Map.add funSerial varDef }
    ctx
  | VarDef.Fun _ ->
    failwith "Can't generalize already-generalized function"
  | _ ->
    failwith "Expected function"

/// Creates an expression to abort.
let hxAbort (ctx: TyCtx) ty loc =
  let funTy = tyFun tyInt ty
  let exitExpr = HExpr.Ref ("exit", HValRef.Prim HPrim.Exit, funTy, loc)
  let callExpr = HExpr.Op (Op.App, exitExpr, HExpr.Lit (Lit.Int 1, loc), ty, loc)
  callExpr, ctx

/// Collect types defined in recursive module.
let collectTyDecls ctx expr =
  let rec go (expr, ctx) =
    match expr with
    | HExpr.Let (pat, init, next, ty, loc) ->
      let next, ctx = (next, ctx) |> go
      HExpr.Let (pat, init, next, ty, loc), ctx

    | HExpr.LetFun (ident, serial, args, body, next, ty, loc) ->
      let next, ctx = (next, ctx) |> go
      HExpr.LetFun (ident, serial, args, body, next, ty, loc), ctx

    | HExpr.TyDef (ident, _, tyDecl, loc) ->
      let tySerial, tyDecl, ctx = ctx |> ctxAddTy ident tyDecl loc
      HExpr.TyDef (ident, tySerial, tyDecl, loc), ctx

    | HExpr.Inf (InfOp.AndThen, exprs, ty, loc) ->
      let exprs, ctx = (exprs, ctx) |> stMap go
      HExpr.Inf (InfOp.AndThen, exprs, ty, loc), ctx

    | _ ->
      expr, ctx

  let expr, ctx = (expr, ctx) |> go
  let ctx = ctxResolveUnifyQueue ctx
  expr, ctx

/// Traverse over in-module variable declarations to build environment
/// to resolve mutually recursive references correctly.
let collectVarDecls ctx expr =
  let rec goPat (pat, ctx) =
    match pat with
    | HPat.Lit _
    | HPat.Nav _
    | HPat.Nil _
    // NOTE: OR patterns doesn't appear because not entering `match` arms.
    | HPat.Or _ ->
      pat, ctx

    | HPat.Ref (ident, _, ty, loc) ->
      // FIXME: handle variant case
      let varTy, _, ctx = ctxFreshTyVar "var" ctx
      let varSerial, ctx = ctxFreshVar ctx ident varTy loc
      HPat.Ref (ident, varSerial, ty, loc), ctx

    | HPat.Call (callee, args, ty, loc) ->
      let args, ctx = (args, ctx) |> stMap goPat
      HPat.Call (callee, args, ty, loc), ctx

    | HPat.Cons (l, r, ty, loc) ->
      let l, ctx = (l, ctx) |> goPat
      let r, ctx = (r, ctx) |> goPat
      HPat.Cons (l, r, ty, loc), ctx

    | HPat.Tuple (items, ty, loc) ->
      let items, ctx = (items, ctx) |> stMap goPat
      HPat.Tuple (items, ty, loc), ctx

    | HPat.As (pat, ident, _, loc) ->
      let varSerial, ctx = ctxFreshVar ctx ident noTy loc
      let pat, ctx = (pat, ctx) |> goPat
      HPat.As (pat, ident, varSerial, loc), ctx

    | HPat.Anno (pat, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      HPat.Anno (pat, ty, loc), ctx

  let rec goExpr (expr, ctx) =
    match expr with
    | HExpr.Let (pat, init, next, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      let next, ctx = (next, ctx) |> goExpr
      HExpr.Let (pat, init, next, ty, loc), ctx

    | HExpr.LetFun (ident, _, args, body, next, ty, loc) ->
      let funTy, _, ctx = ctxFreshTyVar "fun" ctx
      let arity = args |> List.length
      let tyScheme = TyScheme.ForAll ([], funTy)
      let varSerial, ctx = ctxFreshFun ctx ident arity tyScheme loc
      let next, ctx = (next, ctx) |> goExpr
      HExpr.LetFun (ident, varSerial, args, body, next, ty, loc), ctx

    | HExpr.Inf (InfOp.AndThen, exprs, ty, loc) ->
      let exprs, ctx = (exprs, ctx) |> stMap goExpr
      HExpr.Inf (InfOp.AndThen, exprs, ty, loc), ctx

    | _ ->
      expr, ctx

  goExpr (expr, ctx)

let ctxTryResolvePredefinedVar (ctx: TyCtx) maybeVarSerial newTy loc =
  let oldTy =
    match ctx.Vars |> Map.tryFind maybeVarSerial with
    | Some (VarDef.Var (_, oldTy, _)) ->
      Some oldTy
    | Some (VarDef.Fun (_, _, TyScheme.ForAll ([], oldTy), _)) ->
      Some oldTy
    | Some (VarDef.Fun _) ->
      None
    | Some (VarDef.Variant (_, _, _, _, oldTy, _)) ->
      Some oldTy
    | None ->
      None
  match oldTy with
  | Some oldTy ->
    let ctx = unifyTy ctx loc oldTy newTy
    true, ctx
  | None ->
    false, ctx

let inferPatRef (ctx: TyCtx) ident oldSerial loc ty =
  let predefined, ctx = ctxTryResolvePredefinedVar ctx oldSerial ty loc
  if predefined then
    HPat.Ref (ident, oldSerial, ty, loc), ctx
  else

  let serial, ty, ctx =
    match ctxResolveVar ctx ident with
    | Some (serial, VarDef.Variant (_, _, _, _, variantTy, _)) ->
      let ctx = unifyTy ctx loc ty variantTy
      serial, ty, ctx
    | _ ->
      let serial, ctx = ctxFreshVar ctx ident ty loc
      serial, ty, ctx
  HPat.Ref (ident, serial, ty, loc), ctx

let inferPatNav (ctx: TyCtx) l r loc ty =
  match l with
  | HPat.Ref (l, _, _, _) ->
    match ctxResolveQualifiedVariant ctx l r with
    | Some (variantSerial, (variantIdent, _, false, _, variantTy, _)) ->
      let ctx = unifyTy ctx loc ty variantTy
      HPat.Ref (variantIdent, variantSerial, ty, loc), ctx
    | _ ->
      failwith "Unknown type"
  | _ ->
    failwith "invalid use of nav pattern"

let inferPatCall (ctx: TyCtx) callee args loc ty =
  let core ctx calleeSerial arg calleeLoc callLoc ty =
    match ctxFindVar ctx calleeSerial with
    | VarDef.Variant (ident, _, true, _, (Ty.Con (TyCon.Fun, [argTy; callTy]) as variantTy), _) ->
      let arg, ctx = inferPat ctx arg argTy
      let callee = HPat.Ref (ident, calleeSerial, variantTy, calleeLoc)
      let ctx = unifyTy ctx callLoc ty callTy
      HPat.Call (callee, [arg], ty, callLoc), ctx
    | _ ->
      let ctx = ctxAddErr ctx "Expected a function variant." callLoc
      patUnit callLoc, ctx

  match callee, args with
  | HPat.Ref (ident, _, _, refLoc), [arg] ->
    match ctxResolveVar ctx ident with
    | Some (serial, _) ->
      core ctx serial arg refLoc loc ty
    | None ->
      let ctx = ctxAddErr ctx "Unknown variant" refLoc
      patUnit refLoc, ctx
  | HPat.Nav (HPat.Ref (tyIdent, _, _, _), variantIdent, _, refLoc), [arg] ->
    match ctxResolveQualifiedVariant ctx tyIdent variantIdent with
    | Some (serial, _) ->
      core ctx serial arg refLoc loc ty
    | None ->
      failwith "unknown variant"
  | _ ->
    failwith "unimpl use of call pattern"

let inferPatTuple ctx itemPats loc tupleTy =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] ->
      List.rev accPats, List.rev accTys, ctx
    | itemPat :: itemPats ->
      let itemTy, _, ctx = ctxFreshTyVar "item" ctx
      let itemPat, ctx = inferPat ctx itemPat itemTy
      go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats
  let itemPats, itemTys, ctx = go [] [] ctx itemPats
  let ctx = unifyTy ctx loc tupleTy (tyTuple itemTys)
  HPat.Tuple (itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  HPat.Cons (l, r, itemTy, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | HPat.Lit (lit, loc) ->
    pat, unifyTy ctx loc ty (litTy lit)
  | HPat.Nil (_, loc) ->
    let itemTy, _, ctx = ctxFreshTyVar "item" ctx
    let ctx = unifyTy ctx loc ty (tyList itemTy)
    HPat.Nil (itemTy, loc), ctx
  | HPat.Ref (ident, oldSerial, _, loc) ->
    inferPatRef ctx ident oldSerial loc ty
  | HPat.Nav (l, r, _, loc) ->
    inferPatNav ctx l r loc ty
  | HPat.Call (callee, args, _, loc) ->
    inferPatCall ctx callee args loc ty
  | HPat.Cons (l, r, _, loc) ->
    inferPatCons ctx l r loc ty
  | HPat.Tuple (items, _, loc) ->
    inferPatTuple ctx items loc ty
  | HPat.As (pat, ident, _, loc) ->
    let serial, ctx = ctxFreshVar ctx ident ty loc
    let pat, ctx = inferPat ctx pat ty
    HPat.As (pat, ident, serial, loc), ctx
  | HPat.Anno (pat, annoTy, loc) ->
    let annoTy, ctx = ctxResolveTy ctx annoTy
    let ctx = unifyTy ctx loc ty annoTy
    let pat, ctx = inferPat ctx pat annoTy
    pat, ctx
  | HPat.Or (first, second, _, loc) ->
    // FIXME: Error if two patterns introduce different bindings.
    let first, ctx = inferPat ctx first ty
    let second, ctx = inferPat ctx second ty
    HPat.Or (first, second, ty, loc), ctx

let inferRef (ctx: TyCtx) ident loc ty =
  match ctxResolveVar ctx ident, ident with
  | Some (serial, VarDef.Fun (ident, _, tyScheme, loc)), _ ->
    let refTy, ctx = tySchemeInstantiate ctx tyScheme
    let ctx = unifyTy ctx loc refTy ty
    HExpr.Ref (ident, HValRef.Var serial, ty, loc), ctx
  | Some (serial, varDef), _ ->
    let refTy =
      match varDef with
      | VarDef.Var (_, ty, _) ->
        ty
      | VarDef.Variant (_, _, hasArg, _, ty, _) ->
        ty
      | VarDef.Fun _ ->
        failwith "NEVER"
    let ctx = unifyTy ctx loc refTy ty
    HExpr.Ref (ident, HValRef.Var serial, ty, loc), ctx
  | None, "not" ->
    let ctx = unifyTy ctx loc (tyFun tyBool tyBool) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Not, ty, loc), ctx
  | None, "exit" ->
    let resultTy, _, ctx = ctxFreshTyVar "exit" ctx
    let ctx = unifyTy ctx loc (tyFun tyInt resultTy) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Exit, ty, loc), ctx
  | None, "assert" ->
    let ctx = unifyTy ctx loc (tyFun tyBool tyUnit) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Assert, ty, loc), ctx
  | None, "box" ->
    let argTy, _, ctx = ctxFreshTyVar "box" ctx
    let ctx = unifyTy ctx loc (tyFun argTy tyObj) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Box, ty, loc), ctx
  | None, "unbox" ->
    let resultTy, _, ctx = ctxFreshTyVar "unbox" ctx
    let ctx = unifyTy ctx loc (tyFun tyObj resultTy) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Unbox, ty, loc), ctx
  | None, "printfn" ->
    // The function's type is unified in app expression inference.
    HExpr.Ref (ident, HValRef.Prim HPrim.Printfn, ty, loc), ctx
  | None, "char" ->
    // FIXME: `char` can take non-int values, including chars.
    let ctx = unifyTy ctx loc (tyFun tyInt tyChar) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Char, ty, loc), ctx
  | None, "int" ->
    let argTy, _, ctx = ctxFreshTyVar "intArg" ctx
    let ctx = unifyTy ctx loc (tyFun argTy tyInt) ty
    let ctx =
      match substTy ctx argTy with
      | Ty.Meta _ ->
        unifyTy ctx loc tyInt argTy
      | Ty.Con ((TyCon.Int | TyCon.Char | TyCon.Str), _)
      | Ty.Error _ ->
        ctx
      | argTy ->
        ctxAddErr ctx (sprintf "Expected int or char %A" argTy) loc
    HExpr.Ref (ident, HValRef.Prim HPrim.Int, ty, loc), ctx
  | None, "string" ->
    let argTy, _, ctx = ctxFreshTyVar "stringArg" ctx
    let ctx = unifyTy ctx loc (tyFun argTy tyStr) ty
    let ctx =
      match substTy ctx argTy with
      | Ty.Con ((TyCon.Int | TyCon.Char | TyCon.Str), _)
      | Ty.Error _ ->
        ctx
      | _ ->
        ctxAddErr ctx (sprintf "FIXME: Not implemented `string` for %A" argTy) loc
    HExpr.Ref (ident, HValRef.Prim HPrim.String, ty, loc), ctx
  | None, "__nativeFun" ->
    HExpr.Ref (ident, HValRef.Prim (HPrim.NativeFun ("<NativeFunIdent>", -1)), ty, loc), ctx
  | None, _ ->
    let message = sprintf "Couldn't resolve var %s" ident
    let ctx = ctxAddErr ctx message loc
    hxAbort ctx ty loc

let inferNil ctx loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  hxNil itemTy loc, ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target arms loc resultTy =
  let targetTy, _, ctx = ctxFreshTyVar "target" ctx
  let target, ctx = inferExpr ctx target targetTy

  let arms, ctx =
    (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
      let baseCtx = ctx
      let pat, ctx = inferPat ctx pat targetTy
      let guard, ctx = inferExpr ctx guard tyBool
      let body, ctx = inferExpr ctx body resultTy
      let ctx = ctxRollback baseCtx ctx
      (pat, guard, body), ctx
    )

  HExpr.Match (target, arms, resultTy, loc), ctx

let inferNav ctx sub mes loc resultTy =
  // FIXME: This is just patch for tests to pass.
  match sub, mes with
  | HExpr.Ref ("String", _, _, _), "length" ->
    let strLengthFunTy = tyFun tyStr tyInt
    HExpr.Ref ("String.length", HValRef.Prim HPrim.StrLength, strLengthFunTy, loc), ctx
  |_ ->

  // Resolve path in the following order:
  // 1. <type>.<static-member>
  // 2. <value>.<instance-member>
  // NOTE: This implementation is very experimental.
  // NOTE: Nesting (`a.b.c`) is ignored yet.

  let findTyStaticMemberSerial () =
    match sub with
    | HExpr.Ref (tyStaticIdent, _, _, _) ->
      match ctxFindTyDef tyStaticIdent ctx with
      | Some (tySerial, _) ->
        match ctxFindNs ctx (NsRef.TyStatic tySerial) (IdentRef.Var mes) with
        | Some (SymbolRef.Var memberSerial) ->
          Some memberSerial
        | _ -> None
      | _ -> None
    | _ -> None

  let findTyStaticMember () =
    // FIXME: DRY to reuse inferRef
    let ty = resultTy
    match findTyStaticMemberSerial () with
    | Some serial ->
      match ctx.Vars |> Map.find serial with
      | VarDef.Fun (ident, _, tyScheme, loc) ->
        let refTy, ctx = tySchemeInstantiate ctx tyScheme
        let ctx = unifyTy ctx loc refTy ty
        Some (HExpr.Ref (ident, HValRef.Var serial, ty, loc), ctx)
      | varDef ->
        let refTy =
          match varDef with
          | VarDef.Var (_, ty, _) ->
            ty
          | VarDef.Variant (_, _, _, _, ty, _) ->
            ty
          | VarDef.Fun _ ->
            failwith "NEVER"
        let ctx = unifyTy ctx loc refTy ty
        Some (HExpr.Ref (mes, HValRef.Var serial, ty, loc), ctx)
    | _ -> None

  let findTyDynamicMember ctx sub subTy =
    match subTy, mes with
    | Ty.Con (TyCon.Str, []), "Length" ->
      let ctx = unifyTy ctx loc resultTy tyInt
      let funExpr = HExpr.Ref (mes, HValRef.Prim HPrim.StrLength, tyFun tyStr tyInt, loc)
      Some (HExpr.Op (Op.App, funExpr, sub, tyInt, loc), ctx)
    | _ -> None

  let hxError () =
    let ctx = ctxAddErr ctx (sprintf "Unknown nav %A.%s" sub mes) loc
    hxAbort ctx resultTy loc

  match findTyStaticMember () with
  | Some (expr, ctx) ->
    expr, ctx
  | None ->

  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let sub, ctx = inferExpr ctx sub subTy
  let subTy = substTy ctx subTy

  match findTyDynamicMember ctx sub subTy with
  | Some (expr, ctx) ->
    expr, ctx
  | None ->

  hxError ()

/// `x.[i] : 'y` <== x : 'x, i : int or i : range
/// NOTE: Currently only the `x : string` case can compile, however,
/// we don't infer that for compatibility.
let inferIndex ctx l r loc resultTy =
  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let indexTy, _, ctx = ctxFreshTyVar "index" ctx
  let l, ctx = inferExpr ctx l subTy
  let r, ctx = inferExpr ctx r indexTy
  match substTy ctx subTy, substTy ctx indexTy with
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Range, _) ->
    let ctx = unifyTy ctx loc resultTy tyStr
    hxIndex l r resultTy loc, ctx
  | Ty.Con (TyCon.Str, _), _ ->
    let ctx = unifyTy ctx loc indexTy tyInt
    let ctx = unifyTy ctx loc resultTy tyChar
    hxIndex l r resultTy loc, ctx
  | _ ->
    let ctx = ctxAddErr ctx "Type: Index not supported" loc
    hxAbort ctx resultTy loc

let inferOpAppNativeFun ctx callee firstArg arg appTy loc =
  match firstArg, arg with
  | HExpr.Lit (Lit.Str nativeFunIdent, _),
    HExpr.Lit (Lit.Int arity, _) ->
    let rec go ty arity ctx =
      if arity = 0 then
        ty, ctx
      else
        let argTy, _, ctx = ctxFreshTyVar "arg" ctx
        go (tyFun argTy ty) (arity - 1) ctx
    let resultTy, _, ctx = ctxFreshTyVar "result" ctx
    let funTy, ctx = go resultTy arity ctx
    let ctx = unifyTy ctx loc funTy appTy
    HExpr.Ref (nativeFunIdent, HValRef.Prim (HPrim.NativeFun (nativeFunIdent, arity)), appTy, loc), ctx
  | _ ->
    HExpr.Op (Op.App, callee, arg, appTy, loc), ctx

let inferOpAppPrintfn ctx ident arg calleeTy loc =
  match arg with
  | HExpr.Lit (Lit.Str format, _) ->
    let funTy = analyzeFormat format
    let ctx = unifyTy ctx loc calleeTy funTy
    HExpr.Ref (ident, HValRef.Prim HPrim.Printfn, calleeTy, loc), ctx
  | _ ->
    let ctx = ctxAddErr ctx """First arg of printfn must be string literal, "..".""" loc
    hxAbort ctx calleeTy loc

let inferOpApp ctx callee arg loc appTy =
  let argTy, _, ctx = ctxFreshTyVar "arg" ctx
  let arg, ctx = inferExpr ctx arg argTy
  let callee, ctx = inferExpr ctx callee (tyFun argTy appTy)
  match callee with
  | HExpr.Op (Op.App, HExpr.Ref (_, HValRef.Prim (HPrim.NativeFun _), _, _), firstArg, _, _) ->
    inferOpAppNativeFun ctx callee firstArg arg appTy loc
  | HExpr.Ref (ident, HValRef.Prim HPrim.Printfn, calleeTy, loc) ->
    let callee, ctx = inferOpAppPrintfn ctx ident arg calleeTy loc
    HExpr.Op (Op.App, callee, arg, appTy, loc), ctx
  | _ ->
    HExpr.Op (Op.App, callee, arg, appTy, loc), ctx

let inferOpCore (ctx: TyCtx) op left right loc operandTy resultTy =
  let left, ctx = inferExpr ctx left operandTy
  let right, ctx = inferExpr ctx right operandTy
  HExpr.Op (op, left, right, resultTy, loc), ctx

let inferOpAdd (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = ctxFreshTyVar "operand" ctx
  let ctx = unifyTy ctx loc operandTy resultTy
  let expr, ctx = inferOpCore ctx op left right loc operandTy resultTy
  match substTy ctx operandTy with
  | Ty.Con ((TyCon.Int | TyCon.Str), _) ->
    expr, ctx
  | ty ->
    let ctx = ctxAddErr ctx (sprintf "Type: No support (+) for %A" ty) loc
    hxAbort ctx resultTy loc

let inferOpArith (ctx: TyCtx) op left right loc resultTy =
  let ctx = unifyTy ctx loc resultTy tyInt
  inferOpCore ctx op left right loc tyInt resultTy

let inferOpCmp (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = ctxFreshTyVar "operand" ctx
  let ctx = unifyTy ctx loc resultTy tyBool
  inferOpCore ctx op left right loc operandTy resultTy

let inferOpCons ctx left right loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  let left, ctx = inferExpr ctx left itemTy
  let right, ctx = inferExpr ctx right listTy
  HExpr.Op (Op.Cons itemTy, left, right, listTy, loc), ctx

let inferOpRange ctx op left right loc ty =
  let ctx = unifyTy ctx loc ty tyRange
  inferOpCore ctx op left right loc tyInt ty

let inferOp (ctx: TyCtx) op left right loc ty =
  match op with
  | Op.Add ->
    inferOpAdd ctx op left right loc ty
  | Op.Sub
  | Op.Mul
  | Op.Div
  | Op.Mod ->
    inferOpArith ctx op left right loc ty
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le
  | Op.Gt
  | Op.Ge ->
    inferOpCmp ctx op left right loc ty
  | Op.App ->
    inferOpApp ctx left right loc ty
  | Op.Cons _ ->
    inferOpCons ctx left right loc ty
  | Op.Range ->
    inferOpRange ctx op left right loc ty
  | Op.Index ->
    inferIndex ctx left right loc ty
  | Op.And
  | Op.Or
  | Op.Pipe
  | Op.ConsRev ->
    failwith "Never: Desugared operators"

let inferTuple (ctx: TyCtx) items loc tupleTy =
  let rec go acc itemTys ctx items =
    match items with
    | [] ->
      List.rev acc, List.rev itemTys, ctx
    | item :: items ->
      let itemTy, _, ctx = ctxFreshTyVar "item" ctx
      let item, ctx = inferExpr ctx item itemTy
      go (item :: acc) (itemTy :: itemTys) ctx items
  let items, itemTys, ctx = go [] [] ctx items
  let ctx = unifyTy ctx loc tupleTy (tyTuple itemTys)
  hxTuple items loc, ctx

let inferAnno ctx expr annoTy ty loc =
  let annoTy, ctx = ctxResolveTy ctx annoTy
  let ctx = unifyTy ctx loc annoTy ty
  inferExpr ctx expr annoTy

let inferLetVal ctx pat init next ty loc =
  let initTy, _, ctx = ctxFreshTyVar "init" ctx
  // Type init expression.
  let init, initCtx = inferExpr ctx init initTy
  // Remove symbols defined inside `init`.
  let ctx = ctxRollback ctx initCtx

  // Define new variables defined by the pat to the context.
  let pat, nextCtx = inferPat ctx pat initTy
  let next, nextCtx = inferExpr nextCtx next ty
  let ctx = ctxRollback ctx nextCtx

  HExpr.Let (pat, init, next, ty, loc), ctx

let inferLetFun ctx calleeName oldSerial argPats body next ty loc =
  let outerCtx = ctx

  let ctx = ctx |> ctxIncLetDepth
  let bodyTy, _, ctx = ctxFreshTyVar "body" ctx

  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx bodyTy argPats =
    match argPats with
    | [] ->
      [], bodyTy, ctx
    | argPat :: argPats ->
      let argTy, _, ctx = ctxFreshTyVar "arg" ctx
      let pat, ctx = inferPat ctx argPat argTy
      let pats, bodyTy, ctx = inferArgs ctx bodyTy argPats
      pat :: pats, tyFun argTy bodyTy, ctx

  let funTy, _, ctx =
    if calleeName = "main"
    then tyFun tyUnit tyInt, "", ctx // FIXME: argument type is string[]
    else ctxFreshTyVar "fun" ctx

  // Define function itself for recursive call.
  // FIXME: Functions are recursive by default.
  let serial, nextCtx =
    match ctx.Vars |> Map.tryFind oldSerial with
    | Some (VarDef.Fun (_, _, TyScheme.ForAll ([], oldTy), _)) ->
      // In the case the function is predefined.
      let ctx = unifyTy ctx loc oldTy funTy
      oldSerial, ctx
    | _ ->
      let funTyScheme = TyScheme.ForAll ([], funTy)
      let arity = List.length argPats
      ctxFreshFun ctx calleeName arity funTyScheme loc

  let bodyCtx = nextCtx
  let argPats, actualFunTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
  let bodyCtx = unifyTy bodyCtx loc funTy actualFunTy
  let body, bodyCtx = inferExpr bodyCtx body bodyTy
  let nextCtx = ctxRollback nextCtx bodyCtx
  let nextCtx = ctxGeneralizeFun nextCtx outerCtx bodyCtx serial

  let next, nextCtx = inferExpr nextCtx next ty
  let ctx = ctxRollback ctx nextCtx

  HExpr.LetFun (calleeName, serial, argPats, body, next, ty, loc), ctx

/// Returns in reversed order.
let inferExprs ctx exprs lastTy: HExpr list * TyCtx =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      acc, ctx
    | [expr] ->
      let expr, ctx = inferExpr ctx expr lastTy
      expr :: acc, ctx
    | expr :: exprs ->
      let expr, ctx = inferExpr ctx expr tyUnit
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let inferAndThen ctx loc exprs lastTy =
  let exprs, ctx = inferExprs ctx exprs lastTy
  hxAndThen (List.rev exprs) loc, ctx

let inferExprTyDecl ctx ident oldSerial tyDecl loc =
  if oldSerial <> noSerial then
    // In the case the definition already processed due to `module rec`.
    HExpr.TyDef (ident, oldSerial, tyDecl, loc), ctx
  else
    let serial, tyDecl, ctx = ctx |> ctxAddTy ident tyDecl loc
    let ctx = ctx |> ctxResolveUnifyQueue
    HExpr.TyDef (ident, serial, tyDecl, loc), ctx

let inferExprOpen ctx path ty loc =
  let ctx = unifyTy ctx loc ty tyUnit
  HExpr.Open (path, loc), ctx

let inferExpr (ctx: TyCtx) (expr: HExpr) ty: HExpr * TyCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    expr, unifyTy ctx loc (litTy lit) ty
  | HExpr.Ref (ident, _, _, loc) ->
    inferRef ctx ident loc ty
  | HExpr.Match (target, arms, _, loc) ->
    inferMatch ctx target arms loc ty
  | HExpr.Nav (receiver, field,  _,loc) ->
    inferNav ctx receiver field loc ty
  | HExpr.Op (op, l, r, _, loc) ->
    inferOp ctx op l r loc ty
  | HExpr.Inf (InfOp.List _, [], _, loc) ->
    inferNil ctx loc ty
  | HExpr.Inf (InfOp.Tuple, items, _, loc) ->
    inferTuple ctx items loc ty
  | HExpr.Inf (InfOp.Anno, [expr], annoTy, loc) ->
    inferAnno ctx expr annoTy ty loc
  | HExpr.Inf (InfOp.AndThen, exprs, _, loc) ->
    inferAndThen ctx loc exprs ty
  | HExpr.Let (pat, body, next, _, loc) ->
    inferLetVal ctx pat body next ty loc
  | HExpr.LetFun (calleeName, oldSerial, args, body, next, _, loc) ->
    inferLetFun ctx calleeName oldSerial args body next ty loc
  | HExpr.TyDef (ident, oldSerial, tyDef, loc) ->
    inferExprTyDecl ctx ident oldSerial tyDef loc
  | HExpr.Open (path, loc) ->
    inferExprOpen ctx path ty loc
  | HExpr.If _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Closure _, _, _, _)
  | HExpr.Inf (InfOp.CallProc, _, _, _)
  | HExpr.Inf (InfOp.CallClosure, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    let ctx = ctxAddErr ctx error loc
    hxAbort ctx ty loc

/// Replaces type vars embedded in exprs
/// with inference results.
let substTyExpr ctx expr =
  let subst ty = substTy ctx ty
  exprMap subst id expr

let infer (expr: HExpr): HExpr * TyCtx =
  let ctx =
    {
      VarSerial = 0
      Vars = Map.empty
      VarEnv = Map.empty
      TySerial = 0
      TyEnv = Map.empty
      Tys = Map.empty
      TyDepths = Map.empty
      Ns = []
      LetDepth = 0
      UnifyQueue = []
      Diags = []
    }

  let expr, ctx = collectTyDecls ctx expr
  let expr, ctx = collectVarDecls ctx expr

  let expr, ctx = inferExpr ctx expr tyUnit

  // Substitute all types.
  let expr = substTyExpr ctx expr

  let ctx =
    let vars =
      ctx.Vars |> Map.map (fun _ varDef ->
        match varDef with
        | VarDef.Var (ident, ty, loc) ->
          let ty = substTy ctx ty
          VarDef.Var (ident, ty, loc)
        | VarDef.Fun (ident, arity, TyScheme.ForAll (args, ty), loc) ->
          let ty = substTy ctx ty
          VarDef.Fun (ident, arity, TyScheme.ForAll (args, ty), loc)
        | VarDef.Variant (ident, tySerial, hasArg, argTy, ty, loc) ->
          let argTy = substTy ctx argTy
          let ty = substTy ctx ty
          VarDef.Variant (ident, tySerial, hasArg, argTy, ty, loc)
      )
    { ctx with Vars = vars }

  expr, ctx
