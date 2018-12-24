module rec MiloneLang.Mir

open MiloneLang.Helpers

type TyCtx = Typing.TyCtx

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    VarSerial: int
    Vars: Map<int, string * ValueIdent * Ty * Loc>
    Tys: Map<int, TyDef>
    LabelSerial: int
    Decls: MDecl list
    Stmts: MStmt list
    Diags: Diag list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  {
    VarSerial = tyCtx.VarSerial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    LabelSerial = 0
    Decls = []
    Stmts = []
    Diags = tyCtx.Diags
  }

let ctxAddErr (ctx: MirCtx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

let ctxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

let ctxAddDecl (ctx: MirCtx) decl =
  { ctx with Decls = decl :: ctx.Decls }

let ctxAddStmt (ctx: MirCtx) (stmt: MStmt) =
  { ctx with Stmts = stmt :: ctx.Stmts }

/// Returns statements in reversed order.
let ctxTakeStmts (ctx: MirCtx) =
  ctx.Stmts, { ctx with Stmts = [] }

let ctxFreshVar (ctx: MirCtx) (ident: string) (ty: Ty) loc =
  let serial = ctx.VarSerial + 1
  let ctx =
    { ctx with
        VarSerial = ctx.VarSerial + 1
        Vars = ctx.Vars |> Map.add serial (ident, ValueIdent.Var, ty, loc)
    }
  let refExpr = MExpr.Ref (serial, 1, ty, loc)
  refExpr, serial, ctx

let ctxLetFreshVar (ctx: MirCtx) (ident: string) (ty: Ty) loc =
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
  | Op.Range
  | Op.Index -> failwith "Never: We don't use > >= && || :: .. in MIR"

let mtyDef (tySerial, tyDef: TyDef) =
  match tyDef with
  | TyDef.Union (tyIdent, variants, loc) ->
    Some (tySerial, TyDef.Union (tyIdent, variants, loc))
  | TyDef.Bv _ ->
    None

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.UniOp (MUniOp.Proj index, expr, resultTy, loc)

let strAddExpr ctx _op l r (_, loc) =
  MExpr.Op (MOp.StrAdd, l, r, Ty.Str, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let opScalarExpr ctx op l r (ty, loc) =
  MExpr.Op (op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let strCmpExpr ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Op (MOp.StrCmp, l, r, Ty.Int, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

/// Generates a comparison expression.
let cmpExpr ctx (op: MOp) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprTy l with
  | Ty.Bool
  | Ty.Int
  | Ty.Char ->
    opScalarExpr ctx op l r (ty, loc)
  | Ty.Str ->
    strCmpExpr ctx op l r (ty, loc)
  | _ ->
    failwith "unimpl"

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MExpr.Lit (lit, loc)
  let eqExpr, ctx = cmpExpr ctx MOp.Eq expr litExpr Ty.Bool loc
  let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr = MExpr.UniOp (MUniOp.ListIsEmpty, expr, Ty.List itemTy, loc)
  let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let listTy = Ty.List itemTy
  let isEmpty = MExpr.UniOp (MUniOp.ListIsEmpty, expr, Ty.Bool, loc)
  let nonEmpty = MExpr.UniOp (MUniOp.Not, isEmpty, Ty.Bool, loc)
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
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, Ty.Int, loc)
    let rTagExpr = MExpr.Ref (serial, 0, Ty.Int, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, Ty.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx.Vars |> Map.find serial, args with
  | (_, ValueIdent.Variant _, Ty.Fun (argTy, _), _), [arg] ->
    // Compare tags.
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, Ty.Int, loc)
    let rTagExpr = MExpr.Ref (serial, 0, Ty.Int, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, Ty.Bool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt

    // Extract content.
    let extractExpr = MExpr.UniOp (MUniOp.GetVariant serial, expr, argTy, loc)
    let _, ctx = mirifyPat ctx endLabel arg extractExpr
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
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
let mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr): bool * MirCtx =
  match pat with
  | HPat.Ref ("_", _, _, _) ->
    // Discard result.
    true, ctx
  | HPat.Lit (lit, loc) ->
    mirifyPatLit ctx endLabel lit expr loc
  | HPat.Nil (itemTy, loc) ->
    mirifyPatNil ctx endLabel itemTy expr loc
  | HPat.Ref (_, serial, ty, loc) ->
    mirifyPatRef ctx endLabel serial ty loc expr
  | HPat.Call (HPat.Ref (_, serial, _, _), args, ty, loc) ->
    mirifyPatCall ctx endLabel serial args ty loc expr
  | HPat.Cons (l, r, itemTy, loc) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | HPat.Tuple (itemPats, Ty.Tuple itemTys, loc) ->
    mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | HPat.Call _ ->
    failwith "Never: Call pattern incorrect."
  | HPat.Tuple _ ->
    failwith "Never: Tuple pattern must be of tuple type."
  | HPat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."

let mirifyExprRef (ctx: MirCtx) serial arity ty loc =
  match ctx.Vars |> Map.tryFind serial with
  | Some (_, ValueIdent.Variant tySerial, _, _) ->
    MExpr.Variant (tySerial, serial, ty, loc), ctx
  | _ ->
    MExpr.Ref (serial, arity, ty, loc), ctx

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

let mirifyExprMatch ctx target arms ty loc =
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
      else ctxAddStmt ctx (MStmt.Exit (MExpr.Lit (Lit.Int 1, loc), loc))
  let ctx = go false ctx arms

  // End of match.
  let ctx = ctxAddStmt ctx endLabelStmt

  temp, ctx

let mirifyExprIndex ctx l r _ loc =
  match exprTy l, exprTy r with
  | Ty.Str, Ty.Int ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Op (MOp.StrIndex, l, r, Ty.Char, loc), ctx
  | Ty.Str, Ty.Range ->
    let rl, rr =
      match r with
      | HExpr.Op (Op.Range, rl, rr, _, _) -> rl, rr
      | _ -> failwith "Never"
    let l, ctx = mirifyExpr ctx l
    let rl, ctx = mirifyExpr ctx rl
    let rr, ctx = mirifyExpr ctx rr
    let temp, tempSerial, ctx = ctxFreshVar ctx "slice" Ty.Str loc
    let funTy = Ty.Fun (Ty.Str, Ty.Fun (Ty.Int, Ty.Fun (Ty.Int, Ty.Str)))
    let strSliceRef = MExpr.Ref (SerialStrSlice, 3, funTy, loc)
    let callInit = MInit.Call (strSliceRef, [l; rl; rr], funTy)
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, callInit, Ty.Str, loc))
    temp, ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let ctx = ctxAddStmt ctx (MStmt.Exit (arg, loc))
  MExpr.Default (ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "box" Ty.Obj loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, Ty.Obj, loc))
  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Unbox, arg, ty, loc), ctx

let mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.StrLen, arg, ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.UniOp (MUniOp.Not, arg, ty, notLoc), ctx

let mirifyExprCallVariantFun (ctx: MirCtx) serial arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "variant" ty loc
  let init = MInit.Union (serial, arg, mexprTy arg)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, init, ty, loc))
  temp, ctx

let mirifyExprOpCons ctx l r itemTy listTy loc =
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r, itemTy), listTy, loc))
  MExpr.Ref (tempSerial, 0, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let ty = Ty.Tuple itemTys
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
  MExpr.Ref (tempSerial, 0, ty, loc), ctx

let mirifyExprOp ctx op l r ty loc =
  match op with
  | Op.Cons itemTy ->
    mirifyExprOpCons ctx l r itemTy ty loc
  | Op.Index ->
    mirifyExprIndex ctx l r ty loc
  | Op.Gt ->
    mirifyExprOp ctx Op.Lt r l ty loc
  | Op.Ge ->
    mirifyExprOp ctx Op.Le r l ty loc
  | Op.Eq
  | Op.Ne
  | Op.Lt
  | Op.Le ->
    let op = mopFrom op
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    cmpExpr ctx op l r ty loc
  | Op.And
  | Op.Or
  | Op.Pipe ->
    failwith "Never: Desugared operators"
  | Op.App ->
    failwith "Never: Apps erased in FunTrans."
  | _ ->
    let op = mopFrom op
    let lTy = exprTy l
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

let mirifyExprInfCall ctx callee args ty loc =
  let core () =
    let calleeTy = exprTy callee
    let callee, ctx = mirifyExpr ctx callee
    let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
    let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Call (callee, args, calleeTy), ty, loc))
    temp, ctx
  match args with
  | [arg] ->
    match callee with
    | HExpr.Ref (_, serial, _, _, _) when serial = SerialNot ->
      mirifyExprCallNot ctx arg ty loc
    | HExpr.Ref (_, serial, _, _, _) when serial = SerialExit ->
      mirifyExprCallExit ctx arg ty loc
    | HExpr.Ref (_, serial, _, _, _) when serial = SerialBox ->
      mirifyExprCallBox ctx arg ty loc
    | HExpr.Ref (_, serial, _, _, _) when serial = SerialUnbox ->
      mirifyExprCallUnbox ctx arg ty loc
    | HExpr.Ref (_, serial, _, _, _) when serial = SerialStrLength ->
      mirifyExprCallStrLength ctx arg ty loc
    | HExpr.Ref (_, serial, _, _, _) when ctxIsVariantFun ctx serial ->
      mirifyExprCallVariantFun ctx serial arg ty loc
    | _ ->
      core ()
  | _ ->
    core ()

