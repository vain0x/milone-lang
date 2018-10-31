let main () =
  let printIntOrStr isInt value =
    if isInt then
      printfn "%d" (unbox value)
    else
      printfn "%s" (unbox value)

  printIntOrStr true (box 2)
  printIntOrStr false (box "Fizz")
  0
