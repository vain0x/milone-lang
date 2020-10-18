/// Defines the types used in multiple modules.
module rec MiloneLang.Types

/// Unique serial number as identity.
type Serial = int

/// Identifier or name of something.
type Ident = string

/// Literal of primitive value.
[<RequireQualifiedAccess>]
type Lit =
  | Bool of bool
  | Int of int
  | Char of char
  | Str of string

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

/// Location.
type Loc = RowIndex * ColumnIndex

/// Words and punctuations in source code.
[<RequireQualifiedAccess>]
type Token =
  | Error
  | Bool of bool
  | Int of int
  | Char of char
  | Str of string
  | Ident of Ident
  /// `(`
  | ParenL
  /// `)`
  | ParenR
  /// `[`
  | BracketL
  /// `]`
  | BracketR
  /// `&`
  | Amp
  /// `&&`
  | AmpAmp
  /// `->`
  | Arrow
  | Colon
  | ColonColon
  | Comma
  | Dot
  | DotDot
  /// `=`
  | Eq
  /// `>`
  | Gt
  /// `>=`
  | GtEq
  /// `<`
  | Lt
  /// `<=`
  | LtEq
  /// `<>`
  | LtGt
  | Minus
  | Percent
  /// `|`
  | Pipe
  /// `|>`
  | PipeGt
  /// `||`
  | PipePipe
  | Plus
  /// `;`
  | Semi
  | Star
  | Slash
  | As
  | Do
  | Else
  | Fun
  | If
  | In
  | Internal
  | Let
  | Match
  | Module
  | Namespace
  | Of
  | Open
  | Private
  | Public
  | Rec
  | Then
  | Type
  | When
  | With

/// Unary operators in AST.
[<RequireQualifiedAccess>]
type UniOp =
  /// `-`
  | Neg

/// Precedence level of binary operators.
[<RequireQualifiedAccess>]
type OpLevel =
  | Prefix
  | Mul
  | Add
  | Cons
  /// `|>`
  | Pipe
  /// Comparison.
  | Cmp
  | And
  | Or

/// Binary operators in AST.
[<RequireQualifiedAccess>]
type Op =
  /// `*` Multiplier
  | Mul
  /// `/` Divisor
  | Div
  /// `%` Modulo
  | Mod
  /// `+` Addition
  | Add
  /// `-` Subtract
  | Sub
  /// `=` Equal
  | Eq
  /// `<>` Not Equal
  | Ne
  /// `<` Less than
  | Lt
  /// `<=` Less than or equal to
  | Le
  /// `>` Greater than
  | Gt
  /// `>=` Greater than or equal to
  | Ge
  /// `|>`
  | Pipe
  /// `&&`
  | And
  /// `||`
  | Or
  /// `f x` Application
  | App
  /// `::` Cons cell constructor
  | Cons

/// Type expression in AST.
[<RequireQualifiedAccess>]
type ATy =
  | Missing of Loc
  | App of Ident * ATy list * Loc
  | Suffix of ATy * Ident * Loc
  /// Tuple type, e.g. `int * string`.
  | Tuple of ATy list * Loc
  /// Function type, e.g. `int -> string`.
  | Fun of ATy * ATy * Loc

/// Pattern in AST.
[<RequireQualifiedAccess>]
type APat =
  | Missing of Loc
  | Lit of Lit * Loc
  | Ident of Ident * Loc
  | ListLit of APat list * Loc
  | Nav of APat * Ident * Loc
  /// Variant deconstruction. e.g. `Some x`.
  | Call of APat * APat list * Loc
  /// `::`
  | Cons of APat * APat * Loc
  | TupleLit of APat list * Loc
  | As of APat * Ident * Loc
  /// Type annotation, e.g. `x: int`.
  | Anno of APat * ATy * Loc
  | Or of APat * APat * Loc
  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the call pattern.
  | Fun of Ident * APat list * Loc

/// Match arm node in AST.
type AArm =
  /// (pattern, guard, body).
  | AArm of APat * AExpr * AExpr * Loc

