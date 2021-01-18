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

let private valueSymbolCompare l r =
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

/// Calculates discriminant type's name of union type.
let private toDiscriminantEnumName (name: string) = name + "Discriminant"

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
    let m = mapEmpty valueSymbolCompare

    let m =
      mirCtx.Vars
      |> mapFold
           (fun acc varSerial varDef ->
             acc
             |> mapAdd (VarSymbol varSerial) (varDefToName varDef))
           m

    let m =
      mirCtx.Funs
      |> mapFold (fun acc funSerial (funDef: FunDef) -> acc |> mapAdd (FunSymbol funSerial) funDef.Name) m

    let m =
      mirCtx.Variants
      |> mapFold
           (fun acc variantSerial (variantDef: VariantDef) ->
             acc
             |> mapAdd (VariantSymbol variantSerial) variantDef.Name)
           m

    m |> renameIdents id fst valueSymbolCompare

  let tyNames =
    let toKey (serial, tyDef) =
      match tyDef with
      | MetaTyDef _
      | UniversalTyDef _ -> MetaTy(serial, noLoc)

      | SynonymTyDef _ -> tySynonym serial []
      | UnionTyDef _ -> tyUnion serial
      | RecordTyDef _ -> tyRecord serial

    mirCtx.Tys |> renameIdents tyDefToName toKey tyCompare

  { Vars = mirCtx.Vars
    Funs = mirCtx.Funs
    Variants = mirCtx.Variants
    MainFunOpt = mirCtx.MainFunOpt
    ValueUniqueNames = valueUniqueNames
    TyEnv = mapEmpty tyCompare
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
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
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
      let fieldTys, (ctx: CirCtx) =
        (fields, ctx)
        |> stMap
             (fun ((_, ty, _), ctx) ->
               let ty, ctx = cgTyComplete ctx ty
               ty, ctx)

      let fields = fieldTys |> List.mapi (fun i ty -> tupleField i, ty)

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
      | AppTy (IntTk flavor, _) -> cIntegerTyPascalName flavor, ctx
      | AppTy (FloatTk flavor, _) -> cFloatTyPascalName flavor, ctx
      | AppTy (BoolTk, _) -> "Bool", ctx
      | AppTy (CharTk, _) -> "Char", ctx
      | AppTy (StrTk, _) -> "String", ctx

      | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
      | AppTy (ObjTk, _) -> "Object", ctx

      | AppTy (FunTk, _) ->
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

      | AppTy (ListTk, [ itemTy ]) ->
          let itemTy, ctx = ctx |> go itemTy
          let listTy = itemTy + "List"
          listTy, ctx

      | AppTy (VoidTk, _) -> "Void", ctx

      | AppTy (NativePtrTk isMut, [ itemTy ]) ->
          let itemTy, ctx = ctx |> go itemTy

          let ptrTy =
            match isMut with
            | IsConst -> itemTy + "ConstPtr"
            | IsMut -> itemTy + "MutPtr"

          ptrTy, ctx

      | AppTy (NativeFunTk, tyArgs) ->
          let tyArgs, ctx =
            (tyArgs, ctx)
            |> stMap (fun (ty, ctx) -> ctx |> go ty)

          let funTy =
            (tyArgs |> strConcat)
            + "NativeFun"
            + string (List.length tyArgs - 1)

          funTy, ctx

      | AppTy (NativeTypeTk code, _) -> code, ctx

      | AppTy (TupleTk, []) -> "Unit", ctx

      | AppTy (TupleTk, itemTys) ->
          let len = itemTys |> List.length

          let itemTys, ctx =
            (itemTys, ctx)
            |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)

          let tupleTy =
            (itemTys |> strConcat) + "Tuple" + string len

          tupleTy, ctx

      | AppTy (ListTk, _)
      | AppTy (FunTk, _)
      | AppTy (NativePtrTk _, _)
      | AppTy (SynonymTk _, _)
      | AppTy (UnionTk _, _)
      | AppTy (RecordTk _, _)
      | AppTy (UnresolvedTk _, _)
      | AppTy (UnresolvedVarTk _, _)
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
  | AppTy (TupleTk, []) -> CIntTy(IntFlavor(Signed, I32)), ctx
  | AppTy (IntTk flavor, _) -> CIntTy flavor, ctx
  | AppTy (FloatTk flavor, _) -> CFloatTy flavor, ctx
  | AppTy (BoolTk, _) -> CBoolTy, ctx
  | AppTy (CharTk, _) -> CCharTy, ctx
  | AppTy (StrTk, _) -> CStructTy "String", ctx

  // FIXME: Unresolved type variables are `obj` for now.
  | MetaTy _
  | AppTy (ObjTk, _) -> CConstPtrTy CVoidTy, ctx

  | AppTy (FunTk, [ sTy; tTy ]) -> genIncompleteFunTyDecl ctx sTy tTy

  | AppTy (ListTk, [ itemTy ]) -> genIncompleteListTyDecl ctx itemTy

  | AppTy (TupleTk, itemTys) -> genIncompleteTupleTyDecl ctx itemTys

  | AppTy (VoidTk, _) -> CVoidTy, ctx

  | AppTy (NativePtrTk isMut, [ itemTy ]) -> cgNativePtrTy ctx isMut itemTy

  | AppTy (NativeFunTk, tys) -> cgNativeFunTy ctx tys

  | AppTy (NativeTypeTk code, _) -> CEmbedTy code, ctx

  | AppTy (SynonymTk serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyIncomplete ctx ty

      | _ -> failwithf "NEVER: synonym type undefined?"

  | AppTy (UnionTk serial, _) -> genIncompleteUnionTyDecl ctx serial

  | AppTy (RecordTk serial, _) -> genIncompleteRecordTyDecl ctx serial

  | _ -> CVoidTy, addError ctx "error type" noLoc // FIXME: source location

/// Converts a type to complete C type.
///
/// A type is complete if its definition is visible.
let private cgTyComplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (TupleTk, []) -> CIntTy(IntFlavor(Signed, I32)), ctx
  | AppTy (IntTk flavor, _) -> CIntTy flavor, ctx
  | AppTy (FloatTk flavor, _) -> CFloatTy flavor, ctx
  | AppTy (BoolTk, _) -> CBoolTy, ctx
  | AppTy (CharTk, _) -> CCharTy, ctx
  | AppTy (StrTk, _) -> CStructTy "String", ctx

  // FIXME: Unresolved type variables are `obj` for now.
  | MetaTy _
  | AppTy (ObjTk, _) -> CConstPtrTy CVoidTy, ctx

  | AppTy (FunTk, [ sTy; tTy ]) -> genFunTyDef ctx sTy tTy

  | AppTy (ListTk, [ itemTy ]) -> genListTyDef ctx itemTy

  | AppTy (TupleTk, itemTys) ->
      // HOTFIX: Remove Undefined MetaTy. Without this, undefined meta tys are replaced with obj, duplicated tuple definitions are emitted. I don't know why undefined meta tys exist in this stage...
      let itemTys =
        itemTys
        |> List.map
             (fun ty ->
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

  | AppTy (VoidTk, _) -> CVoidTy, ctx

  | AppTy (NativePtrTk isMut, [ itemTy ]) -> cgNativePtrTy ctx isMut itemTy

  | AppTy (NativeFunTk, tys) -> cgNativeFunTy ctx tys

  | AppTy (NativeTypeTk code, _) -> CEmbedTy code, ctx

  | AppTy (SynonymTk serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyComplete ctx ty

      | _ -> failwithf "NEVER: synonym type undefined?"

  | AppTy (UnionTk serial, _) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (UnionTyDef (_, variants, _)) -> genUnionTyDef ctx serial variants

      | _ -> failwithf "NEVER: union type undefined?"

  | AppTy (RecordTk serial, _) ->
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
  | MStrIndexBinary -> failwith "Never"

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

/// `0`, `NULL`, or `(T) {}`
let private genDefault ctx ty =
  match ty with
  | AppTy (TupleTk, [])
  | AppTy (IntTk _, _)
  | AppTy (FloatTk _, _)
  | AppTy (CharTk, _) -> CIntExpr "0", ctx

  | AppTy (BoolTk, _) -> CVarExpr "false", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTk, _)
  | AppTy (ListTk, _)
  | AppTy (NativePtrTk _, _)
  | AppTy (NativeFunTk, _) -> CVarExpr "NULL", ctx

  | AppTy (StrTk, _)
  | AppTy (FunTk, _)
  | AppTy (TupleTk, _)
  | AppTy (SynonymTk _, _)
  | AppTy (UnionTk _, _)
  | AppTy (RecordTk _, _)
  | AppTy (NativeTypeTk _, _) ->
      let ty, ctx = cgTyComplete ctx ty
      CCastExpr(CDefaultExpr, ty), ctx

  | ErrorTy _
  | AppTy (VoidTk, _)
  | AppTy (UnresolvedTk _, _)
  | AppTy (UnresolvedVarTk _, _) -> failwithf "Never %A" ty

let private genVariantNameExpr ctx serial ty =
  let ty, ctx = cgTyComplete ctx ty

  let discriminant =
    CVarExpr(getUniqueVariantName ctx serial)

  CInitExpr([ "discriminant", discriminant ], ty), ctx

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

  | MProjUnary index -> CDotExpr(arg, tupleField index), ctx

  | MGetDiscriminantUnary -> CDotExpr(arg, "discriminant"), ctx

  | MGetVariantUnary serial ->
      let _, ctx = cgTyComplete ctx ty
      CDotExpr(arg, getUniqueVariantName ctx serial), ctx

  | MRecordItemUnary index -> CDotExpr(arg, tupleField index), ctx

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

let private cgExpr (ctx: CirCtx) (arg: MExpr): CExpr * CirCtx =
  match arg |> mxSugar with
  | MLitExpr (lit, _) -> genLit lit, ctx
  | MDefaultExpr (ty, _) -> genDefault ctx ty

  | MVarExpr (serial, _, _) -> CVarExpr(getUniqueVarName ctx serial), ctx
  | MProcExpr (serial, _, _) -> CVarExpr(getUniqueFunName ctx serial), ctx

  | MVariantExpr (_, serial, ty, _) -> genVariantNameExpr ctx serial ty
  | MDiscriminantConstExpr (variantSerial, _) -> genDiscriminant ctx variantSerial, ctx
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
      | _ -> failwith "NEVER"

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

  | _ -> failwithf "NEVER: %A" itself

let private addLetStmt ctx name expr cty storageModifier =
  match storageModifier with
  | StaticSM ->
      let ctx = addDecl ctx (CStaticVarDecl(name, cty))

      match expr with
      | Some expr -> addStmt ctx (CSetStmt(CVarExpr name, expr))
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

let private cgPrimStmt (ctx: CirCtx) itself prim args serial =
  let (VarDef (_, _, resultTy, _)) = ctx.Vars |> mapFind serial

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

  let regularWithTy ctx makeExpr =
    let name = getUniqueVarName ctx serial
    let storageModifier = findStorageModifier ctx serial
    let ty, ctx = cgTyComplete ctx resultTy

    let args, ctx =
      (args, ctx)
      |> stMap (fun (arg, ctx) -> cgExpr ctx arg)

    addLetStmt ctx name (Some(makeExpr args ty)) ty storageModifier

  match prim with
  | MIntOfStrPrim flavor ->
      let name = cStringToIntegerFunName flavor
      conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MFloatOfStrPrim flavor ->
      let name = cStringToFloatFunName flavor
      conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MCharOfStrPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_to_char", [ arg ]))

  | MStrOfBoolPrim -> failwithf "unimplemented: %A" itself
  | MStrOfCharPrim -> conversion ctx (fun arg -> CCallExpr(CVarExpr "str_of_char", [ arg ]))

  | MStrOfIntPrim flavor ->
      let name = cStringOfIntegerFunName flavor
      conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStrOfFloatPrim flavor ->
      let name = cStringOfFloatFunName flavor
      conversion ctx (fun arg -> CCallExpr(CVarExpr name, [ arg ]))

  | MStrGetSlicePrim -> regular ctx (fun args -> (CCallExpr(CVarExpr "str_get_slice", args)))

  | MClosurePrim funSerial ->
      regularWithTy ctx (fun args resultTy ->
        let funExpr = CVarExpr(getUniqueFunName ctx funSerial)
        match args with
        | [ env ] -> CInitExpr([ "fun", funExpr; "env", env ], resultTy)
        | _ -> failwithf "NEVER: %A" itself)

  | MBoxPrim ->
      match args with
      | [ arg ] -> cgBoxStmt ctx serial arg
      | _ -> failwithf "NEVER: %A" itself

  | MConsPrim ->
      match args with
      | [ l; r ] -> cgConsStmt ctx serial l r resultTy
      | _ -> failwithf "NEVER: %A" itself

  | MTuplePrim ->
      regularWithTy ctx (fun args tupleTy ->
        let fields = args |> List.mapi (fun i arg -> tupleField i, arg)
        CInitExpr(fields, tupleTy)
      )

  | MVariantPrim variantSerial ->
      regularWithTy ctx (fun args unionTy ->
          match args with
          | [ payload ] ->
              let variantName = getUniqueVariantName ctx variantSerial
              let fields =
                [ "discriminant", CVarExpr variantName
                  variantName, payload ]

              CInitExpr(fields, unionTy)

          | _ -> failwithf "NEVER: %A" itself)

  | MRecordPrim ->
      regularWithTy ctx (fun args recordTy ->
        let fields = args |> List.mapi (fun i arg -> tupleField i, arg)
        CInitExpr(fields, recordTy)
      )

  | MCallProcPrim ->
      regular ctx (fun args ->
          match args with
          | callee :: args -> CCallExpr(callee, args)
          | [] -> failwithf "NEVER: %A" itself)

  | MCallClosurePrim ->
      regular ctx (fun args ->
          match args with
          | callee :: args ->
            let funPtr = CDotExpr(callee, "fun")
            let envArg = CDotExpr(callee, "env")
            CCallExpr(funPtr, envArg :: args)

          | [] -> failwithf "NEVER: %A" itself)

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
          | _ -> failwith "NEVER")

let private cgCallPrimExpr ctx itself serial prim args =
  let fail msg = failwithf "%s: %A" msg itself
  cgPrimStmt ctx fail prim args serial

let private cgBoxStmt ctx serial arg =
  let argTy, ctx = cgTyComplete ctx (mexprToTy arg)
  let arg, ctx = cgExpr ctx arg

  // void const* p = malloc(sizeof T);
  let temp = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial

  let ctx =
    addLetAllocStmt ctx temp argTy (CConstPtrTy CVoidTy) storageModifier

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CVarExpr temp, CPtrTy argTy))

  addStmt ctx (CSetStmt(left, arg))

let private cgConsStmt ctx serial head tail listTy =
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
      let doArm () =
        let arg, ctx = cgExpr ctx arg
        addStmt ctx (CExprStmt(CCallExpr(CVarExpr "exit", [ arg ])))

      doArm ()

let private cgStmt ctx stmt =
  match stmt with
  | MActionStmt (action, args, _) -> cgActionStmt ctx stmt action args
  | MPrimStmt (prim, args, temp, _) -> cgPrimStmt ctx stmt prim args temp
  | MLetValStmt (serial, init, ty, _) -> cgLetValStmt ctx serial init ty
  | MSetStmt (serial, right, _) -> cgSetStmt ctx serial right
  | MLabelStmt (label, _) -> addStmt ctx (CLabelStmt label)
  | MTerminatorStmt (terminator, _loc) -> cgTerminatorStmt ctx terminator
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
        if isMainFun ctx callee then "milone_main", [] else getUniqueFunName ctx callee, args

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

        let msg =
          locToString loc
          + " "
          + logToString tyDisplayFn log

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
