/// # MirGen
///
/// Converts HIR to MIR.
///
/// Deconstructs pattern matching.
module rec MiloneLang.MirGen

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeIntegers
open MiloneLang.Hir
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Mir

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type MirCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>
    LabelSerial: Serial

    /// (label, parameters), where the label is the entrypoint of current fun.
    /// For tail-rec (tail-call) optimization.
    CurrentFun: (Label * VarSerial list) option

    Stmts: MStmt list
    Blocks: MBlock list
    Decls: MDecl list
    Logs: (Log * Loc) list }

let private ofTyCtx (tyCtx: TyCtx): MirCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    LabelSerial = 0
    CurrentFun = None
    Stmts = []
    Blocks = []
    Decls = []
    Logs = tyCtx.Logs }

let private isNewtypeVariant (ctx: MirCtx) variantSerial =
  match ctx.Variants |> mapTryFind variantSerial with
  | Some variantDef ->
      match ctx.Tys |> mapFind variantDef.UnionTySerial with
      | UnionTyDef (_, variantSerials, _) -> variantSerials |> List.length = 1

      | _ -> failwith "Expected union serial"

  | _ -> failwith "Expected variant serial"

let private addError (ctx: MirCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

let private startBlock (ctx: MirCtx) = { ctx with Stmts = [] }

let private rollback (parentCtx: MirCtx) (ctx: MirCtx) = { ctx with Stmts = parentCtx.Stmts }

let private prependStmt (ctx: MirCtx) stmt =
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

let private addStmt (ctx: MirCtx) (stmt: MStmt) = { ctx with Stmts = stmt :: ctx.Stmts }

let private addTerminator (ctx: MirCtx) terminator loc =
  addStmt ctx (MTerminatorStmt(terminator, loc))

let private takeStmts (ctx: MirCtx) =
  List.rev ctx.Stmts, { ctx with Stmts = [] }

let private addDecl (ctx: MirCtx) decl = { ctx with Decls = decl :: ctx.Decls }

let private takeDecls (ctx: MirCtx) =
  List.rev ctx.Decls, { ctx with Decls = [] }

let private freshVar (ctx: MirCtx) (name: Ident) (ty: Ty) loc =
  let varSerial = VarSerial(ctx.Serial + 1)

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> mapAdd varSerial (VarDef(name, AutoSM, ty, loc)) }

  let refExpr = MRefExpr(varSerial, ty, loc)
  refExpr, varSerial, ctx

let private letFreshVar (ctx: MirCtx) (name: Ident) (ty: Ty) loc =
  let refExpr, serial, ctx = freshVar ctx name ty loc

  let ctx =
    addStmt ctx (MLetValStmt(serial, MUninitInit, ty, loc))

  let setStmt expr = MSetStmt(serial, expr, loc)
  refExpr, setStmt, ctx

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

let private mxNot expr loc = MUnaryExpr(MNotUnary, expr, tyBool, loc)

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
  | AppTy ((IntTyCtor _
           | FloatTyCtor _
           | BoolTyCtor
           | CharTyCtor),
           _) -> mxBinOpScalar ctx op l r (ty, loc)
  | AppTy (StrTyCtor, _) -> mxStrCmp ctx op l r (ty, loc)
  | _ -> failwithf "unimpl %A" (op, l, ty)

let private mtAbort loc = MExitTerminator(MLitExpr(IntLit 1, loc))

let private msGotoUnless pred label loc =
  let notPred = mxNot pred loc
  MTerminatorStmt(MGotoIfTerminator(notPred, label), loc)

// -----------------------------------------------
// Other helpers
// -----------------------------------------------

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

  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private mirifyPatLit ctx endLabel lit expr loc =
  let litExpr = MLitExpr(lit, loc)

  let eqExpr, ctx =
    mxCmp ctx MEqualBinary expr litExpr tyBool loc

  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
  false, ctx

let private mirifyPatNil ctx endLabel itemTy expr loc =
  let isEmptyExpr =
    MUnaryExpr(MListIsEmptyUnary, expr, tyList itemTy, loc)

  let gotoStmt = msGotoUnless isEmptyExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
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
  let ctx = addStmt ctx gotoStmt

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
  true, addStmt ctx (MLetValStmt(serial, MExprInit expr, ty, loc))

