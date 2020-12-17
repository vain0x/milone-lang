module rec fun_closure.Program

// Function can use local variables outside of it.

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

  let rec go n = n >= 10 || n |> inc |> go

  assert (go 0)

let lambdaCase () =
  let lx = 7

  let lf () =
    let lg () = lx
    (fun () -> lg ()) ()

  assert (lf () = lx)

let escapeCase () =
  // In this case, the call graph forms a cycle:
  //    xf1 -> xf2 -> xf3 -> xf4 -> xf1 -> ...
  // Closure conversion should be aware of that,
  // even if xf4 transitively captures x2 and xf1 transitively calls xf4,
  // xf1 doesn't capture x2.

  let rec xf1 (x1: int) =
    let xf2 (x2: int) =
      let xf3 (x3: int) =
        let xf4 () = xf1 (x1 + x2 + x3)

        if x3 = 3 then xf4 () else x3

      if x2 = 2 then xf3 3 else x2

    if x1 = 1 then xf2 2 else x1

  assert (xf1 1 = 1 + 2 + 3)

let innerFunCase () =
  let zf1 x =
    let zf11 () = x
    zf11 ()

  let zf2 x =
    let zf22 () = zf1 x
    zf22 ()

  assert (zf2 1 = 1)

// deprecated: static variables don't get captured now.
let mutuallyRecursiveCase () = assert (f1 () = 1)

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
  lambdaCase ()
  escapeCase ()
  innerFunCase ()
  mutuallyRecursiveCase ()
  0
