/// # Derive
///
/// Generates derived operations such as (=) for types.
module rec MiloneTranslation.Derive

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

// -----------------------------------------------
// Collect usage
// -----------------------------------------------

type private FCtx = AssocSet<Ty>

let private fuExpr ctx expr : FCtx =
  let onExpr expr ctx = fuExpr ctx expr
  let onExprs exprs ctx = exprs |> List.fold fuExpr ctx

  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _ -> ctx

  | HPrimExpr (HPrim.Equal, funTy, _) when tyIsMonomorphic funTy ->
    let ty =
      match funTy with
      | Ty (FunTk, ty :: _) -> ty
      | _ -> unreachable ()

    ctx |> TSet.add ty

  | HPrimExpr _ -> ctx

  | HMatchExpr (cond, arms, _, _) ->
    ctx
    |> onExpr cond
    |> forList (fun (_, guard, body) ctx -> ctx |> onExpr guard |> onExpr body) arms

  | HNodeExpr (_, items, _, _) -> ctx |> onExprs items
  | HBlockExpr (stmts, last) -> fuExpr (ctx |> onExprs stmts) last
  | HLetValExpr (_, body, next, _, _) -> fuExpr (ctx |> onExpr body) next
  | HLetFunExpr (_, _, _, _, body, next, _, _) -> fuExpr (ctx |> onExpr body) next

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable ()

// -----------------------------------------------
// Apply changes
// -----------------------------------------------

let private rewriteExpr (ctx: AssocMap<Ty, FunSerial>) expr : HExpr =
  let onExpr expr = rewriteExpr ctx expr
  let onExprs exprs = exprs |> List.map (rewriteExpr ctx)

  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _ -> expr

  | HPrimExpr (HPrim.Equal, funTy, loc) ->
    let ty =
      match funTy with
      | Ty (FunTk, ty :: _) -> ty
      | _ -> unreachable ()

    match ctx |> TMap.tryFind ty with
    | None -> expr
    | Some funSerial -> HFunExpr(funSerial, funTy, [], loc)

  | HPrimExpr _ -> expr

  | HMatchExpr (cond, arms, ty, loc) ->
    let onArm (pat, guard, body) =
      let guard = onExpr guard
      let body = onExpr body
      pat, guard, body

    HMatchExpr(onExpr cond, List.map onArm arms, ty, loc)

  | HNodeExpr (kind, items, ty, loc) -> HNodeExpr(kind, onExprs items, ty, loc)
  | HBlockExpr (stmts, last) -> HBlockExpr(onExprs stmts, onExpr last)

  | HLetValExpr (pat, body, next, ty, loc) -> HLetValExpr(pat, onExpr body, onExpr next, ty, loc)

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    HLetFunExpr(callee, isRec, vis, args, onExpr body, onExpr next, ty, loc)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

// -----------------------------------------------
// Generation
// -----------------------------------------------

type private DCtx =
  { Serial: Serial
    NewVars: (VarSerial * VarDef) list
    NewFuns: (FunSerial * FunDef) list
    NewLetFuns: (Ty * HExpr) list
    WorkList: Ty list
    EqualFunInstances: AssocMap<Ty, FunSerial> }

let private dCtxOfTyCtx (tyCtx: TyCtx) : DCtx =
  { Serial = tyCtx.Serial
    NewVars = []
    NewFuns = []
    NewLetFuns = []
    WorkList = []
    EqualFunInstances = TMap.empty tyCompare }

