module rec MiloneLang.NameRes

open MiloneLang
open MiloneLang.Types
open MiloneLang.Helpers

[<RequireQualifiedAccess>]
type Binding =
  /// Value binding.
  | Var
    of varSerial:int * varIdent:string

  /// Type binding.
  | Ty
    of tySerial:int * tyIdent:string

  /// Parent scope.
  | Parent
    of int * Scope

/// scopeSerial * (scopeSerial, binding) list.
type Scope = (int * Binding) list

[<RequireQualifiedAccess>]
type ScopeCtx =
  {
    /// Last serial number.
    /// We need manage identifiers as integers rather than strings due to shadowing.
    Serial: int

    /// Serial to ident map.
    NameMap: Map<int, string>

    /// Variable serial to definition map.
    Vars: Map<int, VarDef>

    /// Type serial to definition map.
    Tys: Map<int, TyDef>

    /// Type serial to let-depth map.
    TyDepths: Map<int, int>

    /// Serial of the current scope.
    LocalSerial: int

    /// Current scope.
    Local: Scope

    /// Current let-depth, the number of ancestral let-body.
    LetDepth: int
  }

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

let scopeCtxFromNameCtx (nameCtx: NameCtx): ScopeCtx =
  let (NameCtx (nameMap, serial)) = nameCtx
  let localSerial as serial = serial + 1

  {
    Serial = serial
    NameMap = nameMap
    Vars = Map.empty
    Tys = Map.empty
    TyDepths = Map.empty
    LocalSerial = localSerial
    Local = []
    LetDepth = 0
  }

let scopeCtxGetIdent serial (scopeCtx: ScopeCtx): string =
  scopeCtx.NameMap |> Map.find serial

let scopeCtxGetVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Vars |> Map.containsKey varSerial)
  scopeCtx.Vars |> Map.find varSerial

let scopeCtxGetTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Tys |> Map.containsKey tySerial)
  scopeCtx.Tys |> Map.find tySerial

let scopeCtxIsVariant varSerial scopeCtx =
  match scopeCtx |> scopeCtxGetVar varSerial with
  | VarDef.Variant _ ->
    true

  | _ ->
    false

/// Defines a variable, without adding to any scope.
let scopeCtxDefineVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with Vars = scopeCtx.Vars |> Map.add varSerial varDef }

/// Defines a type, without adding to any scope.
let scopeCtxDefineTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      Tys = scopeCtx.Tys |> Map.add tySerial tyDef
      TyDepths = scopeCtx.TyDepths |> Map.add tySerial scopeCtx.LetDepth
  }

/// Adds a variable to a scope.
let scopeCtxOpenVar scopeSerial varSerial (scopeCtx: ScopeCtx): ScopeCtx =
  let varIdent = scopeCtx |> scopeCtxGetVar varSerial |> varDefIdent
  { scopeCtx with
      Local = (scopeSerial, Binding.Var (varSerial, varIdent)) :: scopeCtx.Local
  }

/// Adds a type to a scope.
let scopeCtxOpenTy scopeSerial tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  let tyIdent = scopeCtx |> scopeCtxGetTy tySerial |> tyDefIdent
  { scopeCtx with
      Local = (scopeSerial, Binding.Ty (tySerial, tyIdent)) :: scopeCtx.Local
  }

/// Defines a variable in the local scope.
let scopeCtxDefineLocalVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineVar varSerial varDef
  |> scopeCtxOpenVar scopeCtx.LocalSerial varSerial

/// Defines a type in the local scope.
let scopeCtxDefineLocalTy tySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> scopeCtxDefineTy tySerial tyDef
  |> scopeCtxOpenTy scopeCtx.LocalSerial tySerial

/// Called on enter the body of let expressions.
let scopeCtxOnEnterLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with LetDepth = scopeCtx.LetDepth + 1 }

let scopeCtxOnLeaveLetBody (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with LetDepth = scopeCtx.LetDepth - 1 }

/// Starts a new scope.
let scopeCtxStartScope (scopeCtx: ScopeCtx): int * ScopeCtx =
  let parentSerial, parent = scopeCtx.LocalSerial, scopeCtx.Local
  let localSerial as serial = scopeCtx.Serial + 1
  let scopeCtx =
    { scopeCtx with
        Serial = serial
        LocalSerial = localSerial
        Local = (localSerial, Binding.Parent (parentSerial, parent)) :: scopeCtx.Local
    }
  parentSerial, scopeCtx

