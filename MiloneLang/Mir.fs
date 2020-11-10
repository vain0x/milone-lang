/// Converts HIR to mid-level intermediate representation (MIR).
///
/// MIR is a procedural, non-recursive, similar to C, IR.
///
/// Deconstructs pattern matching.
module rec MiloneLang.Mir

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

/// Checks whether an expr (body of fun) contains tail-rec call.
let private containsTailRec expr =
  match expr with
  | HInfExpr (InfOp.CallTailRec, _, _, _) -> true

  | HInfExpr (InfOp.Semi, items, _, _) -> items |> List.last |> containsTailRec

  | HLitExpr _
  | HRefExpr _
  | HPrimExpr _
  | HNavExpr _
  | HInfExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> false

  | HMatchExpr (_, arms, _, _) ->
      arms
      |> List.exists (fun (_, _, body) -> body |> containsTailRec)


  | HLetValExpr (_, _, _, next, _, _) -> next |> containsTailRec

  | HLetFunExpr (_, _, _, _, _, next, _, _) -> next |> containsTailRec

  | HErrorExpr _ -> failwithf "NEVER: %A" expr
  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let mirCtxFromTyCtx (tyCtx: TyCtx): MirCtx =
  MirCtx(tyCtx |> tyCtxGetSerial, tyCtx |> tyCtxGetVars, tyCtx |> tyCtxGetTys, 0, None, [], tyCtx |> tyCtxGetLogs)

let mirCtxIsNewTypeVariant (ctx: MirCtx) varSerial =
  match ctx |> mirCtxGetVars |> mapFind varSerial with
  | VariantDef (_, tySerial, _, _, _, _) ->
      match ctx |> mirCtxGetTys |> mapFind tySerial with
      | UnionTyDef (_, variantSerials, _) -> variantSerials |> List.length = 1

      | _ -> failwith "Expected union serial"

  | _ -> failwith "Expected variant serial"

let mirCtxAddErr (ctx: MirCtx) message loc =
  ctx
  |> mirCtxWithLogs ((Log.Error message, loc) :: (ctx |> mirCtxGetLogs))

let mirCtxNewBlock (ctx: MirCtx) = ctx |> mirCtxWithStmts []

let mirCtxRollBack (bCtx: MirCtx) (dCtx: MirCtx) =
  dCtx |> mirCtxWithStmts (bCtx |> mirCtxGetStmts)

let mirCtxPrependStmt ctx stmt =
  ctx
  |> mirCtxWithStmts (listAppend (ctx |> mirCtxGetStmts) [ stmt ])

let mirCtxAddStmt (ctx: MirCtx) (stmt: MStmt) =
  ctx
  |> mirCtxWithStmts (stmt :: (ctx |> mirCtxGetStmts))

/// Returns statements in reversed order.
let mirCtxTakeStmts (ctx: MirCtx) =
  ctx |> mirCtxGetStmts, ctx |> mirCtxWithStmts []

let mirCtxFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let serial = (ctx |> mirCtxGetSerial) + 1

  let ctx =
    ctx
    |> mirCtxWithSerial ((ctx |> mirCtxGetSerial) + 1)
    |> mirCtxWithVars
         (ctx
          |> mirCtxGetVars
          |> mapAdd serial (VarDef(ident, AutoSM, ty, loc)))

  let refExpr = MRefExpr(serial, ty, loc)
  refExpr, serial, ctx

let mirCtxLetFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let refExpr, serial, ctx = mirCtxFreshVar ctx ident ty loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(serial, MUninitInit, ty, loc))

  let setStmt expr = MSetStmt(serial, expr, loc)
  refExpr, setStmt, ctx

let mirCtxFreshLabel (ctx: MirCtx) (ident: Ident) loc =
  let serial = (ctx |> mirCtxGetLabelSerial) + 1

  let ctx =
    ctx
    |> mirCtxWithLabelSerial ((ctx |> mirCtxGetLabelSerial) + 1)

  let label: Label = ident + "_" + string serial
  let labelStmt = MLabelStmt(label, loc)
  labelStmt, label, ctx

