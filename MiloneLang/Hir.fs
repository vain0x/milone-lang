/// # Hir
///
/// Provides types and functions for high-level intermediate representation (HIR).
///
/// HIR is functional-style. Similar to milone-lang's syntax.
///
/// ## Lifecycle
///
/// HIR is generated in `AstToHir` for each file
/// and all modules of a project are *concatenated* in `Bundling`.
///
/// Most of analysis (for error reporting and soundness)
/// and transformations (for code generation) are performed on it.
///
/// Finally HIR is converted to MIR in `MirGen`.
///
/// See `Cli.fs` for details.
module rec MiloneLang.Hir

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers

module S = MiloneStd.StdString

/// Unique serial number to identify something
/// such as variables, nominal types, etc.
type Serial = int

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

/// Number of parameters.
type Arity = int

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

/// Where variable is stored.
[<NoEquality; NoComparison>]
type StorageModifier =
  /// On stack.
  | AutoSM

  /// On static storage.
  | StaticSM

[<Struct>]
[<NoEquality; NoComparison>]
type NameCtx = NameCtx of map: AssocMap<Serial, Ident> * lastSerial: Serial

[<NoEquality; NoComparison>]
type IsMut =
  | IsConst
  | IsMut

/// Type constructor.
[<Struct>]
[<NoEquality; NoComparison>]
type TyCtor =
  | IntTyCtor of intFlavor: IntFlavor
  | FloatTyCtor of floatFlavor: FloatFlavor
  | BoolTyCtor
  | CharTyCtor
  | StrTyCtor
  | ObjTyCtor

  /// Ty args must be `[s; t]`.
  | FunTyCtor

  | TupleTyCtor

  /// Ty args must be `[t]`.
  | ListTyCtor

  // FFI types.
  | VoidTyCtor
  | NativePtrTyCtor of nativePtrIsMut: IsMut
  | NativeFunTyCtor
  | NativeTypeTyCtor of cCode: string

  // Nominal types.
  | SynonymTyCtor of synonymTy: TySerial
  | UnionTyCtor of unionTy: TySerial
  | RecordTyCtor of recordTy: TySerial

  /// Unresolved type. Generated in AstToHir, resolved in NameRes.
  | UnresolvedTyCtor of quals: Serial list * unresolvedSerial: Serial
  | UnresolvedVarTyCtor of unresolvedVarTySerial: Serial

/// Type of expressions.
[<Struct>]
[<NoEquality; NoComparison>]
type Ty =
  | ErrorTy of errorLoc: Loc

  /// Type variable to be bound or quantified..
  | MetaTy of metaTySerial: Serial * metaLoc: Loc

  /// Type application.
  | AppTy of TyCtor * tyArgs: Ty list

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
  | EqTrait of Ty

  /// The type supports `<`.
  | CmpTrait of Ty

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
  | MetaTyDef of Ident * Ty * Loc

  | UniversalTyDef of Ident * Loc

  | SynonymTyDef of Ident * TySerial list * Ty * Loc

  | UnionTyDef of Ident * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * Loc

[<Struct; NoComparison>]
type ModuleTySerial = ModuleTySerial of Serial

//// Module is a type so that it can be used as namespace.
[<NoEquality; NoComparison>]
type ModuleTyDef = { Name: Ident; Loc: Loc }

[<Struct; NoComparison>]
type ModuleSynonymSerial = ModuleSynonymSerial of Serial

//// Module is a type so that it can be used as namespace.
[<NoEquality; NoComparison>]
type ModuleSynonymDef =
  { Name: Ident
    Bound: ModuleTySerial option
    Loc: Loc }

/// Definition of named value in HIR.
[<NoEquality; NoComparison>]
type VarDef = VarDef of Ident * StorageModifier * Ty * Loc

/// Assembly binary interface (ABI): how function looks like at machine-code level.
[<NoEquality; NoComparison>]
type FunAbi =
  | MiloneAbi

  /// Compatible with C language.
  | CAbi

[<NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Abi: FunAbi
    Loc: Loc }

