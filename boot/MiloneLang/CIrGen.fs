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

let tupleField i = sprintf "t%d" i

/// Calculates tag type's name of union type.
let tagTyIdent tyIdent =
  sprintf "%sTag" tyIdent

let calculateVarUniqueNames vars =
  let groups = vars |> mapToList |> Seq.groupBy (fun (_, varDef) -> varDefToIdent varDef)
  groups |> Seq.collect (fun (ident, vars) ->
    vars |> Seq.mapi (fun i (serial, _) ->
      let ident = if i = 0 then sprintf "%s_" ident else sprintf "%s_%d" ident i
      (serial, ident)
  ))
  |> Seq.toList
  |> mapOfList (intHash, intCmp)

let calculateTyUniqueNames tys =
  let groups = tys |> mapToList |> Seq.groupBy (fun (_, tyDef) -> tyDefToIdent tyDef)
  groups |> Seq.collect (fun (ident, tys) ->
    tys |> Seq.mapi (fun i (serial, _) ->
      let ident = if i = 0 then sprintf "%s_" ident else sprintf "%s_%d" ident i
      tyRef serial [], ident
  ))
  |> Seq.toList
  |> mapOfList (tyToHash, tyCmp)

let cirCtxFromMirCtx (mirCtx: MirCtx): CirCtx =
  let varNames = calculateVarUniqueNames (mirCtx |> mirCtxGetVars)
  let tyNames = calculateTyUniqueNames (mirCtx |> mirCtxGetTys)
  CirCtx (
    mirCtx |> mirCtxGetVars,
    varNames,
    mapEmpty (tyToHash, tyCmp),
    mirCtx |> mirCtxGetTys,
    tyNames,
    [],
    [],
    mirCtx |> mirCtxGetLogs
  )

let cirCtxAddErr (ctx: CirCtx) message loc =
  ctx |> cirCtxWithLogs ((Log.Error message, loc) :: (ctx |> cirCtxGetLogs))

let cirCtxNewBlock (ctx: CirCtx) =
  ctx |> cirCtxWithStmts []

let cirCtxRollBack (bCtx: CirCtx) (dCtx: CirCtx) =
  dCtx |> cirCtxWithStmts (bCtx |> cirCtxGetStmts)

let cirCtxAddStmt (ctx: CirCtx) stmt =
  ctx |> cirCtxWithStmts (stmt :: (ctx |> cirCtxGetStmts))

let cirCtxAddDecl (ctx: CirCtx) decl =
  ctx |> cirCtxWithDecls (decl :: (ctx |> cirCtxGetDecls))

let cirCtxAddFunIncomplete (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind funTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let ident, ctx = cirCtxUniqueTyName ctx funTy
    let funStructTy = CTy.Struct ident
    let ctx = ctx |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd funTy (TyInstance.Declared, funStructTy))
    funStructTy, ctx

let cirCtxAddFunDecl (ctx: CirCtx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind funTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let ident, ctx = cirCtxUniqueTyName ctx funTy
    let selfTy, ctx = cirCtxAddFunIncomplete ctx sTy tTy

    let envTy = CTy.Ptr CTy.Void
    let _, argTys, resultTy = tyToArgList funTy

    let argTys, ctx = (argTys, ctx) |> stMap (fun (ty, ctx) -> cirCtxConvertTyIncomplete ctx ty)
    let resultTy, ctx = cirGetCTy ctx resultTy

    let fields =
      [
        "fun", CTy.FunPtr (envTy :: argTys, resultTy)
        "env", envTy
      ]
    let ctx =
      ctx
      |> cirCtxWithDecls (CDecl.Struct (ident, fields, []) :: (ctx |> cirCtxGetDecls))
      |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd funTy (TyInstance.Defined, selfTy))
    selfTy, ctx

let cirCtxAddListIncomplete (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind listTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let ident, ctx = cirCtxUniqueTyName ctx listTy
    let selfTy = CTy.Ptr (CTy.Struct ident)
    let ctx = ctx |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd listTy (TyInstance.Declared, selfTy))
    selfTy, ctx

