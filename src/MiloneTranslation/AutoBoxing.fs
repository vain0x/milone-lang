/// ## Auto Boxing
///
/// Provides implicit indirection by inserting allocate/dereference operations.
module rec MiloneTranslation.AutoBoxing

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open Std.StdSet
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes

module Int = Std.StdInt

let private isFunTy ty =
  match ty with
  | Ty (FunTk, _) -> true
  | _ -> false

let private unwrapRecordTy ty =
  match ty with
  | Ty (RecordTk(tySerial, name), tyArgs) -> tySerial, name, tyArgs
  | _ -> unreachable ()

let private hxBox itemExpr itemTy loc =
  hxCallProc (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) [ itemExpr ] tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxCallProc (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) [ boxExpr ] itemTy loc

// -----------------------------------------------
// Type recursion detection
// -----------------------------------------------

/// "Direct" here means lack of pointer. You can access a value *directly* if you can do without pointer dereference.
/// Examples: `int * string` includes int directly. `int list` includes int only indirectly.
[<NoEquality; NoComparison>]
type private IsDirect =
  | IsDirect
  | IsIndirect

let private compareIsDirect l r : int =
  let toInt isDirect =
    match isDirect with
    | IsDirect -> 0
    | IsIndirect -> 1

  toInt l - toInt r

[<NoEquality; NoComparison>]
type private Status =
  | Recursive
  | Boxed
  | Unboxed

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TrdCtx =
  { Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>

    // ((variantSerial, IsDirect), Boxed) means:
    ///     The variant should be boxed because it is recursive without indirection.
    /// ((variantSerial, IsIndirect), Boxed) means:
    ///     The variant is indirectly recursive (i.e. by following pointers).
    VariantMemo: TreeMap<VariantSerial * IsDirect, Status>

    RecordTyMemo: TreeMap<TySerial * IsDirect, Status> }

let private trdVariant isDirect (ctx: TrdCtx) variantSerial (variantDefOpt: VariantDef option) =
  match
    ctx.VariantMemo
    |> TMap.tryFind (variantSerial, isDirect)
    with
  | Some Recursive ->
    // printfn "// trd variant %s is now boxed (%s)" (ctx.Variants |> mapFind variantSerial).Name (objToString isDirect)
    { ctx with
        VariantMemo =
          ctx.VariantMemo
          |> TMap.add (variantSerial, isDirect) Boxed }

  | Some t ->
    // printfn "// trd variant %s is done: %s" (ctx.Variants |> mapFind variantSerial).Name (objToString t)
    ctx

  | None ->
    // printfn "// trd variant %s begin" (ctx.Variants |> mapFind variantSerial).Name

    let ctx =
      { ctx with
          VariantMemo =
            ctx.VariantMemo
            |> TMap.add (variantSerial, isDirect) Recursive }

    let ctx: TrdCtx =
      let variantDef =
        match variantDefOpt with
        | Some variantDef -> variantDef
        | None -> ctx.Variants |> mapFind variantSerial

      trdTy isDirect ctx variantDef.PayloadTy

    let ctx =
      match
        ctx.VariantMemo
        |> TMap.tryFind (variantSerial, isDirect)
        with
      | Some Recursive
      | None ->
        { ctx with
            VariantMemo =
              ctx.VariantMemo
              |> TMap.add (variantSerial, isDirect) Unboxed }

      | Some _ -> ctx

    // printfn
    //   "// trd variant %s (%s) end: %s"
    //   (ctx.Variants |> mapFind variantSerial).Name
    //   (objToString isDirect)
    //   (ctx.VariantMemo
    //    |> mapFind (variantSerial, isDirect)
    //    |> objToString)
    ctx

let private trdRecordTyDef isDirect (ctx: TrdCtx) tySerial tyDef =
  match
    ctx.RecordTyMemo
    |> TMap.tryFind (tySerial, isDirect)
    with
  | Some Recursive ->
    // printfn "// trd tyDef %s is now boxed" (tyDefToName tyDef)
    { ctx with
        RecordTyMemo =
          ctx.RecordTyMemo
          |> TMap.add (tySerial, isDirect) Boxed }

  | Some t ->
    // printfn "// trd tyDef %s is done: %s" (tyDefToName tyDef) (objToString t)
    ctx

  | None ->
    // printfn "// trd tyDef %s begin" (tyDefToName tyDef)

    let ctx =
      { ctx with
          RecordTyMemo =
            ctx.RecordTyMemo
            |> TMap.add (tySerial, isDirect) Recursive }

    let ctx: TrdCtx =
      match tyDef with
      | RecordTyDef (_, _, fields, _, _) ->
        fields
        |> List.fold (fun ctx (_, fieldTy, _) -> trdTy isDirect ctx fieldTy) ctx

      | _ -> unreachable ()

    let ctx =
      match
        ctx.RecordTyMemo
        |> TMap.tryFind (tySerial, isDirect)
        with
      | Some Recursive
      | None ->
        { ctx with
            RecordTyMemo =
              ctx.RecordTyMemo
              |> TMap.add (tySerial, isDirect) Unboxed }

      | Some _ -> ctx

    // printfn "// trd tyDef %s end: %s" (tyDefToName tyDef) (objToString (ctx.RecordTyMemo |> mapFind tySerial))

    ctx

