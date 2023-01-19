/// Infers the type of expressions.
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
open MiloneSyntax.TirTypes

module S = Std.StdString
module StdInt = Std.StdInt

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private TyCtx =
  {
    /// Last serial number. Mainly used for meta types.
    Serial: Serial

    /// Static and non-static variables.
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    /// Type serial to type definition.
    Tys: TreeMap<TySerial, TyDef>

    MetaTys: TreeMap<TySerial, Ty>
    /// Meta types that can't be generalized.
    NoGeneralizeMetaTys: TreeSet<TySerial>
    /// Whether it's in a function.
    IsFunLocal: bool

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
    MetaTys = TMap.empty compare
    NoGeneralizeMetaTys = TSet.empty compare
    IsFunLocal = false
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

let private canGeneralize (ctx: TyCtx) metaTySerial =
  ctx.NoGeneralizeMetaTys |> TSet.contains metaTySerial |> not

let private freshTySerial (ctx: TyCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1 }

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

// -----------------------------------------------
// Extensions for Ty, Expr
// -----------------------------------------------

let private isNoTy ty =
  match ty with
  | Ty (ErrorTk _, _) -> true
  | _ -> false

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
// Unification
// -----------------------------------------------

// And meta type resolution by substitution or degeneration.

let private expandMeta (ctx: TyCtx) tySerial : Ty option = ctx.MetaTys |> TMap.tryFind tySerial

let private substTy (ctx: TyCtx) ty : Ty = tySubst (expandMeta ctx) ty

let private expandSynonyms (ctx: TyCtx) ty : Ty =
  tyExpandSynonyms (fun tySerial -> ctx.Tys |> TMap.tryFind tySerial) ty

/// Binds a type to a meta type.
///
/// As a precondition, that meta type must be free (not bound)
/// and must not occur in that type (no recursion).
let private bindMetaTy (ctx: TyCtx) tySerial otherTy : TyCtx =
  /// If no-generalize meta type is bound to a type,
  /// propagate "no-generalize" attribute to meta types in the type.
  let noGeneralizeMetaTys =
    if canGeneralize ctx tySerial |> not then
      otherTy
      |> tyCollectFreeVars
      |> List.fold
          (fun acc tySerial ->
            if canGeneralize ctx tySerial |> not then
              acc
            else
              acc |> TSet.add tySerial)
          ctx.NoGeneralizeMetaTys
    else
      ctx.NoGeneralizeMetaTys

  { ctx with
      MetaTys = ctx.MetaTys |> TMap.add tySerial otherTy
      NoGeneralizeMetaTys = noGeneralizeMetaTys }

// Note: Two types should be passed as possible so that lTy is a subtype of rTy.
//       In other words, `unify lTy rTy` should check if `let (r: rTy) = (l: lTy)` is okay.
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
  | StringTk
  | VoidPtrTk _
  | NativePtrTk _ -> true

  | _ -> false

let private tyIsPtr ty =
  let (Ty (tk, _)) = ty

  match tk with
  | VoidPtrTk _
  | NativePtrTk _
  | FunPtrTk -> true
  | _ -> false

let private addTraitBound (t: Trait) loc (ctx: TyCtx) =
  { ctx with NewTraitBounds = (t, loc) :: ctx.NewTraitBounds }

let private resolveTraitBound (ctx: TyCtx) (theTrait: Trait) loc : TyCtx =
  let ok ctx = ctx

  let error ctx =
    addLog ctx (Log.TyBoundError theTrait) loc |> addTraitBound theTrait loc

  let unify2 (lTy1, rTy1) (lTy2, rTy2) =
    let ctx = unifyTy ctx loc lTy1 rTy1
    unifyTy ctx loc lTy2 rTy2

  // Coerce to int as default.
  let defaultToInt ctx ty = unifyTy ctx loc ty tyInt

  /// integer, bool, char, or string
  let expectBasic ctx ty =
    if tyIsBasic ty then ok ctx else error ctx

  match theTrait with
  | Trait.Unary(unary, ty) ->
    let (Ty(tk, _)) = ty

    match unary with
    | UnaryTrait.Add ->
      match tk with
      | ErrorTk _
      | IntTk _
      | FloatTk _
      | CharTk
      | StringTk -> ok ctx
      | _ -> defaultToInt ctx ty

    | UnaryTrait.Equal ->
      // #trait_resolve
      let rec go memo ty =
        let (Ty(tk, tyArgs)) = ty

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
        | FunPtrTk, _ -> true, memo

        // Don't memoize structural types
        // because it doesn't cause infinite recursion
        // and unfortunately memo is discarded.
        | TupleTk, _ -> onTys memo tyArgs
        | ListTk, [ itemTy ] -> go memo itemTy

        | UnionTk(tySerial, _), _ ->
          allowRec memo (fun memo ->
            match ctx.Tys |> mapFind tySerial with
            | UnionTyDef(_, tyVars, variants, _) ->
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

    | UnaryTrait.Compare ->
      match ty with
      | Ty(TupleTk, []) -> ok ctx
      | Ty(CharTk, _) -> error ctx
      | _ -> expectBasic ctx ty

    | UnaryTrait.IntLike ->
      match tk with
      | ErrorTk _
      | IntTk _ -> ok ctx
      | _ -> defaultToInt ctx ty

    | UnaryTrait.NumberLike ->
      match tk with
      | ErrorTk _
      | IntTk _
      | FloatTk _ -> ok ctx
      | _ -> defaultToInt ctx ty

    | UnaryTrait.ToInt flavor ->
      match tk, flavor with
      | ErrorTk _, _
      | IntTk _, _
      | FloatTk _, _
      | StringTk, _
      | VoidPtrTk _, _
      | NativePtrTk _, _ -> ok ctx

      | CharTk, I8
      | CharTk, U8 -> ok ctx

      | _ -> error ctx

    | UnaryTrait.ToFloat ->
      match tk with
      | ErrorTk _
      | IntTk _
      | FloatTk _
      | StringTk -> ok ctx
      | _ -> error ctx

    | UnaryTrait.ToChar ->
      match tk with
      | ErrorTk _
      | IntTk I8
      | IntTk U8
      | CharTk
      | StringTk -> ok ctx
      | _ -> error ctx

    | UnaryTrait.ToString ->
      // #trait_resolve
      let rec go memo ty =
        let (Ty(tk, tyArgs)) = ty

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
            memo |> TSet.add ty |> action

        match tk, tyArgs with
        | _ when tyIsBasic ty -> true, memo

        | TupleTk, [] -> true, memo
        | TupleTk, _ -> onTys memo tyArgs

        | UnionTk(tySerial, _), _ ->
          allowRec memo (fun memo ->
            match ctx.Tys |> mapFind tySerial with
            | UnionTyDef(_, tyVars, variants, _) ->
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

    | UnaryTrait.PtrLike ->
      match tk with
      | ErrorTk _ -> ok ctx
      | _ when tyIsPtr ty -> ok ctx
      | _ -> error ctx

    | UnaryTrait.PtrSize ->
      match tk with
      | ErrorTk _
      | IntTk IPtr
      | IntTk UPtr
      | ObjTk
      | ListTk
      | VoidPtrTk _
      | NativePtrTk _
      | FunPtrTk -> ok ctx
      | _ -> error ctx

  | Trait.Index(lTy, rTy, tTy) ->
    match lTy with
    | Ty(ErrorTk _, _) -> ok ctx
    | Ty(StringTk, _) -> unify2 (rTy, tyInt) (tTy, tyChar)
    | _ -> error ctx

  | Trait.PtrCast(srcTy, destTy) ->
    match srcTy, destTy with
    | Ty(ErrorTk _, _), _
    | _, Ty(ErrorTk _, _) -> ok ctx

    | Ty(OwnTk, [ srcTy ]), Ty(OwnTk, [ destTy ]) when tyIsPtr srcTy && tyIsPtr destTy && not (tyEqual srcTy destTy) ->
      ok ctx

    | _ when tyIsPtr srcTy && tyIsPtr destTy && not (tyEqual srcTy destTy) -> ok ctx

    | _ -> error ctx

let private attemptResolveTraitBounds (ctx: TyCtx) : TyCtx =
  let subst (ctx: TyCtx) ty =
    ty |> substTy ctx |> typingExpandSynonyms ctx.Tys

  let logs, ctx = ctx.Logs, { ctx with Logs = [] }

  let traitAcc, (ctx: TyCtx) =
    ctx.NewTraitBounds
    |> List.fold
         (fun (traitAcc, (ctx: TyCtx)) (theTrait, loc) ->
           let theTrait = Trait.map (subst ctx) theTrait

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
             let theTrait = Trait.map (subst ctx) theTrait
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
// Generalization and instantiation
// -----------------------------------------------

let private instantiateTyScheme (ctx: TyCtx) (tyScheme: TyScheme) loc : Ty * (TySerial * Ty) list * TyCtx =
  match tyScheme with
  | TyScheme ([], ty) -> ty, [], ctx

  | TyScheme (tyVars, ty) ->
    let lastSerial, ty, assignment =
      doInstantiateTyScheme ctx.Serial tyVars ty loc

    ty, assignment, { ctx with Serial = lastSerial }

let private instantiateBoundedTyScheme (ctx: TyCtx) (tyScheme: BoundedTyScheme) loc : Ty * TyCtx =
  let (BoundedTyScheme(tyVars, ty, traits)) = tyScheme
  assert (List.isEmpty tyVars |> not)

  let lastSerial, ty, assignment = doInstantiateTyScheme ctx.Serial tyVars ty loc

  let traits =
    let substMeta = tyAssign assignment

    traits |> List.map (fun (t: Trait) -> t |> Trait.map substMeta, loc)

  // Meta types that appear in trait bounds can't be generalized for now.
  let noGeneralizeMetaTys =
    traits
    |> List.fold
         (fun acc ((t: Trait), _) ->
           // #map_merge
           t
           |> Trait.collectTys
           |> List.choose (fun ty ->
             match ty with
             | Ty(MetaTk(serial, _), _) -> Some serial
             | _ -> None)
           |> List.fold (fun acc tySerial -> TSet.add tySerial acc) acc)
         ctx.NoGeneralizeMetaTys

  ty,
  { ctx with
      Serial = lastSerial
      NoGeneralizeMetaTys = noGeneralizeMetaTys
      NewTraitBounds = List.append traits ctx.NewTraitBounds }

// #generalizeFun
let private generalizeFun (ctx: TyCtx) funSerial =
  let funDef = ctx.Funs |> mapFind funSerial

  let (TyScheme(_, funTy)) = funDef.Ty
  assert (isNoTy funTy |> not)

  let ctx =
    let funTy = substTy ctx funTy
    let funTyScheme = tyGeneralize (canGeneralize ctx) funTy

    // (let (TyScheme (tyVars, funTy)) = funTyScheme
    //  let getTyName tySerial =
    //     ctx.Tys
    //     |> TMap.tryFind tySerial
    //     |> Option.map tyDefToName

    //  __trace ("gen1 fun " + funDef.Name + "<" + (tyVars |> List.map (fun tySerial -> getTyName tySerial |> Option.defaultValue (string tySerial)) |> S.concat ", ") + "> : " + tyDisplay getTyName funTy))

    let ctx =
      { ctx with
          Funs =
            ctx.Funs
            |> TMap.add funSerial { funDef with Ty = funTyScheme } }

    ctx

  ctx

// -----------------------------------------------
// Ascription
// -----------------------------------------------

/// Resolves ascription type.
///
/// Current level is assigned to `'T`s and `_`s.
let private resolveAscriptionTy ctx ascriptionTy : Ty * TyCtx =
  let rec go (ctx: TyCtx) ty =
    match ty with
    | Ty (ErrorTk _, _) -> ty, ctx

    | Ty (InferTk loc, _) -> freshMetaTy loc ctx

    | Ty (_, []) -> ty, ctx

    | Ty (tk, tys) ->
      let tys, ctx = tys |> List.mapFold go ctx
      Ty(tk, tys), ctx

  go ctx ascriptionTy

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

/// Tries to extract ascription type from an expression.
let private exprToAscriptionTy (expr: TExpr) : Ty option =
  match expr with
  | TLitExpr(lit, _) -> Some(litToTy lit)
  | TNodeExpr(TAscribeEN, _, ty, _) -> Some ty

  | TVarExpr _
  | TFunExpr _
  | TVariantExpr _
  | TPrimExpr _
  | TRecordExpr _
  | TNavExpr(_, _, _, _)
  | TNodeExpr _ -> None

  | TMatchExpr(_, arms, _, _) ->
    arms
    |> List.map (fun (_, _, arm) -> arm)
    |> List.tryPick exprToAscriptionTy

  | TBlockExpr(_, last) -> exprToAscriptionTy last

// -----------------------------------------------
// ...
// -----------------------------------------------

// Fill Ty fields of definitions for forward reference.

/// Sets provisional type information in variable definitions of static variables.
/// This allows forward reference of static variables without breaking type inference.
let private initializeVarTy ctx pat =
  patFoldVars
    (fun (ctx: TyCtx) (varSerial, loc) ->
      let varDef = ctx.Vars |> mapFind varSerial

      if isNoTy varDef.Ty then
        let metaTy, ctx = freshMetaTy loc ctx
        let varDef = { varDef with Ty = metaTy }
        { ctx with Vars = ctx.Vars |> TMap.add varSerial varDef }
      else
        ctx)
    ctx
    pat

/// Sets initialized type information in function definition.
let private initializeFunTy (ctx: TyCtx) funSerial args body =
  let argTys, ctx =
    args
    |> List.mapFold (fun ctx pat ->
      match patToAscriptionTy pat with
      | Some ty -> resolveAscriptionTy ctx ty
      | None -> freshMetaTyForPat pat ctx
    ) ctx

  let resultTy, ctx =
    match exprToAscriptionTy body with
    | Some ty -> resolveAscriptionTy ctx ty
    | None -> freshMetaTyForExpr body ctx

  let stubFunTy =
    argTys
    |> List.rev
    |> List.fold (fun funTy argTy -> tyFun argTy funTy) resultTy

  let funDef = ctx.Funs |> mapFind funSerial

  // Ensure pre-initialized function definition doesn't have meaningful type information.
  let _ =
    let (TyScheme (tyVars, uninitTy)) = funDef.Ty
    assert (List.isEmpty tyVars)
    assert (isNoTy uninitTy)

  let tyVars =
    if not ctx.IsFunLocal then
      // Universal types are only definite type parameters at this time.
      let rec univRec acc ty =
        match ty with
        | Ty (UnivTk (tySerial, _, _), _) -> tySerial :: acc
        | Ty (_, tyArgs) -> List.fold univRec acc tyArgs

      univRec [] stubFunTy
      |> listUnique compare
    else
      []

  let funDef = { funDef with Ty = TyScheme(tyVars, stubFunTy) }

  { ctx with Funs = ctx.Funs |> TMap.add funSerial funDef }

/// Initializes type information in definitions.
/// Used for non-local declarations, i.e. static variables and non-local functions.
let private initializeNonlocalVarsAndFuns ctx stmts =
  stmts
  |> List.fold
       (fun ctx stmt ->
         match stmt with
         | TLetValStmt (pat, _, _) -> initializeVarTy ctx pat
         | TLetFunStmt (funSerial, _, _, args, body, _) -> initializeFunTy ctx funSerial args body
         | _ -> ctx)
       ctx

/// Initializes type information in definitions.
/// Used for local functions.
/// Note: Local variables are initialized when its pattern is processed at first time.
let private initializeLocalFuns ctx stmts =
  stmts
  |> List.fold
       (fun ctx stmt ->
         match stmt with
         | TLetFunStmt (funSerial, _, _, args, body, _) -> initializeFunTy ctx funSerial args body
         | _ -> ctx)
       ctx

/// Initializes type information in definitions.
/// Used for parameter patterns in function declarations.
let private initializeParams ctx pats = pats |> List.fold initializeVarTy ctx

// -----------------------------------------------
// Literal validation
// -----------------------------------------------

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
// Primitives
// -----------------------------------------------

let private primNotTy = tyFun tyBool tyBool

let private primBitNotScheme =
  let ty = tyMeta 1 noLoc
  BoundedTyScheme([ 1 ], tyFun ty ty, [ Trait.newIntLike ty ])

let private primAddScheme =
  let meta id = tyMeta id noLoc
  let addTy = meta 1
  BoundedTyScheme([ 1 ], tyFun addTy (tyFun addTy addTy), [ Trait.newAdd addTy ])

let private primSubtractEtcScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun ty ty), [ Trait.newNumberLike ty ])

let private primBitAndEtcScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun ty ty), [ Trait.newIntLike ty ])