/// Variant node in AST.
type AVariant =
  /// (identifier, payload-type).
  | AVariant of Ident * ATy option * Loc

/// Let expression in AST.
[<RequireQualifiedAccess>]
type ALet =
  | LetVal of APat * AExpr * AExpr * Loc
  | LetFun of Ident * args: APat list * AExpr * AExpr * Loc

/// Body of type declaration in AST.
[<RequireQualifiedAccess>]
type ATyDecl =
  | Synonym of ATy
  | Union of AVariant list

/// Expression in AST.
[<RequireQualifiedAccess>]
type AExpr =
  | Missing of Loc
  | Lit of Lit * Loc
  | Ident of Ident * Loc
  /// List literal, e.g. `[]`, `[2; 3]`.
  | ListLit of AExpr list * Loc
  /// condition, then-clause, else-clause.
  | If of AExpr * AExpr * AExpr * Loc
  | Match of AExpr * AArm list * Loc
  | Fun of APat list * AExpr * Loc
  /// Navigation expression, e.g. `str.Length`.
  | Nav of AExpr * Ident * Loc
  | Index of AExpr * AExpr * Loc
  /// Unary operation, e.g. `-x`.
  /// Currently `-` is the only unary operation.
  | Uni of UniOp * AExpr * Loc
  /// Binary operation, e.g. `x + y`.
  | Bin of Op * AExpr * AExpr * Loc
  /// Range syntax, e.g. `first..last`, `first .. step .. last`.
  | Range of AExpr list * Loc
  /// Tuple literal, e.g. `()`, `2, "two"`.
  | TupleLit of AExpr list * Loc
  /// Type annotation.
  | Anno of AExpr * ATy * Loc
  /// Semicolon-separated expressions.
  | Semi of AExpr list * Loc
  /// (pattern, initializer, next). Let-in expression.
  | Let of APat * AExpr * AExpr * Loc
  /// Type synonym definition, e.g. `type UserId = int`.
  | TySynonym of Ident * ATy * Loc
  /// Discriminated union type definition, e.g. `type Result = | Ok | Err of int`.
  | TyUnion of Ident * AVariant list * Loc
  | Open of Ident list * Loc

// -----------------------------------------------
// Intermediate representation types
// -----------------------------------------------

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

[<RequireQualifiedAccess>]
type StorageModifier =
  | Auto
  | Static

type NameCtx = NameCtx of AssocMap<Serial, Ident> * lastSerial: Serial

type ScopeSerial = Serial

[<RequireQualifiedAccess>]
type Binding =
  /// Value binding.
  | Var of VarSerial * varIdent: Ident

  /// Type binding.
  | Ty of TySerial * tyIdent: Ident

  /// Parent scope.
  | Parent of ScopeSerial * Scope

/// (scopeSerial, binding) list.
type Scope = (ScopeSerial * Binding) list

/// Type constructors.
[<RequireQualifiedAccess>]
type TyCon =
  | Bool
  | Int
  | Char
  | Str
  | Obj
  | Fun
  | Tuple
  | List
  /// Type reference, i.e. some union type.
  | Ref of Serial

/// Type of expressions.
[<RequireQualifiedAccess>]
type Ty =
  | Error of Loc
  /// Type variable, i.e. some binding.
  | Meta of Serial * Loc
  | Con of TyCon * Ty list

/// Generalized type.
[<RequireQualifiedAccess>]
type TyScheme = ForAll of TySerial list * Ty

/// Type specification.
type TySpec = TySpec of Ty * Trait list

/// Traits: kind of type constraints.
/// NOTE: `trait` is a reserved word in F#.
[<RequireQualifiedAccess>]
type Trait =
  | Add of Ty
  | Eq of Ty
  | Cmp of Ty
  | Index of lTy: Ty * rTy: Ty * resultTy: Ty
  | ToInt of Ty
  | ToString of Ty

