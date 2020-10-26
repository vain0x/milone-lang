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

type private kgx = KirGenCtx

let private unreachable value = failwithf "NEVER: %A" value

let private isVariantFun varSerial ctx = false

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

type pmx = kgx

type PTerm =
  | PLitTerm of Lit * Loc
  | PTagTerm of VariantSerial * Ty * Loc
  | PNilTerm of itemTy: Ty * Loc
  | PNoneTerm of itemTy: Ty * Loc

type PNode =
  | PResolveNode of Loc
  | PRejectNode of Loc
  | PEqualNode of PTerm * resolve: PNode * reject: PNode * Loc
  | PLetNode of VarSerial * Ty * resolve: PNode * Loc

let private findVarDef _ = failwith ""

let private kgRefPat pat varSerial ty loc resolve reject ctx =
  match findVarDef varSerial with
  | VarDef _ -> PLetNode(varSerial, ty, resolve (), loc)

  | VariantDef _ -> PEqualNode(PTagTerm(varSerial, ty, loc), resolve (), reject (), loc)

  | FunDef _ -> failwithf "NEVER: fun can't appear as pattern. %A" pat

let private kgTuplePat pat itemPats tupleTy loc resolve reject ctx = failwith ""

let private kgCallPat pat callee args ty loc pass fail ctx =
  match callee with
  | HRefPat (serial, _, _) -> failwith ""

  | HSomePat (itemTy, _) ->
      match args with
      | [ itemPat ] -> failwith ""

      | _ -> failwithf "NEVER: bad arity. %A" pat

  | _ -> failwithf "NEVER: illegal call pat. %A" pat

let private kgPat (pat: HPat) resolve reject ctx: PNode =
  match pat with
  | HDiscardPat _ -> resolve ()

  | HLitPat (lit, loc) -> PEqualNode(PLitTerm(lit, loc), resolve (), reject (), loc)

  | HNilPat (itemTy, loc) -> PEqualNode(PNilTerm(itemTy, loc), resolve (), reject (), loc)

  | HNonePat (itemTy, loc) -> PEqualNode(PNoneTerm(itemTy, loc), resolve (), reject (), loc)

  | HRefPat (varSerial, ty, loc) -> kgRefPat pat varSerial ty loc resolve reject ctx

  | HCallPat (callee, args, ty, loc) -> kgCallPat pat callee args ty loc resolve reject ctx

  | HConsPat (l, r, itemTy, loc) -> failwith ""

  | HTuplePat (itemPats, tupleTy, loc) -> kgTuplePat pat itemPats tupleTy loc resolve reject ctx

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
// Emission helpers
// -----------------------------------------------

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
// Primitive dispatch
// -----------------------------------------------

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

let private kgCallSubExpr itself primTy args ty primLoc hole ctx =
  match args with
  | [ l; r ] -> basicPrimNode2 "sub" KSubPrim l r ty primLoc hole ctx
  | _ -> unreachable itself

let private kgCallMulExpr itself primTy args ty primLoc hole ctx =
  match args with
  | [ l; r ] -> basicPrimNode2 "mul" KMulPrim l r ty primLoc hole ctx
  | _ -> unreachable itself

let private kgCallDivExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallModExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallEqExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallLtExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallConsExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallIndexExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallSomeExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallNotExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallExitExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallBoxExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallUnboxExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

let private kgCallStrLengthExpr itself primTy args ty primLoc hole ctx =
  match args with
  | _ -> unreachable itself

// call to other prim listed above.
// just generate a call expression.
// do further more in downstream.
let private kgCallOtherPrimExpr expr prim args ty loc hole ctx = failwith ""

let private kgCallVariantExpr expr varSerial variantTy variantLoc args ty loc hole ctx = failwith ""

// call to something non-prim, non-variant. typically a function.
let private kgCallOtherExpr expr callee args ty loc hole ctx = failwith ""

