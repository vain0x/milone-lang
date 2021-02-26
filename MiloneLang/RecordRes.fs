/// # RecordRes
///
/// Resolves.
module rec MiloneLang.RecordRes

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLang.Typing

module TMap = MiloneStd.StdMap

let private hxIsVarOrUnboxingVar expr =
  match expr with
  | HVarExpr _
  | HNodeExpr (HAppEN, [ HPrimExpr (HPrim.Unbox, _, _); HVarExpr _ ], _, _) -> true
  | _ -> false

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RrCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    /// recordTySerial -> (fieldTys, (field -> (fieldIndex, fieldTy)))
    RecordMap: AssocMap<TySerial, (Ty list * AssocMap<Ident, int * Ty>)> }

let private ofTyCtx (tyCtx: TyCtx): RrCtx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    RecordMap = TMap.empty compare }

let private toTyCtx (tyCtx: TyCtx) (ctx: RrCtx): TyCtx = tyCtx

/// ## Resolution of records and fields
///
/// Record expressions are flexible in order of fields
/// and allow to *extend* a record.
/// Field expressions selects accessed field by name,
/// which requires looking up.
///
/// This stage changes them to normalized form.
/// Record creation always provide all field values in order of declaration
/// and extending a record is explicitly done.
/// Accessed field is selected by indexes, not names.
///
/// ### Conversions
///
/// Record creation:
///
/// ```fsharp
///   {
///     F2 = t2
///     F1 = t1
///   }
/// //=>
///   {
///     F1 = t1
///     F2 = t2
///   }
/// ```
///
/// Since record creation is checked in Typing,
/// fields are exhaustively specified; just sort them without extract checking.
/// (Evaluation order does change.)
///
/// Record mutation:
///
/// ```fsharp
///   { r with
///       Fi = ti
///       ...
///   }
/// //=>
///   {
///       Fi = Ti  // specified fields
///       ...
///       Fj = r.j  // unspecified fields
///       ...
///   }
/// ```
///
/// Conversion of record mutation is similar to record creation
/// but some of fields are unspecified.
/// For such fields, reuse base record's value.

let private buildRecordMap (ctx: RrCtx) =
  ctx.Tys
  |> TMap.fold
       (fun acc tySerial tyDef ->
         match tyDef with
         | RecordTyDef (_, fields, _) ->
             let fieldTys =
               fields |> List.map (fun (_, ty, _) -> ty)

             let fieldMap =
               fields
               |> List.mapi (fun i (name, ty, _) -> name, (i, ty))
               |> TMap.ofList compare

             acc |> TMap.add tySerial (fieldTys, fieldMap)

         | _ -> acc)
       (TMap.empty compare)

let private rewriteRecordExpr (ctx: RrCtx) itself baseOpt fields ty loc =
  let fieldTys, fieldMap =
    match ty with
    | Ty (RecordTk tySerial, _) ->
        match ctx.RecordMap |> TMap.tryFind tySerial with
        | Some (fieldTys, fieldMap) -> fieldTys, fieldMap
        | _ -> failwithf "NEVER: %A" itself
    | _ -> failwithf "NEVER: %A" itself

  // Base expr is guaranteed to be a cheap expr thanks to modification in Typing,
  // so we can freely clone this.
  let baseOpt =
    assert (baseOpt |> Option.forall hxIsVarOrUnboxingVar)

    baseOpt |> Option.map (teExpr ctx)

  let fields =
    fields
    |> List.map
         (fun (name, init, _) ->
           let init = init |> teExpr ctx
           let index, _ = fieldMap |> mapFind name
           index, init)
    |> listSort (fun (l: int, _) (r: int, _) -> compare l r)

  match baseOpt with
  | Some baseExpr ->
      let itemExpr index =
        // FIXME: avoid failwith
        let itemTy =
          match fieldTys |> List.tryItem index with
          | Some it -> it
          | None -> failwith "NEVER"

        HNodeExpr(HRecordItemEN index, [ baseExpr ], itemTy, loc)

      let n = fieldTys |> List.length

      let rec go i fields =
        match fields with
        | [] when i = n -> []

        | (index, init) :: fields when index = i -> init :: go (i + 1) fields

        | _ -> itemExpr i :: go (i + 1) fields

      let fields = go 0 fields
      HNodeExpr(HRecordEN, fields, ty, loc)

  | None ->
      let fields =
        fields |> List.map (fun (_, init) -> init)

      HNodeExpr(HRecordEN, fields, ty, loc)

let private rewriteFieldExpr (ctx: RrCtx) itself recordTy l r ty loc =
  let index =
    match recordTy with
    | Ty (RecordTk tySerial, _) ->
        let _, fieldMap = ctx.RecordMap |> mapFind tySerial

        let index, _ = fieldMap |> mapFind r
        index

    | _ -> failwithf "NEVER: %A" itself

  HNodeExpr(HRecordItemEN index, [ l ], ty, loc)

// -----------------------------------------------
// Control
// -----------------------------------------------

let private teExpr (ctx: RrCtx) expr =
  match expr with
  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let baseOpt = baseOpt |> Option.map (teExpr ctx)

      let fields =
        fields
        |> List.map
             (fun (name, init, loc) ->
               let init = init |> teExpr ctx
               name, init, loc)

      rewriteRecordExpr ctx expr baseOpt fields ty loc

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = exprToTy l
        let l = l |> teExpr ctx
        rewriteFieldExpr ctx expr recordTy l r ty loc

      doArm ()

  | HNodeExpr (kind, items, ty, loc) ->
      let doArm () =
        let items = items |> List.map (teExpr ctx)
        HNodeExpr(kind, items, ty, loc)

      doArm ()

  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond = cond |> teExpr ctx

        let go (pat, guard, body) =
          let guard = guard |> teExpr ctx
          let body = body |> teExpr ctx
          pat, guard, body

        let arms = arms |> List.map go
        HMatchExpr(cond, arms, ty, loc)

      doArm ()

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts = stmts |> List.map (teExpr ctx)
        let last = last |> teExpr ctx
        HBlockExpr(stmts, last)

      doArm ()

  | HLetValExpr (pat, init, next, ty, loc) ->
      let doArm () =
        let init = init |> teExpr ctx
        let next = next |> teExpr ctx
        HLetValExpr(pat, init, next, ty, loc)

      doArm ()

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
      let doArm () =
        let body = body |> teExpr ctx
        let next = next |> teExpr ctx
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc)

      doArm ()

  | HModuleExpr _
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

let recordRes (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  let ctx =
    { ctx with
        RecordMap = buildRecordMap ctx }

  let expr = expr |> teExpr ctx

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
