/// # Syntax
///
/// Provides types and functions for syntax
/// and source location information.
///
/// ## Lifecycle
///
/// Source code (string) is split into a list of tokens in `SyntaxTokenize`
/// and converted to an abstract syntax tree (AST) in `SyntaxParse`.
/// Finally AST is converted to HIR in `AstToHir`.
module rec MiloneLang.Syntax

open MiloneLang.Util

// -----------------------------------------------
// Vocabulary types
// -----------------------------------------------

/// Identifier. Name of something.
type Ident = string

/// Visibility.
[<NoEquality; NoComparison>]
type Vis =
  | PrivateVis
  | PublicVis

/// Literal of primitive, non-generic value.
[<Struct; NoEquality; NoComparison>]
type Lit =
  | BoolLit of boolValue: bool
  | IntLit of intValue: int
  | FloatLit of floatText: string
  | CharLit of charValue: char
  | StrLit of stringValue: string

// -----------------------------------------------
// Position and location
// -----------------------------------------------

/// 0-indexed. Row number.
type RowIndex = int

/// 0-indexed. Column number.
type ColumnIndex = int

/// Position. Coordinate in a file.
type Pos = RowIndex * ColumnIndex

/// Identity of documents.
/// Document can be a source file, an editor tab, or something else.
type DocId = string

/// Location.
type Loc = DocId * RowIndex * ColumnIndex

// -----------------------------------------------
// Syntax types
// -----------------------------------------------

/// Words and punctuations in source code.
type Token =
  /// Illegal bytes, etc.
  | ErrorToken

  | BlankToken
  | NewlinesToken
  | CommentToken

  | IntToken of int
  | FloatToken of string
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
  /// `[<`
  | LeftAttrToken
  /// `>]`
  | RightAttrToken
  /// `&`
  | AmpToken
  /// `&&`
  | AmpAmpToken
  /// `&&&`
  | AmpAmpAmpToken
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
  /// `^`
  | HatToken
  /// `^^^`
  | HatHatHatToken
  /// `<=`
  | LeftEqToken
  /// `<<`
  | LeftLeftToken
  /// `<<<`
  | LeftLeftLeftToken
  /// `<>`
  | LeftRightToken
  /// `>=`
  | RightEqToken
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
  /// `|||`
  | PipePipePipeToken
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
  | ExternToken
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
  /// `&&&`
  | BitAndBinary
  /// `|||`
  | BitOrBinary
  /// `^^^`
  | BitXorBinary
  /// `<<<`
  | LeftShiftBinary
  /// `>>>`
  | RightShiftBinary
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
  | AAppTy of quals: Ident list * Ident * ATy list * Pos

  /// Type variable, e.g. `'T`.
  | AVarTy of Ident * Pos

  /// Type suffix, e.g. `T list`.
  | ASuffixTy of ATy * Ident * Pos

  /// Tuple type, e.g. `int * string`.
  | ATupleTy of ATy list * Pos

  /// Function type, e.g. `int -> string`.
  | AFunTy of ATy * ATy * Pos

  /// Native function type for FFI, e.g. `extern fun (string, int, int) -> string`. (Not F#.)
  | ANativeFunTy of ATy list * ATy * Pos

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
type AArm = AArm of pat: APat * guard: AExpr option * body: AExpr * Pos

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
  /// Used when syntax error has occurred.
  | AMissingExpr of Pos

  | ALitExpr of Lit * Pos

  /// E.g. `x`.
  | AIdentExpr of Ident * Pos

  /// List literal, e.g. `[]`, `[2; 3]`.
  | AListExpr of AExpr list * Pos

  /// Record literal, e.g. `{}`, `{ X = 1; Y = 2 }`.
  | ARecordExpr of AExpr option * (Ident * AExpr * Pos) list * Pos

  /// `if cond then body else alt`.
  | AIfExpr of cond: AExpr * body: AExpr * alt: AExpr option * Pos

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
  /// (`first .. step .. last` is unimplemented yet.)
  | ARangeExpr of AExpr * AExpr * Pos

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

  /// Expression with some attribute.
  | AAttrExpr of contents: AExpr * next: AExpr * Pos

/// Root of AST, a result of parsing single source file.
[<NoEquality; NoComparison>]
type ARoot =
  | AExprRoot of AExpr
  | AModuleRoot of Ident * AExpr * Pos

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litTrue = BoolLit true

let litFalse = BoolLit false

let litCmp l r =
  match l, r with
  | BoolLit l, BoolLit r -> compare l r
  | BoolLit _, _ -> -1
  | _, BoolLit _ -> 1

  | IntLit l, IntLit r -> compare l r
  | IntLit _, _ -> -1
  | _, IntLit _ -> 1

  | FloatLit l, FloatLit r -> compare l r
  | FloatLit _, _ -> -1
  | _, FloatLit _ -> 1

  | CharLit l, CharLit r -> compare l r
  | CharLit _, _ -> -1
  | _, CharLit _ -> 1

  | StrLit l, StrLit r -> compare l r

// -----------------------------------------------
// Position
// -----------------------------------------------

let posCmp (l: Pos) (r: Pos) = pairCmp compare compare l r

let posToString ((y, x): Pos) = string (y + 1) + ":" + string (x + 1)

// -----------------------------------------------
// Location
// -----------------------------------------------

/// No location information. Should be fixed.
let noLoc = "<noLoc>", -1, -1

let locToString ((docId, y, x): Loc) =
  docId
  + ":"
  + string (y + 1)
  + ":"
  + string (x + 1)

let locCmp ((lDoc, ly, lx): Loc) ((rDoc, ry, rx): Loc) =
  let c = compare lDoc rDoc
  if c <> 0 then c
  else if ly <> ry then compare ly ry
  else compare lx rx