let private primShiftScheme =
  let meta id = tyMeta id noLoc
  let ty = meta 1
  BoundedTyScheme([ 1 ], tyFun ty (tyFun tyInt ty), [ Trait.newIntLike ty ])

let private primEqualScheme =
  let meta id = tyMeta id noLoc
  let argTy = meta 1
  BoundedTyScheme([ 1 ], tyFun argTy (tyFun argTy tyBool), [ Trait.newEqual argTy ])

let private primLessScheme =
  let meta id = tyMeta id noLoc
  let compareTy = meta 1
  BoundedTyScheme([ 1 ], tyFun compareTy (tyFun compareTy tyBool), [ Trait.newCompare compareTy ])

let private primCompareScheme =
  let meta id = tyMeta id noLoc
  let compareTy = meta 1
  BoundedTyScheme([ 1 ], tyFun compareTy (tyFun compareTy tyInt), [ Trait.newCompare compareTy ])

let private primIntScheme flavor =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let resultTy = Ty(IntTk flavor, [])
  BoundedTyScheme([ 1 ], tyFun srcTy resultTy, [ Trait.newToInt flavor srcTy ])

let private primFloatScheme flavor =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let resultTy = Ty(FloatTk flavor, [])
  BoundedTyScheme([ 1 ], tyFun srcTy resultTy, [ Trait.newToFloat srcTy ])

let private primToCharScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  BoundedTyScheme([ 1 ], tyFun srcTy tyChar, [ Trait.newToChar srcTy ])

let private primToStringScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  BoundedTyScheme([ 1 ], tyFun srcTy tyString, [ Trait.newToString srcTy ])

let private primBoxScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  TyScheme([ 1 ], tyFun itemTy tyObj)

let private primUnboxScheme =
  let meta id = tyMeta id noLoc
  let resultTy = meta 1
  TyScheme([ 1 ], tyFun tyObj resultTy)

let private primStringLengthTy = tyFun tyString tyInt

let private primNilScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  TyScheme([ 1 ], tyList itemTy)

let private primConsScheme =
  let meta id = tyMeta id noLoc
  let itemTy = meta 1
  let listTy = tyList itemTy
  TyScheme([ 1 ], tyFun itemTy (tyFun listTy listTy))

let private primAssertTy = tyFun tyBool tyUnit

