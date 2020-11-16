/// ## Auto Boxing
///
/// Provides implicit indirection by inserting allocate/dereference operations.
module rec MiloneLang.AutoBoxing

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.TySystem
open MiloneLang.Typing

let private hxBox itemExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) itemExpr tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) boxExpr itemTy loc

// -----------------------------------------------
// Context
// -----------------------------------------------

type private AbCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): AbCtx = { Vars = tyCtx.Vars; Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  { tyCtx with
      Vars = ctx.Vars
      Tys = ctx.Tys }

let private isVariantFun (ctx: AbCtx) varSerial =
  match ctx.Vars |> mapTryFind varSerial with
  | Some (VariantDef (_, _, hasPayload, _, _, _)) -> hasPayload
  | _ -> false

/// ### Boxing of Payloads
///
/// Payload of variants are all boxed so that they can be recursive.
///
/// (Ideally, we should measure size of them and suppress auto-boxing for small variants.)
///
/// ```fsharp
///   // Variant creation. K is a variant that has payload.
///   K payload
///   // =>
///   K (box payload)
///
///   // Variant decomposition. x is a variable defined in the pattern.
///   K payloadPat
///   // =>
///   K (box payloadPat)  // using box pattern to unbox the payload
/// ```

let private postProcessVariantCallPat ctx calleePat argPats =
  match calleePat, argPats with
  | HRefPat (varSerial, _, loc), [ payloadPat ] when varSerial |> isVariantFun ctx ->
      // FIXME: ty is now wrong. ty is previously T -> U where U: union, T: payload, but now obj -> U.
      Some(HBoxPat(payloadPat, loc))

  | _ -> None

let private postProcessVariantFunAppExpr ctx infOp items =
  match infOp, items with
  | InfOp.App, [ (HRefExpr (varSerial, _, _)) as callee; payload ] when varSerial |> isVariantFun ctx ->
      // FIXME: ty is now wrong for the same reason as call-variant pattern.
      let ty, loc = exprExtract payload
      Some(callee, hxBox payload ty loc)

  | _ -> None

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

let private postProcessRecordExpr baseOpt fields recordTy loc =
  let baseOpt =
    baseOpt
    |> Option.map (fun expr -> hxUnbox expr recordTy loc)

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
      let tyArgs = tyArgs |> List.map (abTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private abPat ctx pat =
  match pat with
  | HLitPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _
  | HDiscardPat _
  | HRefPat _ -> pat |> patMap (abTy ctx) id

  | HCallPat (calleePat, argPats, ty, loc) ->
      let calleePat = calleePat |> abPat ctx
      let argPats = argPats |> List.map (abPat ctx)
      let ty = ty |> abTy ctx

      match postProcessVariantCallPat ctx calleePat argPats with
      | Some payloadPat -> HCallPat(calleePat, [ payloadPat ], ty, loc)
      | None -> HCallPat(calleePat, argPats, ty, loc)

  | HConsPat (l, r, itemTy, loc) ->
      let l = l |> abPat ctx
      let r = r |> abPat ctx
      let itemTy = itemTy |> abTy ctx
      HConsPat(l, r, itemTy, loc)

  | HTuplePat (itemPats, tupleTy, loc) ->
      let itemPats = itemPats |> List.map (abPat ctx)
      let tupleTy = tupleTy |> abTy ctx
      HTuplePat(itemPats, tupleTy, loc)

  | HAsPat (bodyPat, varSerial, loc) ->
      let bodyPat = bodyPat |> abPat ctx
      HAsPat(bodyPat, varSerial, loc)

  | HOrPat (l, r, ty, loc) ->
      let l = l |> abPat ctx
      let r = r |> abPat ctx
      let ty = ty |> abTy ctx
      HOrPat(l, r, ty, loc)

  | HBoxPat _ -> failwithf "NEVER: HBoxPat is only generated in AutoBoxing. %A" pat
  | HNavPat _ -> failwithf "NEVER: HNavPat is resolved in NameRes. %A" pat
  | HAnnoPat _ -> failwithf "NEVER: HAnnoPat is resolved in Typing. %A" pat

let private abExpr ctx expr =
  match expr with
  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        assert (ty |> isRecordTy ctx)

        let baseOpt = baseOpt |> Option.map (abExpr ctx)

        let fields =
          fields
          |> List.map (fun (ident, init, loc) ->
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

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items = items |> List.map (abExpr ctx)
        let ty = ty |> abTy ctx

        match postProcessVariantFunAppExpr ctx infOp items with
        | Some (callee, payload) -> hxApp callee payload ty loc
        | None -> HInfExpr(infOp, items, ty, loc)

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

        let arms = arms |> List.map go
        let ty = ty |> abTy ctx
        HMatchExpr(target, arms, ty, loc)

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
        let args = args |> List.map (abPat ctx)
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

         | VariantDef (ident, tySerial, hasPayload, _payloadTy, variantTy, loc) ->
            //  let payloadTy = payloadTy |> abTy ctx
             let payloadTy = tyObj
             let variantTy = variantTy |> abTy ctx
             VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc))

  let tys =
    ctx.Tys
    |> mapMap (fun _ tyDef ->
         match tyDef with
         | SynonymTyDef (ident, tyArgs, bodyTy, loc) ->
             let bodyTy = bodyTy |> abTy ctx
             SynonymTyDef(ident, tyArgs, bodyTy, loc)

         | RecordTyDef (ident, fields, loc) ->
             let fields =
               fields
               |> List.map (fun (ident, ty, loc) ->
                    let ty = ty |> abTy ctx
                    ident, ty, loc)

             RecordTyDef(ident, fields, loc)

         | _ -> tyDef)

  let ctx = { ctx with Vars = vars; Tys = tys }

  let expr = expr |> abExpr ctx

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
