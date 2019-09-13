module rec Competitive.Program

open Competitive.Helpers
open Competitive.SegTree
open Competitive.ABC140A
open Competitive.ABC140B
open Competitive.ABC140E

[<EntryPoint>]
let main _ =
  vectorTest ()
  segTreeTest ()
  abc140aTest ()
  abc140bTest ()
  abc140eTest ()

  // abc140eMain ()
  0
