/// Provides functions, whose implementations use .NET features and work only in F#.
/// Public interface of this module should be compatible with file://./MiloneOnly.milone .
[<AutoOpen>]
module rec MiloneStd.FSharpOnly

open System

let __stringJoin (sep: string) (xs: string list): string = System.String.Join(sep, xs)

// -----------------------------------------------
// MutArray
// -----------------------------------------------

/// UNSAFE: Mutable array. Length is fixed.
///
/// Data mutation must be done carefully in milone-lang.
/// For example, writing an item allocated in inner region to the array
/// will cause use-after-free after leaving the inner region.
type __MutArray<'T> = ArraySegment<'T>

/// UNSAFE: Note calling this function is NOT pure, causing side-effects
/// since returned array is distinct value for each calling.
/// (Only one exception is len = 0.)
let __mutArrayCreate (len: int): __MutArray<_> = __MutArray (Array.zeroCreate len)

let __mutArraySet (index: int) value (array: __MutArray<_>) =
  let mutable array = array
  array.[index] <- value

/// UNSAFE: Gets a contiguous part of mutable array. Contents are shared.
let __mutArraySlice (start: int) (endIndex: int) (array: __MutArray<_>): __MutArray<_> =
  assert (0 <= start)
  assert (start <= endIndex)
  assert (endIndex <= array.Count)
  __MutArray (array.Array, array.Offset + start, endIndex - start)

// -----------------------------------------------
// ConstArray
// -----------------------------------------------

/// Immutable array.
[<Struct; RequireQualifiedAccess; NoEquality; NoComparison>]
type __ConstArray<'T> = { Inner: __MutArray<'T> }

/// Casts a mutable array to immutable array type.
/// Contents are shared. Mutation must not be observed.
let __constArrayOfMut (mutArray: __MutArray<'T>): __ConstArray<'T> = { Inner = mutArray }

let __constArrayLength (array: __ConstArray<_>) = array.Inner.Count

let __constArrayGet (index: int) (array: __ConstArray<_>) = array.Inner.[index]

/// Gets a contiguous part of array.
let __constArraySlice (start: int) (endIndex: int) (array: __ConstArray<_>): __ConstArray<_> =
  let array = array.Inner
  assert (0 <= start)
  assert (start <= endIndex)
  assert (endIndex <= array.Count)
  { Inner = __MutArray (array.Array, array.Offset + start, endIndex - start) }

// -----------------------------------------------
// StrInt
// -----------------------------------------------

let __intOfStr (s: string): int option =
  match Int32.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None
