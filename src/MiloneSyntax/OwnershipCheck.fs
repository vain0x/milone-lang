module rec MiloneSyntax.OwnershipCheck

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.Tir
open MiloneSyntax.TySystem
open MiloneSyntaxTypes.TirTypes
open Std.StdError
open Std.StdMap
open Std.StdSet

module StdInt = Std.StdInt
module S = Std.StdString

let private emptyOwnedTySet: TreeSet<TySerial> = TSet.empty compare

/// Mapping from varSerial to (true = owned | false = disposed)
type private OwnershipMap = TreeMap<VarSerial, bool>

/// Empty ownership map.
let private emptyMap: OwnershipMap = TMap.empty varSerialCompare

/// Map from variable to location where it's used.
/// These variables are used (in a particular area such as branch.)
type private UsedMap = TreeMap<VarSerial, Loc>

let private emptyUsedMap: TreeMap<VarSerial, Loc> = TMap.empty varSerialCompare

// -----------------------------------------------
// Rx
// -----------------------------------------------

/// Read-only context for ownership check.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Rx =
  { GetVarName: VarSerial -> string
    GetVarLoc: VarSerial -> Loc
    Funs: TreeMap<FunSerial, FunDef>
    OwnedTySet: TreeSet<TySerial> }

let private newRxForToplevel ownedTySet (tirCtx: TirCtx) : Rx =
  let findVar varSerial = tirCtx.StaticVars |> mapFind varSerial

  let rx: Rx =
    { GetVarName = fun varSerial -> (findVar varSerial).Name
      GetVarLoc = fun varSerial -> (findVar varSerial).Loc
      Funs = tirCtx.Funs
      OwnedTySet = ownedTySet }

  rx

let private newRxForModule ownedTySet (m: TModule) (tirCtx: TirCtx) : Rx =
  let findVar varSerial =
    match m.Vars |> TMap.tryFind varSerial with
    | Some varDef -> varDef
    | None -> tirCtx.StaticVars |> mapFind varSerial

  let rx: Rx =
    { GetVarName = fun varSerial -> (findVar varSerial).Name
      GetVarLoc = fun varSerial -> (findVar varSerial).Loc
      Funs = tirCtx.Funs
      OwnedTySet = ownedTySet }

  rx

let private funIsGeneric (rx: Rx) funSerial =
  let funDef = rx.Funs |> mapFind funSerial
  let (TyScheme (tyVars, _)) = funDef.Ty
  tyVars |> List.isEmpty |> not

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private OwnershipCheckCtx =
  { Parent: OwnershipMap
    Current: OwnershipMap
    Used: TreeMap<VarSerial, Loc>
    Logs: (Log * Loc) list }

let private emptyCtx () : OwnershipCheckCtx =
  { Parent = emptyMap
    Current = emptyMap
    Used = emptyUsedMap
    Logs = [] }

// -----------------------------------------------
// Error
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private OwnershipError =
  | VariableNotUsed
  | VariableAlreadyUsed
  | VariableCannotBeUsed
  | VariableCannotBeCaptured
  | VariantInvalid
  | CannotUseAsPat
  | StaticVarCannotBeOwned
  | GenericFunCannotUseOwned
  | BranchMustUse of varNames: string list
  | FieldCannotBeOwned
  | PartialApp

let private errorToString err =
  match err with
  | OwnershipError.VariableNotUsed -> "This variable of owned type is not used."

  | OwnershipError.VariableAlreadyUsed -> "This variable of owned type is already used and cannot be used here."

  | OwnershipError.VariableCannotBeUsed ->
    "This variable of owned type must not be used in this branch because the previous branch does not use it."

  | OwnershipError.VariableCannotBeCaptured ->
    "This variable of owned type must not be used in local functions and function expressions."

  | OwnershipError.VariantInvalid ->
    "This variant of owned type is invalid for now. This error happens when a union contains another owned union type. Consider to use the Own type directly."

  | OwnershipError.CannotUseAsPat -> "This variable of owned type cannot be defined by AS pattern."

  | OwnershipError.StaticVarCannotBeOwned -> "This static variable cannot be an owned type."

  | OwnershipError.GenericFunCannotUseOwned -> "This generic function cannot bind type variables to owned types."

  | OwnershipError.BranchMustUse varNames ->
    assert (varNames |> List.isEmpty |> not)

    "This branch must use a particular set of variables that are used in the previous branch. Variables: ["
    + S.concat "; " varNames
    + "]"

  | OwnershipError.FieldCannotBeOwned -> "Fields cannot be owned types for now."

  | OwnershipError.PartialApp -> "Functions that take a value of owned type can't be partially applied."

