/// Defines the types used in multiple modules.
module rec MiloneLang.Types

/// Unique serial number as identity.
type Serial = int

/// Identifier or name of something.
type Ident = string

/// Literal of primitive value.
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
  | Error of string

// -----------------------------------------------
// Syntax types
// -----------------------------------------------

/// 0-indexed.
type RowIndex = int

/// 0-indexed.
type ColumnIndex = int

/// Position in a file.
type Pos = RowIndex * ColumnIndex

/// Words and punctuations in source code.
type Token =
  | ErrorToken
  | IntToken of int
  | CharToken of char
  | StrToken of string
  | IdentToken of Ident

  // punctuations:
  /// `(`
  | LeftParenToken
  /// `)`
  | RightParenToken
  /// `[`
  | LeftBracketToken
  /// `]`
  | RightBracketToken
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

/// Unary operators in AST.
type Unary =
  /// `-`
  | NegUnary

/// Binding power of operators.
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

/// Binary operators in AST.
type Binary =
  /// `*` Multiplier
  | MulBinary
  /// `/` Divisor
  | DivBinary
  /// `%` Modulo
  | ModBinary
  /// `+` Addition
  | AddBinary
  /// `-` Subtract
  | SubBinary
  /// `=` Equal
  | EqualBinary
  /// `<>` Not Equal
  | NotEqualBinary
  /// `<` Less than
  | LessBinary
  /// `<=` Less than or equal to
  | LessEqualBinary
  /// `>` Greater than
  | GreaterBinary
  /// `>=` Greater than or equal to
  | GreaterEqualBinary
  /// `|>`
  | PipeBinary
  /// `&&`
  | LogAndBinary
  /// `||`
  | LogOrBinary
  /// `f x` Application
  | AppBinary
  /// `::` Cons cell constructor
  | ConsBinary

/// Type expression in AST.
type ATy =
  | AMissingTy of Pos
  | AAppTy of Ident * ATy list * Pos
  | ASuffixTy of ATy * Ident * Pos
  /// Tuple type, e.g. `int * string`.
  | ATupleTy of ATy list * Pos
  /// Function type, e.g. `int -> string`.
  | AFunTy of ATy * ATy * Pos

/// Pattern in AST.
type APat =
  | AMissingPat of Pos
  | ALitPat of Lit * Pos
  | AIdentPat of Ident * Pos
  | AListPat of APat list * Pos
  | ANavPat of APat * Ident * Pos
  /// Variant deconstruction. e.g. `Some x`.
  | AAppPat of APat * APat list * Pos
  /// `::`
  | AConsPat of APat * APat * Pos
  | ATuplePat of APat list * Pos
  | AAsPat of APat * Ident * Pos
  /// Type annotation, e.g. `x: int`.
  | AAnnoPat of APat * ATy * Pos
  | AOrPat of APat * APat * Pos
  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the call pattern.
  | AFunDeclPat of Ident * APat list * Pos

/// Match arm node in AST.
type AArm =
  /// (pattern, guard, body).
  | AArm of APat * AExpr * AExpr * Pos

/// Variant node in AST.
type AVariant =
  /// (identifier, payload-type).
  | AVariant of Ident * ATy option * Pos

/// Let expression in AST.
type ALet =
  | ALetVal of Vis * APat * AExpr * AExpr * Pos
  | ALetFun of Vis * Ident * args: APat list * AExpr * AExpr * Pos

/// Body of type declaration in AST.
type ATyDecl =
  | ATySynonymDecl of ATy
  | AUnionTyDecl of AVariant list

