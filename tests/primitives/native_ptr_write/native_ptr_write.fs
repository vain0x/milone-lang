module rec native_ptr_write.Program

// Writes an arbitrary value to memory. Really unsafe.
// See also x_native_code.md in docs.

let strOfRawParts (p: __constptr<char>) (len: int) : string =
  __nativeFun ("str_of_raw_parts", p, len)

let main _ =
  // write to box
  let stringBox = box "zero"
  __ptrWrite (__nativeCast stringBox) 0 "one"
  assert (unbox stringBox = "one")

  // write to array
  let buf: nativeptr<char> = (0UL, 0UL) |> box |> __nativeCast

  __ptrWrite buf 0 'H'
  __ptrWrite buf 1 'i'
  let s = strOfRawParts (__nativeCast buf) 2
  assert (s = "Hi")
  0