let private addError err (loc: Loc) (ctx: OwnershipCheckCtx) =
  { ctx with Logs = (Log.Error(errorToString err), loc) :: ctx.Logs }

// -----------------------------------------------
// Types
// -----------------------------------------------

let private tyIsOwnedWith ownedTySet ty : bool =
  let rec go ty =
    let (Ty (tk, tyArgs)) = ty

    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | BoolTk
    | CharTk
    | StringTk
    | ObjTk
    | FunTk
    | VoidPtrTk _
    | NativePtrTk _
    | NativeFunTk
    | NativeTypeTk _
    | MetaTk _
    | UnivTk _ -> false

    | OwnTk -> true

    | TupleTk
    | ListTk -> tyArgs |> List.exists go

    | UnionTk (tySerial, _) ->
      // Note that it's unclear whether union is an owned when it has an owned type as argument
      // since that type variable might not appear or not *owned*.
      // (E.g. 'T in type U<'T> = V of ('T -> 'T) isn't owned.)
      TSet.contains tySerial ownedTySet
      || tyArgs |> List.exists go

    | RecordTk _ ->
      assert (List.isEmpty tyArgs)
      false // Record types can't be owned types nor generic for now.

    | SynonymTk _
    | InferTk _ -> unreachable () // SynonymTk, InferTk are resolved in Typing.

  go ty

let private tyIsOwned (rx: Rx) ty = tyIsOwnedWith rx.OwnedTySet ty

// FIXME: Union types that own the Own type directly are owned for now.
//        This should be transitive.
let private computeOwnedTySet (tirCtx: TirCtx) =
  tirCtx.Tys
  |> TMap.fold
       (fun ownedTySet tySerial (tyDef: TyDef) ->
         match tyDef with
         | UnionTyDef (_, _, variants, _) ->
           let owned =
             variants
             |> List.exists (fun variantSerial ->
               let variantDef = tirCtx.Variants |> mapFind variantSerial

               variantDef.HasPayload
               && tyIsOwnedWith ownedTySet variantDef.PayloadTy)

           if owned then
             ownedTySet |> TSet.add tySerial
           else
             ownedTySet

         | _ -> ownedTySet)
       emptyOwnedTySet

// -----------------------------------------------
// Check definitions
// -----------------------------------------------

/// Performs ownership check for definitions.
let private ocDefs ownedTySet (tirCtx: TirCtx) =
  let logs, tirCtx = tirCtx.Logs, { tirCtx with Logs = [] }

  let rx = newRxForToplevel ownedTySet tirCtx
  let isOwned ty = tyIsOwned rx ty

  let logs =
    tirCtx.StaticVars
    |> TMap.fold
         (fun logs _ (varDef: VarDef) ->
           if isOwned varDef.Ty then
             let log =
               Log.Error(errorToString OwnershipError.StaticVarCannotBeOwned)

             (log, varDef.Loc) :: logs
           else
             logs)
         logs

  let logs =
    tirCtx.Variants
    |> TMap.fold
         (fun logs _ (variantDef: VariantDef) ->
           if tyIsOwned rx variantDef.PayloadTy then
             if rx.OwnedTySet
                |> TSet.contains variantDef.UnionTySerial
                |> not then
               let log =
                 Log.Error(errorToString OwnershipError.VariantInvalid)

               (log, variantDef.Loc) :: logs
             else
               logs
           else
             logs)
         logs

  let logs =
    tirCtx.Tys
    |> TMap.fold
         (fun logs _ tyDef ->
           match tyDef with
           | RecordTyDef (_, _, fields, _, _) ->
             fields
             |> List.fold
                  (fun logs (_, ty, loc) ->
                    if isOwned ty then
                      let log =
                        Log.Error(errorToString OwnershipError.FieldCannotBeOwned)

                      (log, loc) :: logs
                    else
                      logs)
                  logs

           | UnivTyDef _
           | SynonymTyDef _
           | UnionTyDef _ -> logs)
         logs

  { tirCtx with Logs = logs }

// -----------------------------------------------
// Control
// -----------------------------------------------