/// Gets if the serial denotes to a variant function.
let mirCtxIsVariantFun (ctx: MirCtx) serial =
  match ctx |> mirCtxGetVars |> mapTryFind serial with
  | Some (VariantDef _) -> true
  | _ -> false

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let mxProj expr index resultTy loc =
  MUnaryExpr(MProjUnary index, expr, resultTy, loc)

let mxStrAdd ctx _op l r (_, loc) =
  MBinaryExpr(MStrAddBinary, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let mxBinOpScalar ctx op l r (ty, loc) = MBinaryExpr(op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let mxStrCmp ctx op l r (ty, loc) =
  let strCmpExpr =
    MBinaryExpr(MStrCmpBinary, l, r, tyInt, loc)

  let zeroExpr = MLitExpr(IntLit 0, loc)

  let opExpr =
    MBinaryExpr(op, strCmpExpr, zeroExpr, ty, loc)

  opExpr, ctx

/// Generates a comparison expression.
let mxCmp ctx (op: MBinary) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprToTy l with
  | AppTy ((BoolTyCtor
           | IntTyCtor
           | UIntTyCtor
           | CharTyCtor),
           _) -> mxBinOpScalar ctx op l r (ty, loc)
  | AppTy (StrTyCtor, _) -> mxStrCmp ctx op l r (ty, loc)
  | _ -> failwithf "unimpl %A" (op, l, ty)

let mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MLitExpr(lit, loc)

  let eqExpr, ctx =
    mxCmp ctx MEqualBinary expr litExpr tyBool loc

  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr =
    MUnaryExpr(MListIsEmptyUnary, expr, tyList itemTy, loc)

  let gotoStmt = msGotoUnless isEmptyExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let mirifyPatNone ctx endLabel itemTy expr loc =
  mirifyPatNil ctx endLabel itemTy expr loc

let mirifyPatCons ctx endLabel l r itemTy loc expr =
  let listTy = tyList itemTy

  let isEmpty =
    MUnaryExpr(MListIsEmptyUnary, expr, tyBool, loc)

  let nonEmpty =
    MUnaryExpr(MNotUnary, isEmpty, tyBool, loc)

  let gotoStmt = msGotoUnless nonEmpty endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt

  let head =
    MUnaryExpr(MListHeadUnary, expr, itemTy, loc)

  let tail =
    MUnaryExpr(MListTailUnary, expr, listTy, loc)

  let _, ctx = mirifyPat ctx endLabel l head
  let _, ctx = mirifyPat ctx endLabel r tail
  false, ctx

let mirifyPatSome ctx endLabel item itemTy loc expr =
  let nilPat = HNilPat(itemTy, loc)
  mirifyPatCons ctx endLabel item nilPat itemTy loc expr

let mirifyPatRef (ctx: MirCtx) endLabel serial ty loc expr =
  match ctx |> mirCtxGetVars |> mapFind serial with
  | VariantDef _ ->
      // Compare tags.
      let lTagExpr = MUnaryExpr(MTagUnary, expr, tyInt, loc)
      let rTagExpr = MRefExpr(serial, tyInt, loc)

      let eqExpr =
        MBinaryExpr(MEqualBinary, lTagExpr, rTagExpr, tyBool, loc)

      let gotoStmt = msGotoUnless eqExpr endLabel loc
      let ctx = mirCtxAddStmt ctx gotoStmt
      false, ctx
  | _ ->
      let letStmt =
        MLetValStmt(serial, MExprInit expr, ty, loc)

      true, mirCtxAddStmt ctx letStmt

let mirifyPatCall (ctx: MirCtx) endLabel serial args ty loc expr =
  match ctx |> mirCtxGetVars |> mapFind serial, args with
  | VariantDef (_, _, _, payloadTy, _, _), [ payload ] ->
      let extractExpr =
        MUnaryExpr(MGetVariantUnary serial, expr, payloadTy, loc)

      // Special treatment for new-type variants
      // so that we can deconstruct it with irrefutable patterns
      // (`let` and arguments) without generating an abort branch.
      if mirCtxIsNewTypeVariant ctx serial then
        mirifyPat ctx endLabel payload extractExpr
      else

        // Compare tags.
        let lTagExpr = MUnaryExpr(MTagUnary, expr, tyInt, loc)
        let rTagExpr = MRefExpr(serial, tyInt, loc)

        let eqExpr =
          MBinaryExpr(MEqualBinary, lTagExpr, rTagExpr, tyBool, loc)

        let gotoStmt = msGotoUnless eqExpr endLabel loc
        let ctx = mirCtxAddStmt ctx gotoStmt

        // Extract content.
        let _, ctx =
          mirifyPat ctx endLabel payload extractExpr

        false, ctx

  | _ ->
      let letStmt =
        MLetValStmt(serial, MExprInit expr, ty, loc)

      true, mirCtxAddStmt ctx letStmt

let mirifyPatTuple ctx endLabel itemPats itemTys expr loc =
  let rec go covered ctx i itemPats itemTys =
    match itemPats, itemTys with
    | [], [] -> covered, ctx
    | itemPat :: itemPats, itemTy :: itemTys ->
        let item = mxProj expr i itemTy loc
        let itemCovered, ctx = mirifyPat ctx endLabel itemPat item
        go (covered && itemCovered) ctx (i + 1) itemPats itemTys
    | _ -> failwith "Never"

  go true ctx 0 itemPats itemTys

let mirifyPatBox ctx endLabel itemPat expr loc =
  let ty, _ = patExtract itemPat
  mirifyPat ctx endLabel itemPat (MUnaryExpr(MUnboxUnary, expr, ty, loc))

let mirifyPatAs ctx endLabel pat serial expr loc =
  let ty, _ = patExtract pat

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(serial, MExprInit expr, ty, loc))

  let expr = MRefExpr(serial, ty, loc)
  let covers, ctx = mirifyPat ctx endLabel pat expr
  covers, ctx

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
/// Determines if the pattern covers the whole.
let mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr): bool * MirCtx =
  match pat with
  | HDiscardPat _ ->
      // Discard the result, which we know is pure.
      // FIXME: This should be done in optimization?
      true, ctx

  | HLitPat (lit, loc) -> mirifyPatLit ctx endLabel lit expr loc
  | HNilPat (itemTy, loc) -> mirifyPatNil ctx endLabel itemTy expr loc
  | HNonePat (itemTy, loc) -> mirifyPatNone ctx endLabel itemTy expr loc
  | HRefPat (serial, ty, loc) -> mirifyPatRef ctx endLabel serial ty loc expr
  | HCallPat (HRefPat (serial, _, _), args, ty, loc) -> mirifyPatCall ctx endLabel serial args ty loc expr
  | HCallPat (HSomePat (itemTy, loc), [ item ], _, _) -> mirifyPatSome ctx endLabel item itemTy loc expr
  | HConsPat (l, r, itemTy, loc) -> mirifyPatCons ctx endLabel l r itemTy loc expr
  | HTuplePat (itemPats, AppTy (TupleTyCtor, itemTys), loc) -> mirifyPatTuple ctx endLabel itemPats itemTys expr loc
  | HBoxPat (itemPat, loc) -> mirifyPatBox ctx endLabel itemPat expr loc
  | HAsPat (pat, serial, loc) -> mirifyPatAs ctx endLabel pat serial expr loc
  | HSomePat (_, loc) ->
      let ctx =
        mirCtxAddErr ctx "Some pattern must be used in the form of `Some pat`" loc

      false, ctx
  | HOrPat _ -> failwith "Unimpl nested OR pattern."
  | HNavPat _ -> failwith "Never: Nav pattern in mirify"
  | HCallPat _ -> failwith "Never: Call pattern incorrect."
  | HTuplePat _ -> failwith "Never: Tuple pattern must be of tuple type."
  | HAnnoPat _ -> failwith "Never annotation pattern in MIR-ify stage."

