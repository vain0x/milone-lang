/// # Monomorphize types

module rec MiloneTranslation.MonoTy

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.TypeFloat
open MiloneShared.Util
open MiloneStd.StdError
open MiloneStd.StdMap
open MiloneTranslation.Hir
open MiloneTranslationTypes.HirTypes

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
    | M.StrMt -> just 6
    | M.ObjMt -> just 7
    | M.FunMt _ -> just 8
    | M.ListMt _ -> just 9

    | M.VoidPtrMt -> just 11
    | M.NativePtrMt (IsConst, _) -> pair 12 1
    | M.NativePtrMt (IsMut, _) -> pair 12 2
    | M.NativeFunMt _ -> just 13
    | M.NativeTypeMt _ -> just 14

    | M.UnionMt tySerial -> pair 21 tySerial
    | M.RecordMt tySerial -> pair 22 tySerial

  match l, r with
  | M.ListMt l, M.ListMt r -> monoTyCompare l r
  | M.FunMt l, M.FunMt r -> listCompare monoTyCompare l r
  | M.NativeFunMt l, M.NativeFunMt r -> listCompare monoTyCompare l r
  | M.NativePtrMt (lMut, l), M.NativePtrMt (rMut, r) when mutEquals lMut rMut -> monoTyCompare l r
  | M.NativeTypeMt l, M.NativeTypeMt r -> compare l r
  | _ -> compare (encode l) (encode r)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MtCtx =
  { Serial: Serial
    GetUnionDef: TySerial -> TySerial list * (string * VariantSerial * bool * Ty * Loc) list * Loc
    Map: TreeMap<Tk * MonoTy list, MonoTy * GeneratedTy>
    TyNames: TreeMap<Ty, string>
    NewTys: (TySerial * M.TyDef) list
    NewVariants: (VariantSerial * M.VariantDef) list }

let private ofHirCtx (hirCtx: HirCtx) : MtCtx =
  // #tyNames
  let tyNames =
    hirCtx.Tys
    |> TMap.fold
         (fun tyNames tySerial tyDef ->
           let tk, name =
             match tyDef with
             | UnionTyDef (ident, _, _, _) -> UnionTk tySerial, ident
             | RecordTyDef (ident, _, _, _) -> RecordTk tySerial, ident

           tyNames |> TMap.add (Ty(tk, [])) name)
         (TMap.empty tyCompare)

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

  { Serial = hirCtx.Serial
    GetUnionDef = getUnionDef
    Map = TMap.empty (pairCompare tkCompare (listCompare monoTyCompare))
    TyNames = tyNames
    NewTys = []
    NewVariants = [] }

let private mangle (tk: Tk, tyArgs: Ty list, ctx: MtCtx) : string * MtCtx =
  let name, memo = tyMangle (Ty(tk, tyArgs), ctx.TyNames)
  name, { ctx with TyNames = memo }

// -----------------------------------------------
// Control
// -----------------------------------------------

let private addTupleDef (name: string) (itemTys: MonoTy list) (ctx: MtCtx) =
  match ctx.Map |> TMap.tryFind (TupleTk, itemTys) with
  | _ when List.isEmpty itemTys -> M.UnitMt, ctx

  | Some (ty, _) -> ty, ctx

  | None ->
    let tySerial = ctx.Serial + 1
    let recordTy = Ty(RecordTk tySerial, [])
    let recordMt = M.RecordMt tySerial

    let recordTyDef =
      let fields =
        itemTys
        |> List.mapi (fun i ty -> tupleField i, ty, noLoc)

      M.RecordTyDef(name, fields, IsCRepr false, noLoc)

    let ctx =
      { ctx with
          Serial = ctx.Serial + 1
          TyNames = ctx.TyNames |> TMap.add recordTy name
          Map =
            ctx.Map
            |> TMap.add (TupleTk, itemTys) (recordMt, TupleGT)
            |> TMap.add (RecordTk tySerial, []) (recordMt, TupleGT)
          NewTys = (tySerial, recordTyDef) :: ctx.NewTys }

    recordMt, ctx

