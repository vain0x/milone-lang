/// ## Auto Boxing
///
/// Provides implicit indirection by inserting allocate/dereference operations.
module rec MiloneTranslation.AutoBoxing

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir

module Int = MiloneStd.StdInt
module TSet = MiloneStd.StdSet
module TMap = MiloneStd.StdMap

let private tyIsRecord ty =
  match ty with
  | Ty (RecordTk _, _) -> true
  | _ -> false

let private hxBox itemExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) itemExpr tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) boxExpr itemTy loc

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
  { Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    /// ((variantSerial, IsDirect) -> Boxed) means:
    ///     The variant should be boxed because it is recursive without indirection.
    /// ((variantSerial, IsIndirect) -> Boxed) means:
    ///     The variant is indirectly recursive (i.e. by following pointers).
    VariantMemo: AssocMap<VariantSerial * IsDirect, Status>

    RecordTyMemo: AssocMap<TySerial * IsDirect, Status> }

let private trdVariant isDirect (ctx: TrdCtx) variantSerial (variantDefOpt: VariantDef option) =
  match ctx.VariantMemo
        |> TMap.tryFind (variantSerial, isDirect) with
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

      let ctx : TrdCtx =
        let variantDef =
          match variantDefOpt with
          | Some variantDef -> variantDef
          | None -> ctx.Variants |> mapFind variantSerial

        trdTy isDirect ctx variantDef.PayloadTy

      let ctx =
        match ctx.VariantMemo
              |> TMap.tryFind (variantSerial, isDirect) with
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
  match ctx.RecordTyMemo
        |> TMap.tryFind (tySerial, isDirect) with
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

      let ctx : TrdCtx =
        match tyDef with
        | RecordTyDef (_, fields, _) ->
            fields
            |> List.fold (fun ctx (_, fieldTy, _) -> trdTy isDirect ctx fieldTy) ctx

        | _ -> unreachable ()

      let ctx =
        match ctx.RecordTyMemo
              |> TMap.tryFind (tySerial, isDirect) with
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
  | UnionTyDef (_, variants, _) ->
      variants
      |> List.fold (fun (ctx: TrdCtx) variantSerial -> trdVariant isDirect ctx variantSerial None) ctx

  | RecordTyDef _ -> trdRecordTyDef isDirect ctx tySerial tyDef

  | MetaTyDef _
  | UniversalTyDef _
  | SynonymTyDef _ -> unreachable () // Resolved in Typing.

let private trdTy isDirect (ctx: TrdCtx) ty : TrdCtx =
  match ty with
  | Ty (tk, tyArgs) ->
      let nominal tySerial =
        trdTyDef isDirect ctx tySerial (ctx.Tys |> mapFind tySerial)

      match tk with
      | ErrorTk _
      | IntTk _
      | FloatTk _
      | BoolTk
      | CharTk
      | StrTk
      | ObjTk
      | VoidTk
      | MetaTk _ ->
          assert (List.isEmpty tyArgs)
          ctx

      | ListTk -> tyArgs |> List.fold (trdTy IsIndirect) ctx

      | OptionTk
      | FunTk
      | TupleTk
      | NativePtrTk _
      | NativeFunTk
      | NativeTypeTk _ -> tyArgs |> List.fold (trdTy isDirect) ctx

      | UnionTk tySerial -> nominal tySerial
      | RecordTk tySerial -> nominal tySerial

      | SynonymTk _ -> unreachable () // Resolved in Typing.

      | UnresolvedTk _
      | UnresolvedVarTk _ -> unreachable () // Resolved in NameRes.

let private detectTypeRecursion (tyCtx: TyCtx) : TrdCtx =
  let ctx : TrdCtx =
    { Variants = tyCtx.Variants
      Tys = tyCtx.Tys
      VariantMemo = TMap.empty (pairCompare variantSerialCompare compareIsDirect)
      RecordTyMemo = TMap.empty (pairCompare compare compareIsDirect) }

  let doAll isDirect ctx =
    let ctx =
      tyCtx.Tys |> TMap.fold (trdTyDef isDirect) ctx

    tyCtx.Variants
    |> TMap.fold (fun ctx variantSerial varDef -> trdVariant isDirect ctx variantSerial (Some varDef)) ctx

  ctx |> doAll IsDirect |> doAll IsIndirect