let private markAsDefined (ctx: OwnershipCheckCtx) varSerial : OwnershipCheckCtx =
  { ctx with Current = ctx.Current |> TMap.add varSerial true }

let private markAsUsed (ctx: OwnershipCheckCtx) varSerial loc : OwnershipCheckCtx =
  match ctx.Parent |> TMap.tryFind varSerial with
  | Some true -> { ctx with Used = ctx.Used |> TMap.add varSerial loc }
  | Some false -> addError OwnershipError.VariableAlreadyUsed loc ctx
  | None ->
    match ctx.Current |> TMap.tryFind varSerial with
    | Some true -> { ctx with Current = ctx.Current |> TMap.add varSerial false }
    | Some false -> addError OwnershipError.VariableAlreadyUsed loc ctx
    | None -> addError OwnershipError.VariableCannotBeCaptured loc ctx

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Branch =
  { // Stashed state of the parent branch.
    Parent: OwnershipMap
    Current: OwnershipMap
    Used: UsedMap

    // Set of variables
    //    that are defined outside the branches
    //    and used in the first branch.
    PrevOpt: UsedMap option }

let private enterBranches (ctx: OwnershipCheckCtx) =
  let branch: Branch =
    { Parent = ctx.Parent
      Current = ctx.Current
      Used = ctx.Used
      PrevOpt = None }

  // Merge current and used into parent. this could be more efficient by improving data structure
  let parent =
    ctx.Used
    |> TMap.fold (fun parent varSerial _ -> parent |> TMap.add varSerial false) ctx.Parent

  let parent =
    ctx.Current
    |> TMap.fold (fun parent varSerial owned -> parent |> TMap.add varSerial owned) parent

  let ctx =
    { ctx with
        Parent = parent
        Current = emptyMap
        Used = emptyUsedMap }

  branch, ctx

let private nextBranch (rx: Rx) (branch: Branch) (branchLoc: Loc) (ctx: OwnershipCheckCtx) =
  let current, used, logs, ctx =
    ctx.Current,
    ctx.Used,
    ctx.Logs,
    { ctx with
        Current = emptyMap
        Used = emptyUsedMap
        Logs = [] }

  // All variables that are defined in the branch must be disposed.
  let logs =
    current
    |> TMap.fold
         (fun logs varSerial owned ->
           if owned then
             let log =
               Log.Error(errorToString OwnershipError.VariableNotUsed)

             let loc = rx.GetVarLoc varSerial
             (log, loc) :: logs
           else
             logs)
         logs

  // All variables that are disposed in the previous branch must be disposed
  // and others must not be disposed.
  let logs =
    match branch.PrevOpt with
    | Some prev ->
      let logs =
        used
        |> TMap.fold
             (fun logs varSerial loc ->
               if prev |> TMap.containsKey varSerial |> not then
                 let log =
                   Log.Error(errorToString OwnershipError.VariableCannotBeUsed)

                 (log, loc) :: logs
               else
                 logs)
             logs

      let logs =
        let unused =
          prev
          |> TMap.fold
               (fun acc varSerial _ ->
                 if used |> TMap.containsKey varSerial |> not then
                   varSerial :: acc
                 else
                   acc)
               []

        if unused |> List.isEmpty |> not then
          let names = unused |> List.map rx.GetVarName

          let log =
            Log.Error(errorToString (OwnershipError.BranchMustUse names))

          (log, branchLoc) :: logs
        else
          logs

      logs

    | None -> logs

  let branch =
    if branch.PrevOpt |> Option.isNone then
      { branch with PrevOpt = Some used }
    else
      branch

  let ctx = { ctx with Logs = logs }

  branch, ctx

let private leaveBranches (branch: Branch) (ctx: OwnershipCheckCtx) : OwnershipCheckCtx =
  // Propagate "used" marks to the parent branch.
  let current, used =
    let branchUsed =
      branch.PrevOpt |> Option.defaultValue emptyUsedMap

    branchUsed
    |> TMap.fold
         (fun (current, used) varSerial loc ->
           match branch.Current |> TMap.tryFind varSerial with
           | Some owned ->
             assert owned
             current |> TMap.add varSerial false, used

           | None -> current, used |> TMap.add varSerial loc)
         (branch.Current, branch.Used)

  // Rollback the state to the parent branch.
  { ctx with
      Parent = branch.Parent
      Current = current
      Used = used }

