// Conversion from TIR to HIR.
module rec MiloneCli.Lower

open MiloneShared.Util

module Hir = MiloneTranslation.Hir
module Tir = MiloneSyntax.Tir
module TMap = MiloneStd.StdMap
module Typing = MiloneSyntax.Typing

let private lowerTk (tk: Tir.Tk) : Hir.Tk =
  match tk with
  | Tir.IntTk intFlavor -> Hir.IntTk intFlavor
  | Tir.FloatTk floatFlavor -> Hir.FloatTk floatFlavor
  | Tir.BoolTk -> Hir.BoolTk
  | Tir.CharTk -> Hir.CharTk
  | Tir.StrTk -> Hir.StrTk
  | Tir.ObjTk -> Hir.ObjTk

  | Tir.FunTk -> Hir.FunTk
  | Tir.TupleTk -> Hir.TupleTk
  | Tir.OptionTk -> Hir.OptionTk
  | Tir.ListTk -> Hir.ListTk

  | Tir.VoidTk -> Hir.VoidTk
  | Tir.NativePtrTk isMut -> Hir.NativePtrTk isMut
  | Tir.NativeFunTk -> Hir.NativeFunTk
  | Tir.NativeTypeTk code -> Hir.NativeTypeTk code

  | Tir.MetaTk (serial, loc) -> Hir.MetaTk(serial, loc)
  | Tir.UnionTk serial -> Hir.UnionTk serial
  | Tir.RecordTk serial -> Hir.RecordTk serial

  | Tir.ErrorTk _
  | Tir.SynonymTk _ -> unreachable () // Resolved in Typing.

  | Tir.UnresolvedTk _
  | Tir.UnresolvedVarTk _ -> unreachable () // Resolved in NameRes.

let private lowerTy (ty: Tir.Ty) : Hir.Ty =
  let (Tir.Ty (tk, tyArgs)) = ty
  Hir.Ty(lowerTk tk, List.map lowerTy tyArgs)

let private lowerTyScheme (tyScheme: Tir.TyScheme) : Hir.TyScheme =
  let (Tir.TyScheme (fvs, ty)) = tyScheme
  Hir.TyScheme(fvs, lowerTy ty)

let private lowerVarSerial (Tir.VarSerial serial) = Hir.VarSerial serial
let private lowerFunSerial (Tir.FunSerial serial) = Hir.FunSerial serial
let private lowerVariantSerial (Tir.VariantSerial serial) = Hir.VariantSerial serial

let private lowerVarDef (def: Tir.VarDef) : Hir.VarDef =
  { Name = def.Name
    IsStatic = def.IsStatic
    Linkage = def.Linkage
    Ty = lowerTy def.Ty
    Loc = def.Loc }

let private lowerFunDef (def: Tir.FunDef) : Hir.FunDef =
  { Name = def.Name
    Arity = def.Arity
    Ty = lowerTyScheme def.Ty
    Abi = def.Abi
    Linkage = def.Linkage
    ParentOpt = Option.map lowerFunSerial def.ParentOpt
    Loc = def.Loc }

let private lowerVariantDef (def: Tir.VariantDef) : Hir.VariantDef =
  { Name = def.Name
    UnionTySerial = def.UnionTySerial
    IsNewtype = def.IsNewtype
    HasPayload = def.HasPayload
    PayloadTy = lowerTy def.PayloadTy
    Loc = def.Loc }

let private lowerTyDef (def: Tir.TyDef) : Hir.TyDef =
  match def with
  | Tir.UnionTyDef (ident, tyArgs, variants, loc) ->
    Hir.UnionTyDef(ident, tyArgs, List.map lowerVariantSerial variants, loc)
  | Tir.RecordTyDef (ident, unimplTyArgs, fields, repr, loc) ->
    Hir.RecordTyDef(ident, List.map (fun (ident, ty, loc) -> ident, lowerTy ty, loc) fields, repr, loc)

  | Tir.MetaTyDef _
  | Tir.UniversalTyDef _
  | Tir.SynonymTyDef _ -> unreachable () // Resolved in Typing.