let mirifyExprInfExec ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
  let tempRef, tempSerial, ctx = ctxFreshVar ctx "app" resultTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Exec (callee, args), resultTy, loc))
  tempRef, ctx

let mirifyExprInfFun ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = ctxFreshVar ctx "env" envTy envLoc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (envSerial, MInit.Expr env, envTy, envLoc))

  let tempRef, tempSerial, ctx = ctxFreshVar ctx "fun" funTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Fun (funSerial, envSerial), funTy, loc))
  tempRef, ctx

let mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.List _, [], Ty.List itemTy ->
    MExpr.Default (Ty.List itemTy, loc), ctx
  | InfOp.Tuple, [], Ty.Tuple [] ->
    MExpr.Default (tyUnit, loc), ctx
  | InfOp.Tuple, _, Ty.Tuple itemTys ->
    mirifyExprTuple ctx args itemTys loc
  | InfOp.AndThen, _, _ ->
    mirifyExprAndThen ctx args
  | InfOp.Call, callee :: args, _ ->
    mirifyExprInfCall ctx callee args ty loc
  | InfOp.Exec, callee :: args, _ ->
    mirifyExprInfExec ctx callee args ty loc
  | InfOp.Fun funSerial, [env], _ ->
    mirifyExprInfFun ctx funSerial env ty loc
  | t ->
    failwithf "Never: %A" t

let mirifyExprLetVal ctx pat init letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init
  let ctx =
    if exhaustive then ctx else
    ctxAddErr ctx "Let pattern must be exhaustive for now" letLoc
  MExpr.Default (tyUnit, letLoc), ctx

let mirifyExprLetFun ctx calleeSerial argPats body letLoc =
  let defineArg ctx argPat =
    match argPat with
    | HPat.Ref (_, serial, ty, loc) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      (serial, 1, ty, loc), ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let arg, argSerial, ctx = ctxFreshVar ctx "arg" argTy argLoc
      let exhaustive, ctx = mirifyPat ctx "_never_" argPat arg
      let ctx =
        if exhaustive then ctx else
        ctxAddErr ctx "Argument pattern must be exhaustive for now" argLoc
      (argSerial, 1, argTy, argLoc), ctx

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
    args, blockTy, body, ctx

  let bodyCtx = ctxNewBlock ctx
  let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
  let ctx = ctxRollBack ctx bodyCtx
  let decl = MDecl.LetFun (calleeSerial, args, [], resultTy, body, letLoc)
  let ctx = ctxAddDecl ctx decl
  MExpr.Default (tyUnit, letLoc), ctx

let mirifyExprTyDef ctx tySerial tyDef loc =
  let ctx = ctxAddDecl ctx (MDecl.TyDef (tySerial, tyDef, loc))
  MExpr.Default (tyUnit, loc), ctx

let mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    MExpr.Lit (lit, loc), ctx
  | HExpr.Ref (_, serial, arity, ty, loc) ->
    mirifyExprRef ctx serial arity ty loc
  | HExpr.Match (target, arms, ty, loc) ->
    mirifyExprMatch ctx target arms ty loc
  | HExpr.Op (op, l, r, ty, loc) ->
    mirifyExprOp ctx op l r ty loc
  | HExpr.Inf (infOp, args, ty, loc) ->
    mirifyExprInf ctx infOp args ty loc
  | HExpr.Let (pat, body, loc) ->
    mirifyExprLetVal ctx pat body loc
  | HExpr.LetFun (_, serial, args, body, loc) ->
    mirifyExprLetFun ctx serial args body loc
  | HExpr.TyDef (_, tySerial, tyDef, loc) ->
    mirifyExprTyDef ctx tySerial tyDef loc
  | HExpr.If _
  | HExpr.Nav _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Tuple, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    let ctx = ctxAddErr ctx error loc
    MExpr.Default (Ty.Obj, loc), ctx

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, ctx
    | expr :: exprs ->
      let expr, ctx = mirifyExpr ctx expr
      go (expr :: acc) ctx exprs
  go [] ctx exprs

let mirify (exprs: HExpr list, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = ctxFromTyCtx tyCtx
  let _exprs, ctx = mirifyExprs ctx exprs
  // NOTE: This will fail when you write top-level value expression.
  assert (List.isEmpty ctx.Stmts)
  let decls = List.rev ctx.Decls
  decls, ctx
