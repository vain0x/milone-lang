module rec MiloneLang.Typing

open MiloneLang
open MiloneLang.Helpers

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
    Diags: Diag list
  }

let variantFullName tyIdent variantIdent =
  sprintf "%s.%s" tyIdent variantIdent

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
  }

let ctxFreshTySerial (ctx: TyCtx) =
  let serial = ctx.TySerial + 1
  let ctx = { ctx with TySerial = ctx.TySerial + 1 }
  serial, ctx

let ctxFreshTyVar ident (ctx: TyCtx): Ty * string * TyCtx =
  let serial, ctx = ctxFreshTySerial ctx
  let ident = sprintf "'%s_%d" ident serial
  let ty = Ty.Var serial
  let ctx =
    { ctx with
        TyEnv = ctx.TyEnv |> Map.add ident serial
    }
  ty, ident, ctx

let ctxAddTy tyIdent tyDecl loc ctx =
  match tyDecl with
  | TyDecl.Union (_, variants, _) ->
    let tySerial, ctx = ctxFreshTySerial ctx
    let refTy = Ty.Ref tySerial

    // Register variants as variables.
    let variants, serials, ctx =
      let rec go variantAcc serialAcc variants ctx =
        match variants with
        | [] ->
          List.rev variantAcc, List.rev serialAcc, ctx
        | (lIdent, _, hasArg, lArgTy) :: variants ->
          let lTy = if hasArg then Ty.Fun (lArgTy, refTy) else refTy
          let varDef = VarDef.Variant (lIdent, tySerial, hasArg, lArgTy, lTy, loc)
          let lSerial, ctx = ctxFreshVarCore ctx lIdent varDef
          let ctx = ctxAddVarAlias ctx lSerial (variantFullName tyIdent lIdent)
          let variant = lIdent, lSerial, hasArg, lArgTy
          go (variant :: variantAcc) (lSerial :: serialAcc) variants ctx
      go [] [] variants ctx

    let tyDef = TyDef.Union (tyIdent, serials, loc)
    let ctx =
      { ctx with
          TyEnv = ctx.TyEnv |> Map.add tyIdent tySerial
          Tys = ctx.Tys |> Map.add tySerial tyDef
      }

    let tyDecl = TyDecl.Union (tyIdent, variants, loc)
    tySerial, tyDecl, ctx

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
  | Some (_, TyDef.Bv _)
  | None ->
    Ty.Error
  | Some (tySerial, _) ->
    Ty.Ref tySerial

/// Resolves type references in type annotation.
/// FIXME: Don't modify ctx for now.
let ctxResolveTy ctx ty =
  let rec go (ty, ctx) =
    match ty with
    | Ty.Error
    | Ty.Ref _
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj ->
      ty, ctx
    | Ty.RefIdent ident ->
      ctxResolveTyRefIdent ident ctx, ctx
    | Ty.Fun (sTy, tTy) ->
      let sTy, ctx = go (sTy, ctx)
      let tTy, ctx = go (tTy, ctx)
      Ty.Fun (sTy, tTy), ctx
    | Ty.Tuple itemTys ->
      let itemTys, ctx = (itemTys, ctx) |> stMap go
      Ty.Tuple itemTys, ctx
    | Ty.List ty ->
      let ty, ctx = go (ty, ctx)
      Ty.List ty, ctx
    | Ty.Var _ ->
      failwith "Never"
  go (ty, ctx)

/// Gets if the specified type var doesn't appear in the specified type.
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.RefIdent _
    | Ty.Ref _
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj
    | Ty.Tuple [] ->
      true
    | Ty.Fun (sTy, tTy) ->
      go sTy && go tTy
    | Ty.Tuple (itemTy :: itemTys) ->
      go itemTy && go (Ty.Tuple itemTys)
    | Ty.List ty ->
      go ty
    | Ty.Var s ->
      s <> tySerial
  go ty

/// Gets if the specified type is resolved to a morphic type.
let isMonomorphic ctx ty: bool =
  match substTy ctx ty with
  | Ty.Error
  | Ty.Ref _
  | Ty.Bool
  | Ty.Int
  | Ty.Char
  | Ty.Str
  | Ty.Range
  | Ty.Obj
  | Ty.Tuple [] ->
    true
  | Ty.Fun (sTy, tTy) ->
    isMonomorphic ctx sTy && isMonomorphic ctx tTy
  | Ty.List ty ->
    isMonomorphic ctx ty
  | Ty.Tuple (itemTy :: itemTys) ->
    isMonomorphic ctx itemTy && isMonomorphic ctx (Ty.Tuple itemTys)
  | Ty.Var tySerial ->
    (ctx: TyCtx).Tys |> Map.containsKey tySerial
  | Ty.RefIdent _ ->
    failwith "Never"

