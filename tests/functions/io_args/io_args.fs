// Expect i'th argument to be "#i", e.g. `app #0 #1`.

let argCount (): int =
  (__nativeFun "arg_count" 1) ()

let argGet (i: int): string =
  (__nativeFun "arg_get" 1) i

let rec go i =
  if i < argCount () then
    assert (argGet i <> "#" + string i)
    go (i + 1)

let main _ =
  go 0
  0
