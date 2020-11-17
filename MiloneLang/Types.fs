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
type Lit =
  | BoolLit of bool
  | IntLit of int
  | CharLit of char
  | StrLit of string

/// Visibility.
type Vis =
  | PrivateVis
  | PublicVis

/// Tree to generate a string for debugging.
type DumpTree = DumpTree of heading: string * body: DumpTree list * next: DumpTree list

// -----------------------------------------------
// Errors
// -----------------------------------------------

[<RequireQualifiedAccess>]
type TyUnifyLog =
  | SelfRec
  | Mismatch

[<RequireQualifiedAccess>]
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
type Unary =
  /// `-` Negation
  | NegUnary

/// Binding power.
type Bp =
  | PrefixBp
  | MulBp
  | AddBp
  | ConsBp
  /// `|>`
  | PipeBp
  /// Comparison.
  | CmpBp
  | AndBp
  | OrBp

/// Binary operator.
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
type AArm =
  /// (pattern, guard, body).
  | AArm of APat * AExpr * AExpr * Pos

/// Declaration of variant in AST.
///
/// E.g. `| Card of Suit * Rank` (with `of`)
/// or `| Joker` (without `of`).
type AVariant =
  /// (identifier, payload-type).
  | AVariant of Ident * ATy option * Pos

/// Field declaration in AST.
///
/// E.g. `Name: string`.
type AFieldDecl = Ident * ATy * Pos

/// Let expression in AST.
type ALet =
  | ALetVal of Vis * APat * AExpr * AExpr * Pos
  | ALetFun of Vis * Ident * args: APat list * AExpr * AExpr * Pos

/// Body of type declaration in AST.
type ATyDecl =
  /// E.g. `type Serial = int`.
  | ATySynonymDecl of ATy

  | AUnionTyDecl of AVariant list
  | ARecordTyDecl of AFieldDecl list

/// Expression in AST.
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

/// Serial number of nominal values: variables, functions, or variants.
type VarSerial = Serial

/// Serial number of functions. This is essentially a "subtype" of VarSerial.
type FunSerial = Serial

/// Serial number of variants. This is essentially as "subtype" of VarSerial.
type VariantSerial = Serial

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
type StorageModifier =
  /// On stack.
  | AutoSM

  /// On static storage.
  | StaticSM

type NameCtx = NameCtx of AssocMap<Serial, Ident> * lastSerial: Serial

// FIXME: Not used?
type ScopeSerial = Serial

/// Stack of local scopes.
type ScopeChain = AssocMap<string, Serial * Ident> list

/// Scope chains, vars and types.
type Scope = ScopeChain * ScopeChain

/// Namespace membership.
type NameTree = NameTree of AssocMap<Serial, Serial list>

/// Type constructor.
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

  /// Nominal type. Union or record.
  | RefTyCtor of TySerial

/// Type of expressions.
type Ty =
  | ErrorTy of Loc

  /// Type variable to be bound or quantified..
  | MetaTy of Serial * Loc

  /// Type application.
  | AppTy of TyCtor * Ty list

/// Potentially polymorphic type.
type TyScheme = TyScheme of TySerial list * Ty

/// Type specification.
type TySpec = TySpec of Ty * Trait list

/// Trait, a constraint about types.
// NOTE: `trait` is a reserved word in F#.
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
type TyDecl =
  | TySynonymDecl of Ty * Loc

  /// Union type.
  /// Variants: (ident, serial, has-payload, payload type).
  | UnionTyDecl of Ident * variants: (Ident * VarSerial * bool * Ty) list * Loc

  | RecordTyDecl of Ident * fields: (Ident * Ty * Loc) list * Loc

/// Type definition.
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ident * Ty * Loc

  | UniversalTyDef of Ident * TySerial * Loc

  | SynonymTyDef of Ident * TySerial list * Ty * Loc

  | UnionTyDef of Ident * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * Loc

  //// Module is a type so that it can be used as namespace.
  | ModuleTyDef of Ident * Loc

/// Definition of named value in high-level IR.
type VarDef =
  | VarDef of Ident * StorageModifier * Ty * Loc
  | FunDef of Ident * Arity * TyScheme * Loc
  | VariantDef of Ident * TySerial * hasPayload: bool * payloadTy: Ty * variantTy: Ty * Loc

