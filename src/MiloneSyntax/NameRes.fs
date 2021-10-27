/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneSyntax.NameRes

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneStd.StdMap
open MiloneStd.StdSet
open MiloneShared.Util
open MiloneSyntax.Tir

module S = MiloneStd.StdString

let private txAbort loc = TNodeExpr(TAbortEN, [], noTy, loc)

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

  | "__nativeFun", [ itemTy; resultTy ] -> Ty(NativeFunTk, [ itemTy; resultTy ]) |> Some

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
[<NoEquality; NoComparison>]
type private NsOwner =
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

/// Namespace.
type private Ns<'T> = TreeMap<NsOwner, (TreeMap<Ident, 'T>)>

let private nsFind (key: NsOwner) (ns: Ns<_>) : TreeMap<Ident, _> =
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
type private ScopeKind =
  | ExprScope
  | TyDeclScope

/// Stack of local scopes.
type private ScopeChain<'T> = TreeMap<Ident, 'T> list

/// Scope chains, vars and types.
///
/// Type has also a list of types that it shadows for namespace merging.
type private Scope = ScopeKind list * ScopeChain<ValueSymbol> * ScopeChain<TySymbol> * ScopeChain<NsOwner list>

let private scopeMapEmpty () : TreeMap<Ident, _> = TMap.empty compare

let private scopeChainEmpty () : ScopeChain<_> = [ scopeMapEmpty () ]

let private scopeEmpty () : Scope =
  [], scopeChainEmpty (), scopeChainEmpty (), scopeChainEmpty ()

// -----------------------------------------------
// NameResState
// -----------------------------------------------

/// Intermediate state of NameRes pass.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private NameResState =
  { NameCtx: NameCtx
    ScopeCtx: ScopeCtx
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    VarLevels: TreeMap<Serial, Level>
    Logs: (NameResLog * Loc) list }

let private sInit (nameCtx: NameCtx) : NameResState =
  { NameCtx = nameCtx
    ScopeCtx = ofNameCtx nameCtx
    Vars = emptyVars
    Funs = TMap.empty funSerialCompare
    Variants = TMap.empty variantSerialCompare
    VarLevels = TMap.empty compare
    Logs = [] }

let private optionMerge first second : _ option =
  match first, second with
  | Some _, _ -> first
  | _, Some _ -> second
  | _ -> None

let private mapMerge first second : TreeMap<_, _> =
  second
  |> TMap.fold (fun map key value -> TMap.add key value map) first

let private mapAddEntries (entries: ('K * 'T) list) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
  entries
  |> List.rev
  |> List.fold (fun map (key, value) -> TMap.add key value map) map

/// Merges two scopes into flattened scope.
let private scopeMerge (first: Scope) (second: Scope) : Scope =
  let mergeChain xs1 xs2 : ScopeChain<_> =
    [ List.append xs1 xs2
      |> List.fold mapMerge (scopeMapEmpty ()) ]

  let _, values1, tys1, nss1 = first
  let _, values2, tys2, nss2 = second
  [], mergeChain values1 values2, mergeChain tys1 tys2, mergeChain nss1 nss2

let private sMerge (state: NameResState) (scopeCtx: ScopeCtx) : NameResState * _ =
  let s = state.ScopeCtx

  let globalVars, localVars =
    scopeCtx.NewVars
    |> List.fold
         (fun (globalVars, localVars) (varSerial, varDef: VarDef) ->
           // Var can replace old definition but metadata shouldn't change.
           match TMap.tryFind varSerial scopeCtx.NewVarMeta with
           | Some (isStatic, linkage) ->
             let varDef =
               { varDef with
                   IsStatic = isStatic
                   Linkage = linkage }

             let globalVars = globalVars |> TMap.add varSerial varDef
             globalVars, localVars

           | None ->
             let localVars = localVars |> TMap.add varSerial varDef
             globalVars, localVars)
         (state.Vars, emptyVars)

  // Other fields are intermediate state.
  { state with
      ScopeCtx =
        { state.ScopeCtx with
            Tys = mapAddEntries scopeCtx.NewTys s.Tys
            MainFunOpt = optionMerge scopeCtx.MainFunOpt s.MainFunOpt
            RootModules = List.append scopeCtx.NewRootModules s.RootModules

            // These seem inefficient but not.
            Local = scopeMerge scopeCtx.Local s.Local
            VarNs = mapMerge s.VarNs scopeCtx.VarNs
            TyNs = mapMerge s.TyNs scopeCtx.TyNs
            NsNs = mapMerge s.NsNs scopeCtx.NsNs }

      Vars = globalVars
      Funs = mapAddEntries scopeCtx.NewFuns state.Funs
      Variants = mapMerge state.Variants scopeCtx.NewVariants
      VarLevels = mapAddEntries scopeCtx.NewVarLevels state.VarLevels
      Logs = List.append scopeCtx.NewLogs state.Logs },
  localVars

