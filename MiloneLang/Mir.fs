/// Converts HIR to mid-level intermediate representation (MIR).
///
/// MIR is a procedural, non-recursive, similar to C, IR.
///
/// Deconstructs pattern matching.
module rec MiloneLang.Mir

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Typing

/// Checks whether an expr (body of fun) contains tail-rec call.
let private containsTailRec expr =
  match expr with
  | HInfExpr (InfOp.CallTailRec, _, _, _) -> true

  | HInfExpr (InfOp.Semi, items, _, _) -> items |> List.last |> containsTailRec

  | HLitExpr _
  | HRefExpr _
  | HFunExpr _
  | HVariantExpr _
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

[<RequireQualifiedAccess>]
type MirCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>
    LabelSerial: Serial

    /// (label, parameters), where the label is the entrypoint of current fun.
    /// For tail-rec (tail-call) optimization.
    CurrentFun: (Label * VarSerial list) option

    Stmts: MStmt list
    Blocks: MBlock list
    Decls: MDecl list
    Logs: (Log * Loc) list }

let private mirCtxFromTyCtx (tyCtx: TyCtx): MirCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    LabelSerial = 0
    CurrentFun = None
    Stmts = []
    Blocks = []
    Decls = []
    Logs = tyCtx.Logs }

let private mirCtxIsNewTypeVariant (ctx: MirCtx) varSerial =
  match ctx.Vars |> mapFind varSerial with
  | VariantDef (_, tySerial, _, _, _, _) ->
      match ctx.Tys |> mapFind tySerial with
      | UnionTyDef (_, variantSerials, _) -> variantSerials |> List.length = 1

      | _ -> failwith "Expected union serial"

  | _ -> failwith "Expected variant serial"

let private mirCtxAddErr (ctx: MirCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

let private mirCtxNewBlock (ctx: MirCtx) = { ctx with Stmts = [] }

let private mirCtxRollBack (parentCtx: MirCtx) (ctx: MirCtx) = { ctx with Stmts = parentCtx.Stmts }

let private mirCtxPrependStmt (ctx: MirCtx) stmt =
  { ctx with
      Stmts = List.append ctx.Stmts [ stmt ] }

let private addStmtListList (ctx: MirCtx) (stmtListList: MStmt list list) =
  let stmts =
    stmtListList
    |> List.rev
    |> List.fold (fun stmts stmtList ->
         stmtList
         |> List.fold (fun stmts stmt -> stmt :: stmts) stmts) ctx.Stmts

  { ctx with Stmts = stmts }

let private mirCtxAddStmt (ctx: MirCtx) (stmt: MStmt) = { ctx with Stmts = stmt :: ctx.Stmts }

let private addTerminator (ctx: MirCtx) terminator loc =
  mirCtxAddStmt ctx (MTerminatorStmt(terminator, loc))

let private takeStmts (ctx: MirCtx) =
  List.rev ctx.Stmts, { ctx with Stmts = [] }

let private addDecl (ctx: MirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

let private takeDecls (ctx: MirCtx) =
  List.rev ctx.Decls, { ctx with Decls = [] }

let private mirCtxFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let serial = (ctx.Serial) + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> mapAdd serial (VarDef(ident, AutoSM, ty, loc)) }

  let refExpr = MRefExpr(serial, ty, loc)
  refExpr, serial, ctx

let private mirCtxLetFreshVar (ctx: MirCtx) (ident: Ident) (ty: Ty) loc =
  let refExpr, serial, ctx = mirCtxFreshVar ctx ident ty loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(serial, MUninitInit, ty, loc))

  let setStmt expr = MSetStmt(serial, expr, loc)
  refExpr, setStmt, ctx

let private mirCtxFreshLabel (ctx: MirCtx) (ident: Ident) loc =
  let serial = ctx.LabelSerial + 1

  let ctx =
    { ctx with
        LabelSerial = ctx.LabelSerial + 1 }

  let label: Label = ident + "_" + string serial
  let labelStmt = MLabelStmt(label, loc)
  labelStmt, label, ctx

/// Wraps an expression with projection operation.
/// And unbox if necessary.
let private mxProj expr index resultTy loc =
  MUnaryExpr(MProjUnary index, expr, resultTy, loc)

