/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneLang.NameRes

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeIntegers
open MiloneLang.Hir

let private isNoTy ty =
  match ty with
  | ErrorTy _ -> true
  | _ -> false

// -----------------------------------------------
// Type primitives
// -----------------------------------------------

let private tyPrimOfName name tys loc =
  match name, tys with
  | "unit", [] -> tyUnit
  | "bool", [] -> tyBool

  | "int", []
  | "int32", [] -> tyInt
  | "uint", []
  | "uint32", [] -> AppTy(IntTyCtor(IntFlavor(Unsigned, I32)), [])
  | "sbyte", []
  | "int8", [] -> AppTy(IntTyCtor(IntFlavor(Signed, I8)), [])
  | "byte", []
  | "uint8", [] -> AppTy(IntTyCtor(IntFlavor(Unsigned, I8)), [])

  | "int16", [] -> AppTy(IntTyCtor(IntFlavor(Signed, I16)), [])
  | "int64", [] -> AppTy(IntTyCtor(IntFlavor(Signed, I64)), [])
  | "nativeint", [] -> AppTy(IntTyCtor(IntFlavor(Signed, IPtr)), [])
  | "uint16", [] -> AppTy(IntTyCtor(IntFlavor(Unsigned, I16)), [])
  | "uint64", [] -> AppTy(IntTyCtor(IntFlavor(Unsigned, I64)), [])
  | "unativeint", [] -> AppTy(IntTyCtor(IntFlavor(Unsigned, IPtr)), [])

  | "char", [] -> tyChar
  | "string", [] -> tyStr
  | "obj", [] -> tyObj

  | "option", [ itemTy ] ->
      // FIXME: option is just an alias of list for now
      tyList itemTy

  | "list", [ itemTy ] -> tyList itemTy

  | "nativeptr", [ itemTy ] -> AppTy(NativePtrTyCtor IsMut, [ itemTy ])
  | "constptr", [ itemTy ] -> AppTy(NativePtrTyCtor IsConst, [ itemTy ])

  | _ ->
      // FIXME: Report error correctly
      printfn "#error tyPrimOfName name=%s loc=%s" name (locToString loc)
      ErrorTy loc

// -----------------------------------------------
// Symbols
// -----------------------------------------------

let private valueSymbolToSerial symbol =
  match symbol with
  | VarSymbol (VarSerial s) -> s
  | FunSymbol (FunSerial s) -> s
  | VariantSymbol (VariantSerial s) -> s

let private tySymbolToSerial symbol =
  match symbol with
  | MetaTySymbol s -> s
  | UnivTySymbol s -> s
  | SynonymTySymbol s -> s
  | UnionTySymbol s -> s
  | RecordTySymbol s -> s
  | ModuleTySymbol (ModuleTySerial s) -> s

// -----------------------------------------------
// Namespace
// -----------------------------------------------

type Ns<'K, 'V> = AssocMap<'K, (AssocMap<Ident, 'V>)>

// FIXME: this emits code that doesn't compile due to use of incomplete type
// type NameTree = NameTree of AssocMap<Serial, Serial list>
//   > error: invalid use of undefined type ‘struct UnitNameTree_Fun1’
//   >        struct NameTree_ app_193 = nameTreeEmpty_.fun(nameTreeEmpty_.env, 0);
// let nameTreeEmpty: unit -> NameTree =
//   let it = NameTree(mapEmpty (intHash, compare))
//   fun () -> it

let private nsFind (key: Serial) (ns: Ns<_, _>): AssocMap<Ident, _> =
  match ns |> mapTryFind key with
  | Some submap -> submap
  | None -> mapEmpty compare

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

let private scopeMapEmpty (): AssocMap<Ident, _> = mapEmpty compare

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

    Funs: AssocMap<FunSerial, FunDef>

    Variants: AssocMap<VariantSerial, VariantDef>

    /// Serial of value (variable/fun/variant) to let-depth map.
    VarDepths: AssocMap<Serial, LetDepth>

    /// Type serial to definition map.
    Tys: AssocMap<TySerial, TyDef>

    ModuleTys: AssocMap<ModuleTySerial, ModuleTyDef>

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
    Vars = mapEmpty varSerialCmp
    Funs = mapEmpty funSerialCmp
    Variants = mapEmpty variantSerialCmp
    VarDepths = mapEmpty compare
    Tys = mapEmpty compare
    ModuleTys = mapEmpty moduleTySerialCmp
    TyDepths = mapEmpty compare
    VarNs = mapEmpty compare
    TyNs = mapEmpty compare
    LocalSerial = localSerial
    Local = scopeEmpty ()
    LetDepth = 0 }

