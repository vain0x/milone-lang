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

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.TySystem
open MiloneLang.NameRes

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

    /// Type serial to type definition.
    Tys: AssocMap<TySerial, TyDef>

    TyDepths: AssocMap<TySerial, LetDepth>
    LetDepth: LetDepth
    TraitBounds: (Trait * Loc) list
    Logs: (Log * Loc) list }

let private addLog (ctx: TyCtx) log loc =
  { ctx with
      Logs = (log, loc) :: ctx.Logs }

let private addError (ctx: TyCtx) message loc =
  { ctx with
      Logs = (Log.Error message, loc) :: ctx.Logs }

/// Be carefully. Let depths must be counted the same as name resolution.
let private incDepth (ctx: TyCtx) = { ctx with LetDepth = ctx.LetDepth + 1 }

let private decDepth (ctx: TyCtx) = { ctx with LetDepth = ctx.LetDepth - 1 }

let private findVar (ctx: TyCtx) serial = ctx.Vars |> mapFind serial

let private findTy tySerial (ctx: TyCtx) = ctx.Tys |> mapFind tySerial

let private freshVar (ctx: TyCtx) hint ty loc =
  let varSerial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        Vars =
          ctx.Vars
          |> mapAdd varSerial (VarDef(hint, AutoSM, ty, loc)) }

  varSerial, ctx

let private freshTySerial (ctx: TyCtx) =
  let serial = ctx.Serial + 1

  let ctx =
    { ctx with
        Serial = ctx.Serial + 1
        TyDepths = ctx.TyDepths |> mapAdd serial ctx.LetDepth }

  serial, ctx

let private freshMetaTy (_: Ident) loc (ctx: TyCtx): Ty * unit * TyCtx =
  let serial, ctx = freshTySerial ctx
  let ty = MetaTy(serial, loc)
  ty, (), ctx

let private freshMetaTyForPat pat ctx =
  let _, loc = pat |> patExtract
  let tySerial, ctx = ctx |> freshTySerial
  let ty = MetaTy(tySerial, loc)
  ty, ctx

let private freshMetaTyForExpr expr ctx =
  let _, loc = expr |> exprExtract
  let tySerial, ctx = ctx |> freshTySerial
  let ty = MetaTy(tySerial, loc)
  ty, ctx

// -----------------------------------------------
// Type inference algorithm
// -----------------------------------------------

let private toTyContext (ctx: TyCtx): TyContext =
  { Serial = ctx.Serial
    LetDepth = ctx.LetDepth
    Tys = ctx.Tys
    TyDepths = ctx.TyDepths }

