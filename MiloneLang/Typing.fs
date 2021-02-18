/// Infers the type of expressions.
///
/// The algorithm is based on Didier Rémy's rank-based Hindley-Milner type inference:
///   - [eq-theory-on-types.pdf](http://gallium.inria.fr/~remy/ftp/eq-theory-on-types.pdf)
///
/// This web article (written in English) is very helpful:
///   - [Efficient and Insightful Generalization](http://okmij.org/ftp/ML/generalization.html)
///
/// and this one (written in Japanese) too:
///   - [OCaml でも採用されているレベルベースの多相型型推論とは](https://rhysd.hatenablog.com/entry/2017/12/16/002048)

module rec MiloneLang.Typing

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TySystem
open MiloneLang.NameRes
open MiloneLang.Hir

module StdInt = MiloneStd.StdInt
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type TyCtx =
  {
    /// Next serial number.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    Serial: Serial

    /// Variable serial to variable definition.
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    /// Type serial to type definition.
    Tys: AssocMap<TySerial, TyDef>

    TyLevels: AssocMap<TySerial, Level>
    Level: Level
    TraitBounds: (Trait * Loc) list
    Logs: (Log * Loc) list }

let private addLog (ctx: TyCtx) log loc =
  { ctx with
      Logs = (log, loc) :: ctx.Logs }

let private addError (ctx: TyCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

/// Be carefully. Levels must be counted the same as name resolution.
let private incLevel (ctx: TyCtx) = { ctx with Level = ctx.Level + 1 }

let private decLevel (ctx: TyCtx) = { ctx with Level = ctx.Level - 1 }

let private findVar (ctx: TyCtx) serial = ctx.Vars |> mapFind serial

let private findTy tySerial (ctx: TyCtx) = ctx.Tys |> mapFind tySerial

let private getTyLevel tySerial (ctx: TyCtx): Level =
  ctx.TyLevels
  |> TMap.tryFind tySerial
  |> Option.defaultValue 0

let private isNewtypeVariant (ctx: TyCtx) variantSerial =
  match ctx
        |> findTy
             (ctx.Variants |> mapFind variantSerial)
               .UnionTySerial with
  | UnionTyDef (_, [ _ ], _) -> true
  | _ -> false

let private isMainFun funSerial (ctx: TyCtx) =
  match ctx.MainFunOpt with
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
  | _ -> false

let private freshVar (ctx: TyCtx) hint ty loc =
  let varSerial = VarSerial(ctx.Serial + 1)

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> TMap.add varSerial (VarDef(hint, AutoSM, ty, loc)) }

  varSerial, ctx

let private freshTySerial (ctx: TyCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        TyLevels = ctx.TyLevels |> TMap.add serial ctx.Level }

  serial, ctx

let private freshMetaTy loc (ctx: TyCtx): Ty * TyCtx =
  let serial, ctx = freshTySerial ctx
  let ty = tyMeta serial loc
  ty, ctx

let private freshMetaTyForPat pat ctx =
  let _, loc = pat |> patExtract
  let tySerial, ctx = ctx |> freshTySerial
  let ty = tyMeta tySerial loc
  ty, ctx

let private freshMetaTyForExpr expr ctx =
  let _, loc = expr |> exprExtract
  let tySerial, ctx = ctx |> freshTySerial
  let ty = tyMeta tySerial loc
  ty, ctx

let private validateLit ctx lit loc =
  // FIXME: validate float too
  match lit with
  | IntLit text ->
      match StdInt.tryParse text with
      | Some _ -> ctx
      | None -> addLog ctx Log.LiteralRangeError loc

  | _ -> ctx

// -----------------------------------------------
// Type inference algorithm
// -----------------------------------------------

let private emptyBinding: AssocMap<TySerial, Ty> = TMap.empty compare

let private toTyContext (ctx: TyCtx): TyContext =
  { Serial = ctx.Serial
    Level = ctx.Level
    Tys = ctx.Tys
    TyLevels = ctx.TyLevels
    Binding = emptyBinding
    LevelChanges = emptyTyLevels }

let private withTyContext (ctx: TyCtx) logAcc (tyCtx: TyContext): TyCtx =
  let tys, tyLevels =
    TMap.fold
      (fun (tys, tyLevels) tySerial ty ->
        let tys = tys |> TMap.add tySerial (MetaTyDef ty)
        let tyLevels = tyLevels |> TMap.add tySerial ctx.Level
        tys, tyLevels)
      (ctx.Tys, ctx.TyLevels)
      tyCtx.Binding

  let tyLevels =
    TMap.fold
      (fun tyLevels tySerial level ->
        if level = 0 then
          tyLevels |> TMap.remove tySerial |> snd
        else
          tyLevels |> TMap.add tySerial level)
      tyLevels
      tyCtx.LevelChanges

  { ctx with
      Serial = tyCtx.Serial
      Tys = tys
      TyLevels = tyLevels
      Logs = logAcc }

let private addTraitBounds traits (ctx: TyCtx) =
  { ctx with
      TraitBounds = List.append traits ctx.TraitBounds }

let private resolveTraitBounds (ctx: TyCtx) =
  let rec go logAcc traits ctx =
    match traits with
    | [] -> logAcc, ctx

    | (theTrait, loc) :: traits ->
        let logAcc, ctx =
          typingResolveTraitBound logAcc ctx theTrait loc

        ctx |> go logAcc traits

  let traits = ctx.TraitBounds |> List.rev
  let ctx = { ctx with TraitBounds = [] }

  let logAcc, tyCtx =
    ctx |> toTyContext |> go ctx.Logs traits

  withTyContext ctx logAcc tyCtx

let private substTy (ctx: TyCtx) ty: Ty =
  let substMeta tySerial =
    match ctx.Tys |> TMap.tryFind tySerial with
    | Some (MetaTyDef ty) -> Some ty
    | _ -> None

  tySubst substMeta ty

