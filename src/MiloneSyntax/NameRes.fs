/// # Name Resolution
///
/// Name resolution is a pass to associate names with definitions.
/// See also name-resolution.md in docs.
module rec MiloneSyntax.NameRes

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
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
// Primitives
// -----------------------------------------------

let private valuePrimOfIdent ident =
  match ident with
  | "not" -> TPrim.Not |> Some
  | "exit" -> TPrim.Exit |> Some
  | "assert" -> TPrim.Assert |> Some
  | "box" -> TPrim.Box |> Some
  | "unbox" -> TPrim.Unbox |> Some
  | "printfn" -> TPrim.Printfn |> Some
  | "compare" -> TPrim.Compare |> Some

  | "int"
  | "int32" -> TPrim.ToInt I32 |> Some
  | "uint"
  | "uint32" -> TPrim.ToInt U32 |> Some
  | "sbyte"
  | "int8" -> TPrim.ToInt I8 |> Some
  | "byte"
  | "uint8" -> TPrim.ToInt U8 |> Some

  | "int16" -> TPrim.ToInt I16 |> Some
  | "int64" -> TPrim.ToInt I64 |> Some
  | "nativeint" -> TPrim.ToInt IPtr |> Some
  | "uint16" -> TPrim.ToInt U16 |> Some
  | "uint64" -> TPrim.ToInt U64 |> Some
  | "unativeint" -> TPrim.ToInt UPtr |> Some
  | "float" -> TPrim.ToFloat F64 |> Some
  | "float32" -> TPrim.ToFloat F32 |> Some
  | "char" -> TPrim.Char |> Some
  | "string" -> TPrim.String |> Some

  | "__discriminant" -> TPrim.Discriminant |> Some

  | "__nativeFun" -> TPrim.NativeFun |> Some
  | "__nativeCast" -> TPrim.NativeCast |> Some
  | "__nativeExpr" -> TPrim.NativeExpr |> Some
  | "__nativeStmt" -> TPrim.NativeStmt |> Some
  | "__nativeDecl" -> TPrim.NativeDecl |> Some

  | _ -> None

let private tyPrimOfIdent ident tys =
  match ident, tys with
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
  | "string", [] -> Some tyString
  | "obj", [] -> Some tyObj

  | "list", [ itemTy ] -> Some(tyList itemTy)

  | "voidptr", [] -> Ty(VoidPtrTk IsMut, []) |> Some
  | "nativeptr", [ itemTy ] -> tyNativePtr itemTy |> Some

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

[<NoEquality; NoComparison>]
type private ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial
  | PrimSymbol of TPrim

[<NoEquality; NoComparison>]
type private TySymbol =
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial
  | PrimTySymbol of Tk

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

let private nsOwnerOfTySymbol (tySymbol: TySymbol) : NsOwner option =
  match tySymbol with
  | UnionTySymbol s -> Some(nsOwnerOfTy s)

  | UnivTySymbol _
  | SynonymTySymbol _
  | RecordTySymbol _
  | PrimTySymbol _ -> None

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
    StaticVars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Logs: (NameResLog * Loc) list }