let mirifyExprRef (ctx: MirCtx) serial ty loc =
  match ctx |> mirCtxGetVars |> mapTryFind serial with
  | Some (VariantDef (_, tySerial, _, _, _, _)) -> MVariantExpr(tySerial, serial, ty, loc), ctx
  | Some (FunDef (_, _, _, loc)) -> MProcExpr(serial, ty, loc), ctx
  | _ -> MRefExpr(serial, ty, loc), ctx

let mirifyExprPrim (ctx: MirCtx) prim ty loc =
  match prim with
  | HPrim.Nil -> MDefaultExpr(ty, loc), ctx

  | HPrim.OptionNone -> MDefaultExpr(ty, loc), ctx

  | _ -> failwithf "Never: Primitives must appear as callee."

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
    | HDiscardPat _
    | HRefPat _ ->
        // FIXME: unit-like variant patterns may not be covering
        true
    | HLitPat _
    | HNilPat _
    | HNonePat _
    | HSomePat _
    | HNavPat _
    | HConsPat _
    | HCallPat _ -> false
    | HTuplePat (itemPats, _, _) -> itemPats |> List.forall go
    | HBoxPat (itemPat, _) -> go itemPat
    | HAsPat (pat, _, _) -> go pat
    | HAnnoPat (pat, _, _) -> go pat
    | HOrPat (first, second, _, _) -> go first || go second

  List.exists go pats