let private mirifyPatVariant ctx endLabel serial ty loc expr =
  // Compare tags.
  let lTagExpr = MUnaryExpr(MTagUnary, expr, tyInt, loc)
  let rTagExpr = MTagExpr(serial, loc)

  let eqExpr =
    MBinaryExpr(MEqualBinary, lTagExpr, rTagExpr, tyBool, loc)

  let gotoStmt = msGotoUnless eqExpr endLabel loc
  let ctx = addStmt ctx gotoStmt
  false, ctx

let private mirifyPatCall (ctx: MirCtx) itself endLabel serial args _ty loc expr =
  match args with
  | [ payload ] ->
      let extractExpr =
        MUnaryExpr(MGetVariantUnary serial, expr, patToTy payload, loc)

      // Special treatment for new-type variants
      // so that we can deconstruct it with irrefutable patterns
      // (`let` and arguments) without generating an abort branch.
      if isNewtypeVariant ctx serial then
        mirifyPat ctx endLabel payload extractExpr
      else

        // Compare tags.
        let lTagExpr = MUnaryExpr(MTagUnary, expr, tyInt, loc)
        let rTagExpr = MTagExpr(serial, loc)

        let eqExpr =
          MBinaryExpr(MEqualBinary, lTagExpr, rTagExpr, tyBool, loc)

        let gotoStmt = msGotoUnless eqExpr endLabel loc
        let ctx = addStmt ctx gotoStmt

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
    addStmt ctx (MLetValStmt(serial, MExprInit expr, ty, loc))

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
        addError ctx "Some pattern must be used in the form of `Some pat`" loc

      false, ctx

  | HOrPat _ -> failwith "Unimpl nested OR pattern."
  | HNavPat _ -> failwith "Never: Nav pattern in mirify"
  | HCallPat _ -> failwithf "Never: Call pattern incorrect. %A" pat
  | HTuplePat _ -> failwith "Never: Tuple pattern must be of tuple type."
  | HAnnoPat _ -> failwith "Never annotation pattern in MIR-ify stage."

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private mirifyExprVariant (ctx: MirCtx) itself serial ty loc =
  match ctx.Variants |> mapTryFind serial with
  | Some variantDef -> MVariantExpr(variantDef.UnionTySerial, serial, ty, loc), ctx
  | _ -> failwithf "NEVER: Illegal HVariantExpr. %A" itself

