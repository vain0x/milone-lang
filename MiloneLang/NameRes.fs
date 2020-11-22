/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneLang.NameRes

open MiloneLang.Types
open MiloneLang.Helpers

// -----------------------------------------------
// Type primitives
// -----------------------------------------------

let private tyPrimOfName name tys loc =
  match name, tys with
  | "unit", [] -> tyUnit
  | "bool", [] -> tyBool
  | "int", [] -> tyInt
  | "uint", [] -> tyUInt
  | "char", [] -> tyChar
  | "string", [] -> tyStr
  | "obj", [] -> tyObj

  | "option", [ itemTy ] ->
      // FIXME: option is just an alias of list for now
      tyList itemTy

  | "list", [ itemTy ] -> tyList itemTy

  | _ ->
      // FIXME: Report error correctly
      printfn "#error tyPrimOfName name=%s loc=%s" name (locToString loc)
      ErrorTy loc

// -----------------------------------------------
// Symbols
// -----------------------------------------------

[<Struct; NoEquality; NoComparison>]
type ValueSymbol = ValueSymbol of varSerial: VarSerial

[<Struct; NoEquality; NoComparison>]
type TySymbol = TySymbol of tySerial: TySerial

// -----------------------------------------------
// Namespace
// -----------------------------------------------

type Ns<'K, 'V> = AssocMap<'K, AssocMap<Ident, 'V>>

// FIXME: this emits code that doesn't compile due to use of incomplete type
// type NameTree = NameTree of AssocMap<Serial, Serial list>
//   > error: invalid use of undefined type ‘struct UnitNameTree_Fun1’
//   >        struct NameTree_ app_193 = nameTreeEmpty_.fun(nameTreeEmpty_.env, 0);
// let nameTreeEmpty: unit -> NameTree =
//   let it = NameTree(mapEmpty (intHash, intCmp))
//   fun () -> it

let private nsFind (key: Serial) (ns: Ns<_, _>): AssocMap<Ident, _> =
  match ns |> mapTryFind key with
  | Some submap -> submap
  | None -> mapEmpty strCmp

let private nsAdd (key: Serial) (ident: Ident) value (ns: Ns<_, _>): Ns<_, _> =
  ns
  |> mapAdd key (ns |> nsFind key |> mapAdd ident value)

// --------------------------------------------
// Scopes
// --------------------------------------------

// FIXME: Not used?
type private ScopeSerial = Serial

/// Stack of local scopes.
type private ScopeChain<'T> = AssocMap<Ident, 'T> list

/// Scope chains, vars and types.
type private Scope = ScopeChain<ValueSymbol> * ScopeChain<TySymbol>

let private scopeMapEmpty () = mapEmpty strCmp

let private scopeChainEmpty (): ScopeChain<_> = [ scopeMapEmpty () ]

let private scopeEmpty (): Scope = scopeChainEmpty (), scopeChainEmpty ()

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

[<NoEquality; NoComparison>]
type ScopeCtx =
  {
    /// Last serial number.
    /// We need manage identifiers as integers rather than strings due to shadowing.
    Serial: Serial

    /// Serial to ident map.
    NameMap: AssocMap<Serial, Ident>

    /// Variable serial to definition map.
    Vars: AssocMap<VarSerial, VarDef>

    /// Variable serial to let-depth map.
    VarDepths: AssocMap<VarSerial, LetDepth>

    /// Type serial to definition map.
    Tys: AssocMap<TySerial, TyDef>

    /// Type serial to let-depth map.
    TyDepths: AssocMap<TySerial, LetDepth>

    /// Values contained by types.
    VarNs: Ns<TySerial, ValueSymbol>

    /// Types contained by types.
    TyNs: Ns<TySerial, TySymbol>

    ///Serial of the current scope.
    LocalSerial: ScopeSerial

    /// Current scope.
    Local: Scope

    /// Current let-depth, the number of ancestral let-body.
    LetDepth: LetDepth }

