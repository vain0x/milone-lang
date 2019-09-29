/// Converts HIR to mid-level intermediate representation (MIR).
///
/// MIR is a procedural, non-recursive, similar to C, IR.
///
/// Deconstructs pattern matching.
module rec MiloneLang.Mir

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

/// Middle IR generation context.
[<RequireQualifiedAccess>]
type MirCtx =
  {
    Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>
    LabelSerial: Serial
    Stmts: MStmt list
    Logs: (Log * Loc) list
  }

let mirCtxFromTyCtx (tyCtx: TyCtx): MirCtx =
  {
    Serial = tyCtx |> tyCtxGetSerial
    Vars = tyCtx |> tyCtxGetVars
    Tys = tyCtx |> tyCtxGetTys
    LabelSerial = 0
    Stmts = []
    Logs = tyCtx |> tyCtxGetLogs
  }

let mirCtxIsNewTypeVariant (ctx: MirCtx) varSerial =
  match ctx.Vars |> mapFind varSerial with
  | VarDef.Variant (_, tySerial, _, _, _, _) ->
    match ctx.Tys |> mapFind tySerial with
    | TyDef.Union (_, variantSerials, _) ->
      variantSerials |> listLength = 1

    | _ ->
      failwith "Expected union serial"

  | _ ->
    failwith "Expected variant serial"

let mirCtxAddErr (ctx: MirCtx) message loc =
  { ctx with Logs = (Log.Error message, loc) :: ctx.Logs }

let mirCtxNewBlock (ctx: MirCtx) =
  { ctx with Stmts = [] }

let mirCtxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  { dCtx with Stmts = bCtx.Stmts }

let mirCtxAddStmt (ctx: MirCtx) (stmt: MStmt) =
  { ctx with Stmts = stmt :: ctx.Stmts }

/// Returns statements in reversed order.
let mirCtxTakeStmts (ctx: MirCtx) =
  ctx.Stmts, { ctx with Stmts = [] }

let mirCtxFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let serial = ctx.Serial + 1
  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> mapAdd serial (VarDef.Var (ident, ty, loc))
    }
  let refExpr = MExpr.Ref (serial, ty, loc)
  refExpr, serial, ctx

let mirCtxLetFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let refExpr, serial, ctx = mirCtxFreshVar ctx ident ty loc
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (serial, MInit.UnInit, ty, loc))
  let setStmt expr = MStmt.Set (serial, expr, loc)
  refExpr, setStmt, ctx

let mirCtxFreshLabel (ctx: MirCtx) (ident: Ident) loc =
  let serial = ctx.LabelSerial + 1
  let ctx = { ctx with LabelSerial = ctx.LabelSerial + 1 }
  let label: Label = sprintf "%s_%d" ident serial
  let labelStmt = MStmt.Label (label, loc)
  labelStmt, label, ctx

/// Gets if the serial denotes to a variant function.
let mirCtxIsVariantFun (ctx: MirCtx) serial =
  match ctx.Vars |> mapTryFind serial with
  | Some (VarDef.Variant _) ->
    true
  | _ ->
    false

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let mxProj expr index resultTy loc =
  MExpr.Uni (MUniOp.Proj index, expr, resultTy, loc)