let private trdTyDef isDirect (ctx: TrdCtx) tySerial tyDef : TrdCtx =
  match tyDef with
  | UnionTyDef (_, _, variants, _) ->
    variants
    |> List.fold (fun (ctx: TrdCtx) variantSerial -> trdVariant isDirect ctx variantSerial None) ctx

  | RecordTyDef _ -> trdRecordTyDef isDirect ctx tySerial tyDef

  | OpaqueTyDef _ -> ctx

let private trdTy isDirect (ctx: TrdCtx) ty : TrdCtx =
  match ty with
  | Ty (tk, tyArgs) ->
    let nominal ctx tySerial =
      trdTyDef isDirect ctx tySerial (ctx.Tys |> mapFind tySerial)

    match tk with
    | IntTk _
    | FloatTk _
    | BoolTk
    | CharTk
    | StringTk
    | NeverTk
    | ObjTk
    | VoidPtrTk _
    | OpaqueTk _
    | MetaTk _ ->
      assert (List.isEmpty tyArgs)
      ctx

    | ListTk -> tyArgs |> List.fold (trdTy IsIndirect) ctx

    | FunTk
    | TupleTk
    | NativePtrTk _
    | FunPtrTk
    | NativeTypeTk _ -> tyArgs |> List.fold (trdTy isDirect) ctx

    | UnionTk(tySerial, _) ->
      let ctx = tyArgs |> List.fold (trdTy isDirect) ctx
      nominal ctx tySerial

    | RecordTk(tySerial, _) -> nominal ctx tySerial

let private detectTypeRecursion (hirCtx: HirCtx) : TrdCtx =
  let ctx: TrdCtx =
    { Variants = hirCtx.Variants
      Tys = hirCtx.Tys
      VariantMemo = TMap.empty (pairCompare variantSerialCompare compareIsDirect)
      RecordTyMemo = TMap.empty (pairCompare compare compareIsDirect) }

  let doAll isDirect ctx =
    let ctx =
      hirCtx.Tys |> TMap.fold (trdTyDef isDirect) ctx

    hirCtx.Variants
    |> TMap.fold (fun ctx variantSerial varDef -> trdVariant isDirect ctx variantSerial (Some varDef)) ctx

  ctx |> doAll IsDirect |> doAll IsIndirect

// -----------------------------------------------
// Type size measurement
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TsmCtx =
  { Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>

    BoxedVariants: TreeSet<VariantSerial>
    BoxedRecordTys: TreeSet<TySerial>

    VariantMemo: TreeMap<VariantSerial, int>
    RecordTyMemo: TreeMap<TySerial, int> }

let private tsmVariant (ctx: TsmCtx) variantSerial (variantDefOpt: VariantDef option) =
  match ctx.VariantMemo |> TMap.tryFind variantSerial with
  | Some size ->
    // printfn "// measure variant %s cached: size=%d" (ctx.Variants |> mapFind variantSerial).Name size
    assert (size >= 0)
    size, ctx

  | _ when ctx.BoxedVariants |> TSet.contains variantSerial ->
    // printfn "// measure variant: %s is boxed" (ctx.Variants |> mapFind variantSerial).Name
    12, ctx

  | None ->
    // printfn "// measure variant %s begin" (ctx.Variants |> mapFind variantSerial).Name

    // Prevent infinite recursion, just in case. (Recursive variants are already boxed.)
    let ctx =
      { ctx with VariantMemo = ctx.VariantMemo |> TMap.add variantSerial (-1) }

    let size, (ctx: TsmCtx) =
      let variantDef =
        match variantDefOpt with
        | Some variantDef -> variantDef
        | None -> ctx.Variants |> mapFind variantSerial

      tsmTy ctx variantDef.PayloadTy

    let size, isBoxed =
      if 4 + size > 32 then
        8, true
      else
        size, false

    let ctx =
      assert ((ctx.VariantMemo
               |> TMap.tryFind variantSerial
               |> Option.defaultValue (-1)) < 0)

      { ctx with
          VariantMemo = ctx.VariantMemo |> TMap.add variantSerial size
          BoxedVariants =
            if isBoxed then
              ctx.BoxedVariants |> TSet.add variantSerial
            else
              ctx.BoxedVariants }

    // printfn
    //   "// measure variant %s end: size=%d%s"
    //   (ctx.Variants |> mapFind variantSerial).Name
    //   size
    //   (if isBoxed then " (boxed)" else "")

    size, ctx

