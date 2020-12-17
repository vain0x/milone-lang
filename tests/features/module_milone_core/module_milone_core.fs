module rec module_milone_core.Program

// Currently, "MiloneCore" is visible to any modules without project references.
// (Ideally, prelude modules (List, Option, etc.) should be visible by default.)

open MiloneCore.List

let assertNotEmpty (xs: _ list) = assert (not (List.isEmpty xs))

let main _ =
  assertNotEmpty [ 1 ]
  0