let private sToResult (state: NameResState) : NameResResult =
  let (NameCtx (_, serial)) = state.NameCtx
  let scopeCtx = state.ScopeCtx

  { Serial = serial
    Vars = state.Vars
    Funs = state.Funs
    Variants = state.Variants
    Tys = scopeCtx.Tys
    VarLevels = state.VarLevels
    MainFunOpt = scopeCtx.MainFunOpt
    Logs = state.Logs }

// -----------------------------------------------
// NameResResult
// -----------------------------------------------

/// Output of NameRes pass.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NameResResult =
  { Serial: Serial
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>
    VarLevels: TreeMap<Serial, Level>
    MainFunOpt: FunSerial option
    Logs: (NameResLog * Loc) list }

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ScopeCtx =
  { NameMap: TreeMap<Serial, Ident>

    NewVars: (VarSerial * VarDef) list
    NewFuns: (FunSerial * FunDef) list
    NewFunSet: TreeSet<FunSerial>
    NewVariants: TreeMap<VariantSerial, VariantDef>

    /// Vars/funs and levels.
    NewVarLevels: (Serial * Level) list
    NewVarMeta: TreeMap<VarSerial, IsStatic * Linkage>

    MainFunOpt: FunSerial option

    Tys: TreeMap<TySerial, TyDef>
    NewTys: (TySerial * TyDef) list

    RootModules: ModuleTySerial list
    NewRootModules: ModuleTySerial list
    CurrentModule: ModuleTySerial option
    CurrentPath: string list
    AncestralFuns: FunSerial list

    VarNs: Ns<ValueSymbol>
    TyNs: Ns<TySymbol>
    /// Subnamespaces.
    NsNs: Ns<NsOwner list>

    /// Current scope.
    Local: Scope

    /// Variables defined in current pattern.
    ///
    /// name -> (varSerial, definedLoc, usedLoc list)
    PatScope: TreeMap<Ident, VarSerial * Loc * Loc list>

    /// Current level.
    Level: Level

    NewLogs: (NameResLog * Loc) list }

let private emptyScopeCtx: ScopeCtx =
  { NameMap = TMap.empty compare
    NewVars = []
    NewFuns = []
    NewFunSet = TMap.empty funSerialCompare
    NewVariants = TMap.empty variantSerialCompare
    NewVarLevels = []
    NewVarMeta = TMap.empty varSerialCompare
    MainFunOpt = None
    Tys = TMap.empty compare
    NewTys = []
    RootModules = []
    NewRootModules = []
    CurrentModule = None
    CurrentPath = []
    AncestralFuns = []
    VarNs = TMap.empty nsOwnerCompare
    TyNs = TMap.empty nsOwnerCompare
    NsNs = TMap.empty nsOwnerCompare
    Local = scopeEmpty ()
    PatScope = TMap.empty compare
    Level = 0
    NewLogs = [] }

let private ofNameCtx (nameCtx: NameCtx) : ScopeCtx =
  let (NameCtx (nameMap, _)) = nameCtx

  { emptyScopeCtx with NameMap = nameMap }

let private addLog (log: NameResLog) (loc: Loc) (ctx: ScopeCtx) =
  { ctx with NewLogs = (log, loc) :: ctx.NewLogs }

let private makeLinkage vis name (ctx: ScopeCtx) =
  match vis with
  | PublicVis -> ExternalLinkage(S.concat "_" ctx.CurrentPath + "_" + name)
  | PrivateVis -> InternalLinkage

let private findName serial (scopeCtx: ScopeCtx) : Ident = scopeCtx.NameMap |> mapFind serial

let private findVariant variantSerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.NewVariants
          |> TMap.containsKey variantSerial)

  scopeCtx.NewVariants |> mapFind variantSerial

let private findTy tySerial (scopeCtx: ScopeCtx) =
  assert (scopeCtx.Tys |> TMap.containsKey tySerial)
  scopeCtx.Tys |> mapFind tySerial

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
  findName (nsOwnerToInt nsOwner) scopeCtx

/// Defines a variable, without adding to any scope.
let private addVar varSerial (varDef: VarDef) (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      NewVars = (varSerial, varDef) :: scopeCtx.NewVars

      NewVarLevels =
        (varSerialToInt varSerial, scopeCtx.Level)
        :: scopeCtx.NewVarLevels

      // Store metadata separately not to be overridden on late definition.
      NewVarMeta =
        match varDef.IsStatic, varDef.Linkage with
        | NotStatic, InternalLinkage -> scopeCtx.NewVarMeta
        | isStatic, linkage ->
          scopeCtx.NewVarMeta
          |> TMap.add varSerial (isStatic, linkage) }