let private tsmRecordTyDef (ctx: TsmCtx) tySerial tyDef =
  let canBox () =
    match ctx.Tys |> mapFind tySerial with
    | RecordTyDef (_, _, _, IsCRepr true, _) -> false
    | _ -> true

  match ctx.RecordTyMemo |> TMap.tryFind tySerial with
  | Some size ->
    // printfn "// measure record %s: cached %d" (tyDefToName tyDef) size
    assert (size >= 1)
    size, ctx

  | _ when ctx.BoxedRecordTys |> TSet.contains tySerial ->
    // printfn "// measure record %s: boxed" (tyDefToName tyDef)
    8, ctx

  | None ->
    // printfn "// measure record %s begin" (tyDefToName tyDef)

    // Just in case of recursion was not detected correctly.
    let ctx =
      { ctx with RecordTyMemo = ctx.RecordTyMemo |> TMap.add tySerial (-1) }

    let size, (ctx: TsmCtx) =
      match tyDef with
      | RecordTyDef (_, _, fields, _, _) ->
        fields
        |> List.fold
             (fun (totalSize, ctx) (fieldName, fieldTy, _) ->
               let fieldSize, ctx = tsmTy ctx fieldTy
               //  printfn "//   field %s size=%d total=%d" fieldName fieldSize (totalSize + fieldSize)
               totalSize + fieldSize, ctx)
             (0, ctx)

      | _ -> unreachable ()

    let size, isBoxed =
      if canBox () && size > 32 then
        8, true
      else
        Int.max 1 size, false

    let ctx =
      assert ((ctx.RecordTyMemo
               |> TMap.tryFind tySerial
               |> Option.defaultValue (-1)) < 0)

      { ctx with
          RecordTyMemo = ctx.RecordTyMemo |> TMap.add tySerial size
          BoxedRecordTys =
            if isBoxed then
              ctx.BoxedRecordTys |> TSet.add tySerial
            else
              ctx.BoxedRecordTys }

    // printfn "// measure record %s end: size=%d%s" (tyDefToName tyDef) size (if isBoxed then " (boxed)" else "")
    size, ctx

let private tsmTyDef (ctx: TsmCtx) tySerial tyDef =
  match tyDef with
  | UnionTyDef (_, _, variants, _) ->
    let payloadSize, ctx =
      variants
      |> List.fold
           (fun (maxSize, ctx: TsmCtx) variantSerial ->
             let payloadSize, ctx = tsmVariant ctx variantSerial None
             Int.max maxSize payloadSize, ctx)
           (0, ctx)

    4 + payloadSize, ctx

  | RecordTyDef _ -> tsmRecordTyDef ctx tySerial tyDef

  | OpaqueTyDef _ -> 1000000, ctx

let private tsmTy (ctx: TsmCtx) ty =
  match ty with
  | Ty (tk, tyArgs) ->
    let nominal tySerial =
      tsmTyDef ctx tySerial (ctx.Tys |> mapFind tySerial)

    match tk with
    | BoolTk
    | CharTk
    | NeverTk -> 1, ctx

    | IntTk flavor -> intFlavorToBytes flavor, ctx
    | FloatTk flavor -> floatFlavorToBytes flavor, ctx

    | ObjTk
    | ListTk
    | VoidPtrTk _
    | NativePtrTk _
    | FunPtrTk -> 8, ctx

    | StringTk
    | FunTk -> 16, ctx

    | TupleTk ->
      let size, ctx =
        tyArgs
        |> List.fold
             (fun (totalSize, ctx) fieldTy ->
               let size, ctx = tsmTy ctx fieldTy
               totalSize + size, ctx)
             (0, ctx)

      Int.max 1 size, ctx

    | UnionTk(tySerial, _) -> nominal tySerial
    | RecordTk(tySerial, _) -> nominal tySerial

    | MetaTk _ -> 8, ctx
    | NativeTypeTk _
    | OpaqueTk _ -> 1000000, ctx

let private measureTys (trdCtx: TrdCtx) : TsmCtx =
  let boxedVariants =
    trdCtx.VariantMemo
    |> TMap.fold
         (fun set (variantSerial, isDirect) status ->
           match isDirect, status with
           | IsDirect, Boxed -> set |> TSet.add variantSerial
           | _ -> set)
         (TSet.empty variantSerialCompare)

  let boxedRecordTys =
    trdCtx.RecordTyMemo
    |> TMap.fold
         (fun set (tySerial, isDirect) status ->
           match isDirect, status with
           | IsDirect, Boxed -> set |> TSet.add tySerial
           | _ -> set)
         (TSet.empty compare)

  let ctx: TsmCtx =
    { Variants = trdCtx.Variants
      Tys = trdCtx.Tys
      BoxedVariants = boxedVariants
      BoxedRecordTys = boxedRecordTys
      VariantMemo = TMap.empty variantSerialCompare
      RecordTyMemo = TMap.empty compare }

  let ctx =
    ctx.Tys
    |> TMap.fold (fun ctx tySerial tyDef -> tsmTyDef ctx tySerial tyDef |> snd) ctx

  ctx.Variants
  |> TMap.fold (fun ctx variantSerial varDef -> tsmVariant ctx variantSerial (Some varDef) |> snd) ctx

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private AbCtx =
  { Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>

    BoxedVariants: TreeSet<VariantSerial>
    BoxedRecordTys: TreeSet<TySerial>

    RecursiveVariants: TreeSet<VariantSerial>

    // #erase_enum_like_union
    EnumLikeUnionTys: TreeSet<TySerial>
    EnumLikeVariants: TreeMap<VariantSerial, TySerial * int * Lit> }