let private primOwnAcquireTy =
  let itemTy = tyMeta 1 noLoc
  TyScheme([ 1 ], tyFun itemTy (tyOwn itemTy))

let private primOwnReleaseTy =
  let itemTy = tyMeta 1 noLoc
  TyScheme([ 1 ], tyFun (tyOwn itemTy) itemTy)

let private primNullPtrScheme =
  let ptrTy = tyMeta 1 noLoc
  BoundedTyScheme([ 1 ], ptrTy, [ Trait.newPtrLike ptrTy ])

let private primPtrCastScheme =
  let srcTy = tyMeta 1 noLoc
  let destTy = tyMeta 2 noLoc
  BoundedTyScheme([ 1; 2 ], tyFun srcTy destTy, [ Trait.newPtrCast srcTy destTy ])

let private primPtrInvalidScheme =
  let ptrTy = tyMeta 1 noLoc

  BoundedTyScheme([ 1 ], tyFun tyUNativeInt ptrTy, [ Trait.newPtrLike ptrTy ])

let private primPtrDistanceScheme =
  let ptrTy = tyMeta 1 noLoc
  BoundedTyScheme([ 1 ], tyFun ptrTy (tyFun ptrTy tyNativeInt), [ Trait.newPtrLike ptrTy ])

let private primNativeCastScheme =
  let meta id = tyMeta id noLoc
  let srcTy = meta 1
  let destTy = meta 2

  BoundedTyScheme(
    [ 1; 2 ],
    tyFun srcTy destTy,
    [ Trait.newPtrSize srcTy
      Trait.newPtrSize destTy ]
  )

// -----------------------------------------------
// Features for native interoperability
// -----------------------------------------------

let private castFunAsNativeFun funSerial loc (ctx: TyCtx) : Ty * TyCtx =
  let funDef = ctx.Funs |> mapFind funSerial

  let ctx =
    if funDef.Nonlocal then
      addError ctx "Pointer to a local function is unavailable since it might capture local variables." loc
    else
      ctx

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

// -----------------------------------------------
// Type Decomposition
// -----------------------------------------------

let private expectFunTy ctx ty loc =
  match ty with
  | Ty(FunTk, [ sTy; tTy ]) -> sTy, tTy, ctx

  | _ ->
    let sTy, ctx = freshMetaTy loc ctx
    let tTy, ctx = freshMetaTy loc ctx
    let ctx = unifyTy ctx loc ty (tyFun sTy tTy)
    sTy, tTy, ctx

let private expectListTy ctx targetTy loc =
  match targetTy with
  | Ty(ListTk, [ itemTy ]) -> targetTy, itemTy, ctx

  | _ ->
    let itemTy, ctx = freshMetaTy loc ctx
    let listTy = tyList itemTy
    listTy, itemTy, unifyTy ctx loc targetTy listTy

/// Expects a type to be tuple and returns item types.
let private expectTupleTy (arity: int) ctx targetTy loc =
  match targetTy with
  | Ty(TupleTk, itemTys) when List.length itemTys = arity -> itemTys, ctx

  | _ when arity = 0 ->
    let ctx = unifyTy ctx loc targetTy tyUnit
    [], ctx

  | _ ->
    let itemTys, ctx =
      let rec loop acc ctx i =
        if i < arity then
          let metaTy, ctx = freshMetaTy loc ctx
          loop (metaTy :: acc) ctx (i + 1)
        else
          acc, ctx

      loop [] ctx 0

    let ctx = unifyTy ctx loc targetTy (tyTuple itemTys)
    itemTys, ctx

// -----------------------------------------------
// Helpers for patterns
// -----------------------------------------------

/// Unifies the target type to the type of the variable
/// if the variable type is already initialized.
/// Otherwise, the target type is just assigned to the local variable definition.
let private unifyOrAssignVarTy (ctx: TyCtx) varSerial ty loc =
  let varDef = ctx.Vars |> mapFind varSerial

  if isNoTy varDef.Ty then
    let varDef = { varDef with Ty = ty }
    { ctx with Vars = ctx.Vars |> TMap.add varSerial varDef }
  else
    unifyTy ctx loc ty varDef.Ty

// payloadTy, unionTy, variantTy
let private instantiateVariant (ctx: TyCtx) variantSerial loc : Ty * Ty * Ty * TyCtx =
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

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private inferLitPat ctx pat lit =
  let ctx = validateLit ctx lit (patToLoc pat)
  pat, litToTy lit, ctx

let private checkNilPat ctx loc targetTy =
  let listTy, _, ctx = expectListTy ctx targetTy loc
  TNodePat(TNilPN, [], listTy, loc), ctx

let private checkConsPat ctx headPat tailPat loc targetTy =
  let listTy, itemTy, ctx = expectListTy ctx targetTy loc
  let headPat, ctx = checkPat ctx headPat itemTy
  let tailPat, ctx = checkPat ctx tailPat listTy
  TNodePat(TConsPN, [ headPat; tailPat ], listTy, loc), ctx

let private inferVariantPat (ctx: TyCtx) variantSerial loc =
  let _, unionTy, _, ctx =
    instantiateVariant ctx variantSerial loc

  let ctx =
    let variantDef = ctx.Variants |> mapFind variantSerial

    if variantDef.HasPayload then
      addLog ctx Log.MissingPayloadPat loc
    else
      ctx

  TVariantPat(variantSerial, unionTy, loc), unionTy, ctx

let private checkVariantAppPat (ctx: TyCtx) variantSerial payloadPat loc targetTy =
  let payloadTy, unionTy, _, ctx =
    instantiateVariant ctx variantSerial loc

  let ctx = unifyTy ctx loc targetTy unionTy
  let payloadPat, ctx = checkPat ctx payloadPat payloadTy

  TNodePat(TVariantAppPN variantSerial, [ payloadPat ], unionTy, loc), ctx

let private checkUnitPat ctx loc targetTy =
  let ctx = unifyTy ctx loc targetTy tyUnit
  TNodePat(TTuplePN, [], tyUnit, loc), ctx

let private checkTuplePat ctx itemPats loc targetTy =
  let arity = List.length itemPats
  let itemTys, ctx = expectTupleTy arity ctx targetTy loc

  let entries =
    match listTryZip itemPats itemTys with
    | entries, [], [] -> entries
    | _ -> unreachable ()

  let itemPats, ctx =
    entries
    |> List.mapFold (fun ctx (itemPat, itemTy) -> checkPat ctx itemPat itemTy) ctx

  TNodePat(TTuplePN, itemPats, targetTy, loc), ctx

let private inferAscribePat ctx body ascriptionTy =
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy
  let body, ctx = checkPat ctx body ascriptionTy
  body, ascriptionTy, ctx

let private inferAbortPat ctx loc =
  let targetTy = tyError loc
  tpAbort targetTy loc, targetTy, ctx

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
  | TAbortPN, _ -> inferAbortPat ctx loc

  | TAscribePN, [ bodyPat ] -> inferAscribePat ctx bodyPat (getTy ())
  | TAscribePN, _ -> unreachable ()

  | TNilPN, _
  | TConsPN, _
  | TTuplePN, _
  | TVariantAppPN _, _ ->
    // Forward to check.
    let ty, ctx = freshMetaTyForPat pat ctx
    let pat, ctx = checkPat ctx pat ty
    pat, ty, ctx

  | TNavPN _, _ -> unreachable () // Resolved in NameRes.

let private inferPat ctx pat : TPat * Ty * TyCtx =
  match pat with
  | TLitPat (lit, _) -> inferLitPat ctx pat lit
  | TVariantPat (variantSerial, _, loc) -> inferVariantPat ctx variantSerial loc
  | TNodePat _ -> inferNodePat ctx pat

  | TDiscardPat _
  | TVarPat _
  | TAsPat _
  | TOrPat _ ->
    // Forward to check.
    let ty, ctx = ctx |> freshMetaTyForPat pat
    let pat, ctx = checkPat ctx pat ty
    pat, ty, ctx

/// Checks a pattern type to be equal to the specified type.
let private checkPat (ctx: TyCtx) (pat: TPat) (targetTy: Ty) : TPat * TyCtx =
  match pat with
  | TDiscardPat (_, loc) -> TDiscardPat (targetTy, loc), ctx

  | TVarPat (_, varSerial, _, loc) ->
    let ctx = unifyOrAssignVarTy ctx varSerial targetTy loc
    TVarPat(PrivateVis, varSerial, targetTy, loc), ctx

  | TNodePat (kind, argPats, _, loc) ->
    match kind, argPats with
    | TNilPN, _ -> checkNilPat ctx loc targetTy

    | TConsPN, [ hPat; tPat ] -> checkConsPat ctx hPat tPat loc targetTy
    | TConsPN, _ -> unreachable ()

    | TTuplePN, [] -> checkUnitPat ctx loc targetTy
    | TTuplePN, _ -> checkTuplePat ctx argPats loc targetTy

    | TVariantAppPN variantSerial, [ payloadPat ] -> checkVariantAppPat ctx variantSerial payloadPat loc targetTy
    | TVariantAppPN _, _ -> unreachable ()

    | _ ->
      // Forward to inference.
      let pat, inferredTy, ctx = inferPat ctx pat
      let ctx = unifyTy ctx (patToLoc pat) targetTy inferredTy
      pat, ctx

  | TAsPat (bodyPat, varSerial, loc) ->
    let ctx = unifyOrAssignVarTy ctx varSerial targetTy loc
    let bodyPat, ctx = checkPat ctx bodyPat targetTy
    TAsPat(bodyPat, varSerial, loc), ctx

  | TOrPat (lPat, rPat, loc) ->
    let lPat, ctx = checkPat ctx lPat targetTy
    let rPat, ctx = checkPat ctx rPat targetTy
    TOrPat(lPat, rPat, loc), ctx

  | TLitPat _
  | TVariantPat _ ->
    // Forward to inference.
    let pat, inferredTy, ctx = inferPat ctx pat
    let ctx = unifyTy ctx (patToLoc pat) targetTy inferredTy
    pat, ctx

