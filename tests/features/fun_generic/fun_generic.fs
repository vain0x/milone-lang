module rec fun_generic.Program

// Function defined with let expression is generalized automatically.

let private listRev xs =
  let rec go acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> go (x :: acc) xs

  go [] xs

let rec private listMap f xs =
  match xs with
  | [] -> []
  | x :: xs -> f x :: listMap f xs

let private id x = x

let private f x =
  printfn "%d" x
  x * x

let private flip (x, y) = y, x

let main _ =
  // id<int> instance
  let _: int = id 42
  // id<int> should be reused
  let _: int = id 1
  // Another instance of id
  let _: string list = id [ "A" ]

  let _ = [ 1; 2; 3 ] |> listMap f |> listMap f

  match (1, "a") |> flip |> flip with
  | 1, "a" -> ()
  | _ -> assert false

  match [ 1; 2 ] |> listRev, [ "a"; "b" ] |> listRev with
  | [ 2; 1 ], [ "b"; "a" ] -> ()
  | _ -> assert false

  match [ (1, "a"); (2, "b") ] |> listMap flip with
  | [ ("a", 1); ("b", 2) ] -> ()
  | _ -> assert false

  0
