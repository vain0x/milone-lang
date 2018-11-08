module rec MiloneLang.Mir

open MiloneLang.Helpers

type TyCtx = Typing.TyCtx

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    VarSerial: int
    Vars: Map<int, string * ValueIdent * MTy * Loc>
    Tys: Map<int, string * TyDef * Loc>
    LabelSerial: int
    Decls: MDecl<Loc> list
    Stmts: MStmt<Loc> list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  let vars =
    tyCtx.Vars |> Map.map (fun _ (ident, valueIdent, ty, loc) ->
      let ty = unboxTy (Typing.substTy tyCtx ty)
      ident, valueIdent, ty, loc
    )
  {
    VarSerial = tyCtx.VarSerial
    Vars = vars
    Tys = tyCtx.Tys
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
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
  refExpr, serial, ctx

let ctxLetFreshVar (ctx: MirCtx) (ident: string) (ty: MTy) loc =
  let refExpr, serial, ctx = ctxFreshVar ctx ident ty loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, MInit.UnInit, ty, loc))
  let setStmt expr = MStmt.Set (serial, expr, loc)
  refExpr, setStmt, ctx

let ctxFreshLabel (ctx: MirCtx) (ident: string) loc =
  let serial = ctx.LabelSerial + 1
  let ctx = { ctx with LabelSerial = ctx.LabelSerial + 1 }
  let ident = sprintf "%s_%d" ident serial
  let labelStmt = MStmt.Label (ident, loc)
  labelStmt, ident, ctx

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
  | Op.Pipe
  | Op.And
  | Op.Or
  | Op.Cons
  | Op.Range -> failwith "We don't use > >= && || :: .. in MIR"

let unboxTy (ty: Ty): MTy =
  match ty with
  | Ty.Unit -> MTy.Unit
  | Ty.Bool -> MTy.Bool
  | Ty.Int -> MTy.Int
  | Ty.Char -> MTy.Char
  | Ty.Str -> MTy.Str
  | Ty.Box -> MTy.Box
  | Ty.Fun (lTy, rTy) ->
    MTy.Fun (unboxTy lTy, unboxTy rTy)
  | Ty.List ty ->
    MTy.List (unboxTy ty)
  | Ty.Tuple itemTys ->
    MTy.Tuple (List.map unboxTy itemTys)
  | Ty.Ref (_, serial) ->
    MTy.Ref serial
  | Ty.Error ->
    failwith "Never type error in MIR"
  | Ty.Var _ ->
    failwith "Never type variable in MIR."
  | Ty.Range ->
    failwith "Never range as object in MIR."

