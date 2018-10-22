/// Generates CIR from AST.
module rec MiloneLang.CIrGen

type MirCtx = Mir.MirCtx

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    VarSerial: int
    VarName: Map<int, string>
    Stmts: CStmt list
    Decls: CDecl list
  }

let ctxFromMirCtx (mirCtx: MirCtx): Ctx =
  {
    VarSerial = mirCtx.VarSerial
    VarName = mirCtx.VarName
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

let ctxUniqueName (ctx: Ctx) serial =
  let ident =
    match ctx.VarName |> Map.tryFind serial with
    | Some ident -> ident
    | None -> ""
  sprintf "%s_%d" ident serial

let tyOf expr =
  Typing.tyOf expr

let cty (ty: MTy): CTy =
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CTy.Int
  | MTy.Str ->
    CTy.Ptr CTy.Char
  | MTy.Fun _ ->
    CTy.Ptr CTy.Void
  | MTy.Box boxTy ->
    CTy.Box (cboxTy boxTy)

let cboxTy (ty: MBoxTy): CBoxTy =
  match ty with
  | MBoxTy.Unit
  | MBoxTy.Bool
  | MBoxTy.Int ->
    CBoxTy.Int
  | MBoxTy.Str ->
    CBoxTy.Str
  | MBoxTy.Fun _ ->
    CBoxTy.Int // FIXME: what if function boxed?
  | MBoxTy.Tuple (lTy, rTy) ->
    CBoxTy.Tuple [cty lTy; cty rTy]

let cexprUnit = CExpr.Int 0

let callPrintf format args =
  let format = CExpr.Str (format + "\\n")
  CStmt.Expr (CExpr.Call (CExpr.Prim CPrim.Printf, format :: args, CTy.Int))

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

let ctxFreshVar (ctx: Ctx) (name: string) (ty: CTy) =
  let name, ctx = ctxFreshName ctx name
  name, CExpr.Ref (name, ty), ctx

let genExprBox ctx expr (ty, _) =
  let expr, ctx = genExpr ctx expr
  match ty with
  | MTy.Unit
  | MTy.Bool
  | MTy.Int ->
    CExpr.Box (expr, CBoxTy.Int), ctx
  | MTy.Str ->
    CExpr.Box (expr, CBoxTy.Str), ctx
  | MTy.Fun _ ->
    failwith "unimpl boxing of functions"
  | MTy.Box _ ->
    expr, ctx

/// `box.t[i].?`
let genExprUnbox ctx expr index (ty, _) =
  let expr, ctx = genExpr ctx expr
  let valTy =
    match ty with
    | MTy.Unit
    | MTy.Bool
    | MTy.Int ->
      CBoxTy.Int
    | MTy.Str ->
      CBoxTy.Str
    | MTy.Fun _ ->
      failwith "unimpl unboxing functions"
    | MTy.Box _ ->
      CBoxTy.Self
  CExpr.Unbox (expr, index, valTy, cty ty), ctx

let genExprCall ctx callee args ty =
  match args with
  | [arg] ->
    let callee, ctx = genExpr ctx callee
    let arg, ctx = genExpr ctx arg
    CExpr.Call (callee, [arg], cty ty), ctx
  | [arg1; arg2] ->
    let callee, ctx = genExpr ctx callee
    let arg2, ctx = genExpr ctx arg2
    let arg1, ctx = genExpr ctx arg1
    CExpr.Call (callee, [arg1; arg2], cty ty), ctx
  | [] ->
    failwith "Never zero-arg call"
  | _ ->
    failwith "unimpl call with 2+ args"

let genExprCallPrintfn ctx format args =
  let args, ctx = genExprList ctx args
  let ctx = ctxAddStmt ctx (callPrintf format args)
  cexprUnit, ctx

let genExprOp ctx op first second ty loc =
  // Currently no support of non-int add/cmp/etc.
  let ty = CTy.Int
  let first, ctx = genExpr ctx first
  let second, ctx = genExpr ctx second
  // let tempIdent, temp, ctx = ctxFreshVar ctx "op" ty
  let opExpr = CExpr.Op (op, first, second, ty)
  // let ctx = ctxAddStmt ctx (CStmt.Let (tempIdent, Some opExpr, ty))
  // temp, ctx
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
  | MExpr.Unit _ ->
    cexprUnit, ctx
  | MExpr.Int (value, _) ->
    CExpr.Int value, ctx
  | MExpr.Str (value, _) ->
    CExpr.Str value, ctx
  | MExpr.Bool (false, _) ->
    CExpr.Int 0, ctx
  | MExpr.Bool (true, _) ->
    CExpr.Int 1, ctx
  | MExpr.Ref (_, (MTy.Unit, _)) ->
    cexprUnit, ctx
  | MExpr.Ref (serial, (ty, _)) ->
    CExpr.Ref (ctxUniqueName ctx serial, cty ty), ctx
  | MExpr.Box (expr, a) ->
    genExprBox ctx expr a
  | MExpr.Unbox (expr, index, a) ->
    genExprUnbox ctx expr index a
  | MExpr.Call (MExpr.Prim (MPrim.Printfn, _), (MExpr.Str (format, _)) :: args, _) ->
    genExprCallPrintfn ctx format args
  | MExpr.Call (callee, args, (ty, _)) ->
    genExprCall ctx callee args ty
  | MExpr.Op (op, first, second, (ty, loc)) ->
    genExprOp ctx op first second ty loc
  | MExpr.Prim _
  | MExpr.Call _ ->
    failwithf "unimpl %A" arg

let genStmt ctx stmt =
  match stmt with
  | MStmt.Expr _ ->
    // No side-effect.
    ctx
  | MStmt.LetVal (serial, init, (ty, _)) ->
    let ident = ctxUniqueName ctx serial
    let init, ctx =
      match init with
      | None -> None, ctx
      | Some init ->
        let init, ctx = genExpr ctx init
        Some init, ctx
    ctxAddStmt ctx (CStmt.Let (ident, init, cty ty))
  | MStmt.LetBox (serial, elems, (ty, _)) ->
    let ident = ctxUniqueName ctx serial
    let ctx = ctxAddStmt ctx (CStmt.LetBox (ident, List.length elems))
    let left = CExpr.Ref (ident, cty ty)
    let rec go ctx i elems =
      match elems with
      | [] ->
        ctx
      | (elem, elemA) :: elems ->
        let elem, ctx = genExprBox ctx elem elemA
        let stmt = CStmt.Emplace (left, i, elem)
        let ctx = ctxAddStmt ctx stmt
        go ctx (i + 1) elems
    go ctx 0 elems
  | MStmt.Set (serial, right, (ty, _)) ->
    let right, ctx = genExpr ctx right
    let ident = ctxUniqueName ctx serial
    let left = CExpr.Ref (ident, cty ty)
    ctxAddStmt ctx (CStmt.Set (left, right, cty ty))
  | MStmt.Return (expr, _) ->
    let expr, ctx = genExpr ctx expr
    ctxAddStmt ctx (CStmt.Return (Some expr))
  | MStmt.If (pred, thenCl, elseCl, _a) ->
    let pred, ctx = genExpr ctx pred
    let thenCl, ctx = genBlock ctx thenCl
    let elseCl, ctx = genBlock ctx elseCl
    let ctx = ctxAddStmt ctx (CStmt.If (pred, thenCl, elseCl))
    ctx

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
    let args =
      List.map (fun (arg, (ty, _)) -> ctxUniqueName ctx arg, cty ty) args
    let body, _ctx = genBlock ctx body
    let funDecl = CDecl.Fun (ident, args, cty resultTy, body)
    let ctx = ctxAddDecl ctx funDecl
    genDecls ctx decls

let gen (mirCtx: MirCtx): CDecl list =
  let ctx = ctxFromMirCtx mirCtx
  let decls = List.rev mirCtx.Decls
  genDecls ctx decls
