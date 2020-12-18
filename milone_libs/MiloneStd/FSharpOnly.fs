[<AutoOpen>]
module rec MiloneStd.FSharpOnly

open System

let __stringJoin (sep: string) (xs: string list): string = System.String.Join(sep, xs)

// -----------------------------------------------
// MutArray
// -----------------------------------------------

type __MutArray<'T> = ArraySegment<'T>

let __mutArrayCreate (len: int): __MutArray<_> = __MutArray (Array.zeroCreate len)

let __mutArraySet (index: int) value (array: __MutArray<_>) =
  let mutable array = array
  array.[index] <- value

let __mutArraySlice (start: int) (endIndex: int) (array: __MutArray<_>): __MutArray<_> =
  assert (0 <= start)
  assert (start <= endIndex)
  assert (endIndex <= array.Count)
  __MutArray (array.Array, array.Offset + start, endIndex - start)

// -----------------------------------------------
// ConstArray
// -----------------------------------------------

[<Struct; RequireQualifiedAccess; NoEquality; NoComparison>]
type __ConstArray<'T> = { Inner: __MutArray<'T> }

let __constArrayOfMut (mutArray: __MutArray<'T>): __ConstArray<'T> = { Inner = mutArray }

let __constArrayLength (array: __ConstArray<_>) = array.Inner.Count

let __constArrayGet (index: int) (array: __ConstArray<_>) = array.Inner.[index]

let __constArraySlice (start: int) (endIndex: int) (array: __ConstArray<_>): __ConstArray<_> =
  let array = array.Inner
  assert (0 <= start)
  assert (start <= endIndex)
  assert (endIndex <= array.Count)
  { Inner = __MutArray (array.Array, array.Offset + start, endIndex - start) }