let scopeCtxFinishScope parentSerial (scopeCtx: ScopeCtx): ScopeCtx =
  let rec go bindings =
    match bindings with
    | [] ->
      assert false
      scopeCtx.LocalSerial, []

    | (scope, Binding.Parent (parent, bindings)) :: _ ->
      assert (scope = scopeCtx.LocalSerial && parent = parentSerial)
      parent, bindings

    | (scope, _) :: bindings
      when scope = scopeCtx.LocalSerial ->
      // Discard the local bindings.
      go bindings

    | binding :: bindings ->
      // Keep non-local bindings such as variants.
      let parent, bindings = go bindings
      parent, binding :: bindings

  let localSerial, local =
    go scopeCtx.Local

  { scopeCtx with
      LocalSerial = localSerial
      Local = local
  }

let scopeCtxResolveVar scopeSerial ident (scopeCtx: ScopeCtx): int option =
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

  go scopeSerial scopeCtx.Local

let scopeCtxResolveTyIdent scopeSerial ident (scopeCtx: ScopeCtx): int option =
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

  go scopeSerial scopeCtx.Local

let scopeCtxResolveLocalVar ident (scopeCtx: ScopeCtx) =
  scopeCtx |> scopeCtxResolveVar scopeCtx.LocalSerial ident

let scopeCtxResolveLocalTyIdent ident (scopeCtx: ScopeCtx) =
  scopeCtx |> scopeCtxResolveTyIdent scopeCtx.LocalSerial ident

let scopeCtxResolvePatAsScope pat scopeCtx =
  match pat with
  | HPat.Nav _ ->
    // A.B.C (= (A.B).C) case
    failwith "unimpl"

  | HPat.Ref (_, serial, _, _) ->
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

  | HExpr.Ref (_, HValRef.Var serial, _, _) ->
    let ident = scopeCtx |> scopeCtxGetIdent serial
    scopeCtx |> scopeCtxResolveLocalTyIdent ident

  | _ ->
    None

/// Resolves type identifiers in a type expression.
let scopeCtxResolveTy ty scopeCtx =
  let rec go ty =
    match ty with
    | Ty.Error _ ->
      ty

    | Ty.Con (TyCon.Ref serial, tys) ->
      let ident = scopeCtx |> scopeCtxGetIdent serial
      match scopeCtx |> scopeCtxResolveLocalTyIdent ident with
      | Some tySerial ->
        let tys = tys |> List.map go
        Ty.Con (TyCon.Ref tySerial, tys)

      | None ->
        Ty.Error

    | Ty.Con (tyCon, tys) ->
      let tys = tys |> List.map go
      Ty.Con (tyCon, tys)

    | _ ->
      ty

  go ty

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let scopeCtxDefineFunUniquely serial arity tyScheme loc (scopeCtx: ScopeCtx): ScopeCtx =
  match scopeCtx.Vars |> Map.tryFind serial with
  | Some (VarDef.Fun _) ->
    scopeCtx

  | Some _ ->
    failwith "NEVER"

  | None ->
    let ident = scopeCtx |> scopeCtxGetIdent serial
    let varDef = VarDef.Fun (ident, arity, tyScheme, loc)
    let scopeCtx = scopeCtx |> scopeCtxDefineLocalVar serial varDef
    scopeCtx

/// Adds a type declaration to the context.
/// At the moment, we can't resolve type expressions correctly
/// because some type declarations are still unseen.
/// So keep type expressions unresolved for now and resolve them later.
let scopeCtxDefineTyDeclUniquely tySerial tyDecl loc ctx =
  let tyIdent = ctx |> scopeCtxGetIdent tySerial

  if ctx.Tys |> Map.containsKey tySerial then
    ctx
  else

  match tyDecl with
  | TyDecl.Synonym (body, _synonymLoc) ->
    ctx |> scopeCtxDefineLocalTy tySerial (TyDef.Meta (tyIdent, body, loc))

  | TyDecl.Union (_, variants, _unionLoc) ->
    let unionTy = Ty.Con (TyCon.Ref tySerial, [])
    let defineVariant ctx (variantIdent, variantSerial, hasPayload, payloadTy) =
      // E.g. Some: 'T -> 'T option, None: 'T option
      let variantTy =
        if hasPayload then
          Ty.Con (TyCon.Fun, [payloadTy; unionTy])
        else
          unionTy
      let varDef =
        VarDef.Variant (variantIdent, tySerial, hasPayload, payloadTy, variantTy, loc)
      ctx
      |> scopeCtxDefineVar variantSerial varDef
      |> scopeCtxOpenVar tySerial variantSerial
      |> scopeCtxOpenVar ctx.LocalSerial variantSerial
    let ctx =
      variants |> List.fold defineVariant ctx

    let tyDef =
      let variantSerials = variants |> List.map (fun (_, variantSerial, _, _) -> variantSerial)
      TyDef.Union (tyIdent, variantSerials, loc)
    ctx |> scopeCtxDefineLocalTy tySerial tyDef

