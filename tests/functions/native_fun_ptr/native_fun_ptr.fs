module rec native_fun_ptr.Program

type CompareFun = extern fun (__voidconstptr, __voidconstptr) -> int

let memAlloc (len: int) (size: int): voidptr =
  __nativeFun ("milone_mem_alloc", len, unativeint size)

let sortIntArray (array: nativeptr<int>) (len: int): unit =
  let intCompare (l: __voidconstptr) (r: __voidconstptr) =
    compare (unbox (__nativeCast l): int) (unbox (__nativeCast r): int)

  __nativeFun ("qsort", (__nativeCast array: obj), unativeint len, unativeint 4, (__nativeFun intCompare: CompareFun))

let main _ =
  let len = 5

  let array: nativeptr<int> =
    memAlloc len (__sizeOfVal 0) |> __nativeCast

  __ptrWrite array 0 3
  __ptrWrite array 1 1
  __ptrWrite array 2 4
  __ptrWrite array 3 1
  __ptrWrite array 4 5

  sortIntArray array len

  let array: __constptr<int> = __nativeCast array
  assert (__ptrRead array 0 = 1)
  assert (__ptrRead array 1 = 1)
  assert (__ptrRead array 2 = 3)
  assert (__ptrRead array 3 = 4)
  assert (__ptrRead array 4 = 5)
  0
