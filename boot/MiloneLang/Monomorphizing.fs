module rec MiloneLang.Monomorphizing

open MiloneLang
open MiloneLang.Helpers

// ## Monomorphization
//
// **Monomorphization** refers to a kind of code conversion
// to eliminate use of generic types and functions from program.
//
// We need this stage because the target language (C language)
// doesn't support generics.
//
// ## Glossary
//
// Types and functions are *monomorphic* if and only if
// they have no type parameters.
//
// ### Example
//
// The code below contains use of generic type `Pair<'a, 'b>`
// and two use of generic function `flip`.
//
// ```fsharp
//    type Pair = | Pair of 'a * 'b
//    let flip (Pair (x, y)) = Pair (y, x)
//    Pair (1, "one") |> flip |> flip
// ```
//
// The monomorphization converts it to the code below:
//
// ```fsharp
//    type IntStringPair = | IntStringPair of int * string
//    type StringIntPair = | StringIntPair of string * int
//    let flipIntStringPair (IntStringPair (x, y)) = StringIntPair (y, x)
//    let flipStringIntPair (StringIntPair (x, y)) = IntStringPair (y, x)
//    IntStringPair (1, "one") |> flipIntStringPair |> flipStringIntPair
// ```
//
// In short, this conversion *duplicates* each generic definition
// for each combination of type parameters in use-site
// with type parameters replaced with such monomorphic types.
//
// ### Algorithm
//
// FIXME: Write in English.
//
// すべての部分式について、以下を変化がなくなるまで行う。
// 1. 多相関数 f の参照式で、その使用側の型 t が単相型である式について、
//    f を型 t に単相化したものがすでにあれば単相版の参照に置き換える。
//    なければ、f と型 t のペアをマークする。
// 2. 多相関数 f の定義式について、
//    マークされている「f と単相型 t のペア」につき、この定義式を複製して、
//    f の型 t に対する単相版として記録し、マークを削除する。

// FIXME: We don't support generic types yet.

[<RequireQualifiedAccess>]
type Mode =
  | Monify
  | RemoveGenerics

type MonoCtx =
  {
    VarSerial: int
    Vars: Map<int, VarDef>
    Tys: Map<int, TyDef>

    /// Map from
    /// - generic function serial
    ///
    /// to:
    /// - found use-site types
    GenericFunUseSiteTys: Map<int, Ty list>

    /// Map from pairs:
    /// - generic function's serial
    /// - monomorphic type
    ///
    /// to:
    /// - monomorphized function's serial
    GenericFunMonoSerials: Map<int * Ty, int>

    Mode: Mode
    SomethingHappened: bool
    InfiniteLoopDetector: int
  }

// #############################################################################
// START OF COPY FROM TYPING
// FIXME: DRY!!

let bindTy (ctx: MonoCtx) tySerial ty: MonoCtx =
  let noLoc = 0, 0
  let noIdent = "unknown"

  match substTy ctx ty with
  | Ty.Meta s when s = tySerial -> ctx
  | _ ->

  { ctx with
      Tys = ctx.Tys |> Map.add tySerial (TyDef.Meta (noIdent, ty, noLoc))
  }

let substTy (ctx: MonoCtx) ty: Ty =
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

let unifyTy (ctx: MonoCtx) (lty: Ty) (rty: Ty) =
  let lRootTy, rRootTy = lty, rty
  let rec go lty rty ctx =
    let lSubstTy = substTy ctx lty
    let rSubstTy = substTy ctx rty
    match lSubstTy, rSubstTy with
    | Ty.Meta l, Ty.Meta r when l = r ->
      ctx
    | Ty.Meta lSerial, _ when Typing.tyIsFreeIn rSubstTy lSerial ->
      bindTy ctx lSerial rty
    | _, Ty.Meta _ ->
      go rty lty ctx
    | Ty.Con (lTyCon, []), Ty.Con (rTyCon, []) when lTyCon = rTyCon ->
      ctx
    | Ty.Con (lTyCon, lTy :: lTys), Ty.Con (rTyCon, rTy :: rTys) ->
      ctx |> go lTy rTy |> go (Ty.Con (lTyCon, lTys)) (Ty.Con (rTyCon, rTys))
    | Ty.Error, _
    | _, Ty.Error ->
      ctx
    | Ty.Meta _, _ ->
      eprintfn "Couldn't unify '%A' and '%A' due to self recursion." lSubstTy rSubstTy
      ctx
    | Ty.Con _, _ ->
      eprintfn "While unifying '%A' and '%A', failed to unify '%A' and '%A'." lRootTy rRootTy lSubstTy rSubstTy
      ctx
  go lty rty ctx

