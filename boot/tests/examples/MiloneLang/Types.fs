module rec MiloneLang.Types

/// Location = (rowIndex, columnIndex).
type Loc = int * int

/// Word or punctuation in source code.
[<RequireQualifiedAccess>]
type Token =
  | Bool
    of bool
  | Int
    of int
  | Char
    of char
  | Str
    of string
  | Ident
    of string
  | Do
  | Let
  | Rec
  | If
  | Then
  | Else
  | Match
  | With
  | As
  | When
  /// `(`
  | ParenL
  /// `)`
  | ParenR
  /// `[`
  | BracketL
  /// `]`
  | BracketR
  /// `:`
  | Colon
  /// `.`
  | Dot
  /// `..`
  | Range
  /// `|`
  | Pipe
  /// `->`
  | Arrow
  /// Punctuation.
  | Punct
    of string
  | Private
  | Internal
  | Public
  | Module
  | Namespace
  | Open
  | Type
  | Of
  | Fun
  | In
