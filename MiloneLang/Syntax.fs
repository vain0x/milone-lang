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

/// Is recursive?
[<NoEquality; NoComparison>]
type IsRec =
  | IsRec
  | NotRec

/// Literal of primitive, non-generic value.
[<Struct; NoEquality; NoComparison>]
type Lit =
  | BoolLit of boolValue: bool
  | IntLit of intText: string
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
// Syntax errors
// -----------------------------------------------

type TokenizeError =
  | InvalidCharLitError
  | InvalidStrLitError
  | InvalidRawIdentError
  | BadTokenError
  | UnknownEscapeSequenceError
  | UndefinedOpTokenError
  | ReservedWordError
  | UnimplNumberSuffixError
  | UnimplHexEscapeError
  | OtherTokenizeError of msg: string

let tokenizeErrorToString error =
  match error with
  | InvalidCharLitError -> "Invalid char literal."
  | InvalidStrLitError -> "Invalid string literal."
  | InvalidRawIdentError -> "Invalid raw identifier. Hint: ``write like this``."
  | BadTokenError -> "Invalid characters."

  | UnknownEscapeSequenceError ->
      "Unknown escape sequence. After `\\`, one of these chars is only allowed: `\\` `'` `\"` t r n x. `\\xHH` other than `\\x00` is unimplemented."

  | UndefinedOpTokenError -> "Undefined operator."

  | ReservedWordError ->
      "This word can't be used as identifier, because it's reserved for future expansion of the language."

  | UnimplNumberSuffixError -> "Number literal suffix is unimplemented yet."
  | UnimplHexEscapeError -> "`\\xHH` escape sequence is unimplemented yet, except for `\\x00`."
  | OtherTokenizeError msg -> msg

// -----------------------------------------------
// Syntax types
// -----------------------------------------------

/// Words and punctuations in source code.
type Token =
  | ErrorToken of TokenizeError

  | BlankToken
  | NewlinesToken
  | CommentToken

  | IntToken of intText: string
  | FloatToken of floatText: string
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
  | AAppPat of APat * APat * Pos

  /// `::`
  | AConsPat of APat * APat * Pos

  /// E.g. `x, y, z`.
  | ATuplePat of APat list * Pos

  /// E.g. `(Some x) as opt`.
  | AAsPat of APat * Ident * Pos

  /// Type ascription, e.g. `x: int`.
  | AAscribePat of APat * ATy * Pos

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
  | ALetVal of IsRec * Vis * APat * AExpr * AExpr * Pos
  | ALetFun of IsRec * Vis * Ident * args: APat list * AExpr * AExpr * Pos

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

  /// Type ascription, e.g. `None: int option`.
  | AAscribeExpr of AExpr * ATy * Pos

  /// Semicolon-separated expressions.
  | ASemiExpr of AExpr list * AExpr * Pos

  /// (pattern, initializer, next). Let-in expression.
  | ALetExpr of IsRec * Vis * APat * AExpr * AExpr * Pos

[<NoEquality; NoComparison>]
type ALetDecl =
  | ALetFunDecl of IsRec * Vis * Ident * APat list * AExpr * Pos
  | ALetValDecl of IsRec * Vis * APat * AExpr * Pos

[<NoEquality; NoComparison>]
type ADecl =
  | AExprDecl of AExpr

  | ALetDecl of IsRec * Vis * APat * AExpr * Pos

  /// Type synonym declaration, e.g. `type UserId = int`.
  | ATySynonymDecl of Vis * Ident * tyArgs: Ident list * ATy * Pos

  /// Discriminated union type declaration, e.g. `type Result = | Ok | Err of int`.
  | AUnionTyDecl of Vis * Ident * AVariant list * Pos

  /// Record type declaration, e.g. `type Pos = { X: int; Y: int }`.
  | ARecordTyDecl of Vis * Ident * AFieldDecl list * Pos

  /// Open statement, e.g. `open System.IO`.
  | AOpenDecl of Ident list * Pos

  /// Module synonym statement, e.g. `module T = System.Text`.
  | AModuleSynonymDecl of Ident * Ident list * Pos

  /// Expression with some attribute.
  | AAttrDecl of contents: AExpr * next: ADecl * Pos

