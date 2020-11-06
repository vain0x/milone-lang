module rec record.Program

type Point = { X: int; Y: int }

let main _ =
  let _pt: Point = unbox (box { X = 40; Y = 2 })
  0
