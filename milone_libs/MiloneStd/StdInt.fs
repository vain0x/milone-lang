module rec MiloneStd.StdInt

[<Literal>]
let MinValue = 0x80000000

[<Literal>]
let MaxValue = 0x7fffffff

let min (l: int) (r: int) : int = if l < r then l else r

let max (l: int) (r: int) : int = if l < r then r else l

let tryParse (s: string) : int option = __intOfStr s
