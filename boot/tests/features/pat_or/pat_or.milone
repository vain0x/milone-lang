// Simple case.
let isZeroOrOne x =
  match x with
  | 0
  | 1 -> true
  | _ -> false

let simpleCase () =
  if not (isZeroOrOne 0 && isZeroOrOne 1) then exit 1
  if isZeroOrOne 2 then exit 1

// Nested case.
let startsWithDoubleBits xs =
  match xs with
  | (0 | 1) :: (0 | 1) :: _ ->
    true
  | _ ->
    false

let nestedCase () =
  if startsWithDoubleBits [0; 1; 2] |> not then exit 1
  if startsWithDoubleBits [1; 2] then exit 1

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
  if performComplexMatching (Add (0, 1)) |> not then exit 1
  if performComplexMatching (Add (1, 2)) then exit 1

let main _ =
  simpleCase ()
  nestedCase ()
  complexCase ()
  0
