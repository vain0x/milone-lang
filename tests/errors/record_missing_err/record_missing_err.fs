module rec record_missing_err.Program

type Point = { X: int; Y: int }

let main _ =
  let _p : Point = { X = 1 }

  0
