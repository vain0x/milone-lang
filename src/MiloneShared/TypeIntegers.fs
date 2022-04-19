module rec MiloneShared.TypeIntegers

[<NoComparison>]
type Signedness =
  | Signed
  | Unsigned

[<NoComparison>]
type IntPrecision =
  /// 8-bit
  | N8
  | N16
  | N32
  | N64

  /// Size of pointer.
  | NPtr

[<NoComparison>]
type IntFlavor =
  | I8
  | I16
  | I32
  | I64
  | IPtr
  | U8
  | U16
  | U32
  | U64
  | UPtr

let intFlavorToSignedness flavor =
  match flavor with
  | I8
  | I16
  | I32
  | I64
  | IPtr -> Signed

  | U8
  | U16
  | U32
  | U64
  | UPtr -> Unsigned

let intFlavorToPrecision flavor =
  match flavor with
  | I8
  | U8 -> N8
  | I16
  | U16 -> N16
  | I32
  | U32 -> N32
  | I64
  | U64 -> N64
  | IPtr
  | UPtr -> NPtr

let intFlavorIsUnsigned flavor =
  match intFlavorToSignedness flavor with
  | Unsigned -> true
  | _ -> false

let intFlavorToBytes flavor =
  match intFlavorToPrecision flavor with
  | N8 -> 1
  | N16 -> 2
  | N32 -> 4
  | N64
  | NPtr -> 8

let intFlavorToOrdinary flavor =
  match flavor with
  | I8 -> 1
  | I16 -> 2
  | I32 -> 3
  | I64 -> 4
  | IPtr -> 5
  | U8 -> 6
  | U16 -> 7
  | U32 -> 8
  | U64 -> 9
  | UPtr -> 10

let intFlavorEqual l r =
  intFlavorToOrdinary l = intFlavorToOrdinary r

let intFlavorCompare l r =
  compare (intFlavorToOrdinary l) (intFlavorToOrdinary r)

/// https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/literals
let intFlavorOfSuffix (s: string) : IntFlavor option =
  match s with
  | "y" -> Some I8
  | "s" -> Some I16
  | "L" -> Some I64
  | "n" -> Some IPtr
  | "uy" -> Some U8
  | "us" -> Some U16
  | "u"
  | "ul" -> Some U32
  | "UL" -> Some U64
  | "un" -> Some UPtr
  | _ -> None

let fsharpIntegerTyName flavor =
  match flavor with
  | I8 -> "int8"
  | I16 -> "int16"
  | I32 -> "int"
  | I64 -> "int64"
  | IPtr -> "nativeint"
  | U8 -> "uint8"
  | U16 -> "uint16"
  | U32 -> "uint"
  | U64 -> "uint64"
  | UPtr -> "unativeint"

let cIntegerTyName flavor =
  match flavor with
  | I8 -> "int8_t"
  | I16 -> "int16_t"
  | I32 -> "int"
  | I64 -> "int64_t"
  | IPtr -> "intptr_t"
  | U8 -> "uint8_t"
  | U16 -> "uint16_t"
  | U32 -> "uint32_t"
  | U64 -> "uint64_t"
  | UPtr -> "uintptr_t"

let cIntegerTyPascalName flavor =
  match flavor with
  | I8 -> "Int8"
  | I16 -> "Int16"
  | I32 -> "Int"
  | I64 -> "Int64"
  | IPtr -> "ISize"
  | U8 -> "UInt8"
  | U16 -> "UInt16"
  | U32 -> "UInt"
  | U64 -> "UInt64"
  | UPtr -> "UIntPtr"

let cStringToIntegerFunName flavor =
  match flavor with
  | I8 -> "string_to_int8"
  | I16 -> "string_to_int16"
  | I32 -> "string_to_int"
  | I64 -> "string_to_int64"
  | IPtr -> "string_to_intptr"
  | U8 -> "string_to_uint8"
  | U16 -> "string_to_uint16"
  | U32 -> "string_to_uint32"
  | U64 -> "string_to_uint64"
  | UPtr -> "string_to_uintptr"

let cStringOfIntegerFunName flavor =
  match intFlavorToSignedness flavor with
  | Signed -> "string_of_int64"
  | Unsigned -> "string_of_uint64"
