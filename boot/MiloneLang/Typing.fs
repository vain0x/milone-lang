/// Infers the type of expressions.
///
/// The algorithm is based on Didier Rémy's rank-based Hindley-Milner type inference:
///   - [eq-theory-on-types.pdf](http://gallium.inria.fr/~remy/ftp/eq-theory-on-types.pdf)
///
/// This web article (written in English) is very helpful:
///   - [Efficient and Insightful Generalization](http://okmij.org/ftp/ML/generalization.html)
///
/// and this one (written in Japanese) too:
///   - [OCaml でも採用されているレベルベースの多相型型推論とは](https://rhysd.hatenablog.com/entry/2017/12/16/002048)

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
  let ty = MetaTy(serial, loc)
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

  TyScheme(fvs, ty)

let tyCtxInstantiate ctx (tyScheme: TyScheme) loc =
  match tyScheme with
  | TyScheme ([], ty) -> ty, ctx
  | TyScheme (fvs, ty) ->
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
          |> listFold (fun ctx (src, target) -> tyCtxBindTy ctx src (MetaTy(target, loc)) loc) ctx

        tyCtxSubstTy extendedCtx ty

      ty, ctx

let tySpecInstantiate loc (TySpec (polyTy, traits), ctx) =
  // Refresh meta types and generate bindings.
  let oldTySerials = polyTy |> tyCollectFreeVars

  let bindings, ctx =
    (oldTySerials, ctx)
    |> stMap (fun (oldTySerial, ctx) ->
         let tySerial, ctx = ctx |> tyCtxFreshTySerial
         (oldTySerial, MetaTy(tySerial, loc)), ctx)

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
  | FunDef (ident, arity, TyScheme ([], funTy), loc) ->
      let isOwned tySerial =
        let depth =
          ctx |> tyCtxGetTyDepths |> mapFind tySerial

        depth > outerLetDepth

      let funTy = tyCtxSubstTy ctx funTy
      let funTyScheme = tyGeneralize isOwned funTy

      let varDef = FunDef(ident, arity, funTyScheme, loc)

      let ctx =
        ctx
        |> tyCtxWithVars (ctx |> tyCtxGetVars |> mapAdd funSerial varDef)

      ctx
  | FunDef _ -> failwith "Can't generalize already-generalized function"
  | _ -> failwith "Expected function"

/// Creates an expression to abort.
let hxAbort (ctx: TyCtx) loc =
  let ty, (), ctx = ctx |> tyCtxFreshTyVar "abort" loc
  let funTy = tyFun tyInt ty
  let exitExpr = HPrimExpr(HPrim.Exit, funTy, loc)

  let callExpr =
    hxApp exitExpr (HLitExpr(IntLit 1, loc)) ty loc

  callExpr, ty, ctx

let tyCtxUnifyVarTy varSerial tyOpt loc ctx =
  let varTy, ctx =
    match tyCtxFindVar ctx varSerial with
    | VarDef (_, _, ty, _) -> ty, ctx
    | VariantDef (_, _, _, _, ty, _) -> ty, ctx
    | FunDef (_, _, tyScheme, _) -> tyCtxInstantiate ctx tyScheme loc

  match tyOpt with
  | Some ty ->
      let ctx = tyCtxUnifyTy ctx loc varTy ty
      varTy, ctx

  | None -> varTy, ctx



let tyCtxFreshPatTy pat ctx =
  let _, loc = pat |> patExtract
  let tySerial, ctx = ctx |> tyCtxFreshTySerial
  let ty = MetaTy(tySerial, loc)
  ty, ctx

let tyCtxFreshExprTy expr ctx =
  let _, loc = expr |> exprExtract
  let tySerial, ctx = ctx |> tyCtxFreshTySerial
  let ty = MetaTy(tySerial, loc)
  ty, ctx

let inferPatNil ctx pat loc =
  let itemTy, ctx = ctx |> tyCtxFreshPatTy pat
  let ty = tyList itemTy
  HNilPat(itemTy, loc), ty, ctx

let inferPatNone ctx pat loc =
  let itemTy, ctx = ctx |> tyCtxFreshPatTy pat
  let ty = tyList itemTy
  HNonePat(itemTy, loc), ty, ctx