let private mxStrAdd ctx _op l r (_, loc) =
  MBinaryExpr(MStrAddBinary, l, r, tyStr, loc), ctx

/// x op y ==> `x op y` if `x : {scalar}`
/// where scalar types are int, char, etc.
/// C language supports all operators.
let private mxBinOpScalar ctx op l r (ty, loc) = MBinaryExpr(op, l, r, ty, loc), ctx

/// x <=> y ==> `strcmp(x, y) <=> 0` if `x : string`
let private mxStrCmp ctx op l r (ty, loc) =
  let strCmpExpr =
    MBinaryExpr(MStrCmpBinary, l, r, tyInt, loc)

  let zeroExpr = MLitExpr(IntLit 0, loc)

  let opExpr =
    MBinaryExpr(op, strCmpExpr, zeroExpr, ty, loc)

  opExpr, ctx

/// Generates a comparison expression.
let private mxCmp ctx (op: MBinary) (l: MExpr) r (ty: Ty) loc =
  assert (opIsComparison op)
  match mexprToTy l with
  | AppTy ((BoolTyCtor
           | IntTyCtor
           | UIntTyCtor
           | CharTyCtor),
           _) -> mxBinOpScalar ctx op l r (ty, loc)
  | AppTy (StrTyCtor, _) -> mxStrCmp ctx op l r (ty, loc)
  | _ -> failwithf "unimpl %A" (op, l, ty)

let private mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MLitExpr(lit, loc)

  let eqExpr, ctx =
    mxCmp ctx MEqualBinary expr litExpr tyBool loc

  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let private mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr =
    MUnaryExpr(MListIsEmptyUnary, expr, tyList itemTy, loc)

  let gotoStmt = msGotoUnless isEmptyExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let private mirifyPatNone ctx endLabel itemTy expr loc =
  mirifyPatNil ctx endLabel itemTy expr loc

let private mirifyPatCons ctx endLabel l r itemTy loc expr =
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

let private mirifyPatSome ctx endLabel item itemTy loc expr =
  let nilPat = HNilPat(itemTy, loc)
  mirifyPatCons ctx endLabel item nilPat itemTy loc expr

let private mirifyPatRef ctx _endLabel serial ty loc expr =
  true, mirCtxAddStmt ctx (MLetValStmt(serial, MExprInit expr, ty, loc))

let private mirifyPatVariant ctx endLabel serial ty loc expr =
  // Compare tags.
  let lTagExpr = MUnaryExpr(MTagUnary, expr, tyInt, loc)
  let rTagExpr = MRefExpr(serial, tyInt, loc)

  let eqExpr =
    MBinaryExpr(MEqualBinary, lTagExpr, rTagExpr, tyBool, loc)

  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = mirCtxAddStmt ctx gotoStmt
  false, ctx

let private mirifyPatCall (ctx: MirCtx) itself endLabel serial args _ty loc expr =
  match args with
  | [ payload ] ->
      let extractExpr =
        MUnaryExpr(MGetVariantUnary serial, expr, patToTy payload, loc)

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

  | _ -> failwithf "NEVER: %A" itself

let private mirifyPatTuple ctx endLabel itemPats itemTys expr loc =
  let rec go covered ctx i itemPats itemTys =
    match itemPats, itemTys with
    | [], [] -> covered, ctx
    | itemPat :: itemPats, itemTy :: itemTys ->
        let item = mxProj expr i itemTy loc
        let itemCovered, ctx = mirifyPat ctx endLabel itemPat item
        go (covered && itemCovered) ctx (i + 1) itemPats itemTys
    | _ -> failwith "Never"

  go true ctx 0 itemPats itemTys

let private mirifyPatBox ctx endLabel itemPat expr loc =
  let ty, _ = patExtract itemPat
  mirifyPat ctx endLabel itemPat (MUnaryExpr(MUnboxUnary, expr, ty, loc))

