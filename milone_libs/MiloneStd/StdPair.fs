module rec MiloneStd.StdPair

module Pair =
  let equals (equals0: 'T -> 'T -> bool) (equals1: 'U -> 'U -> bool) (l: 'T * 'U) (r: 'T * 'U) : bool =
    let l0, l1 = l
    let r0, r1 = r
    equals0 l0 r0 && equals1 l1 r1

  let compare (compare0: 'T -> 'T -> int) (compare1: 'U -> 'U -> int) (l: 'T * 'U) (r: 'T * 'U) : int =
    let l0, l1 = l
    let r0, r1 = r

    let c0 = compare0 l0 r0
    if c0 <> 0 then c0 else compare1 l1 r1

  let debug (debug0: 'T -> string) (debug1: 'U -> string) (pair: 'T * 'U) : string =
    let x0, x1 = pair
    "(" + debug0 x0 + ", " + debug1 x1 + ")"