let mirifyExprMatch ctx target arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = mirCtxLetFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = mirCtxFreshLabel ctx "end_match" loc

  let target, ctx = mirifyExpr ctx target

  let isCovering =
    arms
    |> List.choose (fun (pat, guard, _) -> if hxIsAlwaysTrue guard then Some pat else None)
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
          if not needsJump then
            noLabel, ctx
          else
            let _, bodyLabel, ctx = mirCtxFreshLabel ctx "match_body" loc
            bodyLabel, ctx

        let rec goPats ctx acc firstPat pats =
          match pats with
          | pat :: pats ->
              // Label on the pattern.
              // The first pattern's label is unnecessary and not created.
              let acc, ctx =
                if firstPat then
                  acc, ctx
                else
                  let _, patLabel, ctx = mirCtxFreshLabel ctx "next" loc
                  MatchIR.PatLabel patLabel :: acc, ctx

              let acc = MatchIR.Pat(pat, noLabel) :: acc

              let acc =
                if not needsJump then acc else MatchIR.GoBody bodyLabel :: acc

              goPats ctx acc false pats
          | [] -> acc, ctx

        let acc, ctx = goPats ctx acc firstPat pats

        let acc =
          if not needsJump then acc else MatchIR.BodyLabel bodyLabel :: acc

        let acc = MatchIR.Guard(guard, noLabel) :: acc
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
    | (MatchIR.PatLabel patLabel as instruction) :: rest ->
        // The leading instructions refers to this label as next one.
        fixUp (instruction :: acc) patLabel rest
    | MatchIR.Pat (pat, _) :: rest ->
        let acc = MatchIR.Pat(pat, nextLabel) :: acc
        fixUp acc nextLabel rest
    | MatchIR.Guard (guard, _) :: rest ->
        let acc =
          // Trivial guard is unnecessary.
          if guard |> hxIsAlwaysTrue then acc else MatchIR.Guard(guard, nextLabel) :: acc

        fixUp acc nextLabel rest
    | instruction :: rest -> fixUp (instruction :: acc) nextLabel rest
    | [] -> acc

  /// Emits MIR instructions based on matching IRs.
  let rec emit ctx instructions =
    match instructions with
    | MatchIR.PatLabel patLabel :: rest ->
        let ctx =
          mirCtxAddStmt ctx (MLabelStmt(patLabel, loc))

        emit ctx rest
    | MatchIR.Pat (pat, nextLabel) :: rest ->
        // Perform pattern matching. Go to the next pattern on failure.
        let _, ctx = mirifyPat ctx nextLabel pat target
        emit ctx rest
    | MatchIR.GoBody bodyLabel :: rest ->
        let ctx =
          mirCtxAddStmt ctx (MGotoStmt(bodyLabel, loc))

        emit ctx rest
    | MatchIR.BodyLabel bodyLabel :: rest ->
        let ctx =
          mirCtxAddStmt ctx (MLabelStmt(bodyLabel, loc))

        emit ctx rest
    | MatchIR.Guard (guard, nextLabel) :: rest ->
        let ctx =
          if guard |> hxIsAlwaysTrue then
            ctx
          else
            let guard, ctx = mirifyExpr ctx guard
            mirCtxAddStmt ctx (msGotoUnless guard nextLabel loc)

        emit ctx rest
    | MatchIR.Body body :: rest ->
        // Enter into the body.
        let body, ctx = mirifyExpr ctx body
        // Leave the match.
        let ctx = mirCtxAddStmt ctx (tempSet body)

        let ctx =
          mirCtxAddStmt ctx (MGotoStmt(endLabel, loc))

        emit ctx rest
    | [] ->
        // Abort if exhaust.
        if isCovering then
          ctx
        else
          let abortStmt = MExitStmt(MLitExpr(IntLit 1, loc), loc)

          let ctx = mirCtxAddStmt ctx abortStmt
          ctx

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = mirCtxAddStmt ctx endLabelStmt

  temp, ctx

