/// Provides functions, whose implementations use .NET features and work only in F#.
/// Public interface of this module should be compatible with file://./MiloneOnly.milone .
[<AutoOpen>]
module rec MiloneStd.FSharpOnly

open System

let __stringJoin (sep: string) (xs: string list) : string = System.String.Join(sep, xs)

// -----------------------------------------------
// StrInt
// -----------------------------------------------

let __intOfStr (s: string) : int option =
  match Int32.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let __int64OfStr (s: string) : int64 option =
  match Int64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

let __uint64OfStr (s: string) : uint64 option =
  match UInt64.TryParse(s) with
  | true, value -> Some value
  | false, _ -> None

// -----------------------------------------------
// StrEnv
// -----------------------------------------------

let __argCount () : int = Environment.GetCommandLineArgs().Length

let __argGet (index: int) : string =
  Environment.GetCommandLineArgs().[index]
