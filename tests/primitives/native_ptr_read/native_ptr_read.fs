module rec native_ptr_read.Program

// Read memory as arbitrary type. Really unsafe.
// See also x_native_code.md in docs.

let main _ =
  let p: __constptr<string> = "hey" |> box |> __nativeCast
  assert (__ptrRead p 0 = "hey")

  let s: __constptr<char> = __nativeFun ("str_as_ptr", "Hello!")
  assert (__ptrRead s 4 = 'o')

  0
