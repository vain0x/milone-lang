module rec MiloneLang.TypeFloat

[<NoEquality; NoComparison>]
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
  | F32 -> "str_of_float"
  | F64 -> "str_of_double"

let cStringToFloatFunName flavor =
  match flavor with
  | F32 -> "str_to_float"
  | F64 -> "str_to_double"
