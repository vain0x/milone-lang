/// # Fir
///
/// Functional IR for code transformation. (Wants to replace HIR.)
module rec MiloneLang.Fir

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers
open MiloneLang.Hir

module TMap = Std.StdMap
module S = Std.StdString

/// Identity. Unique number to identify such as variables.
type Id = int

// -----------------------------------------------
// Types
// -----------------------------------------------

/// Type constructor.
[<Struct; NoEquality; NoComparison>]
type FTk =
  | IntTk of intFlavor: IntFlavor
  | FloatTk of floatFlavor: FloatFlavor
  | BoolTk
  | CharTk
  | StrTk
  | ObjTk

  /// Ty args must be `[s; t]`.
  | FunTk

  | TupleTk

  /// Ty args must be `[t]`.
  | OptionTk
  | ListTk

  // FFI types.
  | VoidTk
  | NativePtrTk of nativePtrIsMut: IsMut
  | NativeFunTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | BoundTk of univId: Id
  | UnionTk of unionTy: TySerial
  | RecordTk of recordTy: TySerial

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type FTy = FTy of FTk * tyArgs: FTy list

/// Type, possibly polymorphic.
type FTyScheme = Id list * FTy

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FUnionTyDef =
  { Name: string
    Variants: FVariantDef list
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FRecordTyDef =
  { Name: string
    Fields: (string * Ty * Loc) list
    Loc: Loc }

// -----------------------------------------------
// Values
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FLocalVarDef = { Name: Ident; Ty: Ty; Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FFunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Body: FBody list
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FVariantDef =
  { Name: string
    UnionId: Id
    IsNewtype: bool
    HasPayload: bool
    PayloadTy: Ty
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FBody =
  { Stmts: FStmt list
    Expr: FExpr
    LocalVars: AssocMap<Id, VarDef>
    Loc: Loc }

/// Kind of HNodePat.
[<Struct; NoEquality; NoComparison>]
type FPatKind =
  | FNonePk
  | FSomePk
  | FNilPk
  | FConsPk
  | FVariantPk of variant: Id
  | FTuplePk
  | FBoxPk
  | FAbortPk

/// Pattern in HIR.
[<NoEquality; NoComparison>]
type FPat =
  | FLitPat of Lit * Loc
  | FDiscardPat of FTy * Loc
  | FVarPat of Vis * VarSerial * FTy * Loc
  | FVariantPat of VariantSerial * Ty * Loc
  | FNodePat of FPatKind * FPat list * Ty * Loc
  | FAsPat of FPat * VarSerial * Loc
  | FOrPat of FPat * FPat * Loc

/// Primitive in HIR.
[<RequireQualifiedAccess; Struct; NoComparison>]
type FPrim =
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
  | NativeFun
  | NativeCast
  | NativeExpr
  | NativeStmt
  | NativeDecl
  | SizeOfVal
  | PtrRead
  | PtrWrite

[<Struct; NoEquality; NoComparison>]
type FExprKind =
  | FAbortEk
  | FMinusEk

  /// Args can be partial or empty.
  | FCallFunEk of funId: FunSerial

  /// Args: `[]` or `[payload]`.
  | FVariantEk of variantId: VariantSerial

  | FIndexEk
  | FSliceEk

  /// Indirect call to closure.
  /// Args: `[callee, ...args]`. Perhaps partial app.
  | HCallClosureEk

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
type FExpr =
  | FLitExpr of Lit * Loc
  | FVarExpr of VarSerial * FTy * Loc
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
