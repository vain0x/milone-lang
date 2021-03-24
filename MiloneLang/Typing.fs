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
open MiloneLang.TypeIntegers
open MiloneLang.TypeFloat

module StdInt = MiloneStd.StdInt
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
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

let private getTyLevel tySerial (ctx: TyCtx) : Level =
  ctx.TyLevels
  |> TMap.tryFind tySerial
  |> Option.defaultValue 0

let private isNewtypeVariant (ctx: TyCtx) variantSerial =
  let variantDef = ctx.Variants |> mapFind variantSerial
  variantDef.IsNewtype

let private isMainFun funSerial (ctx: TyCtx) =
  match ctx.MainFunOpt with
  | Some mainFun -> funSerialCompare mainFun funSerial = 0
  | _ -> false

let private freshVar (ctx: TyCtx) hint ty loc =
  let varSerial = VarSerial(ctx.Serial + 1)

  let varDef : VarDef =
    { Name = hint
      IsStatic = NotStatic
      Ty = ty
      Linkage = InternalLinkage
      Loc = loc }

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars = ctx.Vars |> TMap.add varSerial varDef }

  varSerial, ctx

let private freshTySerial (ctx: TyCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        TyLevels = ctx.TyLevels |> TMap.add serial ctx.Level }

  serial, ctx

let private freshMetaTy loc (ctx: TyCtx) : Ty * TyCtx =
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
// Unification
// -----------------------------------------------

// And meta type resolution by substitution or degeneration.

let private expandMeta (ctx: TyCtx) tySerial : Ty option =
  match ctx.Tys |> TMap.tryFind tySerial with
  | Some (MetaTyDef ty) -> Some ty
  | _ -> None

let private substTy (ctx: TyCtx) ty : Ty = tySubst (expandMeta ctx) ty

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

let private expandSynonyms (ctx: TyCtx) ty : Ty =
  tyExpandSynonyms (fun tySerial -> ctx.Tys |> TMap.tryFind tySerial) ty

let private unifyTy (ctx: TyCtx) loc (lTy: Ty) (rTy: Ty) : TyCtx =
  let levelUp (ctx: TyCtx) tySerial ty =
    let level = getTyLevel tySerial ctx

    ty
    |> tyCollectFreeVars
    |> List.fold
         (fun tyLevels tySerial ->
           if getTyLevel tySerial ctx <= level then
             // Already non-deep enough.
             tyLevels
           else
             // Prevent this meta ty from getting generalized until level of the bound meta ty.
             tyLevels |> TMap.add tySerial level)
         ctx.TyLevels

  let rec go lTy rTy loc (ctx: TyCtx) =
    match unifyNext lTy rTy loc with
    | UnifyOk -> ctx

    | UnifyOkWithStack stack -> List.fold (fun ctx (l, r) -> go l r loc ctx) ctx stack

    | UnifyError (log, loc) -> addLog ctx log loc

    | UnifyExpandMeta (tySerial, otherTy) ->
        match expandMeta ctx tySerial with
        | Some ty -> go ty otherTy loc ctx

        | None ->
            let otherTy = substTy ctx otherTy

            match unifyAfterExpandMeta lTy rTy tySerial otherTy loc with
            | UnifyAfterExpandMetaResult.OkNoBind -> ctx

            | UnifyAfterExpandMetaResult.OkBind ->
                { ctx with
                    Tys = ctx.Tys |> TMap.add tySerial (MetaTyDef otherTy)
                    TyLevels = levelUp ctx tySerial otherTy }

            | UnifyAfterExpandMetaResult.Error (log, loc) -> addLog ctx log loc

    | UnifyExpandSynonym (tySerial, useTyArgs, otherTy) ->
        let expandedTy =
          // Find def.
          let defTySerials, bodyTy =
            match ctx.Tys |> TMap.tryFind tySerial with
            | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) -> defTySerials, bodyTy
            | _ -> unreachable ()

          // Checked in NameRes.
          assert (List.length defTySerials = List.length useTyArgs)

          tyExpandSynonym useTyArgs defTySerials bodyTy

        go expandedTy otherTy loc ctx

  go lTy rTy loc ctx

let private unifyVarTy varSerial tyOpt loc ctx =
  let varTy = (findVar ctx varSerial).Ty

  match tyOpt with
  | Some ty ->
      let ctx = unifyTy ctx loc varTy ty
      varTy, ctx

  | None -> varTy, ctx

// -----------------------------------------------
// Generalization and instantiation
// -----------------------------------------------

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

  | _ -> unreachable () // Can't generalize already-generalized functions.

