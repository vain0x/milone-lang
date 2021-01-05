module rec effect_printfn.Program

let main _ =
  printfn "No formats"

  let hello = "Hello!"
  printfn "%s" hello

  printfn "Welcome to %s. Entry price is %c%d!" "Milone Land" '$' 1000000007
  0
