/// Converts MIR to CIR.
///
/// CIR is a kind of abstract syntax tree of C.
///
/// Maps operations/primitives/types to C operations/functions/types.
/// Generates type declarations for lists/tuples/etc.
module rec MiloneLang.CIrGen

open MiloneLang.Records
open MiloneLang.Types
open MiloneLang.Helpers

let renameIdents toIdent toKey mapFuns (defMap: AssocMap<int, _>) =
  let rename (ident: string) (index: int) =
    if index = 0 then ident + "_" else ident + "_" + string index

  // Group serials by ident.
  let rec go acc xs =
    match xs with
    | [] -> acc

    | (serial, def) :: xs ->
        let ident = toIdent def

        let serials =
          acc |> mapTryFind ident |> optionDefaultValue []

        let acc = acc |> mapAdd ident (serial :: serials)
        go acc xs

  let serialsMap =
    go (mapEmpty (strHash, strCmp)) (defMap |> mapToList)

  let addIdent ident (identMap, index) serial =
    identMap
    |> mapAdd (toKey serial) (rename ident index),
    index + 1

  let addIdents identMap ident serials =
    serials
    |> listRev
    |> listFold (addIdent ident) (identMap, 0)
    |> fst

  serialsMap |> mapFold addIdents (mapEmpty mapFuns)

let tupleField (i: int) = "t" + string i

/// Calculates tag type's name of union type.
let tagTyIdent (tyIdent: string) = tyIdent + "Tag"

let cirCtxFromMirCtx (mirCtx: MirCtx): CirCtx =
  let varNames =
    mirCtx
    |> mirCtxGetVars
    |> renameIdents varDefToIdent id (intHash, intCmp)

  let tyNames =
    mirCtx
    |> mirCtxGetTys
    |> renameIdents tyDefToIdent (fun serial -> tyRef serial []) (tyToHash, tyCmp)

  CirCtx
    (mirCtx |> mirCtxGetVars,
     varNames,
     mapEmpty (tyToHash, tyCmp),
     mirCtx |> mirCtxGetTys,
     tyNames,
     [],
     [],
     mirCtx |> mirCtxGetLogs)

let cirCtxGetVarStorageModifier (ctx: CirCtx) varSerial =
  match ctx |> cirCtxGetVars |> mapTryFind varSerial with
  | Some (VarDef.Var (_, storageModifier, _, _)) -> storageModifier

  | _ -> StorageModifier.Static

let cirCtxAddErr (ctx: CirCtx) message loc =
  ctx
  |> cirCtxWithLogs ((Log.Error message, loc) :: (ctx |> cirCtxGetLogs))

let cirCtxNewBlock (ctx: CirCtx) = ctx |> cirCtxWithStmts []

let cirCtxRollBack (bCtx: CirCtx) (dCtx: CirCtx) =
  dCtx |> cirCtxWithStmts (bCtx |> cirCtxGetStmts)

let cirCtxAddStmt (ctx: CirCtx) stmt =
  ctx
  |> cirCtxWithStmts (stmt :: (ctx |> cirCtxGetStmts))

let cirCtxAddDecl (ctx: CirCtx) decl =
  ctx
  |> cirCtxWithDecls (decl :: (ctx |> cirCtxGetDecls))

let cirCtxAddFunIncomplete (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind funTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let ident, ctx = cirCtxUniqueTyName ctx funTy
      let funStructTy = CStructTy ident

      let ctx =
        ctx
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd funTy (CTyDeclared, funStructTy))

      funStructTy, ctx