let private ofNameCtx (nameCtx: NameCtx): ScopeCtx =
  let (NameCtx (nameMap, serial)) = nameCtx
  let (localSerial as serial) = serial + 1

  { Serial = serial
    NameMap = nameMap
    Vars = mapEmpty intCmp
    VarDepths = mapEmpty intCmp
    Tys = mapEmpty intCmp
    TyDepths = mapEmpty intCmp
    VarNs = mapEmpty intCmp
    TyNs = mapEmpty intCmp
    LocalSerial = localSerial
    Local = scopeEmpty ()
    LetDepth = 0 }

let private findName serial (scopeCtx: ScopeCtx): Ident = scopeCtx.NameMap |> mapFind serial

let private findVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Vars |> mapContainsKey varSerial)
  scopeCtx.Vars |> mapFind varSerial

let private findTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Tys |> mapContainsKey tySerial)
  scopeCtx.Tys |> mapFind tySerial

let private isFun varSerial scopeCtx =
  match scopeCtx |> findVar varSerial with
  | FunDef _ -> true

  | _ -> false

let private isVariant varSerial scopeCtx =
  match scopeCtx |> findVar varSerial with
  | VariantDef _ -> true

  | _ -> false

/// Defines a variable, without adding to any scope.
let private addVar valueSymbol varDef (scopeCtx: ScopeCtx): ScopeCtx =
  let (ValueSymbol varSerial) = valueSymbol

  // Merge into current definition.
  let varDef =
    match scopeCtx.Vars |> mapTryFind varSerial, varDef with
    | Some (VarDef (_, StaticSM, _, _)), VarDef (name, _, ty, loc) -> VarDef(name, StaticSM, ty, loc)
    | _ -> varDef

  { scopeCtx with
      Vars = scopeCtx.Vars |> mapAdd varSerial varDef
      VarDepths =
        scopeCtx.VarDepths
        |> mapAdd varSerial scopeCtx.LetDepth }

/// Defines a type, without adding to any scope.
let private addTy tySymbol tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  let (TySymbol tySerial) = tySymbol

  { scopeCtx with
      Tys = scopeCtx.Tys |> mapAdd tySerial tyDef
      TyDepths =
        scopeCtx.TyDepths
        |> mapAdd tySerial scopeCtx.LetDepth }

/// Defines an unbound meta type.
let private addUnboundMetaTy tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      TyDepths =
        scopeCtx.TyDepths
        |> mapAdd tySerial scopeCtx.LetDepth }

/// Adds a variable to a namespace.
let private addVarToNs tySerial valueSymbol (scopeCtx: ScopeCtx): ScopeCtx =
  let name =
    let (ValueSymbol varSerial) = valueSymbol
    scopeCtx |> findName varSerial

  { scopeCtx with
      VarNs = scopeCtx.VarNs |> nsAdd tySerial name valueSymbol }

/// Adds a type to a namespace.
let private addTyToNs parentTySerial tySymbol (scopeCtx: ScopeCtx): ScopeCtx =
  let (TySymbol tySerial) = tySymbol
  let name = scopeCtx |> findName tySerial

  { scopeCtx with
      TyNs =
        scopeCtx.TyNs
        |> nsAdd parentTySerial name tySymbol }

/// Adds a variable to a scope.
let private importVar symbol (scopeCtx: ScopeCtx): ScopeCtx =
  let varName =
    let (ValueSymbol varSerial) = symbol
    scopeCtx |> findVar varSerial |> varDefToName

  assert (varName <> "_")

  let scope: Scope =
    match scopeCtx.Local with
    | map :: varScopes, tyScopes ->
        let varScopes =
          (map |> mapAdd varName symbol) :: varScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  { scopeCtx with Local = scope }

/// Adds a type to a scope.
let private importTy symbol (scopeCtx: ScopeCtx): ScopeCtx =
  let tyName =
    let (TySymbol tySerial) = symbol
    scopeCtx |> findTy tySerial |> tyDefToName

  let scope: Scope =
    match scopeCtx.Local with
    | varScopes, map :: tyScopes ->
        let tyScopes =
          (map |> mapAdd tyName symbol) :: tyScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  { scopeCtx with Local = scope }

let private openModule moduleSerial (scopeCtx: ScopeCtx) =
  // Import vars.
  let scopeCtx =
    scopeCtx.VarNs
    |> nsFind moduleSerial
    |> mapFold (fun ctx _ symbol -> ctx |> importVar symbol) scopeCtx

  // Import tys.
  let scopeCtx =
    scopeCtx.TyNs
    |> nsFind moduleSerial
    |> mapFold (fun ctx _ symbol -> ctx |> importTy symbol) scopeCtx

  scopeCtx

