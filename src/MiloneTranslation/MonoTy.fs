/// # Monomorphize types

module rec MiloneTranslation.MonoTy

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.TypeFloat
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes

module M = MiloneTranslation.MonoTyIr

// #tyAssign?
let private getTyAssignment tyVars tyArgs : TreeMap<TySerial, _> =
  match listTryZip tyVars tyArgs with
  | zipped, [], [] -> TMap.ofList compare zipped
  | _ -> unreachable () // Arity mismatch.

// #tyAssign?
let private tyAssign assignment ty =
  tySubst (fun tySerial -> assignment |> TMap.tryFind tySerial) ty

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private UnionDef =
  { VariantMap: TreeMap<VariantSerial, VariantSerial> }

[<NoEquality; NoComparison>]
type private GeneratedTy =
  | TupleGT
  | UnionGT of UnionDef
  | RecordGT

let private tupleField (i: int) : string = "t" + string i

type private MonoTy = M.MonoTy

let private mutEquals (l: IsMut) (r: IsMut) =
  let encode isMut =
    match isMut with
    | IsMut -> true
    | IsConst -> false

  encode l = encode r

let private monoTyCompare (l: MonoTy) (r: MonoTy) : int =
  let pair x y =
    assert (x < 100)
    assert (y < 10100100)
    x * 10100100 + y

  let just n = pair n 0

  let encode (ty: MonoTy) : int =
    match ty with
    | M.IntMt flavor -> pair 1 (intFlavorToOrdinary flavor)
    | M.FloatMt flavor -> pair 2 (floatFlavorToOrdinary flavor)
    | M.UnitMt -> just 3
    | M.BoolMt -> just 4
    | M.CharMt -> just 5
    | M.StringMt -> just 6
    | M.NeverMt -> just 26 // to be reordered
    | M.ObjMt -> just 7
    | M.FunMt _ -> just 8
    | M.ListMt _ -> just 9

    | M.VoidPtrMt IsConst -> pair 11 1
    | M.VoidPtrMt IsMut -> pair 11 2
    | M.NativePtrMt (mode, _) -> pair 12 (RefMode.toInt mode)
    | M.FunPtrMt _ -> just 13
    | M.NativeTypeMt _ -> just 14

    | M.UnionMt(tySerial, _) -> pair 21 tySerial
    | M.RecordMt(tySerial, _) -> pair 22 tySerial
    | M.OpaqueMt(tySerial, _) -> pair 23 tySerial

  match l, r with
  | M.ListMt l, M.ListMt r -> monoTyCompare l r
  | M.FunMt l, M.FunMt r -> listCompare monoTyCompare l r
  | M.FunPtrMt l, M.FunPtrMt r -> listCompare monoTyCompare l r
  | M.NativePtrMt (lMode, l), M.NativePtrMt (rMode, r) when RefMode.equals lMode rMode -> monoTyCompare l r
  | M.NativeTypeMt l, M.NativeTypeMt r -> compare l r
  | _ -> compare (encode l) (encode r)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MtCtx =
  { /// Last serial number.
    Serial: Serial

    GetUnionDef: TySerial -> TySerial list * (string * VariantSerial * bool * Ty * Loc) list * Loc
    GetRecordDef: TySerial -> TySerial list * (string * Ty * Loc) list * Loc
    Map: TreeMap<Tk * MonoTy list, MonoTy * GeneratedTy>
    TyNames: TreeMap<Ty, string>
    NewTys: (TySerial * M.TyDef) list
    NewVariants: (VariantSerial * M.VariantDef) list }

let private ofHirCtx (hirCtx: HirCtx) : MtCtx =
  let getUnionDef tySerial =
    let tyArgs, variants, loc =
      match hirCtx.Tys |> mapFind tySerial with
      | UnionTyDef (_, tyArgs, variants, loc) -> tyArgs, variants, loc
      | _ -> unreachable ()

    let variantDefs =
      variants
      |> List.map (fun variantSerial ->
        let def = hirCtx.Variants |> mapFind variantSerial
        def.Name, variantSerial, def.HasPayload, def.PayloadTy, def.Loc)

    tyArgs, variantDefs, loc

  let getRecordDef tySerial =
    match hirCtx.Tys |> mapFind tySerial with
    | RecordTyDef (_, tyArgs, fields, _, loc) -> tyArgs, fields, loc
    | _ -> unreachable ()

  { Serial = hirCtx.Serial
    GetUnionDef = getUnionDef
    GetRecordDef = getRecordDef
    Map = TMap.empty (pairCompare tkCompare (listCompare monoTyCompare))
    TyNames = TMap.empty tyCompare
    NewTys = []
    NewVariants = [] }