/// Pattern in high-level IR.
type HPat =
  | HLitPat of Lit * Loc

  /// `[]`
  | HNilPat of itemTy: Ty * Loc

  | HNonePat of itemTy: Ty * Loc
  | HSomePat of itemTy: Ty * Loc

  /// `_`
  | HDiscardPat of Ty * Loc

  /// Variable or variant pattern.
  | HRefPat of VarSerial * Ty * Loc

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
type HExpr =
  | HLitExpr of Lit * Loc

  /// Use of named value: variable, function or variant.
  | HRefExpr of VarSerial * Ty * Loc

  | HPrimExpr of HPrim * Ty * Loc

  | HRecordExpr of HExpr option * fields: (Ident * HExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of target: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `str.Length`
  | HNavExpr of HExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | HInfExpr of InfOp * HExpr list * Ty * Loc

  | HLetValExpr of Vis * pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * Vis * isMainFun: bool * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | HOpenExpr of Ident list * Loc
  | HModuleExpr of Serial * body: HExpr * next: HExpr * Loc
  | HErrorExpr of string * Loc

[<RequireQualifiedAccess>]
type MonoMode =
  | Monify
  | RemoveGenerics

// -----------------------------------------------
// KIR types
// -----------------------------------------------

// KIR is continuation passing style (CPS) intermediate representation.

type JointSerial = Serial

/// Primitive in KIR.
///
/// Number of args/results/conts depends on the kind of prim.
/// Prim signature is written as `N/M/K` denoting to use N args, M results, K conts.
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
type KTerm =
  | KLitTerm of Lit * Loc
  | KVarTerm of VarSerial * Ty * Loc
  | KFunTerm of FunSerial * Ty * Loc
  | KVariantTerm of VariantSerial * Ty * Loc

  /// Tag of variant. An integer ID of the variant in union.
  | KTagTerm of VariantSerial * Loc

  | KLabelTerm of VarSerial * Ty * Loc
  | KNilTerm of itemTy: Ty * Loc
  | KNoneTerm of itemTy: Ty * Loc
  | KUnitTerm of Loc

/// Node (statement) in KIR.
type KNode =
  /// Jump to joint.
  | KJumpNode of JointSerial * args: KTerm list * Loc

  /// Return from the current fun.
  | KReturnNode of VarSerial * args: KTerm list * Loc

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
type KJointBinding = KJointBinding of jointSerial: JointSerial * args: VarSerial list * body: KNode * Loc

/// Definition of a fun.
type KFunBinding = KFunBinding of funSerial: VarSerial * args: VarSerial list * body: KNode * Loc

/// Root node of KIR.
type KRoot = KRoot of KFunBinding list

type KVarDef =
  | KLitVarDef of Lit
  | KSelectVarDef of KTerm * KPath

// -----------------------------------------------
// MIR types
// -----------------------------------------------

type Label = string

/// Intermediate language between HIR and MIR for match expressions.
[<RequireQualifiedAccess>]
type MatchIR =
  | PatLabel of Label
  | Pat of HPat * nextLabel: Label
  | GoBody of Label
  | BodyLabel of Label
  | Guard of guard: HExpr * nextLabel: Label
  | Body of body: HExpr

/// Built-in 1-arity operation in middle IR.
type MUnary =
  | MNotUnary

  /// Gets raw ptr of string.
  | MStrPtrUnary

  /// Gets length of string.
  | MStrLenUnary

  /// Downcast.
  | MUnboxUnary

  /// Projection. Gets an item of tuple.
  | MProjUnary of index: int

  /// Gets variant tag of union value.
  | MTagUnary

  /// Gets payload of union value, unchecked.
  | MGetVariantUnary of VariantSerial

  | MListIsEmptyUnary

  /// Gets head of list, unchecked.
  | MListHeadUnary

  /// Gets tail of list, unchecked.
  | MListTailUnary

/// Built-in 2-arity operation in middle IR.
type MBinary =
  | MMulBinary
  | MDivBinary
  | MModBinary
  | MAddBinary
  | MSubBinary
  | MEqualBinary
  | MNotEqualBinary
  | MLessBinary
  | MGreaterEqualBinary
  | MStrAddBinary
  | MStrCmpBinary

  /// `s.[i]`
  | MStrIndexBinary

/// Expression in middle IR.
type MExpr =
  | MLitExpr of Lit * Loc

  /// Default value of the type.
  | MDefaultExpr of Ty * Loc

  /// Variable.
  | MRefExpr of VarSerial * Ty * Loc

  /// Procedure.
  | MProcExpr of FunSerial * Ty * Loc

  /// Variant constant.
  | MVariantExpr of TySerial * VariantSerial * Ty * Loc

  /// Variant tag value.
  | MTagExpr of VariantSerial * Loc

  | MUnaryExpr of MUnary * arg: MExpr * resultTy: Ty * Loc
  | MBinaryExpr of MBinary * MExpr * MExpr * resultTy: Ty * Loc

/// Variable initializer in mid-level IR.
type MInit =
  /// Remain uninitialized at first; initialized later by `MSetStmt`.
  | MUninitInit

  | MExprInit of MExpr

  /// Call to primitive.
  | MCallPrimInit of HPrim * args: MExpr list * primTy: Ty

  /// Direct call to procedure.
  | MCallProcInit of callee: MExpr * args: MExpr list * calleeTy: Ty

  /// Indirect call to closure.
  | MCallClosureInit of callee: MExpr * args: MExpr list

  /// Construct a closure, packing environment.
  | MClosureInit of subFunSerial: FunSerial * envSerial: VarSerial

  | MBoxInit of MExpr
  | MConsInit of head: MExpr * tail: MExpr
  | MTupleInit of items: MExpr list
  | MVariantInit of VariantSerial * payload: MExpr

type MTerminator = MExitTerminator of exitCode: MExpr

/// Statement in middle IR.
type MStmt =
  /// Declare a local variable.
  | MLetValStmt of VarSerial * MInit * Ty * Loc

  /// Set to uninitialized local variable.
  | MSetStmt of VarSerial * init: MExpr * Loc

  | MReturnStmt of MExpr * Loc
  | MLabelStmt of Label * Loc
  | MGotoStmt of Label * Loc
  | MGotoIfStmt of MExpr * Label * Loc

  // Only for KIR (comparison prim).
  | MIfStmt of MExpr * MStmt list * MStmt list * Loc

  | MTerminatorStmt of MTerminator * Loc

type MDecl = MProcDecl of FunSerial * isMain: bool * args: (VarSerial * Ty * Loc) list * body: MStmt list * resultTy: Ty * Loc

// -----------------------------------------------
// CIR types
// -----------------------------------------------

type CTyInstance =
  | CTyDeclared
  | CTyDefined

/// Type in C language.
type CTy =
  | CVoidTy
  | CIntTy
  | CUInt32Ty
  | CCharTy
  | CPtrTy of CTy
  | CFunPtrTy of argTys: CTy list * resultTy: CTy
  | CStructTy of Ident
  | CEnumTy of Ident

/// Unary operators in C language.
type CUnary =
  /// `!p`
  | CNotUnary

  /// `*p`
  | CDerefUnary

/// Binary operators in C language.
type CBinary =
  | CMulBinary
  | CDivBinary
  | CModBinary
  | CAddBinary
  | CSubBinary
  | CEqualBinary
  | CNotEqualBinary
  | CLessBinary
  | CLessEqualBinary
  | CGreaterBinary
  | CGreaterEqualBinary

/// Expression in C language.
type CExpr =
  /// `(struct K){}`
  | CDefaultExpr

  | CIntExpr of int
  | CCharExpr of char

  /// E.g. `"hi"`
  | CStrRawExpr of string

  /// E.g. `(struct String){.str = "hi", .len = 2}`
  | CStrObjExpr of string

  /// Variable.
  | CRefExpr of Ident

  /// `(struct T){.x = x, ..}` Initializer.
  | CInitExpr of fields: (Ident * CExpr) list * CTy

  /// Projection. Field access of tuple.
  | CProjExpr of CExpr * index: int

  /// `(T)x`
  | CCastExpr of CExpr * CTy

  /// `a.x`
  | CNavExpr of CExpr * Ident

  /// `p->x`
  | CArrowExpr of CExpr * Ident

  /// `a[i]`
  | CIndexExpr of CExpr * CExpr

  | CCallExpr of CExpr * args: CExpr list
  | CUnaryExpr of CUnary * CExpr
  | CBinaryExpr of CBinary * CExpr * CExpr

/// Statement in C language.
type CStmt =
  /// `x;`
  | CExprStmt of CExpr

  /// `T x = a;`
  | CLetStmt of Ident * init: CExpr option * CTy

  /// `U* x = (U*)malloc(sizeof T);`
  | CLetAllocStmt of Ident * valPtrTy: CTy * varTy: CTy

  /// `x = a;`
  | CSetStmt of CExpr * CExpr

  | CLabelStmt of Label
  | CGotoStmt of Label
  | CGotoIfStmt of CExpr * Label
  | CIfStmt of CExpr * CStmt list * CStmt list
  | CReturnStmt of CExpr option

/// Top-level definition in C language.
type CDecl =
  /// `#error` directive to cause compile error manually.
  | CErrorDecl of message: string * line: int

  /// Definition of struct type including anonymous union.
  /// ```c
  /// struct K {
  ///   fields...;
  ///
  ///   union {  // Omit if no variants.
  ///     variants...;
  ///   };
  /// };
  /// ```
  | CStructDecl of Ident * fields: (Ident * CTy) list * variants: (Ident * CTy) list

  /// Definition of enum type.
  | CEnumDecl of Ident * variants: Ident list

  /// Definition of global var.
  | CStaticVarDecl of Ident * CTy

  | CFunDecl of Ident * args: (Ident * CTy) list * resultTy: CTy * body: CStmt list