/// Defines a variable in the local scope.
let private addLocalVar valueSymbol varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> addVar valueSymbol varDef
  |> importVar valueSymbol

/// Defines a type in the local scope.
let private addLocalTy tySymbol tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  let (TySymbol tySerial) = tySymbol
  scopeCtx
  |> addTy tySymbol tyDef
  |> importTy tySymbol

/// Called on enter the init of let expressions.
let private enterLetInit (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      LetDepth = scopeCtx.LetDepth + 1 }

let private leaveLetInit (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      LetDepth = scopeCtx.LetDepth - 1 }

/// Starts a new scope.
let private startScope (scopeCtx: ScopeCtx): ScopeSerial * ScopeCtx =
  let parentSerial = scopeCtx.LocalSerial

  let scopeCtx =
    let varScopes, tyScopes = scopeCtx.Local
    { scopeCtx with
        Local = scopeMapEmpty () :: varScopes, scopeMapEmpty () :: tyScopes }

  parentSerial, scopeCtx

let private finishScope _parentSerial (scopeCtx: ScopeCtx): ScopeCtx =
  match scopeCtx.Local with
  | [], _
  | _, [] -> failwith "NEVER: Scope can't be empty."

  | _ :: varScopes, _ :: tyScopes ->
      { scopeCtx with
          Local = varScopes, tyScopes }

let private resolveScopedVarName scopeSerial name (scopeCtx: ScopeCtx): ValueSymbol option =
  if scopeSerial = scopeCtx.LocalSerial then
    // Find from local scope.
    let varScopes, _ = scopeCtx.Local
    varScopes
    |> List.tryPick (fun map -> map |> mapTryFind name)
  else
    // Find from namespace.
    scopeCtx.VarNs
    |> nsFind scopeSerial
    |> mapTryFind name

let private resolveScopedTyName scopeSerial name (scopeCtx: ScopeCtx): TySymbol option =
  if scopeSerial = scopeCtx.LocalSerial then
    // Find from local scope.
    let _, tyScopes = scopeCtx.Local
    tyScopes
    |> List.tryPick (fun map -> map |> mapTryFind name)
  else
    // Find from namespace.
    failwith "Module.Ty syntax is unimplemented"

let private resolveLocalVarName name (scopeCtx: ScopeCtx) =
  scopeCtx
  |> resolveScopedVarName scopeCtx.LocalSerial name

let private resolveLocalTyName name (scopeCtx: ScopeCtx) =
  scopeCtx
  |> resolveScopedTyName scopeCtx.LocalSerial name

let private resolvePatAsScope pat scopeCtx =
  match pat with
  | HNavPat _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HRefPat (serial, _, _) ->
      let name = scopeCtx |> findName serial
      scopeCtx |> resolveLocalTyName name

  | _ -> None

/// Resolves an expressions as scope: type, module or namespace.
let private resolveExprAsScope expr scopeCtx =
  match expr with
  | HNavExpr _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HRefExpr (serial, _, _) ->
      let name = scopeCtx |> findName serial
      scopeCtx |> resolveLocalTyName name

  | _ -> None