let inferPatSome ctx pat loc =
  let itemTy, ctx = ctx |> tyCtxFreshPatTy pat
  let ty = tyFun itemTy (tyList itemTy)
  HSomePat(itemTy, loc), ty, ctx

let inferPatDiscard ctx pat loc =
  let ty, ctx = ctx |> tyCtxFreshPatTy pat
  HDiscardPat(ty, loc), ty, ctx

let inferPatRef (ctx: TyCtx) varSerial loc =
  let ty, ctx =
    ctx |> tyCtxUnifyVarTy varSerial None loc

  HRefPat(varSerial, ty, loc), ty, ctx

let inferPatCall (ctx: TyCtx) pat callee args loc =
  match args with
  | [ payload ] ->
      let resultTy, ctx = ctx |> tyCtxFreshPatTy pat

      let callee, calleeTy, ctx = inferPat ctx callee
      let payload, payloadTy, ctx = inferPat ctx payload

      let ctx =
        tyCtxUnifyTy ctx loc calleeTy (tyFun payloadTy resultTy)

      HCallPat(callee, [ payload ], resultTy, loc), resultTy, ctx

  | _ -> failwith "invalid use of call pattern"

let inferPatTuple ctx itemPats loc =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] -> listRev accPats, listRev accTys, ctx
    | itemPat :: itemPats ->
        let itemPat, itemTy, ctx = inferPat ctx itemPat
        go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats

  let itemPats, itemTys, ctx = go [] [] ctx itemPats

  let tupleTy = tyTuple itemTys
  HTuplePat(itemPats, tupleTy, loc), tupleTy, ctx

let inferPatCons ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let itemTy = lTy
  let listTy = tyList itemTy
  let ctx = tyCtxUnifyTy ctx loc rTy listTy

  HConsPat(l, r, itemTy, loc), listTy, ctx

let inferPatAs ctx body varSerial loc =
  let body, bodyTy, ctx = inferPat ctx body

  let _, ctx =
    ctx |> tyCtxUnifyVarTy varSerial (Some bodyTy) loc


  HAsPat(body, varSerial, loc), bodyTy, ctx

let inferPatAnno ctx body annoTy loc =
  let body, bodyTy, ctx = inferPat ctx body
  let ctx = tyCtxUnifyTy ctx loc bodyTy annoTy
  body, annoTy, ctx

let inferPatOr ctx first second loc =
  // FIXME: Error if two patterns introduce different bindings.
  let first, firstTy, ctx = inferPat ctx first
  let second, secondTy, ctx = inferPat ctx second

  let ctx = tyCtxUnifyTy ctx loc firstTy secondTy

  let ty = firstTy
  HOrPat(first, second, ty, loc), ty, ctx

let inferPat ctx pat: HPat * Ty * TyCtx =
  match pat with
  | HLitPat (lit, _) -> pat, litToTy lit, ctx
  | HNilPat (_, loc) -> inferPatNil ctx pat loc
  | HNonePat (_, loc) -> inferPatNone ctx pat loc
  | HSomePat (_, loc) -> inferPatSome ctx pat loc
  | HDiscardPat (_, loc) -> inferPatDiscard ctx pat loc
  | HRefPat (varSerial, _, loc) -> inferPatRef ctx varSerial loc
  | HCallPat (callee, args, _, loc) -> inferPatCall ctx pat callee args loc
  | HConsPat (l, r, _, loc) -> inferPatCons ctx l r loc
  | HTuplePat (items, _, loc) -> inferPatTuple ctx items loc
  | HAsPat (body, serial, loc) -> inferPatAs ctx body serial loc
  | HAnnoPat (body, annoTy, loc) -> inferPatAnno ctx body annoTy loc
  | HOrPat (first, second, _, loc) -> inferPatOr ctx first second loc
  | HNavPat _ -> failwithf "invalid use of nav pattern %A" pat

let inferRef (ctx: TyCtx) varSerial loc =
  let ty, ctx =
    ctx |> tyCtxUnifyVarTy varSerial None loc

  HRefExpr(varSerial, ty, loc), ty, ctx

let inferPrim ctx prim loc =
  let tySpec = prim |> primToTySpec
  let primTy, traits, ctx = (tySpec, ctx) |> tySpecInstantiate loc
  let ctx = ctx |> tyCtxAddTraitBounds traits
  HPrimExpr(prim, primTy, loc), primTy, ctx

