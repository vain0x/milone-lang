module rec module_libcore.Program

open MiloneCore.List

let assertNotEmpty (xs: _ list) = assert (not (List.isEmpty xs))

let main _ =
  assertNotEmpty [ 1 ]
  0
