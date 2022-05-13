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

/// filename -> (contents option)
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
  /// `<`
  | LeftAngleToken of adjacent: bool
  /// `>`
  | RightAngleToken
  /// `[<`
  | LeftAttrToken
  /// `>]`
  | RightAttrToken
  /// `&`
  | AmpToken
  /// `&&`
  | AmpAmpToken of prefix: bool
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
  | EqualToken
  /// `^`
  | HatToken
  /// `^^^`
  | HatHatHatToken
  /// `<=`
  | LeftEqualToken
  /// `<<`
  | LeftLeftToken
  /// `<<<`
  | LeftLeftLeftToken
  /// `<>`
  | LeftRightToken
  /// `>=`
  | RightEqualToken
  /// `-`
  | MinusToken of minusPrefix: bool
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
  /// `&&`
  | PtrOfUnary

/// Binary operator.
[<NoEquality; NoComparison>]
type Binary =
  /// `*` Multiplication
  | MulBinary
  /// `/` Division
  | DivBinary
  /// `%`
  | ModuloBinary
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
  /// `&&`
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

/// Type parameter list.
///
/// `'<', 'T list, ('>' option)`
type ATyParamList = Pos * Name list * Pos option

/// Type argument list.
///
/// `'<', Type list, ('>' option)`
type ATyArgList = Pos * ATy list * Pos option

/// Type expression in AST.
[<NoEquality; NoComparison>]
type ATy =
  | AMissingTy of Pos

  /// Named type with potential qualifiers and type arguments,
  /// e.g. `int`, `TMap.AssocMap<K, V>`.
  ///
  /// quals: `(name, '.' option) list`
  | AAppTy of quals: (Name * Pos) list * Name * ATyArgList option

  /// Type variable, e.g. `'T`.
  | AVarTy of Name

  /// `'(' Ty ')'`.
  | AParenTy of lPos: Pos * ATy * rPos: Pos option

  /// Type suffix, e.g. `T list`.
  | ASuffixTy of ATy * Name

  /// Tuple type, e.g. `int * string`, `T * T * T`.
  ///
  /// `starPos` is position of the first star.
  | ATupleTy of ATy list * starPos: Pos

  /// Function type, e.g. `int -> string`.
  | AFunTy of ATy * arrowPos: Pos * ATy

/// Pattern in AST.
[<NoEquality; NoComparison>]
type APat =
  | AMissingPat of Pos

  | ALitPat of Lit * Pos

  /// Pattern that is non-keyword identifier.
  /// Variable (`x`), wildcard (`_`) or variant (`None`).
  | AIdentPat of (Vis * Pos) option * Name

  /// E.g. `(_)`.
  | AParenPat of lPos: Pos * APat * rPos: Pos option

  /// E.g. `[ x; y; z ]`.
  | AListPat of lPos: Pos * itemPats: APat list * rPos: Pos option

  /// Navigation, e.g. `Foo.Bar`.
  | ANavPat of APat * dotPos: Pos * Name

  /// Application. e.g. `Some x`.
  ///
  /// Used only for variant destruction.
  /// AFunDeclPat is used for `let`.
  | AAppPat of APat * middlePos: Pos * APat

  /// `::`
  | AConsPat of APat * opPos: Pos * APat

  /// E.g. `x, y, z`.
  ///
  /// `lPos` is at first `,` if non-unit, otherwise `(` if unit.
  | ATuplePat of lPos: Pos * APat list * rOpt: Pos option

  /// E.g. `(Some x) as opt`.
  | AAsPat of APat * asPos: Pos * Name

  /// Type ascription, e.g. `x: int`.
  | AAscribePat of APat * colonPos: Pos * ATy

  /// E.g. `l | r`
  | AOrPat of APat * pipePos: Pos * APat

/// Declaration of variant in AST.
///
/// `('|', Name, ('of' (label? Ty))?)`
///
/// Pipe position can be previous position of name.
///
/// E.g. `| Card of Suit * Rank` (with `of`)
/// or `| Joker` (without `of`).
type AVariantDecl = Pos * Name * (Pos * (Pos option * ATy) list) option

/// Field declaration in AST.
///
/// E.g. `Name: string`.
type AFieldDecl = Name * ATy * Pos

/// Let expression in AST.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ALetContents =
  | LetVal of IsRec * APat * equalPos: Pos * init: AExpr
  | LetFun of IsRec * Vis * Name * argPats: APat list * resultTyOpt: (Pos * ATy) option * equalPos: Pos * body: AExpr

/// Body of type declaration in AST.
[<NoEquality; NoComparison>]
type ATyDeclBody =
  /// E.g. `type Serial = int`.
  | ATySynonymDeclBody of ATy

  | AUnionTyDeclBody of AVariantDecl list
  | ARecordTyDeclBody of lPos: Pos * AFieldDecl list * rPos: Pos option