let private emptyState () : NameResState =
  { ScopeCtx = emptyScopeCtx ()
    StaticVars = emptyVars
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
         (state.StaticVars, emptyVars)

  // Other fields are intermediate state.
  { state with
      ScopeCtx =
        { state.ScopeCtx with
            Serial = ctx.Serial
            Tys = mapAddEntries ctx.NewTys s.Tys
            RootModules = newRootModule :: s.RootModules

            // These seem inefficient but not.
            Local = scopeMerge ctx.Local s.Local
            ValueNs = mapMerge s.ValueNs ctx.ValueNs
            TyNs = mapMerge s.TyNs ctx.TyNs
            NsNs = mapMerge s.NsNs ctx.NsNs }

      StaticVars = globalVars
      Funs = mapAddEntries ctx.NewFuns state.Funs
      Variants = mapAddEntries ctx.NewVariants state.Variants
      Logs = List.append ctx.NewLogs state.Logs },
  localVars

let private sToResult mainFunOpt (state: NameResState) : NameResResult =
  let ctx = state.ScopeCtx

  { Serial = ctx.Serial
    StaticVars = state.StaticVars
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
    StaticVars: TreeMap<VarSerial, VarDef>
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

    ValueNs: Ns<ValueSymbol>
    TyNs: Ns<TySymbol>
    /// Subspaces.
    NsNs: Ns<NsOwner list>

    /// Current scope.
    Local: Scope

    /// Variables defined in current pattern.
    ///
    /// ident -> (varSerial, definedLoc, usedLoc list)
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
    ValueNs = TMap.empty nsOwnerCompare
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

let private addLog (ctx: ScopeCtx) (log: NameResLog) (loc: Loc) =
  { ctx with NewLogs = (log, loc) :: ctx.NewLogs }

let private errorTy ctx log loc : Ty * ScopeCtx =
  let ctx = addLog ctx log loc
  tyError loc, ctx

let private errorPat ctx log loc : TPat * ScopeCtx =
  let ctx = addLog ctx log loc
  tpAbort noTy loc, ctx

let private errorExpr ctx log loc : TExpr * ScopeCtx =
  let ctx = addLog ctx log loc
  txAbort loc, ctx

let private makeLinkage (ctx: ScopeCtx) vis ident =
  match vis with
  | PublicVis -> ExternalLinkage(S.concat "_" ctx.CurrentPath + "_" + ident)
  | PrivateVis -> InternalLinkage

/// Adds a definition of var (not regarding static or not).
///
/// This doesn't imply it's added to any scope or namespace.
let private addVarDef (ctx: ScopeCtx) varSerial (varDef: VarDef) : ScopeCtx =
  { ctx with NewVars = (varSerial, varDef) :: ctx.NewVars }

let private addFunDef (ctx: ScopeCtx) funSerial funDef : ScopeCtx =
  { ctx with NewFuns = (funSerial, funDef) :: ctx.NewFuns }

let private addVariantDef (ctx: ScopeCtx) variantSerial variantDef : ScopeCtx =
  { ctx with NewVariants = (variantSerial, variantDef) :: ctx.NewVariants }

/// Adds a definition of type symbol.
let private addTyDef (ctx: ScopeCtx) tySerial tyDef : ScopeCtx =
  { ctx with
      Tys = ctx.Tys |> TMap.add tySerial tyDef
      NewTys = (tySerial, tyDef) :: ctx.NewTys }

/// Makes a value symbol accessible from a namespace.
let private addValueToNs (ctx: ScopeCtx) (nsOwner: NsOwner) alias valueSymbol : ScopeCtx =
  // __trace (
  //   "addVarToNs "
  //   + nsOwnerDump nsOwner
  //   + "."
  //   + alias
  //   + " = "
  //   + string (valueSymbolToSerial valueSymbol)
  // )

  { ctx with ValueNs = ctx.ValueNs |> nsAdd nsOwner alias valueSymbol }

/// Makes a type symbol accessible from a namespace.
let private addTyToNs (ctx: ScopeCtx) (nsOwner: NsOwner) alias tySymbol : ScopeCtx =
  // __trace (
  //   "addTyToNs "
  //   + nsOwnerDump nsOwner
  //   + "."
  //   + alias
  //   + " = "
  //   + string (tySymbolToSerial tySymbol)
  // )

  { ctx with
      TyNs = ctx.TyNs |> nsAdd nsOwner alias tySymbol

      NsNs =
        match nsOwnerOfTySymbol tySymbol with
        | Some ns -> ctx.NsNs |> nsMerge nsOwner alias ns
        | None -> ctx.NsNs }

/// Makes a child namespace accessible from a namespace.
///
/// `<parent>.<alias>` can be resolved to `<child>`.
let private addNsToNs (ctx: ScopeCtx) (parentNsOwner: NsOwner) alias (childNsOwner: NsOwner) : ScopeCtx =
  // __trace (
  //   "addNsToNs "
  //   + nsOwnerDump parentNsOwner
  //   + "."
  //   + alias
  //   + " = "
  //   + nsOwnerDump childNsOwner
  // )

  { ctx with
      NsNs =
        ctx.NsNs
        |> nsMerge parentNsOwner alias childNsOwner }

/// Adds a value symbol to current scope.
let private importValue (ctx: ScopeCtx) alias (symbol: ValueSymbol) : ScopeCtx =
  assert (alias <> "_")

  let scope: Scope =
    match ctx.Local with
    | kinds, map :: valueScopes, tyScopes, nsScopes ->
      let valueScopes =
        (map |> TMap.add alias symbol) :: valueScopes

      kinds, valueScopes, tyScopes, nsScopes

    | _ -> unreachable () // Scope can't be empty..

  { ctx with Local = scope }

/// Adds a type symbol to current scope.
let private importTy (ctx: ScopeCtx) alias (symbol: TySymbol) : ScopeCtx =
  let scope: Scope =
    match ctx.Local with
    | kinds, valueScopes, (tyMap :: tyScopes), (nsMap :: nsScopes) ->
      let tyMap = tyMap |> TMap.add alias symbol

      let nsMap =
        match nsOwnerOfTySymbol symbol with
        | Some ns -> nsMap |> Multimap.add alias ns
        | None -> nsMap

      kinds, valueScopes, tyMap :: tyScopes, nsMap :: nsScopes

    | _ -> unreachable () // Scope can't be empty.

  { ctx with Local = scope }

/// Adds an NsOwner to current scope.
let private importNsOwner (ctx: ScopeCtx) alias nsOwner : ScopeCtx =
  let scope: Scope =
    match ctx.Local with
    | kinds, valueScopes, tyScopes, ((map :: nsScopes) as allNsScopes) ->
      let shadowed =
        allNsScopes
        |> List.tryPick (fun map -> map |> TMap.tryFind alias)
        |> Option.defaultValue []

      let map =
        map |> TMap.add alias (nsOwner :: shadowed)

      kinds, valueScopes, tyScopes, map :: nsScopes

    | _ -> unreachable () // Scope can't be empty.

  { ctx with Local = scope }

/// Imports all members of the module to current scope.
let private openModule (ctx: ScopeCtx) moduleSerial =
  // Import vars.
  let ctx =
    ctx.ValueNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold importValue ctx

  // Import tys.
  let ctx =
    ctx.TyNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold importTy ctx

  // Import subnamespaces.
  let ctx =
    ctx.NsNs
    |> nsFind (nsOwnerOfModule moduleSerial)
    |> TMap.fold
         (fun ctx alias nsOwners ->
           nsOwners
           |> List.fold (fun ctx nsOwner -> importNsOwner ctx alias nsOwner) ctx)
         ctx

  ctx

let private openModules ctx moduleSerials =
  moduleSerials |> List.fold openModule ctx

/// Called on enter the init of let-fun expressions.
let private enterLetInit (ctx: ScopeCtx) funName : ScopeCtx =
  { ctx with AncestralFuns = funName :: ctx.AncestralFuns }

let private leaveLetInit (ctx: ScopeCtx) : ScopeCtx =
  { ctx with AncestralFuns = listSkip 1 ctx.AncestralFuns }

let private isTyDeclScope (ctx: ScopeCtx) =
  match ctx.Local with
  | TyDeclScope :: _, _, _, _ -> true
  | _ -> false

/// Starts a new scope.
let private startScope (ctx: ScopeCtx) kind : ScopeCtx =
  let kinds, valueScopes, tyScopes, nsScopes = ctx.Local

  { ctx with
      Local = kind :: kinds, scopeMapEmpty () :: valueScopes, scopeMapEmpty () :: tyScopes, scopeMapEmpty () :: nsScopes }

let private finishScope (ctx: ScopeCtx) : ScopeCtx =
  match ctx.Local with
  | [], _, _, _
  | _, [], _, _
  | _, _, [], _
  | _, _, _, [] -> unreachable () // Scope can't be empty..

  | _ :: kinds, _ :: valueScopes, _ :: tyScopes, _ :: nsScopes ->
    { ctx with Local = kinds, valueScopes, tyScopes, nsScopes }

let private enterModule (ctx: ScopeCtx) (moduleName: Ident) =
  let parent = ctx.CurrentPath

  let ctx =
    { ctx with CurrentPath = List.append ctx.CurrentPath [ moduleName ] }

  parent, ctx

let private leaveModule (ctx: ScopeCtx) parent =
  let currentPath = parent
  { ctx with CurrentPath = currentPath }

// -----------------------------------------------
// Resolve
// -----------------------------------------------

/// Resolves a module path to all modules
/// that can be accessible by the path.
///
/// Remarks: Multiple module with same name can exist at a path.
let private resolveModulePath (ctx: ScopeCtx) (path: Ident list) : ModuleTySerial list =
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

      | ident :: tail ->
        resolveQualifiedNsOwner ctx (nsOwnerOfModule serial) ident
        |> List.collect (fun nsOwner ->
          match nsOwnerAsModule nsOwner with
          | Some serial -> go serial tail
          | None -> [])

    roots
    |> List.collect (fun serial -> go serial tail)

/// Resolves an ident qualified by the specified namespace to a value symbol.
let private resolveQualifiedValue (ctx: ScopeCtx) nsOwner ident : ValueSymbol option =
  ctx.ValueNs
  |> nsFind nsOwner
  |> TMap.tryFind ident

/// Resolves an ident qualified by the specified namespace to a type symbol.
let private resolveQualifiedTy (ctx: ScopeCtx) nsOwner ident : TySymbol option =
  ctx.TyNs |> nsFind nsOwner |> TMap.tryFind ident

/// Resolves a qualified NsOwner to all candidates.
let private resolveQualifiedNsOwner (ctx: ScopeCtx) nsOwner ident : NsOwner list =
  ctx.NsNs |> nsFind nsOwner |> Multimap.find ident

/// Resolves an unqualified ident to a value symbol from current scope.
let private resolveUnqualifiedValue (ctx: ScopeCtx) ident =
  let _, valueScopes, _, _ = ctx.Local

  valueScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind ident)

/// Resolves an unqualified ident to a type symbol from current scope.
let private resolveUnqualifiedTy (ctx: ScopeCtx) ident : TySymbol option =
  let _, _, tyScopes, _ = ctx.Local

  tyScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind ident)

