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
///
/// Only top-level functions are generalized. See also:
///   - [Let Should Not Be Generalised](https://www.microsoft.com/en-us/research/publication/let-should-not-be-generalised/)

module rec MiloneSyntax.Typing

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open Std.StdMultimap
open Std.StdSet
open MiloneSyntax.NameRes
open MiloneSyntax.Tir
open MiloneSyntax.TySystem
open MiloneSyntaxTypes.TirTypes

module S = Std.StdString
module StdInt = Std.StdInt

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TyCtx =
  {
    /// Next serial number.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    Serial: Serial

    /// Static and non-static variables.
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    /// Type serial to type definition.
    Tys: TreeMap<TySerial, TyDef>

    TyLevels: TreeMap<TySerial, Level>
    MetaTys: TreeMap<TySerial, Ty>
    QuantifiedTys: TreeSet<TySerial>
    Level: Level

    NewFuns: FunSerial list

    /// Funs that are mutually recursive and defined in the current block.
    ///
    /// These funs might have incorrect ty scheme
    /// because their body might use forward reference of another funs.
    ///
    /// Instantiation of such these funs are recorded
    /// to verify after final ty scheme is computed.
    GrayFuns: TreeSet<FunSerial>
    GrayInstantiations: TreeMap<FunSerial, (Ty * Loc) list>

    // TraitBoundResolution:
    //    Trait bounds are produced by some primitives that are polymorphic and have constraints.
    //    Trait bounds are first added to `NewTraitBounds` to wait for resolution.
    //    Whenever we are about to generalize a function, try to resolve all new bounds
    //    to prevent bounded meta types from getting generalized as possible.
    //    Unresolved bounds are pushed to `TraitBounds` for follow-up resolution
    //    (and resolution errors are just discarded here).
    //    At the end of each module, all `TraitBounds` are resolved.
    TraitBounds: (Trait * Loc) list
    NewTraitBounds: (Trait * Loc) list

    Logs: (Log * Loc) list }

let private newTyCtx (nr: NameResResult) : TyCtx =
  assert (List.isEmpty nr.Logs)

  { Serial = nr.Serial
    Vars = nr.StaticVars
    Funs = nr.Funs
    Variants = nr.Variants
    MainFunOpt = nr.MainFunOpt
    Tys = nr.Tys
    TyLevels = TMap.empty compare
    MetaTys = TMap.empty compare
    QuantifiedTys = TSet.empty compare
    Level = 0
    NewFuns = []
    GrayFuns = TSet.empty funSerialCompare
    GrayInstantiations = TMap.empty funSerialCompare
    TraitBounds = []
    NewTraitBounds = []
    Logs = [] }

let private toTirCtx (ctx: TyCtx) : TirCtx =
  { Serial = ctx.Serial
    StaticVars = ctx.Vars
    Funs = ctx.Funs
    Variants = ctx.Variants
    Tys = ctx.Tys
    MainFunOpt = ctx.MainFunOpt
    Logs = ctx.Logs }

let private addLog (ctx: TyCtx) log loc =
  { ctx with Logs = (log, loc) :: ctx.Logs }

let private addError (ctx: TyCtx) message loc =
  { ctx with Logs = (Log.Error message, loc) :: ctx.Logs }

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

  let varDef: VarDef =
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

let private freshTySerialWithLevel levelDelta (ctx: TyCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        TyLevels =
          ctx.TyLevels
          |> TMap.add serial (ctx.Level + levelDelta) }

  serial, ctx

let private freshMetaTy loc (ctx: TyCtx) : Ty * TyCtx =
  let serial, ctx = freshTySerial ctx
  let ty = tyMeta serial loc
  ty, ctx

let private freshMetaTyForPat pat ctx =
  let loc = pat |> patToLoc
  let tySerial, ctx = ctx |> freshTySerial
  let ty = tyMeta tySerial loc
  ty, ctx

let private freshMetaTyForExpr expr ctx =
  let loc = expr |> exprToLoc
  let tySerial, ctx = ctx |> freshTySerial
  let ty = tyMeta tySerial loc
  ty, ctx

let private validateLit ctx lit loc =
  // should validate float too

  let validateIntLit text flavor =
    let nonNeg =
      if S.startsWith "-" text then
        S.skip 1 text
      else
        text

    let ok =
      match intFlavorToSignedness flavor with
      | Unsigned when S.startsWith "-" text -> false

      | _ when S.startsWith "0x" nonNeg ->
        let digits = S.skip 2 nonNeg
        let maxLength = intFlavorToBytes flavor * 2
        digits.Length <= maxLength

      | _ ->
        // should validate precisely
        match flavor with
        | I8
        | I16
        | I32 -> Option.isSome (StdInt.tryParse text)

        | I64
        | IPtr -> Option.isSome (StdInt.Ext.tryParseInt64 text)

        | _ -> Option.isSome (StdInt.Ext.tryParseUInt64 text)

    if ok then
      ctx
    else
      addLog ctx Log.LiteralRangeError loc

  match lit with
  | IntLit text -> validateIntLit text I32
  | IntLitWithFlavor (text, flavor) -> validateIntLit text flavor
  | _ -> ctx

// -----------------------------------------------
// Unification
// -----------------------------------------------

// And meta type resolution by substitution or degeneration.

let private expandMeta (ctx: TyCtx) tySerial : Ty option = ctx.MetaTys |> TMap.tryFind tySerial

let private substTy (ctx: TyCtx) ty : Ty = tySubst (expandMeta ctx) ty

/// Substitutes bound meta tys in a ty.
/// Unbound meta tys are degenerated, i.e. replaced with unit.
let private substOrDegenerateTy (ctx: TyCtx) ty =
  let substMeta tySerial =
    match ctx.MetaTys |> TMap.tryFind tySerial with
    | Some ty -> Some ty

    | _ ->
      // Degenerate unless quantified.
      if ctx.QuantifiedTys |> TSet.contains tySerial then
        None
      else
        Some tyUnit

  tySubst substMeta ty

let private expandSynonyms (ctx: TyCtx) ty : Ty =
  tyExpandSynonyms (fun tySerial -> ctx.Tys |> TMap.tryFind tySerial) ty

/// Does level-up a meta type.
let private levelUp (ctx: TyCtx) tySerial ty =
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

/// Binds a type to a meta type.
///
/// As a precondition, that meta type must be free (not bound)
/// and must not occur in that type (no recursion).
let private bindMetaTy (ctx: TyCtx) tySerial otherTy : TyCtx =
  { ctx with
      MetaTys = ctx.MetaTys |> TMap.add tySerial otherTy
      TyLevels = levelUp ctx tySerial otherTy }

let private unifyTy (ctx: TyCtx) loc (lTy: Ty) (rTy: Ty) : TyCtx =
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
        | UnifyAfterExpandMetaResult.OkBind -> bindMetaTy ctx tySerial otherTy
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
  assert (isNoTy varTy |> not)

  match tyOpt with
  | Some ty ->
    let ctx = unifyTy ctx loc varTy ty
    varTy, ctx

  | None -> varTy, ctx

// -----------------------------------------------
// Generalization and instantiation
// -----------------------------------------------

let private instantiateTyScheme (ctx: TyCtx) (tyScheme: TyScheme) loc : Ty * (TySerial * Ty) list * TyCtx =
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

let private instantiateBoundedTyScheme (ctx: TyCtx) (tyScheme: BoundedTyScheme) loc : Ty * TyCtx =
  let (BoundedTyScheme (fvs, ty, traits)) = tyScheme
  assert (List.isEmpty fvs |> not)

  let serial, tyLevels, ty, assignment =
    doInstantiateTyScheme ctx.Serial ctx.Level ctx.TyLevels fvs ty loc

  let traits =
    let substMeta = tyAssign assignment

    traits
    |> List.map (fun theTrait -> theTrait |> traitMapTys substMeta, loc)

  // Reset level of meta types that move over monomorphic types due to trait bounds
  // so that these meta types aren't get generalized.
  let tyLevels =
    traits
    |> List.fold
         (fun tyLevels (theTrait, _) ->
           let asInnerTy theTrait =
             match theTrait with
             | AddTrait ty -> Some ty
             | IsIntTrait ty -> Some ty
             | IsNumberTrait ty -> Some ty
             | ToCharTrait ty -> Some ty
             | ToIntTrait ty -> Some ty
             | ToFloatTrait ty -> Some ty
             | ToStringTrait ty -> Some ty
             | _ -> None

           match asInnerTy theTrait with
           | Some (Ty (MetaTk (serial, _), _)) -> tyLevels |> TMap.remove serial |> snd
           | _ -> tyLevels)
         tyLevels

  ty,
  { ctx with
      Serial = serial
      TyLevels = tyLevels
      NewTraitBounds = List.append traits ctx.NewTraitBounds }

