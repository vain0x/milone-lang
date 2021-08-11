/// # MirGen
///
/// Converts HIR to MIR.
///
/// Deconstructs pattern matching.
module rec MiloneTranslation.MirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir
open MiloneTranslation.Mir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

let private unwrapOptionTy ty =
  match ty with
  | Ty (OptionTk, [ it ]) -> it
  | _ -> unreachable ()

let private unwrapListTy ty =
  match ty with
  | Ty (ListTk, [ it ]) -> it
  | _ -> unreachable ()

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MirCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    MainFunOpt: FunSerial option
    Tys: AssocMap<TySerial, TyDef>
    LabelSerial: Serial

    CurrentFunSerial: FunSerial option

    /// (label, parameters), where the label is the entrypoint of current fun.
    /// For tail-rec (tail-call) optimization.
    CurrentFun: (Label * VarSerial list) option

    IsReachable: bool

    FunLocals: AssocMap<FunSerial, (VarSerial * Ty) list>
    ReplacingVars: AssocSet<VarSerial>

    Stmts: MStmt list
    Blocks: MBlock list
    Decls: MDecl list }

let private ofTyCtx (tyCtx: TyCtx) : MirCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    MainFunOpt = tyCtx.MainFunOpt
    Tys = tyCtx.Tys
    LabelSerial = 0
    CurrentFunSerial = None
    CurrentFun = None
    IsReachable = true
    FunLocals = TMap.empty funSerialCompare
    ReplacingVars = TSet.empty varSerialCompare
    Stmts = []
    Blocks = []
    Decls = [] }

let private isNewtypeVariant (ctx: MirCtx) variantSerial =
  (ctx.Variants |> mapFind variantSerial).IsNewtype

let private startBlock (ctx: MirCtx) = { ctx with Stmts = [] }

let private rollback (parentCtx: MirCtx) (ctx: MirCtx) =
  { ctx with
      IsReachable = parentCtx.IsReachable
      Stmts = parentCtx.Stmts }

let private prependStmt (ctx: MirCtx) stmt =
  { ctx with
      Stmts = List.append ctx.Stmts [ stmt ] }

let private addStmtListList (ctx: MirCtx) (stmtListList: MStmt list list) =
  let stmts =
    stmtListList
    |> List.rev
    |> List.fold
         (fun stmts stmtList ->
           stmtList
           |> List.fold (fun stmts stmt -> stmt :: stmts) stmts)
         ctx.Stmts

  { ctx with Stmts = stmts }

let private addStmt (ctx: MirCtx) (stmt: MStmt) =
  match ctx.IsReachable, stmt with
  | _, MLabelStmt _ ->
    { ctx with
        IsReachable = true
        Stmts = stmt :: ctx.Stmts }

  | false, _ -> ctx

  | _, MTerminatorStmt _ ->
    { ctx with
        IsReachable = false
        Stmts = stmt :: ctx.Stmts }

  | _ -> { ctx with Stmts = stmt :: ctx.Stmts }

let private addTerminator (ctx: MirCtx) terminator loc =
  addStmt ctx (MTerminatorStmt(terminator, loc))

let private takeStmts (ctx: MirCtx) =
  List.rev ctx.Stmts, { ctx with Stmts = [] }

let private addDecl (ctx: MirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

let private takeDecls (ctx: MirCtx) =
  List.rev ctx.Decls, { ctx with Decls = [] }

let private freshVar (ctx: MirCtx) (name: Ident) (ty: Ty) loc =
  let varSerial = VarSerial(ctx.Serial + 1)

  let varDef: VarDef =
    { Name = name
      IsStatic = NotStatic
      Ty = noTy // Never used.
      Linkage = InternalLinkage
      Loc = loc }

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> TMap.add varSerial varDef }

  let varExpr = MVarExpr(varSerial, ty, loc)
  varExpr, varSerial, ctx

let private letFreshVar (ctx: MirCtx) (name: Ident) (ty: Ty) loc =
  let varExpr, serial, ctx = freshVar ctx name ty loc

  let ctx =
    addStmt ctx (MLetValStmt(serial, None, ty, loc))

  let setStmt expr = MSetStmt(serial, expr, loc)
  varExpr, setStmt, ctx

let private freshLabel (ctx: MirCtx) (name: Ident) loc =
  let serial = ctx.LabelSerial + 1

  let ctx =
    { ctx with
        LabelSerial = ctx.LabelSerial + 1 }

  let label: Label = name + "_" + string serial
  let labelStmt = MLabelStmt(label, loc)
  labelStmt, label, ctx

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

let private mOpIsAdd op =
  match op with
  | MAddBinary -> true
  | _ -> false

let private opIsComparison op =
  match op with
  | MEqualBinary
  | MLessBinary -> true
  | _ -> false

let private mxNot expr loc =
  MUnaryExpr(MNotUnary, expr, tyBool, loc)

let private mxTupleItem expr index resultTy loc =
  MUnaryExpr(MTupleItemUnary index, expr, resultTy, loc)