let private ofHirCtx (hirCtx: HirCtx) : AbCtx =
  { Vars = hirCtx.StaticVars
    Funs = hirCtx.Funs
    Variants = hirCtx.Variants
    Tys = hirCtx.Tys
    BoxedVariants = TMap.empty variantSerialCompare
    BoxedRecordTys = TMap.empty compare
    RecursiveVariants = TMap.empty variantSerialCompare

    // #erase_enum_like_union
    EnumLikeUnionTys = TMap.empty compare
    EnumLikeVariants = TMap.empty variantSerialCompare }

let private toHirCtx (hirCtx: HirCtx) (ctx: AbCtx) =
  { hirCtx with
      StaticVars = ctx.Vars
      Funs = ctx.Funs
      Variants = ctx.Variants
      Tys = ctx.Tys }

let private needsBoxedVariant (ctx: AbCtx) variantSerial =
  ctx.BoxedVariants |> TSet.contains variantSerial

let private needsBoxedRecordTySerial (ctx: AbCtx) tySerial =
  ctx.BoxedRecordTys |> TSet.contains tySerial

// HOTFIX: Don't unwrap newtype of function to not confuse ArityCheck and EtaExpansion. See also newtype_of_fun_ty_bug.
let private isRecursiveVariant (ctx: AbCtx) variantSerial =
  (ctx.RecursiveVariants
   |> TSet.contains variantSerial)
  || ((ctx.Variants |> mapFind variantSerial).PayloadTy
      |> isFunTy)

let private needsBoxedRecordTy ctx ty =
  match ty with
  | Ty (RecordTk(tySerial, _), _) -> needsBoxedRecordTySerial ctx tySerial
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
///   // ⇒
///   K (box payload)
///
///   // Variant decomposition. x is a variable defined in the pattern.
///   K payloadPat
///   // ⇒
///   K (box payloadPat)  // using box pattern to unbox the payload
/// ```

let private erasePayloadTy ctx variantSerial payloadTy =
  if needsBoxedVariant ctx variantSerial then
    tyObj
  else
    payloadTy |> abTy ctx

let private postProcessVariantAppPat (ctx: AbCtx) variantSerial payloadPat =
  if needsBoxedVariant ctx variantSerial then
    let loc = patToLoc payloadPat
    Some(HNodePat(HBoxPN, [ payloadPat ], tyObj, loc))
  else
    None

let private postProcessVariantFunCallExpr ctx variantSerial payload : HExpr option =
  if needsBoxedVariant ctx variantSerial then
    // FIXME: ty is now wrong for the same reason as call-variant pattern.
    let ty, loc = exprExtract payload
    Some(hxBox payload ty loc)
  else
    None

/// ### Unwrapping newtype variants

// #tyAssign
let private assignToPayloadTy (ctx: AbCtx) variantSerial (tyArgs: Ty list) =
  let variantDef = ctx.Variants |> mapFind variantSerial

  let tyParams =
    match ctx.Tys |> mapFind variantDef.UnionTySerial with
    | UnionTyDef (_, tyParams, _, _) -> tyParams
    | _ -> []

  let assignment =
    match listTryZip tyParams tyArgs with
    | zipped, [], [] -> TMap.ofList compare zipped
    | _ -> unreachable () // Arity mismatch.

  tySubst (fun tySerial -> assignment |> TMap.tryFind tySerial) variantDef.PayloadTy

let private unwrapNewtypeUnionTy (ctx: AbCtx) ty tyArgs : Ty option =
  let asNewtypeVariant ty =
    match ty with
    | Ty (UnionTk(tySerial, _), _) ->
      match ctx.Tys |> mapFind tySerial with
      | UnionTyDef (_, _, [ variantSerial ], _) when not (isRecursiveVariant ctx variantSerial) -> Some variantSerial
      | _ -> None
    | _ -> None

  match asNewtypeVariant ty with
  | Some variantSerial ->
    let variantDef = ctx.Variants |> mapFind variantSerial
    assert variantDef.IsNewtype

    let payloadTy =
      assignToPayloadTy ctx variantSerial tyArgs

    erasePayloadTy ctx variantSerial payloadTy |> Some

  | _ -> None

let private unwrapNewtypeVariantPat (ctx: AbCtx) variantSerial loc : HPat option =
  let variantDef = ctx.Variants |> mapFind variantSerial

  if not (isRecursiveVariant ctx variantSerial)
     && variantDef.IsNewtype
     && not variantDef.HasPayload then
    Some(HNodePat(HTuplePN, [], tyUnit, loc))
  else
    None

