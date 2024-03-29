/// # Lower
///
/// Conversion from TIR to HIR.
module rec MiloneCli.Lower

open MiloneShared.SharedTypes
open Std.StdError
open Std.StdMap

module Hir = MiloneTranslation.HirTypes
module Tir = MiloneSyntax.TirTypes

module private Hir =
  let hxUnit loc =
    Hir.HNodeExpr(Hir.HTupleEN, [], Hir.Ty(Hir.TupleTk, []), loc)

  let varSerialCompare (Hir.VarSerial l) (Hir.VarSerial r) = compare l r

  let funSerialCompare (Hir.FunSerial l) (Hir.FunSerial r) = compare l r

  let variantSerialCompare (Hir.VariantSerial l) (Hir.VariantSerial r) = compare l r

/// Converts a map by transforming key and value.
let private convertMap f compareFun (map: TreeMap<'K, 'T>) : TreeMap<'H, 'U> =
  map
  |> TMap.toList
  |> List.map f
  |> TMap.ofList compareFun

let private lowerTk (tk: Tir.Tk) : Hir.Tk =
  match tk with
  | Tir.IntTk intFlavor -> Hir.IntTk intFlavor
  | Tir.FloatTk floatFlavor -> Hir.FloatTk floatFlavor
  | Tir.BoolTk -> Hir.BoolTk
  | Tir.CharTk -> Hir.CharTk
  | Tir.StringTk -> Hir.StringTk
  | Tir.NeverTk -> Hir.NeverTk
  | Tir.ObjTk -> Hir.ObjTk

  | Tir.FunTk -> Hir.FunTk
  | Tir.TupleTk -> Hir.TupleTk
  | Tir.ListTk -> Hir.ListTk

  | Tir.VoidPtrTk isMut -> Hir.VoidPtrTk isMut
  | Tir.NativePtrTk mode -> Hir.NativePtrTk mode
  | Tir.FunPtrTk -> Hir.FunPtrTk
  | Tir.NativeTypeTk code -> Hir.NativeTypeTk code

  | Tir.MetaTk (serial, loc) -> Hir.MetaTk(serial, loc)
  | Tir.UnivTk (serial, info) -> Hir.MetaTk(serial, info.Loc)
  | Tir.UnionTk (serial, info) -> Hir.UnionTk(serial, info.Name)
  | Tir.RecordTk (serial, info) -> Hir.RecordTk(serial, info.Name)
  | Tir.OpaqueTk (serial, info) -> Hir.OpaqueTk(serial, info.Name)

  | Tir.ErrorTk _
  | Tir.SynonymTk _
  | Tir.InferTk _ // Resolved in Typing.

  | Tir.OwnTk -> unreachable () // Resolved in OwnershipCheck.

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
    Prefix = def.Prefix
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
  | Tir.RecordTyDef (ident, tyArgs, fields, repr, loc) ->
    Hir.RecordTyDef(ident, tyArgs, List.map (fun (ident, ty, loc) -> ident, lowerTy ty, loc) fields, repr, loc)
  | Tir.OpaqueTyDef (ident, loc) -> Hir.OpaqueTyDef(ident, loc)

  | Tir.UnivTyDef _
  | Tir.SynonymTyDef _ -> unreachable () // Resolved in Typing.

let private lowerVarMap vars =
  vars
  |> convertMap (fun (serial, def) -> lowerVarSerial serial, lowerVarDef def) Hir.varSerialCompare

let private lowerPrim (prim: Tir.TPrim) : Hir.HPrim =
  match prim with
  | Tir.TPrim.Not -> Hir.HPrim.Not
  | Tir.TPrim.BitNot -> Hir.HPrim.BitNot
  | Tir.TPrim.Add -> Hir.HPrim.Add
  | Tir.TPrim.Subtract -> Hir.HPrim.Subtract
  | Tir.TPrim.Multiply -> Hir.HPrim.Multiply
  | Tir.TPrim.Divide -> Hir.HPrim.Divide
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
  | Tir.TPrim.ToChar -> Hir.HPrim.ToChar
  | Tir.TPrim.ToString -> Hir.HPrim.ToString
  | Tir.TPrim.Box -> Hir.HPrim.Box
  | Tir.TPrim.Unbox -> Hir.HPrim.Unbox
  | Tir.TPrim.StringLength -> Hir.HPrim.StringLength
  | Tir.TPrim.Nil -> Hir.HPrim.Nil
  | Tir.TPrim.Cons -> Hir.HPrim.Cons
  | Tir.TPrim.Assert -> Hir.HPrim.Assert
  | Tir.TPrim.Printfn -> Hir.HPrim.Printfn
  | Tir.TPrim.PtrCast
  | Tir.TPrim.PtrInvalid
  | Tir.TPrim.PtrAsIn
  | Tir.TPrim.PtrAsNative
  | Tir.TPrim.NativeCast -> Hir.HPrim.NativeCast
  | Tir.TPrim.NullPtr -> Hir.HPrim.NullPtr
  | Tir.TPrim.PtrDistance -> Hir.HPrim.PtrDistance

  | Tir.TPrim.Discriminant
  | Tir.TPrim.OwnAcquire
  | Tir.TPrim.OwnRelease
  | Tir.TPrim.PtrSelect
  | Tir.TPrim.PtrRead
  | Tir.TPrim.PtrWrite
  | Tir.TPrim.FunPtrInvoke
  | Tir.TPrim.NativeFun
  | Tir.TPrim.NativeExpr
  | Tir.TPrim.NativeStmt
  | Tir.TPrim.NativeDecl -> unreachable () // Resolved in Typing.

