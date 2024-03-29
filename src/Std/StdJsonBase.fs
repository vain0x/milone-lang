// F# only
module rec Std.StdJsonBase

let encodeUtf8 (codePoint: int) : string option =
  System.Text.Encoding.UTF32.GetString(System.BitConverter.GetBytes(codePoint))
  |> Some

let jsonNumberToString (n: float) = string n