let private unwrapNewtypeVariantAppPat (ctx: AbCtx) variantSerial payloadPat : HPat option =
  let variantDef = ctx.Variants |> mapFind variantSerial

  if
    not (isRecursiveVariant ctx variantSerial)
    && variantDef.IsNewtype
  then
    Some payloadPat
  else
    None

let private unwrapNewtypeVariantExpr (ctx: AbCtx) variantSerial loc : HExpr option =
  let variantDef = ctx.Variants |> mapFind variantSerial

  if not (isRecursiveVariant ctx variantSerial)
     && variantDef.IsNewtype
     && not variantDef.HasPayload then
    Some(hxUnit loc)
  else
    None

let private unwrapNewtypeVariantCallExpr (ctx: AbCtx) variantSerial payload : HExpr option =
  let variantDef = ctx.Variants |> mapFind variantSerial

  if
    not (isRecursiveVariant ctx variantSerial)
    && variantDef.IsNewtype
  then
    Some payload
  else
    None

/// ### Boxing of Records
///
/// ~Records are all boxed because they tend to be too large to clone.~
///
/// (Ideally, we should measure size of record types and suppress auto-box for small records.)
///
/// ```fsharp
///   // Record creation.
///   { fields... }: R
///   // ⇒
///   box { fields... }: obj
///
///   // Record mutation.
///   { record with fields... }: R
///   // ⇒
///   box { unbox record with fields... }: obj
///
///   // Field projection.
///   (record: R).field
///   // ⇒
///   (unbox record).field
///
///   // Def/use of record-type pat/expr.
///   record: R
///   // ⇒
///   record: obj
/// ```

let private eraseRecordTy ctx ty =
  if needsBoxedRecordTy ctx ty then
    Some tyObj
  else
    None

let private postProcessRecordExpr ctx recordTySerial tyName tyArgs args loc =
  if needsBoxedRecordTySerial ctx recordTySerial then
    let ty = tyRecord recordTySerial tyName tyArgs
    let recordExpr = HNodeExpr(HRecordEN, args, ty, loc)

    Some(hxBox recordExpr ty loc)
  else
    None

let private postProcessFieldExpr ctx recordTySerial tyName tyArgs recordExpr index fieldTy loc =
  if needsBoxedRecordTySerial ctx recordTySerial then
    let ty = tyRecord recordTySerial tyName tyArgs

    Some(HNodeExpr(HRecordItemEN index, [ hxUnbox recordExpr ty loc ], fieldTy, loc))
  else
    None

// -----------------------------------------------
// Control
// -----------------------------------------------

let private abTy (ctx: AbCtx) ty =
  match ty with
  | Ty (RecordTk(tySerial, name), tyArgs) ->
    let ty =
      let tyArgs = tyArgs |> List.map (abTy ctx)
      Ty(RecordTk(tySerial, name), tyArgs)

    match eraseRecordTy ctx ty with
    | Some ty -> ty
    | None -> ty

  // #erase_enum_like_union
  | Ty (UnionTk(tySerial, _), _) when ctx.EnumLikeUnionTys |> TSet.contains tySerial -> tyInt

  | Ty (UnionTk(tySerial, name), tyArgs) ->
    let ty =
      let tyArgs = tyArgs |> List.map (abTy ctx)
      Ty(UnionTk(tySerial, name), tyArgs)

    match unwrapNewtypeUnionTy ctx ty tyArgs with
    | Some ty -> ty
    | None -> ty

  | Ty (_, []) -> ty

  | Ty (tk, tyArgs) ->
    let tyArgs = tyArgs |> List.map (abTy ctx)
    Ty(tk, tyArgs)

let private abPat ctx pat =
  match pat with
  | HLitPat _
  | HDiscardPat _
  | HVarPat _ -> pat |> patMap (abTy ctx)

  | HVariantPat (variantSerial, ty, loc) ->
    let ty = ty |> abTy ctx

    // #erase_enum_like_union
    match (ctx: AbCtx).EnumLikeVariants |> TMap.tryFind variantSerial with
    | Some (_, _, lit) -> HLitPat (lit, loc)
    | _ ->

    match unwrapNewtypeVariantPat ctx variantSerial loc with
    | Some pat -> pat
    | None -> HVariantPat(variantSerial, ty, loc)

  | HNodePat ((HVariantAppPN variantSerial as kind), [ payloadPat ], ty, loc) ->
    let payloadPat = payloadPat |> abPat ctx
    let ty = ty |> abTy ctx

    let payloadPat =
      match postProcessVariantAppPat ctx variantSerial payloadPat with
      | Some payloadPat -> payloadPat
      | None -> payloadPat

    match unwrapNewtypeVariantAppPat ctx variantSerial payloadPat with
    | Some payloadPat -> payloadPat
    | None -> HNodePat(kind, [ payloadPat ], ty, loc)

  | HNodePat (kind, argPats, ty, loc) ->
    let argPats = argPats |> List.map (abPat ctx)
    let ty = ty |> abTy ctx
    HNodePat(kind, argPats, ty, loc)

  | HAsPat (bodyPat, varSerial, loc) ->
    let bodyPat = bodyPat |> abPat ctx
    HAsPat(bodyPat, varSerial, loc)

  | HOrPat (l, r, loc) ->
    let l = l |> abPat ctx
    let r = r |> abPat ctx
    HOrPat(l, r, loc)

