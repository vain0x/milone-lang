let basicCase () =
  let step = 3
  let sub x = x - step
  assert (sub 8 = 5)

let transitiveCase () =
  let step = 1
  let inc x = x + step
  let incTwice x = x |> inc |> inc
  assert (incTwice 0 = 2)

let recursiveCase () =
  let step = 1
  let inc x = x + step

  let rec go n =
    n >= 10 || n |> inc |> go

  assert (go 0)

let main _ =
  basicCase ()
  transitiveCase ()
  recursiveCase ()
  0
