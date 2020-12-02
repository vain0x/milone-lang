module rec native_cast.Program

// Unsafe pointer casting.

let main _ =
  let mutNull: voidptr = __nativeCast (unativeint 0)
  let constNull: __voidconstptr = __nativeCast mutNull
  let constIntPtr: __constptr<int> = __nativeCast constNull
  let intPtr: nativeptr<int> = __nativeCast constIntPtr

  let address: nativeint = __nativeCast intPtr
  assert (int address = 0)
  0
