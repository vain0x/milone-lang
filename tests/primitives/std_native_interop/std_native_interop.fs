module rec std_native_interop.Program

open MiloneStd.NativeInterop

module private NativePtrTests =
  let private testOfNativeInt () =
    let addr: nativeint = __nativeCast (box "hello")
    let _: nativeptr<char> = NativePtr.ofNativeInt addr
    ()

  let private testGet () =
    let p: nativeptr<int> = box (23, 45) |> __nativeCast
    assert (NativePtr.get p 0 = 23)
    assert (NativePtr.get p 1 = 45)

  let private testSet () =
    let p: nativeptr<int> = box (23, 45) |> __nativeCast
    NativePtr.set p 0 46
    NativePtr.set p 1 90
    let x, y = unbox (__nativeCast p)
    assert (x = 46)
    assert (y = 90)

  let private testRead () =
    let p: nativeptr<int> = box (23, 45) |> __nativeCast
    assert (NativePtr.read p = 23)

    let q = NativePtr.add p 1
    assert (NativePtr.read q = 45)

  let private testWrite () =
    let p: nativeptr<int> = box (23, 45) |> __nativeCast
    NativePtr.write p 46
    assert (NativePtr.read p = 46)

  let private testCopy () =
    let p: nativeptr<int> = box (23, 45, 67) |> __nativeCast
    let q: nativeptr<int> = box (0, 0, 0) |> __nativeCast
    assert (NativePtr.get q 1 = 0)

    let inc (p: nativeptr<int>) = NativePtr.add p 1
    NativePtr.copy (inc q) (inc p)

    assert (NativePtr.get q 0 = 0)
    assert (NativePtr.get q 1 = 45)
    assert (NativePtr.get q 2 = 0)

  let private testCopyBlock () =
    let p: nativeptr<int> = box (23, 45, 67, 89) |> __nativeCast
    let q: nativeptr<int> = box (0, 0, 0, 0) |> __nativeCast
    assert (NativePtr.get q 0 = 0)
    assert (NativePtr.get q 1 = 0)
    assert (NativePtr.get q 2 = 0)
    assert (NativePtr.get q 3 = 0)

    let inc (p: nativeptr<int>) = NativePtr.add p 1
    NativePtr.copyBlock (inc q) (inc p) 2

    assert (NativePtr.get q 0 = 0)
    assert (NativePtr.get q 1 = 45)
    assert (NativePtr.get q 2 = 67)
    assert (NativePtr.get q 3 = 0)

  let private testCopyBlockZero () =
    // Copying from/to null is okay when length is 0.
    let p: nativeptr<int> = NativePtr.__getNullPtr ()
    assert (__nativeCast p = 0n)

    NativePtr.copyBlock p p 0

  let private testSizeOf () =
    let intPtr: nativeptr<int> = NativePtr.__getNullPtr ()
    let int64Ptr: nativeptr<int64> = NativePtr.__getNullPtr ()

    assert (NativePtr.__sizeOf intPtr = 4)
    assert (NativePtr.__sizeOf int64Ptr = 8)

  let test () =
    testOfNativeInt ()
    testGet ()
    testSet ()
    testRead ()
    testWrite ()
    testCopy ()
    testCopyBlock ()
    testCopyBlockZero ()
    testSizeOf ()

module private ConstPtrTests =
  let private testGet () =
    let p: __constptr<int> = box (23, 45) |> __nativeCast
    assert (__ConstPtr.get p 0 = 23)
    assert (__ConstPtr.get p 1 = 45)

  let private testRead () =
    let p: __constptr<int> = box (23, 45) |> __nativeCast
    assert (__ConstPtr.read p = 23)

    let q = __ConstPtr.add p 1
    assert (__ConstPtr.read q = 45)

  let private testSizeOf () =
    let intPtr: __constptr<int> = __ConstPtr.getNullPtr ()
    let int64Ptr: __constptr<int64> = __ConstPtr.getNullPtr ()

    assert (__ConstPtr.sizeOf intPtr = 4)
    assert (__ConstPtr.sizeOf int64Ptr = 8)

  let test () =
    testGet ()
    testRead ()
    testSizeOf ()

let main _ =
  NativePtrTests.test ()
  ConstPtrTests.test ()
  0
