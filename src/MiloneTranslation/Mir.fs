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
open MiloneShared.Util
open MiloneTranslation.Hir

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
  | MSizeOfGv

/// Built-in 1-arity operation in middle IR.
[<Struct>]
[<NoEquality; NoComparison>]
type MUnary =
  | MMinusUnary
  | MNotUnary

  // Converts a scalar to int.
  | MIntOfScalarUnary of intOfScalarFlavor: IntFlavor
  | MFloatOfScalarUnary of floatOfScalarFlavor: FloatFlavor
  | MCharOfScalarUnary

  /// Gets raw ptr of string.
  | MStrPtrUnary

  /// Gets length of string.
  | MStrLenUnary

  /// Downcast.
  | MUnboxUnary

  /// Gets an item of tuple.
  | MTupleItemUnary of tupleItemIndex: int

  /// Gets variant tag of union value.
  | MGetDiscriminantUnary

  /// Gets payload of union value, unchecked.
  | MGetVariantUnary of variantSerial: VariantSerial

  /// Gets a field of record.
  | MRecordItemUnary of recordItemIndex: int

  | MListIsEmptyUnary

  /// Gets head of list, unchecked.
  | MListHeadUnary

  /// Gets tail of list, unchecked.
  | MListTailUnary

  | MNativeCastUnary

/// Built-in 2-arity operation in middle IR.
[<NoEquality; NoComparison>]
type MBinary =
  | MMulBinary
  | MDivBinary
  | MModuloBinary
  | MAddBinary
  | MSubBinary
  | MBitAndBinary
  | MBitOrBinary
  | MBitXorBinary
  | MLeftShiftBinary
  | MRightShiftBinary
  | MEqualBinary
  | MNotEqualBinary
  | MLessBinary
  | MGreaterEqualBinary
  | MIntCompareBinary
  | MInt64CompareBinary
  | MUInt64CompareBinary
  | MStrAddBinary
  | MStrCompareBinary

  /// `s.str[i]`
  | MStrIndexBinary

[<NoEquality; NoComparison>]
type MAction =
  | MAssertAction
  | MPrintfnAction
  | MEnterRegionAction
  | MLeaveRegionAction
  | MCallNativeAction of funName: string
  | MPtrWriteAction

[<Struct; NoEquality; NoComparison>]
type MPrim =
  /// string -> int
  | MIntOfStrPrim of intOfStrFlavor: IntFlavor
  | MFloatOfStrPrim of floatOfStrFlavor: FloatFlavor
  | MCharOfStrPrim

  | MStrOfBoolPrim
  | MStrOfCharPrim
  | MStrOfIntPrim of strOfIntFlavor: IntFlavor
  | MStrOfFloatPrim of strOfFloatFlavor: FloatFlavor

  | MStrGetSlicePrim

  /// Construct a closure, packing environment.
  | MClosurePrim of closureFunSerial: FunSerial

  | MBoxPrim
  | MConsPrim
  | MVariantPrim of variantSerial: VariantSerial
  | MRecordPrim

  /// Direct call to procedure.
  | MCallProcPrim

  /// Indirect call to closure.
  | MCallClosurePrim

  | MCallNativePrim of funName: string
  | MPtrReadPrim

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
  | MProcExpr of FunSerial * Ty * Loc

  /// Variant constant.
  | MVariantExpr of TySerial * VariantSerial * Ty * Loc

  | MDiscriminantConstExpr of VariantSerial * Loc
  | MGenericValueExpr of MGenericValue * Ty * Loc

  | MUnaryExpr of MUnary * arg: MExpr * resultTy: Ty * Loc
  | MBinaryExpr of MBinary * MExpr * MExpr * resultTy: Ty * Loc

  | MNativeExpr of code: string * Ty * Loc

[<Struct>]
[<NoEquality; NoComparison>]
type MConst =
  | MLitConst of l: Lit
  | MDiscriminantConst of v: VariantSerial

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type MSwitchClause =
  { Cases: MConst list
    IsDefault: bool
    Terminator: MTerminator }

