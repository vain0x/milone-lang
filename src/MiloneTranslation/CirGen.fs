/// # CirGen
///
/// Converts MIR to CIR.
///
/// Milone-lang's primitives are converted to corresponding C's operator
/// or function all defined in runtime.
/// See `libmilonert` for runtime codes.
///
/// Milone-lang's types are converted to
/// C-style struct/union types.
module rec MiloneTranslation.CirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open Std.StdError
open Std.StdMap
open Std.StdMultimap
open Std.StdSet
open MiloneTranslation.Cir
open MiloneTranslation.Hir
open MiloneTranslation.Mir
open MiloneTranslation.MirGen
open MiloneTranslation.HirTypes

module S = Std.StdString

let private tupleField (i: int) = "t" + string i

/// Calculates discriminant type's name of union type.
let private toDiscriminantEnumName (name: string) = name + "Discriminant"

let private cInt32Ty = CIntTy I32
let private cVoidPtrTy = CPtrTy CVoidTy
let private cVoidConstPtrTy = CConstPtrTy CVoidTy
let private cNullExpr = CVarExpr "NULL"

let private cTyEncode ty =
  match ty with
  | CVoidTy -> 1
  | CIntTy _ -> 2
  | CFloatTy _ -> 3
  | CBoolTy -> 4
  | CCharTy -> 5
  | CPtrTy _ -> 11
  | CConstPtrTy _ -> 12
  | CStructTy _ -> 21
  | CEnumTy _ -> 22
  | CEmbedTy _ -> 31

let private cTyCompare l r =
  match l, r with
  | CIntTy lFlavor, CIntTy rFlavor -> intFlavorCompare lFlavor rFlavor
  | CFloatTy lFlavor, CFloatTy rFlavor -> floatFlavorCompare lFlavor rFlavor

  | CPtrTy lTy, CPtrTy rTy -> cTyCompare lTy rTy
  | CConstPtrTy lTy, CConstPtrTy rTy -> cTyCompare lTy rTy

  | CStructTy l, CStructTy r -> compare l r
  | CEnumTy l, CEnumTy r -> compare l r
  | CEmbedTy l, CEmbedTy r -> compare l r

  | _ -> compare (cTyEncode l) (cTyEncode r)

let private cTyToIdent ty =
  match ty with
  | CVoidTy -> "Void"
  | CIntTy flavor -> cIntegerTyPascalName flavor
  | CFloatTy flavor -> cFloatTyPascalName flavor
  | CBoolTy -> "Bool"
  | CCharTy -> "Char"
  | CPtrTy uTy -> cTyToIdent uTy + "MutPtr"
  | CConstPtrTy uTy -> cTyToIdent uTy + "ConstPtr"
  | CStructTy name -> name
  | CEnumTy name -> name
  | CEmbedTy embed -> embed // should sanitize

// -----------------------------------------------
// Renaming idents
// -----------------------------------------------

/// Frequencies. Mapping from key to multiplicity. (Multi-set.)
type private Freq<'K> = TreeMap<'K, int>

let private freqEmpty compareFun : Freq<_> = TMap.empty compareFun

let private freqAdd key map : int * Freq<_> =
  let i =
    map |> TMap.tryFind key |> Option.defaultValue 0

  let map = map |> TMap.add key (i + 1)
  i, map

/// Computes renamed ident for the index-th occurrence of the same ident.
let private renameIdent (ident: Ident) (index: int) : Ident =
  if index = 0 then
    if ident |> S.contains "_" then
      ident
    else
      ident + "_"
  else
    ident + "_" + string index

let private renameIdents toIdent toKey mapFuns (defMap: TreeMap<_, _>) =
  let rename (ident: string) (index: int) =
    if index = 0 then
      if ident |> S.contains "_" then
        ident
      else
        ident + "_"
    else
      ident + "_" + string index

  // Group serials by ident.
  let serialsMap =
    let folder acc serial def =
      let ident = toIdent def
      acc |> Multimap.add ident (serial, def)

    defMap |> TMap.fold folder (TMap.empty compare)

  let addIdent ident (identMap, index) serial =
    identMap
    |> TMap.add (toKey serial) (rename ident index),
    index + 1

  let addIdents identMap ident serials =
    serials
    |> List.rev
    |> List.fold (addIdent ident) (identMap, 0)
    |> fst

  serialsMap
  |> TMap.fold addIdents (TMap.empty mapFuns)