// expr: nil expr itself
let inferNil ctx expr loc =
  let itemTy, ctx = tyCtxFreshExprTy expr ctx
  hxNil itemTy loc, tyList itemTy, ctx

let inferRecord ctx itself fields loc =
  let recordTy, ctx = tyCtxFreshExprTy itself ctx

  let fields, ctx =
    (fields, ctx)
    |> stMap (fun ((ident, init, loc), ctx) ->
         let init, ty, ctx = inferExpr ctx init
         (ident, init, ty, loc), ctx)

  let ctx =
    let fields =
      fields
      |> listMap (fun (ident, _, ty, loc) -> ident, ty, loc)

    tyCtxAddTraitBounds [ (RecordTrait(recordTy, fields), loc) ] ctx

  let fields =
    fields
    |> listMap (fun (ident, init, _, loc) -> ident, init, loc)

  HRecordExpr(fields, recordTy, loc), recordTy, ctx

/// match 'a with ( | 'a -> 'b )*
// expr: match expr itself
let inferMatch ctx expr cond arms loc =
  let targetTy, ctx = tyCtxFreshExprTy expr ctx

  let cond, condTy, ctx = inferExpr ctx cond

  let arms, ctx =
    (arms, ctx)
    |> stMap (fun ((pat, guard, body), ctx) ->
         let pat, patTy, ctx = inferPat ctx pat

         let ctx =
           tyCtxUnifyTy ctx (patToLoc pat) patTy condTy

         let guard, guardTy, ctx = inferExpr ctx guard

         let ctx =
           tyCtxUnifyTy ctx (exprToLoc guard) guardTy tyBool

         let body, bodyTy, ctx = inferExpr ctx body

         let ctx =
           tyCtxUnifyTy ctx (exprToLoc body) targetTy bodyTy

         (pat, guard, body), ctx)

  HMatchExpr(cond, arms, targetTy, loc), targetTy, ctx

let inferNav ctx sub mes loc =
  let findTyDynamicMember ctx sub subTy =
    let subTy = tyCtxSubstTy ctx subTy
    match subTy, mes with
    | AppTy (StrTyCtor, []), "Length" ->
        let funExpr =
          HPrimExpr(HPrim.StrLength, tyFun tyStr tyInt, loc)

        Some(hxApp funExpr sub tyInt loc, tyInt, ctx)
    | _ -> None

  let sub, subTy, ctx = inferExpr ctx sub

  match findTyDynamicMember ctx sub subTy with
  | Some (expr, ty, ctx) -> expr, ty, ctx
  | None ->
      let ctx =
        tyCtxAddErr ctx (sprintf "Unknown nav %A.%s" sub mes) loc

      hxAbort ctx loc

// expr: app expr itself
let inferOpAppNativeFun ctx expr callee firstArg arg targetTy loc =
  match firstArg, arg with
  | HLitExpr (StrLit nativeFunIdent, _), HLitExpr (IntLit arity, _) ->
      let rec go ty arity ctx =
        if arity = 0 then
          ty, ctx
        else
          let argTy, _, ctx = tyCtxFreshTyVar "arg" loc ctx
          go (tyFun argTy ty) (arity - 1) ctx

      let resultTy, ctx = ctx |> tyCtxFreshExprTy expr
      let funTy, ctx = go resultTy arity ctx

      let ctx = tyCtxUnifyTy ctx loc funTy targetTy

      HPrimExpr(HPrim.NativeFun(nativeFunIdent, arity), funTy, loc), funTy, ctx
  | _ -> hxApp callee arg targetTy loc, targetTy, ctx

let inferOpAppPrintfn ctx arg loc =
  match arg with
  | HLitExpr (StrLit format, _) ->
      let funTy = analyzeFormat format
      HPrimExpr(HPrim.Printfn, funTy, loc), funTy, ctx
  | _ ->
      let ctx =
        tyCtxAddErr ctx """First arg of printfn must be string literal, "..".""" loc

      hxAbort ctx loc

