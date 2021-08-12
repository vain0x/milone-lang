/// # Tir
///
/// Type-check intermediate representation (TIR).
///
/// TIR is functional-style. Similar to milone-lang's syntax.
module rec MiloneSyntax.Tir

open MiloneShared.Util
open MiloneShared.SharedTypes
open MiloneSyntax.Syntax
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers

module TMap = MiloneStd.StdMap
module S = MiloneStd.StdString

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

  | SynonymTyDef of Ident * tyArgs: TySerial list * Ty * Loc

  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * tyArgs: TySerial list * fields: (Ident * Ty * Loc) list * Loc

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

/// Kind of TNodePat.
[<Struct; NoEquality; NoComparison>]
type TPatKind =
  /// `[]`.
  | TNilPN

  /// `p1 :: p2`.
  | TConsPN

  | TNonePN

  /// `Some`.
  | TSomePN

  /// `p1 p2`.
  | TAppPN

  /// `Some p1`.
  | TSomeAppPN

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

/// Pattern in HIR.
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

/// Primitive in HIR.
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
type TExprKind =
  | TAbortEN

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

  /// Use function as function pointer.
  | TNativeFunEN of FunSerial

  /// Embed some C expression to output.
  | TNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | TNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | TNativeDeclEN of nativeDeclCode: string

  /// Size of type.
  | TSizeOfValEN

/// Expression in HIR.
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
  | TNavExpr of TExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | TNodeExpr of TExprKind * TExpr list * Ty * Loc

  /// Evaluate a list of expressions and returns the last, e.g. `x1; x2; ...; y`.
  | TBlockExpr of TExpr list * TExpr

  | TLetValExpr of pat: TPat * init: TExpr * next: TExpr * Ty * Loc
  | TLetFunExpr of FunSerial * IsRec * Vis * args: TPat list * body: TExpr * next: TExpr * Ty * Loc

  /// Type declaration.
  | TTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | TOpenExpr of Ident list * Loc
  | TModuleExpr of ModuleTySerial * body: TExpr list * Loc
  | TModuleSynonymExpr of ModuleSynonymSerial * path: Ident list * Loc

/// TIR program. (project name, module name, decls) list.
type TProgram = (string * string * TExpr list) list

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

  | UnimplGenericTyError
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
// Name context
// -----------------------------------------------

let nameCtxEmpty () = NameCtx(TMap.empty compare, 0)

