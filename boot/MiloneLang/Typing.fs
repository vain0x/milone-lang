/// Infers the type of expressions.
///
/// The algorithm is based on rank-based Hindley-Milner type inference.
/// This article is very helpful (written in Japanese):
///     <https://rhysd.hatenablog.com/entry/2017/12/16/002048>
module rec MiloneLang.Typing

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

let tyCtxGetTy tySerial (ctx: TyCtx) = ctx |> tyCtxGetTys |> mapFind tySerial

let tyCtxAddErr (ctx: TyCtx) message loc =
  ctx
  |> tyCtxWithLogs ((Log.Error message, loc) :: (ctx |> tyCtxGetLogs))

let tyCtxToTyCtx (ctx: TyCtx): TyContext =
  TyContext(ctx |> tyCtxGetSerial, ctx |> tyCtxGetTys, ctx |> tyCtxGetTyDepths)

let tyCtxWithTyCtx (ctx: TyCtx) logAcc (tyCtx: TyContext): TyCtx =
  ctx
  |> tyCtxWithSerial (tyCtx |> tyContextGetSerial)
  |> tyCtxWithTys (tyCtx |> tyContextGetTys)
  |> tyCtxWithTyDepths (tyCtx |> tyContextGetTyDepths)
  |> tyCtxWithLogs logAcc

/// Be carefully. Let depths must be counted the same as name resolution.
let tyCtxIncLetDepth (ctx: TyCtx) =
  ctx
  |> tyCtxWithLetDepth ((ctx |> tyCtxGetLetDepth) + 1)

let tyCtxDecLetDepth (ctx: TyCtx) =
  ctx
  |> tyCtxWithLetDepth ((ctx |> tyCtxGetLetDepth) - 1)

let tyCtxFreshTySerial (ctx: TyCtx) =
  let serial = (ctx |> tyCtxGetSerial) + 1

  let ctx =
    ctx
    |> tyCtxWithSerial ((ctx |> tyCtxGetSerial) + 1)
    |> tyCtxWithTyDepths
         (ctx
          |> tyCtxGetTyDepths
          |> mapAdd serial (ctx |> tyCtxGetLetDepth))

  serial, ctx

let tyCtxFreshTyVar ident loc (ctx: TyCtx): Ty * unit * TyCtx =
  let serial, ctx = tyCtxFreshTySerial ctx
  let ty = Ty.Meta(serial, loc)
  ty, (), ctx

let tyCtxAddTraitBounds traits (ctx: TyCtx) =
  ctx
  |> tyCtxWithTraitBounds (listAppend traits (ctx |> tyCtxGetTraitBounds))

let tyCtxResolveTraitBounds (ctx: TyCtx) =
  let rec go logAcc traits ctx =
    match traits with
    | [] -> logAcc, ctx

    | (theTrait, loc) :: traits ->
        let logAcc, ctx =
          typingResolveTraitBound logAcc ctx theTrait loc

        ctx |> go logAcc traits

  let traits = ctx |> tyCtxGetTraitBounds |> listRev
  let ctx = ctx |> tyCtxWithTraitBounds []

  let logAcc, tyCtx =
    ctx
    |> tyCtxToTyCtx
    |> go (ctx |> tyCtxGetLogs) traits

  tyCtxWithTyCtx ctx logAcc tyCtx

let tyCtxBindTy (ctx: TyCtx) tySerial ty loc =
  typingBind (tyCtxToTyCtx ctx) tySerial ty loc
  |> tyCtxWithTyCtx ctx (ctx |> tyCtxGetLogs)

let tyCtxSubstTy (ctx: TyCtx) ty: Ty = typingSubst (tyCtxToTyCtx ctx) ty

let tyCtxUnifyTy (ctx: TyCtx) loc (lty: Ty) (rty: Ty): TyCtx =
  let logAcc, tyCtx =
    typingUnify (ctx |> tyCtxGetLogs) (tyCtxToTyCtx ctx) lty rty loc

  tyCtxWithTyCtx ctx logAcc tyCtx

/// Assume all bound type variables are resolved by `substTy`.
///
/// `isOwned` checks if the type variable is introduced by the most recent `let`.
/// For example, `let f x = (let g = f in g x)` will have too generic type
/// without this checking (according to TaPL).
let tyGeneralize isOwned (ty: Ty) =
  let fvs =
    tyCollectFreeVars ty |> listFilter isOwned

  TyScheme.ForAll(fvs, ty)

