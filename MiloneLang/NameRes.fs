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

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module S = MiloneStd.StdString

let private isNoTy ty =
  match ty with
  | Ty (ErrorTk _, _) -> true
  | _ -> false

let private hxAbort loc = HNodeExpr(HAbortEN, [], noTy, loc)

// -----------------------------------------------
// Type primitives
// -----------------------------------------------

let private tyPrimOfName name tys =
  match name, tys with
  | "unit", [] -> Some tyUnit
  | "bool", [] -> Some tyBool

  | "int", []
  | "int32", [] -> Some tyInt
  | "uint", []
  | "uint32", [] -> Ty(IntTk(IntFlavor(Unsigned, I32)), []) |> Some
  | "sbyte", []
  | "int8", [] -> Ty(IntTk(IntFlavor(Signed, I8)), []) |> Some
  | "byte", []
  | "uint8", [] -> Ty(IntTk(IntFlavor(Unsigned, I8)), []) |> Some

  | "int16", [] -> Ty(IntTk(IntFlavor(Signed, I16)), []) |> Some
  | "int64", [] -> Ty(IntTk(IntFlavor(Signed, I64)), []) |> Some
  | "nativeint", [] -> Ty(IntTk(IntFlavor(Signed, IPtr)), []) |> Some
  | "uint16", [] -> Ty(IntTk(IntFlavor(Unsigned, I16)), []) |> Some
  | "uint64", [] -> Ty(IntTk(IntFlavor(Unsigned, I64)), []) |> Some
  | "unativeint", [] -> Ty(IntTk(IntFlavor(Unsigned, IPtr)), []) |> Some

  | "float", [] -> Some tyFloat
  | "char", [] -> Some tyChar
  | "string", [] -> Some tyStr
  | "obj", [] -> Some tyObj

  | "option", [ itemTy ] -> Some(tyOption itemTy)
  | "list", [ itemTy ] -> Some(tyList itemTy)

  | "voidptr", [] -> Ty(NativePtrTk IsMut, [ Ty(VoidTk, []) ]) |> Some
  | "nativeptr", [ itemTy ] -> Ty(NativePtrTk IsMut, [ itemTy ]) |> Some
  | "__constptr", [ itemTy ] -> Ty(NativePtrTk IsConst, [ itemTy ]) |> Some

  | "__nativeFun", [ Ty (TupleTk, itemTys); resultTy ] ->
      Ty(NativeFunTk, List.append itemTys [ resultTy ])
      |> Some

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

// -----------------------------------------------
// NsOwner
// -----------------------------------------------

/// Identity of namespace owner.
type NsOwner =
  | TyNsOwner of TySerial
  | ModuleNsOwner of ModuleTySerial
  | ModuleSynonymNsOwner of ModuleSynonymSerial

let private nsOwnerToInt (nsOwner: NsOwner) : int =
  match nsOwner with
  | TyNsOwner tySerial -> tySerial
  | ModuleNsOwner serial -> moduleTySerialToInt serial
  | ModuleSynonymNsOwner serial -> moduleSynonymSerialToInt serial

let private nsOwnerCompare (l: NsOwner) r : int =
  compare (nsOwnerToInt l) (nsOwnerToInt r)

let private nsOwnerOfTySymbol (tySymbol: TySymbol) : NsOwner = TyNsOwner(tySymbolToSerial tySymbol)

// -----------------------------------------------
// Namespace
// -----------------------------------------------

type Ns<'T> = AssocMap<NsOwner, (AssocMap<Ident, 'T>)>

let private nsFind (key: NsOwner) (ns: Ns<_>) : AssocMap<Ident, _> =
  match ns |> TMap.tryFind key with
  | Some submap -> submap
  | None -> TMap.empty compare

let private nsAdd (key: NsOwner) (ident: Ident) value (ns: Ns<_>) : Ns<_> =
  ns
  |> TMap.add key (ns |> nsFind key |> TMap.add ident value)

let private nsMerge (key: NsOwner) (ident: Ident) value (ns: Ns<_>) : Ns<_> =
  let submap =
    ns |> nsFind key |> multimapAdd ident value

  ns |> TMap.add key submap

// --------------------------------------------
// Scopes
// --------------------------------------------

[<NoEquality; NoComparison>]
type ScopeKind =
  | ExprScope
  | TyDeclScope

/// Stack of local scopes.
type private ScopeChain<'T> = AssocMap<Ident, 'T> list

/// Scope chains, vars and types.
///
/// Type has also a list of types that it shadows for namespace merging.
type private Scope = ScopeKind list * ScopeChain<ValueSymbol> * ScopeChain<TySymbol> * ScopeChain<NsOwner list>

let private scopeMapEmpty () : AssocMap<Ident, _> = TMap.empty compare

let private scopeChainEmpty () : ScopeChain<_> = [ scopeMapEmpty () ]

let private scopeEmpty () : Scope =
  [], scopeChainEmpty (), scopeChainEmpty (), scopeChainEmpty ()

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
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

    /// Serial of value (variable/fun) to level map.
    VarLevels: AssocMap<Serial, Level>

    MainFunOpt: FunSerial option

    /// Type serial to definition map.
    Tys: AssocMap<TySerial, TyDef>

    ModuleTys: AssocMap<ModuleTySerial, ModuleTyDef>
    ModuleSynonyms: AssocMap<ModuleSynonymSerial, ModuleSynonymDef>
    RootModules: ModuleTySerial list
    CurrentModule: ModuleTySerial option
    CurrentPath: string list

    /// Values contained by types.
    VarNs: Ns<ValueSymbol>

    /// Types contained by types.
    TyNs: Ns<TySymbol>

    /// Sub namespaces.
    NsNs: Ns<NsOwner list>

    /// Current scope.
    Local: Scope

    /// Variables defined in current pattern.
    ///
    /// name -> (varSerial, definedLoc, usedLoc list)
    PatScope: AssocMap<Ident, VarSerial * Loc * Loc list>

    /// Current level.
    Level: Level

    Logs: (NameResLog * Loc) list }

