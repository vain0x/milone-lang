/// # Monomorphize types

module rec MiloneLang.MonoTy

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Hir

module TMap = MiloneStd.StdMap

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

    Map: AssocMap<Ty, Ty> }

let private ofTyCtx (tyCtx: TyCtx): MtCtx =
  { Serial = tyCtx.Serial

    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys

    Map = TMap.empty tyCompare }

let private toTyCtx tyCtx (mtCtx: MtCtx): TyCtx =
  { tyCtx with
      Vars = mtCtx.Vars
      Funs = mtCtx.Funs
      Variants = mtCtx.Variants
      Tys = mtCtx.Tys }

// -----------------------------------------------
// Generation
// -----------------------------------------------

// -----------------------------------------------
// Transformation
// -----------------------------------------------

// -----------------------------------------------
// Control
// -----------------------------------------------

let private mtTy (ty, ctx): Ty * MtCtx =
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

  | FunTk, _
  | TupleTk, _
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

  let tyCtx = mtCtx |> toTyCtx tyCtx

  decls, tyCtx