let tyCtxInstantiate ctx (tyScheme: TyScheme) loc =
  match tyScheme with
  | TyScheme.ForAll ([], ty) -> ty, ctx
  | TyScheme.ForAll (fvs, ty) ->
      // Generate fresh type variable for each bound type variable.
      let mapping, ctx =
        (fvs, ctx)
        |> stMap (fun (fv, ctx) ->
             let newSerial, ctx = tyCtxFreshTySerial ctx
             (fv, newSerial), ctx)

      // Replace bound variables in the type with fresh ones.
      let ty =
        let extendedCtx =
          mapping
          |> listFold (fun ctx (src, target) -> tyCtxBindTy ctx src (Ty.Meta(target, loc)) loc) ctx

        tyCtxSubstTy extendedCtx ty

      ty, ctx

let tySpecInstantiate loc (TySpec (polyTy, traits), ctx) =
  // Refresh meta types and generate bindings.
  let oldTySerials = polyTy |> tyCollectFreeVars

  let bindings, ctx =
    (oldTySerials, ctx)
    |> stMap (fun (oldTySerial, ctx) ->
         let tySerial, ctx = ctx |> tyCtxFreshTySerial
         (oldTySerial, Ty.Meta(tySerial, loc)), ctx)

  // Replace meta types in the type and trait bounds.
  let substMeta tySerial = bindings |> assocTryFind intCmp tySerial
  let polyTy = polyTy |> tySubst substMeta

  let traits =
    traits
    |> listMap (fun theTrait -> theTrait |> traitMapTys (tySubst substMeta), loc)

  polyTy, traits, ctx

let tyCtxFindVar (ctx: TyCtx) serial = ctx |> tyCtxGetVars |> mapFind serial

let tyCtxGeneralizeFun (ctx: TyCtx) (outerLetDepth: LetDepth) funSerial =
  match ctx |> tyCtxGetVars |> mapFind funSerial with
  | VarDef.Fun (ident, arity, TyScheme.ForAll ([], funTy), loc) ->
      let isOwned tySerial =
        let depth =
          ctx |> tyCtxGetTyDepths |> mapFind tySerial

        depth > outerLetDepth

      let funTy = tyCtxSubstTy ctx funTy
      let funTyScheme = tyGeneralize isOwned funTy

      let varDef =
        VarDef.Fun(ident, arity, funTyScheme, loc)

      let ctx =
        ctx
        |> tyCtxWithVars (ctx |> tyCtxGetVars |> mapAdd funSerial varDef)

      ctx
  | VarDef.Fun _ -> failwith "Can't generalize already-generalized function"
  | _ -> failwith "Expected function"

/// Creates an expression to abort.
let hxAbort (ctx: TyCtx) ty loc =
  let funTy = tyFun tyInt ty
  let exitExpr = HExpr.Prim(HPrim.Exit, funTy, loc)

  let callExpr =
    hxApp exitExpr (HExpr.Lit(Lit.Int 1, loc)) ty loc

  callExpr, ctx

let tyCtxUnifyVarTy varSerial ty loc ctx =
  match tyCtxFindVar ctx varSerial with
  | VarDef.Fun (_, _, tyScheme, _) ->
      let refTy, ctx = tyCtxInstantiate ctx tyScheme loc
      tyCtxUnifyTy ctx loc refTy ty

  | varDef ->
      let refTy =
        match varDef with
        | VarDef.Var (_, _, ty, _) -> ty
        | VarDef.Variant (_, _, _, _, ty, _) -> ty
        | VarDef.Fun _ -> failwith "NEVER"

      tyCtxUnifyTy ctx loc refTy ty

let tyCtxFreshPatTy pat ctx =
  let _, loc = pat |> patExtract
  let tySerial, ctx = ctx |> tyCtxFreshTySerial
  let ty = Ty.Meta(tySerial, loc)
  ty, ctx

let tyCtxFreshExprTy expr ctx =
  let _, loc = expr |> exprExtract
  let tySerial, ctx = ctx |> tyCtxFreshTySerial
  let ty = Ty.Meta(tySerial, loc)
  ty, ctx

let inferPatRef (ctx: TyCtx) varSerial loc ty =
  let ctx = ctx |> tyCtxUnifyVarTy varSerial ty loc
  HPat.Ref(varSerial, ty, loc), ctx

let inferPatNav (ctx: TyCtx) l r loc ty =
  failwithf "invalid use of nav pattern %A" (l, r, loc, ty)

