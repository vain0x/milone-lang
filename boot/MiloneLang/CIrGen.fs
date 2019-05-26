/// Generates CIR from AST.
module rec MiloneLang.CIrGen

open MiloneLang.Helpers

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    Vars: Map<int, VarDef>
    VarUniqueNames: Map<int, string>
    TySerial: int
    TyEnv: Map<Ty, CTy>
    Tys: Map<int, TyDef>
    TyUniqueNames: Map<Ty, string>
    Stmts: CStmt list
    Decls: CDecl list
    Diags: Diag list
  }

let tupleField i = sprintf "t%d" i

/// Calculates tag type's name of union type.
let tagTyIdent tyIdent =
  sprintf "%sTag" tyIdent

let calculateVarUniqueNames vars =
  let groups = vars |> Map.toList |> Seq.groupBy (fun (_, varDef) -> varDefIdent varDef)
  groups |> Seq.collect (fun (ident, vars) ->
    vars |> Seq.mapi (fun i (serial, _) ->
      let ident = if i = 0 then sprintf "%s_" ident else sprintf "%s_%d" ident i
      (serial, ident)
  ))
  |> Map.ofSeq

let calculateTyUniqueNames tys =
  let groups = tys |> Map.toList |> Seq.groupBy (fun (_, tyDef) -> tyDefIdent tyDef)
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
    TySerial = 0
    TyEnv = Map.empty
    Tys = mirCtx.Tys
    TyUniqueNames = tyNames
    Stmts = []
    Decls = []
    Diags = mirCtx.Diags
  }

let ctxAddErr (ctx: Ctx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

let ctxNewBlock (ctx: Ctx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: Ctx) (dCtx: Ctx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddStmt (ctx: Ctx) stmt =
  { ctx with Stmts = stmt :: ctx.Stmts }

let ctxAddDecl (ctx: Ctx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddFunDecl (ctx: Ctx) sTy tTy =
  let funTy = tyFun sTy tTy
  let _, argTys, resultTy = rollFunTy funTy
  let ident, ctx = ctxUniqueTyName ctx funTy
  let selfTy = CTy.Struct ident
  let envTy = CTy.Ptr CTy.Void
  let argTys, ctx = cirifyTys (argTys, ctx)
  let resultTy, ctx = cty ctx resultTy
  let fields = ["fun", CTy.FunPtr (envTy :: argTys, resultTy); "env", envTy]
  let ctx: Ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add funTy selfTy
        Decls = CDecl.Struct (ident, fields, []) :: ctx.Decls
    }
  selfTy, ctx

let ctxAddListDecl (ctx: Ctx) itemTy =
  let listTy = tyList itemTy
  let itemTy, ctx = cty ctx itemTy
  let ident, ctx = ctxUniqueTyName ctx listTy
  let selfTy = CTy.Ptr (CTy.Struct ident)
  let fields = ["head", itemTy; "tail", selfTy]
  let ctx: Ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add listTy selfTy
        Decls = CDecl.Struct (ident, fields, []) :: ctx.Decls
    }
  selfTy, ctx

let ctxAddTupleDecl (ctx: Ctx) itemTys =
  let rec go acc ctx i itemTys =
    match itemTys with
    | [] ->
      List.rev acc, ctx
    | itemTy :: itemTys ->
      let itemTy, ctx = cty ctx itemTy
      let field = tupleField i, itemTy
      go (field :: acc) ctx (i + 1) itemTys
  let fields, ctx = go [] ctx 0 itemTys

  let tupleTy = tyTuple itemTys
  let tupleTyIdent, ctx = ctxUniqueTyName ctx tupleTy
  let ctx: Ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add tupleTy (CTy.Struct tupleTyIdent)
        Decls = CDecl.Struct (tupleTyIdent, fields, []) :: ctx.Decls
    }
  CTy.Struct tupleTyIdent, ctx