let private abExpr ctx expr =
  match expr with
  | HVariantExpr (variantSerial, ty, loc) ->
    let ty = ty |> abTy ctx

    // #erase_enum_like_union
    match (ctx: AbCtx).EnumLikeVariants |> TMap.tryFind variantSerial with
    | Some (_, _, lit) -> HLitExpr (lit, loc)
    | _ ->

    match unwrapNewtypeVariantExpr ctx variantSerial loc with
    | Some expr -> expr
    | None -> HVariantExpr(variantSerial, ty, loc)

  | HNodeExpr (kind, items, ty, loc) ->
    match kind, items with
    | HCallProcEN, [ (HVariantExpr (variantSerial, _, _) as callee); payload ] ->
      let payload = payload |> abExpr ctx
      let ty = ty |> abTy ctx

      let payload =
        match postProcessVariantFunCallExpr ctx variantSerial payload with
        | Some payload -> payload
        | None -> payload

      match unwrapNewtypeVariantCallExpr ctx variantSerial payload with
      | Some payload -> payload
      | None -> hxCallProc callee [ payload ] ty loc

    | HRecordEN, _ ->
      let recordSerial, tyName, tyArgs = unwrapRecordTy ty
      let items = items |> List.map (abExpr ctx)
      let ty = ty |> abTy ctx

      match postProcessRecordExpr ctx recordSerial tyName tyArgs items loc with
      | Some expr -> expr
      | None -> HNodeExpr(HRecordEN, items, ty, loc)

    | HRecordItemEN index, [ recordExpr ] ->
      let recordTySerial, tyName, tyArgs =
        recordExpr |> exprToTy |> unwrapRecordTy

      let recordExpr = recordExpr |> abExpr ctx
      let ty = ty |> abTy ctx

      match postProcessFieldExpr ctx recordTySerial tyName tyArgs recordExpr index ty loc with
      | Some expr -> expr
      | None -> HNodeExpr(HRecordItemEN index, [ recordExpr ], ty, loc)

    | _ ->
      let items = items |> List.map (abExpr ctx)
      let ty = ty |> abTy ctx
      HNodeExpr(kind, items, ty, loc)

  | HLitExpr _ -> expr

  | HVarExpr _
  | HFunExpr _
  | HPrimExpr _ -> expr |> exprMap (abTy ctx)

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond = cond |> abExpr ctx

    let arms =
      arms
      |> List.map (hArmMap (abPat ctx) (abExpr ctx))

    let ty = ty |> abTy ctx
    HMatchExpr(cond, arms, ty, loc)

  | HBlockExpr (stmts, last) ->
    let stmts = stmts |> List.map (abStmt ctx)
    let last = last |> abExpr ctx
    HBlockExpr(stmts, last)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private abStmt ctx stmt =
  match stmt with
  | HExprStmt expr -> HExprStmt(abExpr ctx expr)

  | HLetValStmt (pat, init, loc) ->
    let pat = pat |> abPat ctx
    let init = init |> abExpr ctx
    HLetValStmt(pat, init, loc)

  | HLetFunStmt (callee, args, body, loc) ->
    let args = args |> List.map (abPat ctx)
    let body = body |> abExpr ctx
    HLetFunStmt(callee, args, body, loc)

  | HNativeDeclStmt _ -> unreachable () // Generated in Hoist.

