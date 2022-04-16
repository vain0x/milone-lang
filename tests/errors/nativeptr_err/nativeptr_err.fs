module rec nativeptr_err.Program

module Ptr = Std.Ptr

let private testNullPtrError () =
  let _: unit = __nullptr // type error!

  // FIXME: this should be error
  // let _: unativeint = __nullptr // type error!
  ()

let private testPtrAsInError () =
  let _ = Ptr.asIn // error! missing arg
  let _ = Ptr.asIn () // type error!

  // Argument type must be nativeptr or voidptr.
  let _ = Ptr.asIn (__nullptr: __inptr<int>) // type error!

  let _: byte = Ptr.asIn (__nullptr: voidptr) // type error!
  let _: unit = Ptr.asIn (__nullptr: voidptr) // type error!
  ()

let private testPtrAsNativeError () =
  let _ = Ptr.asNative // error! missing arg
  let _ = Ptr.asNative "" // type error!

  // Argument type must be __inptr or __voidinptr.
  let _ = Ptr.asNative (__nullptr: nativeptr<int>) // type error!
  ()

let private testPtrEqualityError () =
  let np: nativeptr<int> = __nullptr
  let kp: __inptr<int> = __nullptr
  let vp: voidptr = __nullptr

  let _ = np = 0 // type error!
  let _ = np = kp // type error!
  let _ = np = vp // type error!
  ()

let private testSizeOfError () =
  // FIXME: name resolution error prevents type check
  // let _ = sizeof // type argument is mandatory
  ()

let private testPtrOfError () =
  let _ = &&() // error! argument must be variable

  let s = "hello"
  let _ = &&s.[1] // error! argument can't be index
  ()

let private testPtrSelectError () =
  let _ = Ptr.select 0 // error! argument must be pointer type

  let f p = Ptr.select p // error! argument type must be known at this point
  let n = 0
  let _ = f &&n
  ()

let private testPtrReadError () =
  let _ = Ptr.read // error! missing arg
  let _ = Ptr.read 0 // type error!
  let _ = Ptr.read (__nullptr: __outptr<int>) // type error!
  ()

let private testPtrWriteError () =
  let p: nativeptr<int> = __nullptr
  let _ = Ptr.write // error! missing args
  let _ = Ptr.write p // error! missing arg
  let _ = Ptr.write (__nullptr: __inptr<int>) 0 // type error!
  ()

let main _ =
  testNullPtrError ()
  testPtrAsInError ()
  testPtrAsNativeError ()
  testPtrEqualityError ()
  testSizeOfError ()
  testPtrOfError ()
  testPtrSelectError ()
  testPtrReadError ()
  testPtrWriteError ()
  1
