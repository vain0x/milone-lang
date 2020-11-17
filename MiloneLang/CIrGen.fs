/// Converts MIR to CIR.
///
/// CIR is a kind of abstract syntax tree of C.
///
/// Maps operations/primitives/types to C operations/functions/types.
/// Generates type declarations for lists/tuples/etc.
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

[<RequireQualifiedAccess>]
type private CirCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    VarUniqueNames: AssocMap<VarSerial, Ident>
    TyEnv: AssocMap<Ty, CTyInstance * CTy>
    Tys: AssocMap<TySerial, TyDef>
    TyUniqueNames: AssocMap<Ty, Ident>
    Stmts: CStmt list
    Decls: CDecl list
    Logs: (Log * Loc) list }

let private cirCtxFromMirCtx (mirCtx: MirCtx): CirCtx =
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

let private cirCtxGetVarStorageModifier (ctx: CirCtx) varSerial =
  match ctx.Vars |> mapTryFind varSerial with
  | Some (VarDef (_, storageModifier, _, _)) -> storageModifier

  | _ -> StaticSM

let private cirCtxAddErr (ctx: CirCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

let private cirCtxNewBlock (ctx: CirCtx) = { ctx with Stmts = [] }

let private cirCtxRollBack (bCtx: CirCtx) (dCtx: CirCtx) = { dCtx with Stmts = bCtx.Stmts }

let private cirCtxAddStmt (ctx: CirCtx) stmt = { ctx with Stmts = stmt :: ctx.Stmts }

let private cirCtxAddDecl (ctx: CirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

let private cirCtxAddFunIncomplete (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> mapTryFind funTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let ident, (ctx: CirCtx) = cirCtxUniqueTyName ctx funTy
      let funStructTy = CStructTy ident

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd funTy (CTyDeclared, funStructTy) }

      funStructTy, ctx

let private cirCtxAddFunDecl (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> mapTryFind funTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let ident, ctx = cirCtxUniqueTyName ctx funTy
      let selfTy, ctx = cirCtxAddFunIncomplete ctx sTy tTy

      let envTy = CPtrTy CVoidTy
      let _, argTys, resultTy = tyToArgList funTy

      let argTys, ctx =
        (argTys, ctx)
        |> stMap (fun (ty, ctx) -> cirCtxConvertTyIncomplete ctx ty)

      let resultTy, (ctx: CirCtx) = cirGetCTy ctx resultTy

      let fields =
        [ "fun", CFunPtrTy(envTy :: argTys, resultTy)
          "env", envTy ]

      let ctx =
        { ctx with
            Decls = CStructDecl(ident, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd funTy (CTyDefined, selfTy) }

      selfTy, ctx

let private cirCtxAddListIncomplete (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let ident, ctx = cirCtxUniqueTyName ctx listTy
      let selfTy = CPtrTy(CStructTy ident)

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private cirCtxAddListDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> mapTryFind listTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let ident, ctx = cirCtxUniqueTyName ctx listTy
      let selfTy, ctx = cirCtxAddListIncomplete ctx itemTy

      let itemTy, (ctx: CirCtx) = cirGetCTy ctx itemTy
      let fields = [ "head", itemTy; "tail", selfTy ]

      let ctx =
        { ctx with
            Decls = CStructDecl(ident, fields, []) :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd listTy (CTyDefined, selfTy) }

      selfTy, ctx

let private cirCtxAddTupleIncomplete (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let tupleTyIdent, ctx = cirCtxUniqueTyName ctx tupleTy
      let selfTy = CStructTy tupleTyIdent

      let ctx =
        { ctx with
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDeclared, selfTy) }

      selfTy, ctx

let private cirCtxAddTupleDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> mapTryFind tupleTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let tupleTyIdent, ctx = cirCtxUniqueTyName ctx tupleTy
      let selfTy, ctx = cirCtxAddTupleIncomplete ctx itemTys

      let rec go i itemTys =
        match itemTys with
        | [] -> []

        | itemTy :: itemTys ->
            let field = tupleField i, itemTy
            field :: go (i + 1) itemTys

      let itemTys, (ctx: CirCtx) = cirCtxGetCTys (itemTys, ctx)
      let fields = go 0 itemTys

      let tupleDecl = CStructDecl(tupleTyIdent, fields, [])

      let ctx =
        { ctx with
            Decls = tupleDecl :: ctx.Decls
            TyEnv = ctx.TyEnv |> mapAdd tupleTy (CTyDefined, selfTy) }

      selfTy, ctx

let private cirCtxAddUnionIncomplete (ctx: CirCtx) tySerial =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
      let selfTy = CStructTy unionTyIdent

      let ctx =
        { ctx with
            TyEnv =
              ctx.TyEnv
              |> mapAdd unionTyRef (CTyDeclared, selfTy) }

      selfTy, ctx

let private cirCtxAddUnionDecl (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> mapTryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
      let selfTy, ctx = cirCtxAddUnionIncomplete ctx tySerial

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
        |> List.map (fun (_, serial, _, _) -> cirCtxUniqueName ctx serial)

      let variants, ctx =
        (variants, ctx)
        |> stFlatMap (fun ((_, serial, hasPayload, _payloadTy), acc, ctx) ->
             if hasPayload then
               //  let payloadTy, ctx = cirCtxConvertTyIncomplete ctx payloadTy
               //  (cirCtxUniqueName ctx serial, payloadTy)
               //  :: acc,
               //  ctx
               (cirCtxUniqueName ctx serial, ctVoidPtr) :: acc, ctx
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

let private cirCtxAddRecordTyIncomplete (ctx: CirCtx) tySerial =
  let recordTyRef = tyRef tySerial []

  match ctx.TyEnv |> mapTryFind recordTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let recordTyIdent, ctx = cirCtxUniqueTyName ctx recordTyRef
      let selfTy = CStructTy recordTyIdent

      // TODO: Generate type declaration.

      selfTy, ctx

let private cirCtxAddRecordTyDecl ctx tySerial _fields =
  let recordTyRef = tyRef tySerial []
  let recordTyIdent, ctx = cirCtxUniqueTyName ctx recordTyRef
  let selfTy = CStructTy recordTyIdent

  // TODO: Generate type definition.

  selfTy, ctx

let private cirCtxUniqueName (ctx: CirCtx) serial =
  match ctx.VarUniqueNames |> mapTryFind serial with
  | Some ident -> ident
  | None -> failwithf "Never: Unknown value-level identifier serial %d" serial

let private cirCtxUniqueTyName (ctx: CirCtx) ty: _ * CirCtx =
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

let private cirCtxConvertTyIncomplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (BoolTyCtor, _)
  | AppTy (IntTyCtor, _)
  | AppTy (TupleTyCtor, []) -> CIntTy, ctx

  | AppTy (UIntTyCtor, _) -> CUInt32Ty, ctx

  | AppTy (CharTyCtor, _) -> CCharTy, ctx

  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTyCtor, _) -> CPtrTy CVoidTy, ctx

  | AppTy (FunTyCtor, [ sTy; tTy ]) -> cirCtxAddFunIncomplete ctx sTy tTy

  | AppTy (ListTyCtor, [ itemTy ]) -> cirCtxAddListIncomplete ctx itemTy

  | AppTy (TupleTyCtor, itemTys) -> cirCtxAddTupleIncomplete ctx itemTys

  | AppTy (RefTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cirCtxConvertTyIncomplete ctx ty

      | Some (UnionTyDef _) -> cirCtxAddUnionIncomplete ctx serial

      | Some (RecordTyDef _) -> cirCtxAddRecordTyIncomplete ctx serial

      | _ -> CVoidTy, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ -> CVoidTy, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let private cirGetCTy (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | AppTy (BoolTyCtor, _)
  | AppTy (IntTyCtor, _)
  | AppTy (TupleTyCtor, []) -> CIntTy, ctx

  | AppTy (UIntTyCtor, []) -> CUInt32Ty, ctx

  | AppTy (CharTyCtor, _) -> CCharTy, ctx

  | AppTy (StrTyCtor, _) -> CStructTy "String", ctx

  | MetaTy _ // FIXME: Unresolved type variables are `obj` for now.
  | AppTy (ObjTyCtor, _) -> CPtrTy CVoidTy, ctx

  | AppTy (FunTyCtor, [ sTy; tTy ]) -> cirCtxAddFunDecl ctx sTy tTy

  | AppTy (ListTyCtor, [ itemTy ]) -> cirCtxAddListDecl ctx itemTy

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

      cirCtxAddTupleDecl ctx itemTys

  | AppTy (RefTyCtor serial, useTyArgs) ->
      match ctx.Tys |> mapTryFind serial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
          let ty =
            tyExpandSynonym useTyArgs defTySerials bodyTy

          cirGetCTy ctx ty

      | Some (UnionTyDef (_, variants, _)) -> cirCtxAddUnionDecl ctx serial variants

      | Some (RecordTyDef (_, fields, _)) -> cirCtxAddRecordTyDecl ctx serial fields

      | _ -> CVoidTy, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ -> CVoidTy, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let private cirCtxGetCTys (tys, ctx) =
  stMap (fun (ty, ctx) -> cirGetCTy ctx ty) (tys, ctx)

let private cOpFrom op =
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

/// `0`, `NULL`, or `(T) {}`
let private genExprDefault ctx ty =
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
      let ty, ctx = cirGetCTy ctx ty
      CCastExpr(CDefaultExpr, ty), ctx
  | ErrorTy _ -> failwithf "Never %A" ty

let private genExprProc ctx serial _ty _loc =
  let ident = cirCtxUniqueName ctx serial
  CRefExpr ident, ctx

let private genExprVariant ctx serial ty =
  let ty, ctx = cirGetCTy ctx ty
  let tag = CRefExpr(cirCtxUniqueName ctx serial)
  CInitExpr([ "tag", tag ], ty), ctx

let private genExprBinAsCall ctx ident l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let callExpr = CCallExpr(CRefExpr ident, [ l; r ])
  callExpr, ctx

let private genExprUniOp ctx op arg ty _ =
  let arg, ctx = genExpr ctx arg
  match op with
  | MNotUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MStrPtrUnary -> CNavExpr(arg, "str"), ctx
  | MStrLenUnary -> CNavExpr(arg, "len"), ctx
  | MUnboxUnary ->
      let valTy, ctx = cirGetCTy ctx ty

      let deref =
        CUnaryExpr(CDerefUnary, CCastExpr(arg, CPtrTy valTy))

      deref, ctx
  | MProjUnary index -> CProjExpr(arg, index), ctx
  | MTagUnary -> CNavExpr(arg, "tag"), ctx
  | MGetVariantUnary serial ->
      let _, ctx = cirGetCTy ctx ty
      CNavExpr(arg, cirCtxUniqueName ctx serial), ctx
  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MListHeadUnary -> CArrowExpr(arg, "head"), ctx
  | MListTailUnary -> CArrowExpr(arg, "tail"), ctx

let private genExprBin ctx op l r =
  match op with
  | MStrAddBinary -> genExprBinAsCall ctx "str_add" l r
  | MStrCmpBinary -> genExprBinAsCall ctx "str_cmp" l r
  | MStrIndexBinary ->
      let l, ctx = genExpr ctx l
      let r, ctx = genExpr ctx r
      CIndexExpr(CNavExpr(l, "str"), r), ctx
  | _ ->
      let l, ctx = genExpr ctx l
      let r, ctx = genExpr ctx r
      let opExpr = CBinaryExpr(cOpFrom op, l, r)
      opExpr, ctx

let private genExprList ctx exprs =
  let rec go results ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
        let result, ctx = genExpr ctx expr
        go (result :: results) ctx exprs

  go [] ctx exprs

let private genExpr (ctx: CirCtx) (arg: MExpr): CExpr * CirCtx =
  match arg |> mxSugar with
  | MLitExpr (IntLit value, _) -> CIntExpr value, ctx
  | MLitExpr (CharLit value, _) -> CCharExpr value, ctx
  | MLitExpr (StrLit value, _) -> CStrObjExpr value, ctx
  | MLitExpr (BoolLit false, _) -> CIntExpr 0, ctx
  | MLitExpr (BoolLit true, _) -> CIntExpr 1, ctx
  | MDefaultExpr (ty, _) -> genExprDefault ctx ty
  | MRefExpr (serial, _, _) -> CRefExpr(cirCtxUniqueName ctx serial), ctx
  | MProcExpr (serial, ty, loc) -> genExprProc ctx serial ty loc
  | MVariantExpr (_, serial, ty, _) -> genExprVariant ctx serial ty
  | MTagExpr (variantSerial, _) -> CRefExpr(cirCtxUniqueName ctx variantSerial), ctx
  | MUnaryExpr (op, arg, ty, loc) -> genExprUniOp ctx op arg ty loc
  | MBinaryExpr (op, l, r, _, _) -> genExprBin ctx op l r

let private genExprCallPrintfn ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] -> List.rev acc, ctx
    | MLitExpr (StrLit value, _) :: args -> go (CStrRawExpr value :: acc) ctx args
    | arg :: args when tyEq (mexprToTy arg) tyStr ->
        let arg, ctx = genExpr ctx arg
        let acc = CNavExpr(arg, "str") :: acc
        go acc ctx args
    | arg :: args ->
        let arg, ctx = genExpr ctx arg
        go (arg :: acc) ctx args

  let args, ctx = go [] ctx args
  let format = CStrRawExpr(format + "\n")

  let expr =
    CExprStmt(CCallExpr(CRefExpr "printf", format :: args))

  let ctx = cirCtxAddStmt ctx expr
  genExprDefault ctx tyUnit

let private genExprCallInt arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | AppTy (IntTyCtor, _) -> arg, ctx
  | AppTy (UIntTyCtor, _)
  | AppTy (CharTyCtor, _) -> CCastExpr(arg, CIntTy), ctx
  | AppTy (StrTyCtor, _) -> CCallExpr(CRefExpr "str_to_int", [ arg ]), ctx
  | _ -> failwith "Never: Type Error `int`"

let private genExprCallUInt arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | AppTy (UIntTyCtor, _) -> arg, ctx
  | AppTy (IntTyCtor, _)
  | AppTy (CharTyCtor, _) -> CCastExpr(arg, CUInt32Ty), ctx
  | AppTy (StrTyCtor, _) -> CCallExpr(CRefExpr "str_to_uint", [ arg ]), ctx
  | _ -> failwith "Never: Type Error `uint`"

let private genExprCallString arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | AppTy (IntTyCtor, _) -> CCallExpr(CRefExpr "str_of_int", [ arg ]), ctx
  | AppTy (UIntTyCtor, _) -> CCallExpr(CRefExpr "str_of_uint", [ arg ]), ctx
  | AppTy (CharTyCtor, _) -> CCallExpr(CRefExpr "str_of_char", [ arg ]), ctx
  | AppTy (StrTyCtor, _) -> arg, ctx
  | _ -> failwith "Never: Type Error `string`"

let private genExprCallPrim ctx prim args primTy resultTy loc =
  match prim, args, primTy with
  | HPrim.NativeFun (nativeFunIdent, _), _, _ ->
      let args, ctx = genExprList ctx args
      CCallExpr(CRefExpr nativeFunIdent, args), ctx

  | HPrim.Printfn, (MLitExpr (StrLit format, _)) :: args, _ -> genExprCallPrintfn ctx format args

  | HPrim.Assert, _, _ ->
      let callee = CRefExpr "milone_assert"
      let args, ctx = genExprList ctx args
      // Embed the source location information.
      let args =
        let _, y, x = loc
        List.append args [ CIntExpr y; CIntExpr x ]

      let assertCall = CCallExpr(callee, args)

      let ctx = cirCtxAddStmt ctx (CExprStmt assertCall)

      genExprDefault ctx resultTy

  | HPrim.StrGetSlice, _, _ ->
      let callee = CRefExpr "str_get_slice"
      let args, ctx = genExprList ctx args
      CCallExpr(callee, args), ctx

  | HPrim.Char, [ arg ], _ ->
      let arg, ctx = genExpr ctx arg
      CCastExpr(arg, CCharTy), ctx

  | HPrim.Int, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> genExprCallInt arg argTy ctx

  | HPrim.UInt, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> genExprCallUInt arg argTy ctx

  | HPrim.String, [ arg ], AppTy (FunTyCtor, [ argTy; _ ]) -> genExprCallString arg argTy ctx

  | _ -> failwithf "Invalid call to primitive %A" (prim, args, primTy, resultTy)

let private genExprCallPrimInRegion ctx serial arg ty _loc =
  let arg, ctx = genExpr ctx arg

  // Enter, call, leave. The result of call is set to the initialized variable.
  let ctx =
    cirCtxAddStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_enter_region", [])))

  let ctx =
    // t <- f ()
    let unitLit, ctx = genExprDefault ctx tyUnit

    let result, ctx =
      genExprCallClosureCore ctx arg [ unitLit ]

    genInitExprCore ctx serial (Some result) ty

  let ctx =
    cirCtxAddStmt ctx (CExprStmt(CCallExpr(CRefExpr "milone_leave_region", [])))

  ctx

let private genExprCallProc ctx callee args ty =
  match callee, args with
  | _ ->
      let callee, ctx = genExpr ctx callee
      let args, ctx = genExprList ctx args
      CCallExpr(callee, args), ctx

let private genExprCallClosureCore ctx callee args =
  let funPtr = CNavExpr(callee, "fun")
  let envArg = CNavExpr(callee, "env")
  CCallExpr(funPtr, envArg :: args), ctx

let private genExprCallClosure ctx callee args =
  let callee, ctx = genExpr ctx callee
  let args, ctx = genExprList ctx args
  genExprCallClosureCore ctx callee args

let private cirCtxAddLetStmt ctx ident expr cty storageModifier =
  match storageModifier with
  | StaticSM ->
      let ctx =
        cirCtxAddDecl ctx (CStaticVarDecl(ident, cty))

      match expr with
      | Some expr -> cirCtxAddStmt ctx (CSetStmt(CRefExpr ident, expr))
      | _ -> ctx
  | AutoSM -> cirCtxAddStmt ctx (CLetStmt(ident, expr, cty))

let private cirCtxAddLetAllocStmt ctx ident valPtrTy varTy storageModifier =
  match storageModifier with
  | StaticSM -> failwith "NEVER: let-alloc is used only for temporary variables"
  | AutoSM -> cirCtxAddStmt ctx (CLetAllocStmt(ident, valPtrTy, varTy))

let private genInitExprCore ctx serial expr ty =
  let ident = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let cty, ctx = cirGetCTy ctx ty
  cirCtxAddLetStmt ctx ident expr cty storageModifier

let private genInitClosure ctx serial funSerial envSerial ty =
  let ident = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let ty, ctx = cirGetCTy ctx ty

  let fields =
    [ "fun", CRefExpr(cirCtxUniqueName ctx funSerial)
      "env", CRefExpr(cirCtxUniqueName ctx envSerial) ]

  let initExpr = CInitExpr(fields, ty)
  cirCtxAddLetStmt ctx ident (Some initExpr) ty storageModifier

let private genInitBox ctx serial arg =
  let argTy, ctx = cirGetCTy ctx (mexprToTy arg)
  let arg, ctx = genExpr ctx arg

  // void* p = (void*)malloc(sizeof T);
  let temp = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial

  let ctx =
    cirCtxAddLetAllocStmt ctx temp (CPtrTy argTy) (CPtrTy CVoidTy) storageModifier

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CRefExpr temp, CPtrTy argTy))

  let ctx = cirCtxAddStmt ctx (CSetStmt(left, arg))

  ctx

let private genInitCons ctx serial head tail listTy =
  let temp = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let listTy, ctx = cirGetCTy ctx listTy

  let ctx =
    cirCtxAddLetAllocStmt ctx temp listTy listTy storageModifier

  // head
  let head, ctx = genExpr ctx head

  let stmt =
    CSetStmt(CArrowExpr(CRefExpr temp, "head"), head)

  let ctx = cirCtxAddStmt ctx stmt

  // tail
  let tail, ctx = genExpr ctx tail

  let stmt =
    CSetStmt(CArrowExpr(CRefExpr temp, "tail"), tail)

  let ctx = cirCtxAddStmt ctx stmt

  ctx

let private genInitTuple ctx serial items tupleTy =
  let ident = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let tupleTy, ctx = cirGetCTy ctx tupleTy

  let ctx =
    cirCtxAddLetStmt ctx ident None tupleTy storageModifier

  let rec go ctx i items =
    match items with
    | [] -> ctx
    | item :: items ->
        let left = CNavExpr(CRefExpr ident, tupleField i)
        let item, ctx = genExpr ctx item
        let stmt = CSetStmt(left, item)
        let ctx = cirCtxAddStmt ctx stmt
        go ctx (i + 1) items

  go ctx 0 items

let private genInitVariant ctx varSerial variantSerial payload unionTy =
  let temp = cirCtxUniqueName ctx varSerial

  let storageModifier =
    cirCtxGetVarStorageModifier ctx varSerial

  let unionTy, ctx = cirGetCTy ctx unionTy
  let variantName = cirCtxUniqueName ctx variantSerial

  let payloadExpr, ctx = genExpr ctx payload

  let fields =
    [ "tag", CRefExpr(cirCtxUniqueName ctx variantSerial)
      variantName, payloadExpr ]

  let init = CInitExpr(fields, unionTy)

  let ctx =
    cirCtxAddLetStmt ctx temp (Some init) unionTy storageModifier

  ctx

let private genStmtLetVal ctx serial init ty loc =
  match init with
  | MUninitInit -> genInitExprCore ctx serial None ty
  | MExprInit expr ->
      let expr, ctx = genExpr ctx expr
      genInitExprCore ctx serial (Some expr) ty

  | MCallPrimInit (HPrim.InRegion, [ arg ], _) -> genExprCallPrimInRegion ctx serial arg ty loc

  | MCallPrimInit (prim, args, calleeTy) ->
      let expr, ctx =
        genExprCallPrim ctx prim args calleeTy ty loc

      genInitExprCore ctx serial (Some expr) ty
  | MCallProcInit (callee, args, _) ->
      let expr, ctx = genExprCallProc ctx callee args ty
      genInitExprCore ctx serial (Some expr) ty
  | MCallClosureInit (callee, args) ->
      let expr, ctx = genExprCallClosure ctx callee args
      genInitExprCore ctx serial (Some expr) ty
  | MClosureInit (funSerial, envSerial) -> genInitClosure ctx serial funSerial envSerial ty
  | MBoxInit arg -> genInitBox ctx serial arg
  | MConsInit (head, tail) -> genInitCons ctx serial head tail ty
  | MTupleInit items -> genInitTuple ctx serial items ty
  | MVariantInit (variantSerial, payload) -> genInitVariant ctx serial variantSerial payload ty

let private genStmtSet ctx serial right =
  let right, ctx = genExpr ctx right
  let ident = cirCtxUniqueName ctx serial
  let left = CRefExpr(ident)
  cirCtxAddStmt ctx (CSetStmt(left, right))

let private genStmtReturn ctx expr =
  let expr, ctx = genExpr ctx expr
  cirCtxAddStmt ctx (CReturnStmt(Some expr))

let private genStmtJump ctx stmt =
  match stmt with
  | MReturnStmt (expr, _) -> genStmtReturn ctx expr
  | MLabelStmt (label, _) -> cirCtxAddStmt ctx (CLabelStmt label)
  | MGotoStmt (label, _) -> cirCtxAddStmt ctx (CGotoStmt label)
  | MGotoIfStmt (pred, label, _) ->
      let pred, ctx = genExpr ctx pred
      cirCtxAddStmt ctx (CGotoIfStmt(pred, label))

  | MExitStmt (arg, _) ->
      let doArm () =
        let arg, ctx = genExpr ctx arg
        cirCtxAddStmt ctx (CExprStmt(CCallExpr(CRefExpr "exit", [ arg ])))

      doArm ()
  | _ -> failwith "NEVER"

let private genStmt ctx stmt =
  match stmt with
  | MLetValStmt (serial, init, ty, loc) -> genStmtLetVal ctx serial init ty loc
  | MSetStmt (serial, right, _) -> genStmtSet ctx serial right
  | MReturnStmt _
  | MLabelStmt _
  | MGotoStmt _
  | MGotoIfStmt _
  | MExitStmt _ -> genStmtJump ctx stmt

  | MIfStmt (cond, thenCl, elseCl, _) ->
      let cond, ctx = genExpr ctx cond
      let thenCl, ctx = genBlock ctx thenCl
      let elseCl, ctx = genBlock ctx elseCl
      cirCtxAddStmt ctx (CIfStmt(cond, thenCl, elseCl))

  | MProcStmt _ -> ctx

let private genBlock (ctx: CirCtx) (stmts: MStmt list) =
  let bodyCtx: CirCtx = genStmts (cirCtxNewBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = cirCtxRollBack ctx bodyCtx
  List.rev stmts, ctx

let private genStmts (ctx: CirCtx) (stmts: MStmt list): CirCtx =
  let rec go ctx stmts =
    match stmts with
    | [] -> ctx
    | stmt :: stmts ->
        let ctx = genStmt ctx stmt
        go ctx stmts

  go ctx stmts

let private genDecls (ctx: CirCtx) decls =
  match decls with
  | [] -> ctx

  | MProcStmt (callee, isMainFun, args, body, resultTy, _) :: decls ->
      let ident, args =
        if isMainFun then "main", [] else cirCtxUniqueName ctx callee, args

      let rec go acc ctx args =
        match args with
        | [] -> List.rev acc, ctx
        | (arg, ty, _) :: args ->
            let ident = cirCtxUniqueName ctx arg
            let cty, ctx = cirGetCTy ctx ty
            go ((ident, cty) :: acc) ctx args

      let args, ctx = go [] ctx args
      let body, ctx = genBlock ctx body
      let resultTy, ctx = cirGetCTy ctx resultTy
      let funDecl = CFunDecl(ident, args, resultTy, body)
      let ctx = cirCtxAddDecl ctx funDecl
      genDecls ctx decls

  | _ -> failwith "Top-level statements must be declarations."

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

        let ctx =
          cirCtxAddDecl ctx (CErrorDecl(msg, 1 + y))

        go ctx logs

  let logs = ctx.Logs |> List.rev
  let ctx = go ctx logs
  let success = logs |> List.isEmpty
  success, ctx

let gen (decls, mirCtx: MirCtx): CDecl list * bool =
  let ctx = cirCtxFromMirCtx mirCtx
  let ctx = genDecls ctx decls
  let success, ctx = genLogs ctx
  let decls = ctx.Decls |> List.rev
  decls, success
