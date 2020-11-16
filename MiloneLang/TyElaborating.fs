/// # TyElaborating
///
/// Converts some of types to other types.
///
/// - Record types
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

type private TyElaborationCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef>

    /// recordTySerial -> (tupleTy, (field -> fieldIndex, fieldTy))
    RecordMap: AssocMap<TySerial, (Ty * AssocMap<Ident, int * Ty>)> }

let private ofTyCtx (tyCtx: TyCtx): TyElaborationCtx =
  { Vars = tyCtx.Vars
    Tys = tyCtx.Tys
    RecordMap = mapEmpty intCmp }

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
/// Record creation:
///
/// ```fsharp
/// // Assume type R = { F1: T1; F2: T2; ... } is defined.
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
  ctx.Tys
  |> mapFold (fun acc tySerial tyDef ->
       match tyDef with
       | RecordTyDef (_, fields, _) ->
           let tupleTy =
             fields
             |> List.map (fun (_, ty, _) -> ty)
             |> tyTuple

           let fieldMap =
             fields
             |> List.mapi (fun i (ident, ty, _) -> ident, (i, ty))
             |> mapOfList strCmp

           (tySerial, (tupleTy, fieldMap)) :: acc

       | _ -> acc) []
  |> mapOfList intCmp

let private recordToTuple (ctx: TyElaborationCtx) tySerial =
  match ctx.RecordMap |> mapTryFind tySerial with
  | Some (tupleTy, _) -> Some tupleTy
  | _ -> None

let private rewriteRecordExpr (ctx: TyElaborationCtx) itself baseOpt fields ty loc =
  let tupleTy, fieldMap =
    match ty with
    | AppTy (RefTyCtor tySerial, []) ->
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
    |> List.map (fun (ident, init, _) ->
         let init = init |> teExpr ctx
         let index, _ = fieldMap |> mapFind ident
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
    | AppTy (RefTyCtor tySerial, []) ->
        let _, fieldMap = ctx.RecordMap |> mapFind tySerial

        let index, _ = fieldMap |> mapFind r
        index

    | _ -> failwithf "NEVER: %A" itself

  HInfExpr(InfOp.TupleItem index, [ l ], ty, loc)

// -----------------------------------------------
// Control
// -----------------------------------------------

let private teTy (ctx: TyElaborationCtx) ty =
  match ty with
  | AppTy (RefTyCtor tySerial, []) ->
      match recordToTuple ctx tySerial with
      | Some ty -> ty
      | None -> ty

  | AppTy (_, []) -> ty

  | AppTy (tyCtor, tyArgs) ->
      let tyArgs = tyArgs |> List.map (teTy ctx)
      AppTy(tyCtor, tyArgs)

  | MetaTy _
  | ErrorTy _ -> ty

let private tePat ctx pat = pat |> patMap (teTy ctx) id

let private teExpr (ctx: TyElaborationCtx) expr =
  match expr with
  | HRecordExpr (baseOpt, fields, ty, loc) -> rewriteRecordExpr ctx expr baseOpt fields ty loc

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = exprToTy l
        let l = l |> teExpr ctx
        let ty = ty |> teTy ctx
        rewriteFieldExpr ctx expr recordTy l r ty loc

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HRefExpr _
  | HPrimExpr _ -> expr |> exprMap (teTy ctx) id

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target = target |> teExpr ctx

        let go (pat, guard, body) =
          let pat = pat |> tePat ctx
          let guard = guard |> teExpr ctx
          let body = body |> teExpr ctx
          pat, guard, body

        let arms = arms |> List.map go
        let ty = ty |> teTy ctx
        HMatchExpr(target, arms, ty, loc)

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items = items |> List.map (teExpr ctx)
        let ty = ty |> teTy ctx
        HInfExpr(infOp, items, ty, loc)

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

  let vars =
    ctx.Vars
    |> mapMap (fun _ varDef ->
         match varDef with
         | VarDef (ident, sm, ty, loc) ->
             let ty = ty |> teTy ctx
             VarDef(ident, sm, ty, loc)

         | FunDef (ident, arity, TyScheme (tyArgs, ty), loc) ->
             let ty = ty |> teTy ctx
             FunDef(ident, arity, TyScheme(tyArgs, ty), loc)

         | VariantDef (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
             let payloadTy = payloadTy |> teTy ctx
             VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc))

  // FIXME: convert Tys for ty synonyms bodies?

  let ctx = { ctx with Vars = vars }

  let expr = expr |> teExpr ctx
  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
