/// Defines F# primitives for milone-lang.
///
/// Not used in F#.
[<AutoOpen>]
module rec MiloneLang.MiloneOnly

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

let snd (_, y) = y

type Profiler = Profiler of obj

let strJoin (sep: string) (xs: string list): string = (__nativeFun "str_concat" 2) sep xs
