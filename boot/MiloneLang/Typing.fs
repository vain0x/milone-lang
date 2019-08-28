module rec MiloneLang.Typing

open MiloneLang
open MiloneLang.Types
open MiloneLang.Helpers

type TyCtx =
  {
    /// Next serial number.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    Serial: int
    NameMap: Map<int, string>
    /// Variable serial to variable definition.
    Vars: Map<int, VarDef>
    /// Type serial to type definition.
    Tys: Map<int, TyDef>
    TyDepths: Map<int, int>
    LetDepth: int
    UnifyQueue: (Ty * Ty * Loc) list
    Diags: Diag list
  }

let ctxGetIdent serial (ctx: TyCtx) =
  ctx.NameMap |> Map.find serial

let ctxGetTy tySerial (ctx: TyCtx) =
  ctx.Tys |> Map.find tySerial

let ctxAddErr (ctx: TyCtx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

/// Merges derived context into base context
/// for when expr of derived context is done.
/// We rollback environments but keep serials.
let ctxRollback bCtx dCtx: TyCtx =
  assert (bCtx.Serial <= dCtx.Serial)
  { dCtx with
      LetDepth = bCtx.LetDepth
  }

let ctxToTyCtx (ctx: TyCtx): TyContext =
  {
    Serial = ctx.Serial
    Tys = ctx.Tys
    TyDepths = ctx.TyDepths
  }

let ctxWithTyCtx (ctx: TyCtx) (tyCtx: TyContext): TyCtx =
  { ctx with
      Serial = tyCtx.Serial
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths
  }

let ctxIncLetDepth (ctx: TyCtx) =
  { ctx with LetDepth = ctx.LetDepth + 1 }

let ctxDecLetDepth (ctx: TyCtx) =
  { ctx with LetDepth = ctx.LetDepth - 1 }

let ctxFreshTySerial (ctx: TyCtx) =
  let serial = ctx.Serial + 1
  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        TyDepths = ctx.TyDepths |> Map.add serial ctx.LetDepth
    }
  serial, ctx

let ctxFreshTyVar ident loc (ctx: TyCtx): Ty * unit * TyCtx =
  let serial, ctx = ctxFreshTySerial ctx
  let ty = Ty.Meta (serial, loc)
  ty, (), ctx

let ctxUnifyLater (ctx: TyCtx) unresolvedTy metaTy loc =
  { ctx with UnifyQueue = (unresolvedTy, metaTy, loc) :: ctx.UnifyQueue }

let ctxResolveUnifyQueue (ctx: TyCtx) =
  let rec go ctx queue =
    match queue with
    | [] ->
      ctx
    | (unresolvedTy, metaTy, loc) :: queue ->
      let resolvedTy, ctx = ctxResolveTy ctx unresolvedTy loc
      let ctx = unifyTy ctx loc resolvedTy metaTy
      go ctx queue
  let queue = ctx.UnifyQueue
  let ctx = { ctx with UnifyQueue = [] }
  go ctx queue