let private mirifyExprPrim (ctx: MirCtx) prim ty loc =
  match prim with
  | HPrim.Nil -> MDefaultExpr(ty, loc), ctx
  | HPrim.OptionNone -> MDefaultExpr(ty, loc), ctx

  | _ -> failwithf "Never: Primitives must appear as callee."

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
    | AppTy (IntTyCtor _, [])
    | AppTy (CharTyCtor, [])
    | AppTy (UnionTyCtor _, _) -> true

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

  let temp, tempSet, ctx = letFreshVar ctx "switch" ty loc
  let nextLabelStmt, nextLabel, ctx = freshLabel ctx "switch_next" loc

  let cond, ctx =
    let condTy, condLoc = exprExtract cond
    let cond, ctx = mirifyExpr ctx cond

    match condTy with
    | AppTy (UnionTyCtor _, _) -> MUnaryExpr(MTagUnary, cond, tyInt, condLoc), ctx
    | _ -> cond, ctx

  let exhaust, clauses, blocks, ctx =
    arms
    |> List.fold (fun (hasDefault, clauses, blocks, ctx) (pat, _, body) ->
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
  let ctx = addStmt ctx nextLabelStmt

  temp, ctx

/// Gets if the pattern matching must succeed.
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

let private mirifyExprMatchFull ctx cond arms ty loc =
  let noLabel = "<NEVER>"
  let temp, tempSet, ctx = letFreshVar ctx "match" ty loc
  let endLabelStmt, endLabel, ctx = freshLabel ctx "end_match" loc

  let cond, ctx = mirifyExpr ctx cond

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
          if guard |> hxIsAlwaysTrue then acc else MatchIR.Guard(guard, nextLabel) :: acc

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
        let _, ctx = mirifyPat ctx nextLabel pat cond
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
        if isCovering then ctx else addTerminator ctx (mtAbort loc) loc

  let instructionsRev, ctx = goArms ctx [] true arms
  let instructions = fixUp [] endLabel instructionsRev
  let ctx = emit ctx instructions
  let ctx = addStmt ctx endLabelStmt

  temp, ctx

let private mirifyExprMatch ctx cond arms ty loc =
  match mirifyExprMatchAsIfStmt ctx cond arms ty loc with
  | Some (result, ctx) -> result, ctx

  | None ->
      if matchExprCanCompileToSwitch cond arms
      then mirifyExprMatchAsSwitchStmt ctx cond arms ty loc
      else mirifyExprMatchFull ctx cond arms ty loc

// -----------------------------------------------
// Expressions
// -----------------------------------------------

let private mirifyExprCallExit ctx arg ty loc =
  let arg, ctx = mirifyExpr ctx arg

  let ctx =
    addStmt ctx (MTerminatorStmt(MExitTerminator arg, loc))

  MDefaultExpr(ty, loc), ctx

let private mirifyExprCallBox ctx arg _ loc =
  let arg, ctx = mirifyExpr ctx arg
  let temp, tempSerial, ctx = freshVar ctx "box" tyObj loc

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MBoxInit arg, tyObj, loc))

  temp, ctx

let mirifyCallStrIndexExpr ctx l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  MBinaryExpr(MStrIndexBinary, l, r, ty, loc), ctx

let private mirifyCallStrGetSliceExpr ctx args loc =
  assert (List.length args = 3)

  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let temp, tempSerial, ctx = freshVar ctx "slice" tyStr loc
  let init = MPrimInit(MStrGetSlicePrim, args)

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, init, tyStr, loc))

  temp, ctx

let private mirifyExprCallSome ctx item ty loc =
  let _, tempSerial, ctx = freshVar ctx "some" ty loc

  let item, ctx = mirifyExpr ctx item
  let nil = MDefaultExpr(ty, loc)

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MConsInit(item, nil), ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

let private mirifyCallVariantExpr (ctx: MirCtx) serial payload ty loc =
  let payload, ctx = mirifyExpr ctx payload
  let payloadTy = mexprToTy payload

  // FIXME: Generate a serial to reduce diff. Remove this later.
  let _, _payloadSerial, ctx = freshVar ctx "payload" payloadTy loc

  let temp, tempSerial, ctx = freshVar ctx "variant" ty loc
  let init = MVariantInit(serial, payload)

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, init, ty, loc))

  temp, ctx

let private mirifyExprOpCons ctx l r listTy loc =
  let _, tempSerial, ctx = freshVar ctx "list" listTy loc

  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MConsInit(l, r), listTy, loc))

  MRefExpr(tempSerial, listTy, loc), ctx

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
    addStmt ctx (MLetValStmt(tempSerial, MTupleInit items, ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

let private mirifyExprRecord (ctx: MirCtx) args ty loc =
  let name =
    match ty with
    | AppTy (RecordTyCtor tySerial, _) -> ctx.Tys |> mapFind tySerial |> tyDefToName
    | _ -> failwith "NEVER"

  let _, tempSerial, ctx = freshVar ctx name ty loc

  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MRecordInit args, ty, loc))

  MRefExpr(tempSerial, ty, loc), ctx

let private mirifyExprRecordItem ctx index tuple itemTy loc =
  let record, ctx = mirifyExpr ctx tuple
  MUnaryExpr(MRecordItemUnary index, record, itemTy, loc), ctx

let private mirifyExprOpArith ctx itself op l r ty loc =
  let lTy = exprToTy l
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match lTy with
  | AppTy ((IntTyCtor _
           | FloatTyCtor _
           | CharTyCtor),
           _) -> mxBinOpScalar ctx op l r (ty, loc)

  | AppTy (StrTyCtor, _) when op |> mOpIsAdd -> mxStrAdd ctx op l r (ty, loc)

  | _ -> failwithf "NEVER: %A" itself

