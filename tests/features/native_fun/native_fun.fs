let intCmp (l: int) (r: int): int =
  __nativeFun ("int_compare", l, r)

let main _ =
  assert (intCmp 5 3 = 1)
  0
