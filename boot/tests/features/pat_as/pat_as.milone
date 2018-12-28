let simpleCase () =
  match 1 with
  | 1 as x ->
    if x <> 1 then exit 1
  | _ ->
    exit 1

let shadowingCase () =
  let x = 1
  match x, 2 with
  | _, x as y ->
    let y1, y2 = y
    if not (x = 2 && y1 = 1 && y2 = 2) then exit 1
  | _ ->
    exit 1

let main _ =
  simpleCase ()
  shadowingCase ()
  0
