/// # Name resolution
///
/// Resolves symbols as possible.
///
/// This stage traverses the expressions twice
/// to collect symbol information
/// and assign the same serials to the same symbols.
module rec MiloneSyntax.NameRes

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open Std.StdMultimap
open Std.StdSet
open MiloneSyntax.Tir
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.TirTypes

module S = Std.StdString

let private optionMapFold (mapFolder: 'S -> 'T -> 'U * 'S) (state: 'S) (opt: 'T option) : 'U option * 'S =
  match opt with
  | Some item ->
    let item, state = mapFolder state item
    Some item, state

  | None -> None, state

let private listChooseFold (mapFolder: 'S -> 'T -> 'U option * 'S) (state: 'S) (xs: 'T list) : 'U list * 'S =
  let yss, state = List.mapFold mapFolder state xs
  yss |> List.choose id, state

let private listCollectFold (mapFolder: 'S -> 'T -> 'U list * 'S) (state: 'S) (xs: 'T list) : 'U list * 'S =
  let yss, state = List.mapFold mapFolder state xs
  yss |> List.collect id, state

let private identOf (name: NName) = fst name

/// Identity of token based on its text position. (Byte index is better though.)
///
/// While both row number  and column number are 32-bit,
/// PosId is compressed to 32-bit.
///
/// Heuristically most of source files follow either:
///    1. y <= 2^23 and x <= 2^9 (manually written)
///    2. x <= 2^23 and y <= 2^9 (machinery generated)
/// (noting that 2^9 ~ 500, 2^23 ~ 8M.)
///
/// By rotating x by 23 bits up, y and x likely become orthogonal.
type private PosId = uint

let private posOf (name: NName) : PosId =
  let _, (Loc (_, y, x)) = name
  let y = uint y
  let x = uint x
  y ^^^ ((x <<< 23) ||| (x >>> 9))

let private npLoc pat : Loc =
  match pat with
  | NPat.Bad loc -> loc
  | NPat.Ident (_, (_, loc)) -> loc
  | NPat.Discard loc -> loc
  | NPat.Nav (_, _, loc) -> loc
  | NPat.As (_, _, loc) -> loc
  | NPat.Ascribe (_, _, loc) -> loc
  | NPat.Or (_, _, loc) -> loc
  | NPat.Lit (_, loc) -> loc
  | NPat.Nil loc -> loc
  | NPat.Cons (_, _, loc) -> loc
  | NPat.Tuple (_, loc) -> loc
  | NPat.VariantApp (_, _, loc) -> loc

type private ModuleTySerial = Serial
type private ModuleSynonymSerial = Serial

let private noTy = tyError noLoc
let private txTrue loc = TLitExpr(BoolLit true, loc)
let private txAbort loc = TNodeExpr(TAbortEN, [], noTy, loc)
let private txApp f x loc = TNodeExpr(TAppEN, [ f; x ], noTy, loc)
let private txApp2 f x1 x2 loc = txApp (txApp f x1 loc) x2 loc

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
  | "uint32", [] -> Ty(IntTk U32, []) |> Some
  | "sbyte", []
  | "int8", [] -> Ty(IntTk I8, []) |> Some
  | "byte", []
  | "uint8", [] -> Ty(IntTk U8, []) |> Some

  | "int16", [] -> Ty(IntTk I16, []) |> Some
  | "int64", [] -> Ty(IntTk I64, []) |> Some
  | "nativeint", [] -> Ty(IntTk IPtr, []) |> Some
  | "uint16", [] -> Ty(IntTk U16, []) |> Some
  | "uint64", [] -> Ty(IntTk U64, []) |> Some
  | "unativeint", [] -> Ty(IntTk UPtr, []) |> Some

  | "float", [] -> Some tyFloat
  | "char", [] -> Some tyChar
  | "string", [] -> Some tyStr
  | "obj", [] -> Some tyObj

  | "list", [ itemTy ] -> Some(tyList itemTy)

  | "voidptr", [] -> Ty(VoidPtrTk, []) |> Some
  | "nativeptr", [ itemTy ] -> Ty(NativePtrTk IsMut, [ itemTy ]) |> Some
  | "__constptr", [ itemTy ] -> Ty(NativePtrTk IsConst, [ itemTy ]) |> Some

  | "__nativeFun", [ Ty (TupleTk, itemTys); resultTy ] ->
    Ty(NativeFunTk, List.append itemTys [ resultTy ])
    |> Some

  | "__nativeFun", [ itemTy; resultTy ] -> Ty(NativeFunTk, [ itemTy; resultTy ]) |> Some

  | _ -> None

let private binaryToPrim op : TPrim =
  match op with
  | AddBinary -> TPrim.Add
  | SubBinary -> TPrim.Sub
  | MulBinary -> TPrim.Mul
  | DivBinary -> TPrim.Div
  | ModuloBinary -> TPrim.Modulo
  | BitAndBinary -> TPrim.BitAnd
  | BitOrBinary -> TPrim.BitOr
  | BitXorBinary -> TPrim.BitXor
  | LeftShiftBinary -> TPrim.LeftShift
  | RightShiftBinary -> TPrim.RightShift
  | EqualBinary -> TPrim.Equal
  | LessBinary -> TPrim.Less
  | ConsBinary -> TPrim.Cons

  | AppBinary // Handled specially.

  | NotEqualBinary
  | LessEqualBinary
  | GreaterBinary
  | GreaterEqualBinary
  | LogicalAndBinary
  | LogicalOrBinary
  | PipeBinary -> unreachable () // Desugared in NirGen.

// -----------------------------------------------
// Symbols
// -----------------------------------------------

let private tySymbolToSerial symbol =
  match symbol with
  | UnivTySymbol s -> s
  | SynonymTySymbol s -> s
  | UnionTySymbol s -> s
  | RecordTySymbol s -> s

// -----------------------------------------------
// NsOwner
// -----------------------------------------------

/// Identity of namespace owner.
type private NsOwner = uint

let private nsOwnerOfTy tySerial = uint tySerial <<< 1
let private nsOwnerOfModule moduleSerial = (uint moduleSerial <<< 1) ||| 1u

let private nsOwnerAsModule (nsOwner: NsOwner) : ModuleTySerial option =
  if (nsOwner &&& 1u) <> 0u then
    Some(int (nsOwner >>> 1))
  else
    None

let private nsOwnerCompare (l: NsOwner) r : int = compare l r

let private nsOwnerOfTySymbol (tySymbol: TySymbol) : NsOwner = nsOwnerOfTy (tySymbolToSerial tySymbol)

let private nsOwnerDump (nsOwner: NsOwner) = nsOwner |> string

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
    ns |> nsFind key |> Multimap.add ident value

  ns |> TMap.add key submap

// --------------------------------------------
// Scopes
// --------------------------------------------

// In expr scope, type variable can be used and defined without explicit declaration.
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
  { ScopeCtx: ScopeCtx
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Logs: (NameResLog * Loc) list }

let private emptyState () : NameResState =
  { ScopeCtx = emptyScopeCtx ()
    Vars = emptyVars
    Funs = TMap.empty funSerialCompare
    Variants = TMap.empty variantSerialCompare
    Logs = [] }

let private mapMerge first second : TreeMap<_, _> =
  second
  |> TMap.fold (fun map key value -> TMap.add key value map) first

let private mapAddEntries (entries: ('K * 'T) list) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
  entries
  |> List.rev
  |> List.fold (fun map (key, value) -> TMap.add key value map) map

let private mergeChain xs1 xs2 : ScopeChain<_> =
  [ List.append xs1 xs2
    |> List.fold mapMerge (scopeMapEmpty ()) ]

/// Merges two scopes into flattened scope.
let private scopeMerge (first: Scope) (second: Scope) : Scope =
  let _, values1, tys1, nss1 = first
  let _, values2, tys2, nss2 = second
  [], mergeChain values1 values2, mergeChain tys1 tys2, mergeChain nss1 nss2