let private addFunDef funSerial funDef (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      NewFuns = (funSerial, funDef) :: scopeCtx.NewFuns
      NewFunSet = scopeCtx.NewFunSet |> TSet.add funSerial

      NewVarLevels =
        (funSerialToInt funSerial, scopeCtx.Level)
        :: scopeCtx.NewVarLevels }

let private addVariantDef variantSerial variantDef (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      NewVariants =
        scopeCtx.NewVariants
        |> TMap.add variantSerial variantDef }

/// Defines a type, without adding to any scope.
let private addTy tySymbol tyDef (scopeCtx: ScopeCtx) : ScopeCtx =
  let tySerial = tySymbolToSerial tySymbol

  { scopeCtx with
      Tys = scopeCtx.Tys |> TMap.add tySerial tyDef
      NewTys = (tySerial, tyDef) :: scopeCtx.NewTys }

/// Adds a variable to a namespace.
let private addVarToNs (nsOwner: NsOwner) valueSymbol (scopeCtx: ScopeCtx) : ScopeCtx =
  let name =
    scopeCtx |> findValueSymbolName valueSymbol

  { scopeCtx with VarNs = scopeCtx.VarNs |> nsAdd nsOwner name valueSymbol }

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
    findName (valueSymbolToSerial symbol) scopeCtx

  assert (varName <> "_")

  let scope: Scope =
    match scopeCtx.Local with
    | kinds, map :: varScopes, tyScopes, nsScopes ->
      let varScopes =
        (map |> TMap.add varName symbol) :: varScopes

      kinds, varScopes, tyScopes, nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { scopeCtx with Local = scope }

/// Adds a type to a scope, aliasing a name.
let private doImportTyWithAlias alias (symbol: TySymbol) (scopeCtx: ScopeCtx) : ScopeCtx =
  let scope: Scope =
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
  let scope: Scope =
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

/// Called on enter the init of let-fun expressions.
let private enterLetInit funSerial (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Level = scopeCtx.Level + 1
      AncestralFuns = funSerial :: scopeCtx.AncestralFuns }

let private leaveLetInit (scopeCtx: ScopeCtx) : ScopeCtx =
  { scopeCtx with
      Level = scopeCtx.Level - 1
      AncestralFuns = listSkip 1 scopeCtx.AncestralFuns }

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
    { scopeCtx with Local = kinds, varScopes, tyScopes, nsScopes }

let private isTyDeclScope (scopeCtx: ScopeCtx) =
  match scopeCtx.Local with
  | TyDeclScope :: _, _, _, _ -> true
  | _ -> false

