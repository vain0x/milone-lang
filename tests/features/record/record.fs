module rec record.Program

// Basic use of record type.

type Point = { X: int; Y: int }

let main _ =
  let point : Point = { X = 40; Y = 2 }

  assert (point.X = 40)
  assert (point.Y = 2)
  0
