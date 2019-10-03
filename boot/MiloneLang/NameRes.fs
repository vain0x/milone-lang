/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneLang.NameRes

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Records

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

let scopeCtxFromNameCtx (nameCtx: NameCtx): ScopeCtx =
  let (NameCtx (nameMap, serial)) = nameCtx
  let (localSerial as serial) = serial + 1

  ScopeCtx (
    serial,
    nameMap,
    mapEmpty (intHash, intCmp),
    mapEmpty (intHash, intCmp),
    mapEmpty (intHash, intCmp),
    mapEmpty (intHash, intCmp),
    localSerial,
    [],
    0
  )

let scopeCtxGetIdent serial (scopeCtx: ScopeCtx): Ident =
  scopeCtx |> scopeCtxGetNameMap |> mapFind serial

let scopeCtxGetVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx |> scopeCtxGetVars |> mapContainsKey varSerial)
  scopeCtx |> scopeCtxGetVars |> mapFind varSerial

let scopeCtxGetTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx |> scopeCtxGetTys |> mapContainsKey tySerial)
  scopeCtx |> scopeCtxGetTys |> mapFind tySerial

let scopeCtxIsVariant varSerial scopeCtx =
  match scopeCtx |> scopeCtxGetVar varSerial with
  | VarDef.Variant _ ->
    true

  | _ ->
    false

let scopeCtxIsMetaTy tySerial scopeCtx =
  match scopeCtx |> scopeCtxGetTy tySerial with
  | TyDef.Meta _ ->
    true

  | _ ->
    false

/// Defines a variable, without adding to any scope.
let scopeCtxDefineVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithVars (scopeCtx |> scopeCtxGetVars |> mapAdd varSerial varDef)
  |> scopeCtxWithVarDepths (scopeCtx |> scopeCtxGetVarDepths |> mapAdd varSerial (scopeCtx |> scopeCtxGetLetDepth))

/// Defines a type, without adding to any scope.
let scopeCtxDefineTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithTys (scopeCtx |> scopeCtxGetTys |> mapAdd tySerial tyDef)
  |> scopeCtxWithTyDepths (scopeCtx |> scopeCtxGetTyDepths |> mapAdd tySerial (scopeCtx |> scopeCtxGetLetDepth))

/// Defines an unbound meta type.
let scopeCtxDefineFreeTy tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithTyDepths (scopeCtx |> scopeCtxGetTyDepths |> mapAdd tySerial (scopeCtx |> scopeCtxGetLetDepth))

/// Adds a variable to a scope.
let scopeCtxOpenVar scopeSerial varSerial (scopeCtx: ScopeCtx): ScopeCtx =
  let varIdent = scopeCtx |> scopeCtxGetVar varSerial |> varDefToIdent
  assert (varIdent <> "_")

  scopeCtx
  |> scopeCtxWithLocal ((scopeSerial, Binding.Var (varSerial, varIdent)) :: (scopeCtx |> scopeCtxGetLocal))

/// Adds a type to a scope.
let scopeCtxOpenTy scopeSerial tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  let tyIdent = scopeCtx |> scopeCtxGetTy tySerial |> tyDefToIdent
  scopeCtx
  |> scopeCtxWithLocal ((scopeSerial, Binding.Ty (tySerial, tyIdent)) :: (scopeCtx |> scopeCtxGetLocal))

/// Defines a variable in the local scope.
let scopeCtxDefineLocalVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineVar varSerial varDef
  |> scopeCtxOpenVar (scopeCtx |> scopeCtxGetLocalSerial) varSerial

/// Defines a type in the local scope.
let scopeCtxDefineLocalTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineTy tySerial tyDef
  |> scopeCtxOpenTy (scopeCtx |> scopeCtxGetLocalSerial) tySerial

/// Called on enter the body of let expressions.
let scopeCtxOnEnterLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithLetDepth ((scopeCtx |> scopeCtxGetLetDepth) + 1)

let scopeCtxOnLeaveLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxWithLetDepth ((scopeCtx |> scopeCtxGetLetDepth) - 1)

/// Starts a new scope.
let scopeCtxStartScope (scopeCtx: ScopeCtx): ScopeSerial * ScopeCtx =
  let parentSerial, parent = scopeCtx |> scopeCtxGetLocalSerial, scopeCtx |> scopeCtxGetLocal
  let (localSerial as serial) = (scopeCtx |> scopeCtxGetSerial) + 1
  let scopeCtx =
    scopeCtx
    |> scopeCtxWithSerial serial
    |> scopeCtxWithLocalSerial localSerial
    |> scopeCtxWithLocal ((localSerial, Binding.Parent (parentSerial, parent)) :: (scopeCtx |> scopeCtxGetLocal))
  parentSerial, scopeCtx

let scopeCtxFinishScope parentSerial (scopeCtx: ScopeCtx): ScopeCtx =
  let rec go bindings =
    match bindings with
    | [] ->
      assert false
      scopeCtx |> scopeCtxGetLocalSerial, []

    | (scope, Binding.Parent (parent, bindings)) :: _ ->
      assert (scope = (scopeCtx |> scopeCtxGetLocalSerial) && parent = parentSerial)
      parent, bindings

    | (scope, _) :: bindings
      when scope = (scopeCtx |> scopeCtxGetLocalSerial) ->
      // Discard the local bindings.
      go bindings

    | binding :: bindings ->
      // Keep non-local bindings such as variants.
      let parent, bindings = go bindings
      parent, binding :: bindings

  let localSerial, local =
    go (scopeCtx |> scopeCtxGetLocal)

  scopeCtx
  |> scopeCtxWithLocalSerial localSerial
  |> scopeCtxWithLocal local

let scopeCtxResolveVar scopeSerial ident (scopeCtx: ScopeCtx): VarSerial option =
  let rec go current bindings =
    match bindings with
    | [] ->
      None

    | (bindingScope, Binding.Var (varSerial, varIdent)) :: _
      when bindingScope = current && varIdent = ident ->
      Some varSerial

    | (bindingScope, Binding.Parent (parentSerial, parentBindings)) :: bindings
      when bindingScope = current ->
      match go parentSerial parentBindings with
      | Some serial ->
        Some serial

      | None ->
        go current bindings

    | _ :: bindings ->
      go current bindings

  go scopeSerial (scopeCtx |> scopeCtxGetLocal)

let scopeCtxResolveTyIdent scopeSerial ident (scopeCtx: ScopeCtx): TySerial option =
  let rec go current bindings =
    match bindings with
    | [] ->
      None

    | (bindingScope, Binding.Ty (tySerial, tyIdent)) :: _
      when bindingScope = current && tyIdent = ident ->
      Some tySerial

    | (bindingScope, Binding.Parent (parentSerial, parentBindings)) :: bindings
      when bindingScope = current ->
      match go parentSerial parentBindings with
      | Some serial ->
        Some serial

      | None ->
        go current bindings

    | _ :: bindings ->
      go current bindings

  go scopeSerial (scopeCtx |> scopeCtxGetLocal)

let scopeCtxResolveLocalVar ident (scopeCtx: ScopeCtx) =
  scopeCtx |> scopeCtxResolveVar (scopeCtx |> scopeCtxGetLocalSerial) ident

let scopeCtxResolveLocalTyIdent ident (scopeCtx: ScopeCtx) =
  scopeCtx |> scopeCtxResolveTyIdent (scopeCtx |> scopeCtxGetLocalSerial) ident

let scopeCtxResolvePatAsScope pat scopeCtx =
  match pat with
  | HPat.Nav _ ->
    // A.B.C (= (A.B).C) case
    failwith "unimpl"

  | HPat.Ref (serial, _, _) ->
    let ident = scopeCtx |> scopeCtxGetIdent serial
    scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ ->
    None