/// Resolves type references in type annotation.
let ctxResolveTy ctx ty loc =
  let rec go (ty, ctx) =
    match ty with

    | Ty.Con (TyCon.Ref serial, []) when ctx |> ctxGetIdent serial = "_" ->
      let tySerial, ctx = ctxFreshTySerial ctx
      Ty.Meta (tySerial, loc), ctx

    | Ty.Error _ ->
      ty, ctx

    | Ty.Con (TyCon.Ref tySerial, _) ->
      match ctx |> ctxGetTy tySerial with
      | TyDef.Meta (_, bodyTy, _) ->
        bodyTy, ctx

      | _ ->
        ty, ctx

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
    | Ty.Error _
    | Ty.Con (_, []) ->
      true
    | Ty.Con (tyCon, ty :: tys) ->
      go ty && go (Ty.Con (tyCon, tys))
    | Ty.Meta (s, _) ->
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
    | Ty.Error _ :: tys ->
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
  | Ty.Meta (s, _) when s = tySerial -> ctx
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
    | Ty.Error _
    | Ty.Con (_, []) ->
      ty
    | Ty.Con (tyCon, tys) ->
      Ty.Con (tyCon, List.map go tys)
    | Ty.Meta (tySerial, _) ->
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
    | Ty.Meta (l, _), Ty.Meta (r, _) when l = r ->
      msgAcc, ctx
    | Ty.Meta (lSerial, _), _ when tyIsFreeIn rSubstTy lSerial ->
      let ctx = bindTyCore ctx lSerial rty
      msgAcc, ctx
    | _, Ty.Meta _ ->
      go rty lty (msgAcc, ctx)
    | Ty.Con (lTyCon, []), Ty.Con (rTyCon, []) when lTyCon = rTyCon ->
      msgAcc, ctx
    | Ty.Con (lTyCon, lTy :: lTys), Ty.Con (rTyCon, rTy :: rTys) ->
      (msgAcc, ctx) |> go lTy rTy |> go (Ty.Con (lTyCon, lTys)) (Ty.Con (rTyCon, rTys))
    | Ty.Error _, _
    | _, Ty.Error _ ->
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
    | Ty.Error _ :: tys
    | Ty.Con (_, []) :: tys ->
      go fvAcc tys
    | Ty.Con (_, tys1) :: tys2 ->
      let acc = go fvAcc tys1
      let acc = go acc tys2
      acc
    | Ty.Meta (serial, _) :: tys ->
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

let tySchemeInstantiate ctx (tyScheme: TyScheme) loc =
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
          (fun ctx (src, target) -> bindTy ctx src (Ty.Meta (target, loc))) ctx
      substTy extendedCtx ty

    ty, ctx

let ctxFindVar (ctx: TyCtx) serial =
  ctx.Vars |> Map.find serial

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
  let callExpr = HExpr.Bin (Op.App, exitExpr, HExpr.Lit (Lit.Int 1, loc), ty, loc)
  callExpr, ctx

let ctxUnifyVarTy varSerial ty loc ctx =
  match ctxFindVar ctx varSerial with
  | VarDef.Fun (_, _, tyScheme, _) ->
    let refTy, ctx = tySchemeInstantiate ctx tyScheme loc
    unifyTy ctx loc refTy ty

  | varDef ->
    let refTy =
      match varDef with
      | VarDef.Var (_, ty, _) ->
        ty
      | VarDef.Variant (_, _, _, _, ty, _) ->
        ty
      | VarDef.Fun _ ->
        failwith "NEVER"
    unifyTy ctx loc refTy ty

let inferPatRef (ctx: TyCtx) ident varSerial loc ty =
  let ctx = ctx |> ctxUnifyVarTy varSerial ty loc
  HPat.Ref (ident, varSerial, ty, loc), ctx

let inferPatNav (ctx: TyCtx) l r loc ty =
  failwithf "invalid use of nav pattern %A" (l, r, loc, ty)

let inferPatCall (ctx: TyCtx) callee args loc ty =
  match args with
  | [payload] ->
    // FIXME: We should verify that callee is a variant pattern.
    let _, payloadLoc = payload |> patExtract
    let payloadTy, _, ctx = ctx |> ctxFreshTyVar "arg" payloadLoc
    let funTy = tyFun payloadTy ty
    let callee, ctx = inferPat ctx callee funTy
    let payload, ctx = inferPat ctx payload payloadTy
    HPat.Call (callee, [payload], ty, loc), ctx

  | _ ->
    failwith "invalid use of call pattern"

