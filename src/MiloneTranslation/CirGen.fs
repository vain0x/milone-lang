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
open MiloneTranslation.Cir
open MiloneTranslation.Hir
open MiloneTranslation.Mir
open MiloneTranslation.MirGen

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module S = MiloneStd.StdString

let private valueSymbolCompare l r =
  let encode symbol =
    match symbol with
    | VarSymbol (VarSerial serial) -> serial
    | FunSymbol (FunSerial serial) -> serial
    | VariantSymbol (VariantSerial serial) -> serial

  compare (encode l) (encode r)

let private unwrapListTy ty =
  match ty with
  | Ty (ListTk, [ itemTy ]) -> itemTy
  | _ -> unreachable ()

let private renameIdents toIdent toKey mapFuns (defMap: AssocMap<_, _>) =
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

let private tupleField (i: int) = "t" + string i

/// Calculates discriminant type's name of union type.
let private toDiscriminantEnumName (name: string) = name + "Discriminant"

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CirCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    MainFunOpt: FunSerial option
    ValueUniqueNames: AssocMap<ValueSymbol, Ident>
    TyEnv: AssocMap<Ty, CTyInstance * CTy>
    Tys: AssocMap<TySerial, TyDef>
    TyUniqueNames: AssocMap<Ty, Ident>
    Stmts: CStmt list
    Decls: CDecl list

    /// Doc ID of current module.
    DocId: DocId
    /// Already-declared functions.
    VarDecls: AssocSet<VarSerial>
    FunDecls: AssocSet<FunSerial> }

let private ofMirCtx (mirCtx: MirCtx) : CirCtx =
  let valueUniqueNames =
    let m = TMap.empty valueSymbolCompare

    let m =
      mirCtx.Vars
      |> TMap.fold
           (fun acc varSerial (varDef: VarDef) ->
             let name =
               match varDef.Linkage with
               | InternalLinkage -> varDef.Name
               | ExternalLinkage name -> name

             acc |> TMap.add (VarSymbol varSerial) name)
           m

    let m =
      mirCtx.Funs
      |> TMap.fold
           (fun acc funSerial (funDef: FunDef) ->
             let name =
               match funDef.Linkage with
               | InternalLinkage -> funDef.Name
               | ExternalLinkage name -> name

             acc |> TMap.add (FunSymbol funSerial) name)
           m

    let m =
      mirCtx.Variants
      |> TMap.fold
           (fun acc variantSerial (variantDef: VariantDef) ->
             acc
             |> TMap.add (VariantSymbol variantSerial) variantDef.Name)
           m

    m |> renameIdents id fst valueSymbolCompare

  let tyNames =
    let toKey (serial, tyDef) =
      match tyDef with
      | UnionTyDef _ -> tyUnion serial
      | RecordTyDef _ -> tyRecord serial

      | MetaTyDef _ -> unreachable () // Resolved in Typing.

    mirCtx.Tys
    |> renameIdents tyDefToName toKey tyCompare

  { Vars = mirCtx.Vars
    Funs = mirCtx.Funs
    Variants = mirCtx.Variants
    MainFunOpt = mirCtx.MainFunOpt
    ValueUniqueNames = valueUniqueNames
    TyEnv = TMap.empty tyCompare
    Tys = mirCtx.Tys
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []

    DocId = ""
    VarDecls = TSet.empty varSerialCompare
    FunDecls = TSet.empty funSerialCompare }

let private findStorageModifier (ctx: CirCtx) varSerial =
  match ctx.Vars |> TMap.tryFind varSerial with
  | Some varDef -> varDef.IsStatic

  | _ -> IsStatic

let private findVarLinkage (ctx: CirCtx) varSerial =
  match ctx.Vars |> TMap.tryFind varSerial with
  | Some varDef -> varDef.Linkage

  | _ -> InternalLinkage

let private isMainFun (ctx: CirCtx) funSerial =
  match ctx.MainFunOpt with
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
  | _ -> false

let private enterBlock (ctx: CirCtx) = { ctx with Stmts = [] }

let private rollback (bCtx: CirCtx) (dCtx: CirCtx) = { dCtx with Stmts = bCtx.Stmts }

let private addStmt (ctx: CirCtx) stmt = { ctx with Stmts = stmt :: ctx.Stmts }