/// Resolves an expressions as scope: type, module or namespace.
let scopeCtxResolveExprAsScope expr scopeCtx =
  match expr with
  | HExpr.Nav _ ->
    // A.B.C (= (A.B).C) case
    failwith "unimpl"

  | HExpr.Ref (serial, _, _) ->
    let ident = scopeCtx |> scopeCtxGetIdent serial
    scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ ->
    None

/// Resolves type identifiers in a type expression.
let scopeCtxResolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | Ty.Error _ ->
      ty, scopeCtx

    | Ty.Con (TyCon.Ref tySerial, [])
      when (scopeCtx |> scopeCtxGetIdent tySerial) = "_" ->
      // Handle wildcard type.
      let scopeCtx = scopeCtx |> scopeCtxDefineFreeTy tySerial
      Ty.Meta (tySerial, loc), scopeCtx

    | Ty.Con (TyCon.Ref serial, tys) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      let tys, scopeCtx = (tys, scopeCtx) |> stMap go

      match scopeCtx |> scopeCtxResolveLocalTyIdent ident with
      | Some tySerial
        when scopeCtx |> scopeCtxIsMetaTy tySerial ->
        // In the case of type synonyms.
        Ty.Meta (tySerial, loc), scopeCtx

      | Some tySerial ->
        tyRef tySerial tys, scopeCtx

      | None ->
        tyPrimFromIdent ident tys loc, scopeCtx

    | Ty.Con (tyCon, tys) ->
      let tys, scopeCtx = (tys, scopeCtx) |> stMap go
      Ty.Con (tyCon, tys), scopeCtx

    | _ ->
      ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let scopeCtxDefineFunUniquely serial args ty loc (scopeCtx: ScopeCtx): ScopeCtx =
  let arity = args |> listLength
  let tyScheme = TyScheme.ForAll ([], ty)

  match scopeCtx |> scopeCtxGetVars |> mapTryFind serial with
  | Some (VarDef.Fun _) ->
    scopeCtx

  | Some _ ->
    failwith "NEVER"

  | None ->
    let ident = scopeCtx |> scopeCtxGetIdent serial
    let varDef = VarDef.Fun (ident, arity, tyScheme, loc)
    let scopeCtx = scopeCtx |> scopeCtxDefineLocalVar serial varDef
    scopeCtx

/// Defines a type based on a type declaration.
///
/// - This is idempotent. Duplicated calls are just ignored.
/// - You need call `scopeCtxDefineTyFinish` to complete the task.
/// - This doesn't resolve inner type expressions
///   because some type declarations are still unseen.
let scopeCtxDefineTyStart tySerial tyDecl loc ctx =
  let tyIdent = ctx |> scopeCtxGetIdent tySerial

  if ctx |> scopeCtxGetTys |> mapContainsKey tySerial then
    ctx
  else

  match tyDecl with
  | TyDecl.Synonym (body, _synonymLoc) ->
    ctx |> scopeCtxDefineLocalTy tySerial (TyDef.Meta (tyIdent, body, loc))

  | TyDecl.Union (_, variants, _unionLoc) ->
    let defineVariant ctx (variantIdent, variantSerial, hasPayload, payloadTy) =
      let varDef = VarDef.Variant (variantIdent, tySerial, hasPayload, payloadTy, noTy, loc)
      ctx
      |> scopeCtxDefineVar variantSerial varDef
      |> scopeCtxOpenVar tySerial variantSerial
      |> scopeCtxOpenVar (ctx |> scopeCtxGetLocalSerial) variantSerial
    let ctx =
      variants |> listFold defineVariant ctx

    let tyDef =
      let variantSerials = variants |> listMap (fun (_, variantSerial, _, _) -> variantSerial)
      TyDef.Union (tyIdent, variantSerials, loc)
    ctx |> scopeCtxDefineLocalTy tySerial tyDef

