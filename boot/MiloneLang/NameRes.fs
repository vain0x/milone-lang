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
  | VarDef.Variant _ -> true

  | _ -> false

let scopeCtxIsMetaTy tySerial scopeCtx =
  match scopeCtx |> scopeCtxGetTy tySerial with
  | TyDef.Meta _ -> true

  | _ -> false

/// Defines a variable, without adding to any scope.
let scopeCtxDefineVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  // Merge into current definition.
  let varDef =
    match scopeCtx
          |> scopeCtxGetVars
          |> mapTryFind varSerial,
          varDef with
    | Some (VarDef.Var (_, StorageModifier.Static, _, _)), VarDef.Var (ident, _, ty, loc) ->
        VarDef.Var(ident, StorageModifier.Static, ty, loc)
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
    |> listFold (fun ctx varSerial -> ctx |> scopeCtxOpenVar varSerial) scopeCtx

  // Import tys.
  let scopeCtx =
    scopeCtx
    |> scopeCtxGetTyNs
    |> nameTreeTryFind moduleSerial
    |> listFold (fun ctx tySerial -> ctx |> scopeCtxOpenTy tySerial) scopeCtx

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
          |> listTryPick (fun map -> map |> mapTryFind ident) with
    | Some (varSerial, _) -> Some varSerial
    | None -> None

  else
    // Find from namespace.
    scopeCtx
    |> scopeCtxGetVarNs
    |> nameTreeTryFind scopeSerial
    |> listTryFind (fun varSerial -> (scopeCtx |> scopeCtxGetIdent varSerial) = ident)

let scopeCtxResolveTyIdent scopeSerial ident (scopeCtx: ScopeCtx): TySerial option =
  if scopeSerial = (scopeCtx |> scopeCtxGetLocalSerial) then
    // Find from local scope.
    let _, tyScopes = scopeCtx |> scopeCtxGetLocal
    match tyScopes
          |> listTryPick (fun map -> map |> mapTryFind ident) with
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
  | HPat.Nav _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HPat.Ref (serial, _, _) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ -> None

/// Resolves an expressions as scope: type, module or namespace.
let scopeCtxResolveExprAsScope expr scopeCtx =
  match expr with
  | HExpr.Nav _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HExpr.Ref (serial, _, _) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ -> None

/// Resolves type identifiers in a type expression.
let scopeCtxResolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | Ty.Error _ -> ty, scopeCtx

    | Ty.Con (TyCon.Ref tySerial, []) when (scopeCtx |> scopeCtxGetIdent tySerial) = "_" ->
        // Handle wildcard type.
        let scopeCtx =
          scopeCtx |> scopeCtxDefineFreeTy tySerial

        Ty.Meta(tySerial, loc), scopeCtx

    | Ty.Con (TyCon.Ref serial, tys) ->
        let ident = scopeCtx |> scopeCtxGetIdent serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go

        match scopeCtx |> scopeCtxResolveLocalTyIdent ident with
        | Some tySerial when scopeCtx |> scopeCtxIsMetaTy tySerial ->
            // In the case of type synonyms.
            Ty.Meta(tySerial, loc), scopeCtx

        | Some tySerial -> tyRef tySerial tys, scopeCtx

        | None -> tyPrimFromIdent ident tys loc, scopeCtx

    | Ty.Con (tyCon, tys) ->
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        Ty.Con(tyCon, tys), scopeCtx

    | _ -> ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let scopeCtxDefineFunUniquely serial args ty loc (scopeCtx: ScopeCtx): ScopeCtx =
  let arity = args |> listLength
  let tyScheme = TyScheme.ForAll([], ty)

  match scopeCtx |> scopeCtxGetVars |> mapTryFind serial with
  | Some (VarDef.Fun _) -> scopeCtx

  | Some _ -> failwith "NEVER"

  | None ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      let varDef = VarDef.Fun(ident, arity, tyScheme, loc)

      let scopeCtx =
        scopeCtx |> scopeCtxDefineLocalVar serial varDef

      scopeCtx