let private lowerPatKind (kind: Tir.TPatKind) : Hir.HPatKind =
  match kind with
  | Tir.TNilPN -> Hir.HNilPN
  | Tir.TConsPN -> Hir.HConsPN
  | Tir.TVariantAppPN serial -> Hir.HVariantAppPN(lowerVariantSerial serial)
  | Tir.TTuplePN -> Hir.HTuplePN

  | Tir.TNavPN _ -> unreachable () // Resolved in NameRes.
  | Tir.TAscribePN -> unreachable () // Resolved in Typing.
  | Tir.TAbortPN -> unreachable () // Compile error occurred.

let private lowerExprKind (kind: Tir.TExprKind) : Hir.HExprKind =
  match kind with
  | Tir.TMinusEN -> Hir.HMinusEN
  | Tir.TPtrOfEN -> Hir.HPtrOfEN
  | Tir.TFunPtrOfEN -> Hir.HFunPtrOfEN
  | Tir.TAppEN -> Hir.HAppEN
  | Tir.TIndexEN -> Hir.HIndexEN
  | Tir.TSliceEN -> Hir.HSliceEN
  | Tir.TCatchNeverEN -> Hir.HCatchNeverEN
  | Tir.TDiscriminantEN variantSerial -> Hir.HDiscriminantEN(lowerVariantSerial variantSerial)
  | Tir.TCallNativeEN funName -> Hir.HCallNativeEN funName
  | Tir.TTupleEN -> Hir.HTupleEN
  | Tir.TPtrOffsetEN -> Hir.HPtrOffsetEN
  | Tir.TPtrReadEN -> Hir.HPtrReadEN
  | Tir.TPtrWriteEN -> Hir.HPtrWriteEN
  | Tir.TFunPtrInvokeEN -> Hir.HFunPtrInvokeEN

  | Tir.TNativeExprEN code -> Hir.HNativeExprEN code
  | Tir.TNativeStmtEN code -> Hir.HNativeStmtEN code
  | Tir.TNativeDeclEN code -> Hir.HNativeDeclEN code
  | Tir.TSizeOfEN -> Hir.HSizeOfEN
  | Tir.TTyPlaceholderEN -> Hir.HTyPlaceholderEN

  | Tir.TAbortEN -> unreachable () // Compile error occurred.
  | Tir.TAscribeEN -> unreachable () // Resolved in Typing.

let private lowerPat (pat: Tir.TPat) : Hir.HPat =
  match pat with
  | Tir.TLitPat (lit, loc) -> Hir.HLitPat(lit, loc)
  | Tir.TDiscardPat (ty, loc) -> Hir.HDiscardPat(lowerTy ty, loc)
  | Tir.TVarPat (_, varSerial, ty, loc) -> Hir.HVarPat(lowerVarSerial varSerial, lowerTy ty, loc)
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
  | Tir.TNavExpr (l, (r, _), ty, loc) -> Hir.HNavExpr(lowerExpr l, r, lowerTy ty, loc)
  | Tir.TNodeExpr (kind, args, ty, loc) -> Hir.HNodeExpr(lowerExprKind kind, List.map lowerExpr args, lowerTy ty, loc)
  | Tir.TBlockExpr (stmts, last) -> Hir.HBlockExpr(List.map lowerStmt stmts, lowerExpr last)

let private lowerStmt (stmt: Tir.TStmt) : Hir.HStmt =
  match stmt with
  | Tir.TExprStmt expr -> Hir.HExprStmt(lowerExpr expr)

  | Tir.TLetValStmt (pat, init, loc) -> Hir.HLetValStmt(lowerPat pat, lowerExpr init, loc)

  | Tir.TLetFunStmt f ->
    Hir.HLetFunStmt(lowerFunSerial f.FunSerial, List.map lowerPat f.Params, lowerExpr f.Body, f.Loc)

  // note: if flatten all blocks, compile fails (invalid code generated). Does them need being nested or wrapped by HExprStmt?
  | Tir.TBlockStmt (_, stmts) ->
    let stmts = stmts |> List.map lowerStmt

    Hir.HBlockExpr(stmts, Hir.hxUnit noLoc)
    |> Hir.HExprStmt

let private lowerModules (modules: Tir.TProgram) : Hir.HProgram =
  modules
  |> List.map (fun (m: Tir.TModule) ->
    let m: Hir.HModule =
      { DocId = m.DocId
        Vars = lowerVarMap m.Vars
        IsExecutable = m.IsExecutable
        MainFunOpt = m.MainFunOpt |> Option.map lowerFunSerial
        Stmts = List.map lowerStmt m.Stmts }

    m)

let private lowerTirCtx (ctx: Tir.TirCtx) : Hir.HirCtx =
  { Serial = ctx.Serial

    StaticVars = lowerVarMap ctx.StaticVars

    Funs =
      ctx.Funs
      |> convertMap (fun (serial, def) -> lowerFunSerial serial, lowerFunDef def) Hir.funSerialCompare

    Variants =
      ctx.Variants
      |> convertMap (fun (serial, def) -> lowerVariantSerial serial, lowerVariantDef def) Hir.variantSerialCompare

    Tys = ctx.Tys |> TMap.map (fun _ def -> lowerTyDef def) }

let lower (modules: Tir.TProgram, ctx: Tir.TirCtx) : Hir.HProgram * Hir.HirCtx = lowerModules modules, lowerTirCtx ctx