let ctxAddUnionDecl (ctx: Ctx) tyIdent tySerial variants =
  let variants =
    variants |> List.map (fun variantSerial ->
      match ctx.Vars |> Map.tryFind variantSerial with
      | Some (VarDef.Variant (ident, _, hasArg, argTy, _, _)) ->
        ident, variantSerial, hasArg, argTy
      | _ -> failwith "Never"
    )

  let tags =
    variants |> List.map (fun (_, serial, _, _) ->
      ctxUniqueName ctx serial)
  let variants, ctx =
    (variants, ctx) |> stFlatMap (fun ((_, serial, hasArg, argTy), acc, ctx) ->
      if hasArg then
        let argTy, ctx = cty ctx argTy
        (ctxUniqueName ctx serial, argTy) :: acc, ctx
      else
        acc, ctx
    )

  let unionTyIdent, ctx = ctxUniqueTyName ctx (tyRef tySerial [])
  let unionTy = CTy.Struct unionTyIdent
  let tagTyIdent = tagTyIdent unionTyIdent
  let tagTy = CTy.Enum tagTyIdent
  let ctx =
    { ctx with
        TyEnv = ctx.TyEnv |> Map.add (tyRef tySerial []) unionTy
        Decls =
          CDecl.Struct (unionTyIdent, ["tag", tagTy], variants)
          :: CDecl.Enum (tagTyIdent, tags)
          :: ctx.Decls
    }
  unionTy, ctx

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
          let arity, argTys, resultTy = rollFunTy ty
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
        | Ty.Con (TyCon.Range, _)
        | Ty.Con (TyCon.List, _)
        | Ty.Con (TyCon.Fun, _)
        | Ty.Con (TyCon.RefIdent _, _)
        | Ty.Error ->
          failwithf "Never"
      let ctx = { ctx with TyUniqueNames = ctx.TyUniqueNames |> Map.add ty ident }
      ident, ctx
  go ty ctx

let cty (ctx: Ctx) (ty: Ty): CTy * Ctx =
  match ty with
  | Ty.Con (TyCon.Bool, _)
  | Ty.Con (TyCon.Int, _) ->
    CTy.Int, ctx
  | Ty.Con (TyCon.Char, _) ->
    CTy.Char, ctx
  | Ty.Con (TyCon.Str, _) ->
    CTy.Struct "String", ctx
  | Ty.Meta _ // FIXME: Unresolved type variables are `obj` for now.
  | Ty.Con (TyCon.Obj, _) ->
    CTy.Ptr CTy.Void, ctx
  | Ty.Con (TyCon.Fun, [sTy; tTy]) ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddFunDecl ctx sTy tTy
    | Some ty ->
      ty, ctx
  | Ty.Con (TyCon.List, [itemTy]) ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddListDecl ctx itemTy
    | Some ty ->
      ty, ctx
  | Ty.Con (TyCon.Tuple, []) ->
    CTy.Int, ctx
  | Ty.Con (TyCon.Tuple, itemTys) ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddTupleDecl ctx itemTys
    | Some ty ->
      ty, ctx
  | Ty.Con (TyCon.Ref serial, _) ->
    match ctx.Tys |> Map.tryFind serial with
    | Some (TyDef.Union (tyIdent, variants, _)) ->
      match ctx.TyEnv |> Map.tryFind ty with
      | Some ty ->
        ty, ctx
      | None ->
        ctxAddUnionDecl ctx tyIdent serial variants
    | Some (TyDef.Meta _) ->
      failwith "Never"
    | None ->
      CTy.Void, ctxAddErr ctx "Unknown type reference" (0, 0) // FIXME: source location
  | Ty.Con (TyCon.List, _)
  | Ty.Con (TyCon.Fun, _)
  | Ty.Con (TyCon.Range, _)
  | Ty.Con (TyCon.RefIdent _, _)
  | Ty.Error ->
    failwith "Never"

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
  | MOp.Le -> CBinOp.Le
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
  | Ty.Con (TyCon.Range, _)
  | Ty.Con (TyCon.RefIdent _, _)
  | Ty.Error ->
    failwith "Never"

let genExprProc ctx serial _ty _loc =
  let ident = ctxUniqueName ctx serial
  CExpr.Ref ident, ctx