let private mangle (ctx: MtCtx) (tk: Tk, tyArgs: Ty list) : string * MtCtx =
  let name, memo = tyMangle (Ty(tk, tyArgs), ctx.TyNames)
  name, { ctx with TyNames = memo }

// -----------------------------------------------
// Control
// -----------------------------------------------

let private addTupleDef (ctx: MtCtx) (name: string) (itemTys: MonoTy list) =
  match ctx.Map |> TMap.tryFind (TupleTk, itemTys) with
  | _ when List.isEmpty itemTys -> M.UnitMt, ctx

  | Some (ty, _) -> ty, ctx

  | None ->
    let tySerial = ctx.Serial + 1
    let recordTy = Ty(RecordTk(tySerial, name), [])
    let recordMt = M.RecordMt(tySerial, name)

    let recordTyDef =
      let fields =
        itemTys
        |> List.mapi (fun i ty -> tupleField i, ty, noLoc)

      M.RecordTyDef(name, fields, IsCRepr false, noLoc)

    let ctx =
      { ctx with
          Serial = ctx.Serial + 1
          Map =
            ctx.Map
            |> TMap.add (TupleTk, itemTys) (recordMt, TupleGT)
            |> TMap.add (RecordTk(tySerial, name), []) (recordMt, TupleGT)
          NewTys = (tySerial, recordTyDef) :: ctx.NewTys }

    recordMt, ctx

