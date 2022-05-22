/// # SyntaxTypes
///
/// Provides types for syntax
/// and source location information.
///
/// ## Lifecycle
///
/// Source code (string) is split into a list of tokens in `SyntaxTokenize`
/// and converted to an abstract syntax tree (AST) in `SyntaxParse`.
/// Finally AST is converted to NIR in `NirGen`.
module rec MiloneSyntaxTypes.SyntaxTypes

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.UtilParallel

/// Name with ID.
[<NoEquality; NoComparison>]
type Name = Name of string * Pos

// -----------------------------------------------
// Build System
// -----------------------------------------------

type ProjectName = string
type ModuleName = string

type ProjectDir = string
type SourceCode = string

type ModuleSyntaxError = string * Pos

type ModuleSyntaxData = DocId * TokenizeResult * ARoot * ModuleSyntaxError list

// filename -> (contents option)
type ReadTextFileFun = string -> Future<string option>

type FetchModuleFun = ProjectName -> ModuleName -> Future<ModuleSyntaxData option>

// -----------------------------------------------
// Syntax errors
// -----------------------------------------------

type TokenizeError =
  | InvalidCharLitError
  | InvalidStringLitError
  | InvalidRawIdentError
  | BadTokenError
  | UnknownEscapeSequenceError
  | UndefinedOpTokenError
  | ReservedWordError
  | UnimplNumberSuffixError
  | OtherTokenizeError of msg: string

// -----------------------------------------------
// Tokens
// -----------------------------------------------

/// Words and punctuations in source code.
type Token =
  | ErrorToken of TokenizeError

  | BlankToken
  | NewlinesToken
  | CommentToken

  | IntToken of intText: string * IntFlavor option
  | FloatToken of floatText: string
  | CharToken of char
  | StringToken of string
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
  // `<`
  | LeftAngleToken of adjacent: bool
  // `>`
  | RightAngleToken
  // `[<`
  | LeftAttrToken
  // `>]`
  | RightAttrToken
  // `&`
  | AmpToken
  // `&&`
  | AmpAmpToken of prefix: bool
  // `&&&`
  | AmpAmpAmpToken
  // `->`
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
  | EqualToken
  /// `^`
  | HatToken
  /// `^^^`
  | HatHatHatToken
  // `<=`
  | LeftEqualToken
  // `<<`
  | LeftLeftToken
  // `<<<`
  | LeftLeftLeftToken
  // `<>`
  | LeftRightToken
  // `>=`
  | RightEqualToken
  /// `-`
  | MinusToken of minusPrefix: bool
  /// `%`
  | PercentToken
  /// `|`
  | PipeToken
  // `|>`
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
  | ElseToken
  | FalseToken
  | FunToken
  | IfToken
  | InToken
  | LetToken
  | MatchToken
  | ModuleToken
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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TokenizeHost = { FindKeyword: string -> Token option }

type TokenizeResult = (Token * Pos) list
type TokenizeFullResult = (Token * Pos) list

/// Unary operator.
[<NoEquality; NoComparison>]
type Unary =
  | MinusUnary
  // `&&`
  | PtrOfUnary

/// Binary operator.
[<NoEquality; NoComparison>]
type Binary =
  /// `*`
  | MultiplyBinary
  /// `/`
  | DivideBinary
  /// `%`
  | ModuloBinary
  /// `+`
  | AddBinary
  /// `-`
  | SubtractBinary
  /// `=`
  | EqualBinary
  // `<>`
  | NotEqualBinary
  // `<`
  | LessBinary
  // `<=`
  | LessEqualBinary
  // `>`
  | GreaterBinary
  // `>=`
  | GreaterEqualBinary
  // `&&&`
  | BitAndBinary
  /// `|||`
  | BitOrBinary
  /// `^^^`
  | BitXorBinary
  // `<<<`
  | LeftShiftBinary
  // `>>>`
  | RightShiftBinary
  // `|>`
  | PipeBinary
  // `&&`
  | LogicalAndBinary
  /// `||`
  | LogicalOrBinary
  /// `f x` Functional application
  | AppBinary
  /// `::` Construction
  | ConsBinary

// -----------------------------------------------
// AST
// -----------------------------------------------