let private mirifyExprOpCmp ctx op l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r
  mxCmp ctx op l r ty loc

let private mirifyCallCompareExpr ctx itself l r ty loc =
  let l, ctx = mirifyExpr ctx l
  let r, ctx = mirifyExpr ctx r

  match mexprToTy l with
  // Comparison of small or unsigned integers is just `-` for not overflow.
  | AppTy ((IntTyCtor (IntFlavor (_, I8))
           | IntTyCtor (IntFlavor (_, I16))
           | BoolTyCtor
           | CharTyCtor),
           _) -> MBinaryExpr(MSubBinary, l, r, tyInt, loc), ctx

  | AppTy (IntTyCtor (IntFlavor (Signed, I32)), _) -> MBinaryExpr(MIntCompareBinary, l, r, tyInt, loc), ctx

  | AppTy ((IntTyCtor (IntFlavor (Signed, I64))
           | IntTyCtor (IntFlavor (Signed, IPtr))
           | NativePtrTyCtor _),
           _) -> MBinaryExpr(MInt64CompareBinary, l, r, tyInt, loc), ctx

  | AppTy ((IntTyCtor (IntFlavor (Unsigned, _))), _) -> MBinaryExpr(MUInt64CompareBinary, l, r, tyInt, loc), ctx

  | AppTy (StrTyCtor, _) -> MBinaryExpr(MStrCmpBinary, l, r, tyInt, loc), ctx

  | _ -> failwithf "NEVER: %A" itself

let private mirifyExprSemi ctx exprs =
  // Discard non-last expressions.
  let exprs, ctx = mirifyExprs ctx exprs
  List.last exprs, ctx

let private mirifyCallToIntExpr ctx itself flavor arg ty loc =
  let srcTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match srcTy with
  | AppTy (IntTyCtor srcFlavor, _) when intFlavorEq srcFlavor flavor -> arg, ctx

  | AppTy ((IntTyCtor _
           | FloatTyCtor _
           | CharTyCtor
           | NativePtrTyCtor _),
           _) -> MUnaryExpr(MIntOfScalarUnary flavor, arg, AppTy(IntTyCtor flavor, []), loc), ctx

  | AppTy (StrTyCtor, _) ->
      let temp, tempSerial, ctx = freshVar ctx "call" ty loc

      let ctx =
        addStmt ctx (MLetValStmt(tempSerial, MPrimInit(MIntOfStrPrim flavor, [ arg ]), ty, loc))

      temp, ctx

  | _ -> failwithf "NEVER: %A" itself

let private mirifyCallToFloatExpr ctx itself flavor arg ty loc =
  let srcTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match srcTy with
  | AppTy (FloatTyCtor _, _) -> arg, ctx

  | AppTy (IntTyCtor _, _) -> MUnaryExpr(MFloatOfScalarUnary flavor, arg, tyFloat, loc), ctx

  | AppTy (StrTyCtor, _) ->
      let temp, tempSerial, ctx = freshVar ctx "call" ty loc

      let ctx =
        addStmt ctx (MLetValStmt(tempSerial, MPrimInit(MFloatOfStrPrim flavor, [ arg ]), ty, loc))

      temp, ctx

  | _ -> failwithf "NEVER: %A" itself

let private mirifyCallCharExpr ctx itself arg ty loc =
  let argTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  match argTy with
  | AppTy (CharTyCtor, _) -> arg, ctx

  | AppTy (IntTyCtor _, _)
  | AppTy (NativePtrTyCtor _, _) -> MUnaryExpr(MCharOfScalarUnary, arg, tyInt, loc), ctx

  | _ -> failwithf "NEVER: %A" itself