let private sMerge newRootModule (state: NameResState) (ctx: ScopeCtx) : NameResState * _ =
  let s = state.ScopeCtx

  let globalVars, localVars =
    ctx.NewVars
    |> List.fold
         (fun (globalVars, localVars) (varSerial, varDef: VarDef) ->
           match TMap.tryFind varSerial ctx.NewVarMeta with
           | Some (isStatic, linkage) ->
             // Definition is always for non-static. Inherits meta data here.
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
            Serial = ctx.Serial
            Tys = mapAddEntries ctx.NewTys s.Tys
            RootModules = newRootModule :: s.RootModules

            // These seem inefficient but not.
            Local = scopeMerge ctx.Local s.Local
            VarNs = mapMerge s.VarNs ctx.VarNs
            TyNs = mapMerge s.TyNs ctx.TyNs
            NsNs = mapMerge s.NsNs ctx.NsNs }

      Vars = globalVars
      Funs = mapAddEntries ctx.NewFuns state.Funs
      Variants = mapAddEntries ctx.NewVariants state.Variants
      Logs = List.append ctx.NewLogs state.Logs },
  localVars

let private sToResult mainFunOpt (state: NameResState) : NameResResult =
  let ctx = state.ScopeCtx

  { Serial = ctx.Serial
    Vars = state.Vars
    Funs = state.Funs
    Variants = state.Variants
    Tys = ctx.Tys
    MainFunOpt = mainFunOpt
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
    MainFunOpt: FunSerial option
    Logs: (NameResLog * Loc) list }

// -----------------------------------------------
// ScopeCtx
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ScopeCtx =
  { Serial: Serial

    // Partial definitions created by collect declaration.
    DeclaredVars: TreeMap<PosId, VarSerial>
    DeclaredFuns: TreeMap<PosId, FunSerial>
    DeclaredVariants: TreeMap<PosId, VariantSerial>
    DeclaredTys: TreeMap<PosId, TySerial * TySymbol>
    DeclaredTyArities: TreeMap<TySerial, Arity>
    DeclaredModules: TreeMap<PosId, Serial>

    NewVars: (VarSerial * VarDef) list
    NewFuns: (FunSerial * FunDef) list
    NewVariants: (VariantSerial * VariantDef) list

    NewVarMeta: TreeMap<VarSerial, IsStatic * Linkage>

    Tys: TreeMap<TySerial, TyDef>
    NewTys: (TySerial * TyDef) list

    RootModules: (Ident * ModuleTySerial) list
    CurrentPath: string list
    AncestralFuns: Ident list

    VarNs: Ns<ValueSymbol>
    TyNs: Ns<TySymbol>
    /// Subspaces.
    NsNs: Ns<NsOwner list>

    /// Current scope.
    Local: Scope

    /// Variables defined in current pattern.
    ///
    /// name -> (varSerial, definedLoc, usedLoc list)
    PatScope: TreeMap<Ident, VarSerial * Loc * Loc list>

    NewLogs: (NameResLog * Loc) list }

let private emptyScopeCtx () : ScopeCtx =
  { Serial = 0
    DeclaredVars = TMap.empty compare
    DeclaredFuns = TMap.empty compare
    DeclaredVariants = TMap.empty compare
    DeclaredTys = TMap.empty compare
    DeclaredTyArities = TMap.empty compare
    DeclaredModules = TMap.empty compare
    NewVars = []
    NewFuns = []
    NewVariants = []
    NewVarMeta = TMap.empty varSerialCompare
    Tys = TMap.empty compare
    NewTys = []
    RootModules = []
    CurrentPath = []
    AncestralFuns = []
    VarNs = TMap.empty nsOwnerCompare
    TyNs = TMap.empty nsOwnerCompare
    NsNs = TMap.empty nsOwnerCompare
    Local = scopeEmpty ()
    PatScope = TMap.empty compare
    NewLogs = [] }

let private freshSerial (ctx: ScopeCtx) =
  let serial = ctx.Serial + 1
  serial, { ctx with Serial = serial }

let private freshVarSerial (ctx: ScopeCtx) =
  let serial, ctx = freshSerial ctx
  VarSerial serial, ctx

let private freshFunSerial (ctx: ScopeCtx) =
  let serial, ctx = freshSerial ctx
  FunSerial serial, ctx

let private freshVariantSerial (ctx: ScopeCtx) =
  let serial, ctx = freshSerial ctx
  VariantSerial serial, ctx

let private addLog (log: NameResLog) (loc: Loc) (ctx: ScopeCtx) =
  { ctx with NewLogs = (log, loc) :: ctx.NewLogs }

let private errorTy ctx log loc : Ty * ScopeCtx =
  let ctx = ctx |> addLog log loc
  tyError loc, ctx

let private errorPat ctx log loc : TPat * ScopeCtx =
  let ctx = addLog log loc ctx
  tpAbort noTy loc, ctx

let private errorExpr ctx log loc : TExpr * ScopeCtx =
  let ctx = addLog log loc ctx
  txAbort loc, ctx

let private makeLinkage vis name (ctx: ScopeCtx) =
  match vis with
  | PublicVis -> ExternalLinkage(S.concat "_" ctx.CurrentPath + "_" + name)
  | PrivateVis -> InternalLinkage

/// Adds a definition of var (not regarding static or not).
///
/// This doesn't imply it's added to any scope or namespace.
let private addVarDef varSerial (varDef: VarDef) (ctx: ScopeCtx) : ScopeCtx =
  { ctx with NewVars = (varSerial, varDef) :: ctx.NewVars }

let private addFunDef funSerial funDef (ctx: ScopeCtx) : ScopeCtx =
  { ctx with NewFuns = (funSerial, funDef) :: ctx.NewFuns }

let private addVariantDef variantSerial variantDef (ctx: ScopeCtx) : ScopeCtx =
  { ctx with NewVariants = (variantSerial, variantDef) :: ctx.NewVariants }

/// Adds a definition of type symbol.
let private addTyDef tySerial tyDef (ctx: ScopeCtx) : ScopeCtx =
  { ctx with
      Tys = ctx.Tys |> TMap.add tySerial tyDef
      NewTys = (tySerial, tyDef) :: ctx.NewTys }

/// Makes a value symbol accessible from a namespace.
let private addValueToNs (nsOwner: NsOwner) name valueSymbol (ctx: ScopeCtx) : ScopeCtx =
  // __trace (
  //   "addVarToNs "
  //   + nsOwnerDump nsOwner
  //   + "."
  //   + name
  //   + " = "
  //   + string (valueSymbolToSerial valueSymbol)
  // )

  { ctx with VarNs = ctx.VarNs |> nsAdd nsOwner name valueSymbol }

/// Makes a type symbol accessible from a namespace.
let private addTyToNs (nsOwner: NsOwner) name tySymbol (ctx: ScopeCtx) : ScopeCtx =
  // __trace (
  //   "addTyToNs "
  //   + nsOwnerDump nsOwner
  //   + "."
  //   + name
  //   + " = "
  //   + string (tySymbolToSerial tySymbol)
  // )

  { ctx with
      TyNs = ctx.TyNs |> nsAdd nsOwner name tySymbol

      NsNs =
        ctx.NsNs
        |> nsMerge nsOwner name (nsOwnerOfTySymbol tySymbol) }

/// Makes a child namespace accessible from a namespace.
///
/// `<parent>.<name>` can be resolved to `<child>`.
let private addNsToNs (parentNsOwner: NsOwner) name (childNsOwner: NsOwner) (ctx: ScopeCtx) : ScopeCtx =
  // __trace (
  //   "addNsToNs "
  //   + nsOwnerDump parentNsOwner
  //   + "."
  //   + name
  //   + " = "
  //   + nsOwnerDump childNsOwner
  // )

  { ctx with
      NsNs =
        ctx.NsNs
        |> nsMerge parentNsOwner name childNsOwner }

/// Adds a value symbol to current scope.
let private importValue alias (symbol: ValueSymbol) (ctx: ScopeCtx) : ScopeCtx =
  assert (alias <> "_")

  let scope: Scope =
    match ctx.Local with
    | kinds, map :: varScopes, tyScopes, nsScopes ->
      let varScopes =
        (map |> TMap.add alias symbol) :: varScopes

      kinds, varScopes, tyScopes, nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { ctx with Local = scope }

