/// Defines F# primitives for milone-lang.
[<AutoOpen>]
module rec MiloneLang.Polyfills

let failwith (str: string) =
  printfn "FATAL ERROR: %s" str
  exit 1

let failwithf (str: string) =
  printfn "FATAL ERROR: %s" str
  exit 1

let sprintf (fmt: string) =
  printfn "%s" fmt
  exit 1

let objToString _ = "<objToString not supported>"

let ignore _ = ()

let id x = x

let fst (x, _) = x
