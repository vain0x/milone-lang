/// # TirTypes
///
/// Provides public types about typed intermediate representation (TIR).
module rec MiloneSyntax.TirTypes

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open Std.StdMap

type TName = Ident * Loc

// -----------------------------------------------
// TIR types
// -----------------------------------------------

type TySerial = int

[<Struct; NoComparison>]
type VarSerial = VarSerial of Serial

/// Serial number of functions.
[<Struct; NoComparison>]
type FunSerial = FunSerial of Serial

/// Serial number of variants.
[<Struct; NoComparison>]
type VariantSerial = VariantSerial of Serial

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NameLocPair = { Name: string; Loc: Loc }

/// Type constructor.
[<NoEquality; NoComparison>]
type Tk =
  | ErrorTk of errorLoc: Loc

  | IntTk of intFlavor: IntFlavor
  | FloatTk of floatFlavor: FloatFlavor
  | BoolTk
  | CharTk
  | StringTk
  | NeverTk
  | ObjTk

  /// Type arguments must be `[ s; t ]`.
  | FunTk

  | TupleTk

  /// Type arguments must be `[ t ]`.
  | ListTk

  // Special types.
  /// Type arguments must be `[ t ]`.
  | OwnTk
  /// Type arguments must be `[ t ]`.
  | VoidPtrTk of voidPtrIsMut: IsMut
  /// Type arguments must be `[ t ]`.
  | NativePtrTk of mode: RefMode
  /// Type arguments must be `paramTys @ [ resultTy ]`.
  | FunPtrTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | MetaTk of metaTy: TySerial * metaLoc: Loc
  | UnivTk of univTy: TySerial * NameLocPair
  | SynonymTk of synonymTy: TySerial * NameLocPair
  | UnionTk of unionTy: TySerial * NameLocPair
  | RecordTk of recordTy: TySerial * NameLocPair
  | OpaqueTk of opaqueTy: TySerial * NameLocPair

  /// `_` in ascription.
  | InferTk of Loc

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type Ty =
  /// Type application.
  | Ty of Tk * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct; NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

[<Struct; NoEquality; NoComparison>]
type BoundedTyScheme = BoundedTyScheme of tyVars: TySerial list * Ty * Trait list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type UnaryTrait =
  /// Support `+` operator.
  | Add
  /// Support `=` operator.
  | Equal
  /// Support `compare` function.
  | Compare
  /// Integer-like types. Defaults to `int`.
  | IntLike
  /// Types like integers or float. Defaults to `float`.
  | NumberLike
  /// Types convertible to an integer.
  | ToInt of _flavor: IntFlavor
  /// Types convertible to a float.
  | ToFloat
  /// Types convertible to `char`.
  | ToChar
  /// Types convertible to `string`.
  | ToString
  /// Pointer-like types.
  | PtrLike
  /// Types whose runtime representation has the same size as pointer types.
  | PtrSize

/// Trait, a constraint about types.
// NOTE: `trait` is a reserved word in F#.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Trait =
  | Unary of UnaryTrait * Ty

  /// Support index operator. (`t = l.[r]`)
  | Index of lTy: Ty * rTy: Ty * tTy: Ty

  /// Types that can be cast from srcTy to destTy.
  | PtrCast of srcTy: Ty * destTy: Ty

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  | UnivTyDef of Ident * Loc

  | SynonymTyDef of Ident * tyArgs: TySerial list * Ty * Loc

  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * tyArgs: TySerial list * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

  | OpaqueTyDef of Ident * Loc