/// Expression in AST.
type AExpr =
  | AMissingExpr of Pos
  | ALitExpr of Lit * Pos
  | AIdentExpr of Ident * Pos
  /// List literal, e.g. `[]`, `[2; 3]`.
  | AListExpr of AExpr list * Pos
  /// condition, then-clause, else-clause.
  | AIfExpr of AExpr * AExpr * AExpr * Pos
  | AMatchExpr of AExpr * AArm list * Pos
  | AFunExpr of APat list * AExpr * Pos
  /// Navigation expression, e.g. `str.Length`.
  | ANavExpr of AExpr * Ident * Pos
  | AIndexExpr of AExpr * AExpr * Pos
  /// Unary operation, e.g. `-x`.
  /// Currently `-` is the only unary operation.
  | AUnaryExpr of Unary * AExpr * Pos
  /// Binary operation, e.g. `x + y`.
  | ABinaryExpr of Binary * AExpr * AExpr * Pos
  /// Range syntax, e.g. `first..last`, `first .. step .. last`.
  | ARangeExpr of AExpr list * Pos
  /// Tuple literal, e.g. `()`, `2, "two"`.
  | ATupleExpr of AExpr list * Pos
  /// Type annotation.
  | AAnnoExpr of AExpr * ATy * Pos
  /// Semicolon-separated expressions.
  | ASemiExpr of AExpr list * Pos
  /// (pattern, initializer, next). Let-in expression.
  | ALetExpr of Vis * APat * AExpr * AExpr * Pos
  /// Type synonym definition, e.g. `type UserId = int`.
  | ATySynonymExpr of Vis * Ident * ATy * Pos
  /// Discriminated union type definition, e.g. `type Result = | Ok | Err of int`.
  | AUnionTyExpr of Vis * Ident * AVariant list * Pos
  | AOpenExpr of Ident list * Pos

/// Root of AST, a result of parsing single source file.
type ARoot =
  | AExprRoot of AExpr
  | AModuleRoot of Ident * AExpr * Pos

// -----------------------------------------------
// Intermediate representation types
// -----------------------------------------------

/// Something to identify documents (source files).
type DocId = string

/// Location.
type Loc = DocId * RowIndex * ColumnIndex

/// Serial number of types.
type TySerial = Serial

/// Serial number of variable/function/variants.
type VarSerial = Serial

/// Serial number of functions.
type FunSerial = Serial

/// Serial number of variants.
type VariantSerial = Serial

/// Count of parameters or arguments.
type Arity = int

/// Let-depth, i.e. the number of ancestral let nodes
/// of the place where the meta type is introduced.
/// Used for polymorphic type inference.
/// E.g. in `let x: 'x = ((let y: 'y = a: 'a); b: 'b)`,
///   `'x`: 0, `'y`: 1, `'a`: 2, `'b`: 1
/// Only one exception: recursive function have let-depth deeper by 1.
type LetDepth = int

type StorageModifier =
  | AutoSM
  | StaticSM

type NameCtx = NameCtx of AssocMap<Serial, Ident> * lastSerial: Serial

type ScopeSerial = Serial

/// Stack of local scopes.
type ScopeChain = AssocMap<string, Serial * Ident> list

/// Scope chains, vars and types.
type Scope = ScopeChain * ScopeChain

/// Namespace of non-local symbols.
type NameTree = NameTree of AssocMap<Serial, Serial list>

/// Type constructors.
type TyCtor =
  | BoolTyCtor
  | IntTyCtor
  | CharTyCtor
  | StrTyCtor
  | ObjTyCtor
  | FunTyCtor
  | TupleTyCtor
  | ListTyCtor
  /// Type reference, i.e. some union type.
  | RefTyCtor of Serial

/// Type of expressions.
type Ty =
  | ErrorTy of Loc
  /// Type variable, i.e. some binding.
  | MetaTy of Serial * Loc
  | AppTy of TyCtor * Ty list

/// Generalized type.
type TyScheme = TyScheme of TySerial list * Ty

/// Type specification.
type TySpec = TySpec of Ty * Trait list

/// Traits: kind of type constraints.
/// NOTE: `trait` is a reserved word in F#.
type Trait =
  | AddTrait of Ty
  | EqTrait of Ty
  | CmpTrait of Ty
  | IndexTrait of lTy: Ty * rTy: Ty * resultTy: Ty
  | ToIntTrait of Ty
  | ToStringTrait of Ty

/// Type declaration.
type TyDecl =
  | TySynonymDecl of ty: Ty * Loc
  /// Union type.
  /// Variants: (ident, serial, has-payload, payload type).
  | UnionTyDecl of Ident * variants: (Ident * VarSerial * bool * Ty) list * Loc

