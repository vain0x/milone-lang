/// # Hir
///
/// Provides types and functions for high-level intermediate representation (HIR).
///
/// HIR is functional-style. Similar to milone-lang's syntax.
///
/// ## Lifecycle
///
/// HIR is generated in `AstToHir` for each file
/// and all modules of a project are *concatenated* in `AstBundle`.
///
/// Most of analysis (for error reporting and soundness)
/// and transformations (for code generation) are performed on it.
///
/// Finally HIR is converted to MIR in `MirGen`.
///
/// See `Cli.fs` for details.
module rec MiloneTranslation.Hir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util

module TMap = MiloneStd.StdMap
module S = MiloneStd.StdString

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

[<Struct>]
[<NoEquality; NoComparison>]
type NameCtx = NameCtx of map: AssocMap<Serial, Ident> * lastSerial: Serial

/// Type constructor.
[<Struct; NoEquality; NoComparison>]
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
  | OptionTk
  | ListTk

  // FFI types.
  | VoidTk
  | NativePtrTk of nativePtrIsMut: IsMut
  | NativeFunTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | MetaTk of metaTy: TySerial * metaLoc: Loc
  | SynonymTk of synonymTy: TySerial
  | UnionTk of unionTy: TySerial
  | RecordTk of recordTy: TySerial

  /// Unresolved type. Generated in AstToHir, resolved in NameRes.
  | UnresolvedTk of quals: Serial list * unresolvedSerial: Serial
  | UnresolvedVarTk of unresolvedVarTySerial: (Serial * Loc)

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type Ty =
  /// Type application.
  | Ty of Tk * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct>]