let private ofNameCtx (nameCtx: NameCtx) : ScopeCtx =
  let (NameCtx (nameMap, serial)) = nameCtx

  { Serial = serial
    NameMap = nameMap
    Vars = TMap.empty varSerialCompare
    Funs = TMap.empty funSerialCompare
    Variants = TMap.empty variantSerialCompare
    VarLevels = TMap.empty compare
    MainFunOpt = None
    Tys = TMap.empty compare
    ModuleTys = TMap.empty moduleTySerialCompare
    ModuleSynonyms = TMap.empty moduleSynonymSerialCompare
    RootModules = []
    CurrentModule = None
    CurrentPath = []
    VarNs = TMap.empty nsOwnerCompare
    TyNs = TMap.empty nsOwnerCompare
    NsNs = TMap.empty nsOwnerCompare
    Local = scopeEmpty ()
    PatScope = TMap.empty compare
    Level = 0
    Logs = [] }

let private addLog (log: NameResLog) (loc: Loc) (ctx: ScopeCtx) =
  { ctx with
      Logs = (log, loc) :: ctx.Logs }

let private findName serial (scopeCtx: ScopeCtx) : Ident = scopeCtx.NameMap |> mapFind serial

let private findVar varSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Vars |> TMap.containsKey varSerial)
  scopeCtx.Vars |> mapFind varSerial

let private findFun funSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Funs |> TMap.containsKey funSerial)
  scopeCtx.Funs |> mapFind funSerial

let private findVariant variantSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Variants
          |> TMap.containsKey variantSerial)

  scopeCtx.Variants |> mapFind variantSerial

let private findTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Tys |> TMap.containsKey tySerial)
  scopeCtx.Tys |> mapFind tySerial

let private findModuleTy moduleSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.ModuleTys
          |> TMap.containsKey moduleSerial)

  scopeCtx.ModuleTys |> mapFind moduleSerial

let private findModuleSynonym serial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.ModuleSynonyms |> TMap.containsKey serial)
  scopeCtx.ModuleSynonyms |> mapFind serial

let private findVarName varSerial (scopeCtx: ScopeCtx) =
  scopeCtx |> findName (varSerialToInt varSerial)

let private findValueSymbolName valueSymbol scopeCtx =
  scopeCtx
  |> findName (valueSymbolToSerial valueSymbol)

let private findTySymbolName tySymbol (scopeCtx: ScopeCtx) =
  scopeCtx
  |> findTy (tySymbolToSerial tySymbol)
  |> tyDefToName

let private findNsOwnerName nsOwner (scopeCtx: ScopeCtx) =
  match nsOwner with
  | TyNsOwner tySerial ->
      match scopeCtx.Tys |> TMap.tryFind tySerial with
      | Some a -> a |> tyDefToName
      | None -> "type#" + string tySerial

  | ModuleNsOwner serial -> (scopeCtx.ModuleTys |> mapFind serial).Name
  | ModuleSynonymNsOwner serial -> (scopeCtx.ModuleSynonyms |> mapFind serial).Name

/// Defines a variable, without adding to any scope.
let private addVar varSerial (varDef: VarDef) (scopeCtx: ScopeCtx) : ScopeCtx =
  // Merge into current definition.
  let varDef =
    match scopeCtx.Vars |> TMap.tryFind varSerial with
    | Some oldDef ->
        { varDef with
            IsStatic = oldDef.IsStatic }
    | _ -> varDef

  { scopeCtx with
      Vars = scopeCtx.Vars |> TMap.add varSerial varDef
      VarLevels =
        scopeCtx.VarLevels
        |> TMap.add (varSerialToInt varSerial) scopeCtx.Level }

let private addFunDef funSerial funDef (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Funs = scopeCtx.Funs |> TMap.add funSerial funDef
      VarLevels =
        scopeCtx.VarLevels
        |> TMap.add (funSerialToInt funSerial) scopeCtx.Level }

let private addVariantDef variantSerial variantDef (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Variants =
        scopeCtx.Variants
        |> TMap.add variantSerial variantDef }

/// Defines a type, without adding to any scope.
let private addTy tySymbol tyDef (scopeCtx: ScopeCtx) : ScopeCtx =
  let tySerial = tySymbolToSerial tySymbol

  { scopeCtx with
      Tys = scopeCtx.Tys |> TMap.add tySerial tyDef }

let private addModuleTyDef moduleTySerial (tyDef: ModuleTyDef) (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      ModuleTys =
        scopeCtx.ModuleTys
        |> TMap.add moduleTySerial tyDef }

let private addModuleSynonymDef serial (tyDef: ModuleSynonymDef) (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      ModuleSynonyms = scopeCtx.ModuleSynonyms |> TMap.add serial tyDef }

/// Adds a variable to a namespace.
let private addVarToNs (nsOwner: NsOwner) valueSymbol (scopeCtx: ScopeCtx) : ScopeCtx =
  let name =
    scopeCtx |> findValueSymbolName valueSymbol

  { scopeCtx with
      VarNs = scopeCtx.VarNs |> nsAdd nsOwner name valueSymbol }

/// Adds a type to a namespace.
let private addTyToNs (nsOwner: NsOwner) tySymbol (scopeCtx: ScopeCtx) : ScopeCtx =
  let name = scopeCtx |> findTySymbolName tySymbol

  { scopeCtx with
      TyNs = scopeCtx.TyNs |> nsAdd nsOwner name tySymbol

      NsNs =
        scopeCtx.NsNs
        |> nsMerge nsOwner name (nsOwnerOfTySymbol tySymbol) }

/// Adds a child namespace.
let private addNsToNs (parentNsOwner: NsOwner) (childNsOwner: NsOwner) (scopeCtx: ScopeCtx) : ScopeCtx =
  let name = scopeCtx |> findNsOwnerName childNsOwner

  { scopeCtx with
      NsNs =
        scopeCtx.NsNs
        |> nsMerge parentNsOwner name childNsOwner }

/// Adds a variable to a scope.
let private importVar symbol (scopeCtx: ScopeCtx) : ScopeCtx =
  let varName =
    match symbol with
    | VarSymbol varSerial -> (scopeCtx |> findVar varSerial).Name
    | FunSymbol funSerial -> (scopeCtx |> findFun funSerial).Name
    | VariantSymbol variantSerial -> (scopeCtx |> findVariant variantSerial).Name

  assert (varName <> "_")

  let scope : Scope =
    match scopeCtx.Local with
    | kinds, map :: varScopes, tyScopes, nsScopes ->
        let varScopes =
          (map |> TMap.add varName symbol) :: varScopes

        kinds, varScopes, tyScopes, nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { scopeCtx with Local = scope }

