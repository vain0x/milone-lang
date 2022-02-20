module rec Std.StdStringBase

let utf8Length (s: string) : int =
  System.Text.Encoding.UTF8.GetByteCount(s)

let internal concat (sep: string) (xs: string list) : string = System.String.Join(sep, xs)
