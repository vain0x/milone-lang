module rec module_along_with_type.Program

// Typically a module is defined with the same name as a type.

open module_along_with_type.sub

type Range = Range of Pos * Pos

module rec Range =
  let pair s t = Range(s, t)

module rec Range =
  let toString (Range (s, t)) =
    let (Pos (sy, sx)) = s
    let (Pos (ty, tx)) = t

    string (sy + 1) "."
    + string (sx + 1)
    + "-"
    + string (ty + 1) "."
    + string (tx + 1)

let main _ =
  // Type name is not shadowed.
  let p: Pos = Pos.eol
  let r: Range = Range(p, Pos.add p p)

  assert (Pos.toString p = "2:1")
  assert (Pos.toString (Pos.add p p) = "3:1")

  assert (Range.toString r = "2.1-3.1")
  0
