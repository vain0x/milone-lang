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

let ctxAddTupleDecl (ctx: Ctx) lTy rTy =
  let tupleTy = MTy.Tuple (lTy, rTy)
  let lTy, ctx = cty ctx lTy
  let rTy, ctx = cty ctx rTy
  let serial = ctx.TySerial + 1
  let ident = sprintf "Tuple_%d" serial
  let fields = [tupleField 0, lTy; tupleField 1, rTy]
  let ctx =
    { ctx with
        TySerial = ctx.TySerial + 1
        TyEnv = ctx.TyEnv |> Map.add tupleTy (CTy.Struct ident)
        Decls = CDecl.Struct (ident, fields) :: ctx.Decls
    }
  CTy.Struct ident, ctx

let ctxUniqueName (ctx: Ctx) serial =
  let ident =
    match ctx.VarName |> Map.tryFind serial with
    | Some ident -> ident
    | None -> ""
  sprintf "%s_%d" ident serial

let tyOf expr =
  Typing.tyOf expr

let cty (ctx: Ctx) (ty: MTy): CTy * Ctx =
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CTy.Int, ctx
  | MTy.Str ->
    CTy.Ptr CTy.Char, ctx
  | MTy.Fun _ ->
    CTy.Ptr CTy.Void, ctx
  | MTy.List itemTy ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddListDecl ctx itemTy
    | Some ty ->
      ty, ctx
  | MTy.Tuple (lTy, rTy) ->
    match ctx.TyEnv |> Map.tryFind ty with
    | None ->
      ctxAddTupleDecl ctx lTy rTy
    | Some ty ->
      ty, ctx

let callPrintf format args =
  let format = CExpr.Str (format + "\\n")
  CStmt.Expr (CExpr.Call (CExpr.Prim CPrim.Printf, format :: args))

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
  | MTy.Str
  | MTy.List _ ->
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Int 0, ty), ctx
  | MTy.Fun _
  | MTy.Tuple _ ->
    let ty, ctx = cty ctx ty
    CExpr.Cast (CExpr.Default, ty), ctx

/// `tuple.ti`
let genExprProj ctx expr index _ =
  let expr, ctx = genExpr ctx expr
  CExpr.Proj (expr, index), ctx

/// `x[i]`
let genExprIndex ctx l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  CExpr.Index (l, r), ctx

let genExprCall ctx callee args ty =
  match args with
  | [arg] ->
    let callee, ctx = genExpr ctx callee
    let arg, ctx = genExpr ctx arg
    CExpr.Call (callee, [arg]), ctx
  | [arg1; arg2] ->
    let callee, ctx = genExpr ctx callee
    let arg2, ctx = genExpr ctx arg2
    let arg1, ctx = genExpr ctx arg1
    CExpr.Call (callee, [arg1; arg2]), ctx
  | [] ->
    failwith "Never zero-arg call"
  | _ ->
    failwith "unimpl call with 2+ args"

let genExprCallExit ctx arg =
  let arg, ctx = genExpr ctx arg
  CExpr.Call (CExpr.Ref "exit", [arg]), ctx

let genExprCallPrintfn ctx format args =
  let args, ctx = genExprList ctx args
  let ctx = ctxAddStmt ctx (callPrintf format args)
  genExprDefault ctx MTy.Unit

let genExprCallStrAdd ctx l r =
  let l, ctx = genExpr ctx l
  let r, ctx = genExpr ctx r
  let strAddRef = CExpr.Ref "str_add"
  let callExpr = CExpr.Call (strAddRef, [l; r])
  callExpr, ctx

let genExprUniOp ctx arg =
  let arg, ctx = genExpr ctx arg
  CExpr.UniOp (MUniOp.Not, arg), ctx

let genExprOp ctx op first second ty loc =
  // Currently no support of non-int add/cmp/etc.
  let first, ctx = genExpr ctx first
  let second, ctx = genExpr ctx second
  let opExpr = CExpr.Op (op, first, second)
  opExpr, ctx

