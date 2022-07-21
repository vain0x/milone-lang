/// Semantic analysis.
///
/// - name resolution
/// - type inference and checking
/// - pattern matching exhaustivity
/// - validation:
///     - OR pattern bindings
///     - privacy
///     - use of special forms such as printf, __nativeFun, etc.
///     - synonyms must be acyclic
///     - native functions must be closed and monomorphic
module rec MiloneLang.Sema

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers

/// Polymorphic level. (a.k.a. level or rank.)
type PolyLevel = int

[<Struct; NoEquality; NoComparison>]
type Symbol = Symbol of hint: string * serial: int

[<NoEquality; NoComparison>]
type IsMut =
  | IsConst
  | IsMut

[<NoEquality; NoComparison>]
type IsGlobal =
  | IsGlobal
  | NotGlobal

// -----------------------------------------------
// Value symbols
// -----------------------------------------------

[<Struct; NoEquality; NoComparison>]
type VarId = VarId of Symbol

[<NoEquality; NoComparison>]
type VarData =
  { Name: Ident
    Vis: Vis
    IsGlobal: IsGlobal
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type FunId = FunId of Symbol

[<NoEquality; NoComparison>]
type FunData =
  { Name: Ident
    Vis: Vis
    Args: VarId
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type VariantId = VariantId of Symbol

[<NoEquality; NoComparison>]
type VariantData =
  { Name: Ident
    Vis: Vis
    UnionTy: UnionTyId
    PayloadTy: BTy
    Loc: Loc }

// -----------------------------------------------
// Type symbols
// -----------------------------------------------

[<Struct; NoEquality; NoComparison>]
type MetaTyId = MetaTyId of Symbol

[<NoEquality; NoComparison>]
type MetaTyData =
  { Name: Ident
    Bound: BTy option
    Level: PolyLevel
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type UnivTyId = UnivTyId of Symbol

[<NoEquality; NoComparison>]
type UnivTyData = { Name: Ident; Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type SynonymTyId = SynonymTyId of Symbol

[<NoEquality; NoComparison>]
type SynonymTyData = { TyArgs: UnivTyId list; Body: BTy }

[<Struct; NoEquality; NoComparison>]
type UnionTyId = UnionTyId of Symbol

[<NoEquality; NoComparison>]
type UnionTyData =
  { Name: Ident
    Variants: VariantId list
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type RecordTyId = RecordTyId of Symbol

[<NoEquality; NoComparison>]
type RecordTyData =
  { Name: Ident
    Fields: (Ident * BTy * Loc) list
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type ModuleTyId = ModuleTyId of Symbol

[<NoEquality; NoComparison>]
type ModuleTyData = { Name: Ident; Loc: Loc }

// -----------------------------------------------
// Type constructors
// -----------------------------------------------

/// Type constructor.
[<NoEquality; NoComparison>]
type BTk =
  // Built-in monomorphic types.
  | BIntTk of IntFlavor
  | BFloatTk of FloatFlavor
  | BBoolTk
  | BCharTk
  | BStringTk
  | BObjTk

  // Built-in polymorphic object types.
  | BFunTk

  // Built-in product types.
  | BTupleTk

  // Built-in DUnion types.
  | BOptionTk
  | BListTk

  // FFI types.
  | BNativePtrTk
  | BVoidPtrTk
  | BNativeFunTk
  | BUUConstPtrTk

  // Nominal types.
  | BMetaTk of metaTyId: MetaTyId
  | BUnivTk of univTyId: UnivTyId
  | BSynonymTk of synonymTyId: SynonymTyId
  | BUnionTk of unionTyId: UnionTyId
  | BRecordTk of recordTyId: RecordTyId

// -----------------------------------------------
// Type terms
// -----------------------------------------------

[<Struct; NoEquality; NoComparison>]
type BTy = BTy of tyConstructor: BTk * tyArgs: BTy list * Loc

[<NoEquality; NoComparison>]
type BBinding =
  | BValBinding of BPat * init: BExpr * Loc
  | BFunBinding of FunId * BPat list * body: BExpr * Loc

// -----------------------------------------------
// Pattern
// -----------------------------------------------

[<NoEquality; NoComparison>]
type BPatNode =
  | BDiscardPn
  | BVarPn of VarId
  | BVariant0Pn of VariantId
  | BVariant1Pn of VariantId
  | BNilPn
  | BConsPn
  | BNonePn
  | BSomePn
  | BTuplePn
  | BAsPn of VarId
  | BTyAnnotatePn

[<NoEquality; NoComparison>]
type BPat =
  | BNodePat of BPatNode * BPat list * BTy * Loc
  | BOrPat of BPat * BPat * Loc

// -----------------------------------------------
// Expression
// -----------------------------------------------

type BPrim = | BPrim

[<NoEquality; NoComparison>]
type BExpr =
  | BVarExpr of VarId
  | BFunNameExpr of VarId
  | BPrimNameExpr of BPrim * Loc

// -----------------------------------------------
// Statement
// -----------------------------------------------

[<NoEquality; NoComparison>]
type BStmt = BBindStmt of BBinding list

// -----------------------------------------------
// Context
// -----------------------------------------------

[<NoEquality; NoComparison>]
type SemaCtx =
  { Vars: AssocMap<VarId, VarData>
    Funs: AssocMap<FunId, FunData>
    Variants: AssocMap<VariantId, VariantData>
    MetaTys: AssocMap<MetaTyId, MetaTyData>
    UnivTys: AssocMap<UnivTyId, UnivTyData>
    SynonymTys: AssocMap<SynonymTyId, SynonymTyData>
    UnionTys: AssocMap<UnionTyId, UnionTyData>
    RecordTys: AssocMap<RecordTyId, RecordTyData> }