let private mxStrAdd ctx _op l r (_, loc) =
  MBinaryExpr(MStrAddBinary, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let private mxBinOpScalar ctx op l r (ty, loc) = MBinaryExpr(op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let private mxStrCompare ctx op l r (ty, loc) =
  let strCompareExpr =
    MBinaryExpr(MStrCompareBinary, l, r, tyInt, loc)

  let zeroExpr = MLitExpr(IntLit "0", loc)

  let opExpr =
    MBinaryExpr(op, strCompareExpr, zeroExpr, ty, loc)

  opExpr, ctx

/// Generates a comparison expression.
let private mxCompare ctx (op: MBinary) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)

  match mexprToTy l with
  | Ty ((IntTk _
        | FloatTk _
        | BoolTk
        | CharTk),
        _) -> mxBinOpScalar ctx op l r (ty, loc)
  | Ty (StrTk, _) -> mxStrCompare ctx op l r (ty, loc)
  | _ -> unreachable ()

/// How `box`/`unbox` works for the type.
[<RequireQualifiedAccess; NoEquality; NoComparisonAttribute>]
type private BoxMode =
  | Null
  | Alloc
  | Cast

let private toBoxMode (ty: Ty) : BoxMode =
  match ty with
  | Ty (IntTk (IntFlavor (_, IPtr)), _) -> BoxMode.Alloc
  | Ty (TupleTk, []) -> BoxMode.Null

  | Ty (IntTk _, _)
  | Ty (BoolTk, _)
  | Ty (CharTk, _)
  | Ty (ObjTk, _)
  | Ty (ListTk, _)
  | Ty (NativePtrTk _, _)
  | Ty (NativeFunTk, _) -> BoxMode.Cast

  | _ -> BoxMode.Alloc

let private mxUnbox expr ty loc : MExpr =
  match toBoxMode ty with
  | BoxMode.Null -> MUnitExpr loc

  | BoxMode.Cast ->
    let expr =
      MUnaryExpr(MNativeCastUnary, expr, tyNativeInt, loc)

    MUnaryExpr(MNativeCastUnary, expr, ty, loc)

  | BoxMode.Alloc -> MUnaryExpr(MUnboxUnary, expr, ty, loc)

let private mtAbort loc =
  MExitTerminator(MLitExpr(IntLit "1", loc))

let private msGotoUnless cond label loc = MGotoIfStmt(mxNot cond loc, label)

// -----------------------------------------------
// Other helpers
// -----------------------------------------------

/// Checks whether an expr (body of fun) contains tail-rec call.
let private containsTailRec expr =
  match expr with
  | HNodeExpr (HCallTailRecEN, _, _, _) -> true

  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _
  | HNavExpr _
  | HNodeExpr _ -> false

  | HMatchExpr (_, arms, _, _) ->
    arms
    |> List.exists (fun (_, _, body) -> body |> containsTailRec)

  | HBlockExpr (_, last) -> last |> containsTailRec

  | HLetValExpr (_, _, next, _, _) -> next |> containsTailRec

  | HLetFunExpr (_, _, _, _, _, next, _, _) -> next |> containsTailRec

  | HRecordExpr _ -> unreachable () // Resolved in RecordRes.

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MLitExpr(lit, loc)

  let equalExpr, ctx =
    mxCompare ctx MEqualBinary expr litExpr tyBool loc

  let gotoStmt = msGotoUnless equalExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
  ctx

let private mirifyPatNone ctx endLabel expr loc =
  let isNoneExpr =
    mxNot (MUnaryExpr(MOptionIsSomeUnary, expr, tyBool, loc)) loc

  let gotoStmt = msGotoUnless isNoneExpr endLabel loc
  addStmt ctx gotoStmt

let private mirifyPatSomeApp ctx endLabel item loc expr =
  let itemTy = patToTy item

  let isSome =
    MUnaryExpr(MOptionIsSomeUnary, expr, tyBool, loc)

  let gotoStmt = msGotoUnless isSome endLabel loc
  let ctx = addStmt ctx gotoStmt

  let value =
    MUnaryExpr(MOptionToValueUnary, expr, itemTy, loc)

  mirifyPat ctx endLabel item value

let private mirifyPatNil ctx endLabel listTy expr loc =
  let itemTy = unwrapListTy listTy

  let isEmptyExpr =
    MUnaryExpr(MListIsEmptyUnary, expr, tyList itemTy, loc)

  let gotoStmt = msGotoUnless isEmptyExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
  ctx

let private mirifyPatCons ctx endLabel l r listTy loc expr =
  let itemTy = unwrapListTy listTy

  let isEmpty =
    MUnaryExpr(MListIsEmptyUnary, expr, tyBool, loc)

  let nonEmpty =
    MUnaryExpr(MNotUnary, isEmpty, tyBool, loc)

  let gotoStmt = msGotoUnless nonEmpty endLabel loc
  let ctx = addStmt ctx gotoStmt

  let head =
    MUnaryExpr(MListHeadUnary, expr, itemTy, loc)

  let tail =
    MUnaryExpr(MListTailUnary, expr, listTy, loc)

  let ctx = mirifyPat ctx endLabel l head
  let ctx = mirifyPat ctx endLabel r tail
  ctx

let private mirifyPatVar ctx _endLabel serial ty loc expr =
  addStmt ctx (MLetValStmt(serial, Some expr, ty, loc))

let private mirifyPatVariant ctx endLabel serial ty loc expr =
  // Compare tags.
  let equalExpr =
    let lDiscriminant =
      MUnaryExpr(MGetDiscriminantUnary, expr, tyInt, loc)

    let rDiscriminant = MDiscriminantConstExpr(serial, loc)
    MBinaryExpr(MEqualBinary, lDiscriminant, rDiscriminant, tyBool, loc)

  let gotoStmt = msGotoUnless equalExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
  ctx

let private mirifyPatVariantApp (ctx: MirCtx) endLabel serial payloadPat loc expr =
  let extractExpr =
    MUnaryExpr(MGetVariantUnary serial, expr, patToTy payloadPat, loc)

  // Special treatment for new-type variants
  // so that we can deconstruct it with irrefutable patterns
  // (`let` and arguments) without generating an abort branch.
  if isNewtypeVariant ctx serial then
    mirifyPat ctx endLabel payloadPat extractExpr
  else
    // Compare tags.
    let equalExpr =
      let lDiscriminant =
        MUnaryExpr(MGetDiscriminantUnary, expr, tyInt, loc)

      let rDiscriminant = MDiscriminantConstExpr(serial, loc)
      MBinaryExpr(MEqualBinary, lDiscriminant, rDiscriminant, tyBool, loc)

    let gotoStmt = msGotoUnless equalExpr endLabel loc
    let ctx = addStmt ctx gotoStmt

    // Extract payload.
    mirifyPat ctx endLabel payloadPat extractExpr

let private mirifyPatTuple ctx endLabel itemPats expr loc =
  let rec go ctx i itemPats =
    match itemPats with
    | [] -> ctx

    | itemPat :: itemPats ->
      let itemTy = patToTy itemPat
      let item = mxTupleItem expr i itemTy loc
      let ctx = mirifyPat ctx endLabel itemPat item
      go ctx (i + 1) itemPats

  go ctx 0 itemPats

let private mirifyPatBox ctx endLabel itemPat expr loc =
  let ty, _ = patExtract itemPat
  mirifyPat ctx endLabel itemPat (mxUnbox expr ty loc)

let private mirifyPatAbort ctx loc = addTerminator ctx (mtAbort loc) loc

let private mirifyPatAs ctx endLabel pat serial expr loc =
  let ty, _ = patExtract pat

  let ctx =
    addStmt ctx (MLetValStmt(serial, Some expr, ty, loc))

  let expr = MVarExpr(serial, ty, loc)
  mirifyPat ctx endLabel pat expr

/// Processes pattern matching
/// to generate let-val statements for each subexpression
/// and goto statements when determined if the pattern to match.
let private mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr) : MirCtx =
  let fail () = unreachable pat

  match pat with
  | HLitPat (lit, loc) -> mirifyPatLit ctx endLabel lit expr loc
  | HDiscardPat _ -> ctx
  | HVarPat (_, serial, ty, loc) -> mirifyPatVar ctx endLabel serial ty loc expr
  | HVariantPat (serial, ty, loc) -> mirifyPatVariant ctx endLabel serial ty loc expr

  | HNodePat (kind, argPats, ty, loc) ->
    match kind, argPats with
    | HNilPN, _ -> mirifyPatNil ctx endLabel ty expr loc

    | HConsPN, [ l; r ] -> mirifyPatCons ctx endLabel l r ty loc expr
    | HConsPN, _ -> fail ()

    | HNonePN, _ -> mirifyPatNone ctx endLabel expr loc

    | HSomeAppPN, [ payloadPat ] -> mirifyPatSomeApp ctx endLabel payloadPat loc expr
    | HSomeAppPN, _ -> fail ()

    | HVariantAppPN variantSerial, [ payloadPat ] -> mirifyPatVariantApp ctx endLabel variantSerial payloadPat loc expr
    | HVariantAppPN _, _ -> fail ()

    | HTuplePN, _ -> mirifyPatTuple ctx endLabel argPats expr loc

    | HBoxPN, [ itemPat ] -> mirifyPatBox ctx endLabel itemPat expr loc
    | HBoxPN, _ -> fail ()

    | HAbortPN, _ -> mirifyPatAbort ctx loc

  | HAsPat (pat, serial, loc) -> mirifyPatAs ctx endLabel pat serial expr loc

  | HOrPat _ ->
    // HOrPat in match expr is resolved by patNormalize and that in let expr is error in NameRes.
    fail ()

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private mirifyExprVariant (ctx: MirCtx) itself serial ty loc =
  let variantDef = ctx.Variants |> mapFind serial
  MVariantExpr(variantDef.UnionTySerial, serial, ty, loc), ctx