let private kgSemiExpr itself args ty loc hole ctx =
  let rec go args hole ctx =
    match args with
    | [ last ] -> kgExpr last hole ctx

    | arg :: args ->
        // Generate arg and the result is discarded with `_`. And then continue to loop.
        kgExpr arg (fun _ ctx -> go args hole ctx) ctx

    | [] -> failwithf "NEVER: semi can't be empty %A" itself

  go args hole ctx

let private kgInfExpr itself infOp args ty loc hole ctx: KNode * kgx =
  match infOp with
  | InfOp.Semi -> kgSemiExpr itself args ty loc hole ctx

  | InfOp.CallProc ->
      let callee, args =
        match args with
        | callee :: args -> callee, args
        | [] -> failwithf "NEVER: CallProc args must begin with callee. %A" itself

      match callee with
      | HPrimExpr (prim, primTy, primLoc) ->
          match prim with
          | HPrim.Add -> kgCallAddExpr itself primTy args ty primLoc hole ctx
          | HPrim.Sub -> kgCallSubExpr itself primTy args ty primLoc hole ctx
          | HPrim.Mul -> kgCallMulExpr itself primTy args ty primLoc hole ctx
          | HPrim.Div -> kgCallDivExpr itself primTy args ty primLoc hole ctx
          | HPrim.Mod -> kgCallModExpr itself primTy args ty primLoc hole ctx
          | HPrim.Eq -> kgCallEqExpr itself primTy args ty primLoc hole ctx
          | HPrim.Lt -> kgCallLtExpr itself primTy args ty primLoc hole ctx
          | HPrim.Cons -> kgCallConsExpr itself primTy args ty primLoc hole ctx
          | HPrim.Index -> kgCallIndexExpr itself primTy args ty primLoc hole ctx
          | HPrim.OptionSome -> kgCallSomeExpr itself primTy args ty primLoc hole ctx
          | HPrim.Not -> kgCallNotExpr itself primTy args ty primLoc hole ctx
          | HPrim.Exit -> kgCallExitExpr itself primTy args ty primLoc hole ctx
          | HPrim.Box -> kgCallBoxExpr itself primTy args ty primLoc hole ctx
          | HPrim.Unbox -> kgCallUnboxExpr itself primTy args ty primLoc hole ctx
          | HPrim.StrLength -> kgCallStrLengthExpr itself primTy args ty primLoc hole ctx
          | _ -> kgCallOtherPrimExpr itself primTy args ty primLoc hole ctx

      | HRefExpr (varSerial, refTy, refLoc) when ctx |> isVariantFun varSerial ->
          kgCallVariantExpr itself varSerial refTy args ty refLoc loc hole ctx

      | _ -> kgCallOtherExpr itself callee args ty loc hole ctx

  | InfOp.CallClosure ->
      match args with
      | callee :: args -> failwith ""
      // mirifyExprInfCallClosure ctx callee args ty loc

      | [] -> failwithf "NEVER: CallClosure args must begin with callee. %A" itself

  | InfOp.Tuple ->
      match args, ty with
      | [], _ -> hole (KUnitTerm loc) ctx

      | _, AppTy (TupleTyCtor, itemTys) ->
          // mirifyExprTuple ctx args itemTys loc
          failwith ""

      | _ -> failwithf "NEVER: tuple ctor must be of tuple type. %A" itself

  | InfOp.Closure ->
      match args with
      | [ HRefExpr (funSerial, _, _); env ] ->
          // mirifyExprInfClosure ctx funSerial env ty loc
          failwith ""

      | _ -> failwithf "NEVER: bad use of Closure prim. %A" itself

  | InfOp.App -> failwithf "NEVER: InfOp.App is resolved in uneta. %A" itself
  | InfOp.Anno -> failwithf "NEVER: InfOp.Anno is resolved in type inference: %A" itself

// -----------------------------------------------
// match, let-val, let-fun
// -----------------------------------------------

let private newVar hint ty loc ctx = failwith ""

let private newFun hint ty loc ctx = failwith ""

let private newFunSerial loc ctx = failwith ""

let private addFun funSerial funDef funBinding ctx = failwith ""

