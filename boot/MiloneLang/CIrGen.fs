/// Converts MIR to CIR.
///
/// CIR is a kind of abstract syntax tree of C.
///
/// Maps operations/primitives/types to C operations/functions/types.
/// Generates type declarations for lists/tuples/etc.
module rec MiloneLang.CIrGen

open MiloneLang.Types
open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type TyInstance =
  | Declared
  | Defined

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    Vars: Map<VarSerial, VarDef>
    VarUniqueNames: Map<VarSerial, Ident>
    TyEnv: Map<Ty, TyInstance * CTy>
    Tys: Map<TySerial, TyDef>
    TyUniqueNames: Map<Ty, Ident>
    Stmts: CStmt list
    Decls: CDecl list
    Logs: (Log * Loc) list
  }

let tupleField i = sprintf "t%d" i

/// Calculates tag type's name of union type.
let tagTyIdent tyIdent =
  sprintf "%sTag" tyIdent

let calculateVarUniqueNames vars =
  let groups = vars |> Map.toList |> Seq.groupBy (fun (_, varDef) -> varDefToIdent varDef)
  groups |> Seq.collect (fun (ident, vars) ->
    vars |> Seq.mapi (fun i (serial, _) ->
      let ident = if i = 0 then sprintf "%s_" ident else sprintf "%s_%d" ident i
      (serial, ident)
  ))
  |> Map.ofSeq

let calculateTyUniqueNames tys =
  let groups = tys |> Map.toList |> Seq.groupBy (fun (_, tyDef) -> tyDefToIdent tyDef)
  groups |> Seq.collect (fun (ident, tys) ->
    tys |> Seq.mapi (fun i (serial, _) ->
      let ident = if i = 0 then sprintf "%s_" ident else sprintf "%s_%d" ident i
      tyRef serial [], ident
  ))
  |> Map.ofSeq

let ctxFromMirCtx (mirCtx: Mir.MirCtx): Ctx =
  let varNames = calculateVarUniqueNames mirCtx.Vars
  let tyNames = calculateTyUniqueNames mirCtx.Tys
  {
    Vars = mirCtx.Vars
    VarUniqueNames = varNames
    TyEnv = Map.empty
    Tys = mirCtx.Tys
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []
    Logs = mirCtx.Logs
  }

let ctxAddErr (ctx: Ctx) message loc =
  { ctx with Logs = (Log.Error message, loc) :: ctx.Logs }

