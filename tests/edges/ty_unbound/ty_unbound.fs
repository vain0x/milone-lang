module rec ty_unbound.Program

open MiloneCore.List

let assertIsEmpty xs = assert (List.isEmpty xs)

let main _ =
  assertIsEmpty []
  0
