/// ## Auto Boxing
///
/// Provides implicit indirection by inserting allocate/dereference operations.
module rec MiloneLang.AutoBoxing

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.Typing
open MiloneLang.Hir

let private tyIsRecord ty =
  match ty with
  | AppTy (RecordTyCtor _, _) -> true
  | _ -> false

let private hxBox itemExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) itemExpr tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) boxExpr itemTy loc

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private AbCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): AbCtx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  { tyCtx with
      Vars = ctx.Vars
      Variants = ctx.Variants
      Tys = ctx.Tys }

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
  | HVariantPat (_, variantTy, loc), [ payloadPat ] when tyIsFun variantTy ->
      // FIXME: ty is now wrong. ty is previously T -> U where U: union, T: payload, but now obj -> U.
      Some(HBoxPat(payloadPat, loc))

  | _ -> None

let private postProcessVariantFunAppExpr ctx infOp items =
  match infOp, items with
  | InfOp.App, [ (HVariantExpr _) as callee; payload ] ->
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

let private eraseRecordTy () = tyObj

let private postProcessRecordExpr baseOpt fields recordTy loc =
  let baseOpt =
    baseOpt
    |> Option.map (fun expr -> hxUnbox expr recordTy loc)

  let recordExpr =
    HRecordExpr(baseOpt, fields, recordTy, loc)

  hxBox recordExpr recordTy loc

let private postProcessFieldExpr recordExpr recordTy fieldName fieldTy loc =
  assert (recordExpr |> exprToTy |> tyEq tyObj)

  HNavExpr(hxUnbox recordExpr recordTy loc, fieldName, fieldTy, loc)

// -----------------------------------------------
// Control
// -----------------------------------------------

let private abTy ctx ty =
  match ty with
  | AppTy (RecordTyCtor _, _) -> eraseRecordTy ()

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
  | HRefPat _
  | HVariantPat _ -> pat |> patMap (abTy ctx) id

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
        assert (tyIsRecord ty)

        let baseOpt = baseOpt |> Option.map (abExpr ctx)

        let fields =
          fields
          |> List.map (fun (name, init, loc) ->
               let init = init |> abExpr ctx
               name, init, loc)

        postProcessRecordExpr baseOpt fields ty loc

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = l |> exprToTy
        assert (tyIsRecord recordTy)

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
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr |> exprMap (abTy ctx) id

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond = cond |> abExpr ctx

        let go (pat, guard, body) =
          let pat = pat |> abPat ctx
          let guard = guard |> abExpr ctx
          let body = body |> abExpr ctx
          pat, guard, body

        let arms = arms |> List.map go
        let ty = ty |> abTy ctx
        HMatchExpr(cond, arms, ty, loc)

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
         | VarDef (name, sm, ty, loc) ->
             let ty = ty |> abTy ctx
             VarDef(name, sm, ty, loc))

  let funs =
    ctx.Funs
    |> mapMap (fun _ (funDef: FunDef) ->
         let (TyScheme (tyVars, ty)) = funDef.Ty
         let ty = ty |> abTy ctx
         { funDef with
             Ty = TyScheme(tyVars, ty) })

  let variants =
    ctx.Variants
    |> mapMap (fun _ (variantDef: VariantDef) ->
         { variantDef with
             PayloadTy = tyObj
             VariantTy = variantDef.VariantTy |> abTy ctx })

  let tys =
    ctx.Tys
    |> mapMap (fun _ tyDef ->
         match tyDef with
         | SynonymTyDef (name, tyArgs, bodyTy, loc) ->
             let bodyTy = bodyTy |> abTy ctx
             SynonymTyDef(name, tyArgs, bodyTy, loc)

         | RecordTyDef (recordName, fields, loc) ->
             let fields =
               fields
               |> List.map (fun (name, ty, loc) ->
                    let ty = ty |> abTy ctx
                    name, ty, loc)

             RecordTyDef(recordName, fields, loc)

         | _ -> tyDef)

  let ctx =
    { ctx with
        Vars = vars
        Funs = funs
        Variants = variants
        Tys = tys }

  let expr = expr |> abExpr ctx

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
