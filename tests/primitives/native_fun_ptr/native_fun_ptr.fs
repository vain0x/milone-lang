module rec native_fun_ptr.Program

// See also x_native_code.md in docs.

open Std.Ptr

type private CompareFun = FunPtr<VoidInPtr * VoidInPtr, int>

let private memAlloc (len: uint) (size: uint) : voidptr =
  __nativeFun ("milone_region_alloc", len, size)

let private sortIntArray (array: nativeptr<int>) (len: uint) : unit =
  let intCompare (l: VoidInPtr) (r: VoidInPtr) =
    compare (Ptr.read (__nativeCast l: InPtr<int>)) (Ptr.read (__nativeCast r: InPtr<int>))

  __nativeFun ("qsort", (__nativeCast array: voidptr), unativeint len, 4un, (__nativeFun intCompare: CompareFun))

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

let private testUnitFun () =
  let answer () = 42

  let fp: UnitFun = __nativeCast (__nativeFun answer)

  __nativeStmt ("""int (*unit_fun)(void) = {0};""", fp)
  let value: int = __nativeExpr "unit_fun()"
  assert (value = 42)

type private UnaryFun = FunPtr<int, int>

let private testUnaryFun () =
  let inc (n: int) : int = n + 1
  let fp: UnaryFun = __nativeFun inc

  __nativeStmt ("""int (*unary_fun)(int) = {0};""", fp)

  let value: int = __nativeExpr "unary_fun(41)"
  assert (value = 42)

type private VoidFun = FunPtr<int, unit>

let private testVoidFun () =
  let log (n: int) =
    __nativeStmt ("""printf("f is called: n=%d.\n", {0});""", n)

  let fp: VoidFun = __nativeCast (__nativeFun log)

  __nativeStmt ("""void(*void_fun)(int) = {0}; void_fun(42);""", fp)

let private testFunPtrCanBeResult () =
  let plus (x: int) (y: int) = x + y
  let getFunPtr () = __nativeFun plus
  let p = getFunPtr ()
  assert (p <> Ptr.nullPtr)

let main _ =
  testSort ()
  testUnitFun ()
  testUnaryFun ()
  testVoidFun ()
  testFunPtrCanBeResult ()
  0