let private mtTy (ctx: MtCtx) (ty: Ty) : M.MonoTy * MtCtx =
  let (Ty (tk, tyArgs)) = ty

  let polyTyArgs = tyArgs
  let tyArgs, ctx = tyArgs |> List.mapFold mtTy ctx

  match tk, tyArgs with
  | IntTk flavor, _ -> M.IntMt flavor, ctx
  | FloatTk flavor, _ -> M.FloatMt flavor, ctx
  | BoolTk, _ -> M.BoolMt, ctx
  | CharTk, _ -> M.CharMt, ctx
  | StringTk, _ -> M.StringMt, ctx
  | NeverTk, _ -> M.NeverMt, ctx
  | ObjTk, _ -> M.ObjMt, ctx
  | VoidPtrTk isMut, _ -> M.VoidPtrMt isMut, ctx
  | NativeTypeTk cCode, _ -> M.NativeTypeMt cCode, ctx
  | OpaqueTk(tySerial, name), _ -> M.OpaqueMt(tySerial, name), ctx

  | TupleTk, [] -> M.UnitMt, ctx

  | TupleTk, _ ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle ctx (tk, polyTyArgs)
      addTupleDef ctx name tyArgs

  | FunTk, _ -> M.FunMt tyArgs, ctx

  | ListTk, [ itemTy ] -> M.ListMt itemTy, ctx
  | ListTk, _ -> unreachable ()

  | NativePtrTk mode, [ itemTy ] -> M.NativePtrMt(mode, itemTy), ctx
  | NativePtrTk _, _ -> unreachable ()
  | FunPtrTk, _ -> M.FunPtrMt tyArgs, ctx

  | UnionTk(tySerial, name), [] -> M.UnionMt(tySerial, name), ctx

  | UnionTk(polyTySerial, _), tyArgs ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle ctx (tk, polyTyArgs)
      let tyVars, variants, loc = ctx.GetUnionDef polyTySerial
      let assignment = getTyAssignment tyVars polyTyArgs
      let variantCount = List.length variants

      let monoTySerial = ctx.Serial + 1
      let unionTy = Ty(UnionTk(monoTySerial, name), [])
      let unionMt = M.UnionMt(monoTySerial, name)
      let getMonoVariantSerial (i: int) = VariantSerial(monoTySerial + i)

      let monoTyDef =
        let monoVariantSerials =
          List.init variantCount getMonoVariantSerial

        M.UnionTyDef(name, monoVariantSerials, loc)

      let unionDef: UnionDef =
        let variantMap =
          variants
          |> List.mapi (fun i (_, polyVariantSerial, _, _, _) -> polyVariantSerial, getMonoVariantSerial i)
          |> TMap.ofList variantSerialCompare

        { VariantMap = variantMap }

      // Register to prevent recursion.
      let ctx: MtCtx =
        { ctx with
            Serial = ctx.Serial + 1 + variantCount
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (unionMt, UnionGT unionDef)
              |> TMap.add (UnionTk(monoTySerial, name), []) (unionMt, UnionGT unionDef) }

      let monoVariants, ctx =
        variants
        |> List.mapi (fun i item -> i, item)
        |> List.mapFold
             (fun (ctx: MtCtx) (i, t) ->
               let name, _, hasPayload, payloadTy, loc = t
               let v = getMonoVariantSerial i

               let payloadTy, ctx =
                 payloadTy |> tyAssign assignment |> mtTy ctx

               let def: M.VariantDef =
                 { Name = name
                   UnionTySerial = monoTySerial
                   IsNewtype = variantCount = 1
                   HasPayload = hasPayload
                   PayloadTy = payloadTy
                   Loc = loc }

               (v, def), ctx)
             ctx

      let ctx =
        { ctx with
            NewTys = (monoTySerial, monoTyDef) :: ctx.NewTys
            NewVariants = List.append monoVariants ctx.NewVariants }

      unionMt, ctx

  | RecordTk(tySerial, name), [] -> M.RecordMt(tySerial, name), ctx

  | RecordTk(polyTySerial, _), tyArgs ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle ctx (tk, polyTyArgs)
      let tyVars, fields, loc = ctx.GetRecordDef polyTySerial
      let assignment = getTyAssignment tyVars polyTyArgs

      let monoTySerial = ctx.Serial + 1
      let recordTy = Ty(RecordTk(monoTySerial, name), [])
      let recordMt = M.RecordMt(monoTySerial, name)

      // Register to prevent recursion.
      let ctx: MtCtx =
        { ctx with
            Serial = ctx.Serial + 1
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (recordMt, RecordGT)
              |> TMap.add (RecordTk(monoTySerial, name), []) (recordMt, RecordGT) }

      let monoFields, ctx =
        fields
        |> List.mapi (fun i item -> i, item)
        |> List.mapFold
             (fun (ctx: MtCtx) (i, t) ->
               let ident, polyFieldTy, loc = t

               let monoFieldTy, ctx =
                 polyFieldTy |> tyAssign assignment |> mtTy ctx

               (ident, monoFieldTy, loc), ctx)
             ctx

      let ctx =
        // Repr doesn't matter after AutoBoxing.
        let repr = IsCRepr true

        let monoTyDef =
          M.RecordTyDef(name, monoFields, repr, loc)

        { ctx with NewTys = (monoTySerial, monoTyDef) :: ctx.NewTys }

      recordMt, ctx

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

let private tyToUnionDef (ty: Ty, ctx: MtCtx) : (UnionDef * MtCtx) option =
  match ty with
  | Ty ((UnionTk(polyTySerial, _) as tk), ((_ :: _) as tyArgs)) ->
    let tyArgs, ctx = tyArgs |> List.mapFold mtTy ctx
    let _, ctx = ty |> mtTy ctx

    match
      ctx.Map
      |> TMap.tryFind (tk, tyArgs)
      with
    | Some (_, UnionGT it) -> Some(it, ctx)
    | _ -> unreachable ()

  | _ -> None

let private asMonoVariant (ctx: MtCtx) variantSerial ty : (VariantSerial * MtCtx) option =
  match tyToUnionDef (ty, ctx) with
  | Some (unionDef, ctx) ->
    let monoVariantSerial =
      unionDef.VariantMap |> mapFind variantSerial

    Some(monoVariantSerial, ctx)

  | _ -> None