let ctxNewBlock (ctx: Ctx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: Ctx) (dCtx: Ctx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddStmt (ctx: Ctx) stmt =
  { ctx with Stmts = stmt :: ctx.Stmts }

let ctxAddDecl (ctx: Ctx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddFunIncomplete (ctx: Ctx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> Map.tryFind funTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let ident, ctx = ctxUniqueTyName ctx funTy
    let funStructTy = CTy.Struct ident
    let ctx: Ctx =
      { ctx with
          TyEnv = ctx.TyEnv |> Map.add funTy (TyInstance.Declared, funStructTy)
      }
    funStructTy, ctx

let ctxAddFunDecl (ctx: Ctx) sTy tTy =
  let funTy = tyFun sTy tTy
  match ctx.TyEnv |> Map.tryFind funTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let ident, ctx = ctxUniqueTyName ctx funTy
    let selfTy, ctx = ctxAddFunIncomplete ctx sTy tTy

    let envTy = CTy.Ptr CTy.Void
    let _, argTys, resultTy = tyToArgList funTy

    let argTys, ctx = (argTys, ctx) |> stMap (fun (ty, ctx) -> ctxConvertTyIncomplete ctx ty)
    let resultTy, ctx = cty ctx resultTy

    let fields =
      [
        "fun", CTy.FunPtr (envTy :: argTys, resultTy)
        "env", envTy
      ]
    let ctx =
      { ctx with
          Decls = CDecl.Struct (ident, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> Map.add funTy (TyInstance.Defined, selfTy)
      }
    selfTy, ctx

let ctxAddListIncomplete (ctx: Ctx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> Map.tryFind listTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let ident, ctx = ctxUniqueTyName ctx listTy
    let selfTy = CTy.Ptr (CTy.Struct ident)
    let ctx = { ctx with TyEnv = ctx.TyEnv |> Map.add listTy (TyInstance.Declared, selfTy) }
    selfTy, ctx

let ctxAddListDecl (ctx: Ctx) itemTy =
  let listTy = tyList itemTy
  match ctx.TyEnv |> Map.tryFind listTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let ident, ctx = ctxUniqueTyName ctx listTy
    let selfTy, ctx = ctxAddListIncomplete ctx itemTy

    let itemTy, ctx = cty ctx itemTy
    let fields =
      [
        "head", itemTy
        "tail", selfTy
      ]
    let ctx: Ctx =
      { ctx with
          Decls = CDecl.Struct (ident, fields, []) :: ctx.Decls
          TyEnv = ctx.TyEnv |> Map.add listTy (TyInstance.Defined, selfTy)
      }
    selfTy, ctx

let ctxAddTupleIncomplete (ctx: Ctx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> Map.tryFind tupleTy with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let tupleTyIdent, ctx = ctxUniqueTyName ctx tupleTy
    let selfTy = CTy.Struct tupleTyIdent
    let ctx = { ctx with TyEnv = ctx.TyEnv |> Map.add tupleTy (TyInstance.Declared, selfTy) }
    selfTy, ctx

let ctxAddTupleDecl (ctx: Ctx) itemTys =
  let tupleTy = tyTuple itemTys
  match ctx.TyEnv |> Map.tryFind tupleTy with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let tupleTyIdent, ctx = ctxUniqueTyName ctx tupleTy
    let selfTy, ctx = ctxAddTupleIncomplete ctx itemTys

    let rec go i itemTys =
      match itemTys with
      | [] ->
        []

      | itemTy :: itemTys ->
        let field = tupleField i, itemTy
        field :: go (i + 1) itemTys

    let itemTys, ctx = cirifyTys (itemTys, ctx)
    let fields = go 0 itemTys

    let tupleDecl = CDecl.Struct (tupleTyIdent, fields, [])
    let ctx: Ctx =
      { ctx with
          Decls = tupleDecl :: ctx.Decls
          TyEnv = ctx.TyEnv |> Map.add tupleTy (TyInstance.Defined, selfTy)
      }
    selfTy, ctx

let ctxAddUnionIncomplete (ctx: Ctx) tySerial =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> Map.tryFind unionTyRef with
  | Some (_, ty) ->
    ty, ctx

  | None ->
    let unionTyIdent, ctx = ctxUniqueTyName ctx unionTyRef
    let selfTy = CTy.Struct unionTyIdent
    let ctx = { ctx with TyEnv = ctx.TyEnv |> Map.add unionTyRef (TyInstance.Declared, selfTy) }
    selfTy, ctx

let ctxAddUnionDecl (ctx: Ctx) tySerial variants =
  let unionTyRef = tyRef tySerial []
  match ctx.TyEnv |> Map.tryFind unionTyRef with
  | Some (TyInstance.Defined, ty) ->
    ty, ctx

  | _ ->
    let unionTyIdent, ctx = ctxUniqueTyName ctx unionTyRef
    let selfTy, ctx = ctxAddUnionIncomplete ctx tySerial

    let tagTyIdent = tagTyIdent unionTyIdent
    let tagTy = CTy.Enum tagTyIdent

    let variants =
      variants |> List.map (fun variantSerial ->
        match ctx.Vars |> Map.tryFind variantSerial with
        | Some (VarDef.Variant (ident, _, hasPayload, payloadTy, _, _)) ->
          ident, variantSerial, hasPayload, payloadTy
        | _ -> failwith "Never"
      )
    let tags =
      variants |> List.map (fun (_, serial, _, _) ->
        ctxUniqueName ctx serial)
    let variants, ctx =
      (variants, ctx) |> stFlatMap (fun ((_, serial, hasPayload, payloadTy), acc, ctx) ->
        if hasPayload then
          let payloadTy, ctx = ctxConvertTyIncomplete ctx payloadTy
          (ctxUniqueName ctx serial, CTy.Ptr payloadTy) :: acc, ctx
        else
          acc, ctx
      )

    let tagEnumDecl = CDecl.Enum (tagTyIdent, tags)
    let structDecl = CDecl.Struct (unionTyIdent, ["tag", tagTy], variants)
    let ctx =
      { ctx with
          Decls = structDecl :: tagEnumDecl :: ctx.Decls
          TyEnv = ctx.TyEnv |> Map.add unionTyRef (TyInstance.Defined, selfTy)
      }
    selfTy, ctx

let ctxUniqueName (ctx: Ctx) serial =
  match ctx.VarUniqueNames |> Map.tryFind serial with
  | Some ident ->
    ident
  | None ->
    failwithf "Never: Unknown value-level identifier serial %d" serial

let ctxUniqueTyName (ctx: Ctx) ty =
  let rec go ty (ctx: Ctx) =
    match ctx.TyUniqueNames |> Map.tryFind ty with
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
          let len = itemTys |> List.length
          let itemTys, ctx = (itemTys, ctx) |> stMap (fun (itemTy, ctx) -> ctx |> go itemTy)
          sprintf "%s%s%d" (itemTys |> String.concat "") "Tuple" len, ctx
        | Ty.Con (TyCon.Ref serial, _) ->
          // FIXME: This occurs when recursive union types defined.
          failwithf "Never: Unknown type serial %d" serial
        | Ty.Con (TyCon.List, _)
        | Ty.Con (TyCon.Fun, _)
        | Ty.Error _ ->
          failwithf "Never %A" ty
      let ctx = { ctx with TyUniqueNames = ctx.TyUniqueNames |> Map.add ty ident }
      ident, ctx
  go ty ctx

let ctxConvertTyIncomplete (ctx: Ctx) (ty: Ty): CTy * Ctx =
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
    ctxAddFunIncomplete ctx sTy tTy

  | Ty.Con (TyCon.List, [itemTy]) ->
    ctxAddListIncomplete ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) ->
    ctxAddTupleIncomplete ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
    match ctx.Tys |> Map.tryFind serial with
    | Some (TyDef.Union _) ->
      ctxAddUnionIncomplete ctx serial

    | _ ->
      CTy.Void, ctxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  | _ ->
    CTy.Void, ctxAddErr ctx "error type" noLoc // FIXME: source location

let cty (ctx: Ctx) (ty: Ty): CTy * Ctx =
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
    ctxAddFunDecl ctx sTy tTy

  | Ty.Con (TyCon.List, [itemTy]) ->
    ctxAddListDecl ctx itemTy

  | Ty.Con (TyCon.Tuple, itemTys) ->
    ctxAddTupleDecl ctx itemTys

  | Ty.Con (TyCon.Ref serial, _) ->
    match ctx.Tys |> Map.tryFind serial with
    | Some (TyDef.Union (_, variants, _)) ->
      ctxAddUnionDecl ctx serial variants

    | _ ->
      CTy.Void, ctxAddErr ctx "Unknown type reference" noLoc // FIXME: source location

  |  _ ->
    CTy.Void, ctxAddErr ctx "error type" noLoc // FIXME: source location

let cirifyTys (tys, ctx) =
  stMap (fun (ty, ctx) -> cty ctx ty) (tys, ctx)

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
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Default, ty), ctx
  | Ty.Error _ ->
    failwithf "Never %A" ty

let genExprProc ctx serial _ty _loc =
  let ident = ctxUniqueName ctx serial
  CExpr.Ref ident, ctx

let genExprVariant ctx serial ty =
  let ty, ctx = cty ctx ty
  let tag = CExpr.Ref (ctxUniqueName ctx serial)
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
    let valTy, ctx = cty ctx ty
    let deref = CExpr.Uni (CUniOp.Deref, CExpr.Cast (arg, CTy.Ptr valTy))
    deref, ctx
  | MUniOp.Proj index ->
    CExpr.Proj (arg, index), ctx
  | MUniOp.Tag ->
    CExpr.Nav (arg, "tag"), ctx
  | MUniOp.GetVariant serial ->
    let _, ctx = cty ctx ty
    CExpr.Uni (CUniOp.Deref, CExpr.Nav (arg, ctxUniqueName ctx serial)), ctx
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
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, ctx = genExpr ctx expr
      go (result :: results) ctx exprs
  go [] ctx exprs

let genExpr (ctx: Ctx) (arg: MExpr): CExpr * Ctx =
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
    CExpr.Ref (ctxUniqueName ctx serial), ctx
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
      List.rev acc, ctx
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
  let ctx = ctxAddStmt ctx expr
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
      List.append args [CExpr.Int y; CExpr.Int x]
    let assertCall = CExpr.Call (callee, args)
    let ctx = ctxAddStmt ctx (CStmt.Expr assertCall)
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
  let ident = ctxUniqueName ctx serial
  let cty, ctx = cty ctx ty
  ctxAddStmt ctx (CStmt.Let (ident, expr, cty))

let genInitClosure ctx serial funSerial envSerial ty =
  let ident = ctxUniqueName ctx serial
  let ty, ctx = cty ctx ty
  let fields =
    [
      "fun", CExpr.Ref (ctxUniqueName ctx funSerial)
      "env", CExpr.Ref (ctxUniqueName ctx envSerial)
    ]
  let initExpr = CExpr.Init (fields, ty)
  ctxAddStmt ctx (CStmt.Let (ident, Some initExpr, ty))

let genInitBox ctx serial arg =
  let argTy, ctx = cty ctx (mexprToTy arg)
  let arg, ctx = genExpr ctx arg

  // void* p = (void*)malloc(sizeof T);
  let temp = ctxUniqueName ctx serial
  let ctx = ctxAddStmt ctx (CStmt.LetAlloc (temp, CTy.Ptr argTy, CTy.Ptr CTy.Void))

  // *(T*)p = t;
  let left = CExpr.Uni (CUniOp.Deref, CExpr.Cast (CExpr.Ref temp, CTy.Ptr argTy))
  let ctx = ctxAddStmt ctx (CStmt.Set (left, arg))

  ctx

let genInitIndirect ctx serial payload ty =
  let varName = ctxUniqueName ctx serial
  let payloadTy, ctx = cty ctx ty
  let ptrTy = CTy.Ptr payloadTy

  let payload, ctx = genExpr ctx payload

  // T* p = (T*)malloc(sizeof T);
  let ctx = ctxAddStmt ctx (CStmt.LetAlloc (varName, ptrTy, ptrTy))

  // *(T*)p = t;
  let left = CExpr.Uni (CUniOp.Deref, CExpr.Cast (CExpr.Ref varName, ptrTy))
  let ctx = ctxAddStmt ctx (CStmt.Set (left, payload))

  ctx

let genInitCons ctx serial head tail listTy =
  let temp = ctxUniqueName ctx serial
  let listTy, ctx = cty ctx listTy
  let ctx = ctxAddStmt ctx (CStmt.LetAlloc (temp, listTy, listTy))

  // head
  let head, ctx = genExpr ctx head
  let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "head"), head)
  let ctx = ctxAddStmt ctx stmt

  // tail
  let tail, ctx = genExpr ctx tail
  let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "tail"), tail)
  let ctx = ctxAddStmt ctx stmt

  ctx