let nameCtxAdd (Name (name, _)) (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> TMap.add serial name
  serial, NameCtx(map, serial)

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

let tyUnion tySerial tyArgs = Ty(UnionTk tySerial, tyArgs)

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
  | UnionTyDef (name, _, _, _) -> name
  | RecordTyDef (name, _, _, _) -> name

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
// Primitives (TIR)
// -----------------------------------------------

let primFromIdent ident =
  match ident with
  | "not" -> TPrim.Not |> Some

  | "exit" -> TPrim.Exit |> Some

  | "assert" -> TPrim.Assert |> Some

  | "box" -> TPrim.Box |> Some

  | "unbox" -> TPrim.Unbox |> Some

  | "printfn" -> TPrim.Printfn |> Some

  | "compare" -> TPrim.Compare |> Some

  | "char" -> TPrim.Char |> Some

  | "int"
  | "int32" -> TPrim.ToInt(IntFlavor(Signed, I32)) |> Some
  | "uint"
  | "uint32" -> TPrim.ToInt(IntFlavor(Unsigned, I32)) |> Some
  | "sbyte"
  | "int8" -> TPrim.ToInt(IntFlavor(Signed, I8)) |> Some
  | "byte"
  | "uint8" -> TPrim.ToInt(IntFlavor(Unsigned, I8)) |> Some

  | "int16" -> TPrim.ToInt(IntFlavor(Signed, I16)) |> Some
  | "int64" -> TPrim.ToInt(IntFlavor(Signed, I64)) |> Some
  | "nativeint" -> TPrim.ToInt(IntFlavor(Signed, IPtr)) |> Some
  | "uint16" -> TPrim.ToInt(IntFlavor(Unsigned, I16)) |> Some
  | "uint64" -> TPrim.ToInt(IntFlavor(Unsigned, I64)) |> Some
  | "unativeint" -> TPrim.ToInt(IntFlavor(Unsigned, IPtr)) |> Some

  | "float" -> TPrim.ToFloat F64 |> Some
  | "float32" -> TPrim.ToFloat F32 |> Some

  | "string" -> TPrim.String |> Some

  | "None" -> TPrim.OptionNone |> Some

  | "Some" -> TPrim.OptionSome |> Some

  | "inRegion" -> TPrim.InRegion |> Some

  | "__nativeFun" -> TPrim.NativeFun |> Some
  | "__nativeCast" -> TPrim.NativeCast |> Some
  | "__nativeExpr" -> TPrim.NativeExpr |> Some
  | "__nativeStmt" -> TPrim.NativeStmt |> Some
  | "__nativeDecl" -> TPrim.NativeDecl |> Some
  | "__sizeOfVal" -> TPrim.SizeOfVal |> Some
  | "__ptrRead" -> TPrim.PtrRead |> Some
  | "__ptrWrite" -> TPrim.PtrWrite |> Some

  | _ -> None

let primToTySpec prim =
  let meta id = tyMeta id noLoc
  let mono ty = TySpec(ty, [])
  let poly ty traits = TySpec(ty, traits)

  match prim with
  | TPrim.Add ->
    let addTy = meta 1
    poly (tyFun addTy (tyFun addTy addTy)) [ AddTrait addTy ]

  | TPrim.Sub
  | TPrim.Mul
  | TPrim.Div
  | TPrim.Modulo ->
    let ty = meta 1
    poly (tyFun ty (tyFun ty ty)) [ IsNumberTrait ty ]

  | TPrim.BitAnd
  | TPrim.BitOr
  | TPrim.BitXor ->
    let ty = meta 1
    poly (tyFun ty (tyFun ty ty)) [ IsIntTrait ty ]

  | TPrim.LeftShift
  | TPrim.RightShift ->
    let ty = meta 1
    poly (tyFun ty (tyFun tyInt ty)) [ IsIntTrait ty ]

  | TPrim.Equal ->
    let argTy = meta 1
    poly (tyFun argTy (tyFun argTy tyBool)) [ EqualTrait argTy ]

  | TPrim.Less ->
    let compareTy = meta 1
    poly (tyFun compareTy (tyFun compareTy tyBool)) [ CompareTrait compareTy ]

  | TPrim.Compare ->
    let compareTy = meta 1
    poly (tyFun compareTy (tyFun compareTy tyInt)) [ CompareTrait compareTy ]

  | TPrim.Nil ->
    let itemTy = meta 1
    poly (tyList itemTy) []

  | TPrim.Cons ->
    let itemTy = meta 1
    let listTy = tyList itemTy
    poly (tyFun itemTy (tyFun listTy listTy)) []

  | TPrim.OptionNone ->
    let itemTy = meta 1
    poly (tyOption itemTy) []

  | TPrim.OptionSome ->
    let itemTy = meta 1
    let listTy = tyOption itemTy
    poly (tyFun itemTy listTy) []

  | TPrim.Not -> mono (tyFun tyBool tyBool)

  | TPrim.Exit ->
    let resultTy = meta 1
    poly (tyFun tyInt resultTy) []

  | TPrim.Assert -> mono (tyFun tyBool tyUnit)

  | TPrim.Box ->
    let itemTy = meta 1
    poly (tyFun itemTy tyObj) []

  | TPrim.Unbox ->
    let itemTy = meta 1
    poly (tyFun tyObj itemTy) []

  | TPrim.Char ->
    let srcTy = meta 1
    poly (tyFun srcTy tyChar) [ ToCharTrait srcTy ]

  | TPrim.ToInt flavor ->
    let toIntTy = meta 1
    let resultTy = Ty(IntTk flavor, [])
    poly (tyFun toIntTy resultTy) [ ToIntTrait toIntTy ]

  | TPrim.ToFloat flavor ->
    let srcTy = meta 1
    let resultTy = Ty(FloatTk flavor, [])
    poly (tyFun srcTy resultTy) [ ToFloatTrait srcTy ]

  | TPrim.String ->
    let toStrTy = meta 1
    poly (tyFun toStrTy tyStr) [ ToStringTrait toStrTy ]

  | TPrim.StrLength -> mono (tyFun tyStr tyInt)

  | TPrim.InRegion -> mono (tyFun (tyFun tyUnit tyInt) tyInt)

  | TPrim.Printfn
  | TPrim.NativeFun
  | TPrim.NativeExpr
  | TPrim.NativeStmt
  | TPrim.NativeDecl ->
    // Incorrect use of this primitive is handled as error before instantiating its type.
    unreachable ()

  | TPrim.NativeCast ->
    let srcTy = meta 1
    let destTy = meta 2
    poly (tyFun srcTy destTy) [ PtrTrait srcTy; PtrTrait destTy ]

  | TPrim.SizeOfVal -> poly (tyFun (meta 1) tyInt) []

  | TPrim.PtrRead ->
    // __constptr<'p> -> int -> 'a
    let valueTy = meta 1
    poly (tyFun (tyConstPtr valueTy) (tyFun tyInt valueTy)) []

  | TPrim.PtrWrite ->
    // nativeptr<'a> -> int -> 'a -> unit
    let valueTy = meta 1
    poly (tyFun (tyNativePtr valueTy) (tyFun tyInt (tyFun valueTy tyUnit))) []

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let hpAbort ty loc = TNodePat(TAbortPN, [], ty, loc)

let patExtract (pat: TPat) : Ty * Loc =
  match pat with
  | TLitPat (lit, a) -> litToTy lit, a
  | TDiscardPat (ty, a) -> ty, a
  | TVarPat (_, _, ty, a) -> ty, a
  | TVariantPat (_, ty, a) -> ty, a

  | TNodePat (_, _, ty, a) -> ty, a
  | TAsPat (bodyPat, _, a) -> patToTy bodyPat, a
  | TOrPat (l, _, a) -> patToTy l, a

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat = pat |> patExtract |> snd

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: TPat) : TPat =
  let rec go pat =
    match pat with
    | TLitPat (lit, a) -> TLitPat(lit, g a)
    | TDiscardPat (ty, a) -> TDiscardPat(f ty, g a)
    | TVarPat (vis, serial, ty, a) -> TVarPat(vis, serial, f ty, g a)
    | TVariantPat (serial, ty, a) -> TVariantPat(serial, f ty, g a)

    | TNodePat (kind, args, ty, a) -> TNodePat(kind, List.map go args, f ty, g a)
    | TAsPat (bodyPat, serial, a) -> TAsPat(go bodyPat, serial, g a)
    | TOrPat (l, r, a) -> TOrPat(go l, go r, g a)

  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | TLitPat _
    | TDiscardPat _
    | TVarPat _
    | TVariantPat _ -> [ pat ]

    | TNodePat (kind, argPats, ty, loc) ->
      argPats
      |> doNormalizePats
      |> List.map (fun itemPats -> TNodePat(kind, itemPats, ty, loc))

    | TAsPat (bodyPat, serial, loc) ->
      go bodyPat
      |> List.map (fun bodyPat -> TAsPat(bodyPat, serial, loc))

    | TOrPat (l, r, _) -> List.append (go l) (go r)

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
    | TLitPat _ -> false

    | TDiscardPat _
    | TVarPat _ -> true

    | TVariantPat (variantSerial, _, _) -> isNewtypeVariant variantSerial

    | TNodePat (kind, argPats, _, _) ->
      match kind, argPats with
      | TVariantAppPN variantSerial, [ payloadPat ] -> isNewtypeVariant variantSerial && go payloadPat

      | TAbortPN, _ -> true

      | TNilPN, _
      | TConsPN, _
      | TNonePN, _
      | TSomePN, _
      | TSomeAppPN, _
      | TAppPN, _
      | TVariantAppPN _, _
      | TNavPN _, _ -> false

      | TTuplePN, _
      | TAscribePN, _ -> argPats |> List.forall go

    | TAsPat (bodyPat, _, _) -> go bodyPat
    | TOrPat (l, r, _) -> go l || go r

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc = TLitExpr(BoolLit true, loc)