let private mirifyPatAs ctx endLabel pat serial expr loc =
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
let private mirifyPat ctx (endLabel: string) (pat: HPat) (expr: MExpr): bool * MirCtx =
  match pat with
  | HDiscardPat _ ->
      // Discard the result, which we know is pure.
      // FIXME: This should be done in optimization?
      true, ctx

  | HLitPat (lit, loc) -> mirifyPatLit ctx endLabel lit expr loc
  | HNilPat (itemTy, loc) -> mirifyPatNil ctx endLabel itemTy expr loc
  | HNonePat (itemTy, loc) -> mirifyPatNone ctx endLabel itemTy expr loc
  | HRefPat (serial, ty, loc) -> mirifyPatRef ctx endLabel serial ty loc expr
  | HVariantPat (serial, ty, loc) -> mirifyPatVariant ctx endLabel serial ty loc expr
  | HCallPat (HVariantPat (variantSerial, _, _), args, ty, loc) ->
      mirifyPatCall ctx pat endLabel variantSerial args ty loc expr
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
  | HCallPat _ -> failwithf "Never: Call pattern incorrect. %A" pat
  | HTuplePat _ -> failwith "Never: Tuple pattern must be of tuple type."
  | HAnnoPat _ -> failwith "Never annotation pattern in MIR-ify stage."

let private mirifyExprVariant (ctx: MirCtx) itself serial ty loc =
  match ctx.Vars |> mapTryFind serial with
  | Some (VariantDef (_, tySerial, _, _, _, _)) -> MVariantExpr(tySerial, serial, ty, loc), ctx
  | _ -> failwithf "NEVER: Illegal HVariantExpr. %A" itself

let private mirifyExprPrim (ctx: MirCtx) prim ty loc =
  match prim with
  | HPrim.Nil -> MDefaultExpr(ty, loc), ctx

  | HPrim.OptionNone -> MDefaultExpr(ty, loc), ctx

  | _ -> failwithf "Never: Primitives must appear as callee."

let private doEmitIfStmt ctx cond thenHint body altHint alt targetTy loc =
  let temp, tempSet, ctx = mirCtxLetFreshVar ctx "if" targetTy loc
  let nextLabelStmt, nextLabel, ctx = mirCtxFreshLabel ctx "if_next" loc

  // Then clause.
  let thenLabelStmt, thenLabel, ctx = mirCtxFreshLabel ctx thenHint loc
  let parentCtx, ctx = ctx, mirCtxNewBlock ctx

  let body, ctx =
    let ctx = mirCtxAddStmt ctx thenLabelStmt
    let body, ctx = mirifyExpr ctx body
    let ctx = mirCtxAddStmt ctx (tempSet body)

    let ctx =
      addTerminator ctx (MGotoTerminator nextLabel) loc

    takeStmts ctx

  let ctx = mirCtxRollBack parentCtx ctx

  // Else clause. (Almost same as then clause.)
  let elseLabelStmt, elseLabel, ctx = mirCtxFreshLabel ctx altHint loc
  let parentCtx, ctx = ctx, mirCtxNewBlock ctx

  let alt, ctx =
    let ctx = mirCtxAddStmt ctx elseLabelStmt
    let alt, ctx = mirifyExpr ctx alt
    let ctx = mirCtxAddStmt ctx (tempSet alt)

    let ctx =
      addTerminator ctx (MGotoTerminator nextLabel) loc

    takeStmts ctx

  let ctx = mirCtxRollBack parentCtx ctx

  // End of if.
  let ctx =
    addTerminator ctx (MIfTerminator(cond, MGotoTerminator thenLabel, MGotoTerminator elseLabel)) loc

  let ctx = addStmtListList ctx [ alt; body ]
  let ctx = mirCtxAddStmt ctx nextLabelStmt
  temp, ctx

