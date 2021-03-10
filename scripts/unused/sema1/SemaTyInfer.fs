/// # SemaTyInfer
///
/// Type inference. Semantics analysis.
module rec MiloneLang.SemaTyInfer

open MiloneLang.Types

/// Polymorphic level.
type PolyLevel = LetDepth

[<Struct>]
type VarId = VarId of int

[<NoEquality; NoComparison>]
type VarData =
  { Name: Ident
    SM: StorageModifier
    Loc: Loc }

[<Struct>]
type FunId = FunId of int

[<NoEquality; NoComparison>]
type FunData =
  { Name: Ident
    IsMain: bool
    Args: VarId
    Loc: Loc }

[<Struct>]
type VariantId = VariantId of int

[<NoEquality; NoComparison>]
type VariantData =
  { Name: Ident
    PayloadTy: BTy
    Loc: Loc }

[<Struct>]
type MetaTyId = MetaTyId of int

[<NoEquality; NoComparison>]
type MetaTyData =
  { Name: Ident
    Bound: BTy option
    Level: PolyLevel
    Loc: Loc }

[<Struct>]
type UnivTyId = UnivTyId of int

[<NoEquality; NoComparison>]
type UnivTyData = { Name: Ident; Loc: Loc }

[<Struct>]
type SynonymTyId = SynonymTyId of int

[<NoEquality; NoComparison>]
type SynonymTyData = { TyArgs: UnivTyId list; Body: BTy }

[<Struct>]
type UnionTyId = UnionTyId of int

[<NoEquality; NoComparison>]
type UnionTyData =
  { Name: Ident
    Variants: VariantId list
    Loc: Loc }

[<Struct>]
type RecordTyId = RecordTyId of int

[<NoEquality; NoComparison>]
type RecordTyData =
  { Name: Ident
    Fields: (Ident * BTy * Loc) list
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type BTyConstructor =
  // Built-in monomorphic types.
  | BBoolTk
  | BIntTk
  | BUIntTk
  | BCharTk
  | BStringTk
  | BObjTk

  // Built-in polymorphic object types.
  | BFunTk
  | BTupleTk

  // Built-in union types.
  | BOptionTk
  | BListTk

  // Nominal types.
  | BMetaTk of metaTyId: MetaTyId
  | BUnivTk of univTyId: UnivTyId
  | BSynonymTk of synonymTyId: SynonymTyId
  | BUnionTk of unionTyId: UnionTyId
  | BRecordTk of recordTyId: RecordTyId

[<NoEquality; NoComparison>]
type BTy = BTy of k: BTyConstructor * tyArgs: BTy list * loc: Loc

[<NoEquality; NoComparison>]
type BBinding =
  | BValBinding of VarId * init: BExpr * Loc
  | BFunBinding of FunId * args: VarId * body: BExpr * Loc

[<NoEquality; NoComparison>]
type BExpr =
  | BVarExpr of VarId
  | BFunNameExpr of VarId
  | BPrimNameExpr of HPrim * Loc

[<NoEquality; NoComparison>]
type BStmt = BBindStmt of BBinding list

[<NoEquality; NoComparison>]
type SemaCtx =
  { Vars: AssocMap<VarId, VarData>
    Funs: AssocMap<FunId, FunData>
    Variants: AssocMap<VariantId, VariantData>
    UnivTys: AssocMap<UnivTyId, UnivTyData>
    SynonymTys: AssocMap<SynonymTyId, SynonymTyData>
    UnionTys: AssocMap<UnionTyId, UnionTyData>
    RecordTys: AssocMap<RecordTyId, RecordTyData> }
