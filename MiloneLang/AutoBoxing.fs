/// ## Auto Boxing
///
/// Provides implicit indirection by inserting allocate/dereference operations.
module rec MiloneLang.AutoBoxing

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers
open MiloneLang.Hir
open MiloneLang.TySystem
open MiloneLang.Typing

let private tyIsRecord ty =
  match ty with
  | AppTy (RecordTyCtor _, _) -> true
  | _ -> false

let private hxBox itemExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Box, tyFun itemTy tyObj, loc)) itemExpr tyObj loc

let private hxUnbox boxExpr itemTy loc =
  hxApp (HPrimExpr(HPrim.Unbox, tyFun tyObj itemTy, loc)) boxExpr itemTy loc

// -----------------------------------------------
// Type recursion detection
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private Status =
  | Recursive
  | Boxed
  | Unboxed

type private TrdCtx =
  { Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    VariantMemo: AssocMap<VariantSerial, Status>
    RecordTyMemo: AssocMap<TySerial, Status> }

let private trdVariant (ctx: TrdCtx) variantSerial (variantDefOpt: VariantDef option) =
  match ctx.VariantMemo |> mapTryFind variantSerial with
  | Some Recursive ->
      // printfn "// trd variant %s is now boxed" (ctx.Variants |> mapFind variantSerial).Name
      { ctx with
          VariantMemo = ctx.VariantMemo |> mapAdd variantSerial Boxed }

  | Some t ->
      // printfn "// trd variant %s is done: %s" (ctx.Variants |> mapFind variantSerial).Name (objToString t)
      ctx

  | None ->
      // printfn "// trd variant %s begin" (ctx.Variants |> mapFind variantSerial).Name

      let ctx =
        { ctx with
            VariantMemo = ctx.VariantMemo |> mapAdd variantSerial Recursive }

      let ctx: TrdCtx =
        let variantDef =
          match variantDefOpt with
          | Some variantDef -> variantDef
          | None -> ctx.Variants |> mapFind variantSerial

        trdTy ctx variantDef.PayloadTy

      let ctx =
        match ctx.VariantMemo |> mapTryFind variantSerial with
        | Some Recursive
        | None ->
            { ctx with
                VariantMemo = ctx.VariantMemo |> mapAdd variantSerial Unboxed }

        | Some _ -> ctx

      // printfn
      //   "// trd variant %s end: %s"
      //   (ctx.Variants |> mapFind variantSerial).Name
      //   (ctx.VariantMemo
      //    |> mapFind variantSerial
      //    |> objToString)
      ctx

let private trdRecordTyDef (ctx: TrdCtx) tySerial tyDef =
  match ctx.RecordTyMemo |> mapTryFind tySerial with
  | Some Recursive ->
      // printfn "// trd tyDef %s is now boxed" (tyDefToName tyDef)
      { ctx with
          RecordTyMemo = ctx.RecordTyMemo |> mapAdd tySerial Boxed }

  | Some t ->
      // printfn "// trd tyDef %s is done: %s" (tyDefToName tyDef) (objToString t)
      ctx

  | None ->
      // printfn "// trd tyDef %s begin" (tyDefToName tyDef)

      let ctx =
        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> mapAdd tySerial Recursive }

      let ctx: TrdCtx =
        match tyDef with
        | RecordTyDef (_, fields, _) ->
            fields
            |> List.fold (fun ctx (_, fieldTy, _) -> trdTy ctx fieldTy) ctx

        | _ -> failwith "NEVER"

      let ctx =
        match ctx.RecordTyMemo |> mapTryFind tySerial with
        | Some Recursive
        | None ->
            { ctx with
                RecordTyMemo = ctx.RecordTyMemo |> mapAdd tySerial Unboxed }

        | Some _ -> ctx

      // printfn "// trd tyDef %s end: %s" (tyDefToName tyDef) (objToString (ctx.RecordTyMemo |> mapFind tySerial))

      ctx

