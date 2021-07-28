module rec fun_monomorphization_bug.Program

// During compilation, compiles crashes in unreachable code.
// It seems 'T is not replaced with type argument in monomorphization.
// The reason seems g has monomorphic signature and "forceGeneration" doesn't occur.

let myFst (pair: 'T * _) : obj =
  // let g (pair: obj): obj =
  //   let x, _ = unbox pair: 'T * _
  //   box x

  // g (box pair)

  let x, _ = pair // just to pass
  box x

let main _ =
  assert (unbox (myFst (2, 3)) = 2)
  0
