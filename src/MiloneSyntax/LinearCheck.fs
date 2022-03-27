module rec MiloneSyntax.LinearCheck

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.Tir
open MiloneSyntaxTypes.TirTypes
open Std.StdError
open Std.StdMap
open Std.StdSet

module StdInt = Std.StdInt
module S = Std.StdString

let private emptyLinearTySet: TreeSet<TySerial> = TSet.empty compare

/// varSerial -> (true = owned | false = disposed)
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

/// Read-only context for linear check.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Rx =
  { GetVarName: VarSerial -> string
    GetVarLoc: VarSerial -> Loc
    Funs: TreeMap<FunSerial, FunDef>
    LinearTySet: TreeSet<TySerial> }

let private newRxForToplevel linearTys (tirCtx: TirCtx) : Rx =
  let findVar varSerial = tirCtx.StaticVars |> mapFind varSerial

  let rx: Rx =
    { GetVarName = fun varSerial -> (findVar varSerial).Name
      GetVarLoc = fun varSerial -> (findVar varSerial).Loc
      Funs = tirCtx.Funs
      LinearTySet = linearTys }

  rx

let private newRxForModule linearTys (m: TModule) (tirCtx: TirCtx) : Rx =
  let findVar varSerial =
    match m.Vars |> TMap.tryFind varSerial with
    | Some varDef -> varDef
    | None -> tirCtx.StaticVars |> mapFind varSerial

  let rx: Rx =
    { GetVarName = fun varSerial -> (findVar varSerial).Name
      GetVarLoc = fun varSerial -> (findVar varSerial).Loc
      Funs = tirCtx.Funs
      LinearTySet = linearTys }

  rx

let private funIsGeneric (rx: Rx) funSerial =
  let funDef = rx.Funs |> mapFind funSerial
  let (TyScheme (tyVars, _)) = funDef.Ty
  tyVars |> List.isEmpty |> not

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LinearCheckCtx =
  { Parent: OwnershipMap
    Current: OwnershipMap
    Used: TreeMap<VarSerial, Loc>
    Logs: (Log * Loc) list }

let private emptyCtx () : LinearCheckCtx =
  { Parent = emptyMap
    Current = emptyMap
    Used = emptyUsedMap
    Logs = [] }

// -----------------------------------------------
// Error
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LinearError =
  | TypeCannotBeLinear
  | VariableNotUsed
  | VariableAlreadyUsed
  | VariableCannotBeUsed
  | VariableCannotBeCaptured
  | GenericFunCannotUseLinear
  | BranchMustUse of varNames: string list

let private errorToString err =
  match err with
  | LinearError.TypeCannotBeLinear -> "This type cannot be linear."

  | LinearError.VariableNotUsed -> "This linear variable is not used."

  | LinearError.VariableAlreadyUsed -> "This linear variable is already used and cannot be used here."

  | LinearError.VariableCannotBeUsed ->
    "This linear variable must not be used in this branch because the previous branch does not use it."

  | LinearError.VariableCannotBeCaptured ->
    "This linear variable must not be used in local functions and function expressions."

  | LinearError.GenericFunCannotUseLinear -> "This generic function cannot take or return linear values."

  | LinearError.BranchMustUse varNames ->
    assert (varNames |> List.isEmpty |> not)

    "This branch must use a particular set of variables that are used in the previous branch. Variables: ["
    + S.concat "; " varNames
    + "]"

let private addError err (loc: Loc) (ctx: LinearCheckCtx) =
  { ctx with Logs = (Log.Error(errorToString err), loc) :: ctx.Logs }

// -----------------------------------------------
// Types
// -----------------------------------------------

