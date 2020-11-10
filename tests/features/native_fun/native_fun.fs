let intCmp (l: int) (r: int): int =
  (__nativeFun "int_cmp" 2) l r

let main _ =
  assert (intCmp 5 3 = 1)
  0
