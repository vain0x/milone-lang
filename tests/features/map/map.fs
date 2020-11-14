module rec map.Program

// Previously AssocMap/AssocSet were built-in synonyms defined in the compiler
// but currently they are defined as TreeMap.
// This test can be removed?

type AssocMap<'K, 'V> = (uint * ('K * 'V) list) list * ('K -> uint) * ('K -> 'K -> int)

type AssocSet<'K> = AssocMap<'K, unit>

let intCmp (x: int) (y: int) =
  if y < x then 1
  else if y = x then 0
  else -1

let intHash (x: int) = uint x % uint 128

let mapNewSingleton key value hash cmp: AssocMap<_, _> =
  assert (cmp key key = 0)
  [ hash key, [ key, value ] ], hash, cmp

let typeTest () =
  let map = mapNewSingleton 1 "a" intHash intCmp
  let set: AssocSet<_> = mapNewSingleton 2 () intHash intCmp
  ()

let main _ =
  typeTest ()
  0