let private tyIsLinearWith linearTySet ty : bool =
  let rec go ty =
    let (Ty (tk, tyArgs)) = ty

    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | BoolTk
    | CharTk
    | StrTk
    | ObjTk
    | FunTk
    | VoidPtrTk
    | NativePtrTk _
    | NativeFunTk
    | NativeTypeTk _
    | MetaTk _
    | UnivTk _
    | RecordTk _ -> false // Record can't be linear for now.

    | LinearTk -> true

    | TupleTk
    | ListTk -> tyArgs |> List.exists go

    | UnionTk (tySerial, _) ->
      List.isEmpty tyArgs
      && TSet.contains tySerial linearTySet

    | SynonymTk _
    | InferTk _ -> unreachable () // SynonymTk, InferTk are resolved in Typing.

  go ty

let private tyIsLinear (rx: Rx) ty = tyIsLinearWith rx.LinearTySet ty

// FIXME: Union types that own __linear directly are linear for now.
//        This should be transitive.
let private computeLinearTys (tirCtx: TirCtx) =
  let isLinear ty = tyIsLinearWith emptyLinearTySet ty

  tirCtx.Tys
  |> TMap.fold
       (fun linearTySet tySerial (tyDef: TyDef) ->
         match tyDef with
         | UnionTyDef (_, [], variants, _) ->
           // Polymorphic union can't be linear for now.

           let linear =
             variants
             |> List.exists (fun variantSerial ->
               let variantDef = tirCtx.Variants |> mapFind variantSerial

               variantDef.HasPayload
               && isLinear variantDef.PayloadTy)

           if linear then
             linearTySet |> TSet.add tySerial
           else
             linearTySet

         | _ -> linearTySet)
       emptyLinearTySet

// -----------------------------------------------
// Check definitions
// -----------------------------------------------

/// Performs linear check for definitions.
let private lcDefs _linearTys (tirCtx: TirCtx) =
  // WIP
  tirCtx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private markAsDefined (ctx: LinearCheckCtx) varSerial : LinearCheckCtx =
  { ctx with Current = ctx.Current |> TMap.add varSerial true }

let private markAsUsed (ctx: LinearCheckCtx) varSerial loc : LinearCheckCtx =
  match ctx.Parent |> TMap.tryFind varSerial with
  | Some true -> { ctx with Used = ctx.Used |> TMap.add varSerial loc }
  | Some false -> addError LinearError.VariableAlreadyUsed loc ctx
  | None ->
    match ctx.Current |> TMap.tryFind varSerial with
    | Some true -> { ctx with Current = ctx.Current |> TMap.add varSerial false }
    | Some false -> addError LinearError.VariableAlreadyUsed loc ctx
    | None -> addError LinearError.VariableCannotBeCaptured loc ctx

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

let private enterBranches (ctx: LinearCheckCtx) =
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

let private nextBranch (rx: Rx) (branch: Branch) (branchLoc: Loc) (ctx: LinearCheckCtx) =
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
               Log.Error(errorToString LinearError.VariableNotUsed)

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
                   Log.Error(errorToString LinearError.VariableCannotBeUsed)

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
            Log.Error(errorToString (LinearError.BranchMustUse names))

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

let private leaveBranches (branch: Branch) (ctx: LinearCheckCtx) : LinearCheckCtx =
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

let private enterBody (ctx: LinearCheckCtx) : _ * LinearCheckCtx =
  let branch, ctx = enterBranches ctx

  // Prevent body from using parent linear variables (no escape).
  let ctx = { ctx with Parent = emptyMap }

  branch, ctx

let private leaveBody rx (branch: Branch) bodyLoc (ctx: LinearCheckCtx) : LinearCheckCtx =
  // reuse error checking mechanism. this is not ideal because error message talks about branching
  let branch, ctx = nextBranch rx branch bodyLoc ctx
  leaveBranches branch ctx

