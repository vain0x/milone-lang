module rec module_along_with_type.Program

// Typically a module is defined with the same name as a type.

type Pos = Pos of int * int

module rec Pos =
  let eol = Pos (1, 0)

  let add l r: Pos =
    let (Pos (ly, lx)) = l
    let (Pos (ry, rx)) = r
    Pos (ly + ry, lx + rx)

// Extension.
module rec Pos =
  let toString (Pos (row, column)) = string (row + 1) + ":" + string (column + 1)

let main _ =
  assert (Pos.toString Pos.eol = "2:1")
  assert (Pos.toString (Pos.add Pos.eol Pos.eol) = "3:1")
  0