// #generalizeFun
let private generalizeFun (ctx: TyCtx) (outerLevel: Level) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial

  match funDef.Ty with
  | TyScheme ([], funTy) ->
    assert (isNoTy funTy |> not)

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

    // Mark generalized meta tys (universally quantified vars)
    let ctx =
      let (TyScheme (fvs, _)) = funTyScheme

      { ctx with
          QuantifiedTys =
            fvs
            |> List.fold (fun quantifiedTys tyVar -> TSet.add tyVar quantifiedTys) ctx.QuantifiedTys }

    ctx

  | _ -> unreachable () // Can't generalize already-generalized functions.

let private finishLocalFun (ctx: TyCtx) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial

  let funTy =
    match funDef.Ty with
    | TyScheme ([], funTy) ->
      assert (isNoTy funTy |> not)
      funTy

    | _ -> unreachable ()

  let funTy = substTy ctx funTy

  { ctx with
      Funs =
        ctx.Funs
        |> TMap.add funSerial { funDef with Ty = TyScheme([], funTy) } }

// -----------------------------------------------
// Trait bounds
// -----------------------------------------------

let private tyIsBasic ty =
  let (Ty (tk, _)) = ty

  match tk with
  | ErrorTk _
  | IntTk _
  | FloatTk _
  | BoolTk
  | CharTk
  | StrTk
  | VoidPtrTk _
  | NativePtrTk _ -> true

  | _ -> false

let private addTraitBound theTrait loc (ctx: TyCtx) =
  { ctx with NewTraitBounds = (theTrait, loc) :: ctx.NewTraitBounds }

let private resolveTraitBound (ctx: TyCtx) theTrait loc : TyCtx =
  let ok ctx = ctx

  let error ctx =
    addLog ctx (Log.TyBoundError theTrait) loc
    |> addTraitBound theTrait loc

  let unify2 (lTy1, rTy1) (lTy2, rTy2) =
    let ctx = unifyTy ctx loc lTy1 rTy1
    unifyTy ctx loc lTy2 rTy2

  // Coerce to int as default.
  let defaultToInt ctx ty = unifyTy ctx loc ty tyInt

  /// integer, bool, char, or string
  let expectBasic ctx ty =
    if tyIsBasic ty then
      ok ctx
    else
      error ctx

  match theTrait with
  | AddTrait ty ->
    let (Ty (tk, _)) = ty

    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | CharTk
    | StrTk -> ok ctx

    | _ -> defaultToInt ctx ty

  | EqualTrait ty ->
    let rec go memo ty =
      let (Ty (tk, tyArgs)) = ty

      let onTys memo tys =
        tys
        |> List.fold
             (fun (ok, memo) tyArg ->
               if not ok then
                 ok, memo
               else
                 let ok1, memo = go memo tyArg
                 ok && ok1, memo)
             (true, memo)

      let allowRec memo action =
        if memo |> TSet.contains ty then
          true, memo
        else
          // Put memo to prevent recursion. Suppose `ty` is okay here.
          let memo = memo |> TSet.add ty

          // If not ok, `ty` and other tys (that are newly added and depend on `ty`)
          // should be removed from memo. But no need to do here because
          // (1) memo is no longer used if not ok and (2) memo is discarded later.
          action memo

      match tk, tyArgs with
      | _ when tyIsBasic ty -> true, memo

      | TupleTk, []
      | NativeFunTk, _ -> true, memo

      // Don't memoize structural types
      // because it doesn't cause infinite recursion
      // and unfortunately memo is discarded.
      | TupleTk, _ -> onTys memo tyArgs
      | ListTk, [ itemTy ] -> go memo itemTy

      | UnionTk (tySerial, _), _ ->
        allowRec memo (fun memo ->
          match ctx.Tys |> mapFind tySerial with
          | UnionTyDef (_, tyVars, variants, _) ->
            let assignmentOpt =
              match listTryZip tyVars tyArgs with
              | assignment, [], [] -> Some assignment
              | _ -> None

            let payloadTysOpt =
              match assignmentOpt with
              | Some assignment ->
                variants
                |> List.choose (fun variantSerial ->
                  let variantDef = ctx.Variants |> mapFind variantSerial

                  if variantDef.HasPayload then
                    variantDef.PayloadTy
                    |> tySubst (fun tySerial -> assocTryFind compare tySerial assignment)
                    |> Some
                  else
                    None)
                |> Some
              | _ -> None

            match payloadTysOpt with
            | Some payloadTys -> onTys memo payloadTys
            | _ -> false, memo
          | _ -> false, memo)

      | _ -> false, memo

    let resolved, _ = go (TSet.empty tyCompare) ty

    if resolved then ok ctx else error ctx

  | CompareTrait ty ->
    match ty with
    | Ty (TupleTk, []) -> ok ctx
    | _ -> expectBasic ctx ty

  | IndexTrait (lTy, rTy, resultTy) ->
    match lTy with
    | Ty (ErrorTk _, _) -> ok ctx
    | Ty (StrTk, _) -> unify2 (rTy, tyInt) (resultTy, tyChar)
    | _ -> error ctx

  | IsIntTrait ty ->
    match ty with
    | Ty (ErrorTk _, _)
    | Ty (IntTk _, _) -> ok ctx

    | _ -> defaultToInt ctx ty

  | IsNumberTrait ty ->
    match ty with
    | Ty (ErrorTk _, _)
    | Ty (IntTk _, _)
    | Ty (FloatTk _, _) -> ok ctx

    | _ -> defaultToInt ctx ty

  | ToCharTrait (Ty (tk, _)) ->
    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | CharTk
    | StrTk -> ok ctx

    | _ -> error ctx

  | ToIntTrait (Ty (tk, _)) ->
    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | CharTk
    | StrTk
    | VoidPtrTk _
    | NativePtrTk _ -> ok ctx

    | _ -> error ctx

  | ToFloatTrait (Ty (tk, _)) ->
    match tk with
    | ErrorTk _
    | IntTk _
    | FloatTk _
    | StrTk -> ok ctx

    | _ -> error ctx

  | ToStringTrait ty -> expectBasic ctx ty

  | PtrTrait ty ->
    let isPtrTy (Ty (tk, _)) =
      match tk with
      | VoidPtrTk _
      | NativePtrTk _
      | NativeFunTk -> true
      | _ -> false

    match ty with
    | Ty (ErrorTk _, _) -> ok ctx
    | _ when isPtrTy ty -> ok ctx
    | Ty (LinearTk, [ itemTy ]) when isPtrTy itemTy -> ok ctx
    | _ -> error ctx

  | PtrSizeTrait (Ty (tk, _)) ->
    match tk with
    | ErrorTk _
    | IntTk IPtr
    | IntTk UPtr
    | ObjTk
    | ListTk
    | VoidPtrTk _
    | NativePtrTk _
    | NativeFunTk -> ok ctx

    | _ -> error ctx

  | DifferentTypesTrait (lTy, rTy) ->
    match lTy, rTy with
    | Ty (ErrorTk _, _), _
    | _, Ty (ErrorTk _, _) -> ok ctx

    | _ when not (tyEqual lTy rTy) -> ok ctx
    | _ -> error ctx

let private attemptResolveTraitBounds (ctx: TyCtx) : TyCtx =
  let subst (ctx: TyCtx) ty =
    ty |> substTy ctx |> typingExpandSynonyms ctx.Tys

  let logs, ctx = ctx.Logs, { ctx with Logs = [] }

  let traitAcc, (ctx: TyCtx) =
    ctx.NewTraitBounds
    |> List.fold
         (fun (traitAcc, (ctx: TyCtx)) (theTrait, loc) ->
           let theTrait = traitMapTys (subst ctx) theTrait

           let oldCtx = ctx
           assert (List.isEmpty oldCtx.Logs)

           let ctx = resolveTraitBound ctx theTrait loc

           if ctx.Logs |> List.isEmpty then
             traitAcc, ctx
           else
             (theTrait, loc) :: traitAcc, oldCtx)
         ([], ctx)

  { ctx with
      TraitBounds = List.append traitAcc ctx.TraitBounds
      NewTraitBounds = []
      Logs = logs }

