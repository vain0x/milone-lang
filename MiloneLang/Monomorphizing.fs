/// Resolves polymorphic functions.
///
/// ## Monomorphization
///
/// **Monomorphization** refers to a kind of code conversion
/// to eliminate use of generic types and functions from program.
///
/// We need this stage because the target language (C language)
/// doesn't support generics.
///
/// ## Glossary
///
/// Types and functions are *monomorphic* if and only if
/// they have no type parameters.
///
/// ### Example
///
/// The code below contains use of generic type `'a * 'b`
/// and two use of generic function `flip`.
///
/// ```fsharp
///   let flip (x, y) = (y, x)
///   (1, "one") |> flip |> flip
/// ```
///
/// The monomorphization converts it to the code below:
///
/// ```fsharp
///   let flipIntStringPair ((x, y): int * string): string * int = (y, x)
///   let flipStringIntPair ((x, y): string * int): int * string = (y, x)
///   (1, "one") |> flipIntStringPair |> flipStringIntPair
/// ```
///
/// In short, this conversion *clones* generic definitions
/// for each combination of type parameters in use-site
/// with type parameters replaced with such monomorphic types.
///
/// ### Algorithm
///
/// Repeat the following while something happens:
///
/// 1. For each reference expression to generic function `f`,
///    if the use-site type `t` is monomorphic,
///    replace with the monomorphized instance of (`f`, `t`) if exists;
///    or mark the pair (`f`, `t`) for later otherwise.
/// 2. For each definition expression of generic function `f`,
///    for each marked pair (`f`, `t`),
///    clone the definition and unify the function type with `t`.
///    The cloned function is referred to as monomorphized instance of (`f`, `t`).
///
/// NOTE: The algorithm seems inefficient and the finiteness is unproven.
module rec MiloneLang.Monomorphizing

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records
open MiloneLang.TySystem

let intTyToHash (value, ty) =
  intHash value |> hashCombine (tyToHash ty)

let intTyCmp (firstValue, firstTy) (secondValue, secondTy) =
  if firstValue <> secondValue then intCmp firstValue secondValue else tyCmp firstTy secondTy

let monoCtxFromTyCtx (tyCtx: TyCtx): MonoCtx =
  MonoCtx
    (tyCtx |> tyCtxGetSerial,
     tyCtx |> tyCtxGetLogs,

     tyCtx |> tyCtxGetVars,
     tyCtx |> tyCtxGetTys,
     tyCtx |> tyCtxGetTyDepths,

     mapEmpty (intHash, intCmp),
     mapEmpty (intTyToHash, intTyCmp),
     MonoMode.Monify,
     true,
     0)

let monoCtxToTyCtx (monoCtx: MonoCtx): TyContext =
  TyContext(monoCtx |> monoCtxGetSerial, monoCtx |> monoCtxGetTys, monoCtx |> monoCtxGetTyDepths)

let monoCtxWithTyCtx (tyCtx: TyContext) logAcc (monoCtx: MonoCtx) =
  monoCtx
  |> monoCtxWithSerial (tyCtx |> tyContextGetSerial)
  |> monoCtxWithLogs (logAcc)
  |> monoCtxWithTys (tyCtx |> tyContextGetTys)
  |> monoCtxWithTyDepths (tyCtx |> tyContextGetTyDepths)

let monoCtxBindTy (monoCtx: MonoCtx) tySerial ty loc: MonoCtx =
  monoCtx
  |> monoCtxWithTyCtx (typingBind (monoCtxToTyCtx monoCtx) tySerial ty loc) (monoCtx |> monoCtxGetLogs)

let monoCtxSubstTy (monoCtx: MonoCtx) ty: Ty = typingSubst (monoCtxToTyCtx monoCtx) ty

let monoCtxUnifyTy (monoCtx: MonoCtx) (lTy: Ty) (rTy: Ty) loc =
  let tyCtx = monoCtxToTyCtx monoCtx

  let logAcc, tyCtx =
    typingUnify (monoCtx |> monoCtxGetLogs) tyCtx lTy rTy loc

  monoCtx |> monoCtxWithTyCtx tyCtx logAcc

let monoCtxSubstTyExpr ctx expr =
  let subst ty = monoCtxSubstTy ctx ty
  exprMap subst id expr

