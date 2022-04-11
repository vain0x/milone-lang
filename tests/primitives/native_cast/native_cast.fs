module rec native_cast.Program

// Unsafe pointer casting.
// See also x_native_code.md in docs.

let main _ =
  let mutNull: voidptr = __nullptr
  let constNull: __voidconstptr = __nativeCast mutNull
  let constIntPtr: __constptr<int> = __nativeCast constNull
  let intPtr: nativeptr<int> = __nativeCast constIntPtr

  let address: nativeint = __nativeCast intPtr
  assert (address = 0n)
  0
