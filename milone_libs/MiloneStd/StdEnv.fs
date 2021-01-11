/// Functions for execution environment.
module rec MiloneStd.StdEnv

/// Gets a list of command line arguments.
let commandLineArgs () =
  let count = __argCount ()

  let rec go acc i =
    if i = 0 then
      acc
    else
      go (__argGet (i - 1) :: acc) (i - 1)

  go [] count
