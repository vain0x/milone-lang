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
    LabelSerial: int
    Decls: MDecl<Loc> list
    Stmts: MStmt<Loc> list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  {
    VarSerial = tyCtx.VarSerial
    VarName = tyCtx.VarName
    LabelSerial = 0
    Decls = []
    Stmts = []
  }

let ctxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddDecl (ctx: MirCtx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddStmt (ctx: MirCtx) (stmt: MStmt<Loc>) =
  { ctx with Stmts = stmt :: ctx.Stmts }

/// Returns statements in reversed order.
let ctxTakeStmts (ctx: MirCtx) =
  ctx.Stmts, { ctx with Stmts = [] }

let ctxFreshVar (ctx: MirCtx) (ident: string) (ty: MTy) loc =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        VarName = ctx.VarName |> Map.add serial ident
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
  refExpr, serial, ctx

let ctxLetFreshVar (ctx: MirCtx) (ident: string) (ty: MTy) loc =
  let refExpr, serial, ctx = ctxFreshVar ctx ident ty loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, None, ty, loc))
  let setStmt expr = MStmt.Set (serial, expr, loc)
  refExpr, setStmt, ctx

let ctxFreshLabel (ctx: MirCtx) (ident: string) loc =
  let serial = ctx.LabelSerial + 1
  let ctx = { ctx with LabelSerial = ctx.LabelSerial + 1 }
  let ident = sprintf "%s_%d" ident serial
  let labelStmt = MStmt.Label (ident, loc)
  labelStmt, ident, ctx

let opIsComparison op =
  match op with
  | MOp.Eq
  | MOp.Ne
  | MOp.Lt
  | MOp.Le ->
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
  | Op.Gt
  | Op.Ge
  | Op.And
  | Op.Or
  | Op.Cons
  | Op.Tie -> failwith "We don't use > >= && || :: , in MIR"

let mexprExtract expr =
  match expr with
  | MExpr.Unit (ty, loc) -> ty, loc
  | MExpr.Bool (_, loc) -> MTy.Bool, loc
  | MExpr.Int (_, loc) -> MTy.Int, loc
  | MExpr.Str (_, loc) -> MTy.Str, loc
  | MExpr.Nil (itemTy, loc) -> MTy.List itemTy, loc
  | MExpr.Prim (_, loc) -> MTy.Unit, loc // FIXME: incorrect type
  | MExpr.Ref (_, ty, loc) -> ty, loc
  | MExpr.ListIsEmpty (_, itemTy, loc) -> MTy.List itemTy, loc
  | MExpr.ListHead (_, itemTy, loc) -> MTy.List itemTy, loc
  | MExpr.ListTail (_, itemTy, loc) -> MTy.List itemTy, loc
  | MExpr.Proj (_, _, elemTy, loc) -> elemTy, loc
  | MExpr.Index (_, _, ty, loc) -> ty, loc
  | MExpr.Call (_, _, ty, loc) -> ty, loc
  | MExpr.UniOp (_, _, ty, loc) -> ty, loc
  | MExpr.Op (_, _, _, ty, loc) -> ty, loc

let mexprTy expr =
  let ty, _ = mexprExtract expr
  ty

let unboxTy (ty: Ty): MTy =
  match ty with
  | Ty.Unit -> MTy.Unit
  | Ty.Bool -> MTy.Bool
  | Ty.Int -> MTy.Int
  | Ty.Str -> MTy.Str
  | Ty.Fun (lTy, rTy) ->
    MTy.Fun (unboxTy lTy, unboxTy rTy)
  | Ty.List ty ->
    MTy.List (unboxTy ty)
  | Ty.Tuple (lTy, rTy) ->
    MTy.Tuple (unboxTy lTy, unboxTy rTy)
  | Ty.Var _ ->
    failwith "Never type variable here."

