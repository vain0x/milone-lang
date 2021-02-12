module rec MiloneLang.TypeIntegers

[<NoComparison>]
type Signedness =
  | Signed
  | Unsigned

[<NoComparison>]
type IntPrecision =
  /// 8-bit
  | I8
  | I16
  | I32
  | I64

  /// Size of pointer.
  | IPtr

[<Struct; NoComparison>]
type IntFlavor = IntFlavor of Signedness * IntPrecision

let intFlavorToBytes flavor =
  let (IntFlavor (_, precision)) = flavor

  match precision with
  | I8 -> 1
  | I16 -> 2
  | I32 -> 4
  | I64
  | IPtr -> 8

let intFlavorToOrdinary flavor =
  let (IntFlavor (signedness, precision)) = flavor

  let n =
    match precision with
    | I8 -> 1
    | I16 -> 2
    | I32 -> 3
    | I64 -> 4
    | IPtr -> 5

  match signedness with
  | Signed -> n
  | Unsigned -> n * 2

let intFlavorEqual l r =
  intFlavorToOrdinary l = intFlavorToOrdinary r

let fsharpIntegerTyName flavor =
  let (IntFlavor (signedness, precision)) = flavor

  match signedness, precision with
  | Signed, I8 -> "int8"
  | Signed, I16 -> "int16"
  | Signed, I32 -> "int"
  | Signed, I64 -> "int64"
  | Signed, IPtr -> "nativeint"
  | Unsigned, I8 -> "uint8"
  | Unsigned, I16 -> "uint16"
  | Unsigned, I32 -> "uint"
  | Unsigned, I64 -> "uint64"
  | Unsigned, IPtr -> "unativeint"

let cIntegerTyName flavor =
  let (IntFlavor (signedness, precision)) = flavor

  match signedness, precision with
  | Signed, I8 -> "int8_t"
  | Signed, I16 -> "int16_t"
  | Signed, I32 -> "int"
  | Signed, I64 -> "int64_t"
  | Signed, IPtr -> "intptr_t"
  | Unsigned, I8 -> "uint8_t"
  | Unsigned, I16 -> "uint16_t"
  | Unsigned, I32 -> "uint32_t"
  | Unsigned, I64 -> "uint64_t"
  | Unsigned, IPtr -> "uintptr_t"

let cIntegerTyPascalName flavor =
  let (IntFlavor (signedness, precision)) = flavor

  match signedness, precision with
  | Signed, I8 -> "Int8"
  | Signed, I16 -> "Int16"
  | Signed, I32 -> "Int"
  | Signed, I64 -> "Int64"
  | Signed, IPtr -> "ISize"
  | Unsigned, I8 -> "UInt8"
  | Unsigned, I16 -> "UInt16"
  | Unsigned, I32 -> "UInt"
  | Unsigned, I64 -> "UInt64"
  | Unsigned, IPtr -> "UIntPtr"

let cStringToIntegerFunName flavor =
  let (IntFlavor (signedness, precision)) = flavor

  match signedness, precision with
  | Signed, I8 -> "str_to_int8"
  | Signed, I16 -> "str_to_int16"
  | Signed, I32 -> "str_to_int"
  | Signed, I64 -> "str_to_int64"
  | Signed, IPtr -> "str_to_intptr"
  | Unsigned, I8 -> "str_to_uint8"
  | Unsigned, I16 -> "str_to_uint16"
  | Unsigned, I32 -> "str_to_uint32"
  | Unsigned, I64 -> "str_to_uint64"
  | Unsigned, IPtr -> "str_to_uintptr"

let cStringOfIntegerFunName flavor =
  let (IntFlavor (signedness, _)) = flavor

  match signedness with
  | Signed -> "str_of_int64"
  | Unsigned -> "str_of_uint64"