let cirCtxAddFunDecl (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind funTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let ident, ctx = cirCtxUniqueTyName ctx funTy
      let selfTy, ctx = cirCtxAddFunIncomplete ctx sTy tTy

      let envTy = CPtrTy CVoidTy
      let _, argTys, resultTy = tyToArgList funTy

      let argTys, ctx =
        (argTys, ctx)
        |> stMap (fun (ty, ctx) -> cirCtxConvertTyIncomplete ctx ty)

      let resultTy, ctx = cirGetCTy ctx resultTy

      let fields =
        [ "fun", CFunPtrTy(envTy :: argTys, resultTy)
          "env", envTy ]

      let ctx =
        ctx
        |> cirCtxWithDecls
             (CStructDecl(ident, fields, [])
              :: (ctx |> cirCtxGetDecls))
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd funTy (CTyDefined, selfTy))

      selfTy, ctx

let cirCtxAddListIncomplete (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind listTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let ident, ctx = cirCtxUniqueTyName ctx listTy
      let selfTy = CPtrTy(CStructTy ident)

      let ctx =
        ctx
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd listTy (CTyDeclared, selfTy))

      selfTy, ctx

let cirCtxAddListDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind listTy with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let ident, ctx = cirCtxUniqueTyName ctx listTy
      let selfTy, ctx = cirCtxAddListIncomplete ctx itemTy

      let itemTy, ctx = cirGetCTy ctx itemTy
      let fields = [ "head", itemTy; "tail", selfTy ]

      let ctx: CirCtx =
        ctx
        |> cirCtxWithDecls
             (CStructDecl(ident, fields, [])
              :: (ctx |> cirCtxGetDecls))
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd listTy (CTyDefined, selfTy))

      selfTy, ctx

let cirCtxAddTupleIncomplete (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx |> cirCtxGetTyEnv |> mapTryFind tupleTy with
  | Some (_, ty) -> ty, ctx

  | None ->
      let tupleTyIdent, ctx = cirCtxUniqueTyName ctx tupleTy
      let selfTy = CStructTy tupleTyIdent

      let ctx =
        ctx
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd tupleTy (CTyDeclared, selfTy))

      selfTy, ctx

let cirCtxAddTupleDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx |> cirCtxGetTyEnv |> mapTryFind tupleTy with
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

      let itemTys, ctx = cirCtxGetCTys (itemTys, ctx)
      let fields = go 0 itemTys

      let tupleDecl = CStructDecl(tupleTyIdent, fields, [])

      let ctx: CirCtx =
        ctx
        |> cirCtxWithDecls (tupleDecl :: (ctx |> cirCtxGetDecls))
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd tupleTy (CTyDefined, selfTy))

      selfTy, ctx

let cirCtxAddUnionIncomplete (ctx: CirCtx) tySerial =
  let unionTyRef = tyRef tySerial []
  match ctx |> cirCtxGetTyEnv |> mapTryFind unionTyRef with
  | Some (_, ty) -> ty, ctx

  | None ->
      let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
      let selfTy = CStructTy unionTyIdent

      let ctx =
        ctx
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd unionTyRef (CTyDeclared, selfTy))

      selfTy, ctx