let private trdTyDef (ctx: TrdCtx) tySerial tyDef =
  match tyDef with
  | UnionTyDef (_, variants, _) ->
      variants
      |> List.fold (fun (ctx: TrdCtx) variantSerial -> trdVariant ctx variantSerial None) ctx

  | RecordTyDef _ -> trdRecordTyDef ctx tySerial tyDef

  | MetaTyDef _
  | UniversalTyDef _
  | SynonymTyDef _ -> ctx

let private trdTy (ctx: TrdCtx) ty =
  match ty with
  | ErrorTy _
  | MetaTy _ -> ctx

  | AppTy (tyCtor, tyArgs) ->
      let nominal tySerial =
        trdTyDef ctx tySerial (ctx.Tys |> mapFind tySerial)

      match tyCtor with
      | IntTyCtor _
      | FloatTyCtor _
      | BoolTyCtor
      | CharTyCtor
      | StrTyCtor
      | ObjTyCtor
      | VoidTyCtor ->
          assert (List.isEmpty tyArgs)
          ctx

      | ListTyCtor
      | FunTyCtor
      | TupleTyCtor
      | NativePtrTyCtor _ -> tyArgs |> List.fold trdTy ctx

      | UnionTyCtor tySerial -> nominal tySerial
      | RecordTyCtor tySerial -> nominal tySerial

      | SynonymTyCtor _
      | UnresolvedTyCtor _ -> failwith "NEVER"

let private detectTypeRecursion (tyCtx: TyCtx): TrdCtx =
  let ctx: TrdCtx =
    { Variants = tyCtx.Variants
      Tys = tyCtx.Tys
      VariantMemo = mapEmpty variantSerialCmp
      RecordTyMemo = mapEmpty compare }

  let ctx = tyCtx.Tys |> mapFold trdTyDef ctx

  tyCtx.Variants
  |> mapFold (fun ctx variantSerial varDef -> trdVariant ctx variantSerial (Some varDef)) ctx

// -----------------------------------------------
// Type size measurement
// -----------------------------------------------

type private TsmCtx =
  { Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    BoxedVariants: AssocSet<VariantSerial>
    BoxedRecordTys: AssocSet<TySerial>

    VariantMemo: AssocMap<VariantSerial, int>
    RecordTyMemo: AssocMap<TySerial, int> }

let private tsmVariant (ctx: TsmCtx) variantSerial (variantDefOpt: VariantDef option) =
  match ctx.VariantMemo |> mapTryFind variantSerial with
  | Some size ->
      // printfn "// measure variant %s cached: size=%d" (ctx.Variants |> mapFind variantSerial).Name size
      assert (size >= 0)
      size, ctx

  | _ when ctx.BoxedVariants |> setContains variantSerial ->
      // printfn "// measure variant: %s is boxed" (ctx.Variants |> mapFind variantSerial).Name
      12, ctx

  | None ->
      // printfn "// measure variant %s begin" (ctx.Variants |> mapFind variantSerial).Name

      // Prevent infinite recursion, just in case. (Recursive variants are already boxed.)
      let ctx =
        { ctx with
            VariantMemo = ctx.VariantMemo |> mapAdd variantSerial (-1) }

      let size, (ctx: TsmCtx) =
        let variantDef =
          match variantDefOpt with
          | Some variantDef -> variantDef
          | None -> ctx.Variants |> mapFind variantSerial

        tsmTy ctx variantDef.PayloadTy

      let size, isBoxed =
        if 4 + size > 32 then 8, true else size, false

      let ctx =
        assert ((ctx.VariantMemo
                 |> mapTryFind variantSerial
                 |> Option.defaultValue (-1)) < 0)

        { ctx with
            VariantMemo = ctx.VariantMemo |> mapAdd variantSerial size
            BoxedVariants =
              if isBoxed
              then ctx.BoxedVariants |> setAdd variantSerial
              else ctx.BoxedVariants }

      // printfn
      //   "// measure variant %s end: size=%d%s"
      //   (ctx.Variants |> mapFind variantSerial).Name
      //   size
      //   (if isBoxed then " (boxed)" else "")

      size, ctx