let hxApp f x ty loc = TNodeExpr(TAppEN, [ f; x ], ty, loc)

let hxAscribe expr ty loc =
  TNodeExpr(TAscribeEN, [ expr ], ty, loc)

let hxSemi items loc =
  match splitLast items with
  | Some (stmts, last) -> TBlockExpr(stmts, last)
  | None -> TNodeExpr(TTupleEN, [], tyUnit, loc)

let hxTuple items loc =
  TNodeExpr(TTupleEN, items, tyTuple (List.map exprToTy items), loc)

let hxUnit loc = hxTuple [] loc

let hxNil itemTy loc =
  TPrimExpr(TPrim.Nil, tyList itemTy, loc)

let exprExtract (expr: TExpr) : Ty * Loc =
  match expr with
  | TLitExpr (lit, a) -> litToTy lit, a
  | TVarExpr (_, ty, a) -> ty, a
  | TFunExpr (_, ty, a) -> ty, a
  | TVariantExpr (_, ty, a) -> ty, a
  | TPrimExpr (_, ty, a) -> ty, a
  | TRecordExpr (_, _, ty, a) -> ty, a
  | TMatchExpr (_, _, ty, a) -> ty, a
  | TNavExpr (_, _, ty, a) -> ty, a
  | TNodeExpr (_, _, ty, a) -> ty, a
  | TBlockExpr (_, last) -> exprExtract last
  | TLetValExpr (_, _, _, ty, a) -> ty, a
  | TLetFunExpr (_, _, _, _, _, _, ty, a) -> ty, a
  | TTyDeclExpr (_, _, _, _, a) -> tyUnit, a
  | TOpenExpr (_, a) -> tyUnit, a
  | TModuleExpr (_, _, a) -> tyUnit, a
  | TModuleSynonymExpr (_, _, a) -> tyUnit, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: TExpr) : TExpr =
  let goPat pat = patMap f g pat

  let rec go expr =
    match expr with
    | TLitExpr (lit, a) -> TLitExpr(lit, g a)
    | TVarExpr (serial, ty, a) -> TVarExpr(serial, f ty, g a)
    | TFunExpr (serial, ty, a) -> TFunExpr(serial, f ty, g a)
    | TVariantExpr (serial, ty, a) -> TVariantExpr(serial, f ty, g a)
    | TPrimExpr (prim, ty, a) -> TPrimExpr(prim, f ty, g a)

    | TRecordExpr (baseOpt, fields, ty, a) ->
      let baseOpt = baseOpt |> Option.map go

      let fields =
        fields
        |> List.map (fun (name, init, a) -> name, go init, g a)

      TRecordExpr(baseOpt, fields, f ty, g a)

    | TMatchExpr (cond, arms, ty, a) ->
      let arms =
        arms
        |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

      TMatchExpr(go cond, arms, f ty, g a)
    | TNavExpr (sub, mes, ty, a) -> TNavExpr(go sub, mes, f ty, g a)
    | TNodeExpr (kind, args, resultTy, a) -> TNodeExpr(kind, List.map go args, f resultTy, g a)
    | TBlockExpr (stmts, last) -> TBlockExpr(List.map go stmts, go last)
    | TLetValExpr (pat, init, next, ty, a) -> TLetValExpr(goPat pat, go init, go next, f ty, g a)
    | TLetFunExpr (serial, isRec, vis, args, body, next, ty, a) ->
      TLetFunExpr(serial, isRec, vis, List.map goPat args, go body, go next, f ty, g a)
    | TTyDeclExpr (serial, vis, tyArgs, tyDef, a) -> TTyDeclExpr(serial, vis, tyArgs, tyDef, g a)
    | TOpenExpr (path, a) -> TOpenExpr(path, g a)
    | TModuleExpr (name, body, a) -> TModuleExpr(name, List.map go body, g a)
    | TModuleSynonymExpr (name, path, a) -> TModuleSynonymExpr(name, path, g a)

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
let hirProgramEachModule (mutator: TExpr list * 'S -> TExpr list * 'S) (modules: TProgram, state: 'S) : TProgram * 'S =
  (modules, state)
  |> stMap
       (fun ((p, m, decls), state) ->
         let decls, state = (decls, state) |> mutator
         (p, m, decls), state)

/// Does something for each toplevel expression in program, updating a state.
let hirProgramEachExpr (mutator: TExpr * 'S -> TExpr * 'S) (modules: TProgram, state: 'S) : TProgram * 'S =
  (modules, state)
  |> hirProgramEachModule (stMap mutator)

/// Iterates over toplevel expressions in program to update a state.
let hirProgramFoldExpr (folder: TExpr * 'S -> 'S) (state: 'S) (modules: TProgram) : 'S =
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

  | UnimplGenericTyError -> "Generic record type is unimplemented."
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