let cirCtxAddUnionDecl (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyRef tySerial []
  match ctx |> cirCtxGetTyEnv |> mapTryFind unionTyRef with
  | Some (CTyDefined, ty) -> ty, ctx

  | _ ->
      let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
      let selfTy, ctx = cirCtxAddUnionIncomplete ctx tySerial

      let tagTyIdent = tagTyIdent unionTyIdent
      let tagTy = CEnumTy tagTyIdent

      let variants =
        variants
        |> listMap (fun variantSerial ->
             match ctx |> cirCtxGetVars |> mapTryFind variantSerial with
             | Some (VarDef.Variant (ident, _, hasPayload, payloadTy, _, _)) ->
                 ident, variantSerial, hasPayload, payloadTy
             | _ -> failwith "Never")

      let tags =
        variants
        |> listMap (fun (_, serial, _, _) -> cirCtxUniqueName ctx serial)

      let variants, ctx =
        (variants, ctx)
        |> stFlatMap (fun ((_, serial, hasPayload, payloadTy), acc, ctx) ->
             if hasPayload then
               let payloadTy, ctx = cirCtxConvertTyIncomplete ctx payloadTy
               (cirCtxUniqueName ctx serial, CPtrTy payloadTy)
               :: acc,
               ctx
             else
               acc, ctx)

      let tagEnumDecl = CEnumDecl(tagTyIdent, tags)

      let structDecl =
        CStructDecl(unionTyIdent, [ "tag", tagTy ], variants)

      let ctx =
        ctx
        |> cirCtxWithDecls
             (structDecl
              :: tagEnumDecl
              :: (ctx |> cirCtxGetDecls))
        |> cirCtxWithTyEnv
             (ctx
              |> cirCtxGetTyEnv
              |> mapAdd unionTyRef (CTyDefined, selfTy))

      selfTy, ctx

let cirCtxUniqueName (ctx: CirCtx) serial =
  match ctx
        |> cirCtxGetVarUniqueNames
        |> mapTryFind serial with
  | Some ident -> ident
  | None -> failwithf "Never: Unknown value-level identifier serial %d" serial

let cirCtxUniqueTyName (ctx: CirCtx) ty =
  let rec go ty (ctx: CirCtx) =
    let tyToUniqueName ty =
      match ty with
      | Ty.Con (TyCon.Bool, _) -> "Bool", ctx

      | Ty.Con (TyCon.Int, _) -> "Int", ctx

      | Ty.Con (TyCon.Char, _) -> "Char", ctx

      | Ty.Con (TyCon.Str, _) -> "String", ctx

      | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
      | Ty.Con (TyCon.Obj, _) -> "Object", ctx

      | Ty.Con (TyCon.Fun, _) ->
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

      | Ty.Con (TyCon.List, [ itemTy ]) ->
          let itemTy, ctx = ctx |> go itemTy
          let listTy = itemTy + "List"
          listTy, ctx

      | Ty.Con (TyCon.Tuple, []) -> "Unit", ctx

      | Ty.Con (TyCon.Tuple, itemTys) ->
          let len = itemTys |> listLength

          let itemTys, ctx =
            (itemTys, ctx)
            |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)

          let tupleTy =
            (itemTys |> strConcat) + "Tuple" + string len

          tupleTy, ctx

      | Ty.Con (TyCon.Ref _, _)
      | Ty.Con (TyCon.List, _)
      | Ty.Con (TyCon.Fun, _)
      | Ty.Error _ ->
          // FIXME: collect error
          failwithf "/* unknown ty %A */" ty

    // Memoization.
    match ctx |> cirCtxGetTyUniqueNames |> mapTryFind ty with
    | Some ident -> ident, ctx

    | None ->
        let ident, ctx = tyToUniqueName ty

        let ctx =
          ctx
          |> cirCtxWithTyUniqueNames (ctx |> cirCtxGetTyUniqueNames |> mapAdd ty ident)

        ident, ctx

  go ty ctx

let cirCtxConvertTyIncomplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _)
  | Ty.Con (TyCon.Tuple, []) -> CIntTy, ctx

  | Ty.Con (TyCon.Char, _) -> CCharTy, ctx

  | Ty.Con (TyCon.Str, _) -> CStructTy "String", ctx

  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Obj, _) -> CPtrTy CVoidTy, ctx

  | Ty.Con (TyCon.Fun, [ sTy; tTy ]) -> cirCtxAddFunIncomplete ctx sTy tTy

  | Ty.Con (TyCon.List, [ itemTy ]) -> cirCtxAddListIncomplete ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) -> cirCtxAddTupleIncomplete ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
      match ctx |> cirCtxGetTys |> mapTryFind serial with
      | Some (TyDef.Union _) -> cirCtxAddUnionIncomplete ctx serial

      | _ -> CVoidTy, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ -> CVoidTy, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let cirGetCTy (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _)
  | Ty.Con (TyCon.Tuple, []) -> CIntTy, ctx

  | Ty.Con (TyCon.Char, _) -> CCharTy, ctx

  | Ty.Con (TyCon.Str, _) -> CStructTy "String", ctx

  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Obj, _) -> CPtrTy CVoidTy, ctx

  | Ty.Con (TyCon.Fun, [ sTy; tTy ]) -> cirCtxAddFunDecl ctx sTy tTy

  | Ty.Con (TyCon.List, [ itemTy ]) -> cirCtxAddListDecl ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) -> cirCtxAddTupleDecl ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
      match ctx |> cirCtxGetTys |> mapTryFind serial with
      | Some (TyDef.Union (_, variants, _)) -> cirCtxAddUnionDecl ctx serial variants

      | _ -> CVoidTy, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ -> CVoidTy, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let cirCtxGetCTys (tys, ctx) =
  stMap (fun (ty, ctx) -> cirGetCTy ctx ty) (tys, ctx)

