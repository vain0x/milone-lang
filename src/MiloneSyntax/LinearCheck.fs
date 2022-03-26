module rec MiloneSyntax.LinearCheck

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

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Rx = { LinearTys: Serial -> bool }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LinearCheckCtx =
  { Parent: TreeMap<VarSerial, bool>
    Current: TreeMap<VarSerial, bool>
    Used: TreeSet<VarSerial>
    Logs: (Log * Loc) list }

let private emptyCtx () : LinearCheckCtx =
  { Parent = TMap.empty varSerialCompare
    Current = TMap.empty varSerialCompare
    Used = TSet.empty varSerialCompare
    Logs = [] }

// -----------------------------------------------
// Error
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private LinearError =
  | TypeCannotBeLinear
  | NotUsed
  | AlreadyUsed
  | CannotBeCaptured

let private errorToString err =
  match err with
  | LinearError.TypeCannotBeLinear ->
    "This type can't contain __linear type. Currently, tuple, list and discriminated union types can contain __linear types."

  | LinearError.NotUsed ->
    "This value is not used. Consider to use a drop function. (This value is linear type and must be used exactly-once.)"

  | LinearError.AlreadyUsed ->
    "This value is already used and cannot be used here. (This value is linear type and must be used exactly-once.)"

  | LinearError.CannotBeCaptured ->
    "This value is already used and cannot be used here. (This value is linear type and must be used exactly-once.)"

let private addError err (loc: Loc) (ctx: LinearCheckCtx) =
  { ctx with Logs = (Log.Error(errorToString err), loc) :: ctx.Logs }

// -----------------------------------------------
// Types
// -----------------------------------------------

let private tyIsLinear (rx: Rx) ty =
  match ty with
  | Ty (LinearTk, _) -> true
  | _ -> false

// -----------------------------------------------
// Control
// -----------------------------------------------

let private markAsUsed (ctx: LinearCheckCtx) varSerial loc =
  match ctx.Parent |> TMap.tryFind varSerial with
  | Some true -> addError LinearError.AlreadyUsed loc ctx
  | Some false -> { ctx with Used = ctx.Used |> TSet.add varSerial }
  | None ->
    match ctx.Current |> TMap.tryFind varSerial with
    | Some true -> addError LinearError.AlreadyUsed loc ctx
    | Some false -> { ctx with Current = ctx.Current |> TMap.add varSerial true }
    | None ->
      unreachable (
        "var not defined "
        + string (varSerialToInt varSerial)
        + " at "
        + Loc.toString loc
      )

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

  | TMatchExpr (cond, arms, ty, _) ->
    let ctx = lcExpr rx ctx cond

    arms
    |> List.fold
         (fun ctx (_, guard, body) ->
           let ctx = lcExpr rx ctx guard
           lcExpr rx ctx body)
         ctx

  | TNavExpr (l, _, _, _) -> lcExpr rx ctx l

  | TNodeExpr (TAppEN, [ callee; arg ], ty, loc) -> todo ()

  | TNodeExpr (_, args, _, _) -> lcExprs rx ctx args

  | TBlockExpr (stmts, last) ->
    let ctx = lcStmts rx ctx stmts
    lcExpr rx ctx last

let private lcExprs rx ctx exprs : LinearCheckCtx =
  exprs
  |> List.fold (fun ctx expr -> lcExpr rx ctx expr) ctx

let private lcStmt rx (ctx: LinearCheckCtx) stmt : LinearCheckCtx =
  match stmt with
  | TExprStmt expr -> lcExpr rx ctx expr
  | TLetValStmt (_, init, _) -> lcExpr rx ctx init
  | TLetFunStmt (_, _, _, _, body, _) -> lcExpr rx ctx body
  | TBlockStmt (_, stmts) -> lcStmts rx ctx stmts

let private lcStmts rx ctx stmts =
  stmts
  |> List.fold (fun ctx stmt -> lcStmt rx ctx stmt) ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let linearCheck (modules: TProgram, tirCtx: TirCtx) : TirCtx =
  let ctx = { emptyCtx () with Logs = tirCtx.Logs }

  let rx: Rx = todo ()

  let ctx =
    modules
    |> TProgram.foldStmt (fun ctx stmt -> lcStmt rx ctx stmt) ctx

  { tirCtx with Logs = ctx.Logs }
