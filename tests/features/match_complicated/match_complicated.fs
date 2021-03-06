module rec match_complicated.Program

// Complicated test for match expressions.

let testTrivialCase () =
  match () with
  | () -> ()

let testListMatching () =
  match [ 0 ] with
  | _ :: _ :: _ -> assert false
  | [ _ ] -> ()
  | [] -> assert false

let testMatchArmsMakeScope () =
  let x = 2

  match x, 1 with
  | 1, x -> assert false
  | 2, _ -> if x <> 2 then assert false
  | _ -> assert false

let testNestedMatchesParseCorrectly () =
  match 1 with
  | _ when false ->
      match 1 with
      | _ -> assert false
  | _ -> ()

let main _ =
  testTrivialCase ()
  testListMatching ()
  testMatchArmsMakeScope ()
  testNestedMatchesParseCorrectly ()
  0
