/// Generates CIR from AST.
module rec MiloneLang.CIrGen

type MirCtx = Mir.MirCtx

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    VarSerial: int
    VarName: Map<int, string>
    TySerial: int
    TyEnv: Map<MTy, CTy>
    Stmts: CStmt list
    Decls: CDecl list
  }

let tupleField i = sprintf "t%d" i

let ctxFromMirCtx (mirCtx: MirCtx): Ctx =
  {
    VarSerial = mirCtx.VarSerial
    VarName = mirCtx.VarName
    TySerial = 0
    TyEnv = Map.empty
    Stmts = []
    Decls = []
  }

let ctxNewBlock (ctx: Ctx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: Ctx) (dCtx: Ctx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddStmt (ctx: Ctx) stmt =
  { ctx with Stmts = stmt :: ctx.Stmts }

let ctxAddDecl (ctx: Ctx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddListDecl (ctx: Ctx) itemTy =
  let listTy = MTy.List itemTy
  let itemTy, ctx = cty ctx itemTy
  let serial = ctx.TySerial + 1
  let ident = sprintf "List_%d" serial
  let selfTy = CTy.Ptr (CTy.Struct ident)
  let fields = ["head", itemTy; "tail", selfTy]
  let ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add listTy selfTy
        Decls = CDecl.Struct (ident, fields) :: ctx.Decls
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

  let tupleTy = MTy.Tuple itemTys
  let serial = ctx.TySerial + 1
  let tupleTyIdent = sprintf "Tuple_%d" serial
  let ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add tupleTy (CTy.Struct tupleTyIdent)
        Decls = CDecl.Struct (tupleTyIdent, fields) :: ctx.Decls
    }
  CTy.Struct tupleTyIdent, ctx

let ctxUniqueName (ctx: Ctx) serial =
  let ident =
    match ctx.VarName |> Map.tryFind serial with
    | Some ident -> ident
    | None -> ""
  sprintf "%s_%d" ident serial

let cty (ctx: Ctx) (ty: MTy): CTy * Ctx =
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CTy.Int, ctx
  | MTy.Char ->
    CTy.Char, ctx
  | MTy.Str ->
    CTy.Ptr CTy.Char, ctx
  | MTy.Box
  | MTy.Fun _ ->
    CTy.Ptr CTy.Void, ctx
  | MTy.List itemTy ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddListDecl ctx itemTy
    | Some ty ->
      ty, ctx
  | MTy.Tuple itemTys ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddTupleDecl ctx itemTys
    | Some ty ->
      ty, ctx

let cOpFrom op =
  match op with
  | MOp.Mul -> COp.Mul
  | MOp.Div -> COp.Div
  | MOp.Mod -> COp.Mod
  | MOp.Add -> COp.Add
  | MOp.Sub -> COp.Sub
  | MOp.Eq -> COp.Eq
  | MOp.Ne -> COp.Ne
  | MOp.Lt -> COp.Lt
  | MOp.Le -> COp.Le
  | MOp.StrAdd
  | MOp.StrCmp
  | MOp.StrIndex -> failwith "Never"

let callPrintf format args =
  let format = CExpr.Str (format + "\n")
  CStmt.Expr (CExpr.Call (CExpr.Ref "printf", format :: args))

let ctxFreshName (ctx: Ctx) (ident: string) =
  let serial = ctx.VarSerial + 1
  let ctx =
    {
      ctx with
        VarSerial = ctx.VarSerial + 1
        VarName = ctx.VarName |> Map.add serial ident
    }
  let ident = ctxUniqueName ctx serial
  ident, ctx

let ctxFreshVar (ctx: Ctx) (name: string) =
  let name, ctx = ctxFreshName ctx name
  name, CExpr.Ref name, ctx

/// `0` or `(T) {}`
let genExprDefault ctx ty =
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CExpr.Int 0, ctx
  | MTy.Char
  | MTy.Str
  | MTy.Box
  | MTy.List _ ->
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Int 0, ty), ctx
  | MTy.Fun _
  | MTy.Tuple _ ->
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Default, ty), ctx

