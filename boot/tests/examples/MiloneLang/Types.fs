module rec MiloneLang.Types

/// Unique serial number as identity.
type Serial = int

/// Identifier or name of something.
type Ident = string

/// Literal of primitive value.
[<RequireQualifiedAccess>]
type Lit =
  | Bool
    of bool
  | Int
    of int
  | Char
    of char
  | Str
    of string

/// Tree to generate a string for debugging.
type DumpTree =
  | DumpTree
    of heading:string * body:DumpTree list * next:DumpTree list

// -----------------------------------------------
// Syntax types
// -----------------------------------------------

/// 0-indexed.
type RowIndex = int

/// 0-indexed.
type ColumnIndex = int

/// Location.
type Loc = RowIndex * ColumnIndex

/// Words and punctuations in source code.
[<RequireQualifiedAccess>]
type Token =
  | Error
  | Bool
    of bool
  | Int
    of int
  | Char
    of char
  | Str
    of string
  | Ident
    of Ident
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
  | Missing
    of Loc
  | Ident
    of Ident * Loc
  | Suffix
    of ATy * Ident * Loc
  /// Tuple type, e.g. `int * string`.
  | Tuple
    of ATy list * Loc
  /// Function type, e.g. `int -> string`.
  | Fun
    of ATy * ATy * Loc

/// Pattern in AST.
[<RequireQualifiedAccess>]
type APat =
  | Missing
    of Loc
  | Lit
    of Lit * Loc
  | Ident
    of Ident * Loc
  | ListLit
    of APat list * Loc
  | Nav
    of APat * Ident * Loc
  /// Variant deconstruction. e.g. `Some x`.
  | Call
    of APat * APat list * Loc
  /// `::`
  | Cons
    of APat * APat * Loc
  | TupleLit
    of APat list * Loc
  | As
    of APat * Ident * Loc
  /// Type annotation, e.g. `x: int`.
  | Anno
    of APat * ATy * Loc
  | Or
    of APat * APat * Loc
  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the call pattern.
  | Fun
    of Ident * APat list * Loc

/// Match arm node in AST.
type AArm =
  /// (pattern, guard, body).
  | AArm
    of APat * AExpr * AExpr * Loc

/// Variant node in AST.
type AVariant =
  /// (identifier, payload-type).
  | AVariant
    of Ident * ATy list * Loc

/// Let expression in AST.
[<RequireQualifiedAccess>]
type ALet =
  | LetVal
    of APat * AExpr * AExpr * Loc
  | LetFun
    of Ident * args:APat list * AExpr * AExpr * Loc

/// Body of type declaration in AST.
[<RequireQualifiedAccess>]
type ATyDecl =
  | Synonym
    of ATy
  | Union
    of AVariant list

/// Expression in AST.
[<RequireQualifiedAccess>]
type AExpr =
  | Missing
    of Loc
  | Lit
    of Lit * Loc
  | Ident
    of Ident * Loc
  /// List literal, e.g. `[]`, `[2; 3]`.
  | ListLit
    of AExpr list * Loc
  /// condition, then-clause, else-clause. Else clause is `None` is missing.
  | If
    of AExpr * AExpr * AExpr * Loc
  | Match
    of AExpr * AArm list * Loc
  | Fun
    of APat list * AExpr * Loc
  /// Navigation expression, e.g. `str.Length`.
  | Nav
    of AExpr * Ident * Loc
  | Index
    of AExpr * AExpr * Loc
  /// Unary operation, e.g. `-x`.
  /// Currently `-` is the only unary operation.
  | Uni
    of UniOp * AExpr * Loc
  /// Binary operation, e.g. `x + y`.
  | Bin
    of Op * AExpr * AExpr * Loc
  /// Range syntax, e.g. `first..last`, `first .. step .. last`.
  | Range
    of AExpr list * Loc
  /// Tuple literal, e.g. `()`, `2, "two"`.
  | TupleLit
    of AExpr list * Loc
  /// Type annotation.
  | Anno
    of AExpr * ATy * Loc
  /// Semicolon-separated expressions.
  | Semi
    of AExpr list * Loc
  /// (pattern, initializer, next). Let-in expression.
  | Let
    of APat * AExpr * AExpr * Loc
  /// Type synonym definition, e.g. `type UserId = int`.
  | TySynonym
    of Ident * ATy * Loc
  /// Discriminated union type definition, e.g. `type Result = | Ok | Err of int`.
  | TyUnion
    of Ident * AVariant list * Loc
  | Open
    of Ident list * Loc