/// Tries to *sugar* a match expression to if expression
/// when `match p with true -> body | false -> alt`.
let private mirifyExprMatchAsIfStmt ctx cond arms ty loc =
  match exprToTy cond, arms with
  | AppTy (BoolTyCtor, []),
    [ HLitPat (BoolLit true, _), HLitExpr (BoolLit true, _), body;
      HLitPat (BoolLit false, _), HLitExpr (BoolLit true, _), alt ] ->
      let cond, ctx = mirifyExpr ctx cond

      doEmitIfStmt ctx cond "then" body "else" alt ty loc
      |> Some

  | AppTy (ListTyCtor, _),
    [ HNonePat _, HLitExpr (BoolLit true, _), noneCl; HDiscardPat _, HLitExpr (BoolLit true, _), someCl ] ->
      let cond, ctx = mirifyExpr ctx cond

      let isNone =
        let ty, loc = mexprExtract cond
        MUnaryExpr(MListIsEmptyUnary, cond, ty, loc)

      doEmitIfStmt ctx isNone "none_cl" noneCl "some_cl" someCl ty loc
      |> Some

  | AppTy (ListTyCtor, _),
    [ HNilPat _, HLitExpr (BoolLit true, _), nilCl; HDiscardPat _, HLitExpr (BoolLit true, _), consCl ] ->
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
    | AppTy (IntTyCtor, [])
    | AppTy (CharTyCtor, [])
    | AppTy (RefTyCtor _, _) -> true

    | _ -> false

  let rec patIsSimpleAtomic pat =
    match pat with
    | HLitPat _
    | HVariantPat _
    | HDiscardPat _ -> true

    | HBoxPat (bodyPat, _) -> patIsSimpleAtomic bodyPat

    | _ -> false

  /// Pattern is simple, i.e. flat, non-binding and disjunctive-normalized.
  let rec patIsSimple pat =
    match pat with
    | HLitPat _
    | HVariantPat _
    | HDiscardPat _ -> true

    | HCallPat (HVariantPat _, [ payload ], _, _) -> patIsSimpleAtomic payload

    | HOrPat (l, r, _, _) -> patIsSimple l && patIsSimple r

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

    | HVariantPat (variantSerial, _, _) -> [ MTagConst variantSerial ], false

    | HCallPat (HVariantPat (variantSerial, _, _), _, _, _) -> [ MTagConst variantSerial ], false

    | HOrPat (l, r, _, _) ->
        let lCases, lIsDefault = go l
        let rCases, rIsDefault = go r

        if lIsDefault || rIsDefault then
          [], true
        else
          let cases = List.append rCases lCases // reverse order
          cases, false

    | _ -> failwithf "NEVER: %A" pat

  let temp, tempSet, ctx = mirCtxLetFreshVar ctx "switch" ty loc
  let nextLabelStmt, nextLabel, ctx = mirCtxFreshLabel ctx "switch_next" loc

  let cond, ctx =
    let condTy, condLoc = exprExtract cond
    let cond, ctx = mirifyExpr ctx cond

    match condTy with
    | AppTy (RefTyCtor _, _) -> MUnaryExpr(MTagUnary, cond, tyInt, condLoc), ctx
    | _ -> cond, ctx

  let exhaust, clauses, blocks, ctx =
    arms
    |> List.fold (fun (hasDefault, clauses, blocks, ctx) (pat, _, body) ->
         if hasDefault then
           true, clauses, blocks, ctx
         else
           let _, clauseLoc = patExtract pat
           let clauseLabelStmt, clauseLabel, ctx = mirCtxFreshLabel ctx "clause" clauseLoc

           let cases, isDefault = go pat

           let clause: MSwitchClause =
             { Cases = cases
               IsDefault = isDefault
               Terminator = MGotoTerminator clauseLabel }

           // Generate body.
           let parentCtx, ctx = ctx, mirCtxNewBlock ctx

           let block, ctx =
             let ctx = mirCtxAddStmt ctx clauseLabelStmt
             let body, ctx = mirifyExpr ctx body
             let ctx = mirCtxAddStmt ctx (tempSet body)

             let ctx =
               addTerminator ctx (MGotoTerminator nextLabel) loc

             takeStmts ctx

           let ctx = mirCtxRollBack parentCtx ctx

           hasDefault || isDefault, clause :: clauses, block :: blocks, ctx) (false, [], [], ctx)

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
  let ctx = mirCtxAddStmt ctx nextLabelStmt

  temp, ctx

/// Gets if the target must match with any of the patterns.
let private patsIsCovering pats =
  let rec go pat =
    match pat with
    | HDiscardPat _
    | HRefPat _ -> true

    | HLitPat _
    | HNilPat _
    | HNonePat _
    | HSomePat _
    | HVariantPat _
    | HNavPat _
    | HConsPat _
    | HCallPat _ -> false
    | HTuplePat (itemPats, _, _) -> itemPats |> List.forall go
    | HBoxPat (itemPat, _) -> go itemPat
    | HAsPat (pat, _, _) -> go pat
    | HAnnoPat (pat, _, _) -> go pat
    | HOrPat (first, second, _, _) -> go first || go second

  List.exists go pats

