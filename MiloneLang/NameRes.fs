/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneLang.NameRes

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

let scopeMapEmpty () = mapEmpty (strHash, strCmp)

let scopeChainEmpty (): ScopeChain = [ scopeMapEmpty () ]

let scopeEmpty (): Scope = scopeChainEmpty (), scopeChainEmpty ()

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

let scopeCtxFromNameCtx (nameCtx: NameCtx): ScopeCtx =
  let (NameCtx (nameMap, serial)) = nameCtx
  let (localSerial as serial) = serial + 1

  ScopeCtx
    (serial,
     nameMap,
     mapEmpty (intHash, intCmp),
     mapEmpty (intHash, intCmp),
     mapEmpty (intHash, intCmp),
     mapEmpty (intHash, intCmp),
     nameTreeEmpty (),
     nameTreeEmpty (),
     localSerial,
     scopeEmpty (),
     0)

let scopeCtxGetIdent serial (scopeCtx: ScopeCtx): Ident =
  scopeCtx |> scopeCtxGetNameMap |> mapFind serial

let scopeCtxGetVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx
          |> scopeCtxGetVars
          |> mapContainsKey varSerial)
  scopeCtx |> scopeCtxGetVars |> mapFind varSerial

let scopeCtxGetTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx
          |> scopeCtxGetTys
          |> mapContainsKey tySerial)
  scopeCtx |> scopeCtxGetTys |> mapFind tySerial

let scopeCtxIsVariant varSerial scopeCtx =
  match scopeCtx |> scopeCtxGetVar varSerial with
  | VariantDef _ -> true

  | _ -> false

/// Defines a variable, without adding to any scope.
let scopeCtxDefineVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  // Merge into current definition.
  let varDef =
    match scopeCtx
          |> scopeCtxGetVars
          |> mapTryFind varSerial,
          varDef with
    | Some (VarDef (_, StaticSM, _, _)), VarDef (ident, _, ty, loc) -> VarDef(ident, StaticSM, ty, loc)
    | _ -> varDef

  scopeCtx
  |> scopeCtxWithVars
       (scopeCtx
        |> scopeCtxGetVars
        |> mapAdd varSerial varDef)
  |> scopeCtxWithVarDepths
       (scopeCtx
        |> scopeCtxGetVarDepths
        |> mapAdd varSerial (scopeCtx |> scopeCtxGetLetDepth))

/// Defines a type, without adding to any scope.
let scopeCtxDefineTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithTys
       (scopeCtx
        |> scopeCtxGetTys
        |> mapAdd tySerial tyDef)
  |> scopeCtxWithTyDepths
       (scopeCtx
        |> scopeCtxGetTyDepths
        |> mapAdd tySerial (scopeCtx |> scopeCtxGetLetDepth))

/// Defines an unbound meta type.
let scopeCtxDefineFreeTy tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithTyDepths
       (scopeCtx
        |> scopeCtxGetTyDepths
        |> mapAdd tySerial (scopeCtx |> scopeCtxGetLetDepth))

