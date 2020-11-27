module rec native_cast.Program

// Unsafe pointer casting.

let main _ =
  let mutNull: obj = __nativeCast (unativeint 0)
  let constNull: constobj = __nativeCast mutNull
  let constIntPtr: constptr<int> = __nativeCast constNull
  let intPtr: nativeptr<int> = __nativeCast constIntPtr

  let address: nativeint = __nativeCast intPtr
  assert(int address = 0)
  0