let private findName serial (scopeCtx: ScopeCtx): Ident = scopeCtx.NameMap |> mapFind serial

let private findVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Vars |> mapContainsKey varSerial)
  scopeCtx.Vars |> mapFind varSerial

let private findFun funSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Funs |> mapContainsKey funSerial)
  scopeCtx.Funs |> mapFind funSerial

let private findVariant variantSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Variants |> mapContainsKey variantSerial)
  scopeCtx.Variants |> mapFind variantSerial

let private findTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Tys |> mapContainsKey tySerial)
  scopeCtx.Tys |> mapFind tySerial

let private findModuleTy moduleSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.ModuleTys |> mapContainsKey moduleSerial)
  scopeCtx.ModuleTys |> mapFind moduleSerial

let private findTyName tySymbol (scopeCtx: ScopeCtx) =
  match tySymbol with
  | ModuleTySymbol moduleSerial -> (scopeCtx |> findModuleTy moduleSerial).Name
  | _ ->
      scopeCtx
      |> findTy (tySymbolToSerial tySymbol)
      |> tyDefToName

/// Defines a variable, without adding to any scope.
let private addVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  // Merge into current definition.
  let varDef =
    match scopeCtx.Vars |> mapTryFind varSerial, varDef with
    | Some (VarDef (_, StaticSM, _, _)), VarDef (name, _, ty, loc) -> VarDef(name, StaticSM, ty, loc)
    | _ -> varDef

  { scopeCtx with
      Vars = scopeCtx.Vars |> mapAdd varSerial varDef
      VarDepths =
        scopeCtx.VarDepths
        |> mapAdd (varSerialToInt varSerial) scopeCtx.LetDepth }

let private addFunDef funSerial funDef (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      Funs = scopeCtx.Funs |> mapAdd funSerial funDef
      VarDepths =
        scopeCtx.VarDepths
        |> mapAdd (funSerialToInt funSerial) scopeCtx.LetDepth }

let private addVariantDef variantSerial variantDef (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      Variants =
        scopeCtx.Variants
        |> mapAdd variantSerial variantDef
      VarDepths =
        let (VariantSerial variantSerial) = variantSerial
        scopeCtx.VarDepths
        |> mapAdd variantSerial scopeCtx.LetDepth }

/// Defines a type, without adding to any scope.
let private addTy tySymbol tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  let tySerial = tySymbolToSerial tySymbol

  { scopeCtx with
      Tys = scopeCtx.Tys |> mapAdd tySerial tyDef
      TyDepths =
        scopeCtx.TyDepths
        |> mapAdd tySerial scopeCtx.LetDepth }

let private addModuleTyDef moduleTySerial tyDef (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      ModuleTys = scopeCtx.ModuleTys |> mapAdd moduleTySerial tyDef
      TyDepths =
        scopeCtx.TyDepths
        |> mapAdd (moduleTySerialToInt moduleTySerial) scopeCtx.LetDepth }

/// Defines an unbound meta type.
let private addUnboundMetaTy tySerial (scopeCtx: ScopeCtx): ScopeCtx =
  { scopeCtx with
      TyDepths =
        scopeCtx.TyDepths
        |> mapAdd tySerial scopeCtx.LetDepth }

/// Adds a variable to a namespace.
let private addVarToNs tySerial valueSymbol (scopeCtx: ScopeCtx): ScopeCtx =
  let name =
    scopeCtx
    |> findName (valueSymbolToSerial valueSymbol)

  { scopeCtx with
      VarNs = scopeCtx.VarNs |> nsAdd tySerial name valueSymbol }

/// Adds a type to a namespace.
let private addTyToNs parentTySerial tySymbol (scopeCtx: ScopeCtx): ScopeCtx =
  let name =
    scopeCtx |> findName (tySymbolToSerial tySymbol)

  { scopeCtx with
      TyNs =
        scopeCtx.TyNs
        |> nsAdd parentTySerial name tySymbol }

/// Adds a variable to a scope.
let private importVar symbol (scopeCtx: ScopeCtx): ScopeCtx =
  let varName =
    match symbol with
    | VarSymbol varSerial -> scopeCtx |> findVar varSerial |> varDefToName
    | FunSymbol funSerial -> (scopeCtx |> findFun funSerial).Name
    | VariantSymbol variantSerial -> (scopeCtx |> findVariant variantSerial).Name

  assert (varName <> "_")

  let scope: Scope =
    match scopeCtx.Local with
    | map :: varScopes, tyScopes ->
        let varScopes =
          (map |> mapAdd varName symbol) :: varScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  { scopeCtx with Local = scope }