let inferOpApp ctx expr callee arg loc =
  let targetTy, ctx = ctx |> tyCtxFreshExprTy expr
  let arg, argTy, ctx = inferExpr ctx arg
  let callee, calleeTy, ctx = inferExpr ctx callee

  let ctx =
    tyCtxUnifyTy ctx loc calleeTy (tyFun argTy targetTy)

  match callee with
  | HInfExpr (InfOp.App, [ HPrimExpr (HPrim.NativeFun _, _, _); firstArg ], _, _) ->
      inferOpAppNativeFun ctx expr callee firstArg arg targetTy loc
  | HPrimExpr (HPrim.Printfn, _, loc) ->
      let callee, calleeTy, ctx = inferOpAppPrintfn ctx arg loc

      let ctx =
        tyCtxUnifyTy ctx loc calleeTy (tyFun tyStr targetTy)

      hxApp callee arg targetTy loc, targetTy, ctx
  | _ -> hxApp callee arg targetTy loc, targetTy, ctx

let inferTuple (ctx: TyCtx) items loc =
  let rec go acc itemTys ctx items =
    match items with
    | [] -> listRev acc, listRev itemTys, ctx
    | item :: items ->
        let item, itemTy, ctx = inferExpr ctx item
        go (item :: acc) (itemTy :: itemTys) ctx items

  let items, itemTys, ctx = go [] [] ctx items

  hxTuple items loc, tyTuple itemTys, ctx

let inferAnno ctx body annoTy loc =
  let body, bodyTy, ctx = inferExpr ctx body

  let ctx = tyCtxUnifyTy ctx loc bodyTy annoTy

  body, annoTy, ctx

let inferLetVal ctx vis pat init next loc =
  let init, initTy, ctx = inferExpr ctx init
  let pat, patTy, ctx = inferPat ctx pat

  let ctx = tyCtxUnifyTy ctx loc initTy patTy

  let next, nextTy, ctx = inferExpr ctx next
  HLetValExpr(vis, pat, init, next, nextTy, loc), nextTy, ctx

let inferLetFun (ctx: TyCtx) varSerial vis isMainFun argPats body next loc =
  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx funTy argPats =
    match argPats with
    | [] -> [], funTy, ctx

    | argPat :: argPats ->
        let argPat, argTy, ctx = inferPat ctx argPat
        let argPats, funTy, ctx = inferArgs ctx funTy argPats
        argPat :: argPats, tyFun argTy funTy, ctx

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
      | FunDef (_, _, TyScheme ([], oldTy), _) -> tyCtxUnifyTy ctx loc oldTy calleeTy
      | _ -> failwith "NEVER: It must be a pre-generalized function"

    calleeTy, ctx

  let provisionalResultTy, ctx = ctx |> tyCtxFreshExprTy body

  let argPats, funTy, ctx =
    inferArgs ctx provisionalResultTy argPats

  let ctx = tyCtxUnifyTy ctx loc calleeTy funTy

  let body, bodyTy, ctx = inferExpr ctx body

  let ctx =
    tyCtxUnifyTy ctx loc bodyTy provisionalResultTy

  let ctx = ctx |> tyCtxDecLetDepth

  let ctx =
    tyCtxGeneralizeFun ctx outerLetDepth varSerial

  let next, nextTy, ctx = inferExpr ctx next
  HLetFunExpr(varSerial, vis, isMainFun, argPats, body, next, nextTy, loc), nextTy, ctx

/// Returns in reversed order.
let inferExprs ctx exprs loc: HExpr list * Ty * TyCtx =
  let rec go acc (prevTy, prevLoc) ctx exprs =
    match exprs with
    | [] -> acc, prevTy, ctx
    | expr :: exprs ->
        let ctx = tyCtxUnifyTy ctx prevLoc prevTy tyUnit

        let expr, ty, ctx = inferExpr ctx expr
        go (expr :: acc) (ty, exprToLoc expr) ctx exprs

  go [] (tyUnit, loc) ctx exprs

let inferSemi ctx exprs loc =
  let exprs, ty, ctx = inferExprs ctx exprs loc
  hxSemi (listRev exprs) loc, ty, ctx