let autoBox (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  // Detect recursion.
  let trdCtx = detectTypeRecursion hirCtx

  // Measure types.
  let tsmCtx: TsmCtx = measureTys trdCtx

  // Auto boxing.
  let ctx =
    let recursiveVariants =
      trdCtx.VariantMemo
      |> TMap.fold
           (fun set (variantSerial, isDirect) status ->
             match isDirect, status with
             | _, Boxed -> set |> TSet.add variantSerial
             | _ -> set)
           (TSet.empty variantSerialCompare)

    // #erase_enum_like_union
    let enumLikeUnionTys, enumLikeVariants =
      hirCtx.Tys |> TMap.fold
        (fun (tySet, variantMap) tySerial tyDef ->
          match tyDef with
          | UnionTyDef (_, _, variants, _) ->
            let isEnumLike =
              variants |> List.forall (fun v ->
                let variantDef = hirCtx.Variants |> mapFind v
                not variantDef.HasPayload
              )

            if isEnumLike then
              let variantMap =
                variants
                |> List.mapi (fun i v -> i, v)
                |> List.fold (fun variantMap (i, v) ->
                  variantMap |> TMap.add v (tySerial, i, IntLit (string i))) variantMap

              tySet |> TSet.add tySerial, variantMap
            else
              tySet, variantMap
          | _ -> tySet, variantMap)
        (TMap.empty compare, TMap.empty variantSerialCompare)

    { ofHirCtx hirCtx with
        BoxedVariants = tsmCtx.BoxedVariants
        BoxedRecordTys = tsmCtx.BoxedRecordTys
        RecursiveVariants = recursiveVariants

        // #erase_enum_like_union
        EnumLikeUnionTys = enumLikeUnionTys
        EnumLikeVariants = enumLikeVariants }

  let abVars vars =
    vars
    |> TMap.map (fun _ (varDef: VarDef) ->
      let ty = varDef.Ty |> abTy ctx
      { varDef with Ty = ty })

  let funs =
    ctx.Funs
    |> TMap.map (fun _ (funDef: FunDef) ->
      let (TyScheme (tyVars, ty)) = funDef.Ty
      let ty = ty |> abTy ctx

      { funDef with Ty = TyScheme(tyVars, ty) })

  let variants =
    ctx.Variants
    |> TMap.map (fun variantSerial (variantDef: VariantDef) ->
      let payloadTy =
        erasePayloadTy ctx variantSerial variantDef.PayloadTy

      { variantDef with PayloadTy = payloadTy })

  let tys =
    ctx.Tys
    |> TMap.map (fun _ tyDef ->
      match tyDef with
      | RecordTyDef (recordName, tyArgs, fields, repr, loc) ->
        let fields =
          fields
          |> List.map (fun (name, ty, loc) ->
            let ty = ty |> abTy ctx
            name, ty, loc)

        RecordTyDef(recordName, tyArgs, fields, repr, loc)

      | _ -> tyDef)

  let ctx =
    { ctx with
        Vars = abVars ctx.Vars
        Funs = funs
        Variants = variants
        Tys = tys }

  let modules =
    modules
    |> List.map (fun (m: HModule) ->
      let vars = abVars m.Vars
      let stmts = m.Stmts |> List.map (abStmt ctx)
      { m with Vars = vars; Stmts = stmts })

  let hirCtx = ctx |> toHirCtx hirCtx
  modules, hirCtx

// ===============================================
// FIXME: split file

// -----------------------------------------------
// Detect use of type vars
// -----------------------------------------------

let private emptyTyVarSet: TreeSet<TySerial> = TSet.empty compare

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TvCtx =
  { Funs: TreeMap<FunSerial, FunDef>
    UsedTyVars: TreeSet<TySerial> }

let private tvTy (ty: Ty) (ctx: TvCtx) : TvCtx =
  let modified, usedTyVars =
    tyCollectFreeVars ty
    |> List.fold
         (fun (modified, tyVars) tySerial ->
           if not modified && TSet.contains tySerial tyVars then
             false, tyVars
           else
             true, TSet.add tySerial tyVars)
         (false, ctx.UsedTyVars)

  if modified then
    { ctx with UsedTyVars = usedTyVars }
  else
    ctx

let private tvPat (pat: HPat) (ctx: TvCtx) : TvCtx =
  let onTy ty ctx = tvTy ty ctx
  let onPat pat ctx = tvPat pat ctx
  let onPats pats ctx = forList tvPat pats ctx

  match pat with
  | HLitPat _ -> ctx
  | HDiscardPat (ty, _) -> onTy ty ctx
  | HVarPat (_, ty, _) -> onTy ty ctx
  | HVariantPat (_, ty, _) -> onTy ty ctx
  | HNodePat (_, argPats, ty, _) -> ctx |> onPats argPats |> onTy ty
  | HAsPat (bodyPat, _, _) -> onPat bodyPat ctx
  | HOrPat (l, r, _) -> ctx |> onPat l |> onPat r

let private tvExpr (expr: HExpr) (ctx: TvCtx) : TvCtx =
  let onTy ty ctx = tvTy ty ctx
  let onPat pat ctx = tvPat pat ctx
  let onPats pats ctx = forList onPat pats ctx
  let onExpr expr ctx = tvExpr expr ctx
  let onExprs exprs ctx = forList tvExpr exprs ctx
  let onStmts stmts ctx = forList tvStmt stmts ctx

  match expr with
  | HLitExpr _ -> ctx

  | HVarExpr (_, ty, _) -> onTy ty ctx
  | HFunExpr (_, ty, _, _) -> onTy ty ctx
  | HVariantExpr (_, ty, _) -> onTy ty ctx
  | HPrimExpr (_, ty, _) -> onTy ty ctx

  | HMatchExpr (cond, arms, ty, _) ->
    ctx
    |> onExpr cond
    |> forList (fun (pat, guard, body) ctx -> ctx |> onPat pat |> onExpr guard |> onExpr body) arms
    |> onTy ty

  | HNodeExpr (_, args, ty, _) -> ctx |> onExprs args |> onTy ty

  | HBlockExpr (stmts, last) -> ctx |> onStmts stmts |> tvExpr last

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private tvStmt stmt ctx =
  let onTy ty ctx = tvTy ty ctx
  let onPat pat ctx = tvPat pat ctx
  let onPats pats ctx = forList onPat pats ctx
  let onExpr expr ctx = tvExpr expr ctx
  let onExprs exprs ctx = forList tvExpr exprs ctx

  match stmt with
  | HExprStmt expr -> onExpr expr ctx

  | HLetValStmt (pat, init, _) -> ctx |> onExpr init |> onPat pat

  | HLetFunStmt (funSerial, args, body, _) ->
    let parent, ctx =
      ctx.UsedTyVars, { ctx with UsedTyVars = emptyTyVarSet }

    let ctx = ctx |> onPats args |> onExpr body

    let ctx =
      let funDef = ctx.Funs |> mapFind funSerial
      let (TyScheme (tyVars, funTy)) = funDef.Ty
      let oldTyVars = tyVars

      let isOwned (tySerial: TySerial) =
        oldTyVars
        |> List.exists (fun tyVar -> tyVar = tySerial)

      let funs =
        let funDef =
          let tyVars =
            tyVars
            |> List.fold (fun tyVars tySerial -> TSet.add tySerial tyVars) ctx.UsedTyVars
            |> TSet.toList

          { funDef with Ty = TyScheme(tyVars, funTy) }

        ctx.Funs |> TMap.add funSerial funDef

      { ctx with
          Funs = funs
          // #TSetUnion
          UsedTyVars =
            TSet.fold
              (fun tySerial tyVars ->
                if isOwned tyVars then
                  tySerial
                else
                  TSet.add tyVars tySerial)
              parent
              ctx.UsedTyVars }

    ctx

  | HNativeDeclStmt _ -> unreachable () // Generated in Hoist.

// -----------------------------------------------
// Compute ty args
// -----------------------------------------------

type private TyMap = TreeMap<TySerial, TyDef>

let private emptyBinding: TreeMap<TySerial, Ty> = TMap.empty compare

/// Generates a binding (from meta ty to ty) by unifying.
let private unifyTy (lTy: Ty) (rTy: Ty) : TreeMap<TySerial, Ty> =
  unifyOneWay (fun binding (tySerial: TySerial) ty -> binding |> TMap.add tySerial ty) emptyBinding lTy rTy

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TaCtx = { Funs: TreeMap<FunSerial, FunDef> }

let private processFunExpr (ctx: TaCtx) itself funSerial useSiteTy loc : HExpr =
  let def: FunDef = ctx.Funs |> mapFind funSerial
  let (TyScheme (tyVars, genericTy)) = def.Ty

  if List.isEmpty tyVars then
    itself
  else
    let binding = unifyTy genericTy useSiteTy

    let tyArgs =
      tyVars
      |> List.map (fun tySerial ->
        binding
        |> TMap.tryFind tySerial
        |> Option.defaultWith (fun () -> tyMeta tySerial loc))

    HFunExpr(funSerial, useSiteTy, tyArgs, loc)

let private taExpr (ctx: TaCtx) (expr: HExpr) : HExpr =
  let onExpr expr = taExpr ctx expr
  let onExprs exprs = List.map (taExpr ctx) exprs
  let onStmts stmts = List.map (taStmt ctx) stmts

  match expr with
  | HLitExpr _
  | HVarExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr

  | HFunExpr (funSerial, useSiteTy, tyArgs, loc) ->
    assert (List.isEmpty tyArgs) // No computed.
    processFunExpr ctx expr funSerial useSiteTy loc

  | HMatchExpr (cond, arms, ty, loc) ->
    let cond = onExpr cond
    let arms = arms |> List.map (hArmMap id onExpr)
    HMatchExpr(cond, arms, ty, loc)

  | HNodeExpr (kind, args, ty, loc) -> HNodeExpr(kind, onExprs args, ty, loc)
  | HBlockExpr (stmts, last) -> HBlockExpr(onStmts stmts, onExpr last)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private taStmt ctx stmt =
  let onExpr expr = taExpr ctx expr

  match stmt with
  | HExprStmt expr -> HExprStmt(onExpr expr)
  | HLetValStmt (pat, init, loc) -> HLetValStmt(pat, onExpr init, loc)
  | HLetFunStmt (callee, args, body, loc) -> HLetFunStmt(callee, args, taExpr ctx body, loc)
  | HNativeDeclStmt _ -> unreachable () // Generated in Hoist.

let computeFunTyArgs (modules: HProgram, hirCtx: HirCtx) : HProgram * HirCtx =
  let hirCtx =
    let ctx: TvCtx =
      { Funs = hirCtx.Funs
        UsedTyVars = TSet.empty compare }

    let ctx =
      modules
      |> HProgram.foldExpr (fun ctx expr -> tvExpr expr ctx) ctx

    { hirCtx with Funs = ctx.Funs }

  let modules =
    let ctx: TaCtx = { Funs = hirCtx.Funs }
    modules |> HProgram.mapExpr (taExpr ctx)

  modules, hirCtx