/// Expression in AST.
[<NoEquality; NoComparison>]
type AExpr =
  /// Used when syntax error has occurred.
  | AMissingExpr of Pos

  | ALitExpr of Lit * Pos

  /// E.g. `x`, `f<'T>`.
  | AIdentExpr of Name * ATyArgList option

  /// `'(' Expr ')'`.
  | AParenExpr of lPos: Pos * AExpr * rPos: Pos option

  /// List literal, e.g. `[]`, `[ 2; 3 ]`.
  | AListExpr of lPos: Pos * AExpr list * rPos: Pos option

  /// Record literal, e.g. `{}`, `{ X = 1; Y = 2 }`, `{ r with X = n }`.
  ///
  /// - `withClause`: `Expr 'with'`
  /// - `fields`: `Name '=' Expr`
  | ARecordExpr of
    lPos: Pos *
    withClause: (AExpr * Pos option) option *
    fields: (Name * Pos * AExpr) list *
    rPos: Pos option

  /// `if cond then body else alt`.
  | AIfExpr of ifPos: Pos * cond: AExpr * thenPos: Pos * body: AExpr * alt: (Pos * AExpr) option

  /// `match cond with (| pat when guard -> body)*`
  ///
  /// arm: `'|', Pat, ('when' Expr), '->', Expr
  | AMatchExpr of
    matchPos: Pos *
    cond: AExpr *
    withPos: Pos option *
    arms: (Pos option * APat * (Pos * AExpr) option * Pos * AExpr) list

  /// `fun pat1 pat2 ... -> body`
  | AFunExpr of funPos: Pos * argPats: APat list * arrowPos: Pos * AExpr

  /// Navigation, e.g. `s.Length`.
  | ANavExpr of AExpr * dotPos: Pos * Name

  /// E.g. `s.[i]`.
  | AIndexExpr of AExpr * dotPos: Pos * lPos: Pos * AExpr * rPos: Pos option

  /// Unary operation, e.g. `-x`.
  | AUnaryExpr of Unary * opPos: Pos * AExpr

  /// Binary operation, e.g. `x + y`, `f x`.
  ///
  /// Position is either that of operator (when binary isn't app) or position of LHS (when binary is app).
  | ABinaryExpr of Binary * AExpr * opPos: Pos * AExpr

  /// Range syntax, e.g. `first..last`.
  ///
  /// (`first .. step .. last` is unimplemented.)
  | ARangeExpr of AExpr * dotDot: Pos * AExpr

  /// Tuple construction or unit literal, e.g. `()`, `2, "two"`.
  ///
  /// `lPos` is at first ',' if non-unit or `(` if unit. It also can be some position.
  | ATupleExpr of lPos: Pos * items: AExpr list * rOpt: Pos option

  /// Type ascription, e.g. `None: int option`.
  | AAscribeExpr of AExpr * colonPos: Pos * ATy

  /// Semicolon-separated expressions.
  | ASemiExpr of AExpr list * AExpr * leadingPos: Pos

  /// `let ... in next`
  | ALetExpr of letPos: Pos * ALetContents * next: AExpr option

[<NoEquality; NoComparison>]
type ADecl =
  | AExprDecl of AExpr

  /// `let pat = init` or `let f pats... = body`
  | ALetDecl of letPos: Pos * ALetContents

  /// Type synonym declaration, e.g. `type UserId = int`.
  | ATySynonymDecl of typePos: Pos * Vis * Name * tyParamList: ATyParamList option * equalPos: Pos * ATy

  /// Discriminated union type declaration, e.g. `type Result = | Ok | Err of int`.
  | AUnionTyDecl of typePos: Pos * Vis * Name * tyParamList: ATyParamList option * equalPos: Pos * AVariantDecl list

  /// Record type declaration, e.g. `type Pos = { X: int; Y: int }`.
  | ARecordTyDecl of
    typePos: Pos *
    Vis *
    Name *
    tyParamList: ATyParamList option *
    equalPos: Pos *
    lPos: Pos *
    fields: AFieldDecl list *
    rPos: Pos option

  /// Open statement, e.g. `open System.IO`.
  | AOpenDecl of openPos: Pos * Name list

  /// Module synonym statement, e.g. `module T = System.Text`.
  | AModuleSynonymDecl of modulePos: Pos * Name * equalPos: Pos * path: Name list

  /// Module statement, e.g.
  ///
  /// ```fsharp
  /// module Pos =
  ///   let zero = 0, 0
  /// ```
  | AModuleDecl of modulePos: Pos * IsRec * Vis * Name * equalPos: Pos * body: ADecl list

  /// Declaration attached with an attribute.
  /// `[< attributes >] next`
  | AAttrDecl of l: Pos * contents: AExpr * r: Pos option * next: ADecl

/// Root of AST, a result of parsing single source file.
type AModuleHead = Pos * Name list

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