let monoCtxSubstPatTy ctx pat =
  let subst ty = monoCtxSubstTy ctx ty
  patMap subst id pat

let monoCtxSubstPatsTy ctx pats = List.map (monoCtxSubstPatTy ctx) pats

let monoCtxMarkSomethingHappened (ctx: MonoCtx) = ctx |> monoCtxWithSomethingHappened true

let monoCtxFindVarDef (ctx: MonoCtx) serial = ctx |> monoCtxGetVars |> mapFind serial

let monoCtxFindGenericFunDef (ctx: MonoCtx) serial =
  match ctx |> monoCtxGetVars |> mapFind serial with
  | FunDef (_, _, TyScheme ([], _), _) -> None
  | FunDef (ident, arity, TyScheme (_, funTy), loc) -> Some(ident, arity, funTy, loc)
  | _ -> None

let monoCtxGetGenericFunIdent funSerial (ctx: MonoCtx) =
  match monoCtxFindGenericFunDef ctx funSerial with
  | Some (ident, _, _, _) -> ident

  | None -> failwith "NEVER"

/// Generalizes all functions that has type variables.
let monoCtxForceGeneralizeFuns (ctx: MonoCtx) =
  let forceGeneralize (varSerial, varDef) =
    match varDef with
    | FunDef (ident, arity, TyScheme (_, ty), loc) ->
        let fvs = ty |> tyCollectFreeVars
        varSerial, FunDef(ident, arity, TyScheme(fvs, ty), loc)

    | _ -> varSerial, varDef

  let vars =
    ctx
    |> monoCtxGetVars
    |> mapToList
    |> List.map forceGeneralize
    |> mapOfList (intHash, intCmp)

  ctx |> monoCtxWithVars vars

let monoCtxAddMonomorphizedFun (ctx: MonoCtx) genericFunSerial arity useSiteTy loc =
  assert (monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy
          |> Option.isNone)

  let varDef =
    let monoTyScheme = TyScheme([], useSiteTy)

    let ident =
      ctx |> monoCtxGetGenericFunIdent genericFunSerial

    FunDef(ident, arity, monoTyScheme, loc)

  let monoFunSerial = (ctx |> monoCtxGetSerial) + 1

  let ctx =
    ctx
    |> monoCtxWithSerial ((ctx |> monoCtxGetSerial) + 1)
    |> monoCtxWithVars
         (ctx
          |> monoCtxGetVars
          |> mapAdd monoFunSerial varDef)
    |> monoCtxWithGenericFunMonoSerials
         (ctx
          |> monoCtxGetGenericFunMonoSerials
          |> mapAdd (genericFunSerial, useSiteTy) monoFunSerial)

  let ctx = monoCtxMarkSomethingHappened ctx
  monoFunSerial, ctx

let monoCtxFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx
  |> monoCtxGetGenericFunMonoSerials
  |> mapTryFind (funSerial, useSiteTy)