let private mirifyExprPrim (ctx: MirCtx) prim ty loc =
  match prim with
  | HPrim.Nil -> MGenericValueExpr(MNilGv, ty, loc), ctx
  | HPrim.OptionNone -> MGenericValueExpr(MNoneGv, ty, loc), ctx

  | _ -> unreachable () // Primitives must appear as callee.

let private doEmitIfStmt ctx cond thenHint body altHint alt targetTy loc =
  let temp, tempSet, ctx = letFreshVar ctx "if" targetTy loc
  let nextLabelStmt, nextLabel, ctx = freshLabel ctx "if_next" loc

  // Then clause.
  let thenLabelStmt, thenLabel, ctx = freshLabel ctx thenHint loc
  let parentCtx, ctx = ctx, startBlock ctx

  let body, ctx =
    let ctx = addStmt ctx thenLabelStmt
    let body, ctx = mirifyExpr ctx body
    let ctx = addStmt ctx (tempSet body)

    let ctx =
      addTerminator ctx (MGotoTerminator nextLabel) loc

    takeStmts ctx

  let ctx = rollback parentCtx ctx

  // Else clause. (Almost same as then clause.)
  let elseLabelStmt, elseLabel, ctx = freshLabel ctx altHint loc
  let parentCtx, ctx = ctx, startBlock ctx

  let alt, ctx =
    let ctx = addStmt ctx elseLabelStmt
    let alt, ctx = mirifyExpr ctx alt
    let ctx = addStmt ctx (tempSet alt)

    let ctx =
      addTerminator ctx (MGotoTerminator nextLabel) loc

    takeStmts ctx

  let ctx = rollback parentCtx ctx

  // End of if.
  let ctx =
    addTerminator ctx (MIfTerminator(cond, MGotoTerminator thenLabel, MGotoTerminator elseLabel)) loc

  let ctx = addStmtListList ctx [ alt; body ]
  let ctx = addStmt ctx nextLabelStmt
  temp, ctx

/// Tries to *sugar* a match expression to if expression
/// when `match p with true -> body | false -> alt`.
let private mirifyExprMatchAsIfStmt ctx cond arms ty loc =
  match exprToTy cond, arms with
  | Ty (BoolTk, []),
    [ HLitPat (BoolLit true, _), HLitExpr (BoolLit true, _), body
      HLitPat (BoolLit false, _), HLitExpr (BoolLit true, _), alt ] ->
    let cond, ctx = mirifyExpr ctx cond

    doEmitIfStmt ctx cond "then" body "else" alt ty loc
    |> Some

  // | None -> ... | _ -> ...
  | Ty (OptionTk, _),
    [ HNodePat (HNonePN, _, _, _), HLitExpr (BoolLit true, _), noneCl; HDiscardPat _, HLitExpr (BoolLit true, _), someCl ] ->
    let cond, ctx = mirifyExpr ctx cond

    let isNone =
      let ty, loc = mexprExtract cond
      mxNot (MUnaryExpr(MOptionIsSomeUnary, cond, ty, loc)) loc

    doEmitIfStmt ctx isNone "none_cl" noneCl "some_cl" someCl ty loc
    |> Some

  // | [] -> ... | _ -> ...
  | Ty (ListTk, _),
    [ HNodePat (HNilPN, _, _, _), HLitExpr (BoolLit true, _), nilCl; HDiscardPat _, HLitExpr (BoolLit true, _), consCl ] ->
    let cond, ctx = mirifyExpr ctx cond

    let isNil =
      let ty, loc = mexprExtract cond
      MUnaryExpr(MListIsEmptyUnary, cond, ty, loc)

    doEmitIfStmt ctx isNil "nil_cl" nilCl "cons_cl" consCl ty loc
    |> Some

  | _ -> None

let private matchExprCanCompileToSwitch cond arms =
  let tyIsLit ty =
    match ty with
    | Ty (IntTk _, [])
    | Ty (CharTk, [])
    | Ty (UnionTk _, _) -> true

    | _ -> false

  // Irrefutable and no-op.
  let rec patIsDiscarding pat =
    match pat with
    | HDiscardPat _ -> true
    | HNodePat (HBoxPN, [ bodyPat ], _, _) -> patIsDiscarding bodyPat

    | _ -> false

  /// Pattern is simple, i.e. flat, non-binding and disjunctive-normalized.
  let rec patIsSimple pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _ -> true

    | HNodePat (HVariantAppPN _, [ payloadPat ], _, _) -> patIsDiscarding payloadPat

    | HOrPat (l, r, _) -> patIsSimple l && patIsSimple r

    | _ -> false

  tyIsLit (exprToTy cond)
  && arms
     |> List.forall (fun (pat, guard, _) -> patIsSimple pat && hxIsAlwaysTrue guard)

/// Converts a match expression to switch statement.
let private mirifyExprMatchAsSwitchStmt ctx cond arms ty loc =
  // (caseLits, isDefault)
  let rec go pat =
    match pat with
    | HLitPat (lit, _) -> [ MLitConst lit ], false

    | HDiscardPat _ -> [], true

    | HVariantPat (variantSerial, _, _) -> [ MDiscriminantConst variantSerial ], false

    | HNodePat (HVariantAppPN variantSerial, _, _, _) -> [ MDiscriminantConst variantSerial ], false

    | HOrPat (l, r, _) ->
      let lCases, lIsDefault = go l
      let rCases, rIsDefault = go r

      if lIsDefault || rIsDefault then
        [], true
      else
        let cases = List.append rCases lCases // reverse order
        cases, false

    | _ -> unreachable pat

  let temp, tempSet, ctx = letFreshVar ctx "switch" ty loc
  let nextLabelStmt, nextLabel, ctx = freshLabel ctx "switch_next" loc

  let cond, ctx =
    let condTy, condLoc = exprExtract cond
    let cond, ctx = mirifyExpr ctx cond

    match condTy with
    | Ty (UnionTk _, _) -> MUnaryExpr(MGetDiscriminantUnary, cond, tyInt, condLoc), ctx
    | _ -> cond, ctx

  let exhaust, clauses, blocks, ctx =
    arms
    |> List.fold
         (fun (hasDefault, clauses, blocks, ctx) (pat, _, body) ->
           if hasDefault then
             true, clauses, blocks, ctx
           else
             let _, clauseLoc = patExtract pat
             let clauseLabelStmt, clauseLabel, ctx = freshLabel ctx "clause" clauseLoc

             let cases, isDefault = go pat

             let clause: MSwitchClause =
               { Cases = List.rev cases
                 IsDefault = isDefault
                 Terminator = MGotoTerminator clauseLabel }

             // Generate body.
             let parentCtx, ctx = ctx, startBlock ctx

             let block, ctx =
               let ctx = addStmt ctx clauseLabelStmt
               let body, ctx = mirifyExpr ctx body
               let ctx = addStmt ctx (tempSet body)

               let ctx =
                 addTerminator ctx (MGotoTerminator nextLabel) loc

               takeStmts ctx

             let ctx = rollback parentCtx ctx

             hasDefault || isDefault, clause :: clauses, block :: blocks, ctx)
         (false, [], [], ctx)

  let clauses =
    if exhaust then
      clauses
    else
      let clause: MSwitchClause =
        { Cases = []
          IsDefault = true
          Terminator = mtAbort loc }

      clause :: clauses

  let ctx =
    addTerminator ctx (MSwitchTerminator(cond, List.rev clauses)) loc

  let ctx = addStmtListList ctx blocks
  let ctx = addStmt ctx nextLabelStmt

  temp, ctx

