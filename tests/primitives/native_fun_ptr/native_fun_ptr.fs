module rec native_fun_ptr.Program

// See also x_native_code.md in docs.

type private CompareFun = __nativeFun<__voidconstptr * __voidconstptr, int>

let private memAlloc (len: int) (size: int) : voidptr =
  __nativeFun ("milone_mem_alloc", len, unativeint size)

let private sortIntArray (array: nativeptr<int>) (len: int) : unit =
  let intCompare (l: __voidconstptr) (r: __voidconstptr) =
    compare (__ptrRead (__nativeCast l) 0: int) (__ptrRead (__nativeCast r) 0: int)

  __nativeFun ("qsort", (__nativeCast array: voidptr), unativeint len, 4un, (__nativeFun intCompare: CompareFun))

let private testSort () =
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

type private UnitFun = __nativeFun<unit, int>

let private testUnitFun () =
  let answer () = 42

  let fp: UnitFun = __nativeCast (__nativeFun answer)

  __nativeStmt ("""int (*unit_fun)(void) = {0};""", fp)
  let value: int = __nativeExpr "unit_fun()"
  assert (value = 42)

type private UnaryFun = __nativeFun<int, int>

let private testUnaryFun () =
  let inc (n: int) : int = n + 1
  let fp: UnaryFun = __nativeFun inc

  __nativeStmt ("""int (*unary_fun)(int) = {0};""", fp)

  let value: int = __nativeExpr "unary_fun(41)"
  assert (value = 42)

type private VoidFun = __nativeFun<int, unit>

let private testVoidFun () =
  let log (n: int) =
    __nativeStmt ("""printf("f is called: n=%d.\n", {0});""", n)

  let fp: VoidFun = __nativeCast (__nativeFun log)

  __nativeStmt ("""void(*void_fun)(int) = {0}; void_fun(42);""", fp)

let private testFunPtrCanBeResult () =
  let plus (x: int) (y: int) = x + y
  let getFunPtr () = __nativeFun plus
  let p = getFunPtr ()
  assert (p <> __nullptr)

let main _ =
  testSort ()
  testUnitFun ()
  testUnaryFun ()
  testVoidFun ()
  testFunPtrCanBeResult ()
  0