let genInitTuple ctx serial items tupleTy =
  let ident = ctxUniqueName ctx serial
  let tupleTy, ctx = cty ctx tupleTy
  let ctx = ctxAddStmt ctx (CStmt.Let (ident, None, tupleTy))
  let rec go ctx i items =
    match items with
    | [] ->
      ctx
    | item :: items ->
      let left = CExpr.Nav (CExpr.Ref ident, tupleField i)
      let item, ctx = genExpr ctx item
      let stmt = CStmt.Set (left, item)
      let ctx = ctxAddStmt ctx stmt
      go ctx (i + 1) items
  go ctx 0 items

let genInitVariant ctx varSerial variantSerial payloadSerial unionTy =
  let temp = ctxUniqueName ctx varSerial
  let unionTy, ctx = cty ctx unionTy
  let variantName = ctxUniqueName ctx variantSerial
  let payloadExpr = CExpr.Ref (ctxUniqueName ctx payloadSerial)
  let fields =
    [
      "tag", CExpr.Ref (ctxUniqueName ctx variantSerial)
      variantName, payloadExpr
    ]
  let init = CExpr.Init (fields, unionTy)
  let ctx = ctxAddStmt ctx (CStmt.Let (temp, Some init, unionTy))
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
  ctxAddStmt ctx (CStmt.Expr expr)