let listItemTy ty =
  match ty with
  | Ty.List ty ->
    unboxTy ty
  | _ ->
    failwith "List constructor's type must be a list."

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.Proj (expr, index, unboxTy resultTy, loc)

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let itemTy = unboxTy itemTy
  let isEmpty = MExpr.ListIsEmpty (expr, itemTy, loc)
  let nonEmpty = MExpr.UniOp (MUniOp.Not, isEmpty, MTy.Bool, loc)
  let gotoStmt = MStmt.GotoUnless (nonEmpty, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  let head = MExpr.ListHead (expr, itemTy, loc)
  let tail = MExpr.ListTail (expr, itemTy, loc)
  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
/// Determines if the pattern covers the whole.
let mirifyPat ctx (endLabel: string) (pat: Pat<Ty * Loc>) (expr: MExpr<Loc>): bool * MirCtx =
  match pat with
  | Pat.Unit _
  | Pat.Ident ("_", _, _) ->
    // Discard result.
    true, ctx
  | Pat.Int (value, (_, loc)) ->
    let intExpr = MExpr.Int (value, loc)
    let eqExpr = MExpr.Op (MOp.Eq, expr, intExpr, MTy.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | Pat.Nil (Ty.List itemTy, loc) ->
    let isEmptyExpr = MExpr.ListIsEmpty (expr, unboxTy itemTy, loc)
    let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | Pat.Ident (_, serial, (ty, loc)) ->
    let letStmt = MStmt.LetVal (serial, Some expr, unboxTy ty, loc)
    true, ctxAddStmt ctx letStmt
  | Pat.Cons (l, r, (Ty.List itemTy, loc)) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | Pat.Tuple (l, r, (_, loc)) ->
    let fstExpr = projExpr expr 0 (patTy l) loc
    let sndExpr = projExpr expr 1 (patTy r) loc
    let lCovered, ctx = mirifyPat ctx endLabel l fstExpr
    let rCovered, ctx = mirifyPat ctx endLabel r sndExpr
    let covered = lCovered && rCovered
    covered, ctx
  | Pat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."
  | Pat.Nil _
  | Pat.Cons _ ->
    failwith "Never nil/cons patterns must be of list type."

let desugarExprList items a =
  let rec go acc items =
    match items with
    | [] ->
      acc
    | item :: items ->
      go (Expr.Op (Op.Cons, item, acc, a)) items
  go (Expr.List ([], a)) (List.rev items)

/// `[a; b; c]` -> `a :: b :: c :: []`
let mirifyExprList ctx items a =
  mirifyExpr ctx (desugarExprList items a)

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

let mirifyExprIf ctx pred thenCl elseCl (ty, loc) =
  let ty = unboxTy ty
  let temp, tempSet, ctx = ctxLetFreshVar ctx "if" ty loc
  let elseLabelStmt, elseLabel, ctx = ctxFreshLabel ctx "else" loc
  let endLabelStmt, endLabel, ctx = ctxFreshLabel ctx "end_if" loc

  let pred, ctx = mirifyExpr ctx pred
  // if not pred then goto else
  let ctx = ctxAddStmt ctx (MStmt.GotoUnless (pred, elseLabel, loc))
  let thenVal, ctx = mirifyExpr ctx thenCl
  let ctx = ctxAddStmt ctx (tempSet thenVal)
  // goto end_if
  let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))

  // else:
  let ctx = ctxAddStmt ctx elseLabelStmt
  let elseVal, ctx = mirifyExpr ctx elseCl
  let ctx = ctxAddStmt ctx (tempSet elseVal)
  // end_if:
  let ctx = ctxAddStmt ctx endLabelStmt

  temp, ctx

let mstmtExit (ty: MTy) loc =
  let exitFun = MExpr.Prim (MPrim.Exit, loc)
  let one = MExpr.Int (1, loc)
  let callExpr = MExpr.Call (exitFun, [one], ty, loc)
  MStmt.Expr (callExpr, loc)

let mirifyExprMatch ctx target (pat1, body1) (pat2, body2) (ty, loc) =
  let ty = unboxTy ty
  let temp, tempSet, ctx = ctxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = ctxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  // First arm.
  let nextLabelStmt, nextLabel, ctx = ctxFreshLabel ctx "next" loc
  let cover1, ctx = mirifyPat ctx nextLabel pat1 target
  let body, ctx = mirifyExpr ctx body1
  let ctx = ctxAddStmt ctx (tempSet body)
  let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))
  let ctx = ctxAddStmt ctx nextLabelStmt

  // Second, last arm.
  let nextLabelStmt, nextLabel, ctx = ctxFreshLabel ctx "next" loc
  let cover2, ctx = mirifyPat ctx nextLabel pat2 target
  let body, ctx = mirifyExpr ctx body2
  let ctx = ctxAddStmt ctx (tempSet body)
  let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))

  // Exhaust case (unless covered).
  let ctx =
    if cover1 || cover2 then ctx else
      let ctx = ctxAddStmt ctx nextLabelStmt
      let ctx = ctxAddStmt ctx (mstmtExit ty loc)
      ctx

  // End of match.
  let ctx = ctxAddStmt ctx endLabelStmt
  temp, ctx