/// Completes the type definition.
///
/// - No need to call `scopeCtxDefineTyStart` first.
/// - This resolves inner type expressions.
let scopeCtxDefineTyFinish tySerial tyDecl loc ctx =
  let ctx = ctx |> scopeCtxDefineTyStart tySerial tyDecl loc
  let tyDef = ctx |> scopeCtxGetTy tySerial

  match tyDef with
  | TyDef.Meta (tyIdent, bodyTy, loc) ->
    let bodyTy, ctx = ctx |> scopeCtxResolveTy bodyTy loc
    ctx |> scopeCtxDefineTy tySerial (TyDef.Meta (tyIdent, bodyTy, loc))

  | TyDef.Union (_, variantSerials, _unionLoc) ->
    let rec go ctx variantSerial =
      match ctx |> scopeCtxGetVar variantSerial with
      | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
        let payloadTy, ctx = ctx |> scopeCtxResolveTy payloadTy loc
        let variantTy, ctx = ctx |> scopeCtxResolveTy variantTy loc
        let varDef = VarDef.Variant (ident, tySerial, hasPayload, payloadTy, variantTy, loc)
        ctx |> scopeCtxDefineVar variantSerial varDef
      | _ ->
        failwith "NEVER: it must be variant"
    variantSerials |> listFold go ctx

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// This stage, traverse declarations directly inside `module rec`s
// to create variables/types pre-definitions
// so that mutually recursive references resolve correctly.

