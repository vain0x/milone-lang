module rec obj_box_unbox.Program

// box and unbox are used to erase a type of value.

// It's guaranteed that `(unbox (box (x: 'T))): 'T` is x (round-trip).
// If unbox is called incorrectly, it runs into undefined behavior. Really unsafe.

let main _ =
  let printIntOrStr isInt value =
    if isInt then
      printfn "%d" (unbox value)
    else
      printfn "%s" (unbox value)

  printIntOrStr true (box 2)
  printIntOrStr false (box "Fizz")

  // These types don't allocate to box.
  let n = box 42
  assert (unbox n = 42)

  let xs = box [ 4; 2 ]

  match unbox xs with
  | [ a; b ] -> assert (a * 10 + b = 42)
  | _ -> assert false

  0
