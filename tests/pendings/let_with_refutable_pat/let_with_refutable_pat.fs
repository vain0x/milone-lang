module rec let_with_refutable_pat.Program

// Currently let expressions cannot contain refutable patterns,
// which could fail to match, e.g. `Some _`.

type MyUnion =
  | A of int
  | B of string

let main _ =
  let [ first ] = [ 2; 3 ]
  assert (first = 2)

  let isA (A _) = false
  assert (isA (A 2))

  assert false
  0
