module rec MiloneStd.StdInt

[<Literal>]
let MinValue = -2147483648

[<Literal>]
let MaxValue = 2147483647

let min (l: int) (r: int): int = if l < r then l else r

let max (l: int) (r: int): int = if l < r then r else l

let tryParse (s: string): int option = __intOfStr s