let cirCtxAddListDecl (ctx: CirCtx) itemTy =
  let listTy = tyList itemTy
  match ctx |> cirCtxGetTyEnv |> mapTryFind listTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let ident, ctx = cirCtxUniqueTyName ctx listTy
    let selfTy, ctx = cirCtxAddListIncomplete ctx itemTy

    let itemTy, ctx = cirGetCTy ctx itemTy
    let fields =
      [
        "head", itemTy
        "tail", selfTy
      ]
    let ctx: CirCtx =
      ctx
      |> cirCtxWithDecls (CDecl.Struct (ident, fields, []) :: (ctx |> cirCtxGetDecls))
      |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd listTy (TyInstance.Defined, selfTy))
    selfTy, ctx

let cirCtxAddTupleIncomplete (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx |> cirCtxGetTyEnv |> mapTryFind tupleTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let tupleTyIdent, ctx = cirCtxUniqueTyName ctx tupleTy
    let selfTy = CTy.Struct tupleTyIdent
    let ctx = ctx |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd tupleTy (TyInstance.Declared, selfTy))
    selfTy, ctx

let cirCtxAddTupleDecl (ctx: CirCtx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx |> cirCtxGetTyEnv |> mapTryFind tupleTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let tupleTyIdent, ctx = cirCtxUniqueTyName ctx tupleTy
    let selfTy, ctx = cirCtxAddTupleIncomplete ctx itemTys

    let rec go i itemTys =
      match itemTys with
      | [] ->
        []

      | itemTy :: itemTys ->
        let field = tupleField i, itemTy
        field :: go (i + 1) itemTys

    let itemTys, ctx = cirCtxGetCTys (itemTys, ctx)
    let fields = go 0 itemTys

    let tupleDecl = CDecl.Struct (tupleTyIdent, fields, [])
    let ctx: CirCtx =
      ctx
      |> cirCtxWithDecls (tupleDecl :: (ctx |> cirCtxGetDecls))
      |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd tupleTy (TyInstance.Defined, selfTy))
    selfTy, ctx

let cirCtxAddUnionIncomplete (ctx: CirCtx) tySerial =
  let unionTyRef = tyRef tySerial []
  match ctx |> cirCtxGetTyEnv |> mapTryFind unionTyRef with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
    let selfTy = CTy.Struct unionTyIdent
    let ctx = ctx |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd unionTyRef (TyInstance.Declared, selfTy))
    selfTy, ctx

let cirCtxAddUnionDecl (ctx: CirCtx) tySerial variants =
  let unionTyRef = tyRef tySerial []
  match ctx |> cirCtxGetTyEnv |> mapTryFind unionTyRef with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let unionTyIdent, ctx = cirCtxUniqueTyName ctx unionTyRef
    let selfTy, ctx = cirCtxAddUnionIncomplete ctx tySerial

    let tagTyIdent = tagTyIdent unionTyIdent
    let tagTy = CTy.Enum tagTyIdent

    let variants =
      variants |> listMap (fun variantSerial ->
        match ctx |> cirCtxGetVars |> mapTryFind variantSerial with
        | Some (VarDef.Variant (ident, _, hasPayload, payloadTy, _, _)) ->
          ident, variantSerial, hasPayload, payloadTy
        | _ -> failwith "Never"
      )
    let tags =
      variants |> listMap (fun (_, serial, _, _) ->
        cirCtxUniqueName ctx serial)
    let variants, ctx =
      (variants, ctx) |> stFlatMap (fun ((_, serial, hasPayload, payloadTy), acc, ctx) ->
        if hasPayload then
          let payloadTy, ctx = cirCtxConvertTyIncomplete ctx payloadTy
          (cirCtxUniqueName ctx serial, CTy.Ptr payloadTy) :: acc, ctx
        else
          acc, ctx
      )

    let tagEnumDecl = CDecl.Enum (tagTyIdent, tags)
    let structDecl = CDecl.Struct (unionTyIdent, ["tag", tagTy], variants)
    let ctx =
      ctx
      |> cirCtxWithDecls (structDecl :: tagEnumDecl :: (ctx |> cirCtxGetDecls))
      |> cirCtxWithTyEnv (ctx |> cirCtxGetTyEnv |> mapAdd unionTyRef (TyInstance.Defined, selfTy))
    selfTy, ctx

let cirCtxUniqueName (ctx: CirCtx) serial =
  match ctx |> cirCtxGetVarUniqueNames |> mapTryFind serial with
  | Some ident ->
    ident
  | None ->
    failwithf "Never: Unknown value-level identifier serial %d" serial

