module rec native_ptr_write.Program

// Writes an arbitrary value to memory. Really unsafe.
// See also x_native_code.md in docs.

module Ptr = Std.Ptr

let strOfRawParts (p: __constptr<char>) (len: int) : string =
  __nativeFun ("str_of_raw_parts", p, len)

let main _ =
  // write to box
  let stringBox = box "zero"
  Ptr.write (__nativeCast stringBox: nativeptr<string>) "one"
  assert (unbox stringBox = "one")

  // write to array
  let buf: nativeptr<char> = (0UL, 0UL) |> box |> __nativeCast

  Ptr.write buf.[0] 'H'
  Ptr.write buf.[1] 'i'
  let s = strOfRawParts (__nativeCast buf) 2
  assert (s = "Hi")
  0