let monoCtxMarkUseOfGenericFun (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic = useSiteTy |> tyIsMonomorphic

  let notMonomorphizedYet =
    monoCtxFindMonomorphizedFun ctx funSerial useSiteTy
    |> Option.isNone

  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      match ctx
            |> monoCtxGetGenericFunUseSiteTys
            |> mapTryFind funSerial with
      | None -> []
      | Some useSiteTys -> useSiteTys

    let useSiteTys = useSiteTy :: useSiteTys

    let map =
      ctx
      |> monoCtxGetGenericFunUseSiteTys
      |> mapAdd funSerial useSiteTys

    let ctx =
      ctx |> monoCtxWithGenericFunUseSiteTys map

    let ctx = monoCtxMarkSomethingHappened ctx
    ctx

let monoCtxTakeMarkedGenericFunUseSiteTys (ctx: MonoCtx) funSerial =
  match ctx
        |> monoCtxGetGenericFunUseSiteTys
        |> mapTryFind funSerial with
  | None
  | Some [] -> [], ctx
  | Some useSiteTys ->
      let _, map =
        ctx
        |> monoCtxGetGenericFunUseSiteTys
        |> mapRemove funSerial

      let ctx =
        ctx |> monoCtxWithGenericFunUseSiteTys map

      let ctx = monoCtxMarkSomethingHappened ctx
      useSiteTys, ctx

/// Replaces the variable serial to monomorphized function serial if possible.
/// Or marks an use of generic function if possible.
/// Does nothing if the serial is NOT a generic function.
let monoCtxProcessVarRef ctx varSerial useSiteTy =
  match monoCtxFindVarDef ctx varSerial with
  | VarDef _
  | VariantDef _
  | FunDef (_, _, TyScheme ([], _), _) -> varSerial, ctx

  | FunDef _ ->
      match monoCtxFindMonomorphizedFun ctx varSerial useSiteTy with
      | Some monoFunSerial -> monoFunSerial, ctx

      | None ->
          let ctx =
            monoCtxMarkUseOfGenericFun ctx varSerial useSiteTy

          varSerial, ctx

let monifyPat (pat, ctx) = pat, ctx

let monifyExprLetFun ctx callee vis isMainFun args body next ty loc =
  let genericFunSerial = callee

  let letGenericFunExpr =
    HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] -> next, ctx
    | useSiteTy :: useSiteTys ->
        match monoCtxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
        | Some _ -> go next arity genericFunTy useSiteTys ctx
        | None ->

            // Within the context where genericFunTy and useSiteTy are unified
            // resolve all types in args and body.
            let extendedCtx =
              monoCtxUnifyTy ctx genericFunTy useSiteTy loc

            let monoArgs = monoCtxSubstPatsTy extendedCtx args
            let monoBody = monoCtxSubstTyExpr extendedCtx body

            let monoFunSerial, ctx =
              monoCtxAddMonomorphizedFun ctx genericFunSerial arity useSiteTy loc

            let next =
              HLetFunExpr(monoFunSerial, vis, isMainFun, monoArgs, monoBody, next, ty, loc)

            go next arity genericFunTy useSiteTys ctx

  match monoCtxFindGenericFunDef ctx genericFunSerial, monoCtxGetMode ctx with
  | None, _ -> letGenericFunExpr, ctx
  | Some _, MonoMode.RemoveGenerics -> next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
      let useSiteTys, ctx =
        monoCtxTakeMarkedGenericFunUseSiteTys ctx genericFunSerial

      go letGenericFunExpr arity genericFunTy useSiteTys ctx

