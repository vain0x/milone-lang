/// # KirGen
///
/// Generate continuation passing style (CPS) intermediate representation, KIR
/// from HIR.
///
/// This is not only a data transformation but also:
///
/// - resolve pattern matching
/// - resolve operator overloading

module rec MiloneLang.KirGen

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Typing

let private unreachable value = failwithf "NEVER: %A" value

let private kTermToTy (term: KTerm): Ty =
  match term with
  | KLitTerm (lit, _) -> litToTy lit

  | KVarTerm (_, ty, _)
  | KFunTerm (_, ty, _)
  | KVariantTerm (_, ty, _) -> ty

  | KTagTerm _ -> tyInt

  | KLabelTerm (_, ty, _) -> ty

  | KNilTerm (itemTy, _)
  | KNoneTerm (itemTy, _) -> tyList itemTy

  | KUnitTerm _ -> tyUnit

// -----------------------------------------------
// Pattern matching resolution
// -----------------------------------------------

// From:
//
// ```
//   h(match cond with
//     | p1 when g1 -> b1
//     ...
//     | pN when gN -> bN)
// ```
//
// To:
//
// ```
//   let c = cond
//   let a1 () =
//       if pattern-match(c, p1)
//       then (if g1 then g b1 else a2 ())
//       else a2 ()
//   ...
//   and aN () =
//       ...
//       else abort () // exhaust
//   and f t = h t
//   in a1 ()
// ```

[<NoEquality; NoComparison>]
type private PTerm =
  | PLitTerm of Lit * Loc
  | PTagTerm of VariantSerial * Loc
  | PNilTerm of itemTy: Ty * Loc
  | PNoneTerm of itemTy: Ty * Loc

[<NoEquality; NoComparison>]
type private PNode =
  /// Success of pattern matching, discard the current value.
  | PDiscardNode

  /// Set the current value to a var and continue.
  | PLetNode of VarSerial * cont: PNode * Loc

  /// Select a content of the value and continue.
  | PSelectNode of KPath * cont: PNode * Loc

  /// Check if the value equals to expected. Continue if equal or reject otherwise.
  | PEqualNode of expected: PTerm * cont: PNode * Loc
  | PNotEqualNode of unexpected: PTerm * cont: PNode * Loc

  /// Use the value for multiple nodes.
  | PConjNode of PNode list * Loc

let private kgRefPat _itself varSerial _ty loc _ctx = PLetNode(varSerial, PDiscardNode, loc)

let private kgVariantPat _itself variantSerial _ty loc _ctx =
  PSelectNode(KTagPath loc, PEqualNode(PTagTerm(variantSerial, loc), PDiscardNode, loc), loc)

let private kgTuplePat itemPats loc ctx =
  let conts =
    itemPats
    |> List.mapi (fun i itemPat -> PSelectNode(KFieldPath(i, loc), kgPat itemPat ctx, loc))

  PConjNode(conts, loc)

// decomposition of variant
let private kgCallPat itself callee args _ty loc ctx =
  match callee with
  | HVariantPat (variantSerial, _, _) ->
      match args with
      | [ payloadPat ] ->
          PConjNode
            ([ PSelectNode(KTagPath loc, PEqualNode(PTagTerm(variantSerial, loc), PDiscardNode, loc), loc)
               PSelectNode(KPayloadPath(variantSerial, loc), kgPat payloadPat ctx, loc) ],
             loc)

      | _ -> failwithf "NEVER: illegal call pat. %A" itself

  | HSomePat (itemTy, _) ->
      match args with
      | [ itemPat ] ->
          PConjNode
            ([ PEqualNode(PNoneTerm(itemTy, loc), PDiscardNode, loc)
               PSelectNode(KHeadPath(loc), kgPat itemPat ctx, loc) ],
             loc)

      | _ -> failwithf "NEVER: bad arity. %A" itself

  | _ -> failwithf "NEVER: illegal call pat. %A" itself