let inferExpr (ctx: TyCtx) (expr: HExpr): HExpr * Ty * TyCtx =
  match expr with
  | HLitExpr (lit, _) -> expr, litToTy lit, ctx
  | HRefExpr (serial, _, loc) -> inferRef ctx serial loc
  | HPrimExpr (prim, _, loc) -> inferPrim ctx prim loc
  | HRecordExpr (fields, _, loc) -> inferRecord ctx expr fields loc
  | HMatchExpr (cond, arms, _, loc) -> inferMatch ctx expr cond arms loc
  | HNavExpr (receiver, field, _, loc) -> inferNav ctx receiver field loc
  | HInfExpr (InfOp.App, [ callee; arg ], _, loc) -> inferOpApp ctx expr callee arg loc
  | HInfExpr (InfOp.Tuple, items, _, loc) -> inferTuple ctx items loc
  | HInfExpr (InfOp.Anno, [ expr ], annoTy, loc) -> inferAnno ctx expr annoTy loc
  | HInfExpr (InfOp.Semi, exprs, _, loc) -> inferSemi ctx exprs loc
  | HLetValExpr (vis, pat, body, next, _, loc) -> inferLetVal ctx vis pat body next loc
  | HLetFunExpr (oldSerial, vis, isMainFun, args, body, next, _, loc) ->
      inferLetFun ctx oldSerial vis isMainFun args body next loc
  | HTyDeclExpr _
  | HOpenExpr _ -> expr, tyUnit, ctx
  | HInfExpr (InfOp.Anno, _, _, _)
  | HInfExpr (InfOp.App, _, _, _)
  | HInfExpr (InfOp.Closure, _, _, _)
  | HInfExpr (InfOp.CallProc, _, _, _)
  | HInfExpr (InfOp.CallClosure, _, _, _) -> failwith "Never"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"
  | HErrorExpr (error, loc) ->
      let ctx = tyCtxAddErr ctx error loc
      hxAbort ctx loc

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
           | VarDef (ident, storageModifier, _, loc) ->
               let ty, _, ctx = tyCtxFreshTyVar ident loc ctx

               let varDef = VarDef(ident, storageModifier, ty, loc)

               (varSerial, varDef), ctx

           | FunDef (ident, arity, _, loc) ->
               let ty, _, ctx = tyCtxFreshTyVar ident loc ctx
               let tyScheme = TyScheme([], ty)
               let varDef = FunDef(ident, arity, tyScheme, loc)
               (varSerial, varDef), ctx

           | VariantDef (ident, tySerial, hasPayload, payloadTy, _, loc) ->
               // Pre-compute the type of variant.
               let variantTy =
                 let unionTy = tyRef tySerial []
                 if hasPayload then tyFun payloadTy unionTy else unionTy

               let varDef =
                 VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc)

               (varSerial, varDef), ctx)

    ctx
    |> tyCtxWithVars (mapOfList (intHash, intCmp) vars)

  let ctx = ctx |> tyCtxWithLetDepth 0

  let expr, ctx =
    let expr, topLevelTy, ctx = inferExpr ctx expr

    let ctx =
      tyCtxUnifyTy ctx (exprToLoc expr) topLevelTy tyUnit

    expr, ctx

  let ctx = ctx |> tyCtxResolveTraitBounds

  // Substitute all types.
  let expr = tyCtxSubstExprTy ctx expr

  let ctx =
    let vars =
      ctx
      |> tyCtxGetVars
      |> mapMap (fun _ varDef ->
           match varDef with
           | VarDef (ident, storageModifier, ty, loc) ->
               let ty = tyCtxSubstTy ctx ty
               VarDef(ident, storageModifier, ty, loc)
           | FunDef (ident, arity, TyScheme (args, ty), loc) ->
               let ty = tyCtxSubstTy ctx ty
               FunDef(ident, arity, TyScheme(args, ty), loc)
           | VariantDef (ident, tySerial, hasPayload, payloadTy, ty, loc) ->
               let payloadTy = tyCtxSubstTy ctx payloadTy
               let ty = tyCtxSubstTy ctx ty
               VariantDef(ident, tySerial, hasPayload, payloadTy, ty, loc))

    ctx |> tyCtxWithVars vars

  let ctx =
    let tys =
      ctx
      |> tyCtxGetTys
      |> mapFilter (fun _ tyDef ->
           match tyDef with
           | MetaTyDef _ -> false

           | _ -> true)

    ctx |> tyCtxWithTys tys

  expr, ctx
