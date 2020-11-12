let rev xs =
  let rec go acc (xs : int list) =
    match xs with
    | [] ->
      acc
    | x :: xs ->
      go (x :: acc) xs
  go [] xs

let rec printList xs =
  match xs with
  | [] ->
    ()
  | x :: xs ->
    printfn "%d" x
    printList xs

let main _ =
  let xs = 0 :: 1 :: 2 :: []
  printfn "xs:"
  printList xs
  printfn "rev xs:"
  printList (rev xs)
  0