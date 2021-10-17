/// # Tir
///
/// Type-check intermediate representation (TIR).
///
/// TIR is functional-style. Similar to milone-lang's syntax.
module rec MiloneSyntax.Tir

open MiloneShared.Util
open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneStd.StdMap

module S = MiloneStd.StdString

// from syntax
type private ProjectName = string
type private ModuleName = string

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

[<Struct; NoEquality; NoComparison>]
type NameCtx = NameCtx of identMap: TreeMap<Serial, Ident> * lastSerial: Serial

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

  /// Unresolved type. Generated in TirGen, resolved in NameRes.
  | UnresolvedTk of quals: Serial list * unresolvedSerial: Serial
  | UnresolvedVarTk of unresolvedVarTySerial: (Serial * Loc)

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type Ty =
  /// Type application.
  | Ty of Tk * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct; NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

/// Type specification.
[<Struct; NoEquality; NoComparison>]
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

  | RecordTyDecl of Ident * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ty

  | UniversalTyDef of Ident * Loc

  | SynonymTyDef of Ident * tyArgs: TySerial list * Ty * Loc

  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * tyArgs: TySerial list * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

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
    ParentOpt: FunSerial option
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

[<NoComparison>]
type ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial

[<NoComparison>]
type TySymbol =
  | MetaTySymbol of tySerial: TySerial
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial

/// Context of TIR program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TirCtx =
  { /// Last serial number.
    Serial: Serial

    Vars: TreeMap<VarSerial, VarDef>
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

[<NoEquality; NoComparison>]
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
  | TNavExpr of TExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | TNodeExpr of TExprKind * TExpr list * Ty * Loc

  /// Statements and last expression.
  ///
  /// - Statements might define symbols locally for the last expression.
  /// - If recursive, local definitions are mutually recursive.
  | TBlockExpr of IsRec * TStmt list * last: TExpr

/// Statement.
[<NoEquality; NoComparison>]
type TStmt =
  | TExprStmt of TExpr
  | TLetValStmt of TPat * TExpr * Loc
  | TLetFunStmt of FunSerial * IsRec * Vis * args: TPat list * body: TExpr * Loc
  | TTyDeclStmt of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | TOpenStmt of Ident list * Loc
  | TModuleStmt of ModuleTySerial * body: TStmt list * Loc
  | TModuleSynonymStmt of ModuleSynonymSerial * path: Ident list * Loc

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
// Ty
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
// TyDef
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
  | RecordTyDef (name, _, _, _, _) -> name

// -----------------------------------------------
// VarDef
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
// Lit
// -----------------------------------------------

let litToTy (lit: Lit) : Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | FloatLit _ -> tyFloat
  | CharLit _ -> tyChar
  | StrLit _ -> tyStr

// -----------------------------------------------
// TPrim
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

  | "__inRegion" -> TPrim.InRegion |> Some

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
// TPat
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

let patMap (f: Ty -> Ty) (pat: TPat) : TPat =
  let rec go pat =
    match pat with
    | TLitPat (lit, a) -> TLitPat(lit, a)
    | TDiscardPat (ty, a) -> TDiscardPat(f ty, a)
    | TVarPat (vis, serial, ty, a) -> TVarPat(vis, serial, f ty, a)
    | TVariantPat (serial, ty, a) -> TVariantPat(serial, f ty, a)

    | TNodePat (kind, args, ty, a) -> TNodePat(kind, List.map go args, f ty, a)
    | TAsPat (bodyPat, serial, a) -> TAsPat(go bodyPat, serial, a)
    | TOrPat (l, r, a) -> TOrPat(go l, go r, a)

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
// TExpr
// -----------------------------------------------

let hxTrue loc = TLitExpr(BoolLit true, loc)

let hxApp f x ty loc = TNodeExpr(TAppEN, [ f; x ], ty, loc)

let hxAscribe expr ty loc =
  TNodeExpr(TAscribeEN, [ expr ], ty, loc)

let hxLetIn stmt next = TBlockExpr(NotRec, [ stmt ], next)

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
  | TBlockExpr (_, _, last) -> exprExtract last

let exprMap (f: Ty -> Ty) (expr: TExpr) : TExpr =
  let goPat pat = patMap f pat

  let rec go expr =
    match expr with
    | TLitExpr (lit, a) -> TLitExpr(lit, a)
    | TVarExpr (serial, ty, a) -> TVarExpr(serial, f ty, a)
    | TFunExpr (serial, ty, a) -> TFunExpr(serial, f ty, a)
    | TVariantExpr (serial, ty, a) -> TVariantExpr(serial, f ty, a)
    | TPrimExpr (prim, ty, a) -> TPrimExpr(prim, f ty, a)

    | TRecordExpr (baseOpt, fields, ty, a) ->
      let baseOpt = baseOpt |> Option.map go

      let fields =
        fields
        |> List.map (fun (name, init, a) -> name, go init, a)

      TRecordExpr(baseOpt, fields, f ty, a)

    | TMatchExpr (cond, arms, ty, a) ->
      let arms =
        arms
        |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

      TMatchExpr(go cond, arms, f ty, a)
    | TNavExpr (sub, mes, ty, a) -> TNavExpr(go sub, mes, f ty, a)
    | TNodeExpr (kind, args, resultTy, a) -> TNodeExpr(kind, List.map go args, f resultTy, a)
    | TBlockExpr (isRec, stmts, last) -> TBlockExpr(isRec, List.map (stmtMap f) stmts, go last)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

let exprToLoc expr =
  let _, loc = exprExtract expr
  loc

// -----------------------------------------------
// TStmt
// -----------------------------------------------

let stmtToLoc (stmt: TStmt) : Loc =
  match stmt with
  | TExprStmt expr -> exprToLoc expr
  | TLetValStmt (_, _, loc) -> loc
  | TLetFunStmt (_, _, _, _, _, loc) -> loc
  | TTyDeclStmt (_, _, _, _, loc) -> loc
  | TOpenStmt (_, loc) -> loc
  | TModuleStmt (_, _, loc) -> loc
  | TModuleSynonymStmt (_, _, loc) -> loc

let stmtMap (onTy: Ty -> Ty) (stmt: TStmt) : TStmt =
  let onPat pat = patMap onTy pat
  let onPats pats = List.map (patMap onTy) pats
  let onExpr expr = exprMap onTy expr
  let onStmt stmt = stmtMap onTy stmt
  let onStmts stmts = List.map (stmtMap onTy) stmts

  match stmt with
  | TExprStmt expr -> TExprStmt(onExpr expr)
  | TLetValStmt (pat, init, loc) -> TLetValStmt(onPat pat, onExpr init, loc)
  | TLetFunStmt (serial, isRec, vis, args, body, loc) -> TLetFunStmt(serial, isRec, vis, onPats args, onExpr body, loc)
  | TTyDeclStmt (serial, vis, tyArgs, tyDef, loc) -> TTyDeclStmt(serial, vis, tyArgs, tyDef, loc)
  | TOpenStmt (path, loc) -> TOpenStmt(path, loc)
  | TModuleStmt (name, body, loc) -> TModuleStmt(name, onStmts body, loc)
  | TModuleSynonymStmt (name, path, loc) -> TModuleSynonymStmt(name, path, loc)

// -----------------------------------------------
// TModule
// -----------------------------------------------

let emptyVars: TreeMap<VarSerial, VarDef> = TMap.empty varSerialCompare

// -----------------------------------------------
// TProgram
// ----------------------------------------------

module TProgram =
  let foldStmt (folder: 'S -> TStmt -> 'S) (state: 'S) (modules: TProgram) : 'S =
    modules
    |> List.fold (fun state (m: TModule) -> m.Stmts |> List.fold folder state) state

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
