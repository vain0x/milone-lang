module rec MiloneLang.Mir

type TyCtx = Typing.TyCtx

let exprExtract = Parsing.exprExtract

let exprTy = exprExtract >> fst

let exprLoc = exprExtract >> snd

let patTy = Typing.patTy

let patExtract = Parsing.patExtract

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    VarSerial: int
    VarName: Map<int, string>
    Decls: MDecl<MTy * Loc> list
    Stmts: MStmt<MTy * Loc> list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  {
    VarSerial = tyCtx.VarSerial
    VarName = tyCtx.VarName
    Decls = []
    Stmts = []
  }

let ctxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddDecl (ctx: MirCtx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddStmt (ctx: MirCtx) (stmt: MStmt<_>) =
  { ctx with Stmts = stmt :: ctx.Stmts }

/// Returns statements in reversed order.
let ctxTakeStmts (ctx: MirCtx) =
  ctx.Stmts, { ctx with Stmts = [] }

let ctxFreshVar (ctx: MirCtx) (ident: string) (ty, loc) =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarName = ctx.VarName |> Map.add serial ident
    }
  let refExpr = MExpr.Ref (serial, (ty, loc))
  refExpr, serial, ctx

let ctxLetFreshVar (ctx: MirCtx) (ident: string) (ty: MTy, loc) =
  let refExpr, serial, ctx = ctxFreshVar ctx ident (ty, loc)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, None, (ty, loc)))
  let setStmt expr = MStmt.Set (serial, expr, (ty, loc))
  refExpr, setStmt, ctx

let opIsComparison op =
  match op with
  | MOp.Eq
  | MOp.Ne
  | MOp.Lt
  | MOp.Le
  | MOp.Gt
  | MOp.Ge ->
    true
  | _ ->
    false

let mopFrom op =
  match op with
  | Op.Add -> MOp.Add
  | Op.Sub -> MOp.Sub
  | Op.Mul -> MOp.Mul
  | Op.Div -> MOp.Div
  | Op.Mod -> MOp.Mod
  | Op.Eq -> MOp.Eq
  | Op.Ne -> MOp.Ne
  | Op.Lt -> MOp.Lt
  | Op.Le -> MOp.Le
  | Op.Gt -> MOp.Gt
  | Op.Ge -> MOp.Ge
  | Op.And
  | Op.Or
  | Op.Tie -> failwith "We don't use '&&' '||' ',' in MIR"

let unboxTy (ty: Ty): MTy =
  match ty with
  | Ty.Unit -> MTy.Unit
  | Ty.Bool -> MTy.Bool
  | Ty.Int -> MTy.Int
  | Ty.Str -> MTy.Str
  | Ty.Fun (lTy, rTy) ->
    MTy.Fun (unboxTy lTy, unboxTy rTy)
  | Ty.Tuple (lTy, rTy) ->
    MTy.Tuple (unboxTy lTy, unboxTy rTy)
  | Ty.Var _ ->
    failwith "Never type variable here."

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.Proj (expr, index, (unboxTy resultTy, loc))

let mirifyPat ctx (pat: Pat<Ty * Loc>) (expr: MExpr<_>): MirCtx =
  match pat with
  | Pat.Unit (_, loc) ->
    ctxAddStmt ctx (MStmt.Expr (expr, (MTy.Unit, loc)))
  | Pat.Ident (_, serial, (ty, loc)) ->
    ctxAddStmt ctx (MStmt.LetVal (serial, Some expr, (unboxTy ty, loc)))
  | Pat.Tuple (l, r, (_, loc)) ->
    let fstExpr = projExpr expr 0 (patTy l) loc
    let sndExpr = projExpr expr 1 (patTy r) loc
    let ctx = mirifyPat ctx l fstExpr
    let ctx = mirifyPat ctx r sndExpr
    ctx
  | Pat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

let mirifyExprIf ctx pred thenCl elseCl (ty, loc) =
  let ty = unboxTy ty
  let temp, tempSet, ctx = ctxLetFreshVar ctx "if" (ty, loc)

  let pred, ctx = mirifyExpr ctx pred
  // Mirify clauses each in new block.
  // Blocks end with the statement to set the result to the temp var.
  let thenCl, thenVal, ctx = mirifyBlock ctx thenCl
  let thenCl = tempSet thenVal :: thenCl |> List.rev
  let elseCl, elseVal, ctx = mirifyBlock ctx elseCl
  let elseCl = tempSet elseVal :: elseCl |> List.rev

  let ifStmt = MStmt.If (pred, thenCl, elseCl, (MTy.Unit, loc))
  let ctx = ctxAddStmt ctx ifStmt
  temp, ctx