let private lowerPrim (prim: Tir.TPrim) : Hir.HPrim =
  match prim with
  | Tir.TPrim.Not -> Hir.HPrim.Not
  | Tir.TPrim.Add -> Hir.HPrim.Add
  | Tir.TPrim.Sub -> Hir.HPrim.Sub
  | Tir.TPrim.Mul -> Hir.HPrim.Mul
  | Tir.TPrim.Div -> Hir.HPrim.Div
  | Tir.TPrim.Modulo -> Hir.HPrim.Modulo
  | Tir.TPrim.BitAnd -> Hir.HPrim.BitAnd
  | Tir.TPrim.BitOr -> Hir.HPrim.BitOr
  | Tir.TPrim.BitXor -> Hir.HPrim.BitXor
  | Tir.TPrim.LeftShift -> Hir.HPrim.LeftShift
  | Tir.TPrim.RightShift -> Hir.HPrim.RightShift
  | Tir.TPrim.Equal -> Hir.HPrim.Equal
  | Tir.TPrim.Less -> Hir.HPrim.Less
  | Tir.TPrim.Compare -> Hir.HPrim.Compare
  | Tir.TPrim.ToInt flavor -> Hir.HPrim.ToInt flavor
  | Tir.TPrim.ToFloat flavor -> Hir.HPrim.ToFloat flavor
  | Tir.TPrim.Char -> Hir.HPrim.Char
  | Tir.TPrim.String -> Hir.HPrim.String
  | Tir.TPrim.Box -> Hir.HPrim.Box
  | Tir.TPrim.Unbox -> Hir.HPrim.Unbox
  | Tir.TPrim.StrLength -> Hir.HPrim.StrLength
  | Tir.TPrim.OptionNone -> Hir.HPrim.OptionNone
  | Tir.TPrim.OptionSome -> Hir.HPrim.OptionSome
  | Tir.TPrim.Nil -> Hir.HPrim.Nil
  | Tir.TPrim.Cons -> Hir.HPrim.Cons
  | Tir.TPrim.Exit -> Hir.HPrim.Exit
  | Tir.TPrim.Assert -> Hir.HPrim.Assert
  | Tir.TPrim.Printfn -> Hir.HPrim.Printfn
  | Tir.TPrim.InRegion -> Hir.HPrim.InRegion
  | Tir.TPrim.NativeCast -> Hir.HPrim.NativeCast
  | Tir.TPrim.PtrRead -> Hir.HPrim.PtrRead
  | Tir.TPrim.PtrWrite -> Hir.HPrim.PtrWrite

  | Tir.TPrim.NativeFun
  | Tir.TPrim.NativeExpr
  | Tir.TPrim.NativeStmt
  | Tir.TPrim.NativeDecl
  | Tir.TPrim.SizeOfVal -> unreachable () // Resolved in Typing.

let private lowerPatKind (kind: Tir.TPatKind) : Hir.HPatKind =
  match kind with
  | Tir.TNilPN -> Hir.HNilPN
  | Tir.TConsPN -> Hir.HConsPN
  | Tir.TNonePN -> Hir.HNonePN
  | Tir.TSomeAppPN -> Hir.HSomeAppPN
  | Tir.TVariantAppPN serial -> Hir.HVariantAppPN(lowerVariantSerial serial)
  | Tir.TTuplePN -> Hir.HTuplePN
  | Tir.TAbortPN -> Hir.HAbortPN

  | Tir.TAppPN
  | Tir.TNavPN _ -> unreachable () // Resolved in NameRes.

  | Tir.TSomePN
  | Tir.TAscribePN -> unreachable () // Resolved in Typing.

let private lowerExprKind (kind: Tir.TExprKind) : Hir.HExprKind =
  match kind with
  | Tir.TAbortEN -> Hir.HAbortEN
  | Tir.TMinusEN -> Hir.HMinusEN
  | Tir.TAppEN -> Hir.HAppEN
  | Tir.TIndexEN -> Hir.HIndexEN
  | Tir.TSliceEN -> Hir.HSliceEN
  | Tir.TCallNativeEN funName -> Hir.HCallNativeEN funName
  | Tir.TTupleEN -> Hir.HTupleEN
  | Tir.TNativeFunEN funSerial -> Hir.HNativeFunEN(lowerFunSerial funSerial)
  | Tir.TNativeExprEN code -> Hir.HNativeExprEN code
  | Tir.TNativeStmtEN code -> Hir.HNativeStmtEN code
  | Tir.TNativeDeclEN code -> Hir.HNativeDeclEN code
  | Tir.TSizeOfValEN -> Hir.HSizeOfValEN

  | Tir.TAscribeEN -> unreachable () // Resolved in Typing.

