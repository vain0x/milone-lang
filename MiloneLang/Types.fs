/// Defines the types used in multiple modules.
module rec MiloneLang.Types

open MiloneLang.TreeMap

// -----------------------------------------------
// Collections
// -----------------------------------------------

type AssocMap<'K, 'V> = TreeMap<'K, 'V>

type AssocSet<'K> = TreeMap<'K, unit>

// -----------------------------------------------
// Vocabulary
// -----------------------------------------------

/// Unique serial number to identify something
/// such as variables, nominal types, etc.
type Serial = int

/// Identifier. Name of something.
type Ident = string

/// Literal of primitive, non-generic value.
[<Struct>]
[<NoEquality; NoComparison>]
type Lit =
  | BoolLit of boolValue: bool
  | IntLit of intValue: int
  | CharLit of charValue: char
  | StrLit of stringValue: string

/// Visibility.
[<NoEquality; NoComparison>]
type Vis =
  | PrivateVis
  | PublicVis

/// Tree to generate a string for debugging.
[<NoEquality; NoComparison>]
type DumpTree = DumpTree of heading: string * body: DumpTree list * next: DumpTree list

// -----------------------------------------------
// Errors
// -----------------------------------------------

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type TyUnifyLog =
  | SelfRec
  | Mismatch

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type Log =
  | TyUnify of TyUnifyLog * lRootTy: Ty * rRootTy: Ty * lTy: Ty * rTy: Ty
  | TyBoundError of Trait
  | RedundantFieldError of ty: Ident * field: Ident
  | MissingFieldsError of ty: Ident * fields: Ident list
  | Error of string

// -----------------------------------------------
// Syntax types
// -----------------------------------------------

/// 0-indexed. Row number.
type RowIndex = int

/// 0-indexed. Column number.
type ColumnIndex = int

/// Position. Coordinate in a file.
type Pos = RowIndex * ColumnIndex

/// Words and punctuations in source code.
type Token =
  /// Illegal bytes, etc.
  | ErrorToken

  | BlankToken
  | NewlinesToken
  | CommentToken

  | IntToken of int
  | CharToken of char
  | StrToken of string
  | IdentToken of Ident

  /// `'T` etc.
  | TyVarToken of Ident

  // punctuations:
  /// `(`
  | LeftParenToken
  /// `)`
  | RightParenToken
  /// `[`
  | LeftBracketToken
  /// `]`
  | RightBracketToken
  /// `{`
  | LeftBraceToken
  /// `}`
  | RightBraceToken
  /// `<`
  | LeftAngleToken
  /// `>`
  | RightAngleToken
  /// `&`
  | AmpToken
  /// `&&`
  | AmpAmpToken
  /// `->`
  | ArrowToken
  /// `:`
  | ColonToken
  /// `::`
  | ColonColonToken
  /// `,`
  | CommaToken
  /// `.`
  | DotToken
  /// `..`
  | DotDotToken
  /// `=`
  | EqToken
  /// `>=`
  | RightEqToken
  /// `<=`
  | LeftEqToken
  /// `<>`
  | LeftRightToken
  /// `-`
  | MinusToken
  /// `%`
  | PercentToken
  /// `|`
  | PipeToken
  /// `|>`
  | PipeRightToken
  /// `||`
  | PipePipeToken
  /// `+`
  | PlusToken
  /// `;`
  | SemiToken
  /// `/`
  | SlashToken
  /// `*`
  | StarToken

  // keywords:
  | AsToken
  | DoToken
  | ElseToken
  | FalseToken
  | FunToken
  | IfToken
  | InToken
  | InternalToken
  | LetToken
  | MatchToken
  | ModuleToken
  | NamespaceToken
  | OfToken
  | OpenToken
  | PrivateToken
  | PublicToken
  | RecToken
  | ThenToken
  | TrueToken
  | TypeToken
  | WhenToken
  | WithToken

/// Unary operator.
[<NoEquality; NoComparison>]
type Unary =
  /// `-` Negation
  | NegUnary