/// Adds a type to a scope, aliasing a name.
let private doImportTyWithAlias alias (symbol: TySymbol) (scopeCtx: ScopeCtx) : ScopeCtx =
  let scope : Scope =
    match scopeCtx.Local with
    | kinds, varScopes, (tyMap :: tyScopes), (nsMap :: nsScopes) ->
        let tyMap = tyMap |> TMap.add alias symbol

        let nsMap =
          nsMap
          |> multimapAdd alias (nsOwnerOfTySymbol symbol)

        kinds, varScopes, tyMap :: tyScopes, nsMap :: nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { scopeCtx with Local = scope }

let private importTy symbol (scopeCtx: ScopeCtx) : ScopeCtx =
  let tyName = findTySymbolName symbol scopeCtx
  doImportTyWithAlias tyName symbol scopeCtx

/// Adds a type to a scope, aliasing a name.
let private doImportNsWithAlias alias nsOwner (scopeCtx: ScopeCtx) : ScopeCtx =
  let scope : Scope =
    match scopeCtx.Local with
    | kinds, varScopes, tyScopes, ((map :: nsScopes) as allNsScopes) ->
        let shadowed =
          allNsScopes
          |> List.tryPick (fun map -> map |> TMap.tryFind alias)
          |> Option.defaultValue []

        let map =
          map |> TMap.add alias (nsOwner :: shadowed)

        kinds, varScopes, tyScopes, map :: nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { scopeCtx with Local = scope }

let private importNs nsOwner (scopeCtx: ScopeCtx) : ScopeCtx =
  let name = findNsOwnerName nsOwner scopeCtx
  doImportNsWithAlias name nsOwner scopeCtx

let private openModule moduleSerial (scopeCtx: ScopeCtx) =
  // Import vars.
  let scopeCtx =
    scopeCtx.VarNs
    |> nsFind (ModuleNsOwner moduleSerial)
    |> TMap.fold (fun ctx _ symbol -> ctx |> importVar symbol) scopeCtx

  // Import tys.
  let scopeCtx =
    scopeCtx.TyNs
    |> nsFind (ModuleNsOwner moduleSerial)
    |> TMap.fold (fun ctx _ symbol -> ctx |> importTy symbol) scopeCtx

  // Import subnamespaces.
  let scopeCtx =
    scopeCtx.NsNs
    |> nsFind (ModuleNsOwner moduleSerial)
    |> TMap.fold (fun ctx _ nsOwners -> ctx |> forList importNs nsOwners) scopeCtx

  scopeCtx

let private openModules moduleSerials ctx =
  moduleSerials
  |> List.fold (fun ctx moduleSerial -> ctx |> openModule moduleSerial) ctx

/// Defines a variable in the local scope.
let private addLocalVar varSerial varDef (scopeCtx: ScopeCtx) : ScopeCtx =
  scopeCtx
  |> addVar varSerial varDef
  |> importVar (VarSymbol varSerial)

/// Defines a type in the local scope.
let private addLocalTy tySymbol tyDef (scopeCtx: ScopeCtx) : ScopeCtx =
  scopeCtx
  |> addTy tySymbol tyDef
  |> importTy tySymbol

/// Called on enter the init of let expressions.
let private enterLetInit (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Level = scopeCtx.Level + 1 }

let private leaveLetInit (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Level = scopeCtx.Level - 1 }

/// Starts a new scope.
let private startScope kind (scopeCtx: ScopeCtx) : ScopeCtx =
  let kinds, varScopes, tyScopes, nsScopes = scopeCtx.Local

  { scopeCtx with
      Local = kind :: kinds, scopeMapEmpty () :: varScopes, scopeMapEmpty () :: tyScopes, scopeMapEmpty () :: nsScopes }

let private finishScope (scopeCtx: ScopeCtx) : ScopeCtx =
  match scopeCtx.Local with
  | [], _, _, _
  | _, [], _, _
  | _, _, [], _
  | _, _, _, [] -> unreachable () // Scope can't be empty..

  | _ :: kinds, _ :: varScopes, _ :: tyScopes, _ :: nsScopes ->
      { scopeCtx with
          Local = kinds, varScopes, tyScopes, nsScopes }

let private isTyDeclScope (scopeCtx: ScopeCtx) =
  match scopeCtx.Local with
  | TyDeclScope :: _, _, _, _ -> true
  | _ -> false

let private enterModule moduleTySerial (scopeCtx: ScopeCtx) =
  let moduleName =
    (scopeCtx.ModuleTys |> mapFind moduleTySerial)
      .Name

  let scopeCtx =
    match scopeCtx.CurrentModule with
    | None ->
        { scopeCtx with
            RootModules = moduleTySerial :: scopeCtx.RootModules }

    | Some parent ->
        scopeCtx
        |> addNsToNs (ModuleNsOwner parent) (ModuleNsOwner moduleTySerial)

  let parent =
    scopeCtx.CurrentModule, scopeCtx.CurrentPath

  let scopeCtx =
    { scopeCtx with
        CurrentModule = Some moduleTySerial
        CurrentPath = List.append scopeCtx.CurrentPath [ moduleName ] }

  parent, scopeCtx

let private leaveModule parent (scopeCtx: ScopeCtx) =
  let currentModule, currentPath = parent

  { scopeCtx with
      CurrentModule = currentModule
      CurrentPath = currentPath }

let private resolveModulePath path (scopeCtx: ScopeCtx) : ModuleTySerial list =
  match path with
  | [] -> []
  | head :: tail ->
      let roots =
        scopeCtx.RootModules
        |> List.filter
             (fun serial ->
               let moduleDef = scopeCtx.ModuleTys |> mapFind serial

               moduleDef.Name = head)

      let rec go serial path =
        match path with
        | [] -> [ serial ]

        | name :: tail ->
            scopeCtx
            |> resolveSubNsOwners (ModuleNsOwner serial) name
            |> List.collect
                 (fun nsOwner ->
                   match nsOwner with
                   | ModuleNsOwner serial -> go serial tail
                   | _ -> [])

      roots
      |> List.collect (fun serial -> go serial tail)

