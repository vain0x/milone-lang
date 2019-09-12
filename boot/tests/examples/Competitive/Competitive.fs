module rec Competitive.Program

open Competitive.Helpers
open Competitive.ABC140A
open Competitive.ABC140B

[<EntryPoint>]
let main _ =
  vectorTest ()
  abc140aTest ()
  abc140bTest ()

  // abc140bMain ()
  0