let mirifyExprIndex ctx l r ty loc =
  match exprTy l, ty with
  | Ty.Str, Ty.Int ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Index (l, r, MTy.Int, loc), ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx exitLoc arg (ty, loc) =
  let arg, ctx = mirifyExpr ctx arg
  let callee = MExpr.Prim (MPrim.Exit, exitLoc)
  let callExpr = MExpr.Call (callee, [arg], unboxTy ty, loc)
  let ctx = ctxAddStmt ctx (MStmt.Expr (callExpr, loc))
  MExpr.Unit (unboxTy ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg (ty, notLoc) =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Not, arg, unboxTy ty, notLoc), ctx

let mirifyExprCall ctx callee args (ty, loc) =
  let ty = unboxTy ty
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = mirifyExprs ctx args
  let callExpr = MExpr.Call (callee, args, ty, loc)

  let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, Some callExpr, ty, loc))
  temp, ctx

/// l && r ==> if l then r else false
let mirifyExprOpAnd ctx l r (ty, loc) =
  let falseExpr = Expr.Bool (false, (ty, loc))
  mirifyExprIf ctx l r falseExpr (ty, loc)

/// l || r ==> if l then true else r
let mirifyExprOpOr ctx l r (ty, loc) =
  let trueExpr = Expr.Bool (true, (ty, loc))
  mirifyExprIf ctx l trueExpr r (ty, loc)