let genExprCall ctx callee args ty =
  match callee, args with
  | MExpr.Ref (serial, _, _), (MExpr.Value (Value.Str format, _)) :: args
    when serial = Typing.SerialPrintfn ->
    genExprCallPrintfn ctx format args
  | _ ->
    let rec genArgs acc ctx args =
      match args with
      | [] ->
        List.rev acc, ctx
      | arg :: args ->
        let arg, ctx = genExpr ctx arg
        genArgs (arg :: acc) ctx args

    let callee, ctx = genExpr ctx callee
    let args, ctx = genArgs [] ctx args
    CExpr.Call (callee, args), ctx

let genExprCallExit ctx arg =
  let arg, ctx = genExpr ctx arg
  CExpr.Call (CExpr.Ref "exit", [arg]), ctx

let genExprCallPrintfn ctx format args =
  let args, ctx = genExprList ctx args
  let ctx = ctxAddStmt ctx (callPrintf format args)
  genExprDefault ctx MTy.Unit

let genExprOpAsCall ctx ident l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let callExpr = CExpr.Call (CExpr.Ref ident, [l; r])
  callExpr, ctx

let genExprUniOp ctx op arg ty =
  let argTy = Mir.mexprTy arg
  let arg, ctx = genExpr ctx arg
  match op with
  | MUniOp.Not ->
    CExpr.UniOp (CUniOp.Not, arg), ctx
  | MUniOp.StrLen ->
    CExpr.Call (CExpr.Ref "strlen", [arg]), ctx
  | MUniOp.Box ->
    let tempIdent, temp, ctx = ctxFreshVar ctx "box"
    let argTy, ctx = cty ctx argTy
    // void* p = (void*)malloc(sizeof T);
    let ctx = ctxAddStmt ctx (CStmt.LetAlloc (tempIdent, CTy.Ptr argTy, CTy.Ptr CTy.Void))
    // *(T*)p = t;
    let left = CExpr.UniOp (CUniOp.Deref, CExpr.Cast (temp, CTy.Ptr argTy))
    let ctx = ctxAddStmt ctx (CStmt.Set (left, arg))
    temp, ctx
  | MUniOp.Unbox ->
    let valTy, ctx = cty ctx ty
    let deref = CExpr.UniOp (CUniOp.Deref, CExpr.Cast (arg, CTy.Ptr valTy))
    deref, ctx
  | MUniOp.Proj index ->
    CExpr.Proj (arg, index), ctx
  | MUniOp.ListIsEmpty ->
    CExpr.UniOp (CUniOp.Not, arg), ctx
  | MUniOp.ListHead ->
    CExpr.Arrow (arg, "head"), ctx
  | MUniOp.ListTail ->
    CExpr.Arrow (arg, "tail"), ctx
  | MUniOp.Exit ->
    CExpr.Call (CExpr.Ref "exit", [arg]), ctx

let genExprOp ctx op l r =
  match op with
  | MOp.StrAdd ->
    genExprOpAsCall ctx "str_add" l r
  | MOp.StrCmp ->
    genExprOpAsCall ctx "str_cmp" l r
  | MOp.StrIndex ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    CExpr.Index (l, r), ctx
  | _ ->
    let l, ctx = genExpr ctx l
    let r, ctx = genExpr ctx r
    let opExpr = CExpr.Op (cOpFrom op, l, r)
    opExpr, ctx

let genExprList ctx exprs =
  let rec go results ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, ctx = genExpr ctx expr
      go (result :: results) ctx exprs
  go [] ctx exprs

let genExpr (ctx: Ctx) (arg: MExpr<Loc>): CExpr * Ctx =
  match arg with
  | MExpr.Value (Value.Int value, _) ->
    CExpr.Int value, ctx
  | MExpr.Value (Value.Char value, _) ->
    CExpr.Char value, ctx
  | MExpr.Value (Value.Str value, _) ->
    CExpr.Str value, ctx
  | MExpr.Value (Value.Bool false, _) ->
    CExpr.Int 0, ctx
  | MExpr.Value (Value.Bool true, _) ->
    CExpr.Int 1, ctx
  | MExpr.Unit (ty, _) ->
    genExprDefault ctx ty
  | MExpr.Nil _ ->
    CExpr.Ref "NULL", ctx
  | MExpr.Ref (_, MTy.Unit, _) ->
    genExprDefault ctx MTy.Unit
  | MExpr.Ref (serial, _, _) ->
    CExpr.Ref (ctxUniqueName ctx serial), ctx
  | MExpr.Call (callee, args, ty, _) ->
    genExprCall ctx callee args ty
  | MExpr.UniOp (op, arg, ty, _) ->
    genExprUniOp ctx op arg ty
  | MExpr.Op (op, l, r, _, _) ->
    genExprOp ctx op l r