/// Substitutes bound meta tys in a ty.
/// Unbound meta tys are degenerated, i.e. replaced with unit.
let private substOrDegenerateTy (ctx: TyCtx) ty =
  let substMeta tySerial =
    match ctx.Tys |> TMap.tryFind tySerial with
    | Some (MetaTyDef ty) -> Some ty

    | Some (UniversalTyDef _) -> None

    | _ ->
        let level = getTyLevel tySerial ctx
        // Degenerate unless quantified.
        if level < 1000000000 then
          Some tyUnit
        else
          None

  tySubst substMeta ty

let private unifyTy (ctx: TyCtx) loc (lty: Ty) (rty: Ty): TyCtx =
  let unifyCtx: UnifyCtx =
    { Serial = ctx.Serial
      Binding = emptyBinding
      LevelChanges = emptyTyLevels
      LogAcc = ctx.Logs }

  let unifyCtx: UnifyCtx =
    typingUnify ctx.Level ctx.Tys ctx.TyLevels lty rty loc unifyCtx

  // FIXME: dup with withTyContext
  let tys, tyLevels =
    TMap.fold
      (fun (tys, tyLevels) tySerial ty ->
        let tys = tys |> TMap.add tySerial (MetaTyDef ty)
        let tyLevels = tyLevels |> TMap.add tySerial ctx.Level
        tys, tyLevels)
      (ctx.Tys, ctx.TyLevels)
      unifyCtx.Binding

  let tyLevels =
    TMap.fold
      (fun tyLevels tySerial level ->
        if level = 0 then
          tyLevels |> TMap.remove tySerial |> snd
        else
          tyLevels |> TMap.add tySerial level)
      tyLevels
      unifyCtx.LevelChanges
  // /dup

  { ctx with
      Serial = unifyCtx.Serial
      Tys = tys
      TyLevels = tyLevels
      Logs = unifyCtx.LogAcc }

let private unifyVarTy varSerial tyOpt loc ctx =
  let varTy, ctx =
    match findVar ctx varSerial with
    | VarDef (_, _, ty, _) -> ty, ctx

  match tyOpt with
  | Some ty ->
      let ctx = unifyTy ctx loc varTy ty
      varTy, ctx

  | None -> varTy, ctx

/// Assume all bound type variables are resolved by `substTy`.
///
/// `isOwned` checks if the type variable is introduced by the most recent `let`.
/// For example, `let f x = (let g = f in g x)` will have too generic type
/// without this checking (according to TaPL).
let tyGeneralize isOwned (ty: Ty) =
  let fvs =
    tyCollectFreeVars ty |> List.filter isOwned

  TyScheme(fvs, ty)

let private instantiateTyScheme (ctx: TyCtx) (tyScheme: TyScheme) loc =
  match tyScheme with
  | TyScheme ([], ty) -> ty, [], ctx

  | TyScheme (fvs, ty) ->
      let serial, tyLevels, ty, assignment =
        doInstantiateTyScheme ctx.Serial ctx.Level ctx.TyLevels fvs ty loc

      ty,
      assignment,
      { ctx with
          Serial = serial
          TyLevels = tyLevels }

let private instantiateTySpec loc (TySpec (polyTy, traits), ctx: TyCtx) =
  let polyTy, assignment, ctx =
    let tyScheme =
      TyScheme(tyCollectFreeVars polyTy, polyTy)

    instantiateTyScheme ctx tyScheme loc

  // Replace type variables also in trait bounds.
  let traits =
    let substMeta = tyAssign assignment

    traits
    |> List.map (fun theTrait -> theTrait |> traitMapTys substMeta, loc)

  polyTy, traits, ctx

let private generalizeFun (ctx: TyCtx) (outerLevel: Level) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial

  match funDef.Ty with
  | TyScheme ([], funTy) ->
      let isOwned tySerial =
        let level = getTyLevel tySerial ctx
        level > outerLevel

      let funTy = substTy ctx funTy
      let funTyScheme = tyGeneralize isOwned funTy

      let ctx =
        { ctx with
            Funs =
              ctx.Funs
              |> TMap.add funSerial { funDef with Ty = funTyScheme } }

      // Mark generalized meta tys (universally quantified vars),
      // by increasing their level to infinite (10^9).
      let ctx =
        let (TyScheme (fvs, _)) = funTyScheme

        { ctx with
            TyLevels =
              fvs
              |> List.fold (fun tyLevels fv -> tyLevels |> TMap.add fv 1000000000) ctx.TyLevels }

      ctx

  | _ -> failwith "Can't generalize already-generalized functions"

let private castFunAsNativeFun funSerial (ctx: TyCtx): Ty * TyCtx =
  let funDef = ctx.Funs |> mapFind funSerial

  // Mark this function as extern "C".
  let ctx =
    { ctx with
        Funs =
          ctx.Funs
          |> TMap.add funSerial { funDef with Abi = CAbi } }


  let nativeFunTy =
    let (TyScheme (_, ty)) = funDef.Ty

    let ty =
      typingExpandSynonyms (toTyContext ctx) ty

    let _, paramTys, resultTy = tyToArgList ty
    tyNativeFun paramTys resultTy

  nativeFunTy, ctx

/// Resolves ascription type.
///
/// Current level is assigned to `'T`s and `_`s.
let private resolveAscriptionTy ctx ascriptionTy =
  let rec go (ty, ctx: TyCtx) =
    match ty with
    | Ty (ErrorTk _, _) -> ty, ctx

    | Ty (MetaTk (serial, loc), _) when ctx.TyLevels |> TMap.containsKey serial |> not ->
        let ctx =
          { ctx with
              TyLevels = ctx.TyLevels |> TMap.add serial ctx.Level }

        tyMeta serial loc, ctx

    | Ty (MetaTk _, _) -> ty, ctx

    | Ty (_, []) -> ty, ctx

    | Ty (tk, tys) ->
        let tys, ctx = (tys, ctx) |> stMap go
        Ty(tk, tys), ctx

  go (ascriptionTy, ctx)

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