let private kgConsPat l r itemTy loc ctx =
  PNotEqualNode
    (PNilTerm(itemTy, loc),
     PConjNode
       ([ PSelectNode(KHeadPath(loc), kgPat l ctx, loc)
          PSelectNode(KTailPath(loc), kgPat r ctx, loc) ],
        loc),
     loc)

let private kgAsPat bodyPat varSerial loc ctx =
  PLetNode(varSerial, kgPat bodyPat ctx, loc)

let private kgPat (pat: HPat) (ctx: KirGenCtx): PNode =
  match pat with
  | HDiscardPat _ -> PDiscardNode

  | HLitPat (lit, loc) -> PEqualNode(PLitTerm(lit, loc), PDiscardNode, loc)

  | HNilPat (itemTy, loc) -> PEqualNode(PNilTerm(itemTy, loc), PDiscardNode, loc)

  | HNonePat (itemTy, loc) -> PEqualNode(PNoneTerm(itemTy, loc), PDiscardNode, loc)

  | HRefPat (varSerial, ty, loc) -> kgRefPat pat varSerial ty loc ctx

  | HVariantPat (variantSerial, ty, loc) -> kgVariantPat pat variantSerial ty loc ctx

  | HCallPat (callee, args, ty, loc) -> kgCallPat pat callee args ty loc ctx

  | HConsPat (l, r, itemTy, loc) -> kgConsPat l r itemTy loc ctx

  | HTuplePat (itemPats, _, loc) -> kgTuplePat itemPats loc ctx

  | HBoxPat _ -> failwithf "unimplemented. %A" pat

  | HAsPat (bodyPat, varSerial, loc) -> kgAsPat bodyPat varSerial loc ctx

  | HSomePat _ -> failwithf "TODO: match of fun type should be type error. %A" pat
  | HOrPat _ -> failwithf "TODO: implement nested OR pattern. %A" pat
  | HNavPat _ -> failwithf "NEVER: Nav pattern is resolved in type inference. %A" pat
  | HAnnoPat _ -> failwithf "NEVER: Anno pattern is resolved in type inference. %A" pat

// -----------------------------------------------
// KirGenCtx
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type KirGenCtx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>
    Logs: (Log * Loc) list
    MainFunSerial: FunSerial option
    Joints: KJointBinding list
    FunBindings: KFunBinding list }

let private ctxOfTyCtx (tyCtx: TyCtx): KirGenCtx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    Logs = tyCtx.Logs
    MainFunSerial = None
    Joints = []
    FunBindings = [] }

let private ctxUpdateTyCtx (tyCtx: TyCtx) (ctx: KirGenCtx) =
  { tyCtx with
      Serial = ctx.Serial
      Vars = ctx.Vars }

let private freshSerial (ctx: KirGenCtx): Serial * KirGenCtx =
  let serial = ctx.Serial + 1
  let ctx = { ctx with Serial = serial }
  serial, ctx

let private freshFunSerial (ctx: KirGenCtx): FunSerial * KirGenCtx =
  let serial, ctx = freshSerial ctx
  FunSerial serial, ctx

let private newVar hint ty loc (ctx: KirGenCtx) =
  let varSerial, ctx = ctx |> freshSerial

  let ctx =
    { ctx with
        Vars =
          ctx.Vars
          |> mapAdd varSerial (VarDef(hint, AutoSM, ty, loc)) }

  varSerial, ctx

let private addFunDef funSerial funDef (ctx: KirGenCtx) =
  { ctx with
      Funs = ctx.Funs |> mapAdd funSerial funDef }

let private addJointBinding jointBinding (ctx: KirGenCtx) =
  { ctx with
      Joints = jointBinding :: ctx.Joints }

let private addFunBinding funBinding (ctx: KirGenCtx) =
  { ctx with
      FunBindings = funBinding :: ctx.FunBindings }

let private findVarDef varSerial (ctx: KirGenCtx) = ctx.Vars |> mapFind varSerial

