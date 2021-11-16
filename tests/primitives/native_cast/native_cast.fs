module rec native_cast.Program

// Unsafe pointer casting.

let main _ =
  let mutNull: voidptr = __nativeCast 0un
  let constNull: obj = __nativeCast mutNull
  let constIntPtr: __constptr<int> = __nativeCast constNull
  let intPtr: nativeptr<int> = __nativeCast constIntPtr

  let address: nativeint = __nativeCast intPtr
  assert (address = 0n)
  0
