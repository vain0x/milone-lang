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
module rec MiloneLang.CirGen

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers
open MiloneLang.TySystem
open MiloneLang.Hir
open MiloneLang.Mir
open MiloneLang.MirGen
open MiloneLang.Cir

let private valueSymbolCmp l r =
  let encode symbol =
    match symbol with
    | VarSymbol (VarSerial serial) -> serial
    | FunSymbol (FunSerial serial) -> serial
    | VariantSymbol (VariantSerial serial) -> serial

  compare (encode l) (encode r)

let private renameIdents toIdent toKey mapFuns (defMap: AssocMap<_, _>) =
  let rename (ident: string) (index: int) =
    if index = 0 then ident + "_" else ident + "_" + string index

  // Group serials by ident.
  let rec go acc xs =
    match xs with
    | [] -> acc

    | (serial, def) :: xs ->
        let ident = toIdent def

        let serials =
          acc |> mapTryFind ident |> Option.defaultValue []

        let acc =
          acc |> mapAdd ident ((serial, def) :: serials)

        go acc xs

  let serialsMap =
    go (mapEmpty compare) (defMap |> mapToList)

  let addIdent ident (identMap, index) serial =
    identMap
    |> mapAdd (toKey serial) (rename ident index),
    index + 1

  let addIdents identMap ident serials =
    serials
    |> List.rev
    |> List.fold (addIdent ident) (identMap, 0)
    |> fst

  serialsMap |> mapFold addIdents (mapEmpty mapFuns)

let private tupleField (i: int) = "t" + string i

/// Calculates tag type's name of union type.
let private toTagEnumName (name: string) = name + "Tag"

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
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
    Logs: (Log * Loc) list }

let private ofMirCtx (mirCtx: MirCtx): CirCtx =
  let valueUniqueNames =
    let m = mapEmpty valueSymbolCmp

    let m =
      mirCtx.Vars
      |> mapFold (fun acc varSerial varDef ->
           acc
           |> mapAdd (VarSymbol varSerial) (varDefToName varDef)) m

    let m =
      mirCtx.Funs
      |> mapFold (fun acc funSerial (funDef: FunDef) -> acc |> mapAdd (FunSymbol funSerial) funDef.Name) m

    let m =
      mirCtx.Variants
      |> mapFold (fun acc variantSerial (variantDef: VariantDef) ->
           acc
           |> mapAdd (VariantSymbol variantSerial) variantDef.Name) m

    m |> renameIdents id fst valueSymbolCmp

  let tyNames =
    let toKey (serial, tyDef) =
      match tyDef with
      | MetaTyDef _
      | UniversalTyDef _ -> MetaTy(serial, noLoc)

      | SynonymTyDef _ -> tySynonym serial []
      | UnionTyDef _ -> tyUnion serial
      | RecordTyDef _ -> tyRecord serial

    mirCtx.Tys |> renameIdents tyDefToName toKey tyCmp

  { Vars = mirCtx.Vars
    Funs = mirCtx.Funs
    Variants = mirCtx.Variants
    MainFunOpt = mirCtx.MainFunOpt
    ValueUniqueNames = valueUniqueNames
    TyEnv = mapEmpty tyCmp
    Tys = mirCtx.Tys
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []
    Logs = mirCtx.Logs }

let private findStorageModifier (ctx: CirCtx) varSerial =
  match ctx.Vars |> mapTryFind varSerial with
  | Some (VarDef (_, storageModifier, _, _)) -> storageModifier

  | _ -> StaticSM

let private isMainFun (ctx: CirCtx) funSerial =
  match ctx.MainFunOpt with
  | Some mainFun -> funSerialCmp mainFun funSerial = 0
  | _ -> false