let private resolveTraitBoundsAll (ctx: TyCtx) =
  let subst (ctx: TyCtx) ty =
    ty |> substTy ctx |> typingExpandSynonyms ctx.Tys

  // Even if a trait bound can't be resolved,
  // it can become able to resolve after some resolution (unification),
  // so try to resolve all bounds repeatedly until no bound is resolved.
  let rec go (ctx: TyCtx) =
    let traits, ctx =
      ctx.NewTraitBounds, { ctx with NewTraitBounds = [] }

    let n = List.length traits

    let ctx: TyCtx =
      traits
      |> List.fold
           (fun ctx (theTrait, loc) ->
             let theTrait = traitMapTys (subst ctx) theTrait
             resolveTraitBound ctx theTrait loc)
           ctx

    if List.length ctx.NewTraitBounds < n then
      let ctx = { ctx with Logs = [] }
      go ctx
    else
      ctx

  let logs, ctx = ctx.Logs, { ctx with Logs = [] }

  let ctx =
    { ctx with
        TraitBounds = []
        NewTraitBounds = List.append ctx.NewTraitBounds ctx.TraitBounds }

  let ctx = go ctx

  assert (not (List.isEmpty ctx.Logs)
          || List.isEmpty ctx.TraitBounds)

  { ctx with
      Logs = List.append logs ctx.Logs
      TraitBounds = [] }

// -----------------------------------------------
// Others
// -----------------------------------------------

let private isNoTy ty =
  match ty with
  | Ty (ErrorTk _, _) -> true
  | _ -> false

let private addVarLevels ctx pat =
  let onVar (ctx: TyCtx) varSerial loc =
    let varDef = ctx.Vars |> mapFind varSerial

    if isNoTy varDef.Ty then
      let metaTy, ctx = freshMetaTy loc ctx
      let varDef = { varDef with Ty = metaTy }
      { ctx with Vars = ctx.Vars |> TMap.add varSerial varDef }
    else
      ctx

  match pat with
  | TLitPat _
  | TDiscardPat _
  | TVariantPat _ -> ctx

  | TVarPat (_, varSerial, _, loc) -> onVar ctx varSerial loc
  | TNodePat (_, argPats, _, _) -> argPats |> List.fold addVarLevels ctx

  | TAsPat (bodyPat, varSerial, loc) ->
    let ctx = addVarLevels ctx bodyPat
    onVar ctx varSerial loc

  | TOrPat (l, r, _) ->
    let ctx = addVarLevels ctx l
    addVarLevels ctx r

let private initializeFunTy (ctx: TyCtx) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial

  match funDef.Ty with
  | TyScheme ([], funTy) when isNoTy funTy ->
    let tySerial, ctx = freshTySerialWithLevel 1 ctx
    let metaTy = tyMeta tySerial funDef.Loc

    let funDef =
      { funDef with Ty = TyScheme([], metaTy) }

    { ctx with Funs = ctx.Funs |> TMap.add funSerial funDef }

  | _ -> ctx

let private collectVarsAndFuns ctx stmts =
  stmts
  |> List.fold
       (fun ctx stmt ->
         match stmt with
         | TLetValStmt (pat, _, _) -> addVarLevels ctx pat
         | TLetFunStmt (funSerial, _, _, _, _, _) -> initializeFunTy ctx funSerial
         | _ -> ctx)
       ctx

let private collectVarsInPats ctx pats = pats |> List.fold addVarLevels ctx

// payloadTy, unionTy, variantTy
let private instantiateVariant variantSerial loc (ctx: TyCtx) : Ty * Ty * Ty * TyCtx =
  let variantDef = ctx.Variants |> mapFind variantSerial
  let tySerial = variantDef.UnionTySerial

  let tyArgs =
    match ctx.Tys |> mapFind tySerial with
    | UnionTyDef (_, tyArgs, _, _) -> tyArgs
    | _ -> []

  match tyArgs with
  | [] ->
    let payloadTy = variantDef.PayloadTy
    let unionTy = tyUnion tySerial [] loc

    let variantTy =
      if variantDef.HasPayload then
        tyFun payloadTy unionTy
      else
        unionTy

    payloadTy, unionTy, variantTy, ctx

  | _ ->
    let payloadTy = variantDef.PayloadTy

    let unionTy =
      let tyArgs =
        tyArgs
        |> List.map (fun tyArg -> Ty(MetaTk(tyArg, loc), []))

      tyUnion tySerial tyArgs loc

    let variantTy, assignment, ctx =
      let variantTy =
        if variantDef.HasPayload then
          tyFun payloadTy unionTy
        else
          unionTy

      let tyScheme = TyScheme(tyArgs, variantTy)

      instantiateTyScheme ctx tyScheme loc

    let payloadTy = tyAssign assignment payloadTy
    let unionTy = tyAssign assignment unionTy
    payloadTy, unionTy, variantTy, ctx

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

    let _, paramTys, resultTy =
      match ty with
      | Ty (FunTk, [ Ty (TupleTk, []); resultTy ]) -> 0, [], resultTy
      | _ -> tyToArgList ty

    tyNativeFun paramTys resultTy

  nativeFunTy, ctx

/// Resolves ascription type.
///
/// Current level is assigned to `'T`s and `_`s.
let private resolveAscriptionTy ctx ascriptionTy =
  let rec go (ty, ctx: TyCtx) =
    match ty with
    | Ty (ErrorTk _, _) -> ty, ctx

    | Ty (InferTk loc, _) ->
      let serial, ctx = freshTySerial ctx
      tyMeta serial loc, ctx

    | Ty (UnivTk (serial, _, _), _) when ctx.TyLevels |> TMap.containsKey serial |> not ->
      let ctx =
        { ctx with TyLevels = ctx.TyLevels |> TMap.add serial ctx.Level }

      ty, ctx

    | Ty (UnivTk _, _) -> ty, ctx

    | Ty (_, []) -> ty, ctx

    | Ty (tk, tys) ->
      let tys, ctx = (tys, ctx) |> stMap go
      Ty(tk, tys), ctx

  go (ascriptionTy, ctx)

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

let private txApp f x resultTy loc =
  TNodeExpr(TAppEN, [ f; x ], resultTy, loc)

/// Must be used after error occurred.
let private txAbort (ctx: TyCtx) loc =
  assert (ctx.Logs |> List.isEmpty |> not)

  let ty = tyError loc
  TNodeExpr(TAbortEN, [], ty, loc), ty, ctx

/// Reports an error and makes a dummy expression.
let private errorExpr (ctx: TyCtx) msg loc : TExpr * Ty * TyCtx =
  let ctx = addError ctx msg loc
  txAbort ctx loc

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private inferLitPat ctx pat lit =
  let ctx = validateLit ctx lit (patToLoc pat)
  pat, litToTy lit, ctx

/// Tries to get ty ascription from pat.
let private patToAscriptionTy pat =
  match pat with
  | TNodePat (TAscribePN, _, ty, _) -> Some ty

  | TAsPat (bodyPat, _, _) -> patToAscriptionTy bodyPat

  | TOrPat (l, r, _) ->
    match patToAscriptionTy l with
    | None -> patToAscriptionTy r
    | it -> it

  | _ -> None

let private inferNilPat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyList itemTy
  TNodePat(TNilPN, [], ty, loc), ty, ctx

let private inferDiscardPat ctx pat loc =
  let ty, ctx = ctx |> freshMetaTyForPat pat
  TDiscardPat(ty, loc), ty, ctx