// -----------------------------------------------
// Trait bounds
// -----------------------------------------------

let private addTraitBounds traits (ctx: TyCtx) =
  { ctx with
      TraitBounds = List.append traits ctx.TraitBounds }

let private doResolveTraitBound (ctx: TyCtx) theTrait loc : TyCtx =
  let unify lTy rTy loc ctx : TyCtx = unifyTy ctx loc lTy rTy

  let addBoundError (ctx: TyCtx) : TyCtx =
    addLog ctx (Log.TyBoundError theTrait) loc
    |> addTraitBounds [ theTrait, loc ]

  /// integer, bool, char, or string
  let expectBasic ty (ctx: TyCtx) =
    match ty with
    | Ty (ErrorTk _, _)
    | Ty (IntTk _, [])
    | Ty (FloatTk _, [])
    | Ty (BoolTk, [])
    | Ty (CharTk, [])
    | Ty (StrTk, [])
    | Ty (NativePtrTk _, _) -> ctx

    | _ -> addBoundError ctx

  match theTrait with
  | AddTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, []) -> ctx

      // Coerce to int by default.
      | _ -> unify ty tyInt loc ctx

  | EqualTrait ty -> ctx |> expectBasic ty

  | CompareTrait ty -> ctx |> expectBasic ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | Ty (ErrorTk _, _) -> ctx

      | Ty (StrTk, []) ->
          ctx
          |> unify rTy tyInt loc
          |> unify resultTy tyChar loc

      | _ -> addBoundError ctx

  | IsIntTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, []) -> ctx

      // Coerce to int by default.
      | _ -> unify ty tyInt loc ctx

  | IsNumberTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, []) -> ctx

      // Coerce to int by default.
      | _ -> unify ty tyInt loc ctx

  | ToCharTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, []) -> ctx

      | _ -> addBoundError ctx

  | ToIntTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, [])
      | Ty (NativePtrTk _, _) -> ctx

      | _ -> addBoundError ctx

  | ToFloatTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (StrTk, []) -> ctx

      | _ -> addBoundError ctx

  | ToStringTrait ty -> expectBasic ty ctx

  | PtrTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk (IntFlavor (_, IPtr)), [])
      | Ty (ObjTk, [])
      | Ty (ListTk, _)
      | Ty (NativePtrTk _, _)
      | Ty (NativeFunTk, _) -> ctx

      | _ -> addBoundError ctx

let private resolveTraitBounds (ctx: TyCtx) =
  let subst (ctx: TyCtx) ty =
    ty |> substTy ctx |> typingExpandSynonyms ctx.Tys

  // Even if a trait bound can't be resolved,
  // it can become able to resolve after some resolution (unification),
  // so try to resolve all bounds repeatedly until no bound is resolved.
  let rec go (ctx: TyCtx) =
    let traits, ctx =
      List.rev ctx.TraitBounds, { ctx with TraitBounds = [] }

    let n = List.length traits

    let ctx : TyCtx =
      traits
      |> List.fold
           (fun ctx (theTrait, loc) ->
             let theTrait = traitMapTys (subst ctx) theTrait
             doResolveTraitBound ctx theTrait loc)
           ctx

    if List.length ctx.TraitBounds < n then
      let ctx = { ctx with Logs = [] }
      go ctx
    else
      ctx

  let logs, ctx = ctx.Logs, { ctx with Logs = [] }

  let ctx = go ctx

  { ctx with
      Logs = List.append logs ctx.Logs }

// -----------------------------------------------
// Others
// -----------------------------------------------

let private castFunAsNativeFun funSerial (ctx: TyCtx) : Ty * TyCtx =
  let funDef = ctx.Funs |> mapFind funSerial

  // Mark this function as extern "C".
  let ctx =
    { ctx with
        Funs =
          ctx.Funs
          |> TMap.add funSerial { funDef with Abi = CAbi } }

  let nativeFunTy =
    let (TyScheme (_, ty)) = funDef.Ty

    let ty = expandSynonyms ctx ty

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
  HNodePat(HNonePN, [], ty, loc), ty, ctx

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
  HVarPat(PrivateVis, varSerial, ty, loc), ty, ctx

let private inferVariantPat (ctx: TyCtx) variantSerial loc =
  let variantDef = ctx.Variants |> mapFind variantSerial
  let ty = variantDefToVariantTy variantDef

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

