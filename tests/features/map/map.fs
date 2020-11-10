let intCmp (x: int) (y: int) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let intHash (x: int) =
  uint x % uint 128

let mapNewSingleton key value hash cmp: AssocMap<_, _> =
  assert (cmp key key = 0)
  [hash key, [key, value]], hash, cmp

let typeTest () =
  let map = mapNewSingleton 1 "a" intHash intCmp
  let set = mapNewSingleton 2 () intHash intCmp: AssocSet<_>
  ()

let main _ =
  typeTest ()
  0