/// Binary operator.
[<NoEquality; NoComparison>]
type Binary =
  /// `*` Multiplication
  | MulBinary
  /// `/` Division
  | DivBinary
  /// `%` Modulo
  | ModBinary
  /// `+` Addition
  | AddBinary
  /// `-` Subtraction
  | SubBinary
  /// `=`
  | EqualBinary
  /// `<>`
  | NotEqualBinary
  /// `<`
  | LessBinary
  /// `<=`
  | LessEqualBinary
  /// `>`
  | GreaterBinary
  /// `>=`
  | GreaterEqualBinary
  /// `|>`
  | PipeBinary
  /// `&&` Logical and
  | LogAndBinary
  /// `||` Logical or
  | LogOrBinary
  /// `f x` Functional application
  | AppBinary
  /// `::` Construction
  | ConsBinary

/// Type expression in AST.
[<NoEquality; NoComparison>]
type ATy =
  | AMissingTy of Pos

  /// Type application, e.g. `int` or `AssocMap<K, V>`.
  | AAppTy of Ident * ATy list * Pos

  /// Type variable, e.g. `'T`.
  | AVarTy of Ident * Pos

  /// Type suffix, e.g. `T list`.
  | ASuffixTy of ATy * Ident * Pos

  /// Tuple type, e.g. `int * string`.
  | ATupleTy of ATy list * Pos

  /// Function type, e.g. `int -> string`.
  | AFunTy of ATy * ATy * Pos

/// Pattern in AST.
[<NoEquality; NoComparison>]
type APat =
  | AMissingPat of Pos

  | ALitPat of Lit * Pos

  /// Pattern that is non-keyword identifier.
  /// Variable (`x`), wildcard (`_`) or variant (`None`).
  | AIdentPat of Ident * Pos

  /// E.g. `[x; y; z]`.
  | AListPat of APat list * Pos

  /// Navigation, e.g. `Foo.Bar`.
  | ANavPat of APat * Ident * Pos

  /// Application. e.g. `Some x`.
  ///
  /// Used only for variant destruction.
  /// AFunDeclPat is used for `let`.
  | AAppPat of APat * APat list * Pos

  /// `::`
  | AConsPat of APat * APat * Pos

  /// E.g. `x, y, z`.
  | ATuplePat of APat list * Pos

  /// E.g. `(Some x) as opt`.
  | AAsPat of APat * Ident * Pos

  /// Type annotation, e.g. `x: int`.
  | AAnnoPat of APat * ATy * Pos

  /// E.g. `l | r`
  | AOrPat of APat * APat * Pos

  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the app pattern for technically reason.
  | AFunDeclPat of Ident * APat list * Pos

/// Arm of match expression in AST.
///
/// `| pat when guard -> body`
[<Struct>]
[<NoEquality; NoComparison>]
type AArm = AArm of pat: APat * guard: AExpr * body: AExpr * Pos

/// Declaration of variant in AST.
///
/// E.g. `| Card of Suit * Rank` (with `of`)
/// or `| Joker` (without `of`).
[<Struct>]
[<NoEquality; NoComparison>]
type AVariant = AVariant of Ident * payloadTyOpt: ATy option * Pos

/// Field declaration in AST.
///
/// E.g. `Name: string`.
type AFieldDecl = Ident * ATy * Pos

/// Let expression in AST.
[<NoEquality; NoComparison>]
type ALet =
  | ALetVal of Vis * APat * AExpr * AExpr * Pos
  | ALetFun of Vis * Ident * args: APat list * AExpr * AExpr * Pos

/// Body of type declaration in AST.
[<NoEquality; NoComparison>]
type ATyDecl =
  /// E.g. `type Serial = int`.
  | ATySynonymDecl of ATy

  | AUnionTyDecl of AVariant list
  | ARecordTyDecl of AFieldDecl list

