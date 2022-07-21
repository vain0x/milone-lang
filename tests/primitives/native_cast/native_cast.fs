module rec native_cast.Program

// Unsafe pointer casting.
// See also x_native_code.md in docs.

open Std.Ptr

let main _ =
  let mutNull: voidptr = Ptr.nullPtr
  let constNull: VoidInPtr = __nativeCast mutNull
  let constIntPtr: InPtr<int> = __nativeCast constNull
  let intPtr: nativeptr<int> = __nativeCast constIntPtr

  let address: nativeint = __nativeCast intPtr
  assert (address = 0n)
  0