let private inferVarPat (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc
  TVarPat(PrivateVis, varSerial, ty, loc), ty, ctx

let private inferVariantPat (ctx: TyCtx) variantSerial loc =
  let _, unionTy, _, ctx =
    instantiateVariant variantSerial loc ctx

  let ctx =
    let variantDef = ctx.Variants |> mapFind variantSerial

    if variantDef.HasPayload then
      addError ctx "Variant with payload must be used in the form of: `Variant pattern`." loc
    else
      ctx

  TVariantPat(variantSerial, unionTy, loc), unionTy, ctx

let private inferVariantAppPat (ctx: TyCtx) variantSerial payloadPat loc =
  let expectedPayloadTy, unionTy, _, ctx =
    instantiateVariant variantSerial loc ctx

  let payloadPat, payloadTy, ctx = inferPat ctx payloadPat

  let ctx =
    unifyTy ctx loc expectedPayloadTy payloadTy

  TNodePat(TVariantAppPN variantSerial, [ payloadPat ], unionTy, loc), unionTy, ctx

let private inferConsPat ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let listTy = tyList lTy
  let ctx = unifyTy ctx loc rTy listTy

  TNodePat(TConsPN, [ l; r ], listTy, loc), listTy, ctx

let private inferTuplePat ctx itemPats loc =
  let itemPats, itemTys, ctx = doInferPats ctx itemPats

  let tupleTy = tyTuple itemTys
  TNodePat(TTuplePN, itemPats, tupleTy, loc), tupleTy, ctx

let private inferAscribePat ctx body ascriptionTy loc =
  let body, bodyTy, ctx = inferPat ctx body
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy

  let ctx = unifyTy ctx loc bodyTy ascriptionTy
  body, ascriptionTy, ctx

let private inferAsPat ctx body varSerial loc =
  let body, bodyTy, ctx = inferPat ctx body

  let _, ctx =
    ctx |> unifyVarTy varSerial (Some bodyTy) loc

  TAsPat(body, varSerial, loc), bodyTy, ctx

let private inferOrPat ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let ctx = unifyTy ctx loc lTy rTy
  TOrPat(l, r, loc), lTy, ctx

let private inferAbortPat ctx loc =
  let targetTy = tyError loc
  tpAbort targetTy loc, targetTy, ctx

let private doInferPats ctx pats =
  let rec go ctx patAcc tyAcc pats =
    match pats with
    | [] -> List.rev patAcc, List.rev tyAcc, ctx

    | pat :: pats ->
      let pat, ty, ctx = inferPat ctx pat
      go ctx (pat :: patAcc) (ty :: tyAcc) pats

  go ctx [] [] pats

let private inferNodePat ctx pat =
  let kind, argPats, loc =
    match pat with
    | TNodePat (kind, argPats, _, loc) -> kind, argPats, loc
    | _ -> unreachable ()

  let getTy () =
    match pat with
    | TNodePat (_, _, ty, _) -> ty
    | _ -> unreachable ()

  match kind, argPats with
  | TNilPN, _ -> inferNilPat ctx pat loc
  | TConsPN, [ l; r ] -> inferConsPat ctx l r loc
  | TConsPN, _ -> unreachable ()

  | TVariantAppPN variantSerial, [ payloadPat ] -> inferVariantAppPat ctx variantSerial payloadPat loc
  | TVariantAppPN _, _ -> unreachable ()

  | TTuplePN, _ -> inferTuplePat ctx argPats loc

  | TAbortPN, _ -> inferAbortPat ctx loc

  | TAscribePN, [ bodyPat ] -> inferAscribePat ctx bodyPat (getTy ()) loc
  | TAscribePN, _ -> unreachable ()

  | TAppPN, _ // Error in NameRes.
  | TNavPN _, _ -> unreachable () // Resolved in NameRes.

let private inferPat ctx pat : TPat * Ty * TyCtx =
  match pat with
  | TLitPat (lit, _) -> inferLitPat ctx pat lit
  | TDiscardPat (_, loc) -> inferDiscardPat ctx pat loc
  | TVarPat (_, varSerial, _, loc) -> inferVarPat ctx varSerial loc
  | TVariantPat (variantSerial, _, loc) -> inferVariantPat ctx variantSerial loc
  | TNodePat _ -> inferNodePat ctx pat
  | TAsPat (bodyPat, serial, loc) -> inferAsPat ctx bodyPat serial loc
  | TOrPat (l, r, loc) -> inferOrPat ctx l r loc

let private inferRefutablePat ctx pat = inferPat ctx pat

let private inferIrrefutablePat ctx pat =
  if pat
     |> patIsClearlyExhaustive (isNewtypeVariant ctx)
     |> not then
    let loc = patToLoc pat

    let ctx =
      addLog ctx Log.IrrefutablePatNonExhaustiveError loc

    let ty, ctx = freshMetaTyForPat pat ctx
    tpAbort ty loc, ty, ctx
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

  TVarExpr(varSerial, ty, loc), ty, ctx

let private inferFunExpr (ctx: TyCtx) funSerial loc =
  let funDef = ctx.Funs |> mapFind funSerial
  let ty, _, ctx = instantiateTyScheme ctx funDef.Ty loc

  let ctx =
    if ctx.GrayFuns |> TSet.contains funSerial then
      { ctx with
          GrayInstantiations =
            ctx.GrayInstantiations
            |> Multimap.add funSerial (ty, loc) }
    else
      ctx

  TFunExpr(funSerial, ty, loc), ty, ctx

let private inferVariantExpr (ctx: TyCtx) variantSerial loc =
  let _, _, ty, ctx =
    instantiateVariant variantSerial loc ctx

  TVariantExpr(variantSerial, ty, loc), ty, ctx

let private primNotTy = tyFun tyBool tyBool

let private primAddScheme =
  let meta id = tyMeta id noLoc
  let addTy = meta 1
  BoundedTyScheme([ 1 ], tyFun addTy (tyFun addTy addTy), [ AddTrait addTy ])

let private primSubEtcScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun ty ty), [ IsNumberTrait ty ])

let private primBitAndEtcScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun ty ty), [ IsIntTrait ty ])

let private primShiftScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun tyInt ty), [ IsIntTrait ty ])

let private primEqualScheme =
  let meta id = tyMeta id noLoc
  let argTy = meta 1
  BoundedTyScheme([ 1 ], tyFun argTy (tyFun argTy tyBool), [ EqualTrait argTy ])

let private primLessScheme =
  let meta id = tyMeta id noLoc
  let compareTy = meta 1
  BoundedTyScheme([ 1 ], tyFun compareTy (tyFun compareTy tyBool), [ CompareTrait compareTy ])

let private primCompareScheme =
  let meta id = tyMeta id noLoc
  let compareTy = meta 1
  BoundedTyScheme([ 1 ], tyFun compareTy (tyFun compareTy tyInt), [ CompareTrait compareTy ])

let private primIntScheme flavor =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let resultTy = Ty(IntTk flavor, [])
  BoundedTyScheme([ 1 ], tyFun srcTy resultTy, [ ToIntTrait srcTy ])

let private primFloatScheme flavor =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let resultTy = Ty(FloatTk flavor, [])
  BoundedTyScheme([ 1 ], tyFun srcTy resultTy, [ ToFloatTrait srcTy ])

let private primCharScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  BoundedTyScheme([ 1 ], tyFun srcTy tyChar, [ ToCharTrait srcTy ])

let private primStringScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  BoundedTyScheme([ 1 ], tyFun srcTy tyStr, [ ToStringTrait srcTy ])

let private primBoxScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  TyScheme([ 1 ], tyFun itemTy tyObj)

let private primUnboxScheme =
  let meta id = tyMeta id noLoc
  let resultTy = meta 1
  TyScheme([ 1 ], tyFun tyObj resultTy)

let private primStrLengthTy = tyFun tyStr tyInt

let private primNilScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  TyScheme([ 1 ], tyList itemTy)

let private primConsScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  let listTy = tyList itemTy
  TyScheme([ 1 ], tyFun itemTy (tyFun listTy listTy))

let private primExitScheme =
  let meta id = tyMeta id noLoc
  let resultTy = meta 1
  TyScheme([ 1 ], tyFun tyInt resultTy)

let private primAssertTy = tyFun tyBool tyUnit

let private primInRegionTy = tyFun (tyFun tyUnit tyInt) tyInt

let private primAcquireTy =
  let itemTy = tyMeta 1 noLoc
  TyScheme([ 1 ], tyFun itemTy (tyLinear itemTy))

let private primDisposeTy =
  let itemTy = tyMeta 1 noLoc
  TyScheme([ 1 ], tyFun (tyLinear itemTy) itemTy)

let private primNullPtrScheme =
  let ptrTy = tyMeta 1 noLoc
  BoundedTyScheme([ 1 ], ptrTy, [ PtrTrait ptrTy ])