let private tsmRecordTyDef (ctx: TsmCtx) tySerial tyDef =
  match ctx.RecordTyMemo |> mapTryFind tySerial with
  | Some size ->
      // printfn "// measure record %s: cached %d" (tyDefToName tyDef) size
      assert (size >= 1)
      size, ctx

  | _ when ctx.BoxedRecordTys |> setContains tySerial ->
      // printfn "// measure record %s: boxed" (tyDefToName tyDef)
      8, ctx

  | None ->
      // printfn "// measure record %s begin" (tyDefToName tyDef)

      // Just in case of recursion was not detected correctly.
      let ctx =
        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> mapAdd tySerial (-1) }

      let size, (ctx: TsmCtx) =
        match tyDef with
        | RecordTyDef (_, fields, _) ->
            fields
            |> List.fold (fun (totalSize, ctx) (fieldName, fieldTy, _) ->
                 let fieldSize, ctx = tsmTy ctx fieldTy
                 //  printfn "//   field %s size=%d total=%d" fieldName fieldSize (totalSize + fieldSize)
                 totalSize + fieldSize, ctx) (0, ctx)

        | _ -> failwith "NEVER"

      let size, isBoxed =
        if size > 32 then 8, true else intMax 1 size, false

      let ctx =
        assert ((ctx.RecordTyMemo
                 |> mapTryFind tySerial
                 |> Option.defaultValue (-1)) < 0)
        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> mapAdd tySerial size
            BoxedRecordTys = if isBoxed then ctx.BoxedRecordTys |> setAdd tySerial else ctx.BoxedRecordTys }

      // printfn "// measure record %s end: size=%d%s" (tyDefToName tyDef) size (if isBoxed then " (boxed)" else "")
      size, ctx

let private tsmTyDef (ctx: TsmCtx) tySerial tyDef =
  match tyDef with
  | UnionTyDef (_, variants, _) ->
      let payloadSize, ctx =
        variants
        |> List.fold (fun (maxSize, ctx: TsmCtx) variantSerial ->
             let payloadSize, ctx = tsmVariant ctx variantSerial None
             intMax maxSize payloadSize, ctx) (0, ctx)

      4 + payloadSize, ctx

  | RecordTyDef _ -> tsmRecordTyDef ctx tySerial tyDef

  | MetaTyDef _
  | UniversalTyDef _
  | SynonymTyDef _ -> 1000000, ctx

let private tsmTy (ctx: TsmCtx) ty =
  match ty with
  | ErrorTy _
  | MetaTy _ -> 1000000, ctx

  | AppTy (tyCtor, tyArgs) ->
      let nominal tySerial =
        tsmTyDef ctx tySerial (ctx.Tys |> mapFind tySerial)

      match tyCtor with
      | BoolTyCtor
      | CharTyCtor
      | VoidTyCtor -> 1, ctx

      | IntTyCtor flavor -> intFlavorToBytes flavor, ctx
      | FloatTyCtor flavor -> floatFlavorToBytes flavor, ctx

      | ObjTyCtor
      | ListTyCtor
      | NativePtrTyCtor _ -> 8, ctx

      | StrTyCtor
      | FunTyCtor -> 16, ctx

      | TupleTyCtor ->
          let size, ctx =
            tyArgs
            |> List.fold (fun (totalSize, ctx) fieldTy ->
                 let size, ctx = tsmTy ctx fieldTy
                 totalSize + size, ctx) (0, ctx)

          intMax 1 size, ctx

      | UnionTyCtor tySerial -> nominal tySerial
      | RecordTyCtor tySerial -> nominal tySerial

      | SynonymTyCtor _
      | UnresolvedTyCtor _ -> failwith "NEVER"