let cirCtxUniqueTyName (ctx: CirCtx) ty =
  let rec go ty (ctx: CirCtx) =
    match ctx |> cirCtxGetTyUniqueNames |> mapTryFind ty with
    | Some ident ->
      ident, ctx
    | None ->
      let ident, ctx =
        match ty with
        | Ty.Con (TyCon.Bool, _) -> "Bool", ctx
        | Ty.Con (TyCon.Int, _) -> "Int", ctx
        | Ty.Con (TyCon.Char, _) -> "Char", ctx
        | Ty.Con (TyCon.Str, _) -> "String", ctx
        | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
        | Ty.Con (TyCon.Obj, _) -> "Object", ctx
        | Ty.Con (TyCon.Fun, _) ->
          let arity, argTys, resultTy = tyToArgList ty
          let argTys, ctx = (argTys, ctx) |> stMap (fun (argTy, ctx) -> ctx |> go argTy)
          let resultTy, ctx = ctx |> go resultTy
          sprintf "%s%sFun%d" (argTys |> String.concat "") resultTy arity, ctx
        | Ty.Con (TyCon.List, [itemTy]) ->
          let itemTy, ctx = ctx |> go itemTy
          sprintf "%sList" itemTy, ctx
        | Ty.Con (TyCon.Tuple, []) ->
          "Unit", ctx
        | Ty.Con (TyCon.Tuple, itemTys) ->
          let len = itemTys |> listLength
          let itemTys, ctx = (itemTys, ctx) |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)
          sprintf "%s%s%d" (itemTys |> String.concat "") "Tuple" len, ctx
        | Ty.Con (TyCon.Ref serial, _) ->
          // FIXME: This occurs when recursive union types defined.
          failwithf "Never: Unknown type serial %d" serial
        | Ty.Con (TyCon.List, _)
        | Ty.Con (TyCon.Fun, _)
        | Ty.Error _ ->
          eprintfn "NEVER error type %A" ty
          sprintf "/* unknown ty %A */" ty, ctx
      let ctx = ctx |> cirCtxWithTyUniqueNames (ctx |> cirCtxGetTyUniqueNames |> mapAdd ty ident)
      ident, ctx
  go ty ctx

let cirCtxConvertTyIncomplete (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _)
  | Ty.Con (TyCon.Tuple, []) ->
    CTy.Int, ctx

  | Ty.Con (TyCon.Char, _) ->
    CTy.Char, ctx

  | Ty.Con (TyCon.Str, _) ->
    CTy.Struct "String", ctx

  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Obj, _) ->
    CTy.Ptr CTy.Void, ctx

  | Ty.Con (TyCon.Fun, [sTy; tTy]) ->
    cirCtxAddFunIncomplete ctx sTy tTy

  | Ty.Con (TyCon.List, [itemTy]) ->
    cirCtxAddListIncomplete ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) ->
    cirCtxAddTupleIncomplete ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
    match ctx |> cirCtxGetTys |> mapTryFind serial with
    | Some (TyDef.Union _) ->
      cirCtxAddUnionIncomplete ctx serial

    | _ ->
      CTy.Void, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ ->
    CTy.Void, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let cirGetCTy (ctx: CirCtx) (ty: Ty): CTy * CirCtx =
  match ty with
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _)
  | Ty.Con (TyCon.Tuple, []) ->
    CTy.Int, ctx

  | Ty.Con (TyCon.Char, _) ->
    CTy.Char, ctx

  | Ty.Con (TyCon.Str, _) ->
    CTy.Struct "String", ctx

  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Obj, _) ->
    CTy.Ptr CTy.Void, ctx

  | Ty.Con (TyCon.Fun, [sTy; tTy]) ->
    cirCtxAddFunDecl ctx sTy tTy

  | Ty.Con (TyCon.List, [itemTy]) ->
    cirCtxAddListDecl ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) ->
    cirCtxAddTupleDecl ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
    match ctx |> cirCtxGetTys |> mapTryFind serial with
    | Some (TyDef.Union (_, variants, _)) ->
      cirCtxAddUnionDecl ctx serial variants

    | _ ->
      CTy.Void, cirCtxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  |  _ ->
    CTy.Void, cirCtxAddErr ctx "error type" noLoc // FIXME: source location