let listItemTy ty =
  match ty with
  | Ty.List ty ->
    unboxTy ty
  | _ ->
    failwith "List constructor's type must be a list."

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.UniOp (MUniOp.Proj index, expr, unboxTy resultTy, loc)

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let itemTy = unboxTy itemTy
  let listTy = MTy.List itemTy
  let isEmpty = MExpr.UniOp (MUniOp.ListIsEmpty, expr, MTy.Bool, loc)
  let nonEmpty = MExpr.UniOp (MUniOp.Not, isEmpty, MTy.Bool, loc)
  let gotoStmt = MStmt.GotoUnless (nonEmpty, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  let head = MExpr.UniOp (MUniOp.ListHead, expr, itemTy, loc)
  let tail = MExpr.UniOp (MUniOp.ListTail, expr, listTy, loc)
  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
/// Determines if the pattern covers the whole.
let mirifyPat ctx (endLabel: string) (pat: Pat<Loc>) (expr: MExpr<Loc>): bool * MirCtx =
  match pat with
  | Pat.Unit _
  | Pat.Ref ("_", _, _, _) ->
    // Discard result.
    true, ctx
  | Pat.Lit (Lit.Int value, loc) ->
    let intExpr = MExpr.Lit (Lit.Int value, loc)
    let eqExpr = MExpr.Op (MOp.Eq, expr, intExpr, MTy.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | Pat.Nil (itemTy, loc) ->
    let isEmptyExpr = MExpr.UniOp (MUniOp.ListIsEmpty, expr, unboxTy (Ty.List itemTy), loc)
    let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | Pat.Ref (_, serial, ty, loc) ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, unboxTy ty, loc)
    true, ctxAddStmt ctx letStmt
  | Pat.Cons (l, r, itemTy, loc) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | Pat.Tuple (itemPats, Ty.Tuple itemTys, loc) ->
    let rec go covered ctx i itemPats itemTys =
      match itemPats, itemTys with
      | [], [] ->
        covered, ctx
      | itemPat :: itemPats, itemTy :: itemTys ->
        let item = projExpr expr i itemTy loc
        let itemCovered, ctx = mirifyPat ctx endLabel itemPat item
        go (covered && itemCovered) ctx (i + 1) itemPats itemTys
      | _ ->
        failwith "Never"
    go true ctx 0 itemPats itemTys
  | Pat.Lit _ ->
    failwith "unimpl"
  | Pat.Tuple _ ->
    failwith "Never: Tuple pattern must be of tuple type."
  | Pat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."

let mirifyExprRef (ctx: MirCtx) serial ty loc =
  match ctx.Vars |> Map.tryFind serial with
  | Some (_, ValueIdent.Variant tySerial, _, _) ->
    MExpr.Variant (tySerial, serial, unboxTy ty, loc), ctx
  | _ ->
    MExpr.Ref (serial, unboxTy ty, loc), ctx

let desugarExprList items itemTy loc =
  let rec go acc items =
    match items with
    | [] ->
      acc
    | item :: items ->
      go (Expr.Op (Op.Cons, item, acc, Ty.List itemTy, loc)) items
  go (Expr.List ([], itemTy, loc)) (List.rev items)

/// `[a; b; c]` -> `a :: b :: c :: []`
let mirifyExprList ctx items itemTy loc =
  mirifyExpr ctx (desugarExprList items itemTy loc)

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

let mirifyExprIf ctx pred thenCl elseCl ty loc =
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

/// exit(1);
let mstmtExit1 (ty: MTy) loc =
  let one = MExpr.Lit (Lit.Int 1, loc)
  let callExpr = MExpr.UniOp (MUniOp.Exit, one, ty, loc)
  MStmt.Do (callExpr, loc)

let mirifyExprMatch ctx target (pat1, body1) (pat2, body2) ty loc =
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
      let ctx = ctxAddStmt ctx (mstmtExit1 ty loc)
      ctx

  // End of match.
  let ctx = ctxAddStmt ctx endLabelStmt
  temp, ctx

let mirifyExprNav ctx sub mes ty loc =
  let subTy = exprTy sub
  let sub, ctx = mirifyExpr ctx sub
  match subTy, mes with
  | Ty.Str, "Length" ->
    MExpr.UniOp (MUniOp.StrLen, sub, MTy.Int, loc), ctx
  | _ ->
    failwithf "Never nav %A" (sub, mes, ty, loc)

let mirifyExprIndex ctx l r _ loc =
  match exprTy l, exprTy r with
  | Ty.Str, Ty.Int ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Op (MOp.StrIndex, l, r, MTy.Char, loc), ctx
  | Ty.Str, Ty.Range ->
    let rl, rr =
      match r with
      | Expr.Op (Op.Range, rl, rr, _, _) -> rl, rr
      | _ -> failwith "Never"
    let l, ctx = mirifyExpr ctx l
    let rl, ctx = mirifyExpr ctx rl
    let rr, ctx = mirifyExpr ctx rr
    let temp, tempSerial, ctx = ctxFreshVar ctx "slice" MTy.Str loc
    let strSliceRef = MExpr.Ref (SerialStrSlice, MTy.Unit, loc) // FIXME: wrong type
    let callInit = MInit.Call (strSliceRef, [l; rl; rr])
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, callInit, MTy.Str, loc))
    temp, ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let opExpr = MExpr.UniOp (MUniOp.Exit, arg, unboxTy ty, loc)
  let ctx = ctxAddStmt ctx (MStmt.Do (opExpr, loc))
  MExpr.Default (unboxTy ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "box" MTy.Box loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, MTy.Box, loc))
  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Unbox, arg, unboxTy ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Not, arg, unboxTy ty, notLoc), ctx

