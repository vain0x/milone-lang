[<AutoOpen>]
module rec MiloneLang.Polyfills

let failwith (str: string) =
  printfn "FATAL ERROR: %s" str
  exit 1

let failwithf (str: string) =
  printfn "FATAL ERROR: %s" str
  exit 1

let fst (x, _) = x
