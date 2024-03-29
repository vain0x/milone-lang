module rec nativeptr.Program

// See x_native_code.md in docs.

open Std.Own
open Std.Ptr
open Std.Region

let private memAlloc (count: int) (size: int) : voidptr =
  __nativeFun ("milone_region_alloc", count, size)

let private memSet (dest: voidptr) (value: uint8) (count: int) =
  let _ =
    (__nativeFun ("memset", dest, int value, unativeint count): voidptr)

  ()

let private strcpy (dest: nativeptr<char>) (src: InPtr<char>) : nativeptr<char> = __nativeFun ("strcpy", dest, src)

let private testBasic () =
  let buf = memAlloc 1 8
  memSet buf 255uy 8
  assert (Ptr.read (__nativeCast buf: InPtr<int>) = -1)

  // Conversion to int.
  assert (unativeint buf <> 0un)

let private testVoidPtrAvailable () =
  let mutEnv: voidptr = __nativeCast 42un
  let constEnv: VoidInPtr = __nativeCast mutEnv
  assert (__nativeCast constEnv = 42un)

let private testNullPtr () =
  let nullVoidPtr: voidptr = Ptr.nullPtr
  assert (__nativeCast nullVoidPtr = 0un)

  let nullVoidInPtr: VoidInPtr = Ptr.nullPtr
  assert (__nativeCast nullVoidInPtr = 0un)

  let nullNativePtr: nativeptr<float> = Ptr.nullPtr
  assert (__nativeCast nullNativePtr = 0un)

  let nullInPtr: InPtr<float> = Ptr.nullPtr
  assert (__nativeCast nullInPtr = 0un)

  let nullOutPtr: OutPtr<float> = Ptr.nullPtr
  assert (__nativeCast nullOutPtr = 0un)

let private testPtrInvalid () =
  let danglingPtr: nativeptr<int64> = Ptr.invalid 8un
  assert (unativeint danglingPtr = 8un)

let private testPtrCast () =
  // Upcast.
  let voidPtr: voidptr = Ptr.cast (Ptr.nullPtr: nativeptr<byte>)
  let voidInPtr: VoidInPtr = Ptr.cast (Ptr.nullPtr: InPtr<int>)
  let intOutPtr: OutPtr<int> = Ptr.cast (Ptr.nullPtr: nativeptr<int>)

  // Downcast.
  let intPtr: nativeptr<int> = Ptr.cast (Ptr.nullPtr: voidptr)
  let objOutPtr: OutPtr<obj> = Ptr.cast (Ptr.nullPtr: InPtr<string>)

  // Own type can be cast.
  let uintPtrOwn: Own<nativeptr<uint>> =
    Ptr.cast (Own.acquire (Ptr.nullPtr: voidptr))

  let _ = Own.release uintPtrOwn
  ()

let private testAsIn () =
  let mp: nativeptr<int> = Ptr.nullPtr
  // InPtr<int>
  let kp = Ptr.asIn mp
  assert (kp = Ptr.nullPtr)

  let mq: voidptr = Ptr.nullPtr
  // InPtr<int>
  let kq = Ptr.asIn mq
  assert (kq = Ptr.nullPtr)

let private testAsNative () =
  let kp: InPtr<int> = Ptr.nullPtr
  // nativeptr<int>
  let mp = Ptr.asNative kp
  assert (mp = Ptr.nullPtr)

  let kq: VoidInPtr = Ptr.nullPtr
  // voidptr
  let mq = Ptr.asNative kq
  assert (mq = Ptr.nullPtr)

let private testPtrDistance () =
  let p: nativeptr<int> = Ptr.invalid 0x8000un
  let q: nativeptr<int> = Ptr.invalid 0x8020un
  assert (Ptr.distance p p = 0n)
  assert (Ptr.distance p q = 8n)
  assert (Ptr.distance q p = -8n)

let private testEquality () =
  let np: nativeptr<int> = Ptr.nullPtr
  let p: nativeptr<int> = __nativeCast 42un
  assert (p <> np)

  let nq: InPtr<int> = Ptr.nullPtr
  let q: InPtr<int> = __nativeCast 42un
  assert (q <> nq)

let private sizeOfPointee (ptr: nativeptr<'T>) : int = sizeof<'T>

let private testSizeOf () =
  assert (sizeof<char> = 1)
  assert (sizeof<byte> = 1)
  assert (sizeof<int16> = 2)
  assert (sizeof<int> = 4)
  assert (sizeof<int64> = 8)

  let w = sizeof<unativeint>
  assert (sizeof<voidptr> = w)
  assert (sizeof<nativeptr<obj * obj>> = w)
  assert (sizeof<string> = w * 2)
  assert (sizeof<unit -> unit> = w * 2)

  assert (sizeof<int64 * byte * byte> = 16) // 8 + 1 + 1 + padding

  // Size of generic type.
  assert (sizeOfPointee (Ptr.nullPtr: nativeptr<obj * obj>) = sizeof<obj * obj>)

let private testPtrOf () =
  let x = 42
  let p: InPtr<int> = &&x
  assert (Ptr.read p = 42)

let private testPtrSelect () =
  let p: nativeptr<int> =
    __nativeCast (memAlloc 4 sizeof<int>)

  assert (Ptr.select p.[0] = p)
  assert (unativeint (Ptr.select p.[1]) - unativeint p = unativeint sizeof<int>)

let private testPtrRead () =
  __nativeStmt ("int array[] = {1, 2, 4, 8, 16};")
  let p: nativeptr<int> = __nativeExpr "array"

  assert (Ptr.read p = 1)
  assert (Ptr.read p.[0] = 1)
  assert (Ptr.read p.[4] = 16)

  let q: InPtr<int> = Ptr.asIn p
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

  let q: OutPtr<int> = __nativeExpr "&data[7]"
  Ptr.write q 77
  let q = Ptr.asNative q
  assert (Ptr.read q = 77)

let private testRegionAlloc () =
  let p: OutPtr<int> = Region.alloc 2
  Ptr.write p.[0] 42
  Ptr.write p.[1] 43
  // It's now initialized.
  let p: nativeptr<int> = Ptr.asNative p

  assert (Ptr.read p = 42)
  assert (Ptr.read p.[1] = 43)

let private testPtrAddress () =
  let n = 42
  // The result isn't used yet cast shouldn't get removed.
  let _ = unativeint &&n
  ()

let main _ =
  testBasic ()
  testVoidPtrAvailable ()
  testNullPtr ()
  testPtrInvalid ()
  testPtrCast ()
  testAsIn ()
  testAsNative ()
  testPtrDistance ()
  testEquality ()
  testSizeOf ()
  testPtrOf ()
  testPtrSelect ()
  testPtrRead ()
  testPtrWrite ()
  testRegionAlloc ()
  testPtrAddress ()
  0
