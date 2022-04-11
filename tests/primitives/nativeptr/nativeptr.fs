module rec nativeptr.Program

// See x_native_code.md in docs.

module Ptr = Std.Ptr

let memAlloc (count: int) (size: int) : voidptr =
  __nativeFun ("milone_mem_alloc", count, unativeint size)

let memSet (dest: voidptr) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, int value, unativeint count): voidptr)

  ()

let strcpy (dest: nativeptr<char>) (src: __constptr<char>) : nativeptr<char> = __nativeFun ("strcpy", dest, src)

let private testVoidPtrAvailable () =
  let mutEnv: voidptr = __nativeCast 42un
  let constEnv: __voidconstptr = __nativeCast mutEnv
  assert (__nativeCast constEnv = 42un)

let private testNullPtr () =
  let nullVoidPtr: voidptr = __nullptr
  assert (__nativeCast nullVoidPtr = 0un)

  let nullVoidConstPtr: __voidconstptr = __nullptr
  assert (__nativeCast nullVoidConstPtr = 0un)

  let nullNativePtr: nativeptr<float> = __nullptr
  assert (__nativeCast nullNativePtr = 0un)

  let nullConstPtr: __constptr<float> = __nullptr
  assert (__nativeCast nullConstPtr = 0un)

let private testEquality () =
  let np: nativeptr<int> = __nullptr
  let p: nativeptr<int> = __nativeCast 42un
  assert (p <> np)

  let nq: __constptr<int> = __nullptr
  let q: __constptr<int> = __nativeCast 42un
  assert (q <> nq)

let main _ =
  testVoidPtrAvailable ()
  testNullPtr ()
  testEquality ()

  let buf = memAlloc 1 8
  memSet buf 255uy 8
  assert (__ptrRead (__nativeCast buf: __constptr<int>) 0 = -1)

  // Conversion to int.
  assert (unativeint buf <> 0un)

  // Try namespace.
  let np: voidptr = Ptr.cast 0un
  assert (np = __nullptr)
  0
