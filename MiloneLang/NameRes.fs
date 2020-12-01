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
  | "unit", [] -> Some tyUnit
  | "bool", [] -> Some tyBool

  | "int", []
  | "int32", [] -> Some tyInt
  | "uint", []
  | "uint32", [] ->
      AppTy(IntTyCtor(IntFlavor(Unsigned, I32)), [])
      |> Some
  | "sbyte", []
  | "int8", [] ->
      AppTy(IntTyCtor(IntFlavor(Signed, I8)), [])
      |> Some
  | "byte", []
  | "uint8", [] ->
      AppTy(IntTyCtor(IntFlavor(Unsigned, I8)), [])
      |> Some

  | "int16", [] ->
      AppTy(IntTyCtor(IntFlavor(Signed, I16)), [])
      |> Some
  | "int64", [] ->
      AppTy(IntTyCtor(IntFlavor(Signed, I64)), [])
      |> Some
  | "nativeint", [] ->
      AppTy(IntTyCtor(IntFlavor(Signed, IPtr)), [])
      |> Some
  | "uint16", [] ->
      AppTy(IntTyCtor(IntFlavor(Unsigned, I16)), [])
      |> Some
  | "uint64", [] ->
      AppTy(IntTyCtor(IntFlavor(Unsigned, I64)), [])
      |> Some
  | "unativeint", [] ->
      AppTy(IntTyCtor(IntFlavor(Unsigned, IPtr)), [])
      |> Some

  | "float", [] -> Some tyFloat
  | "char", [] -> Some tyChar
  | "string", [] -> Some tyStr
  | "obj", [] -> Some tyObj

  | "option", [ itemTy ] ->
      // FIXME: option is just an alias of list for now
      Some(tyList itemTy)

  | "list", [ itemTy ] -> Some(tyList itemTy)

  | "voidptr", [] ->
      AppTy(NativePtrTyCtor IsMut, [ AppTy(VoidTyCtor, []) ])
      |> Some
  | "voidconstptr", [] ->
      AppTy(NativePtrTyCtor IsConst, [ AppTy(VoidTyCtor, []) ])
      |> Some
  | "nativeptr", [ itemTy ] -> AppTy(NativePtrTyCtor IsMut, [ itemTy ]) |> Some
  | "constptr", [ itemTy ] -> AppTy(NativePtrTyCtor IsConst, [ itemTy ]) |> Some

  | _ -> None

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

    /// Variables defined in current pattern.
    ///
    /// name -> (varSerial, definedLoc, usedLoc list)
    PatScope: AssocMap<Ident, VarSerial * Loc * Loc list>

    /// Current let-depth, the number of ancestral let-body.
    LetDepth: LetDepth

    Logs: (NameResLog * Loc) list }

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
    PatScope = mapEmpty compare
    LetDepth = 0
    Logs = [] }

let private addLog (log: NameResLog) (loc: Loc) (ctx: ScopeCtx) =
  { ctx with
      Logs = (log, loc) :: ctx.Logs }

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
    scopeCtx.TyNs
    |> nsFind scopeSerial
    |> mapTryFind name

let private resolveLocalVarName name (scopeCtx: ScopeCtx) =
  scopeCtx
  |> resolveScopedVarName scopeCtx.LocalSerial name

let private resolveLocalTyName name (scopeCtx: ScopeCtx) =
  scopeCtx
  |> resolveScopedTyName scopeCtx.LocalSerial name

let private resolvePatAsScope pat scopeCtx =
  match pat with
  | HNavPat _ ->
      let scopeCtx =
        scopeCtx
        |> addLog (OtherNameResLog "nested nav pattern is unimplemented") (patToLoc pat)

      None, scopeCtx

  | HRefPat (varSerial, _, _) ->
      let name =
        scopeCtx |> findName (varSerialToInt varSerial)

      scopeCtx |> resolveLocalTyName name, scopeCtx

  | _ -> None, scopeCtx