/// Resolves an unqualified NsOwner to all candidates.
let private resolveUnqualifiedNsOwner (ctx: ScopeCtx) ident : NsOwner list =
  let _, _, _, nsScopes = ctx.Local

  nsScopes
  |> List.tryPick (fun map -> map |> TMap.tryFind ident)
  |> Option.defaultValue []

/// Resolves qualifiers of type.
let private resolveNavTy ctx quals last : TySymbol option * ScopeCtx =
  match quals with
  | [] -> resolveUnqualifiedTy ctx last, ctx

  | head :: tail ->
    // Resolve head.
    let nsOwners = resolveUnqualifiedNsOwner ctx head

    // Resolve tail.
    let rec resolveTyPath ctx (nsOwner: NsOwner) path =
      match path with
      | [] -> [ nsOwner ]

      | ident :: path ->
        resolveQualifiedNsOwner ctx nsOwner ident
        |> List.collect (fun subNsOwner -> resolveTyPath ctx subNsOwner path)

    let tySymbolOpt =
      nsOwners
      |> List.collect (fun nsOwner -> resolveTyPath ctx nsOwner tail)
      |> List.tryPick (fun nsOwner -> resolveQualifiedTy ctx nsOwner last)

    tySymbolOpt, ctx

/// Resolves type names in a type expression.
///
/// selfTyArgs: Type parameters defined by current type declaration.
let private resolveTy ctx ty selfTyArgs : Ty * ScopeCtx =
  let rec go ctx ty : Ty * ScopeCtx =
    match ty with
    | NTy.Bad loc -> tyError loc, ctx

    | NTy.Var (ident, loc) ->
      let resolved =
        match selfTyArgs |> TMap.tryFind ident with
        | (Some _) as some -> some
        | None -> resolveUnqualifiedTy ctx ident

      match resolved with
      | Some (UnivTySymbol tySerial) -> tyUniv tySerial ident loc, ctx

      | _ when isTyDeclScope ctx -> errorTy ctx (UndefinedTyError ident) loc

      | _ ->
        // Define new type variable on the fly.
        let tySerial, ctx = freshSerial ctx

        // __trace ("typeVar " + string tySerial + ":" + ident)

        let ctx =
          let ctx =
            addTyDef ctx tySerial (UnivTyDef(ident, loc))

          importTy ctx ident (UnivTySymbol tySerial)

        tyUniv tySerial ident loc, ctx

    // `__nativeType<T>`
    | NTy.App ([], ("__nativeType", _), [ NTy.App ([], (code, _), [], _) ], _) -> Ty(NativeTypeTk code, []), ctx

    | NTy.App (quals, name, tyArgs, loc) ->
      let ident = identOf name
      let arity = List.length tyArgs
      let tyArgs, ctx = tyArgs |> List.mapFold go ctx

      let symbolOpt, ctx =
        let quals = quals |> List.map identOf
        resolveNavTy ctx quals ident

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
          errorTy ctx (TyArityError(ident, arity, defArity)) loc
        else
          tySynonym tySerial tyArgs, ctx

      | Some (UnionTySymbol tySerial) ->
        // #ty_arity_check
        let defArity = getArity tySerial

        if defArity <> arity then
          errorTy ctx (TyArityError(ident, arity, defArity)) loc
        else
          tyUnion tySerial tyArgs loc, ctx

      | Some (RecordTySymbol tySerial) ->
        // #ty_arity_check
        let defArity = 0 // generic record type is unimplemented

        if arity <> defArity then
          errorTy ctx (TyArityError(ident, arity, defArity)) loc
        else
          tyRecord tySerial loc, ctx

      | Some (PrimTySymbol tk) ->
        match tk with
        | OwnTk
        | VoidPtrTk _
        | NativePtrTk _ ->
          // #ty_arity_check
          let defArity =
            match tk with
            | VoidPtrTk _ -> 0
            | _ -> 1

          if arity <> defArity then
            errorTy ctx (TyArityError(ident, arity, defArity)) loc
          else
            Ty(tk, tyArgs), ctx

        | _ -> unreachable ()

      | Some (UnivTySymbol _) -> unreachable () // UnivTySymbol is only resolved from type variable.

      | None ->
        match tyPrimOfIdent ident tyArgs with
        | Some ty -> ty, ctx
        | None -> errorTy ctx (UndefinedTyError ident) loc

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