let private findVariant variantSerial (ctx: KirGenCtx) = ctx.Variants |> mapFind variantSerial

let private findVarTy varSerial (ctx: KirGenCtx) =
  match ctx.Vars |> mapFind varSerial with
  | VarDef (_, _, ty, _) -> ty

let private selectTy ty path ctx =
  match path with
  | KSelfPath
  | KTailPath _ -> ty

  | KHeadPath _ ->
      match ty with
      | AppTy (ListTyCtor, [ itemTy ]) -> itemTy
      | _ -> unreachable (ty, path)

  | KFieldPath (i, _) ->
      match ty with
      | AppTy (TupleTyCtor, itemTys) -> itemTys |> List.item i
      | _ -> unreachable (ty, path)

  | KTagPath _ -> tyInt

  | KPayloadPath (variantSerial, _) ->
      let variantDef = findVariant variantSerial ctx
      variantDef.PayloadTy

let private collectJoints (f: KirGenCtx -> _ * KirGenCtx) (ctx: KirGenCtx) =
  let parentJoints = ctx.Joints
  let ctx = { ctx with Joints = [] }
  let result, ctx = f ctx
  let joints = ctx.Joints |> List.rev
  let ctx = { ctx with Joints = parentJoints }
  result, joints, ctx

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

let private kTrueTerm loc = KLitTerm(BoolLit true, loc)

let private abortNode loc =
  let code = KLitTerm(IntLit 1, loc)
  KPrimNode(KExitPrim, [ code ], [], [], loc)

/// Converts to basic 2-arity prim node.
let private basicPrimNode2 hint prim l r ty loc hole ctx =
  ctx
  |> kgExpr l (fun l ctx ->
       ctx
       |> kgExpr r (fun r ctx ->
            let result, ctx = ctx |> newVar hint ty loc
            let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
            KPrimNode(prim, [ l; r ], [ result ], [ cont ], loc), ctx))

// -----------------------------------------------
// Non-prim basic expr
// -----------------------------------------------

let private kgRefExpr varSerial ty loc hole ctx =
  ctx |> hole (KVarTerm(varSerial, ty, loc))

let private kgFunExpr funSerial ty loc hole ctx =
  ctx |> hole (KFunTerm(funSerial, ty, loc))

let private kgVariantExpr variantSerial ty loc hole ctx =
  ctx |> hole (KVariantTerm(variantSerial, ty, loc))

let private kgSemiExpr itself args hole ctx =
  let rec go args hole ctx =
    match args with
    | [ last ] -> kgExpr last hole ctx

    | arg :: args ->
        // Generate arg and the result is discarded.
        kgExpr arg (fun _ ctx -> go args hole ctx) ctx

    | [] -> failwithf "NEVER: Semi expr can't be empty. %A" itself

  go args hole ctx

let private kgCallFunExpr funSerial funTy funLoc args ty loc hole ctx =
  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar "call" ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(KCallProcPrim, KFunTerm(funSerial, funTy, funLoc) :: args, [ result ], [ cont ], loc), ctx)

/// Converts an expr calling to variant, i.e., construction of a variant with payload.
let private kgCallVariantExpr variantSerial variantTy variantLoc args ty loc hole ctx =
  let variantName = (ctx |> findVariant variantSerial).Name

  let variantTerm =
    KVariantTerm(variantSerial, variantTy, variantLoc)

  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar variantName ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(KVariantPrim, variantTerm :: args, [ result ], [ cont ], loc), ctx)

let private kgCallClosureExpr callee args ty loc hole ctx =
  ctx
  |> kgExpr callee (fun callee ctx ->
       ctx
       |> kgExprList args (fun args ctx ->
            let result, ctx = ctx |> newVar "call" ty loc
            let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
            KPrimNode(KCallClosurePrim, callee :: args, [ result ], [ cont ], loc), ctx))

