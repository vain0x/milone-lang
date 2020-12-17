module rec native_ptr_read.Program

// Read memory as arbitrary type. Really unsafe.

let main _ =
  let p: __constptr<int> = int 42 |> box |> __nativeCast
  assert (__ptrRead p 0 = 42)

  let s: __constptr<char> = __nativeFun ("str_as_ptr", "Hello!")
  assert (__ptrRead s 4 = 'o')

  0
