/// # CirGen
///
/// Converts MIR to CIR.
///
/// Milone-lang's primitives are converted to corresponding C's operator
/// or function all defined in runtime.
/// See `runtime` for runtime codes.
///
/// Milone-lang's types are converted to
/// C-style struct/union types.
module rec MiloneTranslation.CirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneTranslation.Cir
open MiloneTranslation.Hir
open MiloneTranslation.Mir
open MiloneTranslation.MirGen

module S = MiloneStd.StdString

let private unwrapListTy ty =
  match ty with
  | Ty (ListTk, [ itemTy ]) -> itemTy
  | _ -> unreachable ()

let private tupleField (i: int) = "t" + string i

/// Calculates discriminant type's name of union type.
let private toDiscriminantEnumName (name: string) = name + "Discriminant"

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
      acc |> multimapAdd ident (serial, def)

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

let private funDefToName (funDef: FunDef) =
  match funDef.Linkage with
  | InternalLinkage ->
    let name =
      // FIXME: avoid abusing docId
      let (Loc (docId, _, _)) = funDef.Loc
      let doc = docId |> S.replace "." "_"

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
    MainFunOpt: FunSerial option

    FunLocals: TreeMap<FunSerial, (VarSerial * Ty) list>
    ReplacingVars: TreeSet<VarSerial>

    ValueNameFreq: TreeMap<Ident, int>
    VarUniqueNames: TreeMap<VarSerial, Ident>
    FunUniqueNames: TreeMap<FunSerial, Ident>
    VariantUniqueNames: TreeMap<VariantSerial, Ident>

    /// Doc ID of current module.
    DocIdOpt: DocId option }

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
    VarDecls: TreeSet<VarSerial>
    FunDecls: TreeSet<FunSerial> }

let private ofMirResult (mirCtx: MirResult) : CirCtx =
  let freq = freqEmpty compare

  let varUniqueNames, freq =
    renameIdents2 mirCtx.StaticVars varDefToName (TMap.empty varSerialCompare) freq

  let funUniqueNames, freq =
    renameIdents2 mirCtx.Funs funDefToName (TMap.empty funSerialCompare) freq

  let variantUniqueNames, freq =
    renameIdents2
      mirCtx.Variants
      (fun (variantDef: VariantDef) -> true, variantDef.Name)
      (TMap.empty variantSerialCompare)
      freq

  let tyNames =
    let toKey (serial, tyDef) =
      match tyDef with
      | UnionTyDef _ -> tyUnion serial []
      | RecordTyDef _ -> tyRecord serial

      | MetaTyDef _ -> unreachable () // Resolved in Typing.

    mirCtx.Tys
    |> renameIdents tyDefToName toKey tyCompare

  let rx: Rx =
    { StaticVars = mirCtx.StaticVars
      Funs = mirCtx.Funs
      Variants = mirCtx.Variants
      Tys = mirCtx.Tys
      MainFunOpt = mirCtx.MainFunOpt

      FunLocals = mirCtx.FunLocals
      ReplacingVars = mirCtx.ReplacingVars

      ValueNameFreq = freq
      VarUniqueNames = varUniqueNames
      FunUniqueNames = funUniqueNames
      VariantUniqueNames = variantUniqueNames
      DocIdOpt = None }

  { Rx = rx
    TyEnv = TMap.empty tyCompare
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []
    VarDecls = TSet.empty varSerialCompare
    FunDecls = TSet.empty funSerialCompare }

let private currentDocId (ctx: CirCtx) : DocId =
  match ctx.Rx.DocIdOpt with
  | Some it -> it
  | None -> unreachable () // Must be filled before starting work.

let private findStorageModifier (ctx: CirCtx) varSerial =
  match ctx.Rx.StaticVars |> TMap.tryFind varSerial with
  | Some varDef -> varDef.IsStatic

  | _ -> NotStatic

let private findVarLinkage (ctx: CirCtx) varSerial =
  match ctx.Rx.StaticVars |> TMap.tryFind varSerial with
  | Some varDef -> varDef.Linkage

  | _ -> InternalLinkage

let private isReplacing (ctx: CirCtx) varSerial =
  ctx.Rx.ReplacingVars |> TSet.contains varSerial

let private isMainFun (ctx: CirCtx) funSerial =
  match ctx.Rx.MainFunOpt with
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
  | _ -> false

let private enterBlock (ctx: CirCtx) = { ctx with Stmts = [] }

