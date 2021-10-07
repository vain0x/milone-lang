module rec module_prelude.Program

// Prelude functions are visible by default.
// See milone_libs/MiloneCore/Prelude.milone for implementations.

let main _ =
  assert (id true)
  assert (id 42 = 42)
  0
