// Simple case.
let isZeroOrOne x =
  match x with
  | 0
  | 1 -> true
  | _ -> false

let simpleCase () =
  assert (isZeroOrOne 0 && isZeroOrOne 1)
  assert (isZeroOrOne 2 |> not)

// Nested case.
let startsWithDoubleBits xs =
  match xs with
  | (0 | 1) :: (0 | 1) :: _ ->
    true
  | _ ->
    false

let nestedCase () =
  assert (startsWithDoubleBits [0; 1; 2])
  assert (startsWithDoubleBits [1; 2] |> not)

// Complex case.
type Expr =
  | Add of int * int

let performComplexMatching expr =
  match expr with
  | Add (0, (0 | 1) : int) ->
    true
  | _ ->
    false

let complexCase () =
  assert (performComplexMatching (Add (0, 1)))
  assert (performComplexMatching (Add (1, 2)) |> not)

let main _ =
  simpleCase ()
  nestedCase ()
  complexCase ()
  0