let private kgTupleExpr args ty loc hole ctx =
  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar "tuple" ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(KTuplePrim, args, [ result ], [ cont ], loc), ctx)

let private kgClosureExpr funSerial funTy funLoc env ty loc hole ctx =
  ctx
  |> kgExpr env (fun env ctx ->
       let funTerm = KFunTerm(funSerial, funTy, funLoc)
       let result, ctx = ctx |> newVar "closure" ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(KClosurePrim, [ funTerm; env ], [ result ], [ cont ], loc), ctx)

// -----------------------------------------------
// Prims
// -----------------------------------------------

// Handling prims individually, which tends to code verbose yet easy to maintain.

// prim expr, not appear as callee
let private kgPrimExpr expr prim ty loc hole ctx: KNode * KirGenCtx =
  match prim with
  | HPrim.Nil ->
      let itemTy =
        match ty with
        | AppTy (ListTyCtor, [ itemTy ]) -> itemTy
        | _ -> failwithf "NEVER: []'s type must be a list. %A" expr

      hole (KNilTerm(itemTy, loc)) ctx

  | HPrim.OptionNone ->
      let itemTy =
        match ty with
        | AppTy (ListTyCtor, [ itemTy ]) -> itemTy
        | _ -> failwithf "NEVER: None's type must be a list. %A" expr

      hole (KNoneTerm(itemTy, loc)) ctx

  | _ -> failwithf "NEVER: Prim must appear in form of call(prim, args...). %A" expr

let private kgCallAddExpr itself _primTy args ty loc hole ctx =
  match args with
  | [ l; r ] ->
      match ty with
      | AppTy ((IntTyCtor
               | UIntTyCtor
               | CharTyCtor),
               _) -> basicPrimNode2 "add" KAddPrim l r ty loc hole ctx

      | AppTy (StrTyCtor, _) -> basicPrimNode2 "add" KStrAddPrim l r ty loc hole ctx

      | _ -> failwithf "NEVER: bad type %A" itself

  | _ -> unreachable itself

/// Converts call to exit. Since exit doesn't return, hole is discarded.
let private kgCallExitExpr itself args primLoc ctx =
  match args with
  | [ arg ] ->
      ctx
      |> kgExpr arg (fun arg ctx -> KPrimNode(KExitPrim, [ arg ], [], [], primLoc), ctx)

  | _ -> unreachable itself

let private kgCallComparisonPrimExpr itself hint prim args ty primLoc hole ctx =
  match args with
  | [ l; r ] ->
      ctx
      |> kgExpr l (fun l ctx ->
           ctx
           |> kgExpr r (fun r ctx ->
                // Create a joint.
                let jointSerial, jointBinding, ctx =
                  let jointSerial, ctx = ctx |> freshFunSerial

                  let ctx =
                    let funDef: FunDef =
                      { Name = hint
                        Arity = 1
                        Ty = TyScheme([], tyFun tyBool tyUnit)
                        Loc = primLoc }

                    ctx |> addFunDef jointSerial funDef

                  let cond, ctx = ctx |> newVar hint tyBool primLoc

                  let cont, ctx =
                    hole (KVarTerm(cond, tyBool, primLoc)) ctx

                  let binding =
                    KJointBinding(jointSerial, [ cond ], cont, primLoc)

                  jointSerial, binding, ctx

                let jumpToJoint cond =
                  KJumpNode(jointSerial, [ KLitTerm(BoolLit cond, primLoc) ], primLoc)

                KJointNode
                  ([ jointBinding ],
                   KPrimNode(prim, [ l; r ], [], [ jumpToJoint true; jumpToJoint false ], primLoc),
                   primLoc),
                ctx))

  | _ -> unreachable itself

/// Converts call to regular (not special) prim.
let private kgCallRegularPrimExpr hint prim args ty loc hole ctx =
  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar hint ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(prim, args, [ result ], [ cont ], loc), ctx)

