module rec nativeptr_err.Program

open Std.Own
open Std.Ptr

let private testNullPtrError () =
  let _: unit = Ptr.nullPtr // type error!
  let _: unativeint = Ptr.nullPtr // type error!
  let _: obj = Ptr.nullPtr // type error!
  let _: int list = Ptr.nullPtr // type error!
  ()

let private testPtrCastError (_t: 'T) =
  // unativeint isn't a pointer type.
  let _: voidptr = Ptr.cast 0un // type error!
  let _: unativeint = Ptr.cast (Ptr.nullPtr: nativeptr<int>) // type error!

  // Result type must be different than argument type.
  let _: nativeptr<'T> = Ptr.cast (Ptr.nullPtr: nativeptr<'T>) // type error!

  // Own type can't be wrapped nor unwrapped.
  let _: Own<nativeptr<'T>> = Ptr.cast (Ptr.nullPtr: voidptr) // type error!
  let _: nativeptr<'T> = Ptr.cast (Ptr.nullPtr: Own<voidptr>) // type error!
  ()

let private testPtrAsInError () =
  let _ = Ptr.asIn // error! missing arg
  let _ = Ptr.asIn () // type error!

  // Argument type must be nativeptr or voidptr.
  let _ = Ptr.asIn (Ptr.nullPtr: InPtr<int>) // type error!

  let _: byte = Ptr.asIn (Ptr.nullPtr: voidptr) // type error!
  let _: unit = Ptr.asIn (Ptr.nullPtr: voidptr) // type error!
  ()

let private testPtrAsNativeError () =
  let _ = Ptr.asNative // error! missing arg
  let _ = Ptr.asNative "" // type error!

  // Argument type must be InPtr or VoidInPtr.
  let _ =
    Ptr.asNative (Ptr.nullPtr: nativeptr<int>) // type error!

  ()

let private testPtrEqualityError () =
  let np: nativeptr<int> = Ptr.nullPtr
  let kp: InPtr<int> = Ptr.nullPtr
  let vp: voidptr = Ptr.nullPtr

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
  let _ = Ptr.read (Ptr.nullPtr: OutPtr<int>) // type error!
  ()

let private testPtrWriteError () =
  let p: nativeptr<int> = Ptr.nullPtr
  let _ = Ptr.write // error! missing args
  let _ = Ptr.write p // error! missing arg
  let _ = Ptr.write (Ptr.nullPtr: InPtr<int>) 0 // type error!
  ()

let main _ =
  testNullPtrError ()
  testPtrCastError ()
  testPtrAsInError ()
  testPtrAsNativeError ()
  testPtrEqualityError ()
  testSizeOfError ()
  testPtrOfError ()
  testPtrSelectError ()
  testPtrReadError ()
  testPtrWriteError ()
  1