let inferPatTuple ctx itemPats loc tupleTy =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] ->
      List.rev accPats, List.rev accTys, ctx
    | itemPat :: itemPats ->
      let _, itemLoc = itemPat |> patExtract
      let itemTy, _, ctx = ctxFreshTyVar "item" itemLoc ctx
      let itemPat, ctx = inferPat ctx itemPat itemTy
      go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats
  let itemPats, itemTys, ctx = go [] [] ctx itemPats
  let ctx = unifyTy ctx loc tupleTy (tyTuple itemTys)
  HPat.Tuple (itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" loc ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  HPat.Cons (l, r, itemTy, loc), ctx

let inferPatAs ctx pat ident varSerial loc ty =
  let ctx = ctx |> ctxUnifyVarTy varSerial ty loc
  let pat, ctx = inferPat ctx pat ty
  HPat.As (pat, ident, varSerial, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | HPat.Lit (lit, loc) ->
    pat, unifyTy ctx loc ty (litTy lit)
  | HPat.Nil (_, loc) ->
    let itemTy, _, ctx = ctxFreshTyVar "item" loc ctx
    let ctx = unifyTy ctx loc ty (tyList itemTy)
    HPat.Nil (itemTy, loc), ctx
  | HPat.Ref (ident, varSerial, _, loc) ->
    inferPatRef ctx ident varSerial loc ty
  | HPat.Nav (l, r, _, loc) ->
    inferPatNav ctx l r loc ty
  | HPat.Call (callee, args, _, loc) ->
    inferPatCall ctx callee args loc ty
  | HPat.Cons (l, r, _, loc) ->
    inferPatCons ctx l r loc ty
  | HPat.Tuple (items, _, loc) ->
    inferPatTuple ctx items loc ty
  | HPat.As (pat, ident, serial, loc) ->
    inferPatAs ctx pat ident serial loc ty
  | HPat.Anno (pat, annoTy, loc) ->
    let annoTy, ctx = ctxResolveTy ctx annoTy loc
    let ctx = unifyTy ctx loc ty annoTy
    let pat, ctx = inferPat ctx pat annoTy
    pat, ctx
  | HPat.Or (first, second, _, loc) ->
    // FIXME: Error if two patterns introduce different bindings.
    let first, ctx = inferPat ctx first ty
    let second, ctx = inferPat ctx second ty
    HPat.Or (first, second, ty, loc), ctx

let inferRef (ctx: TyCtx) ident serial loc ty =
  let ctx = ctx |> ctxUnifyVarTy serial ty loc
  HExpr.Ref (ident, HValRef.Var serial, ty, loc), ctx

let inferPrim ctx ident prim loc ty =
  match prim with
  | HPrim.Not ->
    let ctx = unifyTy ctx loc (tyFun tyBool tyBool) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Not, ty, loc), ctx

  | HPrim.Exit ->
    let resultTy, _, ctx = ctxFreshTyVar "exit" loc ctx
    let ctx = unifyTy ctx loc (tyFun tyInt resultTy) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Exit, ty, loc), ctx

  | HPrim.Assert ->
    let ctx = unifyTy ctx loc (tyFun tyBool tyUnit) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Assert, ty, loc), ctx

  | HPrim.Box ->
    let argTy, _, ctx = ctxFreshTyVar "box" loc ctx
    let ctx = unifyTy ctx loc (tyFun argTy tyObj) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Box, ty, loc), ctx

  | HPrim.Unbox ->
    let resultTy, _, ctx = ctxFreshTyVar "unbox" loc ctx
    let ctx = unifyTy ctx loc (tyFun tyObj resultTy) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Unbox, ty, loc), ctx

  | HPrim.Printfn ->
    // The function's type is unified in app expression inference.
    HExpr.Ref (ident, HValRef.Prim HPrim.Printfn, ty, loc), ctx

  | HPrim.Char ->
    // FIXME: `char` can take non-int values, including chars.
    let ctx = unifyTy ctx loc (tyFun tyInt tyChar) ty
    HExpr.Ref (ident, HValRef.Prim HPrim.Char, ty, loc), ctx

  | HPrim.Int ->
    let argTy, _, ctx = ctxFreshTyVar "intArg" loc ctx
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

  | HPrim.String ->
    let argTy, _, ctx = ctxFreshTyVar "stringArg" loc ctx
    let ctx = unifyTy ctx loc (tyFun argTy tyStr) ty
    let ctx =
      match substTy ctx argTy with
      | Ty.Con ((TyCon.Int | TyCon.Char | TyCon.Str), _)
      | Ty.Error _ ->
        ctx
      | _ ->
        ctxAddErr ctx (sprintf "FIXME: Not implemented `string` for %A" argTy) loc
    HExpr.Ref (ident, HValRef.Prim HPrim.String, ty, loc), ctx

  | HPrim.StrLength ->
    let ctx = unifyTy ctx loc ty (tyFun tyStr tyInt)
    HExpr.Ref (ident, HValRef.Prim prim, ty, loc), ctx

  | HPrim.StrSlice ->
    let ctx = unifyTy ctx loc ty (tyFun tyStr (tyFun tyInt (tyFun tyInt tyStr)))
    HExpr.Ref (ident, HValRef.Prim prim, ty, loc), ctx

  | HPrim.NativeFun _ ->
    HExpr.Ref (ident, HValRef.Prim (HPrim.NativeFun ("<NativeFunIdent>", -1)), ty, loc), ctx