/// Adds a type to a scope, aliasing a name.
let private doImportTyWithAlias alias symbol (scopeCtx: ScopeCtx): ScopeCtx =
  let scope: Scope =
    match scopeCtx.Local with
    | varScopes, map :: tyScopes ->
        let tyScopes = (map |> mapAdd alias symbol) :: tyScopes

        varScopes, tyScopes

    | _ -> failwith "NEVER: Scope can't be empty."

  { scopeCtx with Local = scope }

let private importTy symbol (scopeCtx: ScopeCtx): ScopeCtx =
  let tyName = findTyName symbol scopeCtx
  doImportTyWithAlias tyName symbol scopeCtx

let private openModule moduleSerial (scopeCtx: ScopeCtx) =
  // Import vars.
  let scopeCtx =
    scopeCtx.VarNs
    |> nsFind (moduleTySerialToInt moduleSerial)
    |> mapFold (fun ctx _ symbol -> ctx |> importVar symbol) scopeCtx

  // Import tys.
  let scopeCtx =
    scopeCtx.TyNs
    |> nsFind (moduleTySerialToInt moduleSerial)
    |> mapFold (fun ctx _ symbol -> ctx |> importTy symbol) scopeCtx

  scopeCtx

/// Defines a variable in the local scope.
let private addLocalVar varSerial varDef (scopeCtx: ScopeCtx): ScopeCtx =
  scopeCtx
  |> addVar varSerial varDef
  |> importVar (VarSymbol varSerial)

/// Defines a type in the local scope.
let private addLocalTy tySymbol tyDef (scopeCtx: ScopeCtx): ScopeCtx =
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

  | HRefPat (varSerial, _, _) ->
      let name =
        let (VarSerial serial) = varSerial
        scopeCtx |> findName serial

      scopeCtx |> resolveLocalTyName name

  | _ -> None

/// Resolves an expressions as scope: type, module or namespace.
let private resolveExprAsScope expr scopeCtx =
  match expr with
  | HNavExpr _ ->
      // A.B.C (= (A.B).C) case
      failwith "unimpl"

  | HRefExpr (varSerial, _, _) ->
      let name =
        scopeCtx |> findName (varSerialToInt varSerial)

      // HACK: Don't find from synonyms, from module instead.
      match scopeCtx |> resolveLocalTyName name with
      | Some (SynonymTySymbol _) -> scopeCtx |> resolveLocalTyName (name + "Module")
      | it -> it

  | _ -> None