let private renameIdents2
  (defMap: TreeMap<_, 'T>)
  (toIdent: 'T -> bool * string)
  (nameMap: TreeMap<'K, Ident>)
  (freq: Freq<Ident>)
  : TreeMap<'K, Ident> * Freq<Ident> =
  defMap
  |> TMap.fold
       (fun (nameMap, freq) key (value: 'T) ->
         let allowRename, name = toIdent value

         if allowRename then
           let i, freq = freq |> freqAdd name
           let name = renameIdent name i
           let nameMap = nameMap |> TMap.add key name

           nameMap, freq
         else
           assert (freq |> TMap.containsKey name |> not)
           let nameMap = nameMap |> TMap.add key name
           nameMap, freq)
       (nameMap, freq)

let private linkageToIdent rawName linkage =
  match linkage with
  | InternalLinkage -> true, rawName
  | ExternalLinkage name -> false, name

let private varDefToName (varDef: VarDef) =
  linkageToIdent varDef.Name varDef.Linkage

let private funDefToName (df: DocIdToModulePath) (funDef: FunDef) =
  match funDef.Linkage with
  | InternalLinkage ->
    let name =
      let doc =
        match funDef.Loc |> Loc.docId |> df with
        | Some (p, m) -> p + "_" + m
        | None ->
          // #abusingDocId
          // This can happen e.g. Derive generates non-file documents.
          funDef.Loc
          |> Loc.docId
          |> Symbol.toString
          |> S.replace "." "_"

      doc
      + "_"
      + (funDef.Name :: funDef.Prefix
         |> List.rev
         |> S.concat "_")

    true, name

  | ExternalLinkage name -> false, name

// -----------------------------------------------
// Rx
// -----------------------------------------------

/// Read-only context of the pass.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Rx =
  { StaticVars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>
    EntrypointName: string

    ValueNameFreq: TreeMap<Ident, int>
    VarUniqueNames: TreeMap<VarSerial, Ident>
    FunUniqueNames: TreeMap<FunSerial, Ident>
    VariantUniqueNames: TreeMap<VariantSerial, Ident>

    /// Doc ID of current module.
    DocIdOpt: DocId option
    /// Main function of current module.
    MainFunOpt: FunSerial option

    DocIdToModulePath: DocIdToModulePath }

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CirCtx =
  { Rx: Rx

    TyEnv: TreeMap<Ty, CTyInstance * CTy>
    TyUniqueNames: TreeMap<Ty, Ident>
    Stmts: CStmt list
    Decls: CDecl list

    /// Already-declared functions.
    FunDecls: TreeSet<FunSerial>

    /// Nominalized fun pointer types.
    FunPtrTys: TreeMap<CTy list * CTy, string>

    /// Gets if current function is never-returning
    IsNoReturn: bool }

let private ofMirResult entrypointName (df: DocIdToModulePath) (mirCtx: MirResult) : CirCtx =
  let freq = freqEmpty compare

  let varUniqueNames, freq =
    renameIdents2 mirCtx.StaticVars varDefToName (TMap.empty varSerialCompare) freq

  let funUniqueNames, freq =
    renameIdents2 mirCtx.Funs (funDefToName df) (TMap.empty funSerialCompare) freq

  let variantUniqueNames, freq =
    renameIdents2
      mirCtx.Variants
      (fun (variantDef: VariantDef) ->
        let unionIdent =
          match mirCtx.Tys |> mapFind variantDef.UnionTySerial with
          | UnionTyDef (ident, _, _, _) -> ident
          | _ -> unreachable ()

        true, unionIdent + "_" + variantDef.Name)
      (TMap.empty variantSerialCompare)
      freq

  let tyNames =
    let toKey (serial, tyDef) =
      match tyDef with
      | UnionTyDef (ident, _, _, _) -> tyUnion serial ident []
      | RecordTyDef (ident, _, _, _, _) -> tyRecord serial ident []
      | OpaqueTyDef (ident, _) -> Ty(OpaqueTk(serial, ident), [])

    mirCtx.Tys
    |> renameIdents tyDefToName toKey tyCompare

  let rx: Rx =
    { StaticVars = mirCtx.StaticVars
      Funs = mirCtx.Funs
      Variants = mirCtx.Variants
      Tys = mirCtx.Tys
      MainFunOpt = None
      EntrypointName = entrypointName

      ValueNameFreq = freq
      VarUniqueNames = varUniqueNames
      FunUniqueNames = funUniqueNames
      VariantUniqueNames = variantUniqueNames
      DocIdOpt = None
      DocIdToModulePath = df }

  { Rx = rx
    TyEnv = TMap.empty tyCompare
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []
    FunDecls = TSet.empty funSerialCompare
    FunPtrTys = TMap.empty (pairCompare (listCompare cTyCompare) cTyCompare)
    IsNoReturn = false }

let private currentDocId (ctx: CirCtx) : DocId =
  match ctx.Rx.DocIdOpt with
  | Some it -> it
  | None -> unreachable () // Must be filled before starting work.

let private isMainFun (ctx: CirCtx) funSerial =
  match ctx.Rx.MainFunOpt with
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
  | _ -> false

let private getUnionTyOfVariant (ctx: CirCtx) variantSerial =
  let variantDef = ctx.Rx.Variants |> mapFind variantSerial

  let unionTyName =
    match ctx.Rx.Tys |> mapFind variantDef.UnionTySerial with
    | UnionTyDef(ident, _, _, _) -> ident
    | _ -> unreachable ()

  tyUnion variantDef.UnionTySerial unionTyName []

let private enterBlock (ctx: CirCtx) = { ctx with Stmts = [] }

let private rollback (bCtx: CirCtx) (dCtx: CirCtx) = { dCtx with Stmts = bCtx.Stmts }

let private addStmt (ctx: CirCtx) stmt = { ctx with Stmts = stmt :: ctx.Stmts }

let private addDecl (ctx: CirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

// -----------------------------------------------
// Type definition generation
// -----------------------------------------------

let private cgArgTys ctx argTys : CTy list * CirCtx =
  argTys
  |> List.filter (fun ty -> tyIsUnit ty |> not)
  |> List.mapFold cgTyComplete ctx

let private cgResultTy ctx resultTy : CTy * CirCtx =
  if tyIsUnit resultTy || tyIsNever resultTy then
    CVoidTy, ctx
  else
    cgTyComplete ctx resultTy

let private cgFunPtrTy (ctx: CirCtx) argTys resultTy : CTy * CirCtx =
  match ctx.FunPtrTys |> TMap.tryFind (argTys, resultTy) with
  | Some it -> CEmbedTy it, ctx

  | None ->
    let arity = argTys |> List.length |> string

    let ident =
      List.append
        (argTys |> List.map cTyToIdent)
        [ resultTy |> cTyToIdent
          "FunPtr"
          arity ]
      |> S.concat ""

    let ctx =
      { ctx with FunPtrTys = ctx.FunPtrTys |> TMap.add (argTys, resultTy) ident }

    let ctx =
      addDecl ctx (CFunPtrTyDef(ident, argTys, resultTy))

    CEmbedTy ident, ctx

let private genIncompleteFunTyDecl (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy

  match ctx.TyEnv |> TMap.tryFind funTy with
  | Some (_, ty) -> ty, ctx

  | None ->
    let structName, (ctx: CirCtx) = getUniqueTyName ctx funTy
    let funStructTy = CStructTy structName

    let ctx =
      { ctx with
          TyEnv =
            ctx.TyEnv
            |> TMap.add funTy (CTyDeclared, funStructTy) }

    funStructTy, ctx

let private genFunTyDef (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy

  match ctx.TyEnv |> TMap.tryFind funTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let structName, ctx = getUniqueTyName ctx funTy
    let selfTy, ctx = genIncompleteFunTyDecl ctx sTy tTy

    let envTy = CConstPtrTy CVoidTy

    let funPtrTy, ctx =
      let _, argTys, resultTy = tyToArgList funTy
      let argTys, ctx = cgArgTys ctx argTys
      let resultTy, ctx = cgResultTy ctx resultTy
      cgFunPtrTy ctx (envTy :: argTys) resultTy

    let fields = [ "fun", funPtrTy; "env", envTy ]

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add funTy (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteListTyDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy

  match ctx.TyEnv |> TMap.tryFind listTy with
  | Some (_, ty) -> ty, ctx

  | None ->
    let itemTyName, ctx = getUniqueTyName ctx itemTy
    let structName = itemTyName + "Cons"
    let selfTy = CConstPtrTy(CStructTy structName)

    let ctx =
      { ctx with
          Decls = CStructForwardDecl structName :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add listTy (CTyDeclared, selfTy) }

    selfTy, ctx

let private genListTyDef (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy

  match ctx.TyEnv |> TMap.tryFind listTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let itemTyName, ctx = getUniqueTyName ctx itemTy
    let structName = itemTyName + "Cons"
    let selfTy, ctx = genIncompleteListTyDecl ctx itemTy

    let itemTy, (ctx: CirCtx) = cgTyComplete ctx itemTy
    let fields = [ "head", itemTy; "tail", selfTy ]

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add listTy (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteUnionTyDecl (ctx: CirCtx) tySerial name =
  let unionTyRef = tyUnion tySerial name []

  match ctx.TyEnv |> TMap.tryFind unionTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
    let structName, ctx = getUniqueTyName ctx unionTyRef
    let selfTy = CStructTy structName

    let ctx =
      { ctx with
          TyEnv =
            ctx.TyEnv
            |> TMap.add unionTyRef (CTyDeclared, selfTy) }

    selfTy, ctx

let private genUnionTyDef (ctx: CirCtx) tySerial name variants =
  let unionTyRef = tyUnion tySerial name []

  match ctx.TyEnv |> TMap.tryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let structName, ctx = getUniqueTyName ctx unionTyRef
    let selfTy, ctx = genIncompleteUnionTyDecl ctx tySerial name

    let discriminantEnumName = toDiscriminantEnumName structName
    let discriminantTy = CEnumTy discriminantEnumName

    let variants =
      variants
      |> List.map (fun variantSerial ->
        let v = ctx.Rx.Variants |> mapFind variantSerial
        v.Name, variantSerial, v.HasPayload, v.PayloadTy)

    let discriminants =
      variants
      |> List.map (fun (_, serial, _, _) -> getUniqueVariantName ctx serial)

    let variants, ctx =
      variants
      |> List.filter (fun (_, _, hasPayload, _) -> hasPayload)
      |> List.mapFold
           (fun ctx (_, serial, _, payloadTy) ->
             let payloadTy, ctx = cgTyComplete ctx payloadTy
             let name = getUniqueVariantName ctx serial
             (name, payloadTy), ctx)
           ctx

    let discriminantEnumDecl =
      CEnumDecl(discriminantEnumName, discriminants)

    let structDecl =
      CStructDecl(structName, [ "discriminant", discriminantTy ], variants)

    let ctx =
      { ctx with
          Decls = structDecl :: discriminantEnumDecl :: ctx.Decls
          TyEnv =
            ctx.TyEnv
            |> TMap.add unionTyRef (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteRecordTyDecl (ctx: CirCtx) tySerial name =
  let recordTyRef = tyRecord tySerial name []

  match ctx.TyEnv |> TMap.tryFind recordTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
    let structName, ctx = getUniqueTyName ctx recordTyRef
    let selfTy = CStructTy structName

    let ctx =
      { ctx with
          TyEnv =
            ctx.TyEnv
            |> TMap.add recordTyRef (CTyDeclared, selfTy) }

    selfTy, ctx

let private genOpaqueTyDecl (ctx: CirCtx) tySerial name =
  let opaqueTyRef = Ty(OpaqueTk(tySerial, name), [])

  match ctx.TyEnv |> TMap.tryFind opaqueTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
    let name =
      match ctx.Rx.Tys |> mapFind tySerial with
      | OpaqueTyDef (name, _) -> name
      | _ -> unreachable ()

    let selfTy = CStructTy name

    let ctx =
      { ctx with
          Decls = CStructForwardDecl name :: ctx.Decls
          TyEnv =
            ctx.TyEnv
            |> TMap.add opaqueTyRef (CTyDeclared, selfTy) }

    selfTy, ctx

let private genRecordTyDef ctx tySerial name fields =
  let recordTyRef = tyRecord tySerial name []
  let structName, ctx = getUniqueTyName ctx recordTyRef
  let selfTy, ctx = genIncompleteRecordTyDecl ctx tySerial name

  match ctx.TyEnv |> TMap.tryFind recordTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let fieldTys, (ctx: CirCtx) =
      fields
      |> List.map (fun (_, ty, _) -> ty)
      |> List.mapFold cgTyComplete ctx

    let fields =
      fieldTys
      |> List.mapi (fun i ty -> tupleField i, ty)

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv =
            ctx.TyEnv
            |> TMap.add recordTyRef (CTyDefined, selfTy) }

    selfTy, ctx

// -----------------------------------------------
// Naming
// -----------------------------------------------

let private getUniqueVarName (ctx: CirCtx) varSerial =
  ctx.Rx.VarUniqueNames |> mapFind varSerial

let private getUniqueFunName (ctx: CirCtx) funSerial =
  ctx.Rx.FunUniqueNames |> mapFind funSerial

let private getUniqueVariantName (ctx: CirCtx) variantSerial =
  ctx.Rx.VariantUniqueNames |> mapFind variantSerial

let private getUniqueTyName (ctx: CirCtx) ty : _ * CirCtx =
  let memo = ctx.TyUniqueNames
  let name, memo = tyMangle (ty, memo)
  name, { ctx with TyUniqueNames = memo }

let private cgNativePtrTy ctx mode itemTy =
  let itemTy, ctx = cgTyIncomplete ctx itemTy

  match mode with
  | RefMode.ReadWrite
  | RefMode.WriteOnly -> CPtrTy itemTy, ctx
  | RefMode.ReadOnly -> CConstPtrTy itemTy, ctx

let private cgNativeFunTy ctx tys =
  match splitLast tys with
  | None -> unreachable ()
  | Some (argTys, resultTy) ->
    let argTys, ctx = cgArgTys ctx argTys
    let resultTy, ctx = cgResultTy ctx resultTy
    cgFunPtrTy ctx argTys resultTy

/// Converts a type to incomplete type.
/// whose type definition is not necessary to be visible.
let private cgTyIncomplete (ctx: CirCtx) (ty: Ty) : CTy * CirCtx =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | IntTk flavor, _ -> CIntTy flavor, ctx
  | FloatTk flavor, _ -> CFloatTy flavor, ctx
  | BoolTk, _ -> CBoolTy, ctx
  | CharTk, _ -> CCharTy, ctx
  | StringTk, _ -> CStructTy "String", ctx
  | ObjTk, _ -> CConstPtrTy CVoidTy, ctx

  | FunTk, [ sTy; tTy ] -> genIncompleteFunTyDecl ctx sTy tTy
  | FunTk, _ -> unreachable ()

  | NeverTk, _
  | TupleTk, [] -> CCharTy, ctx
  | TupleTk, _ -> unreachable () // Non-unit TupleTk is resolved in MonoTy.

  | ListTk, [ itemTy ] -> genIncompleteListTyDecl ctx itemTy
  | ListTk, _ -> unreachable ()

  | VoidPtrTk IsMut, _ -> cVoidPtrTy, ctx
  | VoidPtrTk IsConst, _ -> cVoidConstPtrTy, ctx
  | NativePtrTk mode, [ itemTy ] -> cgNativePtrTy ctx mode itemTy
  | NativePtrTk _, _ -> unreachable ()
  | FunPtrTk, _ -> cgNativeFunTy ctx tyArgs
  | NativeTypeTk code, _ -> CEmbedTy code, ctx

  | UnionTk(tySerial, name), _ -> genIncompleteUnionTyDecl ctx tySerial name
  | RecordTk(tySerial, name), _ -> genIncompleteRecordTyDecl ctx tySerial name
  | OpaqueTk(tySerial, name), _ -> genOpaqueTyDecl ctx tySerial name

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

/// Converts a type to complete C type.
///
/// A type is complete if its definition is visible.
let private cgTyComplete (ctx: CirCtx) (ty: Ty) : CTy * CirCtx =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | IntTk flavor, _ -> CIntTy flavor, ctx
  | FloatTk flavor, _ -> CFloatTy flavor, ctx
  | BoolTk, _ -> CBoolTy, ctx
  | CharTk, _ -> CCharTy, ctx
  | StringTk, _ -> CStructTy "String", ctx
  | ObjTk, _ -> CConstPtrTy CVoidTy, ctx

  | FunTk, [ sTy; tTy ] -> genFunTyDef ctx sTy tTy
  | FunTk, _ -> unreachable ()

  | NeverTk, _
  | TupleTk, [] -> CCharTy, ctx
  | TupleTk, _ -> unreachable () // Non-unit TupleTk is resolved in MonoTy.

  | ListTk, [ itemTy ] ->
    // Complete definition of the underlying struct type is unnecessary yet
    // since the struct is hold over pointer.
    genIncompleteListTyDecl ctx itemTy
  | ListTk, _ -> unreachable ()

  | VoidPtrTk IsMut, _ -> cVoidPtrTy, ctx
  | VoidPtrTk IsConst, _ -> cVoidConstPtrTy, ctx

  | NativePtrTk mode, [ itemTy ] -> cgNativePtrTy ctx mode itemTy
  | NativePtrTk _, _ -> unreachable ()

  | FunPtrTk, _ -> cgNativeFunTy ctx tyArgs
  | NativeTypeTk code, _ -> CEmbedTy code, ctx

  | UnionTk(serial, name), _ ->
    match ctx.Rx.Tys |> TMap.tryFind serial with
    | Some (UnionTyDef (_, _, variants, _)) -> genUnionTyDef ctx serial name variants

    | _ -> unreachable () // Union type undefined?

  | RecordTk(serial, name), _ ->
    match ctx.Rx.Tys |> TMap.tryFind serial with
    | Some (RecordTyDef (_, _, fields, _, _)) -> genRecordTyDef ctx serial name fields

    | _ -> unreachable () // Record type undefined?

  | OpaqueTk(serial, name), _ -> genOpaqueTyDecl ctx serial name

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

// -----------------------------------------------
// Extern decl
// -----------------------------------------------

let private cgExternFunDecl (ctx: CirCtx) funSerial =
  if TSet.contains funSerial ctx.FunDecls then
    ctx
  else
    let funDef = ctx.Rx.Funs |> mapFind funSerial
    let (Loc (docId, _, _)) = funDef.Loc

    if Symbol.equals docId (currentDocId ctx) then
      ctx
    else
      let (TyScheme (_, ty)) = funDef.Ty

      let argTys, resultTy =
        let rec go arity ty =
          if arity = 0 then
            [], ty
          else
            match ty with
            | Ty (FunTk, [ sTy; tTy ]) ->
              let argTys, resultTy = go (arity - 1) tTy
              sTy :: argTys, resultTy

            | _ -> unreachable (ty, arity)

        go funDef.Arity ty

      let name = getUniqueFunName ctx funSerial
      let argTys, ctx = cgArgTys ctx argTys
      let isNoReturn = tyIsNever resultTy
      let resultTy, ctx = cgResultTy ctx resultTy

      let ctx: CirCtx =
        addDecl ctx (CFunForwardDecl(name, argTys, resultTy, isNoReturn))

      { ctx with FunDecls = TSet.add funSerial ctx.FunDecls }

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private cBinaryOf op =
  match op with
  | MMultiplyBinary -> CMultiplyBinary
  | MDivideBinary -> CDivideBinary
  | MModuloBinary -> CModuloBinary
  | MAddBinary -> CAddBinary
  | MSubtractBinary -> CSubtractBinary

  | MBitAndBinary -> CBitAndBinary
  | MBitOrBinary -> CBitOrBinary
  | MBitXorBinary -> CBitXorBinary
  | MLeftShiftBinary -> CLeftShiftBinary
  | MRightShiftBinary -> CRightShiftBinary

  | MEqualBinary -> CEqualBinary
  | MNotEqualBinary -> CNotEqualBinary
  | MLessBinary -> CLessBinary
  | MGreaterEqualBinary -> CGreaterEqualBinary

  | MInt32CompareBinary
  | MInt64CompareBinary
  | MUInt64CompareBinary
  | MStringAddBinary
  | MStringCompareBinary
  | MStringIndexBinary
  | MPtrAddBinary -> unreachable ()

let private genLit lit =
  match lit with
  | IntLit text -> CIntExpr(text, I32)
  | IntLitWithFlavor (text, flavor) -> CIntExpr(text, flavor)
  | FloatLit text -> CDoubleExpr text
  | BoolLit false -> CVarExpr "false"
  | BoolLit true -> CVarExpr "true"
  | CharLit value -> CCharExpr value
  | ByteLit value -> CCastExpr(CCharExpr (char value), CIntTy U8)
  | StringLit value -> CStringInitExpr value

let private genDiscriminant ctx variantSerial =
  CVarExpr(getUniqueVariantName ctx variantSerial)

let private cgConst ctx mConst =
  match mConst with
  | MLitConst lit -> genLit lit
  | MDiscriminantConst variantSerial -> genDiscriminant ctx variantSerial

let private genVariantNameExpr ctx serial =
  let ty = getUnionTyOfVariant ctx serial
  let ty, ctx = cgTyComplete ctx ty

  let discriminant =
    CVarExpr(getUniqueVariantName ctx serial)

  CInitExpr([ "discriminant", discriminant ], ty), ctx

let private genGenericValue ctx genericValue ty =
  match genericValue with
  | MNilGv -> cNullExpr, ctx

  | MNullPtrGv ->
    match ty with
    | Ty (VoidPtrTk _, _) -> cNullExpr, ctx

    | _ ->
      let ty, ctx = cgTyIncomplete ctx ty
      CCastExpr(cNullExpr, ty), ctx

  | MSizeOfGv ->
    let ty, ctx = cgTyComplete ctx ty
    CSizeOfExpr ty, ctx

  | MTyPlaceholderGv ->
    let ty, ctx = cgTyComplete ctx ty
    CTyPlaceholderExpr ty, ctx

/// Converts a binary expression to a runtime function call.
let private genBinaryExprAsCall ctx funName l r =
  let l, ctx = cgExpr ctx l
  let r, ctx = cgExpr ctx r
  let callExpr = CCallExpr(CVarExpr funName, [ l; r ])
  callExpr, ctx

let private genUnaryExpr ctx op arg =
  let arg, ctx = cgExpr ctx arg

  match op with
  | MMinusUnary -> CUnaryExpr(CMinusUnary, arg), ctx
  | MBitNotUnary -> CUnaryExpr(CBitNotUnary, arg), ctx
  | MNotUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MPtrOfUnary -> CUnaryExpr(CAddressOfUnary, arg), ctx
  | MIntOfScalarUnary flavor -> CCastExpr(arg, CIntTy flavor), ctx
  | MFloatOfScalarUnary flavor -> CCastExpr(arg, CFloatTy flavor), ctx
  | MCharOfScalarUnary -> CCastExpr(arg, CCharTy), ctx
  | MStringAsPtrUnary -> CDotExpr(arg, "ptr"), ctx
  | MStringLengthUnary -> CCastExpr(CDotExpr(arg, "len"), cInt32Ty), ctx

  | MUnboxUnary itemTy ->
    let itemTy, ctx = cgTyComplete ctx itemTy

    let deref =
      CUnaryExpr(CDerefUnary, CCastExpr(arg, CConstPtrTy itemTy))

    deref, ctx

  | MTupleItemUnary (index, tupleTy) ->
    let _, ctx = cgTyComplete ctx tupleTy
    CDotExpr(arg, tupleField index), ctx

  | MGetDiscriminantUnary unionTy ->
    let _, ctx = cgTyComplete ctx unionTy
    CDotExpr(arg, "discriminant"), ctx

  | MGetVariantUnary variantSerial ->
    let _, ctx =
      let unionTy = getUnionTyOfVariant ctx variantSerial
      cgTyComplete ctx unionTy

    CDotExpr(arg, getUniqueVariantName ctx variantSerial), ctx

  | MRecordItemUnary (index, recordTy) ->
    let _, ctx = cgTyComplete ctx recordTy
    CDotExpr(arg, tupleField index), ctx

  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx

  | MListHeadUnary itemTy ->
    let _, ctx = genListTyDef ctx itemTy
    CArrowExpr(arg, "head"), ctx

  | MListTailUnary itemTy ->
    let _, ctx = genListTyDef ctx itemTy
    CArrowExpr(arg, "tail"), ctx

  | MDerefUnary itemTy ->
    let _, ctx = cgTyComplete ctx itemTy
    CUnaryExpr(CDerefUnary, arg), ctx

  | MNativeCastUnary targetTy ->
    let ty, ctx = cgTyComplete ctx targetTy
    CCastExpr(arg, ty), ctx

let private genExprBin ctx op l r =
  match op with
  | MInt32CompareBinary -> genBinaryExprAsCall ctx "milone_int32_compare" l r
  | MInt64CompareBinary -> genBinaryExprAsCall ctx "milone_int64_compare" l r
  | MUInt64CompareBinary -> genBinaryExprAsCall ctx "milone_uint64_compare" l r

  | MStringAddBinary -> genBinaryExprAsCall ctx "string_add" l r
  | MStringCompareBinary -> genBinaryExprAsCall ctx "string_compare" l r
  | MStringIndexBinary ->
    let l, ctx = cgExpr ctx l
    let r, ctx = cgExpr ctx r
    CIndexExpr(CDotExpr(l, "ptr"), r), ctx

  | MPtrAddBinary ->
    let l, ctx = cgExpr ctx l
    let r, ctx = cgExpr ctx r
    CUnaryExpr(CAddressOfUnary, CIndexExpr(l, r)), ctx

  | _ ->
    let l, ctx = cgExpr ctx l
    let r, ctx = cgExpr ctx r
    let opExpr = CBinaryExpr(cBinaryOf op, l, r)
    opExpr, ctx

let private cgExpr (ctx: CirCtx) (arg: MExpr) : CExpr * CirCtx =
  match arg |> mxSugar with
  | MLitExpr (lit, _) -> genLit lit, ctx
  | MUnitExpr _ -> CVarExpr "0", ctx
  | MNeverExpr loc -> unreachable ("MNeverExpr " + Loc.toString loc)

  | MVarExpr (serial, _, _) -> CVarExpr(getUniqueVarName ctx serial), ctx

  | MProcExpr (serial, _) ->
    let ctx = cgExternFunDecl ctx serial
    CVarExpr(getUniqueFunName ctx serial), ctx

  | MVariantExpr (_, serial, _) -> genVariantNameExpr ctx serial
  | MDiscriminantConstExpr (variantSerial, _) -> genDiscriminant ctx variantSerial, ctx
  | MGenericValueExpr (genericValue, ty, _) -> genGenericValue ctx genericValue ty
  | MUnaryExpr (op, arg, _) -> genUnaryExpr ctx op arg
  | MBinaryExpr (op, l, r, _) -> genExprBin ctx op l r

  | MNativeExpr (code, args, _, _) ->
    let args, ctx = cgExprList ctx args
    CNativeExpr(code, args), ctx

let private cgExprList ctx exprs : CExpr list * CirCtx = exprs |> List.mapFold cgExpr ctx

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private addNativeFunDecl ctx funName argTys resultTy =
  let argTys, ctx = cgArgTys ctx argTys
  let isNoReturn = tyIsNever resultTy
  let resultTy, ctx = cgResultTy ctx resultTy

  addDecl ctx (CFunForwardDecl(funName, argTys, resultTy, isNoReturn))

let private cgActionStmt (ctx: CirCtx) itself action args loc =
  match action with
  | MAssertNotAction ->
    let cond, ctx =
      match args with
      | [ arg ] -> cgExpr ctx arg
      | _ -> unreachable ()

    // Embed the source location information.
    let args =
      let (Loc (docId, y, x)) = loc

      let pathname =
        match ctx.Rx.DocIdToModulePath docId with
        | Some (p, m) -> p + "/" + m + ".milone"
        | None -> Symbol.toString docId

      [ CStringLitExpr pathname
        CIntExpr(string y, I32)
        CIntExpr(string x, I32) ]

    addStmt ctx (CIfStmt1(cond, CExprStmt(CCallExpr(CVarExpr "milone_assert_error", args))))

  | MPrintfnAction argTys -> cgPrintfnActionStmt ctx itself args argTys

  | MEnterRegionAction ->
    assert (List.isEmpty args)
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "milone_region_enter", [])))

  | MLeaveRegionAction ->
    assert (List.isEmpty args)
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "milone_region_leave", [])))

  | MCallProcAction ->
    let args, ctx = cgExprList ctx args

    match args with
    | callee :: args -> addStmt ctx (CExprStmt(CCallExpr(callee, args)))
    | _ -> unreachable itself

  | MCallClosureAction ->
    let args, ctx = cgExprList ctx args

    match args with
    | callee :: args ->
      // FIXME: is it ensured that the closure type is complete here?
      let callExpr =
        let funPtr = CDotExpr(callee, "fun")
        let envArg = CDotExpr(callee, "env")
        CCallExpr(funPtr, envArg :: args)

      addStmt ctx (CExprStmt callExpr)

    | _ -> unreachable itself

  | MCallNativeAction (funName, argTys) ->
    let ctx =
      addNativeFunDecl ctx funName argTys tyUnit

    let args, ctx = cgExprList ctx args
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr funName, args)))

  | MPtrWriteAction ->
    match cgExprList ctx args with
    | [ ptr; value ], ctx -> addStmt ctx (CSetStmt(CUnaryExpr(CDerefUnary, ptr), value))
    | _ -> unreachable ()

let private cgPrintfnActionStmt ctx itself args argTys =
  let args =
    match listTryZip args argTys with
    | it, [], [] -> it
    | _ -> unreachable ()

  match args with
  | (MLitExpr (StringLit format, _), _) :: args ->
    let format = CStringLitExpr(format + "\n")

    let args, ctx =
      args
      |> List.mapFold
           (fun ctx (arg, argTy) ->
             match arg with
             | MLitExpr (StringLit value, _) -> CStringLitExpr value, ctx

             | _ when tyEqual argTy tyString ->
               // Insert implicit cast from string to ptr.
               let arg, ctx = cgExpr ctx arg
               CCallExpr(CVarExpr "string_to_c_str", [ arg ]), ctx

             | _ -> cgExpr ctx arg)
           ctx

    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "printf", format :: args)))

  | _ -> unreachable itself