let private addDecl (ctx: CirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

// -----------------------------------------------
// Type definition generation
// -----------------------------------------------

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

    let argTys, ctx =
      (argTys, ctx)
      |> stMap (fun (ty, ctx) -> cgTyComplete ctx ty)

    let resultTy, (ctx: CirCtx) = cgTyComplete ctx resultTy

    let fields =
      [ "fun", CFunPtrTy(envTy :: argTys, resultTy)
        "env", envTy ]

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add funTy (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteOptionTyDecl (ctx: CirCtx) itemTy =
  let optionTy = tyOption itemTy

  match ctx.TyEnv |> TMap.tryFind optionTy with
  | Some (_, ty) -> ty, ctx

  | None ->
    let structName, ctx = getUniqueTyName ctx optionTy
    let selfTy = CStructTy structName

    let ctx =
      { ctx with
          TyEnv =
            ctx.TyEnv
            |> TMap.add optionTy (CTyDeclared, selfTy) }

    selfTy, ctx

let private genOptionTyDef (ctx: CirCtx) itemTy =
  let optionTy = tyOption itemTy

  match ctx.TyEnv |> TMap.tryFind optionTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let structName, ctx = getUniqueTyName ctx optionTy
    let selfTy, ctx = genIncompleteOptionTyDecl ctx itemTy

    let itemTy, (ctx: CirCtx) = cgTyComplete ctx itemTy
    let fields = [ "some", CBoolTy; "value", itemTy ]

    let ctx =
      { ctx with
          Decls = CStructDecl(structName, fields, []) :: ctx.Decls
          TyEnv =
            ctx.TyEnv
            |> TMap.add optionTy (CTyDefined, selfTy) }

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

let private genIncompleteTupleTyDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys

  match ctx.TyEnv |> TMap.tryFind tupleTy with
  | Some (_, ty) -> ty, ctx

  | None ->
    let structName, ctx = getUniqueTyName ctx tupleTy
    let selfTy = CStructTy structName

    let ctx =
      { ctx with
          TyEnv =
            ctx.TyEnv
            |> TMap.add tupleTy (CTyDeclared, selfTy) }

    selfTy, ctx

let private genTupleTyDef (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys

  match ctx.TyEnv |> TMap.tryFind tupleTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
    let structName, ctx = getUniqueTyName ctx tupleTy
    let selfTy, ctx = genIncompleteTupleTyDecl ctx itemTys

    let rec go i itemTys =
      match itemTys with
      | [] -> []

      | itemTy :: itemTys ->
        let field = tupleField i, itemTy
        field :: go (i + 1) itemTys

    let itemTys, (ctx: CirCtx) =
      (itemTys, ctx)
      |> stMap (fun (ty, ctx) -> cgTyComplete ctx ty)

    let fields = go 0 itemTys

    let tupleDecl = CStructDecl(structName, fields, [])

    let ctx =
      { ctx with
          Decls = tupleDecl :: ctx.Decls
          TyEnv = ctx.TyEnv |> TMap.add tupleTy (CTyDefined, selfTy) }

    selfTy, ctx

let private genIncompleteUnionTyDecl (ctx: CirCtx) tySerial =
  let unionTyRef = tyUnion tySerial

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
  let unionTyRef = tyUnion tySerial

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
             let v = ctx.Variants |> mapFind variantSerial
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
  ctx.ValueUniqueNames
  |> mapFind (VarSymbol varSerial)

let private getUniqueFunName (ctx: CirCtx) funSerial =
  ctx.ValueUniqueNames
  |> mapFind (FunSymbol funSerial)

let private getUniqueVariantName (ctx: CirCtx) variantSerial =
  ctx.ValueUniqueNames
  |> mapFind (VariantSymbol variantSerial)

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
  | Some (paramTys, resultTy) ->
    let paramTys, ctx =
      (paramTys, ctx)
      |> stMap (fun (ty, ctx) -> cgTyComplete ctx ty)

    let resultTy, ctx = cgTyComplete ctx resultTy
    CFunPtrTy(paramTys, resultTy), ctx

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
  | TupleTk, _ -> genIncompleteTupleTyDecl ctx tyArgs

  | OptionTk, [ itemTy ] -> genIncompleteOptionTyDecl ctx itemTy
  | OptionTk, _ -> unreachable ()

  | ListTk, [ itemTy ] -> genIncompleteListTyDecl ctx itemTy
  | ListTk, _ -> unreachable ()

  | VoidTk, _ -> CVoidTy, ctx
  | NativePtrTk isMut, [ itemTy ] -> cgNativePtrTy ctx isMut itemTy
  | NativePtrTk _, _ -> unreachable ()
  | NativeFunTk, _ -> cgNativeFunTy ctx tyArgs
  | NativeTypeTk code, _ -> CEmbedTy code, ctx

  | UnionTk tySerial, _ -> genIncompleteUnionTyDecl ctx tySerial
  | RecordTk tySerial, _ -> genIncompleteRecordTyDecl ctx tySerial

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
  | TupleTk, _ -> genTupleTyDef ctx tyArgs

  | OptionTk, [ itemTy ] -> genOptionTyDef ctx itemTy
  | OptionTk, _ -> unreachable ()

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
    match ctx.Tys |> TMap.tryFind serial with
    | Some (UnionTyDef (_, variants, _)) -> genUnionTyDef ctx serial variants

    | _ -> unreachable () // Union type undefined?

  | RecordTk serial, _ ->
    match ctx.Tys |> TMap.tryFind serial with
    | Some (RecordTyDef (_, fields, _)) -> genRecordTyDef ctx serial fields

    | _ -> unreachable () // Record type undefined?

  | MetaTk _, _ -> unreachable () // Resolved in Typing.

// -----------------------------------------------
// Extern decl
// -----------------------------------------------

let private cgExternVarDecl (ctx: CirCtx) varSerial =
  if TSet.contains varSerial ctx.VarDecls then
    ctx
  else
    let varDef = ctx.Vars |> mapFind varSerial

    let name = getUniqueVarName ctx varSerial
    let ty, ctx = cgTyComplete ctx varDef.Ty

    let ctx = addDecl ctx (CExternVarDecl(name, ty))

    { ctx with
        VarDecls = ctx.VarDecls |> TSet.add varSerial }

let private cgExternFunDecl (ctx: CirCtx) funSerial =
  if TSet.contains funSerial ctx.FunDecls then
    ctx
  else
    let funDef = ctx.Funs |> mapFind funSerial
    let (Loc (docId, _, _)) = funDef.Loc

    if docId = ctx.DocId then
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

      let argTys, ctx =
        (argTys, ctx)
        |> stMap (fun (argTy, ctx) -> cgTyComplete ctx argTy)

      let resultTy, ctx = cgTyComplete ctx resultTy

      let ctx : CirCtx =
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
  | MNoneGv ->
    let ty, ctx = cgTyComplete ctx ty
    CInitExpr([ "some", CVarExpr "false" ], ty), ctx

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

  | MOptionIsSomeUnary ->
    let _, ctx = cgTyComplete ctx ty
    CDotExpr(arg, "some"), ctx

  | MOptionToValueUnary ->
    let _, ctx = cgTyComplete ctx ty
    CDotExpr(arg, "value"), ctx

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

  | MVarExpr (serial, _, _) ->
    invoke
      (fun () ->
        let ctx =
          match findStorageModifier ctx serial with
          | IsStatic -> cgExternVarDecl ctx serial
          | NotStatic -> ctx

        CVarExpr(getUniqueVarName ctx serial), ctx)

  | MProcExpr (serial, _, _) -> CVarExpr(getUniqueFunName ctx serial), ctx

  | MVariantExpr (_, serial, ty, _) -> genVariantNameExpr ctx serial ty
  | MDiscriminantConstExpr (variantSerial, _) -> genDiscriminant ctx variantSerial, ctx
  | MGenericValueExpr (genericValue, ty, _) -> genGenericValue ctx genericValue ty
  | MUnaryExpr (op, arg, ty, loc) -> genUnaryExpr ctx op arg ty loc
  | MBinaryExpr (op, l, r, _, _) -> genExprBin ctx op l r

  | MNativeExpr (code, _, _) -> CNativeExpr code, ctx

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private addNativeFunDecl ctx funName args resultTy =
  let argTys, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> cgTyComplete ctx (mexprToTy arg))

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

  | MCallNativeAction funName ->
    let ctx =
      addNativeFunDecl ctx funName args CVoidTy

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

let private addLetStmt ctx name expr cty isStatic linkage =
  match isStatic with
  | IsStatic ->
    let ctx =
      match linkage with
      | InternalLinkage -> addDecl ctx (CInternalStaticVarDecl(name, cty))
      | ExternalLinkage _ -> addDecl ctx (CStaticVarDecl(name, cty))

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
  let cty, ctx = cgTyComplete ctx ty
  addLetStmt ctx name expr cty isStatic linkage

let private cgPrimStmt (ctx: CirCtx) itself prim args serial =
  let resultTy = (ctx.Vars |> mapFind serial).Ty

  let conversion ctx makeExpr =
    match args with
    | [ arg ] ->
      let name = getUniqueVarName ctx serial
      let isStatic = findStorageModifier ctx serial
      let linkage = findVarLinkage ctx serial
      let ty, ctx = cgTyComplete ctx resultTy
      let arg, ctx = cgExpr ctx arg
      addLetStmt ctx name (Some(makeExpr arg)) ty isStatic linkage

    | _ -> unreachable itself

  let regular ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args)) ty isStatic linkage

  let regularWithTy ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args ty)) ty isStatic linkage

  match prim with
  | MIntOfStrPrim flavor ->
    let name = cStringToIntegerFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MFloatOfStrPrim flavor ->
    let name = cStringToFloatFunName flavor
    conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MCharOfStrPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_to_char", [ arg ]))

  | MStrOfBoolPrim -> todo ()
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

    addLetStmt ctx name (Some expr) ty isStatic linkage

  | MBoxPrim ->
    match args with
    | [ arg ] -> cgBoxStmt ctx serial arg
    | _ -> unreachable itself

  | MOptionSomePrim ->
    regularWithTy
      ctx
      (fun args optionTy ->
        match args with
        | [ item ] ->
          let fields =
            [ "some", CVarExpr "true"
              "value", item ]

          CInitExpr(fields, optionTy)
        | _ -> unreachable itself)

  | MConsPrim ->
    match args with
    | [ l; r ] -> cgConsStmt ctx serial l r
    | _ -> unreachable itself

  | MTuplePrim ->
    regularWithTy
      ctx
      (fun args tupleTy ->
        let fields =
          args |> List.mapi (fun i arg -> tupleField i, arg)

        CInitExpr(fields, tupleTy))

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
    let ty, ctx = cgTyComplete ctx resultTy

    let ctx =
      match args with
      | MProcExpr (funSerial, _, loc) :: _ -> cgExternFunDecl ctx funSerial
      | _ -> ctx

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    match args with
    | callee :: args ->
      let expr = CCallExpr(callee, args)
      addLetStmt ctx name (Some expr) ty isStatic linkage

    | [] -> unreachable itself

  | MCallClosurePrim ->
    let name = getUniqueVarName ctx serial
    let isStatic = findStorageModifier ctx serial
    let linkage = findVarLinkage ctx serial
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

      addLetStmt ctx name (Some expr) ty isStatic linkage

    | [] -> unreachable itself

  | MCallNativePrim funName ->
    let ctx =
      let resultTy, ctx = cgTyComplete ctx resultTy
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