[<NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

/// Type specification.
[<Struct>]
[<NoEquality; NoComparison>]
type TySpec = TySpec of Ty * Trait list

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

/// Type declaration.
[<NoEquality; NoComparison>]
type TyDecl =
  | TySynonymDecl of Ty * Loc

  /// Union type.
  /// Variants: (ident, serial, has-payload, payload type).
  | UnionTyDecl of Ident * variants: (Ident * VariantSerial * bool * Ty) list * Loc

  | RecordTyDecl of Ident * fields: (Ident * Ty * Loc) list * Loc

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ty

  | UniversalTyDef of Ident * Loc

  | SynonymTyDef of Ident * TySerial list * Ty * Loc

  | UnionTyDef of Ident * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * Loc

[<Struct; NoComparison>]
type ModuleTySerial = ModuleTySerial of Serial

//// Module is a type so that it can be used as namespace.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleTyDef = { Name: Ident; Loc: Loc }

[<Struct; NoComparison>]
type ModuleSynonymSerial = ModuleSynonymSerial of Serial

//// Module is a type so that it can be used as namespace.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleSynonymDef =
  { Name: Ident
    // Not used.
    Bound: ModuleTySerial list
    Loc: Loc }

/// Definition of named value in HIR.
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

[<Struct; NoComparison>]
type ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial

[<Struct; NoComparison>]
type TySymbol =
  | MetaTySymbol of tySerial: TySerial
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial

/// Kind of HNodePat.
[<Struct; NoEquality; NoComparison>]
type HPatKind =
  /// `[]`.
  | HNilPN

  /// `p1 :: p2`.
  | HConsPN

  | HNonePN

  /// `Some`.
  | HSomePN

  /// `p1 p2`.
  | HAppPN

  /// `Some p1`.
  | HSomeAppPN

  /// `Variant p1`.
  | HVariantAppPN of variantApp: VariantSerial

  /// `p1, p2, ..., pN` or `()`.
  | HTuplePN

  /// `p1.r`
  | HNavPN of navR: Ident

  /// `p1: ty`
  | HAscribePN

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
  | NativeFun
  | NativeCast
  | NativeExpr
  | NativeStmt
  | NativeDecl
  | SizeOfVal
  | PtrRead
  | PtrWrite

[<Struct; NoEquality; NoComparison>]
type HExprKind =
  | HAbortEN

  /// `-x`.
  | HMinusEN

  | HAppEN

  /// `..`.
  ///
  /// Every occurrence of this is currently error
  /// because valid use (`s.[l..r]`) gets rewritten in AstToHir.
  | HRangeEN

  /// Type ascription `x : 'x`.
  | HAscribeEN

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

  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | HOpenExpr of Ident list * Loc
  | HModuleExpr of ModuleTySerial * body: HExpr list * Loc
  | HModuleSynonymExpr of ModuleSynonymSerial * path: Ident list * Loc

/// HIR program. (project name, module name, decls) list.
type HProgram = (string * string * HExpr list) list

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type MonoMode =
  | Monify
  | RemoveGenerics

// -----------------------------------------------
// Errors
// -----------------------------------------------

[<NoEquality; NoComparison>]
type NameResLog =
  // in expression
  | UndefinedValueError of name: string
  | TyUsedAsValueError

  // in pat
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
  | OtherNameResLog of msg: string

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

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyError loc = Ty(ErrorTk loc, [])

/// Placeholder. No type info in the parsing phase.
let noTy = tyError noLoc

let tyInt = Ty(IntTk(IntFlavor(Signed, I32)), [])

let tyBool = Ty(BoolTk, [])

let tyFloat = Ty(FloatTk F64, [])

let tyChar = Ty(CharTk, [])

let tyStr = Ty(StrTk, [])

let tyObj = Ty(ObjTk, [])

let tyTuple tys = Ty(TupleTk, tys)

let tyOption ty = Ty(OptionTk, [ ty ])

let tyList ty = Ty(ListTk, [ ty ])

let tyFun sourceTy targetTy = Ty(FunTk, [ sourceTy; targetTy ])

let tyConstPtr itemTy = Ty(NativePtrTk IsConst, [ itemTy ])

let tyNativePtr itemTy = Ty(NativePtrTk IsMut, [ itemTy ])

let tyNativeFun paramTys resultTy =
  Ty(NativeFunTk, List.append paramTys [ resultTy ])

let tyUnit = tyTuple []

let tyMeta serial loc = Ty(MetaTk(serial, loc), [])

let tySynonym tySerial tyArgs = Ty(SynonymTk tySerial, tyArgs)

let tyUnion tySerial = Ty(UnionTk tySerial, [])

let tyRecord tySerial = Ty(RecordTk tySerial, [])

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let moduleTySerialToInt (ModuleTySerial serial) = serial

let moduleTySerialCompare l r =
  moduleTySerialToInt l - moduleTySerialToInt r

let moduleSynonymSerialToInt (ModuleSynonymSerial serial) = serial

let moduleSynonymSerialCompare l r =
  moduleSynonymSerialToInt l
  - moduleSynonymSerialToInt r

let tyDefToName tyDef =
  match tyDef with
  | MetaTyDef _ -> "{bound}"
  | UniversalTyDef (name, _) -> name
  | SynonymTyDef (name, _, _, _) -> name
  | UnionTyDef (name, _, _) -> name
  | RecordTyDef (name, _, _) -> name

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varSerialToInt (VarSerial serial) = serial

let varSerialCompare l r =
  compare (varSerialToInt l) (varSerialToInt r)

let funSerialToInt (FunSerial serial) = serial

let funSerialCompare l r =
  compare (funSerialToInt l) (funSerialToInt r)

let variantSerialToInt (VariantSerial serial) = serial

let variantSerialCompare l r =
  compare (variantSerialToInt l) (variantSerialToInt r)

let variantDefToVariantTy (variantDef: VariantDef) : Ty =
  let unionTy = tyUnion variantDef.UnionTySerial

  if variantDef.HasPayload then
    tyFun variantDef.PayloadTy unionTy
  else
    unionTy

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litToTy (lit: Lit) : Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | FloatLit _ -> tyFloat
  | CharLit _ -> tyChar
  | StrLit _ -> tyStr

// -----------------------------------------------
// Primitives (HIR)
// -----------------------------------------------

let primFromIdent ident =
  match ident with
  | "not" -> HPrim.Not |> Some

  | "exit" -> HPrim.Exit |> Some

  | "assert" -> HPrim.Assert |> Some

  | "box" -> HPrim.Box |> Some

  | "unbox" -> HPrim.Unbox |> Some

  | "printfn" -> HPrim.Printfn |> Some

  | "compare" -> HPrim.Compare |> Some

  | "char" -> HPrim.Char |> Some

  | "int"
  | "int32" -> HPrim.ToInt(IntFlavor(Signed, I32)) |> Some
  | "uint"
  | "uint32" -> HPrim.ToInt(IntFlavor(Unsigned, I32)) |> Some
  | "sbyte"
  | "int8" -> HPrim.ToInt(IntFlavor(Signed, I8)) |> Some
  | "byte"
  | "uint8" -> HPrim.ToInt(IntFlavor(Unsigned, I8)) |> Some

  | "int16" -> HPrim.ToInt(IntFlavor(Signed, I16)) |> Some
  | "int64" -> HPrim.ToInt(IntFlavor(Signed, I64)) |> Some
  | "nativeint" -> HPrim.ToInt(IntFlavor(Signed, IPtr)) |> Some
  | "uint16" -> HPrim.ToInt(IntFlavor(Unsigned, I16)) |> Some
  | "uint64" -> HPrim.ToInt(IntFlavor(Unsigned, I64)) |> Some
  | "unativeint" -> HPrim.ToInt(IntFlavor(Unsigned, IPtr)) |> Some

  | "float" -> HPrim.ToFloat F64 |> Some
  | "float32" -> HPrim.ToFloat F32 |> Some

  | "string" -> HPrim.String |> Some

  | "None" -> HPrim.OptionNone |> Some

  | "Some" -> HPrim.OptionSome |> Some

  | "inRegion" -> HPrim.InRegion |> Some

  | "__nativeFun" -> HPrim.NativeFun |> Some
  | "__nativeCast" -> HPrim.NativeCast |> Some
  | "__nativeExpr" -> HPrim.NativeExpr |> Some
  | "__nativeStmt" -> HPrim.NativeStmt |> Some
  | "__nativeDecl" -> HPrim.NativeDecl |> Some
  | "__sizeOfVal" -> HPrim.SizeOfVal |> Some
  | "__ptrRead" -> HPrim.PtrRead |> Some
  | "__ptrWrite" -> HPrim.PtrWrite |> Some

  | _ -> None

let primToTySpec prim =
  let meta id = tyMeta id noLoc
  let mono ty = TySpec(ty, [])
  let poly ty traits = TySpec(ty, traits)

  match prim with
  | HPrim.Add ->
      let addTy = meta 1
      poly (tyFun addTy (tyFun addTy addTy)) [ AddTrait addTy ]

  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Modulo ->
      let ty = meta 1
      poly (tyFun ty (tyFun ty ty)) [ IsNumberTrait ty ]

  | HPrim.BitAnd
  | HPrim.BitOr
  | HPrim.BitXor ->
      let ty = meta 1
      poly (tyFun ty (tyFun ty ty)) [ IsIntTrait ty ]

  | HPrim.LeftShift
  | HPrim.RightShift ->
      let ty = meta 1
      poly (tyFun ty (tyFun tyInt ty)) [ IsIntTrait ty ]

  | HPrim.Equal ->
      let argTy = meta 1
      poly (tyFun argTy (tyFun argTy tyBool)) [ EqualTrait argTy ]

  | HPrim.Less ->
      let compareTy = meta 1
      poly (tyFun compareTy (tyFun compareTy tyBool)) [ CompareTrait compareTy ]

  | HPrim.Compare ->
      let compareTy = meta 1
      poly (tyFun compareTy (tyFun compareTy tyInt)) [ CompareTrait compareTy ]

  | HPrim.Nil ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.Cons ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy (tyFun listTy listTy)) []

  | HPrim.OptionNone ->
      let itemTy = meta 1
      poly (tyOption itemTy) []

  | HPrim.OptionSome ->
      let itemTy = meta 1
      let listTy = tyOption itemTy
      poly (tyFun itemTy listTy) []

  | HPrim.Not -> mono (tyFun tyBool tyBool)

  | HPrim.Exit ->
      let resultTy = meta 1
      poly (tyFun tyInt resultTy) []

  | HPrim.Assert -> mono (tyFun tyBool tyUnit)

  | HPrim.Box ->
      let itemTy = meta 1
      poly (tyFun itemTy tyObj) []

  | HPrim.Unbox ->
      let itemTy = meta 1
      poly (tyFun tyObj itemTy) []

  | HPrim.Char ->
      let srcTy = meta 1
      poly (tyFun srcTy tyChar) [ ToCharTrait srcTy ]

  | HPrim.ToInt flavor ->
      let toIntTy = meta 1
      let resultTy = Ty(IntTk flavor, [])
      poly (tyFun toIntTy resultTy) [ ToIntTrait toIntTy ]

  | HPrim.ToFloat flavor ->
      let srcTy = meta 1
      let resultTy = Ty(FloatTk flavor, [])
      poly (tyFun srcTy resultTy) [ ToFloatTrait srcTy ]

  | HPrim.String ->
      let toStrTy = meta 1
      poly (tyFun toStrTy tyStr) [ ToStringTrait toStrTy ]

  | HPrim.StrLength -> mono (tyFun tyStr tyInt)

  | HPrim.InRegion -> mono (tyFun (tyFun tyUnit tyInt) tyInt)

  | HPrim.Printfn
  | HPrim.NativeFun
  | HPrim.NativeExpr
  | HPrim.NativeStmt
  | HPrim.NativeDecl ->
      // Incorrect use of this primitive is handled as error before instantiating its type.
      unreachable ()

  | HPrim.NativeCast ->
      let srcTy = meta 1
      let destTy = meta 2
      poly (tyFun srcTy destTy) [ PtrTrait srcTy; PtrTrait destTy ]

  | HPrim.SizeOfVal -> poly (tyFun (meta 1) tyInt) []

  | HPrim.PtrRead ->
      // __constptr<'p> -> int -> 'a
      let valueTy = meta 1
      poly (tyFun (tyConstPtr valueTy) (tyFun tyInt valueTy)) []

  | HPrim.PtrWrite ->
      // nativeptr<'a> -> int -> 'a -> unit
      let valueTy = meta 1
      poly (tyFun (tyNativePtr valueTy) (tyFun tyInt (tyFun valueTy tyUnit))) []

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let hpAbort ty loc = HNodePat(HAbortPN, [], ty, loc)

