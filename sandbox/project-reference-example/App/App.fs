module rec App.App

open Lib.Lcm
open Lib.Gcd

let f x y =
  printfn "gcd(%d, %d) = %d" x y (gcd x y)
  printfn "lcm(%d, %d) = %d" x y (lcm x y)

[<EntryPoint>]
let main _ =
  f 1 1
  f 2 3
  f 4 6
  f 8 16
  0