let private lcPat (rx: Rx) (ctx: LinearCheckCtx) pat : LinearCheckCtx =
  match pat with
  | TLitPat _ -> ctx

  | TDiscardPat (ty, loc) ->
    if tyIsLinear rx ty then
      addError LinearError.VariableNotUsed loc ctx
    else
      ctx

  | TVarPat (_, varSerial, ty, _) ->
    if tyIsLinear rx ty then
      markAsDefined ctx varSerial
    else
      ctx

  | TVariantPat (_, ty, loc) ->
    if tyIsLinear rx ty then
      addError LinearError.VariableNotUsed loc ctx
    else
      ctx

  | TNodePat (_, argPats, _, _) -> argPats |> List.fold (lcPat rx) ctx

  | TAsPat (bodyPat, varSerial, _) ->
    let ctx =
      let ty = patToTy bodyPat

      if tyIsLinear rx ty then
        markAsDefined ctx varSerial
      else
        ctx

    lcPat rx ctx bodyPat

  | TOrPat (lPat, _, _) -> lcPat rx ctx lPat

let private lcExpr (rx: Rx) (ctx: LinearCheckCtx) expr : LinearCheckCtx =
  match expr with
  | TLitExpr _
  | TVariantExpr _
  | TPrimExpr _ -> ctx

  | TVarExpr (varSerial, ty, loc) ->
    if tyIsLinear rx ty then
      markAsUsed ctx varSerial loc
    else
      ctx

  | TFunExpr (funSerial, ty, loc) ->
    let rec funTyContainsLinear ty =
      match ty with
      | Ty (FunTk, [ sTy; tTy ]) -> tyIsLinear rx sTy || funTyContainsLinear tTy
      | _ -> unreachable ()

    if funIsGeneric rx funSerial
       && funTyContainsLinear ty then
      addError LinearError.GenericFunCannotUseLinear loc ctx
    else
      ctx

  | TRecordExpr (baseOpt, fields, _, _) ->
    let ctx = Option.fold (lcExpr rx) ctx baseOpt

    fields
    |> List.fold (fun ctx (_, init, _) -> lcExpr rx ctx init) ctx

  | TMatchExpr (cond, arms, _, _) ->
    let ctx = lcExpr rx ctx cond

    let branch, ctx = enterBranches ctx

    let branch, ctx =
      arms
      |> List.fold
           (fun (branch, ctx) (_, guard, body) ->
             let ctx = lcExpr rx ctx guard
             let ctx = lcExpr rx ctx body
             nextBranch rx branch (exprToLoc body) ctx)
           (branch, ctx)

    leaveBranches branch ctx

  | TNavExpr (l, _, _, _) -> lcExpr rx ctx l

  | TNodeExpr (_, args, _, _) -> lcExprs rx ctx args

  | TBlockExpr (stmts, last) ->
    let ctx = lcStmts rx ctx stmts
    lcExpr rx ctx last

let private lcExprs rx ctx exprs : LinearCheckCtx = exprs |> List.fold (lcExpr rx) ctx

let private lcStmt rx (ctx: LinearCheckCtx) stmt : LinearCheckCtx =
  match stmt with
  | TExprStmt expr -> lcExpr rx ctx expr

  | TLetValStmt (pat, init, _) ->
    let ctx = lcPat rx ctx pat
    lcExpr rx ctx init

  | TLetFunStmt (_, _, _, argPats, body, loc) ->
    let parent, ctx = enterBody ctx
    let ctx = argPats |> List.fold (lcPat rx) ctx
    let ctx = lcExpr rx ctx body
    leaveBody rx parent loc ctx

  | TBlockStmt (_, stmts) -> lcStmts rx ctx stmts

let private lcStmts rx ctx stmts : LinearCheckCtx = stmts |> List.fold (lcStmt rx) ctx

let private lcProgram linearTys (modules: TProgram) (tirCtx: TirCtx) : TirCtx =
  let ctx = { emptyCtx () with Logs = tirCtx.Logs }

  let ctx =
    modules
    |> List.fold
         (fun ctx (m: TModule) ->
           let rx = newRxForModule linearTys m tirCtx

           m.Stmts |> List.fold (lcStmt rx) ctx)
         ctx

  { tirCtx with Logs = ctx.Logs }