let mxStrAdd ctx _op l r (_, loc) =
  MExpr.Bin (MOp.StrAdd, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let mxBinOpScalar ctx op l r (ty, loc) =
  MExpr.Bin (op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let mxStrCmp ctx op l r (ty, loc) =
  let strCmpExpr = MExpr.Bin (MOp.StrCmp, l, r, tyInt, loc)
  let zeroExpr = MExpr.Lit (Lit.Int 0, loc)
  let opExpr = MExpr.Bin (op, strCmpExpr, zeroExpr, ty, loc)
  opExpr, ctx

/// Generates a comparison expression.
let mxCmp ctx (op: MOp) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprToTy l with
  | Ty.Con ((TyCon.Bool | TyCon.Int | TyCon.Char), _) ->
    mxBinOpScalar ctx op l r (ty, loc)
  | Ty.Con (TyCon.Str, _) ->
    mxStrCmp ctx op l r (ty, loc)
  | _ ->
    failwith "unimpl"

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MExpr.Lit (lit, loc)
  let eqExpr, ctx = mxCmp ctx MOp.Eq expr litExpr tyBool loc
  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr = MExpr.Uni (MUniOp.ListIsEmpty, expr, tyList itemTy, loc)
  let gotoStmt = msGotoUnless isEmptyExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNone ctx endLabel itemTy expr loc =
  mirifyPatNil ctx endLabel itemTy expr loc

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let listTy = tyList itemTy
  let isEmpty = MExpr.Uni (MUniOp.ListIsEmpty, expr, tyBool, loc)
  let nonEmpty = MExpr.Uni (MUniOp.Not, isEmpty, tyBool, loc)
  let gotoStmt = msGotoUnless nonEmpty endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  let head = MExpr.Uni (MUniOp.ListHead, expr, itemTy, loc)
  let tail = MExpr.Uni (MUniOp.ListTail, expr, listTy, loc)
  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

let mirifyPatSome ctx endLabel item itemTy loc expr =
  let nilPat = HPat.Nil (itemTy, loc)
  mirifyPatCons ctx endLabel item nilPat itemTy loc expr

let mirifyPatRef (ctx: MirCtx) endLabel serial ty loc expr =
  match ctx.Vars |> mapFind serial with
  | VarDef.Variant _ ->
    // Compare tags.
    let lTagExpr = MExpr.Uni (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Bin (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
    let gotoStmt = msGotoUnless eqExpr endLabel loc
    let ctx = mirCtxAddStmt ctx gotoStmt
    false, ctx
  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, mirCtxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx.Vars |> mapFind serial, args with
  | VarDef.Variant (_, _, _, payloadTy, _, _), [payload] ->
    let extractExpr = MExpr.Uni (MUniOp.GetVariant serial, expr, payloadTy, loc)

    // Special treatment for new-type variants
    // so that we can deconstruct it with irrefutable patterns
    // (`let` and arguments) without generating an abort branch.
    if mirCtxIsNewTypeVariant ctx serial then
      mirifyPat ctx endLabel payload extractExpr
    else

    // Compare tags.
    let lTagExpr = MExpr.Uni (MUniOp.Tag, expr, tyInt, loc)
    let rTagExpr = MExpr.Ref (serial, tyInt, loc)
    let eqExpr = MExpr.Bin (MOp.Eq, lTagExpr, rTagExpr, tyBool, loc)
    let gotoStmt = msGotoUnless eqExpr endLabel loc
    let ctx = mirCtxAddStmt ctx gotoStmt

    // Extract content.
    let _, ctx = mirifyPat ctx endLabel payload extractExpr
    false, ctx

  | _ ->
    let letStmt = MStmt.LetVal (serial, MInit.Expr expr, ty, loc)
    true, mirCtxAddStmt ctx letStmt

let mirifyPatTuple ctx endLabel itemPats itemTys expr loc =
  let rec go covered ctx i itemPats itemTys =
    match itemPats, itemTys with
    | [], [] ->
      covered, ctx
    | itemPat :: itemPats, itemTy :: itemTys ->
      let item = mxProj expr i itemTy loc
      let itemCovered, ctx = mirifyPat ctx endLabel itemPat item
      go (covered && itemCovered) ctx (i + 1) itemPats itemTys
    | _ ->
      failwith "Never"
  go true ctx 0 itemPats itemTys

let mirifyPatAs ctx endLabel pat serial expr loc =
  let ty, _ = patExtract pat
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (serial, MInit.Expr expr, ty, loc))
  let expr = MExpr.Ref (serial, ty, loc)
  let covers, ctx = mirifyPat ctx endLabel pat expr
  covers, ctx

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
/// Determines if the pattern covers the whole.
let mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr): bool * MirCtx =
  match pat with
  | HPat.Discard _ ->
    // Discard the result, which we know is pure.
    // FIXME: This should be done in optimization?
    true, ctx

  | HPat.Lit (lit, loc) ->
    mirifyPatLit ctx endLabel lit expr loc
  | HPat.Nil (itemTy, loc) ->
    mirifyPatNil ctx endLabel itemTy expr loc
  | HPat.OptionNone (itemTy, loc) ->
    mirifyPatNone ctx endLabel itemTy expr loc
  | HPat.Ref (serial, ty, loc) ->
    mirifyPatRef ctx endLabel serial ty loc expr
  | HPat.Call (HPat.Ref (serial, _, _), args, ty, loc) ->
    mirifyPatCall ctx endLabel serial args ty loc expr
  | HPat.Call (HPat.OptionSome (itemTy, loc), [item], _, _) ->
    mirifyPatSome ctx endLabel item itemTy loc expr
  | HPat.Cons (l, r, itemTy, loc) ->
    mirifyPatCons ctx endLabel l r itemTy loc expr
  | HPat.Tuple (itemPats, Ty.Con (TyCon.Tuple, itemTys), loc) ->
    mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | HPat.As (pat, serial, loc) ->
    mirifyPatAs ctx endLabel pat serial expr loc
  | HPat.OptionSome (_, loc) ->
    let ctx = mirCtxAddErr ctx "Some pattern must be used in the form of `Some pat`" loc
    false, ctx
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

let mirifyExprRef (ctx: MirCtx) serial ty loc =
  match ctx.Vars |> mapTryFind serial with
  | Some (VarDef.Variant (_, tySerial, _, _, _, _)) ->
    MExpr.Variant (tySerial, serial, ty, loc), ctx
  | Some (VarDef.Fun (_, _, _, loc)) ->
    MExpr.Proc (serial, ty, loc), ctx
  | _ ->
    MExpr.Ref (serial, ty, loc), ctx

let mirifyExprPrim (ctx: MirCtx) prim ty loc =
  match prim with
  | HPrim.Nil ->
    MExpr.Default (ty, loc), ctx

  | HPrim.OptionNone ->
    MExpr.Default (ty, loc), ctx

  | _ ->
    failwithf "Never: Primitives must appear as callee."

let mirifyBlock ctx expr =
  let blockCtx = mirCtxNewBlock ctx
  let expr, blockCtx = mirifyExpr blockCtx expr
  let stmts, blockCtx = mirCtxTakeStmts blockCtx
  let ctx = mirCtxRollBack ctx blockCtx
  stmts, expr, ctx

/// Gets if the target must match with any of the patterns.
let patsIsCovering pats =
  let rec go pat =
    match pat with
    | HPat.Discard _
    | HPat.Ref _ ->
      // FIXME: unit-like variant patterns may not be covering
      true
    | HPat.Lit _
    | HPat.Nil _
    | HPat.OptionNone _
    | HPat.OptionSome _
    | HPat.Nav _
    | HPat.Cons _
    | HPat.Call _ ->
      false
    | HPat.Tuple (itemPats, _, _) ->
      itemPats |> listForAll go
    | HPat.As (pat, _, _) ->
      go pat
    | HPat.Anno (pat, _, _) ->
      go pat
    | HPat.Or (first, second, _, _) ->
      go first || go second
  listExists go pats

let mirifyExprMatch ctx target arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = mirCtxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = mirCtxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  let isCovering =
    arms
    |> listChoose
      (fun (pat, guard, _) -> if hxIsAlwaysTrue guard then Some pat else None)
    |> patsIsCovering

  /// By walking over arms, calculates what kind of MIR instructions to emit.
  let rec goArms ctx acc firstPat arms =
    match arms with
    | (pat, guard, body) :: arms ->
      let pats = patNormalize pat
      let disjCount = pats |> listLength

      // No need to jump to body from pattern if no OR patterns.
      let needsJump = disjCount > 1

      let bodyLabel, ctx =
        if not needsJump then noLabel, ctx else
        let _, bodyLabel, ctx = mirCtxFreshLabel ctx "match_body" loc
        bodyLabel, ctx

      let rec goPats ctx acc firstPat pats =
        match pats with
        | pat :: pats ->
          // Label on the pattern.
          // The first pattern's label is unnecessary and not created.
          let acc, ctx =
            if firstPat then acc, ctx else
            let _, patLabel, ctx = mirCtxFreshLabel ctx "next" loc
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
      let _, exhaustLabel, ctx = mirCtxFreshLabel ctx "next" loc
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
      let ctx = mirCtxAddStmt ctx (MStmt.Label (patLabel, loc))
      emit ctx rest
    | MatchIR.Pat (pat, nextLabel) :: rest ->
      // Perform pattern matching. Go to the next pattern on failure.
      let _, ctx = mirifyPat ctx nextLabel pat target
      emit ctx rest
    | MatchIR.GoBody bodyLabel :: rest ->
      let ctx = mirCtxAddStmt ctx (MStmt.Goto (bodyLabel, loc))
      emit ctx rest
    | MatchIR.BodyLabel bodyLabel :: rest ->
      let ctx = mirCtxAddStmt ctx (MStmt.Label (bodyLabel, loc))
      emit ctx rest
    | MatchIR.Guard (guard, nextLabel) :: rest ->
      let ctx =
        if guard |> hxIsAlwaysTrue then ctx else
        let guard, ctx = mirifyExpr ctx guard
        mirCtxAddStmt ctx (msGotoUnless guard nextLabel loc)
      emit ctx rest
    | MatchIR.Body body :: rest ->
      // Enter into the body.
      let body, ctx = mirifyExpr ctx body
      // Leave the match.
      let ctx = mirCtxAddStmt ctx (tempSet body)
      let ctx = mirCtxAddStmt ctx (MStmt.Goto (endLabel, loc))
      emit ctx rest
    | [] ->
      // Abort if exhaust.
      if isCovering then ctx else
      let abortStmt = MStmt.Exit (MExpr.Lit (Lit.Int 1, loc), loc)
      let ctx = mirCtxAddStmt ctx abortStmt
      ctx

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = mirCtxAddStmt ctx endLabelStmt

  temp, ctx

let mirifyExprIndex ctx l r _ loc =
  match exprToTy l, exprToTy r with
  | Ty.Con (TyCon.Str, _), Ty.Con (TyCon.Int, _) ->
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MExpr.Bin (MOp.StrIndex, l, r, tyChar, loc), ctx
  | _ ->
    failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let ctx = mirCtxAddStmt ctx (MStmt.Exit (arg, loc))
  MExpr.Default (ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = mirCtxFreshVar ctx "box" tyObj loc
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Box arg, tyObj, loc))
  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.Unbox, arg, ty, loc), ctx

let mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.StrLen, arg, ty, loc), ctx

let mirifyExprCallSome ctx item ty loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "some" ty loc

  let item, ctx = mirifyExpr ctx item
  let nil = MExpr.Default (ty, loc)
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (item, nil), ty, loc))
  MExpr.Ref (tempSerial, ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MExpr.Uni (MUniOp.Not, arg, ty, notLoc), ctx

let mirifyExprCallVariantFun (ctx: MirCtx) serial payload ty loc =
  // Put payload on the heap.
  let payload, ctx = mirifyExpr ctx payload
  let payloadTy = mexprToTy payload
  let _, payloadSerial, ctx = mirCtxFreshVar ctx "payload" payloadTy loc
  let payloadInit = MInit.Indirect payload
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (payloadSerial, payloadInit, payloadTy, loc))

  let temp, tempSerial, ctx = mirCtxFreshVar ctx "variant" ty loc
  let init = MInit.Variant (serial, payloadSerial)
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, init, ty, loc))
  temp, ctx

let mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Cons (l, r), listTy, loc))
  MExpr.Ref (tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let ty = tyTuple itemTys
  let _, tempSerial, ctx = mirCtxFreshVar ctx "tuple" ty loc

  let rec go acc ctx items =
    match items with
    | [] ->
      listRev acc, ctx
    | item :: items ->
      let item, ctx = mirifyExpr ctx item
      go (item :: acc) ctx items
  let items, ctx = go [] ctx items

  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Tuple items, ty, loc))
  MExpr.Ref (tempSerial, ty, loc), ctx

