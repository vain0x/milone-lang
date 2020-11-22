/// # TyElaborating
///
/// Converts some of types to other types.
///
/// - Record types
/// - Newtype variants (discriminated union type with exactly-one variant)
module rec MiloneLang.TyElaborating

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.Typing

let private hxIsUnboxingRef expr =
  match expr with
  | HInfExpr (InfOp.App, [ HPrimExpr (HPrim.Unbox, _, _); HRefExpr _ ], _, _) -> true
  | _ -> false

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private TyElaborationCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>
    RecordTys: AssocMap<RecordTySerial, RecordTyDef>

    /// recordTySerial -> (tupleTy, (field -> fieldIndex, fieldTy))
    RecordMap: AssocMap<RecordTySerial, (Ty * AssocMap<Ident, int * Ty>)> }

let private ofTyCtx (tyCtx: TyCtx): TyElaborationCtx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    RecordTys = tyCtx.RecordTys
    RecordMap = mapEmpty recordTySerialCmp }

let private toTyCtx (tyCtx: TyCtx) (ctx: TyElaborationCtx): TyCtx =
  { tyCtx with
      Vars = ctx.Vars
      Tys = ctx.Tys }

/// ## Records to Tuples
///
/// Field names are unnecessary for code generation.
/// Records are equivalent to tuples except for ordering of fields.
///
/// ### Conversions
///
/// This stage replaces production and consumption of records with that of tuples,
/// sorting fields in the order of declaration.
///
/// Record type:
///
/// ```fsharp
/// // Assume type R = { F1: T1; F2: T2 } is defined.
///   R
/// //=>
///   T1 * T2
/// ```
///
/// Occurrences of record types are replaced with a tuple type,
/// which consists of field types.
///
/// Record creation:
///
/// ```fsharp
///   {
///     F2 = t2
///     F1 = t1
///   }: R
/// //=>
///   (t1, t2): T1 * T2
/// ```
///
/// Since record creation is checked in Typing that
/// fields are exhaustively specified; we just sort them.
///
/// Record mutation:
///
/// ```fsharp
///   { r with
///       Fi = ti
///       ...
///   }: R
/// //=>
///   (r.1, r.2, ..., ti, ...): (T1 * T2 * ...)
/// ```
///
/// Conversion of record mutation is similar to record creation
/// but some of fields are unspecified.
/// For such fields, reuse base record's value.

let private buildRecordMap (ctx: TyElaborationCtx) =
  assert (ctx.RecordMap |> mapIsEmpty)

  ctx.RecordTys
  |> mapFold (fun acc tySerial (tyDef: RecordTyDef) ->
       let fields =
         tyDef.Fields
         |> List.map (fun (name, ty, loc) ->
              // This affects newtype variants only.
              let ty = ty |> teTy ctx
              name, ty, loc)

       let tupleTy =
         fields
         |> List.map (fun (_, ty, _) -> ty)
         |> tyTuple

       let fieldMap =
         fields
         |> List.mapi (fun i (name, ty, _) -> name, (i, ty))
         |> mapOfList strCmp

       acc |> mapAdd tySerial (tupleTy, fieldMap)) ctx.RecordMap

let private recordToTuple (ctx: TyElaborationCtx) tySerial =
  match ctx.RecordMap |> mapTryFind tySerial with
  | Some (tupleTy, _) -> Some tupleTy
  | _ -> None

let private rewriteRecordExpr (ctx: TyElaborationCtx) itself baseOpt fields ty loc =
  let tupleTy, fieldMap =
    match ty with
    | AppTy (RecordTyCtor tySerial, _) ->
        match ctx.RecordMap |> mapTryFind tySerial with
        | Some (tupleTy, fieldMap) -> tupleTy, fieldMap
        | _ -> failwithf "NEVER: %A" itself
    | _ -> failwithf "NEVER: %A" itself

  // Base expr is guaranteed to be a cheap expr thanks to modification in Typing,
  // so we can freely clone this.
  let baseOpt =
    assert (baseOpt |> Option.forall hxIsUnboxingRef)

    baseOpt |> Option.map (teExpr ctx)

  let fields =
    fields
    |> List.map (fun (name, init, _) ->
         let init = init |> teExpr ctx
         let index, _ = fieldMap |> mapFind name
         index, init)
    |> listSort (fun (l, _) (r, _) -> intCmp l r)

  match baseOpt with
  | Some baseExpr ->
      let itemTys =
        match tupleTy with
        | AppTy (_, fieldTys) -> fieldTys
        | _ -> failwithf "NEVER: %A" itself

      let itemExpr index =
        let itemTy = itemTys |> List.item index
        HInfExpr(InfOp.TupleItem index, [ baseExpr ], itemTy, loc)

      let n = itemTys |> List.length

      let rec go i fields =
        match fields with
        | [] when i = n -> []

        | (index, init) :: fields when index = i -> init :: go (i + 1) fields

        | _ -> itemExpr i :: go (i + 1) fields

      hxTuple (go 0 fields) loc

  | None ->
      let fields =
        fields |> List.map (fun (_, init) -> init)

      hxTuple fields loc