let hpTuple itemPats loc =
  let tupleTy = itemPats |> List.map patToTy |> tyTuple
  HNodePat(HTuplePN, itemPats, tupleTy, loc)

let patExtract (pat: HPat) : Ty * Loc =
  match pat with
  | HLitPat (lit, a) -> litToTy lit, a
  | HDiscardPat (ty, a) -> ty, a
  | HVarPat (_, _, ty, a) -> ty, a
  | HVariantPat (_, ty, a) -> ty, a

  | HNodePat (_, _, ty, a) -> ty, a
  | HAsPat (bodyPat, _, a) -> patToTy bodyPat, a
  | HOrPat (l, _, a) -> patToTy l, a

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat = pat |> patExtract |> snd

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat) : HPat =
  let rec go pat =
    match pat with
    | HLitPat (lit, a) -> HLitPat(lit, g a)
    | HDiscardPat (ty, a) -> HDiscardPat(f ty, g a)
    | HVarPat (vis, serial, ty, a) -> HVarPat(vis, serial, f ty, g a)
    | HVariantPat (serial, ty, a) -> HVariantPat(serial, f ty, g a)

    | HNodePat (kind, args, ty, a) -> HNodePat(kind, List.map go args, f ty, g a)
    | HAsPat (bodyPat, serial, a) -> HAsPat(go bodyPat, serial, g a)
    | HOrPat (l, r, a) -> HOrPat(go l, go r, g a)

  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVarPat _
    | HVariantPat _ -> [ pat ]

    | HNodePat (kind, argPats, ty, loc) ->
        argPats
        |> doNormalizePats
        |> List.map (fun itemPats -> HNodePat(kind, itemPats, ty, loc))

    | HAsPat (bodyPat, serial, loc) ->
        go bodyPat
        |> List.map (fun bodyPat -> HAsPat(bodyPat, serial, loc))

    | HOrPat (l, r, _) -> List.append (go l) (go r)

  go pat

