module rec nativeptr.Program

let memAlloc (count: int) (size: unativeint): obj =
  __nativeFun ("milone_mem_alloc", count, size)

let memSet (dest: obj) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, value, count): obj)

  ()

let strcpy (dest: nativeptr<char>) (src: constptr<char>): nativeptr<char> = __nativeFun ("strcpy", dest, src)

let main _ =
  let buf = memAlloc 1 (unativeint 8)
  memSet buf (uint8 255) 8
  assert ((unbox buf: int) = -1)
  0
