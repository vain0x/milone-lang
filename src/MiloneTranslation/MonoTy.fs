/// # Monomorphize types

module rec MiloneTranslation.MonoTy

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module M = MiloneTranslation.MonoTyIr

type private OptionDef =
  { NoneSerial: VariantSerial
    SomeSerial: VariantSerial }

type private GeneratedTy =
  | TupleGT
  | OptionGT of OptionDef

let private tupleField (i: int) : string = "t" + string i

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private MtCtx =
  { Serial: Serial

    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    Map: AssocMap<Tk * Ty list, Ty * GeneratedTy>
    TyNames: AssocMap<Ty, string>
    NewTys: (TySerial * TyDef) list
    NewVariants: (VariantSerial * VariantDef) list }

let private ofTyCtx (tyCtx: TyCtx) : MtCtx =
  let tyNames =
    tyCtx.Tys
    |> TMap.fold
         (fun tyNames tySerial tyDef ->
           let tk, name =
             match tyDef with
             | UnionTyDef (ident, _, _) -> UnionTk tySerial, ident
             | RecordTyDef (ident, _, _) -> RecordTk tySerial, ident
             | MetaTyDef _ -> unreachable () // Resolved in Typing.

           tyNames |> TMap.add (Ty(tk, [])) name)
         (TMap.empty tyCompare)

  { Serial = tyCtx.Serial

    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys

    Map = TMap.empty (pairCompare tkCompare (listCompare tyCompare))
    TyNames = tyNames
    NewTys = []
    NewVariants = [] }

let private mangle (tk: Tk, tyArgs: Ty list, ctx: MtCtx) : string * MtCtx =
  let name, memo = tyMangle (Ty(tk, tyArgs), ctx.TyNames)
  name, { ctx with TyNames = memo }

// -----------------------------------------------
// Generation
// -----------------------------------------------

// -----------------------------------------------
// Transformation
// -----------------------------------------------

// -----------------------------------------------
// Control
// -----------------------------------------------

let private mtTy (ty: Ty, ctx: MtCtx) : Ty * MtCtx =
  let (Ty (tk, tyArgs)) = ty

  let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy

  match tk, tyArgs with
  | IntTk _, _
  | FloatTk _, _
  | BoolTk, _
  | CharTk, _
  | StrTk, _
  | ObjTk, _
  | VoidTk, _
  | NativeTypeTk _, _
  | UnionTk _, _
  | RecordTk _, _
  | _, [] ->
    assert (List.isEmpty tyArgs)
    Ty(tk, []), ctx

  | TupleTk, _ ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle (tk, tyArgs, ctx)

      let tySerial = ctx.Serial + 1
      let recordTy = Ty(RecordTk tySerial, [])

      let recordTyDef =
        let fields =
          tyArgs
          |> List.mapi (fun i ty -> tupleField i, ty, noLoc)

        RecordTyDef(name, fields, noLoc)

      let ctx =
        { ctx with
            Serial = ctx.Serial + 1
            TyNames = ctx.TyNames |> TMap.add (recordTy) name
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (recordTy, TupleGT)
              |> TMap.add (RecordTk tySerial, []) (recordTy, TupleGT)
            NewTys = (tySerial, recordTyDef) :: ctx.NewTys }

      recordTy, ctx

  | OptionTk, [ iteTy ] ->
    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, _) -> ty, ctx

    | None ->
      let name, ctx = mangle (tk, tyArgs, ctx)

      let tySerial = ctx.Serial + 1
      let noneSerial = VariantSerial(ctx.Serial + 2)
      let someSerial = VariantSerial(ctx.Serial + 3)
      let unionTy = Ty(UnionTk tySerial, [])

      let noneDef: VariantDef =
        { Name = "None"
          UnionTySerial = tySerial
          IsNewtype = false
          HasPayload = false
          PayloadTy = tyUnit
          Loc = noLoc }

      let someDef: VariantDef =
        { Name = "Some"
          UnionTySerial = tySerial
          IsNewtype = false
          HasPayload = true
          PayloadTy = iteTy
          Loc = noLoc }

      let unionTyDef =
        UnionTyDef(name, [ noneSerial; someSerial ], noLoc)

      let optionDef: OptionDef =
        { NoneSerial = noneSerial
          SomeSerial = someSerial }

      let ctx =
        { ctx with
            Serial = ctx.Serial + 3
            TyNames = ctx.TyNames |> TMap.add unionTy name
            Map =
              ctx.Map
              |> TMap.add (tk, tyArgs) (unionTy, OptionGT optionDef)
              |> TMap.add (UnionTk tySerial, []) (unionTy, OptionGT optionDef)
            NewTys = (tySerial, unionTyDef) :: ctx.NewTys
            NewVariants =
              (someSerial, someDef)
              :: (noneSerial, noneDef) :: ctx.NewVariants }

      unionTy, ctx

  | OptionTk, _ -> unreachable ()

  | FunTk, _
  | ListTk, _
  | NativePtrTk _, _
  | NativeFunTk, _ -> Ty(tk, tyArgs), ctx

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