// -----------------------------------------------
// Type size measurement
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TsmCtx =
  { Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    BoxedVariants: AssocSet<VariantSerial>
    BoxedRecordTys: AssocSet<TySerial>

    VariantMemo: AssocMap<VariantSerial, int>
    RecordTyMemo: AssocMap<TySerial, int> }

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
        { ctx with
            VariantMemo = ctx.VariantMemo |> TMap.add variantSerial (-1) }

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
        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> TMap.add tySerial (-1) }

      let size, (ctx: TsmCtx) =
        match tyDef with
        | RecordTyDef (_, fields, _) ->
            fields
            |> List.fold
                 (fun (totalSize, ctx) (fieldName, fieldTy, _) ->
                   let fieldSize, ctx = tsmTy ctx fieldTy
                   //  printfn "//   field %s size=%d total=%d" fieldName fieldSize (totalSize + fieldSize)
                   totalSize + fieldSize, ctx)
                 (0, ctx)

        | _ -> unreachable ()

      let size, isBoxed =
        if size > 32 then
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
  | UnionTyDef (_, variants, _) ->
      let payloadSize, ctx =
        variants
        |> List.fold
             (fun (maxSize, ctx: TsmCtx) variantSerial ->
               let payloadSize, ctx = tsmVariant ctx variantSerial None
               Int.max maxSize payloadSize, ctx)
             (0, ctx)

      4 + payloadSize, ctx

  | RecordTyDef _ -> tsmRecordTyDef ctx tySerial tyDef

  | MetaTyDef _
  | UniversalTyDef _
  | SynonymTyDef _ -> unreachable () // Resolved in Typing.

let private tsmTy (ctx: TsmCtx) ty =
  match ty with
  | Ty (tk, tyArgs) ->
      let nominal tySerial =
        tsmTyDef ctx tySerial (ctx.Tys |> mapFind tySerial)

      match tk with
      | BoolTk
      | CharTk
      | VoidTk -> 1, ctx

      | IntTk flavor -> intFlavorToBytes flavor, ctx
      | FloatTk flavor -> floatFlavorToBytes flavor, ctx

      | ObjTk
      | ListTk
      | NativePtrTk _
      | NativeFunTk -> 8, ctx

      | StrTk
      | FunTk -> 16, ctx

      | OptionTk ->
          match tyArgs with
          | [ itemTy ] ->
              let size, ctx = tsmTy ctx itemTy
              1 + size, ctx

          | _ -> unreachable ()

      | TupleTk ->
          let size, ctx =
            tyArgs
            |> List.fold
                 (fun (totalSize, ctx) fieldTy ->
                   let size, ctx = tsmTy ctx fieldTy
                   totalSize + size, ctx)
                 (0, ctx)

          Int.max 1 size, ctx

      | UnionTk tySerial -> nominal tySerial
      | RecordTk tySerial -> nominal tySerial

      | ErrorTk _
      | MetaTk _
      | NativeTypeTk _ -> 1000000, ctx

      | SynonymTk _ -> unreachable () // Resolved in Typing.

      | UnresolvedTk _
      | UnresolvedVarTk _ -> unreachable () // Resolved in NameRes.

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

  let ctx : TsmCtx =
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
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    BoxedVariants: AssocSet<VariantSerial>
    BoxedRecordTys: AssocSet<TySerial>

    RecursiveVariants: AssocSet<VariantSerial> }

let private ofTyCtx (tyCtx: TyCtx) : AbCtx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    BoxedVariants = TMap.empty variantSerialCompare
    BoxedRecordTys = TMap.empty compare
    RecursiveVariants = TMap.empty variantSerialCompare }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  { tyCtx with
      Vars = ctx.Vars
      Funs = ctx.Funs
      Variants = ctx.Variants
      Tys = ctx.Tys }

