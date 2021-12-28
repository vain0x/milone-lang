/// # Derive
///
/// Generates derived operations such as (=) for types.
module rec MiloneTranslation.Derive

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneStd.StdError
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneTranslation.Hir

// #tyAppliedBy
let private tyAppliedBy n ty =
  match ty with
  | Ty (FunTk, [ _; ty ]) when n > 0 -> tyAppliedBy (n - 1) ty
  | _ -> ty

let private tyFun2 arg1 arg2 result = tyFun arg1 (tyFun arg2 result)
let private tyFun3 arg1 arg2 arg3 result = tyFun arg1 (tyFun2 arg2 arg3 result)

let private hxApp1 callee arg =
  let resultTy = exprToTy callee |> tyAppliedBy 1
  let loc = exprToLoc arg
  hxApp callee arg resultTy loc

let private hxApp2 callee arg1 arg2 = hxApp1 (hxApp1 callee arg1) arg2
let private hxApp3 callee arg1 arg2 arg3 = hxApp1 (hxApp2 callee arg1 arg2) arg3

// -----------------------------------------------
// Collect usage
// -----------------------------------------------

type private FCtx = TreeSet<Ty>

let private fuExpr ctx expr : FCtx =
  let onExpr expr ctx = fuExpr ctx expr
  let onExprs exprs ctx = exprs |> List.fold fuExpr ctx
  let onStmts stmts ctx = stmts |> List.fold fuStmt ctx

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
  | HBlockExpr (stmts, last) -> fuExpr (ctx |> onStmts stmts) last

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable ()

let private fuStmt ctx stmt : FCtx =
  match stmt with
  | HExprStmt expr -> fuExpr ctx expr
  | HLetValStmt (_, init, _) -> fuExpr ctx init
  | HLetFunStmt (_, _, body, _) -> fuExpr ctx body

// -----------------------------------------------
// Apply changes
// -----------------------------------------------

let private rewriteExpr (ctx: TreeMap<Ty, FunSerial>) expr : HExpr =
  let onExpr expr = rewriteExpr ctx expr
  let onExprs exprs = exprs |> List.map (rewriteExpr ctx)
  let onStmts stmts = stmts |> List.map (rewriteStmt ctx)

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
    let arms = arms |> List.map (hArmMap id onExpr)
    HMatchExpr(onExpr cond, arms, ty, loc)

  | HNodeExpr (kind, items, ty, loc) -> HNodeExpr(kind, onExprs items, ty, loc)
  | HBlockExpr (stmts, last) -> HBlockExpr(onStmts stmts, onExpr last)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private rewriteStmt ctx stmt : HStmt =
  let onExpr expr = rewriteExpr ctx expr

  match stmt with
  | HExprStmt expr -> HExprStmt(onExpr expr)
  | HLetValStmt (pat, init, loc) -> HLetValStmt(pat, onExpr init, loc)
  | HLetFunStmt (callee, args, body, loc) -> HLetFunStmt(callee, args, onExpr body, loc)

// -----------------------------------------------
// Generation
// -----------------------------------------------

type private DCtx =
  { Serial: Serial
    NewVars: (VarSerial * VarDef) list
    NewFuns: (FunSerial * FunDef) list
    NewLetFuns: (Ty * HStmt) list
    WorkList: Ty list
    GenericListEqualFunOpt: FunSerial option
    EqualFunInstances: TreeMap<Ty, FunSerial> }

let private ofHirCtx (hirCtx: HirCtx) : DCtx =
  { Serial = hirCtx.Serial
    NewVars = []
    NewFuns = []
    NewLetFuns = []
    WorkList = []
    GenericListEqualFunOpt = None
    EqualFunInstances = TMap.empty tyCompare }