/// Resolves type names in a type expression.
let private resolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | ErrorTy _ -> ty, scopeCtx

    | AppTy (UnresolvedTyCtor serial, []) when (scopeCtx |> findName serial) = "_" ->
        // Handle wildcard type.
        let scopeCtx = scopeCtx |> addUnboundMetaTy serial

        MetaTy(serial, loc), scopeCtx

    | AppTy (UnresolvedTyCtor serial, tys) ->
        let name = scopeCtx |> findName serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go

        match scopeCtx |> resolveLocalTyName name with
        | Some (MetaTySymbol tySerial) ->
            failwithf "meta ty cannot be applied: %A" (serial, tys)
            MetaTy(tySerial, loc), scopeCtx

        | Some (UnivTySymbol tySerial) -> MetaTy(tySerial, loc), scopeCtx

        | Some (SynonymTySymbol tySerial) ->
            // Arity check.
            // FIXME: proper error handling
            match scopeCtx.Tys |> mapTryFind tySerial with
            | Some (SynonymTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> List.length tys ->
                failwithf "synonym arity mismatch: %A" (tySerial, tys, name, defTyArgs, loc)

            | _ -> tySynonym tySerial tys, scopeCtx

        | Some (UnionTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyUnion tySerial, scopeCtx

        | Some (RecordTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyRecord tySerial, scopeCtx

        | Some (ModuleTySymbol _) -> failwith "module can't be used as type."

        | None -> tyPrimOfName name tys loc, scopeCtx

    | AppTy (tyCtor, tys) ->
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        AppTy(tyCtor, tys), scopeCtx

    | _ -> ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let private defineFunUniquely funSerial args ty loc (scopeCtx: ScopeCtx): ScopeCtx =
  match scopeCtx.Funs |> mapTryFind funSerial with
  | Some _ -> scopeCtx

  | None ->
      let name =
        scopeCtx |> findName (funSerialToInt funSerial)

      let funDef: FunDef =
        { Name = name
          Arity = args |> List.length
          Ty = TyScheme([], ty)
          Loc = loc }

      let scopeCtx =
        scopeCtx
        |> addFunDef funSerial funDef
        |> importVar (FunSymbol funSerial)

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
    | Some moduleSerial, PublicVis ->
        ctx
        |> addVarToNs (moduleTySerialToInt moduleSerial) varSerial

    | _ -> ctx

  let addTyToModule tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addTyToNs (moduleTySerialToInt moduleSerial) tySerial

    | _ -> ctx

  let tyName = ctx |> findName tySerial

  if ctx.Tys |> mapContainsKey tySerial then
    ctx
  else

    match tyDecl with
    | TySynonymDecl (body, _) ->
        let tySymbol = SynonymTySymbol tySerial

        ctx
        |> addLocalTy tySymbol (SynonymTyDef(tyName, tyArgs, body, loc))
        |> addTyToModule tySymbol

    | UnionTyDecl (_, variants, _unionLoc) ->
        let defineVariant ctx (name, variantSerial, hasPayload, payloadTy) =
          let variantSymbol = VariantSymbol variantSerial

          let variantDef: VariantDef =
            { Name = name
              UnionTySerial = tySerial
              HasPayload = hasPayload
              PayloadTy = payloadTy
              VariantTy = noTy
              Loc = loc }

          ctx
          |> addVariantDef variantSerial variantDef
          |> addVarToNs tySerial variantSymbol
          |> importVar variantSymbol
          |> addVarToModule variantSymbol

        let ctx = variants |> List.fold defineVariant ctx

        let tySymbol = UnionTySymbol tySerial

        let tyDef =
          let variantSerials =
            variants
            |> List.map (fun (_, variantSerial, _, _) -> variantSerial)

          UnionTyDef(tyName, variantSerials, loc)

        ctx
        |> addLocalTy tySymbol tyDef
        |> addTyToModule tySymbol

    | RecordTyDecl (_, fields, loc) ->
        let tySymbol = RecordTySymbol tySerial

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
      |> addTy (MetaTySymbol tySerial) (MetaTyDef(tyName, bodyTy, loc))

  | UniversalTyDef _ -> ctx

  | SynonymTyDef (tyName, tyArgs, bodyTy, loc) ->
      let parent, ctx = ctx |> startScope

      let ctx =
        tyArgs
        |> List.fold (fun ctx tyArg ->
             let name = ctx |> findName tyArg
             ctx
             |> addLocalTy (UnivTySymbol tyArg) (UniversalTyDef(name, loc))) ctx

      let bodyTy, ctx = ctx |> resolveTy bodyTy loc
      let ctx = ctx |> finishScope parent

      ctx
      |> addTy (SynonymTySymbol tySerial) (SynonymTyDef(tyName, tyArgs, bodyTy, loc))

  | UnionTyDef (_, variantSerials, _unionLoc) ->
      let go ctx variantSerial =
        let def = ctx |> findVariant variantSerial
        let payloadTy, ctx = ctx |> resolveTy def.PayloadTy loc
        assert (def.VariantTy |> isNoTy)
        ctx
        |> addVariantDef variantSerial { def with PayloadTy = payloadTy }

      variantSerials |> List.fold go ctx

  | RecordTyDef (tyName, fields, loc) ->
      let resolveField ((name, ty, loc), ctx) =
        let ty, ctx = ctx |> resolveTy ty loc
        (name, ty, loc), ctx

      let fields, ctx = (fields, ctx) |> stMap resolveField
      ctx
      |> addTy (RecordTySymbol tySerial) (RecordTyDef(tyName, fields, loc))

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// This stage, traverse declarations directly inside `module rec`s
// to create variables/types pre-definitions
// so that mutually recursive references resolve correctly.

let private collectDecls moduleSerialOpt (expr, ctx) =
  let addVarToModule vis varSerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addVarToNs (moduleTySerialToInt moduleSerial) varSerial

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

    | HRefPat (varSerial, ty, loc) ->
        let name =
          ctx |> findName (varSerialToInt varSerial)

        match ctx |> resolveLocalVarName name with
        | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

        | _ ->
            let ctx =
              ctx
              |> addLocalVar varSerial (VarDef(name, StaticSM, ty, loc))
              |> addVarToModule vis (VarSymbol varSerial)

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

    | HAsPat (pat, varSerial, loc) ->
        let name =
          ctx |> findName (varSerialToInt varSerial)

        let ctx =
          ctx
          |> addLocalVar varSerial (VarDef(name, StaticSM, noTy, loc))

        let pat, ctx = (pat, ctx) |> goPat vis
        HAsPat(pat, varSerial, loc), ctx

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

    | HLetFunExpr (funSerial, vis, _, args, body, next, ty, loc) ->
        let isMainFun =
          ctx
          |> findName (funSerialToInt funSerial) = "main"

        let ctx =
          ctx
          |> enterLetInit
          |> defineFunUniquely funSerial args noTy loc
          |> leaveLetInit
          |> addVarToModule vis (FunSymbol funSerial)

        let next, ctx = (next, ctx) |> goExpr
        HLetFunExpr(funSerial, vis, isMainFun, args, body, next, ty, loc), ctx

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

  | HRefPat (varSerial, ty, loc) when ctx |> findName (varSerialToInt varSerial) = "_" -> HDiscardPat(ty, loc), ctx

  | HRefPat (varSerial, ty, loc) ->
      let name =
        ctx |> findName (varSerialToInt varSerial)

      match ctx |> resolveLocalVarName name with
      | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

      | _ ->
          match name with
          | "None" -> HNonePat(ty, loc), ctx

          | "Some" -> HSomePat(ty, loc), ctx

          | _ ->
              let ctx =
                ctx
                |> addLocalVar varSerial (VarDef(name, AutoSM, ty, loc))

              HRefPat(varSerial, ty, loc), ctx

  | HNavPat (l, r, ty, loc) ->
      let varSerial =
        match ctx |> resolvePatAsScope l with
        | Some symbol ->
            ctx
            |> resolveScopedVarName (tySymbolToSerial symbol) r

        | None -> None

      match varSerial with
      | Some (VarSymbol varSerial) -> HRefPat(varSerial, ty, loc), ctx

      | Some (FunSymbol _) ->
          // FIXME: proper error handling
          failwith "Function can't be a pattern."

      | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

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

  | HAsPat (pat, varSerial, loc) ->
      let name =
        ctx |> findName (varSerialToInt varSerial)

      let ctx =
        ctx
        |> addLocalVar varSerial (VarDef(name, AutoSM, noTy, loc))

      let pat, ctx = (pat, ctx) |> nameResPat
      HAsPat(pat, varSerial, loc), ctx

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

  | HRefExpr (varSerial, ty, loc) ->
      let doArm () =
        let name =
          ctx |> findName (varSerialToInt varSerial)

        match ctx |> resolveLocalVarName name with
        | Some (VarSymbol serial) -> HRefExpr(serial, ty, loc), ctx
        | Some (FunSymbol serial) -> HFunExpr(serial, ty, loc), ctx
        | Some (VariantSymbol serial) -> HVariantExpr(serial, ty, loc), ctx

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
        | HRefExpr (varSerial, _, _), "getSlice" when ctx
                                                      |> findName (varSerialToInt varSerial) = "String" ->
            // NOTE: Actually this functions doesn't exist in the F# standard library.
            HPrimExpr(HPrim.StrGetSlice, ty, loc), ctx

        | _ ->

            // Keep the nav expression unresolved so that type inference does.
            let keepUnresolved () =
              let l, ctx = (l, ctx) |> nameResExpr
              HNavExpr(l, r, ty, loc), ctx

            match ctx |> resolveExprAsScope l with
            | Some tySymbol ->
                let scopeSerial = tySymbolToSerial tySymbol
                match ctx |> resolveScopedVarName scopeSerial r with
                | Some (VarSymbol varSerial) -> HRefExpr(varSerial, ty, loc), ctx
                | Some (FunSymbol funSerial) -> HFunExpr(funSerial, ty, loc), ctx
                | Some (VariantSymbol variantSerial) -> HVariantExpr(variantSerial, ty, loc), ctx

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
        | Some (ModuleTySymbol moduleSerial) ->
            let ctx = ctx |> openModule moduleSerial
            expr, ctx

        | _ -> expr, ctx

      doArm ()

  | HModuleExpr (serial, body, next, loc) ->
      let doArm () =
        let moduleName =
          ctx |> findName (moduleTySerialToInt serial)

        let tyDef: ModuleTyDef = { Name = moduleName; Loc = loc }

        let ctx =
          ctx
          |> addModuleTyDef serial tyDef
          |> importTy (ModuleTySymbol serial)

        // HACK: Define module alias for the case it is shadowed by another module.
        //       (F# solves this by merging namespaces of types, but such behavior is unimplemented.)
        let ctx =
          ctx
          |> doImportTyWithAlias (moduleName + "Module") (ModuleTySymbol serial)

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