let cOpFrom op =
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
let genExprDefault ctx ty =
  match ty with
  | Ty.Con (TyCon.Tuple, [])
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _) -> CIntExpr 0, ctx
  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Char, _)
  | Ty.Con (TyCon.Obj, _)
  | Ty.Con (TyCon.List, _) -> CRefExpr "NULL", ctx
  | Ty.Con (TyCon.Str, _)
  | Ty.Con (TyCon.Fun, _)
  | Ty.Con (TyCon.Tuple, _)
  | Ty.Con (TyCon.Ref _, _) ->
      let ty, ctx = cirGetCTy ctx ty
      CCastExpr(CDefaultExpr, ty), ctx
  | Ty.Error _ -> failwithf "Never %A" ty

let genExprProc ctx serial _ty _loc =
  let ident = cirCtxUniqueName ctx serial
  CRefExpr ident, ctx

let genExprVariant ctx serial ty =
  let ty, ctx = cirGetCTy ctx ty
  let tag = CRefExpr(cirCtxUniqueName ctx serial)
  CInitExpr([ "tag", tag ], ty), ctx

let genExprBinAsCall ctx ident l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let callExpr = CCallExpr(CRefExpr ident, [ l; r ])
  callExpr, ctx

let genExprUniOp ctx op arg ty _ =
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
      CUnaryExpr(CDerefUnary, CNavExpr(arg, cirCtxUniqueName ctx serial)), ctx
  | MListIsEmptyUnary -> CUnaryExpr(CNotUnary, arg), ctx
  | MListHeadUnary -> CArrowExpr(arg, "head"), ctx
  | MListTailUnary -> CArrowExpr(arg, "tail"), ctx

let genExprBin ctx op l r =
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

let genExprList ctx exprs =
  let rec go results ctx exprs =
    match exprs with
    | [] -> listRev results, ctx
    | expr :: exprs ->
        let result, ctx = genExpr ctx expr
        go (result :: results) ctx exprs

  go [] ctx exprs

let genExpr (ctx: CirCtx) (arg: MExpr): CExpr * CirCtx =
  match arg |> mxSugar with
  | MExpr.Lit (IntLit value, _) -> CIntExpr value, ctx
  | MExpr.Lit (CharLit value, _) -> CCharExpr value, ctx
  | MExpr.Lit (StrLit value, _) -> CStrObjExpr value, ctx
  | MExpr.Lit (BoolLit false, _) -> CIntExpr 0, ctx
  | MExpr.Lit (BoolLit true, _) -> CIntExpr 1, ctx
  | MExpr.Default (ty, _) -> genExprDefault ctx ty
  | MExpr.Ref (serial, _, _) -> CRefExpr(cirCtxUniqueName ctx serial), ctx
  | MExpr.Proc (serial, ty, loc) -> genExprProc ctx serial ty loc
  | MExpr.Variant (_, serial, ty, _) -> genExprVariant ctx serial ty
  | MExpr.Uni (op, arg, ty, loc) -> genExprUniOp ctx op arg ty loc
  | MExpr.Bin (op, l, r, _, _) -> genExprBin ctx op l r