let private doNormalizePats pats =
  match pats with
  | [] -> [ [] ]

  | headPat :: tailPats ->
      let headPats = patNormalize headPat

      doNormalizePats tailPats
      |> List.collect
           (fun tailPats ->
             headPats
             |> List.map (fun headPat -> headPat :: tailPats))

/// Gets whether a pattern is clearly exhaustive, that is,
/// pattern matching on it always succeeds (assuming type check is passing).
let patIsClearlyExhaustive isNewtypeVariant pat =
  let rec go pat =
    match pat with
    | HLitPat _ -> false

    | HDiscardPat _
    | HVarPat _ -> true

    | HVariantPat (variantSerial, _, _) -> isNewtypeVariant variantSerial

    | HNodePat (kind, argPats, _, _) ->
        match kind, argPats with
        | HVariantAppPN variantSerial, [ payloadPat ] -> isNewtypeVariant variantSerial && go payloadPat

        | HAbortPN, _ -> true

        | HNilPN, _
        | HConsPN, _
        | HNonePN, _
        | HSomePN, _
        | HSomeAppPN, _
        | HAppPN, _
        | HVariantAppPN _, _
        | HNavPN _, _ -> false

        | HTuplePN, _
        | HAscribePN, _
        | HBoxPN, _ -> argPats |> List.forall go

    | HAsPat (bodyPat, _, _) -> go bodyPat
    | HOrPat (l, r, _) -> go l || go r

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc = HLitExpr(BoolLit true, loc)

let hxFalse loc = HLitExpr(BoolLit false, loc)

let hxApp f x ty loc = HNodeExpr(HAppEN, [ f; x ], ty, loc)

let hxAscribe expr ty loc =
  HNodeExpr(HAscribeEN, [ expr ], ty, loc)

let hxSemi items loc =
  match splitLast items with
  | Some (stmts, last) -> HBlockExpr(stmts, last)
  | None -> HNodeExpr(HTupleEN, [], tyUnit, loc)

let hxCallProc callee args resultTy loc =
  HNodeExpr(HCallProcEN, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HNodeExpr(HCallClosureEN, callee :: args, resultTy, loc)

let hxTuple items loc =
  HNodeExpr(HTupleEN, items, tyTuple (List.map exprToTy items), loc)

let hxUnit loc = hxTuple [] loc

let hxNil itemTy loc =
  HPrimExpr(HPrim.Nil, tyList itemTy, loc)

let hxIsUnitLit expr =
  match expr with
  | HNodeExpr (HTupleEN, [], _, _) -> true
  | _ -> false

let hxIsAlwaysTrue expr =
  match expr with
  | HLitExpr (BoolLit true, _) -> true
  | _ -> false

let exprExtract (expr: HExpr) : Ty * Loc =
  match expr with
  | HLitExpr (lit, a) -> litToTy lit, a
  | HVarExpr (_, ty, a) -> ty, a
  | HFunExpr (_, ty, a) -> ty, a
  | HVariantExpr (_, ty, a) -> ty, a
  | HPrimExpr (_, ty, a) -> ty, a
  | HRecordExpr (_, _, ty, a) -> ty, a
  | HMatchExpr (_, _, ty, a) -> ty, a
  | HNavExpr (_, _, ty, a) -> ty, a
  | HNodeExpr (_, _, ty, a) -> ty, a
  | HBlockExpr (_, last) -> exprExtract last
  | HLetValExpr (_, _, _, ty, a) -> ty, a
  | HLetFunExpr (_, _, _, _, _, _, ty, a) -> ty, a
  | HTyDeclExpr (_, _, _, _, a) -> tyUnit, a
  | HOpenExpr (_, a) -> tyUnit, a
  | HModuleExpr (_, _, a) -> tyUnit, a
  | HModuleSynonymExpr (_, _, a) -> tyUnit, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr) : HExpr =
  let goPat pat = patMap f g pat

  let rec go expr =
    match expr with
    | HLitExpr (lit, a) -> HLitExpr(lit, g a)
    | HVarExpr (serial, ty, a) -> HVarExpr(serial, f ty, g a)
    | HFunExpr (serial, ty, a) -> HFunExpr(serial, f ty, g a)
    | HVariantExpr (serial, ty, a) -> HVariantExpr(serial, f ty, g a)
    | HPrimExpr (prim, ty, a) -> HPrimExpr(prim, f ty, g a)

    | HRecordExpr (baseOpt, fields, ty, a) ->
        let baseOpt = baseOpt |> Option.map go

        let fields =
          fields
          |> List.map (fun (name, init, a) -> name, go init, g a)

        HRecordExpr(baseOpt, fields, f ty, g a)

    | HMatchExpr (cond, arms, ty, a) ->
        let arms =
          arms
          |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

        HMatchExpr(go cond, arms, f ty, g a)
    | HNavExpr (sub, mes, ty, a) -> HNavExpr(go sub, mes, f ty, g a)
    | HNodeExpr (kind, args, resultTy, a) -> HNodeExpr(kind, List.map go args, f resultTy, g a)
    | HBlockExpr (stmts, last) -> HBlockExpr(List.map go stmts, go last)
    | HLetValExpr (pat, init, next, ty, a) -> HLetValExpr(goPat pat, go init, go next, f ty, g a)
    | HLetFunExpr (serial, isRec, vis, args, body, next, ty, a) ->
        HLetFunExpr(serial, isRec, vis, List.map goPat args, go body, go next, f ty, g a)
    | HTyDeclExpr (serial, vis, tyArgs, tyDef, a) -> HTyDeclExpr(serial, vis, tyArgs, tyDef, g a)
    | HOpenExpr (path, a) -> HOpenExpr(path, g a)
    | HModuleExpr (name, body, a) -> HModuleExpr(name, List.map go body, g a)
    | HModuleSynonymExpr (name, path, a) -> HModuleSynonymExpr(name, path, g a)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

