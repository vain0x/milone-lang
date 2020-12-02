module rec native_fun_ptr.Program

type CompareFun = extern fun (voidconstptr, voidconstptr) -> int

let rawIntArrayNew (len: int): obj = __nativeFun ("int_array_new", len)

let rawIntArrayGet (array: obj) (index: int): int =
  __nativeFun ("int_array_get", array, index)

let rawIntArraySet (array: obj) (index: int) (value: int): unit =
  __nativeFun ("int_array_set", array, index, value)

let rawIntArraySort (array: obj) (len: int): unit =
  let intCompare (l: voidconstptr) (r: voidconstptr) = compare (unbox (__nativeCast l) : int) (unbox (__nativeCast r) : int)

  __nativeFun ("qsort", array, unativeint len, unativeint 4, (__nativeFun intCompare: CompareFun))

let main _ =
  let len = 5
  let array = rawIntArrayNew len
  rawIntArraySet array 0 3
  rawIntArraySet array 1 1
  rawIntArraySet array 2 4
  rawIntArraySet array 3 1
  rawIntArraySet array 4 5

  rawIntArraySort array len

  assert (rawIntArrayGet array 0 = 1)
  assert (rawIntArrayGet array 1 = 1)
  assert (rawIntArrayGet array 2 = 3)
  assert (rawIntArrayGet array 3 = 4)
  assert (rawIntArrayGet array 4 = 5)
  0