// -----------------------------------------------
// Rewrite
// -----------------------------------------------

// Remove linear primitives.

let private lwTy ty : Ty =
  let (Ty (tk, tyArgs)) = ty

  match tk with
  | LinearTk _ ->
    match tyArgs with
    | [ itemTy ] -> itemTy
    | _ -> unreachable ()

  | _ when List.isEmpty tyArgs -> ty
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

  | TNodeExpr (TAppEN, [ TPrimExpr (TPrim.Acquire, _, _); arg ], _, _) -> lwExpr arg
  | TNodeExpr (TAppEN, [ TPrimExpr (TPrim.Dispose, _, _); arg ], _, _) -> lwExpr arg

  | TNodeExpr (kind, args, ty, loc) -> TNodeExpr(kind, List.map lwExpr args, lwTy ty, loc)
  | TBlockExpr (stmts, last) -> TBlockExpr(List.map lwStmt stmts, lwExpr last)

let private lwStmt stmt : TStmt =
  match stmt with
  | TExprStmt expr -> TExprStmt(lwExpr expr)
  | TLetValStmt (pat, init, loc) -> TLetValStmt(lwPat pat, lwExpr init, loc)

  | TLetFunStmt (funSerial, isRec, vis, argPats, body, loc) ->
    TLetFunStmt(funSerial, isRec, vis, List.map lwPat argPats, lwExpr body, loc)

  | TBlockStmt (isRec, stmts) -> TBlockStmt(isRec, List.map lwStmt stmts)

let private lwProgram linearTys modules tirCtx =
  let modules =
    modules
    |> List.map (fun (m: TModule) ->
      let rx = newRxForModule linearTys m tirCtx

      { m with
          Vars =
            m.Vars
            |> TMap.map (fun _ (varDef: VarDef) ->
              if tyIsLinear rx varDef.Ty then
                { varDef with Ty = lwTy varDef.Ty }
              else
                varDef)
          Stmts = m.Stmts |> List.map lwStmt })

  let tirCtx =
    let rx = newRxForToplevel linearTys tirCtx

    { tirCtx with
        StaticVars =
          tirCtx.StaticVars
          |> TMap.map (fun _ (varDef: VarDef) ->
            if tyIsLinear rx varDef.Ty then
              { varDef with Ty = lwTy varDef.Ty }
            else
              varDef)
        Variants =
          tirCtx.Variants
          |> TMap.map (fun _ (variantDef: VariantDef) ->
            if rx.LinearTySet
               |> TSet.contains variantDef.UnionTySerial
               && tyIsLinear rx variantDef.PayloadTy then
              { variantDef with PayloadTy = lwTy variantDef.PayloadTy }
            else
              variantDef)
        Funs =
          tirCtx.Funs
          |> TMap.map (fun _ (funDef: FunDef) ->
            let (TyScheme (tyArgs, ty)) = funDef.Ty

            if List.isEmpty tyArgs && tyIsLinear rx ty then
              { funDef with Ty = TyScheme([], lwTy ty) }
            else
              funDef)
        Tys =
          tirCtx.Tys
          |> TMap.map (fun _ (tyDef: TyDef) ->
            match tyDef with
            | RecordTyDef (ident, tyArgs, fields, repr, loc) ->
              let fields =
                fields
                |> List.map (fun (ident, ty, loc) -> ident, lwTy ty, loc)

              RecordTyDef(ident, tyArgs, fields, repr, loc)

            | UnivTyDef _
            | SynonymTyDef _
            | UnionTyDef _ -> tyDef) }

  modules, tirCtx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let linearCheck (modules: TProgram, tirCtx: TirCtx) : TProgram * TirCtx =
  let linearTys = computeLinearTys tirCtx

  let tirCtx = lcDefs linearTys tirCtx
  let tirCtx = lcProgram linearTys modules tirCtx

  if tirCtx.Logs |> List.isEmpty then
    lwProgram linearTys modules tirCtx
  else
    modules, tirCtx