// Find from namespace of type (not local).
let private resolveScopedVarName nsOwner name (scopeCtx: ScopeCtx) : ValueSymbol option =
  scopeCtx.VarNs
  |> nsFind nsOwner
  |> TMap.tryFind name

// Find from namespace of type (not local).
let private resolveScopedTyName nsOwner name (scopeCtx: ScopeCtx) : TySymbol option =
  scopeCtx.TyNs
  |> nsFind nsOwner
  |> TMap.tryFind name

let private resolveSubNsOwners nsOwner name (scopeCtx: ScopeCtx) : NsOwner list =
  scopeCtx.NsNs
  |> nsFind nsOwner
  |> multimapFind name

let private resolveLocalVarName name (scopeCtx: ScopeCtx) =
  let _, varScopes, _, _ = scopeCtx.Local

  varScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)

let private resolveLocalTyName name (scopeCtx: ScopeCtx) : TySymbol option =
  let _, _, tyScopes, _ = scopeCtx.Local

  tyScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)

let private resolveLocalNsOwners name (scopeCtx: ScopeCtx) : NsOwner list =
  let _, _, _, nsScopes = scopeCtx.Local

  nsScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)
  |> Option.defaultValue []

/// Resolves qualifiers of type.
let private resolveNavTy quals last ctx =
  let path =
    quals
    |> List.map (fun qual -> ctx |> findName qual)

  match path with
  | [] -> ctx |> resolveLocalTyName last, ctx

  | head :: tail ->
      // Resolve head.
      let nsOwners = ctx |> resolveLocalNsOwners head

      // Resolve tail.
      let rec resolveTyPath (nsOwner: NsOwner) path ctx =
        match path with
        | [] -> [ nsOwner ]

        | name :: path ->
            ctx
            |> resolveSubNsOwners nsOwner name
            |> List.collect (fun subNsOwner -> resolveTyPath subNsOwner path ctx)

      let tySymbolOpt =
        nsOwners
        |> List.collect (fun nsOwner -> resolveTyPath nsOwner tail ctx)
        |> List.tryPick (fun nsOwner -> resolveScopedTyName nsOwner last ctx)

      tySymbolOpt, ctx