let private addLetStmt (ctx: CirCtx) name expr =
  match expr with
  | Some expr -> addStmt ctx (CSetStmt(CVarExpr name, expr))
  | None -> ctx

let private addSetStmt (ctx: CirCtx) name expr =
  addStmt ctx (CSetStmt(CVarExpr name, expr))

let private addLetAllocStmt ctx name valTy varTy =
  // `U* x = (U*)malloc(sizeof T);`
  let stmt =
    let init =
      CCastExpr(
        CCallExpr(
          CVarExpr "milone_region_alloc",
          [ CIntExpr("1", I32)
            CSizeOfExpr valTy ]
        ),
        varTy
      )

    CSetStmt(CVarExpr name, init)

  addStmt ctx stmt

let private cgPrimStmt (ctx: CirCtx) itself prim args serial resultTy =
  let conversion ctx makeExpr =
    match args with
    | [ arg ] ->
      let name = getUniqueVarName ctx serial
      let arg, ctx = cgExpr ctx arg
      addSetStmt ctx name (makeExpr arg)

    | _ -> unreachable itself

  let regular ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let args, ctx = cgExprList ctx args
    addSetStmt ctx name (makeExpr args)

  let regularWithTy ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let ty, ctx = cgTyComplete ctx resultTy
    let args, ctx = cgExprList ctx args
    addSetStmt ctx name (makeExpr args ty)

  match prim with
  | MIntOfStringPrim flavor ->
    let name = cStringToIntegerFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MFloatOfStringPrim flavor ->
    let name = cStringToFloatFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MCharOfStringPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "string_to_char", [ arg ]))

  | MStringOfBoolPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "string_of_bool", [ arg ]))
  | MStringOfCharPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "string_of_char", [ arg ]))

  | MStringOfIntPrim flavor ->
    let name = cStringOfIntegerFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStringOfFloatPrim flavor ->
    let name = cStringOfFloatFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStringGetSlicePrim -> regular ctx (fun args -> (CCallExpr(CVarExpr "string_get_slice", args)))

  | MClosurePrim funSerial ->
    let name = getUniqueVarName ctx serial
    let ty, ctx = cgTyComplete ctx resultTy
    let args, ctx = cgExprList ctx args

    let expr, ctx =
      let funExpr = CVarExpr(getUniqueFunName ctx funSerial)

      match args with
      | [ env ] -> CInitExpr([ "fun", funExpr; "env", env ], ty), ctx
      | _ -> unreachable itself

    addSetStmt ctx name expr

  | MBoxPrim argTy ->
    match args with
    | [ arg ] -> cgBoxStmt ctx serial arg argTy
    | _ -> unreachable itself

  | MConsPrim itemTy ->
    match args with
    | [ l; r ] -> cgConsStmt ctx serial l r itemTy
    | _ -> unreachable itself

  | MVariantPrim variantSerial ->
    regularWithTy ctx (fun args unionTy ->
      match args with
      | [ payload ] ->
        let variantName = getUniqueVariantName ctx variantSerial

        let fields =
          [ "discriminant", CVarExpr variantName
            variantName, payload ]

        CInitExpr(fields, unionTy)

      | _ -> unreachable itself)

  | MRecordPrim ->
    regularWithTy ctx (fun args recordTy ->
      let fields =
        args |> List.mapi (fun i arg -> tupleField i, arg)

      CInitExpr(fields, recordTy))

  | MCallProcPrim ->
    let name = getUniqueVarName ctx serial
    let args, ctx = cgExprList ctx args

    match args with
    | callee :: args -> addSetStmt ctx name (CCallExpr(callee, args))

    | [] -> unreachable itself

  | MCallClosurePrim ->
    let name = getUniqueVarName ctx serial
    let args, ctx = cgExprList ctx args

    match args with
    | callee :: args ->
      let expr =
        let funPtr = CDotExpr(callee, "fun")
        let envArg = CDotExpr(callee, "env")
        CCallExpr(funPtr, envArg :: args)

      addSetStmt ctx name expr

    | [] -> unreachable itself

  | MCallNativePrim (funName, argTys) ->
    let ctx =
      addNativeFunDecl ctx funName argTys resultTy

    regular ctx (fun args -> (CCallExpr(CVarExpr funName, args)))

  | MPtrInvalidPrim ->
    regularWithTy ctx (fun args resultTy ->
      match args with
      | [ arg ] -> CCastExpr(arg, resultTy)
      | _ -> unreachable ())

