module rec list_equal.Program

// List type supports structural equality (=).

// FIXME: it's necessary to open a library manually for now.
module StdEqual = MiloneStd.Equal

let private testIntList () =
  assert ([ 2; 2; 3; 5 ] = [ 2; 2; 3; 5 ])

  let nil: int list = []
  assert (nil = [])
  assert (nil <> [ 0 ])

  // Ordering differs.
  assert ([ 2; 2; 3; 5 ] <> [ 2; 3; 2; 5 ])
  // Prefix.
  assert ([ 2; 2; 3 ] <> [ 2; 2; 3; 5 ])
  // Suffix.
  assert ([ 2; 3; 5 ] <> [ 2; 2; 3; 5 ])

let private testPairList () =
  assert ([ 1, "a"; 2, "b" ] = [ 1, "a"; 2, "b" ])

let main _ =
  testIntList ()
  testPairList ()
  0