/// Upgrades the type declaration to definition.
/// Resolves type expressions.
let scopeCtxDefineTyDef tySerial tyDecl loc ctx =
  let ctx = ctx |> scopeCtxDefineTyDeclUniquely tySerial tyDecl loc
  let tyDef = ctx |> scopeCtxGetTy tySerial

  match tyDef with
  | TyDef.Meta (tyIdent, bodyTy, loc) ->
    let bodyTy = ctx |> scopeCtxResolveTy bodyTy
    ctx |> scopeCtxDefineTy tySerial (TyDef.Meta (tyIdent, bodyTy, loc))

  | TyDef.Union (_, variantSerials, _unionLoc) ->
    let rec go ctx variantSerial =
      match ctx |> scopeCtxGetVar variantSerial with
      | VarDef.Variant (ident, tySerial, hasPayload, payloadTy, variantTy, loc) ->
        let payloadTy = ctx |> scopeCtxResolveTy payloadTy
        let variantTy = ctx |> scopeCtxResolveTy variantTy
        let varDef = VarDef.Variant (ident, tySerial, hasPayload, payloadTy, variantTy, loc)
        ctx |> scopeCtxDefineVar variantSerial varDef
      | _ ->
        failwith "NEVER: it must be variant"
    variantSerials |> List.fold go ctx

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
    | HPat.Nav _
    | HPat.Nil _ ->
      pat, ctx

    | HPat.Or _ ->
      // NOTE: OR patterns doesn't appear because not entering `match` arms.
      assert false
      pat, ctx

    | HPat.Ref (_, serial, ty, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial
      match ctx |> scopeCtxResolveLocalVar ident with
      | Some varSerial
        when ctx |> scopeCtxIsVariant varSerial ->
        HPat.Ref (ident, varSerial, ty, loc), ctx
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

    | HPat.As (pat, _, serial, loc) ->
      let ident = ctx |> scopeCtxGetIdent serial
      let ctx = ctx |> scopeCtxDefineLocalVar serial (VarDef.Var (ident, noTy, loc))
      let pat, ctx = (pat, ctx) |> goPat
      HPat.As (pat, ident, serial, loc), ctx

    | HPat.Anno (pat, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      HPat.Anno (pat, ty, loc), ctx

  let rec goExpr (expr, ctx) =
    match expr with
    | HExpr.Let (pat, init, next, ty, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      let next, ctx = (next, ctx) |> goExpr
      HExpr.Let (pat, init, next, ty, loc), ctx

    | HExpr.LetFun (ident, serial, args, body, next, ty, loc) ->
      let ctx =
        let arity = args |> List.length
        let tyScheme = TyScheme.ForAll ([], ty)
        ctx |> scopeCtxDefineFunUniquely serial arity tyScheme loc
      let next, ctx = (next, ctx) |> goExpr
      HExpr.LetFun (ident, serial, args, body, next, ty, loc), ctx

    | HExpr.Inf (InfOp.AndThen, exprs, ty, loc) ->
      let exprs, ctx = (exprs, ctx) |> stMap goExpr
      HExpr.Inf (InfOp.AndThen, exprs, ty, loc), ctx

    | HExpr.TyDef (ident, serial, tyDecl, loc) ->
      let ctx = ctx |> scopeCtxDefineTyDeclUniquely serial tyDecl loc
      HExpr.TyDef (ident, serial, tyDecl, loc), ctx

    | _ ->
      expr, ctx

  goExpr (expr, ctx)

let nameRes (expr: HExpr, nameCtx: NameCtx): HExpr * ScopeCtx =
  let scopeCtx = scopeCtxFromNameCtx nameCtx
  (expr, scopeCtx) 
  |> collectDecls