let collectDecls (expr, ctx) =
  let rec goPat (pat, ctx) =
    match pat with
    | HPat.Lit _
    | HPat.Discard _
    | HPat.Nav _
    | HPat.Nil _
    | HPat.OptionNone _
    | HPat.OptionSome _ ->
      pat, ctx

    | HPat.Or _ ->
      // NOTE: OR patterns doesn't appear because not entering `match` arms.
      assert false
      pat, ctx

    | HPat.Ref (serial, ty, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial
      match ctx |> scopeCtxResolveLocalVar ident with
      | Some varSerial
        when ctx |> scopeCtxIsVariant varSerial ->
        HPat.Ref (varSerial, ty, loc), ctx
      | _ ->
        let ctx = ctx |> scopeCtxDefineLocalVar serial (VarDef.Var (ident, ty, loc))
        pat, ctx

    | HPat.Call (callee, args, ty, loc) ->
      let args, ctx = (args, ctx) |> stMap goPat
      HPat.Call (callee, args, ty, loc), ctx

    | HPat.Cons (l, r, ty, loc) ->
      let l, ctx = (l, ctx) |> goPat
      let r, ctx = (r, ctx) |> goPat
      HPat.Cons (l, r, ty, loc), ctx

    | HPat.Tuple (items, ty, loc) ->
      let items, ctx = (items, ctx) |> stMap goPat
      HPat.Tuple (items, ty, loc), ctx

    | HPat.As (pat, serial, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial
      let ctx = ctx |> scopeCtxDefineLocalVar serial (VarDef.Var (ident, noTy, loc))
      let pat, ctx = (pat, ctx) |> goPat
      HPat.As (pat, serial, loc), ctx

    | HPat.Anno (pat, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      HPat.Anno (pat, ty, loc), ctx

  let rec goExpr (expr, ctx) =
    match expr with
    | HExpr.Let (pat, init, next, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      let next, ctx = (next, ctx) |> goExpr
      HExpr.Let (pat, init, next, ty, loc), ctx

    | HExpr.LetFun (serial, _, args, body, next, ty, loc) ->
      let isMainFun = ctx |> scopeCtxGetIdent serial = "main"
      let ctx =
        ctx
        |> scopeCtxOnEnterLetBody
        |> scopeCtxDefineFunUniquely serial args noTy loc
        |> scopeCtxOnLeaveLetBody
      let next, ctx = (next, ctx) |> goExpr
      HExpr.LetFun (serial, isMainFun, args, body, next, ty, loc), ctx

    | HExpr.Inf (InfOp.Semi, exprs, ty, loc) ->
      let exprs, ctx = (exprs, ctx) |> stMap goExpr
      HExpr.Inf (InfOp.Semi, exprs, ty, loc), ctx

    | HExpr.TyDecl (serial, tyDecl, loc) ->
      let ctx = ctx |> scopeCtxDefineTyStart serial tyDecl loc
      HExpr.TyDecl (serial, tyDecl, loc), ctx

    | _ ->
      expr, ctx

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
  | HPat.OptionSome _ ->
    pat, ctx

  | HPat.Ref (varSerial, ty, loc)
    when ctx |> scopeCtxGetIdent varSerial = "_" ->
    HPat.Discard (ty, loc), ctx

  | HPat.Ref (varSerial, ty, loc) ->
    let ident = ctx |> scopeCtxGetIdent varSerial
    let variantSerial =
      match ctx |> scopeCtxResolveLocalVar ident with
      | Some varSerial ->
        match ctx |> scopeCtxGetVar varSerial with
        | VarDef.Variant _ ->
          Some varSerial

        | _ ->
          None

      | None ->
        None

    match variantSerial with
    | Some variantSerial ->
      HPat.Ref (variantSerial, ty, loc), ctx

    | None ->
      match ident with
      | "None" ->
        HPat.OptionNone (ty, loc), ctx

      | "Some" ->
        HPat.OptionSome (ty, loc), ctx

      | _ ->
        let varDef = VarDef.Var (ident, ty, loc)
        let ctx = ctx |> scopeCtxDefineLocalVar varSerial varDef
        HPat.Ref (varSerial, ty, loc), ctx

  | HPat.Nav (l, r, ty, loc) ->
    let varSerial =
      match ctx |> scopeCtxResolvePatAsScope l with
      | Some scopeSerial ->
        ctx |> scopeCtxResolveVar scopeSerial r

      | None ->
        None

    match varSerial with
    | Some varSerial ->
      HPat.Ref (varSerial, ty, loc), ctx

    | None ->
      let l, ctx = (l, ctx) |> nameResPat
      HPat.Nav (l, r, ty, loc), ctx

  | HPat.Call (callee, args, ty, loc) ->
    let callee, ctx = (callee, ctx) |> nameResPat
    let args, ctx = (args, ctx) |> stMap nameResPat
    HPat.Call (callee, args, ty, loc), ctx

  | HPat.Cons (l, r, itemTy, loc) ->
    let l, ctx = (l, ctx) |> nameResPat
    let r, ctx = (r, ctx) |> nameResPat
    HPat.Cons (l, r, itemTy, loc), ctx

  | HPat.Tuple (pats, tupleTy, loc) ->
    let pats, ctx = (pats, ctx) |> stMap nameResPat
    HPat.Tuple (pats, tupleTy, loc), ctx

  | HPat.As (pat, serial, loc) ->
    let ident = ctx |> scopeCtxGetIdent serial
    let varDef = VarDef.Var (ident, noTy, loc)
    let ctx = ctx |> scopeCtxDefineLocalVar serial varDef
    let pat, ctx = (pat, ctx) |> nameResPat
    HPat.As (pat, serial, loc), ctx

  | HPat.Anno (pat, ty, loc) ->
    let ty, ctx = ctx |> scopeCtxResolveTy ty loc
    let pat, ctx = (pat, ctx) |> nameResPat
    HPat.Anno (pat, ty, loc), ctx

  | HPat.Or (l, r, ty, loc) ->
    // FIXME: Currently variable bindings in OR patterns are not supported correctly.
    let l, ctx = (l, ctx) |> nameResPat
    let r, ctx = (r, ctx) |> nameResPat
    HPat.Or (l, r, ty, loc), ctx

let nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
  | HExpr.Error _
  | HExpr.Open _
  | HExpr.Lit _
  | HExpr.Prim _ ->
    expr, ctx

  | HExpr.Ref (serial, ty, loc) ->
    let ident = ctx |> scopeCtxGetIdent serial
    match ctx |> scopeCtxResolveLocalVar ident with
    | Some serial ->
      HExpr.Ref (serial, ty, loc), ctx

    | None ->
      match primFromIdent ident with
      | Some prim ->
        HExpr.Prim (prim, ty, loc), ctx

      | None ->
        HExpr.Error ("Undefined variable " + ident, loc), ctx

  | HExpr.Match (target, arms, ty, loc) ->
    let target, ctx =
      (target, ctx) |> nameResExpr
    let arms, ctx =
      (arms, ctx) |> stMap (fun ((pat, guard, body), ctx) ->
        let parent, ctx = ctx |> scopeCtxStartScope
        let pat, ctx = (pat, ctx) |> nameResPat
        let guard, ctx = (guard, ctx) |> nameResExpr
        let body, ctx = (body, ctx) |> nameResExpr
        let ctx = ctx |> scopeCtxFinishScope parent
        (pat, guard, body), ctx
      )
    HExpr.Match (target, arms, ty, loc), ctx

  | HExpr.Nav (l, r, ty, loc) ->
    // FIXME: Patchwork for tests to pass
    match l, r with
    | HExpr.Ref (serial, _, _), "length"
      when ctx |> scopeCtxGetIdent serial = "String" ->
      HExpr.Prim (HPrim.StrLength, ty, loc), ctx

    | HExpr.Ref (serial, _, _), "getSlice"
      when ctx |> scopeCtxGetIdent serial = "String" ->
      // NOTE: Actually this functions doesn't exist in the F# standard library.
      HExpr.Prim (HPrim.StrGetSlice, ty, loc), ctx

    |_ ->

    // Keep the nav expression unresolved so that type inference does.
    let keepUnresolved () =
      let l, ctx = (l, ctx) |> nameResExpr
      HExpr.Nav (l, r, ty, loc), ctx

    match ctx |> scopeCtxResolveExprAsScope l with
    | Some scopeSerial ->
      match ctx |> scopeCtxResolveVar scopeSerial r with
      | Some varSerial ->
        HExpr.Ref (varSerial, ty, loc), ctx

      | _ ->
        // X.ty patterns don't appear yet, so don't search for types.

        keepUnresolved ()

    | _ ->
      keepUnresolved ()

  | HExpr.Inf (op, items, ty, loc) ->
    // Necessary in case of annotation expression.
    let ty, ctx = ctx |> scopeCtxResolveTy ty loc

    let items, ctx = (items, ctx) |> stMap nameResExpr
    HExpr.Inf (op, items, ty, loc), ctx

  | HExpr.Let (pat, body, next, ty, loc) ->
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

    HExpr.Let (pat, body, next, ty, loc), ctx

  | HExpr.LetFun (serial, isMainFun, pats, body, next, ty, loc) ->
    let parent, ctx = ctx |> scopeCtxStartScope
    let ctx = ctx |> scopeCtxOnEnterLetBody

    // Define the function itself for recursive referencing.
    // FIXME: Functions are recursive even if `rec` is missing.
    let ctx = ctx |> scopeCtxDefineFunUniquely serial pats noTy loc

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

    HExpr.LetFun (serial, isMainFun, pats, body, next, ty, loc), ctx

  | HExpr.TyDecl (serial, tyDecl, loc) ->
    let ctx = ctx |> scopeCtxDefineTyFinish serial tyDecl loc
    expr, ctx

let nameRes (expr: HExpr, nameCtx: NameCtx): HExpr * ScopeCtx =
  let scopeCtx = scopeCtxFromNameCtx nameCtx
  (expr, scopeCtx)
  |> collectDecls
  |> nameResExpr
