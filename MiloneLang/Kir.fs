module rec MiloneLang.Kir

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir

// -----------------------------------------------
// KIR types
// -----------------------------------------------

// KIR is continuation passing style (CPS) intermediate representation.

type JointSerial = FunSerial

/// Primitive in KIR.
///
/// Number of args/results/conts depends on the kind of prim.
/// Prim signature is written as `N/M/K` denoting to use N args, M results, K conts.
[<Struct>]
[<NoEquality; NoComparison>]
type KPrim =
  // Scalar arithmetic: 2/1/1.
  | KAddPrim
  | KSubPrim
  | KMulPrim
  | KDivPrim
  | KModPrim

  // Scar bit operation: 2/1/1.
  | KBitAndPrim
  | KBitOrPrim
  | KBitXorPrim
  | KLeftShiftPrim
  | KRightShiftPrim

  // Scalar comparison:
  /// 2/0/2. The first cont is used if two args equal; or the second otherwise.
  | KEqualPrim

  /// 2/0/2. The first cont is used if the first arg is less than the second; or the second otherwise.
  | KLessPrim

  // Bool:
  /// 1/1/1.
  | KNotPrim

  // int:
  | KIntComparePrim

  // String:
  /// 2/1/1.
  | KStrAddPrim

  /// 2/1/1.
  | KStrComparePrim

  /// 2/1/1.
  | KStrIndexPrim

  /// 1/1/1.
  | KStrLengthPrim

  /// 2/1/1.
  | KStrGetSlicePrim

  // List, option:
  /// 2/1/1.
  | KConsPrim

  /// 1/1/1.
  | KSomePrim

  // Tuple:
  /// N/1/1, where N is number of fields.
  | KTuplePrim

  // Union:
  /// 1/1/1.
  | KVariantPrim

  // Function, closure:
  /// 2/1/1.
  | KClosurePrim

  /// (1+A)/1/1, where A is arity.
  | KCallProcPrim

  /// (1+A)/1/1, where A is arity.
  | KCallClosurePrim

  // obj:
  /// 1/1/1.
  | KBoxPrim

  /// 1/1/1.
  | KUnboxPrim

  // Others:
  /// 1/0/0.
  | KExitPrim

  /// 1/0/1.
  | KAssertPrim

  /// 1/1/1.
  | KCharPrim

  /// 1/1/1.
  // FIXME: signedness, precision
  | KIntPrim

  /// 1/1/1.
  | KUIntPrim

  /// 1/1/1.
  | KStringPrim

  /// (1+A)/0/1, where A is arity.
  | KPrintfnPrim

  /// 1/1/1.
  | KInRegionPrim

  /// A/1/1, where A is arity.
  | KNativeFunPrim of Ident * Arity

/// Represents an access path to content of data (tuple or union).
[<NoEquality; NoComparison>]
type KPath =
  /// The value itself.
  | KSelfPath

  | KHeadPath of Loc
  | KTailPath of Loc

  /// N'th field of tuple.
  | KFieldPath of int * Loc

  /// Tag of union.
  | KTagPath of Loc

  /// Payload of union.
  | KPayloadPath of VariantSerial * Loc

/// Term (expression) in KIR.
[<NoEquality; NoComparison>]
type KTerm =
  | KLitTerm of Lit * Loc
  | KVarTerm of VarSerial * Ty * Loc
  | KFunTerm of FunSerial * Ty * Loc
  | KVariantTerm of VariantSerial * Ty * Loc

  /// Tag of variant. An integer ID of the variant in union.
  | KTagTerm of VariantSerial * Loc

  | KLabelTerm of FunSerial * Ty * Loc

  | KNilTerm of itemTy: Ty * Loc
  | KNoneTerm of itemTy: Ty * Loc
  | KUnitTerm of Loc

/// Node (statement) in KIR.
[<NoEquality; NoComparison>]
type KNode =
  /// Jump to joint.
  | KJumpNode of JointSerial * args: KTerm list * Loc

  /// Return from the current fun.
  | KReturnNode of FunSerial * args: KTerm list * Loc

  /// Switch to joint based on the value of `cond`.
  // | KSwitchNode of cond: KTerm * arms: (KTerm * KNode) list * Loc

  /// Assign some part of data to var.
  ///
  /// `path` indicates which part of data is extracted.
  /// For example, if term=`[2; 3]` and path=`KHeadPath` then 2 is set to result.
  ///
  /// Note that simple assignment (`let x = a`) is a selection with path=`KSelfPath`.
  | KSelectNode of KTerm * path: KPath * result: VarSerial * cont: KNode * Loc

  /// Execution of primitive.
  /// Do something using args, binds values to results, and then jump to one of continuations (if continue).
  | KPrimNode of KPrim * args: KTerm list * results: VarSerial list * conts: KNode list * Loc

  /// Declaration of mutually recursive joints.
  | KJointNode of KJointBinding list * cont: KNode * Loc

/// Declaration of a joint.
///
/// Joint is a function-like thing that can be called inside of single fun (i.e. not escaping) and never returns once called.
///
/// Since joint doesn't escape from the parent fun, it may use local vars.
///
/// After compiled to C language, a joint is represented as a *label* of block in C language. Calling a joint is a *goto* with some assignments to local vars.
[<NoEquality; NoComparison>]
type KJointBinding = KJointBinding of jointSerial: JointSerial * args: VarSerial list * body: KNode * Loc

/// Definition of a fun.
[<NoEquality; NoComparison>]
type KFunBinding = KFunBinding of funSerial: FunSerial * args: VarSerial list * body: KNode * Loc

/// Root node of KIR.
[<NoEquality; NoComparison>]
type KRoot = KRoot of KFunBinding list

[<NoEquality; NoComparison>]
type KVarDef =
  | KLitVarDef of Lit
  | KSelectVarDef of KTerm * KPath
