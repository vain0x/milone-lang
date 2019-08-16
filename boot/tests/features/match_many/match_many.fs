let testTrivialCase () =
  match () with
  | () -> ()

let testListMatching () =
  match 0 :: [] with
  | _ :: _ :: [] -> exit 1
  | _ :: [] -> ()
  | [] -> exit 1

let testMatchArmsMakeScope () =
  let x = 2
  match x, 1 with
  | 1, x ->
    exit 1
  | 2, _ ->
    if x <> 2 then exit 1
  | _ ->
    exit 1

let testNestedMatchesParseCorrectly () =
  match 1 with
  | _ when false ->
    match 1 with
    | _ ->
      exit 1
  | _ ->
    ()

let main _ =
  testTrivialCase ()
  testListMatching ()
  testMatchArmsMakeScope ()
  testNestedMatchesParseCorrectly ()
  0