/// Gets if the pattern matching must succeed.
let private patsIsCovering ctx pats =
  pats
  |> List.exists (patIsClearlyExhaustive (isNewtypeVariant ctx))

let private mirifyExprMatchFull ctx cond arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = letFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = freshLabel ctx "end_match" loc

  let cond, ctx = mirifyExpr ctx cond

  let isCovering =
    arms
    |> List.choose
         (fun (pat, guard, _) ->
           if hxIsAlwaysTrue guard then
             Some pat
           else
             None)
    |> patsIsCovering ctx

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
          let _, bodyLabel, ctx = freshLabel ctx "match_body" loc
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
              let _, patLabel, ctx = freshLabel ctx "next" loc
              MatchIR.PatLabel patLabel :: acc, ctx

          let acc = MatchIR.Pat(pat, noLabel) :: acc

          let acc =
            if not needsJump then
              acc
            else
              MatchIR.GoBody bodyLabel :: acc

          goPats ctx acc false pats
        | [] -> acc, ctx

      let acc, ctx = goPats ctx acc firstPat pats

      let acc =
        if not needsJump then
          acc
        else
          MatchIR.BodyLabel bodyLabel :: acc

      let acc = MatchIR.Guard(guard, noLabel) :: acc
      let acc = MatchIR.Body body :: acc
      goArms ctx acc false arms

    | [] ->
      let _, exhaustLabel, ctx = freshLabel ctx "next" loc
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
        if guard |> hxIsAlwaysTrue then
          acc
        else
          MatchIR.Guard(guard, nextLabel) :: acc

      fixUp acc nextLabel rest

    | instruction :: rest -> fixUp (instruction :: acc) nextLabel rest

    | [] -> acc

  /// Emits MIR instructions based on matching IRs.
  let rec emit ctx instructions =
    match instructions with
    | MatchIR.PatLabel patLabel :: rest ->
      let ctx = addStmt ctx (MLabelStmt(patLabel, loc))
      emit ctx rest

    | MatchIR.Pat (pat, nextLabel) :: rest ->
      // Perform pattern matching. Go to the next pattern on failure.
      let ctx = mirifyPat ctx nextLabel pat cond
      emit ctx rest

    | MatchIR.GoBody bodyLabel :: rest ->
      let ctx =
        addTerminator ctx (MGotoTerminator bodyLabel) loc

      emit ctx rest

    | MatchIR.BodyLabel bodyLabel :: rest ->
      let ctx = addStmt ctx (MLabelStmt(bodyLabel, loc))
      emit ctx rest

    | MatchIR.Guard (guard, nextLabel) :: rest ->
      let ctx =
        if guard |> hxIsAlwaysTrue then
          ctx
        else
          let guard, ctx = mirifyExpr ctx guard
          addStmt ctx (msGotoUnless guard nextLabel loc)

      emit ctx rest

    | MatchIR.Body body :: rest ->
      // Enter into the body.
      let body, ctx = mirifyExpr ctx body
      // Leave the match.
      let ctx = addStmt ctx (tempSet body)

      let ctx =
        addTerminator ctx (MGotoTerminator endLabel) loc

      emit ctx rest

    | [] ->
      // Abort if exhaust.
      if isCovering then
        ctx
      else
        addTerminator ctx (mtAbort loc) loc

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = addStmt ctx endLabelStmt

  temp, ctx

let private mirifyExprMatch ctx cond arms ty loc =
  let arms, ctx = reuseArmLocals arms ctx

  match mirifyExprMatchAsIfStmt ctx cond arms ty loc with
  | Some (result, ctx) -> result, ctx

  | None ->
    if matchExprCanCompileToSwitch cond arms then
      mirifyExprMatchAsSwitchStmt ctx cond arms ty loc
    else
      mirifyExprMatchFull ctx cond arms ty loc

// -----------------------------------------------
// Var reusing
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private VarReuse =
  | Replacing
  | ReplacedBy of VarSerial

type private VarReuseMap = AssocMap<VarSerial, VarReuse * Ty>

let private reuseVarSerial (reuseMap: VarReuseMap) serial : VarSerial =
  match TMap.tryFind serial reuseMap with
  | Some (VarReuse.ReplacedBy serial, _) -> serial
  | _ -> serial

let private reuseVarOnPat (reuseMap: VarReuseMap) (pat: HPat) : HPat =
  let rec go pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _ -> pat

    | HVarPat (vis, serial, ty, loc) -> HVarPat(vis, reuseVarSerial reuseMap serial, ty, loc)

    | HNodePat (kind, args, ty, loc) -> HNodePat(kind, List.map go args, ty, loc)
    | HAsPat (bodyPat, serial, loc) -> HAsPat(go bodyPat, reuseVarSerial reuseMap serial, loc)
    | HOrPat (l, r, loc) -> HOrPat(go l, go r, loc)

  go pat

let private reuseVarOnExpr (reuseMap: VarReuseMap) (expr: HExpr) : HExpr =
  let goPat pat = reuseVarOnPat reuseMap pat

  let rec go expr =
    match expr with
    | HLitExpr _
    | HFunExpr _
    | HVariantExpr _
    | HPrimExpr _ -> expr

    | HVarExpr (serial, ty, loc) -> HVarExpr(reuseVarSerial reuseMap serial, ty, loc)

    | HMatchExpr (cond, arms, ty, loc) ->
      let arms =
        arms
        |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

      HMatchExpr(go cond, arms, ty, loc)

    | HNodeExpr (kind, args, ty, loc) -> HNodeExpr(kind, List.map go args, ty, loc)
    | HBlockExpr (stmts, last) -> HBlockExpr(List.map go stmts, go last)
    | HLetValExpr (pat, init, next, ty, loc) -> HLetValExpr(goPat pat, go init, go next, ty, loc)
    | HLetFunExpr (serial, isRec, vis, args, body, next, ty, loc) ->
      HLetFunExpr(serial, isRec, vis, List.map goPat args, go body, go next, ty, loc)

    | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
    | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

  go expr