let exprToLoc expr =
  let _, loc = exprExtract expr
  loc

// -----------------------------------------------
// HProgram
// -----------------------------------------------

/// Does something for each module in program, updating a state.
let hirProgramEachModule (mutator: HExpr list * 'S -> HExpr list * 'S) (modules: HProgram, state: 'S) : HProgram * 'S =
  (modules, state)
  |> stMap
       (fun ((p, m, decls), state) ->
         let decls, state = (decls, state) |> mutator
         (p, m, decls), state)

/// Does something for each toplevel expression in program, updating a state.
let hirProgramEachExpr (mutator: HExpr * 'S -> HExpr * 'S) (modules: HProgram, state: 'S) : HProgram * 'S =
  (modules, state)
  |> hirProgramEachModule (stMap mutator)

/// Iterates over toplevel expressions in program to update a state.
let hirProgramFoldExpr (folder: HExpr * 'S -> 'S) (state: 'S) (modules: HProgram) : 'S =
  modules
  |> List.fold
       (fun state (_, _, decls) ->
         decls
         |> List.fold (fun state decl -> folder (decl, state)) state)
       state

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else if i + 1 < format.Length && format.[i] = '%' then
      match format.[i + 1] with
      | 's' -> tyFun tyStr (go (i + 2))
      | 'd' -> tyFun tyInt (go (i + 2))
      | 'f' -> tyFun tyFloat (go (i + 2))
      | 'c' -> tyFun tyChar (go (i + 2))
      | _ -> go (i + 2)
    else
      go (i + 1)

  tyFun tyStr (go 0)

// -----------------------------------------------
// Logs
// -----------------------------------------------

let nameResLogToString log =
  match log with
  | UndefinedValueError name ->
      "The name '"
      + name
      + "' here should denote to some value; but not found."

  | TyUsedAsValueError -> "This is a type. A value is expected here."

  | UndefinedTyError name ->
      "The name '"
      + name
      + "' here should denote to some type; but not found."

  | VarNameConflictError -> "Variable name conflicts"

  | UnresolvedNavPatError -> "Couldn't resolve nav pattern."

  | IllegalOrPatError -> "OR pattern is disallowed in let expressions."

  | OrPatInconsistentBindingError -> "OR pattern binds different set of variables"

  | TyArityError ("_", _, _) -> "'_' can't have type arguments."

  | TyArityError (name, actual, expected) ->
      "Type arity mismatch. The type '"
      + name
      + "' expected "
      + string expected
      + " arguments; but given "
      + string actual
      + "."

  | ModuleUsedAsTyError name ->
      "The name '"
      + name
      + "' here should denote to some type; but is a module name."

  | ModulePathNotFoundError -> "Module not found for this path"

  | UnimplOrPatBindingError -> "OR pattern including some bindings is unimplemented."

  | OtherNameResLog msg -> msg

let private traitBoundErrorToString tyDisplay it =
  match it with
  | AddTrait ty ->
      "Operator (+) is not supported for type: "
      + tyDisplay ty

  | EqualTrait ty ->
      "Equality is not defined for type: "
      + tyDisplay ty

  | CompareTrait ty ->
      "Comparison is not defined for type: "
      + tyDisplay ty

  | IndexTrait (lTy, rTy, _) ->
      "Index operation type error: lhs: '"
      + tyDisplay lTy
      + "', rhs: "
      + tyDisplay rTy
      + "."

  | IsIntTrait ty ->
      "Expected int or some integer type but was: "
      + tyDisplay ty

  | IsNumberTrait ty ->
      "Expected int or float type but was: "
      + tyDisplay ty

  | ToCharTrait ty -> "Can't convert to char from: " + tyDisplay ty
  | ToIntTrait ty -> "Can't convert to integer from: " + tyDisplay ty
  | ToFloatTrait ty -> "Can't convert to float from: " + tyDisplay ty
  | ToStringTrait ty -> "Can't convert to string from: " + tyDisplay ty
  | PtrTrait ty -> "Expected a pointer type but was: " + tyDisplay ty

let logToString tyDisplay log =
  match log with
  | Log.NameResLog log -> nameResLogToString log

  | Log.LiteralRangeError -> "This type of literal can't represent the value."

  | Log.IrrefutablePatNonExhaustiveError ->
      "Let expressions cannot contain refutable patterns, which could fail to match for now."

  | Log.TyUnify (TyUnifyLog.SelfRec, lTy, rTy) ->
      "Recursive type occurred while unifying '"
      + tyDisplay lTy
      + "' to '"
      + tyDisplay rTy
      + "'."

  | Log.TyUnify (TyUnifyLog.Mismatch, lTy, rTy) ->
      "Type mismatch: '"
      + tyDisplay lTy
      + "' <> '"
      + tyDisplay rTy
      + "'."

  | Log.TyBoundError it -> traitBoundErrorToString tyDisplay it

  | Log.TySynonymCycleError -> "Cyclic type synonym is forbidden."

  | Log.RedundantFieldError (recordName, fieldName) ->
      "The field '"
      + fieldName
      + "' is redundant for record '"
      + recordName
      + "'."

  | Log.MissingFieldsError (recordName, fieldNames) ->
      let fields = fieldNames |> S.concat ", "

      "Record '"
      + recordName
      + "' must have fields: "
      + fields

  | Log.ArityMismatch (actual, expected) ->
      "Arity mismatch: expected "
      + expected
      + ", but was "
      + actual
      + "."

  | Log.Error msg -> msg

// ===============================================
// patchwork

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TyCtx =
  {
    /// Next serial number.
    /// We need to identify variables by serial number rather than names
    /// due to scope locality and shadowing.
    Serial: Serial

    /// Variable serial to variable definition.
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    /// Type serial to type definition.
    Tys: AssocMap<TySerial, TyDef>

    TyLevels: AssocMap<TySerial, Level>
    Level: Level
    TraitBounds: (Trait * Loc) list
    Logs: (Log * Loc) list }

// -----------------------------------------------
// Tk
// -----------------------------------------------

let private tkEncode tk : int =
  let pair l r =
    assert (l < 30 && r < 10000000)
    l * 10000000 + r

  let just x = pair x 0

  let isMutToInt isMut =
    match isMut with
    | IsConst -> 1
    | IsMut -> 2

  match tk with
  | ErrorTk _ -> just 0
  | IntTk flavor -> pair 1 (intFlavorToOrdinary flavor)
  | FloatTk flavor -> pair 2 (floatFlavorToOrdinary flavor)
  | BoolTk -> just 3
  | CharTk -> just 4
  | StrTk -> just 5
  | ObjTk -> just 6
  | FunTk -> just 7
  | TupleTk -> just 8
  | OptionTk -> just 9
  | ListTk -> just 10

  | VoidTk -> just 11
  | NativePtrTk isMut -> pair 12 (isMutToInt isMut)
  | NativeFunTk -> just 13

  | MetaTk (tySerial, _) -> pair 20 tySerial
  | SynonymTk tySerial -> pair 21 tySerial
  | UnionTk tySerial -> pair 22 tySerial
  | RecordTk tySerial -> pair 23 tySerial

  | NativeTypeTk _
  | UnresolvedTk _
  | UnresolvedVarTk _ -> unreachable ()

let tkCompare l r : int =
  match l, r with
  | NativeTypeTk l, NativeTypeTk r -> compare l r

  | NativeTypeTk _, _ -> -1
  | _, NativeTypeTk _ -> 1

  | UnresolvedTk (lQuals, lSerial), UnresolvedTk (rQuals, rSerial) ->
      pairCompare (listCompare compare) compare (lQuals, lSerial) (rQuals, rSerial)

  | UnresolvedTk _, _ -> -1
  | _, UnresolvedTk _ -> 1

  | _ -> tkEncode l - tkEncode r

let tkEqual l r : bool = tkCompare l r = 0

let tkDisplay getTyName tk =
  match tk with
  | ErrorTk loc -> "{error}@" + locToString loc
  | IntTk flavor -> fsharpIntegerTyName flavor
  | FloatTk flavor -> fsharpFloatTyName flavor
  | BoolTk -> "bool"
  | CharTk -> "char"
  | StrTk -> "string"
  | ObjTk -> "obj"
  | FunTk -> "fun"
  | TupleTk -> "tuple"
  | OptionTk -> "option"
  | ListTk -> "list"
  | VoidTk -> "void"
  | NativePtrTk IsMut -> "nativeptr"
  | NativePtrTk IsConst -> "__constptr"
  | NativeFunTk -> "__nativeFun"
  | NativeTypeTk _ -> "__nativeType"
  | MetaTk (tySerial, _) -> getTyName tySerial
  | SynonymTk tySerial -> getTyName tySerial
  | RecordTk tySerial -> getTyName tySerial
  | UnionTk tySerial -> getTyName tySerial
  | UnresolvedTk (_, serial) -> "?" + string serial
  | UnresolvedVarTk (serial, _) -> "'" + string serial

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | AddTrait ty -> AddTrait(f ty)
  | EqualTrait ty -> EqualTrait(f ty)
  | CompareTrait ty -> CompareTrait(f ty)
  | IndexTrait (lTy, rTy, resultTy) -> IndexTrait(f lTy, f rTy, f resultTy)
  | IsIntTrait ty -> IsIntTrait(f ty)
  | IsNumberTrait ty -> IsNumberTrait(f ty)
  | ToCharTrait ty -> ToCharTrait(f ty)
  | ToIntTrait ty -> ToIntTrait(f ty)
  | ToFloatTrait ty -> ToFloatTrait(f ty)
  | ToStringTrait ty -> ToStringTrait(f ty)
  | PtrTrait ty -> PtrTrait(f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyIsUnit ty =
  match ty with
  | Ty (TupleTk, []) -> true
  | _ -> false

let tyIsFun ty =
  match ty with
  | Ty (FunTk, _) -> true
  | _ -> false

let tyCompare l r =
  match l, r with
  | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) ->
      let c = tkCompare lTk rTk

      if c <> 0 then
        c
      else
        listCompare tyCompare lTyArgs rTyArgs

let tyEqual l r = tyCompare l r = 0

/// Gets if the specified type variable doesn't appear in a type.
let tyIsFreeIn ty tySerial : bool =
  let rec go ty =
    match ty with
    | Ty (MetaTk (s, _), _) -> s <> tySerial

    | Ty (_, []) -> true

    | Ty (tk, ty :: tys) -> go ty && go (Ty(tk, tys))

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty : bool =
  let rec go tys =
    match tys with
    | [] -> true

    | Ty (MetaTk _, _) :: _ -> false

    | Ty (_, tys1) :: tys2 -> go tys1 && go tys2

  go [ ty ]

/// Gets a list of type variables.
/// Assume all bound type variables are substituted.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] -> fvAcc

    | Ty (MetaTk (serial, _), _) :: tys ->
        let acc = serial :: fvAcc
        go acc tys

    | Ty (_, []) :: tys -> go fvAcc tys

    | Ty (_, tys1) :: tys2 ->
        let acc = go fvAcc tys1
        let acc = go acc tys2
        acc

  go [] [ ty ] |> listUnique compare

/// Converts nested function type to multi-arguments function type.
let rec tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | Ty (FunTk, [ sTy; tTy ]) -> go (n + 1) (sTy :: acc) tTy
    | tTy -> n, List.rev acc, tTy

  go 0 [] ty

/// Checks if the type contains no bound meta types.
let private tyIsFullySubstituted (isBound: TySerial -> bool) ty : bool =
  let rec go ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) -> isBound tySerial |> not
    | Ty (_, tyArgs) -> List.forall go tyArgs

  go ty

/// Substitutes meta types in a type as possible.
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec go ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) ->
        match substMeta tySerial with
        | Some ty -> go ty

        | None -> ty

    | Ty (_, []) -> ty

    | Ty (tk, tys) -> Ty(tk, List.map go tys)

  go ty

let tyAssign assignment ty =
  tySubst (fun tySerial -> assocTryFind compare tySerial assignment) ty

/// Expands a synonym type using its definition and type args.
let tyExpandSynonym useTyArgs defTySerials bodyTy : Ty =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> unreachable ()

  tyAssign assignment bodyTy

/// Expands all synonyms inside of a type.
let tyExpandSynonyms (expand: TySerial -> TyDef option) ty : Ty =
  let rec go ty =
    match ty with
    | Ty (SynonymTk tySerial, useTyArgs) ->
        match expand tySerial with
        | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
            tyExpandSynonym useTyArgs defTySerials bodyTy
            |> go

        | _ -> Ty(SynonymTk tySerial, useTyArgs)

    | Ty (tk, tyArgs) -> Ty(tk, tyArgs |> List.map go)

  go ty

/// Assume all bound type variables are resolved by `substTy`.
///
/// `isOwned` checks if the type variable is introduced by the most recent `let`.
/// For example, `let f x = (let g = f in g x)` will have too generic type
/// without this checking (according to TaPL).
let tyGeneralize (isOwned: TySerial -> bool) (ty: Ty) : TyScheme =
  let fvs =
    tyCollectFreeVars ty |> List.filter isOwned

  TyScheme(fvs, ty)

/// Converts a type to human readable string.
let tyDisplay getTyName ty =
  let rec go (outerBp: int) ty =
    let paren (bp: int) s =
      if bp >= outerBp then
        s
      else
        "(" + s + ")"

    let nominal tySerial args =
      let tk =
        match tySerial |> getTyName with
        | Some name -> name
        | None -> "?" + string tySerial

      match args with
      | [] -> tk
      | _ ->
          let args = args |> List.map (go 0) |> S.concat ", "
          tk + "<" + args + ">"

    match ty with
    | Ty (FunTk, [ sTy; tTy ]) -> paren 10 (go 11 sTy + " -> " + go 10 tTy)

    | Ty (TupleTk, []) -> "unit"

    | Ty (TupleTk, itemTys) ->
        "("
        + (itemTys |> List.map (go 20) |> S.concat " * ")
        + ")"

    | Ty (OptionTk, [ itemTy ]) -> paren 30 (go 30 itemTy + " option")

    | Ty (ListTk, [ itemTy ]) -> paren 30 (go 30 itemTy + " list")

    | Ty (MetaTk (tySerial, loc), _) ->
        match getTyName tySerial with
        | Some name -> "{" + name + "}@" + locToString loc
        | None -> "{?" + string tySerial + "}@" + locToString loc

    | Ty (SynonymTk tySerial, args) -> nominal tySerial args
    | Ty (UnionTk tySerial, args) -> nominal tySerial args
    | Ty (RecordTk tySerial, args) -> nominal tySerial args

    | Ty (tk, args) ->
        let tk = tkDisplay (fun _ -> unreachable ()) tk

        match args with
        | [] -> tk
        | _ ->
            let args = args |> List.map (go 0) |> S.concat ", "
            tk + "<" + args + ">"

  go 0 ty

/// Generates a unique name from a type.
///
/// Must be used after successful Typing.
let tyMangle (ty: Ty, memo: AssocMap<Ty, string>) : string * AssocMap<Ty, string> =
  let rec go ty ctx =
    let (Ty (tk, tyArgs)) = ty

    let mangleList tys ctx =
      (tys, ctx)
      |> stMap (fun (ty, ctx) -> ctx |> go ty)

    let fixedGeneric (name: string) =
      let tyArgs, ctx = mangleList tyArgs ctx
      S.concat "" tyArgs + name, ctx

    let variadicGeneric (name: string) =
      let arity = List.length tyArgs
      let tyArgs, ctx = mangleList tyArgs ctx
      S.concat "" tyArgs + (name + string arity), ctx

    let doMangle () : string * AssocMap<_, _> =
      match tk with
      | IntTk flavor -> cIntegerTyPascalName flavor, ctx
      | FloatTk flavor -> cFloatTyPascalName flavor, ctx
      | BoolTk -> "Bool", ctx
      | CharTk -> "Char", ctx
      | StrTk -> "String", ctx

      | MetaTk _
      | ObjTk -> "Object", ctx

      | TupleTk when List.isEmpty tyArgs -> "Unit", ctx
      | TupleTk -> variadicGeneric "Tuple"

      | OptionTk -> fixedGeneric "Option"
      | ListTk -> fixedGeneric "List"

      | VoidTk -> "Void", ctx
      | NativePtrTk IsConst -> fixedGeneric "ConstPtr"
      | NativePtrTk IsMut -> fixedGeneric "MutPtr"
      | NativeFunTk -> variadicGeneric "NativeFun"
      | NativeTypeTk name -> name, ctx

      | FunTk ->
          let arity, argTys, resultTy = tyToArgList ty

          let argTys, ctx = mangleList argTys ctx
          let resultTy, ctx = ctx |> go resultTy

          let funTy =
            (argTys |> strConcat)
            + resultTy
            + "Fun"
            + string arity

          funTy, ctx

      | UnionTk _
      | RecordTk _ -> unreachable () // Must be stored in memo.

      | ErrorTk _
      | SynonymTk _ -> unreachable () // Resolved in Typing.

      | UnresolvedTk _
      | UnresolvedVarTk _ -> unreachable () // Resolved in NameRes..

    // Memoization.
    match TMap.tryFind ty ctx with
    | Some name -> name, ctx

    | None ->
        let name, ctx = doMangle ()
        name, TMap.add ty name ctx

  go ty memo

// -----------------------------------------------
// Context-free functions
// -----------------------------------------------

let private getLevel tyLevels levelChanges tySerial : Level =
  match levelChanges |> TMap.tryFind tySerial with
  | Some level -> level
  | _ ->
      tyLevels
      |> TMap.tryFind tySerial
      |> Option.defaultValue 0

let private metaTyIsBound tys binding tySerial : bool =
  TMap.containsKey tySerial binding
  || (match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef _) -> true
      | _ -> false)