let private cgBoxStmt ctx serial arg argTy =
  let argTy, ctx = cgTyComplete ctx argTy
  let arg, ctx = cgExpr ctx arg

  // void const *p = malloc(sizeof T);
  let temp = getUniqueVarName ctx serial

  let ctx =
    addLetAllocStmt ctx temp argTy (CConstPtrTy CVoidTy)

  // *(T *)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CVarExpr temp, CPtrTy argTy))

  addStmt ctx (CSetStmt(left, arg))

let private cgConsStmt ctx serial head tail itemTy =
  let temp = getUniqueVarName ctx serial
  let listTy, ctx = genListTyDef ctx itemTy

  let listStructTy =
    match listTy with
    | CConstPtrTy it -> it
    | _ -> unreachable ()

  let ctx =
    addLetAllocStmt ctx temp listStructTy listTy

  let head, ctx = cgExpr ctx head
  let tail, ctx = cgExpr ctx tail

  let stmt =
    let fields = [ "head", head; "tail", tail ]
    CSetStmt(CUnaryExpr(CDerefUnary, CCastExpr(CVarExpr temp, CPtrTy listStructTy)), CInitExpr(fields, listStructTy))

  addStmt ctx stmt

let private cgLetValStmt ctx serial init =
  let name = getUniqueVarName ctx serial

  let init, ctx =
    match init with
    | None -> None, ctx

    | Some init ->
      let init, ctx = cgExpr ctx init
      Some init, ctx

  addLetStmt ctx name init

