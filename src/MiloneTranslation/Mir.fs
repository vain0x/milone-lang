/// # Mir
///
/// Provides types and functions for mid-level intermediate representation (MIR).
///
/// MIR is still similar to HIR, however, it's imperative
/// and has explicit jump statements and assignments.
///
/// Unlike HIR, expressions are not recursive,
/// e.g. function arguments can't contain another function call.
///
/// (TODO: Function body is just a list of statements.
///        Currently not "well-considered" form; not XXX-normal form nor SSA nor basic blocks etc.)
module rec MiloneTranslation.Mir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneTranslation.HirTypes
open Std.StdMap

// -----------------------------------------------
// MIR types
// -----------------------------------------------

type Label = string

/// Intermediate language between HIR and MIR for match expressions.
[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type MatchIR =
  | PatLabel of Label
  | Pat of HPat * nextLabel: Label
  | GoBody of Label
  | BodyLabel of Label
  | Guard of guard: HExpr * nextLabel: Label
  | Body of body: HExpr

[<NoEquality; NoComparison>]
type MGenericValue =
  | MNilGv
  | MNullPtrGv
  | MSizeOfGv
  | MTyPlaceholderGv

/// Built-in 1-arity operation in middle IR.
[<NoEquality; NoComparison>]
type MUnary =
  | MMinusUnary
  | MBitNotUnary
  | MNotUnary
  | MPtrOfUnary

  // Converts a scalar to int.
  | MIntOfScalarUnary of intOfScalarFlavor: IntFlavor
  | MFloatOfScalarUnary of floatOfScalarFlavor: FloatFlavor
  | MCharOfScalarUnary

  /// Gets raw ptr of string.
  | MStringAsPtrUnary

  /// Gets length of string.
  | MStringLengthUnary

  /// Downcast.
  | MUnboxUnary of itemTy: Ty

  // note: tuple is converted to a record in MonoTy
  /// Gets an item of tuple.
  | MTupleItemUnary of tupleItemIndex: int * tupleTy: Ty

  /// Gets variant tag of union value.
  | MGetDiscriminantUnary of unionTy: Ty

  /// Gets payload of union value, unchecked.
  | MGetVariantUnary of variantSerial: VariantSerial

  /// Gets a field of record.
  | MRecordItemUnary of recordItemIndex: int * recordTy: Ty

  | MListIsEmptyUnary

  /// Gets head of list, unchecked.
  | MListHeadUnary of itemTy: Ty

  /// Gets tail of list, unchecked.
  | MListTailUnary of itemTy: Ty

  /// Dereference a typed pointer.
  | MDerefUnary of itemTy: Ty
  | MNativeCastUnary of targetTy: Ty

/// Built-in 2-arity operation in middle IR.
[<NoEquality; NoComparison>]
type MBinary =
  | MMultiplyBinary
  | MDivideBinary
  | MModuloBinary
  | MAddBinary
  | MSubtractBinary
  | MBitAndBinary
  | MBitOrBinary
  | MBitXorBinary
  | MLeftShiftBinary
  | MRightShiftBinary
  | MEqualBinary
  | MNotEqualBinary
  | MLessBinary
  | MGreaterEqualBinary
  | MInt32CompareBinary
  | MInt64CompareBinary
  | MUInt64CompareBinary
  | MStringAddBinary
  | MStringCompareBinary

  /// `s.ptr[i]`
  | MStringIndexBinary
  // `&p[i]`
  | MPtrAddBinary

[<NoEquality; NoComparison>]
type MAction =
  | MAssertNotAction
  | MPrintfnAction of argTys: Ty list
  | MEnterRegionAction
  | MLeaveRegionAction
  | MCallProcAction
  | MCallClosureAction
  | MCallNativeAction of funName: string * argTys: Ty list
  /// [ ptr; value ]
  | MPtrWriteAction

[<NoEquality; NoComparison>]
type MPrim =
  | MIntOfStringPrim of intOfStringFlavor: IntFlavor
  | MFloatOfStringPrim of floatOfStringFlavor: FloatFlavor
  | MCharOfStringPrim

  | MStringOfBoolPrim
  | MStringOfCharPrim
  | MStringOfIntPrim of stringOfIntFlavor: IntFlavor
  | MStringOfFloatPrim of stringOfFloatFlavor: FloatFlavor

  | MStringGetSlicePrim

  /// Construct a closure, packing environment.
  | MClosurePrim of closureFunSerial: FunSerial

  | MBoxPrim of argTy: Ty
  | MConsPrim of itemTy: Ty
  | MVariantPrim of variantSerial: VariantSerial
  | MRecordPrim

  /// Direct call to procedure.
  | MCallProcPrim

  /// Indirect call to closure.
  | MCallClosurePrim

  | MCallNativePrim of funName: string * argTys: Ty list

  | MPtrInvalidPrim

/// Expression in middle IR.
[<NoEquality; NoComparison>]
type MExpr =
  | MLitExpr of Lit * Loc
  | MUnitExpr of Loc

  /// Never-evaluated expression.
  | MNeverExpr of Loc

  /// Variable.
  | MVarExpr of VarSerial * Ty * Loc

  /// Procedure.
  | MProcExpr of FunSerial * Loc

  /// Variant constant.
  | MVariantExpr of TySerial * VariantSerial * Loc

  | MDiscriminantConstExpr of VariantSerial * Loc
  | MGenericValueExpr of MGenericValue * Ty * Loc

  | MUnaryExpr of MUnary * arg: MExpr * Loc

  | MBinaryExpr of MBinary * MExpr * MExpr * Loc

  | MNativeExpr of code: string * MExpr list * Ty * Loc

[<NoEquality; NoComparison>]
type MConst =
  | MLitConst of l: Lit
  | MDiscriminantConst of v: VariantSerial

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MSwitchClause =
  { Cases: MConst list
    IsDefault: bool
    Terminator: MTerminator }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MAbortCause =
  | Assert
  | Exhaust
  | Never

[<NoEquality; NoComparison>]
type MTerminator =
  | MExitTerminator of exitCode: MExpr
  | MAbortTerminator of MAbortCause
  | MReturnTerminator of result: MExpr * resultTy: Ty
  | MGotoTerminator of Label
  | MIfTerminator of cond: MExpr * thenCl: MTerminator * elseCl: MTerminator
  | MSwitchTerminator of cond: MExpr * MSwitchClause list

/// Statement in middle IR.
[<NoEquality; NoComparison>]
type MStmt =
  | MActionStmt of MAction * MExpr list * Loc

  | MPrimStmt of MPrim * MExpr list * result: VarSerial * resultTy: Ty * Loc

  /// Declare a local variable.
  | MLetValStmt of VarSerial * MExpr option * Ty * Loc

  /// Set to uninitialized local variable.
  | MSetStmt of VarSerial * init: MExpr * Loc

  | MLabelStmt of Label * Loc

  | MGotoIfStmt of cond: MExpr * Label

  | MTerminatorStmt of MTerminator * Loc

  | MNativeStmt of string * MExpr list * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MBlock = { Stmts: MStmt list }

[<NoEquality; NoComparison>]
type MDecl =
  | MProcDecl of
    FunSerial *
    args: (VarSerial * Ty * Loc) list *
    body: MBlock list *
    resultTy: Ty *
    localVars: (VarSerial * Ty * Loc) list *
    Loc
  | MNativeDecl of code: string * args: MExpr list * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MModule =
  { DocId: DocId
    /// Name of local variables.
    Vars: VarNameMap
    /// Static variables that are defined to in the module.
    StaticVars: (VarSerial * Ty) list
    /// Extern variables that are referred to in the module.
    ExternVars: TreeMap<VarSerial, Ty>
    MainFunOpt: FunSerial option
    Decls: MDecl list }

// -----------------------------------------------
// Declarations (MIR)
// -----------------------------------------------

let mDeclToLoc (decl: MDecl) : Loc =
  match decl with
  | MProcDecl (_, _, _, _, _, loc) -> loc
  | MNativeDecl (_, _, loc) -> loc

// -----------------------------------------------
// Expression sugaring (MIR)
// -----------------------------------------------

let mxSugar expr =
  let mxSugarNot l loc =
    match l with
    // SUGAR: `not true` ==> `false`
    // SUGAR: `not false` ==> `true`
    | MLitExpr (BoolLit value, loc) -> MLitExpr(BoolLit(not value), loc)

    // SUGAR: `not (not x)` ==> `x`
    | MUnaryExpr (MNotUnary, l, _) -> l

    // SUGAR: `not (x = y)` ==> `x <> y`
    | MBinaryExpr (MEqualBinary, l, r, loc) -> MBinaryExpr(MNotEqualBinary, l, r, loc)

    // SUGAR: `not (x <> y)` ==> `x = y`
    | MBinaryExpr (MNotEqualBinary, l, r, loc) -> MBinaryExpr(MEqualBinary, l, r, loc)

    // SUGAR: `not (x < y)` ==> `x >= y`
    | MBinaryExpr (MLessBinary, l, r, loc) -> MBinaryExpr(MGreaterEqualBinary, l, r, loc)

    // SUGAR: `not (x >= y)` ==> `x < y`
    | MBinaryExpr (MGreaterEqualBinary, l, r, loc) -> MBinaryExpr(MLessBinary, l, r, loc)

    | _ -> MUnaryExpr(MNotUnary, l, loc)

  let mxSugarBin op l r loc =
    match op, l, r with
    // SUGAR: `x = false` ==> `not x`
    | MEqualBinary, MLitExpr (BoolLit false, _), _ -> mxSugarNot r loc

    | MEqualBinary, _, MLitExpr (BoolLit false, _) -> mxSugarNot l loc

    // SUGAR: `x = true` ==> `x`
    | MEqualBinary, MLitExpr (BoolLit true, _), _ -> r

    | MEqualBinary, _, MLitExpr (BoolLit true, _) -> l

    | _ -> MBinaryExpr(op, l, r, loc)

  match expr with
  // SUGAR: `x: unit` ==> `()`
  | MVarExpr (_, Ty (TupleTk, []), loc) -> MUnitExpr loc

  | MUnaryExpr (MNotUnary, l, loc) ->
    let l = mxSugar l
    mxSugarNot l loc

  | MBinaryExpr (op, l, r, loc) ->
    let l = mxSugar l
    let r = mxSugar r
    mxSugarBin op l r loc

  | _ -> expr
