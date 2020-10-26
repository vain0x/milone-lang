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
open MiloneLang.Records
open MiloneLang.Helpers

let private unreachable value = failwithf "NEVER: %A" value

let private isNewtypeVariant varSerial ctx =
  match ctx |> mirCtxGetVars |> mapFind varSerial with
  | VariantDef (_, tySerial, _, _, _, _) ->
      match ctx |> mirCtxGetTys |> mapFind tySerial with
      | UnionTyDef (_, variantSerials, _) -> variantSerials |> listLength = 1

      | _ -> failwith "Expected union serial"

  | _ -> failwith "Expected variant serial"

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

type private pmx = kgx

type private PTerm =
  | PLitTerm of Lit * Loc
  | PTagTerm of VariantSerial * Ty * Loc
  | PNilTerm of itemTy: Ty * Loc
  | PNoneTerm of itemTy: Ty * Loc

type private PNode =
  | PResolveNode of Loc
  | PEqualNode of PTerm * cont: PNode * Loc
  | PLetNode of VarSerial * Ty * cont: PNode * Loc

let private kgRefPat pat varSerial ty loc hole ctx =
  match findVarDef varSerial ctx with
  | VarDef _ -> PLetNode(varSerial, ty, hole (), loc)

  | VariantDef _ -> PEqualNode(PTagTerm(varSerial, ty, loc), hole (), loc)

  | FunDef _ -> failwithf "NEVER: fun can't appear as pattern. %A" pat

let private kgTuplePat pat itemPats tupleTy loc hole ctx = failwith ""

let private kgCallPat pat callee args ty loc hole ctx =
  match callee with
  | HRefPat (serial, _, _) -> failwith ""

  | HSomePat (itemTy, _) ->
      match args with
      | [ itemPat ] -> failwith ""

      | _ -> failwithf "NEVER: bad arity. %A" pat

  | _ -> failwithf "NEVER: illegal call pat. %A" pat

let private kgPat (pat: HPat) hole ctx: PNode =
  match pat with
  | HDiscardPat _ -> hole ()

  | HLitPat (lit, loc) -> PEqualNode(PLitTerm(lit, loc), hole (), loc)

  | HNilPat (itemTy, loc) -> PEqualNode(PNilTerm(itemTy, loc), hole (), loc)

  | HNonePat (itemTy, loc) -> PEqualNode(PNoneTerm(itemTy, loc), hole (), loc)

  | HRefPat (varSerial, ty, loc) -> kgRefPat pat varSerial ty loc hole ctx

  | HCallPat (callee, args, ty, loc) -> kgCallPat pat callee args ty loc hole ctx

  | HConsPat (l, r, itemTy, loc) -> failwith ""

  | HTuplePat (itemPats, tupleTy, loc) -> kgTuplePat pat itemPats tupleTy loc hole ctx

  | HAsPat (bodyPat, varSerial, loc) -> failwith ""

  | HSomePat _ ->
      // let ctx =
      //   mirCtxAddErr ctx "Some pattern must be used in the form of `Some pat`" loc
      // false, ctx
      failwith "error"

  | HOrPat _ -> failwith "Unimpl nested OR pattern."
  | HNavPat _ -> failwithf "NEVER: Nav pattern is resolved in type inference. %A" pat
  | HAnnoPat _ -> failwithf "NEVER: Anno pattern is resolved in type inference. %A" pat

// -----------------------------------------------
// KirGenCtx
// -----------------------------------------------

type private kgx = KirGenCtx

let private freshSerial (ctx: kgx): Serial * kgx =
  let serial = (ctx |> kirGenCtxGetSerial) + 1
  let ctx = ctx |> kirGenCtxWithSerial serial
  serial, ctx

let private newVar hint ty loc ctx =
  let varSerial, ctx = ctx |> freshSerial

  let ctx =
    let vars =
      ctx
      |> kirGenCtxGetVars
      |> mapAdd varSerial (VarDef(hint, AutoSM, ty, loc))

    ctx |> kirGenCtxWithVars vars

  varSerial, ctx

let private addFun funSerial funDef funBinding ctx =
  let ctx =
    ctx
    |> kirGenCtxWithVars (ctx |> kirGenCtxGetVars |> mapAdd funSerial funDef)

  // TODO: add fun binding
  ctx

let private findVarDef varSerial ctx =
  ctx |> kirGenCtxGetVars |> mapFind varSerial

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

let private kTrueTerm loc = KLitTerm(BoolLit true, loc)

let private abortNode loc ctx =
  let code = KLitTerm(IntLit 1, loc)
  KPrimNode(KExitPrim, [ code ], [], [], loc), ctx

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
  let term =
    match ctx |> findVarDef varSerial with
    | VarDef _ -> KVarTerm(varSerial, ty, loc)
    | FunDef _ -> KFunTerm(varSerial, ty, loc)
    | VariantDef _ -> KVariantTerm(varSerial, ty, loc)

  hole term ctx

