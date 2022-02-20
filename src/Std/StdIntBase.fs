module rec Std.StdIntBase

open System

let internal tryParseInt32 (s: string) : int option =
  match Int32.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let internal tryParseInt64 (s: string) : int64 option =
  match Int64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let internal tryParseUInt64 (s: string) : uint64 option =
  match UInt64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None
