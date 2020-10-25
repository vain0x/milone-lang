/// # KirGen
///
/// Generate continuation passing style (CPS) intermediate representation, KIR
/// from HIR.
///
/// This is not only a data transformation but also:
///
/// - resolve pattern matching

module rec MiloneLang.KirGen

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers

type kgx = KirGenCtx

let private isVariantFun varSerial ctx = false

// -----------------------------------------------
// Pattern matching resolution
// -----------------------------------------------

// TODO

// -----------------------------------------------
// Primitive dispatch
// -----------------------------------------------

// prim expr, not appear as callee
let private kgPrimExpr expr prim ty loc ret ctx: KNode * kgx =
  match prim with
  | HPrim.Nil ->
      let itemTy =
        match ty with
        | AppTy (ListTyCtor, [ itemTy ]) -> itemTy

        | _ -> failwithf "NEVER: []'s type must be a list. %A" expr

      ret (KNilTerm(itemTy, loc)) ctx

  | HPrim.OptionNone ->
      let itemTy =
        match ty with
        | AppTy (ListTyCtor, [ itemTy ]) -> itemTy

        | _ -> failwithf "NEVER: None's type must be a list. %A" expr

      ret (KNoneTerm(itemTy, loc)) ctx

  | _ -> failwithf "NEVER: Prim must appear in form of call(prim, args...). %A" expr

let private kgCallAddExpr expr primTy args ty primLoc ret ctx =
  match args with
  | [ l; r ] ->
      match exprToTy l with
      | AppTy ((IntTyCtor
               | CharTyCtor),
               _) ->
          // scalar add
          failwith "todo"

      | AppTy (StrTyCtor, _) ->
          // string add
          failwith "todo"

      | _ -> failwithf "NEVER: bad type %A" expr

  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallSubExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallMulExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallDivExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallModExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallEqExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallLtExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallConsExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallIndexExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallSomeExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallNotExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallExitExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallBoxExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallUnboxExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

let private kgCallStrLengthExpr expr primTy args ty primLoc ret ctx =
  match args with
  | _ -> failwithf "NEVER: bad arity %A" expr

// call to other prim listed above.
// just generate a call expression.
// do further more in downstream.
let private kgCallOtherPrimExpr expr prim args ty loc ret ctx = failwith ""

let private kgCallVariantExpr expr varSerial variantTy variantLoc args ty loc ret ctx = failwith ""

// call to something non-prim, non-variant. typically a function.
let private kgCallOtherExpr expr callee args ty loc ret ctx = failwith ""

let private kgSemiExpr expr args ty loc ret ctx =
  let rec go args ret ctx =
    match args with
    | [ last ] -> kgExpr last ret ctx

    | arg :: args ->
        // Generate arg and the result is discarded with `_`. And then continue to loop.
        kgExpr arg (fun _ ctx -> ctx |> go args ret) ctx

    | [] -> failwithf "NEVER: semi can't be empty %A" expr

  go args ret ctx

