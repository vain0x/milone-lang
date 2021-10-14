// Type monomorphization intermediate representation.
module rec MiloneTranslation.MonoTyIr

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.TypeFloat

module Hir = MiloneTranslation.Hir

// Same as HIR but type is mono ty (monomorphized).
type private Ty = MonoTy

type private TySerial = Hir.TySerial
type private VarSerial = Hir.VarSerial
type private FunSerial = Hir.FunSerial
type private VariantSerial = Hir.VariantSerial
type private HPatKind = Hir.HPatKind
type private HPrim = Hir.HPrim
type private HExprKind = Hir.HExprKind

/// Monomorphized type (?)
[<NoEquality; NoComparison>]
type MonoTy =
  | IntMt of intFlavor: IntFlavor
  | FloatMt of floatFlavor: FloatFlavor
  | UnitMt
  | BoolMt
  | CharMt
  | StrMt
  | ObjMt

  | FunMt of MonoTy list
  | ListMt of MonoTy

  // FFI types.
  | VoidMt
  | NativePtrMt of IsMut * MonoTy
  | NativeFunMt of MonoTy list
  | NativeTypeMt of cCode: string

  // Nominal types.
  | UnionMt of unionTy: TySerial
  | RecordMt of recordTy: TySerial

[<NoEquality; NoComparison>]
type TyDef =
  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc
  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: Ty
    Abi: FunAbi
    Linkage: Linkage
    ParentOpt: FunSerial option
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VariantDef =
  { Name: Ident
    UnionTySerial: TySerial

    /// Whether this is the only variant of the union.
    IsNewtype: bool

    HasPayload: bool
    PayloadTy: Ty
    Loc: Loc }

/// Pattern in HIR.
[<NoEquality; NoComparison>]
type HPat =
  | HLitPat of Lit * Loc

  /// `_`.
  | HDiscardPat of Ty * Loc

  /// Variable pattern.
  | HVarPat of VarSerial * Ty * Loc

  /// Variant name pattern.
  | HVariantPat of VariantSerial * Ty * Loc

  | HNodePat of HPatKind * HPat list * Ty * Loc

  | HAsPat of HPat * VarSerial * Loc

  /// Disjunction.
  | HOrPat of HPat * HPat * Loc

/// Expression in HIR.
[<NoEquality; NoComparison>]
type HExpr =
  | HLitExpr of Lit * Loc

  /// Name of variable.
  | HVarExpr of VarSerial * Ty * Loc

  /// Name of function.
  | HFunExpr of FunSerial * Ty * Loc

  /// Name of variant.
  | HVariantExpr of VariantSerial * Ty * Loc

  | HPrimExpr of HPrim * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of cond: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// Some built-in operation.
  | HNodeExpr of HExprKind * HExpr list * Ty * Loc

  /// Evaluate a list of expressions and returns the last, e.g. `x1; x2; ...; y`.
  | HBlockExpr of HExpr list * HExpr

  | HLetValExpr of pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * args: HPat list * body: HExpr * next: HExpr * Ty * Loc