// -----------------------------------------------
// match
// -----------------------------------------------

let private kgEvalPTerm (term: PTerm): KTerm =
  match term with
  | PLitTerm (lit, loc) -> KLitTerm(lit, loc)
  | PTagTerm (variantSerial, loc) -> KTagTerm(variantSerial, loc)
  | PNilTerm (itemTy, loc) -> KNilTerm(itemTy, loc)
  | PNoneTerm (itemTy, loc) -> KNoneTerm(itemTy, loc)

let private kgEvalPNode (term: KTerm) (node: PNode) successNode failureNode ctx: KNode * KirGenCtx =
  match node with
  | PDiscardNode -> successNode, ctx

  | PLetNode (varSerial, cont, loc) ->
      let ty = findVarTy varSerial ctx

      let cont, ctx =
        ctx
        |> kgEvalPNode (KVarTerm(varSerial, ty, loc)) cont successNode failureNode

      KSelectNode(term, KSelfPath, varSerial, cont, loc), ctx

  | PSelectNode (path, cont, loc) ->
      let ty = selectTy (kTermToTy term) path ctx
      let varSerial, ctx = newVar "t" ty loc ctx
      let varTerm = KVarTerm(varSerial, ty, loc)

      let cont, ctx =
        kgEvalPNode varTerm cont successNode failureNode ctx

      KSelectNode(term, path, varSerial, cont, loc), ctx

  | PEqualNode (expected, cont, loc) ->
      let expected = kgEvalPTerm expected

      let thenCl, ctx =
        ctx
        |> kgEvalPNode term cont successNode failureNode

      KPrimNode(KEqualPrim, [ term; expected ], [], [ thenCl; failureNode ], loc), ctx

  | PNotEqualNode (unexpected, cont, loc) ->
      let unexpected = kgEvalPTerm unexpected

      let elseCl, ctx =
        ctx
        |> kgEvalPNode term cont successNode failureNode

      KPrimNode(KEqualPrim, [ term; unexpected ], [], [ failureNode; elseCl ], loc), ctx

  | PConjNode (nodes, loc) ->
      let ty = kTermToTy term
      let varSerial, ctx = newVar "t" ty loc ctx
      let varTerm = KVarTerm(varSerial, ty, loc)

      let rec go nodes ctx =
        match nodes with
        | [] -> successNode, ctx

        | node :: nodes ->
            let cont, ctx = go nodes ctx
            kgEvalPNode varTerm node cont failureNode ctx

      let cont, ctx = go nodes ctx

      KSelectNode(term, KSelfPath, varSerial, cont, loc), ctx

