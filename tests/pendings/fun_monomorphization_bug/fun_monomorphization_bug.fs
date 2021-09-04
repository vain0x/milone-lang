module rec fun_monomorphization_bug.Program

// During compilation, compiles crashes in unreachable code.
// It seems 'T is not replaced with type argument in monomorphization.
// The reason seems g has monomorphic signature and "forceGeneration" doesn't occur.

let myFst (pair: 'T * 'U) : obj =
  let g (pair: obj) : obj =
    let (x, _): 'T * 'U = unbox pair
    box x

  g (box pair)

let main _ =
  assert (unbox (myFst (2, 3)) = 2)
  0
