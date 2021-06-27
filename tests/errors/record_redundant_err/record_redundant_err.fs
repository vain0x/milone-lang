module rec record_redundant_err.Program

type Point = { X: int; Y: int }

let main _ =
  let _p : Point = { X = 1; Y = 2; Z = 3 }
  0