/// Adds a type symbol to current scope.
let private importTy alias (symbol: TySymbol) (ctx: ScopeCtx) : ScopeCtx =
  let scope: Scope =
    match ctx.Local with
    | kinds, varScopes, (tyMap :: tyScopes), (nsMap :: nsScopes) ->
      let tyMap = tyMap |> TMap.add alias symbol

      let nsMap =
        nsMap
        |> Multimap.add alias (nsOwnerOfTySymbol symbol)

      kinds, varScopes, tyMap :: tyScopes, nsMap :: nsScopes

    | _ -> unreachable () // Scope can't be empty.

  { ctx with Local = scope }

/// Adds an NsOwner to current scope.
let private importNsOwner alias nsOwner (ctx: ScopeCtx) : ScopeCtx =
  let scope: Scope =
    match ctx.Local with
    | kinds, varScopes, tyScopes, ((map :: nsScopes) as allNsScopes) ->
      let shadowed =
        allNsScopes
        |> List.tryPick (fun map -> map |> TMap.tryFind alias)
        |> Option.defaultValue []

      let map =
        map |> TMap.add alias (nsOwner :: shadowed)

      kinds, varScopes, tyScopes, map :: nsScopes

    | _ -> unreachable () // Scope can't be empty.

  { ctx with Local = scope }

/// Imports all members of the module to current scope.
let private openModule moduleSerial (ctx: ScopeCtx) =
  // Import vars.
  let ctx =
    ctx.VarNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold (fun ctx name symbol -> ctx |> importValue name symbol) ctx

  // Import tys.
  let ctx =
    ctx.TyNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold (fun ctx name symbol -> ctx |> importTy name symbol) ctx

  // Import subnamespaces.
  let ctx =
    ctx.NsNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold (fun ctx name nsOwners -> ctx |> forList (importNsOwner name) nsOwners) ctx

  ctx

let private openModules moduleSerials ctx =
  moduleSerials
  |> List.fold (fun ctx moduleSerial -> ctx |> openModule moduleSerial) ctx

/// Called on enter the init of let-fun expressions.
let private enterLetInit funName (ctx: ScopeCtx) : ScopeCtx =
  { ctx with AncestralFuns = funName :: ctx.AncestralFuns }

let private leaveLetInit (ctx: ScopeCtx) : ScopeCtx =
  { ctx with AncestralFuns = listSkip 1 ctx.AncestralFuns }

let private isTyDeclScope (ctx: ScopeCtx) =
  match ctx.Local with
  | TyDeclScope :: _, _, _, _ -> true
  | _ -> false

/// Starts a new scope.
let private startScope kind (ctx: ScopeCtx) : ScopeCtx =
  let kinds, varScopes, tyScopes, nsScopes = ctx.Local

  { ctx with
      Local = kind :: kinds, scopeMapEmpty () :: varScopes, scopeMapEmpty () :: tyScopes, scopeMapEmpty () :: nsScopes }

let private finishScope (ctx: ScopeCtx) : ScopeCtx =
  match ctx.Local with
  | [], _, _, _
  | _, [], _, _
  | _, _, [], _
  | _, _, _, [] -> unreachable () // Scope can't be empty..

  | _ :: kinds, _ :: varScopes, _ :: tyScopes, _ :: nsScopes ->
    { ctx with Local = kinds, varScopes, tyScopes, nsScopes }

let private enterModule (moduleName: Ident) (ctx: ScopeCtx) =
  let parent = ctx.CurrentPath

  let ctx =
    { ctx with CurrentPath = List.append ctx.CurrentPath [ moduleName ] }

  parent, ctx

let private leaveModule parent (ctx: ScopeCtx) =
  let currentPath = parent
  { ctx with CurrentPath = currentPath }

// -----------------------------------------------
// Resolve
// -----------------------------------------------

/// Resolves a module path to all modules
/// that can be accessible by the path.
///
/// Remarks: Multiple module with same name can exist at a path.
let private resolveModulePath (path: Ident list) (ctx: ScopeCtx) : ModuleTySerial list =
  match path with
  | [] -> []
  | head :: tail ->
    let roots =
      ctx.RootModules
      |> List.choose (fun (moduleName, moduleSerial) ->
        if moduleName = head then
          Some moduleSerial
        else
          None)

    let rec go serial path =
      match path with
      | [] -> [ serial ]

      | name :: tail ->
        ctx
        |> resolveQualifiedNsOwner (nsOwnerOfModule serial) name
        |> List.collect (fun nsOwner ->
          match nsOwnerAsModule nsOwner with
          | Some serial -> go serial tail
          | None -> [])

    roots
    |> List.collect (fun serial -> go serial tail)

/// Resolves an ident qualified by the specified namespace to a value symbol.
let private resolveQualifiedValue nsOwner name (ctx: ScopeCtx) : ValueSymbol option =
  ctx.VarNs |> nsFind nsOwner |> TMap.tryFind name

/// Resolves an ident qualified by the specified namespace to a type symbol.
let private resolveQualifiedTy nsOwner name (ctx: ScopeCtx) : TySymbol option =
  ctx.TyNs |> nsFind nsOwner |> TMap.tryFind name

/// Resolves a qualified NsOwner to all candidates.
let private resolveQualifiedNsOwner nsOwner name (ctx: ScopeCtx) : NsOwner list =
  ctx.NsNs |> nsFind nsOwner |> Multimap.find name

/// Resolves an unqualified ident to a value symbol from current scope.
let private resolveUnqualifiedValue name (ctx: ScopeCtx) =
  let _, varScopes, _, _ = ctx.Local

  varScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)

/// Resolves an unqualified ident to a type symbol from current scope.
let private resolveUnqualifiedTy name (ctx: ScopeCtx) : TySymbol option =
  let _, _, tyScopes, _ = ctx.Local

  tyScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)

/// Resolves an unqualified NsOwner to all candidates.
let private resolveUnqualifiedNsOwner name (ctx: ScopeCtx) : NsOwner list =
  let _, _, _, nsScopes = ctx.Local

  nsScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind name)
  |> Option.defaultValue []

/// Resolves qualifiers of type.
let private resolveNavTy quals last ctx : TySymbol option * ScopeCtx =
  match quals with
  | [] -> ctx |> resolveUnqualifiedTy last, ctx

  | head :: tail ->
    // Resolve head.
    let nsOwners = ctx |> resolveUnqualifiedNsOwner head

    // Resolve tail.
    let rec resolveTyPath (nsOwner: NsOwner) path ctx =
      match path with
      | [] -> [ nsOwner ]

      | name :: path ->
        ctx
        |> resolveQualifiedNsOwner nsOwner name
        |> List.collect (fun subNsOwner -> resolveTyPath subNsOwner path ctx)

    let tySymbolOpt =
      nsOwners
      |> List.collect (fun nsOwner -> resolveTyPath nsOwner tail ctx)
      |> List.tryPick (fun nsOwner -> resolveQualifiedTy nsOwner last ctx)

    tySymbolOpt, ctx

