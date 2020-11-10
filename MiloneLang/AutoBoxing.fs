/// ## Auto Boxing
///
/// Provide implicit indirection by inserting allocate/dereference operations.
module rec MiloneLang.AutoBoxing

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Records

type private AbCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): AbCtx =
  { Vars = tyCtx |> tyCtxGetVars
    Tys = tyCtx |> tyCtxGetTys }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  tyCtx
  |> tyCtxWithVars ctx.Vars
  |> tyCtxWithTys ctx.Tys

/// ### Boxing of Records
///
/// Records are all boxed because they tend to be too large to clone.
///
/// (Ideally, we should measure size of record types and suppress auto-box for small records.)
///
/// ```fsharp
///   // Record creation.
///   { fields... }: R
///   // =>
///   box { fields... }: obj
///
///   // Record mutation.
///   { record with fields... }: R
///   // =>
///   box { unbox record with fields... }: obj
///
///   // Field projection.
///   (record: R).field
///   // =>
///   (unbox record).field
///
///   // Def/use of record-type pat/expr.
///   record: R
///   // =>
///   record: obj
/// ```

let private isRecordTySerial (ctx: AbCtx) tySerial =
  match ctx.Tys |> mapTryFind tySerial with
  | Some (RecordTyDef _) -> true
  | _ -> false

let private isRecordTy ctx ty =
  match ty with
  | AppTy (RefTyCtor tySerial, _) -> tySerial |> isRecordTySerial ctx
  | _ -> false

let private eraseRecordTy ctx tySerial =
  if tySerial |> isRecordTySerial ctx then Some tyObj else None

let private hxBox itemExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) itemExpr tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) boxExpr itemTy loc

let private postProcessRecordExpr baseOpt fields recordTy loc =
  let baseOpt =
    baseOpt
    |> optionMap (fun expr -> hxUnbox expr recordTy loc)

  let recordExpr =
    HRecordExpr(baseOpt, fields, recordTy, loc)

  hxBox recordExpr recordTy loc

let private postProcessFieldExpr recordExpr recordTy fieldIdent fieldTy loc =
  assert (recordExpr |> exprToTy |> tyEq tyObj)

  HNavExpr(hxUnbox recordExpr recordTy loc, fieldIdent, fieldTy, loc)

// -----------------------------------------------
// Control
// -----------------------------------------------

let private abTy ctx ty =
  match ty with
  | AppTy (RefTyCtor tySerial, []) ->
      match eraseRecordTy ctx tySerial with
      | Some ty -> ty
      | None -> ty

  | AppTy (tyCtor, tyArgs) ->
      let tyArgs = tyArgs |> listMap (abTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private abPat ctx pat = pat |> patMap (abTy ctx) id

let private abExpr ctx expr =
  match expr with
  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        assert (ty |> isRecordTy ctx)

        let baseOpt = baseOpt |> optionMap (abExpr ctx)

        let fields =
          fields
          |> listMap (fun (ident, init, loc) ->
               let init = init |> abExpr ctx
               ident, init, loc)

        postProcessRecordExpr baseOpt fields ty loc

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = l |> exprToTy
        assert (recordTy |> isRecordTy ctx)

        let l = l |> abExpr ctx
        let ty = ty |> abTy ctx
        postProcessFieldExpr l recordTy r ty loc

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HRefExpr _
  | HPrimExpr _ -> expr |> exprMap (abTy ctx) id

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target = target |> abExpr ctx

        let go (pat, guard, body) =
          let pat = pat |> abPat ctx
          let guard = guard |> abExpr ctx
          let body = body |> abExpr ctx
          pat, guard, body

        let arms = arms |> listMap go
        let ty = ty |> abTy ctx
        HMatchExpr(target, arms, ty, loc)

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items = items |> listMap (abExpr ctx)
        let ty = ty |> abTy ctx
        HInfExpr(infOp, items, ty, loc)

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat = pat |> abPat ctx
        let init = init |> abExpr ctx
        let next = next |> abExpr ctx
        let ty = ty |> abTy ctx
        HLetValExpr(vis, pat, init, next, ty, loc)

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let args = args |> listMap (abPat ctx)
        let body = body |> abExpr ctx
        let next = next |> abExpr ctx
        let ty = ty |> abTy ctx
        HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "NEVER: %A" (error, loc)
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let autoBox (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  let vars =
    ctx.Vars
    |> mapMap (fun _ varDef ->
         match varDef with
         | VarDef (ident, sm, ty, loc) ->
             let ty = ty |> abTy ctx
             VarDef(ident, sm, ty, loc)

         | FunDef (ident, arity, TyScheme (tyArgs, ty), loc) ->
             let ty = ty |> abTy ctx
             FunDef(ident, arity, TyScheme(tyArgs, ty), loc)

         | VariantDef (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
             let payloadTy = payloadTy |> abTy ctx
             let variantTy = variantTy |> abTy ctx
             VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc))

  let tys =
    ctx.Tys
    |> mapMap (fun _ tyDef ->
         match tyDef with
         | RecordTyDef (ident, fields, loc) ->
             let fields =
               fields
               |> listMap (fun (ident, ty, loc) ->
                    let ty = ty |> abTy ctx
                    ident, ty, loc)

             RecordTyDef(ident, fields, loc)

         | _ -> tyDef)

  let ctx = { ctx with Vars = vars; Tys = tys }

  let expr = expr |> abExpr ctx

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