let mirifyExprCall ctx callee args ty loc =
  match callee, args with
  | Expr.Ref (_, serial, _, _), [arg] when serial = SerialNot ->
    mirifyExprCallNot ctx arg ty loc
  | Expr.Ref (_, serial, _, _), [arg] when serial = SerialExit ->
    mirifyExprCallExit ctx arg ty loc
  | Expr.Ref (_, serial, _, _), [arg] when serial = SerialBox ->
    mirifyExprCallBox ctx arg ty loc
  | Expr.Ref (_, serial, _, _), [arg] when serial = SerialUnbox ->
    mirifyExprCallUnbox ctx arg ty loc
  | _ ->
    let ty = unboxTy ty
    let callee, ctx = mirifyExpr ctx callee
    let args, ctx = mirifyExprs ctx args

    let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Call (callee, args), ty, loc))
    temp, ctx

/// l && r ==> if l then r else false
let mirifyExprOpAnd ctx l r ty loc =
  let falseExpr = Expr.Lit (Lit.Bool false, loc)
  mirifyExprIf ctx l r falseExpr ty loc

/// l || r ==> if l then true else r
let mirifyExprOpOr ctx l r ty loc =
  let trueExpr = Expr.Lit (Lit.Bool true, loc)
  mirifyExprIf ctx l trueExpr r ty loc

/// `x |> f` ==> `(f x)`
/// `x |> f a b ..` ==> `(f a b .. x)` (adhoc workaround)
let mirifyExprOpPipe ctx l r ty loc =
  match r with
  | Expr.Call (callee, args, ty, loc) ->
    mirifyExprCall ctx callee (args @ [l]) ty loc
  | _ ->
    mirifyExprCall ctx r [l] ty loc

