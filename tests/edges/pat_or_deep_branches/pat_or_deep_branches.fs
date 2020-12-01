module rec pat_or_deep_branches.Program

// Complicated OR patterns.
// This test doesn't pass because MirGen emits duplicated variable definitions
// and GCC runs into compile error.

let main _ =
  // match [ 2; 3; 5 ] with
  // | x :: y :: _ :: _ :: _
  // | x :: ((y :: _)
  // | (_ :: y :: []
  // | _ :: _ :: y :: [])) ->
  //     assert (x = 2)
  //     assert (y = 5)

  // | _ -> assert false
  0