/// Adds a variable to a namespace.
let scopeCtxAddVarToNs tySerial varSerial (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithVarNs
       (scopeCtx
        |> scopeCtxGetVarNs
        |> nameTreeAdd tySerial varSerial)

/// Adds a type to a namespace.
let scopeCtxAddTyToNs parentTySerial tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithTyNs
       (scopeCtx
        |> scopeCtxGetTyNs
        |> nameTreeAdd parentTySerial tySerial)

/// Adds a variable to a scope.
let scopeCtxOpenVar varSerial (scopeCtx: ScopeCtx): ScopeCtx =
  let varIdent =
    scopeCtx
    |> scopeCtxGetVar varSerial
    |> varDefToIdent

  assert (varIdent <> "_")

  let scope: Scope =
    match scopeCtx |> scopeCtxGetLocal with
    | map :: varScopes, tyScopes ->
        let varScopes =
          (map |> mapAdd varIdent (varSerial, varIdent))
          :: varScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  scopeCtx |> scopeCtxWithLocal scope

/// Adds a type to a scope.
let scopeCtxOpenTy tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  let tyIdent =
    scopeCtx |> scopeCtxGetTy tySerial |> tyDefToIdent

  let scope: Scope =
    match scopeCtx |> scopeCtxGetLocal with
    | varScopes, map :: tyScopes ->
        let tyScopes =
          (map |> mapAdd tyIdent (tySerial, tyIdent))
          :: tyScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  scopeCtx |> scopeCtxWithLocal scope

let scopeCtxOpenModule moduleSerial scopeCtx =
  // Import vars.
  let scopeCtx =
    scopeCtx
    |> scopeCtxGetVarNs
    |> nameTreeTryFind moduleSerial
    |> List.fold (fun ctx varSerial -> ctx |> scopeCtxOpenVar varSerial) scopeCtx

  // Import tys.
  let scopeCtx =
    scopeCtx
    |> scopeCtxGetTyNs
    |> nameTreeTryFind moduleSerial
    |> List.fold (fun ctx tySerial -> ctx |> scopeCtxOpenTy tySerial) scopeCtx

  scopeCtx

/// Defines a variable in the local scope.
let scopeCtxDefineLocalVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineVar varSerial varDef
  |> scopeCtxOpenVar varSerial

/// Defines a type in the local scope.
let scopeCtxDefineLocalTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineTy tySerial tyDef
  |> scopeCtxOpenTy tySerial

/// Called on enter the body of let expressions.
let scopeCtxOnEnterLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithLetDepth ((scopeCtx |> scopeCtxGetLetDepth) + 1)

let scopeCtxOnLeaveLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithLetDepth ((scopeCtx |> scopeCtxGetLetDepth) - 1)

/// Starts a new scope.
let scopeCtxStartScope (scopeCtx: ScopeCtx): ScopeSerial * ScopeCtx =
  let parentSerial = scopeCtx |> scopeCtxGetLocalSerial

  let scopeCtx =
    let varScopes, tyScopes = scopeCtx |> scopeCtxGetLocal
    scopeCtx
    |> scopeCtxWithLocal (scopeMapEmpty () :: varScopes, scopeMapEmpty () :: tyScopes)

  parentSerial, scopeCtx

let scopeCtxFinishScope _parentSerial (scopeCtx: ScopeCtx): ScopeCtx =
  match scopeCtx |> scopeCtxGetLocal with
  | [], _
  | _, [] -> failwith "NEVER: Scope can't be empty."

  | _ :: varScopes, _ :: tyScopes ->
      scopeCtx
      |> scopeCtxWithLocal (varScopes, tyScopes)

let scopeCtxResolveVar scopeSerial ident (scopeCtx: ScopeCtx): VarSerial option =
  if scopeSerial = (scopeCtx |> scopeCtxGetLocalSerial) then
    // Find from local scope.
    let varScopes, _ = scopeCtx |> scopeCtxGetLocal
    match varScopes
          |> List.tryPick (fun map -> map |> mapTryFind ident) with
    | Some (varSerial, _) -> Some varSerial
    | None -> None

  else
    // Find from namespace.
    scopeCtx
    |> scopeCtxGetVarNs
    |> nameTreeTryFind scopeSerial
    |> List.tryFind (fun varSerial -> (scopeCtx |> scopeCtxGetIdent varSerial) = ident)

let scopeCtxResolveTyIdent scopeSerial ident (scopeCtx: ScopeCtx): TySerial option =
  if scopeSerial = (scopeCtx |> scopeCtxGetLocalSerial) then
    // Find from local scope.
    let _, tyScopes = scopeCtx |> scopeCtxGetLocal
    match tyScopes
          |> List.tryPick (fun map -> map |> mapTryFind ident) with
    | Some (tySerial, _) -> Some tySerial
    | None -> None

  else
    // Find from namespace.
    failwith "NEVER: Not used."

let scopeCtxResolveLocalVar ident (scopeCtx: ScopeCtx) =
  scopeCtx
  |> scopeCtxResolveVar (scopeCtx |> scopeCtxGetLocalSerial) ident

let scopeCtxResolveLocalTyIdent ident (scopeCtx: ScopeCtx) =
  scopeCtx
  |> scopeCtxResolveTyIdent (scopeCtx |> scopeCtxGetLocalSerial) ident

let scopeCtxResolvePatAsScope pat scopeCtx =
  match pat with
  | HNavPat _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HRefPat (serial, _, _) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ -> None

/// Resolves an expressions as scope: type, module or namespace.
let scopeCtxResolveExprAsScope expr scopeCtx =
  match expr with
  | HNavExpr _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HRefExpr (serial, _, _) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ -> None

/// Resolves type identifiers in a type expression.
let scopeCtxResolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | ErrorTy _ -> ty, scopeCtx

    | AppTy (RefTyCtor tySerial, []) when (scopeCtx |> scopeCtxGetIdent tySerial) = "_" ->
        // Handle wildcard type.
        let scopeCtx =
          scopeCtx |> scopeCtxDefineFreeTy tySerial

        MetaTy(tySerial, loc), scopeCtx

    | AppTy (RefTyCtor serial, tys) ->
        let ident = scopeCtx |> scopeCtxGetIdent serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go

        match scopeCtx |> scopeCtxResolveLocalTyIdent ident with
        | Some tySerial ->
            match scopeCtx |> scopeCtxGetTys |> mapTryFind tySerial with
            | Some (UniversalTyDef (_, tySerial, _)) -> MetaTy(tySerial, loc), scopeCtx

            | Some (SynonymTyDef (ident, defTyArgs, _, _)) when List.length defTyArgs <> List.length tys ->
                failwithf "synonym arity mismatch: %A" (tySerial, tys, ident, defTyArgs, loc)

            | _ -> tyRef tySerial tys, scopeCtx

        | None -> tyPrimFromIdent ident tys loc, scopeCtx

    | AppTy (tyCtor, tys) ->
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        AppTy(tyCtor, tys), scopeCtx

    | _ -> ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let scopeCtxDefineFunUniquely serial args ty loc (scopeCtx: ScopeCtx): ScopeCtx =
  let arity = args |> List.length
  let tyScheme = TyScheme([], ty)

  match scopeCtx |> scopeCtxGetVars |> mapTryFind serial with
  | Some (FunDef _) -> scopeCtx

  | Some _ -> failwith "NEVER"

  | None ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      let varDef = FunDef(ident, arity, tyScheme, loc)

      let scopeCtx =
        scopeCtx |> scopeCtxDefineLocalVar serial varDef

      scopeCtx

/// Defines a type based on a type declaration.
///
/// - This is idempotent. Duplicated calls are just ignored.
/// - You need call `scopeCtxDefineTyFinish` to complete the task.
/// - This doesn't resolve inner type expressions
///   because some type declarations are still unseen.
let scopeCtxDefineTyStart moduleSerialOpt tySerial vis tyArgs tyDecl loc ctx =
  let addVarToModule varSerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> scopeCtxAddVarToNs moduleSerial varSerial

    | _ -> ctx

  let addTyToModule tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> scopeCtxAddTyToNs moduleSerial tySerial

    | _ -> ctx

  let tyIdent = ctx |> scopeCtxGetIdent tySerial

  if ctx |> scopeCtxGetTys |> mapContainsKey tySerial then
    ctx
  else

    match tyDecl with
    | TySynonymDecl (body, _) ->
        ctx
        |> scopeCtxDefineLocalTy tySerial (SynonymTyDef(tyIdent, tyArgs, body, loc))
        |> addTyToModule tySerial

    | UnionTyDecl (_, variants, _unionLoc) ->
        let defineVariant ctx (variantIdent, variantSerial, hasPayload, payloadTy) =
          let varDef =
            VariantDef(variantIdent, tySerial, hasPayload, payloadTy, noTy, loc)

          ctx
          |> scopeCtxDefineVar variantSerial varDef
          |> scopeCtxAddVarToNs tySerial variantSerial
          |> scopeCtxOpenVar variantSerial
          |> addVarToModule variantSerial

        let ctx = variants |> List.fold defineVariant ctx

        let tyDef =
          let variantSerials =
            variants
            |> List.map (fun (_, variantSerial, _, _) -> variantSerial)

          UnionTyDef(tyIdent, variantSerials, loc)

        ctx
        |> scopeCtxDefineLocalTy tySerial tyDef
        |> addTyToModule tySerial

    | RecordTyDecl (ident, fields, loc) ->
        let tyDef = RecordTyDef(ident, fields, loc)

        ctx
        |> scopeCtxDefineLocalTy tySerial tyDef
        |> addTyToModule tySerial

/// Completes the type definition.
///
/// - No need to call `scopeCtxDefineTyStart` first.
/// - This resolves inner type expressions.
let scopeCtxDefineTyFinish tySerial tyArgs tyDecl loc ctx =
  let ctx =
    // Pass in PrivateVis because if this type is not pre-declared here, it's local to function.
    ctx
    |> scopeCtxDefineTyStart None tySerial PrivateVis tyArgs tyDecl loc

  let tyDef = ctx |> scopeCtxGetTy tySerial

  match tyDef with
  | MetaTyDef (tyIdent, bodyTy, loc) ->
      let bodyTy, ctx = ctx |> scopeCtxResolveTy bodyTy loc
      ctx
      |> scopeCtxDefineTy tySerial (MetaTyDef(tyIdent, bodyTy, loc))

  | UniversalTyDef _ -> ctx

  | SynonymTyDef (tyIdent, tyArgs, bodyTy, loc) ->
      let parent, ctx = ctx |> scopeCtxStartScope

      let ctx =
        tyArgs
        |> List.fold (fun ctx tyArg ->
             let ident = ctx |> scopeCtxGetIdent tyArg
             ctx
             |> scopeCtxDefineLocalTy tyArg (UniversalTyDef(ident, tyArg, loc))) ctx

      let bodyTy, ctx = ctx |> scopeCtxResolveTy bodyTy loc
      let ctx = ctx |> scopeCtxFinishScope parent

      ctx
      |> scopeCtxDefineTy tySerial (SynonymTyDef(tyIdent, tyArgs, bodyTy, loc))

  | UnionTyDef (_, variantSerials, _unionLoc) ->
      let go ctx variantSerial =
        match ctx |> scopeCtxGetVar variantSerial with
        | VariantDef (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
            let payloadTy, ctx = ctx |> scopeCtxResolveTy payloadTy loc
            let variantTy, ctx = ctx |> scopeCtxResolveTy variantTy loc

            let varDef =
              VariantDef(ident, tySerial, hasPayload, payloadTy, variantTy, loc)

            ctx |> scopeCtxDefineVar variantSerial varDef
        | _ -> failwith "NEVER: it must be variant"

      variantSerials |> List.fold go ctx

  | RecordTyDef (ident, fields, loc) ->
      let resolveField ((ident, ty, loc), ctx) =
        let ty, ctx = ctx |> scopeCtxResolveTy ty loc
        (ident, ty, loc), ctx

      let fields, ctx = (fields, ctx) |> stMap resolveField
      ctx
      |> scopeCtxDefineTy tySerial (RecordTyDef(ident, fields, loc))

  | ModuleTyDef _ -> failwith "NEVER: no use case"

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// This stage, traverse declarations directly inside `module rec`s
// to create variables/types pre-definitions
// so that mutually recursive references resolve correctly.

let nameResCollectDecls moduleSerialOpt (expr, ctx) =
  let addVarToModule vis varSerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> scopeCtxAddVarToNs moduleSerial varSerial

    | _ -> ctx

  let rec goPat vis (pat, ctx) =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HNavPat _
    | HNilPat _
    | HNonePat _
    | HSomePat _ -> pat, ctx

    | HOrPat _ ->
        // NOTE: OR patterns doesn't appear because not entering `match` arms.
        assert false
        pat, ctx

    | HRefPat (serial, ty, loc) ->
        let ident = ctx |> scopeCtxGetIdent serial
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some varSerial when ctx |> scopeCtxIsVariant varSerial -> HRefPat(varSerial, ty, loc), ctx
        | _ ->
            let ctx =
              ctx
              |> scopeCtxDefineLocalVar serial (VarDef(ident, StaticSM, ty, loc))
              |> addVarToModule vis serial

            pat, ctx

    | HCallPat (callee, args, ty, loc) ->
        let args, ctx = (args, ctx) |> stMap (goPat vis)
        HCallPat(callee, args, ty, loc), ctx

    | HConsPat (l, r, ty, loc) ->
        let l, ctx = (l, ctx) |> goPat vis
        let r, ctx = (r, ctx) |> goPat vis
        HConsPat(l, r, ty, loc), ctx

    | HTuplePat (items, ty, loc) ->
        let items, ctx = (items, ctx) |> stMap (goPat vis)
        HTuplePat(items, ty, loc), ctx

    | HAsPat (pat, serial, loc) ->
        let ident = ctx |> scopeCtxGetIdent serial

        let ctx =
          ctx
          |> scopeCtxDefineLocalVar serial (VarDef(ident, StaticSM, noTy, loc))

        let pat, ctx = (pat, ctx) |> goPat vis
        HAsPat(pat, serial, loc), ctx

    | HAnnoPat (pat, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        HAnnoPat(pat, ty, loc), ctx

    | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

  let rec goExpr (expr, ctx) =
    match expr with
    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        let next, ctx = (next, ctx) |> goExpr
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

    | HLetFunExpr (serial, vis, _, args, body, next, ty, loc) ->
        let isMainFun = ctx |> scopeCtxGetIdent serial = "main"

        let ctx =
          ctx
          |> scopeCtxOnEnterLetBody
          |> scopeCtxDefineFunUniquely serial args noTy loc
          |> scopeCtxOnLeaveLetBody
          |> addVarToModule vis serial

        let next, ctx = (next, ctx) |> goExpr
        HLetFunExpr(serial, vis, isMainFun, args, body, next, ty, loc), ctx

    | HInfExpr (InfOp.Semi, exprs, ty, loc) ->
        let exprs, ctx = (exprs, ctx) |> stMap goExpr
        HInfExpr(InfOp.Semi, exprs, ty, loc), ctx

    | HTyDeclExpr (serial, vis, tyArgs, tyDecl, loc) ->
        let ctx =
          ctx
          |> scopeCtxDefineTyStart moduleSerialOpt serial vis tyArgs tyDecl loc

        HTyDeclExpr(serial, vis, tyArgs, tyDecl, loc), ctx

    | _ -> expr, ctx

  goExpr (expr, ctx)

// -----------------------------------------------
// Name Resolution
// -----------------------------------------------

let nameResPat (pat: HPat, ctx: ScopeCtx) =
  match pat with
  | HLitPat _
  | HDiscardPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _ -> pat, ctx

  | HRefPat (varSerial, ty, loc) when ctx |> scopeCtxGetIdent varSerial = "_" -> HDiscardPat(ty, loc), ctx

  | HRefPat (varSerial, ty, loc) ->
      let ident = ctx |> scopeCtxGetIdent varSerial

      let variantSerial =
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some varSerial ->
            match ctx |> scopeCtxGetVar varSerial with
            | VariantDef _ -> Some varSerial

            | _ -> None

        | None -> None

      match variantSerial with
      | Some variantSerial -> HRefPat(variantSerial, ty, loc), ctx

      | None ->
          match ident with
          | "None" -> HNonePat(ty, loc), ctx

          | "Some" -> HSomePat(ty, loc), ctx

          | _ ->
              let varDef = VarDef(ident, AutoSM, ty, loc)

              let ctx =
                ctx |> scopeCtxDefineLocalVar varSerial varDef

              HRefPat(varSerial, ty, loc), ctx

  | HNavPat (l, r, ty, loc) ->
      let varSerial =
        match ctx |> scopeCtxResolvePatAsScope l with
        | Some scopeSerial -> ctx |> scopeCtxResolveVar scopeSerial r

        | None -> None

      match varSerial with
      | Some varSerial -> HRefPat(varSerial, ty, loc), ctx

      | None ->
          let l, ctx = (l, ctx) |> nameResPat
          HNavPat(l, r, ty, loc), ctx

  | HCallPat (callee, args, ty, loc) ->
      let callee, ctx = (callee, ctx) |> nameResPat
      let args, ctx = (args, ctx) |> stMap nameResPat
      HCallPat(callee, args, ty, loc), ctx

  | HConsPat (l, r, itemTy, loc) ->
      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HConsPat(l, r, itemTy, loc), ctx

  | HTuplePat (pats, tupleTy, loc) ->
      let pats, ctx = (pats, ctx) |> stMap nameResPat
      HTuplePat(pats, tupleTy, loc), ctx

  | HAsPat (pat, serial, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial

      let varDef = VarDef(ident, AutoSM, noTy, loc)

      let ctx =
        ctx |> scopeCtxDefineLocalVar serial varDef

      let pat, ctx = (pat, ctx) |> nameResPat
      HAsPat(pat, serial, loc), ctx

  | HAnnoPat (pat, ty, loc) ->
      let ty, ctx = ctx |> scopeCtxResolveTy ty loc
      let pat, ctx = (pat, ctx) |> nameResPat
      HAnnoPat(pat, ty, loc), ctx

  | HOrPat (l, r, ty, loc) ->
      // FIXME: Currently variable bindings in OR patterns are not supported correctly.
      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HOrPat(l, r, ty, loc), ctx

  | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

let nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
  | HErrorExpr _
  | HLitExpr _
  | HPrimExpr _ -> expr, ctx

  | HRefExpr (serial, ty, loc) ->
      let doArm () =
        let ident = ctx |> scopeCtxGetIdent serial
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some serial -> HRefExpr(serial, ty, loc), ctx

        | None ->
            match primFromIdent ident with
            | Some prim -> HPrimExpr(prim, ty, loc), ctx

            | None -> HErrorExpr("Undefined variable " + ident, loc), ctx

      doArm ()

  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        let baseOpt, ctx =
          (baseOpt, ctx) |> stOptionMap nameResExpr

        let fields, ctx =
          (fields, ctx)
          |> stMap (fun ((ident, init, loc), ctx) ->
               let init, ctx = (init, ctx) |> nameResExpr
               (ident, init, loc), ctx)

        HRecordExpr(baseOpt, fields, ty, loc), ctx

      doArm ()

  | HMatchExpr (target, arms, ty, loc) ->
      let doArm () =
        let target, ctx = (target, ctx) |> nameResExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap (fun ((pat, guard, body), ctx) ->
               let parent, ctx = ctx |> scopeCtxStartScope
               let pat, ctx = (pat, ctx) |> nameResPat
               let guard, ctx = (guard, ctx) |> nameResExpr
               let body, ctx = (body, ctx) |> nameResExpr
               let ctx = ctx |> scopeCtxFinishScope parent
               (pat, guard, body), ctx)

        HMatchExpr(target, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        // FIXME: Patchwork for tests to pass
        match l, r with
        | HRefExpr (serial, _, _), "getSlice" when ctx |> scopeCtxGetIdent serial = "String" ->
            // NOTE: Actually this functions doesn't exist in the F# standard library.
            HPrimExpr(HPrim.StrGetSlice, ty, loc), ctx

        | _ ->

            // Keep the nav expression unresolved so that type inference does.
            let keepUnresolved () =
              let l, ctx = (l, ctx) |> nameResExpr
              HNavExpr(l, r, ty, loc), ctx

            match ctx |> scopeCtxResolveExprAsScope l with
            | Some scopeSerial ->
                match ctx |> scopeCtxResolveVar scopeSerial r with
                | Some varSerial -> HRefExpr(varSerial, ty, loc), ctx

                | _ ->
                    // X.ty patterns don't appear yet, so don't search for types.

                    keepUnresolved ()

            | _ -> keepUnresolved ()

      doArm ()

  | HInfExpr (op, items, ty, loc) ->
      let doArm () =
        // Necessary in case of annotation expression.
        let ty, ctx = ctx |> scopeCtxResolveTy ty loc

        let items, ctx = (items, ctx) |> stMap nameResExpr
        HInfExpr(op, items, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let body, ctx =
          let parent, ctx = ctx |> scopeCtxStartScope
          let body, ctx = (body, ctx) |> nameResExpr
          let ctx = ctx |> scopeCtxFinishScope parent
          body, ctx

        let pat, next, ctx =
          let parent, ctx = ctx |> scopeCtxStartScope
          let pat, ctx = (pat, ctx) |> nameResPat
          let next, ctx = (next, ctx) |> nameResExpr
          let ctx = ctx |> scopeCtxFinishScope parent
          pat, next, ctx

        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (serial, vis, isMainFun, pats, body, next, ty, loc) ->
      let doArm () =
        let parent, ctx = ctx |> scopeCtxStartScope
        let ctx = ctx |> scopeCtxOnEnterLetBody

        // Define the function itself for recursive referencing.
        // FIXME: Functions are recursive even if `rec` is missing.
        let ctx =
          ctx
          |> scopeCtxDefineFunUniquely serial pats noTy loc

        let pats, body, ctx =
          // Introduce a function body scope.
          let parent, ctx = ctx |> scopeCtxStartScope
          let pats, ctx = (pats, ctx) |> stMap nameResPat
          let body, ctx = (body, ctx) |> nameResExpr
          let ctx = ctx |> scopeCtxFinishScope parent
          pats, body, ctx

        let ctx = ctx |> scopeCtxOnLeaveLetBody
        let next, ctx = (next, ctx) |> nameResExpr
        let ctx = ctx |> scopeCtxFinishScope parent

        HLetFunExpr(serial, vis, isMainFun, pats, body, next, ty, loc), ctx

      doArm ()

  | HTyDeclExpr (serial, _, tyArgs, tyDecl, loc) ->
      let doArm () =
        let ctx =
          ctx
          |> scopeCtxDefineTyFinish serial tyArgs tyDecl loc

        expr, ctx

      doArm ()

  | HOpenExpr (path, _) ->
      let doArm () =
        // FIXME: resolve module-name based on path
        match ctx
              |> scopeCtxResolveLocalTyIdent (path |> List.last) with
        | Some moduleSerial ->
            let ctx = ctx |> scopeCtxOpenModule moduleSerial

            expr, ctx

        | None -> expr, ctx

      doArm ()

  | HModuleExpr (serial, body, next, loc) ->
      let doArm () =
        let ident = ctx |> scopeCtxGetIdent serial

        let ctx =
          ctx
          |> scopeCtxDefineTy serial (ModuleTyDef(ident, loc))
          |> scopeCtxOpenTy serial

        let parent, ctx = ctx |> scopeCtxStartScope

        let body, ctx =
          (body, ctx)
          |> nameResCollectDecls (Some serial)
          |> nameResExpr

        let ctx = ctx |> scopeCtxFinishScope parent

        // HACK: Polyfills is auto-open.
        let ctx =
          if ident = "Polyfills" then ctx |> scopeCtxOpenModule serial else ctx

        let next, ctx = (next, ctx) |> nameResExpr

        // Module no longer needed.
        Bundling.spliceExpr body next, ctx

      doArm ()

let nameRes (expr: HExpr, nameCtx: NameCtx): HExpr * ScopeCtx =
  let scopeCtx = scopeCtxFromNameCtx nameCtx

  match expr with
  | HModuleExpr _ -> (expr, scopeCtx) |> nameResExpr

  | _ ->
      (expr, scopeCtx)
      |> nameResCollectDecls None
      |> nameResExpr
