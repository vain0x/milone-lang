type ExitCode = int
type ExitCodeList = ExitCode list

type Condition = bool

let polymorphicFunTest () =
  let proj (cond: Condition) body alt =
    if cond then body else alt

  assert (proj true 1 0 = 1)
  assert (proj false "T" "F" = "F")

let main _ =
  let success: ExitCode = 0
  let failure: ExitCode = 1
  let codes: ExitCodeList = [success; failure]
  assert (success = 0)

  polymorphicFunTest ()
  0