let mirifyExprIndex ctx l r _ loc =
  match exprToTy l, exprToTy r with
  | AppTy (StrTyCtor, _), AppTy (IntTyCtor, _) ->
      let l, ctx = mirifyExpr ctx l
      let r, ctx = mirifyExpr ctx r
      MBinaryExpr(MStrIndexBinary, l, r, tyChar, loc), ctx
  | _ -> failwith "unimpl non-string indexing"

let mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  let ctx = mirCtxAddStmt ctx (MExitStmt(arg, loc))
  MDefaultExpr(ty, loc), ctx

let mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = mirCtxFreshVar ctx "box" tyObj loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MBoxInit arg, tyObj, loc))

  temp, ctx

let mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MUnboxUnary, arg, ty, loc), ctx

let mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MStrLenUnary, arg, ty, loc), ctx

let mirifyExprCallSome ctx item ty loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "some" ty loc

  let item, ctx = mirifyExpr ctx item
  let nil = MDefaultExpr(ty, loc)

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MConsInit(item, nil), ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

/// not a ==> !a
let mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MNotUnary, arg, ty, notLoc), ctx

let mirifyExprCallVariantFun (ctx: MirCtx) serial payload ty loc =
  let payload, ctx = mirifyExpr ctx payload
  let payloadTy = mexprToTy payload

  // FIXME: Generate a serial to reduce diff. Remove this later.
  let _, _payloadSerial, ctx =
    mirCtxFreshVar ctx "payload" payloadTy loc

  let temp, tempSerial, ctx = mirCtxFreshVar ctx "variant" ty loc
  let init = MVariantInit(serial, payload)

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, init, ty, loc))

  temp, ctx

let mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MConsInit(l, r), listTy, loc))

  MRefExpr(tempSerial, listTy, loc), ctx

let mirifyExprTuple ctx items itemTys loc =
  let ty = tyTuple itemTys
  let _, tempSerial, ctx = mirCtxFreshVar ctx "tuple" ty loc

  let rec go acc ctx items =
    match items with
    | [] -> List.rev acc, ctx
    | item :: items ->
        let item, ctx = mirifyExpr ctx item
        go (item :: acc) ctx items

  let items, ctx = go [] ctx items

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MTupleInit items, ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