let genExprVariant ctx serial ty =
  let ty, ctx = cty ctx ty
  let tag = CExpr.Ref (ctxUniqueName ctx serial)
  CExpr.Init (["tag", tag], ty), ctx

let genExprOpAsCall ctx ident l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let callExpr = CExpr.Call (CExpr.Ref ident, [l; r])
  callExpr, ctx

let genExprUniOp ctx op arg ty _ =
  let arg, ctx = genExpr ctx arg
  match op with
  | MUniOp.Not ->
    CExpr.UniOp (CUniOp.Not, arg), ctx
  | MUniOp.StrPtr ->
    CExpr.Nav (arg, "str"), ctx
  | MUniOp.StrLen ->
    CExpr.Nav (arg, "len"), ctx
  | MUniOp.Unbox ->
    let valTy, ctx = cty ctx ty
    let deref = CExpr.UniOp (CUniOp.Deref, CExpr.Cast (arg, CTy.Ptr valTy))
    deref, ctx
  | MUniOp.Proj index ->
    CExpr.Proj (arg, index), ctx
  | MUniOp.Tag ->
    CExpr.Nav (arg, "tag"), ctx
  | MUniOp.GetVariant serial ->
    CExpr.Nav (arg, ctxUniqueName ctx serial), ctx
  | MUniOp.ListIsEmpty ->
    CExpr.UniOp (CUniOp.Not, arg), ctx
  | MUniOp.ListHead ->
    CExpr.Arrow (arg, "head"), ctx
  | MUniOp.ListTail ->
    CExpr.Arrow (arg, "tail"), ctx

let genExprOp ctx op l r =
  match op with
  | MOp.StrAdd ->
    genExprOpAsCall ctx "str_add" l r
  | MOp.StrCmp ->
    genExprOpAsCall ctx "str_cmp" l r
  | MOp.StrIndex ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    CExpr.Index (CExpr.Nav (l, "str"), r), ctx
  | _ ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    let opExpr = CExpr.BinOp (cOpFrom op, l, r)
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
  match arg with
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
  | MExpr.Ref (_, Ty.Con (TyCon.Tuple, []), _) ->
    genExprDefault ctx tyUnit
  | MExpr.Ref (serial, _, _) ->
    CExpr.Ref (ctxUniqueName ctx serial), ctx
  | MExpr.Proc (serial, ty, loc) ->
    genExprProc ctx serial ty loc
  | MExpr.Variant (_, serial, ty, _) ->
    genExprVariant ctx serial ty
  | MExpr.UniOp (op, arg, ty, loc) ->
    genExprUniOp ctx op arg ty loc
  | MExpr.Op (op, l, r, _, _) ->
    genExprOp ctx op l r
  | MExpr.Prim _ ->
    failwith "Never: Primitives must be used as callee"

let genExprCallPrintfn ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] ->
      List.rev acc, ctx
    | MExpr.Lit (Lit.Str value, _) :: args ->
      go (CExpr.StrRaw value :: acc) ctx args
    | arg :: args when mexprTy arg = tyStr ->
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

let genExprCallProc ctx callee args ty =
  match callee, args with
  | MExpr.Prim (HPrim.Printfn, _, _), (MExpr.Lit (Lit.Str format, _)) :: args ->
    genExprCallPrintfn ctx format args
  | MExpr.Prim (HPrim.StrSlice, _, _), args ->
    let callee = CExpr.Ref "str_slice"
    let args, ctx = genExprList ctx args
    CExpr.Call (callee, args), ctx
  | MExpr.Prim (HPrim.Char, _, _), [arg] ->
    let arg, ctx = genExpr ctx arg
    CExpr.Cast (arg, CTy.Char), ctx
  | MExpr.Prim (HPrim.Int, Ty.Con (TyCon.Fun, [argTy; _]), _), [arg] ->
    genExprCallInt arg argTy ctx
  | MExpr.Prim (HPrim.String, Ty.Con (TyCon.Fun, [argTy; _]), _), [arg] ->
    genExprCallString arg argTy ctx
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
  let argTy, ctx = cty ctx (mexprTy arg)
  let arg, ctx = genExpr ctx arg

  // void* p = (void*)malloc(sizeof T);
  let temp = ctxUniqueName ctx serial
  let ctx = ctxAddStmt ctx (CStmt.LetAlloc (temp, CTy.Ptr argTy, CTy.Ptr CTy.Void))

  // *(T*)p = t;
  let left = CExpr.UniOp (CUniOp.Deref, CExpr.Cast (CExpr.Ref temp, CTy.Ptr argTy))
  let ctx = ctxAddStmt ctx (CStmt.Set (left, arg))

  ctx