let private primPtrCastScheme =
  let srcTy = tyMeta 1 noLoc
  let destTy = tyMeta 2 noLoc

  BoundedTyScheme(
    [ 1; 2 ],
    tyFun srcTy destTy,
    [ PtrTrait srcTy
      PtrTrait destTy
      DifferentTypesTrait(srcTy, destTy) ]
  )

let private primPtrInvalidScheme =
  let ptrTy = tyMeta 1 noLoc

  BoundedTyScheme([ 1 ], tyFun tyUNativeInt ptrTy, [ PtrTrait ptrTy ])

let private primNativeCastScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let destTy = meta 2

  BoundedTyScheme(
    [ 1; 2 ],
    tyFun srcTy destTy,
    [ PtrSizeTrait srcTy
      PtrSizeTrait destTy ]
  )

let private inferPrimExpr ctx prim loc =
  let onMono ty = TPrimExpr(prim, ty, loc), ty, ctx

  let onUnbounded scheme =
    let primTy, _, ctx = instantiateTyScheme ctx scheme loc
    TPrimExpr(prim, primTy, loc), primTy, ctx

  let onBounded scheme =
    let primTy, ctx =
      instantiateBoundedTyScheme ctx scheme loc

    TPrimExpr(prim, primTy, loc), primTy, ctx

  match prim with
  | TPrim.Not -> onMono primNotTy
  | TPrim.Add -> onBounded primAddScheme

  | TPrim.Sub
  | TPrim.Mul
  | TPrim.Div
  | TPrim.Modulo -> onBounded primSubEtcScheme

  | TPrim.BitAnd
  | TPrim.BitOr
  | TPrim.BitXor -> onBounded primBitAndEtcScheme

  | TPrim.LeftShift
  | TPrim.RightShift -> onBounded primShiftScheme

  | TPrim.Equal -> onBounded primEqualScheme
  | TPrim.Less -> onBounded primLessScheme
  | TPrim.Compare -> onBounded primCompareScheme

  | TPrim.ToInt flavor -> onBounded (primIntScheme flavor)
  | TPrim.ToFloat flavor -> onBounded (primFloatScheme flavor)
  | TPrim.Char -> onBounded primCharScheme
  | TPrim.String -> onBounded primStringScheme
  | TPrim.Box -> onUnbounded primBoxScheme
  | TPrim.Unbox -> onUnbounded primUnboxScheme

  | TPrim.StrLength -> onMono primStrLengthTy

  | TPrim.Nil -> onUnbounded primNilScheme
  | TPrim.Cons -> onUnbounded primConsScheme

  | TPrim.Discriminant _ ->
    let ctx =
      addError ctx "Illegal use of __discriminant. Hint: `__discriminant Variant`." loc

    txAbort ctx loc

  | TPrim.Exit -> onUnbounded primExitScheme
  | TPrim.Assert -> onMono primAssertTy

  | TPrim.Printfn ->
    let ctx =
      addError
        ctx
        "Illegal use of printfn. printfn must have string literal as first argument; e.g. `printfn \"%s\" s`."
        loc

    txAbort ctx loc

  | TPrim.InRegion -> onMono primInRegionTy
  | TPrim.Acquire -> onUnbounded primAcquireTy
  | TPrim.Dispose -> onUnbounded primDisposeTy

  | TPrim.PtrCast -> onBounded primPtrCastScheme
  | TPrim.PtrInvalid -> onBounded primPtrInvalidScheme

  | TPrim.NativeFun ->
    let ctx =
      addError ctx "Illegal use of __nativeFun. Hint: `__nativeFun (\"funName\", arg1, arg2, ...): ResultType`." loc

    txAbort ctx loc

  | TPrim.NativeCast -> onBounded primNativeCastScheme

  | TPrim.NativeExpr ->
    let ctx =
      addError ctx "Illegal use of __nativeExpr. Hint: `__nativeExpr \"Some C code here.\"`." loc

    txAbort ctx loc

  | TPrim.NativeStmt ->
    let ctx =
      addError ctx "Illegal use of __nativeStmt. Hint: `__nativeStmt \"Some C code here.\"`." loc

    txAbort ctx loc

  | TPrim.NativeDecl ->
    let ctx =
      addError ctx "Illegal use of __nativeDecl. Hint: `__nativeDecl \"Some C code here.\"`." loc

    txAbort ctx loc

  | TPrim.NullPtr -> onBounded primNullPtrScheme

  | TPrim.PtrSelect
  | TPrim.PtrRead
  | TPrim.PtrWrite
  | TPrim.PtrAsIn
  | TPrim.PtrAsNative -> errorExpr ctx "This function misses some argument." loc

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
      | Some ((Ty (RecordTk (tySerial, _), tyArgs)) as recordTy) ->
        assert (List.isEmpty tyArgs)

        match ctx |> findTy tySerial with
        | RecordTyDef (name, _unimplTyArgs, fieldDefs, _, _) -> Some(recordTy, name, fieldDefs)
        | _ -> None

      | _ -> None

    match baseTyOpt |> asRecordTy with
    | ((Some _) as it) -> it
    | _ -> expectOpt |> asRecordTy

  match recordTyInfoOpt with
  | None ->
    let ctx =
      addError ctx "Can't infer type of record." loc

    txAbort ctx loc

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
      |> stMap (fun (field, (fieldDefs, ctx)) ->
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
    | None -> TRecordExpr(None, fields, recordTy, loc), recordTy, ctx

    | Some baseExpr ->
      // Assign to a temporary var so that RecordRes can reuse the expr safely.
      // (This kind of modification is not business of typing, though.)
      // { base with fields... } ==> let t = base in { t with fields... }
      let varSerial, ctx = freshVar ctx "base" recordTy loc

      let varPat =
        TVarPat(PrivateVis, varSerial, recordTy, loc)

      let varExpr = TVarExpr(varSerial, recordTy, loc)

      let recordExpr =
        TRecordExpr(Some varExpr, fields, recordTy, loc)

      txLetIn (TLetValStmt(varPat, baseExpr, loc)) recordExpr, recordTy, ctx

/// match 'a with ( | 'a -> 'b )*
let private inferMatchExpr ctx expectOpt itself cond arms loc =
  let targetTy, ctx = freshMetaTyForExpr itself ctx

  let cond, condTy, ctx = inferExpr ctx None cond

  let ctx =
    arms
    |> List.fold (fun ctx (pat, _, _) -> addVarLevels ctx pat) ctx

  let arms, ctx =
    (arms, ctx)
    |> stMap (fun ((pat, guard, body), ctx) ->
      let pat, patTy, ctx = inferRefutablePat ctx pat

      let ctx = unifyTy ctx (patToLoc pat) patTy condTy

      let guard, guardTy, ctx = inferExpr ctx None guard

      let ctx =
        unifyTy ctx (exprToLoc guard) guardTy tyBool

      let body, bodyTy, ctx = inferExpr ctx expectOpt body

      let ctx =
        unifyTy ctx (exprToLoc body) targetTy bodyTy

      (pat, guard, body), ctx)

  TMatchExpr(cond, arms, targetTy, loc), targetTy, ctx

let private inferNavExpr ctx l (r: Ident, rLoc) loc =
  let fail ctx =
    let ctx =
      addError ctx ("Expected to have field: '" + r + "'.") loc

    txAbort ctx loc

  let l, lTy, ctx = inferExpr ctx None l

  let lTy = substTy ctx lTy

  match lTy, r with
  | Ty (StrTk, []), "Length" ->
    let funExpr =
      TPrimExpr(TPrim.StrLength, tyFun tyStr tyInt, loc)

    txApp funExpr l tyInt loc, tyInt, ctx

  | Ty (RecordTk (tySerial, _), tyArgs), _ ->
    assert (List.isEmpty tyArgs)

    let fieldTyOpt =
      match ctx |> findTy tySerial with
      | RecordTyDef (_, _unimplTyArgs, fieldDefs, _, _) ->
        match fieldDefs
              |> List.tryFind (fun (theName, _, _) -> theName = r)
          with
        | Some (_, fieldTy, _) -> Some fieldTy
        | None -> None
      | _ -> None

    match fieldTyOpt with
    | Some fieldTy -> TNavExpr(l, (r, rLoc), fieldTy, loc), fieldTy, ctx
    | None -> fail ctx

  | _ -> fail ctx

let private inferUntypedExprs ctx exprs =
  (exprs, ctx)
  |> stMap (fun (expr, ctx) ->
    let expr, _, ctx =
      match expr with
      | TNodeExpr (TTyPlaceholderEN, [], ty, loc) ->
        let ty, ctx = resolveAscriptionTy ctx ty
        TNodeExpr(TTyPlaceholderEN, [], ty, loc), ty, ctx

      | _ -> inferExpr ctx None expr

    expr, ctx)

let private inferAppExpr ctx itself =
  let callee, arg, loc =
    match itself with
    | TNodeExpr (TAppEN, [ callee; arg ], _, loc) -> callee, arg, loc
    | _ -> unreachable ()

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

  txApp callee arg targetTy loc, targetTy, ctx

type private PtrProjectionInferError =
  | PtrProjectionOk of TExpr * Ty * TyCtx
  | PtrProjectionError of msg: string * Loc * TyCtx

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private PtrOperationKind =
  | Select
  | Read
  | Write

/// (For argument of __ptr.)
let private inferExprAsPtrProjection ctx (kind: PtrOperationKind) expr : TExpr * Ty * TyCtx =
  let rec go ctx expr =
    match expr with
    | TNodeExpr (TIndexEN, [ ptr; index ], _, loc) ->
      match go ctx ptr with
      | PtrProjectionOk (ptr, ptrTy, ctx) ->
        let index, indexTy, ctx = inferExpr ctx (Some tyInt) index

        let ctx =
          unifyTy ctx (exprToLoc index) indexTy tyInt

        PtrProjectionOk(TNodeExpr(TPtrOffsetEN, [ ptr; index ], ptrTy, loc), ptrTy, ctx)

      | err -> err

    | _ ->
      let expr, ty, ctx = inferExpr ctx None expr
      let ty = substTy ctx ty

      match ty with
      | Ty (NativePtrTk mode, _) ->
        match mode, kind with
        | RefMode.ReadOnly, PtrOperationKind.Write ->
          PtrProjectionError("Expected nativeptr but was __inptr.", exprToLoc expr, ctx)
        | RefMode.WriteOnly, PtrOperationKind.Read ->
          PtrProjectionError("Expected nativeptr but was __outptr.", exprToLoc expr, ctx)
        | _ -> PtrProjectionOk(expr, ty, ctx)

      | _ -> PtrProjectionError("Expected pointer type.", exprToLoc expr, ctx)

  match go ctx expr with
  | PtrProjectionOk (expr, ty, ctx) -> expr, ty, ctx

  | PtrProjectionError (msg, loc, ctx) ->
    let ctx = addError ctx msg loc

    txAbort ctx loc

let private inferPrimAppExpr ctx itself =
  let prim, arg, loc =
    match itself with
    | TNodeExpr (TAppEN, [ TPrimExpr (prim, _, loc); arg ], _, _) -> prim, arg, loc
    | _ -> unreachable ()

  match prim, arg with
  // __discriminant Variant
  | TPrim.Discriminant, TVariantExpr (variantSerial, _, _) ->
    TNodeExpr(TDiscriminantEN variantSerial, [], tyInt, loc), tyInt, ctx

  // printfn "..."
  | TPrim.Printfn, TLitExpr (StrLit format, _) ->
    let funTy, targetTy =
      match analyzeFormat format with
      | (Ty (FunTk, [ _; targetTy ])) as funTy -> funTy, targetTy
      | _ -> unreachable ()

    txApp (TPrimExpr(TPrim.Printfn, funTy, loc)) arg targetTy loc, targetTy, ctx

  | TPrim.PtrAsIn, _ ->
    let arg, argTy, ctx = inferExpr ctx None arg
    let argTy = substTy ctx argTy

    let ok resultTy =
      txApp (TPrimExpr(TPrim.NativeCast, tyFun argTy resultTy, loc)) arg resultTy loc, resultTy, ctx

    match argTy with
    | Ty (VoidPtrTk IsMut, _) -> ok tyVoidInPtr
    | Ty (NativePtrTk RefMode.ReadWrite, [ itemTy ]) -> ok (tyInPtr itemTy)
    | Ty (NativePtrTk RefMode.WriteOnly, [ itemTy ]) -> ok (tyInPtr itemTy)
    | Ty (ErrorTk _, _) -> arg, argTy, ctx
    | _ -> errorExpr ctx "Expected nativeptr, __outptr or voidptr type." loc

  | TPrim.PtrAsNative, _ ->
    let arg, argTy, ctx = inferExpr ctx None arg
    let argTy = substTy ctx argTy

    let ok resultTy =
      txApp (TPrimExpr(TPrim.NativeCast, tyFun argTy resultTy, loc)) arg resultTy loc, resultTy, ctx

    match argTy with
    | Ty (VoidPtrTk IsConst, _) -> ok tyVoidPtr
    | Ty (NativePtrTk RefMode.ReadOnly, [ itemTy ]) -> ok (tyNativePtr itemTy)
    | Ty (NativePtrTk RefMode.WriteOnly, [ itemTy ]) -> ok (tyNativePtr itemTy)
    | Ty (ErrorTk _, _) -> arg, argTy, ctx
    | _ -> errorExpr ctx "Expected __inptr, __voidinptr or __outptr type." loc

  | TPrim.PtrSelect, _ -> inferExprAsPtrProjection ctx PtrOperationKind.Select arg

  | TPrim.PtrRead, _ ->
    let expr, ty, ctx =
      inferExprAsPtrProjection ctx PtrOperationKind.Read arg

    let itemTy =
      // #unwrap_ptr_ty
      match ty with
      | Ty (NativePtrTk _, [ item ]) -> item
      | Ty (ErrorTk _, _) -> ty
      | _ -> unreachable ()

    TNodeExpr(TPtrReadEN, [ expr ], itemTy, loc), itemTy, ctx

  // __nativeFun f
  | TPrim.NativeFun, TFunExpr (funSerial, _, _) ->
    let targetTy, ctx = castFunAsNativeFun funSerial ctx
    TNodeExpr(TNativeFunEN funSerial, [], targetTy, loc), targetTy, ctx

  // __nativeFun "funName"
  | TPrim.NativeFun, TLitExpr (StrLit funName, _) ->
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TCallNativeEN funName, [], targetTy, loc), targetTy, ctx

  // __nativeFun ("funName", arg1, arg2, ...)
  | TPrim.NativeFun, TNodeExpr (TTupleEN, TLitExpr (StrLit funName, _) :: args, _, _) ->
    // Type of native function is unchecked. Type ascriptions must be written correctly.
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    let args, ctx = inferUntypedExprs ctx args

    TNodeExpr(TCallNativeEN funName, args, targetTy, loc), targetTy, ctx

  // __nativeExpr "code"
  | TPrim.NativeExpr, TLitExpr (StrLit code, _) ->
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TNativeExprEN code, [], targetTy, loc), targetTy, ctx

  // __nativeExpr ("code", args...)
  | TPrim.NativeExpr, TNodeExpr (TTupleEN, TLitExpr (StrLit code, _) :: args, _, _) ->
    let args, ctx = inferUntypedExprs ctx args
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TNativeExprEN code, args, targetTy, loc), targetTy, ctx

  // __nativeStmt "code"
  | TPrim.NativeStmt, TLitExpr (StrLit code, _) -> TNodeExpr(TNativeStmtEN code, [], tyUnit, loc), tyUnit, ctx

  // __nativeStmt ("code", args...)
  | TPrim.NativeStmt, TNodeExpr (TTupleEN, TLitExpr (StrLit code, _) :: args, _, _) ->
    let args, ctx = inferUntypedExprs ctx args
    TNodeExpr(TNativeStmtEN code, args, tyUnit, loc), tyUnit, ctx

  // __nativeDecl "code"
  | TPrim.NativeDecl, TLitExpr (StrLit code, _) -> TNodeExpr(TNativeDeclEN code, [], tyUnit, loc), tyUnit, ctx

  | _ -> inferAppExpr ctx itself

