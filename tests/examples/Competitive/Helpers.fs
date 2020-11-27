module rec Competitive.Helpers

// -----------------------------------------------
// Native functions
// -----------------------------------------------

let scanInt (): int = __nativeFun "scan_int"

let rawIntArrayNew (len: int): obj = __nativeFun ("int_array_new", len)

let rawIntArrayGet (array: obj) (index: int): int =
  __nativeFun ("int_array_get", array, index)

let rawIntArraySet (array: obj) (index: int) (value: int): unit =
  __nativeFun ("int_array_set", array, index, value)

let rawMemoryCopy (dest: obj) (src: obj) (size: int): unit =
  __nativeFun ("int_array_copy", dest, src, size)

// -----------------------------------------------
// Polyfills
// -----------------------------------------------

let ignore _ = ()

let listIsEmpty xs =
  match xs with
  | [] -> true

  | _ -> false

let listLength xs =
  let rec go len xs =
    match xs with
    | [] -> len

    | _ :: xs -> go (len + 1) xs

  go 0 xs

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> go (x :: acc) xs

  go [] xs

let listEq itemEq xs ys =
  let rec go xs ys =
    match xs, ys with
    | [], [] -> true

    | x :: xs, y :: ys -> itemEq x y && go xs ys

    | _ -> false

  go xs ys

let listReplicate item len =
  let rec go acc i =
    if i = len then acc else go (item :: acc) (i + 1)

  go [] 0

let listInit len gen =
  assert (len >= 0)

  let rec go acc i =
    if i = len then listRev acc else go (gen i :: acc) (i + 1)

  go [] 0

let strConcat (xs: string list) =
  /// Get (str, ys) where
  /// `str` is the concatenation of first `xn` items in `xs`
  /// `ys` is a list of the other items
  let rec go xs xn =
    // assert (xn <= listLength xs)
    match xs with
    | [] ->
        assert (xn = 0)
        "", []
    | x :: xs when xn = 1 -> x, xs
    | x :: y :: xs when xn = 2 -> x + y, xs
    | xs ->
        let m = xn / 2
        let l, xs = go xs m
        let r, xs = go xs (xn - m)
        l + r, xs

  let n = xs |> listLength
  let s, xs = go xs n
  assert (xs |> listIsEmpty)
  s

let unitObj = box ()

let intEq (first: int) (second: int) = first = second

let intMin (first: int) (second: int) = if second < first then second else first

let intMax (first: int) (second: int) = if first < second then second else first

let strEq (first: string) (second: string) = first = second

let failwith msg =
  printfn "ERROR %s" msg
  exit 1

// -----------------------------------------------
// Standard IO
// -----------------------------------------------

let scanIntList len = listInit len (fun _ -> scanInt ())

// -----------------------------------------------
// Types
// -----------------------------------------------

type TypeTag = | TypeTag

let typeToDefault (defaultValue, _, _, _, _, _typeTag) = defaultValue

let typeToSize (_, size, _, _, _, _typeTag) = size

let typeToArrayNew (_, _, arrayNew, _, _, _typeTag) = arrayNew

let typeToArrayGet (_, _, _, arrayGet, _, _typeTag) = arrayGet

let typeToArraySet (_, _, _, _, arraySet, _typeTag) = arraySet

let typeInt =
  0, 4, rawIntArrayNew, rawIntArrayGet, rawIntArraySet, TypeTag

// -----------------------------------------------
// Vectors
// -----------------------------------------------

type VectorTag = | VectorTag

let vectorToLength (_, _, len, _, _vectorTag) = len

let vectorNew itemTy len =
  let array = (itemTy |> typeToArrayNew) len
  itemTy, array, len, len, VectorTag

let vectorCheckIndex index self =
  let len = self |> vectorToLength
  if index < 0 || index >= len then
    printfn "ERROR: Out of range (len = %d, index = %d)" len index
    exit 1

let vectorGet (index: int) self =
  self |> vectorCheckIndex index

  let itemTy, array, _, _, _vectorTag = self
  (itemTy |> typeToArrayGet) array index

let vectorSet (index: int) value self =
  self |> vectorCheckIndex index

  let itemTy, array, _, _, _vectorTag = self
  (itemTy |> typeToArraySet) array index value

let rec vectorPush value self =
  let itemTy, array, len, capacity, _vectorTag = self
  if len = capacity then
    let newCapacity = if len = 0 then 16 else capacity * 2
    let newArray = (itemTy |> typeToArrayNew) (newCapacity)
    let copySize = (itemTy |> typeToSize) * len
    rawMemoryCopy newArray array copySize
    (itemTy, newArray, len, newCapacity, VectorTag)
    |> vectorPush value
  else
    self |> vectorSet len value
    itemTy, array, len + 1, capacity, VectorTag

let vectorOfList ty xs =
  let len = xs |> listLength
  let v = vectorNew ty len

  let rec go i xs =
    match xs with
    | [] -> assert (i = len)
    | x :: xs ->
        v |> vectorSet i x
        go (i + 1) xs

  go 0 xs
  v

let scanIntVector len =
  let v = vectorNew typeInt len

  let rec go i =
    if i < len then
      let value = scanInt ()
      v |> vectorSet i value
      go (i + 1)

  go 0
  v

let vectorTest () =
  let refCase () =
    let v = vectorNew typeInt 1
    assert (v |> vectorToLength = 1)
    assert (v |> vectorGet 0 = 0)
    v |> vectorSet 0 42
    assert (v |> vectorGet 0 = 42)

  refCase ()

  let vectorOfListTest () =
    let v = vectorOfList typeInt [ 1; 2; 3 ]
    assert (v |> vectorToLength = 3)
    assert (v |> vectorGet 0 = 1)
    assert (v |> vectorGet 1 = 2)
    assert (v |> vectorGet 2 = 3)

  vectorOfListTest ()