let private dExpr (tyCtx: TyCtx) expr : DCtx =
  let findTy tySerial = tyCtx.Tys |> mapFind tySerial

  let findVariant variantSerial = tyCtx.Variants |> mapFind variantSerial

  let addVar name ty loc (ctx: DCtx) =
    let serial = ctx.Serial + 1
    let varSerial = VarSerial serial

    let varDef: VarDef =
      { Name = name
        IsStatic = NotStatic
        Linkage = InternalLinkage
        Ty = ty
        Loc = loc }

    let ctx =
      { ctx with
          Serial = serial
          NewVars = (varSerial, varDef) :: ctx.NewVars }

    varSerial, ctx

  // l = r := match l, r with | T1 l, T1 r -> l = r | ... | _ -> false
  let deriveEqualForUnion ty (ctx: DCtx) : DCtx =
    let tySerial =
      match ty with
      | Ty (UnionTk tySerial, _) -> tySerial
      | _ -> unreachable ()

    let ident, variantSerials, loc =
      match findTy tySerial with
      | UnionTyDef (ident, _, variantSerials, loc) -> ident, variantSerials, loc
      | _ -> unreachable ()

    let trueExpr = hxTrue loc
    let falseExpr = HLitExpr(BoolLit false, loc)

    let funSerial, ctx =
      FunSerial(ctx.Serial + 1), { ctx with Serial = ctx.Serial + 1 }

    let funDef: FunDef =
      { Name = ident + "Equal"
        Arity = 2
        Ty = TyScheme([], tyFun ty (tyFun ty tyBool))
        Abi = MiloneAbi
        Linkage = InternalLinkage
        ParentOpt = None
        Loc = loc }

    let lArg, ctx = addVar "l" ty loc ctx
    let rArg, ctx = addVar "r" ty loc ctx

    let arms, ctx =
      variantSerials
      |> List.mapFold
           (fun ctx variantSerial ->
             let variantDef = findVariant variantSerial

             if not variantDef.HasPayload then
               // | T, T -> true
               let variantPat = HVariantPat(variantSerial, ty, loc)
               let pat = hpTuple [ variantPat; variantPat ] loc
               (pat, trueExpr, trueExpr), ctx
             else
               // | T l, T r -> l = r
               let payloadTy = variantDef.PayloadTy
               let lv, ctx = addVar "l" payloadTy loc ctx
               let rv, ctx = addVar "r" payloadTy loc ctx

               let appPat v =
                 let varPat = hpVar v payloadTy loc
                 hpVariantApp variantSerial varPat ty loc

               let pat = hpTuple [ appPat lv; appPat rv ] loc

               let body =
                 let equal =
                   HPrimExpr(HPrim.Equal, tyFun payloadTy (tyFun payloadTy tyBool), loc)

                 let l = HVarExpr(lv, payloadTy, loc)
                 let r = HVarExpr(rv, payloadTy, loc)
                 hxApp (hxApp equal l (tyFun payloadTy tyBool) loc) r tyBool loc

               let ctx =
                 { ctx with
                     WorkList = payloadTy :: ctx.WorkList }

               (pat, trueExpr, body), ctx)
           ctx

    let lastArm =
      // _ -> false
      HDiscardPat(ty, loc), trueExpr, falseExpr

    let matchExpr =
      let cond =
        hxTuple
          [ HVarExpr(lArg, ty, loc)
            HVarExpr(rArg, ty, loc) ]
          loc

      let arms = List.append arms [ lastArm ]
      HMatchExpr(cond, arms, tyBool, loc)

    let letFunExpr =
      let lPat = hpVar lArg ty loc
      let rPat = hpVar rArg ty loc
      HLetFunExpr(funSerial, NotRec, PrivateVis, [ lPat; rPat ], matchExpr, hxUnit loc, tyUnit, loc)

    let ctx =
      { ctx with
          NewFuns = (funSerial, funDef) :: ctx.NewFuns
          NewLetFuns = (ty, letFunExpr) :: ctx.NewLetFuns
          EqualFunInstances = ctx.EqualFunInstances |> TMap.add ty funSerial }

    ctx

  let ctx = dCtxOfTyCtx tyCtx

  let generate (ctx: DCtx) ty : DCtx =
    let (Ty (tk, tyArgs)) = ty

    match tk, tyArgs with
    | IntTk _, _
    | FloatTk _, _
    | BoolTk, _
    | CharTk, _
    | StrTk _, _
    | TupleTk, []
    | NativePtrTk _, _
    | NativeFunTk _, _ -> ctx

    | _ when ctx.EqualFunInstances |> TMap.containsKey ty -> ctx

    | UnionTk _, [] -> deriveEqualForUnion ty ctx

    | _ -> ctx

  let ctx =
    fuExpr (TSet.empty tyCompare) expr
    |> TSet.fold generate ctx

  let rec go workList (ctx: DCtx) : DCtx =
    match workList with
    | [] ->
      if ctx.WorkList |> List.isEmpty then
        ctx
      else
        let workList, ctx =
          ctx.WorkList, { ctx with WorkList = [] }

        go workList ctx

    | ty :: workList -> go workList (generate ctx ty)

  go [] ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let deriveOps (expr, tyCtx: TyCtx) : HExpr * TyCtx =
  let ctx = dExpr tyCtx expr
  assert (List.isEmpty ctx.WorkList)

  let vars =
    ctx.NewVars
    |> List.fold (fun vars (varSerial, varDef) -> vars |> TMap.add varSerial varDef) tyCtx.Vars

  let funs =
    ctx.NewFuns
    |> List.fold (fun funs (funSerial, funDef) -> funs |> TMap.add funSerial funDef) tyCtx.Funs

  let tyCtx =
    { tyCtx with
        Serial = ctx.Serial
        Vars = vars
        Funs = funs }

  let expr =
    let stmts =
      ctx.NewLetFuns
      |> listSort (fun (l, _) (r, _) -> tyCompare l r)
      |> List.map snd

    HBlockExpr(stmts, expr)
    |> rewriteExpr ctx.EqualFunInstances

  expr, tyCtx
