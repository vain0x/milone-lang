module rec std_option.Program

open MiloneStd.StdOption

module S = MiloneStd.StdString

let private some = Some 42
let private none: int option = None

let private testEquals () =
  let equals =
    let intEquals = fun (x: int) y -> x = y
    Option.equals intEquals

  assert (equals some none |> not)
  assert (equals some some)
  assert (equals none none)
  assert (equals (Some 2) (Some 3) |> not)

let private testCompare () =
  let c: int option -> _ -> _ = Option.compare compare

  assert (c none some < 0)
  assert (c some some = 0)
  assert (c none none = 0)
  assert (c (Some 2) (Some 3) < 0)

let private testDebug () =
  let d: int option -> _ = Option.debug string

  assert (d some = "Some(42)")
  assert (d none = "None")

let main _ =
  testEquals ()
  testCompare ()
  testDebug ()
  0
