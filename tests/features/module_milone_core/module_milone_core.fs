module rec module_milone_core.Program

// MiloneCore modules are visible by default.
// See src/MiloneCore for implementations.

let assertNotEmpty (xs: _ list) = assert (not (List.isEmpty xs))

let main _ =
  assertNotEmpty [ 1 ]
  0
