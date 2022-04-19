module rec MiloneShared.TypeFloat

[<NoComparison>]
type FloatFlavor =
  | F32
  | F64

let floatFlavorToBytes flavor =
  match flavor with
  | F32 -> 4
  | F64 -> 8

let floatFlavorToOrdinary flavor =
  match flavor with
  | F32 -> 1
  | F64 -> 2

let floatFlavorCompare l r =
  compare (floatFlavorToOrdinary l) (floatFlavorToOrdinary r)

let fsharpFloatTyName flavor =
  match flavor with
  | F32 -> "float32"
  | F64 -> "float"

let cFloatTyPascalName flavor =
  match flavor with
  | F32 -> "F32"
  | F64 -> "F64"

let cFloatTyName flavor =
  match flavor with
  | F32 -> "float"
  | F64 -> "double"

let cStringOfFloatFunName flavor =
  match flavor with
  | F32 -> "string_of_float32"
  | F64 -> "string_of_float64"

let cStringToFloatFunName flavor =
  match flavor with
  | F32 -> "string_to_float32"
  | F64 -> "string_to_float64"
