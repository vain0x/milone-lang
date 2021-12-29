/// # RecordRes
///
/// Resolves.
module rec MiloneTranslation.RecordRes

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneStd.StdError
open MiloneStd.StdMap
open MiloneTranslation.Hir

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
  { Tys: TreeMap<TySerial, TyDef>

    /// recordTySerial -> (fieldTys, (field -> (fieldIndex, fieldTy)))
    RecordMap: TreeMap<TySerial, (Ty list * TreeMap<Ident, int * Ty>)> }

let private ofHirCtx (hirCtx: HirCtx) : RrCtx =
  { Tys = hirCtx.Tys
    RecordMap = TMap.empty compare }

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
         | RecordTyDef (_, fields, _, _) ->
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
      | _ -> unreachable itself
    | _ -> unreachable itself

  // Base expr is guaranteed to be a cheap expr thanks to modification in Typing,
  // so we can freely clone this.
  let baseOpt =
    assert (baseOpt |> Option.forall hxIsVarOrUnboxingVar)

    baseOpt |> Option.map (teExpr ctx)

  let fields =
    fields
    |> List.map (fun (name, init, _) ->
      let init = init |> teExpr ctx
      let index, _ = fieldMap |> mapFind name
      index, init)
    |> listSort (fun (l: int, _) (r: int, _) -> compare l r)

  match baseOpt with
  | Some baseExpr ->
    let itemExpr index fieldTy =
      HNodeExpr(HRecordItemEN index, [ baseExpr ], fieldTy, loc)

    let rec go i fields fieldTys =
      match fields, fieldTys with
      | [], [] -> []

      | (index, init) :: fields, _ :: fieldTys when index = i -> init :: go (i + 1) fields fieldTys

      | _, fieldTy :: fieldTys -> itemExpr i fieldTy :: go (i + 1) fields fieldTys

      | _, [] -> unreachable ()

    let fields = go 0 fields fieldTys
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

    | _ -> unreachable itself

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
      |> List.map (fun (name, init, loc) ->
        let init = init |> teExpr ctx
        name, init, loc)

    rewriteRecordExpr ctx expr baseOpt fields ty loc

  | HNavExpr (l, r, ty, loc) ->
    let recordTy = exprToTy l
    let l = l |> teExpr ctx
    rewriteFieldExpr ctx expr recordTy l r ty loc

  | HNodeExpr (kind, items, ty, loc) ->
    let items = items |> List.map (teExpr ctx)
    HNodeExpr(kind, items, ty, loc)

  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond = cond |> teExpr ctx

    let arms =
      arms |> List.map (hArmMap id (teExpr ctx))

    HMatchExpr(cond, arms, ty, loc)

  | HBlockExpr (stmts, last) ->
    let stmts = stmts |> List.map (teStmt ctx)
    let last = last |> teExpr ctx
    HBlockExpr(stmts, last)

let private teStmt ctx stmt =
  match stmt with
  | HExprStmt expr -> HExprStmt(teExpr ctx expr)

  | HLetValStmt (pat, init, loc) ->
    let init = init |> teExpr ctx
    HLetValStmt(pat, init, loc)

  | HLetFunStmt (callee, args, body, loc) ->
    let body = body |> teExpr ctx
    HLetFunStmt(callee, args, body, loc)

let recordRes (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let ctx = ofHirCtx hirCtx

  let ctx =
    { ctx with RecordMap = buildRecordMap ctx }

  let modules = modules |> HProgram.mapExpr (teExpr ctx)

  // HirCtx doesn't change.
  modules, hirCtx