/// Creates an expression to abort.
let private hxAbort (ctx: TyCtx) loc =
  let ty, ctx = ctx |> freshMetaTy loc
  let funTy = tyFun tyInt ty
  let exitExpr = HPrimExpr(HPrim.Exit, funTy, loc)

  let callExpr =
    hxApp exitExpr (HLitExpr(IntLit "1", loc)) ty loc

  callExpr, ty, ctx

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private inferLitPat ctx pat lit =
  let ctx = validateLit ctx lit (patToLoc pat)
  pat, litToTy lit, ctx

/// Tries to get ty ascription from pat.
let private patToAscriptionTy pat =
  match pat with
  | HNodePat (HAscribePN, _, ty, _) -> Some ty

  | HAsPat (bodyPat, _, _) -> patToAscriptionTy bodyPat

  | HOrPat (l, r, _) ->
      match patToAscriptionTy l with
      | None -> patToAscriptionTy r
      | it -> it

  | _ -> None

let private inferNilPat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyList itemTy
  HNodePat(HNilPN, [], ty, loc), ty, ctx

let private inferNonePat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyOption itemTy
  HNodePat(HNonePN, [], tyOption ty, loc), ty, ctx

let private inferSomePat ctx pat loc =
  let unknownTy, ctx = ctx |> freshMetaTyForPat pat

  let ctx =
    addError ctx "Some pattern must be used in the form of: `Some pattern`." loc

  hpAbort unknownTy loc, unknownTy, ctx

let private inferDiscardPat ctx pat loc =
  let ty, ctx = ctx |> freshMetaTyForPat pat
  HDiscardPat(ty, loc), ty, ctx