let private doReuseArmLocals funSerial arms (ctx: MirCtx) : _ * MirCtx =
  let emptyReuseMap: VarReuseMap = TMap.empty varSerialCompare

  let emptyVarMap: AssocMap<Ty * int, VarSerial> =
    TMap.empty (pairCompare tyCompare compare)

  // ty -> index:
  // index is the number of variables of the same type appeared earlier in the same pattern.
  let emptyFreq: AssocMap<Ty, int> = TMap.empty tyCompare

  let analyzeVarPat varSerial varTy reuseMap varMap freq =
    let index =
      freq
      |> TMap.tryFind varTy
      |> Option.defaultValue 0

    let freq = freq |> TMap.add varTy (index + 1)

    let reuseMap, varMap =
      match varMap |> TMap.tryFind (varTy, index) with
      | None ->
        let reuseMap =
          reuseMap
          |> TMap.add varSerial (VarReuse.Replacing, varTy)

        let varMap =
          varMap |> TMap.add (varTy, index) varSerial

        reuseMap, varMap

      | Some otherSerial ->
        let reuseMap =
          reuseMap
          |> TMap.add varSerial (VarReuse.ReplacedBy otherSerial, varTy)

        reuseMap, varMap

    reuseMap, varMap, freq

  let reuseMap, _ =
    List.fold
      (fun (reuseMap, varMap) (pat, _, _) ->
        let reuseMap, varMap, _ =
          patFold
            (fun (reuseMap, varMap, freq) varSerial ty -> analyzeVarPat varSerial ty reuseMap varMap freq)
            (reuseMap, varMap, emptyFreq)
            pat

        reuseMap, varMap)
      (emptyReuseMap, emptyVarMap)
      arms

  let arms =
    arms
    |> List.map
         (fun (pat, guard, body) ->
           reuseVarOnPat reuseMap pat, reuseVarOnExpr reuseMap guard, reuseVarOnExpr reuseMap body)

  let ctx: MirCtx =
    let funLocals, replacingVars =
      reuseMap
      |> TMap.fold
           (fun (funLocals, replacingVars) varSerial (_, ty) ->
             multimapAdd funSerial (varSerial, ty) funLocals, TSet.add varSerial replacingVars)
           (ctx.FunLocals, ctx.ReplacingVars)

    { ctx with
        FunLocals = funLocals
        ReplacingVars = replacingVars }

  arms, ctx

let private reuseArmLocals arms (ctx: MirCtx) : _ * MirCtx =
  match ctx.CurrentFunSerial with
  | Some funSerial -> doReuseArmLocals funSerial arms ctx
  | _ -> arms, ctx // toplevel match? unreachable?

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg

  let ctx =
    addTerminator ctx (MExitTerminator arg) loc

  MNeverExpr loc, ctx

let private mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg

  match arg |> mexprToTy |> toBoxMode with
  | BoxMode.Null ->
    // HACK: `box ()` occurs when turning a non-capturing function into function object.
    MNativeExpr("NULL", tyObj, loc), ctx

  | BoxMode.Cast ->
    let arg =
      MUnaryExpr(MNativeCastUnary, arg, tyNativeInt, loc)

    MUnaryExpr(MNativeCastUnary, arg, tyObj, loc), ctx

  | BoxMode.Alloc ->
    let temp, tempSerial, ctx = freshVar ctx "box" tyObj loc

    let ctx =
      addStmt ctx (MPrimStmt(MBoxPrim, [ arg ], tempSerial, tyObj, loc))

    temp, ctx

let private mirifyCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  mxUnbox arg ty loc, ctx

let private mirifyCallStrIndexExpr ctx l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  MBinaryExpr(MStrIndexBinary, l, r, ty, loc), ctx

let private mirifyCallStrGetSliceExpr ctx args loc =
  assert (List.length args = 3)

  let args, ctx = mirifyExprs ctx args

  let temp, tempSerial, ctx = freshVar ctx "slice" tyStr loc

  let ctx =
    addStmt ctx (MPrimStmt(MStrGetSlicePrim, args, tempSerial, tyStr, loc))

  temp, ctx

let private mirifyExprCallSome ctx item ty loc =
  let _, tempSerial, ctx = freshVar ctx "some" ty loc

  let item, ctx = mirifyExpr ctx item

  let ctx =
    addStmt ctx (MPrimStmt(MOptionSomePrim, [ item ], tempSerial, ty, loc))

  MVarExpr(tempSerial, ty, loc), ctx

let private mirifyCallVariantExpr (ctx: MirCtx) serial payload ty loc =
  let payload, ctx = mirifyExpr ctx payload
  let payloadTy = mexprToTy payload

  // FIXME: Generate a serial to reduce diff. Remove this later.
  let _, _payloadSerial, ctx = freshVar ctx "payload" payloadTy loc

  let temp, tempSerial, ctx = freshVar ctx "variant" ty loc

  let ctx =
    addStmt ctx (MPrimStmt(MVariantPrim serial, [ payload ], tempSerial, ty, loc))

  temp, ctx

let private mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = freshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  let ctx =
    addStmt ctx (MPrimStmt(MConsPrim, [ l; r ], tempSerial, listTy, loc))

  MVarExpr(tempSerial, listTy, loc), ctx

let private mirifyExprTuple ctx items itemTys loc =
  let ty = tyTuple itemTys
  let _, tempSerial, ctx = freshVar ctx "tuple" ty loc

  let rec go acc ctx items =
    match items with
    | [] -> List.rev acc, ctx
    | item :: items ->
      let item, ctx = mirifyExpr ctx item
      go (item :: acc) ctx items

  let items, ctx = go [] ctx items

  let ctx =
    addStmt ctx (MPrimStmt(MTuplePrim, items, tempSerial, ty, loc))

  MVarExpr(tempSerial, ty, loc), ctx

let private mirifyExprRecord (ctx: MirCtx) args ty loc =
  let name =
    match ty with
    | Ty (RecordTk tySerial, _) -> ctx.Tys |> mapFind tySerial |> tyDefToName
    | _ -> unreachable ()

  let _, tempSerial, ctx = freshVar ctx name ty loc

  let args, ctx = mirifyExprs ctx args

  let ctx =
    addStmt ctx (MPrimStmt(MRecordPrim, args, tempSerial, ty, loc))

  MVarExpr(tempSerial, ty, loc), ctx

let private mirifyExprRecordItem ctx index tuple itemTy loc =
  let record, ctx = mirifyExpr ctx tuple
  MUnaryExpr(MRecordItemUnary index, record, itemTy, loc), ctx

let private mirifyExprOpArith ctx itself op l r ty loc =
  let lTy = exprToTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match lTy with
  | Ty ((IntTk _
        | FloatTk _
        | CharTk),
        _) -> mxBinOpScalar ctx op l r (ty, loc)

  | Ty (StrTk, _) when op |> mOpIsAdd -> mxStrAdd ctx op l r (ty, loc)

  | _ -> unreachable itself

let private mirifyExprOpCompare ctx op l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  mxCompare ctx op l r ty loc

