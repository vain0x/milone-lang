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

module Int = MiloneStd.StdInt
module TSet = MiloneStd.StdSet
module M = MiloneStd.StdMap

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
  match ctx.VariantMemo |> M.tryFind variantSerial with
  | Some Recursive ->
      // printfn "// trd variant %s is now boxed" (ctx.Variants |> mapFind variantSerial).Name
      { ctx with
          VariantMemo = ctx.VariantMemo |> M.add variantSerial Boxed }

  | Some t ->
      // printfn "// trd variant %s is done: %s" (ctx.Variants |> mapFind variantSerial).Name (objToString t)
      ctx

  | None ->
      // printfn "// trd variant %s begin" (ctx.Variants |> mapFind variantSerial).Name

      let ctx =
        { ctx with
            VariantMemo = ctx.VariantMemo |> M.add variantSerial Recursive }

      let ctx: TrdCtx =
        let variantDef =
          match variantDefOpt with
          | Some variantDef -> variantDef
          | None -> ctx.Variants |> mapFind variantSerial

        trdTy ctx variantDef.PayloadTy

      let ctx =
        match ctx.VariantMemo |> M.tryFind variantSerial with
        | Some Recursive
        | None ->
            { ctx with
                VariantMemo = ctx.VariantMemo |> M.add variantSerial Unboxed }

        | Some _ -> ctx

      // printfn
      //   "// trd variant %s end: %s"
      //   (ctx.Variants |> mapFind variantSerial).Name
      //   (ctx.VariantMemo
      //    |> mapFind variantSerial
      //    |> objToString)
      ctx

let private trdRecordTyDef (ctx: TrdCtx) tySerial tyDef =
  match ctx.RecordTyMemo |> M.tryFind tySerial with
  | Some Recursive ->
      // printfn "// trd tyDef %s is now boxed" (tyDefToName tyDef)
      { ctx with
          RecordTyMemo = ctx.RecordTyMemo |> M.add tySerial Boxed }

  | Some t ->
      // printfn "// trd tyDef %s is done: %s" (tyDefToName tyDef) (objToString t)
      ctx

  | None ->
      // printfn "// trd tyDef %s begin" (tyDefToName tyDef)

      let ctx =
        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> M.add tySerial Recursive }

      let ctx: TrdCtx =
        match tyDef with
        | RecordTyDef (_, fields, _) ->
            fields
            |> List.fold (fun ctx (_, fieldTy, _) -> trdTy ctx fieldTy) ctx

        | _ -> failwith "NEVER"

      let ctx =
        match ctx.RecordTyMemo |> M.tryFind tySerial with
        | Some Recursive
        | None ->
            { ctx with
                RecordTyMemo = ctx.RecordTyMemo |> M.add tySerial Unboxed }

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
  | Ty (tk, tyArgs) ->
      let nominal tySerial =
        trdTyDef ctx tySerial (ctx.Tys |> mapFind tySerial)

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

      | ListTk
      | FunTk
      | TupleTk
      | NativePtrTk _
      | NativeFunTk
      | NativeTypeTk _ -> tyArgs |> List.fold trdTy ctx

      | UnionTk tySerial -> nominal tySerial
      | RecordTk tySerial -> nominal tySerial

      | SynonymTk _
      | UnresolvedTk _
      | UnresolvedVarTk _ -> failwith "NEVER"

let private detectTypeRecursion (tyCtx: TyCtx): TrdCtx =
  let ctx: TrdCtx =
    { Variants = tyCtx.Variants
      Tys = tyCtx.Tys
      VariantMemo = M.empty variantSerialCompare
      RecordTyMemo = M.empty compare }

  let ctx = tyCtx.Tys |> M.fold trdTyDef ctx

  tyCtx.Variants
  |> M.fold (fun ctx variantSerial varDef -> trdVariant ctx variantSerial (Some varDef)) ctx

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
  match ctx.VariantMemo |> M.tryFind variantSerial with
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
            VariantMemo = ctx.VariantMemo |> M.add variantSerial (-1) }

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
                 |> M.tryFind variantSerial
                 |> Option.defaultValue (-1)) < 0)

        { ctx with
            VariantMemo = ctx.VariantMemo |> M.add variantSerial size
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
  match ctx.RecordTyMemo |> M.tryFind tySerial with
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
            RecordTyMemo = ctx.RecordTyMemo |> M.add tySerial (-1) }

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

        | _ -> failwith "NEVER"

      let size, isBoxed =
        if size > 32 then
          8, true
        else
          Int.max 1 size, false

      let ctx =
        assert ((ctx.RecordTyMemo
                 |> M.tryFind tySerial
                 |> Option.defaultValue (-1)) < 0)

        { ctx with
            RecordTyMemo = ctx.RecordTyMemo |> M.add tySerial size
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
  | SynonymTyDef _ -> 1000000, ctx

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

      | SynonymTk _
      | UnresolvedTk _
      | UnresolvedVarTk _ -> failwith "NEVER"

let private measureTys (trdCtx: TrdCtx): TsmCtx =
  let boxedVariants =
    trdCtx.VariantMemo
    |> M.fold
         (fun set variantSerial status ->
           match status with
           | Boxed -> set |> TSet.add variantSerial
           | Unboxed -> set
           | Recursive -> failwith "NEVER")
         (TSet.empty variantSerialCompare)

  let boxedRecordTys =
    trdCtx.RecordTyMemo
    |> M.fold
         (fun set tySerial status ->
           match status with
           | Boxed -> set |> TSet.add tySerial
           | Unboxed -> set
           | Recursive -> failwith "NEVER")
         (TSet.empty compare)

  let ctx: TsmCtx =
    { Variants = trdCtx.Variants
      Tys = trdCtx.Tys
      BoxedVariants = boxedVariants
      BoxedRecordTys = boxedRecordTys
      VariantMemo = M.empty variantSerialCompare
      RecordTyMemo = M.empty compare }

  let ctx =
    ctx.Tys
    |> M.fold (fun ctx tySerial tyDef -> tsmTyDef ctx tySerial tyDef |> snd) ctx

  ctx.Variants
  |> M.fold (fun ctx variantSerial varDef -> tsmVariant ctx variantSerial (Some varDef) |> snd) ctx

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
    BoxedVariants = M.empty variantSerialCompare
    BoxedRecordTys = M.empty compare }