let private measureTys (trdCtx: TrdCtx): TsmCtx =
  let boxedVariants =
    trdCtx.VariantMemo
    |> mapFold (fun set variantSerial status ->
         match status with
         | Boxed -> set |> setAdd variantSerial
         | Unboxed -> set
         | Recursive -> failwith "NEVER") (setEmpty variantSerialCmp)

  let boxedRecordTys =
    trdCtx.RecordTyMemo
    |> mapFold (fun set tySerial status ->
         match status with
         | Boxed -> set |> setAdd tySerial
         | Unboxed -> set
         | Recursive -> failwith "NEVER") (setEmpty compare)

  let ctx: TsmCtx =
    { Variants = trdCtx.Variants
      Tys = trdCtx.Tys
      BoxedVariants = boxedVariants
      BoxedRecordTys = boxedRecordTys
      VariantMemo = mapEmpty variantSerialCmp
      RecordTyMemo = mapEmpty compare }

  let ctx =
    ctx.Tys
    |> mapFold (fun ctx tySerial tyDef -> tsmTyDef ctx tySerial tyDef |> snd) ctx

  ctx.Variants
  |> mapFold (fun ctx variantSerial varDef -> tsmVariant ctx variantSerial (Some varDef) |> snd) ctx

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type private AbCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    BoxedVariants: AssocSet<VariantSerial>
    BoxedRecordTys: AssocSet<TySerial> }

let private ofTyCtx (tyCtx: TyCtx): AbCtx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys
    BoxedVariants = mapEmpty variantSerialCmp
    BoxedRecordTys = mapEmpty compare }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  { tyCtx with
      Vars = ctx.Vars
      Variants = ctx.Variants
      Tys = ctx.Tys }

let private needsBoxedVariant (ctx: AbCtx) variantSerial =
  ctx.BoxedVariants |> setContains variantSerial

let private needsBoxedRecordTySerial (ctx: AbCtx) tySerial =
  ctx.BoxedRecordTys |> setContains tySerial

let private needsBoxedRecordTy ctx ty =
  match ty with
  | AppTy (RecordTyCtor tySerial, _) -> needsBoxedRecordTySerial ctx tySerial
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
  if needsBoxedVariant ctx variantSerial then tyObj else payloadTy |> abTy ctx

let private postProcessVariantCallPat ctx calleePat argPats =
  match calleePat, argPats with
  | HVariantPat (variantSerial, variantTy, loc), [ payloadPat ] when needsBoxedVariant ctx variantSerial ->
      // FIXME: ty is now wrong. ty is previously T -> U where U: union, T: payload, but now obj -> U.
      assert (tyIsFun variantTy)
      Some(HBoxPat(payloadPat, loc))

  | _ -> None

let private postProcessVariantFunAppExpr ctx infOp items =
  match infOp, items with
  | InfOp.App, [ (HVariantExpr (variantSerial, _, _)) as callee; payload ] when needsBoxedVariant ctx variantSerial ->
      // FIXME: ty is now wrong for the same reason as call-variant pattern.
      let ty, loc = exprExtract payload
      Some(callee, hxBox payload ty loc)

  | _ -> None

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
  if needsBoxedRecordTy ctx ty then Some tyObj else None

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
    assert (recordExpr |> exprToTy |> tyEq tyObj)

    Some(HNavExpr(hxUnbox recordExpr recordTy loc, fieldName, fieldTy, loc))
  else
    None

// -----------------------------------------------
// Control
// -----------------------------------------------

let private abTy ctx ty =
  match ty with
  | AppTy (RecordTyCtor _, tyArgs) ->
      assert (List.isEmpty tyArgs)

      match eraseRecordTy ctx ty with
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

  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

let autoBox (expr: HExpr, tyCtx: TyCtx) =
  // Detect recursion.
  let trdCtx = detectTypeRecursion tyCtx

  // Measure types.
  let tsmCtx: TsmCtx = measureTys trdCtx

  // Auto boxing.
  let ctx =
    { ofTyCtx tyCtx with
        BoxedVariants = tsmCtx.BoxedVariants
        BoxedRecordTys = tsmCtx.BoxedRecordTys }

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
    |> mapMap (fun variantSerial (variantDef: VariantDef) ->
         let payloadTy =
           erasePayloadTy ctx variantSerial variantDef.PayloadTy

         let variantTy = variantDef.VariantTy |> abTy ctx

         { variantDef with
             PayloadTy = payloadTy
             VariantTy = variantTy })

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