let private enterBody (ctx: OwnershipCheckCtx) : _ * OwnershipCheckCtx =
  let branch, ctx = enterBranches ctx

  // Prevent body from using parent owned variables (no escape).
  let ctx = { ctx with Parent = emptyMap }

  branch, ctx

let private leaveBody rx (branch: Branch) bodyLoc (ctx: OwnershipCheckCtx) : OwnershipCheckCtx =
  // reuse error checking mechanism. this is not ideal because error message talks about branching
  let branch, ctx = nextBranch rx branch bodyLoc ctx
  leaveBranches branch ctx

let private ocPat (rx: Rx) (ctx: OwnershipCheckCtx) pat : OwnershipCheckCtx =
  match pat with
  | TLitPat _ -> ctx

  | TDiscardPat (ty, loc) ->
    if tyIsOwned rx ty then
      addError OwnershipError.VariableNotUsed loc ctx
    else
      ctx

  | TVarPat (_, varSerial, ty, _) ->
    if tyIsOwned rx ty then
      markAsDefined ctx varSerial
    else
      ctx

  | TVariantPat _ ->
    // Matching to variant is considered a use, okay?
    ctx

  | TNodePat (_, argPats, _, _) -> argPats |> List.fold (ocPat rx) ctx

  | TAsPat (bodyPat, varSerial, loc) ->
    let ctx =
      let ty = patToTy bodyPat

      if tyIsOwned rx ty then
        let ctx = markAsDefined ctx varSerial
        addError OwnershipError.CannotUseAsPat loc ctx
      else
        ctx

    ocPat rx ctx bodyPat

  | TOrPat (lPat, _, _) -> ocPat rx ctx lPat

// applied: true if target of the expression is caller of function application. (It appears as `e` in `e x`.)
let private ocExpr (rx: Rx) (applied: bool) (ctx: OwnershipCheckCtx) expr : OwnershipCheckCtx =
  match expr with
  | TLitExpr _
  | TVariantExpr _
  | TPrimExpr _ -> ctx

  | TVarExpr (varSerial, ty, loc) ->
    if tyIsOwned rx ty then
      markAsUsed ctx varSerial loc
    else
      ctx

  | TFunExpr (funSerial, ty, loc) ->
    let rec funTyContainsOwnedTy ty =
      match ty with
      | Ty (FunTk, [ sTy; tTy ]) -> tyIsOwned rx sTy || funTyContainsOwnedTy tTy
      | _ -> tyIsOwned rx ty

    if funIsGeneric rx funSerial
       && funTyContainsOwnedTy ty then
      let funDef = rx.Funs |> mapFind funSerial
      let (TyScheme (_, defTy)) = funDef.Ty

      let defTy =
        // Replace univTy -> metaTy
        let rec go ty =
          match ty with
          | Ty (UnivTk (tySerial, _, loc), _) -> tyMeta tySerial loc
          | Ty (_, []) -> ty
          | Ty (tk, tys) -> Ty(tk, List.map go tys)

        go defTy

      // Extraction of type assignment.
      let rec go acc lTy rTy =
        match unifyNext lTy rTy loc with
        | UnifyOk -> Some acc

        | UnifyOkWithStack stack ->
          List.fold
            (fun accOpt (l, r) ->
              match accOpt with
              | Some acc -> go acc l r
              | None -> None)
            (Some acc)
            stack

        | UnifyError (log, loc) ->
          // __trace (__dump (log, loc))
          None

        | UnifyExpandMeta (tySerial, otherTy) ->
          match acc |> assocTryFind compare tySerial with
          | Some ty -> go acc ty otherTy

          | None ->
            let otherTy =
              otherTy
              |> tySubst (fun tySerial -> acc |> assocTryFind compare tySerial)

            match unifyAfterExpandMeta lTy rTy tySerial otherTy loc with
            | UnifyAfterExpandMetaResult.OkNoBind -> Some acc
            | UnifyAfterExpandMetaResult.OkBind -> Some((tySerial, otherTy) :: acc)
            | UnifyAfterExpandMetaResult.Error (log, loc) ->
              // __trace (__dump (log, loc))
              None

        | UnifyExpandSynonym _ -> unreachable () // Synonym types are resolved in Typing.

      let tyArgsOpt =
        go [] ty defTy |> Option.map (List.map snd)

      match tyArgsOpt with
      | Some tyArgs ->
        if tyArgs |> List.exists (tyIsOwned rx) then
          addError OwnershipError.GenericFunCannotUseOwned loc ctx
        else
          ctx

      | None ->
        // Unification might fail when program doesn't type-check.
        if ctx.Logs |> List.isEmpty then
          unreachable (ty, defTy, loc)

        assert (ctx.Logs |> List.isEmpty |> not)
        ctx
    else
      ctx

  | TRecordExpr (baseOpt, fields, _, _) ->
    let ctx =
      Option.fold (ocExpr rx false) ctx baseOpt

    fields
    |> List.fold (fun ctx (_, init, _) -> ocExpr rx false ctx init) ctx

  | TMatchExpr (cond, arms, _, _) ->
    let ctx = ocExpr rx false ctx cond

    let branch, ctx = enterBranches ctx

    let branch, ctx =
      arms
      |> List.fold
           (fun (branch, ctx) (pat, guard, body) ->
             let ctx = ocPat rx ctx pat
             let ctx = ocExpr rx false ctx guard
             let ctx = ocExpr rx false ctx body
             nextBranch rx branch (exprToLoc body) ctx)
           (branch, ctx)

    leaveBranches branch ctx

  | TNavExpr (l, _, _, _) -> ocExpr rx false ctx l

  | TNodeExpr (kind, args, ty, loc) ->
    match kind with
    | TAppEN ->
      let l, r =
        match args with
        | [ l; r ] -> l, r
        | _ -> unreachable ()

      let rec takesOwnedArg ty =
        match ty with
        | Ty (FunTk, sTy :: _) when tyIsOwned rx sTy -> true
        | Ty (FunTk, [ _; tTy ]) -> takesOwnedArg tTy
        | _ -> false

      let tyIsFun ty =
        match ty with
        | Ty (FunTk, _) -> true
        | _ -> false

      let ctx =
        if
          not applied && tyIsFun ty
          && takesOwnedArg (exprToTy l)
        then
          addError OwnershipError.PartialApp loc ctx
        else
          ctx

      let ctx = ocExpr rx true ctx l
      ocExpr rx false ctx r

    | _ -> ocExprs rx ctx args

  | TBlockExpr (stmts, last) ->
    let ctx = ocStmts rx ctx stmts
    ocExpr rx applied ctx last