/// Replaces type vars embedded in exprs
/// with inference results.
let substTyExpr ctx expr =
  let subst ty = substTy ctx ty
  exprMap subst id expr

// END OF COPY FROM TYPING
// #############################################################################

let substTyPat ctx pat =
  let subst ty = substTy ctx ty
  patMap subst id pat

let substTyPats ctx pats =
  List.map (substTyPat ctx) pats

let ctxGetMode (ctx: MonoCtx) =
  ctx.Mode

let ctxMarkSomethingHappened (ctx: MonoCtx) =
  { ctx with SomethingHappened = true }

let ctxFindVarDef (ctx: MonoCtx) serial =
  ctx.Vars |> Map.find serial

let ctxFindGenericFunDef (ctx: MonoCtx) serial =
  match ctx.Vars |> Map.find serial with
  | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
    None
  | VarDef.Fun (ident, arity, TyScheme.ForAll (_, funTy), loc) ->
    Some (ident, arity, funTy, loc)
  | _ ->
    None

let ctxAddMonomorphizedFun (ctx: MonoCtx) genericFunSerial ident arity useSiteTy loc =
  assert (ctxFindMonomorphizedFun ctx genericFunSerial useSiteTy |> Option.isNone)

  let monoTyScheme = TyScheme.ForAll ([], useSiteTy)
  let varDef = VarDef.Fun (ident, arity, monoTyScheme, loc)
  let monoFunSerial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial =
          ctx.VarSerial + 1
        Vars =
          ctx.Vars |> Map.add monoFunSerial varDef
        GenericFunMonoSerials =
          ctx.GenericFunMonoSerials
          |> Map.add (genericFunSerial, useSiteTy) monoFunSerial
    }
  let ctx = ctxMarkSomethingHappened ctx
  monoFunSerial, ctx

let ctxFindMonomorphizedFun (ctx: MonoCtx) funSerial useSiteTy =
  ctx.GenericFunMonoSerials |> Map.tryFind (funSerial, useSiteTy)

let ctxMarkUseOfGenericFun (ctx: MonoCtx) funSerial useSiteTy =
  let useSiteTyIsMonomorphic =
    useSiteTy |> Typing.tyIsMonomorphic
  let notMonomorphizedYet =
    ctxFindMonomorphizedFun ctx funSerial useSiteTy |> Option.isNone
  let canMark =
    useSiteTyIsMonomorphic && notMonomorphizedYet

  if not canMark then
    ctx
  else
    let useSiteTys =
      match ctx.GenericFunUseSiteTys |> Map.tryFind funSerial with
      | None -> []
      | Some useSiteTys -> useSiteTys
    let useSiteTys =
      useSiteTy :: useSiteTys
    let map =
      ctx.GenericFunUseSiteTys
      |> Map.add funSerial useSiteTys
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = ctxMarkSomethingHappened ctx
    ctx

let ctxTakeMarkedGenericFunUseSiteTys (ctx: MonoCtx) funSerial =
  match ctx.GenericFunUseSiteTys |> Map.tryFind funSerial with
  | None
  | Some [] ->
    [], ctx
  | Some useSiteTys ->
    let map = ctx.GenericFunUseSiteTys |> Map.remove funSerial
    let ctx = { ctx with GenericFunUseSiteTys = map }
    let ctx = ctxMarkSomethingHappened ctx
    useSiteTys, ctx

let monifyPat (pat, ctx) =
  pat, ctx

let monifyExprRefGenericFun ctx ident genericFunSerial arity useSiteTy loc =
  match ctxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
  | Some monoFunSerial ->
    HExpr.Ref (ident, HValRef.Var monoFunSerial, arity, useSiteTy, loc), ctx
  | None ->
    let ctx = ctxMarkUseOfGenericFun ctx genericFunSerial useSiteTy
    HExpr.Ref (ident, HValRef.Var genericFunSerial, arity, useSiteTy, loc), ctx