let private rollback (bCtx: CirCtx) (dCtx: CirCtx) = { dCtx with Stmts = bCtx.Stmts }

let private addStmt (ctx: CirCtx) stmt = { ctx with Stmts = stmt :: ctx.Stmts }

let private addDecl (ctx: CirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

// -----------------------------------------------
// Type definition generation
// -----------------------------------------------

let private cgArgTys ctx argTys : CTy list * CirCtx =
  let argTys =
    argTys
    |> List.filter (fun ty -> tyIsUnit ty |> not)

  (argTys, ctx)
  |> stMap (fun (ty, ctx) -> cgTyComplete ctx ty)

let private cgResultTy ctx resultTy : CTy * CirCtx =
  if tyIsUnit resultTy then
    CVoidTy, ctx
  else
    cgTyComplete ctx resultTy

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
    let _, argTys, resultTy = tyToArgList funTy

    let argTys, ctx = cgArgTys ctx argTys
    let resultTy, ctx = cgResultTy ctx resultTy

    let fields =
      [ "fun", CFunPtrTy(envTy :: argTys, resultTy)
        "env", envTy ]

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
    let structName, ctx = getUniqueTyName ctx listTy
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
    let structName, ctx = getUniqueTyName ctx listTy
    let selfTy, ctx = genIncompleteListTyDecl ctx itemTy

    let itemTy, (ctx: CirCtx) = cgTyComplete ctx itemTy
    let fields = [ "head", itemTy; "tail", selfTy ]

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add listTy (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteUnionTyDecl (ctx: CirCtx) tySerial =
  let unionTyRef = tyUnion tySerial []

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

let private genUnionTyDef (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyUnion tySerial []

  match ctx.TyEnv |> TMap.tryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let structName, ctx = getUniqueTyName ctx unionTyRef
    let selfTy, ctx = genIncompleteUnionTyDecl ctx tySerial

    let discriminantEnumName = toDiscriminantEnumName structName
    let discriminantTy = CEnumTy discriminantEnumName

    let variants =
      variants
      |> List.map
           (fun variantSerial ->
             let v = ctx.Rx.Variants |> mapFind variantSerial
             v.Name, variantSerial, v.HasPayload, v.PayloadTy)

    let discriminants =
      variants
      |> List.map (fun (_, serial, _, _) -> getUniqueVariantName ctx serial)

    let variants, ctx =
      (variants, ctx)
      |> stFlatMap
           (fun ((_, serial, hasPayload, payloadTy), acc, ctx) ->
             if hasPayload then
               let payloadTy, ctx = cgTyComplete ctx payloadTy

               (getUniqueVariantName ctx serial, payloadTy)
               :: acc,
               ctx
             else
               acc, ctx)

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

let private genIncompleteRecordTyDecl (ctx: CirCtx) tySerial =
  let recordTyRef = tyRecord tySerial

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

let private genRecordTyDef ctx tySerial fields =
  let recordTyRef = tyRecord tySerial
  let structName, ctx = getUniqueTyName ctx recordTyRef
  let selfTy, ctx = genIncompleteRecordTyDecl ctx tySerial

  match ctx.TyEnv |> TMap.tryFind recordTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let fieldTys, (ctx: CirCtx) =
      (fields, ctx)
      |> stMap
           (fun ((_, ty, _), ctx) ->
             let ty, ctx = cgTyComplete ctx ty
             ty, ctx)

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

let private cgNativePtrTy ctx isMut itemTy =
  let itemTy, ctx = cgTyIncomplete ctx itemTy

  match isMut with
  | IsConst -> CConstPtrTy itemTy, ctx
  | IsMut -> CPtrTy itemTy, ctx

let private cgNativeFunTy ctx tys =
  match splitLast tys with
  | None -> unreachable ()
  | Some (argTys, resultTy) ->
    let argTys, ctx = cgArgTys ctx argTys
    let resultTy, ctx = cgResultTy ctx resultTy
    CFunPtrTy(argTys, resultTy), ctx

/// Converts a type to incomplete type.
/// whose type definition is not necessary to be visible.
let private cgTyIncomplete (ctx: CirCtx) (ty: Ty) : CTy * CirCtx =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | IntTk flavor, _ -> CIntTy flavor, ctx
  | FloatTk flavor, _ -> CFloatTy flavor, ctx
  | BoolTk, _ -> CBoolTy, ctx
  | CharTk, _ -> CCharTy, ctx
  | StrTk, _ -> CStructTy "String", ctx
  | ObjTk, _ -> CConstPtrTy CVoidTy, ctx

  | FunTk, [ sTy; tTy ] -> genIncompleteFunTyDecl ctx sTy tTy
  | FunTk, _ -> unreachable ()

  | TupleTk, [] -> CCharTy, ctx
  | TupleTk, _ -> unreachable () // Non-unit TupleTk is resolved in MonoTy.

  | ListTk, [ itemTy ] -> genIncompleteListTyDecl ctx itemTy
  | ListTk, _ -> unreachable ()

  | VoidTk, _ -> CVoidTy, ctx
  | NativePtrTk isMut, [ itemTy ] -> cgNativePtrTy ctx isMut itemTy
  | NativePtrTk _, _ -> unreachable ()
  | NativeFunTk, _ -> cgNativeFunTy ctx tyArgs
  | NativeTypeTk code, _ -> CEmbedTy code, ctx

  | UnionTk tySerial, _ -> genIncompleteUnionTyDecl ctx tySerial
  | RecordTk tySerial, _ -> genIncompleteRecordTyDecl ctx tySerial

  | OptionTk, _ // OptionTk is resolved in MonoTy.
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
  | StrTk, _ -> CStructTy "String", ctx
  | ObjTk, _ -> CConstPtrTy CVoidTy, ctx

  | FunTk, [ sTy; tTy ] -> genFunTyDef ctx sTy tTy
  | FunTk, _ -> unreachable ()

  | TupleTk, [] -> CCharTy, ctx
  | TupleTk, _ -> unreachable () // Non-unit TupleTk is resolved in MonoTy.

  | ListTk, [ itemTy ] ->
    // Complete definition of the underlying struct type is unnecessary yet
    // since the struct is hold over pointer.
    genIncompleteListTyDecl ctx itemTy
  | ListTk, _ -> unreachable ()

  | VoidTk, _ -> CVoidTy, ctx

  | NativePtrTk isMut, [ itemTy ] -> cgNativePtrTy ctx isMut itemTy
  | NativePtrTk _, _ -> unreachable ()

  | NativeFunTk, _ -> cgNativeFunTy ctx tyArgs
  | NativeTypeTk code, _ -> CEmbedTy code, ctx

  | UnionTk serial, _ ->
    match ctx.Rx.Tys |> TMap.tryFind serial with
    | Some (UnionTyDef (_, _, variants, _)) -> genUnionTyDef ctx serial variants

    | _ -> unreachable () // Union type undefined?

  | RecordTk serial, _ ->
    match ctx.Rx.Tys |> TMap.tryFind serial with
    | Some (RecordTyDef (_, fields, _, _)) -> genRecordTyDef ctx serial fields

    | _ -> unreachable () // Record type undefined?

  | OptionTk, _ // OptionTk is resolved in MonoTy.
  | MetaTk _, _ -> unreachable () // Resolved in Typing.

// -----------------------------------------------
// Extern decl
// -----------------------------------------------

let private cgExternVarDecl (ctx: CirCtx) varSerial ty =
  if TSet.contains varSerial ctx.VarDecls then
    ctx
  else
    let name = getUniqueVarName ctx varSerial
    let ty, ctx = cgTyComplete ctx ty

    let ctx = addDecl ctx (CExternVarDecl(name, ty))

    { ctx with
        VarDecls = ctx.VarDecls |> TSet.add varSerial }

let private cgExternFunDecl (ctx: CirCtx) funSerial =
  if TSet.contains funSerial ctx.FunDecls then
    ctx
  else
    let funDef = ctx.Rx.Funs |> mapFind funSerial
    let (Loc (docId, _, _)) = funDef.Loc

    if docId = currentDocId ctx then
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
      let resultTy, ctx = cgResultTy ctx resultTy

      let ctx: CirCtx =
        addDecl ctx (CFunForwardDecl(name, argTys, resultTy))

      { ctx with
          FunDecls = TSet.add funSerial ctx.FunDecls }

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private cBinaryOf op =
  match op with
  | MMulBinary -> CMulBinary
  | MDivBinary -> CDivBinary
  | MModuloBinary -> CModuloBinary
  | MAddBinary -> CAddBinary
  | MSubBinary -> CSubBinary

  | MBitAndBinary -> CBitAndBinary
  | MBitOrBinary -> CBitOrBinary
  | MBitXorBinary -> CBitXorBinary
  | MLeftShiftBinary -> CLeftShiftBinary
  | MRightShiftBinary -> CRightShiftBinary

  | MEqualBinary -> CEqualBinary
  | MNotEqualBinary -> CNotEqualBinary
  | MLessBinary -> CLessBinary
  | MGreaterEqualBinary -> CGreaterEqualBinary

  | MIntCompareBinary
  | MInt64CompareBinary
  | MUInt64CompareBinary
  | MStrAddBinary
  | MStrCompareBinary
  | MStrIndexBinary -> unreachable ()

let private genLit lit =
  match lit with
  | IntLit text -> CIntExpr text
  | FloatLit text -> CDoubleExpr text
  | BoolLit false -> CVarExpr "false"
  | BoolLit true -> CVarExpr "true"
  | CharLit value -> CCharExpr value
  | StrLit value -> CStrObjExpr value

let private genDiscriminant ctx variantSerial =
  CVarExpr(getUniqueVariantName ctx variantSerial)

let private cgConst ctx mConst =
  match mConst with
  | MLitConst lit -> genLit lit
  | MDiscriminantConst variantSerial -> genDiscriminant ctx variantSerial

let private genVariantNameExpr ctx serial ty =
  let ty, ctx = cgTyComplete ctx ty

  let discriminant =
    CVarExpr(getUniqueVariantName ctx serial)

  CInitExpr([ "discriminant", discriminant ], ty), ctx

let private genGenericValue ctx genericValue ty =
  match genericValue with
  | MNilGv -> CVarExpr "NULL", ctx

  | MSizeOfGv ->
    let ty, ctx = cgTyComplete ctx ty
    CSizeOfExpr ty, ctx

/// Converts a binary expression to a runtime function call.
let private genBinaryExprAsCall ctx funName l r =
  let l, ctx = cgExpr ctx l
  let r, ctx = cgExpr ctx r
  let callExpr = CCallExpr(CVarExpr funName, [ l; r ])
  callExpr, ctx

let private genUnaryExpr ctx op arg ty _ =
  let argTy = arg |> mexprToTy
  let arg, ctx = cgExpr ctx arg

  match op with
  | MMinusUnary -> CUnaryExpr(CMinusUnary, arg), ctx
  | MNotUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MIntOfScalarUnary flavor -> CCastExpr(arg, CIntTy flavor), ctx
  | MFloatOfScalarUnary flavor -> CCastExpr(arg, CFloatTy flavor), ctx
  | MCharOfScalarUnary -> CCastExpr(arg, CCharTy), ctx
  | MStrPtrUnary -> CDotExpr(arg, "str"), ctx
  | MStrLenUnary -> CDotExpr(arg, "len"), ctx

  | MUnboxUnary ->
    let valTy, ctx = cgTyComplete ctx ty

    let deref =
      CUnaryExpr(CDerefUnary, CCastExpr(arg, CConstPtrTy valTy))

    deref, ctx

  | MTupleItemUnary index -> CDotExpr(arg, tupleField index), ctx

  | MGetDiscriminantUnary -> CDotExpr(arg, "discriminant"), ctx

  | MGetVariantUnary serial ->
    let _, ctx = cgTyComplete ctx ty
    CDotExpr(arg, getUniqueVariantName ctx serial), ctx

  | MRecordItemUnary index -> CDotExpr(arg, tupleField index), ctx

  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx

  | MListHeadUnary ->
    let _, ctx = genListTyDef ctx (unwrapListTy argTy)
    CArrowExpr(arg, "head"), ctx

  | MListTailUnary ->
    let _, ctx = genListTyDef ctx (unwrapListTy argTy)
    CArrowExpr(arg, "tail"), ctx

  | MNativeCastUnary ->
    let ty, ctx = cgTyComplete ctx ty
    CCastExpr(arg, ty), ctx

let private genExprBin ctx op l r =
  match op with
  | MIntCompareBinary -> genBinaryExprAsCall ctx "int_compare" l r
  | MInt64CompareBinary -> genBinaryExprAsCall ctx "int64_compare" l r
  | MUInt64CompareBinary -> genBinaryExprAsCall ctx "uint64_compare" l r

  | MStrAddBinary -> genBinaryExprAsCall ctx "str_add" l r
  | MStrCompareBinary -> genBinaryExprAsCall ctx "str_compare" l r
  | MStrIndexBinary ->
    let l, ctx = cgExpr ctx l
    let r, ctx = cgExpr ctx r
    CIndexExpr(CDotExpr(l, "str"), r), ctx

  | _ ->
    let l, ctx = cgExpr ctx l
    let r, ctx = cgExpr ctx r
    let opExpr = CBinaryExpr(cBinaryOf op, l, r)
    opExpr, ctx

let private cgExprList ctx exprs =
  let rec go results ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, ctx = cgExpr ctx expr
      go (result :: results) ctx exprs

  go [] ctx exprs

let private cgExpr (ctx: CirCtx) (arg: MExpr) : CExpr * CirCtx =
  match arg |> mxSugar with
  | MLitExpr (lit, _) -> genLit lit, ctx
  | MUnitExpr _ -> CVarExpr "0", ctx
  | MNeverExpr loc -> unreachable ("MNeverExpr " + locToString loc)

  | MVarExpr (serial, ty, _) ->
    let ctx =
      match findStorageModifier ctx serial with
      | IsStatic -> cgExternVarDecl ctx serial ty
      | NotStatic -> ctx

    CVarExpr(getUniqueVarName ctx serial), ctx

  | MProcExpr (serial, _, _) -> CVarExpr(getUniqueFunName ctx serial), ctx

  | MVariantExpr (_, serial, ty, _) -> genVariantNameExpr ctx serial ty
  | MDiscriminantConstExpr (variantSerial, _) -> genDiscriminant ctx variantSerial, ctx
  | MGenericValueExpr (genericValue, ty, _) -> genGenericValue ctx genericValue ty
  | MUnaryExpr (op, arg, ty, loc) -> genUnaryExpr ctx op arg ty loc
  | MBinaryExpr (op, l, r, _, _) -> genExprBin ctx op l r

  | MNativeExpr (code, args, _, _) ->
    let args, ctx = cgExprList ctx args
    CNativeExpr(code, args), ctx

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private addNativeFunDecl ctx funName args resultTy =
  let argTys, ctx = cgArgTys ctx (List.map mexprToTy args)
  let resultTy, ctx = cgResultTy ctx resultTy

  addDecl ctx (CFunForwardDecl(funName, argTys, resultTy))

let private cgActionStmt ctx itself action args =
  match action with
  | MAssertAction ->
    let args, ctx = cgExprList ctx args
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "milone_assert", args)))

  | MPrintfnAction -> cgPrintfnActionStmt ctx itself args

  | MEnterRegionAction ->
    assert (List.isEmpty args)
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "milone_enter_region", [])))

  | MLeaveRegionAction ->
    assert (List.isEmpty args)
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "milone_leave_region", [])))

  | MCallProcAction ->
    let ctx =
      match args with
      | MProcExpr (funSerial, _, _) :: _ -> cgExternFunDecl ctx funSerial
      | _ -> ctx

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    match args with
    | callee :: args -> addStmt ctx (CExprStmt(CCallExpr(callee, args)))
    | _ -> unreachable itself

  | MCallClosureAction ->
    let ctx =
      match args with
      | MProcExpr (funSerial, _, _) :: _ -> cgExternFunDecl ctx funSerial
      | _ -> ctx

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    match args with
    | callee :: args ->
      let callExpr =
        let funPtr = CDotExpr(callee, "fun")
        let envArg = CDotExpr(callee, "env")
        CCallExpr(funPtr, envArg :: args)

      addStmt ctx (CExprStmt callExpr)

    | _ -> unreachable itself

  | MCallNativeAction funName ->
    let ctx = addNativeFunDecl ctx funName args tyUnit

    let args, ctx = cgExprList ctx args
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr funName, args)))

  | MPtrWriteAction ->
    match cgExprList ctx args with
    | [ ptr; CIntExpr "0"; value ], ctx -> addStmt ctx (CSetStmt(CUnaryExpr(CDerefUnary, ptr), value))
    | [ ptr; index; value ], ctx -> addStmt ctx (CSetStmt(CIndexExpr(ptr, index), value))
    | _ -> unreachable ()