let private toTyCtx (tyCtx: TyCtx) (ctx: AbCtx) =
  { tyCtx with
      Vars = ctx.Vars
      Variants = ctx.Variants
      Tys = ctx.Tys }

let private needsBoxedVariant (ctx: AbCtx) variantSerial =
  ctx.BoxedVariants |> TSet.contains variantSerial

let private needsBoxedRecordTySerial (ctx: AbCtx) tySerial =
  ctx.BoxedRecordTys |> TSet.contains tySerial

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

let private postProcessVariantFunAppExpr ctx kind items =
  match kind, items with
  | HAppEN, [ (HVariantExpr (variantSerial, _, _)) as callee; payload ] when needsBoxedVariant ctx variantSerial ->
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

  | Ty (tk, tyArgs) ->
      let tyArgs = tyArgs |> List.map (abTy ctx)
      Ty(tk, tyArgs)

let private abPat ctx pat =
  match pat with
  | HLitPat _
  | HDiscardPat _
  | HVarPat _
  | HVariantPat _ -> pat |> patMap (abTy ctx) id

  | HNodePat (kind, argPats, ty, loc) ->
      let fail () = failwithf "NEVER: %A" pat

      let argPats = argPats |> List.map (abPat ctx)
      let ty = ty |> abTy ctx

      match kind, argPats with
      | HVariantAppPN variantSerial, [ payloadPat ] ->
          match postProcessVariantAppPat ctx variantSerial payloadPat with
          | Some payloadPat -> HNodePat(kind, [ payloadPat ], ty, loc)
          | None -> HNodePat(kind, argPats, ty, loc)

      | _ -> HNodePat(kind, argPats, ty, loc)

  | HAsPat (bodyPat, varSerial, loc) ->
      let bodyPat = bodyPat |> abPat ctx
      HAsPat(bodyPat, varSerial, loc)

  | HOrPat (l, r, loc) ->
      let l = l |> abPat ctx
      let r = r |> abPat ctx
      HOrPat(l, r, loc)

let private abExpr ctx expr =
  match expr with
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

        match postProcessVariantFunAppExpr ctx kind items with
        | Some (callee, payload) -> hxApp callee payload ty loc
        | None -> HNodeExpr(kind, items, ty, loc)

      doArm ()

  | HLitExpr _
  | HOpenExpr _
  | HTyDeclExpr _ -> expr

  | HVarExpr _
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

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts = stmts |> List.map (abExpr ctx)
        let last = last |> abExpr ctx
        HBlockExpr(stmts, last)

      doArm ()

  | HLetValExpr (vis, pat, init, next, ty, loc) ->
      let doArm () =
        let pat = pat |> abPat ctx
        let init = init |> abExpr ctx
        let next = next |> abExpr ctx
        let ty = ty |> abTy ctx
        HLetValExpr(vis, pat, init, next, ty, loc)

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
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

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
    |> M.map
         (fun _ varDef ->
           match varDef with
           | VarDef (name, sm, ty, loc) ->
               let ty = ty |> abTy ctx
               VarDef(name, sm, ty, loc))

  let funs =
    ctx.Funs
    |> M.map
         (fun _ (funDef: FunDef) ->
           let (TyScheme (tyVars, ty)) = funDef.Ty
           let ty = ty |> abTy ctx

           { funDef with
               Ty = TyScheme(tyVars, ty) })

  let variants =
    ctx.Variants
    |> M.map
         (fun variantSerial (variantDef: VariantDef) ->
           let payloadTy =
             erasePayloadTy ctx variantSerial variantDef.PayloadTy

           let variantTy = variantDef.VariantTy |> abTy ctx

           { variantDef with
               PayloadTy = payloadTy
               VariantTy = variantTy })

  let tys =
    ctx.Tys
    |> M.map
         (fun _ tyDef ->
           match tyDef with
           | SynonymTyDef (name, tyArgs, bodyTy, loc) ->
               let bodyTy = bodyTy |> abTy ctx
               SynonymTyDef(name, tyArgs, bodyTy, loc)

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