let inferPatCall (ctx: TyCtx) callee args loc ty =
  match args with
  | [ payload ] ->
      // FIXME: We should verify that callee is a variant pattern.
      let payloadTy, ctx = ctx |> tyCtxFreshPatTy payload
      let callee, ctx = inferPat ctx callee (tyFun payloadTy ty)
      let payload, ctx = inferPat ctx payload payloadTy
      HPat.Call(callee, [ payload ], ty, loc), ctx

  | _ -> failwith "invalid use of call pattern"

let inferPatTuple ctx itemPats loc tupleTy =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] -> listRev accPats, listRev accTys, ctx
    | itemPat :: itemPats ->
        let itemTy, ctx = ctx |> tyCtxFreshPatTy itemPat
        let itemPat, ctx = inferPat ctx itemPat itemTy
        go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats

  let itemPats, itemTys, ctx = go [] [] ctx itemPats

  let ctx =
    tyCtxUnifyTy ctx loc tupleTy (tyTuple itemTys)

  HPat.Tuple(itemPats, tupleTy, loc), ctx

let inferPatCons ctx l r loc listTy =
  let itemTy, ctx = ctx |> tyCtxFreshPatTy l

  let ctx =
    tyCtxUnifyTy ctx loc listTy (tyList itemTy)

  let l, ctx = inferPat ctx l itemTy
  let r, ctx = inferPat ctx r listTy
  HPat.Cons(l, r, itemTy, loc), ctx

let inferPatAs ctx pat varSerial loc ty =
  let ctx = ctx |> tyCtxUnifyVarTy varSerial ty loc
  let pat, ctx = inferPat ctx pat ty
  HPat.As(pat, varSerial, loc), ctx

let inferPat ctx pat ty =
  match pat with
  | HPat.Lit (lit, loc) -> pat, tyCtxUnifyTy ctx loc ty (litToTy lit)
  | HPat.Nil (_, loc) ->
      let itemTy, ctx = ctx |> tyCtxFreshPatTy pat
      let ctx = tyCtxUnifyTy ctx loc ty (tyList itemTy)
      HPat.Nil(itemTy, loc), ctx
  | HPat.OptionNone (_, loc) ->
      let itemTy, ctx = ctx |> tyCtxFreshPatTy pat
      let ctx = tyCtxUnifyTy ctx loc ty (tyList itemTy)
      HPat.OptionNone(itemTy, loc), ctx
  | HPat.OptionSome (_, loc) ->
      let itemTy, ctx = ctx |> tyCtxFreshPatTy pat

      let ctx =
        tyCtxUnifyTy ctx loc ty (tyFun itemTy (tyList itemTy))

      HPat.OptionSome(itemTy, loc), ctx
  | HPat.Discard (_, loc) -> HPat.Discard(ty, loc), ctx
  | HPat.Ref (varSerial, _, loc) -> inferPatRef ctx varSerial loc ty
  | HPat.Nav (l, r, _, loc) -> inferPatNav ctx l r loc ty
  | HPat.Call (callee, args, _, loc) -> inferPatCall ctx callee args loc ty
  | HPat.Cons (l, r, _, loc) -> inferPatCons ctx l r loc ty
  | HPat.Tuple (items, _, loc) -> inferPatTuple ctx items loc ty
  | HPat.As (pat, serial, loc) -> inferPatAs ctx pat serial loc ty
  | HPat.Anno (pat, annoTy, loc) ->
      let ctx = tyCtxUnifyTy ctx loc ty annoTy
      let pat, ctx = inferPat ctx pat annoTy
      pat, ctx
  | HPat.Or (first, second, _, loc) ->
      // FIXME: Error if two patterns introduce different bindings.
      let first, ctx = inferPat ctx first ty
      let second, ctx = inferPat ctx second ty
      HPat.Or(first, second, ty, loc), ctx

let inferRef (ctx: TyCtx) serial loc ty =
  let ctx = ctx |> tyCtxUnifyVarTy serial ty loc
  HExpr.Ref(serial, ty, loc), ctx

let inferPrim ctx prim loc ty =
  let tySpec = prim |> primToTySpec
  let primTy, traits, ctx = (tySpec, ctx) |> tySpecInstantiate loc

  let ctx =
    tyCtxUnifyTy ctx loc primTy ty
    |> tyCtxAddTraitBounds traits

  HExpr.Prim(prim, primTy, loc), ctx

let inferNil ctx loc listTy =
  let itemTy, _, ctx = tyCtxFreshTyVar "item" loc ctx

  let ctx =
    tyCtxUnifyTy ctx loc listTy (tyList itemTy)

  hxNil itemTy loc, ctx

