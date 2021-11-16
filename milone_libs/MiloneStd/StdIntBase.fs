module rec MiloneStd.StdIntBase

open System

let __intOfStr (s: string) : int option =
  match Int32.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let __int64OfStr (s: string) : int64 option =
  match Int64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let __uint64OfStr (s: string) : uint64 option =
  match UInt64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None