// `match cond with (| pat when guard -> body)*`
let private kgMatchExpr cond arms targetTy loc hole ctx: KNode * KirGenCtx =
  // Fun to call to leave the match expr.
  let targetFunSerial, ctx = freshFunSerial ctx

  let leaveMatch target =
    KJumpNode(targetFunSerial, [ target ], loc)

  // Creates a joint for each arm to perform pattern-matching on it
  // and returns a node to evaluate the sub-match that consists of these arms.
  let rec go acc cond arms ctx: KJointBinding list * KNode * KirGenCtx =
    match arms with
    | [] ->
        // Non-exhaustive error.
        acc, abortNode loc, ctx

    | (HDiscardPat _, guard, body) :: _ when hxIsAlwaysTrue guard ->
        let cont, ctx =
          ctx
          |> kgExpr body (fun body ctx -> leaveMatch body, ctx)

        acc, cont, ctx

    | (pat, guard, body) :: arms ->
        let loc = patToLoc pat
        let acc, rest, ctx = go acc cond arms ctx

        let jointSerial, ctx = ctx |> freshFunSerial

        let jointDef: FunDef =
          let armFunTy = tyFun tyUnit tyUnit
          { Name = "arm"
            Arity = 1
            Ty = TyScheme([], armFunTy)
            Loc = loc }

        // Compute pattern-matching.
        let body, ctx =
          let successNode, ctx =
            if hxIsAlwaysTrue guard then
              ctx
              |> kgExpr body (fun body ctx -> leaveMatch body, ctx)
            else
              ctx
              |> kgExpr guard (fun guard ctx ->
                   let body, ctx =
                     ctx
                     |> kgExpr body (fun body ctx -> leaveMatch body, ctx)

                   KPrimNode(KEqualPrim, [ guard; kTrueTerm loc ], [], [ body; rest ], loc), ctx)

          let rec go pats ctx =
            match pats with
            | [] -> rest, ctx

            | pat :: pats ->
                let rest, ctx = go pats ctx
                kgEvalPNode cond (kgPat pat ctx) successNode rest ctx

          go (patNormalize pat |> List.rev) ctx

        let binding =
          KJointBinding(jointSerial, [], body, loc)

        let ctx = ctx |> addFunDef jointSerial jointDef

        binding :: acc, KJumpNode(jointSerial, [], loc), ctx

  let createArmJoints ctx =
    ctx
    |> kgExpr cond (fun cond ctx ->
         let joints, cont, ctx = go [] cond arms ctx

         let ctx =
           { ctx with
               Joints = List.append (List.rev joints) ctx.Joints }

         cont, ctx)

  // Create a joint to be called after the match expr.
  let createTargetJoint ctx =
    let targetVarSerial, ctx = newVar "match_target" targetTy loc ctx

    let funDef: FunDef =
      { Name = "match_next"
        Arity = 1
        Ty = TyScheme([], tyFun targetTy tyUnit)
        Loc = loc }

    let binding, ctx =
      let targetTerm = KVarTerm(targetVarSerial, targetTy, loc)
      let body, ctx = hole targetTerm ctx
      KJointBinding(targetFunSerial, [ targetVarSerial ], body, loc), ctx

    ctx
    |> addFunDef targetFunSerial funDef
    |> addJointBinding binding

  let entryPoint, joints, ctx =
    ctx
    |> collectJoints (fun ctx ->
         let entryPoint, ctx = createArmJoints ctx
         let ctx = createTargetJoint ctx
         entryPoint, ctx)

  KJointNode(joints, entryPoint, loc), ctx

// -----------------------------------------------
// let-val, let-fun
// -----------------------------------------------

let private kgLetValExpr pat init next loc hole ctx: KNode * KirGenCtx =
  match pat with
  | HDiscardPat _ ->
      ctx
      |> kgExpr init (fun _ ctx -> ctx |> kgExpr next hole)

  | HRefPat (varSerial, _, loc) ->
      ctx
      |> kgExpr init (fun init ctx ->
           let cont, ctx = ctx |> kgExpr next hole
           KSelectNode(init, KSelfPath, varSerial, cont, loc), ctx)

  | _ ->
      ctx
      |> kgExpr init (fun init ctx ->
           let success, ctx = ctx |> kgExpr next hole
           let failure = abortNode loc
           kgEvalPNode init (kgPat pat ctx) success failure ctx)