let private inferVarPat (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc
  HVarPat(varSerial, ty, loc), ty, ctx

let private inferVariantPat (ctx: TyCtx) variantSerial loc =
  let variantDef = ctx.Variants |> mapFind variantSerial
  let ty = variantDef.VariantTy

  let ctx =
    if variantDef.HasPayload then
      addError ctx "Variant with payload must be used in the form of: `Variant pattern`." loc
    else
      ctx

  HVariantPat(variantSerial, ty, loc), ty, ctx

let private inferSomeAppPat ctx payloadPat loc =
  let payloadPat, payloadTy, ctx = inferPat ctx payloadPat
  let targetTy = tyOption payloadTy
  HNodePat(HSomeAppPN, [ payloadPat ], targetTy, loc), targetTy, ctx

let private inferVariantAppPat (ctx: TyCtx) variantSerial payloadPat loc =
  let variantDef = ctx.Variants |> mapFind variantSerial
  let targetTy = tyUnion variantDef.UnionTySerial

  let payloadPat, payloadTy, ctx = inferPat ctx payloadPat

  let ctx =
    unifyTy ctx loc variantDef.PayloadTy payloadTy

  HNodePat(HVariantAppPN variantSerial, [ payloadPat ], targetTy, loc), targetTy, ctx

let private inferConsPat ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let listTy = tyList lTy
  let ctx = unifyTy ctx loc rTy listTy

  HNodePat(HConsPN, [ l; r ], listTy, loc), listTy, ctx

let private inferTuplePat ctx itemPats loc =
  let itemPats, itemTys, ctx = doInferPats ctx itemPats

  let tupleTy = tyTuple itemTys
  HNodePat(HTuplePN, itemPats, tupleTy, loc), tupleTy, ctx

let private inferAscribePat ctx body ascriptionTy loc =
  let body, bodyTy, ctx = inferPat ctx body
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy

  let ctx = unifyTy ctx loc bodyTy ascriptionTy
  body, ascriptionTy, ctx

let private inferAsPat ctx body varSerial loc =
  let body, bodyTy, ctx = inferPat ctx body

  let _, ctx =
    ctx |> unifyVarTy varSerial (Some bodyTy) loc

  HAsPat(body, varSerial, loc), bodyTy, ctx

let private inferOrPat ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let ctx = unifyTy ctx loc lTy rTy
  HOrPat(l, r, loc), lTy, ctx

let private inferAbortPat ctx pat loc =
  let targetTy, ctx = freshMetaTyForPat pat ctx
  hpAbort targetTy loc, targetTy, ctx

let private doInferPats ctx pats =
  let rec go ctx patAcc tyAcc pats =
    match pats with
    | [] -> List.rev patAcc, List.rev tyAcc, ctx

    | pat :: pats ->
        let pat, ty, ctx = inferPat ctx pat
        go ctx (pat :: patAcc) (ty :: tyAcc) pats

  go ctx [] [] pats

let private inferPat ctx pat: HPat * Ty * TyCtx =
  match pat with
  | HLitPat (lit, _) -> inferLitPat ctx pat lit
  | HDiscardPat (_, loc) -> inferDiscardPat ctx pat loc
  | HVarPat (varSerial, _, loc) -> inferVarPat ctx varSerial loc
  | HVariantPat (variantSerial, _, loc) -> inferVariantPat ctx variantSerial loc

  | HNodePat (kind, argPats, nodeTy, loc) ->
      let fail () = failwithf "NEVER: %A" pat

      match kind, argPats with
      | HNilPN, _ -> inferNilPat ctx pat loc
      | HNonePN, _ -> inferNonePat ctx pat loc
      | HSomePN, _ -> inferSomePat ctx pat loc

      | HConsPN, [ l; r ] -> inferConsPat ctx l r loc
      | HConsPN, _ -> fail ()

      | HSomeAppPN, [ payloadPat ] -> inferSomeAppPat ctx payloadPat loc
      | HSomeAppPN, _ -> fail ()

      | HVariantAppPN variantSerial, [ payloadPat ] -> inferVariantAppPat ctx variantSerial payloadPat loc
      | HVariantAppPN _, _ -> fail ()

      | HTuplePN, _ -> inferTuplePat ctx argPats loc

      | HAscribePN, [ bodyPat ] -> inferAscribePat ctx bodyPat nodeTy loc
      | HAscribePN, _ -> fail ()

      | HAbortPN, _ -> inferAbortPat ctx pat loc

      | HAppPN, _ -> fail () // Error in NameRes.
      | HNavPN _, _ -> fail () // Resolved in NameRes.
      | HBoxPN, _ -> fail () // Generated in AutoBoxing.

  | HAsPat (bodyPat, serial, loc) -> inferAsPat ctx bodyPat serial loc
  | HOrPat (l, r, loc) -> inferOrPat ctx l r loc

let private inferRefutablePat ctx pat = inferPat ctx pat

let private inferIrrefutablePat ctx pat =
  if pat
     |> patIsClearlyExhaustive (isNewtypeVariant ctx)
     |> not then
    let loc = patToLoc pat

    let ctx =
      addLog ctx Log.IrrefutablePatNonExhaustiveError loc

    let ty, ctx = freshMetaTyForPat pat ctx
    hpAbort ty loc, ty, ctx
  else
    inferPat ctx pat

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private inferLitExpr ctx expr lit =
  let ctx = validateLit ctx lit (exprToLoc expr)
  expr, litToTy lit, ctx

let private inferVarExpr (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc

  HVarExpr(varSerial, ty, loc), ty, ctx

let private inferFunExpr (ctx: TyCtx) funSerial loc =
  let ty, _, ctx =
    let funDef = ctx.Funs |> mapFind funSerial
    instantiateTyScheme ctx funDef.Ty loc

  HFunExpr(funSerial, ty, loc), ty, ctx

let private inferVariantExpr (ctx: TyCtx) variantSerial loc =
  let ty =
    (ctx.Variants |> mapFind variantSerial).VariantTy

  HVariantExpr(variantSerial, ty, loc), ty, ctx

let private inferPrimExpr ctx prim loc =
  match prim with
  | HPrim.Printfn ->
      let ctx =
        addError
          ctx
          "Illegal use of printfn. printfn must have string literal as first argument; e.g. `printfn \"%s\" s`."
          loc

      hxAbort ctx loc

  | HPrim.NativeFun ->
      let ctx =
        addError ctx "Illegal use of __nativeFun. Hint: `__nativeFun (\"funName\", arg1, arg2, ...): ResultType`." loc

      hxAbort ctx loc

  | HPrim.NativeDecl ->
      let ctx =
        addError ctx "Illegal use of __nativeDecl. Hint: `__nativeDecl \"Some C code here.\"`." loc

      hxAbort ctx loc

  | HPrim.SizeOfVal ->
      let ctx =
        addError ctx "Illegal use of __sizeOfVal. Hint: `__sizeOfVal expr`." loc

      hxAbort ctx loc

  | _ ->
      let tySpec = prim |> primToTySpec
      let primTy, traits, ctx = (tySpec, ctx) |> instantiateTySpec loc
      let ctx = ctx |> addTraitBounds traits
      HPrimExpr(prim, primTy, loc), primTy, ctx

let private inferRecordExpr ctx expectOpt baseOpt fields loc =
  // First, infer base if exists.
  let baseOpt, baseTyOpt, ctx =
    match baseOpt with
    | None -> None, None, ctx

    | Some baseExpr ->
        let baseExpr, recordTy, ctx = inferExpr ctx expectOpt baseExpr
        Some baseExpr, Some recordTy, ctx

  // Determine the record type by base expr or expectation.
  let recordTyInfoOpt =
    let asRecordTy tyOpt =
      match tyOpt |> Option.map (substTy ctx) with
      | Some ((Ty (RecordTk tySerial, tyArgs)) as recordTy) ->
          assert (List.isEmpty tyArgs)

          match ctx |> findTy tySerial with
          | RecordTyDef (name, fieldDefs, _) -> Some(recordTy, name, fieldDefs)
          | _ -> None

      | _ -> None

    match baseTyOpt |> asRecordTy with
    | ((Some _) as it) -> it
    | _ -> expectOpt |> asRecordTy

  match recordTyInfoOpt with
  | None ->
      let ctx =
        addError ctx "Can't infer type of record." loc

      hxAbort ctx loc

  | Some (recordTy, recordName, fieldDefs) ->
      let addRedundantErr fieldName loc ctx =
        addLog ctx (Log.RedundantFieldError(recordName, fieldName)) loc

      let addIncompleteErr fieldNames ctx =
        addLog ctx (Log.MissingFieldsError(recordName, fieldNames)) loc

      // Infer field initializers and whether each of them is member of the record type.
      // Whenever a field appears, remove it from the set of fields
      // so that second occurrence of it is marked as redundant.
      let fields, (fieldDefs, ctx) =
        let fieldDefs =
          fieldDefs
          |> List.map (fun (name, ty, _) -> name, ty)
          |> TMap.ofList compare

        (fields, (fieldDefs, ctx))
        |> stMap
             (fun (field, (fieldDefs, ctx)) ->
               let name, init, loc = field

               match fieldDefs |> TMap.remove name with
               | None, _ ->
                   let ctx = ctx |> addRedundantErr name loc
                   let init, _, ctx = inferExpr ctx None init
                   (name, init, loc), (fieldDefs, ctx)

               | Some defTy, fieldDefs ->
                   let init, initTy, ctx = inferExpr ctx (Some defTy) init
                   let ctx = unifyTy ctx loc initTy defTy
                   (name, init, loc), (fieldDefs, ctx))

      // Unless base expr is specified, set of field initializers must be complete.
      let ctx =
        if baseOpt |> Option.isNone
           && fieldDefs |> TMap.isEmpty |> not then
          let fields =
            fieldDefs
            |> TMap.toList
            |> List.map (fun (name, _) -> name)

          ctx |> addIncompleteErr fields
        else
          ctx

      match baseOpt with
      | None -> HRecordExpr(None, fields, recordTy, loc), recordTy, ctx

      | Some baseExpr ->
          // Assign to a temporary var so that RecordRes can reuse the expr safely.
          // (This kind of modification is not business of typing, though.)
          // { base with fields... } ==> let t = base in { t with fields... }
          let varSerial, ctx = freshVar ctx "base" recordTy loc

          let varPat = HVarPat(varSerial, recordTy, loc)
          let varExpr = HVarExpr(varSerial, recordTy, loc)

          let recordExpr =
            HRecordExpr(Some varExpr, fields, recordTy, loc)

          HLetValExpr(PrivateVis, varPat, baseExpr, recordExpr, recordTy, loc), recordTy, ctx

/// match 'a with ( | 'a -> 'b )*
let private inferMatchExpr ctx expectOpt itself cond arms loc =
  let targetTy, ctx = freshMetaTyForExpr itself ctx

  let cond, condTy, ctx = inferExpr ctx None cond

  let arms, ctx =
    (arms, ctx)
    |> stMap
         (fun ((pat, guard, body), ctx) ->
           let pat, patTy, ctx = inferRefutablePat ctx pat

           let ctx = unifyTy ctx (patToLoc pat) patTy condTy

           let guard, guardTy, ctx = inferExpr ctx None guard

           let ctx =
             unifyTy ctx (exprToLoc guard) guardTy tyBool

           let body, bodyTy, ctx = inferExpr ctx expectOpt body

           let ctx =
             unifyTy ctx (exprToLoc body) targetTy bodyTy

           (pat, guard, body), ctx)

  HMatchExpr(cond, arms, targetTy, loc), targetTy, ctx

let private inferNavExpr ctx l (r: Ident) loc =
  let fail ctx =
    let ctx =
      addError ctx ("Expected to have field: '" + r + "'.") loc

    hxAbort ctx loc

  let l, lTy, ctx = inferExpr ctx None l

  let lTy = substTy ctx lTy

  match lTy, r with
  | Ty (StrTk, []), "Length" ->
      let funExpr =
        HPrimExpr(HPrim.StrLength, tyFun tyStr tyInt, loc)

      hxApp funExpr l tyInt loc, tyInt, ctx

  | Ty (RecordTk tySerial, tyArgs), _ ->
      assert (List.isEmpty tyArgs)

      let fieldTyOpt =
        match ctx |> findTy tySerial with
        | RecordTyDef (_, fieldDefs, _) ->
            match fieldDefs
                  |> List.tryFind (fun (theName, _, _) -> theName = r) with
            | Some (_, fieldTy, _) -> Some fieldTy
            | None -> None
        | _ -> None

      match fieldTyOpt with
      | Some fieldTy -> HNavExpr(l, r, fieldTy, loc), fieldTy, ctx
      | None -> fail ctx

  | _ -> fail ctx

let private inferAppExpr ctx itself callee arg loc =
  let inferUntypedExprs ctx exprs =
    (exprs, ctx)
    |> stMap
         (fun (expr, ctx) ->
           let exprs, _, ctx = inferExpr ctx None expr
           exprs, ctx)

  // Special forms must be handled before recursion.
  match callee, arg with
  // printfn "..."
  | HPrimExpr (HPrim.Printfn, _, _), HLitExpr (StrLit format, _) ->
      let funTy, targetTy =
        match analyzeFormat format with
        | (Ty (FunTk, [ _; targetTy ])) as funTy -> funTy, targetTy
        | _ -> failwith "NEVER"

      hxApp (HPrimExpr(HPrim.Printfn, funTy, loc)) arg targetTy loc, targetTy, ctx

  // __nativeFun f
  | HPrimExpr (HPrim.NativeFun, _, loc), HFunExpr (funSerial, _, _) ->
      let targetTy, ctx = castFunAsNativeFun funSerial ctx
      HNodeExpr(HNativeFunEN funSerial, [], targetTy, loc), targetTy, ctx

  // __nativeFun "funName"
  | HPrimExpr (HPrim.NativeFun, _, loc), HLitExpr (StrLit funName, _) ->
      let targetTy, ctx = ctx |> freshMetaTyForExpr itself
      HNodeExpr(HCallNativeEN funName, [], targetTy, loc), targetTy, ctx

  // __nativeFun ("funName", arg1, arg2, ...)
  | HPrimExpr (HPrim.NativeFun, _, loc), HNodeExpr (HTupleEN, HLitExpr (StrLit funName, _) :: args, _, _) ->
      // Type of native function is unchecked. Type ascriptions must be written correctly.
      let targetTy, ctx = ctx |> freshMetaTyForExpr itself
      let args, ctx = inferUntypedExprs ctx args

      HNodeExpr(HCallNativeEN funName, args, targetTy, loc), targetTy, ctx

  // __nativeExpr "code"
  | HPrimExpr (HPrim.NativeExpr, _, loc), HLitExpr (StrLit code, _) ->
      let targetTy, ctx = ctx |> freshMetaTyForExpr itself
      HNodeExpr(HNativeExprEN code, [], targetTy, loc), targetTy, ctx

  // __nativeStmt "code"
  | HPrimExpr (HPrim.NativeStmt, _, loc), HLitExpr (StrLit code, _) ->
      HNodeExpr(HNativeStmtEN code, [], tyUnit, loc), tyUnit, ctx

  // __nativeStmt ("code", args...)
  | HPrimExpr (HPrim.NativeStmt, _, loc), HNodeExpr (HTupleEN, HLitExpr (StrLit code, _) :: args, _, _) ->
      let args, ctx = inferUntypedExprs ctx args
      HNodeExpr(HNativeStmtEN code, args, tyUnit, loc), tyUnit, ctx

  // __nativeDecl "code"
  | HPrimExpr (HPrim.NativeDecl, _, loc), HLitExpr (StrLit code, _) ->
      HNodeExpr(HNativeDeclEN code, [], tyUnit, loc), tyUnit, ctx

  | HPrimExpr (HPrim.SizeOfVal, _, loc), _ ->
      let arg, argTy, ctx = inferExpr ctx None arg
      HNodeExpr(HSizeOfValEN, [ HNodeExpr(HAbortEN, [], argTy, exprToLoc arg) ], tyInt, loc), tyInt, ctx

  | _ ->
      let targetTy, ctx = ctx |> freshMetaTyForExpr itself
      let arg, argTy, ctx = inferExpr ctx None arg
      let callee, calleeTy, ctx = inferExpr ctx None callee

      let ctx =
        unifyTy ctx loc calleeTy (tyFun argTy targetTy)

      hxApp callee arg targetTy loc, targetTy, ctx

let private inferMinusExpr ctx arg loc =
  let arg, argTy, ctx = inferExpr ctx None arg

  let ctx =
    ctx |> addTraitBounds [ IsNumberTrait argTy, loc ]

  HNodeExpr(HMinusEN, [ arg ], argTy, loc), argTy, ctx

let private inferIndexExpr ctx l r loc =
  let l, lTy, ctx = inferExpr ctx (Some tyStr) l
  let r, rTy, ctx = inferExpr ctx (Some tyInt) r
  let tTy, ctx = freshMetaTy loc ctx

  let ctx =
    ctx
    |> addTraitBounds [ IndexTrait(lTy, rTy, tTy), loc ]

  HNodeExpr(HIndexEN, [ l; r ], tTy, loc), tTy, ctx

let private inferSliceExpr ctx l r x loc =
  let l, lTy, ctx = inferExpr ctx (Some tyInt) l
  let r, rTy, ctx = inferExpr ctx (Some tyInt) r
  let x, xTy, ctx = inferExpr ctx None x

  let ctx =
    let actualTy = tyFun lTy (tyFun rTy (tyFun xTy xTy))

    let expectedTy =
      tyFun tyInt (tyFun tyInt (tyFun tyStr tyStr))

    unifyTy ctx loc actualTy expectedTy

  HNodeExpr(HSliceEN, [ l; r; x ], xTy, loc), xTy, ctx

let private inferTupleExpr (ctx: TyCtx) items loc =
  let rec go acc itemTys ctx items =
    match items with
    | [] -> List.rev acc, List.rev itemTys, ctx

    | item :: items ->
        let item, itemTy, ctx = inferExpr ctx None item
        go (item :: acc) (itemTy :: itemTys) ctx items

  let items, itemTys, ctx = go [] [] ctx items

  hxTuple items loc, tyTuple itemTys, ctx

let private inferAscribeExpr ctx body ascriptionTy loc =
  let body, bodyTy, ctx = inferExpr ctx (Some ascriptionTy) body
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy

  let ctx = unifyTy ctx loc bodyTy ascriptionTy
  body, ascriptionTy, ctx

let private inferBlockExpr ctx expectOpt stmts last =
  let stmts, ctx =
    (stmts, ctx)
    |> stMap
         (fun (expr, ctx) ->
           let loc = exprToLoc expr

           let expr, resultTy, ctx = inferExpr ctx None expr
           let ctx = unifyTy ctx loc resultTy tyUnit

           expr, ctx)

  let last, lastTy, ctx = inferExpr ctx expectOpt last

  HBlockExpr(stmts, last), lastTy, ctx

let private inferLetValExpr ctx expectOpt vis pat init next loc =
  let init, initTy, ctx =
    let expectOpt = patToAscriptionTy pat
    inferExpr ctx expectOpt init

  let pat, patTy, ctx = inferIrrefutablePat ctx pat

  let ctx = unifyTy ctx loc initTy patTy

  let next, nextTy, ctx = inferExpr ctx expectOpt next
  HLetValExpr(vis, pat, init, next, nextTy, loc), nextTy, ctx

let private inferLetFunExpr (ctx: TyCtx) expectOpt callee vis argPats body next loc =
  // Special treatment for main function.
  let mainFunTyOpt, ctx =
    if ctx |> isMainFun callee then
      // arguments must be syntactically `_`.
      let ctx =
        match argPats with
        | [ HDiscardPat _ ] -> ctx
        | _ -> addError ctx "main function must be defined in the form of: `let main _ = ...`." loc

      // FIXME: argument type is string[]
      Some(tyFun tyUnit tyInt), ctx
    else
      None, ctx

  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx funTy argPats =
    match argPats with
    | [] -> [], funTy, ctx

    | argPat :: argPats ->
        let argPat, argTy, ctx = inferIrrefutablePat ctx argPat
        let argPats, funTy, ctx = inferArgs ctx funTy argPats
        argPat :: argPats, tyFun argTy funTy, ctx

  let outerLevel = ctx.Level
  let ctx = ctx |> incLevel

  let calleeTy, ctx =
    let calleeTy, ctx =
      match mainFunTyOpt with
      | Some calleeTy -> calleeTy, ctx
      | None -> freshMetaTy loc ctx

    let ctx =
      match (ctx.Funs |> mapFind callee).Ty with
      | TyScheme ([], oldTy) -> unifyTy ctx loc oldTy calleeTy
      | _ -> failwith "NEVER: It must be a pre-generalized function"

    calleeTy, ctx

  let provisionalResultTy, ctx = ctx |> freshMetaTyForExpr body

  let argPats, funTy, ctx =
    inferArgs ctx provisionalResultTy argPats

  let ctx = unifyTy ctx loc calleeTy funTy

  let body, bodyTy, ctx = inferExpr ctx None body

  let ctx =
    unifyTy ctx loc bodyTy provisionalResultTy

  let ctx = ctx |> decLevel

  let ctx = generalizeFun ctx outerLevel callee

  let next, nextTy, ctx = inferExpr ctx expectOpt next
  HLetFunExpr(callee, NotRec, vis, argPats, body, next, nextTy, loc), nextTy, ctx

let private inferExpr (ctx: TyCtx) (expectOpt: Ty option) (expr: HExpr): HExpr * Ty * TyCtx =
  let fail () = failwithf "NEVER: %A" expr

  match expr with
  | HLitExpr (lit, _) -> inferLitExpr ctx expr lit
  | HVarExpr (serial, _, loc) -> inferVarExpr ctx serial loc
  | HFunExpr (serial, _, loc) -> inferFunExpr ctx serial loc
  | HVariantExpr (serial, _, loc) -> inferVariantExpr ctx serial loc
  | HPrimExpr (prim, _, loc) -> inferPrimExpr ctx prim loc
  | HRecordExpr (baseOpt, fields, _, loc) -> inferRecordExpr ctx expectOpt baseOpt fields loc
  | HMatchExpr (cond, arms, _, loc) -> inferMatchExpr ctx expectOpt expr cond arms loc
  | HNavExpr (receiver, field, _, loc) -> inferNavExpr ctx receiver field loc

  | HNodeExpr (HAbortEN, _, _, loc) -> hxAbort ctx loc
  | HNodeExpr (HMinusEN, [ arg ], _, loc) -> inferMinusExpr ctx arg loc
  | HNodeExpr (HAppEN, [ callee; arg ], _, loc) -> inferAppExpr ctx expr callee arg loc
  | HNodeExpr (HTupleEN, items, _, loc) -> inferTupleExpr ctx items loc
  | HNodeExpr (HAscribeEN, [ expr ], ascriptionTy, loc) -> inferAscribeExpr ctx expr ascriptionTy loc

  | HNodeExpr (HIndexEN, [ l; r ], _, loc) -> inferIndexExpr ctx l r loc
  | HNodeExpr (HIndexEN, _, _, _) -> fail ()
  | HNodeExpr (HSliceEN, [ l; r; x ], _, loc) -> inferSliceExpr ctx l r x loc
  | HNodeExpr (HSliceEN, _, _, _) -> fail ()

  | HBlockExpr (stmts, last) -> inferBlockExpr ctx expectOpt stmts last

  | HLetValExpr (vis, pat, body, next, _, loc) -> inferLetValExpr ctx expectOpt vis pat body next loc

  | HLetFunExpr (oldSerial, _, vis, args, body, next, _, loc) ->
      inferLetFunExpr ctx expectOpt oldSerial vis args body next loc

  | HTyDeclExpr _
  | HOpenExpr _ -> expr, tyUnit, ctx

  | HNodeExpr (HRangeEN, _, _, loc) ->
      let ctx =
        addError ctx "Range operator can be used in the form of `s.[l..r]` for now." loc

      hxAbort ctx loc

  | HNodeExpr (HMinusEN, _, _, _)
  | HNodeExpr (HAscribeEN, _, _, _)
  | HNodeExpr (HAppEN, _, _, _)
  | HNodeExpr (HClosureEN, _, _, _)
  | HNodeExpr (HCallProcEN, _, _, _)
  | HNodeExpr (HCallTailRecEN, _, _, _)
  | HNodeExpr (HCallClosureEN, _, _, _)
  | HNodeExpr (HCallNativeEN _, _, _, _)
  | HNodeExpr (HRecordEN, _, _, _)
  | HNodeExpr (HRecordItemEN _, _, _, _)
  | HNodeExpr (HNativeFunEN _, _, _, _)
  | HNodeExpr (HNativeExprEN _, _, _, _)
  | HNodeExpr (HNativeStmtEN _, _, _, _)
  | HNodeExpr (HNativeDeclEN _, _, _, _)
  | HNodeExpr (HSizeOfValEN, _, _, _) -> failwith "NEVER"

  | HModuleExpr _
  | HModuleSynonymExpr _ -> failwith "NEVER: Resolved in NameRes"

// -----------------------------------------------
// Reject cyclic synonyms
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private State =
  | Recursive
  | Cyclic
  | Acyclic

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private SynonymCycleCtx =
  { ExpandMetaOrSynonymTy: TySerial -> Ty option
    TyState: AssocMap<TySerial, State> }

let private setTyState tySerial state (ctx: SynonymCycleCtx) =
  { ctx with
      TyState = ctx.TyState |> TMap.add tySerial state }

let private rcsSynonymTy (ctx: SynonymCycleCtx) tySerial =
  match ctx.TyState |> TMap.tryFind tySerial with
  | Some State.Recursive -> setTyState tySerial State.Cyclic ctx

  | Some _ -> ctx

  | None ->
      let ctx = setTyState tySerial State.Recursive ctx

      let ctx =
        match ctx.ExpandMetaOrSynonymTy tySerial with
        | Some bodyTy -> rcsTy ctx bodyTy
        | None -> ctx

      match ctx.TyState |> TMap.tryFind tySerial with
      | Some State.Recursive -> setTyState tySerial State.Acyclic ctx
      | _ -> ctx

let private rcsTy (ctx: SynonymCycleCtx) (ty: Ty) =
  match ty with
  | Ty (ErrorTk _, _) -> ctx

  | Ty (MetaTk (tySerial, _), _) ->
      match ctx.ExpandMetaOrSynonymTy tySerial with
      | Some bodyTy -> rcsTy ctx bodyTy
      | None -> ctx

  | Ty (tk, tyArgs) ->
      let ctx = rcsTys ctx tyArgs

      match tk with
      | SynonymTk tySerial -> rcsSynonymTy ctx tySerial
      | _ -> ctx

let private rcsTys ctx tys = List.fold rcsTy ctx tys

let private synonymCycleCheck (tyCtx: TyCtx) =
  let ctx: SynonymCycleCtx =
    { ExpandMetaOrSynonymTy =
        fun tySerial ->
          match findTy tySerial tyCtx with
          | MetaTyDef bodyTy -> Some bodyTy
          | SynonymTyDef (_, _, bodyTy, _) -> Some bodyTy
          | _ -> None

      TyState = TMap.empty compare }

  let ctx =
    tyCtx.Tys
    |> TMap.fold
         (fun ctx tySerial (tyDef: TyDef) ->
           match tyDef with
           | SynonymTyDef _ -> rcsSynonymTy ctx tySerial
           | _ -> ctx)
         ctx

  let tys, logs =
    ctx.TyState
    |> TMap.fold
         (fun (tys, logs) tySerial state ->
           match state with
           | State.Cyclic ->
               match findTy tySerial tyCtx with
               | SynonymTyDef (ident, tyArgs, _, loc) ->
                   // Remove body of cyclic synonym to prevent the synonym expansion
                   // from running into stack overflow.
                   let tys =
                     tys
                     |> TMap.add tySerial (SynonymTyDef(ident, tyArgs, tyUnit, loc))

                   let logs = (Log.TySynonymCycleError, loc) :: logs
                   tys, logs

               | _ -> tys, logs
           | _ -> tys, logs)
         (tyCtx.Tys, tyCtx.Logs)

  { tyCtx with Tys = tys; Logs = logs }

// -----------------------------------------------
// Interface
// -----------------------------------------------

let infer (expr: HExpr, scopeCtx: ScopeCtx, errors): HExpr * TyCtx =
  let ctx: TyCtx =
    { Serial = scopeCtx.Serial
      Vars = scopeCtx.Vars
      Funs = scopeCtx.Funs
      Variants = scopeCtx.Variants
      MainFunOpt = scopeCtx.MainFunOpt
      Tys = scopeCtx.Tys
      TyLevels = TMap.empty compare
      Level = 0
      TraitBounds = []
      Logs = [] }

  let ctx =
    errors
    |> List.fold (fun ctx (msg, loc) -> addError ctx msg loc) ctx

  // Assign type vars to var/fun definitions.
  let ctx =
    let vars, ctx =
      ctx.Vars
      |> TMap.fold
           (fun (acc, ctx: TyCtx) varSerial varDef ->
             let ctx =
               { ctx with
                   Level =
                     scopeCtx.VarLevels
                     |> mapFind (varSerialToInt varSerial) }

             let varDef, ctx =
               match varDef with
               | VarDef (name, storageModifier, _, loc) ->
                   let ty, ctx = freshMetaTy loc ctx
                   VarDef(name, storageModifier, ty, loc), ctx

             let acc = acc |> TMap.add varSerial varDef

             acc, ctx)
           (TMap.empty varSerialCompare, ctx)

    { ctx with Vars = vars }

  let funs, ctx =
    ctx.Funs
    |> TMap.fold
         (fun (acc, ctx: TyCtx) funSerial (funDef: FunDef) ->
           let ctx =
             { ctx with
                 Level =
                   scopeCtx.VarLevels
                   |> mapFind (funSerialToInt funSerial) }

           let ty, ctx = freshMetaTy funDef.Loc ctx

           acc
           |> TMap.add funSerial { funDef with Ty = TyScheme([], ty) },
           ctx)
         (TMap.empty funSerialCompare, ctx)

  let ctx = { ctx with Funs = funs }

  let ctx =
    let variants =
      ctx.Variants
      |> TMap.map
           (fun _ (variantDef: VariantDef) ->
             // Pre-compute the type of variant.
             let variantTy =
               let unionTy = tyUnion variantDef.UnionTySerial

               if variantDef.HasPayload then
                 tyFun variantDef.PayloadTy unionTy
               else
                 unionTy

             { variantDef with
                 VariantTy = variantTy })

    { ctx with Variants = variants }

  let ctx = { ctx with Funs = funs; Level = 0 }

  let expr, ctx =
    let expr, topLevelTy, ctx = inferExpr ctx None expr

    let ctx =
      unifyTy ctx (exprToLoc expr) topLevelTy tyUnit

    expr, ctx

  let ctx = ctx |> resolveTraitBounds

  let ctx = synonymCycleCheck ctx

  // Substitute all types. Unbound types are degenerated here.
  let substOrDegenerate ty =
    ty
    |> substOrDegenerateTy ctx
    |> typingExpandSynonyms (toTyContext ctx)

  let expr = exprMap substOrDegenerate id expr

  let ctx =
    let vars =
      ctx.Vars
      |> TMap.map
           (fun _ varDef ->
             match varDef with
             | VarDef (name, storageModifier, ty, loc) ->
                 let ty = substOrDegenerate ty
                 VarDef(name, storageModifier, ty, loc))

    let funs =
      ctx.Funs
      |> TMap.map
           (fun _ (funDef: FunDef) ->
             let (TyScheme (tyVars, ty)) = funDef.Ty
             let ty = substOrDegenerate ty

             { funDef with
                 Ty = TyScheme(tyVars, ty) })

    let variants =
      ctx.Variants
      |> TMap.map
           (fun _ (variantDef: VariantDef) ->
             { variantDef with
                 PayloadTy = substOrDegenerate variantDef.PayloadTy
                 VariantTy = substOrDegenerate variantDef.VariantTy })

    { ctx with
        Vars = vars
        Funs = funs
        Variants = variants }

  let ctx =
    let tys =
      ctx.Tys
      |> TMap.fold
           (fun acc tySerial tyDef ->
             match tyDef with
             | MetaTyDef _ -> acc

             | SynonymTyDef (name, tyArgs, bodyTy, loc) ->
                 let bodyTy = bodyTy |> substOrDegenerate

                 acc
                 |> TMap.add tySerial (SynonymTyDef(name, tyArgs, bodyTy, loc))

             | RecordTyDef (recordName, fields, loc) ->
                 let fields =
                   fields
                   |> List.map
                        (fun (name, ty, loc) ->
                          let ty = substOrDegenerate ty
                          name, ty, loc)

                 acc
                 |> TMap.add tySerial (RecordTyDef(recordName, fields, loc))

             | _ -> acc |> TMap.add tySerial tyDef)
           (TMap.empty compare)

    { ctx with Tys = tys }

  expr, ctx