let private checkRefutablePat ctx pat targetTy =
  let targetTy = substTy ctx targetTy
  checkPat ctx pat targetTy

let private inferIrrefutablePat ctx pat targetTyOpt : TPat * Ty * TyCtx =
  let isNewtypeVariant (ctx: TyCtx) variantSerial =
    ((ctx.Variants |> mapFind variantSerial): VariantDef).IsNewtype

  let pat, ty, ctx =
    match targetTyOpt with
    | Some ty ->
      let ty = substTy ctx ty
      let pat, ctx = checkPat ctx pat ty
      pat, ty, ctx

    | None -> inferPat ctx pat

  if pat |> patIsClearlyExhaustive (isNewtypeVariant ctx) |> not then
    let loc = patToLoc pat

    let ctx = addLog ctx Log.IrrefutablePatNonExhaustiveError loc

    let errorTy = tyError loc
    tpAbort errorTy loc, errorTy, ctx
  else
    pat, ty, ctx

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private inferLitExpr ctx expr lit =
  let ctx = validateLit ctx lit (exprToLoc expr)
  expr, litToTy lit, ctx

let private inferVarExpr (ctx: TyCtx) varSerial loc =
  let ty = (ctx.Vars |> mapFind varSerial).Ty
  assert (isNoTy ty |> not)

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
    instantiateVariant ctx variantSerial loc

  TVariantExpr(variantSerial, ty, loc), ty, ctx

let private inferPrimExpr ctx prim loc =
  let onMono ty = TPrimExpr(prim, ty, loc), ty, ctx

  let onUnbounded scheme =
    let primTy, _, ctx = instantiateTyScheme ctx scheme loc
    TPrimExpr(prim, primTy, loc), primTy, ctx

  let onBounded scheme =
    let primTy, ctx =
      instantiateBoundedTyScheme ctx scheme loc

    TPrimExpr(prim, primTy, loc), primTy, ctx

  let bad ctx err =
    let ctx = addLog ctx err loc
    txAbort ctx loc

  match prim with
  | TPrim.Not -> onMono primNotTy
  | TPrim.BitNot -> onBounded primBitNotScheme
  | TPrim.Add -> onBounded primAddScheme

  | TPrim.Subtract
  | TPrim.Multiply
  | TPrim.Divide
  | TPrim.Modulo -> onBounded primSubtractEtcScheme

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
  | TPrim.ToChar -> onBounded primToCharScheme
  | TPrim.ToString -> onBounded primToStringScheme
  | TPrim.Box -> onUnbounded primBoxScheme
  | TPrim.Unbox -> onUnbounded primUnboxScheme

  | TPrim.StringLength -> onMono primStringLengthTy

  | TPrim.Nil -> onUnbounded primNilScheme
  | TPrim.Cons -> onUnbounded primConsScheme

  | TPrim.Discriminant _ -> bad ctx Log.UseOfDiscriminant

  | TPrim.Assert -> onMono primAssertTy
  | TPrim.Printfn -> bad ctx Log.UseOfPrintfn

  | TPrim.OwnAcquire -> onUnbounded primOwnAcquireTy
  | TPrim.OwnRelease -> onUnbounded primOwnReleaseTy

  | TPrim.PtrCast -> onBounded primPtrCastScheme
  | TPrim.PtrInvalid -> onBounded primPtrInvalidScheme
  | TPrim.PtrDistance -> onBounded primPtrDistanceScheme

  | TPrim.NativeCast -> onBounded primNativeCastScheme
  | TPrim.NativeFun -> bad ctx Log.UseOfNativeFun
  | TPrim.NativeExpr -> bad ctx Log.UseOfNativeExpr
  | TPrim.NativeStmt -> bad ctx Log.UseOfNativeStmt
  | TPrim.NativeDecl -> bad ctx Log.UseOfNativeDecl

  | TPrim.NullPtr -> onBounded primNullPtrScheme

  | TPrim.PtrSelect
  | TPrim.PtrRead
  | TPrim.PtrWrite
  | TPrim.PtrAsIn
  | TPrim.PtrAsNative
  | TPrim.FunPtrInvoke -> bad ctx Log.PrimRequireParam

let private checkRecordExpr ctx expr targetTy =
  // Record type must be determined by target type or base expression type.

  let baseOpt, fields, loc =
    match expr with
    | TRecordExpr (baseOpt, fields, _, loc) -> baseOpt, fields, loc
    | _ -> unreachable ()

  let baseOpt, baseTyOpt, ctx =
    match baseOpt with
    | None -> None, None, ctx

    | Some baseExpr ->
      let baseExpr, ctx = checkExpr ctx baseExpr targetTy
      Some baseExpr, Some targetTy, ctx

  let recordTyInfoOpt =
    let asRecordTy ty =
      let ty = substTy ctx ty

      match ty with
      | Ty (RecordTk (tySerial, _), _) ->
        match ctx.Tys |> mapFind tySerial with
        | RecordTyDef (name, tyVars, fieldDefs, _, _) -> Some(ty, name, tyVars, fieldDefs)
        | _ -> None

      | _ -> None

    match baseTyOpt |> Option.bind asRecordTy with
    | (Some _) as it -> it
    | _ -> targetTy |> asRecordTy

  match recordTyInfoOpt with
  | None ->
    let ctx = addLog ctx Log.RecordTypeNotInferred loc
    let expr, _, ctx = txAbort ctx loc
    expr, ctx

  | Some (recordTy, recordName, tyVars, fieldDefs) ->
    let addRedundantErr fieldName loc ctx =
      addLog ctx (Log.RedundantFieldError(recordName, fieldName)) loc

    let addIncompleteErr fieldNames ctx =
      addLog ctx (Log.MissingFieldsError(recordName, fieldNames)) loc

    // #tyAssign
    let assignment =
      let (Ty (_, tyArgs)) = recordTy

      match listTryZip tyVars tyArgs with
      | it, [], [] -> it
      | _ -> unreachable () // NameRes verified arity.

    // Infer field initializers and whether each of them is member of the record type.
    // Whenever a field appears, remove it from the set of fields
    // so that second occurrence of it is marked as redundant.
    let fields, (fieldDefs, ctx) =
      let fieldDefs =
        fieldDefs
        |> List.map (fun (name, ty, _) -> name, tyAssign assignment ty)
        |> TMap.ofList compare

      fields
      |> List.mapFold
           (fun (fieldDefs, ctx) field ->
             let name, init, loc = field

             match fieldDefs |> TMap.remove name with
             | None, _ ->
               let ctx = ctx |> addRedundantErr name loc
               let init, _, ctx = inferExpr ctx init
               (name, init, loc), (fieldDefs, ctx)

             | Some defTy, fieldDefs ->
               let init, ctx = checkExpr ctx init defTy
               (name, init, loc), (fieldDefs, ctx))
           (fieldDefs, ctx)

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

    TRecordExpr(baseOpt, fields, recordTy, loc), ctx

// match 'a with ( | 'a -> 'b )*
let private checkMatchExpr ctx expr targetTy =
  let cond, arms, loc =
    match expr with
    | TMatchExpr (cond, arms, _, loc) -> cond, arms, loc
    | _ -> unreachable ()

  let cond, condTy, ctx = inferExpr ctx cond

  let ctx =
    arms
    |> List.fold (fun ctx (pat, _, _) -> initializeVarTy ctx pat) ctx

  let arms, ctx =
    arms
    |> List.mapFold
         (fun ctx (pat, guard, body) ->
           let pat, ctx = checkRefutablePat ctx pat condTy
           let guard, ctx = checkExpr ctx guard tyBool

           let body, ctx =
             // FIXME: if type of body is never, it shouldn't be unified with targetTy. test never_ty is failing due to this
             let body, ctx = checkExpr ctx body targetTy

             match substTy ctx targetTy with
             | Ty(NeverTk, _) ->
               TNodeExpr(TCatchNeverEN, [ body ], targetTy, exprToLoc body), ctx

             | _ -> body, ctx

           (pat, guard, body), ctx)
         ctx

  TMatchExpr(cond, arms, targetTy, loc), ctx

let private inferNavExpr ctx l (r: Ident, rLoc) loc =
  let fail log ctx =
    let ctx =
      addLog ctx log loc

    txAbort ctx loc

  let l, lTy, ctx = inferExpr ctx l
  let lTy = substTy ctx lTy

  match lTy, r with
  | Ty (StringTk, []), "Length" ->
    let funExpr =
      TPrimExpr(TPrim.StringLength, tyFun tyString tyInt, loc)

    txApp funExpr l tyInt loc, tyInt, ctx

  | Ty (RecordTk (tySerial, _), tyArgs), _ ->
    let fieldTyOpt =
      match ctx.Tys |> mapFind tySerial with
      | RecordTyDef (_, tyVars, fieldDefs, _, _) ->
        match fieldDefs
              |> List.tryFind (fun (theName, _, _) -> theName = r)
          with
        | Some (_, fieldTy, _) ->
          // #tyAssign
          let fieldTy =
            match listTryZip tyVars tyArgs with
            | it, [], [] -> tyAssign it fieldTy
            | _ -> unreachable () // NameRes verified arity.

          Some fieldTy

        | None -> None
      | _ -> None

    match fieldTyOpt with
    | Some fieldTy -> TNavExpr(l, (r, rLoc), fieldTy, loc), fieldTy, ctx
    | None -> fail (Log.RecordFieldNotFound(r, lTy)) ctx

  | _ -> fail (Log.FieldNotFound r) ctx