let mirifyExprOpCons ctx l r (ty, loc) =
  let itemTy = listItemTy ty
  let listTy = MTy.List itemTy
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetCons (tempSerial, l, r, itemTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

/// Creates a tuple inside a box.
let mirifyExprOpTie ctx l r (ty, loc) =
  let lTy, rTy =
    match ty with
    | Ty.Tuple (lTy, rTy) -> unboxTy lTy, unboxTy rTy
    | _ -> failwith "Tuple constructor's type must be a tuple."
  let lLoc, rLoc = exprLoc l, exprLoc r

  let ty = MTy.Tuple (lTy, rTy)
  let _, tempSerial, ctx = ctxFreshVar ctx "tuple" ty loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let elems = [l; r]
  let ctx = ctxAddStmt ctx (MStmt.LetTuple (tempSerial, elems, ty, loc))
  MExpr.Ref (tempSerial, ty, loc), ctx

/// x op y ==> `x op y` if `x : int`
/// C language supports all operators.
let mirifyExprOpInt ctx op l r (ty, loc) =
  let opExpr = MExpr.Op (op, l, r, ty, loc)
  opExpr, ctx

let mirifyExprOpStrAdd ctx _op l r (_, loc) =
  let strAdd = MExpr.Prim (MPrim.StrAdd, loc)
  let strAddExpr = MExpr.Call (strAdd, [l; r], MTy.Str, loc)
  strAddExpr, ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let mirifyExprOpStrCmp ctx op l r (ty, loc) =
  let strCmp = MExpr.Prim (MPrim.StrCmp, loc)
  let strCmpExpr = MExpr.Call (strCmp, [l; r], MTy.Int, loc)
  let zeroExpr = MExpr.Int (0, loc)
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

let mirifyExprOp ctx op l r a =
  match op with
  | Op.And ->
    mirifyExprOpAnd ctx l r a
  | Op.Or ->
    mirifyExprOpOr ctx l r a
  | Op.Cons ->
    mirifyExprOpCons ctx l r a
  | Op.Tie ->
    mirifyExprOpTie ctx l r a
  | _ ->

  let op, l, r =
    match op with
    | Op.Gt -> MOp.Lt, r, l
    | Op.Ge -> MOp.Le, r, l
    | _ -> mopFrom op, l, r

  let ty, loc = a
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
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprLetVal ctx pat init letLoc =
  let init, ctx = mirifyExpr ctx init
  match mirifyPat ctx "_never_" pat init with
  | true, ctx ->
    MExpr.Unit (MTy.Unit, letLoc), ctx
  | false, _ ->
    failwithf "Let pattern must be exhaustive for now %A" pat

let mirifyExprLetFun ctx pat pats body (_, letLoc) =
  let defineArg ctx argPat =
    match argPat with
    | Pat.Ident (_, serial, (ty, loc)) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      (serial, unboxTy ty, loc), ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let argTy = unboxTy argTy
      let arg, argSerial, ctx = ctxFreshVar ctx "arg" argTy argLoc
      match mirifyPat ctx "_never_" argPat arg with
      | true, ctx ->
        (argSerial, argTy, argLoc), ctx
      | false, _ ->
        failwithf "Argument pattern must be exhaustive for now: %A" argPat

  let rec defineArgs acc ctx argPats =
    match argPats with
    | [] ->
      List.rev acc, ctx
    | argPat :: argPats ->
      let arg, ctx = defineArg ctx argPat
      defineArgs (arg :: acc) ctx argPats

  let mirifyFunBody ctx argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let lastExpr, ctx = mirifyExpr ctx body
    let returnStmt = MStmt.Return (lastExpr, blockLoc)
    let ctx = ctxAddStmt ctx returnStmt

    let stmts, ctx = ctxTakeStmts ctx
    let body = List.rev stmts
    args, unboxTy blockTy, body, ctx

  match pat, pats with
  | Pat.Ident (_, calleeSerial, (_, _)), argPats ->
    let bodyCtx = ctxNewBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = ctxRollBack ctx bodyCtx
    let decl = MDecl.LetFun (calleeSerial, args, resultTy, body, letLoc)
    let ctx = ctxAddDecl ctx decl
    MExpr.Unit (MTy.Unit, letLoc), ctx
  | _ ->
    failwith "First pattern of `let` for function must be an identifier."

let mirifyExpr (ctx: MirCtx) (expr: Expr<Ty * Loc>): MExpr<Loc> * MirCtx =
  match expr with
  | Expr.Unit (_, loc) ->
    MExpr.Unit (MTy.Unit, loc), ctx
  | Expr.Bool (value, (_, loc)) ->
    MExpr.Bool (value, loc), ctx
  | Expr.Int (value, (_, loc)) ->
    MExpr.Int (value, loc), ctx
  | Expr.Str (value, (_, loc)) ->
    MExpr.Str (value, loc), ctx
  | Expr.Prim (PrimFun.Printfn, (_, loc)) ->
    MExpr.Prim (MPrim.Printfn, loc), ctx
  | Expr.Ref (_, serial, (ty, loc)) ->
    MExpr.Ref (serial, unboxTy ty, loc), ctx
  | Expr.List ([], (Ty.List ty, loc)) ->
    MExpr.Nil (unboxTy ty, loc), ctx
  | Expr.List (items, a) ->
    mirifyExprList ctx items a
  | Expr.If (pred, thenCl, elseCl, (ty, loc)) ->
    mirifyExprIf ctx pred thenCl elseCl (ty, loc)
  | Expr.Match (target, arm1, arm2, a) ->
    mirifyExprMatch ctx target arm1 arm2 a
  | Expr.Index (l, r, (ty, loc)) ->
    mirifyExprIndex ctx l r ty loc
  | Expr.Call (Expr.Ref ("not", -1, _), [arg], a) ->
    mirifyExprCallNot ctx arg a
  | Expr.Call (Expr.Prim (PrimFun.Exit, (_, exitLoc)), [arg], a) ->
    mirifyExprCallExit ctx exitLoc arg a
  | Expr.Call (callee, args, a) ->
    mirifyExprCall ctx callee args a
  | Expr.Op (op, l, r, a) ->
    mirifyExprOp ctx op l r a
  | Expr.AndThen (exprs, a) ->
    mirifyExprAndThen ctx exprs a
  | Expr.Let ([pat], init, (_, letLoc)) ->
    mirifyExprLetVal ctx pat init letLoc
  | Expr.Let (pat :: pats, body, a) ->
    mirifyExprLetFun ctx pat pats body a
  | Expr.List ([], _)
  | Expr.Prim (PrimFun.Exit, _)
  | Expr.Call (_, [], _)
  | Expr.Anno _
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
