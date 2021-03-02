/// # Monomorphize types

module rec MiloneLang.MonoTy

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Hir

module TMap = MiloneStd.StdMap

let private tupleField (i: int) = "t" + string i

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

    Map: AssocMap<Ty, Ty>
    TyNames: AssocMap<Ty, string>
    NewTys: (TySerial * TyDef) list }

let private ofTyCtx (tyCtx: TyCtx): MtCtx =
  let tyNames =
    tyCtx.Tys
    |> TMap.fold
         (fun tyNames tySerial tyDef ->
           let tk, name =
             match tyDef with
             | UnionTyDef (ident, _, _) -> UnionTk tySerial, ident
             | RecordTyDef (ident, _, _) -> RecordTk tySerial, ident

             | MetaTyDef _
             | UniversalTyDef _
             | SynonymTyDef _ -> failwith "NEVER: Resolved in Typing."

           tyNames |> TMap.add (Ty(tk, [])) name)
         (TMap.empty tyCompare)

  { Serial = tyCtx.Serial

    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys

    Map = TMap.empty tyCompare
    TyNames = tyNames
    NewTys = [] }

let private mangle (ty: Ty, ctx: MtCtx): string * MtCtx =
  let name, memo = tyMangle (ty, ctx.TyNames)
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

let private mtTy (ty, ctx: MtCtx): Ty * MtCtx =
  let (Ty (tk, tyArgs)) = ty

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
  | _, [] -> ty, ctx

  | TupleTk, _ ->
      (fun () ->
        match ctx.Map |> TMap.tryFind ty with
        | Some ty -> ty, ctx

        | None ->
            let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy
            let name, ctx = mangle (ty, ctx)

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
                  Map = ctx.Map |> TMap.add ty recordTy
                  NewTys = (tySerial, recordTyDef) :: ctx.NewTys }

            recordTy, ctx) ()

  | FunTk, _
  | OptionTk, _
  | ListTk, _
  | NativePtrTk _, _
  | NativeFunTk, _ ->
      let tyArgs, ctx = (tyArgs, ctx) |> stMap mtTy
      Ty(tk, tyArgs), ctx

  | UnresolvedTk _, _
  | UnresolvedVarTk _, _ -> failwith "NEVER: Resolved in NameRes."
  | ErrorTk _, _
  | MetaTk _, _
  | SynonymTk _, _ -> failwith "NEVER: Resolved in Typing"

let private mtPat (pat, ctx): HPat * MtCtx =
  match pat with
  | HLitPat _ -> pat, ctx

  | HDiscardPat (ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HDiscardPat(ty, loc), ctx) ()

  | HVarPat (vis, varSerial, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HVarPat(vis, varSerial, ty, loc), ctx) ()

  | HVariantPat (variantSerial, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HVariantPat(variantSerial, ty, loc), ctx) ()

  | HNodePat (kind, argPats, ty, loc) ->
      (fun () ->
        let argPats, ctx = (argPats, ctx) |> stMap mtPat
        let ty, ctx = (ty, ctx) |> mtTy
        HNodePat(kind, argPats, ty, loc), ctx) ()

  | HAsPat (bodyPat, varSerial, loc) ->
      (fun () ->
        let bodyPat, ctx = (bodyPat, ctx) |> mtPat
        HAsPat(bodyPat, varSerial, loc), ctx) ()

  | HOrPat (l, r, loc) ->
      (fun () ->
        let l, ctx = (l, ctx) |> mtPat
        let r, ctx = (r, ctx) |> mtPat
        HOrPat(l, r, loc), ctx) ()

let private mtExpr (expr, ctx): HExpr * MtCtx =
  match expr with
  | HLitExpr _
  | HTyDeclExpr _
  | HOpenExpr _ -> expr, ctx

  | HVarExpr (varSerial, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HVarExpr(varSerial, ty, loc), ctx) ()

  | HFunExpr (funSerial, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HFunExpr(funSerial, ty, loc), ctx) ()

  | HVariantExpr (variantSerial, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HVariantExpr(variantSerial, ty, loc), ctx) ()

  | HPrimExpr (prim, ty, loc) ->
      (fun () ->
        let ty, ctx = (ty, ctx) |> mtTy
        HPrimExpr(prim, ty, loc), ctx) ()

  | HMatchExpr (cond, arms, ty, loc) ->
      (fun () ->
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
        HMatchExpr(cond, arms, ty, loc), ctx) ()

  | HNodeExpr (kind, args, ty, loc) ->
      (fun () ->
        let args, ctx = (args, ctx) |> stMap mtExpr
        let ty, ctx = (ty, ctx) |> mtTy

        let kind =
          match kind, args with
          | HTupleEN, _ when args |> List.isEmpty |> not -> HRecordEN
          | _ -> kind

        HNodeExpr(kind, args, ty, loc), ctx) ()

  | HBlockExpr (stmts, last) ->
      (fun () ->
        let stmts, ctx = (stmts, ctx) |> stMap mtExpr
        let last, ctx = (last, ctx) |> mtExpr
        HBlockExpr(stmts, last), ctx) ()

  | HLetValExpr _ ->
      (fun () ->
        let pat, init, next, ty, loc =
          match expr with
          | HLetValExpr (pat, init, next, ty, loc) -> pat, init, next, ty, loc
          | _ -> failwith "NEVER"

        let pat, ctx = (pat, ctx) |> mtPat
        let init, ctx = (init, ctx) |> mtExpr
        let next, ctx = (next, ctx) |> mtExpr
        let ty, ctx = (ty, ctx) |> mtTy
        HLetValExpr(pat, init, next, ty, loc), ctx) ()

  | HLetFunExpr _ ->
      (fun () ->
        let callee, isRec, vis, args, body, next, ty, loc =
          match expr with
          | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) -> callee, isRec, vis, args, body, next, ty, loc
          | _ -> failwith "NEVER"

        let args, ctx = (args, ctx) |> stMap mtPat
        let body, ctx = (body, ctx) |> mtExpr
        let next, ctx = (next, ctx) |> mtExpr
        let ty, ctx = (ty, ctx) |> mtTy
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc), ctx) ()

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or RecordRes"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in RecordRes"
  | HModuleExpr _
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

// -----------------------------------------------
// Interface
// -----------------------------------------------

let monoTy (decls: HExpr list, tyCtx: TyCtx): HExpr list * TyCtx =
  let mtCtx = ofTyCtx tyCtx

  let decls, mtCtx = (decls, mtCtx) |> stMap mtExpr

  let vars, mtCtx =
    tyCtx.Vars
    |> TMap.fold
         (fun (vars, ctx) varSerial varDef ->
           let (VarDef (name, sm, ty, loc)) = varDef

           if ty |> tyIsMonomorphic |> not then
             // Ignore variables that appeared in generic functions.
             vars, ctx
           else
             let ty, ctx = (ty, ctx) |> mtTy

             let vars =
               vars
               |> TMap.add varSerial (VarDef(name, sm, ty, loc))

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

             | MetaTyDef _
             | UniversalTyDef _
             | SynonymTyDef _ -> failwith "NEVER: Resolved in Typing"

           let tys =
             if modified then
               tys |> TMap.add tySerial tyDef
             else
               tys

           tys, ctx)
         (tyCtx.Tys, mtCtx)

  let tys =
    mtCtx.NewTys
    |> List.fold (fun tys (tySerial, tyDef) -> tys |> TMap.add tySerial tyDef) tys

  let tyCtx =
    { tyCtx with
        Vars = vars
        Funs = funs
        Variants = variants
        Tys = tys }

  decls, tyCtx
