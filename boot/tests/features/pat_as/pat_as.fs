let simpleCase () =
  match 1 with
  | 1 as x ->
    assert (x = 1)
  | _ ->
    assert false

let shadowingCase () =
  let x = 1
  match x, 2 with
  | _, x as y ->
    let y1, y2 = y
    assert (x = 2 && y1 = 1 && y2 = 2)
  | _ ->
    assert false

let main _ =
  simpleCase ()
  shadowingCase ()
  0
