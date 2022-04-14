module rec nativeptr_err.Program

module Ptr = Std.Ptr

let private testNullPtrError () =
  let _: unit = __nullptr // type error!

  // FIXME: this should be error
  // let _: unativeint = __nullptr // type error!
  ()

let private testPtrAsConstError () =
  let _ = Ptr.asConst // error! missing arg
  let _ = Ptr.asConst () // type error!

  // Argument type must be nativeptr or voidptr.
  let _ = Ptr.asConst (__nullptr: __constptr<int>) // type error!

  let _: byte = Ptr.asConst (__nullptr: voidptr) // type error!
  let _: unit = Ptr.asConst (__nullptr: voidptr) // type error!
  ()

let private testPtrAsMutableError () =
  let _ = Ptr.asMutable // error! missing arg
  let _ = Ptr.asMutable "" // type error!

  // Argument type must be __constptr or __voidconstptr.
  let _ =
    Ptr.asMutable (__nullptr: nativeptr<int>) // type error!

  let _ =
    Ptr.asMutable (__nullptr: nativeptr<int>) // type error!

  ()

let private testPtrEqualityError () =
  let np: nativeptr<int> = __nullptr
  let kp: __constptr<int> = __nullptr
  let vp: voidptr = __nullptr

  let _ = np = 0 // type error!
  let _ = np = kp // type error!
  let _ = np = vp // type error!
  ()

let private testSizeOfError () =
  // FIXME: name resolution error prevents type check
  // let _ = __sizeOf // type argument is mandatory
  ()

let private testPtrOfError () =
  let _ = &&() // error! argument must be variable

  let s = "hello"
  let _ = &&s.[1] // error! argument can't be index
  ()

let private testPtrOffsetError () =
  let _ = __ptr 0 // error! argument must be pointer type

  let f p = __ptr p // error! argument type must be known at this point
  let n = 0
  let _ = f &&n
  ()

let private testReadError () =
  let _ = __read // error! missing arg
  let _ = __read 0 // type error!
  ()

let private testWriteError () =
  let p: nativeptr<int> = __nullptr
  let _ = __write // error! missing args
  let _ = __write p // error! missing arg
  let _ = __write (__nullptr: __constptr<int>) 0 // type error!
  ()

let main _ =
  testNullPtrError ()
  testPtrAsConstError ()
  testPtrAsMutableError ()
  testPtrEqualityError ()
  testSizeOfError ()
  testPtrOfError ()
  testPtrOffsetError ()
  testReadError ()
  testWriteError ()
  1