let private inferUntypedExprs ctx exprs =
  exprs
  |> List.mapFold
       (fun ctx expr ->
         let expr, _, ctx =
           match expr with
           | TNodeExpr (TTyPlaceholderEN, [], ty, loc) ->
             let ty, ctx = resolveAscriptionTy ctx ty
             TNodeExpr(TTyPlaceholderEN, [], ty, loc), ty, ctx

           | _ -> inferExpr ctx expr

         expr, ctx)
       ctx

let private inferAppExpr ctx itself =
  let callee, arg, loc =
    match itself with
    | TNodeExpr(TAppEN, [ callee; arg ], _, loc) -> callee, arg, loc
    | _ -> unreachable ()

  let callee, calleeTy, ctx = inferExpr ctx callee

  let calleeTy, neverReturning, ctx =
    match calleeTy with
    | Ty(FunTk, [ sTy; Ty(NeverTk, _) ]) ->
      let metaTy, ctx = freshMetaTyForExpr itself ctx
      tyFun sTy metaTy, true, ctx

    | _ -> calleeTy, false, ctx

  let argTy, targetTy, ctx = expectFunTy ctx calleeTy loc
  let arg, ctx = checkExpr ctx arg argTy
  let appExpr = txApp callee arg targetTy loc

  if neverReturning then
    TNodeExpr(TCatchNeverEN, [ appExpr ], targetTy, loc), targetTy, ctx
  else
    appExpr, targetTy, ctx

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
        let index, ctx = checkExpr ctx index tyInt
        PtrProjectionOk(TNodeExpr(TPtrOffsetEN, [ ptr; index ], ptrTy, loc), ptrTy, ctx)

      | err -> err

    | _ ->
      let expr, ty, ctx = inferExpr ctx expr
      let ty = substTy ctx ty

      match ty with
      | Ty (NativePtrTk mode, _) ->
        match mode, kind with
        | RefMode.ReadOnly, PtrOperationKind.Write ->
          PtrProjectionError("Expected nativeptr but was InPtr.", exprToLoc expr, ctx)
        | RefMode.WriteOnly, PtrOperationKind.Read ->
          PtrProjectionError("Expected nativeptr but was OutPtr.", exprToLoc expr, ctx)
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
  | TPrim.Printfn, TLitExpr (StringLit format, _) ->
    let funTy, targetTy =
      match analyzeFormat format with
      | (Ty (FunTk, [ _; targetTy ])) as funTy -> funTy, targetTy
      | _ -> unreachable ()

    txApp (TPrimExpr(TPrim.Printfn, funTy, loc)) arg targetTy loc, targetTy, ctx

  | TPrim.PtrAsIn, _ ->
    let arg, argTy, ctx = inferExpr ctx arg
    let argTy = substTy ctx argTy

    let ok resultTy =
      txApp (TPrimExpr(TPrim.NativeCast, tyFun argTy resultTy, loc)) arg resultTy loc, resultTy, ctx

    match argTy with
    | Ty (VoidPtrTk IsMut, _) -> ok tyVoidInPtr
    | Ty (NativePtrTk RefMode.ReadWrite, [ itemTy ]) -> ok (tyInPtr itemTy)
    | Ty (NativePtrTk RefMode.WriteOnly, [ itemTy ]) -> ok (tyInPtr itemTy)
    | Ty (ErrorTk _, _) -> arg, argTy, ctx
    | _ -> errorExpr ctx "Expected nativeptr, OutPtr or voidptr type." loc

  | TPrim.PtrAsNative, _ ->
    let arg, argTy, ctx = inferExpr ctx arg
    let argTy = substTy ctx argTy

    let ok resultTy =
      txApp (TPrimExpr(TPrim.NativeCast, tyFun argTy resultTy, loc)) arg resultTy loc, resultTy, ctx

    match argTy with
    | Ty (VoidPtrTk IsConst, _) -> ok tyVoidPtr
    | Ty (NativePtrTk RefMode.ReadOnly, [ itemTy ]) -> ok (tyNativePtr itemTy)
    | Ty (NativePtrTk RefMode.WriteOnly, [ itemTy ]) -> ok (tyNativePtr itemTy)
    | Ty (ErrorTk _, _) -> arg, argTy, ctx
    | _ -> errorExpr ctx "Expected InPtr, VoidInPtr or OutPtr type." loc

  | TPrim.PtrSelect, _ -> inferExprAsPtrProjection ctx PtrOperationKind.Select arg

  | TPrim.PtrRead, _ ->
    let expr, ptrTy, ctx =
      inferExprAsPtrProjection ctx PtrOperationKind.Read arg

    let ptrTy = substTy ctx ptrTy

    let itemTy =
      // #unwrap_ptr_ty
      match ptrTy with
      | Ty (NativePtrTk _, [ item ]) -> item
      | Ty (ErrorTk _, _) -> ptrTy
      | _ -> unreachable ()

    TNodeExpr(TPtrReadEN, [ expr ], itemTy, loc), itemTy, ctx

  // __nativeFun "funName"
  | TPrim.NativeFun, TLitExpr (StringLit funName, _) ->
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TCallNativeEN funName, [], targetTy, loc), targetTy, ctx

  // __nativeFun ("funName", arg1, arg2, ...)
  | TPrim.NativeFun, TNodeExpr (TTupleEN, TLitExpr (StringLit funName, _) :: args, _, _) ->
    // Type of native function is unchecked. Type ascriptions must be written correctly.
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    let args, ctx = inferUntypedExprs ctx args

    TNodeExpr(TCallNativeEN funName, args, targetTy, loc), targetTy, ctx

  // __nativeExpr "code"
  | TPrim.NativeExpr, TLitExpr (StringLit code, _) ->
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TNativeExprEN code, [], targetTy, loc), targetTy, ctx

  // __nativeExpr ("code", args...)
  | TPrim.NativeExpr, TNodeExpr (TTupleEN, TLitExpr (StringLit code, _) :: args, _, _) ->
    let args, ctx = inferUntypedExprs ctx args
    let targetTy, ctx = ctx |> freshMetaTyForExpr itself
    TNodeExpr(TNativeExprEN code, args, targetTy, loc), targetTy, ctx

  // __nativeStmt "code"
  | TPrim.NativeStmt, TLitExpr (StringLit code, _) -> TNodeExpr(TNativeStmtEN code, [], tyUnit, loc), tyUnit, ctx

  // __nativeStmt ("code", args...)
  | TPrim.NativeStmt, TNodeExpr (TTupleEN, TLitExpr (StringLit code, _) :: args, _, _) ->
    let args, ctx = inferUntypedExprs ctx args
    TNodeExpr(TNativeStmtEN code, args, tyUnit, loc), tyUnit, ctx

  // __nativeDecl "code"
  | TPrim.NativeDecl, TLitExpr (StringLit code, _) -> TNodeExpr(TNativeDeclEN code, [], tyUnit, loc), tyUnit, ctx

  // __nativeDecl ("code", args...)
  | TPrim.NativeDecl, TNodeExpr (TTupleEN, TLitExpr (StringLit code, _) :: args, _, _) ->
    // Infer arguments. Arguments are restricted so that statements don't emit on top-level.
    let args, ctx =
      args
      |> List.mapFold
           (fun ctx arg ->
             let arg, _, ctx =
               match arg with
               | TLitExpr _
               | TVarExpr _ -> inferExpr ctx arg

               | TNodeExpr (TPtrOfEN, [ TFunExpr _ ], _, _) -> inferExpr ctx arg

               | TNodeExpr (TTyPlaceholderEN, [], ty, loc) ->
                 let ty, ctx = resolveAscriptionTy ctx ty
                 TNodeExpr(TTyPlaceholderEN, [], ty, loc), ty, ctx

               | _ -> errorExpr ctx "Expected a literal, a name or (__type: T)." (exprToLoc arg)

             arg, ctx)
           ctx

    TNodeExpr(TNativeDeclEN code, args, tyUnit, loc), tyUnit, ctx

  | _ -> inferAppExpr ctx itself

let private inferWriteExpr ctx expr : TExpr * Ty * TyCtx =
  let ptr, item, loc =
    match expr with
    | TNodeExpr (TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.PtrWrite, _, loc); ptr ], _, _); item ], _, _) ->
      ptr, item, loc
    | _ -> unreachable ()

  let ptr, ptrTy, ctx =
    inferExprAsPtrProjection ctx PtrOperationKind.Write ptr

  let ptrTy = substTy ctx ptrTy

  let itemTy =
    // #unwrap_ptr_ty
    match ptrTy with
    | Ty (NativePtrTk _, [ itemTy ]) -> itemTy
    | Ty (ErrorTk _, _) -> ptrTy
    | _ -> unreachable ()

  let item, ctx = checkExpr ctx item itemTy
  TNodeExpr(TPtrWriteEN, [ ptr; item ], tyUnit, loc), tyUnit, ctx

