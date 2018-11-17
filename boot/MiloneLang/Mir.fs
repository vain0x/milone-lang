module rec MiloneLang.Mir

open MiloneLang.Helpers

type TyCtx = Typing.TyCtx

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    VarSerial: int
    Vars: Map<int, string * ValueIdent * MTy * Loc>
    Tys: Map<int, string * MTyDef * Loc>
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
  let tys =
    tyCtx.Tys |> Map.map (fun tySerial (ident, tyDef, loc) ->
      let tyDef = mtyDef tySerial tyDef
      ident, tyDef, loc
    )
  {
    VarSerial = tyCtx.VarSerial
    Vars = vars
    Tys = tys
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

/// Gets if the serial denotes to a variant function.
let ctxIsVariantFun (ctx: MirCtx) serial =
  match ctx.Vars |> Map.tryFind serial with
  | Some (_, ValueIdent.Variant _, _, _) ->
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
  | Op.Pipe
  | Op.And
  | Op.Or
  | Op.App
  | Op.Cons _
  | Op.Range -> failwith "We don't use > >= && || :: .. in MIR"

let mtyDef tySerial (tyDef: TyDef) =
  match tyDef with
  | TyDef.Union variants ->
    let variants =
      variants |> List.map (fun (_, variantSerial, hasArg, argTy) ->
        let argTy = unboxTy argTy
        let variantTy = MTy.Fun (argTy, MTy.Ref tySerial)
        variantSerial, hasArg, argTy, variantTy
      )
    MTyDef.Union variants

let unboxTy (ty: Ty): MTy =
  match ty with
  | Ty.Unit -> MTy.Unit
  | Ty.Bool -> MTy.Bool
  | Ty.Int -> MTy.Int
  | Ty.Char -> MTy.Char
  | Ty.Str -> MTy.Str
  | Ty.Obj -> MTy.Obj
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

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.UniOp (MUniOp.Proj index, expr, unboxTy resultTy, loc)

let strAddExpr ctx _op l r (_, loc) =
  MExpr.Op (MOp.StrAdd, l, r, MTy.Str, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let opScalarExpr ctx op l r (ty, loc) =
  MExpr.Op (op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let strCmpExpr ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Op (MOp.StrCmp, l, r, MTy.Int, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

/// Generates a comparison expression.
let cmpExpr ctx (op: MOp) (l: MExpr<_>) r (ty: MTy) loc =
  assert (opIsComparison op)
  match mexprTy l with
  | MTy.Bool
  | MTy.Int
  | MTy.Char ->
    opScalarExpr ctx op l r (ty, loc)
  | MTy.Str ->
    strCmpExpr ctx op l r (ty, loc)
  | _ ->
    failwith "unimpl"

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MExpr.Lit (lit, loc)
  let eqExpr, ctx = cmpExpr ctx MOp.Eq expr litExpr MTy.Bool loc
  let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr = MExpr.UniOp (MUniOp.ListIsEmpty, expr, unboxTy (Ty.List itemTy), loc)
  let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

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

let mirifyPatRef (ctx: MirCtx) endLabel serial ty loc expr =
  match ctx.Vars |> Map.find serial with
  | _, ValueIdent.Variant _, _, _ ->
    // Compare tags.
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, MTy.Int, loc)
    let rTagExpr = MExpr.Ref (serial, MTy.Int, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, MTy.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, unboxTy ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx.Vars |> Map.find serial, args with
  | (_, ValueIdent.Variant _, MTy.Fun (argTy, _), _), [arg] ->
    // Compare tags.
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, MTy.Int, loc)
    let rTagExpr = MExpr.Ref (serial, MTy.Int, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, MTy.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt

    // Extract content.
    let extractExpr = MExpr.UniOp (MUniOp.GetVariant serial, expr, argTy, loc)
    let _, ctx = mirifyPat ctx endLabel arg extractExpr
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, unboxTy ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatTuple ctx endLabel itemPats itemTys expr loc =
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
  | Pat.Lit (lit, loc) ->
    mirifyPatLit ctx endLabel lit expr loc
  | Pat.Nil (itemTy, loc) ->
    mirifyPatNil ctx endLabel itemTy expr loc
  | Pat.Ref (_, serial, ty, loc) ->
    mirifyPatRef ctx endLabel serial ty loc expr
  | Pat.Call (Pat.Ref (_, serial, _, _), args, ty, loc) ->
    mirifyPatCall ctx endLabel serial args ty loc expr
  | Pat.Cons (l, r, itemTy, loc) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | Pat.Tuple (itemPats, Ty.Tuple itemTys, loc) ->
    mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | Pat.Call _ ->
    failwith "Never: Call pattern incorrect."
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
      go (Expr.Op (Op.Cons itemTy, item, acc, Ty.List itemTy, loc)) items
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

let mirifyExprMatch ctx target arms ty loc =
  let ty = unboxTy ty
  let temp, tempSet, ctx = ctxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = ctxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  let rec go allCovered ctx arms =
    match arms with
    | (pat, body) :: arms ->
      let nextLabelStmt, nextLabel, ctx = ctxFreshLabel ctx "next" loc
      let covered, ctx = mirifyPat ctx nextLabel pat target
      let body, ctx = mirifyExpr ctx body
      let ctx = ctxAddStmt ctx (tempSet body)
      let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))
      let ctx = ctxAddStmt ctx nextLabelStmt
      go (allCovered || covered) ctx arms
    | [] ->
      // Exhaust case (unless covered).
      if allCovered
      then ctx
      else ctxAddStmt ctx (mstmtExit1 ty loc)
  let ctx = go false ctx arms

  // End of match.
  let ctx = ctxAddStmt ctx endLabelStmt

  temp, ctx

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
  let temp, tempSerial, ctx = ctxFreshVar ctx "box" MTy.Obj loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, MTy.Obj, loc))
  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Unbox, arg, unboxTy ty, loc), ctx

let mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.StrLen, arg, unboxTy ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Not, arg, unboxTy ty, notLoc), ctx

let mirifyExprCallVariantFun (ctx: MirCtx) serial arg ty loc =
  let ty = unboxTy ty
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "variant" ty loc
  let init = MInit.Union (serial, arg, mexprTy arg)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, init, ty, loc))
  temp, ctx

let mirifyExprOpApp ctx callee arg ty loc =
  match callee with
  | Expr.Ref (_, serial, _, _) when serial = SerialNot ->
    mirifyExprCallNot ctx arg ty loc
  | Expr.Ref (_, serial, _, _) when serial = SerialExit ->
    mirifyExprCallExit ctx arg ty loc
  | Expr.Ref (_, serial, _, _) when serial = SerialBox ->
    mirifyExprCallBox ctx arg ty loc
  | Expr.Ref (_, serial, _, _) when serial = SerialUnbox ->
    mirifyExprCallUnbox ctx arg ty loc
  | Expr.Ref (_, serial, _, _) when serial = SerialStrLength ->
    mirifyExprCallStrLength ctx arg ty loc
  | Expr.Ref (_, serial, _, _) when ctxIsVariantFun ctx serial ->
    mirifyExprCallVariantFun ctx serial arg ty loc
  | _ ->
    let ty = unboxTy ty

    /// Converts `(((f x) ..) y)` to `f(x, .., y)`.
    let rec dig acc ctx callee =
      match callee with
      | Expr.Op (Op.App, callee, arg, _, _) ->
        dig (arg :: acc) ctx callee
      | Expr.Op (Op.Pipe, arg, callee, _, _) ->
        dig (arg :: acc) ctx callee
      | _ ->
        callee, acc, ctx

    let callee, args, ctx = dig [arg] ctx callee
    let callee, ctx = mirifyExpr ctx callee
    let args, ctx = mirifyExprs ctx args

    let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Call (callee, args), ty, loc))
    temp, ctx

/// `x |> f` ==> `f x`
let mirifyExprOpPipe ctx l r ty loc =
  mirifyExprOpApp ctx r l ty loc

/// l && r ==> if l then r else false
let mirifyExprOpAnd ctx l r ty loc =
  let falseExpr = Expr.Lit (Lit.Bool false, loc)
  mirifyExprIf ctx l r falseExpr ty loc

/// l || r ==> if l then true else r
let mirifyExprOpOr ctx l r ty loc =
  let trueExpr = Expr.Lit (Lit.Bool true, loc)
  mirifyExprIf ctx l trueExpr r ty loc

let mirifyExprOpCons ctx l r itemTy listTy loc =
  let itemTy = unboxTy itemTy
  let listTy = unboxTy listTy
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r, itemTy), listTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let itemTys = List.map unboxTy itemTys
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

let mirifyExprOp ctx op l r ty loc =
  match op with
  | Op.And ->
    mirifyExprOpAnd ctx l r ty loc
  | Op.Or ->
    mirifyExprOpOr ctx l r ty loc
  | Op.App ->
    mirifyExprOpApp ctx l r ty loc
  | Op.Pipe ->
    mirifyExprOpPipe ctx l r ty loc
  | Op.Cons itemTy ->
    mirifyExprOpCons ctx l r itemTy ty loc
  | Op.Gt ->
    mirifyExprOp ctx Op.Lt r l ty loc
  | Op.Ge ->
    mirifyExprOp ctx Op.Le r l ty loc
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le ->
    let op = mopFrom op
    let ty = unboxTy ty
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    cmpExpr ctx op l r ty loc
  | _ ->
    let op = mopFrom op
    let ty, lTy = unboxTy ty, exprTy l
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    match lTy with
    | Ty.Int
    | Ty.Char ->
      opScalarExpr ctx op l r (ty, loc)
    | Ty.Str when op = MOp.Add ->
      strAddExpr ctx op l r (ty, loc)
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

let mirifyExprLet ctx pat body loc =
  match pat with
  | Pat.Call (callee, args, _, _)->
    mirifyExprLetFun ctx callee args body loc
  | _ ->
    mirifyExprLetVal ctx pat body loc

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
  | Expr.Match (target, arms, ty, loc) ->
    mirifyExprMatch ctx target arms ty loc
  | Expr.Index (l, r, ty, loc) ->
    mirifyExprIndex ctx l r ty loc
  | Expr.Op (op, l, r, ty, loc) ->
    mirifyExprOp ctx op l r ty loc
  | Expr.Tuple (items, itemTys, loc) ->
    mirifyExprTuple ctx items itemTys loc
  | Expr.AndThen (exprs, _, _) ->
    mirifyExprAndThen ctx exprs
  | Expr.Let (pat, body, loc) ->
    mirifyExprLet ctx pat body loc
  | Expr.TyDef (_, tySerial, tyDef, loc) ->
    mirifyExprTyDef ctx tySerial tyDef loc
  | Expr.Nav _
  | Expr.Anno _ ->
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
