module rec MiloneStd.StdInt

let min (l: int) (r: int): int = if l < r then l else r

let max (l: int) (r: int): int = if l < r then r else l

let tryParse (s: string): int option = __intOfStr s