let rec monifyExpr (expr, ctx) =
  match expr with
  | HErrorExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HLitExpr _
  | HPrimExpr _ -> expr, ctx

  | HRefExpr (varSerial, useSiteTy, loc) ->
      let doArm () =
        let varSerial, ctx =
          monoCtxProcessVarRef ctx varSerial useSiteTy

        HRefExpr(varSerial, useSiteTy, loc), ctx

      doArm ()

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target, ctx = (target, ctx) |> monifyExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap (fun ((pat, guard, body), ctx) ->
               let pat, ctx = (pat, ctx) |> monifyPat
               let guard, ctx = (guard, ctx) |> monifyExpr
               let body, ctx = (body, ctx) |> monifyExpr
               (pat, guard, body), ctx)

        HMatchExpr(target, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (subject, message, ty, loc) ->
      let doArm () =
        let subject, ctx = monifyExpr (subject, ctx)
        HNavExpr(subject, message, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, args, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyExpr
        HInfExpr(infOp, args, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat, ctx = (pat, ctx) |> monifyPat
        let init, ctx = (init, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let args, ctx = (args, ctx) |> stMap monifyPat
        let body, ctx = (body, ctx) |> monifyExpr
        let next, ctx = (next, ctx) |> monifyExpr
        monifyExprLetFun ctx callee vis isMainFun args body next ty loc

      doArm ()

  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

// -----------------------------------------------
// Type monomorphization
// -----------------------------------------------

// Used in MIR. This code doesn't need to be here.

let pairHash hash1 hash2 (x1, x2) = hashCombine (hash1 x1) (hash2 x2)

let pairCmp cmp1 cmp2 (l1, l2) (r1, r2) =
  let c = cmp1 l1 r1
  if c <> 0 then c else cmp2 l2 r2

let listHash hash xs =
  xs
  |> List.fold (fun h x -> hashCombine h (hash x)) (intHash 31)

let listCmp cmp ls rs =
  let rec go ls rs =
    match ls, rs with
    | [], _ -> -1
    | _, [] -> 1
    | l :: ls, r :: rs ->
        let c = cmp l r
        if c <> 0 then c else go ls rs

  go ls rs

/// Monomorphized type.
type MonoTy =
  | BoolMonoTy
  | IntMonoTy
  | UIntMonoTy
  | CharMonoTy
  | StrMonoTy
  | ObjMonoTy
  | ListMonoTy of MonoTy
  | FunMonoTy of MonoTy * MonoTy
  | TupleMonoTy of MonoTy list
  | RefMonoTy of TySerial

let monoTyToTag ty =
  match ty with
  | BoolMonoTy -> 1
  | IntMonoTy -> 2
  | UIntMonoTy -> 3
  | CharMonoTy -> 4
  | StrMonoTy -> 5
  | ObjMonoTy -> 6
  | ListMonoTy _ -> 7
  | FunMonoTy _ -> 8
  | TupleMonoTy _ -> 9
  | RefMonoTy tySerial -> 100 + tySerial

let monoTyToChildren ty =
  match ty with
  | BoolMonoTy
  | IntMonoTy
  | UIntMonoTy
  | CharMonoTy
  | StrMonoTy
  | ObjMonoTy
  | RefMonoTy _ -> []

  | ListMonoTy itemTy -> [ itemTy ]
  | FunMonoTy (sTy, tTy) -> [ sTy; tTy ]
  | TupleMonoTy itemTys -> itemTys

let monoTyHash ty =
  intHash (monoTyToTag ty)
  |> hashCombine (monoTyToChildren ty |> listHash monoTyHash)

let monoTyCmp l r =
  let c = intCmp (monoTyToTag l) (monoTyToTag r)
  if c <> 0
  then c
  else listCmp monoTyCmp (monoTyToChildren l) (monoTyToChildren r)

let monoTyListHash tys = listHash monoTyHash tys

let monoTyListCmp l r = listCmp monoTyCmp l r

let monoTyPairHash (t1, t2) =
  monoTyHash t1 |> hashCombine (monoTyHash t2)

let monoTyPairCmp (l1, l2) (r1, r2) =
  let c = monoTyCmp l1 r1
  if c <> 0 then c else monoTyCmp l2 r2

type MonoTyCtx =
  { MonoTuples: AssocMap<MonoTy list, MonoTy>
    MonoFuns: AssocMap<MonoTy * MonoTy, MonoTy>
    MonoLists: AssocMap<MonoTy, MonoTy> }

let private touchMonoTy (monoTy, ctx: MonoTyCtx) =
  match monoTy with
  | BoolMonoTy
  | IntMonoTy
  | UIntMonoTy
  | CharMonoTy
  | StrMonoTy
  | ObjMonoTy
  | TupleMonoTy []
  | RefMonoTy _ -> monoTy, ctx

  | ListMonoTy itemTy ->
      let itemTy, ctx = (itemTy, ctx) |> touchMonoTy

      match ctx.MonoLists |> mapTryFind itemTy with
      | Some ty -> ty, ctx
      | None ->
          let ty = ListMonoTy itemTy

          let ctx =
            { ctx with
                MonoLists = ctx.MonoLists |> mapAdd itemTy ty }

          ty, ctx

  | FunMonoTy (sTy, tTy) ->
      let sTy, ctx = (sTy, ctx) |> touchMonoTy
      let tTy, ctx = (tTy, ctx) |> touchMonoTy

      match ctx.MonoFuns |> mapTryFind (sTy, tTy) with
      | Some ty -> ty, ctx
      | None ->
          let ty = FunMonoTy(sTy, tTy)

          let ctx =
            { ctx with
                MonoFuns = ctx.MonoFuns |> mapAdd (sTy, tTy) ty }

          ty, ctx

  | TupleMonoTy itemTys ->
      let itemTys, ctx = (itemTys, ctx) |> stMap touchMonoTy

      match ctx.MonoTuples |> mapTryFind itemTys with
      | Some ty -> ty, ctx
      | None ->
          let ty = TupleMonoTy itemTys

          let ctx =
            { ctx with
                MonoTuples = ctx.MonoTuples |> mapAdd itemTys ty }

          ty, ctx

let private mtTy (ty, ctx) =
  match ty with
  | ErrorTy _
  | MetaTy _ -> failwithf "NEVER: %A" ty

  | AppTy (tyCtor, tyArgs) ->
      let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy

      match tyCtor with
      | BoolTyCtor -> BoolMonoTy, ctx
      | IntTyCtor -> IntMonoTy, ctx
      | UIntTyCtor -> UIntMonoTy, ctx
      | CharTyCtor -> CharMonoTy, ctx
      | StrTyCtor -> StrMonoTy, ctx
      | ObjTyCtor -> ObjMonoTy, ctx

      | RefTyCtor tySerial ->
          // unimplemented
          assert (List.isEmpty tyArgs)

          RefMonoTy tySerial, ctx

      | TupleTyCtor -> touchMonoTy (TupleMonoTy tyArgs, ctx)

      | FunTyCtor ->
          match tyArgs with
          | [ sTy; tTy ] -> touchMonoTy (FunMonoTy(sTy, tTy), ctx)
          | _ -> failwithf "NEVER: %A" ty

      | ListTyCtor ->
          match tyArgs with
          | [ itemTy ] -> touchMonoTy (ListMonoTy itemTy, ctx)
          | _ -> failwithf "NEVER: %A" ty

let mtPat _pat ctx = ctx

let mtExpr expr ctx =
  match expr with
  | HErrorExpr _
  | HTyDeclExpr _
  | HOpenExpr _
  | HLitExpr _ -> ctx

  | HPrimExpr (_, ty, _) ->
      let _, ctx = (ty, ctx) |> mtTy
      ctx

  | HRefExpr (_, ty, _) ->
      let _, ctx = (ty, ctx) |> mtTy
      ctx

  | HRecordExpr (baseOpt, fields, _, _) ->
      let ctx =
        match baseOpt with
        | Some baseExpr -> ctx |> mtExpr baseExpr
        | None -> ctx

      fields
      |> List.fold (fun ctx (_, init, _) -> ctx |> mtExpr init) ctx

  | HMatchExpr (cond, arms, ty, _) ->
      let ctx = ctx |> mtExpr cond

      let ctx =
        arms
        |> List.fold (fun ctx (pat, guard, body) -> ctx |> mtPat pat |> mtExpr guard |> mtExpr body) ctx

      let _, ctx = mtTy (ty, ctx)
      ctx

  | HInfExpr (_, args, ty, _) ->
      let ctx =
        args
        |> List.fold (fun ctx arg -> mtExpr arg ctx) ctx

      let _, ctx = (ty, ctx) |> mtTy
      ctx

  | HLetValExpr (_, pat, init, next, ty, _) ->
      let ctx = ctx |> mtExpr init |> mtPat pat
      let _, ctx = (ty, ctx) |> mtTy
      ctx |> mtExpr next

  | HLetFunExpr (_, _, _, args, body, next, ty, _) ->
      let ctx =
        args
        |> List.fold (fun ctx arg -> mtPat arg ctx) ctx
        |> mtExpr body

      let _, ctx = (ty, ctx) |> mtTy
      ctx |> mtExpr next

  | HNavExpr _ -> failwithf "NEVER: HNavExpr is resolved in NameRes or Typing. %A" expr
  | HModuleExpr _ -> failwithf "NEVER: HModuleExpr is resolved in NameRes. %A" expr

// -----------------------------------------------
// interface
// -----------------------------------------------

let monify (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let monoCtx =
    monoCtxFromTyCtx tyCtx
    |> monoCtxForceGeneralizeFuns

  // Monomorphization.
  let rec go (expr, ctx) =
    if ctx |> monoCtxGetSomethingHappened |> not then
      expr, ctx
    else if (ctx |> monoCtxGetInfiniteLoopDetector) > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx =
        ctx
        |> monoCtxWithSomethingHappened false
        |> monoCtxWithInfiniteLoopDetector ((ctx |> monoCtxGetInfiniteLoopDetector) + 1)

      (expr, ctx) |> monifyExpr |> go

  let expr, monoCtx = go (expr, monoCtx)

  // Remove generic function definitions.
  // WARNING: Bad kind of code reuse.
  let expr, monoCtx =
    let monoCtx =
      monoCtx |> monoCtxWithMode MonoMode.RemoveGenerics

    monifyExpr (expr, monoCtx)

  let tyCtx =
    tyCtx
    |> tyCtxWithSerial (monoCtx |> monoCtxGetSerial)
    |> tyCtxWithVars (monoCtx |> monoCtxGetVars)
    |> tyCtxWithTys (monoCtx |> monoCtxGetTys)

  expr, tyCtx
