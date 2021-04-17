module rec MiloneSyntax.ArityCheck

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.Tir
open MiloneSyntax.Typing
open MiloneSyntax.TySystem

module StdInt = MiloneStd.StdInt
module S = MiloneStd.StdString
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

// -----------------------------------------------
// ArityEx
// -----------------------------------------------

/// Arity extended.
///
/// This is similar to type, but ignores non-function types to unit type
/// and handles arity of functions.
[<NoEquality; NoComparison>]
type private ArityEx =
  /// Arity of non-function value.
  | UnitAx

  /// Arity of hungry function.
  | HungryAx

  /// Arity of function.
  | FunAx of args: ArityEx list * result: ArityEx

let private arityExIsUnifiable l r =
  let rec go (l, r) =
    match l, r with
    | HungryAx, _
    | _, HungryAx -> true

    | UnitAx, UnitAx -> true

    | FunAx (ls, lt), FunAx (rs, rt) ->
        let zipped, lRest, rRest = listTryZip ls rs

        List.isEmpty lRest
        && List.isEmpty rRest
        && List.forall go zipped
        && go (lt, rt)

    | UnitAx, _
    | FunAx _, _ -> false

  go (l, r)

let private arityExToString a =
  match a with
  | UnitAx -> "_"
  | HungryAx -> "*"

  | FunAx (args, result) ->
      "("
      + (args |> List.map arityExToString |> S.concat ", ")
      + ") -> "
      + arityExToString result

let private tyToArityEx ty =
  let rec goFun ty =
    match ty with
    | Ty (FunTk, [ sTy; tTy ]) ->
        let sTy = tyToArityEx sTy
        let args, result = goFun tTy
        sTy :: args, result

    | _ -> [], UnitAx

  let args, result = goFun ty

  if List.isEmpty args then
    result
  else
    FunAx(args, result)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ArityCheckCtx =
  { GetFunArity: FunSerial -> ArityEx
    Errors: (string * string * Loc) list }

let private addArityError actual expected (loc: Loc) (ctx: ArityCheckCtx) =
  { ctx with
      Errors = (actual, expected, loc) :: ctx.Errors }

let private acExprChecked expr ctx =
  let expected = tyToArityEx (exprToTy expr)
  let actual, ctx = acExpr (expr, ctx)

  if arityExIsUnifiable actual expected |> not then
    ctx
    |> addArityError (arityExToString actual) (arityExToString expected) (exprToLoc expr)
  else
    ctx

// -----------------------------------------------
// Control
// -----------------------------------------------

let private acExpr (expr, ctx: ArityCheckCtx) : ArityEx * ArityCheckCtx =
  match expr with
  | TLitExpr _
  | TTyDeclExpr _
  | TOpenExpr _ -> UnitAx, ctx

  | TVarExpr (_, ty, _) -> tyToArityEx ty, ctx
  | TVariantExpr (_, ty, _) -> tyToArityEx ty, ctx
  | TPrimExpr (_, ty, _) -> tyToArityEx ty, ctx

  | TFunExpr (funSerial, _, _) -> ctx.GetFunArity funSerial, ctx

  | TRecordExpr (baseOpt, fields, _, _) ->
      invoke
        (fun () ->
          let ctx =
            match baseOpt with
            | Some baseExpr -> acExpr (baseExpr, ctx) |> snd
            | None -> ctx

          let ctx =
            fields
            |> List.fold (fun ctx (_, init, _) -> acExprChecked init ctx) ctx

          UnitAx, ctx)

  | TMatchExpr (cond, arms, ty, _) ->
      invoke
        (fun () ->
          let _, ctx = acExpr (cond, ctx)

          let ctx =
            arms
            |> List.fold
                 (fun ctx (_, guard, body) ->
                   let _, ctx = acExpr (guard, ctx)
                   acExprChecked body ctx)
                 ctx

          tyToArityEx ty, ctx)

  | TNavExpr (l, _, ty, _) ->
      let _, ctx = acExpr (l, ctx)
      tyToArityEx ty, ctx

  | TNodeExpr (TAppEN, [ callee; arg ], ty, loc) ->
      let calleeArity, ctx = acExpr (callee, ctx)
      let argArity, ctx = acExpr (arg, ctx)

      match calleeArity with
      | HungryAx -> HungryAx, ctx

      | FunAx (a :: args, result) when arityExIsUnifiable a argArity ->
          if List.isEmpty args then
            tyToArityEx ty, ctx
          else
            FunAx(args, result), ctx

      | _ ->
          let expected =
            "(" + arityExToString argArity + ", ..) -> .."

          let ctx =
            addArityError (arityExToString calleeArity) expected loc ctx

          tyToArityEx ty, ctx

  | TNodeExpr (_, items, ty, _) ->
      let ctx = acExprs items ctx
      tyToArityEx ty, ctx

  | TBlockExpr (stmts, last) ->
      let ctx = acExprs stmts ctx
      acExpr (last, ctx)

  | TLetValExpr (_, init, next, _, _) ->
      let ctx = acExprChecked init ctx
      acExpr (next, ctx)

  | TLetFunExpr (_, _, _, _, body, next, _, _) ->
      let ctx = acExprChecked body ctx
      acExpr (next, ctx)

  | TModuleExpr _
  | TModuleSynonymExpr _ -> unreachable () // Resolved in NameRes.

let private acExprs exprs ctx =
  exprs
  |> List.fold (fun ctx expr -> acExpr (expr, ctx) |> snd) ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let arityCheck (modules: TProgram, tyCtx: Typing.TyCtx) : Typing.TyCtx =
  let ctx : ArityCheckCtx =
    { GetFunArity =
        fun funSerial ->
          let funDef = tyCtx.Funs |> mapFind funSerial

          // HACK: failwithf can take any number of arguments.
          if funDef.Name = "failwithf" then
            HungryAx
          else
            let (TyScheme (_, ty)) = funDef.Ty

            let _, args, result = ty |> tyToArgList

            let args, otherArgs =
              List.truncate funDef.Arity args, List.skip funDef.Arity args

            let result =
              otherArgs
              |> List.rev
              |> List.fold (fun a result -> tyFun a result) result

            let args = List.map tyToArityEx args
            let result = tyToArityEx result
            FunAx(args, result)

      Errors = [] }

  let ctx =
    modules
    |> hirProgramFoldExpr
         (fun (expr, ctx) ->
           let _, ctx = acExpr (expr, ctx)
           ctx)
         ctx

  let logs =
    ctx.Errors
    |> List.map (fun (actual, expected, loc) -> Log.ArityMismatch(actual, expected), loc)

  { tyCtx with
      Logs = List.append tyCtx.Logs logs }