let mirifyExprIndex ctx l r ty loc =
  match exprTy l, ty with
  | Ty.Str, Ty.Int ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Index (l, r, (MTy.Int, loc)), ctx
  | _ ->
    failwith "unimpl non-string indexing"

/// fst a ==> unbox 0 a
let mirifyExprCallFst ctx _calleeLoc arg (ty, callLoc) =
  let arg, ctx = mirifyExpr ctx arg
  projExpr arg 0 ty callLoc, ctx

let mirifyExprCall ctx callee args (ty, loc) =
  let ty = unboxTy ty
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = mirifyExprs ctx args
  let callExpr = MExpr.Call (callee, args, (ty, loc))

  let temp, tempSerial, ctx = ctxFreshVar ctx "call" (ty, loc)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, Some callExpr, (ty, loc)))
  temp, ctx

/// l && r ==> if l then r else false
let mirifyExprOpAnd ctx l r (ty, loc) =
  let falseExpr = Expr.Bool (false, (ty, loc))
  mirifyExprIf ctx l r falseExpr (ty, loc)

/// l || r ==> if l then true else r
let mirifyExprOpOr ctx l r (ty, loc) =
  let trueExpr = Expr.Bool (true, (ty, loc))
  mirifyExprIf ctx l trueExpr r (ty, loc)

/// Creates a tuple inside a box.
let mirifyExprOpTie ctx l r (ty, loc) =
  let lTy, rTy =
    match ty with
    | Ty.Tuple (lTy, rTy) -> unboxTy lTy, unboxTy rTy
    | _ -> failwith "Tuple constructor's type must be a tuple."
  let lLoc, rLoc = exprLoc l, exprLoc r

  let ty = MTy.Tuple (lTy, rTy)
  let _, tempSerial, ctx = ctxFreshVar ctx "tuple" (ty, loc)

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let elems = [l, (lTy, lLoc); r, (rTy, rLoc)]
  let ctx = ctxAddStmt ctx (MStmt.LetTuple (tempSerial, elems, (ty, loc)))
  MExpr.Ref (tempSerial, (ty, loc)), ctx

/// x op y ==> `x op y` if `x : int`
/// C language supports all operators.
let mirifyExprOpInt ctx op l r (ty, loc) =
  let opExpr = MExpr.Op (op, l, r, (ty, loc))
  opExpr, ctx

let mirifyExprOpStrAdd ctx _op l r (_, loc) =
  let tyStrStrStr = MTy.Fun (MTy.Str, MTy.Fun (MTy.Str, MTy.Str))
  let strAdd = MExpr.Prim (MPrim.StrAdd, (tyStrStrStr, loc))
  let strAddExpr = MExpr.Call (strAdd, [l; r], (MTy.Str, loc))
  strAddExpr, ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let mirifyExprOpStrCmp ctx op l r (ty, loc) =
  let strCmp = MExpr.Prim (MPrim.StrCmp, (MTy.Fun (MTy.Str, MTy.Int), loc))
  let strCmpExpr = MExpr.Call (strCmp, [l; r], (MTy.Int, loc))
  let zeroExpr = MExpr.Int (0, (MTy.Int, loc))
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, (ty, loc))
  opExpr, ctx

let mirifyExprOp ctx op l r (ty, loc) =
  let ty, lTy = unboxTy ty, exprTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  match lTy with
  | Ty.Int ->
    mirifyExprOpInt ctx op l r (ty, loc)
  | Ty.Str when op = MOp.Add ->
    mirifyExprOpStrAdd ctx op l r (ty, loc)
  | Ty.Str when opIsComparison op ->
    mirifyExprOpStrCmp ctx op l r (ty, loc)
  | _ ->
    failwithf "unimpl"

let mirifyExprAndThen ctx exprs _ =
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprLetVal ctx pat init (_, letLoc) =
  let init, ctx = mirifyExpr ctx init
  let ctx = mirifyPat ctx pat init
  MExpr.Unit (MTy.Unit, letLoc), ctx

