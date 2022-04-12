/// # TirTypes
///
/// Provides public types about typed intermediate representation (TIR).
module rec MiloneSyntaxTypes.TirTypes

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open Std.StdMap

/// Level.
///
/// Top-level is 0.
/// Inside of init part of `let`, level is incremented by 1.
///
/// For example, in `let none = None: 'a option in none`,
/// level of `'a` is 1.
///
/// In `let _ = (let  = None: 'b option in ()) in ()`,
/// level of `'b` is 2.
///
/// Only one exception: recursive function has level higher by 1.
type Level = int

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

/// Type constructor.
[<NoEquality; NoComparison>]
type Tk =
  | ErrorTk of errorLoc: Loc

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
  | ListTk

  // Special types.
  /// Ty args must be `[t]`.
  | LinearTk
  | VoidPtrTk of voidPtrIsMut: IsMut
  | NativePtrTk of nativePtrIsMut: IsMut
  | NativeFunTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | MetaTk of metaTy: TySerial * metaLoc: Loc
  | UnivTk of univTy: TySerial * name: string * univLoc: Loc
  | SynonymTk of synonymTy: TySerial
  | UnionTk of unionTy: TySerial * Loc option
  | RecordTk of recordTy: TySerial * Loc option

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

/// Trait, a constraint about types.
// NOTE: `trait` is a reserved word in F#.
[<NoEquality; NoComparison>]
type Trait =
  /// The type supports `+`.
  | AddTrait of Ty

  /// The type supports `=`.
  | EqualTrait of Ty

  /// The type supports `<`.
  | CompareTrait of Ty

  /// For `l: lTy, r: rTy`, `l.[r]` is allowed.
  | IndexTrait of lTy: Ty * rTy: Ty * resultTy: Ty

  /// Integer type. Defaults to int.
  | IsIntTrait of Ty

  /// Integer or float type. Defaults to int.
  | IsNumberTrait of Ty

  /// Type supports conversion to char.
  | ToCharTrait of Ty

  /// Type supports conversion to integer.
  | ToIntTrait of Ty

  | ToFloatTrait of Ty

  /// Type can be applied to `string` function.
  | ToStringTrait of Ty

  | PtrTrait of Ty

  /// Two pointer types of the same kind. First one is const, second one is mutable.
  | PtrDualTrait of constTy: Ty * mutTy: Ty

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  | UnivTyDef of Ident * Loc

  | SynonymTyDef of Ident * tyArgs: TySerial list * Ty * Loc

  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * tyArgs: TySerial list * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

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
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Abi: FunAbi
    Linkage: Linkage

    /// Represents a context of function (in reversed order.) Function name is finally prefixed to be unique.
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

/// Context of TIR program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TirCtx =
  { /// Last serial number.
    Serial: Serial

    StaticVars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    Tys: TreeMap<TySerial, TyDef>
    Logs: (Log * Loc) list }

/// Kind of TNodePat.
[<NoEquality; NoComparison>]
type TPatKind =
  /// `[]`.
  | TNilPN

  /// `p1 :: p2`.
  | TConsPN

  /// `p1 p2`.
  | TAppPN

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

  // list:
  | Nil
  | Cons

  // union:
  | Discriminant

  // effects:
  | Exit
  | Assert
  | Printfn
  | InRegion
  | Acquire
  | Dispose
  | NativeFun
  | NativeCast
  | NativeExpr
  | NativeStmt
  | NativeDecl
  | NullPtr
  | PtrAsConst
  | PtrAsMutable
  | PtrRead
  | PtrWrite

[<NoEquality; NoComparison>]
type TExprKind =
  /// `-x`.
  | TMinusEN

  | TAppEN

  /// Type ascription `x : 'x`.
  | TAscribeEN

  /// `s.[i]`
  | TIndexEN

  /// `s.[l .. r]`
  | TSliceEN

  /// Direct call to native fun.
  | TCallNativeEN of funName: string

  /// Tuple constructor, e.g. `x, y, z`.
  | TTupleEN

  | TDiscriminantEN of VariantSerial

  /// Use function as function pointer.
  | TNativeFunEN of FunSerial

  /// Embed some C expression to output.
  | TNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | TNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | TNativeDeclEN of nativeDeclCode: string

  /// Size of type. Argument is a type placeholder. The result type is int.
  | TSizeOfValEN

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

  /// E.g. `List.isEmpty`, `str.Length`
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
  { DocId: DocId

    /// Non-static variables.
    Vars: VarMap

    Stmts: TStmt list }

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

  | UnimplGenericTyError
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
  | ArityMismatch of actual: string * expected: string
  | Error of string