let private mirifyExprMatchFull ctx target arms ty loc =
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
          addTerminator ctx (MGotoTerminator bodyLabel) loc

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
          addTerminator ctx (MGotoTerminator endLabel) loc

        emit ctx rest
    | [] ->
        // Abort if exhaust.
        if isCovering then ctx else addTerminator ctx (mtAbort loc) loc

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = mirCtxAddStmt ctx endLabelStmt

  temp, ctx

let private mirifyExprMatch ctx target arms ty loc =
  match mirifyExprMatchAsIfStmt ctx target arms ty loc with
  | Some (result, ctx) -> result, ctx
  | None ->
      if matchExprCanCompileToSwitch target arms
      then mirifyExprMatchAsSwitchStmt ctx target arms ty loc
      else mirifyExprMatchFull ctx target arms ty loc

let private mirifyExprIndex ctx l r _ loc =
  match exprToTy l, exprToTy r with
  | AppTy (StrTyCtor, _), AppTy (IntTyCtor, _) ->
      let l, ctx = mirifyExpr ctx l
      let r, ctx = mirifyExpr ctx r
      MBinaryExpr(MStrIndexBinary, l, r, tyChar, loc), ctx
  | _ -> failwith "unimpl non-string indexing"

let private mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg

  let ctx =
    mirCtxAddStmt ctx (MTerminatorStmt(MExitTerminator arg, loc))

  MDefaultExpr(ty, loc), ctx

let private mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = mirCtxFreshVar ctx "box" tyObj loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MBoxInit arg, tyObj, loc))

  temp, ctx

let private mirifyExprCallUnbox ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MUnboxUnary, arg, ty, loc), ctx

let private mirifyExprCallStrLength ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MStrLenUnary, arg, ty, loc), ctx

let private mirifyExprCallSome ctx item ty loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "some" ty loc

  let item, ctx = mirifyExpr ctx item
  let nil = MDefaultExpr(ty, loc)

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MConsInit(item, nil), ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

/// not a ==> !a
let private mirifyExprCallNot ctx arg ty notLoc =
  let arg, ctx = mirifyExpr ctx arg
  MUnaryExpr(MNotUnary, arg, ty, notLoc), ctx

let private mirifyExprCallVariantFun (ctx: MirCtx) serial payload ty loc =
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

let private mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = mirCtxFreshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MConsInit(l, r), listTy, loc))

  MRefExpr(tempSerial, listTy, loc), ctx

let private mirifyExprTuple ctx items itemTys loc =
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

let private mirifyExprTupleItem ctx index tuple itemTy loc =
  let tuple, ctx = mirifyExpr ctx tuple
  MUnaryExpr(MProjUnary index, tuple, itemTy, loc), ctx

let private mirifyExprOpArith ctx op l r ty loc =
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

let private mirifyExprOpCmp ctx op l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  mxCmp ctx op l r ty loc

let private mirifyExprSemi ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let private mirifyExprInfCallProc ctx callee args ty loc =
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

  | HVariantExpr (serial, _, _), [ arg ] -> mirifyExprCallVariantFun ctx serial arg ty loc

  | _ -> core ()

let private mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee

  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "app" resultTy loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MCallClosureInit(callee, args), resultTy, loc))

  tempRef, ctx

let private mirifyExprInfCallTailRec (ctx: MirCtx) _callee args ty loc =
  // It's guaranteed that callee points to the current fun,
  // but it's serial can now be wrong due to monomorphization.

  let label, argSerials =
    match ctx.CurrentFun with
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
    addTerminator ctx (MGotoTerminator label) loc

  MDefaultExpr(ty, loc), ctx

let private mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = mirCtxFreshVar ctx "env" envTy envLoc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(envSerial, MExprInit env, envTy, envLoc))

  let tempRef, tempSerial, ctx = mirCtxFreshVar ctx "fun" funTy loc

  let ctx =
    mirCtxAddStmt ctx (MLetValStmt(tempSerial, MClosureInit(funSerial, envSerial), funTy, loc))

  tempRef, ctx