/// Type expression in AST.
[<NoEquality; NoComparison>]
type ATy =
  | AMissingTy of Pos

  /// Named type with potential qualifiers and type arguments.
  // E.g. `int`, `TMap.AssocMap<K, V>`.
  | AAppTy of quals: Name list * Name * ATy list * Pos

  /// Type variable, e.g. `'T`.
  | AVarTy of Name

  /// Type suffix, e.g. `T list`.
  | ASuffixTy of ATy * Name

  /// Tuple type, e.g. `int * string`.
  | ATupleTy of ATy list * Pos

  /// Function type.
  // E.g. `int -> string`
  | AFunTy of ATy * ATy * Pos

/// Pattern in AST.
[<NoEquality; NoComparison>]
type APat =
  | AMissingPat of Pos

  | ALitPat of Lit * Pos

  /// Pattern that is non-keyword identifier.
  /// Variable (`x`), wildcard (`_`) or variant (`None`).
  | AIdentPat of Vis * Name

  /// E.g. `[x; y; z]`.
  | AListPat of APat list * Pos

  /// Navigation, e.g. `Foo.Bar`.
  | ANavPat of APat * Name * Pos

  /// Application. e.g. `Some x`.
  ///
  /// Used only for variant destruction.
  /// AFunDeclPat is used for `let`.
  | AAppPat of APat * APat * Pos

  /// `::`
  | AConsPat of APat * APat * Pos

  /// E.g. `x, y, z`.
  | ATuplePat of APat list * Pos

  /// E.g. `(Some x) as opt`.
  | AAsPat of APat * Name * Pos

  /// Type ascription, e.g. `x: int`.
  | AAscribePat of APat * ATy * Pos

  /// E.g. `l | r`
  | AOrPat of APat * APat * Pos

/// Arm of match expression in AST.
// `| pat when guard -> body`
[<Struct; NoEquality; NoComparison>]
type AArm = AArm of pat: APat * guard: AExpr option * body: AExpr * Pos

/// Declaration of variant in AST.
///
/// E.g. `| Card of Suit * Rank` (with `of`)
/// or `| Joker` (without `of`).
[<Struct; NoEquality; NoComparison>]
type AVariant = AVariant of Name * payloadTyOpt: ATy option * Pos

/// Field declaration in AST.
///
/// E.g. `Name: string`.
type AFieldDecl = Name * ATy * Pos

/// Let expression in AST.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ALetContents =
  | LetVal of IsRec * pat: APat * init: AExpr
  | LetFun of IsRec * Vis * Name * argPats: APat list * resultTyOpt: (ATy * Pos) option * body: AExpr

/// Body of type declaration in AST.
[<NoEquality; NoComparison>]
type ATyDeclBody =
  /// E.g. `type Serial = int`.
  | ATySynonymDeclBody of ATy

  | AUnionTyDeclBody of AVariant list
  | ARecordTyDeclBody of AFieldDecl list

/// Expression in AST.
[<NoEquality; NoComparison>]
type AExpr =
  /// Used when syntax error has occurred.
  | AMissingExpr of Pos

  | ALitExpr of Lit * Pos

  // E.g. `x`, `f<'T>`.
  | AIdentExpr of Name * tyArgs: ATy list

  /// List literal, e.g. `[]`, `[2; 3]`.
  | AListExpr of AExpr list * Pos

  /// Record literal, e.g. `{}`, `{ X = 1; Y = 2 }`.
  | ARecordExpr of AExpr option * (Name * AExpr * Pos) list * Pos

  /// `if cond then body else alt`.
  | AIfExpr of cond: AExpr * body: AExpr * alt: AExpr option * Pos

  // `match cond with (| pat when guard -> body)*`
  | AMatchExpr of cond: AExpr * arms: AArm list * Pos

  // `fun pat1 pat2 ... -> body`
  | AFunExpr of APat list * AExpr * Pos

  /// Navigation, e.g. `s.Length`.
  | ANavExpr of AExpr * Name * Pos

  /// E.g. `s.[i]`.
  | AIndexExpr of AExpr * AExpr * Pos

  /// Unary operation, e.g. `-x`.
  | AUnaryExpr of Unary * AExpr * Pos

  /// Binary operation, e.g. `x + y`, `f x`.
  | ABinaryExpr of Binary * AExpr * AExpr * Pos

  /// Range syntax, e.g. `first..last`.
  ///
  /// (`first .. step .. last` is unimplemented yet.)
  | ARangeExpr of AExpr * AExpr * Pos

  /// Tuple construction or unit literal.
  // E.g. `()`, `2, "two"`.
  | ATupleExpr of AExpr list * Pos

  /// Type ascription, e.g. `None: int option`.
  | AAscribeExpr of AExpr * ATy * Pos

  /// Semicolon-separated expressions.
  | ASemiExpr of AExpr list * AExpr * Pos

  | ALetExpr of ALetContents * next: AExpr * Pos

