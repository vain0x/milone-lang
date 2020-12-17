module rec native_ptr_write.Program

// Writes an arbitrary value to memory. Really unsafe.

let strOfRawParts (p: __constptr<char>) (len: int): string = __nativeFun ("str_of_raw_parts", p, len)

let main _ =
  // write to box
  let intBox = box 0
  __ptrWrite (__nativeCast intBox) 0 42
  assert (unbox intBox = 42)

  // write to array
  let buf: nativeptr<char> = uint64 0 |> box |> __nativeCast
  __ptrWrite buf 0 'H'
  __ptrWrite buf 1 'i'
  let s = strOfRawParts (__nativeCast buf) 2
  assert (s = "Hi")
  0
