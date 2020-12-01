// Expect i'th argument to be "#i", e.g. `app #0 #1`.

let argCount (): int =
  __nativeFun "arg_count"

let argGet (i: int): string =
  __nativeFun ("arg_get", i)

let rec go i =
  if i < argCount () then
    assert (argGet i <> "#" + string i)
    go (i + 1)

let main _ =
  go 0
  0