[<NoEquality; NoComparison>]
type ADecl =
  | AExprDecl of AExpr

  | ALetDecl of ALetContents * Pos

  /// Type synonym declaration, e.g. `type UserId = int`.
  | ATySynonymDecl of Vis * Name * tyArgs: Name list * ATy * Pos

  /// Discriminated union type declaration, e.g. `type Result = | Ok | Err of int`.
  | AUnionTyDecl of Vis * Name * tyArgs: Name list * AVariant list * Pos

  /// Record type declaration, e.g. `type Pos = { X: int; Y: int }`.
  | ARecordTyDecl of Vis * Name * tyArgs: Name list * AFieldDecl list * Pos

  /// Open statement, e.g. `open System.IO`.
  | AOpenDecl of Name list * Pos

  /// Module synonym statement, e.g. `module T = System.Text`.
  | AModuleSynonymDecl of Name * Name list * Pos

  /// Module statement, e.g. `module Pos = let zero () = ...`.
  | AModuleDecl of IsRec * Vis * Name * ADecl list * Pos

  /// Expression with some attribute.
  | AAttrDecl of contents: AExpr * next: ADecl * Pos

/// Root of AST, a result of parsing single source file.
type AModuleHead = Name list * Pos

/// Root of AST, a result of parsing single source file.
[<NoEquality; NoComparison>]
type ARoot = ARoot of AModuleHead option * ADecl list

// -----------------------------------------------
// NIR: IR for NameRes
// -----------------------------------------------

type NLoc = Loc
type NName = Ident * NLoc

[<NoEquality; NoComparison>]
type NirGenLog =
  | InvalidVisError
  | NirGenError of string

/// Type term in NIR.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NTy =
  | Bad of NLoc
  | App of quals: NName list * NName * NTy list * NLoc
  | Var of NName
  | Infer of NLoc

  | Fun of NTy * NTy * NLoc
  | Tuple of NTy list * NLoc

/// Pattern in NIR.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NPat =
  // Fundamental:
  | Bad of NLoc
  | Ident of Vis * NName
  | Discard of NLoc
  | Nav of NPat * NName * NLoc
  | As of NPat * NName * NLoc
  | Ascribe of NPat * NTy * NLoc
  | Or of NPat * NPat * NLoc

  // Type-specific:
  | Lit of Lit * NLoc
  | Nil of NLoc
  | Cons of NPat * NPat * NLoc
  | Tuple of NPat list * NLoc
  | VariantApp of NPat * NPat * NLoc

type NArm = NPat * NExpr option * NExpr * NLoc
type NField = NName * NExpr * NLoc

/// Expression in NIR.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NExpr =
  // Fundamental:
  | Bad of NLoc
  | Ident of NName * tyArgs: NTy list
  | Nav of NExpr * NName * NLoc
  | Ascribe of NExpr * NTy * NLoc
  | TyPlaceholder of NTy * NLoc
  | Block of NStmt list * last: NExpr

  // Type-specific:
  | Lit of Lit * NLoc
  | Match of cond: NExpr * NArm list * NLoc
  | Nil of NLoc
  | Record of NExpr option * NField list * NLoc
  | Tuple of NExpr list * NLoc

  // Primitive:
  | Unary of Unary * NExpr * NLoc
  | Binary of Binary * NExpr * NExpr * NLoc
  | Index of NExpr * NExpr * NLoc
  | Slice of arg: NExpr * start: NExpr * endIndex: NExpr * NLoc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NStmt =
  | Expr of NExpr
  | LetVal of pat: NPat * init: NExpr * NLoc
  | LetFun of IsRec * Vis * NName * argPats: NPat list * body: NExpr * NLoc

type NVariantDecl = NName * NTy option * NLoc
type NFieldDecl = NName * NTy * NLoc

[<NoEquality; NoComparison>]
type NModuleDecl = NModuleDecl of IsRec * Vis * NName * NDecl list * NLoc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type NDecl =
  | Stmt of NStmt
  | TySynonym of Vis * NName * tyArgs: NName list * NTy * NLoc
  | Union of Vis * NName * tyArgs: NName list * NVariantDecl list * NLoc
  | Record of Vis * NName * tyArgs: NName list * NFieldDecl list * IsCRepr * NLoc
  | Open of NName list * NLoc
  | ModuleSynonym of NName * NName list * NLoc
  | Module of NModuleDecl

type NRoot = NModuleDecl

type NModuleRoot = DocId * NRoot
