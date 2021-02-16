module rec MiloneLang.DeriveRecordOps

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLang.Typing

type XExpr =
  | XArgExpr of int
  | XRecordExpr of TySerial * fields: (string * XExpr * Loc) list * Loc

type XFunDef =
  { Name: string
    Args: (string * Ty * Loc) list
    ResultTy: Ty
    Body: XExpr
    Loc: Loc }

let private exprToHir (args: (VarSerial * Ty * Loc) list) (expr: XExpr): HExpr =
  match expr with
  | XArgExpr i ->
      match List.tryItem i args with
      | Some (varSerial, ty, loc) -> HVarExpr(varSerial, ty, loc)
      | None -> failwith "NEVER"

  | XRecordExpr (tySerial, fields, loc) ->
      let fields =
        fields
        |> List.map (fun (name, init, loc) -> name, exprToHir args init, loc)

      HRecordExpr(None, fields, tyRecord tySerial, loc)

let private funDefToHir (funDef: XFunDef) (ctx: TyCtx): (HExpr -> HExpr) * TyCtx =
  let funSerial, serial =
    FunSerial(ctx.Serial + 1), ctx.Serial + 1

  let arity, serial, argAcc, vars =
    funDef.Args
    |> List.fold
         (fun (i, serial, argAcc, vars) (name, ty, loc) ->
           let serial = serial + 1

           let argAcc = (VarSerial serial, ty, loc) :: argAcc

           let vars =
             vars
             |> mapAdd (VarSerial serial) (VarDef(name, AutoSM, ty, loc))

           i + 1, serial, argAcc, vars)
         (0, serial, [], ctx.Vars)

  let args = List.rev argAcc

  let ctx =
    let funTy =
      funDef.Args
      |> List.rev
      |> List.fold (fun funTy (_, ty, _) -> tyFun ty funTy) funDef.ResultTy

    let funDef: FunDef =
      { Name = funDef.Name
        Arity = arity
        Ty = TyScheme([], funTy)
        Abi = CAbi
        Loc = funDef.Loc }

    { ctx with
        Serial = serial
        Vars = vars
        Funs = ctx.Funs |> mapAdd funSerial funDef }

  let letExpr next =
    let nextTy = exprToTy next
    let argPats = List.map (fun (varSerial, ty, loc) -> HVarPat(varSerial, ty, loc)) args
    let body = exprToHir args funDef.Body
    HLetFunExpr(funSerial, IsRec, PublicVis, argPats, body, next, nextTy, funDef.Loc)

  letExpr, ctx

let private recordNewFun (tySerial: TySerial) (tyDef: TyDef): XFunDef =
  let ident, fields, loc =
    match tyDef with
    | RecordTyDef (ident, fields, loc) -> ident, fields, loc
    | _ -> failwithf "NEVER"

  let body =
    let args =
      List.mapi (fun i (name, _, loc) -> name, XArgExpr i, loc) fields

    XRecordExpr(tySerial, args, loc)

  { Name = ident + "_new"
    Args = fields
    ResultTy = tyRecord tySerial
    Body = body
    Loc = loc }

let deriveRecordOps (expr: HExpr, tyCtx: TyCtx): HExpr * TyCtx =
  let funDefs =
    tyCtx.Tys
    |> mapFold
         (fun funDefs tySerial tyDef ->
           match tyDef with
           | RecordTyDef _ -> recordNewFun tySerial tyDef :: funDefs
           | _ -> funDefs)
         []

  funDefs
  |> List.fold
       (fun (expr, tyCtx) funDef ->
         let letExpr, tyCtx = funDefToHir funDef tyCtx
         letExpr expr, tyCtx)
       (expr, tyCtx)