let genExprCallPrintfn ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] -> listRev acc, ctx
    | MExpr.Lit (StrLit value, _) :: args -> go (CStrRawExpr value :: acc) ctx args
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

let genExprCallInt arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | Ty.Con (TyCon.Int, _) -> arg, ctx
  | Ty.Con (TyCon.Char, _) -> CCastExpr(arg, CIntTy), ctx
  | Ty.Con (TyCon.Str, _) -> CCallExpr(CRefExpr "str_to_int", [ arg ]), ctx
  | _ -> failwith "Never: Type Error `int`"

let genExprCallString arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | Ty.Con (TyCon.Int, _) -> CCallExpr(CRefExpr "str_of_int", [ arg ]), ctx
  | Ty.Con (TyCon.Char, _) -> CCallExpr(CRefExpr "str_of_char", [ arg ]), ctx
  | Ty.Con (TyCon.Str, _) -> arg, ctx
  | _ -> failwith "Never: Type Error `int`"

let genExprCallPrim ctx prim args primTy resultTy loc =
  match prim, args, primTy with
  | HPrim.NativeFun (nativeFunIdent, _), _, _ ->
      let args, ctx = genExprList ctx args
      CCallExpr(CRefExpr nativeFunIdent, args), ctx

  | HPrim.Printfn, (MExpr.Lit (StrLit format, _)) :: args, _ -> genExprCallPrintfn ctx format args

  | HPrim.Assert, _, _ ->
      let callee = CRefExpr "milone_assert"
      let args, ctx = genExprList ctx args
      // Embed the source location information.
      let args =
        let _, y, x = loc
        listAppend args [ CIntExpr y; CIntExpr x ]

      let assertCall = CCallExpr(callee, args)

      let ctx =
        cirCtxAddStmt ctx (CExprStmt assertCall)

      genExprDefault ctx resultTy

  | HPrim.StrGetSlice, _, _ ->
      let callee = CRefExpr "str_get_slice"
      let args, ctx = genExprList ctx args
      CCallExpr(callee, args), ctx

  | HPrim.Char, [ arg ], _ ->
      let arg, ctx = genExpr ctx arg
      CCastExpr(arg, CCharTy), ctx

  | HPrim.Int, [ arg ], Ty.Con (TyCon.Fun, [ argTy; _ ]) -> genExprCallInt arg argTy ctx

  | HPrim.String, [ arg ], Ty.Con (TyCon.Fun, [ argTy; _ ]) -> genExprCallString arg argTy ctx

  | _ -> failwithf "Invalid call to primitive %A" (prim, args, primTy, resultTy)

let genExprCallPrimInRegion ctx serial arg ty _loc =
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

let genExprCallProc ctx callee args ty =
  match callee, args with
  | _ ->
      let callee, ctx = genExpr ctx callee
      let args, ctx = genExprList ctx args
      CCallExpr(callee, args), ctx

let genExprCallClosureCore ctx callee args =
  let funPtr = CNavExpr(callee, "fun")
  let envArg = CNavExpr(callee, "env")
  CCallExpr(funPtr, envArg :: args), ctx

let genExprCallClosure ctx callee args =
  let callee, ctx = genExpr ctx callee
  let args, ctx = genExprList ctx args
  genExprCallClosureCore ctx callee args

let cirCtxAddLetStmt ctx ident expr cty storageModifier =
  match storageModifier with
  | StorageModifier.Static ->
      let ctx =
        cirCtxAddDecl ctx (CStaticVarDecl(ident, cty))

      match expr with
      | Some expr -> cirCtxAddStmt ctx (CSetStmt(CRefExpr ident, expr))
      | _ -> ctx
  | StorageModifier.Auto -> cirCtxAddStmt ctx (CLetStmt(ident, expr, cty))

