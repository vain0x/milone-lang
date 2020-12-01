[<AutoOpen>]
module Competitive.Polyfills

let __nativeFun _ =
  printfn "NEVER: __nativeFun is not available in F#"
  exit 1