let genInitCons ctx serial head tail itemTy =
  let temp = ctxUniqueName ctx serial
  let listTy, ctx = cty ctx (tyList itemTy)
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

let genInitUnion ctx varSerial variantSerial arg argTy unionTy =
  let arg, ctx = genExpr ctx arg
  let temp = ctxUniqueName ctx varSerial
  let unionTy, ctx = cty ctx unionTy
  let fields =
    [
      "tag", CExpr.Ref (ctxUniqueName ctx variantSerial)
      ctxUniqueName ctx variantSerial, arg
    ]
  let init = CExpr.Init (fields, unionTy)
  let ctx = ctxAddStmt ctx (CStmt.Let (temp, Some init, unionTy))
  ctx

let genStmtLetVal ctx serial init ty =
  match init with
  | MInit.UnInit ->
    genInitExprCore ctx serial None ty
  | MInit.Expr expr ->
    let expr, ctx = genExpr ctx expr
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
  | MInit.Cons (head, tail, itemTy) ->
    genInitCons ctx serial head tail itemTy
  | MInit.Tuple items ->
    genInitTuple ctx serial items ty
  | MInit.Union (variantSerial, arg, argTy) ->
    genInitUnion ctx serial variantSerial arg argTy ty

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
  | MStmt.LetVal (serial, init, ty, _) ->
    genStmtLetVal ctx serial init ty
  | MStmt.Set (serial, right, _) ->
    genStmtSet ctx serial right
  | MStmt.Return (expr, _) ->
    genStmtReturn ctx expr
  | MStmt.Label (label, _) ->
    ctxAddStmt ctx (CStmt.Label label)
  | MStmt.Goto (label, _) ->
    ctxAddStmt ctx (CStmt.Goto label)
  | MStmt.GotoUnless (pred, label, _) ->
    let pred, ctx = genExpr ctx pred
    ctxAddStmt ctx (CStmt.GotoUnless (pred, label))
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
      if List.isEmpty decls
      then "main", []
      else ctxUniqueName ctx procDecl.Callee, procDecl.Args
    let rec go acc ctx args =
      match args with
      | [] ->
        List.rev acc, ctx
      | (arg, _, ty, _) :: args ->
        let ident = ctxUniqueName ctx arg
        let cty, ctx = cty ctx ty
        go ((ident, cty) :: acc) ctx args
    let args, ctx = go [] ctx args
    let body, ctx = genBlock ctx procDecl.Body
    let resultTy, ctx = cty ctx procDecl.ResultTy
    let funDecl = CDecl.Fun (ident, args, resultTy, body)
    let ctx = ctxAddDecl ctx funDecl
    genDecls ctx decls

let genDiags (ctx: Ctx) =
  let rec go (ctx: Ctx) diags =
    match diags with
    | [] ->
      ctx
    | Diag.Err (message, (y, x)) :: diags ->
      let message = sprintf "%d:%d %s" (1 + y) (1 + x) message
      let ctx = ctxAddDecl ctx (CDecl.ErrDir (message, 1 + y))
      go ctx diags
  let diags = ctx.Diags |> List.rev
  let ctx = go ctx diags
  let success = diags |> List.isEmpty
  success, ctx

let gen (decls, mirCtx: Mir.MirCtx): CDecl list * bool =
  let ctx = ctxFromMirCtx mirCtx
  let ctx = genDecls ctx decls
  let success, ctx = genDiags ctx
  let decls = ctx.Decls |> List.rev
  decls, success
