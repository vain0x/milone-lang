let intCmp (x: int) (y: int) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let strCmp (x: string) (y: string) =
  if y < x then
    1
  else if y = x then
    0
  else
    -1

let mapNewSingleton key value cmp =
  assert (cmp key key = 0)
  [key, value], cmp

let mapEmpty cmp: Map<_, _> =
  [], cmp

let mapAdd key value (map, cmp) =
  (key, value) :: map, cmp

let mapFind key alt (map, cmp) =
  let rec go map =
    match map with
    | [] ->
      alt

    | (k, v) :: _
      when cmp key k = 0 ->
      v

    | _ :: map ->
      go map

  go map

let typeTest () =
  let map = mapNewSingleton "a" 1 strCmp
  ()

let basicCaseTest () =
  let m = mapEmpty intCmp |> mapAdd 1 "a" |> mapAdd 2 "b" |> mapAdd 3 "c"

  assert (m |> mapFind 2 "" = "b")
  assert (m |> mapFind 4 "" = "")

  let n = m |> mapAdd 2 "B"

  assert (n |> mapFind 2 "" = "B")
  assert (m |> mapFind 2 "" = "b")

let main _ =
  typeTest ()
  basicCaseTest ()
  0