/// match 'a with ( | 'a -> 'b )*
let inferMatch ctx target arms loc resultTy =
  let targetTy, ctx = ctx |> tyCtxFreshExprTy target
  let target, ctx = inferExpr ctx target targetTy

  let arms, ctx =
    (arms, ctx)
    |> stMap (fun ((pat, guard, body), ctx) ->
         let pat, ctx = inferPat ctx pat targetTy
         let guard, ctx = inferExpr ctx guard tyBool
         let body, ctx = inferExpr ctx body resultTy
         (pat, guard, body), ctx)

  HExpr.Match(target, arms, resultTy, loc), ctx

let inferNav ctx sub mes loc resultTy =
  let findTyDynamicMember ctx sub subTy =
    let subTy = tyCtxSubstTy ctx subTy
    match subTy, mes with
    | Ty.Con (TyCon.Str, []), "Length" ->
        let ctx = tyCtxUnifyTy ctx loc resultTy tyInt

        let funExpr =
          HExpr.Prim(HPrim.StrLength, tyFun tyStr tyInt, loc)

        Some(hxApp funExpr sub tyInt loc, ctx)
    | _ -> None

  let subTy, ctx = ctx |> tyCtxFreshExprTy sub
  let sub, ctx = inferExpr ctx sub subTy

  match findTyDynamicMember ctx sub subTy with
  | Some (expr, ctx) -> expr, ctx
  | None ->
      let ctx =
        tyCtxAddErr ctx (sprintf "Unknown nav %A.%s" sub mes) loc

      hxAbort ctx resultTy loc

let inferOpAppNativeFun ctx callee firstArg arg appTy loc =
  match firstArg, arg with
  | HExpr.Lit (Lit.Str nativeFunIdent, _), HExpr.Lit (Lit.Int arity, _) ->
      let rec go ty arity ctx =
        if arity = 0 then
          ty, ctx
        else
          let argTy, _, ctx = tyCtxFreshTyVar "arg" loc ctx
          go (tyFun argTy ty) (arity - 1) ctx

      let resultTy, _, ctx = tyCtxFreshTyVar "result" loc ctx
      let funTy, ctx = go resultTy arity ctx
      let ctx = tyCtxUnifyTy ctx loc funTy appTy
      HExpr.Prim(HPrim.NativeFun(nativeFunIdent, arity), appTy, loc), ctx
  | _ -> hxApp callee arg appTy loc, ctx

let inferOpAppPrintfn ctx arg calleeTy loc =
  match arg with
  | HExpr.Lit (Lit.Str format, _) ->
      let funTy = analyzeFormat format
      let ctx = tyCtxUnifyTy ctx loc calleeTy funTy
      HExpr.Prim(HPrim.Printfn, calleeTy, loc), ctx
  | _ ->
      let ctx =
        tyCtxAddErr ctx """First arg of printfn must be string literal, "..".""" loc

      hxAbort ctx calleeTy loc

let inferOpApp ctx callee arg loc appTy =
  let argTy, ctx = ctx |> tyCtxFreshExprTy arg
  let arg, ctx = inferExpr ctx arg argTy
  let callee, ctx = inferExpr ctx callee (tyFun argTy appTy)
  match callee with
  | HExpr.Inf (InfOp.App, [ HExpr.Prim (HPrim.NativeFun _, _, _); firstArg ], _, _) ->
      inferOpAppNativeFun ctx callee firstArg arg appTy loc
  | HExpr.Prim (HPrim.Printfn, calleeTy, loc) ->
      let callee, ctx = inferOpAppPrintfn ctx arg calleeTy loc
      hxApp callee arg appTy loc, ctx
  | _ -> hxApp callee arg appTy loc, ctx

let inferTuple (ctx: TyCtx) items loc tupleTy =
  let rec go acc itemTys ctx items =
    match items with
    | [] -> listRev acc, listRev itemTys, ctx
    | item :: items ->
        let itemTy, ctx = ctx |> tyCtxFreshExprTy item
        let item, ctx = inferExpr ctx item itemTy
        go (item :: acc) (itemTy :: itemTys) ctx items

  let items, itemTys, ctx = go [] [] ctx items

  let ctx =
    tyCtxUnifyTy ctx loc tupleTy (tyTuple itemTys)

  hxTuple items loc, ctx

let inferAnno ctx expr annoTy ty loc =
  let ctx = tyCtxUnifyTy ctx loc annoTy ty
  inferExpr ctx expr annoTy