let private mtPat ctx pat : M.HPat * MtCtx =
  match pat with
  | HLitPat (lit, loc) -> M.HLitPat(lit, loc), ctx

  | HDiscardPat (ty, loc) ->
    let ty, ctx = ty |> mtTy ctx
    M.HDiscardPat(ty, loc), ctx

  | HVarPat (varSerial, ty, loc) ->
    let ty, ctx = ty |> mtTy ctx
    M.HVarPat(varSerial, ty, loc), ctx

  | HVariantPat (variantSerial, ty, loc) ->
    match asMonoVariant ctx variantSerial ty with
    | Some (monoVariantSerial, ctx) ->
      let ty, ctx = ty |> mtTy ctx
      M.HVariantPat(monoVariantSerial, ty, loc), ctx

    | _ ->
      let ty, ctx = ty |> mtTy ctx
      M.HVariantPat(variantSerial, ty, loc), ctx

  | HNodePat (((HVariantAppPN variantSerial) as kind), ([ payloadPat ] as argPats), ty, loc) ->
    match asMonoVariant ctx variantSerial ty with
    | Some (monoVariantSerial, ctx) ->
      let payloadPat, ctx = payloadPat |> mtPat ctx
      let ty, ctx = ty |> mtTy ctx
      M.HNodePat(HVariantAppPN monoVariantSerial, [ payloadPat ], ty, loc), ctx

    | None ->
      let argPats, ctx = argPats |> List.mapFold mtPat ctx
      let ty, ctx = ty |> mtTy ctx
      M.HNodePat(kind, argPats, ty, loc), ctx

  | HNodePat (kind, argPats, ty, loc) ->
    let argPats, ctx = argPats |> List.mapFold mtPat ctx
    let ty, ctx = ty |> mtTy ctx
    M.HNodePat(kind, argPats, ty, loc), ctx

  | HAsPat (bodyPat, varSerial, loc) ->
    let bodyPat, ctx = bodyPat |> mtPat ctx
    M.HAsPat(bodyPat, varSerial, loc), ctx

  | HOrPat (l, r, loc) ->
    let l, ctx = l |> mtPat ctx
    let r, ctx = r |> mtPat ctx
    M.HOrPat(l, r, loc), ctx

let private mtExpr ctx expr : M.HExpr * MtCtx =
  match expr with
  | HLitExpr (lit, loc) -> M.HLitExpr(lit, loc), ctx

  | HVarExpr (varSerial, ty, loc) ->
    let ty, ctx = ty |> mtTy ctx
    M.HVarExpr(varSerial, ty, loc), ctx

  | HFunExpr (funSerial, ty, _, loc) ->
    let ty, ctx = ty |> mtTy ctx
    M.HFunExpr(funSerial, ty, loc), ctx

  | HVariantExpr (variantSerial, ty, loc) ->
    match asMonoVariant ctx variantSerial ty with
    | Some (monoVariantSerial, ctx) ->
      let ty, ctx = ty |> mtTy ctx
      M.HVariantExpr(monoVariantSerial, ty, loc), ctx

    | _ ->
      let ty, ctx = ty |> mtTy ctx
      M.HVariantExpr(variantSerial, ty, loc), ctx

  | HPrimExpr (prim, ty, loc) ->
    let ty, ctx = ty |> mtTy ctx
    M.HPrimExpr(prim, ty, loc), ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = cond |> mtExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guard, body) ->
             let pat, ctx = pat |> mtPat ctx
             let guard, ctx = guard |> mtExpr ctx
             let body, ctx = body |> mtExpr ctx
             (pat, guard, body), ctx)
           ctx

    let ty, ctx = ty |> mtTy ctx
    M.HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) ->
    let onDefault kind =
      let args, ctx = args |> List.mapFold mtExpr ctx
      let ty, ctx = ty |> mtTy ctx
      M.HNodeExpr(kind, args, ty, loc), ctx

    match kind, args with
    | HTupleEN, _ :: _ -> onDefault HRecordEN

    | HCallProcEN, HVariantExpr (variantSerial, variantTy, variantLoc) :: args ->
      match asMonoVariant ctx variantSerial ty with
      | Some (monoVariantSerial, ctx) ->
        let args, ctx = args |> List.mapFold mtExpr ctx
        let variantTy, ctx = variantTy |> mtTy ctx
        let ty, ctx = ty |> mtTy ctx

        let callee =
          M.HVariantExpr(monoVariantSerial, variantTy, variantLoc)

        M.HNodeExpr(kind, callee :: args, ty, loc), ctx

      | _ -> onDefault kind

    | _ -> onDefault kind

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = stmts |> List.mapFold mtStmt ctx
    let last, ctx = last |> mtExpr ctx
    M.HBlockExpr(stmts, last), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private mtStmt ctx stmt : M.HStmt * MtCtx =
  match stmt with
  | HExprStmt expr ->
    let expr, ctx = expr |> mtExpr ctx
    M.HExprStmt expr, ctx

  | HLetValStmt (pat, init, loc) ->
    let pat, ctx = pat |> mtPat ctx
    let init, ctx = init |> mtExpr ctx
    M.HLetValStmt(pat, init, loc), ctx

  | HLetFunStmt (callee, args, body, loc) ->
    let args, ctx = args |> List.mapFold mtPat ctx
    let body, ctx = body |> mtExpr ctx
    M.HLetFunStmt(callee, args, body, loc), ctx

  | HNativeDeclStmt (cCode, args, loc) ->
    let args, ctx = args |> List.mapFold mtExpr ctx
    M.HNativeDeclStmt(cCode, args, loc), ctx