let private mirifyCallStringExpr ctx itself arg ty loc =
  let argTy = arg |> exprToTy
  let arg, ctx = mirifyExpr ctx arg

  let usePrim prim =
    let temp, tempSerial, ctx = freshVar ctx "call" ty loc

    let ctx =
      addStmt ctx (MLetValStmt(tempSerial, MPrimInit(prim, [ arg ]), ty, loc))

    temp, ctx

  match argTy with
  | AppTy (StrTyCtor, _) -> arg, ctx

  | AppTy (IntTyCtor flavor, _) -> usePrim (MStrOfIntPrim flavor)
  | AppTy (FloatTyCtor flavor, _) -> usePrim (MStrOfFloatPrim flavor)
  | AppTy (BoolTyCtor, _) -> usePrim MStrOfBoolPrim
  | AppTy (CharTyCtor, _) -> usePrim MStrOfCharPrim

  | _ -> failwithf "NEVER: %A" itself

let private mirifyCallAssertExpr ctx arg loc =
  let arg, ctx = mirifyExpr ctx arg

  // Embed the source location information.
  let args =
    let _, y, x = loc
    [ arg
      MLitExpr(IntLit y, loc)
      MLitExpr(IntLit x, loc) ]

  let ctx =
    addStmt ctx (MActionStmt(MAssertAction, args, loc))

  MDefaultExpr(tyUnit, loc), ctx

let private mirifyCallInRegionExpr ctx arg ty loc =
  // arg: closure
  let arg, ctx = mirifyExpr ctx arg

  let temp, tempSerial, ctx = freshVar ctx "region_result" tyInt loc

  let ctx =
    addStmt ctx (MActionStmt(MEnterRegionAction, [], loc))

  let ctx =
    let unit = MDefaultExpr(tyUnit, loc)
    addStmt ctx (MLetValStmt(tempSerial, MCallClosureInit(arg, [ unit ]), ty, loc))

  let ctx =
    addStmt ctx (MActionStmt(MLeaveRegionAction, [], loc))

  temp, ctx

let private mirifyCallPrintfnExpr ctx args loc =
  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let ctx =
    addStmt ctx (MActionStmt(MPrintfnAction, args, loc))

  MDefaultExpr(tyUnit, loc), ctx

let private mirifyCallProcExpr ctx callee args ty loc =
  let calleeTy = exprToTy callee
  let callee, ctx = mirifyExpr ctx callee

  let (args, ctx) =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let temp, tempSerial, ctx = freshVar ctx "call" ty loc

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MCallProcInit(callee, args, calleeTy), ty, loc))

  temp, ctx

let private mirifyCallPrimExpr ctx itself prim args ty loc =
  let fail () = failwithf "NEVER: %A" itself

  let regularUnary unary arg =
    let arg, ctx = mirifyExpr ctx arg
    MUnaryExpr(unary, arg, ty, loc), ctx

  let regularBinary binary l r =
    let l, ctx = mirifyExpr ctx l
    let r, ctx = mirifyExpr ctx r
    MBinaryExpr(binary, l, r, ty, loc), ctx

  match prim, args with
  | HPrim.Add, [ l; r ] -> mirifyExprOpArith ctx itself MAddBinary l r ty loc
  | HPrim.Add, _ -> fail ()
  | HPrim.Sub, [ l; r ] -> mirifyExprOpArith ctx itself MSubBinary l r ty loc
  | HPrim.Sub, _ -> fail ()
  | HPrim.Mul, [ l; r ] -> mirifyExprOpArith ctx itself MMulBinary l r ty loc
  | HPrim.Mul, _ -> fail ()
  | HPrim.Div, [ l; r ] -> mirifyExprOpArith ctx itself MDivBinary l r ty loc
  | HPrim.Div, _ -> fail ()
  | HPrim.Mod, [ l; r ] -> mirifyExprOpArith ctx itself MModBinary l r ty loc
  | HPrim.Mod, _ -> fail ()

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

  | HPrim.Eq, [ l; r ] -> mirifyExprOpCmp ctx MEqualBinary l r ty loc
  | HPrim.Eq, _ -> fail ()
  | HPrim.Lt, [ l; r ] -> mirifyExprOpCmp ctx MLessBinary l r ty loc
  | HPrim.Lt, _ -> fail ()
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
  | HPrim.Unbox, [ arg ] -> regularUnary MUnboxUnary arg
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
  | HPrim.InRegion, [ arg ] -> mirifyCallInRegionExpr ctx arg ty loc
  | HPrim.InRegion, _ -> fail ()
  | HPrim.Printfn, _ -> mirifyCallPrintfnExpr ctx args loc
  | HPrim.NativeCast, [ arg ] -> regularUnary MNativeCastUnary arg
  | HPrim.NativeCast, _ -> fail ()

  | HPrim.Nil, _
  | HPrim.OptionNone, _ -> fail ()

  | HPrim.NativeFun, _ -> failwith "NEVER: HPrim.NativeFun is resolved in Typing."