[<NoEquality; NoComparison>]
type VariantDef =
  { Name: Ident
    UnionTySerial: TySerial
    HasPayload: bool
    PayloadTy: Ty
    VariantTy: Ty
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
  | ModuleTySymbol of moduleTySerial: ModuleTySerial
  | ModuleSynonymSymbol of moduleSynonymSerial: ModuleSynonymSerial

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
  | HNavPN of navR: string

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
  | Mod
  | BitAnd
  | BitOr
  | BitXor
  | LeftShift
  | RightShift
  | Eq
  | Lt
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
  | HRefExpr of VarSerial * Ty * Loc

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

  | HLetValExpr of Vis * pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * IsRec * Vis * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | HOpenExpr of Ident list * Loc
  | HModuleExpr of ModuleTySerial * body: HExpr list * Loc
  | HModuleSynonymExpr of ModuleSynonymSerial * path: Ident list * Loc

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

  | UnimplModuleSynonymError
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
  | TyUnify of TyUnifyLog * lRootTy: Ty * rRootTy: Ty * lTy: Ty * rTy: Ty
  | TyBoundError of Trait
  | TySynonymCycleError
  | RedundantFieldError of ty: Ident * field: Ident
  | MissingFieldsError of ty: Ident * fields: Ident list
  | ArityMismatch of actual: Arity * expected: Arity
  | Error of string

// -----------------------------------------------
// Name context
// -----------------------------------------------

let nameCtxEmpty () = NameCtx(mapEmpty compare, 0)

let nameCtxAdd name (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> mapAdd serial name
  serial, NameCtx(map, serial)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

/// Placeholder. No type info in the parsing phase.
let noTy = ErrorTy noLoc

let tyInt =
  AppTy(IntTyCtor(IntFlavor(Signed, I32)), [])

let tyBool = AppTy(BoolTyCtor, [])

let tyFloat = AppTy(FloatTyCtor F64, [])

let tyChar = AppTy(CharTyCtor, [])

let tyStr = AppTy(StrTyCtor, [])

let tyObj = AppTy(ObjTyCtor, [])

let tyTuple tys = AppTy(TupleTyCtor, tys)

let tyList ty = AppTy(ListTyCtor, [ ty ])

let tyFun sourceTy targetTy =
  AppTy(FunTyCtor, [ sourceTy; targetTy ])

let tyConstPtr itemTy =
  AppTy(NativePtrTyCtor IsConst, [ itemTy ])

let tyNativePtr itemTy =
  AppTy(NativePtrTyCtor IsMut, [ itemTy ])

let tyNativeFun paramTys resultTy =
  AppTy(NativeFunTyCtor, List.append paramTys [ resultTy ])

let tyUnit = tyTuple []

let tySynonym tySerial tyArgs = AppTy(SynonymTyCtor tySerial, tyArgs)

let tyUnion tySerial = AppTy(UnionTyCtor tySerial, [])

let tyRecord tySerial = AppTy(RecordTyCtor tySerial, [])

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let moduleTySerialToInt (ModuleTySerial serial) = serial

let moduleTySerialCmp l r =
  moduleTySerialToInt l - moduleTySerialToInt r

let moduleSynonymSerialToInt (ModuleSynonymSerial serial) = serial

let moduleSynonymSerialCmp l r =
  moduleSynonymSerialToInt l
  - moduleSynonymSerialToInt r

let tyDefToName tyDef =
  match tyDef with
  | MetaTyDef (name, _, _) -> name
  | UniversalTyDef (name, _) -> name
  | SynonymTyDef (name, _, _, _) -> name
  | UnionTyDef (name, _, _) -> name
  | RecordTyDef (name, _, _) -> name

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varSerialToInt (VarSerial serial) = serial

let varSerialCmp l r =
  compare (varSerialToInt l) (varSerialToInt r)

let funSerialToInt (FunSerial serial) = serial

let funSerialCmp l r =
  compare (funSerialToInt l) (funSerialToInt r)

let variantSerialToInt (VariantSerial serial) = serial

let variantSerialCmp l r =
  compare (variantSerialToInt l) (variantSerialToInt r)

let varDefToName varDef =
  match varDef with
  | VarDef (name, _, _, _) -> name

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litToTy (lit: Lit): Ty =
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
  let meta id = MetaTy(id, noLoc)
  let mono ty = TySpec(ty, [])
  let poly ty traits = TySpec(ty, traits)

  match prim with
  | HPrim.Add ->
      let addTy = meta 1
      poly (tyFun addTy (tyFun addTy addTy)) [ AddTrait addTy ]

  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Mod ->
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

  | HPrim.Eq ->
      let eqTy = meta 1
      poly (tyFun eqTy (tyFun eqTy tyBool)) [ EqTrait eqTy ]

  | HPrim.Lt ->
      let cmpTy = meta 1
      poly (tyFun cmpTy (tyFun cmpTy tyBool)) [ CmpTrait cmpTy ]

  | HPrim.Compare ->
      let cmpTy = meta 1
      poly (tyFun cmpTy (tyFun cmpTy tyInt)) [ CmpTrait cmpTy ]

  | HPrim.Nil ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.Cons ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy (tyFun listTy listTy)) []

  | HPrim.OptionNone ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.OptionSome ->
      let itemTy = meta 1
      let listTy = tyList itemTy
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
      let resultTy = AppTy(IntTyCtor flavor, [])
      poly (tyFun toIntTy resultTy) [ ToIntTrait toIntTy ]

  | HPrim.ToFloat flavor ->
      let srcTy = meta 1
      let resultTy = AppTy(FloatTyCtor flavor, [])
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
      failwith "NEVER"

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

let patExtract (pat: HPat): Ty * Loc =
  match pat with
  | HLitPat (lit, a) -> litToTy lit, a
  | HDiscardPat (ty, a) -> ty, a
  | HVarPat (_, ty, a) -> ty, a
  | HVariantPat (_, ty, a) -> ty, a

  | HNodePat (_, _, ty, a) -> ty, a
  | HAsPat (bodyPat, _, a) -> patToTy bodyPat, a
  | HOrPat (l, _, a) -> patToTy l, a

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat = pat |> patExtract |> snd

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat): HPat =
  let rec go pat =
    match pat with
    | HLitPat (lit, a) -> HLitPat(lit, g a)
    | HDiscardPat (ty, a) -> HDiscardPat(f ty, g a)
    | HVarPat (serial, ty, a) -> HVarPat(serial, f ty, g a)
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

