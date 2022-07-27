module rec native_fun_ptr.Program

// See also x_native_code.md in docs.

open Std.Ptr

type private CompareFun = FunPtr<VoidInPtr * VoidInPtr, int>

let private memAlloc (len: uint) (size: uint) : voidptr =
  __nativeFun ("milone_region_alloc", len, size)

let intCompare (l: VoidInPtr) (r: VoidInPtr) =
  compare (Ptr.read (Ptr.cast l: InPtr<int>)) (Ptr.read (Ptr.cast r: InPtr<int>))

let private sortIntArray (array: nativeptr<int>) (len: uint) : unit =
  __nativeFun ("qsort", (Ptr.cast array: voidptr), unativeint len, 4un, (&&intCompare: CompareFun))

let private testSort () =
  let len = 5u

  let array: nativeptr<int> =
    memAlloc len (uint sizeof<int>) |> __nativeCast

  Ptr.write array.[0] 3
  Ptr.write array.[1] 1
  Ptr.write array.[2] 4
  Ptr.write array.[3] 1
  Ptr.write array.[4] 5

  sortIntArray array len

  let array: InPtr<int> = __nativeCast array
  assert (Ptr.read array.[0] = 1)
  assert (Ptr.read array.[1] = 1)
  assert (Ptr.read array.[2] = 3)
  assert (Ptr.read array.[3] = 4)
  assert (Ptr.read array.[4] = 5)

type private UnitFun = FunPtr<unit, int>

let private answer () = 42

let private testUnitFun () =
  __nativeStmt ("""int (*unit_fun)(void) = {0};""", (&&answer: UnitFun))
  let value: int = __nativeExpr "unit_fun()"
  assert (value = 42)

type private UnaryFun = FunPtr<int, int>

let private inc (n: int) : int = n + 1

let private testUnaryFun () =
  __nativeStmt ("""int (*unary_fun)(int) = {0};""", (&&inc: UnaryFun))

  let value: int = __nativeExpr "unary_fun(41)"
  assert (value = 42)

type private VoidFun = FunPtr<int, unit>

let private log (n: int) =
  __nativeStmt ("""printf("f is called: n=%d.\n", {0});""", n)

let private testVoidFun () =
  __nativeStmt ("""void(*void_fun)(int) = {0}; void_fun(42);""", (&&log: VoidFun))

let private plus (x: int) (y: int) = x + y

let private testFunPtrCanBeResult () =
  let getFunPtr () = &&plus
  let p = getFunPtr ()
  assert (p <> Ptr.nullPtr)

let private testFunPtrInvoke () =
  assert (FunPtr.invoke &&answer () = 42)
  assert (FunPtr.invoke &&inc 2 = 3)
  assert (FunPtr.invoke &&plus (2, 3) = 5)

let main _ =
  testSort ()
  testUnitFun ()
  testUnaryFun ()
  testVoidFun ()
  testFunPtrCanBeResult ()
  testFunPtrInvoke ()
  0