let private lowerPat (pat: Tir.TPat) : Hir.HPat =
  match pat with
  | Tir.TLitPat (lit, loc) -> Hir.HLitPat(lit, loc)
  | Tir.TDiscardPat (ty, loc) -> Hir.HDiscardPat(lowerTy ty, loc)
  | Tir.TVarPat (vis, varSerial, ty, loc) -> Hir.HVarPat(vis, lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.TVariantPat (variantSerial, ty, loc) -> Hir.HVariantPat(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.TNodePat (kind, args, ty, loc) -> Hir.HNodePat(lowerPatKind kind, List.map lowerPat args, lowerTy ty, loc)
  | Tir.TAsPat (body, varSerial, loc) -> Hir.HAsPat(lowerPat body, lowerVarSerial varSerial, loc)
  | Tir.TOrPat (l, r, loc) -> Hir.HOrPat(lowerPat l, lowerPat r, loc)

let private lowerExpr (expr: Tir.TExpr) : Hir.HExpr =
  match expr with
  | Tir.TLitExpr (lit, loc) -> Hir.HLitExpr(lit, loc)
  | Tir.TVarExpr (varSerial, ty, loc) -> Hir.HVarExpr(lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.TFunExpr (funSerial, ty, loc) -> Hir.HFunExpr(lowerFunSerial funSerial, lowerTy ty, [], loc)
  | Tir.TVariantExpr (variantSerial, ty, loc) -> Hir.HVariantExpr(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.TPrimExpr (prim, ty, loc) -> Hir.HPrimExpr(lowerPrim prim, lowerTy ty, loc)
  | Tir.TRecordExpr (exprOpt, fields, ty, loc) ->
    Hir.HRecordExpr(
      Option.map lowerExpr exprOpt,
      List.map (fun (ident, init, loc) -> ident, lowerExpr init, loc) fields,
      lowerTy ty,
      loc
    )
  | Tir.TMatchExpr (cond, arms, ty, loc) ->
    Hir.HMatchExpr(
      lowerExpr cond,
      List.map (fun (pat, guard, body) -> lowerPat pat, lowerExpr guard, lowerExpr body) arms,
      lowerTy ty,
      loc
    )
  | Tir.TNavExpr (l, r, ty, loc) -> Hir.HNavExpr(lowerExpr l, r, lowerTy ty, loc)
  | Tir.TNodeExpr (kind, args, ty, loc) -> Hir.HNodeExpr(lowerExprKind kind, List.map lowerExpr args, lowerTy ty, loc)
  | Tir.TBlockExpr (_, stmts, last) -> Hir.HBlockExpr(List.map lowerStmt stmts, lowerExpr last)

let private lowerStmt (stmt: Tir.TStmt) : Hir.HExpr =
  match stmt with
  | Tir.TExprStmt expr -> lowerExpr expr

  | Tir.TLetValStmt (pat, init, loc) -> Hir.HLetValExpr(lowerPat pat, lowerExpr init, Hir.hxUnit loc, Hir.tyUnit, loc)

  | Tir.TLetFunStmt (funSerial, isRec, vis, argPats, body, loc) ->
    Hir.HLetFunExpr(
      lowerFunSerial funSerial,
      isRec,
      List.map lowerPat argPats,
      lowerExpr body,
      Hir.hxUnit loc,
      Hir.tyUnit,
      loc
    )

  // These statements are removed. Already used in NameRes.
  | Tir.TTyDeclStmt _
  | Tir.TOpenStmt _
  | Tir.TModuleStmt _
  | Tir.TModuleSynonymStmt _ -> Hir.hxUnit (Tir.stmtToLoc stmt)

let private lowerModules (modules: Tir.TProgram) : Hir.HProgram =
  modules
  |> List.map (fun (p, m, stmts) -> p, m, List.map lowerStmt stmts)

let private lowerTyCtx (tyCtx: Typing.TyCtx) : Hir.TyCtx =
  { Serial = tyCtx.Serial

    Vars =
      tyCtx.Vars
      |> TMap.stableMap (fun serial def -> lowerVarSerial serial, lowerVarDef def) Hir.varSerialCompare

    Funs =
      tyCtx.Funs
      |> TMap.stableMap (fun serial def -> lowerFunSerial serial, lowerFunDef def) Hir.funSerialCompare

    Variants =
      tyCtx.Variants
      |> TMap.stableMap (fun serial def -> lowerVariantSerial serial, lowerVariantDef def) Hir.variantSerialCompare

    MainFunOpt = tyCtx.MainFunOpt |> Option.map lowerFunSerial

    Tys =
      tyCtx.Tys
      |> TMap.map (fun _ def -> lowerTyDef def) }

let lower (modules: Tir.TProgram, tyCtx: Typing.TyCtx) : Hir.HProgram * Hir.TyCtx =
  lowerModules modules, lowerTyCtx tyCtx