let private mirifyExprInf ctx infOp args ty loc =
  match infOp, args, ty with
  | InfOp.Tuple, [], AppTy (TupleTyCtor, []) -> MDefaultExpr(tyUnit, loc), ctx
  | InfOp.Tuple, _, AppTy (TupleTyCtor, itemTys) -> mirifyExprTuple ctx args itemTys loc
  | InfOp.TupleItem index, [ tuple ], itemTy -> mirifyExprTupleItem ctx index tuple itemTy loc
  | InfOp.Semi, _, _ -> mirifyExprSemi ctx args
  | InfOp.CallProc, callee :: args, _ -> mirifyExprInfCallProc ctx callee args ty loc
  | InfOp.CallTailRec, callee :: args, _ -> mirifyExprInfCallTailRec ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ -> mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.Closure, [ HFunExpr (funSerial, _, _); env ], _ -> mirifyExprInfClosure ctx funSerial env ty loc
  | t -> failwithf "Never: %A" t

let private mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init

  let ctx =
    if exhaustive
    then ctx
    else mirCtxAddErr ctx "Let pattern must be exhaustive for now" letLoc

  let next, ctx = mirifyExpr ctx next
  next, ctx

let private mirifyExprLetFun (ctx: MirCtx) calleeSerial isMainFun argPats body next letLoc =
  let prepareTailRec (ctx: MirCtx) args =
    let parentFun = ctx.CurrentFun

    let currentFun, ctx =
      if body |> containsTailRec then
        let labelStmt, label, ctx = mirCtxFreshLabel ctx "tailrec" letLoc
        let ctx = mirCtxPrependStmt ctx labelStmt
        let argSerials = args |> List.map (fun (it, _, _) -> it)
        Some(label, argSerials), ctx
      else
        None, ctx

    let ctx = { ctx with CurrentFun = currentFun }
    parentFun, ctx

  let cleanUpTailRec (ctx: MirCtx) parentFun = { ctx with CurrentFun = parentFun }

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

  let mirifyFunBody (ctx: MirCtx) argPats body =
    let blockTy, blockLoc = exprExtract body

    let args, ctx = defineArgs [] ctx argPats
    let parentFun, ctx = prepareTailRec ctx args
    let lastExpr, ctx = mirifyExpr ctx body

    let ctx =
      addTerminator ctx (MReturnTerminator lastExpr) blockLoc

    let ctx = cleanUpTailRec ctx parentFun

    let body, ctx =
      let stmts, ctx = takeStmts ctx
      let block: MBlock = { Stmts = stmts }
      [ block ], ctx

    args, blockTy, body, ctx

  let core () =
    let bodyCtx = mirCtxNewBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = mirCtxRollBack ctx bodyCtx

    let ctx =
      addDecl ctx (MProcDecl(calleeSerial, isMainFun, args, body, resultTy, letLoc))

    ctx

  let ctx = core ()
  let next, ctx = mirifyExpr ctx next
  next, ctx

let private mirifyExprTyDecl ctx _tySerial _tyDecl loc = MDefaultExpr(tyUnit, loc), ctx

let private mirifyExprOpen ctx loc = MDefaultExpr(tyUnit, loc), ctx

let private mirifyDecl ctx expr =
  match expr with
  | HLetValExpr (_vis, pat, body, next, _, loc) -> mirifyExprLetVal ctx pat body next loc
  | HLetFunExpr (serial, _vis, isMainFun, args, body, next, _, loc) ->
      mirifyExprLetFun ctx serial isMainFun args body next loc
  | HTyDeclExpr (tySerial, _vis, _, tyDecl, loc) -> mirifyExprTyDecl ctx tySerial tyDecl loc
  | HOpenExpr (_, loc) -> mirifyExprOpen ctx loc
  | _ -> failwith "NEVER"

let private mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HLitExpr (lit, loc) -> MLitExpr(lit, loc), ctx
  | HRefExpr (serial, ty, loc) -> MRefExpr(serial, ty, loc), ctx
  | HFunExpr (serial, ty, loc) -> MProcExpr(serial, ty, loc), ctx
  | HVariantExpr (serial, ty, loc) -> mirifyExprVariant ctx expr serial ty loc
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

let private mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] -> List.rev acc, ctx
    | expr :: exprs ->
        let expr, ctx = mirifyExpr ctx expr
        go (expr :: acc) ctx exprs

  go [] ctx exprs

let mirify (expr: HExpr, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = mirCtxFromTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx = mirifyExpr ctx expr

  takeDecls ctx