/// Type declaration.
[<RequireQualifiedAccess>]
type TyDecl =
  | Synonym of ty: Ty * Loc
  /// Union type.
  /// Variants: (ident, serial, has-payload, payload type).
  | Union of Ident * variants: (Ident * VarSerial * bool * Ty) list * Loc

/// Type definition.
[<RequireQualifiedAccess>]
type TyDef =
  /// Bound type variable.
  | Meta of Ident * Ty * Loc
  | Union of Ident * VariantSerial list * Loc

/// Variable definition in high-level IR.
[<RequireQualifiedAccess>]
type VarDef =
  | Var of Ident * StorageModifier * Ty * Loc
  | Fun of Ident * Arity * TyScheme * Loc
  /// Variant constructor.
  | Variant of Ident * TySerial * hasPayload: bool * payloadTy: Ty * variantTy: Ty * Loc

/// Pattern in AST.
[<RequireQualifiedAccess>]
type HPat =
  | Lit of Lit * Loc
  /// `[]`
  | Nil of itemTy: Ty * Loc
  | OptionNone of itemTy: Ty * Loc
  | OptionSome of itemTy: Ty * Loc
  /// `_`
  | Discard of Ty * Loc
  /// Variable pattern.
  | Ref of VarSerial * Ty * Loc
  | Nav of HPat * Ident * Ty * Loc
  | Call of callee: HPat * args: HPat list * Ty * Loc
  /// `::`
  | Cons of HPat * HPat * itemTy: Ty * Loc
  | Tuple of HPat list * tupleTy: Ty * Loc
  | As of HPat * VarSerial * Loc
  /// Type annotation pattern, e.g. `x : int`.
  | Anno of HPat * Ty * Loc
  | Or of HPat * HPat * Ty * Loc

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

/// Expression in AST.
[<RequireQualifiedAccess>]
type HExpr =
  | Lit of Lit * Loc
  /// Variable reference.
  | Ref of VarSerial * Ty * Loc
  | Prim of HPrim * Ty * Loc
  | Match of target: HExpr * (HPat * HExpr * HExpr) list * Ty * Loc
  /// `s.m`
  | Nav of HExpr * Ident * Ty * Loc
  /// Operation with infinite arguments.
  | Inf of InfOp * HExpr list * Ty * Loc
  | Let of pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | LetFun of FunSerial * isMainFun: bool * args: HPat list * body: HExpr * next: HExpr * Ty * Loc
  /// Type declaration.
  | TyDecl of TySerial * TyDecl * Loc
  | Open of Ident list * Loc
  | Error of string * Loc

[<RequireQualifiedAccess>]
type MonoMode =
  | Monify
  | RemoveGenerics

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
[<RequireQualifiedAccess>]
type MUniOp =
  | Not
  | StrPtr
  | StrLen
  | Unbox
  /// Projection. Get an item of tuple.
  | Proj of index: int
  /// Get union tag.
  | Tag
  | GetVariant of VariantSerial
  | ListIsEmpty
  | ListHead
  | ListTail

/// Binary operator in middle IR.
/// Or primitive function with two parameters.
[<RequireQualifiedAccess>]
type MOp =
  | Mul
  | Div
  | Mod
  | Add
  | Sub
  | Eq
  | Ne
  | Lt
  | Ge
  /// Concatenate two strings.
  | StrAdd
  /// Compare two strings.
  | StrCmp
  /// Get a char.
  | StrIndex

/// Expression in middle IR.
[<RequireQualifiedAccess>]
type MExpr =
  | Lit of Lit * Loc
  | Default of Ty * Loc
  | Ref of VarSerial * Ty * Loc
  /// Procedure
  | Proc of FunSerial * Ty * Loc
  | Variant of TySerial * VariantSerial * Ty * Loc
  | Uni of MUniOp * arg: MExpr * resultTy: Ty * Loc
  | Bin of MOp * left: MExpr * right: MExpr * resultTy: Ty * Loc