let cirCtxAddLetAllocStmt ctx ident valPtrTy varTy storageModifier =
  match storageModifier with
  | StorageModifier.Static -> failwith "NEVER: let-alloc is used only for temporary variables"
  | StorageModifier.Auto -> cirCtxAddStmt ctx (CLetAllocStmt(ident, valPtrTy, varTy))

let genInitExprCore ctx serial expr ty =
  let ident = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let cty, ctx = cirGetCTy ctx ty
  cirCtxAddLetStmt ctx ident expr cty storageModifier

let genInitClosure ctx serial funSerial envSerial ty =
  let ident = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let ty, ctx = cirGetCTy ctx ty

  let fields =
    [ "fun", CRefExpr(cirCtxUniqueName ctx funSerial)
      "env", CRefExpr(cirCtxUniqueName ctx envSerial) ]

  let initExpr = CInitExpr(fields, ty)
  cirCtxAddLetStmt ctx ident (Some initExpr) ty storageModifier

let genInitBox ctx serial arg =
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

let genInitIndirect ctx serial payload ty =
  let varName = cirCtxUniqueName ctx serial
  let storageModifier = cirCtxGetVarStorageModifier ctx serial
  let payloadTy, ctx = cirGetCTy ctx ty
  let ptrTy = CPtrTy payloadTy

  let payload, ctx = genExpr ctx payload

  // T* p = (T*)malloc(sizeof T);
  let ctx =
    cirCtxAddLetAllocStmt ctx varName ptrTy ptrTy storageModifier

  // *(T*)p = t;
  let left =
    CUnaryExpr(CDerefUnary, CCastExpr(CRefExpr varName, ptrTy))

  let ctx =
    cirCtxAddStmt ctx (CSetStmt(left, payload))

  ctx

let genInitCons ctx serial head tail listTy =
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

let genInitTuple ctx serial items tupleTy =
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

let genInitVariant ctx varSerial variantSerial payloadSerial unionTy =
  let temp = cirCtxUniqueName ctx varSerial

  let storageModifier =
    cirCtxGetVarStorageModifier ctx varSerial

  let unionTy, ctx = cirGetCTy ctx unionTy
  let variantName = cirCtxUniqueName ctx variantSerial

  let payloadExpr =
    CRefExpr(cirCtxUniqueName ctx payloadSerial)

  let fields =
    [ "tag", CRefExpr(cirCtxUniqueName ctx variantSerial)
      variantName, payloadExpr ]

  let init = CInitExpr(fields, unionTy)

  let ctx =
    cirCtxAddLetStmt ctx temp (Some init) unionTy storageModifier

  ctx

let genStmtLetVal ctx serial init ty loc =
  match init with
  | MInit.UnInit -> genInitExprCore ctx serial None ty
  | MInit.Expr expr ->
      let expr, ctx = genExpr ctx expr
      genInitExprCore ctx serial (Some expr) ty

  | MInit.CallPrim (HPrim.InRegion, [ arg ], _) -> genExprCallPrimInRegion ctx serial arg ty loc

  | MInit.CallPrim (prim, args, calleeTy) ->
      let expr, ctx =
        genExprCallPrim ctx prim args calleeTy ty loc

      genInitExprCore ctx serial (Some expr) ty
  | MInit.CallProc (callee, args, _) ->
      let expr, ctx = genExprCallProc ctx callee args ty
      genInitExprCore ctx serial (Some expr) ty
  | MInit.CallClosure (callee, args) ->
      let expr, ctx = genExprCallClosure ctx callee args
      genInitExprCore ctx serial (Some expr) ty
  | MInit.Closure (funSerial, envSerial) -> genInitClosure ctx serial funSerial envSerial ty
  | MInit.Box arg -> genInitBox ctx serial arg
  | MInit.Indirect payload -> genInitIndirect ctx serial payload ty
  | MInit.Cons (head, tail) -> genInitCons ctx serial head tail ty
  | MInit.Tuple items -> genInitTuple ctx serial items ty
  | MInit.Variant (variantSerial, payloadSerial) -> genInitVariant ctx serial variantSerial payloadSerial ty

