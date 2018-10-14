/// Generates CIR from AST.
module rec MiloneLang.CIrGen

/// IR generation context.
[<RequireQualifiedAccess>]
type Ctx =
  {
    VarSerial: int
    Decls: CDecl list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): Ctx =
  {
    VarSerial = tyCtx.VarSerial
    Decls = []
  }

let ctxRollBack _bCtx dCtx =
  dCtx

let ctxAddDecl (ctx: Ctx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let tyOf expr =
  Typing.tyOf expr

let cty ty: CTy =
  match ty with
  | Ty.Unit ->
    CTy.Void
  | Ty.Bool
  | Ty.Int ->
    CTy.Int
  | Ty.Str ->
    CTy.Ptr CTy.Char
  | Ty.Fun _ ->
    CTy.Ptr CTy.Void
  | Ty.Var _ ->
    failwith "Type vars must be resolved in type inference phase."

let ctyOf expr =
  cty (tyOf expr)

let cop op =
  match op with
  | Op.Add -> COp.Add
  | Op.Sub -> COp.Sub
  | Op.Mul -> COp.Mul
  | Op.Div -> COp.Div
  | Op.Mod -> COp.Mod
  | Op.Eq -> COp.Eq
  | Op.Ne -> COp.Ne
  | Op.Lt -> COp.Lt
  | Op.Le -> COp.Le
  | Op.Gt -> COp.Gt
  | Op.Ge -> COp.Ge
  | Op.And
  | Op.Or -> failwith "We don't use && || in C language"

let callPrintf format args =
  let format = CExpr.Str (format + "\\n")
  CStmt.Expr (CExpr.Call (CExpr.Prim CPrim.Printf, format :: args))

let uniqueName name serial =
  sprintf "%s_%d" name serial

let freshName (ctx: Ctx) (name: string) =
  let serial = ctx.VarSerial + 1
  let name = uniqueName name serial
  let ctx = { ctx with VarSerial = ctx.VarSerial + 1 }
  name, ctx

let freshVar (ctx: Ctx) (name: string) (ty: CTy) =
  let name, ctx = freshName ctx name
  name, CExpr.Ref name, ctx

let genOpExpr acc ctx op first second ty loc =
  match op with
  | Op.And ->
    // l && r ---> if l then r else false
    let falseLit = Expr.Ref ("false", 0, (Ty.Bool, loc))
    let expr = Expr.If (first, second, falseLit, (ty, loc))
    genExpr acc ctx expr
  | Op.Or ->
    // l || r ---> if l then true else r
    let trueLit = Expr.Ref ("true", 0, (Ty.Bool, loc))
    let expr = Expr.If (first, trueLit, second, (ty, loc))
    genExpr acc ctx expr
  | _ ->
    // Currently no support of non-int add/cmp/etc.
    let ty = CTy.Int
    let first, acc, ctx = genExpr acc ctx first
    let second, acc, ctx = genExpr acc ctx second
    let name, ctx = freshName ctx "op"
    let acc = CStmt.Let (name, ty, Some (CExpr.Op (cop op, first, second))) :: acc
    CExpr.Ref name, acc, ctx

let genCall acc ctx callee args ty =
  match args with
  | [arg] ->
    let callee, acc, ctx = genExpr acc ctx callee
    let arg, acc, ctx = genExpr acc ctx arg
    CExpr.Call (callee, [arg]), acc, ctx
  | [] ->
    failwith "Never zero-arg call"
  | _ ->
    failwith "unimpl call with 2+ args"

/// if pred then thenCl else elseCl ->
/// T result;
/// if (pred) { ..; result = thenCl; } else { ..; result = elseCl; }
/// ..(result)
let genIfExpr acc ctx pred thenCl elseCl ty =
  let resultName, result, ctx = freshVar ctx "if" (ctyOf thenCl)
  let pred, acc, ctx = genExpr acc ctx pred
  let thenCl, thenStmts, ctx = genExpr [] ctx thenCl
  let elseCl, elseStmts, ctx = genExpr [] ctx elseCl
  let thenStmts = CStmt.Expr (CExpr.Set (result, thenCl)) :: thenStmts
  let elseStmts = CStmt.Expr (CExpr.Set (result, elseCl)) :: elseStmts
  let acc = CStmt.Let (resultName, cty ty, None) :: acc
  let acc = CStmt.If (pred, List.rev thenStmts, List.rev elseStmts) :: acc
  result, acc, ctx

let genLetVal acc ctx pat init =
  match pat with
  | Pat.Ident (name, serial, (ty, _)) ->
    let name = uniqueName name serial
    let init, acc, ctx = genExpr acc ctx init
    let acc = CStmt.Let (name, cty ty, Some init) :: acc
    CExpr.Ref name, acc, ctx
  | _ ->
    failwith "In `let x = ..`, `x` must be an identifier for now."

let genLetFun acc ctx callee pats body =
  match callee, pats with
  | Pat.Ident (name, serial, (_, _)),
    [Pat.Ident (paramName, paramSerial, (paramTy, _))] ->
    let name = uniqueName name serial
    let result, body, ctx = genExpr [] ctx body
    let body = CStmt.Return (Some result) :: body
    let decl =
      CDecl.Fun {
        Name = name
        Params = [uniqueName paramName paramSerial, cty paramTy]
        Body = List.rev body
      }
    let ctx = ctxAddDecl ctx decl
    CExpr.Unit, acc, ctx
  | _ ->
    failwith "In `let f () = ..`, `f` must be an identifier for now."

let genExprList acc ctx exprs =
  let rec go results acc ctx exprs =
    match exprs with
    | [] -> List.rev results, ctx
    | expr :: exprs ->
      let result, acc, ctx = genExpr acc ctx expr
      go (result :: results) acc ctx exprs
  go [] acc ctx exprs

let genExpr
  (acc: CStmt list) (ctx: Ctx) (arg: Expr<Ty * Loc>)
  : CExpr * CStmt list * Ctx =
  match arg with
  | Expr.Begin ([], _)
  | Expr.Unit _ ->
    CExpr.Unit, acc, ctx
  | Expr.Int (value, _) ->
    CExpr.Int value, acc, ctx
  | Expr.String (value, _) ->
    CExpr.Str value, acc, ctx
  | Expr.Ref ("true", _, _) ->
    CExpr.Int 1, acc, ctx
  | Expr.Ref ("false", _, _) ->
    CExpr.Int 0, acc, ctx
  | Expr.Ref (name, serial, _) ->
    CExpr.Ref (uniqueName name serial), acc, ctx
  | Expr.If (pred, thenCl, elseCl, (ty, _)) ->
    genIfExpr acc ctx pred thenCl elseCl ty
  | Expr.Op (op, first, second, (ty, loc)) ->
    genOpExpr acc ctx op first second ty loc
  | Expr.Call (Expr.Prim (PrimFun.Printfn, _), (Expr.String (format, _)) :: args, _) ->
    let args, ctx = genExprList acc ctx args
    let acc = callPrintf format args :: acc
    CExpr.Unit, acc, ctx
  | Expr.Call (callee, args, (ty, _)) ->
    genCall acc ctx callee args ty
  | Expr.Let ([pat], init, _) ->
    genLetVal acc ctx pat init
  | Expr.Let (callee :: pats, body, _) ->
    genLetFun acc ctx callee pats body
  | Expr.Begin (expr :: exprs, _) ->
    let rec go acc ctx expr exprs =
      match genExpr acc ctx expr, exprs with
      | (result, acc, ctx), [] ->
        result, acc, ctx
      | (_, acc, ctx), expr :: exprs ->
        go acc ctx expr exprs
    go acc ctx expr exprs
  | Expr.Let ([], _, _) ->
    failwith "Never zero-patterns let"
  | Expr.Prim _
  | Expr.Call _
  | Expr.Let _ ->
    failwithf "unimpl %A" arg

let gen (exprs: Expr<Ty * _> list, tyCtx: Typing.TyCtx): CDecl list =
  let ctx = ctxFromTyCtx tyCtx
  match exprs with
  | [Expr.Let ([Pat.Ident ("main", serial, _); Pat.Unit _], body, _)] ->
    let result, acc, bodyCtx = genExpr [] ctx body
    let ctx = ctxRollBack ctx bodyCtx
    let acc = CStmt.Return (Some result) :: acc
    let decl =
      CDecl.Fun {
        Name = "main"
        Params = []
        Body = List.rev acc
      }
    List.rev (decl :: ctx.Decls)
  | _ ->
    failwith "unimpl"