/// Resolves type names in a type expression.
let private resolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | ErrorTy _ -> ty, scopeCtx

    | AppTy (RefTyCtor tySerial, []) when (scopeCtx |> findName tySerial) = "_" ->
        // Handle wildcard type.
        let scopeCtx = scopeCtx |> addUnboundMetaTy tySerial

        MetaTy(tySerial, loc), scopeCtx

    | AppTy (RefTyCtor serial, tys) ->
        let name = scopeCtx |> findName serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go

        match scopeCtx |> resolveLocalTyName name with
        | Some (TySymbol tySerial) ->
            match scopeCtx.Tys |> mapTryFind tySerial with
            | Some (UniversalTyDef (_, tySerial, _)) -> MetaTy(tySerial, loc), scopeCtx

            | Some (SynonymTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> List.length tys ->
                failwithf "synonym arity mismatch: %A" (tySerial, tys, name, defTyArgs, loc)

            | _ -> tyRef tySerial tys, scopeCtx

        | None -> tyPrimOfName name tys loc, scopeCtx

    | AppTy (tyCtor, tys) ->
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        AppTy(tyCtor, tys), scopeCtx

    | _ -> ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let private defineFunUniquely serial args ty loc (scopeCtx: ScopeCtx): ScopeCtx =
  let arity = args |> List.length
  let tyScheme = TyScheme([], ty)

  match scopeCtx.Vars |> mapTryFind serial with
  | Some (FunDef _) -> scopeCtx

  | Some _ -> failwith "NEVER"

  | None ->
      let name = scopeCtx |> findName serial
      let varDef = FunDef(name, arity, tyScheme, loc)

      let scopeCtx =
        scopeCtx
        |> addLocalVar (ValueSymbol serial) varDef

      scopeCtx

/// Defines a type based on a type declaration.
///
/// - This is idempotent. Duplicated calls are just ignored.
/// - You need call `finishDefineTy` to complete the task.
/// - This doesn't resolve inner type expressions
///   because some type declarations are still unseen.
let private startDefineTy moduleSerialOpt tySerial vis tyArgs tyDecl loc ctx =
  let addVarToModule varSerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> addVarToNs moduleSerial varSerial

    | _ -> ctx

  let addTyToModule tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> addTyToNs moduleSerial tySerial

    | _ -> ctx

  let tyName = ctx |> findName tySerial

  if ctx.Tys |> mapContainsKey tySerial then
    ctx
  else

    match tyDecl with
    | TySynonymDecl (body, _) ->
        ctx
        |> addLocalTy (TySymbol tySerial) (SynonymTyDef(tyName, tyArgs, body, loc))
        |> addTyToModule (TySymbol tySerial)

    | UnionTyDecl (_, variants, _unionLoc) ->
        let defineVariant ctx (name, variantSerial, hasPayload, payloadTy) =
          let variantSymbol = ValueSymbol variantSerial
          let varDef = VariantDef(name, tySerial, hasPayload, payloadTy, noTy, loc)

          ctx
          |> addVar variantSymbol varDef
          |> addVarToNs tySerial variantSymbol
          |> importVar variantSymbol
          |> addVarToModule variantSymbol

        let ctx = variants |> List.fold defineVariant ctx

        let tySymbol = TySymbol tySerial

        let tyDef =
          let variantSerials =
            variants
            |> List.map (fun (_, variantSerial, _, _) -> variantSerial)

          UnionTyDef(tyName, variantSerials, loc)

        ctx
        |> addLocalTy tySymbol tyDef
        |> addTyToModule tySymbol

    | RecordTyDecl (_, fields, loc) ->
        let tySymbol = TySymbol tySerial

        let tyDef = RecordTyDef(tyName, fields, loc)

        ctx
        |> addLocalTy tySymbol tyDef
        |> addTyToModule tySymbol

/// Completes the type definition.
///
/// - No need to call `startDefineTy` first.
/// - This resolves inner type expressions.
let private finishDefineTy tySerial tyArgs tyDecl loc ctx =
  let ctx =
    // Pass in PrivateVis because if this type is not pre-declared here, it's local to function.
    ctx
    |> startDefineTy None tySerial PrivateVis tyArgs tyDecl loc

  let tyDef = ctx |> findTy tySerial

  match tyDef with
  | MetaTyDef (tyName, bodyTy, loc) ->
      let bodyTy, ctx = ctx |> resolveTy bodyTy loc
      ctx
      |> addTy (TySymbol tySerial) (MetaTyDef(tyName, bodyTy, loc))

  | UniversalTyDef _ -> ctx

  | SynonymTyDef (tyName, tyArgs, bodyTy, loc) ->
      let parent, ctx = ctx |> startScope

      let ctx =
        tyArgs
        |> List.fold (fun ctx tyArg ->
             let name = ctx |> findName tyArg
             ctx
             |> addLocalTy (TySymbol tyArg) (UniversalTyDef(name, tyArg, loc))) ctx

      let bodyTy, ctx = ctx |> resolveTy bodyTy loc
      let ctx = ctx |> finishScope parent

      ctx
      |> addTy (TySymbol tySerial) (SynonymTyDef(tyName, tyArgs, bodyTy, loc))

  | UnionTyDef (_, variantSerials, _unionLoc) ->
      let go ctx variantSerial =
        match ctx |> findVar variantSerial with
        | VariantDef (name, tySerial, hasPayload, payloadTy, variantTy, loc) ->
            let payloadTy, ctx = ctx |> resolveTy payloadTy loc
            let variantTy, ctx = ctx |> resolveTy variantTy loc

            let varDef =
              VariantDef(name, tySerial, hasPayload, payloadTy, variantTy, loc)

            ctx |> addVar (ValueSymbol variantSerial) varDef

        | _ -> failwith "NEVER: it must be variant"

      variantSerials |> List.fold go ctx

  | RecordTyDef (tyName, fields, loc) ->
      let resolveField ((name, ty, loc), ctx) =
        let ty, ctx = ctx |> resolveTy ty loc
        (name, ty, loc), ctx

      let fields, ctx = (fields, ctx) |> stMap resolveField
      ctx
      |> addTy (TySymbol tySerial) (RecordTyDef(tyName, fields, loc))

  | ModuleTyDef _ -> failwith "NEVER: no use case"

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// This stage, traverse declarations directly inside `module rec`s
// to create variables/types pre-definitions
// so that mutually recursive references resolve correctly.

let private collectDecls moduleSerialOpt (expr, ctx) =
  let addVarToModule vis varSerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis -> ctx |> addVarToNs moduleSerial varSerial

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
        let name = ctx |> findName serial
        match ctx |> resolveLocalVarName name with
        | Some (ValueSymbol varSerial) when ctx |> isVariant varSerial -> HVariantPat(varSerial, ty, loc), ctx

        | _ ->
            let ctx =
              ctx
              |> addLocalVar (ValueSymbol serial) (VarDef(name, StaticSM, ty, loc))
              |> addVarToModule vis (ValueSymbol serial)

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
        let name = ctx |> findName serial

        let ctx =
          ctx
          |> addLocalVar (ValueSymbol serial) (VarDef(name, StaticSM, noTy, loc))

        let pat, ctx = (pat, ctx) |> goPat vis
        HAsPat(pat, serial, loc), ctx

    | HAnnoPat (pat, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        HAnnoPat(pat, ty, loc), ctx

    | HVariantPat _ -> failwithf "NEVER: HVariantPat is generated in NameRes. %A" pat
    | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

  let rec goExpr (expr, ctx) =
    match expr with
    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat vis
        let next, ctx = (next, ctx) |> goExpr
        HLetValExpr(vis, pat, init, next, ty, loc), ctx

    | HLetFunExpr (serial, vis, _, args, body, next, ty, loc) ->
        let isMainFun = ctx |> findName serial = "main"

        let ctx =
          ctx
          |> enterLetInit
          |> defineFunUniquely serial args noTy loc
          |> leaveLetInit
          |> addVarToModule vis (ValueSymbol serial)

        let next, ctx = (next, ctx) |> goExpr
        HLetFunExpr(serial, vis, isMainFun, args, body, next, ty, loc), ctx

    | HInfExpr (InfOp.Semi, exprs, ty, loc) ->
        let exprs, ctx = (exprs, ctx) |> stMap goExpr
        HInfExpr(InfOp.Semi, exprs, ty, loc), ctx

    | HTyDeclExpr (serial, vis, tyArgs, tyDecl, loc) ->
        let ctx =
          ctx
          |> startDefineTy moduleSerialOpt serial vis tyArgs tyDecl loc

        HTyDeclExpr(serial, vis, tyArgs, tyDecl, loc), ctx

    | _ -> expr, ctx

  goExpr (expr, ctx)

// -----------------------------------------------
// Name Resolution
// -----------------------------------------------

let private nameResPat (pat: HPat, ctx: ScopeCtx) =
  match pat with
  | HLitPat _
  | HDiscardPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _ -> pat, ctx

  | HRefPat (varSerial, ty, loc) when ctx |> findName varSerial = "_" -> HDiscardPat(ty, loc), ctx

  | HRefPat (varSerial, ty, loc) ->
      let name = ctx |> findName varSerial

      let variantSerial =
        match ctx |> resolveLocalVarName name with
        | Some (ValueSymbol varSerial) ->
            match ctx |> findVar varSerial with
            | VariantDef _ -> Some varSerial

            | _ -> None

        | None -> None

      match variantSerial with
      | Some variantSerial -> HVariantPat(variantSerial, ty, loc), ctx

      | None ->
          match name with
          | "None" -> HNonePat(ty, loc), ctx

          | "Some" -> HSomePat(ty, loc), ctx

          | _ ->
              let varDef = VarDef(name, AutoSM, ty, loc)

              let ctx =
                ctx |> addLocalVar (ValueSymbol varSerial) varDef

              HRefPat(varSerial, ty, loc), ctx

  | HNavPat (l, r, ty, loc) ->
      let varSerial =
        match ctx |> resolvePatAsScope l with
        | Some (TySymbol scopeSerial) -> ctx |> resolveScopedVarName scopeSerial r

        | None -> None

      match varSerial with
      | Some (ValueSymbol varSerial) when isVariant varSerial ctx -> HVariantPat(varSerial, ty, loc), ctx
      | Some (ValueSymbol varSerial) -> HRefPat(varSerial, ty, loc), ctx

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
      let name = ctx |> findName serial

      let varDef = VarDef(name, AutoSM, noTy, loc)

      let ctx =
        ctx |> addLocalVar (ValueSymbol serial) varDef

      let pat, ctx = (pat, ctx) |> nameResPat
      HAsPat(pat, serial, loc), ctx

  | HAnnoPat (pat, ty, loc) ->
      let ty, ctx = ctx |> resolveTy ty loc
      let pat, ctx = (pat, ctx) |> nameResPat
      HAnnoPat(pat, ty, loc), ctx

  | HOrPat (l, r, ty, loc) ->
      // FIXME: Currently variable bindings in OR patterns are not supported correctly.
      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HOrPat(l, r, ty, loc), ctx

  | HVariantPat _ -> failwithf "NEVER: HVariantPat is generated in NameRes. %A" pat
  | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

let private nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
  | HErrorExpr _
  | HLitExpr _
  | HPrimExpr _ -> expr, ctx

  | HRefExpr (serial, ty, loc) ->
      let doArm () =
        let name = ctx |> findName serial
        match ctx |> resolveLocalVarName name with
        | Some (ValueSymbol serial) when ctx |> isFun serial -> HFunExpr(serial, ty, loc), ctx

        | Some (ValueSymbol serial) when ctx |> isVariant serial -> HVariantExpr(serial, ty, loc), ctx

        | Some (ValueSymbol serial) -> HRefExpr(serial, ty, loc), ctx

        | None ->
            match primFromIdent name with
            | Some prim -> HPrimExpr(prim, ty, loc), ctx

            | None -> HErrorExpr("Undefined variable " + name, loc), ctx

      doArm ()

  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        let baseOpt, ctx =
          (baseOpt, ctx) |> stOptionMap nameResExpr

        let fields, ctx =
          (fields, ctx)
          |> stMap (fun ((name, init, loc), ctx) ->
               let init, ctx = (init, ctx) |> nameResExpr
               (name, init, loc), ctx)

        HRecordExpr(baseOpt, fields, ty, loc), ctx

      doArm ()

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond, ctx = (cond, ctx) |> nameResExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap (fun ((pat, guard, body), ctx) ->
               let parent, ctx = ctx |> startScope
               let pat, ctx = (pat, ctx) |> nameResPat
               let guard, ctx = (guard, ctx) |> nameResExpr
               let body, ctx = (body, ctx) |> nameResExpr
               let ctx = ctx |> finishScope parent
               (pat, guard, body), ctx)

        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        // FIXME: Patchwork for tests to pass
        match l, r with
        | HRefExpr (serial, _, _), "getSlice" when ctx |> findName serial = "String" ->
            // NOTE: Actually this functions doesn't exist in the F# standard library.
            HPrimExpr(HPrim.StrGetSlice, ty, loc), ctx

        | _ ->

            // Keep the nav expression unresolved so that type inference does.
            let keepUnresolved () =
              let l, ctx = (l, ctx) |> nameResExpr
              HNavExpr(l, r, ty, loc), ctx

            match ctx |> resolveExprAsScope l with
            | Some (TySymbol scopeSerial) ->
                match ctx |> resolveScopedVarName scopeSerial r with
                | Some (ValueSymbol varSerial) when ctx |> isFun varSerial -> HFunExpr(varSerial, ty, loc), ctx

                | Some (ValueSymbol varSerial) when ctx |> isVariant varSerial -> HVariantExpr(varSerial, ty, loc), ctx

                | Some (ValueSymbol varSerial) -> HRefExpr(varSerial, ty, loc), ctx

                | _ ->
                    // X.ty patterns don't appear yet, so don't search for types.

                    keepUnresolved ()

            | _ -> keepUnresolved ()

      doArm ()

  | HInfExpr (op, items, ty, loc) ->
      let doArm () =
        // Necessary in case of annotation expression.
        let ty, ctx = ctx |> resolveTy ty loc

        let items, ctx = (items, ctx) |> stMap nameResExpr
        HInfExpr(op, items, ty, loc), ctx

      doArm ()

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      let doArm () =
        let body, ctx =
          let parent, ctx = ctx |> startScope
          let body, ctx = (body, ctx) |> nameResExpr
          let ctx = ctx |> finishScope parent
          body, ctx

        let pat, next, ctx =
          let parent, ctx = ctx |> startScope
          let pat, ctx = (pat, ctx) |> nameResPat
          let next, ctx = (next, ctx) |> nameResExpr
          let ctx = ctx |> finishScope parent
          pat, next, ctx

        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (serial, vis, isMainFun, pats, body, next, ty, loc) ->
      let doArm () =
        let parent, ctx = ctx |> startScope
        let ctx = ctx |> enterLetInit

        // Define the function itself for recursive referencing.
        // FIXME: Functions are recursive even if `rec` is missing.
        let ctx =
          ctx |> defineFunUniquely serial pats noTy loc

        let pats, body, ctx =
          // Introduce a function body scope.
          let parent, ctx = ctx |> startScope
          let pats, ctx = (pats, ctx) |> stMap nameResPat
          let body, ctx = (body, ctx) |> nameResExpr
          let ctx = ctx |> finishScope parent
          pats, body, ctx

        let ctx = ctx |> leaveLetInit
        let next, ctx = (next, ctx) |> nameResExpr
        let ctx = ctx |> finishScope parent

        HLetFunExpr(serial, vis, isMainFun, pats, body, next, ty, loc), ctx

      doArm ()

  | HTyDeclExpr (serial, _, tyArgs, tyDecl, loc) ->
      let doArm () =
        let ctx =
          ctx |> finishDefineTy serial tyArgs tyDecl loc

        expr, ctx

      doArm ()

  | HOpenExpr (path, _) ->
      let doArm () =
        // FIXME: resolve module-name based on path
        match ctx |> resolveLocalTyName (path |> List.last) with
        | Some (TySymbol moduleSerial) ->
            let ctx = ctx |> openModule moduleSerial

            expr, ctx

        | None -> expr, ctx

      doArm ()

  | HModuleExpr (serial, body, next, loc) ->
      let doArm () =
        let moduleName = ctx |> findName serial

        let ctx =
          ctx
          |> addTy (TySymbol serial) (ModuleTyDef(moduleName, loc))
          |> importTy (TySymbol serial)

        let parent, ctx = ctx |> startScope

        let body, ctx =
          (body, ctx)
          |> collectDecls (Some serial)
          |> nameResExpr

        let ctx = ctx |> finishScope parent

        // HACK: MiloneOnly is auto-open.
        let ctx =
          if moduleName = "MiloneOnly" then ctx |> openModule serial else ctx

        let next, ctx = (next, ctx) |> nameResExpr

        // Module no longer needed.
        spliceExpr body next, ctx

      doArm ()

  | _ -> failwithf "NEVER: HVariantExpr is generated in NameRes. %A" expr

let nameRes (expr: HExpr, nameCtx: NameCtx): HExpr * ScopeCtx =
  let scopeCtx = ofNameCtx nameCtx

  match expr with
  | HModuleExpr _ -> (expr, scopeCtx) |> nameResExpr

  | _ ->
      (expr, scopeCtx)
      |> collectDecls None
      |> nameResExpr
