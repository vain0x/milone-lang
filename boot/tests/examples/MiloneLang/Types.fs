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