let private cgSetStmt ctx serial right =
  let right, ctx = cgExpr ctx right
  let name = getUniqueVarName ctx serial
  let left = CVarExpr(name)
  addStmt ctx (CSetStmt(left, right))

let private cgTerminatorStmt (ctx: CirCtx) stmt loc : CStmt * CirCtx =
  match stmt with
  | MReturnTerminator (expr, argTy) ->
    if ctx.IsNoReturn then
      CNoopStmt, ctx
    else if tyIsUnit argTy || tyIsNever argTy then
      CReturnStmt None, ctx
    else
      let expr, ctx = cgExpr ctx expr
      CReturnStmt(Some expr), ctx

  | MGotoTerminator label -> CGotoStmt label, ctx

  | MIfTerminator (cond, thenCl, elseCl) ->
    let cond, ctx = cgExpr ctx cond
    let thenCl, ctx = cgTerminatorStmt ctx thenCl loc
    let elseCl, ctx = cgTerminatorStmt ctx elseCl loc
    CIfStmt(cond, thenCl, elseCl), ctx

  | MSwitchTerminator (cond, clauses) ->
    let cond, ctx = cgExpr ctx cond

    let clauses, ctx =
      clauses
      |> List.mapFold
           (fun ctx (clause: MSwitchClause) ->
             let cases =
               clause.Cases
               |> List.map (fun cond -> cgConst ctx cond)

             let stmt, ctx = cgTerminatorStmt ctx clause.Terminator loc

             (cases, clause.IsDefault, stmt), ctx)
           ctx

    CSwitchStmt(cond, clauses), ctx

  | MExitTerminator arg ->
    let arg, ctx = cgExpr ctx arg
    CExprStmt(CCallExpr(CVarExpr "exit", [ arg ])), ctx

  | MAbortTerminator cause ->
    let f =
      match cause with
      | MAbortCause.Assert -> "milone_assert_error"
      | MAbortCause.Exhaust -> "milone_exhaust_error"
      | MAbortCause.Never -> "milone_never_error"

    // Embed the source location information.
    let args =
      let (Loc (docId, y, x)) = loc

      let pathname =
        match ctx.Rx.DocIdToModulePath docId with
        | Some (p, m) -> p + "/" + m + ".milone"
        | None -> Symbol.toString docId

      [ CStringLitExpr pathname
        CIntExpr(string y, I32)
        CIntExpr(string x, I32) ]

    CExprStmt(CCallExpr(CVarExpr f, args)), ctx