let private ocExprs rx ctx exprs : OwnershipCheckCtx =
  exprs |> List.fold (ocExpr rx false) ctx

let private ocStmt rx (ctx: OwnershipCheckCtx) stmt : OwnershipCheckCtx =
  match stmt with
  | TExprStmt expr -> ocExpr rx false ctx expr

  | TLetValStmt (pat, init, _) ->
    let ctx = ocPat rx ctx pat
    ocExpr rx false ctx init

  | TLetFunStmt (_, _, _, argPats, body, loc) ->
    let parent, ctx = enterBody ctx
    let ctx = argPats |> List.fold (ocPat rx) ctx
    let ctx = ocExpr rx false ctx body
    leaveBody rx parent loc ctx

  | TBlockStmt (_, stmts) -> ocStmts rx ctx stmts

let private ocStmts rx ctx stmts : OwnershipCheckCtx = stmts |> List.fold (ocStmt rx) ctx

let private ocProgram ownedTySet (modules: TProgram) (tirCtx: TirCtx) : TirCtx =
  let ctx = { emptyCtx () with Logs = tirCtx.Logs }

  let ctx =
    modules
    |> List.fold
         (fun ctx (m: TModule) ->
           let rx = newRxForModule ownedTySet m tirCtx

           m.Stmts |> List.fold (ocStmt rx) ctx)
         ctx

  { tirCtx with Logs = ctx.Logs }

// -----------------------------------------------
// Rewrite
// -----------------------------------------------

// Remove Std.Own primitives.

/// Gets whether a type syntactically contains the Own type (not owned types).
/// (It doesn't consider type variables are owned or not.)
let private tyContainsOwn ty =
  let rec go ty =
    match ty with
    | Ty (OwnTk, _) -> true
    | Ty (_, []) -> false
    | Ty (_, tyArgs) -> tyArgs |> List.exists go

  go ty

let private lwTy ty : Ty =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | OwnTk, [ itemTy ] -> lwTy itemTy
  | _, [] -> ty
  | _ -> Ty(tk, List.map lwTy tyArgs)

let private lwPat pat : TPat = patMap lwTy pat