let mirifyExprTupleItem ctx index tuple itemTy loc =
  let tuple, ctx = mirifyExpr ctx tuple
  MUnaryExpr(MProjUnary index, tuple, itemTy, loc), ctx

let mirifyExprOpArith ctx op l r ty loc =
  let lTy = exprToTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match lTy with
  | AppTy ((IntTyCtor
           | UIntTyCtor
           | CharTyCtor),
           _) -> mxBinOpScalar ctx op l r (ty, loc)

  | AppTy (StrTyCtor, _) when op |> mOpIsAdd -> mxStrAdd ctx op l r (ty, loc)

  | _ ->
      // FIXME: error
      printfn "#error invalid type of arithmetic operator"
      MDefaultExpr(ty, loc), ctx

let mirifyExprOpCmp ctx op l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  mxCmp ctx op l r ty loc

let mirifyExprSemi ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let mirifyExprInfCallProc ctx callee args ty loc =
  let core () =
    match callee with
    | HPrimExpr (prim, _, _) ->
        let primTy = exprToTy callee

        let (args, ctx) =
          (args, ctx)
          |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

        let temp, tempSerial, ctx = mirCtxFreshVar ctx "call" ty loc

        let ctx =
          mirCtxAddStmt ctx (MLetValStmt(tempSerial, MCallPrimInit(prim, args, primTy), ty, loc))

        temp, ctx
    | _ ->
        let calleeTy = exprToTy callee
        let callee, ctx = mirifyExpr ctx callee

        let (args, ctx) =
          (args, ctx)
          |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

        let temp, tempSerial, ctx = mirCtxFreshVar ctx "call" ty loc

        let ctx =
          mirCtxAddStmt ctx (MLetValStmt(tempSerial, MCallProcInit(callee, args, calleeTy), ty, loc))

        temp, ctx

  match callee, args with
  | HPrimExpr (prim, _, _), _ ->
      match prim, args with
      | HPrim.Add, [ l; r ] -> mirifyExprOpArith ctx MAddBinary l r ty loc
      | HPrim.Sub, [ l; r ] -> mirifyExprOpArith ctx MSubBinary l r ty loc
      | HPrim.Mul, [ l; r ] -> mirifyExprOpArith ctx MMulBinary l r ty loc
      | HPrim.Div, [ l; r ] -> mirifyExprOpArith ctx MDivBinary l r ty loc
      | HPrim.Mod, [ l; r ] -> mirifyExprOpArith ctx MModBinary l r ty loc
      | HPrim.Eq, [ l; r ] -> mirifyExprOpCmp ctx MEqualBinary l r ty loc
      | HPrim.Lt, [ l; r ] -> mirifyExprOpCmp ctx MLessBinary l r ty loc
      | HPrim.Cons, [ l; r ] -> mirifyExprOpCons ctx l r ty loc
      | HPrim.Index, [ l; r ] -> mirifyExprIndex ctx l r ty loc
      | HPrim.OptionSome, [ item ] -> mirifyExprCallSome ctx item ty loc
      | HPrim.Not, [ arg ] -> mirifyExprCallNot ctx arg ty loc
      | HPrim.Exit, [ arg ] -> mirifyExprCallExit ctx arg ty loc
      | HPrim.Box, [ arg ] -> mirifyExprCallBox ctx arg ty loc
      | HPrim.Unbox, [ arg ] -> mirifyExprCallUnbox ctx arg ty loc
      | HPrim.StrLength, [ arg ] -> mirifyExprCallStrLength ctx arg ty loc
      | _ -> core ()

  | HRefExpr (serial, _, _), [ arg ] when mirCtxIsVariantFun ctx serial ->
      mirifyExprCallVariantFun ctx serial arg ty loc

  | _ -> core ()

let mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee

  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "app" resultTy loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MCallClosureInit(callee, args), resultTy, loc))

  tempRef, ctx