let private cgPrintfnActionStmt ctx itself args =
  match args with
  | (MLitExpr (StrLit format, _)) :: args ->
    let format = CStrRawExpr(format + "\n")

    let args, ctx =
      (args, ctx)
      |> stMap
           (fun (arg, ctx) ->
             match arg with
             | MLitExpr (StrLit value, _) -> CStrRawExpr value, ctx

             | _ when tyEqual (mexprToTy arg) tyStr ->
               // Insert implicit cast from str to str ptr.
               let arg, ctx = cgExpr ctx arg
               CCallExpr(CVarExpr "str_to_c_str", [ arg ]), ctx

             | _ -> cgExpr ctx arg)

    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "printf", format :: args)))

  | _ -> unreachable itself

let private addLetStmt (ctx: CirCtx) name expr cty isStatic linkage replacing =
  match isStatic with
  | IsStatic ->
    let ctx =
      match linkage with
      | InternalLinkage -> addDecl ctx (CInternalStaticVarDecl(name, cty))
      | ExternalLinkage _ -> addDecl ctx (CStaticVarDecl(name, cty))

    match expr with
    | Some expr -> addStmt ctx (CSetStmt(CVarExpr name, expr))
    | _ -> ctx

  | NotStatic when replacing ->
    match expr with
    | Some expr -> addStmt ctx (CSetStmt(CVarExpr name, expr))
    | _ -> ctx

  | NotStatic -> addStmt ctx (CLetStmt(name, expr, cty))