let inferNil ctx loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" loc ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  hxNil itemTy loc, ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target arms loc resultTy =
  let targetTy, _, ctx = ctxFreshTyVar "target" loc ctx
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
  let findTyDynamicMember ctx sub subTy =
    match subTy, mes with
    | Ty.Con (TyCon.Str, []), "Length" ->
      let ctx = unifyTy ctx loc resultTy tyInt
      let funExpr = HExpr.Ref (mes, HValRef.Prim HPrim.StrLength, tyFun tyStr tyInt, loc)
      Some (HExpr.Bin (Op.App, funExpr, sub, tyInt, loc), ctx)
    | _ -> None

  let hxError () =
    let ctx = ctxAddErr ctx (sprintf "Unknown nav %A.%s" sub mes) loc
    hxAbort ctx resultTy loc

  let _, subLoc = sub |> exprExtract
  let subTy, _, ctx = ctxFreshTyVar "sub" loc ctx
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
  let _, subLoc = l |> exprExtract
  let subTy, _, ctx = ctxFreshTyVar "sub" subLoc ctx
  let indexTy, _, ctx = ctxFreshTyVar "index" loc ctx
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
        let argTy, _, ctx = ctxFreshTyVar "arg" loc ctx
        go (tyFun argTy ty) (arity - 1) ctx
    let resultTy, _, ctx = ctxFreshTyVar "result" loc ctx
    let funTy, ctx = go resultTy arity ctx
    let ctx = unifyTy ctx loc funTy appTy
    HExpr.Ref (nativeFunIdent, HValRef.Prim (HPrim.NativeFun (nativeFunIdent, arity)), appTy, loc), ctx
  | _ ->
    HExpr.Bin (Op.App, callee, arg, appTy, loc), ctx

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
  let _, argLoc = arg |> exprExtract
  let argTy, _, ctx = ctxFreshTyVar "arg" argLoc ctx
  let arg, ctx = inferExpr ctx arg argTy
  let callee, ctx = inferExpr ctx callee (tyFun argTy appTy)
  match callee with
  | HExpr.Bin (Op.App, HExpr.Ref (_, HValRef.Prim (HPrim.NativeFun _), _, _), firstArg, _, _) ->
    inferOpAppNativeFun ctx callee firstArg arg appTy loc
  | HExpr.Ref (ident, HValRef.Prim HPrim.Printfn, calleeTy, loc) ->
    let callee, ctx = inferOpAppPrintfn ctx ident arg calleeTy loc
    HExpr.Bin (Op.App, callee, arg, appTy, loc), ctx
  | _ ->
    HExpr.Bin (Op.App, callee, arg, appTy, loc), ctx

let inferOpCore (ctx: TyCtx) op left right loc operandTy resultTy =
  let left, ctx = inferExpr ctx left operandTy
  let right, ctx = inferExpr ctx right operandTy
  HExpr.Bin (op, left, right, resultTy, loc), ctx

let inferOpAdd (ctx: TyCtx) op left right loc resultTy =
  let _, operandLoc = left |> exprExtract
  let operandTy, _, ctx = ctxFreshTyVar "operand" operandLoc ctx
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
  let _, operandLoc = left |> exprExtract
  let operandTy, _, ctx = ctxFreshTyVar "operand" operandLoc ctx
  let ctx = unifyTy ctx loc resultTy tyBool
  inferOpCore ctx op left right loc operandTy resultTy

let inferOpCons ctx left right loc listTy =
  let _, itemLoc = left |> exprExtract
  let itemTy, _, ctx = ctxFreshTyVar "item" itemLoc ctx
  let ctx = unifyTy ctx loc listTy (tyList itemTy)
  let left, ctx = inferExpr ctx left itemTy
  let right, ctx = inferExpr ctx right listTy
  HExpr.Bin (Op.Cons, left, right, listTy, loc), ctx

