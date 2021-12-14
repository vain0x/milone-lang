module rec MiloneStd.StdInt

module B = MiloneStd.StdIntBase

[<Literal>]
let MinValue = 0x80000000

[<Literal>]
let MaxValue = 0x7fffffff

let min (l: int) (r: int) : int = if l < r then l else r

let max (l: int) (r: int) : int = if l < r then r else l

let tryParse (s: string) : int option = B.tryParseInt32 s

/// experimental
module Ext =
  let tryParseInt64 (s: string) : int64 option = B.tryParseInt64 s
  let tryParseUInt64 (s: string) : uint64 option = B.tryParseUInt64 s
