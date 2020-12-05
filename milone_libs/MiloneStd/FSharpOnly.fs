[<AutoOpen>]
module rec MiloneStd.FSharpOnly

let __stringJoin (sep: string) (xs: string list): string = System.String.Join(sep, xs)