let private withTyContext (ctx: TyCtx) logAcc (tyCtx: TyContext): TyCtx =
  { ctx with
      Serial = tyCtx.Serial
      Tys = tyCtx.Tys
      TyDepths = tyCtx.TyDepths
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

  let logAcc, tyCtx = ctx |> toTyContext |> go ctx.Logs traits

  withTyContext ctx logAcc tyCtx

let private bindTy (ctx: TyCtx) tySerial ty loc =
  typingBind (toTyContext ctx) tySerial ty loc
  |> withTyContext ctx ctx.Logs

let private substTy (ctx: TyCtx) ty: Ty = typingSubst (toTyContext ctx) ty

/// Substitutes bound meta tys in a ty.
/// Unbound meta tys are degenerated, i.e. replaced with unit.
let private substOrDegenerateTy (ctx: TyCtx) ty =
  let substMeta tySerial =
    match ctx.Tys |> mapTryFind tySerial with
    | Some (MetaTyDef (_, ty, _)) -> Some ty

    | Some (UniversalTyDef _) -> None

    | _ ->
        let depth = ctx.TyDepths |> mapFind tySerial
        // Degenerate unless quantified.
        if depth < 1000000000 then Some tyUnit else None

  tySubst substMeta ty

let private unifyTy (ctx: TyCtx) loc (lty: Ty) (rty: Ty): TyCtx =
  let logAcc, tyCtx =
    typingUnify ctx.Logs (toTyContext ctx) lty rty loc

  withTyContext ctx logAcc tyCtx

let private unifyVarTy varSerial tyOpt loc ctx =
  let varTy, ctx =
    match findVar ctx varSerial with
    | VarDef (_, _, ty, _) -> ty, ctx
    | VariantDef (_, _, _, _, ty, _) -> ty, ctx
    | FunDef (_, _, tyScheme, _) -> instantiateTyScheme ctx tyScheme loc

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

let private instantiateTyScheme ctx (tyScheme: TyScheme) loc =
  match tyScheme with
  | TyScheme ([], ty) -> ty, ctx

  | TyScheme (fvs, ty) ->
      // Generate fresh type variable for each bound type variable.
      let mapping, ctx =
        (fvs, ctx)
        |> stMap (fun (fv, ctx) ->
             let newSerial, ctx = freshTySerial ctx
             (fv, newSerial), ctx)

      // Replace bound variables in the type with fresh ones.
      let ty =
        let extendedCtx =
          mapping
          |> List.fold (fun ctx (src, target) -> bindTy ctx src (MetaTy(target, loc)) loc) ctx

        substTy extendedCtx ty

      ty, ctx

let private instantiateTySpec loc (TySpec (polyTy, traits), ctx) =
  // Refresh meta types and generate bindings.
  let oldTySerials = polyTy |> tyCollectFreeVars

  let bindings, ctx =
    (oldTySerials, ctx)
    |> stMap (fun (oldTySerial, ctx) ->
         let tySerial, ctx = ctx |> freshTySerial
         (oldTySerial, MetaTy(tySerial, loc)), ctx)

  // Replace meta types in the type and trait bounds.
  let substMeta tySerial = bindings |> assocTryFind intCmp tySerial
  let polyTy = polyTy |> tySubst substMeta

  let traits =
    traits
    |> List.map (fun theTrait -> theTrait |> traitMapTys (tySubst substMeta), loc)

  polyTy, traits, ctx

let private generalizeFun (ctx: TyCtx) (outerLetDepth: LetDepth) funSerial =
  match ctx.Vars |> mapFind funSerial with
  | FunDef (ident, arity, TyScheme ([], funTy), loc) ->
      let isOwned tySerial =
        let depth = ctx.TyDepths |> mapFind tySerial

        depth > outerLetDepth

      let funTy = substTy ctx funTy
      let funTyScheme = tyGeneralize isOwned funTy

      let varDef = FunDef(ident, arity, funTyScheme, loc)

      let ctx =
        { ctx with
            Vars = ctx.Vars |> mapAdd funSerial varDef }

      // Mark generalized meta tys (universally quantified vars),
      // by increasing their depth to infinite (10^9).
      let ctx =
        let (TyScheme (fvs, _)) = funTyScheme
        { ctx with
            TyDepths =
              fvs
              |> List.fold (fun tyDepths fv -> tyDepths |> mapAdd fv 1000000000) (ctx.TyDepths) }

      ctx
  | FunDef _ -> failwith "Can't generalize already-generalized function"
  | _ -> failwith "Expected function"

// -----------------------------------------------
// Emission helpers
// -----------------------------------------------

/// Creates an expression to abort.
let private hxAbort (ctx: TyCtx) loc =
  let ty, (), ctx = ctx |> freshMetaTy "abort" loc
  let funTy = tyFun tyInt ty
  let exitExpr = HPrimExpr(HPrim.Exit, funTy, loc)

  let callExpr =
    hxApp exitExpr (HLitExpr(IntLit 1, loc)) ty loc

  callExpr, ty, ctx

// -----------------------------------------------
// Pattern
// -----------------------------------------------

/// Tries to get ty annotation from pat.
let private patToAnnoTy pat =
  match pat with
  | HAnnoPat (_, ty, _) -> Some ty

  | HAsPat (pat, _, _) -> patToAnnoTy pat

  | HOrPat (l, r, _, _) ->
      match patToAnnoTy l with
      | None -> patToAnnoTy r
      | it -> it

  | _ -> None

let private inferNilPat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyList itemTy
  HNilPat(itemTy, loc), ty, ctx

let private inferNonePat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyList itemTy
  HNonePat(itemTy, loc), ty, ctx

let private inferSomePat ctx pat loc =
  let itemTy, ctx = ctx |> freshMetaTyForPat pat
  let ty = tyFun itemTy (tyList itemTy)
  HSomePat(itemTy, loc), ty, ctx

let private inferDiscardPat ctx pat loc =
  let ty, ctx = ctx |> freshMetaTyForPat pat
  HDiscardPat(ty, loc), ty, ctx

let private inferRefPat (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc

  HRefPat(varSerial, ty, loc), ty, ctx

let private inferVariantPat (ctx: TyCtx) variantSerial loc =
  let ty, ctx = ctx |> unifyVarTy variantSerial None loc

  HVariantPat(variantSerial, ty, loc), ty, ctx

let private inferCallPat (ctx: TyCtx) pat callee args loc =
  match args with
  | [ payload ] ->
      let resultTy, ctx = ctx |> freshMetaTyForPat pat

      let callee, calleeTy, ctx = inferPat ctx callee
      let payload, payloadTy, ctx = inferPat ctx payload

      let ctx =
        unifyTy ctx loc calleeTy (tyFun payloadTy resultTy)

      HCallPat(callee, [ payload ], resultTy, loc), resultTy, ctx

  | _ -> failwith "invalid use of call pattern"

let private inferTuplePat ctx itemPats loc =
  let rec go accPats accTys ctx itemPats =
    match itemPats with
    | [] -> List.rev accPats, List.rev accTys, ctx
    | itemPat :: itemPats ->
        let itemPat, itemTy, ctx = inferPat ctx itemPat
        go (itemPat :: accPats) (itemTy :: accTys) ctx itemPats

  let itemPats, itemTys, ctx = go [] [] ctx itemPats

  let tupleTy = tyTuple itemTys
  HTuplePat(itemPats, tupleTy, loc), tupleTy, ctx

let private inferConsPat ctx l r loc =
  let l, lTy, ctx = inferPat ctx l
  let r, rTy, ctx = inferPat ctx r

  let itemTy = lTy
  let listTy = tyList itemTy
  let ctx = unifyTy ctx loc rTy listTy

  HConsPat(l, r, itemTy, loc), listTy, ctx

let private inferAsPat ctx body varSerial loc =
  let body, bodyTy, ctx = inferPat ctx body

  let _, ctx =
    ctx |> unifyVarTy varSerial (Some bodyTy) loc

  HAsPat(body, varSerial, loc), bodyTy, ctx

let private inferAnnoPat ctx body annoTy loc =
  let body, bodyTy, ctx = inferPat ctx body
  let ctx = unifyTy ctx loc bodyTy annoTy
  body, annoTy, ctx

let private inferOrPat ctx first second loc =
  // FIXME: Error if two patterns introduce different bindings.
  let first, firstTy, ctx = inferPat ctx first
  let second, secondTy, ctx = inferPat ctx second

  let ctx = unifyTy ctx loc firstTy secondTy

  let ty = firstTy
  HOrPat(first, second, ty, loc), ty, ctx

let private inferPat ctx pat: HPat * Ty * TyCtx =
  match pat with
  | HLitPat (lit, _) -> pat, litToTy lit, ctx
  | HNilPat (_, loc) -> inferNilPat ctx pat loc
  | HNonePat (_, loc) -> inferNonePat ctx pat loc
  | HSomePat (_, loc) -> inferSomePat ctx pat loc
  | HDiscardPat (_, loc) -> inferDiscardPat ctx pat loc
  | HRefPat (varSerial, _, loc) -> inferRefPat ctx varSerial loc
  | HVariantPat (variantSerial, _, loc) -> inferVariantPat ctx variantSerial loc
  | HCallPat (callee, args, _, loc) -> inferCallPat ctx pat callee args loc
  | HConsPat (l, r, _, loc) -> inferConsPat ctx l r loc
  | HTuplePat (items, _, loc) -> inferTuplePat ctx items loc
  | HAsPat (body, serial, loc) -> inferAsPat ctx body serial loc
  | HAnnoPat (body, annoTy, loc) -> inferAnnoPat ctx body annoTy loc
  | HOrPat (first, second, _, loc) -> inferOrPat ctx first second loc
  | HNavPat _ -> failwithf "NEVER: HNavPat is resolved in NameRes. %A" pat
  | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private inferRefExpr (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc

  HRefExpr(varSerial, ty, loc), ty, ctx

let private inferFunExpr (ctx: TyCtx) varSerial loc =
  let ty, ctx = ctx |> unifyVarTy varSerial None loc

  HFunExpr(varSerial, ty, loc), ty, ctx

let private inferVariantExpr (ctx: TyCtx) variantSerial loc =
  let ty, ctx = ctx |> unifyVarTy variantSerial None loc

  HVariantExpr(variantSerial, ty, loc), ty, ctx

let private inferPrimExpr ctx prim loc =
  let tySpec = prim |> primToTySpec
  let primTy, traits, ctx = (tySpec, ctx) |> instantiateTySpec loc
  let ctx = ctx |> addTraitBounds traits
  HPrimExpr(prim, primTy, loc), primTy, ctx

let private inferNilExpr ctx itself loc =
  let itemTy, ctx = freshMetaTyForExpr itself ctx
  hxNil itemTy loc, tyList itemTy, ctx

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
      | Some ((AppTy (RefTyCtor tySerial, [])) as recordTy) ->
          match ctx |> findTy tySerial with
          | RecordTyDef (recordIdent, fieldDefs, _) -> Some(recordTy, recordIdent, fieldDefs)
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

  | Some (recordTy, recordIdent, fieldDefs) ->
      let addRedundantErr fieldIdent loc ctx =
        addLog ctx (Log.RedundantFieldError(recordIdent, fieldIdent)) loc

      let addIncompleteErr fieldIdents ctx =
        addLog ctx (Log.MissingFieldsError(recordIdent, fieldIdents)) loc

      // Infer field initializers and whether each of them is member of the record type.
      // Whenever a field appears, remove it from the set of fields
      // so that second occurrence of it is marked as redundant.
      let fields, (fieldDefs, ctx) =
        let fieldDefs =
          fieldDefs
          |> List.map (fun (ident, ty, _) -> ident, ty)
          |> mapOfList strCmp

        (fields, (fieldDefs, ctx))
        |> stMap (fun (field, (fieldDefs, ctx)) ->
             let ident, init, loc = field

             match fieldDefs |> mapRemove ident with
             | None, _ ->
                 let ctx = ctx |> addRedundantErr ident loc
                 let init, _, ctx = inferExpr ctx None init
                 (ident, init, loc), (fieldDefs, ctx)

             | Some defTy, fieldDefs ->
                 let init, initTy, ctx = inferExpr ctx (Some defTy) init
                 let ctx = unifyTy ctx loc initTy defTy
                 (ident, init, loc), (fieldDefs, ctx))

      // Unless base expr is specified, set of field initializers must be complete.
      let ctx =
        if baseOpt
           |> Option.isNone
           && fieldDefs |> mapIsEmpty |> not then
          let fields =
            fieldDefs
            |> mapToList
            |> List.map (fun (ident, _) -> ident)

          ctx |> addIncompleteErr fields
        else
          ctx

      match baseOpt with
      | None -> HRecordExpr(None, fields, recordTy, loc), recordTy, ctx

      | Some baseExpr ->
          // Assign to a temporary var so that TyElaborating can reuse the expr safely.
          // (This kind of modification is not business of typing, though.)
          // { base with fields... } ==> let t = base in { t with fields... }
          let varSerial, ctx = freshVar ctx "base" recordTy loc

          let varPat = HRefPat(varSerial, recordTy, loc)
          let varExpr = HRefExpr(varSerial, recordTy, loc)

          let recordExpr =
            HRecordExpr(Some varExpr, fields, recordTy, loc)

          HLetValExpr(PrivateVis, varPat, baseExpr, recordExpr, recordTy, loc), recordTy, ctx

/// match 'a with ( | 'a -> 'b )*
let private inferMatchExpr ctx expectOpt itself cond arms loc =
  let targetTy, ctx = freshMetaTyForExpr itself ctx

  let cond, condTy, ctx = inferExpr ctx None cond

  let arms, ctx =
    (arms, ctx)
    |> stMap (fun ((pat, guard, body), ctx) ->
         let pat, patTy, ctx = inferPat ctx pat

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
  | AppTy (StrTyCtor, []), "Length" ->
      let funExpr =
        HPrimExpr(HPrim.StrLength, tyFun tyStr tyInt, loc)

      hxApp funExpr l tyInt loc, tyInt, ctx

  | AppTy (RefTyCtor tySerial, []), _ ->
      let fieldTyOpt =
        let ident = r
        match ctx |> findTy tySerial with
        | RecordTyDef (_, fieldDefs, _) ->
            match fieldDefs
                  |> List.tryFind (fun (theIdent, _, _) -> theIdent = ident) with
            | Some (_, fieldTy, _) -> Some fieldTy
            | None -> None
        | _ -> None

      match fieldTyOpt with
      | Some fieldTy -> HNavExpr(l, r, fieldTy, loc), fieldTy, ctx
      | None -> fail ctx

  | _ -> fail ctx

let private inferNativeFunAppExpr ctx itself callee firstArg arg targetTy loc =
  match firstArg, arg with
  | HLitExpr (StrLit nativeFunIdent, _), HLitExpr (IntLit arity, _) ->
      let rec go ty arity ctx =
        if arity = 0 then
          ty, ctx
        else
          let argTy, _, ctx = freshMetaTy "arg" loc ctx
          go (tyFun argTy ty) (arity - 1) ctx

      let resultTy, ctx = ctx |> freshMetaTyForExpr itself
      let funTy, ctx = go resultTy arity ctx

      let ctx = unifyTy ctx loc funTy targetTy

      HPrimExpr(HPrim.NativeFun(nativeFunIdent, arity), funTy, loc), funTy, ctx
  | _ -> hxApp callee arg targetTy loc, targetTy, ctx

let private inferPrintfnAppExpr ctx arg loc =
  match arg with
  | HLitExpr (StrLit format, _) ->
      let funTy = analyzeFormat format
      HPrimExpr(HPrim.Printfn, funTy, loc), funTy, ctx
  | _ ->
      let ctx =
        addError ctx """First arg of printfn must be string literal, "..".""" loc

      hxAbort ctx loc

let private inferAppExpr ctx itself callee arg loc =
  let targetTy, ctx = ctx |> freshMetaTyForExpr itself
  let arg, argTy, ctx = inferExpr ctx None arg
  let callee, calleeTy, ctx = inferExpr ctx None callee

  let ctx =
    unifyTy ctx loc calleeTy (tyFun argTy targetTy)

  match callee with
  | HInfExpr (InfOp.App, [ HPrimExpr (HPrim.NativeFun _, _, _); firstArg ], _, _) ->
      inferNativeFunAppExpr ctx itself callee firstArg arg targetTy loc

  | HPrimExpr (HPrim.Printfn, _, loc) ->
      let callee, calleeTy, ctx = inferPrintfnAppExpr ctx arg loc

      let ctx =
        unifyTy ctx loc calleeTy (tyFun tyStr targetTy)

      hxApp callee arg targetTy loc, targetTy, ctx

  | _ -> hxApp callee arg targetTy loc, targetTy, ctx

let private inferTupleExpr (ctx: TyCtx) items loc =
  let rec go acc itemTys ctx items =
    match items with
    | [] -> List.rev acc, List.rev itemTys, ctx

    | item :: items ->
        let item, itemTy, ctx = inferExpr ctx None item
        go (item :: acc) (itemTy :: itemTys) ctx items

  let items, itemTys, ctx = go [] [] ctx items

  hxTuple items loc, tyTuple itemTys, ctx

let private inferAnnoExpr ctx body annoTy loc =
  let body, bodyTy, ctx = inferExpr ctx (Some annoTy) body

  let ctx = unifyTy ctx loc bodyTy annoTy

  body, annoTy, ctx

let private inferLetValExpr ctx expectOpt vis pat init next loc =
  let init, initTy, ctx =
    let expectOpt = patToAnnoTy pat
    inferExpr ctx expectOpt init

  let pat, patTy, ctx = inferPat ctx pat

  let ctx = unifyTy ctx loc initTy patTy

  let next, nextTy, ctx = inferExpr ctx expectOpt next
  HLetValExpr(vis, pat, init, next, nextTy, loc), nextTy, ctx

let private inferLetFunExpr (ctx: TyCtx) expectOpt callee vis isMainFun argPats body next loc =
  /// Infers argument patterns,
  /// constructing function's type.
  let rec inferArgs ctx funTy argPats =
    match argPats with
    | [] -> [], funTy, ctx

    | argPat :: argPats ->
        let argPat, argTy, ctx = inferPat ctx argPat
        let argPats, funTy, ctx = inferArgs ctx funTy argPats
        argPat :: argPats, tyFun argTy funTy, ctx

  let outerLetDepth = ctx.LetDepth
  let ctx = ctx |> incDepth

  let calleeTy, ctx =
    let calleeTy, _, ctx =
      if isMainFun then
        tyFun tyUnit tyInt, (), ctx // FIXME: argument type is string[]
      else
        freshMetaTy "fun" loc ctx

    let ctx =
      match ctx.Vars |> mapFind callee with
      | FunDef (_, _, TyScheme ([], oldTy), _) -> unifyTy ctx loc oldTy calleeTy
      | _ -> failwith "NEVER: It must be a pre-generalized function"

    calleeTy, ctx

  let provisionalResultTy, ctx = ctx |> freshMetaTyForExpr body

  let argPats, funTy, ctx =
    inferArgs ctx provisionalResultTy argPats

  let ctx = unifyTy ctx loc calleeTy funTy

  let body, bodyTy, ctx = inferExpr ctx None body

  let ctx =
    unifyTy ctx loc bodyTy provisionalResultTy

  let ctx = ctx |> decDepth

  let ctx = generalizeFun ctx outerLetDepth callee

  let next, nextTy, ctx = inferExpr ctx expectOpt next
  HLetFunExpr(callee, vis, isMainFun, argPats, body, next, nextTy, loc), nextTy, ctx

/// Returns in reversed order.
let private inferExprs ctx expectOpt exprs loc: HExpr list * Ty * TyCtx =
  let rec go acc (prevTy, prevLoc) ctx exprs =
    match exprs with
    | [] -> acc, prevTy, ctx

    | expr :: exprs ->
        let ctx = unifyTy ctx prevLoc prevTy tyUnit

        let expectOpt =
          if List.isEmpty exprs then expectOpt else None

        let expr, ty, ctx = inferExpr ctx expectOpt expr
        go (expr :: acc) (ty, exprToLoc expr) ctx exprs

  go [] (tyUnit, loc) ctx exprs

let private inferSemiExpr ctx expectOpt exprs loc =
  let exprs, ty, ctx = inferExprs ctx expectOpt exprs loc
  hxSemi (List.rev exprs) loc, ty, ctx

let private inferExpr (ctx: TyCtx) (expectOpt: Ty option) (expr: HExpr): HExpr * Ty * TyCtx =
  match expr with
  | HLitExpr (lit, _) -> expr, litToTy lit, ctx

  | HRefExpr (serial, _, loc) -> inferRefExpr ctx serial loc
  | HFunExpr (serial, _, loc) -> inferFunExpr ctx serial loc
  | HVariantExpr (serial, _, loc) -> inferVariantExpr ctx serial loc
  | HPrimExpr (prim, _, loc) -> inferPrimExpr ctx prim loc
  | HRecordExpr (baseOpt, fields, _, loc) -> inferRecordExpr ctx expectOpt baseOpt fields loc
  | HMatchExpr (cond, arms, _, loc) -> inferMatchExpr ctx expectOpt expr cond arms loc
  | HNavExpr (receiver, field, _, loc) -> inferNavExpr ctx receiver field loc
  | HInfExpr (InfOp.App, [ callee; arg ], _, loc) -> inferAppExpr ctx expr callee arg loc
  | HInfExpr (InfOp.Tuple, items, _, loc) -> inferTupleExpr ctx items loc
  | HInfExpr (InfOp.Anno, [ expr ], annoTy, loc) -> inferAnnoExpr ctx expr annoTy loc
  | HInfExpr (InfOp.Semi, exprs, _, loc) -> inferSemiExpr ctx expectOpt exprs loc
  | HLetValExpr (vis, pat, body, next, _, loc) -> inferLetValExpr ctx expectOpt vis pat body next loc

  | HLetFunExpr (oldSerial, vis, isMainFun, args, body, next, _, loc) ->
      inferLetFunExpr ctx expectOpt oldSerial vis isMainFun args body next loc

  | HTyDeclExpr _
  | HOpenExpr _ -> expr, tyUnit, ctx

  | HErrorExpr (error, loc) ->
      let ctx = addError ctx error loc
      hxAbort ctx loc

  | HInfExpr (InfOp.Anno, _, _, _)
  | HInfExpr (InfOp.App, _, _, _)
  | HInfExpr (InfOp.Closure, _, _, _)
  | HInfExpr (InfOp.CallProc, _, _, _)
  | HInfExpr (InfOp.CallTailRec, _, _, _)
  | HInfExpr (InfOp.CallClosure, _, _, _)
  | HInfExpr (InfOp.TupleItem _, _, _, _) -> failwith "NEVER"

  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

let infer (expr: HExpr, scopeCtx: ScopeCtx, errors): HExpr * TyCtx =
  let ctx: TyCtx =
    { Serial = scopeCtx.Serial
      Vars = scopeCtx.Vars
      Tys = scopeCtx.Tys
      TyDepths = scopeCtx.TyDepths
      LetDepth = 0
      TraitBounds = []
      Logs = [] }

  let ctx =
    errors
    |> List.fold (fun ctx (msg, loc) -> addError ctx msg loc) ctx

  // Assign type vars to var/fun definitions.
  let ctx =
    let vars, ctx =
      ctx.Vars
      |> mapFold (fun (acc, ctx: TyCtx) varSerial varDef ->
           let ctx =
             { ctx with
                 LetDepth = scopeCtx.VarDepths |> mapFind varSerial }

           let varDef, ctx =
             match varDef with
             | VarDef (ident, storageModifier, _, loc) ->
                 let ty, _, ctx = freshMetaTy ident loc ctx
                 VarDef(ident, storageModifier, ty, loc), ctx

             | FunDef (ident, arity, _, loc) ->
                 let ty, _, ctx = freshMetaTy ident loc ctx
                 FunDef(ident, arity, TyScheme([], ty), loc), ctx

             | VariantDef (ident, tySerial, hasPayload, payloadTy, _, loc) ->
                 // Pre-compute the type of variant.
                 let variantTy =
                   let unionTy = tyRef tySerial []
                   if hasPayload then tyFun payloadTy unionTy else unionTy

                 VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc), ctx

           let acc = acc |> mapAdd varSerial varDef

           acc, ctx) (mapEmpty intCmp, ctx)

    { ctx with Vars = vars }

  let ctx = { ctx with LetDepth = 0 }

  let expr, ctx =
    let expr, topLevelTy, ctx = inferExpr ctx None expr

    let ctx =
      unifyTy ctx (exprToLoc expr) topLevelTy tyUnit

    expr, ctx

  let ctx = ctx |> resolveTraitBounds

  // Substitute all types. Unbound types are degenerated here.
  let substOrDegenerate ty =
    ty
    |> substOrDegenerateTy ctx
    |> typingExpandSynonyms (toTyContext ctx)

  let expr = exprMap substOrDegenerate id expr

  let ctx =
    let vars =
      ctx.Vars
      |> mapMap (fun _ varDef ->
           match varDef with
           | VarDef (ident, storageModifier, ty, loc) ->
               let ty = substOrDegenerate ty
               VarDef(ident, storageModifier, ty, loc)

           | FunDef (ident, arity, TyScheme (args, ty), loc) ->
               let ty = substOrDegenerate ty
               FunDef(ident, arity, TyScheme(args, ty), loc)

           | VariantDef (ident, tySerial, hasPayload, payloadTy, ty, loc) ->
               let payloadTy = substOrDegenerate payloadTy
               let ty = substOrDegenerate ty
               VariantDef(ident, tySerial, hasPayload, payloadTy, ty, loc))

    { ctx with Vars = vars }

  let ctx =
    let tys =
      ctx.Tys
      |> mapFold (fun acc tySerial tyDef ->
           match tyDef with
           | MetaTyDef _ -> acc

           | SynonymTyDef (ident, tyArgs, bodyTy, loc) ->
               let bodyTy = bodyTy |> substOrDegenerate
               acc
               |> mapAdd tySerial (SynonymTyDef(ident, tyArgs, bodyTy, loc))

           | RecordTyDef (ident, fields, loc) ->
               let fields =
                 fields
                 |> List.map (fun (ident, ty, loc) ->
                      let ty = substOrDegenerate ty
                      ident, ty, loc)

               acc
               |> mapAdd tySerial (RecordTyDef(ident, fields, loc))

           | _ -> acc |> mapAdd tySerial tyDef) (mapEmpty intCmp)

    { ctx with Tys = tys }

  expr, ctx
