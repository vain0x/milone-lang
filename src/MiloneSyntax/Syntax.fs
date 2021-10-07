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
module rec MiloneSyntax.Syntax

open MiloneShared.SharedTypes
open MiloneShared.Util

module TMap = MiloneStd.StdMap

/// Name with ID.
[<NoEquality; NoComparison>]
type Name = Name of string * Pos

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

/// Unary operator.
[<NoEquality; NoComparison>]
type Unary = | MinusUnary

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

/// Type expression in AST.
[<NoEquality; NoComparison>]
type ATy =
  | AMissingTy of Pos

  /// Named type with potential qualifiers and type arguments,
  /// e.g. `int`, `TMap.AssocMap<K, V>`.
  | AAppTy of quals: Name list * Name * ATy list * Pos

  /// Type variable, e.g. `'T`.
  | AVarTy of Name

  /// Type suffix, e.g. `T list`.
  | ASuffixTy of ATy * Name

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

  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the app pattern for technically reason.
  | AFunDeclPat of Vis * Name * APat list

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
type AVariant = AVariant of Name * payloadTyOpt: ATy option * Pos

/// Field declaration in AST.
///
/// E.g. `Name: string`.
type AFieldDecl = Name * ATy * Pos

/// Let expression in AST.
[<NoEquality; NoComparison>]
type ALet =
  | ALetVal of IsRec * APat * AExpr * AExpr * Pos
  | ALetFun of IsRec * Vis * Name * args: APat list * AExpr * AExpr * Pos

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
  | AIdentExpr of Name

  /// List literal, e.g. `[]`, `[2; 3]`.
  | AListExpr of AExpr list * Pos

  /// Record literal, e.g. `{}`, `{ X = 1; Y = 2 }`.
  | ARecordExpr of AExpr option * (Name * AExpr * Pos) list * Pos

  /// `if cond then body else alt`.
  | AIfExpr of cond: AExpr * body: AExpr * alt: AExpr option * Pos

  /// `match cond with (| pat when guard -> body)*`
  | AMatchExpr of cond: AExpr * arms: AArm list * Pos

  /// `fun pat1 pat2 ... -> body`
  | AFunExpr of APat list * AExpr * Pos

  /// Navigation, e.g. `str.Length`.
  | ANavExpr of AExpr * Name * Pos

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
  | ALetExpr of IsRec * APat * AExpr * AExpr * Pos

[<NoEquality; NoComparison>]
type ALetDecl =
  | ALetFunDecl of IsRec * Vis * Name * APat list * AExpr * Pos
  | ALetValDecl of IsRec * APat * AExpr * Pos

[<NoEquality; NoComparison>]
type ADecl =
  | AExprDecl of AExpr

  | ALetDecl of IsRec * APat * AExpr * Pos

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
[<NoEquality; NoComparison>]
type ARoot =
  | AExprRoot of ADecl list
  | AModuleRoot of Name * ADecl list * Pos

// -----------------------------------------------
// Keywords
// -----------------------------------------------

type private KeywordMap = AssocMap<Ident, Token>

// See also <https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/keyword-reference>.
let private keywordMapBuild () : KeywordMap =
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

  let map = TMap.empty compare

  let map =
    miloneKeywords
    |> List.fold (fun map (name, token) -> TMap.add name token map) map

  let map =
    fsharpKeywords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  let map =
    ocamlKeywords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  let map =
    reservedWords
    |> List.fold (fun map name -> TMap.add name reservedToken map) map

  map

// -----------------------------------------------
// Host
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TokenizeHost = { FindKeyword: string -> Token option }

let tokenizeHostNew () : TokenizeHost =
  let keywordMap = keywordMapBuild ()

  { FindKeyword = fun ident -> keywordMap |> TMap.tryFind ident }

// -----------------------------------------------
// Module dependencies
// -----------------------------------------------

/// (projectName, moduleName, pos) list
let findDependentModules ast =
  let rec onDecl decl =
    match decl with
    | AOpenDecl ([ Name (p, _); Name (m, _) ], pos) -> Some(p, m, pos)
    | AModuleSynonymDecl (_, [ Name (p, _); Name (m, _) ], pos) -> Some(p, m, pos)
    | AAttrDecl (_, next, _) -> onDecl next
    | _ -> None

  let decls =
    match ast with
    | AExprRoot decls -> decls
    | AModuleRoot (_, decls, _) -> decls

  decls |> List.choose onDecl