let private tyExpandMeta tys binding tySerial : Ty option =
  match binding |> TMap.tryFind tySerial with
  | (Some _) as it -> it
  | _ ->
      match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef ty) -> Some ty
      | _ -> None

let doInstantiateTyScheme
  (serial: int)
  (level: Level)
  (tyLevels: AssocMap<TySerial, Level>)
  (tySerials: TySerial list)
  (ty: Ty)
  (loc: Loc)
  =
  let serial, tyLevels, assignment =
    tySerials
    |> List.fold
         (fun (serial, tyLevels, assignment) tySerial ->
           let serial = serial + 1
           let tyLevels = tyLevels |> TMap.add serial level

           let assignment =
             (tySerial, tyMeta serial loc) :: assignment

           serial, tyLevels, assignment)
         (serial, tyLevels, [])

  let ty = tyAssign assignment ty
  serial, tyLevels, ty, assignment

// -----------------------------------------------
// Unification
// -----------------------------------------------

type UnifyResult =
  | UnifyOk
  | UnifyOkWithStack of (Ty * Ty) list
  | UnifyError of Log * Loc
  | UnifyExpandMeta of metaSerial: TySerial * other: Ty
  | UnifyExpandSynonym of synonymSerial: TySerial * synonymArgs: Ty list * other: Ty