let private inferFunPtrInvokeExpr ctx expr : TExpr * Ty * TyCtx =
  let callee, arg, loc =
    match expr with
    | TNodeExpr (TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.FunPtrInvoke, _, loc); callee ], _, _); arg ], _, _) ->
      callee, arg, loc
    | _ -> unreachable ()

  let callee, calleeTy, ctx = inferExpr ctx callee

  let argTys, resultTy =
    match substTy ctx calleeTy with
    | Ty (FunPtrTk, tyArgs) ->
      match splitLast tyArgs with
      | Some (argTys, resultTy) -> argTys, resultTy
      | None -> unreachable ()
    | _ -> unreachable ()

  let argTy =
    match argTys with
    | [ ty ] -> ty
    | [] -> tyUnit
    | _ -> tyTuple argTys

  let arg, ctx = checkExpr ctx arg argTy
  TNodeExpr(TFunPtrInvokeEN, [ callee; arg ], resultTy, loc), resultTy, ctx

let private inferMinusExpr ctx arg loc =
  let arg, argTy, ctx = inferExpr ctx arg

  let ctx =
    ctx |> addTraitBound (Trait.newNumberLike argTy) loc

  TNodeExpr(TMinusEN, [ arg ], argTy, loc), argTy, ctx

let private inferPtrOfExpr ctx arg loc =
  match arg with
  | TVarExpr _ ->
    let arg, argTy, ctx = inferExpr ctx arg
    let ty = tyInPtr argTy
    TNodeExpr(TPtrOfEN, [ arg ], ty, loc), ty, ctx

  | TFunExpr (funSerial, _, _) ->
    let arg, _, ctx = inferExpr ctx arg
    let ty, ctx = castFunAsNativeFun funSerial loc ctx
    TNodeExpr(TFunPtrOfEN, [ arg ], ty, loc), ty, ctx

  | _ ->
    let ctx = addError ctx "Expected a variable." loc
    txAbort ctx loc

let private inferIndexExpr ctx l r loc =
  let l, lTy, ctx = inferExpr ctx l
  let r, rTy, ctx = inferExpr ctx r
  let tTy, ctx = freshMetaTy loc ctx

  let ctx =
    ctx
    |> addTraitBound (Trait.newIndex lTy rTy tTy) loc

  TNodeExpr(TIndexEN, [ l; r ], tTy, loc), tTy, ctx

let private inferSliceExpr ctx l r x loc =
  let l, lTy, ctx = inferExpr ctx l
  let r, rTy, ctx = inferExpr ctx r
  let x, xTy, ctx = inferExpr ctx x

  let ctx =
    let actualTy = tyFun lTy (tyFun rTy (tyFun xTy xTy))

    let expectedTy =
      tyFun tyInt (tyFun tyInt (tyFun tyString tyString))

    unifyTy ctx loc actualTy expectedTy

  TNodeExpr(TSliceEN, [ l; r; x ], xTy, loc), xTy, ctx

let private checkTupleExpr (ctx: TyCtx) items loc targetTy =
  let arity = List.length items
  let itemTys, ctx = expectTupleTy arity ctx targetTy loc

  let items =
    match listTryZip items itemTys with
    | it, [], [] -> it
    | _ -> unreachable ()

  let items, ctx =
    items
    |> List.mapFold
         (fun ctx (item, itemTy) ->
           let item, ctx = checkExpr ctx item itemTy
           item, ctx)
         ctx

  txTuple items loc, ctx

let private inferAscribeExpr ctx body ascriptionTy =
  let ascriptionTy, ctx = resolveAscriptionTy ctx ascriptionTy
  let body, ctx = checkExpr ctx body ascriptionTy
  body, ascriptionTy, ctx

let private checkBlockExpr ctx expr targetTy =
  let stmts, last =
    match expr with
    | TBlockExpr(stmts, last) -> stmts, last
    | _ -> unreachable ()

  let ctx = initializeLocalFuns ctx stmts

  let stmts, ctx =
    stmts |> List.mapFold (fun ctx stmt -> inferStmt ctx NotRec stmt) ctx

  let last, ctx = checkExpr ctx last targetTy

  TBlockExpr(stmts, last), ctx

/// Transforms an expression for type check in *check* mode.
///
/// The result is guaranteed to have the specified type.
let private checkExpr (ctx: TyCtx) (expr: TExpr) (targetTy: Ty) : TExpr * TyCtx =
  match expr with
  | TRecordExpr _ -> checkRecordExpr ctx expr targetTy
  | TMatchExpr _ -> checkMatchExpr ctx expr targetTy
  | TBlockExpr _ -> checkBlockExpr ctx expr targetTy

  | TNodeExpr (kind, args, _, loc) ->
    match kind, args with
    | TTupleEN, _ -> checkTupleExpr ctx args loc targetTy

    | _ ->
      // Forward to inference.
      let expr, inferredTy, ctx = inferExpr ctx expr
      let ctx = unifyTy ctx (exprToLoc expr) inferredTy targetTy
      expr, ctx

  | _ ->
    // Forward to inference.
    let expr, inferredTy, ctx = inferExpr ctx expr
    let ctx = unifyTy ctx (exprToLoc expr) inferredTy targetTy
    expr, ctx

/// Transforms an expression for type check in *inference mode* (a.k.a. synthesis mode.)
///
/// This mode synthesizes the type of an expression bottom-up.
/// The target type isn't provided.
let private inferExpr (ctx: TyCtx) (expr: TExpr) : TExpr * Ty * TyCtx =
  match expr with
  | TLitExpr (lit, _) -> inferLitExpr ctx expr lit
  | TVarExpr (serial, _, loc) -> inferVarExpr ctx serial loc
  | TFunExpr (serial, _, loc) -> inferFunExpr ctx serial loc
  | TVariantExpr (serial, _, loc) -> inferVariantExpr ctx serial loc
  | TPrimExpr (prim, _, loc) -> inferPrimExpr ctx prim loc
  | TNavExpr (receiver, field, _, loc) -> inferNavExpr ctx receiver field loc

  | TNodeExpr (kind, args, exprTy, loc) ->
    match kind, args with
    | TAppEN, [ TPrimExpr _; _ ] -> inferPrimAppExpr ctx expr
    | TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.PtrWrite, _, _); _ ], _, _); _ ] -> inferWriteExpr ctx expr
    | TAppEN, [ TNodeExpr (TAppEN, [ TPrimExpr (TPrim.FunPtrInvoke, _, _); _ ], _, _); _ ] ->
      inferFunPtrInvokeExpr ctx expr
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

    | TAscribeEN, [ arg ] -> inferAscribeExpr ctx arg exprTy
    | TAscribeEN, _ -> unreachable ()

    | TSizeOfEN, [ TNodeExpr (TTyPlaceholderEN, _, ty, _) ] ->
      assert (isNoTy ty |> not)
      assert (tyEqual exprTy tyInt)
      expr, tyInt, ctx

    | TSizeOfEN, _ -> unreachable ()

    | TTyPlaceholderEN, _ ->
      txUnit loc, tyUnit, addError ctx "Type placeholder can appear in argument of __nativeExpr or __nativeStmt." loc

    | TAbortEN, _ -> txAbort ctx loc

    | TTupleEN, _ ->
      // Forward to check.
      let targetTy, ctx = freshMetaTyForExpr expr ctx
      let expr, ctx = checkExpr ctx expr targetTy
      expr, targetTy, ctx

    | TFunPtrOfEN, _
    | TDiscriminantEN _, _
    | TCatchNeverEN, _
    | TCallNativeEN _, _
    | TPtrOffsetEN, _
    | TPtrReadEN, _
    | TPtrWriteEN, _
    | TFunPtrInvokeEN, _
    | TNativeExprEN _, _
    | TNativeStmtEN _, _
    | TNativeDeclEN _, _ -> unreachable ()

  | TRecordExpr _
  | TMatchExpr _
  | TBlockExpr _ ->
    // Forward to check.
    let targetTy, ctx = freshMetaTyForExpr expr ctx
    let expr, ctx = checkExpr ctx expr targetTy
    expr, targetTy, ctx

// -----------------------------------------------
// Statement
// -----------------------------------------------

let private inferExprStmt ctx expr =
  let expr, ctx = checkExpr ctx expr tyUnit
  TExprStmt expr, ctx

let private inferLetValStmt ctx pat init loc =
  let ascriptionTyOpt, ctx =
    match patToAscriptionTy pat with
    | Some ty ->
      let ty, ctx = resolveAscriptionTy ctx ty
      Some ty, ctx

    | None -> None, ctx

  let init, initTy, ctx =
    match ascriptionTyOpt with
    | Some ascriptionTy ->
      let expr, ctx = checkExpr ctx init ascriptionTy
      expr, ascriptionTy, ctx

    | None -> inferExpr ctx init

  let pat, _, ctx = inferIrrefutablePat ctx pat (Some initTy)
  TLetValStmt(pat, init, loc), ctx