let genExprList ctx exprs =
  let rec go results ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, ctx = genExpr ctx expr
      go (result :: results) ctx exprs
  go [] ctx exprs

let genExpr (ctx: Ctx) (arg: MExpr<MTy * Loc>): CExpr * Ctx =
  match arg with
  | MExpr.Unit (ty, _) ->
    genExprDefault ctx ty
  | MExpr.Int (value, _) ->
    CExpr.Int value, ctx
  | MExpr.Str (value, _) ->
    CExpr.Str value, ctx
  | MExpr.Bool (false, _) ->
    CExpr.Int 0, ctx
  | MExpr.Bool (true, _) ->
    CExpr.Int 1, ctx
  | MExpr.Nil _ ->
    CExpr.Ref "NULL", ctx
  | MExpr.Prim (MPrim.Exit, _) ->
    CExpr.Ref "exit", ctx
  | MExpr.Prim (MPrim.StrCmp, _) ->
    CExpr.Ref "strcmp", ctx
  | MExpr.Ref (_, (MTy.Unit, _)) ->
    genExprDefault ctx MTy.Unit
  | MExpr.Ref (serial, _) ->
    CExpr.Ref (ctxUniqueName ctx serial), ctx
  | MExpr.ListIsEmpty _
  | MExpr.ListHead _
  | MExpr.ListTail _ ->
    failwith "unimpl"
  | MExpr.Proj (expr, index, a) ->
    genExprProj ctx expr index a
  | MExpr.Index (l, r, _) ->
    genExprIndex ctx l r
  | MExpr.Call (MExpr.Prim (MPrim.Printfn, _), (MExpr.Str (format, _)) :: args, _) ->
    genExprCallPrintfn ctx format args
  | MExpr.Call (MExpr.Prim (MPrim.StrAdd, _), [l; r], _) ->
    genExprCallStrAdd ctx l r
  | MExpr.Call (callee, args, (ty, _)) ->
    genExprCall ctx callee args ty
  | MExpr.UniOp (MUniOp.Not, arg, _) ->
    genExprUniOp ctx arg
  | MExpr.Op (op, first, second, (ty, loc)) ->
    genExprOp ctx op first second ty loc
  | MExpr.Prim _
  | MExpr.Call _ ->
    failwithf "unimpl %A" arg

let genStmt ctx stmt =
  match stmt with
  | MStmt.Expr (expr, _) ->
    let expr, ctx = genExpr ctx expr
    ctxAddStmt ctx (CStmt.Expr expr)
  | MStmt.LetVal (serial, init, (ty, _)) ->
    let ident = ctxUniqueName ctx serial
    let init, ctx =
      match init with
      | None -> None, ctx
      | Some init ->
        let init, ctx = genExpr ctx init
        Some init, ctx
    let cty, ctx = cty ctx ty
    ctxAddStmt ctx (CStmt.Let (ident, init, cty))
  | MStmt.LetCons (serial, (head, _), (tail, _), (ty, _)) ->
    let temp = ctxUniqueName ctx serial
    let listTy, ctx = cty ctx ty
    let ctx = ctxAddStmt ctx (CStmt.LetAlloc (temp, listTy))

    // head
    let head, ctx = genExpr ctx head
    let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "head"), head)
    let ctx = ctxAddStmt ctx stmt

    // tail
    let tail, ctx = genExpr ctx tail
    let stmt = CStmt.Set (CExpr.Arrow (CExpr.Ref temp, "tail"), tail)
    let ctx = ctxAddStmt ctx stmt

    ctx
  | MStmt.LetTuple (serial, elems, (ty, _)) ->
    let ident = ctxUniqueName ctx serial
    let tupleTy, ctx = cty ctx ty
    let ctx = ctxAddStmt ctx (CStmt.Let (ident, None, tupleTy))
    let rec go ctx i elems =
      match elems with
      | [] ->
        ctx
      | (elem, _) :: elems ->
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
      | (arg, (ty, _)) :: args ->
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
