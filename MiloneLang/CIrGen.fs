/// # CirGen
///
/// Converts MIR to CIR.
///
/// CIR is a kind of abstract syntax tree of the C language.
///
/// This stage does:
///
/// - Mapping operations to corresponding C features.
/// - Translates types of Milone-lang to C-style type definitions.
module rec MiloneLang.CIrGen

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.TySystem
open MiloneLang.Mir

let private ctVoidPtr = CPtrTy CVoidTy

let private renameIdents toIdent toKey mapFuns (defMap: AssocMap<int, _>) =
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

        let acc = acc |> mapAdd ident (serial :: serials)
        go acc xs

  let serialsMap =
    go (mapEmpty strCmp) (defMap |> mapToList)

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
let private tagTyIdent (tyIdent: string) = tyIdent + "Tag"

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type private CirCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    VarUniqueNames: AssocMap<VarSerial, Ident>
    TyEnv: AssocMap<Ty, CTyInstance * CTy>
    Tys: AssocMap<TySerial, TyDef>
    TyUniqueNames: AssocMap<Ty, Ident>
    Stmts: CStmt list
    Decls: CDecl list
    Logs: (Log * Loc) list }

let private ofMirCtx (mirCtx: MirCtx): CirCtx =
  let varNames =
    mirCtx.Vars
    |> renameIdents varDefToIdent id intCmp

  let tyNames =
    mirCtx.Tys
    |> renameIdents tyDefToIdent (fun serial -> tyRef serial []) tyCmp

  { Vars = mirCtx.Vars
    VarUniqueNames = varNames
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
      let ident, (ctx: CirCtx) = getUniqueTyName ctx funTy
      let funStructTy = CStructTy ident

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
      let ident, ctx = getUniqueTyName ctx funTy
      let selfTy, ctx = genIncompleteFunTyDecl ctx sTy tTy

      let envTy = CPtrTy CVoidTy
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
            Decls = CStructDecl(ident, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd funTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteListTyDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let ident, ctx = getUniqueTyName ctx listTy
      let selfTy = CPtrTy(CStructTy ident)

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private genListTyDef (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let ident, ctx = getUniqueTyName ctx listTy
      let selfTy, ctx = genIncompleteListTyDecl ctx itemTy

      let itemTy, (ctx: CirCtx) = cgTyComplete ctx itemTy
      let fields = [ "head", itemTy; "tail", selfTy ]

      let ctx =
        { ctx with
            Decls = CStructDecl(ident, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteTupleTyDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let tupleTyIdent, ctx = getUniqueTyName ctx tupleTy
      let selfTy = CStructTy tupleTyIdent

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private genTupleTyDef (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let tupleTyIdent, ctx = getUniqueTyName ctx tupleTy
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

      let tupleDecl = CStructDecl(tupleTyIdent, fields, [])

      let ctx =
        { ctx with
            Decls = tupleDecl :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteUnionTyDecl (ctx: CirCtx) tySerial =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let unionTyIdent, ctx = getUniqueTyName ctx unionTyRef
      let selfTy = CStructTy unionTyIdent

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd unionTyRef (CTyDeclared, selfTy) }

      selfTy, ctx

let private genUnionTyDef (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let unionTyIdent, ctx = getUniqueTyName ctx unionTyRef
      let selfTy, ctx = genIncompleteUnionTyDecl ctx tySerial

      let tagTyIdent = tagTyIdent unionTyIdent
      let tagTy = CEnumTy tagTyIdent

      let variants =
        variants
        |> List.map (fun variantSerial ->
             match ctx.Vars |> mapTryFind variantSerial with
             | Some (VariantDef (ident, _, hasPayload, payloadTy, _, _)) -> ident, variantSerial, hasPayload, payloadTy
             | _ -> failwith "Never")

      let tags =
        variants
        |> List.map (fun (_, serial, _, _) -> getUniqueVarName ctx serial)

      let variants, ctx =
        (variants, ctx)
        |> stFlatMap (fun ((_, serial, hasPayload, _payloadTy), acc, ctx) ->
             if hasPayload then
               //  let payloadTy, ctx = cgTyIncomplete ctx payloadTy
               //  (getUniqueVarName ctx serial, payloadTy)
               //  :: acc,
               //  ctx
               (getUniqueVarName ctx serial, ctVoidPtr) :: acc, ctx
             else
               acc, ctx)

      let tagEnumDecl = CEnumDecl(tagTyIdent, tags)

      let structDecl =
        CStructDecl(unionTyIdent, [ "tag", tagTy ], variants)

      let ctx =
        { ctx with
            Decls = structDecl :: tagEnumDecl :: ctx.Decls
            TyEnv =
              ctx.TyEnv
              |> mapAdd unionTyRef (CTyDefined, selfTy) }

      selfTy, ctx

let private genIncompleteRecordTyDecl (ctx: CirCtx) tySerial =
  let recordTyRef = tyRef tySerial []

  match ctx.TyEnv |> mapTryFind recordTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let recordTyIdent, ctx = getUniqueTyName ctx recordTyRef
      let selfTy = CStructTy recordTyIdent

      // TODO: Generate type declaration.

      selfTy, ctx

let private genRecordTyDef ctx tySerial _fields =
  let recordTyRef = tyRef tySerial []
  let recordTyIdent, ctx = getUniqueTyName ctx recordTyRef
  let selfTy = CStructTy recordTyIdent

  // TODO: Generate type definition.

  selfTy, ctx

// -----------------------------------------------
// Naming
// -----------------------------------------------

let private getUniqueVarName (ctx: CirCtx) serial =
  match ctx.VarUniqueNames |> mapTryFind serial with
  | Some ident -> ident
  | None -> failwithf "Never: Unknown value-level identifier serial %d" serial

let private getUniqueTyName (ctx: CirCtx) ty: _ * CirCtx =
  let rec go ty (ctx: CirCtx) =
    let tyToUniqueName ty =
      match ty with
      | AppTy (BoolTyCtor, _) -> "Bool", ctx

      | AppTy (IntTyCtor, _) -> "Int", ctx

      | AppTy (UIntTyCtor, _) -> "UInt", ctx

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

      | AppTy (TupleTyCtor, []) -> "Unit", ctx

      | AppTy (TupleTyCtor, itemTys) ->
          let len = itemTys |> List.length

          let itemTys, ctx =
            (itemTys, ctx)
            |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)

          let tupleTy =
            (itemTys |> strConcat) + "Tuple" + string len

          tupleTy, ctx

      | AppTy (RefTyCtor _, _)
      | AppTy (ListTyCtor, _)
      | AppTy (FunTyCtor, _)
      | ErrorTy _ ->
          // FIXME: collect error
          failwithf "/* unknown ty %A */" ty

    // Memoization.
    match ctx.TyUniqueNames |> mapTryFind ty with
    | Some ident -> ident, ctx

    | None ->
        let ident, ctx = tyToUniqueName ty

        let ctx =
          { ctx with
              TyUniqueNames = ctx.TyUniqueNames |> mapAdd ty ident }

        ident, ctx

  go ty ctx

/// Converts a type to incomplete type.
/// whose type definition is not necessary to be visible.
let private cgTyIncomplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (BoolTyCtor, _)
  | AppTy (IntTyCtor, _)
  | AppTy (TupleTyCtor, []) -> CIntTy, ctx

  | AppTy (UIntTyCtor, _) -> CUInt32Ty, ctx

  | AppTy (CharTyCtor, _) -> CCharTy, ctx

  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTyCtor, _) -> CPtrTy CVoidTy, ctx

  | AppTy (FunTyCtor, [ sTy; tTy ]) -> genIncompleteFunTyDecl ctx sTy tTy

  | AppTy (ListTyCtor, [ itemTy ]) -> genIncompleteListTyDecl ctx itemTy

  | AppTy (TupleTyCtor, itemTys) -> genIncompleteTupleTyDecl ctx itemTys

  | AppTy (RefTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyIncomplete ctx ty

      | Some (UnionTyDef _) -> genIncompleteUnionTyDecl ctx serial

      | Some (RecordTyDef _) -> genIncompleteRecordTyDecl ctx serial

      | _ -> CVoidTy, addError ctx "Unknown type reference" noLoc // FIXME: source location

  | _ -> CVoidTy, addError ctx "error type" noLoc // FIXME: source location

/// Converts a type to complete C type.
///
/// A type is complete if its definition is visible.
let private cgTyComplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (BoolTyCtor, _)
  | AppTy (IntTyCtor, _)
  | AppTy (TupleTyCtor, []) -> CIntTy, ctx

  | AppTy (UIntTyCtor, []) -> CUInt32Ty, ctx

  | AppTy (CharTyCtor, _) -> CCharTy, ctx

  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTyCtor, _) -> CPtrTy CVoidTy, ctx

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

  | AppTy (RefTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cgTyComplete ctx ty

      | Some (UnionTyDef (_, variants, _)) -> genUnionTyDef ctx serial variants

      | Some (RecordTyDef (_, fields, _)) -> genRecordTyDef ctx serial fields

      | _ -> CVoidTy, addError ctx "Unknown type reference" noLoc // FIXME: source location

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
  | MEqualBinary -> CEqualBinary
  | MNotEqualBinary -> CNotEqualBinary
  | MLessBinary -> CLessBinary
  | MGreaterEqualBinary -> CGreaterEqualBinary
  | MStrAddBinary
  | MStrCmpBinary
  | MStrIndexBinary -> failwith "Never"

let private genLit lit =
  match lit with
  | IntLit value -> CIntExpr value
  | CharLit value -> CCharExpr value
  | StrLit value -> CStrObjExpr value
  | BoolLit false -> CIntExpr 0
  | BoolLit true -> CIntExpr 1

let private genTag ctx variantSerial =
  CRefExpr(getUniqueVarName ctx variantSerial)

let private cgConst ctx mConst =
  match mConst with
  | MLitConst lit -> genLit lit
  | MTagConst variantSerial -> genTag ctx variantSerial

/// `0`, `NULL`, or `(T) {}`
let private genDefault ctx ty =
  match ty with
  | AppTy (TupleTyCtor, [])
  | AppTy (BoolTyCtor, _)
  | AppTy (IntTyCtor, _)
  | AppTy (UIntTyCtor, _) -> CIntExpr 0, ctx
  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (CharTyCtor, _)
  | AppTy (ObjTyCtor, _)
  | AppTy (ListTyCtor, _) -> CRefExpr "NULL", ctx
  | AppTy (StrTyCtor, _)
  | AppTy (FunTyCtor, _)
  | AppTy (TupleTyCtor, _)
  | AppTy (RefTyCtor _, _) ->
      let ty, ctx = cgTyComplete ctx ty
      CCastExpr(CDefaultExpr, ty), ctx
  | ErrorTy _ -> failwithf "Never %A" ty

let private genVariantNameExpr ctx serial ty =
  let ty, ctx = cgTyComplete ctx ty
  let tag = CRefExpr(getUniqueVarName ctx serial)
  CInitExpr([ "tag", tag ], ty), ctx

let private genBinaryExprAsCall ctx ident l r =
  let l, ctx = cgExpr ctx l
  let r, ctx = cgExpr ctx r
  let callExpr = CCallExpr(CRefExpr ident, [ l; r ])
  callExpr, ctx

let private genUnaryExpr ctx op arg ty _ =
  let arg, ctx = cgExpr ctx arg
  match op with
  | MNotUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MStrPtrUnary -> CNavExpr(arg, "str"), ctx
  | MStrLenUnary -> CNavExpr(arg, "len"), ctx

  | MUnboxUnary ->
      let valTy, ctx = cgTyComplete ctx ty

      let deref =
        CUnaryExpr(CDerefUnary, CCastExpr(arg, CPtrTy valTy))

      deref, ctx

  | MProjUnary index -> CProjExpr(arg, index), ctx

  | MTagUnary -> CNavExpr(arg, "tag"), ctx

  | MGetVariantUnary serial ->
      let _, ctx = cgTyComplete ctx ty
      CNavExpr(arg, getUniqueVarName ctx serial), ctx

  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MListHeadUnary -> CArrowExpr(arg, "head"), ctx
  | MListTailUnary -> CArrowExpr(arg, "tail"), ctx

let private genExprBin ctx op l r =
  match op with
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
  | MProcExpr (serial, _, _) -> CRefExpr(getUniqueVarName ctx serial), ctx

  | MVariantExpr (_, serial, ty, _) -> genVariantNameExpr ctx serial ty
  | MTagExpr (variantSerial, _) -> genTag ctx variantSerial, ctx
  | MUnaryExpr (op, arg, ty, loc) -> genUnaryExpr ctx op arg ty loc
  | MBinaryExpr (op, l, r, _, _) -> genExprBin ctx op l r

// -----------------------------------------------
// Statements
// -----------------------------------------------

let private cgPrintfnCallExpr ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] -> List.rev acc, ctx
    | MLitExpr (StrLit value, _) :: args -> go (CStrRawExpr value :: acc) ctx args
    | arg :: args when tyEq (mexprToTy arg) tyStr ->
        let arg, ctx = cgExpr ctx arg
        let acc = CNavExpr(arg, "str") :: acc
        go acc ctx args
    | arg :: args ->
        let arg, ctx = cgExpr ctx arg
        go (arg :: acc) ctx args

  let args, ctx = go [] ctx args
  let format = CStrRawExpr(format + "\n")

  let expr =
    CExprStmt(CCallExpr(CRefExpr "printf", format :: args))

  let ctx = addStmt ctx expr
  genDefault ctx tyUnit

let private cgCallIntExpr arg argTy ctx =
  let arg, ctx = cgExpr ctx arg
  match argTy with
  | AppTy (IntTyCtor, _) -> arg, ctx
  | AppTy (UIntTyCtor, _)
  | AppTy (CharTyCtor, _) -> CCastExpr(arg, CIntTy), ctx
  | AppTy (StrTyCtor, _) -> CCallExpr(CRefExpr "str_to_int", [ arg ]), ctx
  | _ -> failwith "Never: Type Error `int`"

let private cgCallUIntExpr arg argTy ctx =
  let arg, ctx = cgExpr ctx arg
  match argTy with
  | AppTy (UIntTyCtor, _) -> arg, ctx
  | AppTy (IntTyCtor, _)
  | AppTy (CharTyCtor, _) -> CCastExpr(arg, CUInt32Ty), ctx
  | AppTy (StrTyCtor, _) -> CCallExpr(CRefExpr "str_to_uint", [ arg ]), ctx
  | _ -> failwith "Never: Type Error `uint`"

let private cgCallStringExpr arg argTy ctx =
  let arg, ctx = cgExpr ctx arg
  match argTy with
  | AppTy (IntTyCtor, _) -> CCallExpr(CRefExpr "str_of_int", [ arg ]), ctx
  | AppTy (UIntTyCtor, _) -> CCallExpr(CRefExpr "str_of_uint", [ arg ]), ctx
  | AppTy (CharTyCtor, _) -> CCallExpr(CRefExpr "str_of_char", [ arg ]), ctx
  | AppTy (StrTyCtor, _) -> arg, ctx
  | _ -> failwith "Never: Type Error `string`"

let private cgCallPrimExpr ctx prim args primTy resultTy loc =
  match prim, args, primTy with
  | HPrim.NativeFun (nativeFunIdent, _), _, _ ->
      let args, ctx = cgExprList ctx args
      CCallExpr(CRefExpr nativeFunIdent, args), ctx

  | HPrim.Printfn, (MLitExpr (StrLit format, _)) :: args, _ -> cgPrintfnCallExpr ctx format args

  | HPrim.Assert, _, _ ->
      let args, ctx = cgExprList ctx args
      // Embed the source location information.
      let args =
        let _, y, x = loc
        List.append args [ CIntExpr y; CIntExpr x ]

      let ctx =
        addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_assert", args)))

      genDefault ctx resultTy

  | HPrim.StrGetSlice, _, _ ->
      let args, ctx = cgExprList ctx args
      CCallExpr(CRefExpr "str_get_slice", args), ctx

  | HPrim.Char, [ arg ], _ ->
      let arg, ctx = cgExpr ctx arg
      CCastExpr(arg, CCharTy), ctx

  | HPrim.Int, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> cgCallIntExpr arg argTy ctx

  | HPrim.UInt, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> cgCallUIntExpr arg argTy ctx

  | HPrim.String, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> cgCallStringExpr arg argTy ctx

  | _ -> failwithf "Invalid call to primitive %A" (prim, args, primTy, resultTy)

let private cgCallInRegionExpr ctx serial arg ty _loc =
  let arg, ctx = cgExpr ctx arg

  // Enter, call, leave. The result of call is set to the initialized variable.
  let ctx =
    addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_enter_region", [])))

  let ctx =
    // t <- f ()
    let unitLit, ctx = genDefault ctx tyUnit

    let result, ctx = doGenCallClosureExpr ctx arg [ unitLit ]

    doGenLetValStmt ctx serial (Some result) ty

  let ctx =
    addStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_leave_region", [])))

  ctx

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

let private addLetStmt ctx ident expr cty storageModifier =
  match storageModifier with
  | StaticSM ->
      let ctx = addDecl ctx (CStaticVarDecl(ident, cty))

      match expr with
      | Some expr -> addStmt ctx (CSetStmt(CRefExpr ident, expr))
      | _ -> ctx

  | AutoSM -> addStmt ctx (CLetStmt(ident, expr, cty))

let private addLetAllocStmt ctx ident valPtrTy varTy storageModifier =
  match storageModifier with
  | StaticSM -> failwith "NEVER: let-alloc is used only for temporary variables"
  | AutoSM -> addStmt ctx (CLetAllocStmt(ident, valPtrTy, varTy))

let private doGenLetValStmt ctx serial expr ty =
  let ident = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let cty, ctx = cgTyComplete ctx ty
  addLetStmt ctx ident expr cty storageModifier

let private cgClosureInit ctx serial funSerial envSerial ty =
  let ident = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let ty, ctx = cgTyComplete ctx ty

  let fields =
    [ "fun", CRefExpr(getUniqueVarName ctx funSerial)
      "env", CRefExpr(getUniqueVarName ctx envSerial) ]

  let initExpr = CInitExpr(fields, ty)
  addLetStmt ctx ident (Some initExpr) ty storageModifier

let private cgBoxInit ctx serial arg =
  let argTy, ctx = cgTyComplete ctx (mexprToTy arg)
  let arg, ctx = cgExpr ctx arg

  // void* p = (void*)malloc(sizeof T);
  let temp = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial

  let ctx =
    addLetAllocStmt ctx temp (CPtrTy argTy) (CPtrTy CVoidTy) storageModifier

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CRefExpr temp, CPtrTy argTy))

  let ctx = addStmt ctx (CSetStmt(left, arg))

  ctx

let private cgConsInit ctx serial head tail listTy =
  let temp = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let listTy, ctx = cgTyComplete ctx listTy

  let ctx =
    addLetAllocStmt ctx temp listTy listTy storageModifier

  // head
  let head, ctx = cgExpr ctx head

  let stmt =
    CSetStmt(CArrowExpr(CRefExpr temp, "head"), head)

  let ctx = addStmt ctx stmt

  // tail
  let tail, ctx = cgExpr ctx tail

  let stmt =
    CSetStmt(CArrowExpr(CRefExpr temp, "tail"), tail)

  let ctx = addStmt ctx stmt

  ctx

let private cgTupleInit ctx serial items tupleTy =
  let ident = getUniqueVarName ctx serial
  let storageModifier = findStorageModifier ctx serial
  let tupleTy, ctx = cgTyComplete ctx tupleTy

  let ctx =
    addLetStmt ctx ident None tupleTy storageModifier

  let rec go ctx i items =
    match items with
    | [] -> ctx
    | item :: items ->
        let left = CNavExpr(CRefExpr ident, tupleField i)
        let item, ctx = cgExpr ctx item
        let stmt = CSetStmt(left, item)
        let ctx = addStmt ctx stmt
        go ctx (i + 1) items

  go ctx 0 items

let private cgVariantInit ctx varSerial variantSerial payload unionTy =
  let temp = getUniqueVarName ctx varSerial

  let storageModifier = findStorageModifier ctx varSerial

  let unionTy, ctx = cgTyComplete ctx unionTy
  let variantName = getUniqueVarName ctx variantSerial

  let payloadExpr, ctx = cgExpr ctx payload

  let fields =
    [ "tag", CRefExpr(getUniqueVarName ctx variantSerial)
      variantName, payloadExpr ]

  let init = CInitExpr(fields, unionTy)

  let ctx =
    addLetStmt ctx temp (Some init) unionTy storageModifier

  ctx

let private cgLetValStmt ctx serial init ty loc =
  match init with
  | MUninitInit -> doGenLetValStmt ctx serial None ty

  | MExprInit expr ->
      let expr, ctx = cgExpr ctx expr
      doGenLetValStmt ctx serial (Some expr) ty

  | MCallPrimInit (HPrim.InRegion, [ arg ], _) -> cgCallInRegionExpr ctx serial arg ty loc

  | MCallPrimInit (prim, args, calleeTy) ->
      let expr, ctx =
        cgCallPrimExpr ctx prim args calleeTy ty loc

      doGenLetValStmt ctx serial (Some expr) ty

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

let private cgSetStmt ctx serial right =
  let right, ctx = cgExpr ctx right
  let ident = getUniqueVarName ctx serial
  let left = CRefExpr(ident)
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
  | MLetValStmt (serial, init, ty, loc) -> cgLetValStmt ctx serial init ty loc
  | MSetStmt (serial, right, _) -> cgSetStmt ctx serial right
  | MLabelStmt (label, _) -> addStmt ctx (CLabelStmt label)
  | MTerminatorStmt (terminator, _loc) -> cgTerminatorStmt ctx terminator

  | MIfStmt (cond, thenCl, elseCl, _) ->
      let cond, ctx = cgExpr ctx cond
      let thenCl, ctx = cgBlock ctx thenCl
      let elseCl, ctx = cgBlock ctx elseCl
      addStmt ctx (CIfStmt(cond, thenCl, elseCl))

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

  | MProcDecl (callee, isMainFun, args, body, resultTy, _) :: decls ->
      let ident, args =
        if isMainFun then "main", [] else getUniqueVarName ctx callee, args

      let rec go acc ctx args =
        match args with
        | [] -> List.rev acc, ctx
        | (arg, ty, _) :: args ->
            let ident = getUniqueVarName ctx arg
            let cty, ctx = cgTyComplete ctx ty
            go ((ident, cty) :: acc) ctx args

      let args, ctx = go [] ctx args
      let body, ctx = cgBlocks ctx body
      let resultTy, ctx = cgTyComplete ctx resultTy
      let funDecl = CFunDecl(ident, args, resultTy, body)
      let ctx = addDecl ctx funDecl
      cgDecls ctx decls

// -----------------------------------------------
// Interface
// -----------------------------------------------

let private genLogs (ctx: CirCtx) =
  let tyDisplayFn ty =
    let getTyIdent tySerial =
      ctx.Tys
      |> mapTryFind tySerial
      |> Option.map tyDefToIdent

    tyDisplay getTyIdent ty

  let rec go (ctx: CirCtx) logs =
    match logs with
    | [] -> ctx
    | (log, loc) :: logs ->
        let _, y, _ = loc
        let msg = log |> logToString tyDisplayFn loc

        let ctx = addDecl ctx (CErrorDecl(msg, 1 + y))

        go ctx logs

  let logs = ctx.Logs |> List.rev
  let ctx = go ctx logs
  let success = logs |> List.isEmpty
  success, ctx

let genCir (decls, mirCtx: MirCtx): CDecl list * bool =
  let ctx = ofMirCtx mirCtx
  let ctx = cgDecls ctx decls
  let success, ctx = genLogs ctx
  let decls = ctx.Decls |> List.rev
  decls, success
