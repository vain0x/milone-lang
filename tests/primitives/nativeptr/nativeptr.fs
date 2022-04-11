module rec nativeptr.Program

// nativeptr<T> is equivalent to pointer type `T *` in C.
// voidptr is `void *` in C.
// obj is `void const *` in C.
// __constptr<T> is equivalent to `T const *` in C. (NOT exists in F#.)
// See also x_native_code.md in docs.

let memAlloc (count: int) (size: int) : voidptr =
  __nativeFun ("milone_mem_alloc", count, unativeint size)

let memSet (dest: voidptr) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, int value, unativeint count): voidptr)

  ()

let strcpy (dest: nativeptr<char>) (src: __constptr<char>) : nativeptr<char> = __nativeFun ("strcpy", dest, src)

let private testEquality () =
  let np : nativeptr<int> = __nativeCast 0un
  let p : nativeptr<int> = __nativeCast 42un
  assert (p = p)
  assert (p <> np)

  let nq : __constptr<int> = __nativeCast 0un
  let q : __constptr<int> = __nativeCast 42un
  assert (q = q)
  assert (q <> nq)

let main _ =
  testEquality ()

  let buf = memAlloc 1 8
  memSet buf 255uy 8
  assert (__ptrRead (__nativeCast buf: __constptr<int>) 0 = -1)

  // Conversion to int.
  assert (unativeint buf <> 0un)
  0