let genStmt ctx stmt =
  match stmt with
  | MStmt.Expr (expr, _) ->
    let expr, ctx = genExpr ctx expr
    ctxAddStmt ctx (CStmt.Expr expr)
  | MStmt.LetVal (serial, init, ty, _) ->
    let ident = ctxUniqueName ctx serial
    let init, ctx =
      match init with
      | None -> None, ctx
      | Some init ->
        let init, ctx = genExpr ctx init
        Some init, ctx
    let cty, ctx = cty ctx ty
    ctxAddStmt ctx (CStmt.Let (ident, init, cty))
  | MStmt.LetCons (serial, head, tail, itemTy, _) ->
    let temp = ctxUniqueName ctx serial
    let listTy, ctx = cty ctx (MTy.List itemTy)
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
  | MStmt.LetTuple (serial, elems, tupleTy, _) ->
    let ident = ctxUniqueName ctx serial
    let tupleTy, ctx = cty ctx tupleTy
    let ctx = ctxAddStmt ctx (CStmt.Let (ident, None, tupleTy))
    let rec go ctx i elems =
      match elems with
      | [] ->
        ctx
      | elem :: elems ->
        let left = CExpr.Nav (CExpr.Ref ident, tupleField i)
        let elem, ctx = genExpr ctx elem
        let stmt = CStmt.Set (left, elem)
        let ctx = ctxAddStmt ctx stmt
        go ctx (i + 1) elems
    go ctx 0 elems
  | MStmt.Set (serial, right, _) ->
    let right, ctx = genExpr ctx right
    let ident = ctxUniqueName ctx serial
    let left = CExpr.Ref (ident)
    ctxAddStmt ctx (CStmt.Set (left, right))
  | MStmt.Return (expr, _) ->
    let expr, ctx = genExpr ctx expr
    ctxAddStmt ctx (CStmt.Return (Some expr))
  | MStmt.Label (label, _) ->
    ctxAddStmt ctx (CStmt.Label label)
  | MStmt.Goto (label, _) ->
    ctxAddStmt ctx (CStmt.Goto label)
  | MStmt.GotoUnless (pred, label, _) ->
    let pred, ctx = genExpr ctx pred
    ctxAddStmt ctx (CStmt.GotoUnless (pred, label))

let genBlock (ctx: Ctx) (stmts: MStmt<_> list) =
  let bodyCtx = genStmts (ctxNewBlock ctx) stmts
  let stmts = bodyCtx.Stmts
  let ctx = ctxRollBack ctx bodyCtx
  List.rev stmts, ctx

let genStmts (ctx: Ctx) (stmts: MStmt<_> list): Ctx =
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
    ctx.Decls |> List.rev
  | MDecl.LetFun (callee, args, resultTy, body, _) :: decls ->
    let ident, args =
      if List.isEmpty decls
      then "main", []
      else ctxUniqueName ctx callee, args
    let rec go acc ctx args =
      match args with
      | [] ->
        List.rev acc, ctx
      | (arg, ty, _) :: args ->
        let ident = ctxUniqueName ctx arg
        let cty, ctx = cty ctx ty
        go ((ident, cty) :: acc) ctx args
    let args, ctx = go [] ctx args
    let body, ctx = genBlock ctx body
    let resultTy, ctx = cty ctx resultTy
    let funDecl = CDecl.Fun (ident, args, resultTy, body)
    let ctx = ctxAddDecl ctx funDecl
    genDecls ctx decls

let gen (mirCtx: MirCtx): CDecl list =
  let ctx = ctxFromMirCtx mirCtx
  let decls = List.rev mirCtx.Decls
  genDecls ctx decls
