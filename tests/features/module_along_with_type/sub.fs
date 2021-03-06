module rec module_along_with_type.sub

type Pos = Pos of int * int

module rec Pos =
  let eol = Pos(1, 0)

  let add l r : Pos =
    let (Pos (ly, lx)) = l
    let (Pos (ry, rx)) = r
    Pos(ly + ry, lx + rx)

// Extension.
module rec Pos =
  let toString (Pos (row, column)) =
    string (row + 1) + ":" + string (column + 1)