/// Expression in AST.
[<NoEquality; NoComparison>]
type AExpr =
  | AMissingExpr of Pos
  | ALitExpr of Lit * Pos

  /// E.g. `x`.
  | AIdentExpr of Ident * Pos

  /// List literal, e.g. `[]`, `[2; 3]`.
  | AListExpr of AExpr list * Pos

  /// Record literal, e.g. `{}`, `{ X = 1; Y = 2 }`.
  | ARecordExpr of AExpr option * (Ident * AExpr * Pos) list * Pos

  /// `if cond then body else alt`. alt is filled with `()` if omit.
  | AIfExpr of cond: AExpr * body: AExpr * alt: AExpr * Pos

  /// `match cond with (| pat when guard -> body)*`
  | AMatchExpr of cond: AExpr * arms: AArm list * Pos

  /// `fun pat1 pat2 ... -> body`
  | AFunExpr of APat list * AExpr * Pos

  /// Navigation, e.g. `str.Length`.
  | ANavExpr of AExpr * Ident * Pos

  /// E.g. `str.[i]`.
  | AIndexExpr of AExpr * AExpr * Pos

  /// Unary operation, e.g. `-x`.
  /// Currently `-` is the only unary operation.
  | AUnaryExpr of Unary * AExpr * Pos

  /// Binary operation, e.g. `x + y`, `f x`.
  | ABinaryExpr of Binary * AExpr * AExpr * Pos

  /// Range syntax, e.g. `first..last`.
  ///
  /// This could be `first .. step .. last` but not supported yet.
  | ARangeExpr of AExpr list * Pos

  /// Tuple construction or unit literal, e.g. `()`, `2, "two"`.
  | ATupleExpr of AExpr list * Pos

  /// Type annotation, e.g. `None: int option`.
  | AAnnoExpr of AExpr * ATy * Pos

  /// Semicolon-separated expressions.
  | ASemiExpr of AExpr list * Pos

  /// (pattern, initializer, next). Let-in expression.
  | ALetExpr of Vis * APat * AExpr * AExpr * Pos

  /// Type synonym declaration, e.g. `type UserId = int`.
  | ATySynonymExpr of Vis * Ident * tyArgs: Ident list * ATy * Pos

  /// Discriminated union type declaration, e.g. `type Result = | Ok | Err of int`.
  | AUnionTyExpr of Vis * Ident * AVariant list * Pos

  /// Record type declaration, e.g. `type Pos = { X: int; Y: int }`.
  | ARecordTyExpr of Vis * Ident * AFieldDecl list * Pos

  /// Open statement, e.g. `open System.IO`.
  | AOpenExpr of Ident list * Pos

/// Root of AST, a result of parsing single source file.
[<NoEquality; NoComparison>]
type ARoot =
  | AExprRoot of AExpr
  | AModuleRoot of Ident * AExpr * Pos

// -----------------------------------------------
// Intermediate representation types
// -----------------------------------------------

/// Identity of documents.
/// Document can be a source file, an editor tab, or something else.
type DocId = string

/// Location.
type Loc = DocId * RowIndex * ColumnIndex

/// Serial number of types.
type TySerial = Serial

/// Serial number of variables.
[<Struct; NoEquality; NoComparison>]
type VarSerial = VarSerial of Serial

/// Serial number of functions.
[<Struct; NoEquality; NoComparison>]
type FunSerial = FunSerial of Serial

/// Serial number of variants.
[<Struct; NoEquality; NoComparison>]
type VariantSerial = VariantSerial of Serial

/// Number of parameters.
type Arity = int

/// Let-depth, i.e. the number of ancestral let nodes
/// of the place where the meta type is introduced.
/// Used for polymorphic type inference.
/// E.g. in `let x: 'x = ((let y: 'y = a: 'a); b: 'b)`,
///   `'x`: 0, `'y`: 1, `'a`: 2, `'b`: 1
/// Only one exception: recursive function have let-depth deeper by 1.
type LetDepth = int

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

/// Type constructor.
[<Struct>]
[<NoEquality; NoComparison>]
type TyCtor =
  | BoolTyCtor
  | IntTyCtor
  | UIntTyCtor
  | CharTyCtor
  | StrTyCtor
  | ObjTyCtor

  /// Ty args must be `[s; t]`.
  | FunTyCtor

  | TupleTyCtor

  /// Ty args must be `[t]`.
  | ListTyCtor

  // Nominal types.
  | SynonymTyCtor of synonymTy: TySerial
  | UnionTyCtor of unionTy: TySerial
  | RecordTyCtor of recordTy: TySerial

  /// Unresolved type. Generated in AstToHir, resolved in NameRes.
  | UnresolvedTyCtor of Serial

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

  /// The type is scalar.
  | ScalarTrait of Ty

  /// The type supports `=`.
  | EqTrait of Ty

  /// The type supports `<`.
  | CmpTrait of Ty

  /// For `l: lTy, r: rTy`, `l.[r]` is allowed.
  | IndexTrait of lTy: Ty * rTy: Ty * resultTy: Ty

  /// Type can be applied to `int`/`uint` function.
  | ToIntTrait of Ty

  /// Type can be applied to `string` function.
  | ToStringTrait of Ty

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

