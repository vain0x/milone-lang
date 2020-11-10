/// Provides some of built-in functions in F# for milone-lang.
// HACK: In NameRes, modules named 'Polyfills' is automatically opened.
// [<AutoOpen>]
module rec MiloneCore.Polyfills

let failwith (str: string) =
  printfn "FATAL ERROR: %s" str
  exit 1
