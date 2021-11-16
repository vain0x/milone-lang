module rec MiloneStd.StdStringBase

let __stringLengthInUtf8Bytes (s: string) : int =
  System.Text.Encoding.UTF8.GetByteCount(s)

let __stringJoin (sep: string) (xs: string list) : string = System.String.Join(sep, xs)
