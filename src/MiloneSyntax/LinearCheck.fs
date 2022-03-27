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

// -----------------------------------------------
// Context
// -----------------------------------------------

let private emptySet: TreeSet<VarSerial> = TSet.empty varSerialCompare

/// varSerial -> (true = owned | false = disposed)
type private OwnershipMap = TreeMap<VarSerial, bool>

let private emptyMap: OwnershipMap = TMap.empty varSerialCompare

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Rx =
  { GetVarName: VarSerial -> string
    GetVarLoc: VarSerial -> Loc
    LinearTySet: TreeSet<TySerial> }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LinearCheckCtx =
  { Parent: OwnershipMap
    Current: OwnershipMap
    Used: TreeSet<VarSerial>
    Logs: (Log * Loc) list }

let private emptyCtx () : LinearCheckCtx =
  { Parent = emptyMap
    Current = emptyMap
    Used = emptySet
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

// -----------------------------------------------
// Control
// -----------------------------------------------

let private markAsDefined (ctx: LinearCheckCtx) varSerial : LinearCheckCtx =
  { ctx with Current = ctx.Current |> TMap.add varSerial true }

let private markAsUsed (ctx: LinearCheckCtx) varSerial loc : LinearCheckCtx =
  match ctx.Parent |> TMap.tryFind varSerial with
  | Some true -> { ctx with Used = ctx.Used |> TSet.add varSerial }
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
    Used: TreeSet<VarSerial>

    // The set of variables
    //    that are defined outside the branches
    //    and used in the first branch.
    PrevOpt: TreeSet<VarSerial> option }

let private enterBranches (ctx: LinearCheckCtx) =
  let branch: Branch =
    { Parent = ctx.Parent
      Current = ctx.Current
      Used = ctx.Used
      PrevOpt = None }

  // Merge current and used into parent. this could be more efficient by improving data structure
  let parent =
    ctx.Used
    |> TSet.fold (fun parent varSerial -> parent |> TMap.add varSerial false) ctx.Parent

  let parent =
    ctx.Current
    |> TMap.fold (fun parent varSerial owned -> parent |> TMap.add varSerial owned) parent

  let ctx =
    { ctx with
        Parent = parent
        Current = emptyMap
        Used = emptySet }

  branch, ctx

let private nextBranch (rx: Rx) (branch: Branch) (ctx: LinearCheckCtx) =
  // All variables that are defined in the branch must be disposed.
  let ctx =
    let logs =
      ctx.Current
      |> TMap.fold
           (fun logs varSerial owned ->
             if owned then
               let log =
                 Log.Error(errorToString LinearError.VariableNotUsed)

               let loc = rx.GetVarLoc varSerial
               (log, loc) :: logs
             else
               logs)
           ctx.Logs

    { ctx with
        Current = emptyMap
        Logs = logs }

  // All variables that are disposed in the previous branch must be disposed
  // and others must not be disposed.
  let ctx =
    match branch.PrevOpt with
    | Some prev ->
      let logs =
        ctx.Used
        |> TSet.fold
             (fun logs varSerial ->
               if prev |> TSet.contains varSerial |> not then
                 let log =
                   Log.Error(errorToString LinearError.VariableCannotBeUsed)
                 // location is incorrect. Used should contain loc
                 let loc = rx.GetVarLoc varSerial
                 (log, loc) :: logs
               else
                 logs)
             ctx.Logs

      let logs =
        let unused =
          prev
          |> TSet.fold
               (fun acc varSerial ->
                 if ctx.Used |> TSet.contains varSerial |> not then
                   varSerial :: acc
                 else
                   acc)
               []

        if unused |> List.isEmpty |> not then
          let names = unused |> List.map rx.GetVarName

          let log =
            Log.Error(errorToString (LinearError.BranchMustUse names))

          let loc = noLoc // FIXME: location of branch
          (log, loc) :: logs
        else
          logs

      { ctx with Logs = logs }

    | None -> ctx

  let branch =
    if branch.PrevOpt |> Option.isNone then
      { branch with PrevOpt = Some ctx.Used }
    else
      branch

  branch, ctx

let private leaveBranches (branch: Branch) (ctx: LinearCheckCtx) : LinearCheckCtx =
  // Propagate "used" marks to the parent branch.
  let current, used =
    let branchUsed =
      branch.PrevOpt |> Option.defaultValue emptySet

    branchUsed
    |> TSet.fold
         (fun (current, used) varSerial ->
           match branch.Current |> TMap.tryFind varSerial with
           | Some owned ->
             assert owned
             current |> TMap.add varSerial false, used

           | None -> current, used |> TSet.add varSerial)
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

let private leaveBody rx (branch: Branch) (ctx: LinearCheckCtx) : LinearCheckCtx =
  let branch, ctx = nextBranch rx branch ctx
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
  | TFunExpr _
  | TVariantExpr _
  | TPrimExpr _ -> ctx

  | TVarExpr (varSerial, ty, loc) ->
    if tyIsLinear rx ty then
      markAsUsed ctx varSerial loc
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
             nextBranch rx branch ctx)
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

  | TLetFunStmt (_, _, _, argPats, body, _) ->
    let parent, ctx = enterBody ctx
    let ctx = argPats |> List.fold (lcPat rx) ctx
    let ctx = lcExpr rx ctx body
    leaveBody rx parent ctx

  | TBlockStmt (_, stmts) -> lcStmts rx ctx stmts

let private lcStmts rx ctx stmts : LinearCheckCtx = stmts |> List.fold (lcStmt rx) ctx

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

// -----------------------------------------------
// Interface
// -----------------------------------------------

let linearCheck (modules: TProgram, tirCtx: TirCtx) : TProgram * TirCtx =
  let ctx = { emptyCtx () with Logs = tirCtx.Logs }

  let emptyLinearTySet = TSet.empty compare

  // FIXME: Union types that own __linear directly are linear for now.
  //        This should be transitive.
  let linearTys =
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

  let makeRxGlobal () : Rx =
    let findVar varSerial = tirCtx.StaticVars |> mapFind varSerial

    let rx: Rx =
      { GetVarName = fun varSerial -> (findVar varSerial).Name
        GetVarLoc = fun varSerial -> (findVar varSerial).Loc
        LinearTySet = linearTys }

    rx

  let makeRx (m: TModule) : Rx =
    let findVar varSerial =
      match m.Vars |> TMap.tryFind varSerial with
      | Some v -> v
      | None -> tirCtx.StaticVars |> mapFind varSerial

    let rx: Rx =
      { GetVarName = fun varSerial -> (findVar varSerial).Name
        GetVarLoc = fun varSerial -> (findVar varSerial).Loc
        LinearTySet = linearTys }

    rx

  let ctx =
    modules
    |> List.fold
         (fun ctx (m: TModule) ->
           let rx = makeRx m

           m.Stmts |> List.fold (lcStmt rx) ctx)
         ctx

  // Remove linear primitives.
  let modules =
    modules
    |> List.map (fun (m: TModule) ->
      let rx = makeRx m

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
    let rx = makeRxGlobal ()

    // Not updating Tys since record types can't be linear for now.
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
              funDef) }

  modules, { tirCtx with Logs = ctx.Logs }