let private cgStmt ctx stmt =
  match stmt with
  | MActionStmt (action, args, loc) -> cgActionStmt ctx stmt action args loc
  | MPrimStmt (prim, args, temp, resultTy, _) -> cgPrimStmt ctx stmt prim args temp resultTy
  | MLetValStmt (serial, init, _, _) -> cgLetValStmt ctx serial init
  | MSetStmt (serial, right, _) -> cgSetStmt ctx serial right
  | MLabelStmt (label, _) -> addStmt ctx (CLabelStmt label)

  | MGotoIfStmt (cond, label) ->
    let cond, ctx = cgExpr ctx cond
    addStmt ctx (CGotoIfStmt(cond, label))

  | MTerminatorStmt (terminator, loc) ->
    let stmt, ctx = cgTerminatorStmt ctx terminator loc

    match stmt with
    | CNoopStmt -> ctx
    | _ -> addStmt ctx stmt

  | MNativeStmt (code, args, _) ->
    let args, ctx = cgExprList ctx args
    addStmt ctx (CNativeStmt(code, args))

let private cgBlock (ctx: CirCtx) (stmts: MStmt list) =
  let bodyCtx: CirCtx = cgStmts (enterBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = rollback ctx bodyCtx
  List.rev stmts, ctx

let private cgBlocks (ctx: CirCtx) (blocks: MBlock list) =
  match blocks with
  | [ block ] -> cgBlock ctx block.Stmts
  | _ -> unreachable () // not implemented yet

let private cgStmts (ctx: CirCtx) (stmts: MStmt list) : CirCtx =
  let rec go ctx stmts =
    match stmts with
    | [] -> ctx
    | stmt :: stmts ->
      let ctx = cgStmt ctx stmt
      go ctx stmts

  go ctx stmts

let private genMainFun entrypointName stmts : CDecl =
  let intTy = CEmbedTy "int"

  let args =
    [ "argc", intTy
      "argv", CPtrTy(CPtrTy(CEmbedTy "char")) ]

  let stmts =
    CExprStmt(CCallExpr(CVarExpr "milone_start", [ CVarExpr "argc"; CVarExpr "argv" ]))
    :: stmts

  let isNoReturn = false

  CFunDecl(entrypointName, args, intTy, stmts, isNoReturn)

let private cgDecls (ctx: CirCtx) decls =
  match decls with
  | [] -> ctx

  | MProcDecl (callee, args, body, resultTy, localVars, _) :: decls ->
    let def: FunDef = ctx.Rx.Funs |> mapFind callee

    let isNoReturn = tyIsNever resultTy
    let ctx = { ctx with IsNoReturn = isNoReturn }

    let main, funName, args =
      if isMainFun ctx callee then
        true, ctx.Rx.EntrypointName, []
      else
        false, getUniqueFunName ctx callee, args

    let rec collectArgs acc ctx args =
      match args with
      | [] -> List.rev acc, ctx
      | (arg, ty, _) :: args ->
        let name = getUniqueVarName ctx arg
        let cty, ctx = cgTyComplete ctx ty
        collectArgs ((name, cty) :: acc) ctx args

    let collectFunLocalStmts (ctx: CirCtx) =
      localVars
      |> List.mapFold
           (fun (ctx: CirCtx) (varSerial, ty, _) ->
             let name = getUniqueVarName ctx varSerial
             let cty, ctx = cgTyComplete ctx ty
             CLetStmt(name, None, cty), ctx)
           ctx

    let args, ctx = collectArgs [] ctx args
    let stmts, ctx = collectFunLocalStmts ctx
    let body, ctx = cgBlocks ctx body
    let resultTy, ctx = cgResultTy ctx resultTy

    let funDecl =
      let body = List.append stmts body

      if main then
        genMainFun funName body
      else
        match def.Linkage with
        | InternalLinkage -> CStaticFunDecl(funName, args, resultTy, body, isNoReturn)
        | ExternalLinkage _ -> CFunDecl(funName, args, resultTy, body, isNoReturn)

    let ctx = addDecl ctx funDecl
    cgDecls ctx decls

  | MNativeDecl (code, args, _) :: decls ->
    let args, ctx = cgExprList ctx args
    let ctx = addDecl ctx (CNativeDecl(code, args))
    cgDecls ctx decls

// Sort declarations by kind.
// Without this, static variable definition can appear before its type definition.
let private sortDecls (decls: CDecl list) : CDecl list =
  let tys, vars, funs =
    decls
    |> List.fold
         (fun (tys, vars, funs) decl ->
           match decl with
           | CErrorDecl _
           | CFunPtrTyDef _
           | CStructForwardDecl _
           | CStructDecl _
           | CEnumDecl _
           | CNativeDecl _ -> decl :: tys, vars, funs

           | CStaticVarDecl _
           | CInternalStaticVarDecl _
           | CExternVarDecl _ -> tys, decl :: vars, funs

           | CFunForwardDecl _
           | CFunDecl _
           | CStaticFunDecl _ -> tys, vars, decl :: funs)
         ([], [], [])

  List.collect List.rev [ tys; vars; funs ]

let private cgModule (ctx: CirCtx) (m: MModule) : DocId * CDecl list =
  let varUniqueNames, _ =
    renameIdents2 m.Vars (fun name -> true, name) ctx.Rx.VarUniqueNames ctx.Rx.ValueNameFreq

  let ctx: CirCtx =
    { Rx =
        { ctx.Rx with
            DocIdOpt = Some m.DocId
            VarUniqueNames = varUniqueNames
            MainFunOpt = m.MainFunOpt }
      TyEnv = TMap.empty tyCompare
      TyUniqueNames = ctx.TyUniqueNames
      Stmts = []
      Decls = []
      FunDecls = TSet.empty funSerialCompare
      FunPtrTys = TMap.empty (pairCompare (listCompare cTyCompare) cTyCompare)
      IsNoReturn = false }

  // Generate leading native decls to not be preceded by generated decls.
  let moduleDecls, ctx =
    let leadingNativeDeclAcc, decls =
      let rec go acc decls =
        match decls with
        | (MNativeDecl (cCode, [], _)) :: decls -> go (CNativeDecl(cCode, []) :: acc) decls
        | _ -> acc, decls

      go [] m.Decls

    decls, { ctx with Decls = leadingNativeDeclAcc }

  // Generate extern var decls.
  let ctx =
    m.ExternVars
    |> TMap.fold
         (fun ctx varSerial ty ->
           let name = getUniqueVarName ctx varSerial
           let ty, ctx = cgTyComplete ctx ty
           addDecl ctx (CExternVarDecl(name, ty)))
         ctx

  // Generate static var decls.
  let ctx =
    m.StaticVars
    |> List.fold
         (fun ctx (varSerial, ty) ->
           let name = getUniqueVarName ctx varSerial
           let ty, ctx = cgTyComplete ctx ty
           addDecl ctx (CStaticVarDecl(name, ty)))
         ctx

  // Generate decls.
  let ctx = cgDecls ctx moduleDecls
  let decls = List.rev ctx.Decls |> sortDecls

  m.DocId, decls

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genCir
  (entrypointName: string)
  (df: DocIdToModulePath)
  (modules: MModule list, mirResult: MirResult)
  : (DocId * CDecl list) list =
  let ctx = ofMirResult entrypointName df mirResult

  modules
  |> __parallelMap (cgModule ctx)
  |> List.filter (fun (_, decls) -> decls |> List.isEmpty |> not)
