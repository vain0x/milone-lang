module rec Std.StdTesting

open Std.StdError

let private shouldEqualString (expected: string) (actual: string) : bool =
  if actual = expected then
    true
  else
    let message =
      "Assertion violation.\n  actual   = "
      + actual
      + "\n  expected = "
      + expected

    __writeErrorLine message
    false

let shouldEqual (debug: 'T -> string) (expected: 'T) (actual: 'T) : bool =
  shouldEqualString (debug expected) (debug actual)