/// Variable initializer in mid-level IR.
[<RequireQualifiedAccess>]
type MInit =
  /// Remain uninitialized at first; initialized later by `MStmt.Set`.
  | UnInit
  | Expr of MExpr
  /// Call to primitive.
  | CallPrim of HPrim * args: MExpr list * primTy: Ty
  /// Direct call to procedure.
  | CallProc of callee: MExpr * args: MExpr list * calleeTy: Ty
  /// Indirect call to closure.
  | CallClosure of callee: MExpr * args: MExpr list
  /// Construct a closure, packing environment.
  | Closure of subFunSerial: FunSerial * envSerial: VarSerial
  | Box of MExpr
  | Indirect of MExpr
  | Cons of head: MExpr * tail: MExpr
  | Tuple of items: MExpr list
  | Variant of VariantSerial * payloadSerial: VarSerial

/// Statement in middle IR.
/// Doesn't introduce global things, e.g. functions.
[<RequireQualifiedAccess>]
type MStmt =
  /// Statement to evaluate an expression, e.g. `f ();`.
  | Do of MExpr * Loc
  /// Declare a local variable.
  | LetVal of VarSerial * MInit * Ty * Loc
  /// Set to uninitialized local variable.
  | Set of VarSerial * init: MExpr * Loc
  | Return of MExpr * Loc
  | Label of Label * Loc
  | Goto of Label * Loc
  | GotoIf of MExpr * Label * Loc
  | Exit of MExpr * Loc
  | Proc of FunSerial * isMain: bool * args: (VarSerial * Ty * Loc) list * body: MStmt list * resultTy: Ty * Loc

// -----------------------------------------------
// CIR types
// -----------------------------------------------

[<RequireQualifiedAccess>]
type TyInstance =
  | Declared
  | Defined

/// Type in C language.
[<RequireQualifiedAccess>]
type CTy =
  | Void
  | Int
  | Char
  | Ptr of CTy
  | FunPtr of CTy list * CTy
  | Struct of Ident
  | Enum of Ident

[<RequireQualifiedAccess>]
type CUniOp =
  | Not
  | Deref

[<RequireQualifiedAccess>]
type CBinOp =
  | Mul
  | Div
  | Mod
  | Add
  | Sub
  /// Equal
  | Eq
  /// Not Equal
  | Ne
  /// Less than
  | Lt
  /// Less than or equal to
  | Le
  /// Greater than
  | Gt
  /// Greater than or equal to
  | Ge

/// Expression in C language.
[<RequireQualifiedAccess>]
type CExpr =
  /// `{}`
  | Default
  | Int of int
  | Char of char
  | StrRaw of string
  | StrObj of string
  | Ref of Ident
  /// `(struct T){.x = x, ..}` Initializer.
  | Init of fields: (Ident * CExpr) list * CTy
  /// Projection. Get an item of tuple.
  | Proj of CExpr * index: int
  | Cast of CExpr * CTy
  | Nav of CExpr * Ident
  | Arrow of CExpr * Ident
  /// `a[i]`
  | Index of CExpr * CExpr
  | Call of CExpr * args: CExpr list
  | Uni of CUniOp * CExpr
  | Bin of CBinOp * CExpr * CExpr

/// Statement in C language.
[<RequireQualifiedAccess>]
type CStmt =
  /// `x;`
  | Expr of CExpr
  /// `T x = a;`
  | Let of Ident * init: CExpr option * CTy
  /// `U* x = (U*)malloc(sizeof T);`
  | LetAlloc of Ident * valPtrTy: CTy * varTy: CTy
  /// `x = a;`
  | Set of CExpr * CExpr
  | Label of Label
  | Goto of Label
  | GotoIf of CExpr * Label
  | Return of CExpr option

/// Top-level definition in C language.
[<RequireQualifiedAccess>]
type CDecl =
  /// `#error` directive to cause compile error manually.
  | ErrDir of message: string * line: int
  | Struct of Ident * fields: (Ident * CTy) list * variants: (Ident * CTy) list
  | Enum of Ident * variants: Ident list
  | StaticVar of Ident * CTy
  | Fun of Ident * args: (Ident * CTy) list * CTy * body: CStmt list