let private needsBoxedVariant (ctx: AbCtx) variantSerial =
  ctx.BoxedVariants |> TSet.contains variantSerial

let private needsBoxedRecordTySerial (ctx: AbCtx) tySerial =
  ctx.BoxedRecordTys |> TSet.contains tySerial

let private isRecursiveVariant (ctx: AbCtx) variantSerial =
  ctx.RecursiveVariants
  |> TSet.contains variantSerial

let private needsBoxedRecordTy ctx ty =
  match ty with
  | Ty (RecordTk tySerial, _) -> needsBoxedRecordTySerial ctx tySerial
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

let private postProcessVariantFunAppExpr ctx variantSerial payload : HExpr option =
  if needsBoxedVariant ctx variantSerial then
    // FIXME: ty is now wrong for the same reason as call-variant pattern.
    let ty, loc = exprExtract payload
    Some(hxBox payload ty loc)
  else
    None

/// ### Unwrapping newtype variants

let private unwrapNewtypeUnionTy (ctx: AbCtx) ty : Ty option =
  let asNewtypeVariant ty =
    match ty with
    | Ty (UnionTk tySerial, _) ->
        match ctx.Tys |> mapFind tySerial with
        | UnionTyDef (_, [ variantSerial ], _) when not (isRecursiveVariant ctx variantSerial) -> Some variantSerial
        | _ -> None
    | _ -> None

  match asNewtypeVariant ty with
  | Some variantSerial ->
      let variantDef = ctx.Variants |> mapFind variantSerial
      assert variantDef.IsNewtype

      erasePayloadTy ctx variantSerial variantDef.PayloadTy
      |> Some

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

  if not (isRecursiveVariant ctx variantSerial)
     && variantDef.IsNewtype then
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

let private unwrapNewtypeVariantAppExpr (ctx: AbCtx) variantSerial payload : HExpr option =
  let variantDef = ctx.Variants |> mapFind variantSerial

  if not (isRecursiveVariant ctx variantSerial)
     && variantDef.IsNewtype then
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

let private eraseRecordTy ctx ty =
  if needsBoxedRecordTy ctx ty then
    Some tyObj
  else
    None

let private postProcessRecordExpr ctx baseOpt fields recordTy loc =
  if needsBoxedRecordTy ctx recordTy then
    let baseOpt =
      baseOpt
      |> Option.map (fun expr -> hxUnbox expr recordTy loc)

    let recordExpr =
      HRecordExpr(baseOpt, fields, recordTy, loc)

    Some(hxBox recordExpr recordTy loc)
  else
    None

let private postProcessFieldExpr ctx recordExpr recordTy fieldName fieldTy loc =
  if needsBoxedRecordTy ctx recordTy then
    assert (recordExpr |> exprToTy |> tyEqual tyObj)

    Some(HNavExpr(hxUnbox recordExpr recordTy loc, fieldName, fieldTy, loc))
  else
    None

// -----------------------------------------------
// Control
// -----------------------------------------------

