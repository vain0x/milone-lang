let inc (x : int) = x + 1
let twice (x : int) = x * x
let sub (x : int) y = x - y
let between l r (x : int) = l <= x && x < r

let main _ =
  let n = 1 |> inc |> twice |> twice
  if n <> 16 then exit 1

  if (100 |> sub) 98 |> (between 2 3) |> not then exit 2

  // The fixity of `|>` is between `=` and `::`.
  let len (xs : int list) =
    match xs with
    | [] -> 0
    | _ -> 1

  if 1 :: [] |> len = 0 then exit 1

  0