/// Adds type-var/type binding.
let bindTy (ctx: TyCtx) tySerial ty: TyCtx =
  // FIXME: track location info
  let noLoc = 0, 0
  // FIXME: track identifier
  let noIdent = "unknown"

  // Don't bind itself.
  match substTy ctx ty with
  | Ty.Var s when s = tySerial -> ctx
  | _ ->

  { ctx with
      Tys = ctx.Tys |> Map.add tySerial (TyDef.Bv (noIdent, ty, noLoc))
  }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let substTy (ctx: TyCtx) ty: Ty =
  let rec go ty =
    match ty with
    | Ty.Error
    | Ty.Bool
    | Ty.Int
    | Ty.Char
    | Ty.Str
    | Ty.Range
    | Ty.Obj
    | Ty.Ref _ ->
      ty
    | Ty.Fun (sty, tty) ->
      Ty.Fun (go sty, go tty)
    | Ty.Tuple itemTys ->
      Ty.Tuple (List.map go itemTys)
    | Ty.List ty ->
      Ty.List (go ty)
    | Ty.Var tySerial ->
      match ctx.Tys |> Map.tryFind tySerial with
      | Some (TyDef.Bv (_, ty, _)) ->
        go ty
      | _ ->
        ty
    | Ty.RefIdent ident ->
      failwithf "Unresolved type name %A" ident
  go ty

/// Resolves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let unifyTy (ctx: TyCtx) loc (lty: Ty) (rty: Ty): TyCtx =
  let lRootTy, rRootTy = lty, rty
  let rec go lty rty ctx =
    let lSubstTy = substTy ctx lty
    let rSubstTy = substTy ctx rty
    match lSubstTy, rSubstTy with
    | Ty.Var l, Ty.Var r when l = r ->
      ctx
    | Ty.Var lSerial, _ when tyIsFreeIn rSubstTy lSerial ->
      bindTy ctx lSerial rty
    | _, Ty.Var _ ->
      go rty lty ctx
    | Ty.Fun (lSTy, lTTy), Ty.Fun (rSTy, rTTy) ->
      ctx |> go lSTy rSTy |> go lTTy rTTy
    | Ty.List lTy, Ty.List rTy ->
      ctx |> go lTy rTy
    | Ty.Tuple (lTy :: lTys), Ty.Tuple (rTy :: rTys) ->
      ctx |> go lTy rTy |> go (Ty.Tuple lTys) (Ty.Tuple rTys)
    | Ty.Error, _
    | _, Ty.Error
    | Ty.Tuple [], Ty.Tuple []
    | Ty.Bool, Ty.Bool
    | Ty.Int, Ty.Int
    | Ty.Char, Ty.Char
    | Ty.Str, Ty.Str
    | Ty.Range, Ty.Range
    | Ty.Obj, Ty.Obj ->
      ctx
    | Ty.Ref l, Ty.Ref r when l = r ->
      ctx
    | Ty.Var _, _ ->
      let message = sprintf "Couldn't unify '%A' and '%A' due to self recursion." lSubstTy rSubstTy
      ctxAddErr ctx message loc
    | Ty.Bool, _
    | Ty.Int, _
    | Ty.Char, _
    | Ty.Str, _
    | Ty.Range, _
    | Ty.Obj, _
    | Ty.Fun _, _
    | Ty.Tuple _, _
    | Ty.List _, _
    | Ty.Ref _, _ ->
      let lRootTy = substTy ctx lRootTy
      let rRootTy = substTy ctx rRootTy
      let message = sprintf "While unifying '%A' and '%A', failed to unify '%A' and '%A'." lRootTy rRootTy lSubstTy rSubstTy
      ctxAddErr ctx message loc
    | Ty.RefIdent _, _ ->
      failwith "Never"
  go lty rty ctx

let ctxResolveVar (ctx: TyCtx) ident =
  match ctx.VarEnv |> Map.tryFind ident with
  | None -> None
  | Some serial ->
    match ctx.Vars |> Map.tryFind serial with
    | None -> None
    | Some varDef -> Some (serial, varDef)

/// Creates an expression to abort.
let hxAbort (ctx: TyCtx) ty loc =
  let funTy = Ty.Fun (Ty.Int, ty)
  let exitExpr = HExpr.Ref ("exit", SerialExit, 1, funTy, loc)
  let callExpr = HExpr.Op (Op.App, exitExpr, HExpr.Lit (Lit.Int 1, loc), ty, loc)
  callExpr, ctx