let private kgLetFunExpr funSerial isMainFun argPats body next loc hole (ctx: KirGenCtx): KNode * KirGenCtx =
  let failure = abortNode loc

  // Remember main fun.
  let ctx =
    if isMainFun then
      { ctx with
          MainFunSerial = Some funSerial }
    else
      ctx

  // Process arg pats and body.
  let (argVars, body), joints, ctx =
    let rec go argPats hole ctx =
      match argPats with
      | [] -> [], hole, ctx

      | HRefPat (varSerial, _, _) :: argPats ->
          // Skip pattern-matching in this usual case.
          let argVars, hole, ctx = ctx |> go argPats hole
          (varSerial :: argVars), hole, ctx

      | argPat :: argPats ->
          // Create a var as parameter.
          let varSerial, argTerm, ctx =
            let argTy, argLoc = patExtract argPat
            let varSerial, ctx = ctx |> newVar "arg" argTy argLoc
            let argTerm = KVarTerm(varSerial, argTy, argLoc)
            varSerial, argTerm, ctx

          let argVars, hole, ctx = ctx |> go argPats hole

          let argVars = varSerial :: argVars

          // Prepend pattern-matching to the hole.
          let hole ctx =
            let cont, ctx = hole ctx
            ctx
            |> kgEvalPNode argTerm (kgPat argPat ctx) cont failure

          argVars, hole, ctx

    let bodyHole ctx =
      let returnNode result = KReturnNode(funSerial, [ result ], loc)

      ctx
      |> kgExpr body (fun body ctx -> returnNode body, ctx)

    ctx
    |> collectJoints (fun ctx ->
         let argVars, hole, ctx = ctx |> go argPats bodyHole
         let body, ctx = hole ctx
         (argVars, body), ctx)

  let ctx =
    let joints =
      KJointBinding(funSerial, [], body, loc)
      :: List.rev joints

    let body =
      KJointNode(joints, KJumpNode(funSerial, [], loc), loc)

    ctx
    |> addFunBinding (KFunBinding(funSerial, argVars, body, loc))

  ctx |> kgExpr next hole

// -----------------------------------------------
// kgExpr
// -----------------------------------------------

// Controller of the pass.
// Decompose an HIR expr and dispatch to one of funs to generate KIR node, defined above.

let private kgInfExpr itself infOp args ty loc hole ctx: KNode * KirGenCtx =
  match infOp with
  | InfOp.Semi -> kgSemiExpr itself args hole ctx

  | InfOp.CallProc ->
      let callee, args =
        match args with
        | callee :: args -> callee, args
        | [] -> failwithf "NEVER: CallProc args must begin with callee. %A" itself

      match callee with
      | HPrimExpr (prim, primTy, primLoc) ->
          let comparison hint prim =
            kgCallComparisonPrimExpr itself hint prim args ty primLoc hole ctx

          let regular hint prim =
            kgCallRegularPrimExpr hint prim args ty primLoc hole ctx

          match prim with
          | HPrim.Add -> kgCallAddExpr itself primTy args ty primLoc hole ctx
          | HPrim.Sub -> regular "sub" KSubPrim
          | HPrim.Mul -> regular "mul" KMulPrim
          | HPrim.Div -> regular "div" KDivPrim
          | HPrim.Mod -> regular "mod" KModPrim
          | HPrim.Eq -> comparison "equal" KEqualPrim
          | HPrim.Lt -> comparison "less" KLessPrim
          | HPrim.Nil -> unreachable itself
          | HPrim.Cons -> regular "cons" KConsPrim
          | HPrim.OptionNone -> unreachable itself
          | HPrim.OptionSome -> regular "some" KSomePrim
          | HPrim.Index -> regular "index" KStrIndexPrim
          | HPrim.Not -> regular "not" KNotPrim
          | HPrim.Exit -> kgCallExitExpr itself args primLoc ctx
          | HPrim.Assert -> regular "assert" KAssertPrim
          | HPrim.Box -> regular "box" KBoxPrim
          | HPrim.Unbox -> regular "unbox" KUnboxPrim
          | HPrim.Printfn -> regular "printfn" KPrintfnPrim
          | HPrim.StrLength -> regular "str_length" KStrLengthPrim
          | HPrim.StrGetSlice -> regular "str_get_slice" KStrGetSlicePrim
          | HPrim.Char -> regular "char" KCharPrim
          | HPrim.Int -> regular "int" KIntPrim
          | HPrim.UInt -> regular "uint" KUIntPrim
          | HPrim.String -> regular "string" KStringPrim
          | HPrim.InRegion -> regular "in_region" KInRegionPrim
          | HPrim.NativeFun (name, arity) -> regular name (KNativeFunPrim(name, arity))

      | HFunExpr (funSerial, funTy, funLoc) -> kgCallFunExpr funSerial funTy funLoc args ty loc hole ctx

      | HVariantExpr (variantSerial, variantTy, variantLoc) ->
          kgCallVariantExpr variantSerial variantTy variantLoc args ty loc hole ctx

      | _ -> failwithf "NEVER: CallClosure should be used. %A" itself

  | InfOp.CallClosure ->
      match args with
      | callee :: args -> kgCallClosureExpr callee args ty loc hole ctx
      | [] -> failwithf "NEVER: CallClosure args must begin with callee. %A" itself

  | InfOp.CallTailRec -> failwith "unimplemented"

  | InfOp.Tuple -> kgTupleExpr args ty loc hole ctx

  | InfOp.TupleItem _ -> failwithf "unimplemented. %A" itself

  | InfOp.Closure ->
      match args with
      | [ HFunExpr (funSerial, funTy, funLoc); env ] -> kgClosureExpr funSerial funTy funLoc env ty loc hole ctx

      | _ -> failwithf "NEVER: bad use of Closure prim. %A" itself

  | InfOp.App -> failwithf "NEVER: InfOp.App is resolved in uneta. %A" itself
  | InfOp.Anno -> failwithf "NEVER: InfOp.Anno is resolved in type inference: %A" itself