/// Resolves type names in a type expression.
let private resolveTy ty loc scopeCtx =
  let rec go (ty, scopeCtx) =
    match ty with
    | Ty (ErrorTk _, _) -> ty, scopeCtx

    | Ty (UnresolvedTk ([], serial), []) when (scopeCtx |> findName serial) = "_" -> tyMeta serial loc, scopeCtx

    | Ty (UnresolvedTk ([], serial), [ Ty (UnresolvedTk ([], itemSerial), _) ]) when
      (scopeCtx |> findName serial = "__nativeType") ->
        let code = scopeCtx |> findName itemSerial
        Ty(NativeTypeTk code, []), scopeCtx

    | Ty (UnresolvedVarTk (serial, loc), tys) ->
        assert (List.isEmpty tys)
        let name = scopeCtx |> findName serial

        match resolveLocalTyName name scopeCtx with
        | Some (UnivTySymbol tySerial) -> tyMeta tySerial loc, scopeCtx

        | _ when scopeCtx |> isTyDeclScope ->
            let scopeCtx =
              scopeCtx |> addLog (UndefinedTyError name) loc

            tyError loc, scopeCtx

        | _ ->
            let scopeCtx =
              scopeCtx
              |> addLocalTy (UnivTySymbol serial) (UniversalTyDef(name, loc))

            tyMeta serial loc, scopeCtx

    | Ty (UnresolvedTk (quals, serial), tys) ->
        let name = scopeCtx |> findName serial
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        let arity = List.length tys

        let symbolOpt, scopeCtx = resolveNavTy quals name scopeCtx

        match symbolOpt with
        | Some (UnivTySymbol tySerial) -> tyMeta tySerial loc, scopeCtx

        | Some (SynonymTySymbol tySerial) ->
            // Arity check.
            match scopeCtx.Tys |> TMap.tryFind tySerial with
            | Some (SynonymTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> arity ->
                let scopeCtx =
                  scopeCtx
                  |> addLog (TyArityError(name, arity, List.length defTyArgs)) loc

                tyError loc, scopeCtx

            | _ -> tySynonym tySerial tys, scopeCtx

        | Some (UnionTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyUnion tySerial, scopeCtx

        | Some (RecordTySymbol tySerial) ->
            assert (List.isEmpty tys)
            tyRecord tySerial, scopeCtx

        | Some (MetaTySymbol _) -> unreachable (serial, name, loc)

        | None ->
            match tyPrimOfName name tys with
            | Some ty -> ty, scopeCtx
            | None ->
                let scopeCtx =
                  scopeCtx |> addLog (UndefinedTyError name) loc

                tyError loc, scopeCtx

    | Ty (tk, tys) ->
        let tys, scopeCtx = (tys, scopeCtx) |> stMap go
        Ty(tk, tys), scopeCtx

    | _ -> ty, scopeCtx

  go (ty, scopeCtx)

// -----------------------------------------------
// Definitions
// -----------------------------------------------

let private defineFunUniquely funSerial args ty loc (scopeCtx: ScopeCtx) : ScopeCtx =
  match scopeCtx.Funs |> TMap.tryFind funSerial with
  | Some _ -> scopeCtx

  | None ->
      let name =
        scopeCtx |> findName (funSerialToInt funSerial)

      let funDef : FunDef =
        { Name = name
          Arity = args |> List.length
          Ty = TyScheme([], ty)
          Abi = MiloneAbi
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
        |> addVarToNs (ModuleNsOwner moduleSerial) varSerial

    | _ -> ctx

  let addTyToModule tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addTyToNs (ModuleNsOwner moduleSerial) tySerial

    | _ -> ctx

  let tyName = ctx |> findName tySerial

  if ctx.Tys |> TMap.containsKey tySerial then
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

          let variantDef : VariantDef =
            { Name = name
              UnionTySerial = tySerial
              IsNewtype = List.length variants = 1
              HasPayload = hasPayload
              PayloadTy = payloadTy
              Loc = loc }

          ctx
          |> addVariantDef variantSerial variantDef
          |> addVarToNs (TyNsOwner tySerial) variantSymbol
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
  | UniversalTyDef _ -> ctx

  | SynonymTyDef (tyName, tyArgs, bodyTy, loc) ->
      let ctx = ctx |> startScope TyDeclScope

      let ctx =
        tyArgs
        |> List.fold
             (fun ctx tyArg ->
               let name = ctx |> findName tyArg

               ctx
               |> addLocalTy (UnivTySymbol tyArg) (UniversalTyDef(name, loc)))
             ctx

      let bodyTy, ctx = ctx |> resolveTy bodyTy loc
      let ctx = ctx |> finishScope

      ctx
      |> addTy (SynonymTySymbol tySerial) (SynonymTyDef(tyName, tyArgs, bodyTy, loc))

  | UnionTyDef (_, variantSerials, _unionLoc) ->
      let go ctx variantSerial =
        let def = ctx |> findVariant variantSerial
        let payloadTy, ctx = ctx |> resolveTy def.PayloadTy loc

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

  | MetaTyDef _ -> unreachable tyDecl // Bound meta types don't happen in NameRes.

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
        |> addVarToNs (ModuleNsOwner moduleSerial) varSerial

    | _ -> ctx

  let addTyToModule vis tySerial ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addTyToNs (ModuleNsOwner moduleSerial) tySerial

    | _ -> ctx

  let addNsToModule vis nsOwner ctx =
    match moduleSerialOpt, vis with
    | Some moduleSerial, PublicVis ->
        ctx
        |> addNsToNs (ModuleNsOwner moduleSerial) nsOwner

    | _ -> ctx

  let rec goPat (pat, ctx) =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _
    | HOrPat _ -> pat, ctx

    | HVarPat (vis, varSerial, ty, loc) ->
        let name =
          ctx |> findName (varSerialToInt varSerial)

        match ctx |> resolveLocalVarName name with
        | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

        | _ ->
            let varDef : VarDef =
              { Name = name
                IsStatic = IsStatic
                Ty = ty
                Loc = loc }

            let ctx =
              ctx
              |> addLocalVar varSerial varDef
              |> addVarToModule vis (VarSymbol varSerial)

            pat, ctx

    | HNodePat (kind, argPats, ty, loc) ->
        let argPats, ctx = (argPats, ctx) |> stMap goPat
        HNodePat(kind, argPats, ty, loc), ctx

    | HAsPat (pat, varSerial, loc) ->
        let name =
          ctx |> findName (varSerialToInt varSerial)

        let varDef : VarDef =
          { Name = name
            IsStatic = IsStatic
            Ty = noTy
            Loc = loc }

        let ctx = ctx |> addLocalVar varSerial varDef

        let pat, ctx = (pat, ctx) |> goPat
        HAsPat(pat, varSerial, loc), ctx

  let rec goExpr (expr, ctx) =
    match expr with
    | HLetValExpr (pat, init, next, ty, loc) ->
        let pat, ctx = (pat, ctx) |> goPat
        let next, ctx = (next, ctx) |> goExpr
        HLetValExpr(pat, init, next, ty, loc), ctx

    | HLetFunExpr (funSerial, isRec, vis, args, body, next, ty, loc) ->
        let ctx =
          let name =
            ctx |> findName (funSerialToInt funSerial)

          if name = "main" then
            { ctx with MainFunOpt = Some funSerial }
          else
            ctx

        let ctx =
          ctx
          |> enterLetInit
          |> defineFunUniquely funSerial args noTy loc
          |> leaveLetInit
          |> addVarToModule vis (FunSymbol funSerial)

        let next, ctx = (next, ctx) |> goExpr
        HLetFunExpr(funSerial, isRec, vis, args, body, next, ty, loc), ctx

    | HBlockExpr (stmts, last) ->
        let stmts, ctx = (stmts, ctx) |> stMap goExpr
        let last, ctx = (last, ctx) |> goExpr
        HBlockExpr(stmts, last), ctx

    | HTyDeclExpr (serial, vis, tyArgs, tyDecl, loc) ->
        let ctx =
          ctx
          |> startDefineTy moduleSerialOpt serial vis tyArgs tyDecl loc

        HTyDeclExpr(serial, vis, tyArgs, tyDecl, loc), ctx

    | HModuleExpr (serial, body, loc) ->
        let name =
          ctx |> findName (moduleTySerialToInt serial)

        let ctx =
          ctx
          |> addModuleTyDef serial ({ Name = name; Loc = loc }: ModuleTyDef)
          |> addNsToModule PublicVis (ModuleNsOwner serial)
          |> importNs (ModuleNsOwner serial)

        HModuleExpr(serial, body, loc), ctx

    | HModuleSynonymExpr (serial, path, loc) ->
        let name =
          ctx |> findName (moduleSynonymSerialToInt serial)

        match name, path with
        | "_", _
        | _, [] -> expr, ctx

        | _ ->
            let ctx =
              ctx
              |> addModuleSynonymDef serial ({ Name = name; Bound = []; Loc = loc }: ModuleSynonymDef)
              |> importNs (ModuleSynonymNsOwner serial)

            expr, ctx

    | _ -> expr, ctx

  goExpr (expr, ctx)

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private doResolveVarInPat serial name ty loc (ctx: ScopeCtx) =
  match ctx.PatScope |> TMap.tryFind name with
  | None ->
      let varSerial = VarSerial serial

      let varDef : VarDef =
        { Name = name
          IsStatic = NotStatic
          Ty = ty
          Loc = loc }

      let ctx =
        { ctx with
            PatScope = ctx.PatScope |> TMap.add name (varSerial, loc, []) }
        |> addLocalVar varSerial varDef

      varSerial, ctx

  | Some (varSerial, defLoc, useLocs) ->
      let ctx =
        { ctx with
            PatScope =
              ctx.PatScope
              |> TMap.add name (varSerial, defLoc, loc :: useLocs) }

      varSerial, ctx

let private nameResVarPat vis serial ty loc ctx =
  // FIXME: report error on `public _`, `public Variant` or `public None`.

  let name = ctx |> findName serial

  if name = "_" then
    HDiscardPat(ty, loc), ctx
  else
    match ctx |> resolveLocalVarName name with
    | Some (VariantSymbol variantSerial) -> HVariantPat(variantSerial, ty, loc), ctx

    | _ ->
        match name with
        | "None" -> HNodePat(HNonePN, [], ty, loc), ctx
        | "Some" -> HNodePat(HSomePN, [], ty, loc), ctx

        | _ ->
            let varSerial, ctx =
              doResolveVarInPat serial name ty loc ctx

            HVarPat(vis, varSerial, ty, loc), ctx

let private nameResNavPat pat ctx =
  /// Resolves a pattern as scope.
  ///
  /// Returns (scopeOpt, pat).
  /// scopeOpt is `Some s` if pat is resolved to scope `s`.
  /// `pat` is also updated by resolving inner qualifiers as possible.
  let rec resolvePatAsNsOwners pat ctx : NsOwner list =
    match pat with
    | HVarPat (_, varSerial, _, _) ->
        let name = ctx |> findVarName varSerial
        ctx |> resolveLocalNsOwners name

    | HNodePat (HNavPN r, [ l ], _, _) ->
        ctx
        |> resolvePatAsNsOwners l
        |> List.collect (fun nsOwner -> ctx |> resolveSubNsOwners nsOwner r)

    | _ -> []

  let l, r, ty, loc =
    match pat with
    | HNodePat (HNavPN r, [ l ], ty, loc) -> l, r, ty, loc
    | _ -> unreachable ()

  let notResolved ctx =
    let ctx = ctx |> addLog UnresolvedNavPatError loc
    hpAbort noTy loc, ctx

  let patOpt =
    resolvePatAsNsOwners l ctx
    |> List.tryPick
         (fun nsOwner ->
           match ctx |> resolveScopedVarName nsOwner r with
           | Some (VariantSymbol variantSerial) -> Some(HVariantPat(variantSerial, ty, loc))
           | _ -> None)

  match patOpt with
  | Some pat -> pat, ctx
  | None -> notResolved ctx

let private nameResAppPat l r loc ctx =
  let l, ctx = (l, ctx) |> nameResPat
  let r, ctx = (r, ctx) |> nameResPat

  match l with
  | HNodePat (HSomePN, [], _, _) -> HNodePat(HSomeAppPN, [ r ], noTy, loc), ctx
  | HVariantPat (variantSerial, _, _) -> HNodePat(HVariantAppPN variantSerial, [ r ], noTy, loc), ctx
  | _ ->
      let ctx =
        ctx
        |> addLog (OtherNameResLog "Pattern can apply to Some or a variant that takes a payload.") loc

      hpAbort noTy loc, ctx

let private nameResAscribePat bodyPat ascriptionTy loc ctx =
  let ascriptionTy, ctx = ctx |> resolveTy ascriptionTy loc
  let bodyPat, ctx = (bodyPat, ctx) |> nameResPat
  HNodePat(HAscribePN, [ bodyPat ], ascriptionTy, loc), ctx

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
  | HVariantPat _ -> pat, ctx

  | HVarPat (vis, VarSerial serial, ty, loc) -> nameResVarPat vis serial ty loc ctx

  | HNodePat (kind, argPats, ty, loc) ->
      let fail () = unreachable pat

      match kind, argPats with
      | HNilPN, _
      | HNonePN, _
      | HSomePN, _
      | HAbortPN, _ ->
          assert (List.isEmpty argPats)
          pat, ctx

      | HAppPN, [ l; r ] -> nameResAppPat l r loc ctx
      | HAppPN, _ -> fail ()

      | HConsPN, _
      | HSomeAppPN, _
      | HVariantAppPN _, _
      | HTuplePN, _
      | HBoxPN, _ ->
          let argPats, ctx = (argPats, ctx) |> stMap nameResPat
          HNodePat(kind, argPats, ty, loc), ctx

      | HNavPN _, [ _ ] -> nameResNavPat pat ctx
      | HNavPN _, _ -> fail ()

      | HAscribePN, [ bodyPat ] -> nameResAscribePat bodyPat ty loc ctx
      | HAscribePN, _ -> fail ()

  | HAsPat (bodyPat, VarSerial serial, loc) -> nameResAsPat bodyPat serial loc ctx

  | HOrPat (l, r, loc) ->
      // No OR patterns appear in arm patterns due to normalization.
      // So we can assume that it's inside of irrefutable pattern.
      let ctx = ctx |> addLog IllegalOrPatError loc

      let l, ctx = (l, ctx) |> nameResPat
      let r, ctx = (r, ctx) |> nameResPat
      HOrPat(l, r, loc), ctx

let private doWithPatScope patScopeOpt (f: ScopeCtx -> _ * ScopeCtx) (ctx: ScopeCtx) =
  let parentPatScope, ctx =
    ctx.PatScope,
    { ctx with
        PatScope =
          patScopeOpt
          |> Option.defaultValue (TMap.empty compare) }

  let result, ctx = f ctx

  let patScope, ctx =
    ctx.PatScope, { ctx with PatScope = parentPatScope }

  (patScope, result), ctx

let private nameResRefutablePat (pat: HPat, ctx: ScopeCtx) =
  let loc = patToLoc pat

  let pat, pats =
    match patNormalize pat with
    | [] -> unreachable ()
    | pat :: pats -> pat, pats

  let (lScope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat (pat, ctx))

  let ctx =
    lScope
    |> TMap.fold
         (fun ctx (_: string) (_, _, useLocs) ->
           match useLocs with
           | [] -> ctx
           | loc :: _ -> ctx |> addLog VarNameConflictError loc)
         ctx

  // Set of variables defined in the left-hand side.
  let varSerialSet =
    lScope
    |> TMap.toList
    |> List.map (fun (_: string, (varSerial, _, _)) -> varSerial)
    |> TSet.ofList varSerialCompare

  let pats, ctx =
    (pats, ctx)
    |> stMap
         (fun (pat, ctx) ->
           let (rScope, pat), ctx =
             ctx
             |> doWithPatScope (Some lScope) (fun ctx -> nameResPat (pat, ctx))

           // Validate that each variable defined in the left-hand side
           // appears also right-hand side exactly once.
           let ok =
             let ok, set =
               rScope
               |> TMap.fold
                    (fun (ok, set) (_: string) (varSerial: VarSerial, _, usedLocs) ->
                      match usedLocs with
                      | [ _ ] when ok ->
                          let removed, set = set |> TSet.remove varSerial
                          ok && removed, set

                      | _ -> false, set)
                    (true, varSerialSet)

             ok && TSet.isEmpty set

           let ctx =
             if ok then
               ctx
             else
               ctx |> addLog OrPatInconsistentBindingError loc

           pat, ctx)

  // PENDING: MirGen generates illegal code for binding OR patterns, so reject here.
  let ctx =
    if
      not (List.isEmpty pats)
      && not (TSet.isEmpty varSerialSet)
    then
      ctx |> addLog UnimplOrPatBindingError loc
    else
      ctx

  let pat =
    List.fold (fun l r -> HOrPat(l, r, loc)) pat pats

  pat, ctx

let private nameResIrrefutablePat (pat: HPat, ctx: ScopeCtx) =
  let (scope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat (pat, ctx))

  let ctx =
    scope
    |> TMap.fold
         (fun ctx (_: string) (_, _, useLocs) ->
           match useLocs with
           | [] -> ctx
           | loc :: _ -> ctx |> addLog VarNameConflictError loc)
         ctx

  pat, ctx

// -----------------------------------------------
// Expression
// -----------------------------------------------

type private ResolvedExpr =
  | ResolvedAsExpr of HExpr
  | ResolvedAsScope of NsOwner list * HExpr option * Loc
  | NotResolvedExpr of Ident * Loc

/// Tries to resolve a name expression as value; or just return None.
let private doNameResVarExpr expr ctx =
  let serial, ty, loc =
    match expr with
    | HVarExpr (VarSerial serial, ty, loc) -> serial, ty, loc
    | _ -> unreachable ()

  let name = ctx |> findName serial

  match ctx |> resolveLocalVarName name with
  | Some (VarSymbol serial) -> HVarExpr(serial, ty, loc) |> Some
  | Some (FunSymbol serial) -> HFunExpr(serial, ty, loc) |> Some
  | Some (VariantSymbol serial) -> HVariantExpr(serial, ty, loc) |> Some

  | None ->
      match primFromIdent name with
      | Some prim -> HPrimExpr(prim, ty, loc) |> Some
      | None -> None

let private nameResVarExpr expr ctx =
  match doNameResVarExpr expr ctx with
  | Some expr -> expr, ctx

  | None ->
      let name, loc =
        match expr with
        | HVarExpr (VarSerial serial, _, loc) -> findName serial ctx, loc
        | _ -> unreachable ()

      let ctx =
        ctx |> addLog (UndefinedValueError name) loc

      hxAbort loc, ctx

let private nameResNavExpr expr ctx =
  /// Resolves an expressions as scope.
  ///
  /// Returns (scopeOpt, exprOpt).
  /// scopeOpt should eb some it can be resolved to scope.
  /// exprOpt is also obtained by resolving inner `nav`s as possible.
  let rec resolveExprAsNsOwners expr ctx : ResolvedExpr * ScopeCtx =
    match expr with
    | HVarExpr (VarSerial serial, _, loc) ->
        let name = ctx |> findName serial
        let nsOwners = ctx |> resolveLocalNsOwners name
        let exprOpt = doNameResVarExpr expr ctx

        match nsOwners, exprOpt with
        | [], None -> NotResolvedExpr(name, loc), ctx
        | [], Some expr -> ResolvedAsExpr expr, ctx
        | _ -> ResolvedAsScope(nsOwners, exprOpt, loc), ctx

    | HNavExpr (l, r, ty, loc) ->
        let l, ctx = ctx |> resolveExprAsNsOwners l

        match l with
        | NotResolvedExpr _ -> l, ctx

        | ResolvedAsExpr l -> ResolvedAsExpr(HNavExpr(l, r, ty, loc)), ctx

        | ResolvedAsScope (superNsOwners, lExprOpt, _) ->
            assert (List.isEmpty superNsOwners |> not)

            // Resolve as namespaces.
            let nsOwners =
              superNsOwners
              |> List.collect (fun nsOwner -> ctx |> resolveSubNsOwners nsOwner r)

            // Resolve as value.
            let exprOpt =
              let varSymbolOpt =
                superNsOwners
                |> List.tryPick
                     (fun nsOwner ->
                       match ctx |> resolveScopedVarName nsOwner r with
                       | None -> None
                       | it -> it)

              match varSymbolOpt with
              | Some (VarSymbol varSerial) -> HVarExpr(varSerial, ty, loc) |> Some
              | Some (FunSymbol funSerial) -> HFunExpr(funSerial, ty, loc) |> Some
              | Some (VariantSymbol variantSerial) -> HVariantExpr(variantSerial, ty, loc) |> Some
              | None -> None

            // If not resolved as value, keep try to unresolved.
            let exprOpt =
              match exprOpt, lExprOpt with
              | Some _, _ -> exprOpt
              | None, Some l -> HNavExpr(l, r, ty, loc) |> Some
              | None, None -> None

            match nsOwners, exprOpt with
            | [], None -> NotResolvedExpr(r, loc), ctx
            | [], Some expr -> ResolvedAsExpr expr, ctx
            | _ -> ResolvedAsScope(nsOwners, exprOpt, loc), ctx

    | _ ->
        // l is clearly unresolvable as type, e.g. `(getStr ()).Length`.
        let expr, ctx = nameResExpr (expr, ctx)
        ResolvedAsExpr expr, ctx

  let result, ctx = resolveExprAsNsOwners expr ctx

  match result with
  | ResolvedAsExpr expr -> expr, ctx

  | ResolvedAsScope (_, Some expr, _) -> expr, ctx

  | ResolvedAsScope (_, None, loc) ->
      let ctx = ctx |> addLog TyUsedAsValueError loc
      hxAbort loc, ctx

  | NotResolvedExpr (name, loc) ->
      let ctx =
        ctx |> addLog (UndefinedValueError name) loc

      hxAbort loc, ctx

let private nameResExpr (expr: HExpr, ctx: ScopeCtx) =
  match expr with
  | HLitExpr _
  | HPrimExpr _ -> expr, ctx

  | HVarExpr _ -> nameResVarExpr expr ctx

  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        let baseOpt, ctx =
          (baseOpt, ctx) |> stOptionMap nameResExpr

        let fields, ctx =
          (fields, ctx)
          |> stMap
               (fun ((name, init, loc), ctx) ->
                 let init, ctx = (init, ctx) |> nameResExpr
                 (name, init, loc), ctx)

        HRecordExpr(baseOpt, fields, ty, loc), ctx

      doArm ()

  | HMatchExpr (cond, arms, ty, loc) ->
      let doArm () =
        let cond, ctx = (cond, ctx) |> nameResExpr

        let arms, ctx =
          (arms, ctx)
          |> stMap
               (fun ((pat, guard, body), ctx) ->
                 let ctx = ctx |> startScope ExprScope
                 let pat, ctx = (pat, ctx) |> nameResRefutablePat
                 let guard, ctx = (guard, ctx) |> nameResExpr
                 let body, ctx = (body, ctx) |> nameResExpr
                 let ctx = ctx |> finishScope
                 (pat, guard, body), ctx)

        HMatchExpr(cond, arms, ty, loc), ctx

      doArm ()

  | HNavExpr _ -> nameResNavExpr expr ctx

  | HNodeExpr (op, items, ty, loc) ->
      let doArm () =
        // Necessary in case of ascribe expression.
        let ty, ctx = ctx |> resolveTy ty loc

        let items, ctx = (items, ctx) |> stMap nameResExpr
        HNodeExpr(op, items, ty, loc), ctx

      doArm ()

  | HBlockExpr (stmts, last) ->
      let doArm () =
        let stmts, ctx = (stmts, ctx) |> stMap nameResExpr
        let last, ctx = (last, ctx) |> nameResExpr
        HBlockExpr(stmts, last), ctx

      doArm ()

  | HLetValExpr (pat, body, next, ty, loc) ->
      let doArm () =
        let body, ctx =
          let ctx = ctx |> startScope ExprScope
          let body, ctx = (body, ctx) |> nameResExpr
          let ctx = ctx |> finishScope
          body, ctx

        let pat, next, ctx =
          let ctx = ctx |> startScope ExprScope
          let pat, ctx = (pat, ctx) |> nameResIrrefutablePat
          let next, ctx = (next, ctx) |> nameResExpr
          let ctx = ctx |> finishScope
          pat, next, ctx

        HLetValExpr(pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (serial, isRec, vis, pats, body, next, ty, loc) ->
      let doArm () =
        let ctx = ctx |> startScope ExprScope

        let pats, body, ctx =
          match isRec with
          | IsRec ->
              // Define the function itself for recursive referencing.
              let ctx =
                ctx
                |> enterLetInit
                |> defineFunUniquely serial pats noTy loc
                |> startScope ExprScope

              let pats, ctx =
                (pats, ctx) |> stMap nameResIrrefutablePat

              let body, ctx = (body, ctx) |> nameResExpr
              let ctx = ctx |> finishScope |> leaveLetInit
              pats, body, ctx

          | NotRec ->
              let ctx =
                ctx |> enterLetInit |> startScope ExprScope

              let pats, ctx =
                (pats, ctx) |> stMap nameResIrrefutablePat

              let body, ctx = (body, ctx) |> nameResExpr

              let ctx =
                ctx
                |> finishScope
                |> defineFunUniquely serial pats noTy loc
                |> leaveLetInit

              pats, body, ctx

        let next, ctx = (next, ctx) |> nameResExpr
        let ctx = ctx |> finishScope

        HLetFunExpr(serial, isRec, vis, pats, body, next, ty, loc), ctx

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
          let moduleSerials = ctx |> resolveModulePath path

          if List.isEmpty moduleSerials then
            ctx |> addLog ModulePathNotFoundError loc
          else
            ctx |> openModules moduleSerials

        expr, ctx

      doArm ()

  | HModuleExpr (serial, body, loc) ->
      let doArm () =
        let moduleName =
          ctx |> findName (moduleTySerialToInt serial)

        let ctx =
          ctx
          |> addModuleTyDef serial ({ Name = moduleName; Loc = loc }: ModuleTyDef)
          |> importNs (ModuleNsOwner serial)

        let parent, ctx = ctx |> enterModule serial

        let ctx = ctx |> startScope ExprScope

        let ctx =
          // Open the parent module (and modules with the same path).
          ctx
          |> forList (fun moduleTySerial ctx -> openModule moduleTySerial ctx) (ctx |> resolveModulePath (snd parent))

        let body, ctx =
          (body, ctx)
          |> stMap (collectDecls (Some serial))
          |> stMap nameResExpr

        let ctx = ctx |> finishScope |> leaveModule parent

        // HACK: MiloneOnly is auto-open.
        let ctx =
          if moduleName = "MiloneOnly" then
            ctx |> openModule serial
          else
            ctx

        // Module no longer needed.
        hxSemi body loc, ctx

      doArm ()

  | HModuleSynonymExpr (serial, path, loc) ->
      let doArm () =
        let name =
          ctx |> findName (moduleSynonymSerialToInt serial)

        let ctx =
          match name, path with
          | "_", _
          | _, [] -> ctx

          | _, path ->
              let moduleSerials = ctx |> resolveModulePath path

              if List.isEmpty moduleSerials then
                ctx |> addLog ModulePathNotFoundError loc
              else
                ctx
                |> addModuleSynonymDef
                     serial
                     ({ Name = name
                        Bound = moduleSerials
                        Loc = loc }: ModuleSynonymDef)
                |> forList
                     (fun moduleSerial ctx -> doImportNsWithAlias name (ModuleNsOwner moduleSerial) ctx)
                     moduleSerials

        hxUnit loc, ctx

      doArm ()

  | HFunExpr _
  | HVariantExpr _ -> unreachable expr // HFunExpr and HVariantExpr are generated in NameRes.

let nameRes (exprs: HExpr list, nameCtx: NameCtx) : HExpr * ScopeCtx =
  let scopeCtx = ofNameCtx nameCtx

  let exprs, scopeCtx =
    (exprs, scopeCtx)
    |> stMap (collectDecls None)
    |> stMap nameResExpr

  hxSemi exprs noLoc, scopeCtx
