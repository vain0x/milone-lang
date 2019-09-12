module rec Competitive.Helpers

// -----------------------------------------------
// Native functions
// -----------------------------------------------

let scanInt (): int =
  (__nativeFun "scan_int" 1) 0

let rawIntArrayNew (len: int): obj =
  (__nativeFun "int_array_new" 1) len

let rawIntArrayGet (array: obj) (index: int): int =
  (__nativeFun "int_array_get" 2) array index

let rawIntArraySet (array: obj) (index: int) (value: int): obj =
  (__nativeFun "int_array_set" 3) array index value

let rawMemoryCopy (dest: obj) (src: obj) (size: int): obj =
  (__nativeFun "memcpy" 3) dest src size

// -----------------------------------------------
// Polyfills
// -----------------------------------------------

let ignore _ = ()

let listLength xs =
  let rec go len xs =
    match xs with
    | [] ->
      len
    | _ :: xs ->
      go (len + 1) xs
  go 0 xs

// -----------------------------------------------
// Types
// -----------------------------------------------

type TypeTag =
  | TypeTag

let typeToDefault (defaultValue, _, _, _, _, _typeTag) = defaultValue

let typeToSize (_, size, _, _, _, _typeTag) = size

let typeToArrayNew (_, _, arrayNew, _, _, _typeTag) = arrayNew

let typeToArrayGet (_, _, _, arrayGet, _, _typeTag) = arrayGet

let typeToArraySet (_, _, _, _, arraySet, _typeTag) = arraySet

let typeInt = 0, 4, rawIntArrayNew, rawIntArrayGet, rawIntArraySet, TypeTag

// -----------------------------------------------
// Vectors
// -----------------------------------------------

type VectorTag =
  | VectorTag

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
  (itemTy |> typeToArraySet) array index value |> ignore

let rec vectorPush value self =
  let itemTy, array, len, capacity, _vectorTag = self
  if len = capacity then
    let newCapacity = if len = 0 then 16 else capacity * 2
    let newArray = (itemTy |> typeToArrayNew) (newCapacity)
    let copySize = (itemTy |> typeToSize) * len
    rawMemoryCopy newArray array copySize |> ignore
    (itemTy, newArray, len, newCapacity, VectorTag) |> vectorPush value
  else
    self |> vectorSet len value
    itemTy, array, len + 1, capacity, VectorTag

let vectorOfList ty xs =
  let len = xs |> listLength
  let v = vectorNew ty len
  let rec go i xs =
    match xs with
    | [] ->
      assert (i = len)
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
    let v = vectorOfList typeInt [1; 2; 3]
    assert (v |> vectorToLength = 3)
    assert (v |> vectorGet 0 = 1)
    assert (v |> vectorGet 1 = 2)
    assert (v |> vectorGet 2 = 3)

  vectorOfListTest ()
