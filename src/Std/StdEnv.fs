/// Functions for execution environment.
module rec Std.StdEnv

module B = Std.StdEnvBase

/// Gets a list of command line arguments.
let commandLineArgs () =
  let count = B.getArgCount ()

  let rec go acc i =
    if i = 0 then
      acc
    else
      go (B.getArg (i - 1) :: acc) (i - 1)

  go [] count