let private inferLetFunStmt ctx mutuallyRec callee vis argPats body loc =
  let isMainFun (ctx: TyCtx) funSerial =
    match ctx.MainFunOpt with
    | Some mainFun -> funSerialCompare mainFun funSerial = 0
    | _ -> false

  // Special treatment for main function.
  let mainFunTyOpt, ctx =
    if isMainFun ctx callee then
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
      let argPat, argTy, ctx = inferIrrefutablePat ctx argPat None
      let argPats, funTy, ctx = inferArgs ctx funTy argPats
      argPat :: argPats, tyFun argTy funTy, ctx

  let ctx, parentIsFunLocal = { ctx with IsFunLocal = true }, ctx.IsFunLocal

  let calleeTy, ctx =
    let funDef = ctx.Funs |> mapFind callee
    let oldTy, _, ctx = instantiateTyScheme ctx funDef.Ty loc
    oldTy, ctx

  let provisionalResultTy, ctx = ctx |> freshMetaTyForExpr body

  let argPats, funTy, ctx =
    let ctx = argPats |> initializeParams ctx
    inferArgs ctx provisionalResultTy argPats

  let ctx = unifyTy ctx loc calleeTy funTy

  let body, bodyTy, ctx =
    let body, ctx = checkExpr ctx body provisionalResultTy

    match substTy ctx provisionalResultTy with
    | Ty(NeverTk, _) -> TNodeExpr(TCatchNeverEN, [ body ], tyNever, loc), tyNever, ctx
    | bodyTy -> body, bodyTy, ctx

  let ctx =
    match mainFunTyOpt, bodyTy with
    | Some _, Ty(NeverTk, _) -> unifyTy ctx loc calleeTy (tyFun tyUnit tyNever)
    | Some mainFunTy, _ -> unifyTy ctx loc calleeTy mainFunTy
    | _ -> ctx

  let ctx =
    if not parentIsFunLocal then
      let ctx = attemptResolveTraitBounds ctx
      generalizeFun ctx callee
    else
      let funSerial = callee
      let funDef = ctx.Funs |> mapFind funSerial

      let funTy =
        let (TyScheme (_, funTy)) = funDef.Ty
        assert (isNoTy funTy |> not)
        funTy

      let funTy = substTy ctx funTy

      { ctx with
          Funs =
            ctx.Funs
            |> TMap.add funSerial { funDef with Ty = TyScheme([], funTy) } }

  let ctx =
    match mutuallyRec with
    | IsRec -> { ctx with GrayFuns = ctx.GrayFuns |> TSet.add callee }
    | _ -> ctx

  let ctx = { ctx with IsFunLocal = parentIsFunLocal }

  TLetFunStmt(callee, NotRec, vis, argPats, body, loc), ctx