/// Definition of named value.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VarDef =
  { Name: Ident
    IsStatic: IsStatic
    Linkage: Linkage
    Ty: Ty
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FunDef =
  {
    Name: Ident
    Arity: Arity
    Ty: TyScheme
    Abi: FunAbi
    Linkage: Linkage

    /// Whether it's declared in a module, rather than module.
    Nonlocal: bool

    /// Represents a context of function (in reversed order.) Function name is finally prefixed to be unique.
    Prefix: string list

    Loc: Loc
  }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VariantDef =
  {
    Name: Ident
    UnionTySerial: TySerial

    /// Whether this is the only variant of the union.
    IsNewtype: bool

    HasPayload: bool
    PayloadTy: Ty
    Loc: Loc
  }

/// Context of TIR program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TirCtx =
  {
    /// Last serial number.
    Serial: Serial

    StaticVars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    Tys: TreeMap<TySerial, TyDef>
    Logs: (Log * Loc) list
  }

/// Kind of TNodePat.
[<NoEquality; NoComparison>]
type TPatKind =
  /// `[]`.
  | TNilPN

  /// `p1 :: p2`.
  | TConsPN

  /// `Variant p1`.
  | TVariantAppPN of variantApp: VariantSerial

  /// `p1, p2, ..., pN` or `()`.
  | TTuplePN

  /// `p1.r`
  | TNavPN of navR: Ident

  /// `p1: ty`
  | TAscribePN

  /// Generated after compile error occurred while processing a pattern.
  | TAbortPN

/// Pattern.
[<NoEquality; NoComparison>]
type TPat =
  | TLitPat of Lit * Loc

  /// `_`.
  | TDiscardPat of Ty * Loc

  /// Variable pattern.
  | TVarPat of Vis * VarSerial * Ty * Loc

  /// Variant name pattern.
  | TVariantPat of VariantSerial * Ty * Loc

  | TNodePat of TPatKind * TPat list * Ty * Loc

  | TAsPat of TPat * VarSerial * Loc

  /// Disjunction.
  | TOrPat of TPat * TPat * Loc

/// Primitive.
[<RequireQualifiedAccess; Struct; NoComparison>]
type TPrim =
  // operator:
  | Not
  | BitNot
  | Add
  | Subtract
  | Multiply
  | Divide
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
  | ToChar
  | ToString
  | Box
  | Unbox

  // string:
  | StringLength

  // list:
  | Nil
  | Cons

  // union:
  | Discriminant

  // effects:
  | Assert
  | Printfn
  | OwnAcquire
  | OwnRelease
  | NativeFun
  | NativeCast
  | NativeExpr
  | NativeStmt
  | NativeDecl
  | NullPtr
  | PtrSelect
  | PtrRead
  | PtrWrite
  | PtrCast
  | PtrInvalid
  | PtrAsIn
  | PtrAsNative
  | PtrDistance
  | FunPtrInvoke

[<NoEquality; NoComparison>]
type TExprKind =
  /// `-x`.
  | TMinusEN

  // `&&x`.
  | TPtrOfEN

  | TFunPtrOfEN

  | TAppEN

  /// Type ascription `x : 'x`.
  | TAscribeEN

  /// `s.[i]`
  | TIndexEN

  /// `s.[l .. r]`
  | TSliceEN

  /// This is a marker of a never-returning functional application.
  | TCatchNeverEN

  /// Direct call to native fun.
  | TCallNativeEN of funName: string

  /// Tuple constructor, e.g. `x, y, z`.
  | TTupleEN

  | TDiscriminantEN of VariantSerial

  /// `Ptr.select p.[i]`
  | TPtrOffsetEN
  /// Ptr.read accessPath
  | TPtrReadEN
  /// Ptr.write accessPath value
  | TPtrWriteEN

  | TFunPtrInvokeEN

  /// Embed some C expression to output.
  | TNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | TNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | TNativeDeclEN of nativeDeclCode: string

  /// Size of type. Argument is a type placeholder. The result type is int.
  | TSizeOfEN

  /// Name of type.
  | TTyPlaceholderEN

  /// Generated after compile error occurred while processing an expression.
  | TAbortEN

/// Expression.
[<NoEquality; NoComparison>]
type TExpr =
  | TLitExpr of Lit * Loc

  /// Name of variable.
  | TVarExpr of VarSerial * Ty * Loc

  /// Name of function.
  | TFunExpr of FunSerial * Ty * Loc

  /// Name of variant.
  | TVariantExpr of VariantSerial * Ty * Loc

  | TPrimExpr of TPrim * Ty * Loc

  | TRecordExpr of TExpr option * fields: (Ident * TExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | TMatchExpr of cond: TExpr * arms: (TPat * TExpr * TExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `s.Length`
  | TNavExpr of TExpr * TName * Ty * Loc

  /// Some built-in operation.
  | TNodeExpr of TExprKind * TExpr list * Ty * Loc

  /// Statements and last expression.
  ///
  /// - Statements might define symbols locally for the last expression.
  | TBlockExpr of TStmt list * last: TExpr

/// Statement.
[<NoEquality; NoComparison>]
type TStmt =
  | TExprStmt of TExpr
  | TLetValStmt of TPat * TExpr * Loc
  | TLetFunStmt of FunSerial * IsRec * Vis * args: TPat list * body: TExpr * Loc

  /// If recursive, local definitions are mutually recursive.
  | TBlockStmt of IsRec * TStmt list

type private VarMap = TreeMap<VarSerial, VarDef>

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TModule =
  {
    DocId: DocId

    /// Non-static variables.
    Vars: VarMap

    Stmts: TStmt list
  }

type TProgram = TModule list

// -----------------------------------------------
// Errors
// -----------------------------------------------

[<NoEquality; NoComparison>]
type NameResLog =
  // in expression
  | UndefinedValueError of name: string
  | TyUsedAsValueError

  // in pat
  | VariantAppPatArityError
  | UnresolvedNavPatError
  | IllegalOrPatError
  | OrPatInconsistentBindingError
  | VarNameConflictError

  // in type
  | UndefinedTyError of name: string
  | TyArityError of name: string * actual: int * expected: int
  | ModuleUsedAsTyError of name: string

  // other
  | ModulePathNotFoundError

  | UnimplOrPatBindingError
  | UnimplTyArgListError

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type TyUnifyLog =
  | SelfRec
  | Mismatch

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type Log =
  | NameResLog of NameResLog
  | LiteralRangeError
  | IrrefutablePatNonExhaustiveError
  | TyUnify of TyUnifyLog * Ty * Ty
  | TyBoundError of Trait
  | TySynonymCycleError
  | RedundantFieldError of ty: Ident * field: Ident
  | MissingFieldsError of ty: Ident * fields: Ident list
  | RecordTypeNotInferred
  | RecordFieldNotFound of field: Ident * recordTy: Ty
  | FieldNotFound of field: Ident
  | MissingPayloadPat
  | ArityMismatch of actual: string * expected: string

  // Illegal use of primitives.
  | UseOfDiscriminant
  | UseOfPrintfn
  | UseOfNativeFun
  | UseOfNativeExpr
  | UseOfNativeStmt
  | UseOfNativeDecl
  | PrimRequireParam

  | Error of string
