module rec nativeptr.Program

// See x_native_code.md in docs.

module Ptr = Std.Ptr

let private memAlloc (count: int) (size: int) : voidptr =
  __nativeFun ("milone_mem_alloc", count, unativeint size)

let private memSet (dest: voidptr) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, int value, unativeint count): voidptr)

  ()

let private strcpy (dest: nativeptr<char>) (src: __inptr<char>) : nativeptr<char> = __nativeFun ("strcpy", dest, src)

let private testBasic () =
  let buf = memAlloc 1 8
  memSet buf 255uy 8
  assert (Ptr.read (__nativeCast buf: __inptr<int>) = -1)

  // Conversion to int.
  assert (unativeint buf <> 0un)

let private testVoidPtrAvailable () =
  let mutEnv: voidptr = __nativeCast 42un
  let constEnv: __voidinptr = __nativeCast mutEnv
  assert (__nativeCast constEnv = 42un)

let private testNullPtr () =
  let nullVoidPtr: voidptr = __nullptr
  assert (__nativeCast nullVoidPtr = 0un)

  let nullVoidInPtr: __voidinptr = __nullptr
  assert (__nativeCast nullVoidInPtr = 0un)

  let nullNativePtr: nativeptr<float> = __nullptr
  assert (__nativeCast nullNativePtr = 0un)

  let nullInPtr: __inptr<float> = __nullptr
  assert (__nativeCast nullInPtr = 0un)

let private testAsConst () =
  let mp: nativeptr<int> = __nullptr
  // __inptr<int>
  let kp = Ptr.asConst mp
  assert (kp = __nullptr)

  let mq: voidptr = __nullptr
  // __inptr<int>
  let kq = Ptr.asConst mq
  assert (kq = __nullptr)

let private testAsMutable () =
  let kp: __inptr<int> = __nullptr
  // nativeptr<int>
  let mp = Ptr.asMutable kp
  assert (mp = __nullptr)

  let kq: __voidinptr = __nullptr
  // voidptr
  let mq = Ptr.asMutable kq
  assert (mq = __nullptr)

let private testEquality () =
  let np: nativeptr<int> = __nullptr
  let p: nativeptr<int> = __nativeCast 42un
  assert (p <> np)

  let nq: __inptr<int> = __nullptr
  let q: __inptr<int> = __nativeCast 42un
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

let private testPtrOf () =
  let x = 42
  let p: __inptr<int> = &&x
  assert (Ptr.read p = 42)

let private testPtrSelect () =
  let p: nativeptr<int> = __nativeCast (memAlloc 4 __sizeOf<int>)

  assert (Ptr.select p.[0] = p)
  assert (unativeint (Ptr.select p.[1]) - unativeint p = unativeint __sizeOf<int>)

let private testPtrRead () =
  __nativeStmt ("int array[] = {1, 2, 4, 8, 16};")
  let p: nativeptr<int> = __nativeExpr "array"

  assert (Ptr.read p = 1)
  assert (Ptr.read p.[0] = 1)
  assert (Ptr.read p.[4] = 16)

  let q: __inptr<int> = Ptr.asConst p
  assert (Ptr.read q = 1)
  assert (Ptr.read q.[2] = 4)

let private testPtrWrite () =
  __nativeStmt ("int data[8] = { 0 };")
  let p: nativeptr<int> = __nativeExpr "data"

  Ptr.write p 42
  assert (Ptr.read p = 42)
  Ptr.write p.[0] 43
  assert (Ptr.read p = 43)
  Ptr.write p.[3] 39
  assert (Ptr.read p.[3] = 39)

let main _ =
  testBasic ()
  testVoidPtrAvailable ()
  testNullPtr ()
  testAsConst ()
  testAsMutable ()
  testEquality ()
  testSizeOf ()
  testPtrOf ()
  testPtrSelect ()
  testPtrRead ()
  testPtrWrite ()
  0
