/// # HirTypes
///
/// Provides types for high-level intermediate representation (HIR).
///
/// HIR is functional-style. Similar to milone-lang's syntax.
module rec MiloneTranslationTypes.HirTypes

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open Std.StdMap

module S = Std.StdString

// -----------------------------------------------
// HIR types
// -----------------------------------------------

/// Serial number of types.
type TySerial = Serial

/// Serial number of variables.
[<Struct; NoComparison>]
type VarSerial = VarSerial of Serial

/// Serial number of functions.
[<Struct; NoComparison>]
type FunSerial = FunSerial of Serial

/// Serial number of variants.
[<Struct; NoComparison>]
type VariantSerial = VariantSerial of Serial

/// Type constructor.
[<NoEquality; NoComparison>]
type Tk =
  | IntTk of intFlavor: IntFlavor
  | FloatTk of floatFlavor: FloatFlavor
  | BoolTk
  | CharTk
  | StringTk
  | ObjTk

  /// Ty args must be `[s; t]`.
  | FunTk

  | TupleTk

  /// Ty args must be `[t]`.
  | ListTk

  // FFI types.
  | VoidPtrTk of IsMut
  | NativePtrTk of mode: RefMode
  | NativeFunTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | MetaTk of metaTy: TySerial * metaLoc: Loc
  | UnionTk of unionTy: TySerial
  | RecordTk of recordTy: TySerial

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type Ty =
  /// Type application.
  | Ty of Tk * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct; NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

/// Definition of named value in HIR.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VarDef =
  { Name: Ident
    IsStatic: IsStatic
    Linkage: Linkage

    /// Remark:
    ///   After monomorphization, local variables occur in multiple monomorphized instances
    ///   and their Ty contain undefined type variables. It shouldn't be used.
    Ty: Ty

    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Abi: FunAbi
    Linkage: Linkage
    Prefix: string list
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

/// Kind of HNodePat.
[<NoEquality; NoComparison>]
type HPatKind =
  /// `[]`.
  | HNilPN

  /// `p1 :: p2`.
  | HConsPN

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
  | StringLength

  // list:
  | Nil
  | Cons

  // effects:
  | Exit
  | Assert
  | Printfn
  | InRegion
  | NullPtr
  | PtrDistance
  | NativeCast

[<NoEquality; NoComparison>]
type HExprKind =
  /// `-x`.
  | HMinusEN

  /// `&&x`.
  | HPtrOfEN

  | HAppEN

  /// `s.[i]`
  | HIndexEN

  /// `s.[l .. r]`
  | HSliceEN

  | HDiscriminantEN of VariantSerial

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

  /// `Ptr.select p.[i]`
  | HPtrOffsetEN
  /// Ptr.read accessPath
  | HPtrReadEN
  /// Ptr.write accessPath value
  | HPtrWriteEN

  /// Use function as function pointer.
  | HNativeFunEN of FunSerial

  /// Embed some C expression to output.
  | HNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | HNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | HNativeDeclEN of nativeDeclCode: string

  /// Size of type. Argument is a type placeholder. The result type is int.
  | HSizeOfEN

  /// Name of type.
  | HTyPlaceholderEN

/// Expression in HIR.
[<NoEquality; NoComparison>]
type HExpr =
  | HLitExpr of Lit * Loc

  /// Name of variable.
  | HVarExpr of VarSerial * Ty * Loc

  /// Name of function.
  | HFunExpr of FunSerial * Ty * tyArgs: Ty list * Loc

  /// Name of variant.
  | HVariantExpr of VariantSerial * Ty * Loc

  | HPrimExpr of HPrim * Ty * Loc

  | HRecordExpr of HExpr option * fields: (Ident * HExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of cond: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `s.Length`
  | HNavExpr of HExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | HNodeExpr of HExprKind * HExpr list * Ty * Loc

  /// Evaluate a list of expressions and returns the last, e.g. `x1; x2; ...; y`.
  | HBlockExpr of HStmt list * HExpr

/// Statement in HIR.
[<NoEquality; NoComparison>]
type HStmt =
  | HExprStmt of HExpr
  | HLetValStmt of HPat * init: HExpr * Loc
  | HLetFunStmt of FunSerial * argPats: HPat list * body: HExpr * Loc

type VarMap = TreeMap<VarSerial, VarDef>
type VarNameMap = TreeMap<VarSerial, Ident>

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HModule =
  { DocId: DocId

    /// Non-static variables.
    Vars: VarMap

    Stmts: HStmt list }

/// Module. Variable info is reduced.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HModule2 =
  { DocId: DocId

    /// Non-static variables.
    Vars: VarNameMap

    Stmts: HStmt list }

/// HIR program. (project name, module name, decls) list.
type HProgram = HModule list

// -----------------------------------------------
// HirCtx
// -----------------------------------------------

/// Context of HIR program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HirCtx =
  { /// Next serial number.
    Serial: Serial

    StaticVars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    Tys: TreeMap<TySerial, TyDef> }