let private mtModule ctx (m: HModule2) =
  let stmts, ctx = m.Stmts |> List.mapFold mtStmt ctx

  let m: M.HModule2 =
    { DocId = m.DocId

      // Not updated, because Ty fields are no longer used.
      Vars = m.Vars

      MainFunOpt = m.MainFunOpt
      Stmts = stmts }

  m, ctx

// -----------------------------------------------
// Context
// -----------------------------------------------

let private mtDefs (hirCtx: HirCtx) (mtCtx: MtCtx) =
  let staticVars, mtCtx =
    hirCtx.StaticVars
    |> TMap.fold
         (fun (staticVars, ctx) varSerial (varDef: VarDef) ->
           let ty, ctx = varDef.Ty |> mtTy ctx

           let varDef: M.VarDef =
             { Name = varDef.Name
               Ty = ty
               Linkage = varDef.Linkage
               Loc = varDef.Loc }

           staticVars |> TMap.add varSerial varDef, ctx)
         (TMap.empty varSerialCompare, mtCtx)

  let funs, mtCtx =
    hirCtx.Funs
    |> TMap.fold
         (fun (funs, ctx) funSerial (funDef: FunDef) ->
           let (TyScheme (tyVars, ty)) = funDef.Ty

           if tyVars |> List.isEmpty |> not then
             funs, ctx
           else
             let ty, ctx = ty |> mtTy ctx

             let funDef: M.FunDef =
               { Name = funDef.Name
                 Arity = funDef.Arity
                 Ty = ty
                 Abi = funDef.Abi
                 Linkage = funDef.Linkage
                 Prefix = funDef.Prefix
                 Loc = funDef.Loc }

             let funs = funs |> TMap.add funSerial funDef

             funs, ctx)
         (TMap.empty funSerialCompare, mtCtx)

  let variants, mtCtx =
    hirCtx.Variants
    |> TMap.fold
         (fun (variants, ctx) variantSerial (variantDef: VariantDef) ->
           let monomorphic =
             match hirCtx.Tys |> mapFind variantDef.UnionTySerial with
             | UnionTyDef (_, [], _, _) -> true
             | _ -> false

           if monomorphic then
             let payloadTy, ctx =
               let ty = variantDef.PayloadTy
               ty |> mtTy ctx

             let variantDef: M.VariantDef =
               { Name = variantDef.Name
                 UnionTySerial = variantDef.UnionTySerial
                 IsNewtype = variantDef.IsNewtype
                 HasPayload = variantDef.HasPayload
                 PayloadTy = payloadTy
                 Loc = variantDef.Loc }

             let variants =
               variants |> TMap.add variantSerial variantDef

             variants, ctx
           else
             variants, ctx)
         (TMap.empty variantSerialCompare, mtCtx)

  let tys, mtCtx =
    hirCtx.Tys
    |> TMap.fold
         (fun (tys, ctx) tySerial (tyDef: TyDef) ->
           match tyDef with
           | UnionTyDef (name, [], serials, loc) ->
             let tyDef = M.UnionTyDef(name, serials, loc)
             tys |> TMap.add tySerial tyDef, ctx

           | RecordTyDef (ident, [], fields, repr, loc) ->
             let fields, ctx =
               fields
               |> List.mapFold
                    (fun ctx (ident, ty, loc) ->
                      let ty, ctx = ty |> mtTy ctx
                      (ident, ty, loc), ctx)
                    ctx

             let tyDef = M.RecordTyDef(ident, fields, repr, loc)

             tys |> TMap.add tySerial tyDef, ctx

           | OpaqueTyDef (ident, loc) ->
             let tyDef = M.OpaqueTyDef(ident, loc)
             tys |> TMap.add tySerial tyDef, ctx

           | UnionTyDef _
           | RecordTyDef _ -> tys, ctx)
         (TMap.empty compare, mtCtx)

  let variants =
    mtCtx.NewVariants
    |> List.fold (fun variants (variantSerial, variantDef) -> variants |> TMap.add variantSerial variantDef) variants

  let tys =
    mtCtx.NewTys
    |> List.fold (fun tys (tySerial, tyDef) -> tys |> TMap.add tySerial tyDef) tys

  staticVars, funs, variants, tys, mtCtx