/// Defines a type based on a type declaration.
///
/// - This is idempotent. Duplicated calls are just ignored.
/// - You need call `scopeCtxDefineTyFinish` to complete the task.
/// - This doesn't resolve inner type expressions
///   because some type declarations are still unseen.
let scopeCtxDefineTyStart moduleSerialOpt tySerial vis tyDecl loc ctx =
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
    | TyDecl.Synonym (body, _synonymLoc) ->
        ctx
        |> scopeCtxDefineLocalTy tySerial (TyDef.Meta(tyIdent, body, loc))

    | TyDecl.Union (_, variants, _unionLoc) ->
        let defineVariant ctx (variantIdent, variantSerial, hasPayload, payloadTy) =
          let varDef =
            VarDef.Variant(variantIdent, tySerial, hasPayload, payloadTy, noTy, loc)

          ctx
          |> scopeCtxDefineVar variantSerial varDef
          |> scopeCtxAddVarToNs tySerial variantSerial
          |> scopeCtxOpenVar variantSerial
          |> addVarToModule variantSerial

        let ctx = variants |> listFold defineVariant ctx

        let tyDef =
          let variantSerials =
            variants
            |> listMap (fun (_, variantSerial, _, _) -> variantSerial)

          TyDef.Union(tyIdent, variantSerials, loc)

        ctx
        |> scopeCtxDefineLocalTy tySerial tyDef
        |> addTyToModule tySerial

