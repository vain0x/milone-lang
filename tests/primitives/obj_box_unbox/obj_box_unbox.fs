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

  // boxing int types


  0