let private enterModule moduleTySerial (scopeCtx: ScopeCtx) =
  let moduleName =
    findName (moduleTySerialToInt moduleTySerial) scopeCtx

  let scopeCtx =
    match scopeCtx.CurrentModule with
    | None ->
      { scopeCtx with
          RootModules = moduleTySerial :: scopeCtx.RootModules
          NewRootModules = moduleTySerial :: scopeCtx.NewRootModules }

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
      |> List.filter (fun serial ->
        let moduleName =
          findName (moduleTySerialToInt serial) scopeCtx

        moduleName = head)

    let rec go serial path =
      match path with
      | [] -> [ serial ]

      | name :: tail ->
        scopeCtx
        |> resolveSubNsOwners (ModuleNsOwner serial) name
        |> List.collect (fun nsOwner ->
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
      (scopeCtx |> findName serial = "__nativeType")
      ->
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
        // Arity check. #tyaritycheck
        match scopeCtx.Tys |> TMap.tryFind tySerial with
        | Some (SynonymTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> arity ->
          let scopeCtx =
            scopeCtx
            |> addLog (TyArityError(name, arity, List.length defTyArgs)) loc

          tyError loc, scopeCtx

        | _ -> tySynonym tySerial tys, scopeCtx

      | Some (UnionTySymbol tySerial) ->
        // Arity check. #tyaritycheck
        match scopeCtx.Tys |> TMap.tryFind tySerial with
        | Some (UnionTyDef (name, defTyArgs, _, _)) when List.length defTyArgs <> arity ->
          let scopeCtx =
            scopeCtx
            |> addLog (TyArityError(name, arity, List.length defTyArgs)) loc

          tyError loc, scopeCtx

        | _ -> tyUnion tySerial tys, scopeCtx

      | Some (RecordTySymbol tySerial) ->
        // Arity check. #tyaritycheck
        match scopeCtx.Tys |> TMap.tryFind tySerial with
        | Some (RecordTyDef _) when arity <> 0 ->
          let defArity = 0 // generic record type is unimplemented

          let scopeCtx =
            scopeCtx
            |> addLog (TyArityError(name, arity, defArity)) loc

          tyError loc, scopeCtx

        | _ -> tyRecord tySerial, scopeCtx

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

let private defineFunUniquely vis funSerial args ty loc (scopeCtx: ScopeCtx) : ScopeCtx =
  if scopeCtx.NewFunSet |> TSet.contains funSerial then
    scopeCtx
  else
    let name =
      scopeCtx |> findName (funSerialToInt funSerial)

    let funDef: FunDef =
      { Name = name
        Arity = args |> List.length
        Ty = TyScheme([], ty)
        Abi = MiloneAbi
        Linkage = makeLinkage vis name scopeCtx

        Prefix =
          // The function itself is registered as ancestor if `rec`. Use the second for that case.
          scopeCtx.AncestralFuns
          |> List.skipWhile (fun x -> funSerialCompare x funSerial = 0)
          |> List.map (fun funSerial -> findName (funSerialToInt funSerial) scopeCtx)

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
      let defineVariant ctx (name, variantSerial, hasPayload, payloadTy, loc) =
        let variantSymbol = VariantSymbol variantSerial

        let variantDef: VariantDef =
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
          |> List.map (fun (_, variantSerial, _, _, _) -> variantSerial)

        UnionTyDef(tyName, tyArgs, variantSerials, loc)

      ctx
      |> addLocalTy tySymbol tyDef
      |> addTyToModule tySymbol

    | RecordTyDecl (_, fields, repr, loc) ->
      let tySymbol = RecordTySymbol tySerial

      let tyDef =
        RecordTyDef(tyName, tyArgs, fields, repr, loc)

      ctx
      |> addLocalTy tySymbol tyDef
      |> addTyToModule tySymbol

/// Completes the type definition.
///
/// - No need to call `startDefineTy` first.
/// - This resolves inner type expressions.
let private finishDefineTy tySerial tyArgs tyDecl loc ctx =
  let withTyArgsImported tyArgs (body: ScopeCtx -> 'A * ScopeCtx) ctx : 'A * ScopeCtx =
    ctx
    |> startScope TyDeclScope
    |> forList
         (fun tyArg ctx ->
           let name = ctx |> findName tyArg

           ctx
           |> addLocalTy (UnivTySymbol tyArg) (UniversalTyDef(name, loc)))
         tyArgs
    |> body
    |> (fun (result, ctx) -> result, finishScope ctx)

  let ctx =
    // Pass in PrivateVis because if this type is not pre-declared here, it's local to function.
    ctx
    |> startDefineTy None tySerial PrivateVis tyArgs tyDecl loc

  let tyDef = ctx |> findTy tySerial

  match tyDef with
  | UniversalTyDef _ -> ctx

  | SynonymTyDef (tyName, tyArgs, bodyTy, loc) ->
    let bodyTy, ctx =
      ctx
      |> withTyArgsImported tyArgs (resolveTy bodyTy loc)

    ctx
    |> addTy (SynonymTySymbol tySerial) (SynonymTyDef(tyName, tyArgs, bodyTy, loc))

  | UnionTyDef (_, tyArgs, variantSerials, _) ->
    ctx
    |> withTyArgsImported tyArgs (fun ctx ->
      let ctx =
        variantSerials
        |> List.fold
             (fun ctx variantSerial ->
               let def = ctx |> findVariant variantSerial
               let payloadTy, ctx = ctx |> resolveTy def.PayloadTy loc

               ctx
               |> addVariantDef variantSerial { def with PayloadTy = payloadTy })
             ctx

      (), ctx)
    |> snd

  | RecordTyDef (tyName, tyArgs, fields, repr, loc) ->
    let ctx =
      if tyArgs |> List.isEmpty |> not then
        addLog UnimplGenericTyError loc ctx
      else
        ctx

    let resolveField ((name, ty, loc), ctx) =
      let ty, ctx = ctx |> resolveTy ty loc
      (name, ty, loc), ctx

    let fields, ctx = (fields, ctx) |> stMap resolveField

    ctx
    |> addTy (RecordTySymbol tySerial) (RecordTyDef(tyName, tyArgs, fields, repr, loc))

  | MetaTyDef _ -> unreachable tyDecl // Bound meta types don't happen in NameRes.

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// This stage, traverse declarations directly inside `module rec`s
// to create variables/types pre-definitions
// so that mutually recursive references resolve correctly.

let private collectDecls moduleSerialOpt (stmt, ctx) : TStmt * ScopeCtx =
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

  let rec goPat (pat, ctx) : TPat * ScopeCtx =
    match pat with
    | TLitPat _
    | TDiscardPat _
    | TVariantPat _
    | TOrPat _ -> pat, ctx

    | TVarPat (vis, varSerial, ty, loc) ->
      let name =
        ctx |> findName (varSerialToInt varSerial)

      match ctx |> resolveLocalVarName name with
      | Some (VariantSymbol variantSerial) -> TVariantPat(variantSerial, ty, loc), ctx

      | _ ->
        let varDef: VarDef =
          { Name = name
            IsStatic = IsStatic
            Ty = ty
            Linkage = makeLinkage vis name ctx
            Loc = loc }

        let ctx =
          ctx
          |> addLocalVar varSerial varDef
          |> addVarToModule vis (VarSymbol varSerial)

        pat, ctx

    | TNodePat (kind, argPats, ty, loc) ->
      let argPats, ctx = (argPats, ctx) |> stMap goPat
      TNodePat(kind, argPats, ty, loc), ctx

    | TAsPat (pat, varSerial, loc) ->
      let name =
        ctx |> findName (varSerialToInt varSerial)

      let varDef: VarDef =
        { Name = name
          IsStatic = IsStatic
          Ty = noTy
          Linkage = InternalLinkage
          Loc = loc }

      let ctx = ctx |> addLocalVar varSerial varDef

      let pat, ctx = (pat, ctx) |> goPat
      TAsPat(pat, varSerial, loc), ctx

  let rec goStmt (stmt, ctx) : TStmt * ScopeCtx =
    match stmt with
    | TExprStmt _ -> stmt, ctx

    | TLetValStmt (pat, init, loc) ->
      let pat, ctx = (pat, ctx) |> goPat
      TLetValStmt(pat, init, loc), ctx

    | TLetFunStmt (funSerial, isRec, vis, args, body, loc) ->
      let ctx =
        let name =
          ctx |> findName (funSerialToInt funSerial)

        if name = "main" then
          { ctx with MainFunOpt = Some funSerial }
        else
          ctx

      let ctx =
        ctx
        |> enterLetInit funSerial
        |> defineFunUniquely vis funSerial args noTy loc
        |> leaveLetInit
        |> addVarToModule vis (FunSymbol funSerial)

      TLetFunStmt(funSerial, isRec, vis, args, body, loc), ctx

    | TTyDeclStmt (serial, vis, tyArgs, tyDecl, loc) ->
      let ctx =
        ctx
        |> startDefineTy moduleSerialOpt serial vis tyArgs tyDecl loc

      TTyDeclStmt(serial, vis, tyArgs, tyDecl, loc), ctx

    | TOpenStmt (path, loc) ->
      let ctx =
        let moduleSerials = ctx |> resolveModulePath path

        if List.isEmpty moduleSerials then
          ctx |> addLog ModulePathNotFoundError loc
        else
          ctx |> openModules moduleSerials

      stmt, ctx

    | TModuleStmt (serial, body, loc) ->
      let ctx =
        ctx
        |> addNsToModule PublicVis (ModuleNsOwner serial)
        |> importNs (ModuleNsOwner serial)

      TModuleStmt(serial, body, loc), ctx

    | TModuleSynonymStmt (serial, path, _) ->
      let name =
        ctx |> findName (moduleSynonymSerialToInt serial)

      match name, path with
      | "_", _
      | _, [] -> stmt, ctx

      | _ ->
        let ctx =
          ctx |> importNs (ModuleSynonymNsOwner serial)

        stmt, ctx

  goStmt (stmt, ctx)

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private doResolveVarInPat serial name ty loc (ctx: ScopeCtx) =
  match ctx.PatScope |> TMap.tryFind name with
  | None ->
    let varSerial = VarSerial serial

    let varDef: VarDef =
      { Name = name
        IsStatic = NotStatic
        Ty = ty
        Linkage = InternalLinkage
        Loc = loc }

    let ctx =
      { ctx with PatScope = ctx.PatScope |> TMap.add name (varSerial, loc, []) }
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
    TDiscardPat(ty, loc), ctx
  else
    match ctx |> resolveLocalVarName name with
    | Some (VariantSymbol variantSerial) -> TVariantPat(variantSerial, ty, loc), ctx

    | _ ->
      match name with
      | "None" -> TNodePat(TNonePN, [], ty, loc), ctx
      | "Some" -> TNodePat(TSomePN, [], ty, loc), ctx

      | _ ->
        let varSerial, ctx =
          doResolveVarInPat serial name ty loc ctx

        TVarPat(vis, varSerial, ty, loc), ctx

let private nameResNavPat pat ctx =
  /// Resolves a pattern as scope.
  ///
  /// Returns (scopeOpt, pat).
  /// scopeOpt is `Some s` if pat is resolved to scope `s`.
  /// `pat` is also updated by resolving inner qualifiers as possible.
  let rec resolvePatAsNsOwners pat ctx : NsOwner list =
    match pat with
    | TVarPat (_, varSerial, _, _) ->
      let name = ctx |> findVarName varSerial
      ctx |> resolveLocalNsOwners name

    | TNodePat (TNavPN r, [ l ], _, _) ->
      ctx
      |> resolvePatAsNsOwners l
      |> List.collect (fun nsOwner -> ctx |> resolveSubNsOwners nsOwner r)

    | _ -> []

  let l, r, ty, loc =
    match pat with
    | TNodePat (TNavPN r, [ l ], ty, loc) -> l, r, ty, loc
    | _ -> unreachable ()

  let notResolved ctx =
    let ctx = ctx |> addLog UnresolvedNavPatError loc
    tpAbort noTy loc, ctx

  let patOpt =
    resolvePatAsNsOwners l ctx
    |> List.tryPick (fun nsOwner ->
      match ctx |> resolveScopedVarName nsOwner r with
      | Some (VariantSymbol variantSerial) -> Some(TVariantPat(variantSerial, ty, loc))
      | _ -> None)

  match patOpt with
  | Some pat -> pat, ctx
  | None -> notResolved ctx

let private nameResAppPat l r loc ctx =
  let l, ctx = (l, ctx) |> nameResPat
  let r, ctx = (r, ctx) |> nameResPat

  match l with
  | TNodePat (TSomePN, [], _, _) -> TNodePat(TSomeAppPN, [ r ], noTy, loc), ctx
  | TVariantPat (variantSerial, _, _) -> TNodePat(TVariantAppPN variantSerial, [ r ], noTy, loc), ctx
  | _ ->
    let ctx =
      ctx
      |> addLog (OtherNameResLog "Pattern can apply to Some or a variant that takes a payload.") loc

    tpAbort noTy loc, ctx

let private nameResAscribePat bodyPat ascriptionTy loc ctx =
  let ascriptionTy, ctx = ctx |> resolveTy ascriptionTy loc
  let bodyPat, ctx = (bodyPat, ctx) |> nameResPat
  TNodePat(TAscribePN, [ bodyPat ], ascriptionTy, loc), ctx

let private nameResAsPat bodyPat serial loc ctx =
  let bodyPat, ctx = (bodyPat, ctx) |> nameResPat

  let varSerial, ctx =
    let name = ctx |> findName serial
    doResolveVarInPat serial name noTy loc ctx

  TAsPat(bodyPat, varSerial, loc), ctx

let private nameResPat (pat: TPat, ctx: ScopeCtx) =
  match pat with
  | TLitPat _
  | TDiscardPat _
  | TVariantPat _ -> pat, ctx

  | TVarPat (vis, VarSerial serial, ty, loc) -> nameResVarPat vis serial ty loc ctx

  | TNodePat (kind, argPats, ty, loc) ->
    let fail () = unreachable pat

    match kind, argPats with
    | TNilPN, _
    | TNonePN, _
    | TSomePN, _
    | TAbortPN, _ ->
      assert (List.isEmpty argPats)
      pat, ctx

    | TAppPN, [ l; r ] -> nameResAppPat l r loc ctx
    | TAppPN, _ -> fail ()

    | TConsPN, _
    | TSomeAppPN, _
    | TVariantAppPN _, _
    | TTuplePN, _ ->
      let argPats, ctx = (argPats, ctx) |> stMap nameResPat
      TNodePat(kind, argPats, ty, loc), ctx

    | TNavPN _, [ _ ] -> nameResNavPat pat ctx
    | TNavPN _, _ -> fail ()

    | TAscribePN, [ bodyPat ] -> nameResAscribePat bodyPat ty loc ctx
    | TAscribePN, _ -> fail ()

  | TAsPat (bodyPat, VarSerial serial, loc) -> nameResAsPat bodyPat serial loc ctx

  | TOrPat (l, r, loc) ->
    // No OR patterns appear in arm patterns due to normalization.
    // So we can assume that it's inside of irrefutable pattern.
    let ctx = ctx |> addLog IllegalOrPatError loc

    let l, ctx = (l, ctx) |> nameResPat
    let r, ctx = (r, ctx) |> nameResPat
    TOrPat(l, r, loc), ctx

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

let private nameResRefutablePat (pat: TPat, ctx: ScopeCtx) =
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
    |> stMap (fun (pat, ctx) ->
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
    List.fold (fun l r -> TOrPat(l, r, loc)) pat pats

  pat, ctx

let private nameResIrrefutablePat (pat: TPat, ctx: ScopeCtx) =
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

[<NoEquality; NoComparison>]
type private ResolvedExpr =
  | ResolvedAsExpr of TExpr
  | ResolvedAsScope of NsOwner list * TExpr option * Loc
  | NotResolvedExpr of Ident * Loc

/// Tries to resolve a name expression as value; or just return None.
let private doNameResVarExpr expr ctx =
  let serial, ty, loc =
    match expr with
    | TVarExpr (VarSerial serial, ty, loc) -> serial, ty, loc
    | _ -> unreachable ()

  let name = ctx |> findName serial

  match ctx |> resolveLocalVarName name with
  | Some (VarSymbol serial) -> TVarExpr(serial, ty, loc) |> Some
  | Some (FunSymbol serial) -> TFunExpr(serial, ty, loc) |> Some
  | Some (VariantSymbol serial) -> TVariantExpr(serial, ty, loc) |> Some

  | None ->
    match primFromIdent name with
    | Some prim -> TPrimExpr(prim, ty, loc) |> Some
    | None -> None

let private nameResVarExpr expr ctx =
  match doNameResVarExpr expr ctx with
  | Some expr -> expr, ctx

  | None ->
    let name, loc =
      match expr with
      | TVarExpr (VarSerial serial, _, loc) -> findName serial ctx, loc
      | _ -> unreachable ()

    let ctx =
      ctx |> addLog (UndefinedValueError name) loc

    txAbort loc, ctx

let private nameResNavExpr expr ctx =
  /// Resolves an expressions as scope.
  ///
  /// Returns (scopeOpt, exprOpt).
  /// scopeOpt should eb some it can be resolved to scope.
  /// exprOpt is also obtained by resolving inner `nav`s as possible.
  let rec resolveExprAsNsOwners expr ctx : ResolvedExpr * ScopeCtx =
    match expr with
    | TVarExpr (VarSerial serial, _, loc) ->
      let name = ctx |> findName serial
      let nsOwners = ctx |> resolveLocalNsOwners name
      let exprOpt = doNameResVarExpr expr ctx

      match nsOwners, exprOpt with
      | [], None -> NotResolvedExpr(name, loc), ctx
      | [], Some expr -> ResolvedAsExpr expr, ctx
      | _ -> ResolvedAsScope(nsOwners, exprOpt, loc), ctx

    | TNavExpr (l, r, ty, loc) ->
      let l, ctx = ctx |> resolveExprAsNsOwners l

      match l with
      | NotResolvedExpr _ -> l, ctx

      | ResolvedAsExpr l -> ResolvedAsExpr(TNavExpr(l, r, ty, loc)), ctx

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
            |> List.tryPick (fun nsOwner ->
              match ctx |> resolveScopedVarName nsOwner r with
              | None -> None
              | it -> it)

          match varSymbolOpt with
          | Some (VarSymbol varSerial) -> TVarExpr(varSerial, ty, loc) |> Some
          | Some (FunSymbol funSerial) -> TFunExpr(funSerial, ty, loc) |> Some
          | Some (VariantSymbol variantSerial) -> TVariantExpr(variantSerial, ty, loc) |> Some
          | None -> None

        // If not resolved as value, keep try to unresolved.
        let exprOpt =
          match exprOpt, lExprOpt with
          | Some _, _ -> exprOpt
          | None, Some l -> TNavExpr(l, r, ty, loc) |> Some
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
    txAbort loc, ctx

  | NotResolvedExpr (name, loc) ->
    let ctx =
      ctx |> addLog (UndefinedValueError name) loc

    txAbort loc, ctx

let private nameResExpr (expr: TExpr, ctx: ScopeCtx) : TExpr * ScopeCtx =
  match expr with
  | TLitExpr _
  | TPrimExpr _ -> expr, ctx

  | TVarExpr _ -> nameResVarExpr expr ctx

  | TRecordExpr (baseOpt, fields, ty, loc) ->
    let baseOpt, ctx =
      (baseOpt, ctx) |> stOptionMap nameResExpr

    let fields, ctx =
      (fields, ctx)
      |> stMap (fun ((name, init, loc), ctx) ->
        let init, ctx = (init, ctx) |> nameResExpr
        (name, init, loc), ctx)

    TRecordExpr(baseOpt, fields, ty, loc), ctx

  | TMatchExpr (cond, arms, ty, loc) ->
    let cond, ctx = (cond, ctx) |> nameResExpr

    let arms, ctx =
      (arms, ctx)
      |> stMap (fun ((pat, guard, body), ctx) ->
        let ctx = ctx |> startScope ExprScope
        let pat, ctx = (pat, ctx) |> nameResRefutablePat
        let guard, ctx = (guard, ctx) |> nameResExpr
        let body, ctx = (body, ctx) |> nameResExpr
        let ctx = ctx |> finishScope
        (pat, guard, body), ctx)

    TMatchExpr(cond, arms, ty, loc), ctx

  | TNavExpr _ -> nameResNavExpr expr ctx

  | TNodeExpr (op, items, ty, loc) ->
    // Necessary in case of ascribe expression.
    let ty, ctx = ctx |> resolveTy ty loc

    let items, ctx = (items, ctx) |> stMap nameResExpr
    TNodeExpr(op, items, ty, loc), ctx

  | TBlockExpr (NotRec, stmts, last) ->
    let ctx = ctx |> startScope ExprScope
    let stmts, ctx = (stmts, ctx) |> stMap nameResStmt
    let last, ctx = (last, ctx) |> nameResExpr
    let ctx = ctx |> finishScope
    TBlockExpr(NotRec, stmts, last), ctx

  | TFunExpr _ // TFunExpr is generated in NameRes.
  | TVariantExpr _ // TVariantExpr is generated in NameRes.
  | TBlockExpr (IsRec, _, _) -> // Recursive TBlockExpr is generated in NameRes.
    unreachable ()

let private nameResStmt (stmt, ctx) : TStmt * ScopeCtx =
  match stmt with
  | TExprStmt expr ->
    let expr, ctx = (expr, ctx) |> nameResExpr
    TExprStmt expr, ctx

  | TLetValStmt (pat, body, loc) ->
    let ctx = ctx |> startScope ExprScope
    let body, ctx = (body, ctx) |> nameResExpr
    let ctx = ctx |> finishScope

    let pat, ctx = (pat, ctx) |> nameResIrrefutablePat
    TLetValStmt(pat, body, loc), ctx

  | TLetFunStmt (serial, IsRec, vis, pats, body, loc) ->
    // Define the function itself for recursive referencing.
    // (If this declaration is not written in module directly, visibility meaning less, so use PrivateVis.)
    let ctx =
      ctx
      |> enterLetInit serial
      |> defineFunUniquely PrivateVis serial pats noTy loc
      |> startScope ExprScope

    let pats, ctx =
      (pats, ctx) |> stMap nameResIrrefutablePat

    let body, ctx = (body, ctx) |> nameResExpr
    let ctx = ctx |> finishScope |> leaveLetInit
    TLetFunStmt(serial, IsRec, vis, pats, body, loc), ctx

  | TLetFunStmt (serial, NotRec, vis, pats, body, loc) ->
    let ctx =
      ctx |> enterLetInit serial |> startScope ExprScope

    let pats, ctx =
      (pats, ctx) |> stMap nameResIrrefutablePat

    let body, ctx = (body, ctx) |> nameResExpr

    let ctx =
      ctx
      |> finishScope
      |> defineFunUniquely PrivateVis serial pats noTy loc
      |> leaveLetInit

    TLetFunStmt(serial, NotRec, vis, pats, body, loc), ctx

  | TTyDeclStmt (serial, _, tyArgs, tyDecl, loc) ->
    let ctx =
      ctx |> finishDefineTy serial tyArgs tyDecl loc

    stmt, ctx

  | TOpenStmt _ -> stmt, ctx

  | TModuleStmt (serial, body, loc) ->
    let moduleName =
      ctx |> findName (moduleTySerialToInt serial)

    let ctx = ctx |> importNs (ModuleNsOwner serial)

    let parent, ctx = ctx |> enterModule serial

    let ctx = ctx |> startScope ExprScope

    let ctx =
      // Open the parent module (and modules with the same path).
      ctx
      |> forList (fun moduleTySerial ctx -> openModule moduleTySerial ctx) (ctx |> resolveModulePath (snd parent))

    let stmts, ctx =
      nameResModuleBody (Some serial) (body, ctx)

    let ctx = ctx |> finishScope |> leaveModule parent

    // HACK: MiloneOnly is auto-open.
    let ctx =
      if moduleName = "MiloneOnly" then
        ctx |> openModule serial
      else
        ctx

    TExprStmt(TBlockExpr(IsRec, stmts, txUnit loc)), ctx

  | TModuleSynonymStmt (serial, path, loc) ->
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
          |> forList (fun moduleSerial ctx -> doImportNsWithAlias name (ModuleNsOwner moduleSerial) ctx) moduleSerials

    // No longer necessary.
    TExprStmt(txUnit loc), ctx

let private nameResModuleBody serialOpt (stmts, ctx) : TStmt list * ScopeCtx =
  (stmts, ctx)
  |> stMap (collectDecls serialOpt)
  |> stMap nameResStmt

// -----------------------------------------------
// Interface
// -----------------------------------------------

let nameRes (layers: TProgram list, nameCtx: NameCtx) : TProgram * NameResResult =
  let layers, state =
    layers
    |> List.mapFold
         (fun (state: NameResState) layer ->
           // Single scopeCtx is used to do NameRes all modules in current layer.
           let scopeCtx = state.ScopeCtx

           let modulesCtxs =
             layer
             |> __parallelMap (fun (m: TModule) ->
               let stmts, scopeCtx =
                 nameResModuleBody None (m.Stmts, scopeCtx)

               let m = { m with Stmts = stmts }
               m, scopeCtx)

           modulesCtxs
           |> List.mapFold
                (fun state (m: TModule, scopeCtx) ->
                  let state, localVars = sMerge state scopeCtx
                  { m with Vars = localVars }, state)
                state)
         (sInit nameCtx)

  let result = sToResult state

  List.collect id layers, result