let inferLetVal ctx pat init next ty loc =
  let initTy, ctx = ctx |> tyCtxFreshExprTy init
  let init, ctx = inferExpr ctx init initTy
  let pat, ctx = inferPat ctx pat initTy
  let next, ctx = inferExpr ctx next ty
  HExpr.Let(pat, init, next, ty, loc), ctx

let inferLetFun (ctx: TyCtx) varSerial isMainFun argPats body next ty loc =
  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx bodyTy argPats =
    match argPats with
    | [] -> [], bodyTy, ctx

    | argPat :: argPats ->
        let argTy, ctx = ctx |> tyCtxFreshPatTy argPat
        let pat, ctx = inferPat ctx argPat argTy
        let pats, bodyTy, ctx = inferArgs ctx bodyTy argPats
        pat :: pats, tyFun argTy bodyTy, ctx

  let outerLetDepth = ctx |> tyCtxGetLetDepth
  let ctx = ctx |> tyCtxIncLetDepth

  let calleeTy, ctx =
    let calleeTy, _, ctx =
      if isMainFun then
        tyFun tyUnit tyInt, (), ctx // FIXME: argument type is string[]
      else
        tyCtxFreshTyVar "fun" loc ctx

    let ctx =
      match ctx |> tyCtxGetVars |> mapFind varSerial with
      | VarDef.Fun (_, _, TyScheme.ForAll ([], oldTy), _) -> tyCtxUnifyTy ctx loc oldTy calleeTy
      | _ -> failwith "NEVER: It must be a pre-generalized function"

    calleeTy, ctx

  let bodyTy, ctx = ctx |> tyCtxFreshExprTy body
  let argPats, funTy, ctx = inferArgs ctx bodyTy argPats
  let ctx = tyCtxUnifyTy ctx loc calleeTy funTy

  let body, ctx = inferExpr ctx body bodyTy
  let ctx = ctx |> tyCtxDecLetDepth

  let ctx =
    tyCtxGeneralizeFun ctx outerLetDepth varSerial

  let next, ctx = inferExpr ctx next ty
  HExpr.LetFun(varSerial, isMainFun, argPats, body, next, ty, loc), ctx

/// Returns in reversed order.
let inferExprs ctx exprs lastTy: HExpr list * TyCtx =
  let rec go acc ctx exprs =
    match exprs with
    | [] -> acc, ctx
    | [ expr ] ->
        let expr, ctx = inferExpr ctx expr lastTy
        expr :: acc, ctx
    | expr :: exprs ->
        let expr, ctx = inferExpr ctx expr tyUnit
        go (expr :: acc) ctx exprs

  go [] ctx exprs

let inferSemi ctx loc exprs lastTy =
  let exprs, ctx = inferExprs ctx exprs lastTy
  hxSemi (listRev exprs) loc, ctx

let inferExprTyDecl ctx tySerial tyDecl loc = HExpr.TyDecl(tySerial, tyDecl, loc), ctx

let inferExprOpen ctx path ty loc =
  let ctx = tyCtxUnifyTy ctx loc ty tyUnit
  HExpr.Open(path, loc), ctx

let inferExpr (ctx: TyCtx) (expr: HExpr) ty: HExpr * TyCtx =
  match expr with
  | HExpr.Lit (lit, loc) -> expr, tyCtxUnifyTy ctx loc (litToTy lit) ty
  | HExpr.Ref (serial, _, loc) -> inferRef ctx serial loc ty
  | HExpr.Prim (prim, _, loc) -> inferPrim ctx prim loc ty
  | HExpr.Match (target, arms, _, loc) -> inferMatch ctx target arms loc ty
  | HExpr.Nav (receiver, field, _, loc) -> inferNav ctx receiver field loc ty
  | HExpr.Inf (InfOp.App, [ callee; arg ], _, loc) -> inferOpApp ctx callee arg loc ty
  | HExpr.Inf (InfOp.Tuple, items, _, loc) -> inferTuple ctx items loc ty
  | HExpr.Inf (InfOp.Anno, [ expr ], annoTy, loc) -> inferAnno ctx expr annoTy ty loc
  | HExpr.Inf (InfOp.Semi, exprs, _, loc) -> inferSemi ctx loc exprs ty
  | HExpr.Let (pat, body, next, _, loc) -> inferLetVal ctx pat body next ty loc
  | HExpr.LetFun (oldSerial, isMainFun, args, body, next, _, loc) ->
      inferLetFun ctx oldSerial isMainFun args body next ty loc
  | HExpr.TyDecl (oldSerial, tyDef, loc) -> inferExprTyDecl ctx oldSerial tyDef loc
  | HExpr.Open (path, loc) -> inferExprOpen ctx path ty loc
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.App, _, _, _)
  | HExpr.Inf (InfOp.Closure, _, _, _)
  | HExpr.Inf (InfOp.CallProc, _, _, _)
  | HExpr.Inf (InfOp.CallClosure, _, _, _) -> failwith "Never"
  | HExpr.Error (error, loc) ->
      let ctx = tyCtxAddErr ctx error loc
      hxAbort ctx ty loc