let mirifyExprInfCallTailRec ctx _callee args ty loc =
  // It's guaranteed that callee points to the current fun,
  // but it's serial can now be wrong due to monomorphization.

  let label, argSerials =
    match ctx |> mirCtxGetCurrentFun with
    | Some it -> it
    | None -> failwithf "NEVER: current fun must exists. %A" loc

  // Evaluate args and assign to temp vars.
  let tempExprs, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) ->
         let ty, loc = exprExtract arg
         let tempVarExpr, tempVarSerial, ctx = mirCtxFreshVar ctx "arg" ty loc

         let arg, ctx = mirifyExpr ctx arg

         let ctx =
           mirCtxAddStmt ctx (MLetValStmt(tempVarSerial, MExprInit arg, ty, loc))

         tempVarExpr, ctx)

  // Update args.
  let ctx =
    let rec go ctx argSerials tempExprs =
      match argSerials, tempExprs with
      | [], [] -> ctx

      | argSerial :: argSerials, tempExpr :: tempExprs ->
          let ctx =
            mirCtxAddStmt ctx (MSetStmt(argSerial, tempExpr, loc))

          go ctx argSerials tempExprs

      | _ -> failwithf "NEVER: Arity mismatch. %A" loc

    go ctx argSerials tempExprs

  let ctx =
    mirCtxAddStmt ctx (MGotoStmt(label, loc))

  MDefaultExpr(ty, loc), ctx

let mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = mirCtxFreshVar ctx "env" envTy envLoc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(envSerial, MExprInit env, envTy, envLoc))

  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "fun" funTy loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MClosureInit(funSerial, envSerial), funTy, loc))

  tempRef, ctx

let mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.Tuple, [], AppTy (TupleTyCtor, []) -> MDefaultExpr(tyUnit, loc), ctx
  | InfOp.Tuple, _, AppTy (TupleTyCtor, itemTys) -> mirifyExprTuple ctx args itemTys loc
  | InfOp.TupleItem index, [ tuple ], itemTy -> mirifyExprTupleItem ctx index tuple itemTy loc
  | InfOp.Semi, _, _ -> mirifyExprSemi ctx args
  | InfOp.CallProc, callee :: args, _ -> mirifyExprInfCallProc ctx callee args ty loc
  | InfOp.CallTailRec, callee :: args, _ -> mirifyExprInfCallTailRec ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ -> mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.Closure, [ HRefExpr (funSerial, _, _); env ], _ -> mirifyExprInfClosure ctx funSerial env ty loc
  | t -> failwithf "Never: %A" t

let mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init

  let ctx =
    if exhaustive
    then ctx
    else mirCtxAddErr ctx "Let pattern must be exhaustive for now" letLoc

  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprLetFun ctx calleeSerial isMainFun argPats body next letLoc =
  let prepareTailRec ctx args =
    let parentFun = ctx |> mirCtxGetCurrentFun

    let currentFun, ctx =
      if body |> containsTailRec then
        let labelStmt, label, ctx = mirCtxFreshLabel ctx "tailrec" letLoc
        let ctx = mirCtxPrependStmt ctx labelStmt
        let argSerials = args |> List.map (fun (it, _, _) -> it)
        Some(label, argSerials), ctx
      else
        None, ctx

    let ctx = ctx |> mirCtxWithCurrentFun currentFun
    parentFun, ctx

  let cleanUpTailRec ctx parentFun = ctx |> mirCtxWithCurrentFun parentFun

  let defineArg ctx argPat =
    match argPat with
    | HRefPat (serial, ty, loc) ->
        // NOTE: Optimize for usual cases to not generate redundant local vars.
        (serial, ty, loc), ctx
    | _ ->
        let argTy, argLoc = patExtract argPat
        let arg, argSerial, ctx = mirCtxFreshVar ctx "arg" argTy argLoc
        let exhaustive, ctx = mirifyPat ctx "_never_" argPat arg

        let ctx =
          if exhaustive
          then ctx
          else mirCtxAddErr ctx "Argument pattern must be exhaustive for now" argLoc

        (argSerial, argTy, argLoc), ctx

  let rec defineArgs acc ctx argPats =
    match argPats with
    | [] -> List.rev acc, ctx
    | argPat :: argPats ->
        let arg, ctx = defineArg ctx argPat
        defineArgs (arg :: acc) ctx argPats

  let mirifyFunBody ctx argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let parentFun, ctx = prepareTailRec ctx args
    let lastExpr, ctx = mirifyExpr ctx body
    let returnStmt = MReturnStmt(lastExpr, blockLoc)
    let ctx = mirCtxAddStmt ctx returnStmt

    let ctx = cleanUpTailRec ctx parentFun
    let stmts, ctx = mirCtxTakeStmts ctx
    let body = List.rev stmts
    args, blockTy, body, ctx

  let core () =
    let bodyCtx = mirCtxNewBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = mirCtxRollBack ctx bodyCtx

    let procStmt =
      MProcStmt(calleeSerial, isMainFun, args, body, resultTy, letLoc)

    let ctx = mirCtxAddStmt ctx procStmt
    ctx

  let ctx = core ()
  let next, ctx = mirifyExpr ctx next
  next, ctx