/// Root of AST, a result of parsing single source file.
[<NoEquality; NoComparison>]
type ARoot =
  | AExprRoot of ADecl list
  | AModuleRoot of Ident * ADecl list * Pos

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litTrue = BoolLit true

let litFalse = BoolLit false

// int and float are not ordered by value.
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

// -----------------------------------------------
// Keywords
// -----------------------------------------------

type private KeywordMap = AssocMap<Ident, Token>

// See also <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/keyword-reference>.
let private keywordMapBuild (): KeywordMap =
  let miloneKeywords =
    [ "as", AsToken
      "else", ElseToken
      "false", FalseToken
      "fun", FunToken
      "if", IfToken
      "in", InToken
      "let", LetToken
      "match", MatchToken
      "module", ModuleToken
      "of", OfToken
      "open", OpenToken
      "private", PrivateToken
      "public", PublicToken
      "rec", RecToken
      "then", ThenToken
      "true", TrueToken
      "type", TypeToken
      "when", WhenToken
      "with", WithToken ]

  let fsharpKeywords =
    [ "abstract"
      "and"
      "base"
      "begin"
      "class"
      "const"
      "default"
      "delegate"
      "do"
      "done"
      "downcast"
      "downto"
      "elif"
      "end"
      "exception"
      "extern"
      "finally"
      "fixed"
      "for"
      "function"
      "global"
      "inherit"
      "inline"
      "interface"
      "internal"
      "lazy"
      "member"
      "mutable"
      "namespace"
      "new"
      "null"
      "or"
      "override"
      "return"
      "static"
      "struct"
      "to"
      "try"
      "upcast"
      "use"
      "val"
      "void"
      "while"
      "yield" ]

  let ocamlKeywords =
    [ "asr"
      "land"
      "lor"
      "lsl"
      "lsr"
      "lxor"
      "mod"
      "sig" ]

  let reservedWords =
    [ "atomic"
      "break"
      "checked"
      "component"
      "const"
      "constraint"
      "constructor"
      "continue"
      "eager"
      "event"
      "external"
      "functor"
      "include"
      "method"
      "mixin"
      "object"
      "parallel"
      "process"
      "protected"
      "pure"
      "sealed"
      "tailcall"
      "trait"
      "virtual"
      "volatile" ]

  let reservedToken = ErrorToken ReservedWordError

  let map = mapEmpty compare

  let map =
    miloneKeywords
    |> List.fold (fun map (name, token) -> mapAdd name token map) map

  let map =
    fsharpKeywords
    |> List.fold (fun map name -> mapAdd name reservedToken map) map

  let map =
    ocamlKeywords
    |> List.fold (fun map name -> mapAdd name reservedToken map) map

  let map =
    reservedWords
    |> List.fold (fun map name -> mapAdd name reservedToken map) map

  map

// -----------------------------------------------
// Host
// -----------------------------------------------

type TokenizeHost = { FindKeyword: string -> Token option }

let tokenizeHostNew (): TokenizeHost =
  let keywordMap = keywordMapBuild ()

  { FindKeyword = fun ident -> keywordMap |> mapTryFind ident }

// -----------------------------------------------
// Module dependencies
// -----------------------------------------------

/// (projectName, moduleName, pos) list
let findDependentModules ast =
  let rec onDecl decl =
    match decl with
    | AOpenDecl ([ p; m ], pos) -> Some(p, m, pos)
    | AModuleSynonymDecl (_, [ p; m ], pos) -> Some(p, m, pos)
    | AAttrDecl (_, next, _) -> onDecl next
    | _ -> None

  let decls =
    match ast with
    | AExprRoot decls -> decls
    | AModuleRoot (_, decls, _) -> decls

  decls |> List.choose onDecl
