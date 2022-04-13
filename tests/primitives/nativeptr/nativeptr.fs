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

let private testAsConst () =
  let mp: nativeptr<int> = __nullptr
  // __constptr<int>
  let kp = Ptr.asConst mp
  assert (kp = __nullptr)

  let mq: voidptr = __nullptr
  // __constptr<int>
  let kq = Ptr.asConst mq
  assert (kq = __nullptr)

let private testAsMutable () =
  let kp: __constptr<int> = __nullptr
  // nativeptr<int>
  let mp = Ptr.asConst kp
  assert (mp = __nullptr)

  let kq: __voidconstptr = __nullptr
  // voidptr
  let mq = Ptr.asConst kq
  assert (mq = __nullptr)

let private testEquality () =
  let np: nativeptr<int> = __nullptr
  let p: nativeptr<int> = __nativeCast 42un
  assert (p <> np)

  let nq: __constptr<int> = __nullptr
  let q: __constptr<int> = __nativeCast 42un
  assert (q <> nq)

let private sizeOfPointee (ptr: nativeptr<'T>) : int = __sizeOf<'T>

let private testSizeOf () =
  assert (__sizeOf<char> = 1)
  assert (__sizeOf<byte> = 1)
  assert (__sizeOf<int16> = 2)
  assert (__sizeOf<int> = 4)
  assert (__sizeOf<int64> = 8)

  let w = __sizeOf<unativeint>
  assert (__sizeOf<voidptr> = w)
  assert (__sizeOf<nativeptr<obj * obj>> = w)
  assert (__sizeOf<string> = w * 2)
  assert (__sizeOf<unit -> unit> = w * 2)

  assert (__sizeOf<int64 * byte * byte> = 16) // 8 + 1 + 1 + padding

  // Size of generic type.
  assert (sizeOfPointee (__nullptr: nativeptr<obj * obj>) = __sizeOf<obj * obj>)

let private testPtrOperator () =
  let x = 42
  let p: __constptr<int> = &&x
  assert (__ptrRead p 0 = 42)

let main _ =
  testVoidPtrAvailable ()
  testNullPtr ()
  testAsConst ()
  testAsMutable ()
  testEquality ()
  testSizeOf ()
  testPtrOperator ()

  let buf = memAlloc 1 8
  memSet buf 255uy 8
  assert (__ptrRead (__nativeCast buf: __constptr<int>) 0 = -1)

  // Conversion to int.
  assert (unativeint buf <> 0un)
  0