let cirCtxGetCTys (tys, ctx) =
  stMap (fun (ty, ctx) -> cirGetCTy ctx ty) (tys, ctx)

let cOpFrom op =
  match op with
  | MOp.Mul -> CBinOp.Mul
  | MOp.Div -> CBinOp.Div
  | MOp.Mod -> CBinOp.Mod
  | MOp.Add -> CBinOp.Add
  | MOp.Sub -> CBinOp.Sub
  | MOp.Eq -> CBinOp.Eq
  | MOp.Ne -> CBinOp.Ne
  | MOp.Lt -> CBinOp.Lt
  | MOp.Ge -> CBinOp.Ge
  | MOp.StrAdd
  | MOp.StrCmp
  | MOp.StrIndex -> failwith "Never"

/// `0`, `NULL`, or `(T) {}`
let genExprDefault ctx ty =
  match ty with
  | Ty.Con (TyCon.Tuple, [])
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _) ->
    CExpr.Int 0, ctx
  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Char, _)
  | Ty.Con (TyCon.Obj, _)
  | Ty.Con (TyCon.List, _) ->
    CExpr.Ref "NULL", ctx
  | Ty.Con (TyCon.Str, _)
  | Ty.Con (TyCon.Fun, _)
  | Ty.Con (TyCon.Tuple, _)
  | Ty.Con (TyCon.Ref _, _) ->
    let ty, ctx = cirGetCTy ctx ty
    CExpr.Cast (CExpr.Default, ty), ctx
  | Ty.Error _ ->
    failwithf "Never %A" ty

let genExprProc ctx serial _ty _loc =
  let ident = cirCtxUniqueName ctx serial
  CExpr.Ref ident, ctx

let genExprVariant ctx serial ty =
  let ty, ctx = cirGetCTy ctx ty
  let tag = CExpr.Ref (cirCtxUniqueName ctx serial)
  CExpr.Init (["tag", tag], ty), ctx

let genExprBinAsCall ctx ident l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let callExpr = CExpr.Call (CExpr.Ref ident, [l; r])
  callExpr, ctx

let genExprUniOp ctx op arg ty _ =
  let arg, ctx = genExpr ctx arg
  match op with
  | MUniOp.Not ->
    CExpr.Uni (CUniOp.Not, arg), ctx
  | MUniOp.StrPtr ->
    CExpr.Nav (arg, "str"), ctx
  | MUniOp.StrLen ->
    CExpr.Nav (arg, "len"), ctx
  | MUniOp.Unbox ->
    let valTy, ctx = cirGetCTy ctx ty
    let deref = CExpr.Uni (CUniOp.Deref, CExpr.Cast (arg, CTy.Ptr valTy))
    deref, ctx
  | MUniOp.Proj index ->
    CExpr.Proj (arg, index), ctx
  | MUniOp.Tag ->
    CExpr.Nav (arg, "tag"), ctx
  | MUniOp.GetVariant serial ->
    let _, ctx = cirGetCTy ctx ty
    CExpr.Uni (CUniOp.Deref, CExpr.Nav (arg, cirCtxUniqueName ctx serial)), ctx
  | MUniOp.ListIsEmpty ->
    CExpr.Uni (CUniOp.Not, arg), ctx
  | MUniOp.ListHead ->
    CExpr.Arrow (arg, "head"), ctx
  | MUniOp.ListTail ->
    CExpr.Arrow (arg, "tail"), ctx

let genExprBin ctx op l r =
  match op with
  | MOp.StrAdd ->
    genExprBinAsCall ctx "str_add" l r
  | MOp.StrCmp ->
    genExprBinAsCall ctx "str_cmp" l r
  | MOp.StrIndex ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    CExpr.Index (CExpr.Nav (l, "str"), r), ctx
  | _ ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    let opExpr = CExpr.Bin (cOpFrom op, l, r)
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
  | MExpr.Lit (Lit.Int value, _) ->
    CExpr.Int value, ctx
  | MExpr.Lit (Lit.Char value, _) ->
    CExpr.Char value, ctx
  | MExpr.Lit (Lit.Str value, _) ->
    CExpr.StrObj value, ctx
  | MExpr.Lit (Lit.Bool false, _) ->
    CExpr.Int 0, ctx
  | MExpr.Lit (Lit.Bool true, _) ->
    CExpr.Int 1, ctx
  | MExpr.Default (ty, _) ->
    genExprDefault ctx ty
  | MExpr.Ref (serial, _, _) ->
    CExpr.Ref (cirCtxUniqueName ctx serial), ctx
  | MExpr.Proc (serial, ty, loc) ->
    genExprProc ctx serial ty loc
  | MExpr.Variant (_, serial, ty, _) ->
    genExprVariant ctx serial ty
  | MExpr.Uni (op, arg, ty, loc) ->
    genExprUniOp ctx op arg ty loc
  | MExpr.Bin (op, l, r, _, _) ->
    genExprBin ctx op l r