let private mirifyCallCompareExpr ctx itself l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match mexprToTy l with
  // Comparison of small or unsigned integers is just `-` for not overflow.
  | Ty ((IntTk (IntFlavor (_, I8))
        | IntTk (IntFlavor (_, I16))
        | BoolTk
        | CharTk),
        _) -> MBinaryExpr(MSubBinary, l, r, tyInt, loc), ctx

  | Ty (IntTk (IntFlavor (Signed, I32)), _) -> MBinaryExpr(MIntCompareBinary, l, r, tyInt, loc), ctx

  | Ty ((IntTk (IntFlavor (Signed, I64))
        | IntTk (IntFlavor (Signed, IPtr))
        | NativePtrTk _),
        _) -> MBinaryExpr(MInt64CompareBinary, l, r, tyInt, loc), ctx

  | Ty ((IntTk (IntFlavor (Unsigned, _))), _) -> MBinaryExpr(MUInt64CompareBinary, l, r, tyInt, loc), ctx

  | Ty (StrTk, _) -> MBinaryExpr(MStrCompareBinary, l, r, tyInt, loc), ctx

  | _ -> unreachable itself

let private mirifyCallToIntExpr ctx itself flavor arg ty loc =
  let srcTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match srcTy with
  | Ty (IntTk srcFlavor, _) when intFlavorEqual srcFlavor flavor -> arg, ctx

  | Ty ((IntTk _
        | FloatTk _
        | CharTk
        | NativePtrTk _),
        _) -> MUnaryExpr(MIntOfScalarUnary flavor, arg, Ty(IntTk flavor, []), loc), ctx

  | Ty (StrTk, _) ->
    let temp, tempSerial, ctx = freshVar ctx "call" ty loc

    let ctx =
      addStmt ctx (MPrimStmt(MIntOfStrPrim flavor, [ arg ], tempSerial, ty, loc))

    temp, ctx

  | _ -> unreachable itself

let private mirifyCallToFloatExpr ctx itself flavor arg ty loc =
  let srcTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match srcTy with
  | Ty (FloatTk _, _) -> arg, ctx

  | Ty (IntTk _, _) -> MUnaryExpr(MFloatOfScalarUnary flavor, arg, tyFloat, loc), ctx

  | Ty (StrTk, _) ->
    let temp, tempSerial, ctx = freshVar ctx "call" ty loc

    let ctx =
      addStmt ctx (MPrimStmt(MFloatOfStrPrim flavor, [ arg ], tempSerial, ty, loc))

    temp, ctx

  | _ -> unreachable itself

let private mirifyCallCharExpr ctx itself arg ty loc =
  let argTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match argTy with
  | Ty (CharTk, _) -> arg, ctx

  | Ty ((IntTk _
        | FloatTk _),
        _) -> MUnaryExpr(MCharOfScalarUnary, arg, tyInt, loc), ctx

  | Ty (StrTk, _) ->
    let temp, tempSerial, ctx = freshVar ctx "char_of_string" ty loc

    let ctx =
      addStmt ctx (MPrimStmt(MCharOfStrPrim, [ arg ], tempSerial, ty, loc))

    temp, ctx

  | _ -> unreachable itself

let private mirifyCallStringExpr ctx itself arg ty loc =
  let argTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  let usePrim prim =
    let temp, tempSerial, ctx = freshVar ctx "call" ty loc

    let ctx =
      addStmt ctx (MPrimStmt(prim, [ arg ], tempSerial, ty, loc))

    temp, ctx

  match argTy with
  | Ty (StrTk, _) -> arg, ctx

  | Ty (IntTk flavor, _) -> usePrim (MStrOfIntPrim flavor)
  | Ty (FloatTk flavor, _) -> usePrim (MStrOfFloatPrim flavor)
  | Ty (BoolTk, _) -> usePrim MStrOfBoolPrim
  | Ty (CharTk, _) -> usePrim MStrOfCharPrim

  | _ -> unreachable itself

let private mirifyCallAssertExpr ctx arg loc =
  let arg, ctx = mirifyExpr ctx arg

  // Embed the source location information.
  let args =
    let (Loc (_, y, x)) = loc

    [ arg
      MLitExpr(IntLit(string y), loc)
      MLitExpr(IntLit(string x), loc) ]

  let ctx =
    addStmt ctx (MActionStmt(MAssertAction, args, loc))

  MUnitExpr loc, ctx

let private mirifyCallInRegionExpr ctx arg loc =
  // arg: closure
  let arg, ctx = mirifyExpr ctx arg

  let temp, tempSerial, ctx = freshVar ctx "region_result" tyInt loc

  let ctx =
    addStmt ctx (MActionStmt(MEnterRegionAction, [], loc))

  let ctx =
    let unit = MUnitExpr loc
    addStmt ctx (MPrimStmt(MCallClosurePrim, [ arg; unit ], tempSerial, tyInt, loc))

  let ctx =
    addStmt ctx (MActionStmt(MLeaveRegionAction, [], loc))

  temp, ctx

let private mirifyCallPrintfnExpr ctx args loc =
  let args, ctx = mirifyExprs ctx args

  let ctx =
    addStmt ctx (MActionStmt(MPrintfnAction, args, loc))

  MUnitExpr loc, ctx

let private mirifyCallProcExpr ctx callee args ty loc =
  let callee, ctx = mirifyExpr ctx callee

  let args, ctx = mirifyExprs ctx args

  let temp, tempSerial, ctx = freshVar ctx "call" ty loc

  let ctx =
    addStmt ctx (MPrimStmt(MCallProcPrim, callee :: args, tempSerial, ty, loc))

  temp, ctx