let genStmtSet ctx serial right =
  let right, ctx = genExpr ctx right
  let ident = ctxUniqueName ctx serial
  let left = CExpr.Ref (ident)
  ctxAddStmt ctx (CStmt.Set (left, right))

let genStmtReturn ctx expr =
  let expr, ctx = genExpr ctx expr
  ctxAddStmt ctx (CStmt.Return (Some expr))

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
    ctxAddStmt ctx (CStmt.Label label)
  | MStmt.Goto (label, _) ->
    ctxAddStmt ctx (CStmt.Goto label)
  | MStmt.GotoIf (pred, label, _) ->
    let pred, ctx = genExpr ctx pred
    ctxAddStmt ctx (CStmt.GotoIf (pred, label))
  | MStmt.Exit (arg, _) ->
    let arg, ctx = genExpr ctx arg
    ctxAddStmt ctx (CStmt.Expr (CExpr.Call (CExpr.Ref "exit", [arg])))
  | MStmt.Proc _ ->
    ctx

let genBlock (ctx: Ctx) (stmts: MStmt list) =
  let bodyCtx = genStmts (ctxNewBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = ctxRollBack ctx bodyCtx
  List.rev stmts, ctx

let genStmts (ctx: Ctx) (stmts: MStmt list): Ctx =
  let rec go ctx stmts =
    match stmts with
    | [] -> ctx
    | stmt :: stmts ->
      let ctx = genStmt ctx stmt
      go ctx stmts
  go ctx stmts

let genDecls (ctx: Ctx) decls =
  match decls with
  | [] ->
    ctx
  | MDecl.Proc (procDecl, _) :: decls ->
    let ident, args =
      if procDecl.Main
      then "main", []
      else ctxUniqueName ctx procDecl.Callee, procDecl.Args
    let rec go acc ctx args =
      match args with
      | [] ->
        List.rev acc, ctx
      | (arg, ty, _) :: args ->
        let ident = ctxUniqueName ctx arg
        let cty, ctx = cty ctx ty
        go ((ident, cty) :: acc) ctx args
    let args, ctx = go [] ctx args
    let body, ctx = genBlock ctx procDecl.Body
    let resultTy, ctx = cty ctx procDecl.ResultTy
    let funDecl = CDecl.Fun (ident, args, resultTy, body)
    let ctx = ctxAddDecl ctx funDecl
    genDecls ctx decls

let genLogs (ctx: Ctx) =
  let rec go (ctx: Ctx) logs =
    match logs with
    | [] ->
      ctx
    | (log, loc) :: logs ->
      let y, _ = loc
      let msg = log |> logToString loc
      let ctx = ctxAddDecl ctx (CDecl.ErrDir (msg, 1 + y))
      go ctx logs

  let logs = ctx.Logs |> List.rev
  let ctx = go ctx logs
  let success = logs |> List.isEmpty
  success, ctx

let gen (decls, mirCtx: Mir.MirCtx): CDecl list * bool =
  let ctx = ctxFromMirCtx mirCtx
  let ctx = genDecls ctx decls
  let success, ctx = genLogs ctx
  let decls = ctx.Decls |> List.rev
  decls, success