let monifyExprLetFun ctx ident callee args body next ty loc =
  let genericFunSerial = callee
  let letGenericFunExpr = HExpr.LetFun (ident, callee, args, body, next, ty, loc)

  let rec go next arity genericFunTy useSiteTys ctx =
    match useSiteTys with
    | [] ->
      next, ctx
    | useSiteTy :: useSiteTys ->
      match ctxFindMonomorphizedFun ctx genericFunSerial useSiteTy with
      | Some _ ->
        go next arity genericFunTy useSiteTys ctx
      | None ->

      // Within the context where genericFunTy and useSiteTy are unified
      // resolve all types in args and body.
      let extendedCtx = unifyTy ctx genericFunTy useSiteTy
      let monoArgs = substTyPats extendedCtx args
      let monoBody = substTyExpr extendedCtx body
      let monoFunSerial, ctx = ctxAddMonomorphizedFun ctx genericFunSerial ident arity useSiteTy loc
      let next = HExpr.LetFun (ident, monoFunSerial, monoArgs, monoBody, next, ty, loc)
      go next arity genericFunTy useSiteTys ctx

  match ctxFindGenericFunDef ctx genericFunSerial, ctxGetMode ctx with
  | None, _ ->
    letGenericFunExpr, ctx
  | Some _, Mode.RemoveGenerics ->
    next, ctx
  | Some (_, arity, genericFunTy, _), _ ->
    let useSiteTys, ctx =
      ctxTakeMarkedGenericFunUseSiteTys ctx genericFunSerial
    go letGenericFunExpr arity genericFunTy useSiteTys ctx

let rec monifyExpr (expr, ctx) =
  match expr with
  | HExpr.Error _
  | HExpr.TyDef _
  | HExpr.Lit _
  | HExpr.Ref (_, HValRef.Prim _, _, _, _) ->
    expr, ctx

  | HExpr.Ref (ident, HValRef.Var serial, arity, useSiteTy, loc) ->
    match ctxFindVarDef ctx serial with
    | VarDef.Var _
    | VarDef.Variant _
    | VarDef.Fun (_, _, TyScheme.ForAll ([], _), _) ->
      expr, ctx
    | VarDef.Fun _ ->
      monifyExprRefGenericFun ctx ident serial arity useSiteTy loc

  | HExpr.Match (target, arms, ty, loc) ->
    let target, ctx = (target, ctx) |> monifyExpr
    let arms, ctx = (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
      let pat, ctx = (pat, ctx) |> monifyPat
      let guard, ctx = (guard, ctx) |> monifyExpr
      let body, ctx = (body, ctx) |> monifyExpr
      (pat, guard, body), ctx)
    HExpr.Match (target, arms, ty, loc), ctx

  | HExpr.Nav (subject, message, ty, loc) ->
    let subject, ctx = monifyExpr (subject, ctx)
    HExpr.Nav (subject, message, ty, loc), ctx

  | HExpr.Op (op, l, r, ty, loc) ->
    let l, ctx = (l, ctx) |> monifyExpr
    let r, ctx = (r, ctx) |> monifyExpr
    HExpr.Op (op, l, r, ty, loc), ctx

  | HExpr.Inf (infOp, args, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyExpr
    HExpr.Inf (infOp, args, ty, loc), ctx

  | HExpr.Let (pat, init, next, ty, loc) ->
    let pat, ctx = (pat, ctx) |> monifyPat
    let init, ctx = (init, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    HExpr.Let (pat, init, next, ty, loc), ctx

  | HExpr.LetFun (ident, callee, args, body, next, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap monifyPat
    let body, ctx = (body, ctx) |> monifyExpr
    let next, ctx = (next, ctx) |> monifyExpr
    monifyExprLetFun ctx ident callee args body next ty loc

  | HExpr.If _ ->
    failwith "Never: If expressions are desugared"

let monify (expr: HExpr, tyCtx: Typing.TyCtx): HExpr * Typing.TyCtx =
  let monoCtx: MonoCtx =
    {
      VarSerial = tyCtx.VarSerial
      Vars = tyCtx.Vars
      Tys = tyCtx.Tys

      GenericFunUseSiteTys = Map.empty
      GenericFunMonoSerials = Map.empty

      Mode = Mode.Monify
      SomethingHappened = true
      InfiniteLoopDetector = 0
    }

  // Monomorphization.
  let rec go (expr, ctx) =
    if ctx.SomethingHappened |> not then
      expr, ctx
    else if ctx.InfiniteLoopDetector > 1000000 then
      failwith "Infinite loop in monomorphization"
    else
      let ctx =
        { ctx with
            SomethingHappened = false
            InfiniteLoopDetector = ctx.InfiniteLoopDetector + 1
        }
      (expr, ctx) |> monifyExpr |> go

  let expr, monoCtx =
    go (expr, monoCtx)

  // Remove generic function definitions.
  let expr, monoCtx =
    let monoCtx = { monoCtx with Mode = Mode.RemoveGenerics }
    monifyExpr (expr, monoCtx)

  let tyCtx =
    {
      tyCtx with
        VarSerial = monoCtx.VarSerial
        Vars = monoCtx.Vars
        Tys = monoCtx.Tys
    }

  expr, tyCtx
