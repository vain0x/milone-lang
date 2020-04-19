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

// deprecated: static variables don't get captured now.
let mutuallyRecursiveCase () =
  assert (f1 () = 1)

let f1 () = f2 ()
let f2 () = f3 ()
let f3 () = f4 ()
let f4 () = f5 ()
let f5 () = f6 ()
let f6 () = f7 ()
let f7 () = a
let a = 1

let main _ =
  basicCase ()
  transitiveCase ()
  recursiveCase ()
  mutuallyRecursiveCase ()
  0