/// Type definition.
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ident * Ty * Loc
  | UnionTyDef of Ident * VariantSerial list * Loc
  | ModuleTyDef of Ident * Loc

/// Variable definition in high-level IR.
type VarDef =
  | VarDef of Ident * StorageModifier * Ty * Loc
  | FunDef of Ident * Arity * TyScheme * Loc
  /// Variant constructor.
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
  /// Variable pattern.
  | HRefPat of VarSerial * Ty * Loc
  | HNavPat of HPat * Ident * Ty * Loc
  | HCallPat of callee: HPat * args: HPat list * Ty * Loc
  /// `::`
  | HConsPat of HPat * HPat * itemTy: Ty * Loc
  | HTuplePat of HPat list * tupleTy: Ty * Loc
  | HAsPat of HPat * VarSerial * Loc
  /// Type annotation pattern, e.g. `x : int`.
  | HAnnoPat of HPat * Ty * Loc
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
  /// Tuple constructor, e.g. `x, y, z`.
  | Tuple
  /// Closure constructor.
  | Closure

/// Expression in HIR.
type HExpr =
  | HLitExpr of Lit * Loc
  /// Variable reference.
  | HRefExpr of VarSerial * Ty * Loc
  | HPrimExpr of HPrim * Ty * Loc
  | HMatchExpr of target: HExpr * (HPat * HExpr * HExpr) list * Ty * Loc
  /// `s.m`
  | HNavExpr of HExpr * Ident * Ty * Loc
  /// Operation with infinite arguments.
  | HInfExpr of InfOp * HExpr list * Ty * Loc
  | HLetValExpr of Vis * pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * Vis * isMainFun: bool * args: HPat list * body: HExpr * next: HExpr * Ty * Loc
  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * TyDecl * Loc
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

/// Primitive in KIR.
type KPrim =
  // Arithmetic:
  | KAddPrim
  | KSubPrim
  | KMulPrim
  | KDivPrim
  | KModPrim

  // Comparison:
  | KEqualPrim
  | KLessPrim

  // Bool:
  | KNotPrim

  // String:
  | KIndexPrim
  | KStrLengthPrim
  | KStrGetSlicePrim

  // List, option:
  | KConsPrim
  | KSomePrim

  // Tuple:
  | KTuplePrim

  // Function, closure:
  | KClosurePrim
  | KCallProcPrim
  | KCallClosurePrim

  // obj:
  | KBoxPrim
  | KUnboxPrim

  // Others:
  | KExitPrim
  | KAssertPrim
  | KCharPrim
  | KIntPrim
  | KStringPrim
  | KPrintfnPrim
  | KInRegionPrim
  | KNativeFunPrim of Ident * Arity

/// Represents an access path to content of data (tuple or union).
type KPath =
  /// N'th field of tuple.
  | KFieldPath of int * Loc

  /// Tag of union.
  | KTagPath of Loc

  /// Payload of union.
  | KPayloadPath of VarSerial * Loc

/// Term (expression) in KIR.
type KTerm =
  | KLitTerm of Lit * Loc
  | KVarTerm of VarSerial * Loc
  | KLabelTerm of VarSerial * Loc
  | KNilTerm of itemTy: Ty * Loc
  | KNoneTerm of itemTy: Ty * Loc

/// Node (statement) in KIR.
type KNode =
  /// Jump to label.
  | KJumpNode of VarSerial * args: KTerm list * Loc

  /// Switch to label based on the value of `cond`.
  | KSwitchNode of cond: KTerm * arms: (KTerm * KNode) list * Loc

  /// Select contents of data (tuple or union).
  | KSelectNode of KTerm * path: KPath * result: VarSerial * cont: KNode * Loc

  /// Execution of primitive.
  /// Do something using args, binds values to results, and then jump to one of continuations (if continue).
  | KPrimNode of KPrim * args: KTerm list * results: VarSerial list * conts: KNode list * Loc

type KFunBinding = KFunBinding of funSerial: VarSerial * args: VarSerial list * body: KNode * Loc

/// Root node of KIR.
type KRoot = KRoot of KFunBinding list * KNode

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