let genExprCallPrintfn ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] ->
      listRev acc, ctx
    | MExpr.Lit (Lit.Str value, _) :: args ->
      go (CExpr.StrRaw value :: acc) ctx args
    | arg :: args when mexprToTy arg = tyStr ->
      let arg, ctx = genExpr ctx arg
      let acc = CExpr.Nav (arg, "str") :: acc
      go acc ctx args
    | arg :: args ->
      let arg, ctx = genExpr ctx arg
      go (arg :: acc) ctx args

  let args, ctx = go [] ctx args
  let format = CExpr.StrRaw (format + "\n")
  let expr = CStmt.Expr (CExpr.Call (CExpr.Ref "printf", format :: args))
  let ctx = cirCtxAddStmt ctx expr
  genExprDefault ctx tyUnit

let genExprCallInt arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | Ty.Con (TyCon.Int, _) ->
    arg, ctx
  | Ty.Con (TyCon.Char,_) ->
    CExpr.Cast (arg, CTy.Int), ctx
  | Ty.Con (TyCon.Str, _) ->
    CExpr.Call (CExpr.Ref "str_to_int", [arg]), ctx
  | _ ->
    failwith "Never: Type Error `int`"

let genExprCallString arg argTy ctx =
  let arg, ctx = genExpr ctx arg
  match argTy with
  | Ty.Con (TyCon.Int, _) ->
    CExpr.Call (CExpr.Ref "str_of_int", [arg]), ctx
  | Ty.Con (TyCon.Char, _) ->
    CExpr.Call (CExpr.Ref "str_of_char", [arg]), ctx
  | Ty.Con (TyCon.Str, _) ->
    arg, ctx
  | _ ->
    failwith "Never: Type Error `int`"

let genExprCallPrim ctx prim args primTy resultTy loc =
  match prim, args, primTy with
  | HPrim.NativeFun (nativeFunIdent, _), _, _ ->
    let args, ctx = genExprList ctx args
    CExpr.Call (CExpr.Ref nativeFunIdent, args), ctx

  | HPrim.Printfn, (MExpr.Lit (Lit.Str format, _)) :: args, _ ->
    genExprCallPrintfn ctx format args

  | HPrim.Assert, _, _ ->
    let callee = CExpr.Ref "milone_assert"
    let args, ctx = genExprList ctx args
    // Embed the source location information.
    let args =
      let y, x = loc
      listAppend args [CExpr.Int y; CExpr.Int x]
    let assertCall = CExpr.Call (callee, args)
    let ctx = cirCtxAddStmt ctx (CStmt.Expr assertCall)
    genExprDefault ctx resultTy

  | HPrim.StrGetSlice, _, _ ->
    let callee = CExpr.Ref "str_get_slice"
    let args, ctx = genExprList ctx args
    CExpr.Call (callee, args), ctx

  | HPrim.Char, [arg], _ ->
    let arg, ctx = genExpr ctx arg
    CExpr.Cast (arg, CTy.Char), ctx

  | HPrim.Int, [arg], Ty.Con (TyCon.Fun, [argTy; _]) ->
    genExprCallInt arg argTy ctx

  | HPrim.String, [arg], Ty.Con (TyCon.Fun, [argTy; _]) ->
    genExprCallString arg argTy ctx

  | _ ->
    failwithf "Invalid call to primitive %A" (prim, args, primTy, resultTy)

let genExprCallProc ctx callee args ty =
  match callee, args with
  | _ ->
    let callee, ctx = genExpr ctx callee
    let args, ctx = genExprList ctx args
    CExpr.Call (callee, args), ctx