/// Adds a value symbol to current module if public.
let private addValueToModule ctx (currentModule: NsOwner) vis alias valueSymbol =
  if isPublic vis then
    addValueToNs ctx currentModule alias valueSymbol
  else
    ctx

let private addTyToModule ctx currentModule vis alias tySerial =
  if isPublic vis then
    addTyToNs ctx currentModule alias tySerial
  else
    ctx

let private addSubmoduleToModule ctx currentModule vis alias subNsOwner =
  if isPublic vis then
    addNsToNs ctx currentModule alias subNsOwner
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
      let linkage = makeLinkage ctx vis (identOf name)

      { ctx with
          DeclaredVars =
            ctx.DeclaredVars
            |> TMap.add (posOf name) varSerial
          NewVarMeta =
            ctx.NewVarMeta
            |> TMap.add varSerial (IsStatic, linkage) }

    let ctx = importValue ctx (identOf name) varSymbol

    addValueToModule ctx currentModule vis (identOf name) varSymbol

  match pat with
  | NPat.Ident (vis, name) ->
    match resolveUnqualifiedValue ctx (identOf name) with
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

    let ctx = importValue ctx (identOf name) funSymbol

    addValueToModule ctx currentModule vis (identOf name) funSymbol

let private cdAfterTyDecl (ctx: ScopeCtx) currentModule vis name tySerial tySymbol arity : ScopeCtx =
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

  let ctx = importTy ctx (identOf name) tySymbol
  addTyToModule ctx currentModule vis (identOf name) tySymbol

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
             let ctx =
               addValueToNs ctx (nsOwnerOfTy tySerial) (identOf name) variantSymbol

             importValue ctx (identOf name) variantSymbol

           let ctx =
             addValueToModule ctx currentModule vis (identOf name) (VariantSymbol variantSerial)

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
      addLog ctx UnimplGenericTyError loc
    else
      ctx

  let tySerial, ctx = freshSerial ctx
  let tySymbol = RecordTySymbol tySerial
  let arity = List.length tyArgs
  cdAfterTyDecl ctx currentModule vis name tySerial tySymbol arity