let unifyNext (lTy: Ty) (rTy: Ty) (loc: Loc) : UnifyResult =
  let mismatchError () =
    UnifyError(Log.TyUnify(TyUnifyLog.Mismatch, lTy, rTy), loc)

  match lTy, rTy with
  | Ty (MetaTk _, _), _
  | _, Ty (MetaTk _, _) ->
      match lTy, rTy with
      | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> UnifyOk

      | Ty (MetaTk (lSerial, _), _), _ -> UnifyExpandMeta(lSerial, rTy)
      | _, Ty (MetaTk (rSerial, _), _) -> UnifyExpandMeta(rSerial, lTy)

      | _ -> unreachable ()

  | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) when tkEqual lTk rTk ->
      match lTyArgs, rTyArgs with
      | [], [] -> UnifyOk

      | _ ->
          match listTryZip lTyArgs rTyArgs with
          | tyPairs, [], [] -> UnifyOkWithStack(tyPairs)
          | _ -> mismatchError ()

  | Ty (SynonymTk _, _), _
  | _, Ty (SynonymTk _, _) ->
      match lTy, rTy with
      | Ty (SynonymTk tySerial, tyArgs), _ -> UnifyExpandSynonym(tySerial, tyArgs, rTy)
      | _, Ty (SynonymTk tySerial, tyArgs) -> UnifyExpandSynonym(tySerial, tyArgs, lTy)
      | _ -> unreachable ()

  | _ -> mismatchError ()

[<RequireQualifiedAccess>]
type UnifyAfterExpandMetaResult =
  | OkNoBind
  | OkBind
  | Error of Log * Loc

let unifyAfterExpandMeta lTy rTy tySerial otherTy loc =
  match otherTy with
  | Ty (MetaTk (otherSerial, _), _) when otherSerial = tySerial -> UnifyAfterExpandMetaResult.OkNoBind

  | _ when tyIsFreeIn otherTy tySerial |> not ->
      // ^ Occurrence check.
      UnifyAfterExpandMetaResult.Error(Log.TyUnify(TyUnifyLog.SelfRec, lTy, rTy), loc)

  | _ -> UnifyAfterExpandMetaResult.OkBind

let typingSubst tys binding ty : Ty = tySubst (tyExpandMeta tys binding) ty

let typingExpandSynonyms tys ty =
  tyExpandSynonyms (fun tySerial -> tys |> TMap.tryFind tySerial) ty