/// Resolves type names in a type expression.
///
/// selfTyArgs: Type parameters defined by current type declaration.
let private resolveTy ctx ty selfTyArgs : Ty * ScopeCtx =
  let rec go ctx ty : Ty * ScopeCtx =
    match ty with
    | NTy.Bad loc -> tyError loc, ctx

    | NTy.Var (name, loc) ->
      let resolved =
        match selfTyArgs |> TMap.tryFind name with
        | (Some _) as some -> some
        | None -> resolveUnqualifiedTy name ctx

      match resolved with
      | Some (UnivTySymbol tySerial) -> tyUniv tySerial name loc, ctx

      | _ when ctx |> isTyDeclScope -> errorTy ctx (UndefinedTyError name) loc

      | _ ->
        // Define new type variable on the fly.
        let tySerial, ctx = freshSerial ctx

        // __trace ("typeVar " + string tySerial + ":" + name)

        let ctx =
          ctx
          |> addTyDef tySerial (UnivTyDef(name, loc))
          |> importTy name (UnivTySymbol tySerial)

        tyUniv tySerial name loc, ctx

    // `__nativeType<T>`
    | NTy.App ([], ("__nativeType", _), [ NTy.App ([], (code, _), [], _) ], _) -> Ty(NativeTypeTk code, []), ctx

    | NTy.App (quals, name, tyArgs, loc) ->
      let name = identOf name
      let arity = List.length tyArgs
      let tyArgs, ctx = tyArgs |> List.mapFold go ctx

      let symbolOpt, ctx =
        let quals = quals |> List.map identOf
        resolveNavTy quals name ctx

      let getArity tySerial =
        match ctx.DeclaredTyArities |> TMap.tryFind tySerial with
        | Some arity -> arity
        | None ->
          match ctx.Tys |> TMap.tryFind tySerial with
          | Some (SynonymTyDef (_, tyArgs, _, _)) -> List.length tyArgs
          | Some (UnionTyDef (_, tyArgs, _, _)) -> List.length tyArgs
          | Some (RecordTyDef (_, tyArgs, _, _, _)) -> List.length tyArgs
          | _ -> 0 // maybe unreachable?

      match symbolOpt with
      | Some (SynonymTySymbol tySerial) ->
        // #ty_arity_check
        let defArity = getArity tySerial

        if defArity <> arity then
          errorTy ctx (TyArityError(name, arity, defArity)) loc
        else
          tySynonym tySerial tyArgs, ctx

      | Some (UnionTySymbol tySerial) ->
        // #ty_arity_check
        let defArity = getArity tySerial

        if defArity <> arity then
          errorTy ctx (TyArityError(name, arity, defArity)) loc
        else
          tyUnion tySerial tyArgs loc, ctx

      | Some (RecordTySymbol tySerial) ->
        // #ty_arity_check
        let defArity = 0 // generic record type is unimplemented

        if arity <> defArity then
          errorTy ctx (TyArityError(name, arity, defArity)) loc
        else
          tyRecord tySerial loc, ctx

      | Some (UnivTySymbol _) -> unreachable () // UnivTySymbol is only resolved from type variable.

      | None ->
        match tyPrimOfName name tyArgs with
        | Some ty -> ty, ctx
        | None -> errorTy ctx (UndefinedTyError name) loc

    | NTy.Infer loc -> Ty(InferTk loc, []), ctx

    | NTy.Fun (sTy, tTy, _) ->
      let sTy, ctx = sTy |> go ctx
      let tTy, ctx = tTy |> go ctx
      tyFun sTy tTy, ctx

    | NTy.Tuple (itemTys, _) ->
      let itemTys, ctx = itemTys |> List.mapFold go ctx
      tyTuple itemTys, ctx

  go ctx ty

// -----------------------------------------------
// Collect declarations
// -----------------------------------------------

// Traverse declarations directly inside `module rec`s
// to register symbol pre-definitions
//    (provide serials, import to scope, add to namespace)
// so that recursive references resolve correctly.
// Complete definitions aren't generated here.

let private isPublic vis =
  match vis with
  | PublicVis -> true
  | _ -> false

/// Exports a value symbol via current module if it's public.
let private exportValue ctx (currentModule: NsOwner) vis name valueSymbol =
  if isPublic vis then
    ctx |> addValueToNs currentModule name valueSymbol
  else
    ctx

let private exportTy ctx currentModule vis name tySerial =
  if isPublic vis then
    ctx |> addTyToNs currentModule name tySerial
  else
    ctx

let private exportModule ctx currentModule vis name subNsOwner =
  if isPublic vis then
    ctx |> addNsToNs currentModule name subNsOwner
  else
    ctx

let private cdPat (currentModule: NsOwner) (ctx: ScopeCtx) pat : ScopeCtx =
  let onVar (ctx: ScopeCtx) vis name =
    let varSerial, ctx = freshVarSerial ctx
    let varSymbol = VarSymbol varSerial

    // __trace (
    //   "cdPatOnVar "
    //   + string (varSerialToInt varSerial)
    //   + ":"
    //   + identOf name
    // )

    let ctx =
      let linkage = makeLinkage vis (identOf name) ctx

      { ctx with
          DeclaredVars =
            ctx.DeclaredVars
            |> TMap.add (posOf name) varSerial
          NewVarMeta =
            ctx.NewVarMeta
            |> TMap.add varSerial (IsStatic, linkage) }

    let ctx =
      ctx |> importValue (identOf name) varSymbol

    exportValue ctx currentModule vis (identOf name) varSymbol

  match pat with
  | NPat.Ident (vis, name) ->
    match ctx |> resolveUnqualifiedValue (identOf name) with
    | Some (VariantSymbol _) -> ctx
    | _ -> onVar ctx vis name

  | NPat.As (bodyPat, name, _) ->
    let ctx = onVar ctx PublicVis name
    bodyPat |> cdPat currentModule ctx

  | NPat.Ascribe _
  | NPat.Cons _
  | NPat.Tuple _
  | NPat.VariantApp _ ->
    let pats =
      match pat with
      | NPat.Ascribe (bodyPat, _, _) -> [ bodyPat ]
      | NPat.Cons (l, r, _) -> [ l; r ]
      | NPat.Tuple (itemPats, _) -> itemPats
      | NPat.VariantApp (l, r, _) -> [ l; r ]
      | _ -> unreachable ()

    pats |> List.fold (cdPat currentModule) ctx

  | NPat.Or _ // No need to recurse into OR pats because they don't bind any symbol for now.

  | NPat.Bad _
  | NPat.Discard _
  | NPat.Nav _
  | NPat.Lit _
  | NPat.Nil _ -> ctx

let private cdStmt currentModule ctx stmt : ScopeCtx =
  match stmt with
  | NStmt.Expr _ -> ctx

  | NStmt.LetVal (pat, _, _) -> cdPat currentModule ctx pat

  | NStmt.LetFun (_, vis, name, _, _, _) ->
    let funSerial, ctx = freshFunSerial ctx
    let funSymbol = FunSymbol funSerial

    // __trace (
    //   "cdStmtLetFun "
    //   + string (funSerialToInt funSerial)
    //   + ":"
    //   + identOf name
    // )

    let ctx =
      { ctx with
          DeclaredFuns =
            ctx.DeclaredFuns
            |> TMap.add (posOf name) funSerial }

    let ctx =
      ctx |> importValue (identOf name) funSymbol

    exportValue ctx currentModule vis (identOf name) funSymbol

let private cdAfterTyDecl (ctx: ScopeCtx) currentModule vis (name: NName) tySerial tySymbol arity : ScopeCtx =
  // __trace (
  //   "cdAfterTyDecl "
  //   + string tySerial
  //   + ":"
  //   + identOf name
  // )

  let ctx =
    { ctx with
        DeclaredTys =
          ctx.DeclaredTys
          |> TMap.add (posOf name) (tySerial, tySymbol)
        DeclaredTyArities = ctx.DeclaredTyArities |> TMap.add tySerial arity }

  let ctx = ctx |> importTy (identOf name) tySymbol
  exportTy ctx currentModule vis (identOf name) tySymbol

let private cdTySynonymDecl currentModule (ctx: ScopeCtx) decl : ScopeCtx =
  let vis, name, tyArgs =
    match decl with
    | NDecl.TySynonym (vis, name, tyArgs, _, _) -> vis, name, tyArgs
    | _ -> unreachable ()

  let tySerial, ctx = freshSerial ctx
  let tySymbol = SynonymTySymbol tySerial
  let arity = List.length tyArgs
  cdAfterTyDecl ctx currentModule vis name tySerial tySymbol arity

let private cdUnionTyDecl currentModule (ctx: ScopeCtx) decl : ScopeCtx =
  let vis, name, tyArgs, variants =
    match decl with
    | NDecl.Union (vis, name, tyArgs, variants, _) -> vis, name, tyArgs, variants
    | _ -> unreachable ()

  let tySerial, ctx = freshSerial ctx
  let tySymbol = UnionTySymbol tySerial
  let arity = List.length tyArgs

  let variants, ctx =
    variants
    |> List.mapFold
         (fun ctx variant ->
           let name, _, _ = variant
           let variantSerial, ctx = freshVariantSerial ctx
           let variantSymbol = VariantSymbol variantSerial

           //  __trace (
           //    "cdVariant "
           //    + string (variantSerialToInt variantSerial)
           //    + ":"
           //    + identOf name
           //  )

           let ctx =
             ctx
             |> addValueToNs (nsOwnerOfTy tySerial) (identOf name) variantSymbol
             |> importValue (identOf name) variantSymbol

           let ctx =
             exportValue ctx currentModule vis (identOf name) (VariantSymbol variantSerial)

           (variantSerial, posOf name), ctx)
         ctx

  let ctx =
    { ctx with
        DeclaredVariants =
          variants
          |> List.fold (fun map (variantSerial, pos) -> map |> TMap.add pos variantSerial) ctx.DeclaredVariants }

  cdAfterTyDecl ctx currentModule vis name tySerial tySymbol arity