let mirifyExprOpArith ctx op l r ty loc =
  let lTy = exprToTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match lTy with
  | Ty.Con ((TyCon.Int | TyCon.Char), _) ->
    mxBinOpScalar ctx op l r (ty, loc)

  | Ty.Con (TyCon.Str, _) when op = MOp.Add ->
    mxStrAdd ctx op l r (ty, loc)

  | _ ->
    eprintfn "Arithmetic operator %A is not implemented (ty = %A)" op ty
    MExpr.Default (ty, loc), ctx

let mirifyExprOpCmp ctx op l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  mxCmp ctx op l r ty loc

let mirifyExprSemi ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  listLast exprs, ctx

let mirifyExprInfCallProc ctx callee args ty loc =
  let core () =
    match callee with
    | HExpr.Prim (prim, _, _) ->
      let primTy = exprToTy callee
      let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
      let temp, tempSerial, ctx = mirCtxFreshVar ctx "call" ty loc
      let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallPrim (prim, args, primTy), ty, loc))
      temp, ctx
    | _ ->
      let calleeTy = exprToTy callee
      let callee, ctx = mirifyExpr ctx callee
      let (args, ctx) = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
      let temp, tempSerial, ctx = mirCtxFreshVar ctx "call" ty loc
      let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallProc (callee, args, calleeTy), ty, loc))
      temp, ctx

  match callee, args with
  | HExpr.Prim (prim, _, _), _ ->
    match prim, args with
    | HPrim.Add, [l; r] ->
      mirifyExprOpArith ctx MOp.Add l r ty loc
    | HPrim.Sub, [l; r] ->
      mirifyExprOpArith ctx MOp.Sub l r ty loc
    | HPrim.Mul, [l; r] ->
      mirifyExprOpArith ctx MOp.Mul l r ty loc
    | HPrim.Div, [l; r] ->
      mirifyExprOpArith ctx MOp.Div l r ty loc
    | HPrim.Mod, [l; r] ->
      mirifyExprOpArith ctx MOp.Mod l r ty loc
    | HPrim.Eq, [l; r] ->
      mirifyExprOpCmp ctx MOp.Eq l r ty loc
    | HPrim.Lt, [l; r] ->
      mirifyExprOpCmp ctx MOp.Lt l r ty loc
    | HPrim.Cons, [l; r] ->
      mirifyExprOpCons ctx l r ty loc
    | HPrim.Index, [l; r] ->
      mirifyExprIndex ctx l r ty loc
    | HPrim.OptionSome, [item] ->
      mirifyExprCallSome ctx item ty loc
    | HPrim.Not, [arg] ->
      mirifyExprCallNot ctx arg ty loc
    | HPrim.Exit, [arg] ->
      mirifyExprCallExit ctx arg ty loc
    | HPrim.Box, [arg] ->
      mirifyExprCallBox ctx arg ty loc
    | HPrim.Unbox, [arg] ->
      mirifyExprCallUnbox ctx arg ty loc
    | HPrim.StrLength, [arg] ->
      mirifyExprCallStrLength ctx arg ty loc
    | _ ->
      core ()

  | HExpr.Ref (serial, _, _), [arg] when mirCtxIsVariantFun ctx serial ->
    mirifyExprCallVariantFun ctx serial arg ty loc

  | _ ->
    core ()

let mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee
  let args, ctx = (args, ctx) |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)
  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "app" resultTy loc
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.CallClosure (callee, args), resultTy, loc))
  tempRef, ctx

let mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = mirCtxFreshVar ctx "env" envTy envLoc
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (envSerial, MInit.Expr env, envTy, envLoc))

  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "fun" funTy loc
  let ctx = mirCtxAddStmt ctx (MStmt.LetVal (tempSerial, MInit.Closure (funSerial, envSerial), funTy, loc))
  tempRef, ctx

let mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.Tuple, [], Ty.Con (TyCon.Tuple, []) ->
    MExpr.Default (tyUnit, loc), ctx
  | InfOp.Tuple, _, Ty.Con (TyCon.Tuple, itemTys) ->
    mirifyExprTuple ctx args itemTys loc
  | InfOp.Semi, _, _ ->
    mirifyExprSemi ctx args
  | InfOp.CallProc, callee :: args, _ ->
    mirifyExprInfCallProc ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ ->
    mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.Closure, [HExpr.Ref (funSerial, _, _); env], _ ->
    mirifyExprInfClosure ctx funSerial env ty loc
  | t ->
    failwithf "Never: %A" t

let mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init
  let ctx =
    if exhaustive then ctx else
    mirCtxAddErr ctx "Let pattern must be exhaustive for now" letLoc
  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprLetFun ctx calleeSerial isMainFun argPats body next letLoc =
  let defineArg ctx argPat =
    match argPat with
    | HPat.Ref (serial, ty, loc) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      (serial, ty, loc), ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let arg, argSerial, ctx = mirCtxFreshVar ctx "arg" argTy argLoc
      let exhaustive, ctx = mirifyPat ctx "_never_" argPat arg
      let ctx =
        if exhaustive then ctx else
        mirCtxAddErr ctx "Argument pattern must be exhaustive for now" argLoc
      (argSerial, argTy, argLoc), ctx

  let rec defineArgs acc ctx argPats =
    match argPats with
    | [] ->
      listRev acc, ctx
    | argPat :: argPats ->
      let arg, ctx = defineArg ctx argPat
      defineArgs (arg :: acc) ctx argPats

  let mirifyFunBody ctx argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let lastExpr, ctx = mirifyExpr ctx body
    let returnStmt = MStmt.Return (lastExpr, blockLoc)
    let ctx = mirCtxAddStmt ctx returnStmt

    let stmts, ctx = mirCtxTakeStmts ctx
    let body = listRev stmts
    args, blockTy, body, ctx

  let bodyCtx = mirCtxNewBlock ctx
  let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
  let ctx = mirCtxRollBack ctx bodyCtx
  let procStmt = MStmt.Proc ({ Callee = calleeSerial; Args = args; ResultTy = resultTy; Body = body; Main = isMainFun }, letLoc)
  let ctx = mirCtxAddStmt ctx procStmt

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
  | HExpr.Ref (serial, ty, loc) ->
    mirifyExprRef ctx serial ty loc
  | HExpr.Prim (prim, ty, loc) ->
    mirifyExprPrim ctx prim ty loc
  | HExpr.Match (target, arms, ty, loc) ->
    mirifyExprMatch ctx target arms ty loc
  | HExpr.Inf (infOp, args, ty, loc) ->
    mirifyExprInf ctx infOp args ty loc
  | HExpr.Let (pat, body, next, _, loc) ->
    mirifyExprLetVal ctx pat body next loc
  | HExpr.LetFun (serial, isMainFun, args, body, next, _, loc) ->
    mirifyExprLetFun ctx serial isMainFun args body next loc
  | HExpr.TyDecl (tySerial, tyDecl, loc) ->
    mirifyExprTyDecl ctx tySerial tyDecl loc
  | HExpr.Open (_, loc) ->
    mirifyExprOpen ctx loc
  | HExpr.Nav _ ->
    failwith "Never"
  | HExpr.Error (error, loc) ->
    let ctx = mirCtxAddErr ctx error loc
    MExpr.Default (tyObj, loc), ctx

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] ->
      listRev acc, ctx
    | expr :: exprs ->
      let expr, ctx = mirifyExpr ctx expr
      go (expr :: acc) ctx exprs
  go [] ctx exprs

/// Collect all declaration contained by the statements.
let collectDecls (stmts: MStmt list) =
  let rec go decls stmts =
    match stmts with
    | MStmt.Proc (procDecl, loc) :: stmts ->
      let decls = go decls procDecl.Body
      let decls = MDecl.Proc (procDecl, loc) :: decls
      let decls = go decls stmts
      decls
    | _ :: stmts ->
      go decls stmts
    | [] ->
      decls
  go [] stmts |> listRev

let mirify (expr: HExpr, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = mirCtxFromTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx = mirifyExpr ctx expr

  let stmts = ctx.Stmts |> listRev
  let decls = collectDecls stmts
  decls, ctx
