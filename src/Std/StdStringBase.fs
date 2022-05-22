module rec Std.StdStringBase

let utf8Length (s: string) : int =
  System.Text.Encoding.UTF8.GetByteCount(s)

let internal concat (sep: string) (xs: string list) : string = System.String.Join(sep, xs)

let internal stringAsPtr (_: string) : 'A = raise (System.NotSupportedException())

let internal ensureNullTerminatedString (s: string) : string = s

let internal stringToNative (_: string) = raise (System.NotSupportedException())

let internal unsafeWrapString _ptr (_: int) : string = raise (System.NotSupportedException())

let internal unsafeStringOfNative _ptr : string = raise (System.NotSupportedException())

let internal unsafeStringOfRawParts _ptr (_: int) : string = raise (System.NotSupportedException())
