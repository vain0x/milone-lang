module rec MiloneLang.Mir

open MiloneLang.Helpers

type TyCtx = Typing.TyCtx

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    VarSerial: int
    Vars: Map<int, VarDef>
    Tys: Map<int, TyDef>
    LabelSerial: int
    Stmts: MStmt list
    Diags: Diag list
  }

let ctxFromTyCtx (tyCtx: Typing.TyCtx): MirCtx =
  {
    VarSerial = tyCtx.VarSerial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    LabelSerial = 0
    Stmts = []
    Diags = tyCtx.Diags
  }

let ctxAddErr (ctx: MirCtx) message loc =
  { ctx with Diags = Diag.Err (message, loc) :: ctx.Diags }

let ctxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let ctxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

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
        Vars = ctx.Vars |> Map.add serial (VarDef.Var (ident, ty, loc))
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
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
  | Some (VarDef.Variant _) ->
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
  | Op.ConsRev
  | Op.Range
  | Op.Index -> failwith "Never: We don't use > >= && || :: .. in MIR"

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let projExpr expr index resultTy loc =
  MExpr.UniOp (MUniOp.Proj index, expr, resultTy, loc)

let strAddExpr ctx _op l r (_, loc) =
  MExpr.Op (MOp.StrAdd, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let opScalarExpr ctx op l r (ty, loc) =
  MExpr.Op (op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let strCmpExpr ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Op (MOp.StrCmp, l, r, tyInt, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Op (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

/// Generates a comparison expression.
let cmpExpr ctx (op: MOp) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprTy l with
  | Ty.Con ((TyCon.Bool | TyCon.Int | TyCon.Char), _) ->
    opScalarExpr ctx op l r (ty, loc)
  | Ty.Con (TyCon.Str, _) ->
    strCmpExpr ctx op l r (ty, loc)
  | _ ->
    failwith "unimpl"

let hxIsAlwaysTrue expr =
  match expr with
  | HExpr.Lit (Lit.Bool true, _) -> true
  | _ -> false

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MExpr.Lit (lit, loc)
  let eqExpr, ctx = cmpExpr ctx MOp.Eq expr litExpr tyBool loc
  let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr = MExpr.UniOp (MUniOp.ListIsEmpty, expr, tyList itemTy, loc)
  let gotoStmt = MStmt.GotoUnless (isEmptyExpr, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let listTy = tyList itemTy
  let isEmpty = MExpr.UniOp (MUniOp.ListIsEmpty, expr, tyBool, loc)
  let nonEmpty = MExpr.UniOp (MUniOp.Not, isEmpty, tyBool, loc)
  let gotoStmt = MStmt.GotoUnless (nonEmpty, endLabel, loc)
  let ctx = ctxAddStmt ctx gotoStmt
  let head = MExpr.UniOp (MUniOp.ListHead, expr, itemTy, loc)
  let tail = MExpr.UniOp (MUniOp.ListTail, expr, listTy, loc)
  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

let mirifyPatRef (ctx: MirCtx) endLabel serial ty loc expr =
  match ctx.Vars |> Map.find serial with
  | VarDef.Variant _ ->
    // Compare tags.
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
    let gotoStmt = MStmt.GotoUnless (eqExpr, endLabel, loc)
    let ctx = ctxAddStmt ctx gotoStmt
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, ctxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx.Vars |> Map.find serial, args with
  | VarDef.Variant (_, _, _, argTy, _, _), [arg] ->
    // Compare tags.
    let lTagExpr = MExpr.UniOp (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Op (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
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

let mirifyPatAs ctx endLabel pat serial expr loc =
  let ty, _ = patExtract pat
  let ctx = ctxAddStmt ctx (MStmt.LetVal (serial, MInit.Expr expr, ty, loc))
  let expr = MExpr.Ref (serial, ty, loc)
  let covers, ctx = mirifyPat ctx endLabel pat expr
  covers, ctx

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
  | HPat.Tuple (itemPats, Ty.Con (TyCon.Tuple, itemTys), loc) ->
    mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | HPat.As (pat, _, serial, loc) ->
    mirifyPatAs ctx endLabel pat serial expr loc
  | HPat.Or _ ->
    failwith "Unimpl nested OR pattern."
  | HPat.Nav _ ->
    failwith "Never: Nav pattern in mirify"
  | HPat.Call _ ->
    failwith "Never: Call pattern incorrect."
  | HPat.Tuple _ ->
    failwith "Never: Tuple pattern must be of tuple type."
  | HPat.Anno _ ->
    failwith "Never annotation pattern in MIR-ify stage."

let mirifyExprRef (ctx: MirCtx) valRef ty loc =
  match valRef with
  | HValRef.Var serial ->
    match ctx.Vars |> Map.tryFind serial with
    | Some (VarDef.Variant (_, tySerial, _, _, _, _)) ->
      MExpr.Variant (tySerial, serial, ty, loc), ctx
    | Some (VarDef.Fun (_, _, _, loc)) ->
      MExpr.Proc (serial, ty, loc), ctx
    | _ ->
      MExpr.Ref (serial, ty, loc), ctx
  | HValRef.Prim prim ->
    MExpr.Prim (prim, ty, loc), ctx

let mirifyBlock ctx expr =
  let blockCtx = ctxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = ctxTakeStmts blockCtx
  let ctx = ctxRollBack ctx blockCtx
  stmts, expr, ctx

/// Gets if the target must match with any of the patterns.
let patsIsCovering pats =
  let rec go pat =
    match pat with
    | HPat.Ref _ ->
      true
    | HPat.Lit _
    | HPat.Nil _
    | HPat.Nav _
    | HPat.Cons _
    | HPat.Call _ ->
      false
    | HPat.Tuple (itemPats, _, _) ->
      itemPats |> List.forall go
    | HPat.As (pat, _, _, _) ->
      go pat
    | HPat.Anno (pat, _, _) ->
      go pat
    | HPat.Or (first, second, _, _) ->
      go first || go second
  List.exists go pats

let mirifyExprMatch ctx target arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = ctxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = ctxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  let isCovering =
    arms
    |> List.choose
      (fun (pat, guard, _) -> if hxIsAlwaysTrue guard then Some pat else None)
    |> patsIsCovering

  /// By walking over arms, calculates what kind of MIR instructions to emit.
  let rec goArms ctx acc firstPat arms =
    match arms with
    | (pat, guard, body) :: arms ->
      let pats = patNormalize pat
      let disjCount = pats |> List.length

      // No need to jump to body from pattern if no OR patterns.
      let needsJump = disjCount > 1

      let bodyLabel, ctx =
        if not needsJump then noLabel, ctx else
        let _, bodyLabel, ctx = ctxFreshLabel ctx "match_body" loc
        bodyLabel, ctx

      let rec goPats ctx acc firstPat pats =
        match pats with
        | pat :: pats ->
          // Label on the pattern.
          // The first pattern's label is unnecessary and not created.
          let acc, ctx =
            if firstPat then acc, ctx else
            let _, patLabel, ctx = ctxFreshLabel ctx "next" loc
            MatchIR.PatLabel patLabel :: acc, ctx
          let acc =
            MatchIR.Pat (pat, noLabel) :: acc
          let acc =
            if not needsJump then acc else
            MatchIR.GoBody bodyLabel :: acc

          goPats ctx acc false pats
        | [] ->
          acc, ctx

      let acc, ctx = goPats ctx acc firstPat pats

      let acc =
        if not needsJump then acc else
        MatchIR.BodyLabel bodyLabel :: acc
      let acc = MatchIR.Guard (guard, noLabel) :: acc
      let acc = MatchIR.Body body :: acc
      goArms ctx acc false arms
    | [] ->
      let _, exhaustLabel, ctx = ctxFreshLabel ctx "next" loc
      let acc = MatchIR.PatLabel exhaustLabel :: acc
      acc, ctx

  /// Fixes up instructions.
  /// 1. By walking over instructions in the reversed order,
  /// fill `nextLabel` fields.
  /// 2. Remove trivial guards.
  let rec fixUp acc nextLabel instructionsRev =
    match instructionsRev with
    | MatchIR.PatLabel patLabel as instruction :: rest ->
      // The leading instructions refers to this label as next one.
      fixUp (instruction :: acc) patLabel rest
    | MatchIR.Pat (pat, _) :: rest ->
      let acc = MatchIR.Pat (pat, nextLabel) :: acc
      fixUp acc nextLabel rest
    | MatchIR.Guard (guard, _) :: rest ->
      let acc =
        // Trivial guard is unnecessary.
        if guard |> hxIsAlwaysTrue then acc else
        MatchIR.Guard (guard, nextLabel) :: acc
      fixUp acc nextLabel rest
    | instruction :: rest ->
      fixUp (instruction :: acc) nextLabel rest
    | [] ->
      acc

  /// Emits MIR instructions based on matching IRs.
  let rec emit ctx instructions =
    match instructions with
    | MatchIR.PatLabel patLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Label (patLabel, loc))
      emit ctx rest
    | MatchIR.Pat (pat, nextLabel) :: rest ->
      // Perform pattern matching. Go to the next pattern on failure.
      let _, ctx = mirifyPat ctx nextLabel pat target
      emit ctx rest
    | MatchIR.GoBody bodyLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Goto (bodyLabel, loc))
      emit ctx rest
    | MatchIR.BodyLabel bodyLabel :: rest ->
      let ctx = ctxAddStmt ctx (MStmt.Label (bodyLabel, loc))
      emit ctx rest
    | MatchIR.Guard (guard, nextLabel) :: rest ->
      let ctx =
        if guard |> hxIsAlwaysTrue then ctx else
        let guard, ctx = mirifyExpr ctx guard
        ctxAddStmt ctx (MStmt.GotoUnless (guard, nextLabel, loc))
      emit ctx rest
    | MatchIR.Body body :: rest ->
      // Enter into the body.
      let body, ctx = mirifyExpr ctx body
      // Leave the match.
      let ctx = ctxAddStmt ctx (tempSet body)
      let ctx = ctxAddStmt ctx (MStmt.Goto (endLabel, loc))
      emit ctx rest
    | [] ->
      // Abort if exhaust.
      if isCovering then ctx else
      let abortStmt = MStmt.Exit (MExpr.Lit (Lit.Int 1, loc), loc)
      let ctx = ctxAddStmt ctx abortStmt
      ctx

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = ctxAddStmt ctx endLabelStmt

  temp, ctx

let mirifyExprIndex ctx l r _ loc =
  match exprTy l, exprTy r with
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Int, _) ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Op (MOp.StrIndex, l, r, tyChar, loc), ctx
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Range, _) ->
    let rl, rr =
      match r with
      | HExpr.Op (Op.Range, rl, rr, _, _) -> rl, rr
      | _ -> failwith "Never"
    let l, ctx = mirifyExpr ctx l
    let rl, ctx = mirifyExpr ctx rl
    let rr, ctx = mirifyExpr ctx rr
    let temp, tempSerial, ctx = ctxFreshVar ctx "slice" tyStr loc
    let funTy = tyFun tyStr (tyFun tyInt (tyFun tyInt tyStr))
    let strSliceRef = MExpr.Prim (HPrim.StrSlice, funTy, loc)
    let callInit = MInit.CallProc (strSliceRef, [l; rl; rr], funTy)
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, callInit, tyStr, loc))
    temp, ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let ctx = ctxAddStmt ctx (MStmt.Exit (arg, loc))
  MExpr.Default (ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = ctxFreshVar ctx "box" tyObj loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, tyObj, loc))
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
  // Put payload on the heap.
  let arg, ctx = mirifyExpr ctx arg
  let payloadTy = mexprTy arg
  let _, payloadSerial, ctx = ctxFreshVar ctx "payload" payloadTy loc
  let payloadInit = MInit.Indirect arg
  let ctx = ctxAddStmt ctx (MStmt.LetVal (payloadSerial, payloadInit, payloadTy, loc))

  let temp, tempSerial, ctx = ctxFreshVar ctx "variant" ty loc
  let init = MInit.Variant (serial, payloadSerial)
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, init, ty, loc))
  temp, ctx

