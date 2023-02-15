module rec fun_generic_complicated.Program

// Mutually recursive functions and explicit type variables.
// note: In F#, type check pass if all type variables are 'A, but not if 'A and 'B.
module private MutualRecursion =
  let mutuallyRecursive1 (a: 'A) : 'A =
    mutuallyRecursive2 a

  let mutuallyRecursive2 (b: 'B) : 'B =
    if false then
      mutuallyRecursive1 b
    else
      b

let private testMutualRecursion () =
  MutualRecursion.mutuallyRecursive1 ()
  MutualRecursion.mutuallyRecursive2 ()

  MutualRecursion.mutuallyRecursive1 0 |> ignore
  MutualRecursion.mutuallyRecursive2 0 |> ignore

let main _ =
  testMutualRecursion ()
  0