let private rewriteFieldExpr (ctx: TyElaborationCtx) itself recordTy l r ty loc =
  let index =
    match recordTy with
    | AppTy (RecordTyCtor tySerial, _) ->
        let _, fieldMap = ctx.RecordMap |> mapFind tySerial

        let index, _ = fieldMap |> mapFind r
        index

    | _ -> failwithf "NEVER: %A" itself

  HInfExpr(InfOp.TupleItem index, [ l ], ty, loc)

/// ## Newtype variant unwrapping
///
/// Newtype variants are unnecessary for code generation.
///
/// Newtype variant, such as `N` in `type N = N of T`,
/// is equivalent to its payload type `T`.
///
/// After AutoBoxing, variants are guaranteed to not recursive.
///
/// ### Conversions
///
/// This stage replaces production and consumption of newtype variants
/// with their payload.
///
/// Variant type:
///
/// ```fsharp
/// // Assume type N = N of T is defined.
///   N  // type
/// //=>
///   T
/// ```
///
/// Variant creation:
///
/// ```fsharp
///   N (payload: T): N  // expression
/// //=>
///   payload: T
/// ```
///
/// Variant pattern:
///
/// ```fsharp
///   N (payloadPat: T): N  // pattern
/// //=>
///   payloadPat: T
/// ```

let private rewriteNewtypeTy (ctx: TyElaborationCtx) tySerial =
  match ctx.Tys |> mapTryFind tySerial with
  | Some (UnionTyDef (_, [ variantSerial ], _)) ->
      let variantDef = ctx.Variants |> mapFind variantSerial
      Some variantDef.PayloadTy

  | _ -> None

let private rewriteNewtypeVariantPat (ctx: TyElaborationCtx) variantSerial loc =
  let variantDef = ctx.Variants |> mapFind variantSerial

  match ctx.Tys |> mapTryFind variantDef.UnionTySerial with
  | Some (UnionTyDef (_, [ _ ], _)) ->
      if variantDef.HasPayload
      then failwith "ref pat of non-unit newtype should be type error"

      Some(HTuplePat([], tyUnit, loc))

  | _ -> None

let private rewriteNewtypeCallPat (ctx: TyElaborationCtx) callee args =
  match callee, args with
  | HVariantPat (variantSerial, _, _), [ payloadPat ] ->
      let variantDef = ctx.Variants |> mapFind variantSerial
      match ctx.Tys |> mapTryFind variantDef.UnionTySerial with
      | Some (UnionTyDef (_, [ _ ], _)) -> Some payloadPat

      | _ -> None

  | _ -> None

let private rewriteNewtypeVariantExpr (ctx: TyElaborationCtx) variantSerial loc =
  let variantDef = ctx.Variants |> mapFind variantSerial

  match ctx.Tys |> mapTryFind variantDef.UnionTySerial with
  | Some (UnionTyDef (_, [ _ ], _)) ->
      if variantDef.HasPayload then
        // N => (fun payload -> N payload) => (fun payload -> payload) => id ?
        failwith "ref of non-unit newtype is unimplemented"

      Some(hxUnit loc)

  | _ -> None

let private rewriteNewtypeAppExpr (ctx: TyElaborationCtx) infOp items =
  match infOp, items with
  | InfOp.App, [ HVariantExpr (variantSerial, _, _); payload ] ->
      let variantDef = ctx.Variants |> mapFind variantSerial
      match ctx.Tys |> mapTryFind variantDef.UnionTySerial with
      | Some (UnionTyDef (_, [ _ ], _)) -> Some payload
      | _ -> None
  | _ -> None

// -----------------------------------------------
// Control
// -----------------------------------------------