let private addError (ctx: CirCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

let private enterBlock (ctx: CirCtx) = { ctx with Stmts = [] }

let private rollback (bCtx: CirCtx) (dCtx: CirCtx) = { dCtx with Stmts = bCtx.Stmts }

let private addStmt (ctx: CirCtx) stmt = { ctx with Stmts = stmt :: ctx.Stmts }

let private addDecl (ctx: CirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

// -----------------------------------------------
// Type definition generation
// -----------------------------------------------

let private genIncompleteFunTyDecl (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> mapTryFind funTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let structName, (ctx: CirCtx) = getUniqueTyName ctx funTy
      let funStructTy = CStructTy structName

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd funTy (CTyDeclared, funStructTy) }

      funStructTy, ctx

let private genFunTyDef (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> mapTryFind funTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let structName, ctx = getUniqueTyName ctx funTy
      let selfTy, ctx = genIncompleteFunTyDecl ctx sTy tTy

      let envTy = CConstPtrTy CVoidTy
      let _, argTys, resultTy = tyToArgList funTy

      let argTys, ctx =
        (argTys, ctx)
        |> stMap (fun (ty, ctx) -> cgTyIncomplete ctx ty)

      let resultTy, (ctx: CirCtx) = cgTyComplete ctx resultTy

      let fields =
        [ "fun", CFunPtrTy(envTy :: argTys, resultTy)
          "env", envTy ]

      let ctx =
        { ctx with
            Decls = CStructDecl(structName, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd funTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteListTyDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let structName, ctx = getUniqueTyName ctx listTy
      let selfTy = CConstPtrTy(CStructTy structName)

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private genListTyDef (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let structName, ctx = getUniqueTyName ctx listTy
      let selfTy, ctx = genIncompleteListTyDecl ctx itemTy

      let itemTy, (ctx: CirCtx) = cgTyComplete ctx itemTy
      let fields = [ "head", itemTy; "tail", selfTy ]

      let ctx =
        { ctx with
            Decls = CStructDecl(structName, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteTupleTyDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let structName, ctx = getUniqueTyName ctx tupleTy
      let selfTy = CStructTy structName

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private genTupleTyDef (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
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
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteUnionTyDecl (ctx: CirCtx) tySerial =
  let unionTyRef = tyUnion tySerial
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let structName, ctx = getUniqueTyName ctx unionTyRef
      let selfTy = CStructTy structName

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd unionTyRef (CTyDeclared, selfTy) }

      selfTy, ctx

let private genUnionTyDef (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyUnion tySerial
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let structName, ctx = getUniqueTyName ctx unionTyRef
      let selfTy, ctx = genIncompleteUnionTyDecl ctx tySerial

      let tagEnumName = toTagEnumName structName
      let tagTy = CEnumTy tagEnumName

      let variants =
        variants
        |> List.map (fun variantSerial ->
             let v = ctx.Variants |> mapFind variantSerial
             v.Name, variantSerial, v.HasPayload, v.PayloadTy)

      let tags =
        variants
        |> List.map (fun (_, serial, _, _) -> getUniqueVariantName ctx serial)

      let variants, ctx =
        (variants, ctx)
        |> stFlatMap (fun ((_, serial, hasPayload, payloadTy), acc, ctx) ->
             if hasPayload then
               let payloadTy, ctx = cgTyComplete ctx payloadTy
               (getUniqueVariantName ctx serial, payloadTy)
               :: acc,
               ctx
             else
               acc, ctx)

      let tagEnumDecl = CEnumDecl(tagEnumName, tags)

      let structDecl =
        CStructDecl(structName, [ "tag", tagTy ], variants)

      let ctx =
        { ctx with
            Decls = structDecl :: tagEnumDecl :: ctx.Decls
            TyEnv =
              ctx.TyEnv
              |> mapAdd unionTyRef (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteRecordTyDecl (ctx: CirCtx) tySerial =
  let recordTyRef = tyRecord tySerial

  match ctx.TyEnv |> mapTryFind recordTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let structName, ctx = getUniqueTyName ctx recordTyRef
      let selfTy = CStructTy structName

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd recordTyRef (CTyDeclared, selfTy) }

      selfTy, ctx

let private genRecordTyDef ctx tySerial fields =
  let recordTyRef = tyRecord tySerial
  let structName, ctx = getUniqueTyName ctx recordTyRef
  let selfTy, ctx = genIncompleteRecordTyDecl ctx tySerial

  match ctx.TyEnv |> mapTryFind recordTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let fields, (ctx: CirCtx) =
        (fields, ctx)
        |> stMap (fun ((name, ty, _), ctx) ->
             let ty, ctx = cgTyComplete ctx ty
             (name, ty), ctx)

      let ctx =
        { ctx with
            Decls = CStructDecl(structName, fields, []) :: ctx.Decls
            TyEnv =
              ctx.TyEnv
              |> mapAdd recordTyRef (CTyDefined, selfTy) }

      selfTy, ctx

// -----------------------------------------------
// Naming
// -----------------------------------------------

let private getUniqueVarName (ctx: CirCtx) varSerial =
  match ctx.ValueUniqueNames
        |> mapTryFind (VarSymbol varSerial) with
  | Some name -> name
  | None -> failwithf "Never: Unknown var serial=%s" (objToString varSerial)

let private getUniqueFunName (ctx: CirCtx) funSerial =
  match ctx.ValueUniqueNames
        |> mapTryFind (FunSymbol funSerial) with
  | Some name -> name
  | None -> failwithf "Never: Unknown fun serial=%s" (objToString funSerial)

let private getUniqueVariantName (ctx: CirCtx) variantSerial =
  match ctx.ValueUniqueNames
        |> mapTryFind (VariantSymbol variantSerial) with
  | Some name -> name
  | None -> failwithf "Never: Unknown variant serial=%s" (objToString variantSerial)

let private getUniqueTyName (ctx: CirCtx) ty: _ * CirCtx =
  let rec go ty (ctx: CirCtx) =
    let tyToUniqueName ty =
      match ty with
      | AppTy (IntTyCtor flavor, _) -> cIntegerTyPascalName flavor, ctx
      | AppTy (FloatTyCtor flavor, _) -> cFloatTyPascalName flavor, ctx
      | AppTy (BoolTyCtor, _) -> "Bool", ctx
      | AppTy (CharTyCtor, _) -> "Char", ctx
      | AppTy (StrTyCtor, _) -> "String", ctx

      | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
      | AppTy (ObjTyCtor, _) -> "Object", ctx

      | AppTy (FunTyCtor, _) ->
          let arity, argTys, resultTy = tyToArgList ty

          let argTys, ctx =
            (argTys, ctx)
            |> stMap (fun (argTy, ctx) -> ctx |> go argTy)

          let resultTy, ctx = ctx |> go resultTy

          let funTy =
            (argTys |> strConcat)
            + resultTy
            + "Fun"
            + string arity

          funTy, ctx

      | AppTy (ListTyCtor, [ itemTy ]) ->
          let itemTy, ctx = ctx |> go itemTy
          let listTy = itemTy + "List"
          listTy, ctx

      | AppTy (VoidTyCtor, _) -> "Void", ctx

      | AppTy (NativePtrTyCtor isMut, [ itemTy ]) ->
          let itemTy, ctx = ctx |> go itemTy

          let ptrTy =
            match isMut with
            | IsConst -> itemTy + "ConstPtr"
            | IsMut -> itemTy + "MutPtr"

          ptrTy, ctx

      | AppTy (NativeFunTyCtor, tyArgs) ->
          let tyArgs, ctx =
            (tyArgs, ctx)
            |> stMap (fun (ty, ctx) -> ctx |> go ty)

          let funTy =
            (tyArgs |> strConcat)
            + "NativeFun"
            + string (List.length tyArgs - 1)

          funTy, ctx

      | AppTy (NativeTypeTyCtor code, _) -> code, ctx

      | AppTy (TupleTyCtor, []) -> "Unit", ctx

      | AppTy (TupleTyCtor, itemTys) ->
          let len = itemTys |> List.length

          let itemTys, ctx =
            (itemTys, ctx)
            |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)

          let tupleTy =
            (itemTys |> strConcat) + "Tuple" + string len

          tupleTy, ctx

      | AppTy (ListTyCtor, _)
      | AppTy (FunTyCtor, _)
      | AppTy (NativePtrTyCtor _, _)
      | AppTy (SynonymTyCtor _, _)
      | AppTy (UnionTyCtor _, _)
      | AppTy (RecordTyCtor _, _)
      | AppTy (UnresolvedTyCtor _, _)
      | ErrorTy _ ->
          // FIXME: collect error
          failwithf "/* unknown ty %A */" ty

    // Memoization.
    match ctx.TyUniqueNames |> mapTryFind ty with
    | Some name -> name, ctx

    | None ->
        let name, ctx = tyToUniqueName ty

        let ctx =
          { ctx with
              TyUniqueNames = ctx.TyUniqueNames |> mapAdd ty name }

        name, ctx

  go ty ctx

let private cgNativePtrTy ctx isMut itemTy =
  let itemTy, ctx = cgTyIncomplete ctx itemTy

  match isMut with
  | IsConst -> CConstPtrTy itemTy, ctx
  | IsMut -> CPtrTy itemTy, ctx

let private cgNativeFunTy ctx tys =
  match splitLast tys with
  | None -> failwith "NEVER"
  | Some (paramTys, resultTy) ->
      let paramTys, ctx =
        (paramTys, ctx)
        |> stMap (fun (ty, ctx) -> cgTyComplete ctx ty)

      let resultTy, ctx = cgTyComplete ctx resultTy
      CFunPtrTy(paramTys, resultTy), ctx

/// Converts a type to incomplete type.
/// whose type definition is not necessary to be visible.
let private cgTyIncomplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (TupleTyCtor, []) -> CIntTy(IntFlavor(Signed, I32)), ctx
  | AppTy (IntTyCtor flavor, _) -> CIntTy flavor, ctx
  | AppTy (FloatTyCtor flavor, _) -> CFloatTy flavor, ctx
  | AppTy (BoolTyCtor, _) -> CBoolTy, ctx
  | AppTy (CharTyCtor, _) -> CCharTy, ctx
  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  // FIXME: Unresolved type variables are `obj` for now.
  | MetaTy _
  | AppTy (ObjTyCtor, _) -> CConstPtrTy CVoidTy, ctx

  | AppTy (FunTyCtor, [ sTy; tTy ]) -> genIncompleteFunTyDecl ctx sTy tTy

  | AppTy (ListTyCtor, [ itemTy ]) -> genIncompleteListTyDecl ctx itemTy

  | AppTy (TupleTyCtor, itemTys) -> genIncompleteTupleTyDecl ctx itemTys

  | AppTy (VoidTyCtor, _) -> CVoidTy, ctx

  | AppTy (NativePtrTyCtor isMut, [ itemTy ]) -> cgNativePtrTy ctx isMut itemTy

  | AppTy (NativeFunTyCtor, tys) -> cgNativeFunTy ctx tys

  | AppTy (NativeTypeTyCtor code, _) -> CEmbedTy code, ctx

  | AppTy (SynonymTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyIncomplete ctx ty

      | _ -> failwithf "NEVER: synonym type undefined?"

  | AppTy (UnionTyCtor serial, _) -> genIncompleteUnionTyDecl ctx serial

  | AppTy (RecordTyCtor serial, _) -> genIncompleteRecordTyDecl ctx serial

  | _ -> CVoidTy, addError ctx "error type" noLoc // FIXME: source location

/// Converts a type to complete C type.
///
/// A type is complete if its definition is visible.
let private cgTyComplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (TupleTyCtor, []) -> CIntTy(IntFlavor(Signed, I32)), ctx
  | AppTy (IntTyCtor flavor, _) -> CIntTy flavor, ctx
  | AppTy (FloatTyCtor flavor, _) -> CFloatTy flavor, ctx
  | AppTy (BoolTyCtor, _) -> CBoolTy, ctx
  | AppTy (CharTyCtor, _) -> CCharTy, ctx
  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  // FIXME: Unresolved type variables are `obj` for now.
  | MetaTy _
  | AppTy (ObjTyCtor, _) -> CConstPtrTy CVoidTy, ctx

  | AppTy (FunTyCtor, [ sTy; tTy ]) -> genFunTyDef ctx sTy tTy

  | AppTy (ListTyCtor, [ itemTy ]) -> genListTyDef ctx itemTy

  | AppTy (TupleTyCtor, itemTys) ->
      // HOTFIX: Remove Undefined MetaTy. Without this, undefined meta tys are replaced with obj, duplicated tuple definitions are emitted. I don't know why undefined meta tys exist in this stage...
      let itemTys =
        itemTys
        |> List.map (fun ty ->
             let substMeta tySerial =
               match ctx.Tys |> mapTryFind tySerial with
               | Some (MetaTyDef (_, ty, _)) -> Some ty
               | Some (UniversalTyDef _)
               | None -> Some tyObj
               | _ -> None

             ty
             |> tySubst substMeta
             |> tyExpandSynonyms (fun tySerial -> ctx.Tys |> mapTryFind tySerial))

      genTupleTyDef ctx itemTys

  | AppTy (VoidTyCtor, _) -> CVoidTy, ctx

  | AppTy (NativePtrTyCtor isMut, [ itemTy ]) -> cgNativePtrTy ctx isMut itemTy

  | AppTy (NativeFunTyCtor, tys) -> cgNativeFunTy ctx tys

  | AppTy (NativeTypeTyCtor code, _) -> CEmbedTy code, ctx

  | AppTy (SynonymTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyComplete ctx ty

      | _ -> failwithf "NEVER: synonym type undefined?"

  | AppTy (UnionTyCtor serial, _) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (UnionTyDef (_, variants, _)) -> genUnionTyDef ctx serial variants

      | _ -> failwithf "NEVER: union type undefined?"

  | AppTy (RecordTyCtor serial, _) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (RecordTyDef (_, fields, _)) -> genRecordTyDef ctx serial fields

      | _ -> failwithf "NEVER: record type undefined?"

  | _ -> CVoidTy, addError ctx "error type" noLoc // FIXME: source location

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private cBinaryOf op =
  match op with
  | MMulBinary -> CMulBinary
  | MDivBinary -> CDivBinary
  | MModBinary -> CModBinary
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
  | MStrCmpBinary
  | MStrIndexBinary -> failwith "Never"

let private genLit lit =
  match lit with
  | IntLit value -> CIntExpr value
  | FloatLit text -> CDoubleExpr text
  | BoolLit false -> CRefExpr "false"
  | BoolLit true -> CRefExpr "true"
  | CharLit value -> CCharExpr value
  | StrLit value -> CStrObjExpr value

let private genTag ctx variantSerial =
  CRefExpr(getUniqueVariantName ctx variantSerial)

let private cgConst ctx mConst =
  match mConst with
  | MLitConst lit -> genLit lit
  | MTagConst variantSerial -> genTag ctx variantSerial

/// `0`, `NULL`, or `(T) {}`
let private genDefault ctx ty =
  match ty with
  | AppTy (TupleTyCtor, [])
  | AppTy (IntTyCtor _, _)
  | AppTy (FloatTyCtor _, _)
  | AppTy (CharTyCtor, _) -> CIntExpr 0, ctx

  | AppTy (BoolTyCtor, _) -> CRefExpr "false", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTyCtor, _)
  | AppTy (ListTyCtor, _)
  | AppTy (NativePtrTyCtor _, _)
  | AppTy (NativeFunTyCtor, _) -> CRefExpr "NULL", ctx

  | AppTy (StrTyCtor, _)
  | AppTy (FunTyCtor, _)
  | AppTy (TupleTyCtor, _)
  | AppTy (SynonymTyCtor _, _)
  | AppTy (UnionTyCtor _, _)
  | AppTy (RecordTyCtor _, _)
  | AppTy (NativeTypeTyCtor _, _) ->
      let ty, ctx = cgTyComplete ctx ty
      CCastExpr(CDefaultExpr, ty), ctx

  | ErrorTy _
  | AppTy (VoidTyCtor, _)
  | AppTy (UnresolvedTyCtor _, _) -> failwithf "Never %A" ty

let private genVariantNameExpr ctx serial ty =
  let ty, ctx = cgTyComplete ctx ty

  let tag =
    CRefExpr(getUniqueVariantName ctx serial)

  CInitExpr([ "tag", tag ], ty), ctx

/// Converts a binary expression to a runtime function call.
let private genBinaryExprAsCall ctx funName l r =
  let l, ctx = cgExpr ctx l
  let r, ctx = cgExpr ctx r
  let callExpr = CCallExpr(CRefExpr funName, [ l; r ])
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
  | MStrPtrUnary -> CNavExpr(arg, "str"), ctx
  | MStrLenUnary -> CNavExpr(arg, "len"), ctx

  | MUnboxUnary ->
      let valTy, ctx = cgTyComplete ctx ty

      let deref =
        CUnaryExpr(CDerefUnary, CCastExpr(arg, CConstPtrTy valTy))

      deref, ctx

  | MProjUnary index -> CProjExpr(arg, index), ctx

  | MTagUnary -> CNavExpr(arg, "tag"), ctx

  | MGetVariantUnary serial ->
      let _, ctx = cgTyComplete ctx ty
      CNavExpr(arg, getUniqueVariantName ctx serial), ctx

  | MRecordItemUnary index ->
      let fieldName =
        match argTy with
        | AppTy (RecordTyCtor tySerial, _) ->
            match ctx.Tys |> mapFind tySerial with
            | RecordTyDef (_, fields, _) ->
                match fields |> List.tryItem index with
                | Some (name, _, _) -> name
                | None -> failwith "NEVER"
            | _ -> failwith "NEVER"
        | _ -> failwith "NEVER"

      CNavExpr(arg, fieldName), ctx

  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MListHeadUnary -> CArrowExpr(arg, "head"), ctx
  | MListTailUnary -> CArrowExpr(arg, "tail"), ctx

  | MNativeCastUnary ->
      let ty, ctx = cgTyComplete ctx ty
      CCastExpr(arg, ty), ctx

  | MSizeOfValUnary ->
      let argTy, ctx = cgTyComplete ctx argTy
      CSizeOfExpr argTy, ctx

let private genExprBin ctx op l r =
  match op with
  | MIntCompareBinary -> genBinaryExprAsCall ctx "int_compare" l r
  | MInt64CompareBinary -> genBinaryExprAsCall ctx "int64_compare" l r
  | MUInt64CompareBinary -> genBinaryExprAsCall ctx "uint64_compare" l r

  | MStrAddBinary -> genBinaryExprAsCall ctx "str_add" l r
  | MStrCmpBinary -> genBinaryExprAsCall ctx "str_cmp" l r
  | MStrIndexBinary ->
      let l, ctx = cgExpr ctx l
      let r, ctx = cgExpr ctx r
      CIndexExpr(CNavExpr(l, "str"), r), ctx

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

let private cgExpr (ctx: CirCtx) (arg: MExpr): CExpr * CirCtx =
  match arg |> mxSugar with
  | MLitExpr (lit, _) -> genLit lit, ctx
  | MDefaultExpr (ty, _) -> genDefault ctx ty

  | MRefExpr (serial, _, _) -> CRefExpr(getUniqueVarName ctx serial), ctx
  | MProcExpr (serial, _, _) -> CRefExpr(getUniqueFunName ctx serial), ctx

  | MVariantExpr (_, serial, ty, _) -> genVariantNameExpr ctx serial ty
  | MTagExpr (variantSerial, _) -> genTag ctx variantSerial, ctx
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
      addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_assert", args)))

  | MPrintfnAction -> cgPrintfnActionStmt ctx itself args

  | MEnterRegionAction ->
      assert (List.isEmpty args)
      addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_enter_region", [])))

  | MLeaveRegionAction ->
      assert (List.isEmpty args)
      addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_leave_region", [])))

  | MCallNativeAction funName ->
      let ctx =
        addNativeFunDecl ctx funName args CVoidTy

      let args, ctx = cgExprList ctx args
      addStmt ctx (CExprStmt(CCallExpr(CRefExpr funName, args)))

  | MPtrWriteAction ->
      match cgExprList ctx args with
      | [ ptr; CIntExpr 0; value ], ctx -> addStmt ctx (CSetStmt(CUnaryExpr(CDerefUnary, ptr), value))
      | [ ptr; index; value ], ctx -> addStmt ctx (CSetStmt(CIndexExpr(ptr, index), value))
      | _ -> failwith "NEVER"

let private cgPrintfnActionStmt ctx itself args =
  match args with
  | (MLitExpr (StrLit format, _)) :: args ->
      let format = CStrRawExpr(format + "\n")

      let args, ctx =
        (args, ctx)
        |> stMap (fun (arg, ctx) ->
             match arg with
             | MLitExpr (StrLit value, _) -> CStrRawExpr value, ctx

             | _ when tyEq (mexprToTy arg) tyStr ->
                 // Insert implicit cast from str to str ptr.
                 let arg, ctx = cgExpr ctx arg
                 CNavExpr(arg, "str"), ctx

             | _ -> cgExpr ctx arg)

      addStmt ctx (CExprStmt(CCallExpr(CRefExpr "printf", format :: args)))

  | _ -> failwithf "NEVER: %A" itself

let private cgCallProcExpr ctx callee args ty =
  match callee, args with
  | _ ->
      let callee, ctx = cgExpr ctx callee
      let args, ctx = cgExprList ctx args
      CCallExpr(callee, args), ctx

let private doGenCallClosureExpr ctx callee args =
  let funPtr = CNavExpr(callee, "fun")
  let envArg = CNavExpr(callee, "env")
  CCallExpr(funPtr, envArg :: args), ctx

let private cgCallClosureExpr ctx callee args =
  let callee, ctx = cgExpr ctx callee
  let args, ctx = cgExprList ctx args
  doGenCallClosureExpr ctx callee args

let private addLetStmt ctx name expr cty storageModifier =
  match storageModifier with
  | StaticSM ->
      let ctx = addDecl ctx (CStaticVarDecl(name, cty))

      match expr with
      | Some expr -> addStmt ctx (CSetStmt(CRefExpr name, expr))
      | _ -> ctx

  | AutoSM -> addStmt ctx (CLetStmt(name, expr, cty))

let private addLetAllocStmt ctx name valTy varTy storageModifier =
  match storageModifier with
  | StaticSM -> failwith "NEVER: let-alloc is used only for temporary variables"
  | AutoSM -> addStmt ctx (CLetAllocStmt(name, valTy, varTy))

let private doGenLetValStmt ctx serial expr ty =
  let name = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let cty, ctx = cgTyComplete ctx ty
  addLetStmt ctx name expr cty storageModifier

let private cgCallPrimExpr ctx itself serial prim args resultTy _loc =
  let conversion ctx makeExpr =
    match args with
    | [ arg ] ->
        let name = getUniqueVarName ctx serial
        let storageModifier = findStorageModifier ctx serial
        let ty, ctx = cgTyComplete ctx resultTy
        let arg, ctx = cgExpr ctx arg
        addLetStmt ctx name (Some(makeExpr arg)) ty storageModifier

    | _ -> failwithf "NEVER: %A" itself

  let regular ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let storageModifier = findStorageModifier ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args)) ty storageModifier

  match prim with
  | MIntOfStrPrim flavor ->
      let name = cStringToIntegerFunName flavor
      conversion ctx (fun arg -> CCallExpr(CRefExpr name, [ arg ]))

  | MFloatOfStrPrim flavor ->
      let name = cStringToFloatFunName flavor
      conversion ctx (fun arg -> CCallExpr(CRefExpr name, [ arg ]))

  | MStrOfBoolPrim -> failwithf "unimplemented: %A" itself
  | MStrOfCharPrim -> conversion ctx (fun arg -> CCallExpr(CRefExpr "str_of_char", [ arg ]))

  | MStrOfIntPrim flavor ->
      let name = cStringOfIntegerFunName flavor
      conversion ctx (fun arg -> CCallExpr(CRefExpr name, [ arg ]))

  | MStrOfFloatPrim flavor ->
      let name = cStringOfFloatFunName flavor
      conversion ctx (fun arg -> CCallExpr(CRefExpr name, [ arg ]))

  | MStrGetSlicePrim -> regular ctx (fun args -> (CCallExpr(CRefExpr "str_get_slice", args)))

  | MCallNativePrim funName ->
      let ctx =
        let resultTy, ctx = cgTyComplete ctx resultTy
        addNativeFunDecl ctx funName args resultTy

      regular ctx (fun args -> (CCallExpr(CRefExpr funName, args)))

  | MPtrReadPrim ->
      regular ctx (fun args ->
        match args with
        | [ ptr; CIntExpr 0 ] -> CUnaryExpr(CDerefUnary, ptr)
        | [ ptr; index ] -> CIndexExpr(ptr, index)
        | _ -> failwith "NEVER")

let private cgClosureInit ctx serial funSerial envSerial ty =
  let name = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let ty, ctx = cgTyComplete ctx ty

  let fields =
    [ "fun", CRefExpr(getUniqueFunName ctx funSerial)
      "env", CRefExpr(getUniqueVarName ctx envSerial) ]

  let initExpr = CInitExpr(fields, ty)
  addLetStmt ctx name (Some initExpr) ty storageModifier

let private cgBoxInit ctx serial arg =
  let argTy, ctx = cgTyComplete ctx (mexprToTy arg)
  let arg, ctx = cgExpr ctx arg

  // void const* p = malloc(sizeof T);
  let temp = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial

  let ctx =
    addLetAllocStmt ctx temp argTy (CConstPtrTy CVoidTy) storageModifier

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CRefExpr temp, CPtrTy argTy))

  let ctx = addStmt ctx (CSetStmt(left, arg))

  ctx

let private cgConsInit ctx serial head tail listTy =
  let temp = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let listTy, ctx = cgTyComplete ctx listTy

  let listStructTy =
    match listTy with
    | CConstPtrTy it -> it
    | _ -> failwithf "NEVER"

  let ctx =
    addLetAllocStmt ctx temp listStructTy listTy storageModifier

  let head, ctx = cgExpr ctx head
  let tail, ctx = cgExpr ctx tail

  let stmt =
    let fields = [ "head", head; "tail", tail ]
    CSetStmt(CUnaryExpr(CDerefUnary, CCastExpr(CRefExpr temp, CPtrTy listStructTy)), CInitExpr(fields, listStructTy))

  let ctx = addStmt ctx stmt

  ctx

let private cgTupleInit ctx serial items tupleTy =
  let name = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let tupleTy, ctx = cgTyComplete ctx tupleTy

  let ctx =
    addLetStmt ctx name None tupleTy storageModifier

  let rec go ctx i items =
    match items with
    | [] -> ctx
    | item :: items ->
        let left = CNavExpr(CRefExpr name, tupleField i)
        let item, ctx = cgExpr ctx item
        let stmt = CSetStmt(left, item)
        let ctx = addStmt ctx stmt
        go ctx (i + 1) items

  go ctx 0 items

let private cgVariantInit ctx varSerial variantSerial payload unionTy =
  let temp = getUniqueVarName ctx varSerial

  let storageModifier = findStorageModifier ctx varSerial

  let unionTy, ctx = cgTyComplete ctx unionTy
  let variantName = getUniqueVariantName ctx variantSerial

  let payloadExpr, ctx = cgExpr ctx payload

  let fields =
    [ "tag", CRefExpr(getUniqueVariantName ctx variantSerial)
      variantName, payloadExpr ]

  let init = CInitExpr(fields, unionTy)

  let ctx =
    addLetStmt ctx temp (Some init) unionTy storageModifier

  ctx

let private cgRecordInit (ctx: CirCtx) serial args ty =
  let fields =
    match ty with
    | AppTy (RecordTyCtor tySerial, _) ->
        match ctx.Tys |> mapFind tySerial with
        | RecordTyDef (_, fields, _) -> fields
        | _ -> failwith "NEVER"
    | _ -> failwith "NEVER"

  assert (List.length fields = List.length args)

  let pairs =
    match listTryZip fields args with
    | it, [], [] -> it
    | _ -> failwith "NEVER"

  let name = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let ty, ctx = cgTyComplete ctx ty

  let ctx =
    addLetStmt ctx name None ty storageModifier

  pairs
  |> List.fold (fun ctx ((fieldName, _, _), arg) ->
       let l = CNavExpr(CRefExpr name, fieldName)
       let arg, ctx = cgExpr ctx arg
       addStmt ctx (CSetStmt(l, arg))) ctx

let private cgLetValStmt ctx serial init ty loc =
  match init with
  | MUninitInit -> doGenLetValStmt ctx serial None ty

  | MExprInit expr ->
      let expr, ctx = cgExpr ctx expr
      doGenLetValStmt ctx serial (Some expr) ty

  | MPrimInit (prim, args) -> cgCallPrimExpr ctx init serial prim args ty loc

  | MCallProcInit (callee, args, _) ->
      let expr, ctx = cgCallProcExpr ctx callee args ty
      doGenLetValStmt ctx serial (Some expr) ty

  | MCallClosureInit (callee, args) ->
      let expr, ctx = cgCallClosureExpr ctx callee args
      doGenLetValStmt ctx serial (Some expr) ty

  | MClosureInit (funSerial, envSerial) -> cgClosureInit ctx serial funSerial envSerial ty
  | MBoxInit arg -> cgBoxInit ctx serial arg
  | MConsInit (head, tail) -> cgConsInit ctx serial head tail ty
  | MTupleInit items -> cgTupleInit ctx serial items ty
  | MVariantInit (variantSerial, payload) -> cgVariantInit ctx serial variantSerial payload ty
  | MRecordInit fields -> cgRecordInit ctx serial fields ty

let private cgSetStmt ctx serial right =
  let right, ctx = cgExpr ctx right
  let name = getUniqueVarName ctx serial
  let left = CRefExpr(name)
  addStmt ctx (CSetStmt(left, right))

let private cgReturnStmt ctx expr =
  let expr, ctx = cgExpr ctx expr
  addStmt ctx (CReturnStmt(Some expr))

// FIXME: Without the result type annotation, invalid code is generated for some reason.
let private cgTerminatorAsBlock ctx terminator: CStmt list * CirCtx =
  cgBlock ctx [ MTerminatorStmt(terminator, noLoc) ]

let private cgTerminatorStmt ctx stmt =
  match stmt with
  | MReturnTerminator expr -> cgReturnStmt ctx expr
  | MGotoTerminator label -> addStmt ctx (CGotoStmt label)

  | MGotoIfTerminator (pred, label) ->
      let pred, ctx = cgExpr ctx pred
      addStmt ctx (CGotoIfStmt(pred, label))

  | MIfTerminator (cond, thenCl, elseCl) ->
      let cond, ctx = cgExpr ctx cond
      let thenCl, ctx = cgTerminatorAsBlock ctx thenCl
      let elseCl, ctx = cgTerminatorAsBlock ctx elseCl
      addStmt ctx (CIfStmt(cond, thenCl, elseCl))

  | MSwitchTerminator (cond, clauses) ->
      let cond, ctx = cgExpr ctx cond

      let clauses, ctx =
        (clauses, ctx)
        |> stMap (fun (clause: MSwitchClause, ctx) ->
             let cases =
               clause.Cases
               |> List.map (fun cond -> cgConst ctx cond)

             let stmts, ctx =
               cgTerminatorAsBlock ctx clause.Terminator

             (cases, clause.IsDefault, stmts), ctx)

      addStmt ctx (CSwitchStmt(cond, clauses))

  | MExitTerminator arg ->
      let doArm () =
        let arg, ctx = cgExpr ctx arg
        addStmt ctx (CExprStmt(CCallExpr(CRefExpr "exit", [ arg ])))

      doArm ()

let private cgStmt ctx stmt =
  match stmt with
  | MActionStmt (action, args, _) -> cgActionStmt ctx stmt action args
  | MLetValStmt (serial, init, ty, loc) -> cgLetValStmt ctx serial init ty loc
  | MSetStmt (serial, right, _) -> cgSetStmt ctx serial right
  | MLabelStmt (label, _) -> addStmt ctx (CLabelStmt label)
  | MTerminatorStmt (terminator, _loc) -> cgTerminatorStmt ctx terminator

  | MIfStmt (cond, thenCl, elseCl, _) ->
      let cond, ctx = cgExpr ctx cond
      let thenCl, ctx = cgBlock ctx thenCl
      let elseCl, ctx = cgBlock ctx elseCl
      addStmt ctx (CIfStmt(cond, thenCl, elseCl))

  | MNativeStmt (code, _) -> addStmt ctx (CNativeStmt code)

let private cgBlock (ctx: CirCtx) (stmts: MStmt list) =
  let bodyCtx: CirCtx = cgStmts (enterBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = rollback ctx bodyCtx
  List.rev stmts, ctx

let private cgBlocks (ctx: CirCtx) (blocks: MBlock list) =
  match blocks with
  | [ block ] -> cgBlock ctx block.Stmts

  | _ -> failwith "unimplemented"

let private cgStmts (ctx: CirCtx) (stmts: MStmt list): CirCtx =
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
      let funName, args =
        if isMainFun ctx callee then "main", [] else getUniqueFunName ctx callee, args

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
      let funDecl = CFunDecl(funName, args, resultTy, body)
      let ctx = addDecl ctx funDecl
      cgDecls ctx decls

  | MNativeDecl (code, _) :: decls ->
      let ctx = addDecl ctx (CNativeDecl code)
      cgDecls ctx decls

// -----------------------------------------------
// Interface
// -----------------------------------------------

let private genLogs (ctx: CirCtx) =
  let tyDisplayFn ty =
    let getTyName tySerial =
      ctx.Tys
      |> mapTryFind tySerial
      |> Option.map tyDefToName

    tyDisplay getTyName ty

  let rec go (ctx: CirCtx) logs =
    match logs with
    | [] -> ctx
    | (log, loc) :: logs ->
        let _, y, _ = loc
        let msg = locToString loc + " " + logToString tyDisplayFn log
        let ctx = addDecl ctx (CErrorDecl(msg, 1 + y))
        go ctx logs

  let logs = ctx.Logs |> List.rev
  let ctx = go ctx logs
  let success = logs |> List.isEmpty
  success, ctx

let genCir (decls, mirCtx: MirCtx): bool * CDecl list =
  let ctx = ofMirCtx mirCtx
  let ctx = cgDecls ctx decls
  let ok, ctx = genLogs ctx
  let decls = ctx.Decls |> List.rev
  ok, decls