let private kgInfExpr expr infOp args ty loc ret ctx: KNode * kgx =
  match infOp with
  | InfOp.Semi -> kgSemiExpr expr args ty loc ret ctx

  | InfOp.CallProc ->
      let callee, args =
        match args with
        | callee :: args -> callee, args
        | [] -> failwithf "NEVER: CallProc args must begin with callee. %A" expr

      match callee with
      | HPrimExpr (prim, primTy, primLoc) ->
          match prim with
          | HPrim.Add -> kgCallAddExpr expr primTy args ty primLoc ret ctx
          | HPrim.Sub -> kgCallSubExpr expr primTy args ty primLoc ret ctx
          | HPrim.Mul -> kgCallMulExpr expr primTy args ty primLoc ret ctx
          | HPrim.Div -> kgCallDivExpr expr primTy args ty primLoc ret ctx
          | HPrim.Mod -> kgCallModExpr expr primTy args ty primLoc ret ctx
          | HPrim.Eq -> kgCallEqExpr expr primTy args ty primLoc ret ctx
          | HPrim.Lt -> kgCallLtExpr expr primTy args ty primLoc ret ctx
          | HPrim.Cons -> kgCallConsExpr expr primTy args ty primLoc ret ctx
          | HPrim.Index -> kgCallIndexExpr expr primTy args ty primLoc ret ctx
          | HPrim.OptionSome -> kgCallSomeExpr expr primTy args ty primLoc ret ctx
          | HPrim.Not -> kgCallNotExpr expr primTy args ty primLoc ret ctx
          | HPrim.Exit -> kgCallExitExpr expr primTy args ty primLoc ret ctx
          | HPrim.Box -> kgCallBoxExpr expr primTy args ty primLoc ret ctx
          | HPrim.Unbox -> kgCallUnboxExpr expr primTy args ty primLoc ret ctx
          | HPrim.StrLength -> kgCallStrLengthExpr expr primTy args ty primLoc ret ctx
          | _ -> kgCallOtherPrimExpr expr primTy args ty primLoc ret ctx

      | HRefExpr (varSerial, refTy, refLoc) when ctx |> isVariantFun varSerial ->
          kgCallVariantExpr expr varSerial refTy args ty refLoc loc ret ctx

      | _ -> kgCallOtherExpr expr callee args ty loc ret ctx

  | InfOp.CallClosure ->
      match args with
      | callee :: args -> failwith ""
      // mirifyExprInfCallClosure ctx callee args ty loc

      | [] -> failwithf "NEVER: CallClosure args must begin with callee. %A" expr

  | InfOp.Tuple ->
      match args, ty with
      | [], _ -> ret (KUnitTerm loc) ctx

      | _, AppTy (TupleTyCtor, itemTys) ->
          // mirifyExprTuple ctx args itemTys loc
          failwith ""

      | _ -> failwithf "NEVER: tuple ctor must be of tuple type. %A" expr

  | InfOp.Closure ->
      match args with
      | [ HRefExpr (funSerial, _, _); env ] ->
          // mirifyExprInfClosure ctx funSerial env ty loc
          failwith ""

      | _ -> failwithf "NEVER: bad use of Closure prim. %A" expr

  | InfOp.App -> failwithf "NEVER: InfOp.App is resolved in uneta. %A" expr
  | InfOp.Anno -> failwithf "NEVER: InfOp.Anno is resolved in type inference: %A" expr

// -----------------------------------------------
// match, let-val, let-fun
// -----------------------------------------------

let private kgMatchExpr expr cond arms targetTy loc ret ctx: KNode * kgx = failwith ""

let private kgLetValExpr expr pat init next nextTy loc ret ctx: KNode * kgx = failwith ""

let private kgLetFunExpr expr funSerial isMainFun args body next nextTy loc ret ctx: KNode * kgx = failwith ""

// -----------------------------------------------
// kgExpr
// -----------------------------------------------

let private kgExpr (expr: HExpr) (ret: KTerm -> kgx -> KNode * kgx) (ctx: kgx): KNode * kgx =
  match expr with
  | HLitExpr (lit, loc) -> ret (KLitTerm(lit, loc)) ctx

  | HRefExpr (varSerial, ty, loc) -> ret (KVarTerm(varSerial, ty, loc)) ctx

  | HPrimExpr (prim, ty, loc) -> kgPrimExpr expr prim ty loc ret ctx

  | HMatchExpr (cond, arms, ty, loc) -> kgMatchExpr expr cond arms ty loc ret ctx

  | HInfExpr (infOp, args, ty, loc) -> kgInfExpr expr infOp args ty loc ret ctx

  | HLetValExpr (_vis, pat, init, next, nextTy, loc) -> kgLetValExpr expr pat init next nextTy loc ret ctx

  | HLetFunExpr (funSerial, _vis, isMainFun, args, body, next, nextTy, loc) ->
      kgLetFunExpr expr funSerial isMainFun args body next nextTy loc ret ctx

  | HTyDeclExpr _
  | HOpenExpr _ ->
      let justUnit () =
        let loc = exprToLoc expr
        ret (KUnitTerm loc) ctx

      justUnit ()

  | HErrorExpr (msg, loc) ->
      let raiseError () =
        failwithf "HErrorExpr in KirGen: %s" (msg + " " + locToString loc)

      raiseError ()

  | HNavExpr _ -> failwithf "NEVER: nav is resolved in type inference. %A" expr
  | HModuleExpr _ -> failwithf "NEVER: module is resolved in name res. %A" expr

let kirGen (_expr: HExpr, tyCtx: TyCtx): KRoot * TyCtx =
  KRoot([], KPrimNode(KExitPrim, [], [], [], noLoc)), tyCtx