let inferOpRange ctx op left right loc ty =
  let ctx = unifyTy ctx loc ty tyRange
  inferOpCore ctx op left right loc tyInt ty

let inferBin (ctx: TyCtx) op left right loc ty =
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
  | Op.Pipe ->
    failwith "Never: Desugared operators"

let inferTuple (ctx: TyCtx) items loc tupleTy =
  let rec go acc itemTys ctx items =
    match items with
    | [] ->
      List.rev acc, List.rev itemTys, ctx
    | item :: items ->
      let _, itemLoc = item |> exprExtract
      let itemTy, _, ctx = ctxFreshTyVar "item" itemLoc ctx
      let item, ctx = inferExpr ctx item itemTy
      go (item :: acc) (itemTy :: itemTys) ctx items
  let items, itemTys, ctx = go [] [] ctx items
  let ctx = unifyTy ctx loc tupleTy (tyTuple itemTys)
  hxTuple items loc, ctx

let inferAnno ctx expr annoTy ty loc =
  let annoTy, ctx = ctxResolveTy ctx annoTy loc
  let ctx = unifyTy ctx loc annoTy ty
  inferExpr ctx expr annoTy

let inferLetVal ctx pat init next ty loc =
  let _, initLoc = init |> exprExtract
  let initTy, _, ctx = ctxFreshTyVar "init" initLoc ctx
  // Type init expression.
  let init, initCtx = inferExpr ctx init initTy
  // Remove symbols defined inside `init`.
  let ctx = ctxRollback ctx initCtx

  // Define new variables defined by the pat to the context.
  let pat, nextCtx = inferPat ctx pat initTy
  let next, nextCtx = inferExpr nextCtx next ty
  let ctx = ctxRollback ctx nextCtx

  HExpr.Let (pat, init, next, ty, loc), ctx

let inferLetFun ctx calleeName varSerial argPats body next ty loc =
  let outerCtx = ctx

  let ctx = ctx |> ctxIncLetDepth
  let bodyTy, _, ctx =
    let _, bodyLoc = body |> exprExtract
    ctxFreshTyVar "body" bodyLoc ctx

  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx bodyTy argPats =
    match argPats with
    | [] ->
      [], bodyTy, ctx
    | argPat :: argPats ->
      let _, argLoc = argPat |> patExtract
      let argTy, _, ctx = ctxFreshTyVar "arg" argLoc ctx
      let pat, ctx = inferPat ctx argPat argTy
      let pats, bodyTy, ctx = inferArgs ctx bodyTy argPats
      pat :: pats, tyFun argTy bodyTy, ctx

  let funTy, _, ctx =
    if calleeName = "main"
    then tyFun tyUnit tyInt, (), ctx // FIXME: argument type is string[]
    else ctxFreshTyVar "fun" loc ctx

  // Define function itself for recursive call.
  // FIXME: Functions are recursive by default.
  let serial, nextCtx =
    match ctx.Vars |> Map.find varSerial with
    | VarDef.Fun (_, _, TyScheme.ForAll ([], oldTy), _) ->
      // In the case the function is predefined.
      let ctx = unifyTy ctx loc oldTy funTy
      varSerial, ctx
    | _ ->
      failwith "NEVER: It must be a pre-generalized function"

  let bodyCtx = nextCtx
  let argPats, actualFunTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
  let bodyCtx = unifyTy bodyCtx loc funTy actualFunTy
  let body, bodyCtx = inferExpr bodyCtx body bodyTy
  let nextCtx = ctxRollback nextCtx bodyCtx |> ctxDecLetDepth
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

let inferSemi ctx loc exprs lastTy =
  let exprs, ctx = inferExprs ctx exprs lastTy
  hxSemi (List.rev exprs) loc, ctx

let inferExprTyDecl ctx ident tySerial tyDecl loc =
  HExpr.TyDef (ident, tySerial, tyDecl, loc), ctx