let private teTy (ctx: TyElaborationCtx) ty =
  match ty with
  | AppTy (UnionTyCtor tySerial, tyArgs) ->
      assert (List.isEmpty tyArgs)

      match rewriteNewtypeTy ctx tySerial with
      | Some ty -> ty
      | None -> ty

  | AppTy (RecordTyCtor tySerial, tyArgs) ->
      assert (List.isEmpty tyArgs)

      match recordToTuple ctx tySerial with
      | Some ty -> ty
      | None -> ty

  | AppTy (_, []) -> ty

  | AppTy (tyCtor, tyArgs) ->
      let tyArgs = tyArgs |> List.map (teTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private tePat ctx pat =
  match pat with
  | HRefPat (varSerial, ty, loc) ->
      let ty = ty |> teTy ctx
      HRefPat(varSerial, ty, loc)

  | HVariantPat (variantSerial, ty, loc) ->
      let ty = ty |> teTy ctx

      match rewriteNewtypeVariantPat ctx variantSerial loc with
      | Some pat -> pat
      | None -> HVariantPat(variantSerial, ty, loc)

  | HCallPat (callee, args, ty, loc) ->
      match rewriteNewtypeCallPat ctx callee args with
      | Some payloadPat -> payloadPat |> tePat ctx

      | None ->
          let callee = callee |> tePat ctx
          let args = args |> List.map (tePat ctx)
          HCallPat(callee, args, ty, loc)

  | HLitPat _ -> pat

  | HNilPat _
  | HNonePat _
  | HSomePat _
  | HDiscardPat _ -> pat |> patMap (teTy ctx) id

  | HConsPat (l, r, itemTy, loc) ->
      let l = l |> tePat ctx
      let r = r |> tePat ctx
      let itemTy = itemTy |> teTy ctx
      HConsPat(l, r, itemTy, loc)

  | HTuplePat (itemPats, ty, loc) ->
      let itemPats = itemPats |> List.map (tePat ctx)
      let ty = ty |> teTy ctx
      HTuplePat(itemPats, ty, loc)

  | HBoxPat (itemPat, loc) ->
      let itemPat = itemPat |> tePat ctx
      HBoxPat(itemPat, loc)

  | HAsPat (body, varSerial, loc) ->
      let body = body |> tePat ctx
      HAsPat(body, varSerial, loc)

  | HOrPat (l, r, ty, loc) ->
      let l = l |> tePat ctx
      let r = r |> tePat ctx
      let ty = ty |> teTy ctx
      HOrPat(l, r, ty, loc)

  | HNavPat _ -> failwith "NEVER: HNavPat is resolved in NameRes."
  | HAnnoPat _ -> failwith "NEVER: HAnnoPat is resolved in Typing."

let private teExpr (ctx: TyElaborationCtx) expr =
  match expr with
  | HVariantExpr (varSerial, ty, loc) ->
      match rewriteNewtypeVariantExpr ctx varSerial loc with
      | Some expr -> expr

      | None ->
          let ty = ty |> teTy ctx
          HVariantExpr(varSerial, ty, loc)

  | HRecordExpr (baseOpt, fields, ty, loc) -> rewriteRecordExpr ctx expr baseOpt fields ty loc

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = exprToTy l
        let l = l |> teExpr ctx
        let ty = ty |> teTy ctx
        rewriteFieldExpr ctx expr recordTy l r ty loc

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        match rewriteNewtypeAppExpr ctx infOp items with
        | Some payload -> payload |> teExpr ctx

        | None ->
            let items = items |> List.map (teExpr ctx)
            let ty = ty |> teTy ctx
            HInfExpr(infOp, items, ty, loc)

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HRefExpr _
  | HFunExpr _
  | HPrimExpr _ -> expr |> exprMap (teTy ctx) id

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond = cond |> teExpr ctx

        let go (pat, guard, body) =
          let pat = pat |> tePat ctx
          let guard = guard |> teExpr ctx
          let body = body |> teExpr ctx
          pat, guard, body

        let arms = arms |> List.map go
        let ty = ty |> teTy ctx
        HMatchExpr(cond, arms, ty, loc)

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat = pat |> tePat ctx
        let init = init |> teExpr ctx
        let next = next |> teExpr ctx
        let ty = ty |> teTy ctx
        HLetValExpr(vis, pat, init, next, ty, loc)

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      let doArm () =
        let args = args |> List.map (tePat ctx)
        let body = body |> teExpr ctx
        let next = next |> teExpr ctx
        let ty = ty |> teTy ctx
        HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc)

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "NEVER: %A" (error, loc)
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let tyElaborate (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  let ctx =
    { ctx with
        RecordMap = buildRecordMap ctx }

  let expr = expr |> teExpr ctx

  let vars =
    ctx.Vars
    |> mapMap (fun _ varDef ->
         match varDef with
         | VarDef (name, sm, ty, loc) ->
             let ty = ty |> teTy ctx
             VarDef(name, sm, ty, loc))

  let funs =
    ctx.Funs
    |> mapMap (fun _ (funDef: FunDef) ->
         let (TyScheme (tyVars, ty)) = funDef.Ty
         let ty = ty |> teTy ctx
         { funDef with
             Ty = TyScheme(tyVars, ty) })

  let variants =
    ctx.Variants
    |> mapMap (fun _ (variantDef: VariantDef) ->
         { variantDef with
             PayloadTy = variantDef.PayloadTy |> teTy ctx })

  let tys =
    ctx.Tys
    |> mapMap (fun _ tyDef ->
         match tyDef with
         | SynonymTyDef (name, tyArgs, bodyTy, loc) ->
             let bodyTy = bodyTy |> teTy ctx
             SynonymTyDef(name, tyArgs, bodyTy, loc)

         | _ -> tyDef)

  let ctx =
    { ctx with
        Vars = vars
        Funs = funs
        Variants = variants
        Tys = tys }

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
