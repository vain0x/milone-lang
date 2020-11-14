[<AutoOpen>]
module Competitive.Polyfills

let __nativeFun _ =
  printfn "NEVER: nativeFun is unsupported"
  exit 1