let private mtPat (pat, ctx) : HPat * MtCtx =
  match pat with
  | HLitPat _ -> pat, ctx

  | HDiscardPat (ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HDiscardPat(ty, loc), ctx

  | HVarPat (vis, varSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HVarPat(vis, varSerial, ty, loc), ctx

  | HVariantPat (variantSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HVariantPat(variantSerial, ty, loc), ctx

  | HNodePat (HNonePN, _, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    let (Ty (tk, tyArgs)) = ty

    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, OptionGT optionDef) -> HVariantPat(optionDef.NoneSerial, ty, loc), ctx
    | _ -> unreachable ()

  | HNodePat (HSomeAppPN, [ itemPat ], ty, loc) ->
    let itemPat, ctx = (itemPat, ctx) |> mtPat
    let ty, ctx = (ty, ctx) |> mtTy
    let (Ty (tk, tyArgs)) = ty

    match ctx.Map |> TMap.tryFind (tk, tyArgs) with
    | Some (ty, OptionGT optionDef) -> HNodePat(HVariantAppPN optionDef.SomeSerial, [ itemPat ], ty, loc), ctx
    | _ -> unreachable ()

  | HNodePat (kind, argPats, ty, loc) ->
    let argPats, ctx = (argPats, ctx) |> stMap mtPat
    let ty, ctx = (ty, ctx) |> mtTy
    HNodePat(kind, argPats, ty, loc), ctx

  | HAsPat (bodyPat, varSerial, loc) ->
    let bodyPat, ctx = (bodyPat, ctx) |> mtPat
    HAsPat(bodyPat, varSerial, loc), ctx

  | HOrPat (l, r, loc) ->
    let l, ctx = (l, ctx) |> mtPat
    let r, ctx = (r, ctx) |> mtPat
    HOrPat(l, r, loc), ctx

let private mtExpr (expr, ctx) : HExpr * MtCtx =
  match expr with
  | HLitExpr (lit, loc) -> expr, ctx // M.HLitExpr(lit, loc), ctx

  | HVarExpr (varSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HVarExpr(varSerial, ty, loc), ctx

  | HFunExpr (funSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HFunExpr(funSerial, ty, loc), ctx

  | HVariantExpr (variantSerial, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    HVariantExpr(variantSerial, ty, loc), ctx

  | HPrimExpr (prim, ty, loc) ->
    let ty, ctx = (ty, ctx) |> mtTy
    let (Ty (tk, tyArgs)) = ty

    let regular () = HPrimExpr(prim, ty, loc), ctx

    match prim with
    | HPrim.OptionNone ->
      match ctx.Map |> TMap.tryFind (tk, tyArgs) with
      | Some (ty, OptionGT def) -> HVariantExpr(def.NoneSerial, ty, loc), ctx
      | _ -> unreachable ()

    | HPrim.OptionSome ->
      let optionTy =
        match ty with
        | Ty (FunTk, [ _; it ]) -> it
        | _ -> unreachable ()

      let (Ty (tk, tyArgs)) = optionTy

      match ctx.Map |> TMap.tryFind (tk, tyArgs) with
      | Some (_, OptionGT def) -> HVariantExpr(def.SomeSerial, ty, loc), ctx
      | _ -> unreachable ()

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
    HMatchExpr(cond, arms, ty, loc), ctx

  | HNodeExpr (kind, args, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap mtExpr
    let ty, ctx = (ty, ctx) |> mtTy

    let kind =
      match kind, args with
      | HTupleEN, _ when args |> List.isEmpty |> not -> HRecordEN
      | _ -> kind

    HNodeExpr(kind, args, ty, loc), ctx

  | HBlockExpr (stmts, last) ->
    let stmts, ctx = (stmts, ctx) |> stMap mtExpr
    let last, ctx = (last, ctx) |> mtExpr
    HBlockExpr(stmts, last), ctx

  | HLetValExpr (pat, init, next, ty, loc) ->
    let pat, ctx = (pat, ctx) |> mtPat
    let init, ctx = (init, ctx) |> mtExpr
    let ty, ctx = (ty, ctx) |> mtTy
    let next, ctx = (next, ctx) |> mtExpr
    HLetValExpr(pat, init, next, ty, loc), ctx

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    let args, ctx = (args, ctx) |> stMap mtPat
    let body, ctx = (body, ctx) |> mtExpr
    let ty, ctx = (ty, ctx) |> mtTy
    let next, ctx = (next, ctx) |> mtExpr
    HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc), ctx

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

// -----------------------------------------------
// Interface
// -----------------------------------------------

let monoTy (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let mtCtx = ofTyCtx tyCtx

  let decls, mtCtx = (decls, mtCtx) |> stMap mtExpr

  let vars, mtCtx =
    tyCtx.Vars
    |> TMap.fold
         (fun (vars, ctx) varSerial (varDef: VarDef) ->
           let ty = varDef.Ty

           if ty |> tyIsMonomorphic |> not then
             // Ignore variables that appeared in generic functions.
             vars, ctx
           else
             let ty, ctx = (ty, ctx) |> mtTy

             let vars =
               vars |> TMap.add varSerial { varDef with Ty = ty }

             vars, ctx)
         (tyCtx.Vars, mtCtx)

  let funs, mtCtx =
    tyCtx.Funs
    |> TMap.fold
         (fun (funs, ctx) funSerial (funDef: FunDef) ->
           let (TyScheme (tyVars, ty)) = funDef.Ty

           if tyVars |> List.isEmpty |> not then
             funs, ctx
           else
             let ty, ctx = (ty, ctx) |> mtTy

             let funs =
               funs
               |> TMap.add funSerial { funDef with Ty = TyScheme([], ty) }

             funs, ctx)
         (tyCtx.Funs, mtCtx)

  let variants, mtCtx =
    tyCtx.Variants
    |> TMap.fold
         (fun (variants, ctx) variantSerial (variantDef: VariantDef) ->
           let ty = variantDef.PayloadTy
           let ty, ctx = (ty, ctx) |> mtTy

           let variants =
             variants
             |> TMap.add variantSerial { variantDef with PayloadTy = ty }

           variants, ctx)
         (tyCtx.Variants, mtCtx)

  let tys, mtCtx =
    mtCtx.Tys
    |> TMap.fold
         (fun (tys, ctx) tySerial (tyDef: TyDef) ->
           let modified, tyDef, ctx =
             match tyDef with
             | UnionTyDef _ -> false, tyDef, ctx

             | RecordTyDef (ident, fields, loc) ->
               let fields, ctx =
                 (fields, ctx)
                 |> stMap
                      (fun ((ident, ty, loc), ctx) ->
                        let ty, ctx = (ty, ctx) |> mtTy
                        (ident, ty, loc), ctx)

               let tyDef = RecordTyDef(ident, fields, loc)
               true, tyDef, ctx

             | MetaTyDef _ -> unreachable () // Resolve in Typing.

           let tys =
             if modified then
               tys |> TMap.add tySerial tyDef
             else
               tys

           tys, ctx)
         (tyCtx.Tys, mtCtx)

  let variants =
    mtCtx.NewVariants
    |> List.fold (fun variants (variantSerial, variantDef) -> variants |> TMap.add variantSerial variantDef) variants

  let tys =
    mtCtx.NewTys
    |> List.fold (fun tys (tySerial, tyDef) -> tys |> TMap.add tySerial tyDef) tys

  let tyCtx =
    { tyCtx with
        Serial = mtCtx.Serial
        Vars = vars
        Funs = funs
        Variants = variants
        Tys = tys }

  decls, tyCtx
