module rec Competitive.Program

open Std.IO
open Std.StdError
open Competitive.Scan
open Competitive.SegTree
open Competitive.ABC140A
open Competitive.ABC140B
open Competitive.ABC140E

[<EntryPoint>]
let main _ =
  segTreeTest ()
  abc140aTest ()
  abc140bTest ()
  abc140eTest ()

  // Comment in the next line to try with stdio.
  // IO.exec abc140eMain |> never
  0