/// Replaces type vars embedded in exprs
/// with inference results.
let tyCtxSubstExprTy ctx expr =
  let subst ty = tyCtxSubstTy ctx ty
  exprMap subst id expr

let infer (expr: HExpr, scopeCtx: ScopeCtx, errorListList): HExpr * TyCtx =
  let ctx =
    TyCtx
      (scopeCtx |> scopeCtxGetSerial,
       scopeCtx |> scopeCtxGetVars,
       scopeCtx |> scopeCtxGetTys,
       scopeCtx |> scopeCtxGetTyDepths,
       0,
       [],
       [])

  let rec addErrorListList xss ctx =
    match xss with
    | [] -> ctx

    | [] :: xss -> ctx |> addErrorListList xss

    | ((msg, loc) :: errors) :: xss ->
        tyCtxAddErr ctx msg loc
        |> addErrorListList (errors :: xss)

  let ctx = ctx |> addErrorListList errorListList

  // Assign type vars to var/fun definitions.
  let ctx =
    let vars, ctx =
      (mapToList (ctx |> tyCtxGetVars), ctx)
      |> stMap (fun ((varSerial, varDef), ctx) ->
           let ctx =
             ctx
             |> tyCtxWithLetDepth
                  (scopeCtx
                   |> scopeCtxGetVarDepths
                   |> mapFind varSerial)

           match varDef with
           | VarDef.Var (ident, storageModifier, _, loc) ->
               let ty, _, ctx = tyCtxFreshTyVar ident loc ctx

               let varDef =
                 VarDef.Var(ident, storageModifier, ty, loc)

               (varSerial, varDef), ctx

           | VarDef.Fun (ident, arity, _, loc) ->
               let ty, _, ctx = tyCtxFreshTyVar ident loc ctx
               let tyScheme = TyScheme.ForAll([], ty)
               let varDef = VarDef.Fun(ident, arity, tyScheme, loc)
               (varSerial, varDef), ctx

           | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, _, loc) ->
               // Pre-compute the type of variant.
               let variantTy =
                 let unionTy = tyRef tySerial []
                 if hasPayload then tyFun payloadTy unionTy else unionTy

               let varDef =
                 VarDef.Variant(ident, tySerial, hasPayload, payloadTy, variantTy, loc)

               (varSerial, varDef), ctx)

    ctx
    |> tyCtxWithVars (mapOfList (intHash, intCmp) vars)

  let ctx = ctx |> tyCtxWithLetDepth 0

  let expr, ctx = inferExpr ctx expr tyUnit

  let ctx = ctx |> tyCtxResolveTraitBounds

  // Substitute all types.
  let expr = tyCtxSubstExprTy ctx expr

  let ctx =
    let vars =
      ctx
      |> tyCtxGetVars
      |> mapMap (fun _ varDef ->
           match varDef with
           | VarDef.Var (ident, storageModifier, ty, loc) ->
               let ty = tyCtxSubstTy ctx ty
               VarDef.Var(ident, storageModifier, ty, loc)
           | VarDef.Fun (ident, arity, TyScheme.ForAll (args, ty), loc) ->
               let ty = tyCtxSubstTy ctx ty
               VarDef.Fun(ident, arity, TyScheme.ForAll(args, ty), loc)
           | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, ty, loc) ->
               let payloadTy = tyCtxSubstTy ctx payloadTy
               let ty = tyCtxSubstTy ctx ty
               VarDef.Variant(ident, tySerial, hasPayload, payloadTy, ty, loc))

    ctx |> tyCtxWithVars vars

  let ctx =
    let tys =
      ctx
      |> tyCtxGetTys
      |> mapFilter (fun _ tyDef ->
           match tyDef with
           | TyDef.Meta _ -> false

           | _ -> true)

    ctx |> tyCtxWithTys tys

  expr, ctx