let private mirifyExprInfCallClosure ctx callee args resultTy loc =
  let callee, ctx = mirifyExpr ctx callee

  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  let tempRef, tempSerial, ctx = freshVar ctx "app" resultTy loc

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MCallClosureInit(callee, args), resultTy, loc))

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
         let tempVarExpr, tempVarSerial, ctx = freshVar ctx "arg" ty loc

         let arg, ctx = mirifyExpr ctx arg

         let ctx =
           addStmt ctx (MLetValStmt(tempVarSerial, MExprInit arg, ty, loc))

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

      | _ -> failwithf "NEVER: Arity mismatch. %A" loc

    go ctx argSerials tempExprs

  let ctx =
    addTerminator ctx (MGotoTerminator label) loc

  MDefaultExpr(ty, loc), ctx

let private mirifyExprInfClosure ctx funSerial env funTy loc =
  let envTy, envLoc = exprExtract env
  let env, ctx = mirifyExpr ctx env
  let _, envSerial, ctx = freshVar ctx "env" envTy envLoc

  let ctx =
    addStmt ctx (MLetValStmt(envSerial, MExprInit env, envTy, envLoc))

  let tempRef, tempSerial, ctx = freshVar ctx "fun" funTy loc

  let ctx =
    addStmt ctx (MLetValStmt(tempSerial, MClosureInit(funSerial, envSerial), funTy, loc))

  tempRef, ctx

let private mirifyExprInfCallNative ctx (funName: string) args ty loc =
  let args, ctx =
    (args, ctx)
    |> stMap (fun (arg, ctx) -> mirifyExpr ctx arg)

  // No result if result type is unit.
  if ty |> tyIsUnit then
    let ctx =
      addStmt ctx (MActionStmt(MCallNativeAction funName, args, loc))

    MDefaultExpr(tyUnit, loc), ctx
  else
    let temp, tempSerial, ctx =
      freshVar ctx (funName + "_result") ty loc

    let ctx =
      addStmt ctx (MLetValStmt(tempSerial, MPrimInit(MCallNativePrim funName, args), ty, loc))

    temp, ctx

let private mirifyExprInf ctx itself infOp args ty loc =
  match infOp, args, ty with
  | InfOp.Tuple, [], AppTy (TupleTyCtor, []) -> MDefaultExpr(tyUnit, loc), ctx
  | InfOp.Tuple, _, AppTy (TupleTyCtor, itemTys) -> mirifyExprTuple ctx args itemTys loc
  | InfOp.Record, _, _ -> mirifyExprRecord ctx args ty loc
  | InfOp.RecordItem index, [ record ], itemTy -> mirifyExprRecordItem ctx index record itemTy loc
  | InfOp.Semi, _, _ -> mirifyExprSemi ctx args

  | InfOp.Index, [ l; r ], _ -> mirifyCallStrIndexExpr ctx l r ty loc
  | InfOp.Slice, _, _ -> mirifyCallStrGetSliceExpr ctx args loc

  | InfOp.CallProc, [ HVariantExpr (variantSerial, _, _); arg ], _ -> mirifyCallVariantExpr ctx variantSerial arg ty loc
  | InfOp.CallProc, HPrimExpr (prim, _, _) :: args, _ -> mirifyCallPrimExpr ctx itself prim args ty loc
  | InfOp.CallProc, callee :: args, _ -> mirifyCallProcExpr ctx callee args ty loc

  | InfOp.CallTailRec, callee :: args, _ -> mirifyExprInfCallTailRec ctx callee args ty loc
  | InfOp.CallClosure, callee :: args, _ -> mirifyExprInfCallClosure ctx callee args ty loc
  | InfOp.CallNative funName, args, _ -> mirifyExprInfCallNative ctx funName args ty loc
  | InfOp.Closure, [ HFunExpr (funSerial, _, _); env ], _ -> mirifyExprInfClosure ctx funSerial env ty loc
  | t -> failwithf "Never: %A" t