let genExprCallClosure ctx callee args =
  let callee, ctx = genExpr ctx callee
  let args, ctx = genExprList ctx args
  let funPtr = CExpr.Nav (callee, "fun")
  let envArg = CExpr.Nav (callee, "env")
  CExpr.Call (funPtr, envArg :: args), ctx

let genInitExprCore ctx serial expr ty =
  let ident = cirCtxUniqueName ctx serial
  let cty, ctx = cirGetCTy ctx ty
  cirCtxAddStmt ctx (CStmt.Let (ident, expr, cty))

let genInitClosure ctx serial funSerial envSerial ty =
  let ident = cirCtxUniqueName ctx serial
  let ty, ctx = cirGetCTy ctx ty
  let fields =
    [
      "fun", CExpr.Ref (cirCtxUniqueName ctx funSerial)
      "env", CExpr.Ref (cirCtxUniqueName ctx envSerial)
    ]
  let initExpr = CExpr.Init (fields, ty)
  cirCtxAddStmt ctx (CStmt.Let (ident, Some initExpr, ty))

let genInitBox ctx serial arg =
  let argTy, ctx = cirGetCTy ctx (mexprToTy arg)
  let arg, ctx = genExpr ctx arg

  // void* p = (void*)malloc(sizeof T);
  let temp = cirCtxUniqueName ctx serial
  let ctx = cirCtxAddStmt ctx (CStmt.LetAlloc (temp, CTy.Ptr argTy, CTy.Ptr CTy.Void))

  // *(T*)p = t;
  let left = CExpr.Uni (CUniOp.Deref, CExpr.Cast (CExpr.Ref temp, CTy.Ptr argTy))
  let ctx = cirCtxAddStmt ctx (CStmt.Set (left, arg))

  ctx

let genInitIndirect ctx serial payload ty =
  let varName = cirCtxUniqueName ctx serial
  let payloadTy, ctx = cirGetCTy ctx ty
  let ptrTy = CTy.Ptr payloadTy

  let payload, ctx = genExpr ctx payload

  // T* p = (T*)malloc(sizeof T);
  let ctx = cirCtxAddStmt ctx (CStmt.LetAlloc (varName, ptrTy, ptrTy))

  // *(T*)p = t;
  let left = CExpr.Uni (CUniOp.Deref, CExpr.Cast (CExpr.Ref varName, ptrTy))
  let ctx = cirCtxAddStmt ctx (CStmt.Set (left, payload))

  ctx

let genInitCons ctx serial head tail listTy =
  let temp = cirCtxUniqueName ctx serial
  let listTy, ctx = cirGetCTy ctx listTy
  let ctx = cirCtxAddStmt ctx (CStmt.LetAlloc (temp, listTy, listTy))

  // head
  let head, ctx = genExpr ctx head
  let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "head"), head)
  let ctx = cirCtxAddStmt ctx stmt

  // tail
  let tail, ctx = genExpr ctx tail
  let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "tail"), tail)
  let ctx = cirCtxAddStmt ctx stmt

  ctx

let genInitTuple ctx serial items tupleTy =
  let ident = cirCtxUniqueName ctx serial
  let tupleTy, ctx = cirGetCTy ctx tupleTy
  let ctx = cirCtxAddStmt ctx (CStmt.Let (ident, None, tupleTy))
  let rec go ctx i items =
    match items with
    | [] ->
      ctx
    | item :: items ->
      let left = CExpr.Nav (CExpr.Ref ident, tupleField i)
      let item, ctx = genExpr ctx item
      let stmt = CStmt.Set (left, item)
      let ctx = cirCtxAddStmt ctx stmt
      go ctx (i + 1) items
  go ctx 0 items

let genInitVariant ctx varSerial variantSerial payloadSerial unionTy =
  let temp = cirCtxUniqueName ctx varSerial
  let unionTy, ctx = cirGetCTy ctx unionTy
  let variantName = cirCtxUniqueName ctx variantSerial
  let payloadExpr = CExpr.Ref (cirCtxUniqueName ctx payloadSerial)
  let fields =
    [
      "tag", CExpr.Ref (cirCtxUniqueName ctx variantSerial)
      variantName, payloadExpr
    ]
  let init = CExpr.Init (fields, unionTy)
  let ctx = cirCtxAddStmt ctx (CStmt.Let (temp, Some init, unionTy))
  ctx