// -----------------------------------------------
// Back to HIR
// -----------------------------------------------

let private bthTy (ty: MonoTy) : Ty =
  let ofTk (tk: Tk) : Ty = Ty(tk, [])
  let newTyApp tk tyArgs = Ty(tk, List.map bthTy tyArgs)

  match ty with
  | M.IntMt flavor -> ofTk (IntTk flavor)
  | M.FloatMt flavor -> ofTk (FloatTk flavor)
  | M.UnitMt -> ofTk TupleTk
  | M.BoolMt -> ofTk BoolTk
  | M.CharMt -> ofTk CharTk
  | M.StringMt -> ofTk StringTk
  | M.NeverMt -> ofTk NeverTk
  | M.ObjMt -> ofTk ObjTk
  | M.ListMt itemTy -> newTyApp ListTk [ itemTy ]
  | M.FunMt tyArgs -> newTyApp FunTk tyArgs

  | M.VoidPtrMt isMut -> ofTk (VoidPtrTk isMut)
  | M.NativePtrMt (isMut, itemTy) -> newTyApp (NativePtrTk isMut) [ itemTy ]
  | M.FunPtrMt tyArgs -> newTyApp FunPtrTk tyArgs
  | M.NativeTypeMt cCode -> ofTk (NativeTypeTk cCode)

  | M.UnionMt(tySerial, name) -> ofTk (UnionTk(tySerial, name))
  | M.RecordMt(tySerial, name) -> ofTk (RecordTk(tySerial, name))
  | M.OpaqueMt(tySerial, name) -> ofTk (OpaqueTk(tySerial, name))

let private bthPat (pat: M.HPat) : HPat =
  let ofTy ty = bthTy ty
  let ofPat pat = bthPat pat
  let ofPats pats = List.map bthPat pats

  match pat with
  | M.HLitPat (lit, loc) -> HLitPat(lit, loc)
  | M.HDiscardPat (ty, loc) -> HDiscardPat(ofTy ty, loc)
  | M.HVarPat (varSerial, ty, loc) -> HVarPat(varSerial, ofTy ty, loc)
  | M.HVariantPat (variantSerial, ty, loc) -> HVariantPat(variantSerial, ofTy ty, loc)
  | M.HNodePat (kind, pats, ty, loc) -> HNodePat(kind, ofPats pats, ofTy ty, loc)
  | M.HAsPat (pat, varSerial, loc) -> HAsPat(ofPat pat, varSerial, loc)
  | M.HOrPat (l, r, loc) -> HOrPat(ofPat l, ofPat r, loc)

let private bthExpr (expr: M.HExpr) : HExpr =
  let ofTy ty = bthTy ty
  let ofPat pat = bthPat pat
  let ofPats pats = List.map bthPat pats
  let ofExpr expr = bthExpr expr
  let ofExprs exprs = List.map bthExpr exprs
  let ofStmts stmts = List.map bthStmt stmts

  match expr with
  | M.HLitExpr (lit, loc) -> HLitExpr(lit, loc)
  | M.HVarExpr (varSerial, ty, loc) -> HVarExpr(varSerial, ofTy ty, loc)
  | M.HFunExpr (funSerial, ty, loc) -> HFunExpr(funSerial, ofTy ty, [], loc)
  | M.HVariantExpr (variantSerial, ty, loc) -> HVariantExpr(variantSerial, ofTy ty, loc)
  | M.HPrimExpr (prim, ty, loc) -> HPrimExpr(prim, ofTy ty, loc)

  | M.HMatchExpr (cond, arms, ty, loc) ->
    let arms =
      arms
      |> List.map (fun (pat, guard, body) -> ofPat pat, ofExpr guard, ofExpr body)

    HMatchExpr(ofExpr cond, arms, ofTy ty, loc)

  | M.HNodeExpr (kind, args, ty, loc) -> HNodeExpr(kind, ofExprs args, ofTy ty, loc)
  | M.HBlockExpr (stmts, last) -> HBlockExpr(ofStmts stmts, ofExpr last)