let private kgSemiExpr itself args hole ctx =
  let rec go args hole ctx =
    match args with
    | [ last ] -> kgExpr last hole ctx

    | arg :: args ->
        // Generate arg and the result is discarded with `_`. And then continue to loop.
        kgExpr arg (fun _ ctx -> go args hole ctx) ctx

    | [] -> failwithf "NEVER: semi can't be empty %A" itself

  go args hole ctx

let private kgCallFunExpr funSerial funTy funLoc args ty loc hole ctx =
  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar "call" ty loc
       let cont, ctx = hole (KVarTerm(result, ty, loc)) ctx
       KPrimNode(KCallProcPrim, KFunTerm(funSerial, funTy, funLoc) :: args, [ result ], [ cont ], loc), ctx)

/// Converts an expr calling to variant, i.e., construction of a variant with payload.
let private kgCallVariantExpr variantSerial variantTy variantLoc args ty loc hole ctx =
  let variantIdent =
    ctx |> findVarDef variantSerial |> varDefToIdent

  let variantTerm =
    KVariantTerm(variantSerial, variantTy, variantLoc)

  ctx
  |> kgExprList args (fun args ctx ->
       let result, ctx = ctx |> newVar variantIdent ty loc
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
let private kgPrimExpr expr prim ty loc hole ctx: KNode * kgx =
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

let private kgEvalPTerm (term: PTerm) hole ctx: KNode * kgx =
  match term with
  | PLitTerm (lit, loc) -> hole (KLitTerm(lit, loc)) ctx

  | PTagTerm (variantSerial, ty, loc) ->
      let variantTerm = KVariantTerm(variantSerial, ty, loc)
      let result, ctx = ctx |> newVar "tag" tyInt loc
      let cont, ctx = hole (KVarTerm(result, tyInt, loc)) ctx
      KSelectNode(variantTerm, KTagPath loc, result, cont, loc), ctx

  | PNilTerm (itemTy, loc) -> hole (KNilTerm(itemTy, loc)) ctx

  | PNoneTerm (itemTy, loc) -> hole (KNoneTerm(itemTy, loc)) ctx

let private kgEvalPNode (term: KTerm) (node: PNode) successNode failureNode ctx: KNode * kgx =
  match node with
  | PResolveNode _ -> successNode, ctx

  | PEqualNode (expected, cont, loc) ->
      ctx
      |> kgEvalPTerm expected (fun expected ctx ->
           let thenCl, ctx =
             ctx
             |> kgEvalPNode term cont successNode failureNode

           KPrimNode(KEqualPrim, [ term; expected ], [], [ thenCl; failureNode ], loc), ctx)

  | PLetNode (varSerial, ty, cont, loc) ->
      let cont, ctx =
        ctx
        |> kgEvalPNode (KVarTerm(varSerial, ty, loc)) cont successNode failureNode

      KPrimNode(KMovePrim, [ term ], [ varSerial ], [ cont ], loc), ctx

// `match cond with (| pat when guard -> body)*`
let private kgMatchExpr cond arms targetTy loc hole ctx: KNode * kgx =
  // Fun to call to leave the match expr.
  let targetFunSerial, ctx = freshSerial ctx

  let leaveMatch target loc =
    KJumpNode(targetFunSerial, [ target ], loc)

  // Creates a fun for each arm to perform pattern-matching on it
  // and returns a node to evaluate the sub-match that consists of these arms.
  let rec go cond arms ctx: KNode * kgx =
    match arms with
    | [] ->
        // Non-exhaustive error.
        abortNode loc ctx

    | (pat, guard, body) :: arms ->
        let loc = patToLoc pat
        let rest, ctx = go cond arms ctx

        let armFunSerial, ctx = ctx |> freshSerial

        let armFunDef =
          let armFunTy = tyFun tyUnit tyUnit
          FunDef("arm", 1, TyScheme([], armFunTy), loc)

        // Compute pattern-matching.
        let body, ctx =
          let pNode =
            kgPat pat (fun () -> PResolveNode loc) ctx

          let successNode, ctx =
            ctx
            |> kgExpr body (fun body ctx ->
                 ctx
                 |> kgExpr guard (fun guard ctx ->
                      KPrimNode(KEqualPrim, [ guard; kTrueTerm loc ], [], [ leaveMatch body loc; rest ], loc), ctx))

          kgEvalPNode cond pNode successNode rest ctx

        let binding = KFunBinding(armFunSerial, [], body, loc)

        let ctx =
          ctx |> addFun armFunSerial armFunDef binding

        KJumpNode(armFunSerial, [ KUnitTerm loc ], loc), ctx

  let node, ctx =
    ctx
    |> kgExpr cond (fun cond ctx -> go cond arms ctx)

  // Create target fun.
  let ctx =
    let targetVarSerial, ctx = newVar "match_target" targetTy loc ctx

    let body, ctx =
      hole (KVarTerm(targetVarSerial, targetTy, loc)) ctx

    let binding =
      KFunBinding(targetFunSerial, [ targetVarSerial ], body, loc)

    let funDef =
      FunDef("match_next", 1, TyScheme([], tyFun targetTy tyUnit), loc)

    ctx |> addFun targetFunSerial funDef binding

  node, ctx

// -----------------------------------------------
// let-val, let-fun
// -----------------------------------------------

let private kgLetValExpr expr pat init next nextTy loc hole ctx: KNode * kgx = failwith ""

let private kgLetFunExpr expr funSerial isMainFun args body next nextTy loc hole ctx: KNode * kgx = failwith ""

// -----------------------------------------------
// kgExpr
// -----------------------------------------------

// Controller of the pass.
// Decompose an HIR expr and dispatch to one of funs to generate KIR node, defined above.

let private kgInfExpr itself infOp args ty loc hole ctx: KNode * kgx =
  match infOp with
  | InfOp.Semi -> kgSemiExpr itself args hole ctx

  | InfOp.CallProc ->
      let callee, args =
        match args with
        | callee :: args -> callee, args
        | [] -> failwithf "NEVER: CallProc args must begin with callee. %A" itself

      match callee with
      | HPrimExpr (prim, primTy, primLoc) ->
          let regular hint prim =
            kgCallRegularPrimExpr hint prim args ty primLoc hole ctx

          match prim with
          | HPrim.Add -> kgCallAddExpr itself primTy args ty primLoc hole ctx
          | HPrim.Sub -> regular "sub" KSubPrim
          | HPrim.Mul -> regular "mul" KMulPrim
          | HPrim.Div -> regular "div" KDivPrim
          | HPrim.Mod -> regular "mod" KModPrim
          | HPrim.Eq -> regular "equal" KEqualPrim
          | HPrim.Lt -> regular "less" KLessPrim
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
          | HPrim.String -> regular "string" KStringPrim
          | HPrim.InRegion -> regular "in_region" KInRegionPrim
          | HPrim.NativeFun (ident, arity) -> regular ident (KNativeFunPrim(ident, arity))

      | HRefExpr (varSerial, refTy, refLoc) ->
          match ctx |> findVarDef varSerial with
          | VarDef _ -> failwithf "NEVER: CallClosure should be used. %A" itself
          | FunDef _ -> kgCallFunExpr varSerial refTy refLoc args ty loc hole ctx
          | VariantDef _ -> kgCallVariantExpr varSerial refTy refLoc args ty loc hole ctx

      | _ -> failwithf "NEVER: CallClosure should be used. %A" itself

  | InfOp.CallClosure ->
      match args with
      | callee :: args -> kgCallClosureExpr callee args ty loc hole ctx
      | [] -> failwithf "NEVER: CallClosure args must begin with callee. %A" itself

  | InfOp.Tuple -> kgTupleExpr args ty loc hole ctx

  | InfOp.Closure ->
      match args with
      | [ HRefExpr (funSerial, funTy, funLoc); env ] -> kgClosureExpr funSerial funTy funLoc env ty loc hole ctx

      | _ -> failwithf "NEVER: bad use of Closure prim. %A" itself

  | InfOp.App -> failwithf "NEVER: InfOp.App is resolved in uneta. %A" itself
  | InfOp.Anno -> failwithf "NEVER: InfOp.Anno is resolved in type inference: %A" itself

/// Evaluates an expression and fills a hole with the result term.
let private kgExpr (expr: HExpr) (hole: KTerm -> kgx -> KNode * kgx) (ctx: kgx): KNode * kgx =
  match expr with
  | HLitExpr (lit, loc) -> hole (KLitTerm(lit, loc)) ctx

  | HRefExpr (varSerial, ty, loc) -> kgRefExpr varSerial ty loc hole ctx

  | HPrimExpr (prim, ty, loc) -> kgPrimExpr expr prim ty loc hole ctx

  | HMatchExpr (cond, arms, ty, loc) -> kgMatchExpr cond arms ty loc hole ctx

  | HInfExpr (infOp, args, ty, loc) -> kgInfExpr expr infOp args ty loc hole ctx

  | HLetValExpr (_vis, pat, init, next, nextTy, loc) -> kgLetValExpr expr pat init next nextTy loc hole ctx

  | HLetFunExpr (funSerial, _vis, isMainFun, args, body, next, nextTy, loc) ->
      kgLetFunExpr expr funSerial isMainFun args body next nextTy loc hole ctx

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

let kirGen (_expr: HExpr, tyCtx: TyCtx): KRoot * TyCtx =
  KRoot([], KPrimNode(KExitPrim, [], [], [], noLoc)), tyCtx