let private mirifyCallPrimExpr ctx itself prim args ty loc =
  let fail () = unreachable itself

  let regularUnary unary arg =
    let arg, ctx = mirifyExpr ctx arg
    MUnaryExpr(unary, arg, ty, loc), ctx

  let regularBinary binary l r =
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MBinaryExpr(binary, l, r, ty, loc), ctx

  let regularPrim hint prim =
    let args, ctx = mirifyExprs ctx args

    let tempExpr, temp, ctx = freshVar ctx hint ty loc

    let ctx =
      addStmt ctx (MPrimStmt(prim, args, temp, ty, loc))

    tempExpr, ctx

  let regularAction action =
    let args, ctx = mirifyExprs ctx args

    let ctx =
      addStmt ctx (MActionStmt(action, args, loc))

    MUnitExpr loc, ctx

  match prim, args with
  | HPrim.Add, [ l; r ] -> mirifyExprOpArith ctx itself MAddBinary l r ty loc
  | HPrim.Add, _ -> fail ()
  | HPrim.Sub, [ l; r ] -> mirifyExprOpArith ctx itself MSubBinary l r ty loc
  | HPrim.Sub, _ -> fail ()
  | HPrim.Mul, [ l; r ] -> mirifyExprOpArith ctx itself MMulBinary l r ty loc
  | HPrim.Mul, _ -> fail ()
  | HPrim.Div, [ l; r ] -> mirifyExprOpArith ctx itself MDivBinary l r ty loc
  | HPrim.Div, _ -> fail ()
  | HPrim.Modulo, [ l; r ] -> mirifyExprOpArith ctx itself MModuloBinary l r ty loc
  | HPrim.Modulo, _ -> fail ()

  | HPrim.BitAnd, [ l; r ] -> regularBinary MBitAndBinary l r
  | HPrim.BitAnd, _ -> fail ()
  | HPrim.BitOr, [ l; r ] -> regularBinary MBitOrBinary l r
  | HPrim.BitOr, _ -> fail ()
  | HPrim.BitXor, [ l; r ] -> regularBinary MBitXorBinary l r
  | HPrim.BitXor, _ -> fail ()
  | HPrim.LeftShift, [ l; r ] -> regularBinary MLeftShiftBinary l r
  | HPrim.LeftShift, _ -> fail ()
  | HPrim.RightShift, [ l; r ] -> regularBinary MRightShiftBinary l r
  | HPrim.RightShift, _ -> fail ()

  | HPrim.Equal, [ l; r ] -> mirifyExprOpCompare ctx MEqualBinary l r ty loc
  | HPrim.Equal, _ -> fail ()
  | HPrim.Less, [ l; r ] -> mirifyExprOpCompare ctx MLessBinary l r ty loc
  | HPrim.Less, _ -> fail ()
  | HPrim.Compare, [ l; r ] -> mirifyCallCompareExpr ctx itself l r ty loc
  | HPrim.Compare, _ -> fail ()
  | HPrim.Cons, [ l; r ] -> mirifyExprOpCons ctx l r ty loc
  | HPrim.Cons, _ -> fail ()
  | HPrim.OptionSome, [ item ] -> mirifyExprCallSome ctx item ty loc
  | HPrim.OptionSome, _ -> fail ()
  | HPrim.Not, [ arg ] -> regularUnary MNotUnary arg
  | HPrim.Not, _ -> fail ()
  | HPrim.Exit, [ arg ] -> mirifyExprCallExit ctx arg ty loc
  | HPrim.Exit, _ -> fail ()
  | HPrim.Box, [ arg ] -> mirifyExprCallBox ctx arg ty loc
  | HPrim.Box, _ -> fail ()
  | HPrim.Unbox, [ arg ] -> mirifyCallUnbox ctx arg ty loc
  | HPrim.Unbox, _ -> fail ()
  | HPrim.StrLength, [ arg ] -> regularUnary MStrLenUnary arg
  | HPrim.StrLength, _ -> fail ()
  | HPrim.ToInt flavor, [ arg ] -> mirifyCallToIntExpr ctx itself flavor arg ty loc
  | HPrim.ToInt _, _ -> fail ()
  | HPrim.ToFloat flavor, [ arg ] -> mirifyCallToFloatExpr ctx itself flavor arg ty loc
  | HPrim.ToFloat _, _ -> fail ()
  | HPrim.Char, [ arg ] -> mirifyCallCharExpr ctx itself arg ty loc
  | HPrim.Char, _ -> fail ()
  | HPrim.String, [ arg ] -> mirifyCallStringExpr ctx itself arg ty loc
  | HPrim.String, _ -> fail ()
  | HPrim.Assert, [ arg ] -> mirifyCallAssertExpr ctx arg loc
  | HPrim.Assert, _ -> fail ()
  | HPrim.InRegion, [ arg ] -> mirifyCallInRegionExpr ctx arg loc
  | HPrim.InRegion, _ -> fail ()
  | HPrim.Printfn, _ -> mirifyCallPrintfnExpr ctx args loc
  | HPrim.NativeCast, [ arg ] -> regularUnary MNativeCastUnary arg
  | HPrim.NativeCast, _ -> fail ()
  | HPrim.PtrRead, _ -> regularPrim "read" MPtrReadPrim
  | HPrim.PtrWrite, _ -> regularAction MPtrWriteAction

  | HPrim.Nil, _
  | HPrim.OptionNone, _ -> fail ()

let private mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee

  let args, ctx = mirifyExprs ctx args

  let tempRef, tempSerial, ctx = freshVar ctx "app" resultTy loc

  let ctx =
    addStmt ctx (MPrimStmt(MCallClosurePrim, callee :: args, tempSerial, resultTy, loc))

  tempRef, ctx

let private mirifyExprInfCallTailRec (ctx: MirCtx) _callee args ty loc =
  // It's guaranteed that callee points to the current fun,
  // but it's serial can now be wrong due to monomorphization.

  let label, argSerials =
    match ctx.CurrentFun with
    | Some it -> it
    | None -> unreachable loc // Current fun must exists.

  // Evaluate args and assign to temp vars.
  let tempExprs, ctx =
    (args, ctx)
    |> stMap
         (fun (arg, ctx) ->
           let ty, loc = exprExtract arg
           let tempVarExpr, tempVarSerial, ctx = freshVar ctx "arg" ty loc

           let arg, ctx = mirifyExpr ctx arg

           let ctx =
             addStmt ctx (MLetValStmt(tempVarSerial, Some arg, ty, loc))

           tempVarExpr, ctx)

  // Update args.
  let ctx =
    let rec go ctx argSerials tempExprs =
      match argSerials, tempExprs with
      | [], [] -> ctx

      | argSerial :: argSerials, tempExpr :: tempExprs ->
        let ctx =
          addStmt ctx (MSetStmt(argSerial, tempExpr, loc))

        go ctx argSerials tempExprs

      | _ -> unreachable loc // Arity mismatch.

    go ctx argSerials tempExprs

  let ctx =
    addTerminator ctx (MGotoTerminator label) loc

  MNeverExpr loc, ctx

let private mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env

  // FIXME: Generate a serial to reduce diff; remove this later.
  let _, _, ctx = freshVar ctx "env" envTy envLoc

  let tempRef, tempSerial, ctx = freshVar ctx "fun" funTy loc

  let ctx =
    addStmt ctx (MPrimStmt(MClosurePrim funSerial, [ env ], tempSerial, funTy, loc))

  tempRef, ctx

let private mirifyExprInfCallNative ctx (funName: string) args ty loc =
  let args, ctx = mirifyExprs ctx args

  // No result if result type is unit.
  if ty |> tyIsUnit then
    let ctx =
      addStmt ctx (MActionStmt(MCallNativeAction funName, args, loc))

    MUnitExpr loc, ctx
  else
    let temp, tempSerial, ctx =
      freshVar ctx (funName + "_result") ty loc

    let ctx =
      addStmt ctx (MPrimStmt(MCallNativePrim funName, args, tempSerial, ty, loc))

    temp, ctx