let private inferWriteExpr ctx expr : TExpr * Ty * TyCtx =
  let ptr, item, loc =
    match expr with
    | TNodeExpr (TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.PtrWrite, _, loc); ptr ], _, _); item ], _, _) ->
      ptr, item, loc
    | _ -> unreachable ()

  let ptr, ptrTy, ctx =
    inferExprAsPtrProjection ctx PtrOperationKind.Write ptr

  let itemTy =
    // #unwrap_ptr_ty
    match ptrTy with
    | Ty (NativePtrTk _, [ itemTy ]) -> itemTy
    | Ty (ErrorTk _, _) -> ptrTy
    | _ -> unreachable ()

  let item, actualItemTy, ctx = inferExpr ctx (Some itemTy) item
  let ctx = unifyTy ctx loc actualItemTy itemTy
  TNodeExpr(TPtrWriteEN, [ ptr; item ], tyUnit, loc), tyUnit, ctx

let private inferMinusExpr ctx arg loc =
  let arg, argTy, ctx = inferExpr ctx None arg

  let ctx =
    ctx |> addTraitBound (IsNumberTrait argTy) loc

  TNodeExpr(TMinusEN, [ arg ], argTy, loc), argTy, ctx

let private inferPtrOfExpr ctx arg loc =
  match arg with
  | TVarExpr _ ->
    let arg, argTy, ctx = inferExpr ctx None arg
    let ty = tyInPtr argTy
    TNodeExpr(TPtrOfEN, [ arg ], ty, loc), ty, ctx

  | _ ->
    let ctx = addError ctx "Expected a variable." loc
    txAbort ctx loc