let private addLetAllocStmt ctx name valTy varTy isStatic =
  match isStatic with
  | IsStatic -> unreachable () // let-alloc is used only for temporary variables.
  | NotStatic -> addStmt ctx (CLetAllocStmt(name, valTy, varTy))

let private doGenLetValStmt ctx serial expr ty =
  let name = getUniqueVarName ctx serial
  let isStatic = findStorageModifier ctx serial
  let linkage = findVarLinkage ctx serial
  let replacing = isReplacing ctx serial
  let cty, ctx = cgTyComplete ctx ty
  addLetStmt ctx name expr cty isStatic linkage replacing

let private cgPrimStmt (ctx: CirCtx) itself prim args serial resultTy =
  let conversion ctx makeExpr =
    match args with
    | [ arg ] ->
      let name = getUniqueVarName ctx serial
      let isStatic = findStorageModifier ctx serial
      let linkage = findVarLinkage ctx serial
      let replacing = isReplacing ctx serial
      let ty, ctx = cgTyComplete ctx resultTy
      let arg, ctx = cgExpr ctx arg
      addLetStmt ctx name (Some(makeExpr arg)) ty isStatic linkage replacing

    | _ -> unreachable itself

  let regular ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let replacing = isReplacing ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args)) ty isStatic linkage replacing

  let regularWithTy ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let replacing = isReplacing ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args ty)) ty isStatic linkage replacing

  match prim with
  | MIntOfStrPrim flavor ->
    let name = cStringToIntegerFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MFloatOfStrPrim flavor ->
    let name = cStringToFloatFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MCharOfStrPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_to_char", [ arg ]))

  | MStrOfBoolPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_of_bool", [ arg ]))
  | MStrOfCharPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_of_char", [ arg ]))

  | MStrOfIntPrim flavor ->
    let name = cStringOfIntegerFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStrOfFloatPrim flavor ->
    let name = cStringOfFloatFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStrGetSlicePrim -> regular ctx (fun args -> (CCallExpr(CVarExpr "str_get_slice", args)))

  | MClosurePrim funSerial ->
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let replacing = isReplacing ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    let expr, ctx =
      let ctx = cgExternFunDecl ctx funSerial
      let funExpr = CVarExpr(getUniqueFunName ctx funSerial)

      match args with
      | [ env ] -> CInitExpr([ "fun", funExpr; "env", env ], ty), ctx
      | _ -> unreachable itself

    addLetStmt ctx name (Some expr) ty isStatic linkage replacing

  | MBoxPrim ->
    match args with
    | [ arg ] -> cgBoxStmt ctx serial arg
    | _ -> unreachable itself

  | MConsPrim ->
    match args with
    | [ l; r ] -> cgConsStmt ctx serial l r
    | _ -> unreachable itself

  | MVariantPrim variantSerial ->
    regularWithTy
      ctx
      (fun args unionTy ->
        match args with
        | [ payload ] ->
          let variantName = getUniqueVariantName ctx variantSerial

          let fields =
            [ "discriminant", CVarExpr variantName
              variantName, payload ]

          CInitExpr(fields, unionTy)

        | _ -> unreachable itself)

  | MRecordPrim ->
    regularWithTy
      ctx
      (fun args recordTy ->
        let fields =
          args |> List.mapi (fun i arg -> tupleField i, arg)

        CInitExpr(fields, recordTy))

  | MCallProcPrim ->
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let replacing = isReplacing ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let ctx =
      match args with
      | MProcExpr (funSerial, _, _) :: _ -> cgExternFunDecl ctx funSerial
      | _ -> ctx

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    match args with
    | callee :: args ->
      let expr = CCallExpr(callee, args)
      addLetStmt ctx name (Some expr) ty isStatic linkage replacing

    | [] -> unreachable itself

  | MCallClosurePrim ->
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let replacing = isReplacing ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let ctx =
      match args with
      | MProcExpr (funSerial, _, _) :: _ -> cgExternFunDecl ctx funSerial
      | _ -> ctx

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    match args with
    | callee :: args ->
      let expr =
        let funPtr = CDotExpr(callee, "fun")
        let envArg = CDotExpr(callee, "env")
        CCallExpr(funPtr, envArg :: args)

      addLetStmt ctx name (Some expr) ty isStatic linkage replacing

    | [] -> unreachable itself

  | MCallNativePrim funName ->
    let ctx =
      addNativeFunDecl ctx funName args resultTy

    regular ctx (fun args -> (CCallExpr(CVarExpr funName, args)))

  | MPtrReadPrim ->
    regular
      ctx
      (fun args ->
        match args with
        | [ ptr; CIntExpr "0" ] -> CUnaryExpr(CDerefUnary, ptr)
        | [ ptr; index ] -> CIndexExpr(ptr, index)
        | _ -> unreachable ())