/// Unary operator in middle IR.
/// Or primitive function with single parameter.
type MUnary =
  | MNotUnary
  | MStrPtrUnary
  | MStrLenUnary
  | MUnboxUnary
  /// Projection. Get an item of tuple.
  | MProjUnary of index: int
  /// Get union tag.
  | MTagUnary
  | MGetVariantUnary of VariantSerial
  | MListIsEmptyUnary
  | MListHeadUnary
  | MListTailUnary

/// Binary operator in middle IR.
/// Or primitive function with two parameters.
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
  /// Concatenate two strings.
  | MStrAddBinary
  /// Compare two strings.
  | MStrCmpBinary
  /// Get a char.
  | MStrIndexBinary

/// Expression in middle IR.
type MExpr =
  | MLitExpr of Lit * Loc
  | MDefaultExpr of Ty * Loc
  | MRefExpr of VarSerial * Ty * Loc
  /// Procedure
  | MProcExpr of FunSerial * Ty * Loc
  | MVariantExpr of TySerial * VariantSerial * Ty * Loc
  | MUnaryExpr of MUnary * arg: MExpr * resultTy: Ty * Loc
  | MBinaryExpr of MBinary * left: MExpr * right: MExpr * resultTy: Ty * Loc

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
  | MIndirectInit of MExpr
  | MConsInit of head: MExpr * tail: MExpr
  | MTupleInit of items: MExpr list
  | MVariantInit of VariantSerial * payloadSerial: VarSerial

/// Statement in middle IR.
/// Doesn't introduce global things, e.g. functions.
type MStmt =
  /// Statement to evaluate an expression, e.g. `f ();`.
  | MDoStmt of MExpr * Loc
  /// Declare a local variable.
  | MLetValStmt of VarSerial * MInit * Ty * Loc
  /// Set to uninitialized local variable.
  | MSetStmt of VarSerial * init: MExpr * Loc
  | MReturnStmt of MExpr * Loc
  | MLabelStmt of Label * Loc
  | MGotoStmt of Label * Loc
  | MGotoIfStmt of MExpr * Label * Loc
  | MExitStmt of MExpr * Loc
  | MProcStmt of FunSerial * isMain: bool * args: (VarSerial * Ty * Loc) list * body: MStmt list * resultTy: Ty * Loc

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
  | CCharTy
  | CPtrTy of CTy
  | CFunPtrTy of CTy list * CTy
  | CStructTy of Ident
  | CEnumTy of Ident

/// Unary operators.
type CUnary =
  | CNotUnary
  | CDerefUnary

/// Binary operators in C language.
type CBinary =
  | CMulBinary
  | CDivBinary
  | CModBinary
  | CAddBinary
  | CSubBinary
  /// Equal
  | CEqualBinary
  /// Not Equal
  | CNotEqualBinary
  /// Less than
  | CLessBinary
  /// Less than or equal to
  | CLessEqualBinary
  /// Greater than
  | CGreaterBinary
  /// Greater than or equal to
  | CGreaterEqualBinary

/// Expression in C language.
type CExpr =
  /// `{}`
  | CDefaultExpr
  | CIntExpr of int
  | CCharExpr of char
  | CStrRawExpr of string
  | CStrObjExpr of string
  | CRefExpr of Ident
  /// `(struct T){.x = x, ..}` Initializer.
  | CInitExpr of fields: (Ident * CExpr) list * CTy
  /// Projection. Get an item of tuple.
  | CProjExpr of CExpr * index: int
  | CCastExpr of CExpr * CTy
  | CNavExpr of CExpr * Ident
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
  | CReturnStmt of CExpr option

/// Top-level definition in C language.
type CDecl =
  /// `#error` directive to cause compile error manually.
  | CErrorDecl of message: string * line: int
  | CStructDecl of Ident * fields: (Ident * CTy) list * variants: (Ident * CTy) list
  | CEnumDecl of Ident * variants: Ident list
  | CStaticVarDecl of Ident * CTy
  | CFunDecl of Ident * args: (Ident * CTy) list * CTy * body: CStmt list