[<Struct; NoEquality; NoComparison>]
type ModuleTySerial = ModuleTySerial of Serial

//// Module is a type so that it can be used as namespace.
[<NoEquality; NoComparison>]
type ModuleTyDef = { Name: Ident; Loc: Loc }

/// Definition of named value in high-level IR.
[<NoEquality; NoComparison>]
type VarDef = VarDef of Ident * StorageModifier * Ty * Loc

[<NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Loc: Loc }

[<NoEquality; NoComparison>]
type VariantDef =
  { Name: Ident
    UnionTySerial: TySerial
    HasPayload: bool
    PayloadTy: Ty
    VariantTy: Ty
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial

[<Struct; NoEquality; NoComparison>]
type TySymbol =
  | MetaTySymbol of tySerial: TySerial
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial
  | ModuleTySymbol of moduleTySerial: ModuleTySerial

/// Pattern in high-level IR.
[<NoEquality; NoComparison>]
type HPat =
  | HLitPat of Lit * Loc

  /// `[]`
  | HNilPat of itemTy: Ty * Loc

  | HNonePat of itemTy: Ty * Loc
  | HSomePat of itemTy: Ty * Loc

  /// `_`
  | HDiscardPat of Ty * Loc

  /// Variable pattern.
  | HRefPat of VarSerial * Ty * Loc

  /// Variant pattern.
  | HVariantPat of VariantSerial * Ty * Loc

  /// Navigation, e.g. `Result.Ok _`.
  | HNavPat of HPat * Ident * Ty * Loc

  /// Variant decomposition, e.g. `Some x`.
  | HCallPat of callee: HPat * args: HPat list * Ty * Loc

  /// `::`
  | HConsPat of HPat * HPat * itemTy: Ty * Loc

  /// e.g. `x, y, z`
  | HTuplePat of HPat list * tupleTy: Ty * Loc

  /// Used to dereference a box inside of pattern matching.
  ///
  /// To match a value `v: obj` with box pattern `box p: T`,
  /// match `unbox v: T` with `p: T`.
  ///
  /// This is only generated internally in AutoBoxing.
  /// Not a part of F# nor milone-lang syntax.
  /// Unlike `:? T`, unboxing is unchecked.
  | HBoxPat of HPat * Loc

  | HAsPat of HPat * VarSerial * Loc

  /// Type annotation, e.g. `x: int`.
  | HAnnoPat of HPat * Ty * Loc

  /// Disjunction.
  | HOrPat of HPat * HPat * Ty * Loc

/// Primitive in high-level IR.
[<RequireQualifiedAccess>]
[<Struct>]
[<NoEquality; NoComparison>]
type HPrim =
  | Add
  | Sub
  | Mul
  | Div
  | Mod
  | Eq
  | Lt
  | Nil
  | Cons
  | OptionNone
  | OptionSome
  | Index
  | Not
  | Exit
  | Assert
  | Box
  | Unbox
  | Printfn
  | StrLength
  | StrGetSlice
  | Char
  | Int
  | UInt
  | String
  | InRegion
  | NativeFun of Ident * Arity

[<RequireQualifiedAccess>]
[<Struct>]
[<NoEquality; NoComparison>]
type InfOp =
  | App

  /// Type annotation `x : 'x`.
  | Anno

  /// `x; y`
  | Semi

  /// Direct call to procedure or primitive.
  | CallProc

  /// Indirect call to closure.
  | CallClosure

  /// Direct call to current procedure at the end of function (i.e. tail-call).
  | CallTailRec

  /// Tuple constructor, e.g. `x, y, z`.
  | Tuple

  /// Closure constructor.
  | Closure

  /// Get an item of tuple.
  | TupleItem of index: int

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
  | HInfExpr of InfOp * HExpr list * Ty * Loc

  | HLetValExpr of Vis * pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * Vis * isMainFun: bool * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | HOpenExpr of Ident list * Loc
  | HModuleExpr of ModuleTySerial * body: HExpr * next: HExpr * Loc
  | HErrorExpr of string * Loc

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type MonoMode =
  | Monify
  | RemoveGenerics

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

  // Scalar comparison:
  /// 2/0/2. The first cont is used if two args equal; or the second otherwise.
  | KEqualPrim

  /// 2/0/2. The first cont is used if the first arg is less than the second; or the second otherwise.
  | KLessPrim

  // Bool:
  /// 1/1/1.
  | KNotPrim

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