let private kgAbort loc ctx =
  let code = KLitTerm(IntLit 1, loc)
  KPrimNode(KExitPrim, [ code ], [], [], loc), ctx

let private kgIfNode _ = failwith ""

let private kgEvalPTerm (term: PTerm) hole: KTerm =
  match term with
  | PLitTerm (lit, loc) -> KLitTerm(lit, loc) |> hole

  | PTagTerm (variantSerial, ty, loc) ->
      // KSelectNode ()
      failwith ""

  | PNilTerm (itemTy, loc) -> KNilTerm(itemTy, loc) |> hole

  | PNoneTerm (itemTy, loc) -> KNoneTerm(itemTy, loc) |> hole

let private kgEvalPNode (term: KTerm) (node: PNode) resolve reject ctx: KNode * kgx =
  match node with
  | PResolveNode _ -> resolve ()

  | PRejectNode _ -> reject ()

  | PEqualNode (expected, resolve, reject, loc) ->
      // if term == expected, then resolve, else reject
      failwith ""

  | PLetNode (varSerial, ty, cont, loc) ->
      let next, ctx =
        kgEvalPNode (KVarTerm(varSerial, ty, loc)) cont resolve reject ctx

      failwith ""

// `match cond with (| pat when guard -> body)*`
let private kgMatchExpr expr cond arms targetTy loc hole ctx: KNode * kgx =
  // Fun to call to leave the match expr.
  let targetFunSerial, ctx = newFunSerial loc ctx

  let leaveMatch target loc =
    KJumpNode(targetFunSerial, [ target ], loc)

  // Creates a fun for each arm to perform pattern-matching on it;
  // returns a node to evaluate the match that consists of these arms.
  let rec go cond arms ctx: KNode * kgx =
    match arms with
    | [] ->
        // Non-exhaustive error.
        kgAbort loc ctx

    | (pat, guard, body) :: arms ->
        let loc = patToLoc pat
        let rest, ctx = go cond arms ctx

        let armFunSerial, ctx = ctx |> newFunSerial loc

        let armFunDef =
          let armFunTy = tyFun tyUnit tyUnit
          FunDef("arm", 1, TyScheme([], armFunTy), loc)

        // Compute pattern-matching.
        let body, ctx =
          let pNode =
            kgPat pat (fun () -> PResolveNode loc) (fun () -> PRejectNode loc) ctx

          let onSuccess () =
            // TODO: check guard. use rest if false
            kgExpr body (fun body ctx -> leaveMatch body loc, ctx) ctx

          let onFailure () = rest, ctx

          kgEvalPNode cond pNode onSuccess onFailure ctx

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

let private kgLetValExpr expr pat init next nextTy loc hole ctx: KNode * kgx = failwith ""

let private kgLetFunExpr expr funSerial isMainFun args body next nextTy loc hole ctx: KNode * kgx = failwith ""

// -----------------------------------------------
// kgExpr
// -----------------------------------------------

/// Evaluates an expression and fills a hole with the result term.
let private kgExpr (expr: HExpr) (hole: KTerm -> kgx -> KNode * kgx) (ctx: kgx): KNode * kgx =
  match expr with
  | HLitExpr (lit, loc) -> hole (KLitTerm(lit, loc)) ctx

  | HRefExpr (varSerial, ty, loc) -> hole (KVarTerm(varSerial, ty, loc)) ctx

  | HPrimExpr (prim, ty, loc) -> kgPrimExpr expr prim ty loc hole ctx

  | HMatchExpr (cond, arms, ty, loc) -> kgMatchExpr expr cond arms ty loc hole ctx

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

/// Evaluates two expressions and fills a hole with their results.
let private kgExpr2 x1 x2 hole ctx =
  ctx
  |> kgExpr x1 (fun x1 ctx ->
       ctx
       |> kgExpr x2 (fun x2 ctx -> hole (x1, x2, ctx)))

let kirGen (_expr: HExpr, tyCtx: TyCtx): KRoot * TyCtx =
  KRoot([], KPrimNode(KExitPrim, [], [], [], noLoc)), tyCtx
