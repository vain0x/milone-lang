/// Immutable array implementation.
module rec MiloneStd.StdArray

// This is safe wrapper of mutable array.
// Public functions should be written carefully so that they are pure,
// i.e. observable side-effects don't happen.

/// Immutable array.
type Array<'T> = __ConstArray<'T>

// -----------------------------------------------
// Creation
// -----------------------------------------------

/// Gets an empty array.
///
/// PERF: O(1) time, no allocation.
let empty (): Array<_> = __constArrayOfMut (__mutArrayCreate 0)

/// Creates an array with specified length. i'th item is `f i`.
///
/// E.g. `init f 3` is `[| f 0; f 1; f 2 |]`.
let init (len: int) (f: int -> _): Array<_> =
  if len <= 0 then
    assert (len = 0)
    empty ()
  else
    let array = __mutArrayCreate len

    let rec arrayInitLoop i =
      if i < len then
        let item = f i
        __mutArraySet i item array
        arrayInitLoop (i + 1)

    arrayInitLoop 0
    __constArrayOfMut array

/// Creates an array with specified length. Items are all equal to specified value.
///
/// E.g. `replicate 3 x` is `[| x; x; x |]`.
let replicate (len: int) item: Array<_> = init len (fun (_: int) -> item)

/// Creates an array with specified length. i'th item is `i`.
///
/// E.g. `range 3` is `[| 0; 1; 2 |]`.
let range (len: int): Array<int> = init len (fun (i: int) -> i)

// -----------------------------------------------
// Get
// -----------------------------------------------

/// Gets the length of array.
///
/// O(1) time.
let length (array: Array<_>): int = __constArrayLength array

/// Gets whether the array is empty (that is, length is zero).
///
/// O(1) time.
let isEmpty (array: Array<_>): bool = length array = 0

/// Gets the i'th item of array.
///
/// O(1) time.
let tryItem (i: int) (array: Array<_>): _ option =
  if uint i < uint (length array) then
    Some(__constArrayGet i array)
  else
    None

// -----------------------------------------------
// Search
// -----------------------------------------------

// let findIndex (pred: _ -> bool) (array: Array<_>): int option

// let findLastIndex (pred: _ -> bool) (array: Array<_>): int option

// let lowerBound, upperBound, equalRange

// -----------------------------------------------
// Split
// -----------------------------------------------

/// Gets a contiguous part of specified array.
///
/// Boundary exceeding is just ignored.
/// Intersection of (start .. endIndex-1) and (0 .. len-1) is used.
///
/// O(1) time, no allocation.
let slice (start: int) (endIndex: int) (array: Array<_>): Array<_> =
  let len = length array
  let start = if start >= 0 then start else 0
  let endIndex = if endIndex < len then endIndex else len

  if start < endIndex then
    __constArraySlice start endIndex array
  else
    empty ()

let skip (skipLen: int) (array: Array<_>): Array<_> = slice skipLen (length array) array

let truncate (takeLen: int) (array: Array<_>): Array<_> = slice 0 takeLen array

let splitAt (index: int) (array: Array<_>): Array<_> * Array<_> =
  slice 0 index array, slice index (length array) array

/// Tries to split an array into a pair of head item and tail part.
///
/// E.g. `[| x1; x2; ... |]` => `Some (x1, [| x2; ... |])`
let uncons (array: Array<_>): (_ * Array<_>) option =
  let len = length array

  if len = 0 then
    None
  else
    let head = __constArrayGet 0 array
    let tail = __constArraySlice 1 len array
    Some(head, tail)

// -----------------------------------------------
// Batch operations
// -----------------------------------------------

let mapi (f: int -> _ -> _) (array: Array<_>): Array<_> =
  init (length array) (fun (i: int) -> f i (__constArrayGet i array))

let map (f: _ -> _) (array: Array<_>): Array<_> =
  init (length array) (fun (i: int) -> f (__constArrayGet i array))

let choose (f: _ -> _ option) (src: Array<_>): Array<_> =
  let len = length src
  let dest = __mutArrayCreate len

  // si: number of items read from src.
  // di: number of items written to dest.
  let rec chooseLoop di si =
    if si = len then
      di
    else
      match f (__constArrayGet si src) with
      | Some value ->
          __mutArraySet di value dest
          chooseLoop (di + 1) (si + 1)

      | None -> chooseLoop di (si + 1)

  let di = chooseLoop 0 0

  if di = 0 then
    empty ()
  else
    __constArrayOfMut (__mutArraySlice 0 di dest)

let filter (pred: _ -> bool) (src: Array<_>): Array<_> =
  choose (fun item -> if pred item then Some item else None) src

let fold folder state (array: Array<_>) =
  let len = length array

  let rec arrayFoldLoop state i =
    if i = len then
      state
    else
      arrayFoldLoop (folder state (__constArrayGet i array)) (i + 1)

  arrayFoldLoop state 0

// TODO: scan, collect, flatten, partition, partition2

// let sortWith compare (array: Array<_>): Array<_> =

let ofList (xs: _ list): Array<_> =
  let len =
    let rec listLengthLoop acc xs =
      match xs with
      | [] -> acc
      | _ :: xs -> listLengthLoop (acc + 1) xs

    listLengthLoop 0 xs

  let dest = __mutArrayCreate len

  let rec ofListLoop i xs =
    match xs with
    | [] -> assert (i = len)
    | x :: xs ->
        __mutArraySet i x dest
        ofListLoop (i + 1) xs

  ofListLoop 0 xs
  __constArrayOfMut dest

let toList (array: Array<_>): _ list =
  let rec toListLoop acc i =
    if i = 0 then
      acc
    else
      toListLoop (__constArrayGet (i - 1) array :: acc) (i - 1)

  toListLoop [] (length array)