[<NoEquality; NoComparison>]
type MTerminator =
  | MExitTerminator of exitCode: MExpr
  | MReturnTerminator of result: MExpr
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
  | MProcDecl of FunSerial * args: (VarSerial * Ty * Loc) list * body: MBlock list * resultTy: Ty * Loc
  | MNativeDecl of code: string * Loc

// -----------------------------------------------
// Expressions (MIR)
// -----------------------------------------------

let mexprExtract expr =
  match expr with
  | MLitExpr (lit, loc) -> litToTy lit, loc
  | MUnitExpr loc -> tyUnit, loc
  | MNeverExpr loc -> tyUnit, loc
  | MVarExpr (_, ty, loc) -> ty, loc
  | MProcExpr (_, ty, loc) -> ty, loc
  | MVariantExpr (_, _, ty, loc) -> ty, loc
  | MDiscriminantConstExpr (_, loc) -> tyInt, loc

  | MGenericValueExpr (genericValue, ty, loc) ->
    match genericValue with
    | MNilGv -> ty, loc
    | MSizeOfGv -> tyInt, loc

  | MUnaryExpr (_, _, ty, loc) -> ty, loc
  | MBinaryExpr (_, _, _, ty, loc) -> ty, loc
  | MNativeExpr (_, ty, loc) -> ty, loc

let mexprToTy expr = expr |> mexprExtract |> fst

// -----------------------------------------------
// Declarations (MIR)
// -----------------------------------------------

let mDeclToLoc (decl: MDecl) : Loc =
  match decl with
  | MProcDecl (_, _, _, _, loc) -> loc
  | MNativeDecl (_, loc) -> loc

// -----------------------------------------------
// Expression sugaring (MIR)
// -----------------------------------------------

let mxSugar expr =
  let mxSugarUni op l ty loc =
    match l with
    // SUGAR: `not true` ==> `false`
    // SUGAR: `not false` ==> `true`
    | MLitExpr (BoolLit value, loc) -> MLitExpr(BoolLit(not value), loc)

    // SUGAR: `not (not x)` ==> `x`
    | MUnaryExpr (MNotUnary, l, _, _) -> l

    // SUGAR: `not (x = y)` ==> `x <> y`
    | MBinaryExpr (MEqualBinary, l, r, ty, loc) -> MBinaryExpr(MNotEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x <> y)` ==> `x = y`
    | MBinaryExpr (MNotEqualBinary, l, r, ty, loc) -> MBinaryExpr(MEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x < y)` ==> `x >= y`
    | MBinaryExpr (MLessBinary, l, r, ty, loc) -> MBinaryExpr(MGreaterEqualBinary, l, r, ty, loc)

    // SUGAR: `not (x >= y)` ==> `x < y`
    | MBinaryExpr (MGreaterEqualBinary, l, r, ty, loc) -> MBinaryExpr(MLessBinary, l, r, ty, loc)

    | _ -> MUnaryExpr(op, l, ty, loc)

  let mxSugarBin op l r ty loc =
    match op, l, r with
    // SUGAR: `x = false` ==> `not x`
    | MEqualBinary, MLitExpr (BoolLit false, _), _ -> mxSugarUni MNotUnary r ty loc

    | MEqualBinary, _, MLitExpr (BoolLit false, _) -> mxSugarUni MNotUnary l ty loc

    // SUGAR: `x = true` ==> `x`
    | MEqualBinary, MLitExpr (BoolLit true, _), _ -> r

    | MEqualBinary, _, MLitExpr (BoolLit true, _) -> l

    | _ -> MBinaryExpr(op, l, r, ty, loc)

  match expr with
  // SUGAR: `x: unit` ==> `()`
  | MVarExpr (_, Ty (TupleTk, []), loc) -> MUnitExpr loc

  | MUnaryExpr (op, l, ty, loc) ->
    let l = mxSugar l
    mxSugarUni op l ty loc

  | MBinaryExpr (op, l, r, ty, loc) ->
    let l = mxSugar l
    let r = mxSugar r
    mxSugarBin op l r ty loc

  | _ -> expr
