/// # Monomorphize types

module rec MiloneTranslation.MonoTy

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.TypeFloat
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module M = MiloneTranslation.MonoTyIr

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private OptionDef =
  { NoneSerial: VariantSerial
    SomeSerial: VariantSerial }

[<NoEquality; NoComparison>]
type private GeneratedTy =
  | TupleGT
  | OptionGT of OptionDef

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

    | M.VoidMt -> just 11
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
    Map: AssocMap<Tk * MonoTy list, MonoTy * GeneratedTy>
    TyNames: AssocMap<Ty, string>
    NewTys: (TySerial * M.TyDef) list
    NewVariants: (VariantSerial * M.VariantDef) list }

let private ofTyCtx (tyCtx: TyCtx) : MtCtx =
  let tyNames =
    tyCtx.Tys
    |> TMap.fold
         (fun tyNames tySerial tyDef ->
           let tk, name =
             match tyDef with
             | UnionTyDef (ident, _, _, _) -> UnionTk tySerial, ident
             | RecordTyDef (ident, _, _, _) -> RecordTk tySerial, ident
             | MetaTyDef _ -> unreachable () // Resolved in Typing.

           tyNames |> TMap.add (Ty(tk, [])) name)
         (TMap.empty tyCompare)

  { Serial = tyCtx.Serial
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
  | VoidTk, _ -> M.VoidMt, ctx
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

  | OptionTk, [ itemTy ] ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle (tk, polyTyArgs, ctx)

      let tySerial = ctx.Serial + 1
      let noneSerial = VariantSerial(ctx.Serial + 2)
      let someSerial = VariantSerial(ctx.Serial + 3)
      let unionTy = Ty(UnionTk tySerial, [])
      let unionMt = M.UnionMt tySerial

      let noneDef: M.VariantDef =
        { Name = "None"
          UnionTySerial = tySerial
          IsNewtype = false
          HasPayload = false
          PayloadTy = M.UnitMt
          Loc = noLoc }

      let someDef: M.VariantDef =
        { Name = "Some"
          UnionTySerial = tySerial
          IsNewtype = false
          HasPayload = true
          PayloadTy = itemTy
          Loc = noLoc }

      let unionTyDef =
        M.UnionTyDef(name, [], [ noneSerial; someSerial ], noLoc)

      let optionDef: OptionDef =
        { NoneSerial = noneSerial
          SomeSerial = someSerial }

      let ctx =
        { ctx with
            Serial = ctx.Serial + 3
            TyNames = ctx.TyNames |> TMap.add unionTy name
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (unionMt, OptionGT optionDef)
              |> TMap.add (UnionTk tySerial, []) (unionMt, OptionGT optionDef)
            NewTys = (tySerial, unionTyDef) :: ctx.NewTys
            NewVariants =
              (someSerial, someDef)
              :: (noneSerial, noneDef) :: ctx.NewVariants }

      unionMt, ctx

  | OptionTk, _ -> unreachable ()

  | FunTk, _ -> M.FunMt(tyArgs), ctx

  | ListTk, [ itemTy ] -> M.ListMt itemTy, ctx
  | ListTk, _ -> unreachable ()

  | NativePtrTk isMut, [ itemTy ] -> M.NativePtrMt(isMut, itemTy), ctx
  | NativePtrTk _, _ -> unreachable ()
  | NativeFunTk, _ -> M.NativeFunMt tyArgs, ctx

  | UnionTk tySerial, _ ->
    // NOTE: Surprizing! Ty args are ignored here but it does work.
    //       Due to AutoBoxing, all ty parameters are hidden behind `obj`,
    //       no need to monomorphize ty definitions.
    M.UnionMt tySerial, ctx

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

let private tyToOptionDef (ty: Ty, ctx: MtCtx) =
  let (Ty (_, tyArgs)) = ty
  let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy

  match ctx.Map |> TMap.tryFind (OptionTk, tyArgs) with
  | Some (_, OptionGT it) -> it, ctx
  | _ -> unreachable ()

let private mtPat (pat, ctx) : M.HPat * MtCtx =
  match pat with
  | HLitPat (lit, loc) -> M.HLitPat(lit, loc), ctx

  | HDiscardPat (ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HDiscardPat(ty, loc), ctx

  | HVarPat (vis, varSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HVarPat(vis, varSerial, ty, loc), ctx

  | HVariantPat (variantSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    M.HVariantPat(variantSerial, ty, loc), ctx

  | HNodePat (HNonePN, _, ty, loc) ->
    let optionDef, ctx = tyToOptionDef (ty, ctx)

    let ty, ctx = (ty, ctx) |> mtTy
    M.HVariantPat(optionDef.NoneSerial, ty, loc), ctx

  | HNodePat (HSomeAppPN, [ itemPat ], ty, loc) ->
    let optionDef, ctx = tyToOptionDef (ty, ctx)

    let itemPat, ctx = (itemPat, ctx) |> mtPat
    let ty, ctx = (ty, ctx) |> mtTy
    M.HNodePat(HVariantAppPN optionDef.SomeSerial, [ itemPat ], ty, loc), ctx

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
    let ty, ctx = (ty, ctx) |> mtTy
    M.HVariantExpr(variantSerial, ty, loc), ctx

  | HPrimExpr (prim, ty, loc) ->
    let hTy = ty
    let ty, ctx = (ty, ctx) |> mtTy

    let regular () = M.HPrimExpr(prim, ty, loc), ctx

    match prim with
    | HPrim.OptionNone ->
      let optionDef, ctx = tyToOptionDef (hTy, ctx)
      M.HVariantExpr(optionDef.NoneSerial, ty, loc), ctx

    | HPrim.OptionSome ->
      let optionDef, ctx =
        match hTy with
        | Ty (FunTk, [ _; ty ]) -> tyToOptionDef (ty, ctx)
        | _ -> unreachable ()

      M.HVariantExpr(optionDef.SomeSerial, ty, loc), ctx

    | _ -> regular ()

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = (cond, ctx) |> mtExpr

    let arms, ctx =
      (arms, ctx)
      |> stMap
           (fun ((pat, guard, body), ctx) ->
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
    | _ -> onDefault kind

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap mtExpr
    let last, ctx = (last, ctx) |> mtExpr
    M.HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
    let pat, ctx = (pat, ctx) |> mtPat
    let init, ctx = (init, ctx) |> mtExpr
    let ty, ctx = (ty, ctx) |> mtTy
    let next, ctx = (next, ctx) |> mtExpr
    M.HLetValExpr(pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap mtPat
    let body, ctx = (body, ctx) |> mtExpr
    let ty, ctx = (ty, ctx) |> mtTy
    let next, ctx = (next, ctx) |> mtExpr
    M.HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

// -----------------------------------------------
// Context
// -----------------------------------------------

let private mtDefs (tyCtx: TyCtx) (mtCtx: MtCtx) =
  // Remark: `VarDef`s don't need updating because Ty fields are no longer used.

  let funs, mtCtx =
    tyCtx.Funs
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
                 ParentOpt = funDef.ParentOpt
                 Loc = funDef.Loc }

             let funs = funs |> TMap.add funSerial funDef

             funs, ctx)
         (TMap.empty funSerialCompare, mtCtx)

  let variants, mtCtx =
    tyCtx.Variants
    |> TMap.fold
         (fun (variants, ctx) variantSerial (variantDef: VariantDef) ->
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

           variants, ctx)
         (TMap.empty variantSerialCompare, mtCtx)

  let tys, mtCtx =
    tyCtx.Tys
    |> TMap.fold
         (fun (tys, ctx) tySerial (tyDef: TyDef) ->
           match tyDef with
           | UnionTyDef (name, tyArgs, serials, loc) ->
             let tyDef = M.UnionTyDef(name, tyArgs, serials, loc)
             tys |> TMap.add tySerial tyDef, ctx

           | RecordTyDef (ident, fields, repr, loc) ->
             let fields, ctx =
               (fields, ctx)
               |> stMap
                    (fun ((ident, ty, loc), ctx) ->
                      let ty, ctx = (ty, ctx) |> mtTy
                      (ident, ty, loc), ctx)

             let tyDef = M.RecordTyDef(ident, fields, repr, loc)
             tys |> TMap.add tySerial tyDef, ctx

           | MetaTyDef _ -> unreachable ()) // Resolve in Typing.
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

  | M.VoidMt -> ofTk VoidTk
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
  | M.HVarPat (vis, varSerial, ty, loc) -> HVarPat(vis, varSerial, ofTy ty, loc)
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
  | M.HBlockExpr (stmts, last) -> HBlockExpr(ofExprs stmts, ofExpr last)
  | M.HLetValExpr (pat, init, next, ty, loc) -> HLetValExpr(ofPat pat, ofExpr init, ofExpr next, ofTy ty, loc)
  | M.HLetFunExpr (funSerial, isRec, vis, args, body, next, ty, loc) ->
    HLetFunExpr(funSerial, isRec, vis, ofPats args, ofExpr body, ofExpr next, ofTy ty, loc)

let private bthFunDef (funDef: M.FunDef) : FunDef =
  { Name = funDef.Name
    Arity = funDef.Arity
    Ty = TyScheme([], bthTy funDef.Ty)
    Abi = funDef.Abi
    Linkage = funDef.Linkage
    ParentOpt = funDef.ParentOpt
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

let monoTy (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let mtCtx = ofTyCtx tyCtx

  // Convert to IR.
  let decls, mtCtx = (decls, mtCtx) |> stMap mtExpr
  let funs, variants, tys, mtCtx = mtDefs tyCtx mtCtx

  // Back to HIR.
  let decls = decls |> List.map bthExpr

  let funs =
    funs
    |> TMap.map (fun _ funDef -> bthFunDef funDef)

  let variants =
    variants
    |> TMap.map (fun _ varDef -> bthVariantDef varDef)

  let tys =
    tys |> TMap.map (fun _ tyDef -> bthTyDef tyDef)

  let tyCtx =
    { tyCtx with
        Serial = mtCtx.Serial
        Funs = funs
        Variants = variants
        Tys = tys }

  decls, tyCtx