let private cdRecordTyDecl currentModule ctx decl : ScopeCtx =
  let vis, name, tyArgs, loc =
    match decl with
    | NDecl.Record (vis, name, tyArgs, _, _, loc) -> vis, name, tyArgs, loc
    | _ -> unreachable ()

  let ctx =
    if tyArgs |> List.isEmpty |> not then
      addLog UnimplGenericTyError loc ctx
    else
      ctx

  let tySerial, ctx = freshSerial ctx
  let tySymbol = RecordTySymbol tySerial
  let arity = List.length tyArgs
  cdAfterTyDecl ctx currentModule vis name tySerial tySymbol arity

let private cdOpenDecl ctx path loc : ScopeCtx =
  let path = path |> List.map identOf
  let moduleSerials = ctx |> resolveModulePath path

  // __trace (
  //   "cdOpenDecl "
  //   + S.concat "." path
  //   + " -> "
  //   + (moduleSerials |> List.map string |> S.concat ", ")
  // )

  let ctx =
    if List.isEmpty moduleSerials then
      ctx |> addLog ModulePathNotFoundError loc
    else
      ctx |> openModules moduleSerials

  ctx

let private cdModuleSynonymDecl ctx name path : ScopeCtx =
  match identOf name, path with
  | "_", _
  | _, [] -> ctx

  | _ ->
    let moduleSerials =
      let path = path |> List.map identOf
      ctx |> resolveModulePath path

    if List.isEmpty moduleSerials then
      let _, loc = name
      ctx |> addLog ModulePathNotFoundError loc
    else
      // Import all modules that are referred by the path via the specified alias.
      moduleSerials
      |> List.fold (fun ctx moduleSerial -> importNsOwner (identOf name) (nsOwnerOfModule moduleSerial) ctx) ctx

let private cdModuleDecl currentModule ctx decl : ScopeCtx =
  let (NModuleDecl (_, vis, name, _, _)) = decl

  let moduleSerial, ctx = freshSerial ctx
  let moduleNs = nsOwnerOfModule moduleSerial

  // __trace (
  //   "cdModuleDecl "
  //   + string moduleSerial
  //   + ":"
  //   + identOf name
  // )

  let ctx =
    { ctx with
        DeclaredModules =
          ctx.DeclaredModules
          |> TMap.add (posOf name) moduleSerial }

  let ctx =
    ctx |> importNsOwner (identOf name) moduleNs

  exportModule ctx currentModule vis (identOf name) moduleNs

let private cdDecl (currentModule: NsOwner) (ctx: ScopeCtx) decl : ScopeCtx =
  match decl with
  | NDecl.Stmt stmt -> cdStmt currentModule ctx stmt

  | NDecl.TySynonym _ -> cdTySynonymDecl currentModule ctx decl
  | NDecl.Union _ -> cdUnionTyDecl currentModule ctx decl
  | NDecl.Record _ -> cdRecordTyDecl currentModule ctx decl

  | NDecl.Open (path, loc) -> cdOpenDecl ctx path loc
  | NDecl.ModuleSynonym (name, path, _) -> cdModuleSynonymDecl ctx name path
  | NDecl.Module decl -> cdModuleDecl currentModule ctx decl

let private collectDecls (currentModule: NsOwner) ctx (decls: NDecl list) : ScopeCtx =
  decls |> List.fold (cdDecl currentModule) ctx

// -----------------------------------------------
// Resolve definitions
// -----------------------------------------------

// Resolve definitions (rd) is a follow-up pass
// to resolve all types in these definitions
// and create a complete set of type definitions for TIR.

let private defineTyArgs (ctx: ScopeCtx) tyArgs =
  let tyArgToSerials, ctx =
    tyArgs
    |> List.mapFold
         (fun ctx tyArg ->
           let tySerial, ctx = freshSerial ctx
           (identOf tyArg, tySerial), ctx)
         ctx

  let tyArgSerials = tyArgToSerials |> List.map snd

  tyArgSerials, tyArgToSerials, ctx

let private rdTySynonymDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, bodyTy, loc =
    match decl with
    | NDecl.TySynonym (_, name, tyArgs, bodyTy, loc) -> name, tyArgs, bodyTy, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = ctx |> startScope TyDeclScope
  let tyArgSerials, tyArgToSerials, ctx = defineTyArgs ctx tyArgs

  let bodyTy, ctx =
    let tyArgs =
      tyArgToSerials
      |> List.map (fun (tyArg, univTySerial) -> tyArg, UnivTySymbol univTySerial)
      |> TMap.ofList compare

    resolveTy ctx bodyTy tyArgs

  let tyDef =
    SynonymTyDef(identOf name, tyArgSerials, bodyTy, loc)

  addTyDef tySerial tyDef ctx |> finishScope

let private rdUnionTyDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, variants, loc =
    match decl with
    | NDecl.Union (_, name, tyArgs, variants, loc) -> name, tyArgs, variants, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = ctx |> startScope TyDeclScope
  let tyArgSerials, tyArgToSerials, ctx = defineTyArgs ctx tyArgs

  let variants, ctx =
    let tyArgs =
      tyArgToSerials
      |> List.map (fun (tyArg, univTySerial) -> tyArg, UnivTySymbol univTySerial)
      |> TMap.ofList compare

    variants
    |> List.mapFold
         (fun (ctx: ScopeCtx) variant ->
           let name, payloadTyOpt, loc = variant

           let variantSerial =
             ctx.DeclaredVariants |> mapFind (posOf name)

           let payloadTyOpt, ctx =
             match payloadTyOpt with
             | Some payloadTy ->
               let payloadTy, ctx = resolveTy ctx payloadTy tyArgs
               Some payloadTy, ctx
             | None -> None, ctx

           (variantSerial, (name, payloadTyOpt, loc)), ctx)
         ctx

  let ctx =
    let newtype = List.length variants = 1

    { ctx with
        NewVariants =
          variants
          |> List.fold
               (fun variants (variantSerial, (name, payloadTyOpt, loc)) ->
                 let payloadTy =
                   payloadTyOpt |> Option.defaultValue tyUnit

                 let variantDef: VariantDef =
                   { Name = identOf name
                     UnionTySerial = tySerial
                     IsNewtype = newtype
                     HasPayload = Option.isSome payloadTyOpt
                     PayloadTy = payloadTy
                     Loc = loc }

                 (variantSerial, variantDef) :: variants)
               ctx.NewVariants }

  let tyDef =
    let variantSerials = variants |> List.map fst
    UnionTyDef(identOf name, tyArgSerials, variantSerials, loc)

  addTyDef tySerial tyDef ctx |> finishScope

let private rdRecordTyDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, fields, repr, loc =
    match decl with
    | NDecl.Record (_, name, tyArgs, fields, repr, loc) -> name, tyArgs, fields, repr, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = ctx |> startScope TyDeclScope
  let tyArgSerials, tyArgToSerials, ctx = defineTyArgs ctx tyArgs

  let fields, ctx =
    let tyArgs =
      tyArgToSerials
      |> List.map (fun (tyArg, univTySerial) -> tyArg, UnivTySymbol univTySerial)
      |> TMap.ofList compare

    fields
    |> List.mapFold
         (fun ctx field ->
           let name, fieldTy, loc = field
           let fieldTy, ctx = resolveTy ctx fieldTy tyArgs
           (identOf name, fieldTy, loc), ctx)
         ctx

  let tyDef =
    RecordTyDef(identOf name, tyArgSerials, fields, repr, loc)

  addTyDef tySerial tyDef ctx |> finishScope

let private rdDecl ctx decl =
  match decl with
  | NDecl.TySynonym _ -> rdTySynonymDecl ctx decl
  | NDecl.Union _ -> rdUnionTyDecl ctx decl
  | NDecl.Record _ -> rdRecordTyDecl ctx decl

  | NDecl.Stmt _
  | NDecl.Open _
  | NDecl.ModuleSynonym _
  | NDecl.Module _ -> ctx

let private resolveDefs (ctx: ScopeCtx) decls : ScopeCtx = decls |> List.fold rdDecl ctx

// -----------------------------------------------
// Ty
// -----------------------------------------------