let private inferPat ctx pat : HPat * Ty * TyCtx =
  match pat with
  | HLitPat (lit, _) -> inferLitPat ctx pat lit
  | HDiscardPat (_, loc) -> inferDiscardPat ctx pat loc
  | HVarPat (_, varSerial, _, loc) -> inferVarPat ctx varSerial loc
  | HVariantPat (variantSerial, _, loc) -> inferVariantPat ctx variantSerial loc

  | HNodePat (kind, argPats, nodeTy, loc) ->
      let fail () = unreachable pat

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
    ctx.Variants
    |> mapFind variantSerial
    |> variantDefToVariantTy

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

          let varPat =
            HVarPat(PrivateVis, varSerial, recordTy, loc)

          let varExpr = HVarExpr(varSerial, recordTy, loc)

          let recordExpr =
            HRecordExpr(Some varExpr, fields, recordTy, loc)

          HLetValExpr(varPat, baseExpr, recordExpr, recordTy, loc), recordTy, ctx

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
        | _ -> unreachable ()

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

      let callee, calleeTy, ctx = inferExpr ctx None callee

      let arg, argTy, ctx =
        let tyAsFunArg ty =
          match ty with
          | Ty (FunTk, it :: _) -> Some it
          | _ -> None

        inferExpr ctx (tyAsFunArg calleeTy) arg

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

let private inferLetValExpr ctx expectOpt pat init next loc =
  let init, initTy, ctx =
    let expectOpt = patToAscriptionTy pat
    inferExpr ctx expectOpt init

  let pat, patTy, ctx = inferIrrefutablePat ctx pat

  let ctx = unifyTy ctx loc initTy patTy

  let next, nextTy, ctx = inferExpr ctx expectOpt next
  HLetValExpr(pat, init, next, nextTy, loc), nextTy, ctx

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
      | _ -> unreachable () // It must be a pre-generalized function.

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

let private inferExpr (ctx: TyCtx) (expectOpt: Ty option) (expr: HExpr) : HExpr * Ty * TyCtx =
  let fail () = unreachable expr

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

  | HLetValExpr (pat, body, next, _, loc) -> inferLetValExpr ctx expectOpt pat body next loc

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
  | HNodeExpr (HSizeOfValEN, _, _, _) -> unreachable ()

  | HModuleExpr _
  | HModuleSynonymExpr _ -> unreachable () // Resolved in NameRes.

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
  let ctx : SynonymCycleCtx =
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

let infer (modules: HProgram, scopeCtx: ScopeCtx, errors) : HProgram * TyCtx =
  let ctx : TyCtx =
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
      |> TMap.mapFold
           (fun (ctx: TyCtx) varSerial (varDef: VarDef) ->
             let ctx =
               { ctx with
                   Level =
                     scopeCtx.VarLevels
                     |> mapFind (varSerialToInt varSerial) }

             let varDef, ctx =
               let ty, ctx = freshMetaTy varDef.Loc ctx
               { varDef with Ty = ty }, ctx

             varDef, ctx)
           ctx

    { ctx with Vars = vars }

  let funs, ctx =
    ctx.Funs
    |> TMap.mapFold
         (fun (ctx: TyCtx) funSerial (funDef: FunDef) ->
           let ctx =
             { ctx with
                 Level =
                   scopeCtx.VarLevels
                   |> mapFind (funSerialToInt funSerial) }

           let ty, ctx = freshMetaTy funDef.Loc ctx

           { funDef with Ty = TyScheme([], ty) }, ctx)
         ctx

  let ctx = { ctx with Funs = funs; Level = 0 }

  let modules, ctx =
    let inferStmt (expr, ctx) =
      let expr, ty, ctx = inferExpr ctx (Some tyUnit) expr
      let ctx = unifyTy ctx (exprToLoc expr) ty tyUnit
      expr, ctx

    (modules, ctx) |> hirProgramEachExpr inferStmt

  let ctx = ctx |> resolveTraitBounds

  let ctx = synonymCycleCheck ctx

  // Substitute all types. Unbound types are degenerated here.
  let substOrDegenerate ty =
    ty
    |> substOrDegenerateTy ctx
    |> expandSynonyms ctx

  let modules, ctx =
    (modules, ctx)
    |> hirProgramEachExpr (fun (expr, ctx) ->
      exprMap substOrDegenerate id expr, ctx)

  let ctx =
    let vars =
      ctx.Vars
      |> TMap.map
           (fun _ (varDef: VarDef) ->
             let ty = substOrDegenerate varDef.Ty
             { varDef with Ty = ty })

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
                 PayloadTy = substOrDegenerate variantDef.PayloadTy })

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
             | MetaTyDef _
             | UniversalTyDef _
             | SynonymTyDef _ -> acc

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

  modules, ctx
