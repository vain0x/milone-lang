let main _ =
  let id x = x

  // id<int> instance
  let _: int = id 42
  // id<int> should be reused
  let _: int = id 1
  // Another instance of id
  let _: string list = id ["A"]

  let rec listMap f xs =
    match xs with
    | [] ->
      []
    | x :: xs ->
      f x :: listMap f xs
  let f x =
    printfn "%d" x
    x * x
  let _ = [1; 2; 3] |> listMap f |> listMap f

  let flip (x, y) = y, x
  match (1, "a") |> flip |> flip with
  | 1, "a" -> ()
  | _ -> exit 1

  0
