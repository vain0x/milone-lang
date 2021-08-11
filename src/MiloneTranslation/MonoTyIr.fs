// Type monomorphization intermediate representation.
module rec MiloneTranslation.MonoTyIr

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.TypeFloat
open MiloneShared.Util
open MiloneTranslation.Hir

module Hir = MiloneTranslation.Hir

// Same as HIR but type is mono ty (monomorphized).
type private Ty = MonoTy

/// Monomorphized type.
[<Struct; NoEquality; NoComparison>]
type MonoTy =
  | IntMt of intFlavor: IntFlavor
  | FloatMt of floatFlavor: FloatFlavor
  | BoolMt
  | CharMt
  | StrMt
  | ObjMt
  | UnitMt

  // FFI types.
  | VoidMt
  | NativePtrMt of nativePtrIsMut: IsMut
  | NativeFunMt
  | NativeTypeMt of cCode: string

  // Nominal types.
  | UnionMt of unionTy: TySerial
  | ListMt of listTy: TySerial
  | RecordMt of recordTy: TySerial

/// Kind of HNodePat.
[<Struct; NoEquality; NoComparison>]
type HPatKind =
  /// `[]`.
  | HNilPN

  /// `p1 :: p2`.
  | HConsPN

  | HNonePN

  /// `Some p1`.
  | HSomeAppPN

  /// `Variant p1`.
  | HVariantAppPN of variantApp: VariantSerial

  /// `p1, p2, ..., pN` or `()`.
  | HTuplePN

  /// Used to dereference a box inside of pattern matching.
  ///
  /// To match a value `v: obj` with box pattern `box p: T`,
  /// match `unbox v: T` with `p: T`.
  ///
  /// This is only generated internally in AutoBoxing.
  /// Not a part of F# nor milone-lang syntax.
  /// Unlike `:? T`, unboxing is unchecked.
  | HBoxPN

  /// Generated after compile error occurred while processing a pattern.
  | HAbortPN

/// Pattern in HIR.
[<NoEquality; NoComparison>]
type HPat =
  | HLitPat of Lit * Loc

  /// `_`.
  | HDiscardPat of Ty * Loc

  /// Variable pattern.
  | HVarPat of Vis * VarSerial * Ty * Loc

  /// Variant name pattern.
  | HVariantPat of VariantSerial * Ty * Loc

  | HNodePat of HPatKind * HPat list * Ty * Loc

  | HAsPat of HPat * VarSerial * Loc

  /// Disjunction.
  | HOrPat of HPat * HPat * Loc

/// Primitive in HIR.
[<RequireQualifiedAccess; Struct; NoComparison>]
type HPrim =
  // operator:
  | Not
  | Add
  | Sub
  | Mul
  | Div
  | Modulo
  | BitAnd
  | BitOr
  | BitXor
  | LeftShift
  | RightShift
  | Equal
  | Less
  | Compare

  // conversion:
  | ToInt of toIntFlavor: IntFlavor
  | ToFloat of toFloatFlavor: FloatFlavor
  | Char
  | String
  | Box
  | Unbox

  // string:
  | StrLength

  // option:
  | OptionNone
  | OptionSome

  // list:
  | Nil
  | Cons

  // effects:
  | Exit
  | Assert
  | Printfn
  | InRegion
  | NativeCast
  | PtrRead
  | PtrWrite

[<Struct; NoEquality; NoComparison>]
type HExprKind =
  | HAbortEN

  /// `-x`.
  | HMinusEN

  | HAppEN

  /// `s.[i]`
  | HIndexEN

  /// `s.[l .. r]`
  | HSliceEN

  /// Direct call to procedure or primitive.
  | HCallProcEN

  /// Indirect call to closure.
  | HCallClosureEN

  /// Direct call to current procedure at the end of function (i.e. tail-call).
  | HCallTailRecEN

  /// Direct call to native fun.
  | HCallNativeEN of funName: string

  /// Tuple constructor, e.g. `x, y, z`.
  | HTupleEN

  /// Closure constructor.
  | HClosureEN

  /// Record creation.
  ///
  /// Unlike record expr, it's guaranteed that
  /// all of fields are specified in order of declaration.
  | HRecordEN

  /// Gets i'th field of record.
  | HRecordItemEN of index: int

  /// Use function as function pointer.
  | HNativeFunEN of FunSerial

  /// Embed some C expression to output.
  | HNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | HNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | HNativeDeclEN of nativeDeclCode: string

  /// Size of type.
  | HSizeOfValEN

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

  | HRecordExpr of HExpr option * fields: (Ident * HExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of cond: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `str.Length`
  | HNavExpr of HExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | HNodeExpr of HExprKind * HExpr list * Ty * Loc

  /// Evaluate a list of expressions and returns the last, e.g. `x1; x2; ...; y`.
  | HBlockExpr of HExpr list * HExpr

  | HLetValExpr of pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * IsRec * Vis * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

/// HIR program. (project name, module name, decls) list.
type HProgram = (string * string * HExpr list) list

// -----------------------------------------------
// Back to HIR
// -----------------------------------------------

let backToHir (_program: HProgram) : Hir.HProgram = todo ()