let private nameResTyInAscription ctx ty : Ty * ScopeCtx =
  let tyArgs = TMap.empty compare
  resolveTy ctx ty tyArgs

// -----------------------------------------------
// Pattern
// -----------------------------------------------

let private doResolveVarInPat (ctx: ScopeCtx) name : VarSerial * ScopeCtx =
  let ident, loc = name

  match ctx.PatScope |> TMap.tryFind ident with
  | None ->
    let varSerial, ctx =
      match ctx.DeclaredVars |> TMap.tryFind (posOf name) with
      | Some it -> it, ctx
      | None -> freshVarSerial ctx

    let varDef: VarDef =
      { Name = ident
        IsStatic = NotStatic
        Ty = noTy
        Linkage = InternalLinkage
        Loc = loc }

    let ctx =
      { ctx with
          PatScope =
            ctx.PatScope
            |> TMap.add ident (varSerial, loc, []) }
      |> addVarDef varSerial varDef
      |> importValue ident (VarSymbol varSerial)

    varSerial, ctx

  // Duplicated var in a pattern.
  | Some (varSerial, defLoc, useLocs) ->
    let ctx =
      { ctx with
          PatScope =
            ctx.PatScope
            |> TMap.add ident (varSerial, defLoc, loc :: useLocs) }

    varSerial, ctx

let private nameResIdentPat ctx vis name : TPat * ScopeCtx =
  assert (identOf name <> "_")
  let _, loc = name

  match ctx |> resolveUnqualifiedValue (identOf name) with
  | Some (VariantSymbol variantSerial) -> TVariantPat(variantSerial, noTy, loc), ctx

  | _ ->
    let varSerial, ctx = doResolveVarInPat ctx name
    TVarPat(vis, varSerial, noTy, loc), ctx

let private nameResNavPat ctx pat : TPat * ScopeCtx =
  /// Resolves a pattern as scope.
  ///
  /// Returns (scopeOpt, pat).
  /// scopeOpt is `Some s` if pat is resolved to scope `s`.
  /// `pat` is also updated by resolving inner qualifiers as possible.
  let rec resolvePatAsNsOwners pat ctx : NsOwner list =
    match pat with
    | NPat.Ident (_, name) -> ctx |> resolveUnqualifiedNsOwner (identOf name)

    | NPat.Nav (l, r, _) ->
      ctx
      |> resolvePatAsNsOwners l
      |> List.collect (fun nsOwner -> ctx |> resolveQualifiedNsOwner nsOwner (identOf r))

    | _ -> []

  let l, r, loc =
    match pat with
    | NPat.Nav (l, r, loc) -> l, r, loc
    | _ -> unreachable ()

  let patOpt =
    resolvePatAsNsOwners l ctx
    |> List.tryPick (fun nsOwner ->
      match ctx |> resolveQualifiedValue nsOwner (identOf r) with
      | Some (VariantSymbol variantSerial) -> Some(TVariantPat(variantSerial, noTy, loc))
      | _ -> None)

  match patOpt with
  | Some pat -> pat, ctx
  | None -> errorPat ctx UnresolvedNavPatError loc

let private nameResAscribePat ctx bodyPat ascriptionTy loc : TPat * ScopeCtx =
  let ascriptionTy, ctx = nameResTyInAscription ctx ascriptionTy

  let bodyPat, ctx = bodyPat |> nameResPat ctx
  TNodePat(TAscribePN, [ bodyPat ], ascriptionTy, loc), ctx

let private nameResAsPat ctx bodyPat name loc : TPat * ScopeCtx =
  let bodyPat, ctx = bodyPat |> nameResPat ctx
  let varSerial, ctx = doResolveVarInPat ctx name
  TAsPat(bodyPat, varSerial, loc), ctx

let private nameResPat (ctx: ScopeCtx) (pat: NPat) : TPat * ScopeCtx =
  match pat with
  | NPat.Bad loc -> tpAbort noTy loc, ctx
  | NPat.Ident (vis, name) -> nameResIdentPat ctx vis name
  | NPat.Discard loc -> TDiscardPat(noTy, loc), ctx
  | NPat.Nav _ -> nameResNavPat ctx pat
  | NPat.As (bodyPat, name, loc) -> nameResAsPat ctx bodyPat name loc
  | NPat.Ascribe (bodyPat, ty, loc) -> nameResAscribePat ctx bodyPat ty loc

  | NPat.Or (_, _, loc) ->
    // No OR patterns appear in arm patterns due to normalization.
    // So we can assume that it's inside of irrefutable pattern.
    errorPat ctx IllegalOrPatError loc

  | NPat.Lit (lit, loc) -> TLitPat(lit, loc), ctx
  | NPat.Nil loc -> TNodePat(TNilPN, [], noTy, loc), ctx

  | NPat.Cons (l, r, loc) ->
    let l, ctx = l |> nameResPat ctx
    let r, ctx = r |> nameResPat ctx
    TNodePat(TConsPN, [ l; r ], noTy, loc), ctx

  | NPat.Tuple (itemPats, loc) ->
    let itemPats, ctx = itemPats |> List.mapFold nameResPat ctx
    TNodePat(TTuplePN, itemPats, noTy, loc), ctx

  | NPat.VariantApp (l, r, loc) ->
    let l, ctx = l |> nameResPat ctx
    let r, ctx = r |> nameResPat ctx

    match l with
    | TVariantPat (variantSerial, _, _) -> TNodePat(TVariantAppPN variantSerial, [ r ], noTy, loc), ctx
    | _ -> errorPat ctx VariantAppPatArityError loc

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

let private npNormalize (pat: NPat) : NPat list =
  /// Gets a pair of:
  ///
  /// - sub-patterns
  /// - a function to update sub-patterns
  ///
  /// That is, `decompose Pat(P) = (P, fun P' -> Pat(P'))`
  /// where P, P' are arguments of a particular pattern.
  let decompose pat =
    match pat with
    | NPat.Nav (l, r, loc) ->
      [ l ],
      (fun pats ->
        match pats with
        | [ l ] -> NPat.Nav(l, r, loc)
        | _ -> unreachable ())

    | NPat.Ascribe (bodyPat, ty, loc) ->
      [ bodyPat ],
      (fun pats ->
        match pats with
        | [ bodyPat ] -> NPat.Ascribe(bodyPat, ty, loc)
        | _ -> unreachable ())

    | NPat.Cons (l, r, loc) ->
      [ l; r ],
      (fun pats ->
        match pats with
        | [ l; r ] -> NPat.Cons(l, r, loc)
        | _ -> unreachable ())

    | NPat.Tuple (itemPats, loc) ->
      let arity = List.length itemPats

      itemPats,
      (fun itemPats ->
        assert (List.length itemPats = arity)
        NPat.Tuple(itemPats, loc))

    | NPat.VariantApp (l, r, loc) ->
      [ l; r ],
      (fun pats ->
        match pats with
        | [ l; r ] -> NPat.VariantApp(l, r, loc)
        | _ -> unreachable ())

    | NPat.Bad _
    | NPat.Ident _
    | NPat.Discard _
    | NPat.As _
    | NPat.Or _
    | NPat.Lit _
    | NPat.Nil _ -> unreachable () // Never used.

  // nf for normal form
  let rec nf pat : NPat list =
    match pat with
    // e.g. `(p | q) | (r | s) -> [ p; q; r; s ]`
    | NPat.Or (l, r, _) -> List.append (nf l) (nf r)

    // e.g. `P(p | q, r | s) -> [ P(p, r); P(p, s); P(q, r); P(q, s) ]`
    | NPat.Nav _
    | NPat.Ascribe _
    | NPat.Cons _
    | NPat.Tuple _
    | NPat.VariantApp _ ->
      // acc: suffix of sub-patterns
      // pats: prefix of sub-patterns in reversed order
      //
      // Let pat be `P(p | q, r | s)`.
      // `bruteForce [] [ r | s; p | q ]`
      // -> `[ ...bruteForce [ r] [ p | q ]; ...bruteForce [ s ] [ p | q ] ]`
      // -> `[ ...bruteForce [ p; r ] []; ...bruteForce [ q; r ]; ...snip; ...snip ]`
      // -> `[ p, r; p, s; q, r; q, s ]`.
      let rec bruteForce acc pats : NPat list list =
        match pats with
        | [] -> [ acc ]
        | p :: pats ->
          nf p
          |> List.collect (fun p -> bruteForce (p :: acc) pats)

      let pats, create = decompose pat

      bruteForce [] (List.rev pats) |> List.map create

    | NPat.Bad _
    | NPat.Ident _
    | NPat.Discard _

    // No need to normalize body of `as` pattern.
    // Since OR patterns don't bind for now,
    // the body doesn't contain OR pattern and therefore normal form is [ pat ].
    | NPat.As _

    | NPat.Lit _
    | NPat.Nil _ -> [ pat ]

  nf pat

