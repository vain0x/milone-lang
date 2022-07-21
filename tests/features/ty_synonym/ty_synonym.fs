module rec ty_synonym.Program

// Type synonyms should work.

type ExitCode = int
type ExitCodeList = ExitCode list

type Condition = bool

let baseCase () =
  let success: ExitCode = 0
  let failure: ExitCode = 1
  let codes: ExitCodeList = [ success; failure ]
  assert (success = 0)

// int = ExitCode should be unifiable.
let yodaCase (exitCode: ExitCode) = assert (0 = exitCode)

let private proj (cond: Condition) body alt = if cond then body else alt

let polymorphicFunCase () =
  assert (proj true 1 0 = 1)
  assert (proj false "T" "F" = "F")

let main _ =
  baseCase ()
  yodaCase 0
  polymorphicFunCase ()
  0
