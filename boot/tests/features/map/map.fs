let strCmp (x: string) (y: string) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let mapNewSingleton key value cmp =
  assert (cmp key key = 0)
  [key, value], cmp

let main _ =
  let map = mapNewSingleton "a" 1 strCmp
  0