let private nameResRefutablePat (ctx: ScopeCtx) (pat: NPat) : TPat * ScopeCtx =
  let loc = npLoc pat

  let pat, pats =
    match npNormalize pat with
    | pat :: pats -> pat, pats
    | [] -> unreachable ()

  let (lScope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat ctx pat)

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
        |> doWithPatScope (Some lScope) (fun ctx -> nameResPat ctx pat)

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

let private nameResIrrefutablePat (ctx: ScopeCtx) (pat: NPat) : TPat * ScopeCtx =
  let (scope, pat), ctx =
    ctx
    |> doWithPatScope None (fun ctx -> nameResPat ctx pat)

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
let private doNameResVarExpr ctx name loc : TExpr option =
  match ctx |> resolveUnqualifiedValue name with
  | Some symbol ->
    let expr =
      match symbol with
      | VarSymbol serial -> TVarExpr(serial, noTy, loc)
      | FunSymbol serial -> TFunExpr(serial, noTy, loc)
      | VariantSymbol serial -> TVariantExpr(serial, noTy, loc)

    Some expr

  | None ->
    match primFromIdent name with
    | Some prim -> TPrimExpr(prim, noTy, loc) |> Some
    | None -> None

let private nameResUnqualifiedIdentExpr ctx name loc : TExpr * ScopeCtx =
  match doNameResVarExpr ctx name loc with
  | Some expr -> expr, ctx
  | None -> errorExpr ctx (UndefinedValueError name) loc

let private nameResNavExpr (ctx: ScopeCtx) (expr: NExpr) : TExpr * ScopeCtx =
  /// Resolves an expressions as scope.
  ///
  /// Returns (scopeOpt, exprOpt).
  /// scopeOpt should eb some it can be resolved to scope.
  /// exprOpt is also obtained by resolving inner `nav`s as possible.
  let rec resolveExprAsNsOwners ctx expr : ResolvedExpr * ScopeCtx =
    match expr with
    | NExpr.Ident (ident, loc) ->
      let nsOwners = ctx |> resolveUnqualifiedNsOwner ident
      let exprOpt = doNameResVarExpr ctx ident loc

      match nsOwners, exprOpt with
      | [], None -> NotResolvedExpr(ident, loc), ctx
      | [], Some expr -> ResolvedAsExpr expr, ctx
      | _ -> ResolvedAsScope(nsOwners, exprOpt, loc), ctx

    | NExpr.Nav (l, rName, dotLoc) ->
      let l, ctx = resolveExprAsNsOwners ctx l
      let r, identLoc = rName

      match l with
      | NotResolvedExpr _ -> l, ctx

      | ResolvedAsExpr l -> ResolvedAsExpr(TNavExpr(l, rName, noTy, dotLoc)), ctx

      | ResolvedAsScope (superNsOwners, lExprOpt, _) ->
        assert (List.isEmpty superNsOwners |> not)

        // Resolve as namespaces.
        let nsOwners =
          superNsOwners
          |> List.collect (fun nsOwner -> ctx |> resolveQualifiedNsOwner nsOwner r)

        // Resolve as value.
        let exprOpt =
          let varSymbolOpt =
            superNsOwners
            |> List.tryPick (fun nsOwner ->
              match ctx |> resolveQualifiedValue nsOwner r with
              | None -> None
              | it -> it)

          match varSymbolOpt with
          | Some (VarSymbol varSerial) -> TVarExpr(varSerial, noTy, identLoc) |> Some
          | Some (FunSymbol funSerial) -> TFunExpr(funSerial, noTy, identLoc) |> Some
          | Some (VariantSymbol variantSerial) ->
            TVariantExpr(variantSerial, noTy, identLoc)
            |> Some
          | None -> None

        // If not resolved as value, keep try to unresolved.
        let exprOpt =
          match exprOpt, lExprOpt with
          | Some _, _ -> exprOpt
          | None, Some l -> TNavExpr(l, rName, noTy, dotLoc) |> Some
          | None, None -> None

        match nsOwners, exprOpt with
        | [], None -> NotResolvedExpr(r, dotLoc), ctx
        | [], Some expr -> ResolvedAsExpr expr, ctx
        | _ -> ResolvedAsScope(nsOwners, exprOpt, identLoc), ctx

    | _ ->
      // l is clearly unresolvable as type, e.g. `(getStr ()).Length`.
      let expr, ctx = expr |> nameResExpr ctx
      ResolvedAsExpr expr, ctx

  let result, ctx = resolveExprAsNsOwners ctx expr

  match result with
  | ResolvedAsExpr expr -> expr, ctx
  | ResolvedAsScope (_, Some expr, _) -> expr, ctx
  | ResolvedAsScope (_, None, loc) -> errorExpr ctx TyUsedAsValueError loc
  | NotResolvedExpr (name, loc) -> errorExpr ctx (UndefinedValueError name) loc

let private nameResExpr (ctx: ScopeCtx) (expr: NExpr) : TExpr * ScopeCtx =
  match expr with
  | NExpr.Bad loc -> txAbort loc, ctx
  | NExpr.Lit (lit, loc) -> TLitExpr(lit, loc), ctx

  | NExpr.Ident (name, loc) -> nameResUnqualifiedIdentExpr ctx name loc
  | NExpr.Nav _ -> nameResNavExpr ctx expr

  | NExpr.Ascribe (body, ty, loc) ->
    // Resolve ascription first so that type variables are defined in current scope.
    let ty, ctx = nameResTyInAscription ctx ty

    let body, ctx = body |> nameResExpr ctx
    TNodeExpr(TAscribeEN, [ body ], ty, loc), ctx

  | NExpr.TyPlaceholder (ty, loc) ->
    let ty, ctx = nameResTyInAscription ctx ty
    TNodeExpr(TTyPlaceholderEN, [], ty, loc), ctx

  | NExpr.Block (stmts, last) ->
    let ctx = ctx |> startScope ExprScope
    let stmts, ctx = stmts |> List.mapFold nameResStmt ctx
    let last, ctx = last |> nameResExpr ctx
    let ctx = ctx |> finishScope
    TBlockExpr(stmts, last), ctx

  | NExpr.Match (cond, arms, loc) ->
    let cond, ctx = cond |> nameResExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guardOpt, body, loc) ->
             let ctx = ctx |> startScope ExprScope
             let pat, ctx = pat |> nameResRefutablePat ctx

             // Default to `true` if guard is missing.
             let guard, ctx =
               match guardOpt with
               | Some guard -> guard |> nameResExpr ctx
               | None -> txTrue loc, ctx

             let body, ctx = body |> nameResExpr ctx
             let ctx = ctx |> finishScope
             (pat, guard, body), ctx)
           ctx

    TMatchExpr(cond, arms, noTy, loc), ctx

  | NExpr.Nil loc -> TPrimExpr(TPrim.Nil, noTy, loc), ctx

  | NExpr.Record (baseOpt, fields, loc) ->
    let baseOpt, ctx =
      baseOpt |> optionMapFold nameResExpr ctx

    let fields, ctx =
      fields
      |> List.mapFold
           (fun ctx ((name, _), init, loc) ->
             let init, ctx = init |> nameResExpr ctx
             (name, init, loc), ctx)
           ctx

    TRecordExpr(baseOpt, fields, noTy, loc), ctx

  | NExpr.Tuple (items, loc) ->
    let items, ctx = items |> List.mapFold nameResExpr ctx
    TNodeExpr(TTupleEN, items, noTy, loc), ctx

  | NExpr.Unary (MinusUnary, arg, loc) ->
    let arg, ctx = arg |> nameResExpr ctx
    TNodeExpr(TMinusEN, [ arg ], noTy, loc), ctx

  | NExpr.Binary (AppBinary, l, r, loc) ->
    let l, ctx = l |> nameResExpr ctx
    let r, ctx = r |> nameResExpr ctx
    txApp l r loc, ctx

  | NExpr.Binary (op, l, r, loc) ->
    let primExpr = TPrimExpr(binaryToPrim op, noTy, loc)
    let l, ctx = l |> nameResExpr ctx
    let r, ctx = r |> nameResExpr ctx
    txApp2 primExpr l r loc, ctx

  | NExpr.Index (l, r, loc) ->
    let l, ctx = l |> nameResExpr ctx
    let r, ctx = r |> nameResExpr ctx
    TNodeExpr(TIndexEN, [ l; r ], noTy, loc), ctx

  | NExpr.Slice (x, l, r, loc) ->
    let x, ctx = x |> nameResExpr ctx
    let l, ctx = l |> nameResExpr ctx
    let r, ctx = r |> nameResExpr ctx
    TNodeExpr(TSliceEN, [ l; r; x ], noTy, loc), ctx

