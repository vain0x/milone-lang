module rec ptr_read.Program

// Read memory, unchecked.

let main _ =
  let p: constptr<int> = int 42 |> box |> __nativeCast
  assert (__ptrRead p 0 = 42)

  let s: constptr<char> = __nativeFun ("str_as_ptr", "Hello!")
  assert (__ptrRead s 4 = 'o')

  0