let mirifyExprOpCons ctx l r itemTy listTy loc =
  let _, tempSerial, ctx = ctxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r, itemTy), listTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let ty = tyTuple itemTys
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
    | Ty.Con ((TyCon.Int | TyCon.Char), _) ->
      opScalarExpr ctx op l r (ty, loc)
    | Ty.Con (TyCon.Str, _) when op = MOp.Add ->
      strAddExpr ctx op l r (ty, loc)
    | _ ->
      failwithf "unimpl"

let mirifyExprAndThen ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprInfCallProc ctx callee args ty loc =
  let core () =
    let calleeTy = exprTy callee
    let callee, ctx = mirifyExpr ctx callee
    let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
    let temp, tempSerial, ctx = ctxFreshVar ctx "call" ty loc
    let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallProc (callee, args, calleeTy), ty, loc))
    temp, ctx
  match args with
  | [arg] ->
    match callee with
    | HExpr.Ref (_, HValRef.Prim HPrim.Not, _, _) ->
      mirifyExprCallNot ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Exit, _, _) ->
      mirifyExprCallExit ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Box, _, _) ->
      mirifyExprCallBox ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.Unbox, _, _) ->
      mirifyExprCallUnbox ctx arg ty loc
    | HExpr.Ref (_, HValRef.Prim HPrim.StrLength, _, _) ->
      mirifyExprCallStrLength ctx arg ty loc
    | HExpr.Ref (_, HValRef.Var serial, _, _) when ctxIsVariantFun ctx serial ->
      mirifyExprCallVariantFun ctx serial arg ty loc
    | _ ->
      core ()
  | _ ->
    core ()

let mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
  let tempRef, tempSerial, ctx = ctxFreshVar ctx "app" resultTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallClosure (callee, args), resultTy, loc))
  tempRef, ctx

let mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = ctxFreshVar ctx "env" envTy envLoc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (envSerial, MInit.Expr env, envTy, envLoc))

  let tempRef, tempSerial, ctx = ctxFreshVar ctx "fun" funTy loc
  let ctx = ctxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Closure (funSerial, envSerial), funTy, loc))
  tempRef, ctx

let mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.List _, [], Ty.Con (TyCon.List, [itemTy]) ->
    MExpr.Default (tyList itemTy, loc), ctx
  | InfOp.Tuple, [], Ty.Con (TyCon.Tuple, []) ->
    MExpr.Default (tyUnit, loc), ctx
  | InfOp.Tuple, _, Ty.Con (TyCon.Tuple, itemTys) ->
    mirifyExprTuple ctx args itemTys loc
  | InfOp.AndThen, _, _ ->
    mirifyExprAndThen ctx args
  | InfOp.CallProc, callee :: args, _ ->
    mirifyExprInfCallProc ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ ->
    mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.Closure funSerial, [env], _ ->
    mirifyExprInfClosure ctx funSerial env ty loc
  | t ->
    failwithf "Never: %A" t

let mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init
  let ctx =
    if exhaustive then ctx else
    ctxAddErr ctx "Let pattern must be exhaustive for now" letLoc
  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprLetFun ctx calleeSerial argPats body next letLoc =
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
  let procStmt = MStmt.Proc ({ Callee = calleeSerial; Args = args; ResultTy = resultTy; Body = body }, letLoc)
  let ctx = ctxAddStmt ctx procStmt

  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprTyDecl ctx _tySerial _tyDecl loc =
  MExpr.Default (tyUnit, loc), ctx

let mirifyExprOpen ctx loc =
  MExpr.Default (tyUnit, loc), ctx

let mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HExpr.Lit (lit, loc) ->
    MExpr.Lit (lit, loc), ctx
  | HExpr.Ref (_, serial, ty, loc) ->
    mirifyExprRef ctx serial ty loc
  | HExpr.Match (target, arms, ty, loc) ->
    mirifyExprMatch ctx target arms ty loc
  | HExpr.Op (op, l, r, ty, loc) ->
    mirifyExprOp ctx op l r ty loc
  | HExpr.Inf (infOp, args, ty, loc) ->
    mirifyExprInf ctx infOp args ty loc
  | HExpr.Let (pat, body, next, _, loc) ->
    mirifyExprLetVal ctx pat body next loc
  | HExpr.LetFun (_, serial, args, body, next, _, loc) ->
    mirifyExprLetFun ctx serial args body next loc
  | HExpr.TyDef (_, tySerial, tyDecl, loc) ->
    mirifyExprTyDecl ctx tySerial tyDecl loc
  | HExpr.Open (_, loc) ->
    mirifyExprOpen ctx loc
  | HExpr.If _
  | HExpr.Nav _
  | HExpr.Inf (InfOp.Anno, _, _, _)
  | HExpr.Inf (InfOp.Tuple, _, _, _)
  | HExpr.Inf (InfOp.List _, _, _, _) ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    let ctx = ctxAddErr ctx error loc
    MExpr.Default (tyObj, loc), ctx

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      List.rev acc, ctx
    | expr :: exprs ->
      let expr, ctx = mirifyExpr ctx expr
      go (expr :: acc) ctx exprs
  go [] ctx exprs

/// Collect all declaration contained by the statements.
let collectDecls (stmts: MStmt list) =
  let rec go decls stmts =
    match stmts with
    | MStmt.Proc (procDecl, loc) :: stmts ->
      let decls = MDecl.Proc (procDecl, loc) :: decls
      let decls = go decls procDecl.Body
      go decls stmts
    | _ :: stmts ->
      go decls stmts
    | [] ->
      decls
  go [] stmts

let mirify (expr: HExpr, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = ctxFromTyCtx tyCtx

  // FIXME: Don't discard the result expression because it may cause some effects.
  let _expr, ctx = mirifyExpr ctx expr

  let decls = collectDecls ctx.Stmts
  decls, ctx