let genStmtLetVal ctx serial init ty loc =
  match init with
  | MInit.UnInit ->
    genInitExprCore ctx serial None ty
  | MInit.Expr expr ->
    let expr, ctx = genExpr ctx expr
    genInitExprCore ctx serial (Some expr) ty
  | MInit.CallPrim (prim, args, calleeTy) ->
    let expr, ctx = genExprCallPrim ctx prim args calleeTy ty loc
    genInitExprCore ctx serial (Some expr) ty
  | MInit.CallProc (callee, args, _) ->
    let expr, ctx = genExprCallProc ctx callee args ty
    genInitExprCore ctx serial (Some expr) ty
  | MInit.CallClosure (callee, args) ->
    let expr, ctx = genExprCallClosure ctx callee args
    genInitExprCore ctx serial (Some expr) ty
  | MInit.Closure (funSerial, envSerial) ->
    genInitClosure ctx serial funSerial envSerial ty
  | MInit.Box arg ->
    genInitBox ctx serial arg
  | MInit.Indirect payload ->
    genInitIndirect ctx serial payload ty
  | MInit.Cons (head, tail) ->
    genInitCons ctx serial head tail ty
  | MInit.Tuple items ->
    genInitTuple ctx serial items ty
  | MInit.Variant (variantSerial, payloadSerial) ->
    genInitVariant ctx serial variantSerial payloadSerial ty

let genStmtDo ctx expr =
  let expr, ctx = genExpr ctx expr
  cirCtxAddStmt ctx (CStmt.Expr expr)

let genStmtSet ctx serial right =
  let right, ctx = genExpr ctx right
  let ident = cirCtxUniqueName ctx serial
  let left = CExpr.Ref (ident)
  cirCtxAddStmt ctx (CStmt.Set (left, right))

let genStmtReturn ctx expr =
  let expr, ctx = genExpr ctx expr
  cirCtxAddStmt ctx (CStmt.Return (Some expr))

let genStmt ctx stmt =
  match stmt with
  | MStmt.Do (expr, _) ->
    genStmtDo ctx expr
  | MStmt.LetVal (serial, init, ty, loc) ->
    genStmtLetVal ctx serial init ty loc
  | MStmt.Set (serial, right, _) ->
    genStmtSet ctx serial right
  | MStmt.Return (expr, _) ->
    genStmtReturn ctx expr
  | MStmt.Label (label, _) ->
    cirCtxAddStmt ctx (CStmt.Label label)
  | MStmt.Goto (label, _) ->
    cirCtxAddStmt ctx (CStmt.Goto label)
  | MStmt.GotoIf (pred, label, _) ->
    let pred, ctx = genExpr ctx pred
    cirCtxAddStmt ctx (CStmt.GotoIf (pred, label))
  | MStmt.Exit (arg, _) ->
    let arg, ctx = genExpr ctx arg
    cirCtxAddStmt ctx (CStmt.Expr (CExpr.Call (CExpr.Ref "exit", [arg])))
  | MStmt.Proc _ ->
    ctx

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
  | [] ->
    ctx

  | MStmt.Proc (callee, isMainFun, args, body, resultTy, _) :: decls ->
    let ident, args =
      if isMainFun
      then "main", []
      else cirCtxUniqueName ctx callee, args
    let rec go acc ctx args =
      match args with
      | [] ->
        listRev acc, ctx
      | (arg, ty, _) :: args ->
        let ident = cirCtxUniqueName ctx arg
        let cty, ctx = cirGetCTy ctx ty
        go ((ident, cty) :: acc) ctx args
    let args, ctx = go [] ctx args
    let body, ctx = genBlock ctx body
    let resultTy, ctx = cirGetCTy ctx resultTy
    let funDecl = CDecl.Fun (ident, args, resultTy, body)
    let ctx = cirCtxAddDecl ctx funDecl
    genDecls ctx decls

  | _ ->
    failwith "Top-level statements must be declarations."

let genLogs (ctx: CirCtx) =
  let rec go (ctx: CirCtx) logs =
    match logs with
    | [] ->
      ctx
    | (log, loc) :: logs ->
      let y, _ = loc
      let msg = log |> logToString loc
      let ctx = cirCtxAddDecl ctx (CDecl.ErrDir (msg, 1 + y))
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
