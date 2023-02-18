/// # SharedTypes
///
/// Provides types that are commonly used in syntax part and semantics part.
module rec MiloneShared.SharedTypes

open MiloneShared.TypeIntegers
open MiloneShared.UtilSymbol
open Std.StdPair

let private compareInt (l: int) r = compare l r
let private compareString (l: string) r = compare l r

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

/// Read-write permission.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type RefMode =
  /// nativeptr
  | ReadWrite
  /// InPtr
  | ReadOnly
  /// OutPtr
  | WriteOnly

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
  | ByteLit of byteValue: byte
  | StringLit of stringValue: string

// -----------------------------------------------
// Position and location
// -----------------------------------------------

/// 0-indexed. Row number.
type RowIndex = int

/// 0-indexed. Column number.
type ColumnIndex = int

/// Position. Coordinate in a file.
type Pos = RowIndex * ColumnIndex

/// Range of text.
type Range = Pos * Pos

/// Identity of documents.
/// Document can be a source file, an editor tab, or something else.
type DocId = Symbol

/// Location.
type Loc = Loc of DocId * RowIndex * ColumnIndex

// -----------------------------------------------
// RefMode
// -----------------------------------------------

module RefMode =
  let toInt mode =
    match mode with
    | RefMode.ReadWrite -> 1
    | RefMode.ReadOnly -> 2
    | RefMode.WriteOnly -> 3

  let equals l r = toInt l = toInt r

  let compare l r = compareInt (toInt l) (toInt r)

// -----------------------------------------------
// Position
// -----------------------------------------------

module Pos =
  let compare (l: Pos) (r: Pos) = Pair.compare compareInt compareInt l r

  let toString (pos: Pos) =
    let (y, x) = pos
    string (y + 1) + ":" + string (x + 1)

// -----------------------------------------------
// Location
// -----------------------------------------------

// #generateDocId
/// No location information. Should be fixed.
let noLoc = Loc(Symbol.intern "<noLoc>", 0, 0)

module Loc =
  let ofDocPos (docId: DocId) (pos: Pos) : Loc =
    let y, x = pos
    Loc(docId, y, x)

  let toDocPos (loc: Loc) : DocId * Pos =
    let (Loc(docId, y, x)) = loc
    docId, (y, x)

  let docId (loc: Loc) : DocId =
    let (Loc(docId, _, _)) = loc
    docId

  let toString (Loc(docId, y, x)) =
    Symbol.toString docId + ":" + string (y + 1) + ":" + string (x + 1)

  let equals l r =
    let (Loc(lDoc, ly, lx)) = l
    let (Loc(rDoc, ry, rx)) = r
    Symbol.equals lDoc rDoc && ly = ry && lx = rx

  let compare l r =
    let (Loc(lDoc, ly, lx)) = l
    let (Loc(rDoc, ry, rx)) = r

    let c = Symbol.compare lDoc rDoc

    if c <> 0 then c
    else if ly <> ry then compareInt ly ry
    else compareInt lx rx
