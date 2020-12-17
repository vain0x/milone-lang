module rec native_fun_ptr.Program

// __nativeFun<P, T> is a language extension to describe a function pointer type: P -> T.
// For zero-parameter function, use unit as P.
// For multi-parameter function, use tuple type as P.
// For void-returning function, use unit as T.
// (ABI is same as C.)

type CompareFun = __nativeFun<obj * obj, int>

let memAlloc (len: int) (size: int): voidptr =
  __nativeFun ("milone_mem_alloc", len, unativeint size)

let sortIntArray (array: nativeptr<int>) (len: int): unit =
  let intCompare (l: obj) (r: obj) =
    compare (unbox (__nativeCast l): int) (unbox (__nativeCast r): int)

  __nativeFun
    ("qsort", (__nativeCast array: voidptr), unativeint len, unativeint 4, (__nativeFun intCompare: CompareFun))

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
