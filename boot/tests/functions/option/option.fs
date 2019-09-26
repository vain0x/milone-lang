module rec Program

let basicSomeCase () =
  match Some 1 with
  | None ->
    assert false

  | Some 1 ->
    ()

  | _ ->
    assert false

let basicNoneCase () =
  // FIXME: directly using None emits invalid codes (e.g. `NULL->head`)
  let none: string option = None

  match none with
  | Some "a" ->
    assert false

  | None ->
    ()

  | _ ->
    assert false

let main _ =
  basicSomeCase ()
  basicNoneCase ()
  0
