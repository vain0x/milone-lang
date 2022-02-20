module rec Std.StdArrayBase

// -----------------------------------------------
// MutArray
// -----------------------------------------------

/// UNSAFE: Mutable array. Length is fixed.
///
/// Data mutation must be done carefully in milone-lang.
/// For example, writing an item allocated in inner region to the array
/// will cause use-after-free after leaving the inner region.
type __MutArray<'T> = System.ArraySegment<'T>

/// UNSAFE: Note calling this function is NOT pure, causing side-effects
/// since returned array is distinct value for each calling.
/// (Only one exception is len = 0.)
let internal __mutArrayCreate (len: int) : __MutArray<_> = __MutArray (Array.zeroCreate len)

let internal __mutArraySet (index: int) value (array: __MutArray<_>) =
  let mutable array = array
  array.[index] <- value

/// UNSAFE: Gets a contiguous part of mutable array. Contents are shared.
let internal __mutArraySlice (start: int) (endIndex: int) (array: __MutArray<_>) : __MutArray<_> =
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
let internal __constArrayOfMut (mutArray: __MutArray<'T>) : __ConstArray<'T> = { Inner = mutArray }

let internal __constArrayLength (array: __ConstArray<_>) = array.Inner.Count

let internal __constArrayGet (index: int) (array: __ConstArray<_>) = array.Inner.[index]

/// Gets a contiguous part of array.
let internal __constArraySlice (start: int) (endIndex: int) (array: __ConstArray<_>) : __ConstArray<_> =
  let array = array.Inner
  assert (0 <= start)
  assert (start <= endIndex)
  assert (endIndex <= array.Count)
  { Inner = __MutArray (array.Array, array.Offset + start, endIndex - start) }
