/// # SharedTypes
///
/// Provides types that are commonly used in syntax part and semantics part.
module rec MiloneShared.SharedTypes

open MiloneShared.TypeIntegers

// -----------------------------------------------
// Vocabulary types
// -----------------------------------------------

/// Unique number to identify something
/// such as variables, nominal types, etc.
type Serial = int

/// Count of parameters or arguments.
type Arity = int

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

/// Is static variable?
[<NoEquality; NoComparison>]
type IsStatic =
  /// Static variable. (This doesn't imply linkage.)
  | IsStatic

  /// Local variable.
  | NotStatic

/// Assembly binary interface (ABI): how function looks like at machine-code level.
[<NoEquality; NoComparison>]
type FunAbi =
  | MiloneAbi

  /// Compatible with C language.
  | CAbi

/// How the symbol looks to linker.
[<NoEquality; NoComparison>]
type Linkage =
  | InternalLinkage
  | ExternalLinkage of name: string

[<NoEquality; NoComparison>]
type IsMut =
  | IsConst
  | IsMut

[<NoEquality; NoComparison>]
type IsCRepr = IsCRepr of bool

let isCRepr (IsCRepr x) = x

/// Literal of primitive, non-generic value.
[<NoEquality; NoComparison>]
type Lit =
  | BoolLit of boolValue: bool
  | IntLit of intText: string
  | IntLitWithFlavor of string * IntFlavor
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
type Loc = Loc of DocId * RowIndex * ColumnIndex

// -----------------------------------------------
// Position
// -----------------------------------------------

let private pairCompare compare1 compare2 (l1, l2) (r1, r2) =
  let c = compare1 l1 r1
  if c <> 0 then c else compare2 l2 r2

let posCompare (l: Pos) (r: Pos) = pairCompare compare compare l r

let posToString ((y, x): Pos) = string (y + 1) + ":" + string (x + 1)

// -----------------------------------------------
// Location
// -----------------------------------------------

/// No location information. Should be fixed.
let noLoc = Loc("<noLoc>", 0, 0)

let locToString (Loc (docId, y, x)) =
  docId
  + ":"
  + string (y + 1)
  + ":"
  + string (x + 1)

let locCompare (Loc (lDoc, ly, lx)) (Loc (rDoc, ry, rx)) =
  let c = compare lDoc rDoc

  if c <> 0 then c
  else if ly <> ry then compare ly ry
  else compare lx rx

module Loc =
  let ofDocPos (docId: DocId) (pos: Pos) : Loc =
    let y, x = pos
    Loc(docId, y, x)

  let toDocPos (loc: Loc) : DocId * Pos =
    let (Loc (docId, y, x)) = loc
    docId, (y, x)