let private bthStmt stmt =
  let ofTy ty = bthTy ty
  let ofPat pat = bthPat pat
  let ofPats pats = List.map bthPat pats
  let ofExpr expr = bthExpr expr
  let ofExprs exprs = List.map bthExpr exprs

  match stmt with
  | M.HExprStmt expr -> HExprStmt(bthExpr expr)
  | M.HLetValStmt (pat, init, loc) -> HLetValStmt(ofPat pat, ofExpr init, loc)
  | M.HLetFunStmt (funSerial, args, body, loc) -> HLetFunStmt(funSerial, ofPats args, ofExpr body, loc)
  | M.HNativeDeclStmt (cCode, args, loc) -> HNativeDeclStmt(cCode, ofExprs args, loc)

let private bthModule (m: M.HModule2) : HModule2 =
  { DocId = m.DocId
    Vars = m.Vars
    MainFunOpt = m.MainFunOpt
    Stmts = m.Stmts |> List.map bthStmt }

let private bthVarDef (varDef: M.VarDef) : VarDef =
  { Name = varDef.Name
    IsStatic = IsStatic
    Linkage = varDef.Linkage
    Ty = bthTy varDef.Ty
    Loc = varDef.Loc }

let private bthFunDef (funDef: M.FunDef) : FunDef =
  { Name = funDef.Name
    Arity = funDef.Arity
    Ty = TyScheme([], bthTy funDef.Ty)
    Abi = funDef.Abi
    Linkage = funDef.Linkage
    Prefix = funDef.Prefix
    Loc = funDef.Loc }

let private bthVariantDef (variantDef: M.VariantDef) : VariantDef =
  { Name = variantDef.Name
    UnionTySerial = variantDef.UnionTySerial
    IsNewtype = variantDef.IsNewtype
    HasPayload = variantDef.HasPayload
    PayloadTy = bthTy variantDef.PayloadTy
    Loc = variantDef.Loc }

let private bthTyDef (tyDef: M.TyDef) : TyDef =
  match tyDef with
  | M.UnionTyDef (ident, variantSerials, loc) -> UnionTyDef(ident, [], variantSerials, loc)

  | M.RecordTyDef (ident, fields, repr, loc) ->
    let fields =
      fields
      |> List.map (fun (ident, ty, loc) -> ident, bthTy ty, loc)

    RecordTyDef(ident, [], fields, repr, loc)

  | M.OpaqueTyDef (ident, loc) -> OpaqueTyDef(ident, loc)

// -----------------------------------------------
// Interface
// -----------------------------------------------

let monoTy (modules: HModule2 list, hirCtx: HirCtx) : HModule2 list * HirCtx =
  let mtCtx = ofHirCtx hirCtx

  // Convert to IR.
  let modules, mtCtx = modules |> List.mapFold mtModule mtCtx
  let staticVars, funs, variants, tys, mtCtx = mtDefs hirCtx mtCtx

  // Back to HIR.
  let modules = modules |> List.map bthModule

  let staticVars =
    staticVars
    |> TMap.map (fun _ varDef -> bthVarDef varDef)

  let funs =
    funs
    |> TMap.map (fun _ funDef -> bthFunDef funDef)

  let variants =
    variants
    |> TMap.map (fun _ varDef -> bthVariantDef varDef)

  let tys =
    tys |> TMap.map (fun _ tyDef -> bthTyDef tyDef)

  let hirCtx =
    { hirCtx with
        Serial = mtCtx.Serial
        StaticVars = staticVars
        Funs = funs
        Variants = variants
        Tys = tys }

  modules, hirCtx