let private cgBoxStmt ctx serial arg =
  let argTy, ctx = cgTyComplete ctx (mexprToTy arg)
  let arg, ctx = cgExpr ctx arg

  // void const* p = malloc(sizeof T);
  let temp = getUniqueVarName ctx serial
  let isStatic = findStorageModifier ctx serial

  let ctx =
    addLetAllocStmt ctx temp argTy (CConstPtrTy CVoidTy) isStatic

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CVarExpr temp, CPtrTy argTy))

  addStmt ctx (CSetStmt(left, arg))

let private cgConsStmt ctx serial head tail =
  let temp = getUniqueVarName ctx serial
  let isStatic = findStorageModifier ctx serial
  let listTy, ctx = genListTyDef ctx (mexprToTy head)

  let listStructTy =
    match listTy with
    | CConstPtrTy it -> it
    | _ -> unreachable ()

  let ctx =
    addLetAllocStmt ctx temp listStructTy listTy isStatic

  let head, ctx = cgExpr ctx head
  let tail, ctx = cgExpr ctx tail

  let stmt =
    let fields = [ "head", head; "tail", tail ]
    CSetStmt(CUnaryExpr(CDerefUnary, CCastExpr(CVarExpr temp, CPtrTy listStructTy)), CInitExpr(fields, listStructTy))

  addStmt ctx stmt