let private lwExpr expr : TExpr =
  match expr with
  | TLitExpr _
  | TVarExpr _
  | TFunExpr _
  | TVariantExpr _
  | TPrimExpr _ -> exprMap lwTy expr

  | TRecordExpr (baseOpt, fields, ty, loc) ->
    TRecordExpr(
      Option.map lwExpr baseOpt,
      List.map (fun (ident, init, loc) -> ident, lwExpr init, loc) fields,
      lwTy ty,
      loc
    )

  | TMatchExpr (cond, arms, ty, loc) ->
    TMatchExpr(
      lwExpr cond,
      List.map (fun (pat, guard, body) -> lwPat pat, lwExpr guard, lwExpr body) arms,
      lwTy ty,
      loc
    )

  | TNavExpr (l, r, ty, loc) -> TNavExpr(lwExpr l, r, lwTy ty, loc)

  | TNodeExpr (TAppEN, [ TPrimExpr (TPrim.OwnAcquire, _, _); arg ], _, _) -> lwExpr arg
  | TNodeExpr (TAppEN, [ TPrimExpr (TPrim.OwnRelease, _, _); arg ], _, _) -> lwExpr arg

  | TNodeExpr (kind, args, ty, loc) -> TNodeExpr(kind, List.map lwExpr args, lwTy ty, loc)
  | TBlockExpr (stmts, last) -> TBlockExpr(List.map lwStmt stmts, lwExpr last)

let private lwStmt stmt : TStmt =
  match stmt with
  | TExprStmt expr -> TExprStmt(lwExpr expr)
  | TLetValStmt (pat, init, loc) -> TLetValStmt(lwPat pat, lwExpr init, loc)

  | TLetFunStmt (funSerial, isRec, vis, argPats, body, loc) ->
    TLetFunStmt(funSerial, isRec, vis, List.map lwPat argPats, lwExpr body, loc)

  | TBlockStmt (isRec, stmts) -> TBlockStmt(isRec, List.map lwStmt stmts)

let private lwProgram modules (tirCtx: TirCtx) : TProgram * TirCtx =
  let modules =
    modules
    |> List.map (fun (m: TModule) ->
      { m with
          Vars =
            m.Vars
            |> TMap.map (fun _ (varDef: VarDef) ->
              if tyContainsOwn varDef.Ty then
                { varDef with Ty = lwTy varDef.Ty }
              else
                varDef)
          Stmts = m.Stmts |> List.map lwStmt })

  let tirCtx =
    { tirCtx with
        StaticVars =
          tirCtx.StaticVars
          |> TMap.map (fun _ (varDef: VarDef) ->
            if tyContainsOwn varDef.Ty then
              { varDef with Ty = lwTy varDef.Ty }
            else
              varDef)
        Variants =
          tirCtx.Variants
          |> TMap.map (fun _ (variantDef: VariantDef) ->
            if tyContainsOwn variantDef.PayloadTy then
              { variantDef with PayloadTy = lwTy variantDef.PayloadTy }
            else
              variantDef)
        Funs =
          tirCtx.Funs
          |> TMap.map (fun _ (funDef: FunDef) ->
            let (TyScheme (tyVars, ty)) = funDef.Ty

            if tyContainsOwn ty then
              { funDef with Ty = TyScheme(tyVars, lwTy ty) }
            else
              funDef)
        Tys =
          tirCtx.Tys
          |> TMap.map (fun _ (tyDef: TyDef) ->
            match tyDef with
            | RecordTyDef (ident, tyArgs, fields, repr, loc) ->
              if fields
                 |> List.exists (fun (_, ty, _) -> tyContainsOwn ty) then
                let fields =
                  fields
                  |> List.map (fun (ident, ty, loc) -> ident, lwTy ty, loc)

                RecordTyDef(ident, tyArgs, fields, repr, loc)
              else
                tyDef

            | UnivTyDef _
            | SynonymTyDef _
            | UnionTyDef _ -> tyDef) }

  modules, tirCtx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let ownershipCheck (modules: TProgram, tirCtx: TirCtx) : TProgram * TirCtx =
  let ownedTySet = computeOwnedTySet tirCtx

  let tirCtx = ocDefs ownedTySet tirCtx
  let tirCtx = ocProgram ownedTySet modules tirCtx

  if tirCtx.Logs |> List.isEmpty then
    lwProgram modules tirCtx
  else
    modules, tirCtx