let private cdOpenDecl ctx path loc : ScopeCtx =
  let path = path |> List.map identOf
  let moduleSerials = resolveModulePath ctx path

  // __trace (
  //   "cdOpenDecl "
  //   + S.concat "." path
  //   + " -> "
  //   + (moduleSerials |> List.map string |> S.concat ", ")
  // )

  let ctx =
    if List.isEmpty moduleSerials then
      addLog ctx ModulePathNotFoundError loc
    else
      openModules ctx moduleSerials

  ctx

let private cdModuleSynonymDecl ctx name path : ScopeCtx =
  match identOf name, path with
  | "_", _
  | _, [] -> ctx

  | _ ->
    let moduleSerials =
      let path = path |> List.map identOf
      resolveModulePath ctx path

    if List.isEmpty moduleSerials then
      let _, loc = name
      addLog ctx ModulePathNotFoundError loc
    else
      // Import all modules that are referred by the path via the specified alias.
      moduleSerials
      |> List.fold (fun ctx moduleSerial -> importNsOwner ctx (identOf name) (nsOwnerOfModule moduleSerial)) ctx

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
    importNsOwner ctx (identOf name) moduleNs

  addSubmoduleToModule ctx currentModule vis (identOf name) moduleNs

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
      let ctx =
        { ctx with
            PatScope =
              ctx.PatScope
              |> TMap.add ident (varSerial, loc, []) }

      let ctx = addVarDef ctx varSerial varDef
      importValue ctx ident (VarSymbol varSerial)

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

  match resolveUnqualifiedValue ctx (identOf name) with
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
  let rec resolvePatAsNsOwners ctx pat : NsOwner list =
    match pat with
    | NPat.Ident (_, name) -> resolveUnqualifiedNsOwner ctx (identOf name)

    | NPat.Nav (l, r, _) ->
      resolvePatAsNsOwners ctx l
      |> List.collect (fun nsOwner -> resolveQualifiedNsOwner ctx nsOwner (identOf r))

    | _ -> []

  let l, r, loc =
    match pat with
    | NPat.Nav (l, r, loc) -> l, r, loc
    | _ -> unreachable ()

  let patOpt =
    resolvePatAsNsOwners ctx l
    |> List.tryPick (fun nsOwner ->
      match resolveQualifiedValue ctx nsOwner (identOf r) with
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

let private doWithPatScope (ctx: ScopeCtx) patScopeOpt (f: ScopeCtx -> _ * ScopeCtx) =
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
    doWithPatScope ctx None (fun ctx -> nameResPat ctx pat)

  let ctx =
    lScope
    |> TMap.fold
         (fun ctx (_: string) (_, _, useLocs) ->
           match useLocs with
           | [] -> ctx
           | loc :: _ -> addLog ctx VarNameConflictError loc)
         ctx

  // Set of variables defined in the left-hand side.
  let varSerialSet =
    lScope
    |> TMap.toList
    |> List.map (fun (_: string, (varSerial, _, _)) -> varSerial)
    |> TSet.ofList varSerialCompare

  let pats, ctx =
    pats
    |> List.mapFold
         (fun ctx pat ->
           let (rScope, pat), ctx =
             doWithPatScope ctx (Some lScope) (fun ctx -> nameResPat ctx pat)

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
               addLog ctx OrPatInconsistentBindingError loc

           pat, ctx)
         ctx

  // PENDING: MirGen generates illegal code for binding OR patterns, so reject here.
  let ctx =
    if
      not (List.isEmpty pats)
      && not (TSet.isEmpty varSerialSet)
    then
      addLog ctx UnimplOrPatBindingError loc
    else
      ctx

  let pat =
    List.fold (fun l r -> TOrPat(l, r, loc)) pat pats

  pat, ctx

let private nameResIrrefutablePat (ctx: ScopeCtx) (pat: NPat) : TPat * ScopeCtx =
  let (scope, pat), ctx =
    doWithPatScope ctx None (fun ctx -> nameResPat ctx pat)

  let ctx =
    scope
    |> TMap.fold
         (fun ctx (_: string) (_, _, useLocs) ->
           match useLocs with
           | [] -> ctx
           | loc :: _ -> addLog ctx VarNameConflictError loc)
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
let private doNameResVarExpr ctx ident loc : TExpr option =
  match resolveUnqualifiedValue ctx ident with
  | Some symbol ->
    let expr =
      match symbol with
      | VarSymbol serial -> TVarExpr(serial, noTy, loc)
      | FunSymbol serial -> TFunExpr(serial, noTy, loc)
      | VariantSymbol serial -> TVariantExpr(serial, noTy, loc)
      | PrimSymbol prim -> TPrimExpr(prim, noTy, loc)

    Some expr

  | None ->
    match valuePrimOfIdent ident with
    | Some prim -> TPrimExpr(prim, noTy, loc) |> Some
    | None -> None

let private nameResUnqualifiedIdentExpr ctx ident loc tyArgs : TExpr * ScopeCtx =
  if List.isEmpty tyArgs then
    match doNameResVarExpr ctx ident loc with
    | Some expr -> expr, ctx
    | None -> errorExpr ctx (UndefinedValueError ident) loc
  else
    let tyArgs, ctx =
      List.mapFold nameResTyInAscription ctx tyArgs

    match resolveUnqualifiedValue ctx ident with
    | None when ident = "sizeof" ->
      match tyArgs with
      | [ ty ] -> TNodeExpr(TSizeOfEN, [ TNodeExpr(TTyPlaceholderEN, [], ty, loc) ], tyInt, loc), ctx
      | _ -> errorExpr ctx (TyArityError(ident, List.length tyArgs, 1)) loc

    | _ -> errorExpr ctx UnimplTyArgListError loc

let private nameResNavExpr (ctx: ScopeCtx) (expr: NExpr) : TExpr * ScopeCtx =
  /// Resolves an expressions as scope.
  ///
  /// Returns (scopeOpt, exprOpt).
  /// scopeOpt should eb some it can be resolved to scope.
  /// exprOpt is also obtained by resolving inner `nav`s as possible.
  let rec resolveExprAsNsOwners ctx expr : ResolvedExpr * ScopeCtx =
    match expr with
    | NExpr.Ident ((ident, loc), []) ->
      let nsOwners = resolveUnqualifiedNsOwner ctx ident
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
          |> List.collect (fun nsOwner -> resolveQualifiedNsOwner ctx nsOwner r)

        // Resolve as value.
        let exprOpt =
          let varSymbolOpt =
            superNsOwners
            |> List.tryPick (fun nsOwner ->
              match resolveQualifiedValue ctx nsOwner r with
              | None -> None
              | it -> it)

          match varSymbolOpt with
          | Some (VarSymbol varSerial) -> TVarExpr(varSerial, noTy, identLoc) |> Some
          | Some (FunSymbol funSerial) -> TFunExpr(funSerial, noTy, identLoc) |> Some
          | Some (VariantSymbol variantSerial) ->
            TVariantExpr(variantSerial, noTy, identLoc)
            |> Some
          | Some (PrimSymbol prim) -> TPrimExpr(prim, noTy, identLoc) |> Some
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
  | NotResolvedExpr (ident, loc) -> errorExpr ctx (UndefinedValueError ident) loc

let private nameResExpr (ctx: ScopeCtx) (expr: NExpr) : TExpr * ScopeCtx =
  match expr with
  | NExpr.Bad loc -> txAbort loc, ctx
  | NExpr.Lit (lit, loc) -> TLitExpr(lit, loc), ctx

  | NExpr.Ident ((ident, loc), tyArgs) -> nameResUnqualifiedIdentExpr ctx ident loc tyArgs
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
    let ctx = startScope ctx ExprScope
    let stmts, ctx = stmts |> List.mapFold nameResStmt ctx
    let last, ctx = last |> nameResExpr ctx
    let ctx = finishScope ctx
    TBlockExpr(stmts, last), ctx

  | NExpr.Match (cond, arms, loc) ->
    let cond, ctx = cond |> nameResExpr ctx

    let arms, ctx =
      arms
      |> List.mapFold
           (fun ctx (pat, guardOpt, body, loc) ->
             let ctx = startScope ctx ExprScope
             let pat, ctx = pat |> nameResRefutablePat ctx

             // Default to `true` if guard is missing.
             let guard, ctx =
               match guardOpt with
               | Some guard -> guard |> nameResExpr ctx
               | None -> txTrue loc, ctx

             let body, ctx = body |> nameResExpr ctx
             let ctx = finishScope ctx
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
           (fun ctx ((ident, _), init, loc) ->
             let init, ctx = init |> nameResExpr ctx
             (ident, init, loc), ctx)
           ctx

    TRecordExpr(baseOpt, fields, noTy, loc), ctx

  | NExpr.Tuple (items, loc) ->
    let items, ctx = items |> List.mapFold nameResExpr ctx
    TNodeExpr(TTupleEN, items, noTy, loc), ctx

  | NExpr.Unary (MinusUnary, arg, loc) ->
    let arg, ctx = arg |> nameResExpr ctx
    TNodeExpr(TMinusEN, [ arg ], noTy, loc), ctx

  | NExpr.Unary (PtrOfUnary, arg, loc) ->
    let arg, ctx = arg |> nameResExpr ctx
    TNodeExpr(TPtrOfEN, [ arg ], noTy, loc), ctx

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

// -----------------------------------------------
// Statement
// -----------------------------------------------

let private nameResLetValStmt (ctx: ScopeCtx) stmt : TStmt * ScopeCtx =
  let pat, init, loc =
    match stmt with
    | NStmt.LetVal (pat, init, loc) -> pat, init, loc
    | _ -> unreachable ()

  let ctx = startScope ctx ExprScope
  let init, ctx = init |> nameResExpr ctx
  let ctx = finishScope ctx

  let pat, ctx = pat |> nameResIrrefutablePat ctx
  TLetValStmt(pat, init, loc), ctx

let private nameResLetFunStmt (ctx: ScopeCtx) stmt : TStmt * ScopeCtx =
  let isRec, vis, name, argPats, body, loc =
    match stmt with
    | NStmt.LetFun (isRec, vis, name, argPats, body, loc) -> isRec, vis, name, argPats, body, loc
    | _ -> unreachable ()

  let vis, (funSerial, ctx) =
    match ctx.DeclaredFuns |> TMap.tryFind (posOf name) with
    | Some funSerial -> vis, (funSerial, ctx)
    | None -> PrivateVis, freshFunSerial ctx

  let funName = identOf name

  let ctx =
    let funDef: FunDef =
      { Name = funName
        Arity = List.length argPats
        Ty = TyScheme([], noTy)
        Abi = MiloneAbi
        Linkage = makeLinkage ctx vis funName
        Prefix = ctx.AncestralFuns
        Loc = loc }

    addFunDef ctx funSerial funDef

  let ctx =
    // For recursive referencing.
    match isRec with
    | IsRec -> importValue ctx funName (FunSymbol funSerial)
    | _ -> ctx

  let argPats, body, ctx =
    // __trace ("enterLetFun " + funName)

    let ctx =
      let ctx = enterLetInit ctx funName
      startScope ctx ExprScope

    let argPats, ctx =
      argPats |> List.mapFold nameResIrrefutablePat ctx

    let body, ctx = body |> nameResExpr ctx

    let ctx =
      let ctx = finishScope ctx
      leaveLetInit ctx

    // __trace ("leaveLetFun " + funName)
    argPats, body, ctx

  let ctx =
    match isRec with
    | NotRec -> importValue ctx funName (FunSymbol funSerial)
    | _ -> ctx

  TLetFunStmt(funSerial, isRec, vis, argPats, body, loc), ctx

let private nameResStmt ctx (stmt: NStmt) : TStmt * ScopeCtx =
  match stmt with
  | NStmt.Expr expr ->
    let expr, ctx = expr |> nameResExpr ctx
    TExprStmt expr, ctx

  | NStmt.LetVal _ -> nameResLetValStmt ctx stmt
  | NStmt.LetFun _ -> nameResLetFunStmt ctx stmt

// -----------------------------------------------
// Declaration
// -----------------------------------------------

/// Defines type arguments declared in a type declaration.
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

let private nameResTySynonymDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, bodyTy, loc =
    match decl with
    | NDecl.TySynonym (_, name, tyArgs, bodyTy, loc) -> name, tyArgs, bodyTy, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = startScope ctx TyDeclScope
  let tyArgSerials, tyArgToSerials, ctx = defineTyArgs ctx tyArgs

  let bodyTy, ctx =
    let tyArgs =
      tyArgToSerials
      |> List.map (fun (tyArg, univTySerial) -> tyArg, UnivTySymbol univTySerial)
      |> TMap.ofList compare

    resolveTy ctx bodyTy tyArgs

  let tyDef =
    SynonymTyDef(identOf name, tyArgSerials, bodyTy, loc)

  let ctx = addTyDef ctx tySerial tyDef
  finishScope ctx

let private nameResUnionTyDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, variants, loc =
    match decl with
    | NDecl.Union (_, name, tyArgs, variants, loc) -> name, tyArgs, variants, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = startScope ctx TyDeclScope
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

  let ctx = addTyDef ctx tySerial tyDef
  finishScope ctx

let private nameResRecordTyDecl (ctx: ScopeCtx) decl : ScopeCtx =
  let name, tyArgs, fields, repr, loc =
    match decl with
    | NDecl.Record (_, name, tyArgs, fields, repr, loc) -> name, tyArgs, fields, repr, loc
    | _ -> unreachable ()

  let tySerial, _ = ctx.DeclaredTys |> mapFind (posOf name)

  let ctx = startScope ctx TyDeclScope
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

  let ctx = addTyDef ctx tySerial tyDef
  finishScope ctx

let private nameResModuleDecl (ctx: ScopeCtx) moduleDecl : TStmt * ScopeCtx =
  let (NModuleDecl (_, _, name, decls, _)) = moduleDecl

  let moduleSerial =
    ctx.DeclaredModules |> mapFind (posOf name)

  let parent, ctx =
    let ctx = startScope ctx ExprScope
    enterModule ctx (identOf name)

  let ctx =
    // Open the parent module (and modules with the same path).
    let parentPath = parent

    resolveModulePath ctx parentPath
    |> List.fold openModule ctx

  let stmts, ctx =
    nameResDecls (nsOwnerOfModule moduleSerial) ctx decls

  let ctx =
    let ctx = leaveModule ctx parent
    finishScope ctx

  TBlockStmt(IsRec, stmts), ctx

let private nameResDecl ctx (decl: NDecl) : TStmt option * ScopeCtx =
  let some (stmt, ctx) = Some stmt, ctx
  let none ctx = None, ctx

  match decl with
  | NDecl.Stmt stmt -> nameResStmt ctx stmt |> some
  | NDecl.TySynonym _ -> nameResTySynonymDecl ctx decl |> none
  | NDecl.Union _ -> nameResUnionTyDecl ctx decl |> none
  | NDecl.Record _ -> nameResRecordTyDecl ctx decl |> none
  | NDecl.Module decl -> nameResModuleDecl ctx decl |> some

  // Open and module synonym statements are used in collectDecls and no longer necessary.
  | NDecl.Open _
  | NDecl.ModuleSynonym _ -> None, ctx

let private nameResDecls (currentModule: NsOwner) ctx decls : TStmt list * ScopeCtx =
  let ctx = collectDecls currentModule ctx decls
  decls |> listChooseFold nameResDecl ctx

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

  let state =
    let s: ModuleTySerial = 1000000001 // 10^8
    let stdModuleSerial, s = s, s + 1
    let stdNs = nsOwnerOfModule stdModuleSerial
    let stdOwnNs, s = nsOwnerOfModule s, s + 1
    let ownModuleNs, s = nsOwnerOfModule s, s + 1
    let stdPtrNs, s = nsOwnerOfModule s, s + 1
    let ptrModuleNs = nsOwnerOfModule s

    let state = emptyState ()
    let ctx = state.ScopeCtx
    let ctx = addNsToNs ctx stdNs "Own" stdOwnNs
    let ctx = addNsToNs ctx stdNs "Ptr" stdPtrNs

    // Std.Own
    let ctx =
      let ctx =
        addTyToNs ctx stdOwnNs "Own" (PrimTySymbol OwnTk)

      let ctx = addNsToNs ctx stdOwnNs "Own" ownModuleNs

      let addValue alias prim ctx =
        addValueToNs ctx ownModuleNs alias (PrimSymbol prim)

      ctx
      |> addValue "acquire" TPrim.OwnAcquire
      |> addValue "release" TPrim.OwnRelease

    // Std.Ptr
    let ctx =
      let addTy alias prim ctx =
        addTyToNs ctx stdPtrNs alias (PrimTySymbol prim)

      let add alias prim ctx =
        addValueToNs ctx ptrModuleNs alias (PrimSymbol prim)

      let ctx = addNsToNs ctx stdPtrNs "Ptr" ptrModuleNs

      ctx
      |> addTy "InPtr" (NativePtrTk RefMode.ReadOnly)
      |> addTy "OutPtr" (NativePtrTk RefMode.WriteOnly)
      |> addTy "VoidInPtr" (VoidPtrTk IsConst)
      |> add "select" TPrim.PtrSelect
      |> add "read" TPrim.PtrRead
      |> add "write" TPrim.PtrWrite
      |> add "nullPtr" TPrim.NullPtr
      |> add "cast" TPrim.PtrCast
      |> add "invalid" TPrim.PtrInvalid
      |> add "asIn" TPrim.PtrAsIn
      |> add "asNative" TPrim.PtrAsNative
      |> add "distance" TPrim.PtrDistance

    let ctx =
      { ctx with RootModules = ("Std", stdModuleSerial) :: ctx.RootModules }

    { state with ScopeCtx = ctx }

  let modules, state =
    layers
    |> listCollectFold
         (fun (state: NameResState) modules ->
           modules
           |> List.mapFold
                (fun (state: NameResState) moduleRoot ->
                  let newRootModule, m, ctx =
                    nameResModuleRoot state.ScopeCtx moduleRoot

                  let state, localVars = sMerge newRootModule state ctx
                  { m with Vars = localVars }, state)
                state)
         state

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
