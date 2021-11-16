/// Provides functions, whose implementations use .NET features and work only in F#.
/// Public interface of this module should be compatible with file://./MiloneOnly.milone .
[<AutoOpen>]
module rec MiloneStd.FSharpOnly

open System

let __stringJoin (sep: string) (xs: string list) : string = System.String.Join(sep, xs)

// -----------------------------------------------
// StrEnv
// -----------------------------------------------

let __argCount () : int = Environment.GetCommandLineArgs().Length

let __argGet (index: int) : string =
  Environment.GetCommandLineArgs().[index]