/// Evaluates an expression and fills a hole with the result term.
let private kgExpr (expr: HExpr) (hole: KTerm -> KirGenCtx -> KNode * KirGenCtx) (ctx: KirGenCtx): KNode * KirGenCtx =
  match expr with
  | HLitExpr (lit, loc) -> hole (KLitTerm(lit, loc)) ctx

  | HRefExpr (varSerial, ty, loc) -> kgRefExpr varSerial ty loc hole ctx

  | HFunExpr (varSerial, ty, loc) -> kgFunExpr varSerial ty loc hole ctx

  | HVariantExpr (variantSerial, ty, loc) -> kgVariantExpr variantSerial ty loc hole ctx

  | HPrimExpr (prim, ty, loc) -> kgPrimExpr expr prim ty loc hole ctx

  | HRecordExpr _ -> failwithf "unimplemented. %A" expr

  | HMatchExpr (cond, arms, ty, loc) -> kgMatchExpr cond arms ty loc hole ctx

  | HInfExpr (infOp, args, ty, loc) -> kgInfExpr expr infOp args ty loc hole ctx

  | HLetValExpr (_vis, pat, init, next, _, loc) -> kgLetValExpr pat init next loc hole ctx

  | HLetFunExpr (funSerial, _vis, isMainFun, args, body, next, _, loc) ->
      kgLetFunExpr funSerial isMainFun args body next loc hole ctx

  | HTyDeclExpr _
  | HOpenExpr _ ->
      let justUnit () =
        let loc = exprToLoc expr
        hole (KUnitTerm loc) ctx

      justUnit ()

  | HErrorExpr (msg, loc) ->
      let raiseError () =
        failwithf "HErrorExpr in KirGen: %s" (msg + " " + locToString loc)

      raiseError ()

  | HNavExpr _ -> failwithf "NEVER: nav is resolved in type inference. %A" expr
  | HModuleExpr _ -> failwithf "NEVER: module is resolved in name res. %A" expr

/// Converts a list of expressions sequentially
/// and fills a hole with the list of their results.
let private kgExprList args hole ctx =
  match args with
  | [] -> hole [] ctx

  | arg :: args ->
      ctx
      |> kgExpr arg (fun arg ctx ->
           ctx
           |> kgExprList args (fun args ctx -> hole (arg :: args) ctx))

let kirGen (expr: HExpr, tyCtx: TyCtx): KRoot * KirGenCtx =
  let _, ctx =
    ctxOfTyCtx tyCtx
    |> kgExpr expr (fun _ ctx -> abortNode noLoc, ctx)

  let funBindings = ctx.FunBindings |> List.rev
  KRoot(funBindings), ctx