let private mirifyExprInf ctx itself kind args ty loc =
  match kind, args, ty with
  | HMinusEN, [ arg ], _ ->
    let arg, ctx = mirifyExpr ctx arg
    MUnaryExpr(MMinusUnary, arg, ty, loc), ctx

  | HTupleEN, [], Ty (TupleTk, []) -> MUnitExpr loc, ctx
  | HTupleEN, _, Ty (TupleTk, itemTys) -> mirifyExprTuple ctx args itemTys loc
  | HRecordEN, _, _ -> mirifyExprRecord ctx args ty loc
  | HRecordItemEN index, [ record ], itemTy -> mirifyExprRecordItem ctx index record itemTy loc

  | HIndexEN, [ l; r ], _ -> mirifyCallStrIndexExpr ctx l r ty loc
  | HSliceEN, _, _ -> mirifyCallStrGetSliceExpr ctx args loc

  | HCallProcEN, [ HVariantExpr (variantSerial, _, _); arg ], _ -> mirifyCallVariantExpr ctx variantSerial arg ty loc
  | HCallProcEN, HPrimExpr (prim, _, _) :: args, _ -> mirifyCallPrimExpr ctx itself prim args ty loc
  | HCallProcEN, callee :: args, _ -> mirifyCallProcExpr ctx callee args ty loc

  | HCallTailRecEN, callee :: args, _ -> mirifyExprInfCallTailRec ctx callee args ty loc
  | HCallClosureEN, callee :: args, _ -> mirifyExprInfCallClosure ctx callee args ty loc
  | HCallNativeEN funName, args, _ -> mirifyExprInfCallNative ctx funName args ty loc
  | HClosureEN, [ HFunExpr (funSerial, _, _); env ], _ -> mirifyExprInfClosure ctx funSerial env ty loc

  | HNativeFunEN funSerial, _, _ -> MProcExpr(funSerial, ty, loc), ctx

  | HNativeExprEN code, _, _ -> MNativeExpr(code, ty, loc), ctx

  | HNativeStmtEN code, args, _ ->
    let args, ctx = mirifyExprs ctx args

    let ctx =
      addStmt ctx (MNativeStmt(code, args, loc))

    MUnitExpr loc, ctx

  | HNativeDeclEN code, _, _ ->
    let ctx = addDecl ctx (MNativeDecl(code, loc))
    MUnitExpr loc, ctx

  | HSizeOfValEN, [ HNodeExpr (_, _, ty, _) ], _ -> MGenericValueExpr(MSizeOfGv, ty, loc), ctx

  | t -> unreachable t

let private mirifyExprLetValContents ctx pat init =
  assert (patsIsCovering ctx [ pat ])
  let init, ctx = mirifyExpr ctx init
  mirifyPat ctx "_never_" pat init

let private mirifyExprLetFunContents (ctx: MirCtx) calleeSerial argPats body letLoc =
  let prepareCurrentFunSerial (ctx: MirCtx) =
    ctx.CurrentFunSerial,
    { ctx with
        CurrentFunSerial = Some calleeSerial }

  let cleanUpCurrentFunSerial (ctx: MirCtx) parent = { ctx with CurrentFunSerial = parent }

  let prepareTailRec (ctx: MirCtx) args =
    let parentFun = ctx.CurrentFun

    let currentFun, ctx =
      if body |> containsTailRec then
        let labelStmt, label, ctx = freshLabel ctx "tailrec" letLoc
        let ctx = prependStmt ctx labelStmt
        let argSerials = args |> List.map (fun (it, _, _) -> it)
        Some(label, argSerials), ctx
      else
        None, ctx

    let ctx = { ctx with CurrentFun = currentFun }
    parentFun, ctx

  let cleanUpTailRec (ctx: MirCtx) parentFun = { ctx with CurrentFun = parentFun }

  let defineArg ctx argPat =
    assert (patsIsCovering ctx [ argPat ])

    match argPat with
    | HVarPat (_, serial, ty, loc) ->
      // NOTE: Optimize for usual cases to not generate redundant local vars.
      (serial, ty, loc), ctx
    | _ ->
      let argTy, argLoc = patExtract argPat
      let arg, argSerial, ctx = freshVar ctx "arg" argTy argLoc
      let ctx = mirifyPat ctx "_never_" argPat arg

      (argSerial, argTy, argLoc), ctx

  let rec defineArgs acc ctx argPats =
    match argPats with
    | [] -> List.rev acc, ctx
    | argPat :: argPats ->
      let arg, ctx = defineArg ctx argPat
      defineArgs (arg :: acc) ctx argPats

  let mirifyFunBody (ctx: MirCtx) argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let parentSerial, ctx = prepareCurrentFunSerial ctx
    let parentFun, ctx = prepareTailRec ctx args
    let lastExpr, ctx = mirifyExpr ctx body

    let ctx =
      addTerminator ctx (MReturnTerminator lastExpr) blockLoc

    let ctx = cleanUpTailRec ctx parentFun
    let ctx = cleanUpCurrentFunSerial ctx parentSerial

    let body, ctx =
      let stmts, ctx = takeStmts ctx
      let block: MBlock = { Stmts = stmts }
      [ block ], ctx

    args, blockTy, body, ctx

  let core () =
    let bodyCtx = startBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = rollback ctx bodyCtx

    let ctx =
      addDecl ctx (MProcDecl(calleeSerial, args, body, resultTy, letLoc))

    ctx

  core ()

let private mirifyOtherExprWrapper ctx expr =
  match expr with
  | HLitExpr (lit, loc) -> MLitExpr(lit, loc), ctx
  | HVarExpr (serial, ty, loc) -> MVarExpr(serial, ty, loc), ctx
  | HFunExpr (serial, ty, loc) -> MProcExpr(serial, ty, loc), ctx

  | HVariantExpr (serial, ty, loc) -> mirifyExprVariant ctx expr serial ty loc
  | HPrimExpr (prim, ty, loc) -> mirifyExprPrim ctx prim ty loc
  | HMatchExpr (cond, arms, ty, loc) -> mirifyExprMatch ctx cond arms ty loc
  | HNodeExpr (kind, args, ty, loc) -> mirifyExprInf ctx expr kind args ty loc

  | HBlockExpr _
  | HLetValExpr _
  | HLetFunExpr _ -> unreachable () // See mirifyExpr below.

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private mirifyExpr (ctx: MirCtx) (expr: HExpr) : MExpr * MirCtx =
  match expr with
  | HBlockExpr (stmts, last) ->
    let ctx =
      stmts
      |> List.fold
           (fun ctx stmt ->
             // Discard intermediate results.
             let _, ctx = mirifyExpr ctx stmt
             ctx)
           ctx

    mirifyExpr ctx last

  | HLetValExpr (pat, init, next, _, _) ->
    let ctx = mirifyExprLetValContents ctx pat init
    mirifyExpr ctx next

  | HLetFunExpr (funSerial, _, _, argPats, body, next, _, loc) ->
    let ctx =
      mirifyExprLetFunContents ctx funSerial argPats body loc

    mirifyExpr ctx next

  | _ ->
    // Split function to reduce stack size.
    // (This was required to avoid stack overflow previously but it might be non-issue now?)
    mirifyOtherExprWrapper ctx expr

let private mirifyExprs ctx exprs =
  (exprs, ctx)
  |> stMap (fun (expr, ctx) -> mirifyExpr ctx expr)

let mirify (decls: HExpr list, tyCtx: TyCtx) : MDecl list * MirCtx =
  let ctx = ofTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx =
    (decls, ctx)
    |> stMap (fun (expr, ctx) -> mirifyExpr ctx expr)

  takeDecls ctx