let private mirifyExprLetVal ctx pat init next letLoc =
  let init, ctx = mirifyExpr ctx init
  let exhaustive, ctx = mirifyPat ctx "_never_" pat init

  let ctx =
    if exhaustive
    then ctx
    else addError ctx "Let pattern must be exhaustive for now" letLoc

  let next, ctx = mirifyExpr ctx next
  next, ctx

let private mirifyExprLetFun (ctx: MirCtx) calleeSerial isMainFun argPats body next letLoc =
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
    match argPat with
    | HRefPat (serial, ty, loc) ->
        // NOTE: Optimize for usual cases to not generate redundant local vars.
        (serial, ty, loc), ctx
    | _ ->
        let argTy, argLoc = patExtract argPat
        let arg, argSerial, ctx = freshVar ctx "arg" argTy argLoc
        let exhaustive, ctx = mirifyPat ctx "_never_" argPat arg

        let ctx =
          if exhaustive
          then ctx
          else addError ctx "Argument pattern must be exhaustive for now" argLoc

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
    let bodyCtx = startBlock ctx
    let args, resultTy, body, bodyCtx = mirifyFunBody bodyCtx argPats body
    let ctx = rollback ctx bodyCtx

    let ctx =
      addDecl ctx (MProcDecl(calleeSerial, isMainFun, args, body, resultTy, letLoc))

    ctx

  let ctx = core ()
  let next, ctx = mirifyExpr ctx next
  next, ctx

let private mirifyExpr (ctx: MirCtx) (expr: HExpr): MExpr * MirCtx =
  match expr with
  | HLitExpr (lit, loc) -> MLitExpr(lit, loc), ctx
  | HRefExpr (serial, ty, loc) -> MRefExpr(serial, ty, loc), ctx
  | HFunExpr (serial, ty, loc) -> MProcExpr(serial, ty, loc), ctx

  | HVariantExpr (serial, ty, loc) -> mirifyExprVariant ctx expr serial ty loc
  | HPrimExpr (prim, ty, loc) -> mirifyExprPrim ctx prim ty loc
  | HMatchExpr (cond, arms, ty, loc) -> mirifyExprMatch ctx cond arms ty loc
  | HInfExpr (infOp, args, ty, loc) -> mirifyExprInf ctx expr infOp args ty loc

  | HLetValExpr (_vis, pat, body, next, _, loc) -> mirifyExprLetVal ctx pat body next loc
  | HLetFunExpr (serial, _vis, isMainFun, args, body, next, _, loc) ->
      mirifyExprLetFun ctx serial isMainFun args body next loc

  | HTyDeclExpr _
  | HOpenExpr _ -> MDefaultExpr(tyUnit, exprToLoc expr), ctx

  | HNavExpr _ -> failwith "NEVER: HNavExpr is resolved in NameRes, Typing, or RecordRes"
  | HRecordExpr _ -> failwith "NEVER: HRecordExpr is resolved in RecordRes"
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let private mirifyExprs ctx exprs =
  let rec go acc ctx exprs =
    match exprs with
    | [] -> List.rev acc, ctx

    | expr :: exprs ->
        let expr, ctx = mirifyExpr ctx expr
        go (expr :: acc) ctx exprs

  go [] ctx exprs

let mirify (expr: HExpr, tyCtx: TyCtx): MDecl list * MirCtx =
  let ctx = ofTyCtx tyCtx

  // OK: It's safe to discard the expression thanks to main hoisting.
  let _expr, ctx = mirifyExpr ctx expr

  takeDecls ctx