let private cgLetValStmt ctx serial init ty =
  let init, ctx =
    match init with
    | None -> None, ctx

    | Some init ->
      let init, ctx = cgExpr ctx init
      Some init, ctx

  doGenLetValStmt ctx serial init ty

let private cgSetStmt ctx serial right =
  let right, ctx = cgExpr ctx right
  let name = getUniqueVarName ctx serial
  let left = CVarExpr(name)
  addStmt ctx (CSetStmt(left, right))

let private cgReturnStmt ctx expr =
  if expr |> mexprToTy |> tyIsUnit then
    addStmt ctx (CReturnStmt None)
  else
    let expr, ctx = cgExpr ctx expr
    addStmt ctx (CReturnStmt(Some expr))

// FIXME: Without the result type ascription, invalid code is generated for some reason.
let private cgTerminatorAsBlock ctx terminator : CStmt list * CirCtx =
  cgBlock ctx [ MTerminatorStmt(terminator, noLoc) ]

let private cgTerminatorStmt ctx stmt =
  match stmt with
  | MReturnTerminator expr -> cgReturnStmt ctx expr
  | MGotoTerminator label -> addStmt ctx (CGotoStmt label)

  | MIfTerminator (cond, thenCl, elseCl) ->
    let cond, ctx = cgExpr ctx cond
    let thenCl, ctx = cgTerminatorAsBlock ctx thenCl
    let elseCl, ctx = cgTerminatorAsBlock ctx elseCl
    addStmt ctx (CIfStmt(cond, thenCl, elseCl))

  | MSwitchTerminator (cond, clauses) ->
    let cond, ctx = cgExpr ctx cond

    let clauses, ctx =
      (clauses, ctx)
      |> stMap
           (fun (clause: MSwitchClause, ctx) ->
             let cases =
               clause.Cases
               |> List.map (fun cond -> cgConst ctx cond)

             let stmts, ctx =
               cgTerminatorAsBlock ctx clause.Terminator

             (cases, clause.IsDefault, stmts), ctx)

    addStmt ctx (CSwitchStmt(cond, clauses))

  | MExitTerminator arg ->
    let arg, ctx = cgExpr ctx arg
    addStmt ctx (CExprStmt(CCallExpr(CVarExpr "exit", [ arg ])))

