module rec list_pat.Program

// Multiline list pattern.

let main _ =
  match [ 1; 2; 3; 4; 5; 6; 7 ]
        |> List.map (fun x -> Some(Some(Some(x))))
    with
  | [ Some (Some (Some x1))
      Some (Some (Some x2))
      Some (Some (Some x3))
      Some (Some (Some x4))
      Some (Some (Some x5))
      Some (Some (Some x6))
      Some (Some (Some x7)) ] ->
    assert (x1 = 1)
    assert (x2 = 2)
    assert (x3 = 3)
    assert (x4 = 4)
    assert (x5 = 5)
    assert (x6 = 6)
    assert (x7 = 7)

  | _ -> assert false

  0