let private inferIndexExpr ctx l r loc =
  let l, lTy, ctx = inferExpr ctx (Some tyStr) l
  let r, rTy, ctx = inferExpr ctx (Some tyInt) r
  let tTy, ctx = freshMetaTy loc ctx

  let ctx =
    ctx
    |> addTraitBound (IndexTrait(lTy, rTy, tTy)) loc

  TNodeExpr(TIndexEN, [ l; r ], tTy, loc), tTy, ctx

let private inferSliceExpr ctx l r x loc =
  let l, lTy, ctx = inferExpr ctx (Some tyInt) l
  let r, rTy, ctx = inferExpr ctx (Some tyInt) r
  let x, xTy, ctx = inferExpr ctx None x

  let ctx =
    let actualTy = tyFun lTy (tyFun rTy (tyFun xTy xTy))

    let expectedTy =
      tyFun tyInt (tyFun tyInt (tyFun tyStr tyStr))

    unifyTy ctx loc actualTy expectedTy

  TNodeExpr(TSliceEN, [ l; r; x ], xTy, loc), xTy, ctx

let private inferTupleExpr (ctx: TyCtx) items loc =
  let rec go acc itemTys ctx items =
    match items with
    | [] -> List.rev acc, List.rev itemTys, ctx

    | item :: items ->
      let item, itemTy, ctx = inferExpr ctx None item
      go (item :: acc) (itemTy :: itemTys) ctx items

  let items, itemTys, ctx = go [] [] ctx items

  txTuple items loc, tyTuple itemTys, ctx

let private inferAscribeExpr ctx body ascriptionTy loc =
  let body, bodyTy, ctx = inferExpr ctx (Some ascriptionTy) body
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy

  let ctx = unifyTy ctx loc bodyTy ascriptionTy
  body, ascriptionTy, ctx

let private inferNodeExpr ctx expr : TExpr * Ty * TyCtx =
  let kind, args, loc =
    match expr with
    | TNodeExpr (kind, args, _, loc) -> kind, args, loc
    | _ -> unreachable ()

  let getTy () =
    match expr with
    | TNodeExpr (_, _, ty, _) -> ty
    | _ -> unreachable ()

  match kind, args with
  | TAppEN, [ TPrimExpr _; _ ] -> inferPrimAppExpr ctx expr
  | TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.PtrWrite, _, _); _ ], _, _); _ ] -> inferWriteExpr ctx expr
  | TAppEN, [ _; _ ] -> inferAppExpr ctx expr
  | TAppEN, _ -> unreachable ()

  | TMinusEN, [ arg ] -> inferMinusExpr ctx arg loc
  | TMinusEN, _ -> unreachable ()
  | TPtrOfEN, [ arg ] -> inferPtrOfExpr ctx arg loc
  | TPtrOfEN, _ -> unreachable ()
  | TIndexEN, [ l; r ] -> inferIndexExpr ctx l r loc
  | TIndexEN, _ -> unreachable ()
  | TSliceEN, [ l; r; x ] -> inferSliceExpr ctx l r x loc
  | TSliceEN, _ -> unreachable ()

  | TTupleEN, _ -> inferTupleExpr ctx args loc

  | TAscribeEN, [ expr ] -> inferAscribeExpr ctx expr (getTy ()) loc
  | TAscribeEN, _ -> unreachable ()

  | TSizeOfEN, [ TNodeExpr (TTyPlaceholderEN, _, ty, _) ] ->
    assert (isNoTy ty |> not)
    assert (getTy () |> tyEqual tyInt)
    expr, tyInt, ctx

  | TSizeOfEN, _ -> unreachable ()

  | TTyPlaceholderEN, _ ->
    txUnit loc, tyUnit, addError ctx "Type placeholder can appear in argument of __nativeExpr or __nativeStmt." loc

  | TAbortEN, _ -> txAbort ctx loc

  | TDiscriminantEN _, _
  | TCallNativeEN _, _
  | TPtrOffsetEN _, _
  | TPtrReadEN _, _
  | TPtrWriteEN _, _
  | TNativeFunEN _, _
  | TNativeExprEN _, _
  | TNativeStmtEN _, _
  | TNativeDeclEN _, _ -> unreachable ()

let private inferBlockExpr ctx expectOpt (stmts: TStmt list) last =
  let ctx = collectVarsAndFuns ctx stmts

  let stmts, ctx =
    (stmts, ctx)
    |> stMap (fun (stmt, ctx) -> inferStmt ctx NotRec stmt)

  let last, lastTy, ctx = inferExpr ctx expectOpt last

  TBlockExpr(stmts, last), lastTy, ctx

// -----------------------------------------------
// Statement
// -----------------------------------------------

let private inferExprStmt ctx expr =
  let expr, ty, ctx = inferExpr ctx None expr
  let ctx = unifyTy ctx (exprToLoc expr) ty tyUnit
  TExprStmt expr, ctx

let private inferLetValStmt ctx pat init loc =
  let init, initTy, ctx =
    let expectOpt = patToAscriptionTy pat
    inferExpr ctx expectOpt init

  let pat, patTy, ctx = inferIrrefutablePat ctx pat

  let ctx = unifyTy ctx loc initTy patTy

  TLetValStmt(pat, init, loc), ctx

let private inferLetFunStmt ctx mutuallyRec callee vis argPats body loc =
  // Special treatment for main function.
  let mainFunTyOpt, ctx =
    if ctx |> isMainFun callee then
      // arguments must be syntactically `_`.
      let ctx =
        match argPats with
        | [ TDiscardPat _ ] -> ctx
        | _ -> addError ctx "main function must be defined in the form of: `let main _ = ...`." loc

      // argument type should be string[]
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
    let ctx = argPats |> collectVarsInPats ctx
    inferArgs ctx provisionalResultTy argPats

  let ctx = unifyTy ctx loc calleeTy funTy

  let body, bodyTy, ctx = inferExpr ctx None body

  let ctx =
    unifyTy ctx loc bodyTy provisionalResultTy

  let ctx = ctx |> decLevel

  let ctx =
    if outerLevel = 0 then
      let ctx = attemptResolveTraitBounds ctx
      generalizeFun ctx outerLevel callee
    else
      finishLocalFun ctx callee

  let ctx =
    match mutuallyRec with
    | IsRec -> { ctx with GrayFuns = ctx.GrayFuns |> TSet.add callee }
    | _ -> ctx

  let ctx =
    { ctx with NewFuns = callee :: ctx.NewFuns }

  TLetFunStmt(callee, NotRec, vis, argPats, body, loc), ctx

let private inferExpr (ctx: TyCtx) (expectOpt: Ty option) (expr: TExpr) : TExpr * Ty * TyCtx =
  let fail () = unreachable expr

  match expr with
  | TLitExpr (lit, _) -> inferLitExpr ctx expr lit
  | TVarExpr (serial, _, loc) -> inferVarExpr ctx serial loc
  | TFunExpr (serial, _, loc) -> inferFunExpr ctx serial loc
  | TVariantExpr (serial, _, loc) -> inferVariantExpr ctx serial loc
  | TPrimExpr (prim, _, loc) -> inferPrimExpr ctx prim loc
  | TRecordExpr (baseOpt, fields, _, loc) -> inferRecordExpr ctx expectOpt baseOpt fields loc
  | TMatchExpr (cond, arms, _, loc) -> inferMatchExpr ctx expectOpt expr cond arms loc
  | TNavExpr (receiver, field, _, loc) -> inferNavExpr ctx receiver field loc
  | TNodeExpr _ -> inferNodeExpr ctx expr
  | TBlockExpr (stmts, last) -> inferBlockExpr ctx expectOpt stmts last