let private mtTy (ty: Ty, ctx: MtCtx) : M.MonoTy * MtCtx =
  let (Ty (tk, tyArgs)) = ty

  let polyTyArgs = tyArgs
  let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy

  match tk, tyArgs with
  | IntTk flavor, _ -> M.IntMt flavor, ctx
  | FloatTk flavor, _ -> M.FloatMt flavor, ctx
  | BoolTk, _ -> M.BoolMt, ctx
  | CharTk, _ -> M.CharMt, ctx
  | StrTk, _ -> M.StrMt, ctx
  | ObjTk, _ -> M.ObjMt, ctx
  | VoidPtrTk, _ -> M.VoidPtrMt, ctx
  | NativeTypeTk cCode, _ -> M.NativeTypeMt cCode, ctx
  | RecordTk tySerial, _ -> M.RecordMt tySerial, ctx

  | TupleTk, [] -> M.UnitMt, ctx

  | TupleTk, _ ->
    assert (List.isEmpty tyArgs |> not)

    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle (tk, polyTyArgs, ctx)
      addTupleDef name tyArgs ctx

  | FunTk, _ -> M.FunMt(tyArgs), ctx

  | ListTk, [ itemTy ] -> M.ListMt itemTy, ctx
  | ListTk, _ -> unreachable ()

  | NativePtrTk isMut, [ itemTy ] -> M.NativePtrMt(isMut, itemTy), ctx
  | NativePtrTk _, _ -> unreachable ()
  | NativeFunTk, _ -> M.NativeFunMt tyArgs, ctx

  | UnionTk tySerial, [] -> M.UnionMt tySerial, ctx

  | UnionTk polyTySerial, tyArgs ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle (tk, polyTyArgs, ctx)
      let tyVars, variants, loc = ctx.GetUnionDef polyTySerial
      let assignment = getTyAssignment tyVars polyTyArgs
      let variantCount = List.length variants

      let monoTySerial = ctx.Serial + 1
      let unionTy = Ty(UnionTk monoTySerial, [])
      let unionMt = M.UnionMt monoTySerial
      let getMonoVariantSerial (i: int) = VariantSerial(monoTySerial + i)

      let monoTyDef =
        let monoVariantSerials =
          List.init variantCount getMonoVariantSerial

        M.UnionTyDef(name, [], monoVariantSerials, loc)

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
            TyNames = ctx.TyNames |> TMap.add unionTy name
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (unionMt, UnionGT unionDef)
              |> TMap.add (UnionTk monoTySerial, []) (unionMt, UnionGT unionDef) }

      let monoVariants, ctx =
        variants
        |> List.mapi (fun i item -> i, item)
        |> List.mapFold
             (fun (ctx: MtCtx) (i, t) ->
               let name, _, hasPayload, payloadTy, loc = t
               let v = getMonoVariantSerial i

               let payloadTy, ctx =
                 (payloadTy |> tyAssign assignment, ctx) |> mtTy

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

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

let private tyToUnionDef (ty: Ty, ctx: MtCtx) : (UnionDef * MtCtx) option =
  match ty with
  | Ty (UnionTk polyTySerial, ((_ :: _) as tyArgs)) ->
    let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy
    let _, ctx = (ty, ctx) |> mtTy

    match
      ctx.Map
      |> TMap.tryFind (UnionTk polyTySerial, tyArgs)
      with
    | Some (_, UnionGT it) -> Some(it, ctx)
    | _ -> unreachable ()

  | _ -> None

let private asMonoVariant variantSerial ty (ctx: MtCtx) : (VariantSerial * MtCtx) option =
  match tyToUnionDef (ty, ctx) with
  | Some (unionDef, ctx) ->
    let monoVariantSerial =
      unionDef.VariantMap |> mapFind variantSerial

    Some(monoVariantSerial, ctx)

  | _ -> None

let private mtPat (pat, ctx) : M.HPat * MtCtx =
  match pat with
  | HLitPat (lit, loc) -> M.HLitPat(lit, loc), ctx

  | HDiscardPat (ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HDiscardPat(ty, loc), ctx

  | HVarPat (varSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HVarPat(varSerial, ty, loc), ctx

  | HVariantPat (variantSerial, ty, loc) ->
    match asMonoVariant variantSerial ty ctx with
    | Some (monoVariantSerial, ctx) ->
      let ty, ctx = (ty, ctx) |> mtTy
      M.HVariantPat(monoVariantSerial, ty, loc), ctx

    | _ ->
      let ty, ctx = (ty, ctx) |> mtTy
      M.HVariantPat(variantSerial, ty, loc), ctx

  | HNodePat (((HVariantAppPN variantSerial) as kind), ([ payloadPat ] as argPats), ty, loc) ->
    match asMonoVariant variantSerial ty ctx with
    | Some (monoVariantSerial, ctx) ->
      let payloadPat, ctx = (payloadPat, ctx) |> mtPat
      let ty, ctx = (ty, ctx) |> mtTy
      M.HNodePat(HVariantAppPN monoVariantSerial, [ payloadPat ], ty, loc), ctx

    | None ->
      let argPats, ctx = (argPats, ctx) |> stMap mtPat
      let ty, ctx = (ty, ctx) |> mtTy
      M.HNodePat(kind, argPats, ty, loc), ctx

  | HNodePat (kind, argPats, ty, loc) ->
    let argPats, ctx = (argPats, ctx) |> stMap mtPat
    let ty, ctx = (ty, ctx) |> mtTy
    M.HNodePat(kind, argPats, ty, loc), ctx

  | HAsPat (bodyPat, varSerial, loc) ->
    let bodyPat, ctx = (bodyPat, ctx) |> mtPat
    M.HAsPat(bodyPat, varSerial, loc), ctx

  | HOrPat (l, r, loc) ->
    let l, ctx = (l, ctx) |> mtPat
    let r, ctx = (r, ctx) |> mtPat
    M.HOrPat(l, r, loc), ctx

let private mtExpr (expr, ctx) : M.HExpr * MtCtx =
  match expr with
  | HLitExpr (lit, loc) -> M.HLitExpr(lit, loc), ctx

  | HVarExpr (varSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HVarExpr(varSerial, ty, loc), ctx

  | HFunExpr (funSerial, ty, _, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HFunExpr(funSerial, ty, loc), ctx

  | HVariantExpr (variantSerial, ty, loc) ->
    match asMonoVariant variantSerial ty ctx with
    | Some (monoVariantSerial, ctx) ->
      let ty, ctx = (ty, ctx) |> mtTy
      M.HVariantExpr(monoVariantSerial, ty, loc), ctx

    | _ ->
      let ty, ctx = (ty, ctx) |> mtTy
      M.HVariantExpr(variantSerial, ty, loc), ctx

  | HPrimExpr (prim, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HPrimExpr(prim, ty, loc), ctx

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = (cond, ctx) |> mtExpr

    let arms, ctx =
      (arms, ctx)
      |> stMap (fun ((pat, guard, body), ctx) ->
        let pat, ctx = (pat, ctx) |> mtPat
        let guard, ctx = (guard, ctx) |> mtExpr
        let body, ctx = (body, ctx) |> mtExpr
        (pat, guard, body), ctx)

    let ty, ctx = (ty, ctx) |> mtTy
    M.HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) ->
    let onDefault kind =
      let args, ctx = (args, ctx) |> stMap mtExpr
      let ty, ctx = (ty, ctx) |> mtTy
      M.HNodeExpr(kind, args, ty, loc), ctx

    match kind, args with
    | HTupleEN, _ :: _ -> onDefault HRecordEN

    | HCallProcEN, HVariantExpr (variantSerial, variantTy, variantLoc) :: args ->
      match asMonoVariant variantSerial ty ctx with
      | Some (monoVariantSerial, ctx) ->
        let args, ctx = (args, ctx) |> stMap mtExpr
        let variantTy, ctx = (variantTy, ctx) |> mtTy
        let ty, ctx = (ty, ctx) |> mtTy

        let callee =
          M.HVariantExpr(monoVariantSerial, variantTy, variantLoc)

        M.HNodeExpr(kind, callee :: args, ty, loc), ctx

      | _ -> onDefault kind

    | _ -> onDefault kind

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap mtStmt
    let last, ctx = (last, ctx) |> mtExpr
    M.HBlockExpr(stmts, last), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private mtStmt (stmt, ctx) : M.HStmt * MtCtx =
  match stmt with
  | HExprStmt expr ->
    let expr, ctx = mtExpr (expr, ctx)
    M.HExprStmt expr, ctx

  | HLetValStmt (pat, init, loc) ->
    let pat, ctx = (pat, ctx) |> mtPat
    let init, ctx = (init, ctx) |> mtExpr
    M.HLetValStmt(pat, init, loc), ctx

  | HLetFunStmt (callee, args, body, loc) ->
    let args, ctx = (args, ctx) |> stMap mtPat
    let body, ctx = (body, ctx) |> mtExpr
    M.HLetFunStmt(callee, args, body, loc), ctx

let private mtModule (m: HModule2, ctx) =
  let stmts, ctx = (m.Stmts, ctx) |> stMap mtStmt

  let m: M.HModule2 =
    { DocId = m.DocId
      Vars = m.Vars
      Stmts = stmts }

  m, ctx

// -----------------------------------------------
// Context
// -----------------------------------------------

let private mtDefs (hirCtx: HirCtx) (mtCtx: MtCtx) =
  // Remark: `VarDef`s don't need updating because Ty fields are no longer used.

  let funs, mtCtx =
    hirCtx.Funs
    |> TMap.fold
         (fun (funs, ctx) funSerial (funDef: FunDef) ->
           let (TyScheme (tyVars, ty)) = funDef.Ty

           if tyVars |> List.isEmpty |> not then
             funs, ctx
           else
             let ty, ctx = (ty, ctx) |> mtTy

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
               (ty, ctx) |> mtTy

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
           | UnionTyDef (name, tyArgs, serials, loc) ->
             let tyDef = M.UnionTyDef(name, tyArgs, serials, loc)
             tys |> TMap.add tySerial tyDef, ctx

           | RecordTyDef (ident, fields, repr, loc) ->
             let fields, ctx =
               (fields, ctx)
               |> stMap (fun ((ident, ty, loc), ctx) ->
                 let ty, ctx = (ty, ctx) |> mtTy
                 (ident, ty, loc), ctx)

             let tyDef = M.RecordTyDef(ident, fields, repr, loc)
             tys |> TMap.add tySerial tyDef, ctx)
         (TMap.empty compare, mtCtx)

  let variants =
    mtCtx.NewVariants
    |> List.fold (fun variants (variantSerial, variantDef) -> variants |> TMap.add variantSerial variantDef) variants

  let tys =
    mtCtx.NewTys
    |> List.fold (fun tys (tySerial, tyDef) -> tys |> TMap.add tySerial tyDef) tys

  funs, variants, tys, mtCtx

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
  | M.StrMt -> ofTk StrTk
  | M.ObjMt -> ofTk ObjTk
  | M.ListMt itemTy -> newTyApp ListTk [ itemTy ]
  | M.FunMt tyArgs -> newTyApp FunTk tyArgs

  | M.VoidPtrMt -> ofTk VoidPtrTk
  | M.NativePtrMt (isMut, itemTy) -> newTyApp (NativePtrTk isMut) [ itemTy ]
  | M.NativeFunMt tyArgs -> newTyApp NativeFunTk tyArgs
  | M.NativeTypeMt cCode -> ofTk (NativeTypeTk cCode)

  | M.UnionMt tySerial -> ofTk (UnionTk tySerial)
  | M.RecordMt tySerial -> ofTk (RecordTk tySerial)

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

let private bthModule (m: M.HModule2) : HModule2 =
  { DocId = m.DocId
    Vars = m.Vars
    Stmts = m.Stmts |> List.map bthStmt }

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
  | M.UnionTyDef (ident, tyArgs, variantSerials, loc) -> UnionTyDef(ident, tyArgs, variantSerials, loc)

  | M.RecordTyDef (ident, fields, repr, loc) ->
    let fields =
      fields
      |> List.map (fun (ident, ty, loc) -> ident, bthTy ty, loc)

    RecordTyDef(ident, fields, repr, loc)

// -----------------------------------------------
// Interface
// -----------------------------------------------

let monoTy (modules: HModule2 list, hirCtx: HirCtx) : HModule2 list * HirCtx =
  let mtCtx = ofHirCtx hirCtx

  // Convert to IR.
  let modules, mtCtx = (modules, mtCtx) |> stMap mtModule
  let funs, variants, tys, mtCtx = mtDefs hirCtx mtCtx

  // Back to HIR.
  let modules = modules |> List.map bthModule

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
        Funs = funs
        Variants = variants
        Tys = tys }

  modules, hirCtx