let private inferBlockStmt (ctx: TyCtx) mutuallyRec stmts : TStmt * TyCtx =
  let parentCtx = ctx

  let ctx = initializeNonlocalVarsAndFuns ctx stmts

  let stmts, ctx =
    stmts
    |> List.mapFold (fun ctx stmt -> inferStmt ctx mutuallyRec stmt) ctx

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
               let funTy = substTy ctx funTy
               let funTyScheme = tyGeneralize (canGeneralize ctx) funTy

               let funs =
                 ctx.Funs
                 |> TMap.add funSerial { funDef with Ty = funTyScheme }

               let instantiations, grayInstantiations =
                 ctx.GrayInstantiations |> TMap.remove funSerial

               let ctx =
                 { ctx with
                     Funs = funs
                     GrayInstantiations = grayInstantiations }

              //  let _ =
              //   let getTyName tySerial =
              //       ctx.Tys
              //       |> TMap.tryFind tySerial
              //       |> Option.map tyDefToName

              //   __trace ("gen2 fun " + funDef.Name + "<" + (tyVars |> List.map (fun tySerial -> getTyName tySerial |> Option.defaultValue (string tySerial)) |> S.concat ", ") + "> : " + tyDisplay getTyName funTy)

               let ctx =
                 instantiations
                 |> Option.defaultValue []
                 |> List.fold
                      (fun (ctx: TyCtx) (useSiteTy, loc) ->
                        let funTy, _, ctx = instantiateTyScheme ctx funTyScheme loc
                        let newCtx = unifyTy ctx loc useSiteTy funTy
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
// Recursive Declaration Decomposition
// -----------------------------------------------

// What:
// Split declarations into a list of recursive blocks
// so that forward references are all bound in each block.
//
// Why:
// This improves result of generalization
// by preventing unnecessary unification of meta types that can be generalized.
//
// How:
// First attach a number level to each declaration in order.
// For each occurrence of a variable or function that is defined at level U
// in a declaration of level L (< U), unify levels L..U to L.
// Finally group declarations by their levels.
//
// Proof (sketch):
// After the process, forward-references are all bound in each block
// because variables and functions defined in a recursive block
// must not be referred in another forward block;
// if so, these two blocks must have had the same level.
//
// Remark:
// This doesn't change order of declarations.

module private RecursiveDeclDecomposition =
  [<RequireQualifiedAccess; NoEquality; NoComparison>]
  type private RddCtx =
    { VarLevels: TreeMap<VarSerial, int>
      FunLevels: TreeMap<FunSerial, int>
      LevelMap: TreeMap<int, int> }

  /// Unwrap recursive blocks that are made from modules in NameRes.
  let private flattenBlocks stmts =
    stmts |> List.collect
      (fun stmt ->
        match stmt with
        | TBlockStmt (IsRec, stmts) -> flattenBlocks stmts
        | _ -> [ stmt ])

  /// Enumerates all variables defined in a pattern
  /// to compute varLevelMap.
  let private collectVars (level: int) (varLevelMap: TreeMap<VarSerial, int>) pat : TreeMap<VarSerial, int> =
    patFoldVars (fun varMap (varSerial, _) -> TMap.add varSerial level varMap) varLevelMap pat

  /// Finds occurrences of variables and functions
  /// to unify levels.
  let private rddOnExpr level (ctx: RddCtx) (expr: TExpr) =
    let toCurrentLevel level =
      ctx.LevelMap |> TMap.tryFind level |> Option.defaultValue level

    let levelDown (ctx: RddCtx) (lower: int) (upper: int) =
      let lower = toCurrentLevel lower

      let rec update levelMap l =
        if l <= upper then
          update (levelMap |> TMap.add l lower) (l + 1)
        else
          levelMap

      { ctx with LevelMap = update ctx.LevelMap lower }

    match expr with
    | TVarExpr (varSerial, _, _) ->
      match ctx.VarLevels |> TMap.tryFind varSerial |> Option.map toCurrentLevel with
      | Some varLevel when level < varLevel -> levelDown ctx level varLevel

      | _ -> ctx

    | TFunExpr(funSerial, _, _) ->
      match ctx.FunLevels |> TMap.tryFind funSerial |> Option.map toCurrentLevel with
      | Some funLevel when level < funLevel -> levelDown ctx level funLevel
      | _ -> ctx

    | TLitExpr _
    | TVariantExpr _
    | TPrimExpr _ -> ctx

    | TRecordExpr(_, fields, _, _) -> fields |> List.fold (fun ctx (_, init, _) -> rddOnExpr level ctx init) ctx

    | TMatchExpr(cond, arms, _, _) ->
      let ctx = rddOnExpr level ctx cond

      arms |> List.fold
        (fun ctx (_, guard, arm) ->
          let ctx = rddOnExpr level ctx guard
          rddOnExpr level ctx arm)
        ctx

    | TNavExpr(lExpr, _, _, _) -> rddOnExpr level ctx lExpr
    | TNodeExpr(_, args, _, _) -> args |> List.fold (rddOnExpr level) ctx

    | TBlockExpr(stmts, last) ->
      let ctx = stmts |> List.fold (rddOnStmt level) ctx
      rddOnExpr level ctx last

  let private rddOnStmt level (ctx: RddCtx) (stmt: TStmt) =
    match stmt with
    | TExprStmt expr -> rddOnExpr level ctx expr
    | TLetValStmt (_, init, _) -> rddOnExpr level ctx init
    | TLetFunStmt(_, _, _, _, body, _) -> rddOnExpr level ctx body
    | TBlockStmt(_, stmts) -> stmts |> List.fold (rddOnStmt level) ctx

  // See comments above.
  let decompose (_tyCtx: TyCtx) (stmts: TStmt list) : TStmt list =
    let leveledStmts =
      stmts
      |> flattenBlocks
      |> List.mapi (fun i stmt -> i + 1, stmt)

    let levelMap =
      leveledStmts
      |> List.fold
        (fun acc (level, stmt) ->
          let varLevelMap, funLevelMap = acc
          match stmt with
          | TExprStmt _
          | TBlockStmt _ -> acc

          | TLetValStmt (pat, _, _) -> collectVars level varLevelMap pat, funLevelMap
          | TLetFunStmt (funSerial, _, _, _, _, _) -> varLevelMap, TMap.add funSerial level funLevelMap
        )
        (TMap.empty varSerialCompare, TMap.empty funSerialCompare)

    let ctx =
      let varLevels, funLevels = levelMap
      let ctx: RddCtx = { VarLevels = varLevels; FunLevels = funLevels; LevelMap = TMap.empty compare }

      leveledStmts |> List.fold (fun ctx (level, stmt) -> rddOnStmt level ctx stmt) ctx

    let blocks =
      let getLevel l = ctx.LevelMap |> TMap.tryFind l |> Option.defaultValue l
      let same l r = getLevel l = getLevel r

      let rec groupLoop acc stmts =
        match stmts with
        | [] -> List.rev acc

        | (level, stmt) :: stmts ->
          let rec blockLoop acc stmts =
            match stmts with
            | (l, stmt) :: stmts when same l level -> blockLoop (stmt :: acc) stmts
            | _ -> List.rev acc, stmts

          let block, stmts = blockLoop [ stmt ] stmts
          groupLoop (block :: acc) stmts

      groupLoop [] leveledStmts

    blocks
    |> List.map (fun stmts -> TBlockStmt(IsRec, stmts))

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
          match tyCtx.Tys |> mapFind tySerial with
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
             match tyCtx.Tys |> mapFind tySerial with
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
// Rms
// -----------------------------------------------

// RMS: Resolve Meta types and Synonyms. A follow-up pass of type check.

// RMS includes three operations:
//
// - substitute: replace resolved meta types with actual types
// - degenerate: replace undefined meta types with unit
// - expand: replace type synonyms with actual types
module private Rms =
  // #map_merge
  let private setAppend first secondSet =
    secondSet |> TSet.fold (fun set item -> TSet.add item set) first

  [<RequireQualifiedAccess; NoEquality; NoComparison>]
  type private RmsCtx =
    { StaticVars: TreeMap<VarSerial, VarDef>
      LocalVars: TreeMap<VarSerial, VarDef>
      Funs: TreeMap<FunSerial, FunDef>
      Tys: TreeMap<TySerial, TyDef>
      MetaTys: TreeMap<TySerial, Ty>
      DefinedTys: TreeSet<TySerial> }

  let private newRmsCtx localVars (ctx: TyCtx): RmsCtx =
    { StaticVars = ctx.Vars
      LocalVars = localVars
      Funs = ctx.Funs
      Tys = ctx.Tys
      MetaTys = ctx.MetaTys
      DefinedTys = TSet.empty compare }

  /// Substitutes bound meta tys in a ty.
  /// Unbound meta tys are degenerated, i.e. replaced with unit.
  let private rmsTy (ctx: RmsCtx) (ty: Ty) : Ty =
    let substMeta tySerial =
      match ctx.MetaTys |> TMap.tryFind tySerial with
      | Some ty -> Some ty

      | _ when ctx.DefinedTys |> TSet.contains tySerial |> not ->
        // Degenerate unbounded meta type.
        // __trace ("degenerate: " + string tySerial + " in " + __dump ty)
        Some tyUnit

      | _ -> None

    let ty = tySubst substMeta ty
    tyExpandSynonyms (fun tySerial -> ctx.Tys |> TMap.tryFind tySerial) ty

  let private rmsPat (ctx: RmsCtx) (pat: TPat) : TPat * RmsCtx =
    let onTy ty = rmsTy ctx ty

    let onVar (ctx: RmsCtx) varSerial =
      match ctx.LocalVars |> TMap.tryFind varSerial with
      | Some varDef ->
          let ty = rmsTy ctx varDef.Ty
          { ctx with LocalVars = ctx.LocalVars |> TMap.add varSerial { varDef with Ty = ty } }

      | None ->
          let varDef = ctx.StaticVars |> mapFind varSerial
          let ty = rmsTy ctx varDef.Ty
          { ctx with StaticVars = ctx.StaticVars |> TMap.add varSerial { varDef with Ty = ty } }

    match pat with
    | TLitPat _ -> pat, ctx
    | TDiscardPat(ty, loc) -> TDiscardPat(onTy ty, loc), ctx

    | TVarPat(vis, varSerial, ty, loc) ->
      let ctx = onVar ctx varSerial
      TVarPat(vis, varSerial, onTy ty, loc), ctx

    | TVariantPat(variantSerial, ty, loc) -> TVariantPat(variantSerial, onTy ty, loc), ctx

    | TNodePat(kind, argPats, ty, loc) ->
      let argPats, ctx = List.mapFold rmsPat ctx argPats
      TNodePat(kind, argPats, onTy ty, loc), ctx

    | TAsPat(argPat, varSerial, loc) ->
      let ctx = onVar ctx varSerial
      let argPat, ctx = rmsPat ctx argPat
      TAsPat(argPat, varSerial, loc), ctx

    | TOrPat(lPat, rPat, loc) ->
      let lPat, ctx = rmsPat ctx lPat
      let rPat, ctx = rmsPat ctx rPat
      TOrPat(lPat, rPat, loc), ctx

  let private rmsExpr (ctx: RmsCtx) (expr: TExpr) : TExpr * RmsCtx =
    let onTy ty = rmsTy ctx ty

    match expr with
    | TLitExpr _ -> expr, ctx

    | TVarExpr _
    | TFunExpr _
    | TVariantExpr _
    | TPrimExpr _ -> exprMap onTy expr, ctx

    | TRecordExpr (baseOpt, fields, ty, loc) ->
      let baseOpt, ctx = optionMapFold rmsExpr ctx baseOpt

      let fields, ctx =
        fields
        |> List.mapFold (fun ctx (name, init, loc) ->
          let init, ctx = rmsExpr ctx init
          (name, init, loc), ctx)
          ctx

      TRecordExpr(baseOpt, fields, onTy ty, loc), ctx

    | TMatchExpr (cond, arms, ty, loc) ->
      let cond, ctx = rmsExpr ctx cond

      let arms, ctx =
        arms
        |> List.mapFold (fun ctx (pat, guard, body) ->
          let pat , ctx = rmsPat ctx pat
          let guard, ctx = rmsExpr ctx guard
          let body ,ctx = rmsExpr ctx body
          (pat, guard, body), ctx) ctx

      TMatchExpr(cond, arms, onTy ty, loc), ctx

    | TNavExpr (lExpr, r, ty, loc) ->
      let lExpr, ctx = rmsExpr ctx lExpr
      TNavExpr(lExpr, r, onTy ty, loc), ctx

    | TNodeExpr (kind, args, ty, loc) ->
      let args, ctx = List.mapFold rmsExpr ctx args
      TNodeExpr(kind, args, onTy ty, loc), ctx

    | TBlockExpr (stmts, last) ->
      let stmts, ctx = List.mapFold rmsStmt ctx stmts
      let last, ctx = rmsExpr ctx last
      TBlockExpr(stmts, last), ctx

  let private rmsStmt (ctx: RmsCtx) (stmt: TStmt) : TStmt * RmsCtx =
    match stmt with
    | TExprStmt expr ->
      let expr, ctx = rmsExpr ctx expr
      TExprStmt expr, ctx

    | TLetValStmt (pat, init, loc) ->
      let pat, ctx = rmsPat ctx pat
      let init, ctx = rmsExpr ctx init
      TLetValStmt(pat, init, loc), ctx

    | TLetFunStmt (funSerial, isRec, vis, argPats, body, loc) ->
      let parentCtx = ctx

      // Update definition:
      let funDef: FunDef = ctx.Funs |> mapFind funSerial
      let (TyScheme(tyVars, funTy)) = funDef.Ty
      let definedTys = TSet.ofList compare tyVars
      let ctx = { ctx with DefinedTys = setAppend ctx.DefinedTys definedTys }
      let funTy = rmsTy ctx funTy
      let funDef = { funDef with Ty = TyScheme(tyVars, funTy) }
      let ctx = { ctx with Funs = ctx.Funs |> TMap.add funSerial funDef }

      // Recurse:
      let argPats, ctx = argPats |> List.mapFold rmsPat ctx
      let body, ctx = rmsExpr ctx body
      let ctx = { ctx with DefinedTys = parentCtx.DefinedTys }

      TLetFunStmt (funSerial, isRec, vis, argPats, body, loc), ctx

    | TBlockStmt (isRec, stmts) ->
      let stmts, ctx = List.mapFold rmsStmt ctx stmts
      TBlockStmt (isRec, stmts), ctx

  let rmsModule (ctx: TyCtx) (m: TModule) : TModule * TyCtx =
    let rmsCtx = newRmsCtx m.Vars ctx
    let stmts, rmsCtx = List.mapFold rmsStmt rmsCtx m.Stmts

    let m =
      { m with
          Vars = rmsCtx.LocalVars
          Stmts = stmts }

    let ctx =
      { ctx with
          Vars = rmsCtx.StaticVars
          Funs = rmsCtx.Funs
          MetaTys = TMap.empty compare
          NoGeneralizeMetaTys = TSet.empty compare }

    m, ctx

// -----------------------------------------------
// Expand Synonyms
// -----------------------------------------------

let private expandAllSynonyms (ctx: TyCtx) : TyCtx =
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

            | RecordTyDef (recordName, tyArgs, fields, repr, loc) ->
              let fields =
                fields
                |> List.map (fun (name, ty, loc) ->
                  let ty = expandSynonyms ctx ty
                  name, ty, loc)

              acc
              |> TMap.add tySerial (RecordTyDef(recordName, tyArgs, fields, repr, loc))

            | _ -> acc |> TMap.add tySerial tyDef)
          (TMap.empty compare)

  { ctx with
      Variants = variants
      Tys = tys }

// -----------------------------------------------
// Interface
// -----------------------------------------------

let private inferModule (ctx: TyCtx) (m: TModule) : TModule * TyCtx =
  let parentCtx = ctx

  let isStaticVar varSerial =
    parentCtx.Vars |> TMap.containsKey varSerial

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
    let ctx = { ctx with IsFunLocal = false }

    let stmts =
      m.Stmts
      |> RecursiveDeclDecomposition.decompose ctx

    let ctx = initializeNonlocalVarsAndFuns ctx stmts

    stmts
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

  let m =
    { m with
        Vars = localVars
        Stmts = stmts }

  let ctx = { ctx with Vars = staticVars }

  // Resolve meta types and synonyms.
  let m, ctx = Rms.rmsModule ctx m

  m, ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let infer (modules: TProgram, nameRes: NameResResult) : TProgram * TirCtx =
  let ctx = newTyCtx nameRes

  let ctx = synonymCycleCheck ctx
  let modules, ctx = modules |> List.mapFold inferModule ctx
  let ctx = expandAllSynonyms ctx

  let tirCtx = toTirCtx ctx

  // Enforce.
  assert (tirCtx.StaticVars
          |> TMap.toList
          |> List.forall (fun (_, varDef: VarDef) ->
            match varDef.IsStatic with
            | IsStatic -> tyIsMonomorphic varDef.Ty
            | NotStatic -> false))

  modules, tirCtx