let inferPatRef (ctx: TyCtx) ident loc ty =
  let serial, ty, ctx =
    match ctxResolveVar ctx ident with
    | Some (serial, VarDef.Variant (_, _, _, _, variantTy, _)) ->
      let ctx = unifyTy ctx loc ty variantTy
      serial, ty, ctx
    | _ ->
      let serial, ctx = ctxFreshVar ctx ident ty loc
      serial, ty, ctx
  HPat.Ref (ident, serial, ty, loc), ctx

let inferPatCall (ctx: TyCtx) callee args loc ty =
  match callee, args with
  | HPat.Ref (ident, _, _, refLoc), [arg] ->
    match ctxResolveVar ctx ident with
    | Some (serial, VarDef.Variant (_, _, true, _, (Ty.Fun (argTy, callTy) as variantTy), _)) ->
      let arg, ctx = inferPat ctx arg argTy
      let callee = HPat.Ref (ident, serial, variantTy, refLoc)
      let ctx = unifyTy ctx loc ty callTy
      HPat.Call (callee, [arg], ty, loc), ctx
    | _ ->
      let ctx = ctxAddErr ctx "Expected a function variant." loc
      patUnit loc, ctx
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
  let ctx = unifyTy ctx loc tupleTy (Ty.Tuple itemTys)
  HPat.Tuple (itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (Ty.List itemTy)
  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  HPat.Cons (l, r, itemTy, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | HPat.Lit (lit, loc) ->
    pat, unifyTy ctx loc ty (litTy lit)
  | HPat.Nil (_, loc) ->
    let itemTy, _, ctx = ctxFreshTyVar "item" ctx
    let ctx = unifyTy ctx loc ty (Ty.List itemTy)
    HPat.Nil (itemTy, loc), ctx
  | HPat.Ref (ident, _, _, loc) ->
    inferPatRef ctx ident loc ty
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
  | Some (serial, varDef), _ ->
    let refTy, arity = varDefTyArity varDef
    let ctx = unifyTy ctx loc refTy ty
    HExpr.Ref (ident, serial, arity, ty, loc), ctx
  | None, "not" ->
    let ctx = unifyTy ctx loc (Ty.Fun (Ty.Bool, Ty.Bool)) ty
    HExpr.Ref (ident, SerialNot, 1, ty, loc), ctx
  | None, "exit" ->
    let resultTy, _, ctx = ctxFreshTyVar "exit" ctx
    let ctx = unifyTy ctx loc (Ty.Fun (Ty.Int, resultTy)) ty
    HExpr.Ref (ident, SerialExit, 1, ty, loc), ctx
  | None, "box" ->
    let argTy, _, ctx = ctxFreshTyVar "box" ctx
    let ctx = unifyTy ctx loc (Ty.Fun (argTy, Ty.Obj)) ty
    HExpr.Ref (ident, SerialBox, 1, ty, loc), ctx
  | None, "unbox" ->
    let resultTy, _, ctx = ctxFreshTyVar "unbox" ctx
    let ctx = unifyTy ctx loc (Ty.Fun (Ty.Obj, resultTy)) ty
    HExpr.Ref (ident, SerialUnbox, 1, ty, loc), ctx
  | None, "printfn" ->
    // The function's type is unified in app expression inference.
    HExpr.Ref (ident, SerialPrintfn, 9999, ty, loc), ctx
  | None, "char" ->
    // FIXME: `char` can take non-int values, including chars.
    let ctx = unifyTy ctx loc (Ty.Fun (Ty.Int, Ty.Char)) ty
    HExpr.Ref (ident, SerialCharFun, 1, ty, loc), ctx
  | None, "int" ->
    let argTy, _, ctx = ctxFreshTyVar "intArg" ctx
    let ctx = unifyTy ctx loc (Ty.Fun (argTy, Ty.Int)) ty
    let ctx =
      match substTy ctx argTy with
      | Ty.Var _ ->
        unifyTy ctx loc Ty.Int argTy
      | Ty.Int
      | Ty.Char
      | Ty.Str
      | Ty.Error _ ->
        ctx
      | argTy ->
        ctxAddErr ctx (sprintf "Expected int or char %A" argTy) loc
    HExpr.Ref (ident, SerialIntFun, 1, ty, loc), ctx
  | None, "string" ->
    let argTy, _, ctx = ctxFreshTyVar "stringArg" ctx
    let ctx = unifyTy ctx loc (Ty.Fun (argTy, Ty.Str)) ty
    let ctx =
      match substTy ctx argTy with
      | Ty.Int
      | Ty.Char
      | Ty.Str
      | Ty.Error _ ->
        ctx
      | _ ->
        ctxAddErr ctx (sprintf "FIXME: Not implemented `string` for %A" argTy) loc
    HExpr.Ref (ident, SerialStringFun, 1, ty, loc), ctx
  | None, _ ->
    let message = sprintf "Couldn't resolve var %s" ident
    let ctx = ctxAddErr ctx message loc
    hxAbort ctx ty loc

let inferNil ctx loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (Ty.List itemTy)
  hxNil itemTy loc, ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target arms loc resultTy =
  let targetTy, _, ctx = ctxFreshTyVar "target" ctx
  let target, ctx = inferExpr ctx target targetTy

  let arms, ctx =
    (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
      let baseCtx = ctx
      let pat, ctx = inferPat ctx pat targetTy
      let guard, ctx = inferExpr ctx guard Ty.Bool
      let body, ctx = inferExpr ctx body resultTy
      let ctx = ctxRollback baseCtx ctx
      (pat, guard, body), ctx
    )

  HExpr.Match (target, arms, resultTy, loc), ctx

let inferNav ctx sub mes loc resultTy =
  let asUnionTyName sub =
    match sub with
    | HExpr.Ref (ident, _, _, _, _) ->
      match ctx |> ctxFindTyDef ident with
      | Some (_, tyDef) ->
        Some (tyDefIdent tyDef)
      | None ->
        None
    | _ ->
      None
  match asUnionTyName sub with
  | Some tyName ->
    // FIXME: Terrible implementation for test passing.
    // We should find type or value from the namespace of the type to which the subject denote.s
    inferRef ctx (variantFullName tyName mes) loc resultTy
  | _ ->

  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let sub, ctx = inferExpr ctx sub subTy
  match substTy ctx subTy, mes with
  | Ty.Str, "Length" ->
    let ctx = unifyTy ctx loc resultTy Ty.Int
    let funExpr = HExpr.Ref (mes, SerialStrLength, 1, Ty.Fun (Ty.Str, Ty.Int), loc)
    HExpr.Op (Op.App, funExpr, sub, Ty.Int, loc), ctx
  | _ ->
    let ctx = ctxAddErr ctx (sprintf "Unknown nav %A.%s" sub mes) loc
    hxAbort ctx resultTy loc

/// `x.[i] : 'y` <== x : 'x, i : int or i : range
/// NOTE: Currently only the `x : string` case can compile, however,
/// we don't infer that for compatibility.
let inferIndex ctx l r loc resultTy =
  let subTy, _, ctx = ctxFreshTyVar "sub" ctx
  let indexTy, _, ctx = ctxFreshTyVar "index" ctx
  let l, ctx = inferExpr ctx l subTy
  let r, ctx = inferExpr ctx r indexTy
  match substTy ctx subTy, substTy ctx indexTy with
  | Ty.Str, Ty.Range ->
    let ctx = unifyTy ctx loc resultTy Ty.Str
    hxIndex l r resultTy loc, ctx
  | Ty.Str, _ ->
    let ctx = unifyTy ctx loc indexTy Ty.Int
    let ctx = unifyTy ctx loc resultTy Ty.Char
    hxIndex l r resultTy loc, ctx
  | _ ->
    let ctx = ctxAddErr ctx "Type: Index not supported" loc
    hxAbort ctx resultTy loc

let inferOpAppPrintfn ctx ident serial arg calleeTy loc =
  match arg with
  | HExpr.Lit (Lit.Str format, _) ->
    let funTy = analyzeFormat format
    let arity = arityTy funTy
    let ctx = unifyTy ctx loc calleeTy funTy
    HExpr.Ref (ident, serial, arity, calleeTy, loc), ctx
  | _ ->
    let ctx = ctxAddErr ctx """First arg of printfn must be string literal, "..".""" loc
    hxAbort ctx calleeTy loc

let inferOpApp ctx callee arg loc appTy =
  let argTy, _, ctx = ctxFreshTyVar "arg" ctx
  let arg, ctx = inferExpr ctx arg argTy
  let callee, ctx = inferExpr ctx callee (Ty.Fun (argTy, appTy))
  let callee, ctx =
    match callee with
    | HExpr.Ref (ident, serial, _, calleeTy, loc) when serial = SerialPrintfn ->
      inferOpAppPrintfn ctx ident serial arg calleeTy loc
    | _ ->
      callee, ctx
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
  | Ty.Int
  | Ty.Str ->
    expr, ctx
  | ty ->
    let ctx = ctxAddErr ctx (sprintf "Type: No support (+) for %A" ty) loc
    hxAbort ctx resultTy loc

let inferOpArith (ctx: TyCtx) op left right loc resultTy =
  let ctx = unifyTy ctx loc resultTy Ty.Int
  inferOpCore ctx op left right loc Ty.Int resultTy

let inferOpCmp (ctx: TyCtx) op left right loc resultTy =
  let operandTy, _, ctx = ctxFreshTyVar "operand" ctx
  let ctx = unifyTy ctx loc resultTy Ty.Bool
  inferOpCore ctx op left right loc operandTy resultTy

let inferOpCons ctx left right loc listTy =
  let itemTy, _, ctx = ctxFreshTyVar "item" ctx
  let ctx = unifyTy ctx loc listTy (Ty.List itemTy)
  let left, ctx = inferExpr ctx left itemTy
  let right, ctx = inferExpr ctx right listTy
  HExpr.Op (Op.Cons itemTy, left, right, listTy, loc), ctx

let inferOpRange ctx op left right loc ty =
  let ctx = unifyTy ctx loc ty Ty.Range
  inferOpCore ctx op left right loc Ty.Int ty

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
  | Op.Pipe ->
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
  let ctx = unifyTy ctx loc tupleTy (Ty.Tuple itemTys)
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

let inferLetFun ctx calleeName argPats body next ty loc =
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
      pat :: pats, Ty.Fun (argTy, bodyTy), ctx

  let arity = List.length argPats
  let funTy, _, ctx =
    if calleeName = "main"
    then Ty.Fun (tyUnit, Ty.Int), "", ctx // FIXME: argument type is string[]
    else ctxFreshTyVar "fun" ctx

  // Define function itself for recursive call.
  // FIXME: Functions are recursive by default.
  let serial, nextCtx = ctxFreshFun ctx calleeName arity funTy loc

  let bodyCtx = nextCtx
  let argPats, actualFunTy, bodyCtx = inferArgs bodyCtx bodyTy argPats
  let bodyCtx = unifyTy bodyCtx loc funTy actualFunTy
  let body, bodyCtx = inferExpr bodyCtx body bodyTy
  let nextCtx = ctxRollback nextCtx bodyCtx

  let nextCtx =
    if isMonomorphic bodyCtx funTy |> not then
      let funTy = substTy bodyCtx funTy
      let message = sprintf "Reject polymorphic functions are not supported for now due to lack of let-polymorphism %A %A" funTy argPats
      ctxAddErr nextCtx message loc
    else
      nextCtx

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

let inferExprTyDecl ctx ident tyDecl loc =
  let serial, tyDecl, ctx = ctx |> ctxAddTy ident tyDecl loc
  HExpr.TyDef (ident, serial, tyDecl, loc), ctx

let inferExpr (ctx: TyCtx) (expr: HExpr) ty: HExpr * TyCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    expr, unifyTy ctx loc (litTy lit) ty
  | HExpr.Ref (ident, _, _, _, loc) ->
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
  | HExpr.LetFun (calleeName, _, args, body, next, _, loc) ->
    inferLetFun ctx calleeName args body next ty loc
  | HExpr.TyDef (ident, _, tyDef, loc) ->
    inferExprTyDecl ctx ident tyDef loc
  | HExpr.If _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Fun _, _, _, _)
  | HExpr.Inf (InfOp.Exec, _, _, _)
  | HExpr.Inf (InfOp.Call, _, _, _)
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
      Diags = []
    }

  let ctx =
    let strLengthVarDef = VarDef.Fun ("String.length", 1, Ty.Fun (Ty.Str, Ty.Int), (0, 0))
    { ctx with
        VarEnv = ctx.VarEnv |> Map.add "String.length" SerialStrLength
        Vars = ctx.Vars |> Map.add SerialStrLength strLengthVarDef
        TyEnv = ctx.TyEnv |> Map.add "String" -1
        Tys = ctx.Tys |> Map.add -1 (TyDef.Union ("String", [], (0, 0)))
    }

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
        | VarDef.Fun (ident, arity, ty, loc) ->
          let ty = substTy ctx ty
          VarDef.Fun (ident, arity, ty, loc)
        | VarDef.Variant (ident, tySerial, hasArg, argTy, ty, loc) ->
          let argTy = substTy ctx argTy
          let ty = substTy ctx ty
          VarDef.Variant (ident, tySerial, hasArg, argTy, ty, loc)
      )
    { ctx with Vars = vars }

  expr, ctx