let inferExprOpen ctx path ty loc =
  let ctx = unifyTy ctx loc ty tyUnit
  HExpr.Open (path, loc), ctx

let inferExpr (ctx: TyCtx) (expr: HExpr) ty: HExpr * TyCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    expr, unifyTy ctx loc (litTy lit) ty
  | HExpr.Ref (ident, HValRef.Var serial, _, loc) ->
    inferRef ctx ident serial loc ty
  | HExpr.Ref (ident, HValRef.Prim prim, _, loc) ->
    inferPrim ctx ident prim loc ty
  | HExpr.Match (target, arms, _, loc) ->
    inferMatch ctx target arms loc ty
  | HExpr.Nav (receiver, field,  _,loc) ->
    inferNav ctx receiver field loc ty
  | HExpr.Bin (op, l, r, _, loc) ->
    inferBin ctx op l r loc ty
  | HExpr.Inf (InfOp.List _, [], _, loc) ->
    inferNil ctx loc ty
  | HExpr.Inf (InfOp.Tuple, items, _, loc) ->
    inferTuple ctx items loc ty
  | HExpr.Inf (InfOp.Anno, [expr], annoTy, loc) ->
    inferAnno ctx expr annoTy ty loc
  | HExpr.Inf (InfOp.Semi, exprs, _, loc) ->
    inferSemi ctx loc exprs ty
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

let infer (expr: HExpr, scopeCtx: NameRes.ScopeCtx): HExpr * TyCtx =
  let ctx =
    {
      Serial = scopeCtx.Serial
      NameMap = scopeCtx.NameMap
      Vars = scopeCtx.Vars
      Tys = scopeCtx.Tys
      TyDepths = scopeCtx.TyDepths
      LetDepth = 0
      UnifyQueue = []
      Diags = []
    }

  let ctx =
    let tys, ctx =
      (Map.toList ctx.Tys, ctx)
      |> stMap (fun ((tySerial, tyDef), ctx) ->
        match tyDef with
        | TyDef.Meta (ident, bodyTy, loc) ->
          // Replace types with type vars and unify later.
          let ty, _, ctx = ctxFreshTyVar ident loc ctx
          let ctx = ctxUnifyLater ctx bodyTy ty loc
          (tySerial, TyDef.Meta (ident, ty, loc)), ctx

        | TyDef.Union _ ->
          (tySerial, tyDef), ctx
      )
    { ctx with Tys = Map.ofList tys }

  // Assign type vars to var/fun definitions.
  let ctx =
    let vars, ctx =
      (Map.toList ctx.Vars, ctx)
      |> stMap (fun ((varSerial, varDef), ctx) ->
        let ctx = { ctx with LetDepth = scopeCtx.VarDepths |> Map.find varSerial }
        match varDef with
        | VarDef.Var (ident, _, loc) ->
          let ty, _, ctx = ctxFreshTyVar ident loc ctx
          let varDef = VarDef.Var (ident, ty, loc)
          (varSerial, varDef), ctx

        | VarDef.Fun (ident, arity, _, loc) ->
          let ty, _, ctx = ctxFreshTyVar ident loc ctx
          let tyScheme = TyScheme.ForAll ([], ty)
          let varDef = VarDef.Fun (ident, arity, tyScheme, loc)
          (varSerial, varDef), ctx

        | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, _, loc) ->
          let ty, _, ctx = ctxFreshTyVar ident loc ctx
          let ctx = ctxUnifyLater ctx payloadTy ty loc

          // Pre-compute the type of variant.
          let unionTy = tyRef tySerial []
          let variantTy = if hasPayload then tyFun ty unionTy else unionTy

          let varDef = VarDef.Variant (ident, tySerial, hasPayload, ty, variantTy, loc)
          (varSerial, varDef), ctx
      )
    { ctx with Vars = Map.ofList vars }

  let ctx = ctx |> ctxResolveUnifyQueue
  let ctx = { ctx with LetDepth = 0 }

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
        | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, ty, loc) ->
          let payloadTy = substTy ctx payloadTy
          let ty = substTy ctx ty
          VarDef.Variant (ident, tySerial, hasPayload, payloadTy, ty, loc)
      )
    { ctx with Vars = vars }

  expr, ctx