/// Completes the type definition.
///
/// - No need to call `scopeCtxDefineTyStart` first.
/// - This resolves inner type expressions.
let scopeCtxDefineTyFinish tySerial tyDecl loc ctx =
  let ctx =
    // Pass in PrivateVis because if this type is not pre-declared here, it's local to function.
    ctx
    |> scopeCtxDefineTyStart None tySerial PrivateVis tyDecl loc

  let tyDef = ctx |> scopeCtxGetTy tySerial

  match tyDef with
  | TyDef.Meta (tyIdent, bodyTy, loc) ->
      let bodyTy, ctx = ctx |> scopeCtxResolveTy bodyTy loc
      ctx
      |> scopeCtxDefineTy tySerial (TyDef.Meta(tyIdent, bodyTy, loc))

  | TyDef.Union (_, variantSerials, _unionLoc) ->
      let rec go ctx variantSerial =
        match ctx |> scopeCtxGetVar variantSerial with
        | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
            let payloadTy, ctx = ctx |> scopeCtxResolveTy payloadTy loc
            let variantTy, ctx = ctx |> scopeCtxResolveTy variantTy loc

            let varDef =
              VarDef.Variant(ident, tySerial, hasPayload, payloadTy, variantTy, loc)

            ctx |> scopeCtxDefineVar variantSerial varDef
        | _ -> failwith "NEVER: it must be variant"

      variantSerials |> listFold go ctx

  | TyDef.Module _ -> failwith "NEVER: no use case"

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
    | HPat.Lit _
    | HPat.Discard _
    | HPat.Nav _
    | HPat.Nil _
    | HPat.OptionNone _
    | HPat.OptionSome _ -> pat, ctx

    | HPat.Or _ ->
        // NOTE: OR patterns doesn't appear because not entering `match` arms.
        assert false
        pat, ctx

    | HPat.Ref (serial, ty, loc) ->
        let ident = ctx |> scopeCtxGetIdent serial
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some varSerial when ctx |> scopeCtxIsVariant varSerial -> HPat.Ref(varSerial, ty, loc), ctx
        | _ ->
            let ctx =
              ctx
              |> scopeCtxDefineLocalVar serial (VarDef.Var(ident, StorageModifier.Static, ty, loc))
              |> addVarToModule vis serial

            pat, ctx

    | HPat.Call (callee, args, ty, loc) ->
        let args, ctx = (args, ctx) |> stMap (goPat vis)
        HPat.Call(callee, args, ty, loc), ctx

    | HPat.Cons (l, r, ty, loc) ->
        let l, ctx = (l, ctx) |> goPat vis
        let r, ctx = (r, ctx) |> goPat vis
        HPat.Cons(l, r, ty, loc), ctx

    | HPat.Tuple (items, ty, loc) ->
        let items, ctx = (items, ctx) |> stMap (goPat vis)
        HPat.Tuple(items, ty, loc), ctx

    | HPat.As (pat, serial, loc) ->
        let ident = ctx |> scopeCtxGetIdent serial

        let ctx =
          ctx
          |> scopeCtxDefineLocalVar serial (VarDef.Var(ident, StorageModifier.Static, noTy, loc))

        let pat, ctx = (pat, ctx) |> goPat vis
        HPat.As(pat, serial, loc), ctx

    | HPat.Anno (pat, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        HPat.Anno(pat, ty, loc), ctx

  let rec goExpr (expr, ctx) =
    match expr with
    | HExpr.Let (vis, pat, init, next, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        let next, ctx = (next, ctx) |> goExpr
        HExpr.Let(vis, pat, init, next, ty, loc), ctx

    | HExpr.LetFun (serial, vis, _, args, body, next, ty, loc) ->
        let isMainFun = ctx |> scopeCtxGetIdent serial = "main"

        let ctx =
          ctx
          |> scopeCtxOnEnterLetBody
          |> scopeCtxDefineFunUniquely serial args noTy loc
          |> scopeCtxOnLeaveLetBody
          |> addVarToModule vis serial

        let next, ctx = (next, ctx) |> goExpr
        HExpr.LetFun(serial, vis, isMainFun, args, body, next, ty, loc), ctx

    | HExpr.Inf (InfOp.Semi, exprs, ty, loc) ->
        let exprs, ctx = (exprs, ctx) |> stMap goExpr
        HExpr.Inf(InfOp.Semi, exprs, ty, loc), ctx

    | HExpr.TyDecl (serial, vis, tyDecl, loc) ->
        let ctx =
          ctx
          |> scopeCtxDefineTyStart moduleSerialOpt serial vis tyDecl loc

        HExpr.TyDecl(serial, vis, tyDecl, loc), ctx

    | _ -> expr, ctx

  goExpr (expr, ctx)

// -----------------------------------------------
// Name Resolution
// -----------------------------------------------

let nameResPat (pat: HPat, ctx: ScopeCtx) =
  match pat with
  | HPat.Lit _
  | HPat.Discard _
  | HPat.Nil _
  | HPat.OptionNone _
  | HPat.OptionSome _ -> pat, ctx

  | HPat.Ref (varSerial, ty, loc) when ctx |> scopeCtxGetIdent varSerial = "_" -> HPat.Discard(ty, loc), ctx

  | HPat.Ref (varSerial, ty, loc) ->
      let ident = ctx |> scopeCtxGetIdent varSerial

      let variantSerial =
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some varSerial ->
            match ctx |> scopeCtxGetVar varSerial with
            | VarDef.Variant _ -> Some varSerial

            | _ -> None

        | None -> None

      match variantSerial with
      | Some variantSerial -> HPat.Ref(variantSerial, ty, loc), ctx

      | None ->
          match ident with
          | "None" -> HPat.OptionNone(ty, loc), ctx

          | "Some" -> HPat.OptionSome(ty, loc), ctx

          | _ ->
              let varDef =
                VarDef.Var(ident, StorageModifier.Auto, ty, loc)

              let ctx =
                ctx |> scopeCtxDefineLocalVar varSerial varDef

              HPat.Ref(varSerial, ty, loc), ctx

  | HPat.Nav (l, r, ty, loc) ->
      let varSerial =
        match ctx |> scopeCtxResolvePatAsScope l with
        | Some scopeSerial -> ctx |> scopeCtxResolveVar scopeSerial r

        | None -> None

      match varSerial with
      | Some varSerial -> HPat.Ref(varSerial, ty, loc), ctx

      | None ->
          let l, ctx = (l, ctx) |> nameResPat
          HPat.Nav(l, r, ty, loc), ctx

  | HPat.Call (callee, args, ty, loc) ->
      let callee, ctx = (callee, ctx) |> nameResPat
      let args, ctx = (args, ctx) |> stMap nameResPat
      HPat.Call(callee, args, ty, loc), ctx

  | HPat.Cons (l, r, itemTy, loc) ->
      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HPat.Cons(l, r, itemTy, loc), ctx

  | HPat.Tuple (pats, tupleTy, loc) ->
      let pats, ctx = (pats, ctx) |> stMap nameResPat
      HPat.Tuple(pats, tupleTy, loc), ctx

  | HPat.As (pat, serial, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial

      let varDef =
        VarDef.Var(ident, StorageModifier.Auto, noTy, loc)

      let ctx =
        ctx |> scopeCtxDefineLocalVar serial varDef

      let pat, ctx = (pat, ctx) |> nameResPat
      HPat.As(pat, serial, loc), ctx

  | HPat.Anno (pat, ty, loc) ->
      let ty, ctx = ctx |> scopeCtxResolveTy ty loc
      let pat, ctx = (pat, ctx) |> nameResPat
      HPat.Anno(pat, ty, loc), ctx

  | HPat.Or (l, r, ty, loc) ->
      // FIXME: Currently variable bindings in OR patterns are not supported correctly.
      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HPat.Or(l, r, ty, loc), ctx

let nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
  | HExpr.Error _
  | HExpr.Lit _
  | HExpr.Prim _ -> expr, ctx

  | HExpr.Ref (serial, ty, loc) ->
      let doArm () =
        let ident = ctx |> scopeCtxGetIdent serial
        match ctx |> scopeCtxResolveLocalVar ident with
        | Some serial -> HExpr.Ref(serial, ty, loc), ctx

        | None ->
            match primFromIdent ident with
            | Some prim -> HExpr.Prim(prim, ty, loc), ctx

            | None -> HExpr.Error("Undefined variable " + ident, loc), ctx

      doArm ()

  | HExpr.Match (target, arms, ty, loc) ->
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

        HExpr.Match(target, arms, ty, loc), ctx

      doArm ()

  | HExpr.Nav (l, r, ty, loc) ->
      let doArm () =
        // FIXME: Patchwork for tests to pass
        match l, r with
        | HExpr.Ref (serial, _, _), "getSlice" when ctx |> scopeCtxGetIdent serial = "String" ->
            // NOTE: Actually this functions doesn't exist in the F# standard library.
            HExpr.Prim(HPrim.StrGetSlice, ty, loc), ctx

        | _ ->

            // Keep the nav expression unresolved so that type inference does.
            let keepUnresolved () =
              let l, ctx = (l, ctx) |> nameResExpr
              HExpr.Nav(l, r, ty, loc), ctx

            match ctx |> scopeCtxResolveExprAsScope l with
            | Some scopeSerial ->
                match ctx |> scopeCtxResolveVar scopeSerial r with
                | Some varSerial -> HExpr.Ref(varSerial, ty, loc), ctx

                | _ ->
                    // X.ty patterns don't appear yet, so don't search for types.

                    keepUnresolved ()

            | _ -> keepUnresolved ()

      doArm ()

  | HExpr.Inf (op, items, ty, loc) ->
      let doArm () =
        // Necessary in case of annotation expression.
        let ty, ctx = ctx |> scopeCtxResolveTy ty loc

        let items, ctx = (items, ctx) |> stMap nameResExpr
        HExpr.Inf(op, items, ty, loc), ctx

      doArm ()

  | HExpr.Let (vis, pat, body, next, ty, loc) ->
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

        HExpr.Let(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HExpr.LetFun (serial, vis, isMainFun, pats, body, next, ty, loc) ->
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

        HExpr.LetFun(serial, vis, isMainFun, pats, body, next, ty, loc), ctx

      doArm ()

  | HExpr.TyDecl (serial, _, tyDecl, loc) ->
      let doArm () =
        let ctx =
          ctx |> scopeCtxDefineTyFinish serial tyDecl loc

        expr, ctx

      doArm ()

  | HExpr.Open (path, _) ->
      let doArm () =
        // FIXME: resolve module-name based on path
        match ctx
              |> scopeCtxResolveLocalTyIdent (path |> listLast) with
        | Some moduleSerial ->
            let ctx = ctx |> scopeCtxOpenModule moduleSerial

            expr, ctx

        | None -> expr, ctx

      doArm ()

  | HExpr.Module (serial, body, next, loc) ->
      let doArm () =
        let ident = ctx |> scopeCtxGetIdent serial

        let ctx =
          ctx
          |> scopeCtxDefineTy serial (TyDef.Module(ident, loc))
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
  | HExpr.Module _ -> (expr, scopeCtx) |> nameResExpr

  | _ ->
      (expr, scopeCtx)
      |> nameResCollectDecls None
      |> nameResExpr
