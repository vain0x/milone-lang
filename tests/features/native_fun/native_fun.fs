let intCompare (l: int) (r: int): int =
  __nativeFun ("int_compare", l, r)

let main _ =
  assert (intCompare 5 3 = 1)
  0