let genStmtDo ctx expr =
  let expr, ctx = genExpr ctx expr
  cirCtxAddStmt ctx (CExprStmt expr)

let genStmtSet ctx serial right =
  let right, ctx = genExpr ctx right
  let ident = cirCtxUniqueName ctx serial
  let left = CRefExpr(ident)
  cirCtxAddStmt ctx (CSetStmt(left, right))

let genStmtReturn ctx expr =
  let expr, ctx = genExpr ctx expr
  cirCtxAddStmt ctx (CReturnStmt(Some expr))

let genStmtJump ctx stmt =
  match stmt with
  | MStmt.Return (expr, _) -> genStmtReturn ctx expr
  | MStmt.Label (label, _) -> cirCtxAddStmt ctx (CLabelStmt label)
  | MStmt.Goto (label, _) -> cirCtxAddStmt ctx (CGotoStmt label)
  | MStmt.GotoIf (pred, label, _) ->
      let pred, ctx = genExpr ctx pred
      cirCtxAddStmt ctx (CGotoIfStmt(pred, label))
  | MStmt.Exit (arg, _) ->
      let doArm () =
        let arg, ctx = genExpr ctx arg
        cirCtxAddStmt ctx (CExprStmt(CCallExpr(CRefExpr "exit", [ arg ])))

      doArm ()
  | _ -> failwith "NEVER"

let genStmt ctx stmt =
  match stmt with
  | MStmt.Do (expr, _) -> genStmtDo ctx expr
  | MStmt.LetVal (serial, init, ty, loc) -> genStmtLetVal ctx serial init ty loc
  | MStmt.Set (serial, right, _) -> genStmtSet ctx serial right
  | MStmt.Return _
  | MStmt.Label _
  | MStmt.Goto _
  | MStmt.GotoIf _
  | MStmt.Exit _ -> genStmtJump ctx stmt
  | MStmt.Proc _ -> ctx

let genBlock (ctx: CirCtx) (stmts: MStmt list) =
  let bodyCtx = genStmts (cirCtxNewBlock ctx) stmts
  let stmts = bodyCtx |> cirCtxGetStmts
  let ctx = cirCtxRollBack ctx bodyCtx
  listRev stmts, ctx

let genStmts (ctx: CirCtx) (stmts: MStmt list): CirCtx =
  let rec go ctx stmts =
    match stmts with
    | [] -> ctx
    | stmt :: stmts ->
        let ctx = genStmt ctx stmt
        go ctx stmts

  go ctx stmts

let genDecls (ctx: CirCtx) decls =
  match decls with
  | [] -> ctx

  | MStmt.Proc (callee, isMainFun, args, body, resultTy, _) :: decls ->
      let ident, args =
        if isMainFun then "main", [] else cirCtxUniqueName ctx callee, args

      let rec go acc ctx args =
        match args with
        | [] -> listRev acc, ctx
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

let genLogs (ctx: CirCtx) =
  let rec go (ctx: CirCtx) logs =
    match logs with
    | [] -> ctx
    | (log, loc) :: logs ->
        let _, y, _ = loc
        let msg = log |> logToString loc

        let ctx =
          cirCtxAddDecl ctx (CErrorDecl(msg, 1 + y))

        go ctx logs

  let logs = ctx |> cirCtxGetLogs |> listRev
  let ctx = go ctx logs
  let success = logs |> listIsEmpty
  success, ctx

let gen (decls, mirCtx: MirCtx): CDecl list * bool =
  let ctx = cirCtxFromMirCtx mirCtx
  let ctx = genDecls ctx decls
  let success, ctx = genLogs ctx
  let decls = ctx |> cirCtxGetDecls |> listRev
  decls, success