let private inferBlockStmt (ctx: TyCtx) mutuallyRec stmts : TStmt * TyCtx =
  let outerLevel = ctx.Level
  let parentCtx = ctx

  let ctx = collectVarsAndFuns ctx stmts

  let stmts, ctx =
    (stmts, ctx)
    |> stMap (fun (stmt, ctx) -> inferStmt ctx mutuallyRec stmt)

  // Generalize these funs again.
  // Ty scheme of these funs might try to quantify meta tys that are bound later.
  let ctx =
    stmts
    |> List.fold
         (fun (ctx: TyCtx) stmt ->
           match stmt with
           | TLetFunStmt (funSerial, _, _, _, _, _) ->
             let funDef: FunDef = ctx.Funs |> mapFind funSerial
             let (TyScheme (tyVars, funTy)) = funDef.Ty

             match tyVars with
             | [] -> ctx

             | _ ->
               // #generalizeFun
               let isOwned tySerial =
                 let highLevel () =
                   let level = getTyLevel tySerial ctx
                   level > outerLevel

                 let alreadyQuantified () =
                   tyVars |> List.exists (fun t -> t = tySerial)

                 highLevel () || alreadyQuantified ()

               let funTy = substTy ctx funTy
               let funTyScheme = tyGeneralize isOwned funTy

               let funs =
                 ctx.Funs
                 |> TMap.add funSerial { funDef with Ty = funTyScheme }

               let quantifiedTys =
                 tyVars
                 |> List.fold (fun quantifiedTys tyVar -> TSet.add tyVar quantifiedTys) ctx.QuantifiedTys

               let instantiations, grayInstantiations =
                 ctx.GrayInstantiations |> TMap.remove funSerial

               let ctx =
                 { ctx with
                     Funs = funs
                     QuantifiedTys = quantifiedTys
                     GrayInstantiations = grayInstantiations }

               let ctx =
                 instantiations
                 |> Option.defaultValue []
                 |> List.fold
                      (fun (ctx: TyCtx) (useSiteTy, loc) ->
                        let funTy, _, ctx = instantiateTyScheme ctx funTyScheme loc
                        let newCtx = unifyTy ctx loc funTy useSiteTy
                        { ctx with Logs = newCtx.Logs })
                      ctx

               ctx
           | _ -> ctx)
         ctx

  let ctx =
    { ctx with GrayFuns = parentCtx.GrayFuns }

  TBlockStmt(mutuallyRec, stmts), ctx

let private inferStmt ctx mutuallyRec stmt : TStmt * TyCtx =
  match stmt with
  | TExprStmt expr -> inferExprStmt ctx expr
  | TLetValStmt (pat, init, loc) -> inferLetValStmt ctx pat init loc
  | TLetFunStmt (oldSerial, _, vis, args, body, loc) -> inferLetFunStmt ctx mutuallyRec oldSerial vis args body loc
  | TBlockStmt (mutuallyRec, stmts) -> inferBlockStmt ctx mutuallyRec stmts

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
    TyState: TreeMap<TySerial, State> }

let private setTyState tySerial state (ctx: SynonymCycleCtx) =
  { ctx with TyState = ctx.TyState |> TMap.add tySerial state }

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
                 |> TMap.add tySerial (SynonymTyDef(ident, tyArgs, tyError loc, loc))

               let logs = (Log.TySynonymCycleError, loc) :: logs
               tys, logs

             | _ -> tys, logs
           | _ -> tys, logs)
         (tyCtx.Tys, tyCtx.Logs)

  { tyCtx with Tys = tys; Logs = logs }

// -----------------------------------------------
// Interface
// -----------------------------------------------

let infer (modules: TProgram, nameRes: NameResResult) : TProgram * TirCtx =
  let ctx = newTyCtx nameRes

  let ctx = synonymCycleCheck ctx

  let substOrDegenerate ctx ty =
    ty
    |> substOrDegenerateTy ctx
    |> expandSynonyms ctx

  let substOrDegenerateVars ctx vars =
    vars
    |> TMap.map (fun _ (varDef: VarDef) ->
      let ty = substOrDegenerate ctx varDef.Ty
      { varDef with Ty = ty })

  let substOrDegenerateStmts ctx stmts =
    stmts
    |> List.map (fun stmt -> stmtMap (substOrDegenerate ctx) stmt)

  let modules, ctx =
    let oldStaticVars = ctx.Vars

    let isStaticVar varSerial =
      oldStaticVars |> TMap.containsKey varSerial

    modules
    |> List.mapFold
         (fun (ctx: TyCtx) (m: TModule) ->
           // #map_merge
           let vars, ctx =
             m.Vars
             |> TMap.fold
                  (fun (vars, ctx: TyCtx) varSerial (varDef: VarDef) ->
                    let vars = TMap.add varSerial varDef vars
                    vars, ctx)
                  (ctx.Vars, ctx)

           let ctx = { ctx with Vars = vars }

           let stmts, ctx =
             let ctx = collectVarsAndFuns ctx m.Stmts

             m.Stmts
             |> List.mapFold (fun ctx stmt -> inferStmt ctx NotRec stmt) ctx

           let ctx = ctx |> resolveTraitBoundsAll

           let staticVars, localVars =
             ctx.Vars
             |> TMap.fold
                  (fun (staticVars, localVars) varSerial varDef ->
                    if isStaticVar varSerial then
                      let staticVars = staticVars |> TMap.add varSerial varDef

                      staticVars, localVars
                    else
                      let localVars = localVars |> TMap.add varSerial varDef

                      staticVars, localVars)
                  (emptyVars, emptyVars)

           // Resolve meta types.
           let stmts, staticVars, localVars, ctx =
             let stmts = substOrDegenerateStmts ctx stmts
             let staticVars = substOrDegenerateVars ctx staticVars
             let localVars = substOrDegenerateVars ctx localVars

             let funs =
               ctx.NewFuns
               |> List.fold
                    (fun funs funSerial ->
                      let funDef: FunDef = funs |> mapFind funSerial

                      let (TyScheme (tyVars, ty)) = funDef.Ty
                      let ty = substOrDegenerate ctx ty

                      let funDef =
                        { funDef with Ty = TyScheme(tyVars, ty) }

                      funs |> TMap.add funSerial funDef)
                    ctx.Funs

             let ctx =
               { ctx with
                   Funs = funs
                   NewFuns = []
                   MetaTys = TMap.empty compare
                   TyLevels = TMap.empty compare
                   QuantifiedTys = TMap.empty compare }

             stmts, staticVars, localVars, ctx

           let m =
             { m with
                 Vars = localVars
                 Stmts = stmts }

           let ctx = { ctx with Vars = staticVars }
           m, ctx)
         ctx

  // Expand synonyms.
  let ctx =
    let variants =
      ctx.Variants
      |> TMap.map (fun _ (variantDef: VariantDef) ->
        { variantDef with PayloadTy = expandSynonyms ctx variantDef.PayloadTy })

    let tys =
      ctx.Tys
      |> TMap.fold
           (fun acc tySerial tyDef ->
             match tyDef with
             | UnivTyDef _
             | SynonymTyDef _ -> acc

             | RecordTyDef (recordName, unimplTyArgs, fields, repr, loc) ->
               let fields =
                 fields
                 |> List.map (fun (name, ty, loc) ->
                   let ty = expandSynonyms ctx ty
                   name, ty, loc)

               acc
               |> TMap.add tySerial (RecordTyDef(recordName, unimplTyArgs, fields, repr, loc))

             | _ -> acc |> TMap.add tySerial tyDef)
           (TMap.empty compare)

    { ctx with
        Variants = variants
        Tys = tys }

  let tirCtx = toTirCtx ctx

  // Enforce.
  assert (tirCtx.StaticVars
          |> TMap.toList
          |> List.forall (fun (_, varDef: VarDef) ->
            match varDef.IsStatic with
            | IsStatic -> tyIsMonomorphic varDef.Ty
            | NotStatic -> false))

  modules, tirCtx