let mirifyExprOpCons ctx l r ty loc =
  let itemTy = listItemTy ty
  let listTy = MTy.List itemTy
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r, itemTy), listTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items ty loc =
  let itemTys =
    match ty with
    | Ty.Tuple itemTys -> List.map unboxTy itemTys
    | _ -> failwith "Tuple constructor's type must be a tuple."
  let ty = MTy.Tuple itemTys
  let _, tempSerial, ctx = ctxFreshVar ctx "tuple" ty loc

  let rec go acc ctx items =
    match items with
    | [] ->
      List.rev acc, ctx
    | item :: items ->
      let item, ctx = mirifyExpr ctx item
      go (item :: acc) ctx items
  let items, ctx = go [] ctx items

  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Tuple items, ty, loc))
  MExpr.Ref (tempSerial, ty, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let mirifyExprOpScalar ctx op l r (ty, loc) =
  let opExpr = MExpr.Op (op, l, r, ty, loc)
  opExpr, ctx

let mirifyExprOpStrAdd ctx _op l r (_, loc) =
  let strAddExpr = MExpr.Op (MOp.StrAdd, l, r, MTy.Str, loc)
  strAddExpr, ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let mirifyExprOpStrCmp ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Op (MOp.StrCmp, l, r, MTy.Int, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

let mirifyExprOp ctx op l r ty loc =
  match op with
  | Op.And ->
    mirifyExprOpAnd ctx l r ty loc
  | Op.Or ->
    mirifyExprOpOr ctx l r ty loc
  | Op.Pipe ->
    mirifyExprOpPipe ctx l r ty loc
  | Op.Cons ->
    mirifyExprOpCons ctx l r ty loc
  | _ ->

  let op, l, r =
    match op with
    | Op.Gt -> MOp.Lt, r, l
    | Op.Ge -> MOp.Le, r, l
    | _ -> mopFrom op, l, r

  let ty, lTy = unboxTy ty, exprTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  match lTy with
  | Ty.Int
  | Ty.Char ->
    mirifyExprOpScalar ctx op l r (ty, loc)
  | Ty.Str when op = MOp.Add ->
    mirifyExprOpStrAdd ctx op l r (ty, loc)
  | Ty.Str when opIsComparison op ->
    mirifyExprOpStrCmp ctx op l r (ty, loc)
  | _ ->
    failwithf "unimpl"

let mirifyExprAndThen ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprLetVal ctx pat init letLoc =
  let init, ctx = mirifyExpr ctx init
  match mirifyPat ctx "_never_" pat init with
  | true, ctx ->
    MExpr.Default (MTy.Unit, letLoc), ctx
  | false, _ ->
    failwithf "Let pattern must be exhaustive for now %A" pat

let mirifyExprLetFun ctx pat pats body letLoc =
  let defineArg ctx argPat =
    match argPat with
    | Pat.Ref (_, serial, ty, loc) ->
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
  | Pat.Ref (_, calleeSerial, _, _), argPats ->
    let bodyCtx = ctxNewBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = ctxRollBack ctx bodyCtx
    let decl = MDecl.LetFun (calleeSerial, args, [], resultTy, body, letLoc)
    let ctx = ctxAddDecl ctx decl
    MExpr.Default (MTy.Unit, letLoc), ctx
  | _ ->
    failwith "First pattern of `let` for function must be an identifier."

let mirifyExprTyDef ctx tySerial tyDef loc =
  let ctx = ctxAddDecl ctx (MDecl.TyDef (tySerial, tyDef, loc))
  MExpr.Default (MTy.Unit, loc), ctx

let mirifyExpr (ctx: MirCtx) (expr: Expr<Loc>): MExpr<Loc> * MirCtx =
  match expr with
  | Expr.Lit (lit, loc) ->
    MExpr.Lit (lit, loc), ctx
  | Expr.Unit loc ->
    MExpr.Default (MTy.Unit, loc), ctx
  | Expr.Ref (_, serial, ty, loc) ->
    mirifyExprRef ctx serial ty loc
  | Expr.List ([], itemTy, loc) ->
    MExpr.Default (MTy.List (unboxTy itemTy), loc), ctx
  | Expr.List (items, itemTy, loc) ->
    mirifyExprList ctx items itemTy loc
  | Expr.If (pred, thenCl, elseCl, ty, loc) ->
    mirifyExprIf ctx pred thenCl elseCl ty loc
  | Expr.Match (target, arm1, arm2, ty, loc) ->
    mirifyExprMatch ctx target arm1 arm2 ty loc
  | Expr.Nav (l, r, ty, loc) ->
    mirifyExprNav ctx l r ty loc
  | Expr.Index (l, r, ty, loc) ->
    mirifyExprIndex ctx l r ty loc
  | Expr.Call (callee, args, ty, loc) ->
    mirifyExprCall ctx callee args ty loc
  | Expr.Op (op, l, r, ty, loc) ->
    mirifyExprOp ctx op l r ty loc
  | Expr.Tuple (items, ty, loc) ->
    mirifyExprTuple ctx items ty loc
  | Expr.AndThen (exprs, _, _) ->
    mirifyExprAndThen ctx exprs
  | Expr.Let ([pat], init, letLoc) ->
    mirifyExprLetVal ctx pat init letLoc
  | Expr.Let (pat :: pats, body, letLoc) ->
    mirifyExprLetFun ctx pat pats body letLoc
  | Expr.TyDef (_, tySerial, tyDef, loc) ->
    mirifyExprTyDef ctx tySerial tyDef loc
  | Expr.Call (_, [], _, _)
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

let mirify (exprs: Expr<Loc> list, tyCtx: TyCtx): MDecl<_> list * MirCtx =
  let ctx = ctxFromTyCtx tyCtx
  let _exprs, ctx = mirifyExprs ctx exprs
  assert (List.isEmpty ctx.Stmts)
  let decls = List.rev ctx.Decls
  decls, ctx
