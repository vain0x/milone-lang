/// Generates CIR from AST.
module rec MiloneLang.CIrGen

open MiloneLang.Helpers

type MirTransCtx = MirTrans.MirTransCtx

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    VarSerial: int
    Vars: Map<int, string * MTy * Loc>
    TySerial: int
    TyEnv: Map<MTy, CTy>
    Stmts: CStmt list
    Decls: CDecl list
  }

let tupleField i = sprintf "t%d" i

let ctxFromMirCtx (mirCtx: MirTransCtx): Ctx =
  {
    VarSerial = mirCtx.VarSerial
    Vars = mirCtx.Vars
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
    match ctx.Vars |> Map.tryFind serial with
    | Some (ident, _, _) -> ident
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
    CTy.Struct "String", ctx
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
  | MTy.Ref _ ->
    failwith "unimpl"

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

/// `0`, `NULL`, or `(T) {}`
let genExprDefault ctx ty =
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CExpr.Int 0, ctx
  | MTy.Char
  | MTy.Box
  | MTy.List _ ->
    CExpr.Ref "NULL", ctx
  | MTy.Str
  | MTy.Fun _
  | MTy.Tuple _ ->
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Default, ty), ctx
  | MTy.Ref _ ->
    failwith "unimpl"

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
    CExpr.Index (CExpr.Nav (l, "str"), r), ctx
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
    CExpr.StrObj value, ctx
  | MExpr.Value (Value.Bool false, _) ->
    CExpr.Int 0, ctx
  | MExpr.Value (Value.Bool true, _) ->
    CExpr.Int 1, ctx
  | MExpr.Default (ty, _) ->
    genExprDefault ctx ty
  | MExpr.Ref (_, MTy.Unit, _) ->
    genExprDefault ctx MTy.Unit
  | MExpr.Ref (serial, _, _) ->
    CExpr.Ref (ctxUniqueName ctx serial), ctx
  | MExpr.UniOp (op, arg, ty, loc) ->
    genExprUniOp ctx op arg ty loc
  | MExpr.Op (op, l, r, _, _) ->
    genExprOp ctx op l r

let genExprCallPrintfn ctx format args =
  // Insert implicit cast from str to str ptr.
  let rec go acc ctx args =
    match args with
    | [] ->
      List.rev acc, ctx
    | MExpr.Value (Value.Str value, _) :: args ->
      go (CExpr.StrRaw value :: acc) ctx args
    | arg :: args when mexprTy arg = MTy.Str ->
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
  genExprDefault ctx MTy.Unit

let genExprCall ctx callee args ty =
  match callee, args with
  | MExpr.Ref (serial, _, _), (MExpr.Value (Value.Str format, _)) :: args
    when serial = SerialPrintfn ->
    genExprCallPrintfn ctx format args
  | MExpr.Ref (serial, _, _), args
    when serial = SerialStrSlice ->
    let callee = CExpr.Ref "str_slice"
    let args, ctx = genExprList ctx args
    CExpr.Call (callee, args), ctx
  | _ ->
    let callee, ctx = genExpr ctx callee
    let args, ctx = genExprList ctx args
    CExpr.Call (callee, args), ctx

let genInitExprCore ctx serial expr ty =
  let ident = ctxUniqueName ctx serial
  let cty, ctx = cty ctx ty
  ctxAddStmt ctx (CStmt.Let (ident, expr, cty))

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

let genStmtLetVal ctx serial init ty =
  match init with
  | MInit.UnInit ->
    genInitExprCore ctx serial None ty
  | MInit.Expr expr ->
    let expr, ctx = genExpr ctx expr
    genInitExprCore ctx serial (Some expr) ty
  | MInit.Call (callee, args) ->
    let expr, ctx = genExprCall ctx callee args ty
    genInitExprCore ctx serial (Some expr) ty
  | MInit.Box arg ->
    genInitBox ctx serial arg
  | MInit.Cons (head, tail, itemTy) ->
    genInitCons ctx serial head tail itemTy
  | MInit.Tuple items ->
    genInitTuple ctx serial items ty

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
  | MDecl.LetFun (callee, args, _caps, resultTy, body, _) :: decls ->
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

let gen (decls, mirTransCtx: MirTransCtx): CDecl list =
  let ctx = ctxFromMirCtx mirTransCtx
  genDecls ctx decls