let private nameResStmt ctx (stmt: NStmt) : TStmt * ScopeCtx =
  match stmt with
  | NStmt.Expr expr ->
    let expr, ctx = expr |> nameResExpr ctx
    TExprStmt expr, ctx

  | NStmt.LetVal (pat, body, loc) ->
    let ctx = ctx |> startScope ExprScope
    let body, ctx = body |> nameResExpr ctx
    let ctx = ctx |> finishScope

    let pat, ctx = pat |> nameResIrrefutablePat ctx
    TLetValStmt(pat, body, loc), ctx

  | NStmt.LetFun (IsRec, vis, name, argPats, body, loc) ->
    // #defineFun
    let defineFun (ctx: ScopeCtx) vis name arity loc : FunSerial * ScopeCtx =
      let hoisted, vis, (funSerial, ctx) =
        match ctx.DeclaredFuns |> TMap.tryFind (posOf name) with
        | Some funSerial -> true, vis, (funSerial, ctx)
        | None -> false, PrivateVis, freshFunSerial ctx

      let funName = identOf name

      let funDef: FunDef =
        { Name = funName
          Arity = arity
          Ty = TyScheme([], noTy)
          Abi = MiloneAbi
          Linkage = makeLinkage vis funName ctx
          Prefix = ctx.AncestralFuns
          Loc = loc }

      let ctx = addFunDef funSerial funDef ctx

      let ctx =
        if not hoisted then
          ctx |> importValue funName (FunSymbol funSerial)
        else
          ctx

      funSerial, ctx

    // Define the function itself for recursive referencing.
    let funSerial, ctx =
      let arity = List.length argPats
      defineFun ctx vis name arity loc

    let funName = identOf name

    // __trace ("enterLetFun " + funName)

    let argPats, body, ctx =
      let ctx =
        ctx
        |> enterLetInit funName
        |> startScope ExprScope

      let argPats, ctx =
        argPats |> List.mapFold nameResIrrefutablePat ctx

      let body, ctx = body |> nameResExpr ctx
      let ctx = ctx |> finishScope |> leaveLetInit

      argPats, body, ctx

    // __trace ("leaveLetFun " + funName)

    TLetFunStmt(funSerial, IsRec, vis, argPats, body, loc), ctx

  | NStmt.LetFun (NotRec, vis, name, argPats, body, loc) ->
    let arity = List.length argPats

    // #defineFun
    let hoisted, vis, (funSerial, ctx) =
      match ctx.DeclaredFuns |> TMap.tryFind (posOf name) with
      | Some funSerial -> true, vis, (funSerial, ctx)
      | None -> false, PrivateVis, freshFunSerial ctx

    let funName = identOf name

    let funDef: FunDef =
      { Name = funName
        Arity = arity
        Ty = TyScheme([], noTy)
        Abi = MiloneAbi
        Linkage = makeLinkage vis funName ctx
        Prefix = ctx.AncestralFuns
        Loc = loc }

    let ctx = addFunDef funSerial funDef ctx

    // __trace ("enterLetFun " + funName)

    let argPats, body, ctx =
      let ctx =
        ctx
        |> enterLetInit funName
        |> startScope ExprScope

      let argPats, ctx =
        argPats |> List.mapFold nameResIrrefutablePat ctx

      let body, ctx = body |> nameResExpr ctx
      let ctx = ctx |> finishScope |> leaveLetInit

      argPats, body, ctx

    let ctx =
      if not hoisted then
        ctx |> importValue funName (FunSymbol funSerial)
      else
        ctx

    // __trace ("leaveLetFun " + funName)

    TLetFunStmt(funSerial, NotRec, vis, argPats, body, loc), ctx

let private nameResModuleDecl (ctx: ScopeCtx) moduleDecl : TStmt * ScopeCtx =
  let (NModuleDecl (_, _, name, decls, _)) = moduleDecl

  let moduleSerial =
    ctx.DeclaredModules |> mapFind (posOf name)

  let parent, ctx =
    ctx
    |> startScope ExprScope
    |> enterModule (identOf name)

  let ctx =
    // Open the parent module (and modules with the same path).
    let parentPath = parent

    resolveModulePath parentPath ctx
    |> List.fold (fun ctx moduleTySerial -> openModule moduleTySerial ctx) ctx

  let stmts, ctx =
    nameResDecls (nsOwnerOfModule moduleSerial) ctx decls

  let ctx = ctx |> leaveModule parent |> finishScope

  TBlockStmt(IsRec, stmts), ctx

let private nameResDecl ctx (decl: NDecl) : TStmt option * ScopeCtx =
  let some (value, ctx) = Some value, ctx

  match decl with
  | NDecl.Stmt stmt -> nameResStmt ctx stmt |> some
  | NDecl.Module decl -> nameResModuleDecl ctx decl |> some

  // Type declarations are only used in collectDecls and resolveDecls.
  | NDecl.TySynonym _
  | NDecl.Union _
  | NDecl.Record _

  // Open and module synonym statements are used in collectDecls and no longer necessary.
  | NDecl.Open _
  | NDecl.ModuleSynonym _ -> None, ctx

let private nameResDecls (currentModule: NsOwner) ctx decls : TStmt list * ScopeCtx =
  let ctx = collectDecls currentModule ctx decls

  // Perform name resolution for statements and inner modules.
  let stmts, ctx = decls |> listChooseFold nameResDecl ctx

  let ctx = resolveDefs ctx decls
  stmts, ctx

let private nameResModuleRoot ctx (root: NModuleRoot) : _ * TModule * ScopeCtx =
  let docId, moduleDecl = root
  let (NModuleDecl (_, _, name, _, _)) = moduleDecl
  let moduleSerial, ctx = freshSerial ctx
  let newRootModule = identOf name, moduleSerial

  // __trace (
  //   "nameResModuleRoot "
  //   + string moduleSerial
  //   + ":"
  //   + identOf name
  // )

  let ctx =
    { ctx with
        RootModules = newRootModule :: ctx.RootModules

        DeclaredModules =
          ctx.DeclaredModules
          |> TMap.add (posOf name) moduleSerial }

  let stmt, ctx = nameResModuleDecl ctx moduleDecl

  let m: TModule =
    { DocId = docId
      Vars = emptyVars // Filled later.
      Stmts = [ stmt ] }

  newRootModule, m, ctx

// -----------------------------------------------
// Interface
// -----------------------------------------------

let nameRes (layers: NModuleRoot list list) : TProgram * NameResResult =
  // note: NameRes should work per layer in parallel
  //       but it doesn't so due to sequential serial generation for now.

  let modules, state =
    layers
    |> listCollectFold
         (fun (state: NameResState) modules ->
           modules
           |> List.mapFold
                (fun (state: NameResState) moduleRoot ->
                  let newModule, m, ctx =
                    nameResModuleRoot state.ScopeCtx moduleRoot

                  let state, localVars = sMerge newModule state ctx
                  { m with Vars = localVars }, state)
                state)
         (emptyState ())

  let mainFunOpt =
    state.Funs
    |> TMap.fold
         (fun acc funSerial (funDef: FunDef) ->
           if funDef.Name = "main" then
             funSerial :: acc
           else
             acc)
         []
    |> List.tryLast

  modules, sToResult mainFunOpt state