let mirifyExprTyDecl ctx _tySerial _tyDecl loc = MDefaultExpr(tyUnit, loc), ctx

let mirifyExprOpen ctx loc = MDefaultExpr(tyUnit, loc), ctx

let mirifyDecl ctx expr =
  match expr with
  | HLetValExpr (_vis, pat, body, next, _, loc) -> mirifyExprLetVal ctx pat body next loc
  | HLetFunExpr (serial, _vis, isMainFun, args, body, next, _, loc) ->
      mirifyExprLetFun ctx serial isMainFun args body next loc
  | HTyDeclExpr (tySerial, _vis, tyDecl, loc) -> mirifyExprTyDecl ctx tySerial tyDecl loc
  | HOpenExpr (_, loc) -> mirifyExprOpen ctx loc
  | _ -> failwith "NEVER"

let mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HLitExpr (lit, loc) -> MLitExpr(lit, loc), ctx
  | HRefExpr (serial, ty, loc) -> mirifyExprRef ctx serial ty loc
  | HPrimExpr (prim, ty, loc) -> mirifyExprPrim ctx prim ty loc
  | HMatchExpr (target, arms, ty, loc) -> mirifyExprMatch ctx target arms ty loc
  | HInfExpr (infOp, args, ty, loc) -> mirifyExprInf ctx infOp args ty loc
  | HLetValExpr _
  | HLetFunExpr _
  | HTyDeclExpr _
  | HOpenExpr _ -> mirifyDecl ctx expr
  | HErrorExpr (error, loc) ->
      let doArm () =
        let ctx = mirCtxAddErr ctx error loc
        MDefaultExpr(tyObj, loc), ctx

      doArm ()

  | HNavExpr _ -> failwith "NEVER: nav expr is resolved in NameRes, Typing, or TyElaborating"
  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] -> List.rev acc, ctx
    | expr :: exprs ->
        let expr, ctx = mirifyExpr ctx expr
        go (expr :: acc) ctx exprs

  go [] ctx exprs

/// Collect all declaration contained by the statements.
let mirifyCollectDecls (stmts: MStmt list) =
  let rec go decls stmts =
    match stmts with
    | (MProcStmt (_, _, _, body, _, _) as decl) :: stmts ->
        let doArm () =
          let decls = go decls body
          let decls = decl :: decls
          let decls = go decls stmts
          decls

        doArm ()
    | _ :: stmts -> go decls stmts
    | [] -> decls

  go [] stmts |> List.rev

let mirify (expr: HExpr, tyCtx: TyCtx): MStmt list * MirCtx =
  let ctx = mirCtxFromTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx = mirifyExpr ctx expr

  let stmts = ctx |> mirCtxGetStmts |> List.rev
  let decls = mirifyCollectDecls stmts
  decls, ctx