let private cgCallPrimExpr ctx itself serial prim args = cgPrimStmt ctx itself prim args serial

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
    invoke
      (fun () ->
        let arg, ctx = cgExpr ctx arg
        addStmt ctx (CExprStmt(CCallExpr(CVarExpr "exit", [ arg ]))))

let private cgStmt ctx stmt =
  match stmt with
  | MActionStmt (action, args, _) -> cgActionStmt ctx stmt action args
  | MPrimStmt (prim, args, temp, _) -> cgPrimStmt ctx stmt prim args temp
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
  let bodyCtx : CirCtx = cgStmts (enterBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = rollback ctx bodyCtx
  List.rev stmts, ctx

let private cgBlocks (ctx: CirCtx) (blocks: MBlock list) =
  match blocks with
  | [ block ] -> cgBlock ctx block.Stmts

  | _ -> todo ()

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
    let def : FunDef = ctx.Funs |> mapFind callee

    let funName, args =
      if isMainFun ctx callee then
        "milone_main", []
      else
        getUniqueFunName ctx callee, args

    let rec go acc ctx args =
      match args with
      | [] -> List.rev acc, ctx
      | (arg, ty, _) :: args ->
        let name = getUniqueVarName ctx arg
        let cty, ctx = cgTyComplete ctx ty
        go ((name, cty) :: acc) ctx args

    let args, ctx = go [] ctx args
    let body, ctx = cgBlocks ctx body
    let resultTy, ctx = cgTyComplete ctx resultTy

    let funDecl =
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

// -----------------------------------------------
// Interface
// -----------------------------------------------

let genCir (decls, mirCtx: MirCtx) : (DocId * CDecl list) list =
  let ctx = ofMirCtx mirCtx

  // Split into modules based on docId.
  let acc, _ =
    decls
    |> List.fold
         (fun moduleMap decl ->
           let (Loc (docId, _, _)) = mDeclToLoc decl

           moduleMap |> multimapAdd docId decl)
         (TMap.empty compare)
    |> TMap.fold
         (fun (acc, ctx: CirCtx) docId declAcc ->
           // Reset state.
           let ctx =
             { ctx with
                 TyEnv = TMap.empty tyCompare
                 Stmts = []
                 Decls = []
                 VarDecls = TSet.empty varSerialCompare
                 FunDecls = TSet.empty funSerialCompare
                 DocId = docId }

           // Generate decls.
           let decls = List.rev declAcc
           let ctx = cgDecls ctx decls
           let decls = List.rev ctx.Decls |> sortDecls

           (docId, decls) :: acc, ctx)
         ([], ctx)

  List.rev acc