/// Resolves an expressions as scope: type, module or namespace.
let private resolveExprAsScope expr scopeCtx =
  match expr with
  | HNavExpr _ ->
      let scopeCtx =
        scopeCtx
        |> addLog (OtherNameResLog "nested nav expr is unimplemented") (exprToLoc expr)

      None, scopeCtx

  | HRefExpr (varSerial, _, loc) ->
      let name =
        scopeCtx |> findName (varSerialToInt varSerial)

      // HACK: Don't find from synonyms, from module instead.
      match scopeCtx |> resolveLocalTyName name with
      | Some (SynonymTySymbol _) -> scopeCtx |> resolveLocalTyName (name + "Module"), scopeCtx
      | it -> it, scopeCtx

  | _ -> None, scopeCtx

/// Resolves type names in a type expression.
let private resolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | ErrorTy _ -> ty, scopeCtx

    | AppTy (UnresolvedTyCtor ([], serial), []) when (scopeCtx |> findName serial) = "_" ->
        // Handle wildcard type.
        let scopeCtx = scopeCtx |> addUnboundMetaTy serial

        MetaTy(serial, loc), scopeCtx

    | AppTy (UnresolvedTyCtor (quals, serial), tys) ->
        let qualNames =
          quals
          |> List.map (fun qual -> scopeCtx |> findName qual)

        let name = scopeCtx |> findName serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go

        let arity = List.length tys

        let symbolOpt, scopeCtx =
          match qualNames with
          | [] -> scopeCtx |> resolveLocalTyName name, scopeCtx

          | [ baseQual ] ->
              let tySymbolOpt = scopeCtx |> resolveLocalTyName baseQual

              match tySymbolOpt with
              | Some tySymbol ->
                  scopeCtx
                  |> resolveScopedTyName (tySymbolToSerial tySymbol) name,
                  scopeCtx

              | None -> None, scopeCtx

          | _ ->
              None,
              scopeCtx
              |> addLog (OtherNameResLog "Type with 2+ '.'s is unimplemented") loc

        match symbolOpt with
        | Some (MetaTySymbol tySerial) ->
            if arity > 0 then
              let scopeCtx =
                scopeCtx
                |> addLog (TyArityError(name, arity, 0)) loc

              ErrorTy loc, scopeCtx
            else
              MetaTy(tySerial, loc), scopeCtx

        | Some (UnivTySymbol tySerial) -> MetaTy(tySerial, loc), scopeCtx

        | Some (SynonymTySymbol tySerial) ->
            // Arity check.
            match scopeCtx.Tys |> mapTryFind tySerial with
            | Some (SynonymTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> arity ->
                let scopeCtx =
                  scopeCtx
                  |> addLog (TyArityError(name, arity, List.length defTyArgs)) loc

                ErrorTy loc, scopeCtx

            | _ -> tySynonym tySerial tys, scopeCtx

        | Some (UnionTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyUnion tySerial, scopeCtx

        | Some (RecordTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyRecord tySerial, scopeCtx

        | Some (ModuleTySymbol _) ->
            let scopeCtx =
              scopeCtx |> addLog (ModuleUsedAsTyError name) loc

            ErrorTy loc, scopeCtx

        | None ->
            match tyPrimOfName name tys loc with
            | Some ty -> ty, scopeCtx
            | None ->
                let scopeCtx =
                  scopeCtx |> addLog (UndefinedTyError name) loc

                ErrorTy loc, scopeCtx

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

  let addTyToModule vis tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addTyToNs (moduleTySerialToInt moduleSerial) tySerial

    | _ -> ctx

  let rec goPat vis (pat, ctx) =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _
    | HNavPat _
    | HNilPat _
    | HNonePat _
    | HSomePat _
    | HOrPat _ -> pat, ctx

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

    | HModuleExpr (serial, body, next, loc) ->
        let ctx =
          ctx
          |> addTyToModule PublicVis (ModuleTySymbol serial)
          |> importTy (ModuleTySymbol serial)

        let next, ctx = (next, ctx) |> goExpr

        HModuleExpr(serial, body, next, loc), ctx

    | _ -> expr, ctx

  goExpr (expr, ctx)

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private doResolveVarInPat serial name ty loc (ctx: ScopeCtx) =
  match ctx.PatScope |> mapTryFind name with
  | None ->
      let varSerial = VarSerial serial

      let ctx =
        { ctx with
            PatScope = ctx.PatScope |> mapAdd name (varSerial, loc, []) }
        |> addLocalVar varSerial (VarDef(name, AutoSM, ty, loc))

      varSerial, ctx

  | Some (varSerial, defLoc, useLocs) ->
      let ctx =
        { ctx with
            PatScope =
              ctx.PatScope
              |> mapAdd name (varSerial, defLoc, loc :: useLocs) }

      varSerial, ctx

let private nameResRefPat serial ty loc ctx =
  let name = ctx |> findName serial

  if name = "_" then
    HDiscardPat(ty, loc), ctx
  else
    match ctx |> resolveLocalVarName name with
    | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

    | _ ->
        match name with
        | "None" -> HNonePat(ty, loc), ctx
        | "Some" -> HSomePat(ty, loc), ctx

        | _ ->
            let varSerial, ctx = doResolveVarInPat serial name ty loc ctx
            HRefPat(varSerial, ty, loc), ctx

let private nameResNavPat l r ty loc ctx =
  let varSerialOpt, ctx =
    match ctx |> resolvePatAsScope l with
    | Some symbol, ctx ->
        (ctx
         |> resolveScopedVarName (tySymbolToSerial symbol) r),
        ctx

    | None, ctx -> None, ctx

  match varSerialOpt with
  | Some (VarSymbol varSerial) -> HRefPat(varSerial, ty, loc), ctx

  | Some (FunSymbol _) ->
      let ctx = ctx |> addLog (FunPatError r) loc
      HDiscardPat(noTy, loc), ctx

  | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

  | None ->
      let ctx =
        ctx
        |> addLog (OtherNameResLog "Couldn't resolve nav pattern.") loc

      HDiscardPat(noTy, loc), ctx

let private nameResAsPat bodyPat serial loc ctx =
  let bodyPat, ctx = (bodyPat, ctx) |> nameResPat

  let varSerial, ctx =
    let name = ctx |> findName serial
    doResolveVarInPat serial name noTy loc ctx

  HAsPat(bodyPat, varSerial, loc), ctx

let private nameResPat (pat: HPat, ctx: ScopeCtx) =
  match pat with
  | HLitPat _
  | HDiscardPat _
  | HVariantPat _
  | HNilPat _
  | HNonePat _
  | HSomePat _ -> pat, ctx

  | HRefPat (VarSerial serial, ty, loc) -> nameResRefPat serial ty loc ctx

  | HNavPat (l, r, ty, loc) -> nameResNavPat l r ty loc ctx

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

  | HAsPat (bodyPat, VarSerial serial, loc) -> nameResAsPat bodyPat serial loc ctx

  | HAnnoPat (bodyPat, ty, loc) ->
      let ty, ctx = ctx |> resolveTy ty loc
      let bodyPat, ctx = (bodyPat, ctx) |> nameResPat
      HAnnoPat(bodyPat, ty, loc), ctx

  | HOrPat (l, r, ty, loc) ->
      // No OR patterns appear in arm patterns due to normalization.
      // So we can assume that it's inside of irrefutable pattern.
      let ctx =
        ctx
        |> addLog (OtherNameResLog "OR pattern is disallowed in let expressions.") loc

      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HOrPat(l, r, ty, loc), ctx

  | HBoxPat _ -> failwithf "NEVER: HBoxPat is generated in AutoBoxing. %A" pat

let private doWithPatScope patScopeOpt (f: ScopeCtx -> _ * ScopeCtx) (ctx: ScopeCtx) =
  let parentPatScope, ctx =
    ctx.PatScope,
    { ctx with
        PatScope =
          patScopeOpt
          |> Option.defaultValue (mapEmpty compare) }

  let result, ctx = f ctx

  let patScope, ctx =
    ctx.PatScope, { ctx with PatScope = parentPatScope }

  (patScope, result), ctx

let private nameResRefutablePat (pat: HPat, ctx: ScopeCtx) =
  let loc = patToLoc pat

  let pat, pats =
    match patNormalize pat with
    | [] -> failwith "NEVER"
    | pat :: pats -> pat, pats

  let (lScope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat (pat, ctx))

  let ctx =
    lScope
    |> mapFold (fun ctx (_: string) (_, _, useLocs) ->
         match useLocs with
         | [] -> ctx
         | loc :: _ ->
             ctx
             |> addLog (OtherNameResLog "Variable name conflicts") loc) ctx

  // Set of variables defined in the left-hand side.
  let varSerialSet =
    lScope
    |> mapToList
    |> List.map (fun (_: string, (varSerial, _, _)) -> varSerial)
    |> setOfList varSerialCmp

  let pats, ctx =
    (pats, ctx)
    |> stMap (fun (pat, ctx) ->
         let (rScope, pat), ctx =
           ctx
           |> doWithPatScope (Some lScope) (fun ctx -> nameResPat (pat, ctx))

         // Validate that each variable defined in the left-hand side
         // appears also right-hand side exactly once.
         let ok =
           let ok, set =
             rScope
             |> mapFold (fun (ok, set) (_: string) (varSerial: VarSerial, _, usedLocs) ->
                  match usedLocs with
                  | [ _ ] when ok ->
                      let removed, set = set |> setRemove varSerial
                      ok && removed, set

                  | _ -> false, set) (true, varSerialSet)

           ok && setIsEmpty set

         let ctx =
           if ok then
             ctx
           else
             ctx
             |> addLog (OtherNameResLog "OR pattern binds different set of variables") loc

         pat, ctx)

  let pat =
    (pat :: pats)
    |> List.reduce (fun l r -> HOrPat(l, r, noTy, loc))

  pat, ctx

let private nameResIrrefutablePat (pat: HPat, ctx: ScopeCtx) =
  let (scope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat (pat, ctx))

  let ctx =
    scope
    |> mapFold (fun ctx (_: string) (_, _, useLocs) ->
         match useLocs with
         | [] -> ctx
         | loc :: _ ->
             ctx
             |> addLog (OtherNameResLog "Variable name conflicts") loc) ctx

  pat, ctx

// -----------------------------------------------
// Expression
// -----------------------------------------------

let private nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
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

            | None ->
                let ctx =
                  ctx |> addLog (UndefinedValueError name) loc

                HInfExpr(InfOp.Abort, [], ty, loc), ctx

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
               let pat, ctx = (pat, ctx) |> nameResRefutablePat
               let guard, ctx = (guard, ctx) |> nameResExpr
               let body, ctx = (body, ctx) |> nameResExpr
               let ctx = ctx |> finishScope parent
               (pat, guard, body), ctx)

        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        // Keep the nav expression unresolved so that type inference does.
        let keepUnresolved ctx =
          let l, ctx = (l, ctx) |> nameResExpr
          HNavExpr(l, r, ty, loc), ctx

        let tySymbolOpt, ctx = ctx |> resolveExprAsScope l
        match tySymbolOpt with
        | Some tySymbol ->
            let scopeSerial = tySymbolToSerial tySymbol
            match ctx |> resolveScopedVarName scopeSerial r with
            | Some (VarSymbol varSerial) -> HRefExpr(varSerial, ty, loc), ctx
            | Some (FunSymbol funSerial) -> HFunExpr(funSerial, ty, loc), ctx
            | Some (VariantSymbol variantSerial) -> HVariantExpr(variantSerial, ty, loc), ctx

            | _ ->
                // X.ty patterns don't appear yet, so don't search for types.

                keepUnresolved ctx

        | _ -> keepUnresolved ctx

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
          let pat, ctx = (pat, ctx) |> nameResIrrefutablePat
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

          let pats, ctx =
            (pats, ctx) |> stMap nameResIrrefutablePat

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

  | HOpenExpr (path, loc) ->
      let doArm () =
        let ctx =
          // FIXME: resolve module-name based on path
          let tySymbolOpt =
            ctx |> resolveLocalTyName (path |> List.last)

          match tySymbolOpt with
          | Some (ModuleTySymbol moduleSerial) -> ctx |> openModule moduleSerial
          | _ ->
              ctx
              |> addLog (OtherNameResLog("Unknown path: " + strJoin "." path)) loc

        expr, ctx

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

  | HFunExpr _
  | HVariantExpr _ -> failwithf "NEVER: HFunExpr and HVariantExpr is generated in NameRes. %A" expr

let nameRes (expr: HExpr, nameCtx: NameCtx): HExpr * ScopeCtx =
  let scopeCtx = ofNameCtx nameCtx

  match expr with
  | HModuleExpr _ -> (expr, scopeCtx) |> nameResExpr

  | _ ->
      (expr, scopeCtx)
      |> collectDecls None
      |> nameResExpr