let mirifyExprLetFun ctx pat pats body (_, letLoc) =
  let letA = MTy.Unit, letLoc

  let defineArgs ctx argPat =
    match argPat with
    | Pat.Ident (_, serial, (ty, loc)) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      [serial, (unboxTy ty, loc)], ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let argTy = unboxTy argTy
      let arg, argSerial, ctx = ctxFreshVar ctx "arg" (argTy, argLoc)
      let args = [argSerial, (argTy, argLoc)]
      let ctx = mirifyPat ctx argPat arg
      args, ctx

  let mirifyFunBody ctx argPat body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs ctx argPat
    let lastExpr, ctx = mirifyExpr ctx body
    let returnStmt = MStmt.Return (lastExpr, (MTy.Unit, blockLoc))
    let ctx = ctxAddStmt ctx returnStmt

    let stmts, ctx = ctxTakeStmts ctx
    let body = List.rev stmts
    args, unboxTy blockTy, body, ctx

  match pat, pats with
  | Pat.Ident (_, calleeSerial, (_, _)),
    [argPat] ->
    let bodyCtx = ctxNewBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPat body
    let ctx = ctxRollBack ctx bodyCtx
    let decl = MDecl.LetFun (calleeSerial, args, resultTy, body, letA)
    let ctx = ctxAddDecl ctx decl
    MExpr.Unit letA, ctx
  | _ ->
    failwith "First pattern of `let` for function must be an identifier."

let mirifyExpr (ctx: MirCtx) (expr: Expr<Ty * Loc>): MExpr<MTy * Loc> * MirCtx =
  match expr with
  | Expr.Unit (_, loc) ->
    MExpr.Unit (MTy.Unit, loc), ctx
  | Expr.Bool (value, (_, loc)) ->
    MExpr.Bool (value, (MTy.Bool, loc)), ctx
  | Expr.Int (value, (_, loc)) ->
    MExpr.Int (value, (MTy.Int, loc)), ctx
  | Expr.Str (value, (_, loc)) ->
    MExpr.Str (value, (MTy.Str, loc)), ctx
  | Expr.Prim (PrimFun.Printfn, (ty, loc)) ->
    MExpr.Prim (MPrim.Printfn, (unboxTy ty, loc)), ctx // FIXME: boxTy?
  | Expr.Ref (_, serial, (ty, loc)) ->
    MExpr.Ref (serial, (unboxTy ty, loc)), ctx
  | Expr.If (pred, thenCl, elseCl, (ty, loc)) ->
    mirifyExprIf ctx pred thenCl elseCl (ty, loc)
  | Expr.Index (l, r, (ty, loc)) ->
    mirifyExprIndex ctx l r ty loc
  | Expr.Call (Expr.Prim (PrimFun.Fst, (_, calleeLoc)), [arg], a) ->
    mirifyExprCallFst ctx calleeLoc arg a
  | Expr.Call (callee, args, a) ->
    mirifyExprCall ctx callee args a
  | Expr.Op (Op.And, l, r, a) ->
    mirifyExprOpAnd ctx l r a
  | Expr.Op (Op.Or, l, r, a) ->
    mirifyExprOpOr ctx l r a
  | Expr.Op (Op.Tie, l, r, a) ->
    mirifyExprOpTie ctx l r a
  | Expr.Op (op, l, r, a) ->
    mirifyExprOp ctx (mopFrom op) l r a
  | Expr.AndThen (exprs, a) ->
    mirifyExprAndThen ctx exprs a
  | Expr.Let ([pat], init, a) ->
    mirifyExprLetVal ctx pat init a
  | Expr.Let (pat :: pats, body, a) ->
    mirifyExprLetFun ctx pat pats body a
  | Expr.Call (_, [], _)
  | Expr.Anno _
  | Expr.Prim (PrimFun.Fst, _)
  | Expr.Let ([], _, _) ->
    failwith "Never"

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, ctx
    | expr :: exprs ->
      let expr, ctx = mirifyExpr ctx expr
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let mirify (exprs: Expr<Ty * Loc> list, tyCtx: TyCtx): MirCtx =
  let ctx = ctxFromTyCtx tyCtx
  let _exprs, ctx = mirifyExprs ctx exprs
  assert (List.isEmpty ctx.Stmts)
  ctx