let hxTrue loc = HLitExpr(litTrue, loc)

let hxFalse loc = HLitExpr(litFalse, loc)

let hxApp f x ty loc = HNodeExpr(HAppEN, [ f; x ], ty, loc)

let hxAscribe expr ty loc = HNodeExpr(HAscribeEN, [ expr ], ty, loc)

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

let exprExtract (expr: HExpr): Ty * Loc =
  match expr with
  | HLitExpr (lit, a) -> litToTy lit, a
  | HRefExpr (_, ty, a) -> ty, a
  | HFunExpr (_, ty, a) -> ty, a
  | HVariantExpr (_, ty, a) -> ty, a
  | HPrimExpr (_, ty, a) -> ty, a
  | HRecordExpr (_, _, ty, a) -> ty, a
  | HMatchExpr (_, _, ty, a) -> ty, a
  | HNavExpr (_, _, ty, a) -> ty, a
  | HNodeExpr (_, _, ty, a) -> ty, a
  | HBlockExpr (_, last) -> exprExtract last
  | HLetValExpr (_, _, _, _, ty, a) -> ty, a
  | HLetFunExpr (_, _, _, _, _, _, ty, a) -> ty, a
  | HTyDeclExpr (_, _, _, _, a) -> tyUnit, a
  | HOpenExpr (_, a) -> tyUnit, a
  | HModuleExpr (_, _, a) -> tyUnit, a
  | HModuleSynonymExpr (_, _, a) -> tyUnit, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr): HExpr =
  let goPat pat = patMap f g pat

  let rec go expr =
    match expr with
    | HLitExpr (lit, a) -> HLitExpr(lit, g a)
    | HRefExpr (serial, ty, a) -> HRefExpr(serial, f ty, g a)
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
    | HLetValExpr (vis, pat, init, next, ty, a) -> HLetValExpr(vis, goPat pat, go init, go next, f ty, g a)
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

  | UnimplModuleSynonymError -> "This kind of module synonym is unimplemented. Hint: `module A = P.M`."

  | UnimplOrPatBindingError -> "OR pattern including some bindings is unimplemented."

  | OtherNameResLog msg -> msg

let private traitBoundErrorToString tyDisplay it =
  match it with
  | AddTrait ty ->
      "Operator (+) is not supported for type: "
      + tyDisplay ty

  | EqTrait ty ->
      "Equality is not defined for type: "
      + tyDisplay ty

  | CmpTrait ty ->
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

  | Log.TyUnify (TyUnifyLog.SelfRec, _, _, lTy, rTy) ->
      "Recursive type occurred while unifying '"
      + tyDisplay lTy
      + "' to '"
      + tyDisplay rTy
      + "'."

  | Log.TyUnify (TyUnifyLog.Mismatch, _, _, lTy, rTy) ->
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
      + string expected
      + ", but was "
      + string actual
      + "."

  | Log.Error msg -> msg