let private abTy ctx ty =
  match ty with
  | Ty (RecordTk _, tyArgs) ->
      assert (List.isEmpty tyArgs)

      match eraseRecordTy ctx ty with
      | Some ty -> ty
      | None -> ty

  | Ty (UnionTk _, tyArgs) ->
      assert (List.isEmpty tyArgs)

      match unwrapNewtypeUnionTy ctx ty with
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
  | HVarPat _ -> pat |> patMap (abTy ctx) id

  | HVariantPat (variantSerial, ty, loc) ->
      let doArm () =
        let ty = ty |> abTy ctx

        match unwrapNewtypeVariantPat ctx variantSerial loc with
        | Some pat -> pat
        | None -> HVariantPat(variantSerial, ty, loc)

      doArm ()

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
      let doArm () =
        let ty = ty |> abTy ctx

        match unwrapNewtypeVariantExpr ctx variantSerial loc with
        | Some expr -> expr
        | None -> HVariantExpr(variantSerial, ty, loc)

      doArm ()

  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        assert (tyIsRecord ty)

        let baseOpt = baseOpt |> Option.map (abExpr ctx)

        let fields =
          fields
          |> List.map
               (fun (name, init, loc) ->
                 let init = init |> abExpr ctx
                 name, init, loc)

        match postProcessRecordExpr ctx baseOpt fields ty loc with
        | Some expr -> expr
        | None -> HRecordExpr(baseOpt, fields, ty, loc)

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let recordTy = l |> exprToTy
        assert (tyIsRecord recordTy)

        let l = l |> abExpr ctx
        let ty = ty |> abTy ctx

        match postProcessFieldExpr ctx l recordTy r ty loc with
        | Some expr -> expr
        | None -> HNavExpr(l, r, ty, loc)

      doArm ()

  | HNodeExpr (kind, items, ty, loc) ->
      let doArm () =
        let items = items |> List.map (abExpr ctx)
        let ty = ty |> abTy ctx

        match kind, items with
        | HAppEN, [ (HVariantExpr (variantSerial, _, _) as callee); payload ] ->
            let payload =
              match postProcessVariantFunAppExpr ctx variantSerial payload with
              | Some payload -> payload
              | None -> payload

            match unwrapNewtypeVariantAppExpr ctx variantSerial payload with
            | Some payload -> payload
            | None -> hxApp callee payload ty loc

        | _ -> HNodeExpr(kind, items, ty, loc)

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HVarExpr _
  | HFunExpr _
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

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts = stmts |> List.map (abExpr ctx)
        let last = last |> abExpr ctx
        HBlockExpr(stmts, last)

      doArm ()

  | HLetValExpr (pat, init, next, ty, loc) ->
      let doArm () =
        let pat = pat |> abPat ctx
        let init = init |> abExpr ctx
        let next = next |> abExpr ctx
        let ty = ty |> abTy ctx
        HLetValExpr(pat, init, next, ty, loc)

      doArm ()

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
      let doArm () =
        let args = args |> List.map (abPat ctx)
        let body = body |> abExpr ctx
        let next = next |> abExpr ctx
        let ty = ty |> abTy ctx
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc)

      doArm ()

  | HModuleExpr _
  | HModuleSynonymExpr _ -> unreachable () // Resolved in NameRes.

let autoBox (expr: HExpr, tyCtx: TyCtx) =
  // Detect recursion.
  let trdCtx = detectTypeRecursion tyCtx

  // Measure types.
  let tsmCtx : TsmCtx = measureTys trdCtx

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

    { ofTyCtx tyCtx with
        BoxedVariants = tsmCtx.BoxedVariants
        BoxedRecordTys = tsmCtx.BoxedRecordTys
        RecursiveVariants = recursiveVariants }

  let vars =
    ctx.Vars
    |> TMap.map
         (fun _ (varDef: VarDef) ->
           let ty = varDef.Ty |> abTy ctx
           { varDef with Ty = ty })

  let funs =
    ctx.Funs
    |> TMap.map
         (fun _ (funDef: FunDef) ->
           let (TyScheme (tyVars, ty)) = funDef.Ty
           let ty = ty |> abTy ctx

           { funDef with
               Ty = TyScheme(tyVars, ty) })

  let variants =
    ctx.Variants
    |> TMap.map
         (fun variantSerial (variantDef: VariantDef) ->
           let payloadTy =
             erasePayloadTy ctx variantSerial variantDef.PayloadTy

           { variantDef with
               PayloadTy = payloadTy })

  let tys =
    ctx.Tys
    |> TMap.map
         (fun _ tyDef ->
           match tyDef with
           | RecordTyDef (recordName, fields, loc) ->
               let fields =
                 fields
                 |> List.map
                      (fun (name, ty, loc) ->
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