let private cgStmt ctx stmt =
  match stmt with
  | MActionStmt (action, args, _) -> cgActionStmt ctx stmt action args
  | MPrimStmt (prim, args, temp, resultTy, _) -> cgPrimStmt ctx stmt prim args temp resultTy
  | MLetValStmt (serial, init, ty, _) -> cgLetValStmt ctx serial init ty
  | MSetStmt (serial, right, _) -> cgSetStmt ctx serial right
  | MLabelStmt (label, _) -> addStmt ctx (CLabelStmt label)

  | MGotoIfStmt (cond, label) ->
    let cond, ctx = cgExpr ctx cond
    addStmt ctx (CGotoIfStmt(cond, label))

  | MTerminatorStmt (terminator, _loc) -> cgTerminatorStmt ctx terminator

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

let private cgDecls (ctx: CirCtx) decls =
  match decls with
  | [] -> ctx

  | MProcDecl (callee, args, body, resultTy, _) :: decls ->
    let def: FunDef = ctx.Rx.Funs |> mapFind callee

    let funName, args =
      if isMainFun ctx callee then
        "milone_main", []
      else
        getUniqueFunName ctx callee, args

    let rec collectArgs acc ctx args =
      match args with
      | [] -> List.rev acc, ctx
      | (arg, ty, _) :: args ->
        let name = getUniqueVarName ctx arg
        let cty, ctx = cgTyComplete ctx ty
        collectArgs ((name, cty) :: acc) ctx args

    let collectFunLocalStmts (ctx: CirCtx) =
      ctx.Rx.FunLocals
      |> multimapFind callee
      |> List.mapFold
           (fun (ctx: CirCtx) (varSerial, ty) ->
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

      match def.Linkage with
      | InternalLinkage -> CStaticFunDecl(funName, args, resultTy, body)
      | ExternalLinkage _ -> CFunDecl(funName, args, resultTy, body)

    let ctx = addDecl ctx funDecl
    cgDecls ctx decls

  | MNativeDecl (code, _) :: decls ->
    let ctx = addDecl ctx (CNativeDecl code)
    cgDecls ctx decls

// Sort declarations by kind.
// Without this, static variable definition can appear before its type definition.
let private sortDecls (decls: CDecl list) : CDecl list =
  let types, vars, bodies =
    decls
    |> List.fold
         (fun (types, vars, bodies) decl ->
           match decl with
           | CErrorDecl _
           | CStructForwardDecl _
           | CStructDecl _
           | CEnumDecl _ -> decl :: types, vars, bodies

           | CStaticVarDecl _
           | CInternalStaticVarDecl _
           | CExternVarDecl _ -> types, decl :: vars, bodies

           | CNativeDecl _
           | CFunForwardDecl _
           | CFunDecl _
           | CStaticFunDecl _ -> types, vars, decl :: bodies)
         ([], [], [])

  List.collect List.rev [ types; vars; bodies ]

let private cgModule (ctx: CirCtx) (m: MModule) : DocId * CDecl list =
  let varUniqueNames, _ =
    renameIdents2 m.Vars (fun name -> true, name) ctx.Rx.VarUniqueNames ctx.Rx.ValueNameFreq

  let ctx: CirCtx =
    { Rx =
        { ctx.Rx with
            DocIdOpt = Some m.DocId
            VarUniqueNames = varUniqueNames }
      TyEnv = TMap.empty tyCompare
      TyUniqueNames = ctx.TyUniqueNames
      Stmts = []
      Decls = []
      VarDecls = TSet.empty varSerialCompare
      FunDecls = TSet.empty funSerialCompare }

  // Generate decls.
  let ctx = cgDecls ctx m.Decls
  let decls = List.rev ctx.Decls |> sortDecls

  m.DocId, decls

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genCir (modules: MModule list, mirResult: MirResult) : (DocId * CDecl list) list =
  let ctx = ofMirResult mirResult

  modules
  |> __parallelMap (cgModule ctx)
  |> List.filter (fun (_, decls) -> decls |> List.isEmpty |> not)
