module rec nativeptr.Program

// nativeptr<T> is equivalent to `T *` in C, which exists in F#.
// voidptr is `void *` in C. (Exists in F#.)

// __constptr<T> is equivalent to `T const *` in C. (NOT exists in F#.)
// __voidconstptr is `void const *` in C. (NOT exists in F#.)

let memAlloc (count: int) (size: int): voidptr =
  __nativeFun ("milone_mem_alloc", count, unativeint size)

let memSet (dest: voidptr) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, int value, unativeint count): voidptr)

  ()

let strcpy (dest: nativeptr<char>) (src: __constptr<char>): nativeptr<char> = __nativeFun ("strcpy", dest, src)

let main _ =
  let buf = memAlloc 1 8
  memSet buf (uint8 255) 8
  assert ((unbox (__nativeCast buf: obj): int) = -1)

  // Conversion to int.
  assert (unativeint buf <> unativeint 0)
  0