let private deriveOnStmt (hirCtx: HirCtx) (ctx: DCtx) stmt : DCtx =
  let findTy tySerial = hirCtx.Tys |> mapFind tySerial

  let findVariant variantSerial =
    hirCtx.Variants |> mapFind variantSerial

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

  let findGenericListEqualFunOpt (ctx: DCtx) : FunSerial option * DCtx =
    match ctx.GenericListEqualFunOpt with
    | (Some _) as it -> it, ctx
    | None ->
      let funSerialOpt =
        hirCtx.Funs
        |> TMap.fold
             (fun opt funSerial (funDef: FunDef) ->
               let (Loc (docId, _, _)) = funDef.Loc

               if docId = "MiloneStd.Equal"
                  && funDef.Name = "genericListEqual" then
                 Some funSerial
               else
                 opt)
             None

      let ctx =
        if Option.isSome funSerialOpt then
          { ctx with GenericListEqualFunOpt = funSerialOpt }
        else
          ctx

      funSerialOpt, ctx

  // l = r :=
  //    let (l1, l2, ...), (r1, r2, ...) = l, r
  //    (l1 = r1) & (l2 = r2) & ...
  let deriveEqualForTuple ty (ctx: DCtx) : DCtx =
    let loc = Loc("MiloneDerive.TupleEqual", 0, 0)

    let tyArgs =
      match ty with
      | Ty (TupleTk, tyArgs) -> tyArgs
      | _ -> unreachable ()

    let funSerial, ctx =
      FunSerial(ctx.Serial + 1), { ctx with Serial = ctx.Serial + 1 }

    let funDef: FunDef =
      { Name = "tuple" + string (List.length tyArgs) + "Equal"
        Arity = 2
        Ty = TyScheme([], tyFun ty (tyFun ty tyBool))
        Abi = MiloneAbi
        Linkage = InternalLinkage
        Prefix = []
        Loc = loc }

    let lArg, ctx = addVar "l" ty loc ctx
    let rArg, ctx = addVar "r" ty loc ctx

    let lPatAcc, rPatAcc, prodAcc, ctx =
      tyArgs
      |> List.fold
           (fun (lPats, rPats, prods, ctx) tyArg ->
             let lArg, ctx = addVar "l" tyArg loc ctx
             let rArg, ctx = addVar "r" tyArg loc ctx

             let lPat = hpVar lArg tyArg loc
             let rPat = hpVar rArg tyArg loc

             let prod =
               let equal =
                 HPrimExpr(HPrim.Equal, tyFun tyArg (tyFun tyArg tyBool), loc)

               let l = HVarExpr(lArg, tyArg, loc)
               let r = HVarExpr(rArg, tyArg, loc)
               hxApp (hxApp equal l (tyFun tyArg tyBool) loc) r tyBool loc

             lPat :: lPats, rPat :: rPats, prod :: prods, ctx)
           ([], [], [], ctx)

    let lPat = hpTuple (List.rev lPatAcc) loc
    let rPat = hpTuple (List.rev rPatAcc) loc

    let prod =
      let prod0, prods =
        match List.rev prodAcc with
        | head :: tail -> head, tail
        | _ -> unreachable () // Not empty.

      List.fold
        (fun l r ->
          let conj =
            HPrimExpr(HPrim.BitAnd, tyFun tyBool (tyFun tyBool tyBool), loc)

          hxApp (hxApp conj l (tyFun tyBool tyBool) loc) r tyBool loc)
        prod0
        prods

    let body =
      HBlockExpr(
        [ HLetValStmt(lPat, HVarExpr(lArg, ty, loc), loc)
          HLetValStmt(rPat, HVarExpr(rArg, ty, loc), loc) ],
        prod
      )

    let letFunStmt =
      let lPat = hpVar lArg ty loc
      let rPat = hpVar rArg ty loc
      HLetFunStmt(funSerial, [ lPat; rPat ], body, loc)

    let ctx =
      { ctx with
          NewFuns = (funSerial, funDef) :: ctx.NewFuns
          NewLetFuns = (ty, letFunStmt) :: ctx.NewLetFuns
          WorkList = List.append tyArgs ctx.WorkList
          EqualFunInstances = ctx.EqualFunInstances |> TMap.add ty funSerial }

    ctx

  // l = r :=
  //    MiloneStd.Equal.genericListEqual compare l r
  let deriveEqualForList ty (ctx: DCtx) : DCtx =
    let loc = Loc("MiloneDerive.ListEqual", 0, 0)

    let itemTy =
      match ty with
      | Ty (ListTk, [ itemTy ]) -> itemTy
      | _ -> unreachable ()

    let underlyingFun, ctx =
      match findGenericListEqualFunOpt ctx with
      | Some it, ctx -> it, ctx

      | _ ->
        // FIXME: don't crash it
        printfn "ERROR: open MiloneStd.Equal to enable list equality"
        exit 1

    let funSerial, ctx =
      FunSerial(ctx.Serial + 1), { ctx with Serial = ctx.Serial + 1 }

    let funDef: FunDef =
      { Name = "listEqual"
        Arity = 2
        Ty = TyScheme([], tyFun ty (tyFun ty tyBool))
        Abi = MiloneAbi
        Linkage = InternalLinkage
        Prefix = []
        Loc = loc }

    let lArg, ctx = addVar "l" ty loc ctx
    let rArg, ctx = addVar "r" ty loc ctx

    let body =
      let equalTy = tyFun2 itemTy itemTy tyBool

      let callee =
        HFunExpr(underlyingFun, tyFun3 equalTy itemTy itemTy tyBool, [], loc)

      let equalPrim = HPrimExpr(HPrim.Equal, equalTy, loc)
      let l = HVarExpr(lArg, ty, loc)
      let r = HVarExpr(rArg, ty, loc)

      hxApp3 callee equalPrim l r

    let letFunStmt =
      let lPat = hpVar lArg ty loc
      let rPat = hpVar rArg ty loc
      HLetFunStmt(funSerial, [ lPat; rPat ], body, loc)

    let ctx =
      { ctx with
          NewFuns = (funSerial, funDef) :: ctx.NewFuns
          NewLetFuns = (ty, letFunStmt) :: ctx.NewLetFuns
          WorkList = itemTy :: ctx.WorkList
          EqualFunInstances = ctx.EqualFunInstances |> TMap.add ty funSerial }

    ctx

  // l = r := match l, r with | T1 l, T1 r -> l = r | ... | _ -> false
  let deriveEqualForUnion ty (ctx: DCtx) : DCtx =
    let tySerial, tyArgs =
      match ty with
      | Ty (UnionTk tySerial, tyArgs) -> tySerial, tyArgs
      | _ -> unreachable ()

    let ident, tyVars, variantSerials, loc =
      match findTy tySerial with
      | UnionTyDef (ident, tyVars, variantSerials, loc) -> ident, tyVars, variantSerials, loc
      | _ -> unreachable ()

    // #tyAssign
    let tyAssign =
      match listTryZip tyVars tyArgs with
      | [], [], [] -> id
      | assignment, [], [] -> tySubst (fun tySerial -> assocTryFind compare tySerial assignment)
      | _ -> fun (_: Ty) -> unreachable ()

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
        Prefix = []
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
               let payloadTy = tyAssign variantDef.PayloadTy
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
                 { ctx with WorkList = payloadTy :: ctx.WorkList }

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

    let letFunStmt =
      let lPat = hpVar lArg ty loc
      let rPat = hpVar rArg ty loc
      HLetFunStmt(funSerial, [ lPat; rPat ], matchExpr, loc)

    let ctx =
      { ctx with
          NewFuns = (funSerial, funDef) :: ctx.NewFuns
          NewLetFuns = (ty, letFunStmt) :: ctx.NewLetFuns
          EqualFunInstances = ctx.EqualFunInstances |> TMap.add ty funSerial }

    ctx

  let generate (ctx: DCtx) ty : DCtx =
    let (Ty (tk, tyArgs)) = ty

    match tk, tyArgs with
    | IntTk _, _
    | FloatTk _, _
    | BoolTk, _
    | CharTk, _
    | StrTk _, _
    | NativePtrTk _, _
    | NativeFunTk _, _ -> ctx

    | _ when ctx.EqualFunInstances |> TMap.containsKey ty -> ctx

    | TupleTk _, [] -> ctx
    | TupleTk _, _ -> deriveEqualForTuple ty ctx

    | ListTk _, _ -> deriveEqualForList ty ctx
    | UnionTk _, _ -> deriveEqualForUnion ty ctx

    | _ -> ctx

  let ctx =
    fuStmt (TSet.empty tyCompare) stmt
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

  let ctx = go [] ctx

  assert (List.isEmpty ctx.WorkList)
  ctx

let private deriveOnModule (m: HModule, hirCtx: HirCtx) : HModule * HirCtx =
  let ctx =
    m.Stmts
    |> List.fold (deriveOnStmt hirCtx) (ofHirCtx hirCtx)

  assert (List.isEmpty ctx.WorkList)

  // Rewrite.
  let stmts =
    let letFunStmts =
      ctx.NewLetFuns
      |> listSort (fun (l, _) (r, _) -> tyCompare l r)
      |> List.map snd

    let stmts = List.append letFunStmts m.Stmts

    stmts
    |> List.map (rewriteStmt ctx.EqualFunInstances)

  // Merge.
  let localVars =
    ctx.NewVars
    |> List.fold (fun vars (varSerial, varDef) -> vars |> TMap.add varSerial varDef) m.Vars

  let funs =
    ctx.NewFuns
    |> List.fold (fun funs (funSerial, funDef) -> funs |> TMap.add funSerial funDef) hirCtx.Funs

  let m =
    { m with
        Vars = localVars
        Stmts = stmts }

  let hirCtx =
    { hirCtx with
        Serial = ctx.Serial
        Funs = funs }

  m, hirCtx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let deriveOps (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  (modules, hirCtx) |> stMap deriveOnModule
