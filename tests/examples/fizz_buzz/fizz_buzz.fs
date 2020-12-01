let main _ =
  let rec fizzBuzz i =
    if i <= 15 then
      if i % 15 = 0 then
        printfn "FizzBuzz"
      else if i % 3 = 0 then
        printfn "Fizz"
      else if i % 5 = 0 then
        printfn "Buzz"
      else
        printfn "%d" i
      fizzBuzz (i + 1)
  fizzBuzz 1
  0
